/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 */
/* MediaTek Inc. (C) 2012. All rights reserved.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON
 * AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek Software")
 * have been modified by MediaTek Inc. All revisions are subject to any receiver's
 * applicable license agreements with MediaTek Inc.
 */

#include "typedefs.h"
#include "platform.h"
#include "blkdev.h"
#include "cust_part.h"

static part_t platform_parts[PART_MAX_COUNT] = {
	{PART_PRELOADER, 0, PART_SIZE_PRELOADER, 0,PART_FLAG_NONE},
	{PART_MBR, 0, PART_SIZE_MBR, 0,PART_FLAG_NONE},
	{PART_EBR1, 0, PART_SIZE_EBR1, 0,PART_FLAG_NONE},
	{PART_PMT, 0, PART_SIZE_PMT, 0,PART_FLAG_NONE},
	{PART_PRO_INFO, 0, PART_SIZE_PRO_INFO, 0,PART_FLAG_NONE},
	{PART_NVRAM, 0, PART_SIZE_NVRAM, 0,PART_FLAG_NONE},
	{PART_PROTECT_F, 0, PART_SIZE_PROTECT_F, 0,PART_FLAG_NONE},
	{PART_PROTECT_S, 0, PART_SIZE_PROTECT_S, 0,PART_FLAG_NONE},
	{PART_SECURE, 0, PART_SIZE_SECCFG, 0,PART_FLAG_NONE},
	{PART_UBOOT, 0, PART_SIZE_UBOOT, 0,PART_FLAG_NONE},
	{PART_BOOTIMG, 0, PART_SIZE_BOOTIMG, 0,PART_FLAG_NONE},
	{PART_RECOVERY, 0, PART_SIZE_RECOVERY, 0,PART_FLAG_NONE},
	{PART_SECSTATIC, 0, PART_SIZE_SEC_RO, 0,PART_FLAG_NONE},
	{PART_MISC, 0, PART_SIZE_MISC, 0,PART_FLAG_NONE},
	{PART_LOGO, 0, PART_SIZE_LOGO, 0,PART_FLAG_NONE},
	{PART_EXPDB, 0, PART_SIZE_EXPDB, 0,PART_FLAG_NONE},
	{PART_ANDSYSIMG, 0, PART_SIZE_ANDROID, 0,PART_FLAG_NONE},
	{PART_CACHE, 0, PART_SIZE_CACHE, 0,PART_FLAG_NONE},
	{PART_USER, 0, PART_SIZE_USRDATA, 0,PART_FLAG_NONE},
	{PART_FAT, 0, PART_SIZE_FAT, 0,PART_FLAG_NONE},
	{NULL,0,0,0,PART_FLAG_END},
};

void cust_part_init(void){}

part_t *cust_part_tbl(void)
{
	 return &platform_parts[0];
}

