/*
 * IMP ISP header file.
 *
 * Copyright (C) 2022 Ingenic Semiconductor Co.,Ltd
 */

#ifndef __IMP_LDC_H__
#define __IMP_LDC_H__

#include <stdbool.h>
#include "imp_common.h"
#include "imp_isp.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

typedef enum {
	IMPISP_Offline_DISABLE,		/**< 不使能离线LDC模块,close离线LDC设备 */
	IMPISP_Offline_ENABLE,		/**< 使能离线LDC模块,open离线LDC设备 */
	IMPISP_Offline_BUTT,        /**< 用于判断参数的有效性，参数大小必须小于这个值 */
} IMPISPLDCOfflineOpsMode;

/**
 * @fn int32_t IMP_ISP_LDC_OfflineInit(IMPISPLDCOfflineOpsMode mode);
 *
 * LDC离线模式初始化接口
 *
 * @param[in] mode      离线LDC初始化属性.
 *
 * @retval 0 成功
 * @retval 非0 失败，返回错误码
 *
 * @attention 此函数需要在调用IMP_ISP_LDC_SetMode接口之后。
 */
int32_t IMP_ISP_LDC_OfflineInit(IMPISPLDCOfflineOpsMode mode);

typedef struct {
	int blocksize;
	double strength;
	double d0;
	double d1;
	double d2;
	double d3;
	double fx;
	double fy;
	double cx;
	double cy;
} IMPISPLDCCalibrationParam; /**<用于生成LUT表的参数 */

typedef enum {
	IMPISP_LDC_PARAM = 0, /**<使用参数生成LUT表模式 */
	IMPISP_LDC_LUT,       /**<直接读取LUT表文件模式 */
	IMPISP_LDC_LUT_ADDR,  /**<直接读取LUT表地址模式，直接是LUT表地址；该表格式为 header + data, header size is 128Bytes */
} IMPISPLDCLutMode;

typedef struct {
	void *addr;			/**< LUT表内存起始地址 */
	uint32_t length;	/**< LUT表内存大小，单位bytes */
} IMPISPLDCLutAddr;

typedef struct {
	IMPISPLDCFunc                  func;           /**< 离线模式仅支持I2D和LDC功能，创建Job配置所有需要的功能使用|进行多选 */
	uint16_t                       width;          /**<当前输入和输出的宽度 */
	uint16_t                       height;         /**<当前输入和输出的高度 */
	IMPISPLDCLutBlockSize          size;           /**<lut表中的分块大小 */
	IMPISPLDCLutMode               ldc_lut_mode;   /**<选择直接读取LUT表文件模式或者使用参数生成LUT表模式 */
	union {
		char                       lut_name[128];  /**< lut表的文件路径，绝对路径，直接读取LUT表文件模式下使用*/
		IMPISPLDCCalibrationParam  param;          /**<用于生成LUT表的参数 */
		IMPISPLDCLutAddr			lut_addr;		/*< lut表参数内存地址参数 */
	};
	uint32_t                       job_hander;     /**<输出参数,Job的句柄 */
} IMPISPLDCJobAttr;

/**
 * @fn int32_t IMP_ISP_LDC_OfflineCreateJob(IMPISPLDCJobAttr *attr)
 *
 * 创建LDC离线模式Job
 *
 * @param[in] attr  离线LDC属性.
 *
 * @retval 0 成功
 * @retval 非0 失败，返回错误码
 *
 * @attention 此函数需要在调用IMP_ISP_LDC_OfflineInit接口之后。
 */
int32_t IMP_ISP_LDC_OfflineCreateJob(IMPISPLDCJobAttr *attr);


typedef struct {
	IMPISPLDCFunc                  func;           /**< 离线模式仅支持I2D和LDC功能，创建Job配置所有需要的功能使用|进行多选 */
	uint16_t                       src_width;          /**<当前输入的宽度 */
	uint16_t                       src_height;         /**<当前输入的高度 */
	uint16_t                       dst_width;          /**<当前输出的宽度（LDC模式下有效） */
	uint16_t                       dst_height;         /**<当前输出的高度（LDC模式下有效）*/
	IMPISPLDCLutBlockSize          size;           /**<lut表中的分块大小 */
	IMPISPLDCLutMode               ldc_lut_mode;   /**<选择直接读取LUT表文件模式或者使用参数生成LUT表模式 */
	union {
		char                       lut_name[128];  /**< lut表的文件路径，绝对路径，直接读取LUT表文件模式下使用*/
		IMPISPLDCCalibrationParam  param;          /**<用于生成LUT表的参数 */
		IMPISPLDCLutAddr			lut_addr;		/*< lut表参数内存地址参数 */
	};
	uint32_t                       job_hander;     /**<输出参数,Job的句柄 */
} IMPISPLDCJobAttrExt;

