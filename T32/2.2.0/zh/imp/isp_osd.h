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
 * ISPOSD资源初始化，集成在IMP_system_init接口中，用户无需再调用
 *
 * @param 无
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remarks 无。
 *
 * @attention 该接口逐渐弃用。
 */
int IMP_OSD_Init_ISP(void);

/**
 * @fn int IMP_OSD_SetPoolSize_ISP(int size)
 *
 * 创建ISPOSD使用的rmem内存大小
 *
 * @param[in] size ISPOSD使用的rmem内存大小
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remarks 无。
 *
 * @attention 该接口逐渐弃用。
 */
int IMP_OSD_SetPoolSize_ISP(int size);

/**
 * @fn int IMP_OSD_CreateRgn_ISP(int chn,IMPIspOsdAttrAsm *pIspOsdAttr)
 *
 * 创建ISPOSD区域
 *
 * @param[in] chn 需要创建ISPOSD的sensor标号，范围0~3
 * @param[in] IMPIspOsdAttrAsm ISPOSD属性
 *
 * @retval handle 区域句柄号
 *
 * @remarks 无。
 *
 * @attention 该接口逐渐弃用。
 */
int IMP_OSD_CreateRgn_ISP(int chn,IMPIspOsdAttrAsm *pIspOsdAttr);

/**
 * @fn int IMP_OSD_SetRgnAttr_PicISP(int chn,int handle, IMPIspOsdAttrAsm *pIspOsdAttr)
 *
 * 设置ISPOSD 通道区域的属性
 *
 * @param[in] chn 需要设置ISPOSD的sensor标号，范围0~3
 * @param[in] handle ISPOSD区域句柄
 * @param[in] IMPIspOsdAttrAsm ISPOSD属性结构体
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remarks 无。
 *
 * @attention 该接口逐渐弃用。
 */
int IMP_OSD_SetRgnAttr_PicISP(int chn,int handle, IMPIspOsdAttrAsm *pIspOsdAttr);

/**
 * @fn int IMP_OSD_GetRgnAttr_ISPPic(int chn,int handle, IMPIspOsdAttrAsm *pIspOsdAttr)
 *
 * 获取ISPOSD 通道号中的区域属性
 *
 * @param[in] chn 需要获取ISPOSD属性的sensor标号，范围0~3
 * @param[in] handle ISPOSD区域句柄
 * @param[out] IMPIspOsdAttrAsm ISPOSD属性结构体
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remarks 无。
 *
 * @attention 该接口逐渐弃用。
 */

int IMP_OSD_GetRgnAttr_ISPPic(int chn,int handle, IMPIspOsdAttrAsm *pIspOsdAttr);

/**
 * @fn int IMP_OSD_ShowRgn_ISP( int chn,int handle, int showFlag)
 *
 * 设置ISPOSD通道号中的handle对应的显示状态
 *
 * @param[in] chn 需要使能/关闭ISPOSD显示的sensor标号，范围0~3
 * @param[in] handle ISPOSD区域句柄
 * @param[in] showFlag 使能ISPOSD显示
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remarks 无。
 *
 * @attention 该接口逐渐弃用。
 */
int IMP_OSD_ShowRgn_ISP( int chn,int handle, int showFlag);

/**
 * @fn int IMP_OSD_DestroyRgn_ISP(int chn,int handle)
 *
 * 销毁通道中对应的handle节点
 *
 * @param[in] chn 需要销毁ISPOSD区域的sensor标号，范围0~3
 * @param[in] handle ISPOSD区域句柄
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remarks 无。
 *
 * @attention 该接口逐渐弃用。
 */
int IMP_OSD_DestroyRgn_ISP(int chn,int handle);

/**
 * @fn void IMP_OSD_Exit_ISP(void)
 *
 * 销毁ISPOSD相关资源，集成在IMP_System_Exit接口中，用户无需再调用
 *
 * @param 无
 *
 * @retval 无
 *
 * @remarks 无。
 *
 * @attention 该接口逐渐弃用。
 */
void IMP_OSD_Exit_ISP(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif

