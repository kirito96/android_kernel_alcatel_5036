#ifndef _CUST_BATTERY_METER_H
#define _CUST_BATTERY_METER_H

#include <mach/mt_typedefs.h>

// ============================================================
// define
// ============================================================
//#define SOC_BY_AUXADC
//#define SOC_BY_HW_FG
#define SOC_BY_SW_FG

/* ADC Channel Number */
#define CUST_TABT_NUMBER 17
#define VBAT_CHANNEL_NUMBER      7
#define ISENSE_CHANNEL_NUMBER	 6
#define VCHARGER_CHANNEL_NUMBER  4
#define VBATTEMP_CHANNEL_NUMBER  5

/* ADC resistor  */
#define R_BAT_SENSE 4					
#define R_I_SENSE 4						
#define R_CHARGER_1 330
#define R_CHARGER_2 39

#define TEMPERATURE_T0             110
#define TEMPERATURE_T1             0
#define TEMPERATURE_T2             25
#define TEMPERATURE_T3             50
#define TEMPERATURE_T              255 // This should be fixed, never change the value

#define FG_METER_RESISTANCE 	0

/* Qmax for battery  */
#define Q_MAX_POS_50	1728
#define Q_MAX_POS_25	1715
#define Q_MAX_POS_0		1602
#define Q_MAX_NEG_10	1254

#define FMT_Q_MAX_POS_50	1728
#define FMT_Q_MAX_POS_25	1715
#define FMT_Q_MAX_POS_0		1602
#define FMT_Q_MAX_NEG_10	1602

#define Q_MAX_POS_50_H_CURRENT	1710
#define Q_MAX_POS_25_H_CURRENT	1698
#define Q_MAX_POS_0_H_CURRENT	1547
#define Q_MAX_NEG_10_H_CURRENT	1067

#define FMT_Q_MAX_POS_50_H_CURRENT	1710
#define FMT_Q_MAX_POS_25_H_CURRENT	1698
#define FMT_Q_MAX_POS_0_H_CURRENT	1547
#define FMT_Q_MAX_NEG_10_H_CURRENT	1067
//mingquan.lai adds to support battery id check for California(do not check in MMI version) 
#if !defined(JRD_BUILD_MMITEST)
#define BATT_ID_CHECK_SUPPORT 1
#endif

/* Discharge Percentage */
#define OAM_D5		 0		//  1 : D5,   0: D2    mingquan.lai customize 20130912


/* battery meter parameter */
#define CUST_TRACKING_POINT  14
#define CUST_R_SENSE         200
#define CUST_HW_CC 		     0
#define AGING_TUNING_VALUE   103
#define CUST_R_FG_OFFSET    0

#define OCV_BOARD_COMPESATE	0 //mV 
#define R_FG_BOARD_BASE		1000
#define R_FG_BOARD_SLOPE	1000 //slope
#define CAR_TUNE_VALUE		94 //1.00


/* HW Fuel gague  */
#define CURRENT_DETECT_R_FG	10  //1mA
#define MinErrorOffset       1000
#define FG_VBAT_AVERAGE_SIZE 18
#define R_FG_VALUE 			0 // mOhm, base is 20



/* Disable Battery check for HQA */
#ifdef MTK_DISABLE_POWER_ON_OFF_VOLTAGE_LIMITATION
#define FIXED_TBAT_25
#endif

#endif	//#ifndef _CUST_BATTERY_METER_H