/**
 * @fn int32_t IMP_ISP_LDC_OfflineCreateJobExt(IMPISPLDCJobAttrExt *attr)
 *
 * 创建全功能LDC离线模式Job
 *
 * @param[in] attr  离线LDC属性.
 *
 * @retval 0 成功
 * @retval 非0 失败，返回错误码
 *
 * @attention 此函数需要在调用IMP_ISP_LDC_OfflineInit接口之后。
 * @attention 此函数T32V不支持。
 */
int32_t IMP_ISP_LDC_OfflineCreateJobExt(IMPISPLDCJobAttrExt *attr);


/**
 * @fn int32_t IMP_ISP_LDC_OfflineDestroyJob(uint32_t job_handler)
 *
 * 销毁LDC离线模式Job
 *
 * @param[in] job_handler  创建Job时输出的句柄.
 *
 * @retval 0 成功
 * @retval 非0 失败，返回错误码
 *
 * @attention 此函数需要在调用IMP_ISP_LDC_OfflineCreateJob接口之后调用,确保所有task都已经完成。
 */
int32_t IMP_ISP_LDC_OfflineDestroyJob(uint32_t job_handler);

typedef struct {
	uint32_t job_hander;   /**<输入参数,job的句柄 */
	uint32_t addr_in;      /**<输入Y地址 */
	uint32_t addr_uv_in;   /**<输入UV地址 */
	uint32_t addr_out;     /**<输出Y地址 */
	uint32_t addr_uv_out;  /**<输出UV地址 */
	uint16_t stride_in;    /**<输入跨度 */
	uint16_t stride_out;   /**<输出跨度 */
	IMPISPLDCI2dAngle  angle;  /**< 使用I2D时需要配置，旋转的角度*/
	IMPISPLDCFunc      func;   /**<选择当前task需要使用的功能 */
} IMPISPLDCTaskAttr;

/**
 * @fn int32_t IMP_ISP_LDC_OfflineSubmitTask(IMPISPLDCTaskAttr *attr)
 *
 * 提交离线模式LDC矫正任务
 *
 * @param[in] attr  离线LDC task属性.
 *
 * @retval 0 成功
 * @retval 非0 失败，返回错误码
 *
 * @attention 此函数需要在调用IMP_ISP_LDC_OfflineCreateJob接口之后。
 */
int32_t IMP_ISP_LDC_OfflineSubmitTask(IMPISPLDCTaskAttr *attr);

typedef struct {
	uint32_t          job_hander;  /**<输入参数,job的句柄 */
	IMPISPLDCLutMode  lut_mode;    /**<选择直接读取LUT表文件模式或者使用参数生成LUT表模式 */
	union {
		char                       lut_name[128];  /**< lut表的文件路径，绝对路径，直接读取LUT表文件模式下使用*/
		IMPISPLDCCalibrationParam  param;          /**<用于生成LUT表的参数 */
		IMPISPLDCLutAddr			lut_addr;		/*< lut表参数内存地址参数, 包括128bytes头 + lut数据 */
	};
} IMPISPLDCUpdateLutAttr;

/**
 * @fn int32_t IMP_ISP_LDC_OfflineUpdateLutToJob(IMPISPLDCUpdateLutAttr *attr)
 *
 * 离线LDC基于Job替换lut表
 *
 * @param[in] attr  离线LDC替换lut表属性.
 *
 * @retval 0 成功
 * @retval 非0 失败，返回错误码
 *
 * @attention 此函数需要在调用IMP_ISP_LDC_OfflineCreateJob接口之后,且需要确保IMP_ISP_EnableSensor已经调用。
 */
int32_t IMP_ISP_LDC_OfflineUpdateLutToJob(IMPISPLDCUpdateLutAttr *attr);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

/**
 * @}
 */

#endif /* __IMP_ISP_H__ */
