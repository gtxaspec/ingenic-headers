/*
 * Ingenic IMP ISPOSD solution.
 *
 * Copyright (C) 2021 Ingenic Semiconductor Co.,Ltd
 * Author: Jim <jim.wang@ingenic.com>
 */

#include <stdio.h>
#include <string.h>
#include <semaphore.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <imp/imp_log.h>
#include <imp/imp_osd.h>
//#include <constraints.h>
#include <imp/imp_utils.h>

#ifndef __ISP_OSD_H__
#define __ISP_OSD_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */


/**
 * @fn int IMP_OSD_Init_ISP(void);
 *
 * ISPOSD resources are initialized and integrated into the IMP_system_init interface.
 * Users do not need to invoke the resource
 *
 * @param None
 *
 * @retval 0 success
 * @retval no-0 failure
 *
 * @remarks None
 *
 * @attention the interface is being gradually deprecated.
 */
int IMP_OSD_Init_ISP(void);

/**
 * @fn int IMP_OSD_SetPoolSize_ISP(int size)
 *
 * create ISPOSD's rmem size
 *
 * @param[in] size Create ISPOSD's rmem size
 *
 * @retval 0 success
 * @retval no-0 failure
 *
 * @remarks None
 *
 * @attention the interface is being gradually deprecated.
 */
int IMP_OSD_SetPoolSize_ISP(int size);

/**
 * @fn int IMP_OSD_CreateRgn_ISP(int chn,IMPIspOsdAttrAsm *pIspOsdAttr)
 *
 * Create ISPOSD's region
 *
 * @param[in] chn Sensor ID for creating ISPOSD, range 0-3
 * @param[in] IMPIspOsdAttrAsm ISPOSD attributes
 *
 * @retval handle Region handle number
 *
 * @remarks None
 *
 * @attention the interface is being gradually deprecated.
 */
int IMP_OSD_CreateRgn_ISP(int chn,IMPIspOsdAttrAsm *pIspOsdAttr);

/**
 * @fn int IMP_OSD_SetRgnAttr_PicISP(int chn,int handle, IMPIspOsdAttrAsm *pIspOsdAttr)
 *
 * set ISPOSDattr
 *
 * @param[in] chn Sensor ID for which ISPOSD needs to be configured, range 0-3
 * @param[in] handle ISPOSD region handle
 * @param[in] IMPIspOsdAttrAsm ISPOSD attribute structure
 *
 * @retval 0 success
 * @retval no-0 failure
 *
 * @remarks None
 *
 * @attention the interface is being gradually deprecated.
 */
int IMP_OSD_SetRgnAttr_PicISP(int chn,int handle, IMPIspOsdAttrAsm *pIspOsdAttr);

/**
 * @fn int IMP_OSD_GetRgnAttr_ISPPic(int chn,int handle, IMPIspOsdAttrAsm *pIspOsdAttr)
 *
 * Get ISPOSD's IMPIspOsdAttrAsm from chn's handle
 *
 * @param[in] chn Sensor ID for configuring ISPOSD, range 0-3
 * @param[in] handle ISPOSD region handle
 * @param[out] IMPIspOsdAttrAsm ISPOSD attribute structure
 *
 * @retval 0 success
 * @retval no-0 failure
 *
 * @remarks None
 *
 * @attention the interface is being gradually deprecated.
 */

int IMP_OSD_GetRgnAttr_ISPPic(int chn,int handle, IMPIspOsdAttrAsm *pIspOsdAttr);

/**
 * @fn int IMP_OSD_ShowRgn_ISP( int chn,int handle, int showFlag)
 *
 * Set ISPOSD's chn's handle show flag status
 *
 * @param[in] chn Sensor ID for enable/disable ISPOSD, range 0-3
 * @param[in] handle ISPOSD region handle
 * @param[in] showFlag Flag to enable ISPOSD display
 *
 * @retval 0 success
 * @retval no-0 failure
 *
 * @remarks None
 *
 * @attention the interface is being gradually deprecated.
 */
int IMP_OSD_ShowRgn_ISP( int chn,int handle, int showFlag);

/**
 * @fn int IMP_OSD_DestroyRgn_ISP(int chn,int handle)
 *
 * destroy the region of channel
 *
 * @param[in] chn Sensor ID for destroying the ISPOSD region, range 0-3
 * @param[in] handle ISPOSD region handle
 *
 * @retval 0 success
 * @retval no-0 failure
 *
 * @remarks None
 *
 * @attention the interface is being gradually deprecated.
 */
int IMP_OSD_DestroyRgn_ISP(int chn,int handle);

/**
 * @fn void IMP_OSD_Exit_ISP(void)
 *
 * destroy ISPOSD's resource,used in IMP_System_Exit，and suggest customer not use this interface
 *
 * @param None
 *
 * @retval None
 *
 * @remarks None
 *
 * @attention the interface is being gradually deprecated.
 */
void IMP_OSD_Exit_ISP(void);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif

