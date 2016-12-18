#include <target/board.h>

//#define CFG_POWER_CHARGING

#ifdef CFG_POWER_CHARGING
#include <platform/mt_typedefs.h>
#include <platform/mt_reg_base.h>
#include <platform/mt_pmic.h>
#include <platform/boot_mode.h>
#include <platform/mt_gpt.h>
#include <platform/mt_sleep.h>
#include <platform/mt_rtc.h>
#include <platform/mt_disp_drv.h>
#include <platform/mtk_wdt.h>
#include <platform/mtk_key.h>
#include <platform/mt_logo.h>
#include <platform/mt_leds.h>
#include <printf.h>
#include <sys/types.h>
#include <target/cust_battery.h>

#undef printf

#if BATT_ID_CHECK_SUPPORT
#define AUXADC_BATT_ID_CHANNEL 0
#define CHG_MIN_VALID_BATT_ID  700
#define CHG_MAX_VALID_BATT_ID  1000
#define FMT_CHG_MIN_VALID_BATT_ID  1300
#define FMT_CHG_MAX_VALID_BATT_ID  1650
int byd_fmt_batt_id;  // 1 BYD 2 FMT
#endif
/*****************************************************************************
 *  Type define
 ****************************************************************************/
#define BATTERY_LOWVOL_THRESOLD             3500   //mingquan.lai set to 3.5V for CR460828


/*****************************************************************************
 *  Global Variable
 ****************************************************************************/
bool g_boot_reason_change = false;


/*****************************************************************************
 *  Externl Variable
 ****************************************************************************/
extern bool g_boot_menu;


void kick_charger_wdt(void)
{
    upmu_set_rg_chrwdt_td(0x0);           // CHRWDT_TD, 4s
    upmu_set_rg_chrwdt_wr(1); 			  // CHRWDT_WR
    upmu_set_rg_chrwdt_int_en(1);         // CHRWDT_INT_EN
    upmu_set_rg_chrwdt_en(1);             // CHRWDT_EN
    upmu_set_rg_chrwdt_flag_wr(1);        // CHRWDT_WR
}


void pchr_turn_on_charging (void)
{
	upmu_set_rg_usbdl_rst(1);		//force leave USBDL mode
	
	kick_charger_wdt();
	
	upmu_set_rg_cs_vth(0xC);    	// CS_VTH, 450mA	
	upmu_set_rg_csdac_en(1);        // CSDAC_EN
    upmu_set_rg_chr_en(1);          // CHR_EN       
}

#if BATT_ID_CHECK_SUPPORT
extern int IMM_GetOneChannelValue(int dwChannel, int data[4], int* rawdata);
void check_battery_id(void){
	int i = 0, bat_id_vol = 0, data[4] = {0,0,0,0};
	int res =0;
	int rawdata = 0;
	printf("check_battery_id() begin:20130528");

	for(i = 0; i < 3; i++)     
	{    
		res = IMM_GetOneChannelValue(AUXADC_BATT_ID_CHANNEL,data,&rawdata);
		if(res < 0)
		{
			printf("[BATTERY][adc_driver]: get data error\n");
			break;
		}
		else
		{
			printf("[BATTERY][adc_driver]: channel0[%d]raw = %d\n",i,rawdata);
		}
		msleep(5);	
		bat_id_vol += (rawdata * 1500 / 4096);
		printf("[BATTERY]adc: channel0[%d]vol = %d\n",i,rawdata * 1500 / 4096);
	}

	if(res < 0)  /*get adc value fail*/
		return res; 

	bat_id_vol = bat_id_vol/3;       
	if((bat_id_vol < CHG_MIN_VALID_BATT_ID) || ((bat_id_vol > CHG_MAX_VALID_BATT_ID)&&(bat_id_vol < FMT_CHG_MIN_VALID_BATT_ID))||(bat_id_vol > FMT_CHG_MAX_VALID_BATT_ID)) /*battery id error*/
  	{
		printf("[BATTERY]battery id error %d!\n", bat_id_vol);
       //BMT_status.bat_id_valid = 0;	
	  
      // pchr_turn_off_charging();//turn off charging
      // leds_battery_full_charging();//turn off led
#if 1
        #ifndef NO_POWER_OFF
		printf("mt6575_power_off() called:20130528");
        mt6575_power_off();//power off
        
        #endif
        while(1);	
#endif
   	}
	else if((bat_id_vol < CHG_MAX_VALID_BATT_ID)&&(bat_id_vol > CHG_MIN_VALID_BATT_ID))
  	{
		//BMT_status.bat_id_valid = 1;
		byd_fmt_batt_id = 1; //byd
		printk("[BATTERY]battery id BYD %d!\n", bat_id_vol);
  	}
  	else
  	{
       	//BMT_status.bat_id_valid = 1; 
		byd_fmt_batt_id = 2; //fmt
		printk("[BATTERY]battery id FMT %d!\n", bat_id_vol);
  	}
}
#endif	
/*add by swangxingxing for FR460121 end*/
void mt65xx_bat_init(void)
{
    int i = 0;
	kal_int32 bat_vol;

    // Low Battery Safety Booting
    
    bat_vol = get_bat_sense_volt(1);
    printf("check VBAT=%d mV with %d mV\n", bat_vol, BATTERY_LOWVOL_THRESOLD);
	#if BATT_ID_CHECK_SUPPORT	
        check_battery_id();
    #endif
    pchr_turn_on_charging();

	if(g_boot_mode == KERNEL_POWER_OFF_CHARGING_BOOT && (upmu_get_pwrkey_deb()==0) ) {
		printf("[mt65xx_bat_init] KPOC+PWRKEY => change boot mode\n");
		
		g_boot_reason_change = true;
	}
    rtc_boot_check(false);

	#ifndef MTK_DISABLE_POWER_ON_OFF_VOLTAGE_LIMITATION
    if (bat_vol < BATTERY_LOWVOL_THRESOLD)
    {
        if(g_boot_mode == KERNEL_POWER_OFF_CHARGING_BOOT && upmu_is_chr_det() == KAL_TRUE)
        {
            printf("[%s] Kernel Low Battery Power Off Charging Mode\n", __func__);
            g_boot_mode = LOW_POWER_OFF_CHARGING_BOOT;
            return;
        }
        else
        {
            printf("[BATTERY] battery voltage(%dmV) <= CLV ! Can not Boot Linux Kernel !! \n\r",bat_vol);
#ifndef NO_POWER_OFF
            mt6575_power_off();
#endif			
            while(1)
            {
                printf("If you see the log, please check with RTC power off API\n\r");
            }
        }
    }
	#endif
    return;
}

#else

#include <platform/mt_typedefs.h>
#include <platform/mt_reg_base.h>
#include <printf.h>

void mt65xx_bat_init(void)
{
    printf("[BATTERY] Skip mt65xx_bat_init !!\n\r");
    printf("[BATTERY] If you want to enable power off charging, \n\r");
    printf("[BATTERY] Please #define CFG_POWER_CHARGING!!\n\r");
}

#endif
