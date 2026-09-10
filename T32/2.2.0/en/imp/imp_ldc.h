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
	IMPISP_Offline_DISABLE,		/**<Disable the offline LDC module and close the offline LDC device. */
	IMPISP_Offline_ENABLE,		/**<Enable the offline LDC module and open the offline LDC device */
	IMPISP_Offline_BUTT,        /**<effect paramater, parameters have to be less than this value */
} IMPISPLDCOfflineOpsMode;

/**
 * @fn int32_t IMP_ISP_LDC_OfflineInit(IMPISPLDCOfflineOpsMode mode);
 *
 * LDC offline mode initialization interface
 *
 * @param[in] mode      offlineLDC initialization attribute.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention This function needs to be called after invoking the IMP_ISP_LDC_SetMode interface.。
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
} IMPISPLDCCalibrationParam;  /**<Parameters used for generating the LUT table */

typedef enum {
	IMPISP_LDC_PARAM = 0,  /**<Using the parameter to generate the LUT table mode */
	IMPISP_LDC_LUT,        /**<Direct reading mode of LUT table file */
	IMPISP_LDC_LUT_ADDR,   /**<Read the LUT table from a memory address directly. The table format is header + data, and the header size is 128 bytes. */
} IMPISPLDCLutMode;

typedef struct {
	void *addr;       /**<Start address of the LUT table in memory */
	uint32_t length;  /**<Size of the LUT table in memory, in bytes;It is composed of header information and data, the size of header is 128 bytes. */
} IMPISPLDCLutAddr;

typedef struct {
	IMPISPLDCFunc                  func;           /**<The offline mode only supports I2D and LDC functions. To create a Job configuration, select all the required functions using | */
	uint16_t                       width;          /**<The current input width */
	uint16_t                       height;         /**<The current input height */
	IMPISPLDCLutBlockSize          size;           /**<The block size in the lut table */
	IMPISPLDCLutMode               ldc_lut_mode;   /**<Choose the mode of directly reading the LUT table file or the mode of generating the LUT table using parameters. */
	union {
		char                       lut_name[128];  /**<The file path of the LUT table, the absolute path, and the mode for directly reading the LUT table file when used */
		IMPISPLDCCalibrationParam  param;          /**<Parameters used for generating the LUT table */
		IMPISPLDCLutAddr			lut_addr;		/*< The memory address of LUT table*/
	};
	uint32_t                       job_hander;     /**<Output parameter, Handle of Job */
} IMPISPLDCJobAttr;

/**
 * @fn int32_t IMP_ISP_LDC_OfflineCreateJob(IMPISPLDCJobAttr *attr)
 *
 * Create LDC offline mode Job
 *
 * @param[in] attr  offline LDC attribute.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention This function needs to be called after invoking the IMP_ISP_LDC_OfflineInit interface.
 */
int32_t IMP_ISP_LDC_OfflineCreateJob(IMPISPLDCJobAttr *attr);

typedef struct {
	IMPISPLDCFunc                  func;           /**<The offline mode only supports I2D and LDC functions. When creating a job, select all required functions by combining them with | */
	uint16_t                       src_width;      /**<Current input width */
	uint16_t                       src_height;     /**<Current input height */
	uint16_t                       dst_width;      /**<Current output width, valid in LDC mode */
	uint16_t                       dst_height;     /**<Current output height, valid in LDC mode */
	IMPISPLDCLutBlockSize          size;           /**<The block size in the LUT table */
	IMPISPLDCLutMode               ldc_lut_mode;   /**<Select direct LUT file loading mode or parameter-based LUT generation mode */
	union {
		char                       lut_name[128];  /**<Absolute path of the LUT table file, used in direct LUT file loading mode */
		IMPISPLDCCalibrationParam  param;          /**<Parameters used for generating the LUT table */
		IMPISPLDCLutAddr           lut_addr;       /**<LUT table memory address parameters */
	};
	uint32_t                       job_hander;     /**<Output parameter, handle of the job */
} IMPISPLDCJobAttrExt;

/**
 * @fn int32_t IMP_ISP_LDC_OfflineCreateJobExt(IMPISPLDCJobAttrExt *attr)
 *
 * Create a full-featured LDC offline mode job
 *
 * @param[in] attr  Offline LDC attributes.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention This function needs to be called after invoking the IMP_ISP_LDC_OfflineInit interface.
 * @attention This function is not supported on T32V.
 */
int32_t IMP_ISP_LDC_OfflineCreateJobExt(IMPISPLDCJobAttrExt *attr);

/**
 * @fn int32_t IMP_ISP_LDC_OfflineDestroyJob(uint32_t job_handler)
 *
 * Destroy LDC offline mode Job
 *
 * @param[in] job_handler  The handle output when creating a Job.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention This function should be called after invoking the IMP_ISP_LDC_OfflineCreateJob interface, ensuring that all tasks have been completed.
 */
int32_t IMP_ISP_LDC_OfflineDestroyJob(uint32_t job_handler);

typedef struct {
	uint32_t job_hander;   /**<Input parameters, the handle of job */
	uint32_t addr_in;      /**<Enter the Y address */
	uint32_t addr_uv_in;   /**<Enter the UV address */
	uint32_t addr_out;     /**<Output Y address */
	uint32_t addr_uv_out;  /**<Output UV address */
	uint16_t stride_in;    /**<Input stride */
	uint16_t stride_out;   /**<Output stride */
	IMPISPLDCI2dAngle  angle;  /**<When using I2D, configuration is required and the rotation angle needs to be specified. */
	IMPISPLDCFunc      func;   /**<Select the functions required for the current task */
} IMPISPLDCTaskAttr;

/**
 * @fn int32_t IMP_ISP_LDC_OfflineSubmitTask(IMPISPLDCTaskAttr *attr)
 *
 * Submit the offline mode LDC correction task
 *
 * @param[in] attr  Offline LDC task attribute.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention This function needs to be called after invoking the IMP_ISP_LDC_OfflineCreateJob interface,And it is necessary to ensure that IMP_ISP_EnableSensor has been called.
 */
int32_t IMP_ISP_LDC_OfflineSubmitTask(IMPISPLDCTaskAttr *attr);

typedef struct {
	uint32_t          job_hander;  /**<Input parameters, the handle of job */
	IMPISPLDCLutMode  lut_mode;    /**<Choose the mode of directly reading the LUT table file or the mode of generating the LUT table using parameters. */
	union {
		char                       lut_name[128];  /**<The file path of the LUT table, the absolute path, and the mode for directly reading the LUT table file when used */
		IMPISPLDCCalibrationParam  param;          /**<Parameters used for generating the LUT table */
		IMPISPLDCLutAddr			lut_addr;		/*< The memory address of LUT table */
	};
} IMPISPLDCUpdateLutAttr;

/**
 * @fn int32_t IMP_ISP_LDC_OfflineUpdateLutToJob(IMPISPLDCUpdateLutAttr *attr)
 *
 * Offline LDC is based on Job replacement of lut table
 *
 * @param[in] attr  Offline LDC replaces the attributes of the lut table.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention This function needs to be called after invoking the IMP_ISP_LDC_OfflineCreateJob interface.
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
