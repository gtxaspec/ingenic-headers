/*
 * IMP ISP header file.
 *
 * Copyright (C) 2014 Ingenic Semiconductor Co.,Ltd
 */

#ifndef __IMP_ISP_H__
#define __IMP_ISP_H__

#include <stdbool.h>
#include "imp_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

/**
 * ISP Function Toggle
 */
typedef enum {
	IMPISP_TUNING_OPS_MODE_DISABLE,			/**< DISABLE mode of the current module */
	IMPISP_TUNING_OPS_MODE_ENABLE,			/**< ENABLE mode of the current module */
	IMPISP_TUNING_OPS_MODE_BUTT,			/**< effect paramater, parameters have to be less than this value*/
} IMPISPTuningOpsMode;

/**
 * ISP Function Mode
 */
typedef enum {
	IMPISP_TUNING_OPS_TYPE_AUTO,			/**< AUTO mode of the current module*/
	IMPISP_TUNING_OPS_TYPE_MANUAL,			/**< MANUAL mode of the current module*/
	IMPISP_TUNING_OPS_TYPE_BUTT,			/**< effect paramater, parameters have to be less than this value*/
} IMPISPTuningOpsType;

/**
 * @file
 * The header file of ISP
 */

/**
 * @defgroup IMP_ISP
 * @ingroup imp
 * @brief Image signal processing unit. It contains several key function, for example, image effects setting, night scene, sensor's operations and so on.
 *
 * ISP module is not related to the data flow, so no need to process Bind, Only used for effect parameters configuration and sensor controls.
 *
 * The ISP manipulation is as follow:
 * @code
 * int32_t ret = 0;
 * ret = IMP_ISP_Open(); // step.1  create ISP module
 * if(ret < 0){
 *     printf("Failed to ISPInit\n");
 *     return -1;
 * }
 * IMPSensorInfo sensor;
 * sensor.name = "xxx";
 * sensor.cbus_type = SENSOR_CONTROL_INTERFACE_I2C; // OR SENSOR_CONTROL_INTERFACE_SPI
 * sensor.i2c = {
 * 	.type = "xxx", // I2C sets the name, this name has to be the same as the name of the sensor drivers in struct i2c_device_id.
 *	.addr = xx,	// the I2C address
 *	.i2c_adapter_id = xx, // The value is the I2C adapter ID.
 * }
 * OR
 * sensor.spi = {
 *	.modalias = "xx", // SPI sets the name, this name has to be the same as the name of the sensor drivers in struct i2c_device_id.
 *	.bus_num = xx, // It is the address of SPI bus.
 * }
 * ret = IMP_ISP_AddSensor(&sensor); //step.2, add a sensor. Before the function is called, the sensor driver has to be registered into kernel.
 * if (ret < 0) {
 *     printf("Failed to Register sensor\n");
 *     return -1;
 * }
 *
 * ret = IMP_ISP_EnableSensor(void); //step.3, Enable sensor and sensor starts to output image.
 * if (ret < 0) {
 *     printf("Failed to EnableSensor\n");
 *     return -1;
 * }
 *
 * ret = IMP_ISP_EnableTuning(); //step.4, Enable ISP tuning, then you can use ISP debug interface.
 * if (ret < 0) {
 *     printf("Failed to EnableTuning\n");
 *     return -1;
 * }
 *
 * Debug interface, please refer to the ISP debug interface documentation //step.5 Effect of debugging.
 *
 * @endcode
 * The process which uninstall(disable)ISP is as follows:
 * @code
 * int32_t ret = 0;
 * IMPSensorInfo sensor;
 * sensor.name = "xxx";
 * ret = IMP_ISP_DisableTuning(); //step.1 Turn off ISP tuning
 * if (ret < 0) {
 *     printf("Failed to disable tuning\n");
 *     return -1;
 * }
 *
 * ret = IMP_ISP_DisableSensor(); //step.2, Turn off sensor, Note that sensor will stop output pictures, so that all FrameSource should be closed.
 * if (ret < 0) {
 *     printf("Failed to disable sensor\n");
 *     return -1;
 * }
 *
 * ret = IMP_ISP_DelSensor(&sensor); //step.3, Delete sensor, before that step, the sensor has to be stopped.
 * if (ret < 0) {
 *     printf("Failed to disable sensor\n");
 *     return -1;
 * }
 *
 * ret = IMP_ISP_Close(); //step.4, After deleting all sensors, you can run this interface to clean up the ISP module.
 * if (ret < 0) {
 *     printf("Failed to disable sensor\n");
 *     return -1;
 * }
 * @endcode
 * There are more examples in the samples.
 * @{
 */

/**
* Sensor Number Label
*/
typedef enum {
	IMPVI_MAIN = 0,       /**< Main Sensor */
	IMPVI_SEC = 1,        /**< Second Sensor */
	IMPVI_THR = 2,        /**< Third Sensor */
	IMPVI_BUTT,           /**< effect paramater, parameters have to be less than this value */
} IMPVI_NUM;

/**
* The enum is types of sensor control bus.
*/
typedef enum {
	TX_SENSOR_CONTROL_INTERFACE_I2C = 1,	/**< I2C control bus */
	TX_SENSOR_CONTROL_INTERFACE_SPI,	/**< SPI control bus */
} IMPSensorControlBusType;

/**
* Defines I2C bus information
*/
typedef struct {
	char type[20];		/**< Set the name, the value must be match with sensor name in 'struct i2c_device_id' */
	int32_t addr;		/**< the I2C address */
	int32_t i2c_adapter_id;	/**< I2C adapter ID */
} IMPI2CInfo;

/**
* Defines SPI bus information
*/
typedef struct {
	char modalias[32];              /**< Set the name, the value must be match with sensor name in 'struct i2c_device_id' */
	int32_t bus_num;		/**< Address of SPI bus */
} IMPSPIInfo;

/**
* Defines Sensor data input interface
*/
typedef enum {
	IMPISP_SENSOR_VI_MIPI_CSI0 = 0,    /**< The MIPI CSI0 interface */
	IMPISP_SENSOR_VI_MIPI_CSI1 = 1,    /**< The MIPI CSI1 interface */
	IMPISP_SENSOR_VI_DVP = 2,          /**< The DVP interface */
	IMPISP_SENSOR_VI_BUTT = 3,         /**< effect paramater, parameters have to be less than this value */
} IMPSensorVinType;

/**
* Defines Sensor mclk clock source
*/
typedef enum {
	IMPISP_SENSOR_MCLK0 = 0,       /**< MCLK0 */
	IMPISP_SENSOR_MCLK1 = 1,       /**< MCLK1 */
	IMPISP_SENSOR_MCLK2 = 2,       /**< MCLK2 */
	IMPISP_SENSOR_MCLK_BUTT = 3,   /**< effect paramater, parameters have to be less than this value*/
} IMPSensorMclk;

#define GPIO_PA(n) (0 * 32 + (n))
#define GPIO_PB(n) (1 * 32 + (n))
#define GPIO_PC(n) (2 * 32 + (n))
#define GPIO_PD(n) (3 * 32 + (n))

/**
* Defines the information of sensor
*/
typedef struct {
	char name[32];					/**< the sensor name */
	IMPSensorControlBusType cbus_type;		/**< the sensor control bus type */
	union {
		IMPI2CInfo i2c;				/**< I2C bus information */
		IMPSPIInfo spi;				/**< SPI bus information */
	};
	int rst_gpio;		/**< The reset pin of sensor. */
	int pwdn_gpio;		/**< The power down pin of sensor. */
	int power_gpio;		/**< The power pin of sensor, but it is invalid now. */
	unsigned short sensor_id;               /**< The Sensor ID */
	IMPSensorVinType video_interface;       /**< The Sensor data input interface */
	IMPSensorMclk mclk;                     /**< The Sensor input mclk clock source */
	int default_boot;                       /**< The Sensor default boot setting */
} IMPSensorInfo;

/**
 * @fn int32_t IMP_ISP_Open(void)
 *
 * Open the ISP module
 *
 * @param none
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @remark After calling the function,it first creates the ISP module, then prepares to add sensor to ISP, and starts the ISP effect debugging function.
 *
 * @attention Before adding sensor image, this function must be called firstly.
 */
int32_t IMP_ISP_Open(void);

/**
 * @fn int32_t IMP_ISP_Close(void)
 *
 * Close the ISP module
 *
 * @param none
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @remark After calling the function, ISP will stop working.
 *
 * @attention Before calling this function, make sure that all FrameSources and effect debugging functions are off(disabled), and all sensors are deleted.
 */
int32_t IMP_ISP_Close(void);

/**
 * @fn int32_t IMP_ISP_SetDefaultBinPath(IMPVI_NUM num, char *path)
 *
 * Sets the default path to the ISP bin file.
 *
 * @param[in] num   The sensor num label you want to delete.
 * @param[in] path  The bin file path property to set.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @remark Sets the absolute path to the Bin file when the user-defined ISP is started.
 *
 * @attention This function must be called before adding the sensor and after opening the ISP.
 */
int32_t IMP_ISP_SetDefaultBinPath(IMPVI_NUM num, char *path);

/**
 * @fn int32_t IMP_ISP_GetDefaultBinPath(IMPVI_NUM num, char *path)
 *
 * Gets the default path to the ISP bin file.
 *
 * @param[in] num   The sensor num label you want to delete.
 * @param[out] path  The bin file path property to get.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @remark Get the absolute path to the Bin file when the user-defined ISP is started.
 *
 * @attention This function must be called after the sensor is added.
 * @attention Only bin file path attributes for a single ISP can be retrieved at a time.
 */
int32_t IMP_ISP_GetDefaultBinPath(IMPVI_NUM num, char *path);

/**
 * @fn int32_t IMP_ISP_AddSensor(IMPVI_NUM num, IMPSensorInfo *pinfo)
 *
 * Add a sensor into ISP module.
 *
 * @param[in] num   The sensor num label you want to add.
 * @param[in] pinfo The pointer for the sensor information.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @remark The sensor will be used to capture image.
 *
 * @attention Before using this function, you must ensure that the camera driver has been registered into the kernel.
*/
int32_t IMP_ISP_AddSensor(IMPVI_NUM num, IMPSensorInfo *pinfo);

/**
 * @fn int32_t IMP_ISP_DelSensor(IMPVI_NUM num, IMPSensorInfo *pinfo)
 *
 * Delete a sensor from ISP module.
 *
 * @param[in] num   The sensor num label you want to delete.
 * @param[in] pinfo The pointer for the sensor information
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @remark Delete a sensor(image sensor which would be a camera)
 *
 * @attention Before using this function, you must ensure that the sensor has been stopped working, use IMP_ISP_DisableSensor function to do so.
 * @attention In a multi-camera system, you must add IMPVI_NUM 0-1-2 before calling other APIS.
 */
int32_t IMP_ISP_DelSensor(IMPVI_NUM num, IMPSensorInfo *pinfo);

/**
 * @fn int32_t IMP_ISP_EnableSensor(IMPVI_NUM num, IMPSensorInfo *pinfo)
 *
 * Enable a sensor from ISP module.
 *
 * @param[in] num   The sensor num label you want to enable.
 * @param[in] pinfo The pointer for the sensor information
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @remark Enable a sensor(image sensor which would be a camera)
 *
 * @attention Before using this function, you must ensure that the sensor has been added, use IMP_ISP_AddSensor function to do so.
 */
int32_t IMP_ISP_EnableSensor(IMPVI_NUM num, IMPSensorInfo *info);

/**
 * @fn int32_t IMP_ISP_DisableSensor(IMPVI_NUM num)
 *
 * Disable the running sensor.
 *
 * @param[in] num    the sensor num label.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @remark  if a sensor is not used, FrameSource and ISP won't be working either.
 *
 * @attention Before using this function, you must ensure that the Framesource and ISP have stopped working.
 */
int32_t IMP_ISP_DisableSensor(IMPVI_NUM num);

/**
* Dual Camera Cache mode struct
*/
typedef enum {
	IMPISP_DUALSENSOR_SIGLE_BYPASS_MODE = 0,        /**< disable the isp dual sensor mode */
	IMPISP_DUALSENSOR_DUAL_DIRECT_MODE,		/**< dual sensor mode without cached */
	IMPISP_DUALSENSOR_DUAL_SELECT_MODE,		/**< dual sensor select mode */
	IMPISP_DUALSENSOR_DUAL_SINGLECACHED_MODE,	/**< dual sensor mode with single sensor cached */
	IMPISP_DUALSENSOR_DUAL_ALLCACHED_MODE,		/**< dual sensor mode with all sensor cached */
	IMPISP_DUALSENSOR_MODE_BUTT,			/**< effect paramater, parameters have to be less than this value*/
} IMPISPDualSensorMode;

/**
 * the sensor num you want to add on isp
 */
typedef struct {
	IMPISPTuningOpsMode en;            /**< dual mode switch enable */
	uint32_t switch_con;               /**< dual mode switch index */
	uint32_t switch_con_num;           /**< dual mode switch index num (0bit ~ 4bit)*/
} IMPISPDualSensorSwitchAttr;

/**
* the sensor num you want to add on isp
*/
typedef enum {
	IMPISP_TOTAL_ONE = 1,                       /**< add up to 1 sensor on isp */
	IMPISP_TOTAL_TWO,                           /**< add up to 2 sensor on isp */
	IMPISP_TOTAL_THR,                           /**< add up to 3 sensor on isp */
	IMPISP_TOTAL_BUTT,                          /**< effect paramater, parameters have to be less than this value */
} IMPISPSensorNum;

/**
* the joint mode when enable dual sensor mode struct
*/
typedef enum{
        IMPISP_NOT_JOINT = 0,                       /**< disable joint mode when enable dual sensor mode */
        //fs0 and fs3 splicing
        IMPISP_MAIN_ON_THE_LEFT,                    /**< main camera image on the left of joint image */
        IMPISP_MAIN_ON_THE_RIGHT,                   /**< main camera image on the right of joint image */
        IMPISP_MAIN_ON_THE_ABOVE,                   /**< main camera image on the above of joint image */
        IMPISP_MAIN_ON_THE_UNDER,                   /**< main camera image on the under of joint image */

        //fs0 and fs1 splicing
        IMPISP_MAIN_01_ON_THE_LEFT = 0x10,
        IMPISP_MAIN_01_ON_THE_RIGHT = 0x20,
        IMPISP_MAIN_01_ON_THE_ABOVE = 0x30,
        IMPISP_MAIN_01_ON_THE_UNDER = 0x40,

        //fs1 and fs4 splicing
        IMPISP_SEC_14_ON_THE_LEFT =  0x100,
        IMPISP_SEC_14_ON_THE_RIGHT = 0x200,
        IMPISP_SEC_14_ON_THE_ABOVE = 0x300,
        IMPISP_SEC_14_ON_THE_UNDER = 0x400,

        //fs3 and fs4 splicing
        IMPISP_SEC_34_ON_THE_LEFT =  0x1000,
        IMPISP_SEC_34_ON_THE_RIGHT = 0x2000,
        IMPISP_SEC_34_ON_THE_ABOVE = 0x3000,
        IMPISP_SEC_34_ON_THE_UNDER = 0x4000,

        IMPISP_MAIN_JOINT_BUTT,                     /**< effect paramater, parameters have to be less than this value */
} IMPISPDualSensorSplitJoint;

/**
* Multi Camera system parameters struct
*/
typedef struct  {
	IMPISPSensorNum sensor_num;                 /**< the sum of sensors you want to add on the isp */
	IMPISPDualSensorMode dual_mode;             /**< the cache mode when enable dual sensor mode */
	IMPISPDualSensorSwitchAttr dual_mode_switch;/**< the dual mode switch */
	IMPISPDualSensorSplitJoint joint_mode;      /**< the joint mode when enable dual sensor mode */
} IMPISPCameraInputMode;

/**
 * @fn int32_t IMP_ISP_SetCameraInputMode(IMPISPCameraInputMode *mode)
 *
 * Set the parameters of multi camera system.
 *
 * @param[in] mode 	The mode of camera input.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @remark Set the parameters of multi camera system.
 *
 * @attention Have to call this function before IMP_ISP_AddSensor.
 */
int32_t IMP_ISP_SetCameraInputMode(IMPISPCameraInputMode *mode);

/**
 * @fn int32_t IMP_ISP_GetCameraInputMode(IMPISPCameraInputMode *mode)
 *
 * Get the parameters of multi camera system.
 *
 * @param[in] mode 	The mode of camera input.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @remark Get the parameters of multi camera system.
 *
 * @attention Have to call this function after IMP_ISP_SetCameraInputMode.
 */
int32_t IMP_ISP_GetCameraInputMode(IMPISPCameraInputMode *mode);

/**
 * @fn int32_t IMP_ISP_SetCameraInputSelect(IMPVI_NUM vinum);
 *
 * selecte the output camera of multi camera system.
 *
 * @param[in] vinum 	The label of camera input.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @remark Set the parameters of multi camera system.
 *
 * @attention Have to call this function after IMP_ISP_AddSensor.
 * @attention Only can call this function on IMPISP_DUALSENSOR_DUAL_SELECT_MODE dual sensor mode.
 */
int32_t IMP_ISP_SetCameraInputSelect(IMPVI_NUM vinum);

/**
 * @fn int32_t IMP_ISP_Tuning_SetISPBypass(IMPVI_NUM num, IMPISPTuningOpsMode *enable)
 *
 * Control ISP modules.
 *
 * @param[in] num       The sensor num label.
 * @param[in] enable 	bypass output mode (yes / no)
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @remark To enable the bypass function of the sensor, invoke this interface before AddSensor.
 * @remark To disable the bypass function of the sensor, invoke the interface before DisableSensor.
 * @remark For details about the usage process, see sample-ISP-bypass.
 *
 * @attention Before using it, make sure that ISP is working properly.
 */
int32_t IMP_ISP_Tuning_SetISPBypass(IMPVI_NUM num, IMPISPTuningOpsMode *enable);

/**
 * @fn int32_t IMP_ISP_Tuning_GetISPBypass(IMPVI_NUM num, IMPISPTuningOpsMode *enable)
 *
 * Get ISP modules state.
 *
 * @param[in] num       The sensor num label.
 * @param[out] enable 	bypass output mode (yes / no)
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @remark none
 *
 * @attention Before using it, make sure that ISP is working properly.
 */
int32_t IMP_ISP_Tuning_GetISPBypass(IMPVI_NUM num, IMPISPTuningOpsMode *enable);

/**
 * @fn int32_t IMP_ISP_WDR_ENABLE(IMPVI_NUM num, IMPISPTuningOpsMode *mode)
 *
 * Toggle ISP WDR Mode.
 *
 * @param[in] num       The sensor num label.
 * @param[in] mode     ISP WDR mode
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Have to call this function before IMP_ISP_AddSensor for the first time.
 */
int32_t IMP_ISP_WDR_ENABLE(IMPVI_NUM num, IMPISPTuningOpsMode *mode);

/**
 * @fn int32_t IMP_ISP_WDR_ENABLE_GET(IMPVI_NUM num, IMPISPTuningOpsMode *mode)
 *
 * Get ISP WDR Mode.
 *
 * @param[in] num       The sensor num label.
 * @param[out] mode     ISP WDR mode
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using that function, make sure that ISP is working properly.
 */
int32_t IMP_ISP_WDR_ENABLE_GET(IMPVI_NUM num, IMPISPTuningOpsMode *mode);

/**
 * @fn int32_t IMP_ISP_EnableTuning(void)
 *
 * Enable effect debugging of ISP
 *
 * @param[in] void    none.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using this function, you must ensure that 'IMP_ISP_EnableSensor' is working.
 */
int32_t IMP_ISP_EnableTuning(void);

/**
 * @fn int32_t IMP_ISP_DisableTuning(void)
 *
 * Disable effect debugging of ISP
 *
 * @param void    none
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention First you must ensure that ISP is no longer working, then stop the sensor, after that you can use this function.
 */
int32_t IMP_ISP_DisableTuning(void);

/**
 * @fn int32_t IMP_ISP_SetSensorRegister(IMPVI_NUM num, uint32_t *reg, uint32_t *value)
 *
 * Set the value of a register of a sensor.
 *
 * @param[in] num       The sensor num label.
 * @param[in] reg 	The address of the register.
 * @param[in] value 	The value of the register.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @remark Value of a register can be directly set.
 *
 * @attention Before using this function, you must ensure that the sensor is working, so it will be able to be configured or set.
 */
int32_t IMP_ISP_SetSensorRegister(IMPVI_NUM num, uint32_t *reg, uint32_t *value);

/**
 * @fn int32_t IMP_ISP_GetSensorRegister(IMPVI_NUM num, uint32_t *reg, uint32_t *value)
 *
 * Obtain a value of the register of sensor.
 *
 * @param[in] num       The sensor num label.
 * @param[in] reg 	The address of the register.
 * @param[out] value 	The pointer of register value.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @remark You can directly obtain the value of the sensor's register.
 *
 * @attention Before using this function, you must ensure that the sensor is working.
 */
int32_t IMP_ISP_GetSensorRegister(IMPVI_NUM num, uint32_t *reg, uint32_t *value);

/**
 * Sensor attribute parameter
 */
typedef struct {
	uint32_t hts;           /**< sensor hts */
	uint32_t vts;           /**< sensor vts */
	uint32_t fps;           /**< sensor frame rate */
	uint32_t width;         /**< sensor output width */
	uint32_t height;        /**< sensor output height */
} IMPISPSENSORAttr;

/**
 * @fn int32_t IMP_ISP_Tuning_GetSensorAttr(IMPVI_NUM num, IMPISPSENSORAttr *attr)
 *
 * Get Sensor Attr.
 *
 * @param[in] num       The sensor num label.
 * @param[out] attr     Sensor attr.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using that function, make sure that ISP is working properly.
 */
int32_t IMP_ISP_Tuning_GetSensorAttr(IMPVI_NUM num, IMPISPSENSORAttr *attr);

/**
 * @fn int32_t IMP_ISP_Tuning_SetSensorFPS(IMPVI_NUM num, uint32_t *fps_num, uint32_t *fps_den)
 *
 * Set the FPS of enabled sensor.
 *
 * @param[in] num       The sensor num label.
 * @param[in] fps_num 	The numerator value of FPS.
 * @param[in] fps_den 	The denominator value of FPS.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using this function, make sure that 'IMP_ISP_EnableSensor' and 'IMP_ISP_EnableTuning' are working properly.
 */
int32_t IMP_ISP_Tuning_SetSensorFPS(IMPVI_NUM num, uint32_t *fps_num, uint32_t *fps_den);

/**
 * @fn int32_t IMP_ISP_Tuning_GetSensorFPS(IMPVI_NUM num, uint32_t *fps_num, uint32_t *fps_den)
 *
 * Get the FPS of enabled sensor.
 *
 * @param[in] num       The sensor num label.
 * @param[in] fps_num   The pointer for numerator value of FPS.
 * @param[in] fps_den   The pointer for denominator value of FPS.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using this function, make sure that 'IMP_ISP_EnableSensor' and 'IMP_ISP_EnableTuning' are working properly.
 * @attention Before starting data transmission in a Channel, you must first call this function in order to obtain the sensor's default FPS.
 */
int32_t IMP_ISP_Tuning_GetSensorFPS(IMPVI_NUM num, uint32_t *fps_num, uint32_t *fps_den);

/**
 * @fn int32_t IMP_ISP_Tuning_SetVideoDrop(void (*cb)(void))
 *
 * Set the video loss function. When there is a problem with the connection line of the sensor board, the callback function will be executed.
 *
 * @param[in] cb 	The pointer for callback function.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using it, make sure that 'IMP_ISP_EnableTuning' is working properly.
 */
int32_t IMP_ISP_Tuning_SetVideoDrop(void (*cb)(void));

/**
 * ISP Wait Frame irq parameters
 */

typedef enum {
	IMPISP_IRQ_FD = 0,	/**< frame start */
	IMPISP_IRQ_FS = 1,	/**< frame end */
} IMPISPIrqType;

/**
 * ISP Wait Frame Parameters
 */
typedef struct {
	uint32_t timeout;		/**< timeout,unit is ms */
	uint64_t cnt;			/**< Frame count */
	IMPISPIrqType irqtype;          /**< Frame irq type*/
} IMPISPWaitFrameAttr;

/**
 * @fn int32_t IMP_ISP_Tuning_WaitFrameDone(IMPVI_NUM num, IMPISPWaitFrameAttr *attr)
 * Wait frame done
 *
 * @param[in]  num      The sensor num label.
 * @param[out]  attr     frame done parameters
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using that function, make sure that ISP is working properly.
 */
int32_t IMP_ISP_Tuning_WaitFrameDone(IMPVI_NUM num, IMPISPWaitFrameAttr *attr);

/**
 * ISP Anti-flicker mode structure.
 */
typedef enum {
	IMPISP_ANTIFLICKER_DISABLE_MODE,	/**< Disable ISP antiflicker */
	IMPISP_ANTIFLICKER_NORMAL_MODE,         /**< Enable ISP antiflicker normal mode, and the min integration can not reach the sensor min integration time */
	IMPISP_ANTIFLICKER_AUTO_MODE,           /**< Enable ISP antiflicker auto mode, and the min integration can reach the sensor min integration time */
	IMPISP_ANTIFLICKER_BUTT,                /**< effect paramater, parameters have to be less than this value */
} IMPISPAntiflickerMode;

/**
 * ISP Anti-flicker attrbution structure.
 */
typedef struct {
	IMPISPAntiflickerMode mode;         /**< ISP antiflicker mode */
	uint8_t freq;                       /**< ISP antiflicker frequence */
} IMPISPAntiflickerAttr;

/**
 * @fn int32_t IMP_ISP_Tuning_SetAntiFlickerAttr(IMPVI_NUM num, IMPISPAntiflickerAttr *pattr)
 *
 * Set the antiflicker parameter.
 *
 * @param[in] num       The sensor num label.
 * @param[in] attr 	The value for antiflicker attr
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before calling this function, make sure that ISP debugging function is working.
 */
int32_t IMP_ISP_Tuning_SetAntiFlickerAttr(IMPVI_NUM num, IMPISPAntiflickerAttr *pattr);

/**
 * @fn int32_t IMP_ISP_Tuning_GetAntiFlickerAttr(IMPVI_NUM num, IMPISPAntiflickerAttr *pattr)
 *
 * Get the mode of antiflicker
 *
 * @param[in] num       The sensor num label.
 * @param[in] pattr     The pointer for antiflicker mode.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before calling this function, make sure that ISP debugging function is working.
 */
int32_t IMP_ISP_Tuning_GetAntiFlickerAttr(IMPVI_NUM num, IMPISPAntiflickerAttr *pattr);

/**
 * HV Flip mode struct
 */
typedef enum {
	IMPISP_FLIP_NORMAL_MODE = 0,	/**< normal mode */
	IMPISP_FLIP_H_MODE,				/**< ISP mirror mode */
	IMPISP_FLIP_V_MODE,				/**< ISP flip mode */
	IMPISP_FLIP_HV_MODE,			/**< ISP mirror and flip mode */
	IMPISP_FLIP_SENSOR_H_MODE,		/**< Sensor mirror mode */
	IMPISP_FLIP_SENSOR_V_MODE,		/**< Sensor flip mode */
	IMPISP_FLIP_SENSOR_HV_MODE,		/**< Sensor morror and flip mode */
	IMPISP_FLIP_IHSV_MODE,			/**< ISP mirror and Sensor flip mode */
	IMPISP_FLIP_SHIV_MODE,			/**< Sensor mirror and ISP flip mode */
	IMPISP_FLIP_MODE_BUTT,          /**< effect paramater, parameters have to be less than this value */
} IMPISPHVFLIP;

/**
 * @fn int32_t IMP_ISP_Tuning_SetHVFLIP(IMPVI_NUM num, IMPISPHVFLIP *hvflip)
 *
 * Set HV Flip mode.
 *
 * @param[in] num       The sensor num label.
 * @param[in] hvflip    HV Flip mode.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using that function, make sure that ISP is working properly.
 */
int32_t IMP_ISP_Tuning_SetHVFLIP(IMPVI_NUM num, IMPISPHVFLIP *hvflip);

/**
 * @fn int32_t IMP_ISP_Tuning_GetHVFlip(IMPVI_NUM num, IMPISPHVFLIP *hvflip)
 *
 * Get HV Flip mode.
 *
 * @param[in] num       The sensor num label.
 * @param[out] hvflip   hvflip mode.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using that function, make sure that ISP is working properly.
 */
int32_t IMP_ISP_Tuning_GetHVFlip(IMPVI_NUM num, IMPISPHVFLIP *hvflip);

/**
 * Defines the enumeration of ISP working mode.
 */
typedef enum {
	IMPISP_RUNNING_MODE_DAY = 0,        /**< ISP day mode */
	IMPISP_RUNNING_MODE_NIGHT = 1,      /**< ISP night mode */
	IMPISP_RUNNING_MODE_CUSTOM = 2,     /**< custom mode */
	IMPISP_RUNNING_MODE_BUTT,           /**< effect paramater, parameters have to be less than this value */
} IMPISPRunningMode;

/**
 * @fn int32_t IMP_ISP_Tuning_SetISPRunningMode(IMPVI_NUM num, IMPISPRunningMode *mode)
 *
 * Set ISP running mode, normal mode or night vision mode; default mode: normal mode.
 *
 * @param[in] num       The sensor num label.
 * @param[in] mode      running mode parameter
 *
 * @remark ISP running mode. If enable custom mode, must add extra custom bin file.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * Example：
 * @code
 * IMPISPRunningMode mode;
 *
 *	if( it is during a night now){
		mode = IMPISP_RUNNING_MODE_NIGHT
	}else{
		mode = IMPISP_RUNNING_MODE_DAY;
	}
	ret = IMP_ISP_Tuning_SetISPRunningMode(IMPVI_MAIN, &mode);
	if(ret){
		IMP_LOG_ERR(TAG, "IMP_ISP_Tuning_SetISPRunningMode error !\n");
		return -1;
	}
 *
 * @endcode
 *
 * @attention Before using it, make sure that 'IMP_ISP_EnableTuning' is working properly.
 */
int32_t IMP_ISP_Tuning_SetISPRunningMode(IMPVI_NUM num, IMPISPRunningMode *mode);

/**
 * @fn int32_t IMP_ISP_Tuning_GetISPRunningMode(IMPVI_NUM num, IMPISPRunningMode *pmode)
 *
 * Get ISP running mode, normal mode or night vision mode;
 *
 * @param[in] num       The sensor num label.
 * @param[in] pmode     The pointer of the running mode.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using it, make sure that 'IMP_ISP_EnableTuning' is working properly.
 */
int32_t IMP_ISP_Tuning_GetISPRunningMode(IMPVI_NUM num, IMPISPRunningMode *pmode);

/**
 * @fn int32_t IMP_ISP_Tuning_SetBrightness(IMPVI_NUM num, unsigned char *bright)
 *
 * Set the brightness of image effect.
 *
 * @param[in] num       The sensor num label.
 * @param[in] bright    The value for brightness.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @remark The default value is 128, more than 128 that means increase brightness, and less than 128 that means decrease brightness.\n
 *
 * @attention Before using it, make sure that ISP is working properly.
 */
int32_t IMP_ISP_Tuning_SetBrightness(IMPVI_NUM num, unsigned char *bright);

/**
 * @fn int32_t IMP_ISP_Tuning_GetBrightness(IMPVI_NUM num, unsigned char *pbright)
 *
 * Get the brightness of image effect.
 *
 * @param[in] num       The sensor num label.
 * @param[out] pbright   The pointer for brightness value.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @remark The default value is 128, more than 128 (increase brightness), and less than 128 (decrease brightness).\n
 *
 * @attention Before using it, make sure that ISP is working properly.
 */
int32_t IMP_ISP_Tuning_GetBrightness(IMPVI_NUM num, unsigned char *pbright);

/**
 * @fn int32_t IMP_ISP_Tuning_SetContrast(IMPVI_NUM num, unsigned char *contrast)
 *
 * Set the contrast of image effect.
 *
 * @param[in] num           The sensor num label.
 * @param[in] contrast      The value for contrast.
 *
 * @retval 0 means success.
 * @retval Other value means failure, its value is an error code.
 *
 * @remark The default value is 128, more than 128 (increase contrast), and less than 128 (decrease contrast).
 *
 * @attention Before using it, make sure that ISP is working properly.
 */
int32_t IMP_ISP_Tuning_SetContrast(IMPVI_NUM num, unsigned char *contrast);

/**
 * @fn int32_t IMP_ISP_Tuning_GetContrast(IMPVI_NUM num, unsigned char *pcontrast)
 *
 * Get the contrast of image effect.
 *
 * @param[in] num               The sensor num label.
 * @param[out] pcontrast 	The pointer for contrast.
 *
 * @retval 0 means success.
 * @retval Other value means failure, its value is an error code.
 *
 * @remark The default value is 128, more than 128 (increase contrast), and less than 128 (decrease contrast).
 *
 * @attention Before using it, make sure that ISP is working properly.
 */
int32_t IMP_ISP_Tuning_GetContrast(IMPVI_NUM num, unsigned char *pcontrast);

 /**
  * @fn int32_t IMP_ISP_Tuning_SetSharpness(IMPVI_NUM num, unsigned char *sharpness)
 *
 * Set the sharpness of image effect.
 *
 * @param[in] num               The sensor num label.
 * @param[in] sharpness 	The value for sharpening strength.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @remark The default value is 128, more than 128 (increase sharpening), and less than 128 (decrease sharpening).
 *
 * @attention Before using it, make sure that ISP is working properly.
 */
int32_t IMP_ISP_Tuning_SetSharpness(IMPVI_NUM num, unsigned char *sharpness);

/**
 * @fn int32_t IMP_ISP_Tuning_GetSharpness(IMPVI_NUM num, unsigned char *psharpness)
 *
 * Get the sharpness of image effect.
 *
 * @param[in] num               The sensor num label.
 * @param[out] psharpness 	The pointer for sharpness strength.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @remark The default value is 128, more than 128 (increase sharpening), and less than 128 (decrease sharpening).
 *
 * @attention Before using it, make sure that ISP is working properly.
 */
int32_t IMP_ISP_Tuning_GetSharpness(IMPVI_NUM num, unsigned char *psharpness);

/**
 * @fn int32_t IMP_ISP_Tuning_SetSaturation(IMPVI_NUM num, unsigned char *saturation)
 *
 * Set the saturation of image effect.
 *
 * @param[in] num           The sensor num label.
 * @param[in] saturation    The value for saturation strength.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @remark  The default value is 128, more than 128 (increase saturation), and less than 128 (decrease saturation).
 *
 * @attention Before using it, make sure that ISP is working properly.
 */

int32_t IMP_ISP_Tuning_SetSaturation(IMPVI_NUM num, unsigned char *saturation);

/**
 * @fn int32_t IMP_ISP_Tuning_GetSaturation(IMPVI_NUM num, unsigned char *psaturation)
 *
 * Get the saturation of image effect.
 *
 * @param[in] num                   The sensor num label.
 * @param[in] psaturation           The pointer for saturation strength.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @remark  The default value is 128, more than 128 (increase saturation), and less than 128 (decrease saturation).
 *
 * @attention Before using it, make sure that ISP is working properly.
 */
int32_t IMP_ISP_Tuning_GetSaturation(IMPVI_NUM num, unsigned char *psaturation);

/**
 * @fn int32_t IMP_ISP_Tuning_SetBcshHue(IMPVI_NUM num, unsigned char *hue)
 *
 * Set the hue of image color.
 *
 * @param[in] num       The sensor num label.
 * @param[in] hue       The value of hue, range from 0 to 255, default 128.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @remark The default value is 128, more than 128 that means increase hue, and less than 128 that means decrease hue.
 *
 * @attention Before using it, make sure that ISP is working properly.
 */
int32_t IMP_ISP_Tuning_SetBcshHue(IMPVI_NUM num, unsigned char *hue);

/**
 * @fn int32_t IMP_ISP_Tuning_GetBcshHue(IMPVI_NUM num, unsigned char *hue)
 *
 * Get the hue of image color.
 *
 * @param[in] num       The sensor num label.
 * @param[out] hue       The pointer for hue value.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @remark The default value is 128, more than 128 (increase hue), and less than 128 (decrease hue).
 *
 * @attention Before using it, make sure that ISP is working properly.
 */
int32_t IMP_ISP_Tuning_GetBcshHue(IMPVI_NUM num, unsigned char *hue);

/**
 * ISP Module Control
 */
typedef union {
	uint32_t key;                           /**< module ctrl key */
	struct {
		uint32_t bitBypassBLC : 1;      /**< [0] */
		uint32_t bitBypassLSC : 1;      /**< [1] */
		uint32_t bitBypassAWB0 : 1;     /**< [2] */
		uint32_t bitBypassWDR : 1;      /**< [3] */
		uint32_t bitBypassDPC : 1;      /**< [4] */
		uint32_t bitBypassGIB : 1;      /**< [5] */
		uint32_t bitBypassAWB1 : 1;     /**< [6] */
		uint32_t bitBypassADR : 1;      /**< [7] */
		uint32_t bitBypassDMSC : 1;     /**< [8] */
		uint32_t bitBypassCCM : 1;      /**< [9] */
		uint32_t bitBypassGAMMA : 1;    /**< [10] */
		uint32_t bitBypassDEFOG : 1;    /**< [11] */
		uint32_t bitBypassCSC : 1;      /**< [12] */
		uint32_t bitBypassMDNS : 1;     /**< [13] */
		uint32_t bitBypassYDNS : 1;     /**< [14] */
		uint32_t bitBypassBCSH : 1;     /**< [15] */
		uint32_t bitBypassCLM : 1;      /**< [16] */
		uint32_t bitBypassYSP : 1;      /**< [17] */
		uint32_t bitBypassSDNS : 1;     /**< [18] */
		uint32_t bitBypassCDNS : 1;     /**< [19] */
		uint32_t bitBypassHLDC : 1;     /**< [20] */
		uint32_t bitBypassLCE : 1;      /**< [21] */
		uint32_t bitRsv : 10;           /**< [22 ~ 30] */
	};
} IMPISPModuleCtl;

/**
 * @fn int32_t IMP_ISP_Tuning_SetModuleControl(IMPVI_NUM num, IMPISPModuleCtl *ispmodule)
 *
 * Set ISP Module control
 *
 * @param[in] num       The sensor num label.
 * @param[in] ispmodule ISP Module control.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using that function, make sure that ISP is working properly.
 */
int32_t IMP_ISP_Tuning_SetModuleControl(IMPVI_NUM num, IMPISPModuleCtl *ispmodule);

/**
 * @fn int32_t IMP_ISP_Tuning_GetModuleControl(IMPVI_NUM num, IMPISPModuleCtl *ispmodule)
 *
 * Get ISP Module control.
 *
 * @param[in] num           The sensor num label.
 * @param[out] ispmodule    ISP Module control
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using that function, make sure that ISP is working properly.
 */
int32_t IMP_ISP_Tuning_GetModuleControl(IMPVI_NUM num, IMPISPModuleCtl *ispmodule);

/**
 * ISP module ratio set array list label
 */
typedef enum {
	IMP_ISP_MODULE_SINTER = 0,  /**< sinter denoise array list label */
	IMP_ISP_MODULE_TEMPER,      /**< temper denoise array list label */
	IMP_ISP_MODULE_DRC,         /**< DRC denoise array list label(reserved) */
	IMP_ISP_MODULE_DPC,         /**< DPC denoise array list label(reserved) */
	IMP_ISP_MODULE_DEFOG,	   /**< DEFOG module array list label>*/
	IMP_ISP_MODULE_BUTT,        /**< effect paramater, parameters have to be less than this value */
} IMPISPModuleRatioArrayList;

/**
 * ISP module ratio array unit
 */
typedef struct {
	IMPISPTuningOpsMode en;   /**< module ratio enable */
	uint8_t ratio;            /**< module ratio value. The default value is 128, more than 128 (increase strength), and less than 128 (decrease strength) */
} IMPISPRatioUnit;

/**
 * ISP module ratio Attrbution
 */
typedef struct {
	IMPISPRatioUnit ratio_attr[16]; /**< module ratio attr */
} IMPISPModuleRatioAttr;

/**
 * @fn int32_t IMP_ISP_Tuning_SetModule_Ratio(IMPVI_NUM num, IMPISPModuleRatioAttr *ratio)
 *
 * set isp modules ratio.
 *
 * @param[in] num   The sensor num label.
 * @param[in] ratio module ratio set attrbution.
 *
 * @retval 0 means success.
 * @retval Other value means failure, its value is an error code.
 *
 * @attention Before using it, make sure that ISP is working properly.
 */
int32_t IMP_ISP_Tuning_SetModule_Ratio(IMPVI_NUM num, IMPISPModuleRatioAttr *ratio);

/**
 * @fn int32_t IMP_ISP_Tuning_GetModule_Ratio(IMPVI_NUM num, IMPISPModuleRatioAttr *ratio)
 *
 * set isp modules ratio.
 *
 * @param[in] num       The sensor num label.
 * @param[out] ratio     module ratio set attrbution.
 *
 * @retval 0 means success.
 * @retval Other value means failure, its value is an error code.
 *
 * @attention Before using it, make sure that ISP is working properly.
 */
int32_t IMP_ISP_Tuning_GetModule_Ratio(IMPVI_NUM num, IMPISPModuleRatioAttr *ratio);

/**
 * ISP CSC Matrix Standard
 */
typedef enum {
	IMP_ISP_CG_BT601_FULL,     /**< BT601 full range */
	IMP_ISP_CG_BT601_LIMITED,  /**< BT601 not full range */
	IMP_ISP_CG_BT709_FULL,     /**< BT709 full range */
	IMP_ISP_CG_BT709_LIMITED,  /**< BT709 not full range */
	IMP_ISP_CG_USER,           /**< CUSTOM mode. Only use this mode, the IMPISPCscMatrix parameters is valid. */
	IMP_ISP_CG_BUTT,           /**< effect paramater, parameters have to be less than this value */
} IMPISPCSCColorGamut;

/**
 * ISP CSC Matrix struct
 */
typedef struct {
	float CscCoef[9];               /**< 3x3 matrix */
	unsigned char CscOffset[2];     /**< [0]:UV offset [1]:Y offset */
	unsigned char CscClip[4];       /**< Y max, Y min, UV max, UV min */
} IMPISPCscMatrix;

/**
 * ISP CSC Attribution
 */
typedef struct {
	IMPISPCSCColorGamut ColorGamut;     /**< RGB to YUV Matrix Standard */
	IMPISPCscMatrix Matrix;             /**< Custom Matrix */
} IMPISPCSCAttr;

/**
 * @fn int32_t IMP_ISP_Tuning_SetISPCSCAttr(IMPVI_NUM num, IMPISPCSCAttr *csc)
 *
 * set csc attr
 *
 * @param[in] num   The sensor num label.
 * @param[in] csc  csc attr.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using that function, make sure that ISP is working properly.
 */
int32_t IMP_ISP_Tuning_SetISPCSCAttr(IMPVI_NUM num, IMPISPCSCAttr *csc);

/**
 * @fn int32_t IMP_ISP_Tuning_GetISPCSCAttr(IMPVI_NUM num, IMPISPCSCAttr *csc)
 *
 * Get CCM Attr.
 *
 * @param[in] num   The sensor num label.
 * @param[out] csc  csc attr.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using that function, make sure that ISP is working properly.
 */
int32_t IMP_ISP_Tuning_GetISPCSCAttr(IMPVI_NUM num, IMPISPCSCAttr *csc);

/**
 * ISP CCM Attr
 */
typedef struct {
	IMPISPTuningOpsMode ManualEn;       /**< CCM Manual enable ctrl */
	IMPISPTuningOpsMode SatEn;          /**< CCM Saturation enable ctrl */
	float ColorMatrix[9];               /**< color matrix on manual mode */
} IMPISPCCMAttr;
/**
 * @fn int32_t IMP_ISP_Tuning_SetCCMAttr(IMPVI_NUM num, IMPISPCCMAttr *ccm)
 *
 * set ccm attr
 *
 * @param[in] num   The sensor num label.
 * @param[in] ccm  ccm attr.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using that function, make sure that ISP is working properly.
 */
int32_t IMP_ISP_Tuning_SetCCMAttr(IMPVI_NUM num, IMPISPCCMAttr *ccm);

/**
 * @fn int32_t IMP_ISP_Tuning_GetCCMAttr(IMPVI_NUM num, IMPISPCCMAttr *ccm)
 *
 * Get CCM Attr.
 *
 * @param[in] num   The sensor num label.
 * @param[out] ccm  ccm attr.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using that function, make sure that ISP is working properly.
 */
int32_t IMP_ISP_Tuning_GetCCMAttr(IMPVI_NUM num, IMPISPCCMAttr *ccm);

/**
 * ISP Gamma mode enumeration
 */
typedef enum {
	IMP_ISP_GAMMA_CURVE_DEFAULT,    /**< default gamma mode */
	IMP_ISP_GAMMA_CURVE_SRGB,       /**< sRGB gamma mode */
	IMP_ISP_GAMMA_CURVE_HDR,        /**< HDR gamma mode */
	IMP_ISP_GAMMA_CURVE_USER,       /**< user define mode */
	IMP_ISP_GAMMA_CURVE_BUTT,       /**< effect paramater, parameters have to be less than this value */
} IMPISPGammaCurveType;

/**
 * Defines the attribute of gamma.
 */
typedef struct {
	IMPISPGammaCurveType Curve_type;    /**< gamma mode */
	uint16_t gamma[129];                /**< The array of gamma attribute has 129 elements */
} IMPISPGammaAttr;

/**
 * @fn int32_t IMP_ISP_Tuning_SetGammaAttr(IMPVI_NUM num, IMPISPGammaAttr *gamma)
 *
 * Sets the attributes of ISP gamma.
 *
 * @param[in] num       The sensor num label.
 * @param[in] gamma 	The pointer of the attributes.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using it, make sure that 'IMP_ISP_EnableTuning' is working properly.
 */
int32_t IMP_ISP_Tuning_SetGammaAttr(IMPVI_NUM num, IMPISPGammaAttr *gamma);

/**
 * @fn int32_t IMP_ISP_Tuning_GetGammaAttr(IMPVI_NUM num, IMPISPGammaAttr *gamma)
 *
 * Obtains the attributes of gamma.
 *
 * @param[in] num       The sensor num label.
 * @param[out] gamma 	The address of the attributes.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using it, make sure that 'IMP_ISP_EnableTuning' is working properly.
 */
int32_t IMP_ISP_Tuning_GetGammaAttr(IMPVI_NUM num, IMPISPGammaAttr *gamma);

/**
 * statistics color domain
 */
typedef enum {
	IMP_ISP_HIST_ON_RAW,   /**< Raw Domain */
	IMP_ISP_HIST_ON_YUV,   /**< YUV Domain */
} IMPISPHistDomain;

/**
 * statistics hist area struct
 */
typedef struct {
	unsigned int start_h;   /**< start pixel in the horizontal */
	unsigned int start_v;   /**< start pixel in the vertical */
	unsigned char node_h;   /**< the statistics node num in the horizontal [12 ~ 15] */
	unsigned char node_v;   /**< the statistics node num in the vertical [12 ~ 15]*/
} IMPISP3AStatisLocation;

/**
 * AE statistics attribution
 */
typedef struct {
	IMPISPTuningOpsMode ae_sta_en;  /**< AE enable*/
	IMPISP3AStatisLocation local;   /**< AE statistics location */
	IMPISPHistDomain hist_domain;   /**< AE Hist statistics color domain */
	unsigned char histThresh[4];    /**< AE Hist Thresh */
} IMPISPAEStatisAttr;

/**
 * AWB statistics value attribution
 */
typedef enum {
	IMP_ISP_AWB_ORIGIN,    /**< Original value */
	IMP_ISP_AWB_LIMITED,   /**< Limited statistics value */
} IMPISPAWBStatisMode;

/**
 * AWB statistics attribution
 */
typedef struct {
	IMPISPTuningOpsMode awb_sta_en;	/**< AWB enable*/
	IMPISP3AStatisLocation local;	/**< AWB Statistic area */
	IMPISPAWBStatisMode mode;		/**< AWB Statistic mode */
} IMPISPAWBStatisAttr;

typedef struct{
	unsigned char thlow1; 			/*Ldg low brightness threshold [Value range: 0 to 255] */
	unsigned char thlow2; 			/*Ldg low brightness threshold [Value range: 0 to 255] */
	unsigned short slplow; 			/*Ldg low brightness slope [Value range :0 to 4095]*/
	unsigned char gainlow; 			/*Ldg low-brightness gain [Value range: 0 to 255] */
	unsigned char thhigh1; 			/*Ldg High brightness threshold [Value range: 0 to 255] */
	unsigned char thhigh2; 			/*Ldg High brightness threshold [Value range: 0 to 255] */
	unsigned short slphigh; 		/*Ldg high brightness slope [Value range: 0 to 4095] */
	unsigned char gainhigh; 		/*Ldg brightness gain [Value range: 0 to 255] */
}isp_af_ldg_info;

typedef struct{
	unsigned char fir0;
	unsigned char fir1;
	unsigned char iir0;
	unsigned char iir1;
}isp_af_ldg_en;
/**
 * AF statistics attribution
 */
typedef struct {
	IMPISPTuningOpsMode af_sta_en;          /**< AF enable*/
	IMPISP3AStatisLocation local;           /**< AF statistics area */
	unsigned char af_metrics_shift;         /**< Metrics scaling factor 0x0 is default*/
	unsigned short af_delta;                /**< AF statistics low pass fliter weight [0 ~ 64]*/
	unsigned short af_theta;                /**< AF statistics high pass fliter weight [0 ~ 64]*/
	unsigned short af_hilight_th;           /**< AF high light threshold [0 ~ 255]*/
	unsigned short af_alpha_alt;            /**< AF statistics H and V direction weight [0 ~ 64]*/
	unsigned short af_belta_alt;            /**< AF statistics H and V direction weight [0 ~ 64]*/
	isp_af_ldg_en ldg_en;               	/**< AF Enables or disables the LDG module*/
	isp_af_ldg_info fir0;               	/**< LDG of FIR0 filter*/
	isp_af_ldg_info fir1;               	/**< LDG of FIR1 filter*/
	isp_af_ldg_info iir0;               	/**< LDG of IIR0 filter*/
	isp_af_ldg_info iir1;               	/**< LDG of IIR1 filter*/
} IMPISPAFStatisAttr;

/**
 * Statistics info attribution
 */
typedef struct {
	IMPISPAEStatisAttr ae;      /**< AE statistics info attr */
	IMPISPAWBStatisAttr awb;    /**< AWB statistics info attr */
	IMPISPAFStatisAttr af;      /**< AF statistics info attr */
} IMPISPStatisConfig;

/**
 * @fn int32_t IMP_ISP_Tuning_SetStatisConfig(IMPVI_NUM num, IMPISPStatisConfig *statis_config)
 *
 * set statistics attribution
 *
 * @param[in] num               The sensor num label.
 * @param[in] statis_config 	statistics configuration.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using it, make sure that 'IMP_ISP_EnableTuning' is working properly.
 */
int32_t IMP_ISP_Tuning_SetStatisConfig(IMPVI_NUM num, IMPISPStatisConfig *statis_config);

/**
 * @fn int32_t IMP_ISP_Tuning_GetStatisConfig(IMPVI_NUM num, IMPISPStatisConfig *statis_config)
 *
 * set statistics attribution
 *
 * @param[in] num               The sensor num label.
 * @param[out] statis_config 	statistics configuration.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using it, make sure that 'IMP_ISP_EnableTuning' is working properly.
 */
int32_t IMP_ISP_Tuning_GetStatisConfig(IMPVI_NUM num, IMPISPStatisConfig *statis_config);

/**
 * weight value
 */
typedef struct {
	unsigned char weight[15][15];    /**< The weight info of each zone [0 ~ 8]*/
} IMPISPWeight;

/**
 * AE weight attribute
 */
typedef struct {
	IMPISPTuningOpsMode roi_enable;     /**< roi weight set enable */
	IMPISPTuningOpsMode weight_enable;  /**< global weight set enable */
	IMPISPWeight ae_roi;                /**< roi weight value (0 ~ 8) */
	IMPISPWeight ae_weight;             /**< global weight value (0 ~ 8)*/
} IMPISPAEWeightAttr;

/**
* @fn int32_t IMP_ISP_Tuning_SetAeWeight(IMPVI_NUM num, IMPISPAEWeightAttr *ae_weight)
*
* set ae weight
*
* @param[in] num               The sensor num label.
* @param[out] ae_weight 	ae weight.
*
* @retval 0 means success.
* @retval Other values mean failure, its value is an error code.
*
* @attention Before using it, make sure that 'IMP_ISP_EnableTuning' is working properly.
*/
int32_t IMP_ISP_Tuning_SetAeWeight(IMPVI_NUM num, IMPISPAEWeightAttr *ae_weight);

/**
* @fn int32_t IMP_ISP_Tuning_GetAeWeight(IMPVI_NUM num, IMPISPAEWeightAttr *ae_weight)
*
* set ae weight
*
* @param[in] num               The sensor num label.
* @param[out] ae_weight 	ae weight.
*
* @retval 0 means success.
* @retval Other values mean failure, its value is an error code.
*
* @attention Before using it, make sure that 'IMP_ISP_EnableTuning' is working properly.
*/
int32_t IMP_ISP_Tuning_GetAeWeight(IMPVI_NUM num, IMPISPAEWeightAttr *ae_weight);

/**
 * statistics info each area
 */
typedef struct {
	uint32_t statis[15][15];    /**< statistics info each area*/
}  __attribute__((packed, aligned(1))) IMPISPStatisZone;

/**
 * AE statistics info
 */
typedef struct {
	unsigned short ae_hist_5bin[5];     /**< AE hist bin value [0 ~ 65535] */
	uint32_t ae_hist_256bin[256];       /**< AE hist bin value, is the true value of pixels num each bin */
	IMPISPStatisZone ae_statis;         /**< AE statistics info */
}  __attribute__((packed, aligned(1))) IMPISPAEStatisInfo;

/**
* @fn int32_t IMP_ISP_Tuning_GetAeStatistics(IMPVI_NUM num, IMPISPAEStatisInfo *ae_statis)
*
* set ae weight
*
* @param[in]   num                 The sensor num label.
* @param[out]  ae_statis           ae statistics.
*
* @retval 0 means success.
* @retval Other values mean failure, its value is an error code.
*
* @attention Before using it, make sure that 'IMP_ISP_EnableTuning' is working properly.
*/
int32_t IMP_ISP_Tuning_GetAeStatistics(IMPVI_NUM num, IMPISPAEStatisInfo *ae_statis);

/**
 * AE integration time unit
 */
typedef enum {
	ISP_CORE_EXPR_UNIT_LINE,			/**< The unit is integration line */
	ISP_CORE_EXPR_UNIT_US,				/**< The unit is millisecond */
} IMPISPAEIntegrationTimeUnit;

/**
 * AE exposure info
 */
typedef struct {
	IMPISPAEIntegrationTimeUnit AeIntegrationTimeUnit;     /**< AE integration time unit */
	IMPISPTuningOpsType AeMode;                            /**< AE freezen enable */
	IMPISPTuningOpsType AeIntegrationTimeMode;             /**< AE integration time manual */
	IMPISPTuningOpsType AeAGainManualMode;                 /**< AE sensor analog gain manual */
	IMPISPTuningOpsType AeDGainManualMode;                 /**< AE sensor digital gain manual */
	IMPISPTuningOpsType AeIspDGainManualMode;              /**< AE ISP digital gain manual */
	uint32_t AeIntegrationTime;                            /**< AE integration time value */
	uint32_t AeAGain;                                      /**< AE sensor analog gain value */
	uint32_t AeDGain;                                      /**< AE sensor digital gain value */
	uint32_t AeIspDGain;                                   /**< AE ISP digital gain value */

	IMPISPTuningOpsType AeMinIntegrationTimeMode;          /**< Reserve */
	IMPISPTuningOpsType AeMinAGainMode;                    /**< AE min analog gain enable */
	IMPISPTuningOpsType AeMinDgainMode;                    /**< Reserve */
	IMPISPTuningOpsType AeMinIspDGainMode;                 /**< Reserve */
	IMPISPTuningOpsType AeMaxIntegrationTimeMode;          /**< AE max integration time enable */
	IMPISPTuningOpsType AeMaxAGainMode;                    /**< AE max sensor analog gain enable */
	IMPISPTuningOpsType AeMaxDgainMode;                    /**< AE max sensor digital gain enable */
	IMPISPTuningOpsType AeMaxIspDGainMode;                 /**< AE max isp digital gain enable */
	uint32_t AeMinIntegrationTime;                         /**< AE min integration time */
	uint32_t AeMinAGain;                                   /**< AE min sensor analog gain */
	uint32_t AeMinDgain;                                   /**< AE min sensor digital gain */
	uint32_t AeMinIspDGain;                                /**< AE min isp digital gain */
	uint32_t AeMaxIntegrationTime;                         /**< AE max integration time */
	uint32_t AeMaxAGain;                                   /**< AE max sensor analog gain */
	uint32_t AeMaxDgain;                                   /**< AE max sensor digital gain */
	uint32_t AeMaxIspDGain;                                /**< AE max isp digital gain */

	/* AE Manual mode attr for short frame on WDR mode*/
	IMPISPTuningOpsType AeShortMode;                        /**< AE freezen enable */
	IMPISPTuningOpsType AeShortIntegrationTimeMode;         /**< AE integration time manual */
	IMPISPTuningOpsType AeShortAGainManualMode;             /**< AE sensor analog gain manual */
	IMPISPTuningOpsType AeShortDGainManualMode;             /**< AE sensor digital gain manual */
	IMPISPTuningOpsType AeShortIspDGainManualMode;          /**< AE ISP digital gain manual */
	uint32_t AeShortIntegrationTime;                        /**< AE integration time value */
	uint32_t AeShortAGain;                                  /**< AE sensor analog gain value */
	uint32_t AeShortDGain;                                  /**< AE sensor digital gain value */
	uint32_t AeShortIspDGain;                               /**< AE ISP digital gain value */

	IMPISPTuningOpsType AeShortMinIntegrationTimeMode;      /**< Reserve */
	IMPISPTuningOpsType AeShortMinAGainMode;                /**< AE min analog gain enable */
	IMPISPTuningOpsType AeShortMinDgainMode;                /**< Reserve */
	IMPISPTuningOpsType AeShortMinIspDGainMode;             /**< Reserve */
	IMPISPTuningOpsType AeShortMaxIntegrationTimeMode;      /**< AE max integration time enable */
	IMPISPTuningOpsType AeShortMaxAGainMode;                /**< AE max sensor analog gain enable */
	IMPISPTuningOpsType AeShortMaxDgainMode;                /**< AE max sensor digital gain enable */
	IMPISPTuningOpsType AeShortMaxIspDGainMode;             /**< AE max isp digital gain enable */
	uint32_t AeShortMinIntegrationTime;                     /**< AE min integration time */
	uint32_t AeShortMinAGain;                               /**< AE min sensor analog gain */
	uint32_t AeShortMinDgain;                               /**< AE min sensor digital gain */
	uint32_t AeShortMinIspDGain;                            /**< AE min isp digital gain */
	uint32_t AeShortMaxIntegrationTime;                     /**< AE max integration time */
	uint32_t AeShortMaxAGain;                               /**< AE max sensor analog gain */
	uint32_t AeShortMaxDgain;                               /**< AE max sensor digital gain */
	uint32_t AeShortMaxIspDGain;                            /**< AE max isp digital gain */

	uint32_t TotalGainDb;                                   /**< AE total gain, unit is dB */
	uint32_t TotalGainDbShort;                              /**< AE short frame total gain, unit is dB */
	uint32_t ExposureValue;                                 /**< AE exposure value(integration time x again x dgain) */
	uint32_t EVLog2;                                        /**< AE exposure value cal by log */
} IMPISPAEExprInfo;

/**
* @fn int32_t IMP_ISP_Tuning_SetAeExprInfo(IMPVI_NUM num, IMPISPAEExprInfo *exprinfo)
*
* set ae exposure attr
*
* @param[in]   num                 The sensor num label.
* @param[in]  exprinfo             ae exposure info.
*
* @retval 0 means success.
* @retval Other values mean failure, its value is an error code.
*
* @attention Before using it, make sure that 'IMP_ISP_EnableTuning' is working properly.
*/
int32_t IMP_ISP_Tuning_SetAeExprInfo(IMPVI_NUM num, IMPISPAEExprInfo *exprinfo);

/**
* @fn int32_t IMP_ISP_Tuning_GetAeExprInfo(IMPVI_NUM num, IMPISPAEExprInfo *exprinfo)
*
* set ae exposure attr
*
* @param[in]   num                 The sensor num label.
* @param[out]  exprinfo            ae exposure info.
*
* @retval 0 means success.
* @retval Other values mean failure, its value is an error code.
*
* @attention Before using it, make sure that 'IMP_ISP_EnableTuning' is working properly.
*/
int32_t IMP_ISP_Tuning_GetAeExprInfo(IMPVI_NUM num, IMPISPAEExprInfo *exprinfo);

/**
 * AE scence mode
 */
typedef enum {
	IMP_ISP_AE_SCENCE_AUTO,         /**< auto mode */
	IMP_ISP_AE_SCENCE_DISABLE,      /**< diable mode */
	TISP_AE_SCENCE_ROI_ENABLE,	/**< ROI enable mode */
	TISP_AE_SCENCE_GLOBAL_ENABLE,	/**< GLOBAL enable mode */
	IMP_ISP_AE_SCENCE_BUTT,         /**< effect paramater, parameters have to be less than this value */
} IMPISPAEScenceMode;

/**
 * AE scence mode attr
 */
typedef struct {
	IMPISPAEScenceMode AeHLCEn;         /**< AE high light depress enable */
	unsigned char AeHLCStrength;        /**< AE high light depress strength (0 ~ 10) */
	IMPISPAEScenceMode AeBLCEn;         /**< AE back light compensation */
	unsigned char AeBLCStrength;        /**< AE back light compensation strength (0 ~ 10) */
	IMPISPAEScenceMode AeTargetCompEn;  /**< AE luma target compensation enable */
	uint32_t AeTargetComp;              /**< AE luma target compensation strength（0 ~ 255）*/
	IMPISPAEScenceMode AeStartEn;       /**< AE start point enable */
	uint32_t AeStartEv;                 /**< AE start ev value */

	uint32_t luma;                      /**< AE luma value */
	uint32_t luma_scence;               /**< AE scence luma value */
        bool stable;                        /**< AE stable info, 1:stable  0:converging */
        uint32_t target;                    /**< Current AE target */
        uint32_t ae_mean;                   /**< Current Ae statistical weighted average value */
} IMPISPAEScenceAttr;

/**
* @fn int32_t IMP_ISP_Tuning_SetAeScenceAttr(IMPVI_NUM num, IMPISPAEScenceAttr *scenceattr)
*
* set ae scence mode attr
*
* @param[in]   num                     The sensor num label.
* @param[in]  scenceattr              ae scence attr.
*
* @retval 0 means success.
* @retval Other values mean failure, its value is an error code.
*
* @attention Before using it, make sure that 'IMP_ISP_EnableTuning' is working properly.
*/
int32_t IMP_ISP_Tuning_SetAeScenceAttr(IMPVI_NUM num, IMPISPAEScenceAttr *scenceattr);

/**
* @fn int32_t IMP_ISP_Tuning_GetAeScenceAttr(IMPVI_NUM num, IMPISPAEScenceAttr *scenceattr)
*
* get ae scence mode attr
*
* @param[in]   num                     The sensor num label.
* @param[out]  scenceattr              ae scence attr.
*
* @retval 0 means success.
* @retval Other values mean failure, its value is an error code.
*
* @attention Before using it, make sure that 'IMP_ISP_EnableTuning' is working properly.
*/
int32_t IMP_ISP_Tuning_GetAeScenceAttr(IMPVI_NUM num, IMPISPAEScenceAttr *scenceattr);

/**
 * AWB statistics info
 */
typedef struct {
	IMPISPStatisZone awb_r;     /**< AWB R channel statistics value */
	IMPISPStatisZone awb_g;     /**< AWB G channel statistics value */
	IMPISPStatisZone awb_b;     /**< AWB B channel statistics value */
} IMPISPAWBStatisInfo;

/**
* @fn int32_t IMP_ISP_Tuning_GetAwbStatistics(IMPVI_NUM num, IMPISPAWBStatisInfo *awb_statis)
*
* get awb statistics
*
* @param[in]   num                     The sensor num label.
* @param[out]  awb_statis              awb statistics.
*
* @retval 0 means success.
* @retval Other values mean failure, its value is an error code.
*
* @attention Before using it, make sure that 'IMP_ISP_EnableTuning' is working properly.
*/
int32_t IMP_ISP_Tuning_GetAwbStatistics(IMPVI_NUM num, IMPISPAWBStatisInfo *awb_statis);

/**
 * awb gain
 */
typedef struct {
	uint32_t rgain;	    /**< awb r-gain */
	uint32_t bgain;	    /**< awb b-gain */
} IMPISPAWBGain;

/**
 * AWB Global statistics
 */
typedef struct {
	IMPISPAWBGain statis_weight_gain;	/**< awb global weight gain */
	IMPISPAWBGain statis_gol_gain;		/**< awb global gain */
} IMPISPAWBGlobalStatisInfo;

/**
* @fn int32_t IMP_ISP_Tuning_GetAwbGlobalStatistics(IMPVI_NUM num, IMPISPAWBGlobalStatisInfo *awb_statis)
*
* get awb global statistics
*
* @param[in]   num                     The sensor num label.
* @param[out]  awb_statis              awb statistics.
*
* @retval 0 means success.
* @retval Other values mean failure, its value is an error code.
*
* @attention Before using it, make sure that 'IMP_ISP_EnableTuning' is working properly.
*/
int32_t IMP_ISP_Tuning_GetAwbGlobalStatistics(IMPVI_NUM num, IMPISPAWBGlobalStatisInfo *awb_statis);

/**
 * awb mode
 */
typedef enum {
	ISP_CORE_WB_MODE_AUTO = 0,			/**< auto mode */
	ISP_CORE_WB_MODE_MANUAL,			/**< manual mode */
	ISP_CORE_WB_MODE_DAY_LIGHT,			/**< day light mode */
	ISP_CORE_WB_MODE_CLOUDY,			/**< cloudy mode */
	ISP_CORE_WB_MODE_INCANDESCENT,                  /**< incandescent mode */
	ISP_CORE_WB_MODE_FLOURESCENT,                   /**< flourescent mode */
	ISP_CORE_WB_MODE_TWILIGHT,			/**< twilight mode */
	ISP_CORE_WB_MODE_SHADE,				/**< shade mode */
	ISP_CORE_WB_MODE_WARM_FLOURESCENT,              /**< warm flourescent mode */
	ISP_CORE_WB_MODE_COLORTEND,			/**< Color Trend Mode */
} IMPISPAWBMode;

/**
 * awb custom mode attribution
 */
typedef struct {
	IMPISPTuningOpsMode customEn;  /**< awb custom enable */
	IMPISPAWBGain gainH;           /**< awb gain on high ct */
	IMPISPAWBGain gainM;           /**< awb gain on medium ct */
	IMPISPAWBGain gainL;           /**< awb gain on low ct */
	uint32_t ct_node[4];           /**< awb custom mode nodes */
} IMPISPAWBCustomModeAttr;

/**
 * awb attribution
 */
typedef struct isp_core_wb_attr{
	IMPISPAWBMode mode;                     /**< awb mode */
	IMPISPAWBGain gain_val;			/**< awb gain on manual mode */
	IMPISPTuningOpsMode awb_frz;            /**< awb frz enable */
	unsigned int ct;                        /**< awb current ct value */
	IMPISPAWBCustomModeAttr custom;         /**< awb custom attribution */
	IMPISPTuningOpsMode awb_start_en;       /**< awb algo start function enable */
	IMPISPAWBGain awb_start;                /**< awb algo start point */
} IMPISPWBAttr;

/**
* @fn int32_t IMP_ISP_Tuning_SetAwbAttr(IMPVI_NUM num, IMPISPWBAttr *attr)
*
* set awb attribution
*
* @param[in]  num                     The sensor num label.
* @param[in]  attr                    awb attribution.
*
* @retval 0 means success.
* @retval Other values mean failure, its value is an error code.
*
* @attention Before using it, make sure that 'IMP_ISP_EnableTuning' is working properly.
*/
int32_t IMP_ISP_Tuning_SetAwbAttr(IMPVI_NUM num, IMPISPWBAttr *attr);

/**
* @fn int32_t IMP_ISP_Tuning_GetAwbAttr(IMPVI_NUM num, IMPISPWBAttr *attr)
*
* get awb attribution
*
* @param[in]   num                     The sensor num label.
* @param[out]  attr                    awb attribution.
*
* @retval 0 means success.
* @retval Other values mean failure, its value is an error code.
*
* @attention Before using it, make sure that 'IMP_ISP_EnableTuning' is working properly.
*/
int32_t IMP_ISP_Tuning_GetAwbAttr(IMPVI_NUM num, IMPISPWBAttr *attr);

/**
 * @fn int32_t IMP_ISP_Tuning_SetAwbWeight(IMPVI_NUM num, IMPISPWeight *awb_weight)
 *
 * set awb weight
 *
 * @param[in] num                     The sensor num label.
 * @param[in] awb_weight              awb weight.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using it, make sure that 'IMP_ISP_EnableTuning' is working properly.
 */
int32_t IMP_ISP_Tuning_SetAwbWeight(IMPVI_NUM num, IMPISPWeight *awb_weight);

/**
 * @fn int32_t IMP_ISP_Tuning_GetAwbWeight(IMPVI_NUM num, IMPISPWeight *awb_weight)
 *
 * get awb weight
 *
 * @param[in]    num                     The sensor num label.
 * @param[out]   awb_weight              awb weight.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using it, make sure that 'IMP_ISP_EnableTuning' is working properly.
 */
int32_t IMP_ISP_Tuning_GetAwbWeight(IMPVI_NUM num, IMPISPWeight *awb_weight);

/**
 * AF statistics info each area
 */
typedef struct {
	IMPISPStatisZone Af_Fir0;
	IMPISPStatisZone Af_Fir1;
	IMPISPStatisZone Af_Iir0;
	IMPISPStatisZone Af_Iir1;
	IMPISPStatisZone Af_YSum;				/* The brightness of the high point */
	IMPISPStatisZone Af_HighLumaCnt;		/* Number of high highlights */
} IMPISPAFStatisInfo;
/**
 * @fn int32_t IMP_ISP_Tuning_GetAfStatistics(IMPVI_NUM num, IMPISPAFStatisInfo *af_statis)
 *
 * get awb weight
 *
 * @param[in]    num                     The sensor num label.
 * @param[out]   af_statis               af statistics.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using it, make sure that 'IMP_ISP_EnableTuning' is working properly.
 */
int32_t IMP_ISP_Tuning_GetAfStatistics(IMPVI_NUM num, IMPISPAFStatisInfo *af_statis);

/**
 * AF metrics
 */
typedef struct {
	uint32_t af_metrics;        /**< AF Main metrics */
	uint32_t af_metrics_alt;    /**< AF second metrics */
	uint8_t af_frame_num;		/**< AF frame num */
	uint32_t af_wl;            /*Statistical value of the output of the low-pass filter*/
	uint32_t af_wh;            /*Statistical value of the high-pass filter output*/
} IMPISPAFMetricsInfo;

/**
 * @fn int32_t IMP_ISP_Tuning_GetAFMetricesInfo(IMPVI_NUM num, IMPISPAFMetricsInfo *metric)
 *
 * get af metrics
 *
 * @param[in]    num                        The sensor num label.
 * @param[out]   metric                     af metrics.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using it, make sure that 'IMP_ISP_EnableTuning' is working properly.
 */
int32_t IMP_ISP_Tuning_GetAFMetricesInfo(IMPVI_NUM num, IMPISPAFMetricsInfo *metric);

/**
 * @fn int32_t IMP_ISP_Tuning_SetAfWeight(IMPVI_NUM num, IMPISPWeight *af_weight)
 *
 * set zone weighting for AF
 *
 * @param[in] num           The sensor num label.
 * @param[in] af_weight     af weight
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using that function, make sure that ISP is working properly.
 */
int32_t IMP_ISP_Tuning_SetAfWeight(IMPVI_NUM num, IMPISPWeight *af_weight);
/**
 * @fn int32_t IMP_ISP_Tuning_GetAfWeight(IMPVI_NUM num, IMPISPWeight *af_weight)
 *
 * get zone weighting for AF
 *
 * @param[in] num            The sensor num label.
 * @param[out] af_weight     af weight
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using that function, make sure that ISP is working properly.
 */
int32_t IMP_ISP_Tuning_GetAfWeight(IMPVI_NUM num, IMPISPWeight *af_weight);

/**
 * ISP AutoZoom Attribution
 */
typedef struct {
	int32_t zoom_chx_en[3];     /**< auto zoom enable for each channel */
	int32_t zoom_left[3];       /**< the start pixel in horizen on zoom area */
	int32_t zoom_top[3];        /**< the start pixel in vertical on zoom are */
	int32_t zoom_width[3];      /**< zoom area width */
	int32_t zoom_height[3];     /**< zoom area height */
} IMPISPAutoZoom;

/**
 * @fn int32_t IMP_ISP_Tuning_SetAutoZoom(IMPVI_NUM num, IMPISPAutoZoom *ispautozoom)
 *
 * set auto zoom attribution
 *
 * @param[in] num               The sensor num label.
 * @param[in] ispautozoom       auto zoom attribution
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using that function, make sure that ISP is working properly.
 */
int32_t IMP_ISP_Tuning_SetAutoZoom(IMPVI_NUM num, IMPISPAutoZoom *ispautozoom);

/**
 * @fn int32_t IMP_ISP_Tuning_GetAutoZoom(IMPVI_NUM num, IMPISPAutoZoom *ispautozoom)
 *
 * set auto zoom attribution
 *
 * @param[in]  num               The sensor num label.
 * @param[out] ispautozoom       auto zoom attribution
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using that function, make sure that ISP is working properly.
 */
int32_t IMP_ISP_Tuning_GetAutoZoom(IMPVI_NUM num, IMPISPAutoZoom *ispautozoom);

/**
 * fill data type of Mask parameters
 */
typedef enum {
	IMPISP_MASK_TYPE_RGB = 0, /**< RGB type */
	IMPISP_MASK_TYPE_YUV = 1, /**< YUV type */
} IMPISP_MASK_TYPE;

/**
 * fill data value of Mask parameters
 */
typedef struct color_value {
	struct {
		unsigned char r_value;	/**< R offset of RGB type */
		unsigned char g_value;	/**< G offset of RGB type */
		unsigned char b_value;	/**< B offset of RGB type */
	} mask_argb;			/**< RGB type */
	struct {
		unsigned char y_value;	/**< Y offset of YUV type */
		unsigned char u_value;	/**< U offset of YUV type */
		unsigned char v_value;	/**< V offset of YUV type */
	} mask_ayuv;			/**< YUV type */
} IMP_ISP_COLOR_VALUE;

/**
 * Mask parameters of each channel
 */
typedef struct isp_mask_block_par {
	unsigned char mask_en;          /**< mask enable */
	unsigned short mask_pos_top;    /**< y of mask position */
	unsigned short mask_pos_left;   /**< x of mask position  */
	unsigned short mask_width;      /**< mask block width */
	unsigned short mask_height;     /**< mask block height */
	IMPISP_MASK_TYPE mask_type;		/**< mask type */
	IMP_ISP_COLOR_VALUE mask_value;  /**< mask value */
} IMPISP_MASK_BLOCK_PAR;

/**
 * Mask parameters
 */
typedef struct {
	IMPISP_MASK_BLOCK_PAR mask_chx[3][4];	/**< chan0 mask attr */
} IMPISPMASKAttr;

/**
 * @fn int32_t IMP_ISP_Tuning_SetMask(IMPVI_NUM num, IMPISPMASKAttr *mask)
 *
 * Set Mask Attr.
 *
 * @param[in] num       The sensor num label.
 * @param[in] mask      Mask attr.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using that function, make sure that ISP is working properly.
 */
int32_t IMP_ISP_Tuning_SetMask(IMPVI_NUM num, IMPISPMASKAttr *mask);

/**
 * @fn int32_t IMP_ISP_Tuning_GetMask(IMPVI_NUM num, IMPISPMASKAttr *mask)
 *
 * Get Mask Attr.
 *
 * @param[in]   num         The sensor num label.
 * @param[out]  mask        Mask attr.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using that function, make sure that ISP is working properly.
 */
int32_t IMP_ISP_Tuning_GetMask(IMPVI_NUM num, IMPISPMASKAttr *mask);

/**
 * OSD picture type
 */
typedef enum {
	IMP_ISP_OSD_PIC_FILE,	/**< picture file */
	IMP_ISP_OSD_PIC_ARRAY,	/**< picture array */
	IMP_ISP_OSD_PIC_BUTT,	/**< effect paramater, parameters have to be less than this value */
} IMPISPOSDPicType;

/**
 * OSD picture atribution
 */
typedef struct {
	uint8_t  osd_enable;           /**< osd enable */
	uint16_t osd_left;             /**< osd area x value */
	uint16_t osd_top;              /**< osd area y value */
	uint16_t osd_width;            /**< osd area width */
	uint16_t osd_height;           /**< osd area height */
	char *osd_image;			   /**< osd picture(file path/array) */
	IMPISPOSDPicType osd_image_type; /**< osd picture type */
	uint16_t osd_stride;           /**< osd stride, In bytes, for example, 320x240 RGBA8888 osd_stride=320*4. */
} IMPISPOSDPicAttr;

/**
 * OSD picture type
 */
typedef enum {
	IMP_ISP_PIC_ARGB_8888,  /**< ARGB8888 */
	IMP_ISP_PIC_ARGB_1555,  /**< ARBG1555 */
} IMPISPPICTYPE;

/**
 * OSD type
 */
typedef enum {
	IMP_ISP_ARGB_TYPE_BGRA = 0,
	IMP_ISP_ARGB_TYPE_GBRA,
	IMP_ISP_ARGB_TYPE_BRGA,
	IMP_ISP_ARGB_TYPE_RBGA,
	IMP_ISP_ARGB_TYPE_GRBA,
	IMP_ISP_ARGB_TYPE_RGBA,

	IMP_ISP_ARGB_TYPE_ABGR = 8,
	IMP_ISP_ARGB_TYPE_AGBR,
	IMP_ISP_ARGB_TYPE_ABRG,
	IMP_ISP_ARGB_TYPE_AGRB,
	IMP_ISP_ARGB_TYPE_ARBG,
	IMP_ISP_ARGB_TYPE_ARGB,
} IMPISPARGBType;

/**
 * OSD channel attribution
 */
typedef struct {
	IMPISPPICTYPE osd_type;                         /**< OSD picture type */
	IMPISPARGBType osd_argb_type;                   /**< OSD argb type */
	IMPISPTuningOpsMode osd_pixel_alpha_disable;    /**< OSD pixel alpha disable function enable */
	IMPISPOSDPicAttr pic[8];                        /**< OSD picture attribution */
} IMPISPOSDChxAttr;

/**
 * OSD attribution
 */
typedef struct {
	IMPISPOSDChxAttr osd_chx[2];       /**< OSD attribution for channel 0/1 */
} IMPISPOSDAttr;

typedef struct {
	int chx;
	int pic_num;
	IMPISPPICTYPE osd_type;                        /**< Fill image type */
	IMPISPARGBType osd_argb_type;                  /**< Fill format */
	IMPISPTuningOpsMode osd_pixel_alpha_disable;   /**< Fill Pixel Alpha disable function enabled */
	IMPISPOSDPicAttr pic;
} IMPISPSingleOSDAttr;

/**
 * @fn int32_t IMP_ISP_GetOSDAttr(IMPVI_NUM num, IMPISPOSDAttr *attr)
 *
 * Get osd Attr.
 *
 * @param[in]   num         The sensor num label.
 * @param[out]  attr        osd attr.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using that function, make sure that ISP is working properly.
 */
int32_t IMP_ISP_GetOSDAttr(IMPVI_NUM num, IMPISPOSDAttr *attr);

/**
 * @fn int32_t IMP_ISP_SetOSDAttr(IMPVI_NUM num, IMPISPOSDAttr *attr)
 *
 * Set osd Attr.
 *
 * @param[in]   num         The sensor num label.
 * @param[in]   attr        osd attr.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using that function, make sure that ISP is working properly.
 */
int32_t IMP_ISP_SetOSDAttr(IMPVI_NUM num, IMPISPOSDAttr *attr);

/**
 * Draw window attribution
 */
typedef struct {
	uint8_t  wind_enable;           /**< draw window enable */
	uint16_t wind_left;             /**< window start pixel in horizental */
	uint16_t wind_top;              /**< window start pixel in vertical */
	uint16_t wind_width;            /**< window width */
	uint16_t wind_height;           /**< window height */
	IMP_ISP_COLOR_VALUE wind_color; /**< window color */
	uint8_t  wind_line_width;           /**< window line width */
	uint8_t  wind_alpha;            /**< window alpha */
}IMPISPDrawWindAttr;

/**
 * Draw range attribution
 */
typedef struct {
	uint8_t  rang_enable;              /**< draw range enable */
	uint16_t rang_left;                /**< range start pixel in horizental */
	uint16_t rang_top;                 /**< range start pixel in vertical */
	uint16_t rang_width;               /**< range width */
	uint16_t rang_height;              /**< range height */
	IMP_ISP_COLOR_VALUE rang_color;    /**< range color */
	uint8_t  rang_line_width;          /**< range line width */
	uint8_t  rang_alpha;               /**< range alpha(3bit) */
	uint16_t rang_extend;              /**< range extend */
} IMPISPDrawRangAttr;

/**
 * Draw line attribution
 */
typedef struct {
	uint8_t  line_enable;           /**< draw line enable */
	uint16_t line_startx;           /**< line start pixel in horizental */
	uint16_t line_starty;           /**< line start pixel in vertical */
	uint16_t line_endx;             /**< line width */
	uint16_t line_endy;             /**< line height */
	IMP_ISP_COLOR_VALUE line_color; /**< line color */
	uint8_t  line_width;            /**< line line width */
	uint8_t  line_alpha;            /**< line alpha */
} IMPISPDrawLineAttr;

/**
 * Draw type
 */
typedef enum {
	IMP_ISP_DRAW_LINE,      /**< Draw line */
	IMP_ISP_DRAW_RANGE,     /**< Draw range */
	IMP_ISP_DRAW_WIND,      /**< Draw window */
} IMPISPDrawType;

/**
 * Draw unit Attribution
 */
typedef struct {
	IMPISPDrawType type;               /**< draw type */
	IMPISP_MASK_TYPE color_type;		/**< mask type */
	union {
		IMPISPDrawWindAttr wind;   /**< draw window attr */
		IMPISPDrawRangAttr rang;   /**< draw range attr */
		IMPISPDrawLineAttr line;   /**< draw line attr */
	} draw_cfg;                        /**< draw attr */
} IMPISPDrawUnitAttr;

/**
 * Draw Attribution for each channel
 */
typedef struct {
	IMPISPDrawUnitAttr draw_chx[2][16];   /**< draw attr for channel0, the max draw num is 16 */
} IMPISPDrawAttr;

/**
 * @fn int32_t IMP_ISP_GetDrawAttr(IMPVI_NUM num, IMPISPDrawAttr *attr)
 *
 * Get draw Attr.
 *
 * @param[in]   num         The sensor num label.
 * @param[out]  attr        draw attr.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using that function, make sure that ISP is working properly.
 */
int32_t IMP_ISP_GetDrawAttr(IMPVI_NUM num, IMPISPDrawAttr *attr);

/**
 * @fn int32_t IMP_ISP_SetDrawAttr(IMPVI_NUM num, IMPISPDrawAttr *attr)
 *
 * Set draw Attr.
 *
 * @param[in]   num         The sensor num label.
 * @param[in]   attr        draw attr.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using that function, make sure that ISP is working properly.
 */
int32_t IMP_ISP_SetDrawAttr(IMPVI_NUM num, IMPISPDrawAttr *attr);

/**
 * Face AE Attribution
 */
typedef struct {
	IMPISPTuningOpsMode enable; /**< Face AE enable */
	unsigned int left;   /**< Face AE left point of face area */
	unsigned int top;    /**< Face AE top point of face area */
	unsigned int right;  /**< Face AE right point of face area */
	unsigned int bottom; /**< Face AE bottom point of face area */
	unsigned int target; /**< Face AE target of face area */
} IMPISPFaceAttr;

/**
 * @fn int32_t IMP_ISP_Tuning_GetFaceAe(IMPVI_NUM num, IMPISPFaceAttr *gaeattr)
 *
 * Get face ae Attr.
 *
 * @param[in]   num         The sensor num label.
 * @param[out]  gaeattr     Face Ae attr.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using that function, make sure that ISP is working properly.
 */
int32_t IMP_ISP_Tuning_GetFaceAe(IMPVI_NUM num, IMPISPFaceAttr *gaeattr);

/**
 * @fn int32_t IMP_ISP_Tuning_SetFaceAe(IMPVI_NUM num, IMPISPFaceAttr *saeattr)
 *
 * Set face ae Attr.
 *
 * @param[in]   num         The sensor num label.
 * @param[in]   saeattr     Face AE attr.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using that function, make sure that ISP is working properly.
 */
int32_t IMP_ISP_Tuning_SetFaceAe(IMPVI_NUM num, IMPISPFaceAttr *saeattr);

/**
 * @fn int32_t IMP_ISP_Tuning_GetFaceAwb(IMPVI_NUM num, IMPISPFaceAttr *gawbattr)
 *
 * Get face ae Attr.
 *
 * @param[in]   num         The sensor num label.
 * @param[in]  gawbattr    Face Awb attr.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using that function, make sure that ISP is working properly.
 */
int32_t IMP_ISP_Tuning_GetFaceAwb(IMPVI_NUM num, IMPISPFaceAttr *gawbattr);

/**
 * @fn int32_t IMP_ISP_Tuning_SetFaceAwb(IMPVI_NUM num, IMPISPFaceAttr *sawbattr)
 *
 * Set face ae Attr.
 *
 * @param[in]   num         The sensor num label.
 * @param[in]   sawbattr    Face AWB attr.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using that function, make sure that ISP is working properly.
 */
int32_t IMP_ISP_Tuning_SetFaceAwb(IMPVI_NUM num, IMPISPFaceAttr *sawbattr);

/**
 * 3th custom AE library init Attribution
 */
typedef struct {
	IMPISPAEIntegrationTimeUnit AeIntegrationTimeUnit;  /**< AE integration time unit */
	/* Long frames in WDR mode or AE properties in linear mode*/
	uint32_t AeIntegrationTime;                         /**< AE integration time value */
	uint32_t AeAGain;				    /**< AE sensor analog gain value */
	uint32_t AeDGain;				    /**< AE sensor digital gain value */
	uint32_t AeIspDGain;				    /**< AE ISP digital gain value */

	uint32_t AeMinIntegrationTime;                      /**< AE min integration time */
	uint32_t AeMinAGain;				    /**< AE min sensor analog gain */
	uint32_t AeMinDgain;				    /**< AE min sensor digital gain */
	uint32_t AeMinIspDGain;				    /**< AE min isp digital gain */
	uint32_t AeMaxIntegrationTime;			    /**< AE max integration time */
	uint32_t AeMaxAGain;				    /**< AE max sensor analog gain */
	uint32_t AeMaxDgain;				    /**< AE max sensor digital gain */
	uint32_t AeMaxIspDGain;				    /**< AE max isp digital gain */

	/* AE Manual mode attr for short frame on WDR mode*/
	uint32_t AeShortIntegrationTime;                    /**< AE integration time value */
	uint32_t AeShortAGain;				    /**< AE sensor analog gain value */
	uint32_t AeShortDGain;				    /**< AE sensor digital gain value */
	uint32_t AeShortIspDGain;			    /**< AE ISP digital gain value */

	uint32_t AeShortMinIntegrationTime;                 /**< AE min integration time */
	uint32_t AeShortMinAGain;			    /**< AE min sensor analog gain */
	uint32_t AeShortMinDgain;			    /**< AE min sensor digital gain */
	uint32_t AeShortMinIspDGain;			    /**< AE min isp digital gain */
	uint32_t AeShortMaxIntegrationTime;		    /**< AE max integration time */
	uint32_t AeShortMaxAGain;			    /**< AE max sensor analog gain */
	uint32_t AeShortMaxDgain;			    /**< AE max sensor digital gain */
	uint32_t AeShortMaxIspDGain;			    /**< AE max isp digital gain */
	uint32_t fps;                                       /**< sensor fps 16/16 */
	IMPISPAEStatisAttr AeStatis;                        /**< Ae statis attrbution */
} IMPISPAeInitAttr;

/**
 * 3th custom AE library AE information
 */
typedef struct {
	IMPISPAEStatisInfo ae_info;                         /**< Ae statis information */
	IMPISPAEIntegrationTimeUnit AeIntegrationTimeUnit;  /**< AE integration time unit */
	uint32_t AeIntegrationTime;                         /**< AE integration time value */
	uint32_t AeAGain;				    /**< AE sensor analog gain value */
	uint32_t AeDGain;				    /**< AE sensor digital gain value */
	uint32_t AeIspDGain;				    /**< AE ISP digital gain value */
	uint32_t AeShortIntegrationTime;                    /**< AE integration time value */
	uint32_t AeShortAGain;				    /**< AE sensor analog gain value */
	uint32_t AeShortDGain;				    /**< AE sensor digital gain value */
	uint32_t AeShortIspDGain;			    /**< AE ISP digital gain value */

	uint32_t Wdr_mode;                                  /**< WDR mode or not */
	IMPISPSENSORAttr sensor_attr;                       /**< sensor attribution */
}  __attribute__((packed, aligned(1))) IMPISPAeInfo;

/**
 * 3th custom AE library AE attribution
 */
typedef struct {
	uint32_t change;                                    /**< change AE attr or not */
	IMPISPAEIntegrationTimeUnit AeIntegrationTimeUnit;  /**< AE integration time unit */
	uint32_t AeIntegrationTime;                         /**< AE integration time value */
	uint32_t AeAGain;				    /**< AE sensor analog gain value */
	uint32_t AeDGain;				    /**< AE sensor digital gain value */
	uint32_t AeIspDGain;				    /**< AE ISP digital gain value */

	/* AE Manual mode attr for short frame on WDR mode*/
	uint32_t AeShortIntegrationTime;                    /**< AE integration time value */
	uint32_t AeShortAGain;				    /**< AE sensor analog gain value */
	uint32_t AeShortDGain;				    /**< AE sensor digital gain value */
	uint32_t AeShortIspDGain;			    /**< AE ISP digital gain value */

	uint32_t luma;                                      /**< AE Luma value */
	uint32_t luma_scence;                               /**< AE scence Luma value */
} IMPISPAeAttr;

/**
 * 3th custom AE library AE notify attribution
 */
typedef enum {
	IMPISP_AE_NOTIFY_FPS_CHANGE,                        /* AE notify the fps change*/
} IMPISPAeNotify;

/**
 * AE callback function of custom auto exposure Library
 */
typedef struct {
	void *priv_data;								       	/* private data addr*/
	int (*open)(void *priv_data, IMPISPAeInitAttr *AeInitAttr);                              /* AE open function for 3th custom library*/
	void (*close)(void *priv_data);                                                         /* AE close function for 3th custom library*/
	void (*handle)(void *priv_data, const IMPISPAeInfo *AeInfo, IMPISPAeAttr *AeAttr);      /* AE handle function for 3th custom library*/
	int (*notify)(void *priv_data, IMPISPAeNotify notify, void *data);                      /* AE notify function for 3th custom library*/
} IMPISPAeAlgoFunc;

/**
 *@fn int32_t IMP_ISP_SetAeAlgoFunc(IMPVI_NUM num, IMPISPAeAlgoFunc *ae_func)
 *
 * User defined auto exposure library registration interface
 *
 * @param[in]  num         The sensor num label.
 * @param[in]  ae_func     the callback functions.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using that function, make sure that IMP_ISP_AddSensor have be called.
 */
int32_t IMP_ISP_SetAeAlgoFunc(IMPVI_NUM num, IMPISPAeAlgoFunc *ae_func);

/**
 * 3th custom AWB library AWB init information
 */
typedef struct {
	IMPISPAWBStatisAttr AwbStatis; /* awb statis attribution*/
} IMPISPAwbInitAttr;

/**
 * 3th custom AWB library AWB information
 */
typedef struct {
	uint32_t cur_r_gain;                   /* current awb r-gain*/
	uint32_t cur_b_gain;                   /* current awb b-gain*/
	uint32_t r_gain_statis;                /* current awb r-gain of global statis info*/
	uint32_t b_gain_statis;                /* current awb b-gain of global statis info*/
	uint32_t r_gain_wei_statis;            /* current awb r-gain of global weighted statis info*/
	uint32_t b_gain_wei_statis;            /* current awb b-gain of global weighted statis info*/
	IMPISPAWBStatisInfo awb_statis;        /* current awb statis info for each zone*/
}__attribute__((packed, aligned(1))) IMPISPAwbInfo;

/**
 * 3th custom AWB library AWB attribution
 */
typedef struct {
	uint32_t change;  /* change awb attribution or not*/
	uint32_t r_gain;  /* awb attribution of r-gain*/
	uint32_t b_gain;  /* awb attribution of b-gain*/
	uint32_t ct;      /* awb color temp*/
} IMPISPAwbAttr;

/**
 * 3th custom AWB library AWB notify attribution
 */
typedef enum {
	IMPISP_AWB_NOTIFY_MODE_CHANGE, 			/**< Current AWB mode change */
} IMPISPAwbNotify;

/**
 * 3th custom AWB library callback functions
 */
typedef struct {
	void *priv_data;                                                                                 /* private data addr*/
	int (*open)(void *priv_data, IMPISPAwbInitAttr *AwbInitAttr);					 /* AWB open function for 3th custom library*/
	void (*close)(void *priv_data);									 /* AWB close function for 3th custom library*/
	void (*handle)(void *priv_data, const IMPISPAwbInfo *AwbInfo, IMPISPAwbAttr *AwbAttr);		 /* AWB handle function for 3th custom library*/
	int (*notify)(void *priv_data, IMPISPAwbNotify notify, void *data);				 /* AWB notify function for 3th custom library*/
} IMPISPAwbAlgoFunc;

/**
 * @fn int32_t IMP_ISP_SetAwbAlgoFunc(IMPVI_NUM num, IMPISPAwbAlgoFunc *awb_func)
 *
 * the callback functions interface for 3th custom AWB library.
 *
 * @param[in]  num         The sensor num label.
 * @param[in]  awb_func    the callback functions.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using that function, make sure that IMP_ISP_AddSensor have be called.
 */
int32_t IMP_ISP_SetAwbAlgoFunc(IMPVI_NUM num, IMPISPAwbAlgoFunc *awb_func);

/**
 * Tuning bin file function properties.
 */
typedef struct {
	IMPISPTuningOpsMode enable;	 /**< Switch bin function switch */
	char bname[64];				 /**< The absolute path to the bin file */
} IMPISPBinAttr;

/**
 * @fn int32_t IMP_ISP_Tuning_SwitchBin(IMPVI_NUM num, IMPISPBinAttr *attr)
 *
 * Switch to bin file.
 *
 * @param[in] num      The label corresponding to the sensor.
 * @param[in] attr     The bin file properties to switch.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using that function, make sure that ISP is working properly.
 */
int32_t IMP_ISP_Tuning_SwitchBin(IMPVI_NUM num, IMPISPBinAttr *attr);

/**
 * WDR output mode.
 */
typedef enum {
        IMPISP_WDR_OUTPUT_MODE_FUS_FRAME,	/**< Mixture mode */
        IMPISP_WDR_OUTPUT_MODE_LONG_FRAME,	/**< Long frame mode */
        IMPISP_WDR_OUTPUT_MODE_SHORT_FRAME,	/**< Short frame mode */
        IMPISP_WDR_OUTPUT_MODE_BUTT,		/**< effect paramater, parameters have to be less than this value */
} IMPISPWdrOutputMode;

/**
 * @fn int32_t IMP_ISP_Tuning_SetWdrOutputMode(IMPVI_NUM num, IMPISPWdrOutputMode *mode)
 *
 * Set the WDR image output mode.
 *
 * @param[in] num	The label corresponding to the sensor.
 * @param[in] mode	output mode.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using it, make sure that 'IMP_ISP_EnableTuning' is working properly.
 */
int32_t IMP_ISP_Tuning_SetWdrOutputMode(IMPVI_NUM num, IMPISPWdrOutputMode *mode);

/**
 * @fn int32_t IMP_ISP_Tuning_GetWdrOutputMode(IMPVI_NUM num, IMPISPWdrOutputMode *mode)
 *
 * Get the WDR image output mode.
 *
 * @param[in] num	The label corresponding to the sensor.
 * @param[out] mode	output mode.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using it, make sure that 'IMP_ISP_EnableTuning' is working properly.
 */
int32_t IMP_ISP_Tuning_GetWdrOutputMode(IMPVI_NUM num, IMPISPWdrOutputMode *mode);

/**
 * frame drop parameter.
 */
typedef struct {
	IMPISPTuningOpsMode enable;	/**< enbale mark */
        uint8_t lsize;			/**< sum (range:0~31) */
        uint32_t fmark;			/**< bit mark(1 output,0 drop) */
} IMPISPFrameDrop;

/**
 * frame drop attr.
 */
typedef struct {
	IMPISPFrameDrop fdrop[3];	/**< frame drop parameters for each channel */
} IMPISPFrameDropAttr;

/**
 * @fn int32_t IMP_ISP_SetFrameDrop(IMPVI_NUM num, IMPISPFrameDropAttr *attr)
 *
 * Set frame drop attr.
 *
 * @param[in] num	The label corresponding to the sensor.
 * @param[in] attr	Frame drop attr.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @remark Every time (lsize+1) is accepted, (fmark invalid figure) is lost.
 * @remark Example:lsize=3,fmark=0x5(Frames 2 and 4 are lost every 4).
 *
 * @attention Before using it, make sure that 'IMP_ISP_Open' is working properly.
 */
int32_t IMP_ISP_SetFrameDrop(IMPVI_NUM num, IMPISPFrameDropAttr *attr);

/**
 * @fn int32_t IMP_ISP_GetFrameDrop(IMPVI_NUM num, IMPISPFrameDropAttr *attr)
 *
 * Get frame drop attr.
 *
 * @param[in] num	The label corresponding to the sensor.
 * @param[out] attr	Frame drop attr.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @remark Every time (lsize+1) is accepted, (fmark invalid figure) is lost.
 * @remark Example:lsize=3,fmark=0x5(Frames 2 and 4 are lost every 4).
 *
 * @attention Before using it, make sure that 'IMP_ISP_Open' is working properly.
 */
int32_t IMP_ISP_GetFrameDrop(IMPVI_NUM num, IMPISPFrameDropAttr *attr);

/**
 * Scaler mode
 */
typedef enum {
        IMPISP_SCALER_FITTING_CRUVE,
        IMPISP_SCALER_FIXED_WEIGHT,
        IMPISP_SCALER_BUTT,
} IMPISPScalerMode;

/**
 * Scaler effect params
 */
typedef struct {
        uint8_t chx;		/*channel 0~2*/
        IMPISPScalerMode mode;	/*scaler method*/
        uint8_t level;		/*scaler level range 0~128*/
} IMPISPScalerLvAttr;

/**
 * @fn IMP_ISP_SetScalerLv(IMPVI_NUM num, IMPISPScalerLvAttr *attr)
 *
 * Set Scaler method and level.
 *
 * @param[in] num  The label corresponding to the sensor.
 * @param[in] mscaler opt.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using it, make sure that 'IMP_ISP_EnableTuning' is working properly.
 */
int32_t IMP_ISP_SetScalerLv(IMPVI_NUM num, IMPISPScalerLvAttr *attr);

/**
 * @fn IMP_ISP_StartNightMode(IMPVI_NUM num)
 *
 * Start night mode.
 *
 * @param[in] num  The label corresponding to the sensor.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Using range: After IMP_ISP_Open, IMP_ISP_AddSensor before.
 */
int32_t IMP_ISP_StartNightMode(IMPVI_NUM num);

/**
 * @fn int32_t IMP_ISP_GetSingleOSDAttr(IMPVI_NUM num, IMPISPSingleOSDAttr *attr)
 *
 * Set the fill parameters.
 *
 * @param[in] num   The label corresponding to the sensor.
 * @param[in] attr  Frame drop attr.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using it, make sure that 'IMP_ISP_EnableTuning' is working properly.
 */
int32_t IMP_ISP_GetSingleOSDAttr(IMPVI_NUM num, IMPISPSingleOSDAttr *attr);

/**
 * @fn int32_t IMP_ISP_SetSingleOSDAttr(IMPVI_NUM num, IMPISPSingleOSDAttr *attr)
 *
 * Set the fill parameters.
 *
 * @param[in] num   The label corresponding to the sensor.
 * @param[in] attr  Frame drop attr.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using it, make sure that 'IMP_ISP_EnableTuning' is working properly.
 */
int32_t IMP_ISP_SetSingleOSDAttr(IMPVI_NUM num, IMPISPSingleOSDAttr *attr);

/**
 * raw attribute and buffer attribute。
 */
typedef  struct {
	uint32_t paddr;		/*  buffer paddr */
	uint32_t vaddr;		/*  buffer vaddr */
	uint32_t buf_size;	/*  buffer size */
}IMPISPRAWBUF;

typedef struct {
	IMPISPRAWBUF buf;			/* buf properties */
	uint32_t raw_width;         /* sensor width */
	uint32_t raw_height;        /* sensor height */
	uint8_t raw_bit;            /* The input parameters can only be 8,16 */ /* 8:get 8bit raw，16:get 16bit raw */
	unsigned short sensor_id;   /* Camera ID */
} IMPISPGETRawiConfig;

/**
 * @fn IMP_ISP_GetRaw(IMPVI_NUM num, IMPISPGETRawiConfig *attr)
 *
 * The application layer obtains the Raw image.
 *
 * @param[in] num       The sensor num label.
 * @param[in] attr      raw attr.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using it, make sure that 'IMP_ISP_Open' is working properly.
 */
int32_t IMP_ISP_GetRaw(IMPVI_NUM num, IMPISPGETRawiConfig *attr);

/**
 * @fn IMP_ISP_SetPreDqtime(IMPVI_NUM num, uint32_t *dqtime)
 *
 * Set the triggering delay of soft interrupt in single frame scheduling.
 *
 * @param[in] num       The sensor num label.
 * @param[in] attr      raw attr.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @remark The num parameter does not need to be set
 * @remark because the interface does not differentiate between primary and secondary data.
 *
 * @attention Before using it, make sure that 'IMP_ISP_Open' is working properly.
 */
int32_t IMP_ISP_SetPreDqtime(IMPVI_NUM num, uint32_t *dqtime);

typedef struct {
        int16_t strength;     	/**< Distortion correction intensity [range: 0 to 255, default: 128]*/
        int16_t width;          /**< Image width */
        int16_t height;         /**< Image height */
        int16_t center_w;       /**< Image distortion horizontal optical center range:[width/2-120, width/2+120] */
        int16_t center_h;       /**< Image distortion vertical optical center range:[height/2-120, height/2+120] */
} IMPISPHLDCAttr;

/**
 * @fn int32_t IMP_ISP_Tuning_SetISPHLDCAttr(IMPVI_NUM num, IMPISPHLDCAttr *hldc)
 *
 * Set the HLDC properties.
 *
 * @param[in] num       The sensor num label.
 * @param[in] hldc      hldc attr.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using that function, make sure that ISP is working properly.
 *
 *1. If the resolution is greater than 1080p, the input value needs to be set before opening the HLDC module
 *2. The HLDC is disabled by default in the effect bin file (ps: IMP_ISP_Tuning_GetModuleControl is called in this case, and the return value is 1,1 means bypass is enabled, corresponding to HLDC is disabled)
 *3. please directly IMP_ISP_Tuning_GetHLDCAttr (image width and height is 1920*1080 default value), SET (three values: intensity, optical center), GET (at this time, the width and height of the image obtained is your current real resolution)
 *4. the smaller the intensity, the wider the image is pulled, the greater the intensity, the narrower the image is relatively pulled; 128 is the default intensity. Do not set 128 for the first time after starting the machine. You can first set other values and then set 128 (128 means no distortion correction, and you can choose to turn off HLDC, the effect is the same).
 */
int32_t IMP_ISP_Tuning_SetHLDCAttr(IMPVI_NUM num, IMPISPHLDCAttr *hldc);

/**
 * @fn int32_t IMP_ISP_Tuning_GetISPHLDCAttr(IMPVI_NUM num, IMPISPHLDCAttr *hldc)
 *
 * Get the HLDC attr.
 *
 * @param[in] num       The sensor num label.
 * @param[out] hldc      hldc attr.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using that function, make sure that ISP is working properly.
 */
int32_t IMP_ISP_Tuning_GetHLDCAttr(IMPVI_NUM num, IMPISPHLDCAttr *hldc);

/**
 * Mjpeg fixed contrast
 */
typedef struct {
	uint8_t mode;         /* When set to 1, the parameter takes effect. If the parameter is 0, does not take effect*/
	uint8_t range_low;    /* Can be set to 16, increase the contrast effect, can increase this value */
	uint8_t range_high;   /* Can be set to 235*/
} IMPISPFixedContrastAttr;

/**
 * @fn int32_t IMP_ISP_Tuning_SetFixedContraster(IMPISPFixedContrastAttr *attr)
 *
 * mjpeg sets fixed contrast.
 *
 * @param[out] attr attribute.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using it, make sure that 'IMP_ISP_EnableTuning' is working properly.
 */
int32_t IMP_ISP_Tuning_SetFixedContraster(IMPVI_NUM num, IMPISPFixedContrastAttr *attr);

/**
 * ISP Bypass attr
 */
typedef struct {
	uint8_t enable;			/**< bypass enable */
	uint8_t vc_index;		/**< mipi virtual channel selection(0/1/2/3) */
	uint8_t dma_index;		/**< dma channel selection(0/1) */
} IMPISPBypass;

/**
 * ISP Bypass attr set
 */
typedef struct {
	IMPISPBypass bypass[3];	/**< The bypass attribute of each channel */
} IMPISPBypassAttr;

/**
 * @fn int32_t IMP_ISP_Bypass_Bind(IMPVI_NUM num, IMPISPBypassAttr *attr)
 *
 * Example Set the binding relationship of ISP Bypass.
 *
 * @param[in] num       The sensor num label.
 * @param[in] attr		bypass attr
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @remark Dma should preferentially use channel 0.
 * @remark When the third camera is used, only channel 0 can be used.
 *
 * @attention Before using it, make sure that 'IMP_ISP_Open' is working properly.
 * @attention This function and IMP_ISP_Tuning_SetISPBypass cannot be used together.
 */
int32_t IMP_ISP_Bypass_Bind(IMPVI_NUM num, IMPISPBypassAttr *attr);

#define MAXISPCHNMUN 6	/*ISP supports 6 channels; But ISPOSD only supports 4 channels, namely: main camera chn0 and chn1, secondary camera chn3 and chn4*/
#define MAXISPOSDPIC 8	/*The max pic chn num*/

typedef enum {
	IMP_ISP_OSD_RGN_FREE,	/*The region is free or not create*/
	IMP_ISP_OSD_RGN_BUSY,	/*The region has been created*/
}IMPIspOsdRngStat;

typedef enum {
	ISP_OSD_REG_INV		  = 0, /**< Invalid */
	ISP_OSD_REG_PIC 	  = 1, /**< The type of pic*/
}IMPISPOSDType;
typedef struct IMPISPOSDNode IMPISPOSDNode;

/*ISPOSD Attribute set*/
typedef struct {
	IMPISPOSDType type;
	union {
		IMPISPSingleOSDAttr stsinglepicAttr;/* ISPOSD of the pic type*/
	};
}IMPIspOsdAttrAsm;

/**
 * @fn int IMP_ISP_Tuning_SetOsdPoolSize(int size)
 *
 * create ISPOSD's rmem size
 *
 * @param[in]
 *
 * @retval 0 success
 * @retval no-0 failure
 *
 * @remarks none
 *
 * @attention none
 */
int IMP_ISP_Tuning_SetOsdPoolSize(int size);

/**
 * @fn int IMP_ISP_Tuning_CreateOsdRgn(int chn,IMPIspOsdAttrAsm *pIspOsdAttr)
 *
 * Create ISPOSD's region
 *
 * @param[in] chn num，IMPIspOsdAttrAsm Structure pointer
 *
 * @retval 0 success
 * @retval no-0 failure
 *
 * @remarks none
 *
 * @attention none
 */
int IMP_ISP_Tuning_CreateOsdRgn(int chn,IMPIspOsdAttrAsm *pIspOsdAttr);

/**
 * @fn int IMP_ISP_Tuning_SetOsdRgnAttr(int chn,int handle, IMPIspOsdAttrAsm *pIspOsdAttr)
 *
 * set ISPOSDattr
 *
 * @param[in] chn num，handle num IMPIspOsdAttrAsm Structure pointer
 *
 * @retval 0 success
 * @retval no-0 failure
 *
 * @remarks none
 *
 * @attention none
 */
int IMP_ISP_Tuning_SetOsdRgnAttr(int chn,int handle, IMPIspOsdAttrAsm *pIspOsdAttr);

/**
 * @fn int IMP_ISP_Tuning_GetOsdRgnAttr(int chn,int handle, IMPIspOsdAttrAsm *pIspOsdAttr)
 *
 * Get ISPOSD's IMPIspOsdAttrAsm from chn's handle
 *
 * @param[in] chn num, handle num,IMPOSDRgnCreateStat Structure pointer
 *
 * @retval 0 success
 * @retval no-0 failure
 *
 * @remarks none
 *
 * @attention none
 */
int IMP_ISP_Tuning_GetOsdRgnAttr(int chn,int handle, IMPIspOsdAttrAsm *pIspOsdAttr);

/**
 * @fn int IMP_ISP_Tuning_ShowOsdRgn( int chn,int handle, int showFlag)
 *
 * Set ISPOSD's chn's handle show flag status
 *
 * @param[in] chn num，handlenum，showFlag'status(0:close，1:open)
 *
 * @retval 0 success
 * @retval no-0 failure
 *
 * @remarks none
 *
 * @attention none
 */
int IMP_ISP_Tuning_ShowOsdRgn(int chn,int handle, int showFlag);

/**
 * @fn int IMP_ISP_Tuning_DestroyOsdRgn(int chn,int handle)
 *
 * destroy the region of channel
 *
 * @param[in] chn num，handle num
 *
 * @retval 0 success
 * @retval no-0 failure
 *
 * @remarks none
 *
 * @attention none
 */
int IMP_ISP_Tuning_DestroyOsdRgn(int chn,int handle);

/**
 * WDR initialization mode.
 */
typedef enum {
	IMPISP_TYPE_WDR_FS = 1,
	IMPISP_TYPE_WDR_DOL,
	IMPISP_TYPE_WDR_NATIVE,
} IMPISPWdrInitMode;

/**
 * WDR initial operating mode.
 */
typedef enum {
	IMPISP_TYPE_RUN_LINEAR,
	IMPISP_TYPE_RUN_WDR,
} IMPISPWdrRunMode;

/**
 * WDR mode enable properties.
 */
typedef struct {
	IMPISPWdrRunMode rmode;
	IMPISPWdrInitMode imode;
} IMPISPWdrOpenAttr;

/**
 * @fn int32_t IMP_ISP_WDR_OPEN(IMPVI_NUM num, IMPISPWdrOpenAttr *attr)
 *
 * Open the WDR.
 *
 * @param[in] num       The sensor num label.
 * @param[in] attr      WDR attr.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @remark Imode is used to configure the WDR mode, and rmode is used to select the boot mode.
 *
 * @attention Have to call this function before IMP_ISP_AddSensor for the first time.
 * @attention When starting in Linear mode, you need to configure the wdr_cache attribute under the Linear branch of the sensor driver check function.
 */
int32_t IMP_ISP_WDR_OPEN(IMPVI_NUM num, IMPISPWdrOpenAttr *attr);

/**
 * AE exposure meter properties
 */
typedef struct {
	IMPISPTuningOpsMode mode;
	uint32_t elist[16][5];    /**< Column order description: reserved | exposure time (us) | again | dgain | Reserved */
} IMPISPAeExpListAttr;

/**
 * @fn int32_t IMP_ISP_Tuning_SetAeExpList(IMPVI_NUM num, IMPISPAeExpListAttr *attr)
 *
 * Set the AE exposure meter
 *
 * @param[in] num    The sensor num label.
 * @param[in] attr   attr
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using it, make sure that 'IMP_ISP_EnableTuning' is working properly.
 */
int32_t IMP_ISP_Tuning_SetAeExpList(IMPVI_NUM num, IMPISPAeExpListAttr *attr);

/**
 * @fn int32_t IMP_ISP_Tuning_GetAeExpList(IMPVI_NUM num, IMPISPAeExpListAttr *attr)
 *
 * Obtain the AE exposure sheet
 *
 * @param[in] num   The sensor num label.
 * @param[out] attr    attr
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using it, make sure that 'IMP_ISP_EnableTuning' is working properly.
 */
int32_t IMP_ISP_Tuning_GetAeExpList(IMPVI_NUM num, IMPISPAeExpListAttr *attr);

typedef struct {
        uint16_t step_s;    //Convergence speed from light to dark
        uint16_t step_d;    //Dark-to-light convergence speed
} IMPISPAeSpeedAttr;

/**
 * @fn int32_t IMP_ISP_Tuning_GetAeSpeed(IMPVI_NUM num, IMPISPAeSpeedAttr *attr);
 *
 * Obtain the convergence speed of the AE
 *
 * @param[in] num   The sensor num label.
 * @param[out] attr    attr
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using it, make sure that 'IMP_ISP_EnableTuning' is working properly.
 */
int32_t IMP_ISP_Tuning_GetAeSpeed(IMPVI_NUM num, IMPISPAeSpeedAttr *attr);

/**
 * @fn int32_t IMP_ISP_Tuning_SetAeSpeed(IMPVI_NUM num, IMPISPAeSpeedAttr *attr);
 *
 * Set the convergence speed of the AE
 *
 * @param[in] num   The sensor num label.
 * @param[out] attr    attr
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using it, make sure that 'IMP_ISP_EnableTuning' is working properly.
 */
int32_t IMP_ISP_Tuning_SetAeSpeed(IMPVI_NUM num, IMPISPAeSpeedAttr *attr);

/**
 * ISP WB COEFFT parameter structure.
 */
typedef struct isp_core_rgb_coefft_wb_attr {
		unsigned short rgb_coefft_wb_r;
		unsigned short rgb_coefft_wb_g;
		unsigned short rgb_coefft_wb_b;
}IMPISPCoefftWb;

/**
 * @fn IMP_ISP_Tuning_Awb_GetRgbCoefft(IMPVI_NUM num, IMPISPCoefftWb *isp_core_rgb_coefft_wb_attr)
 *
 * Obtain the AWB RGB channel offset parameter manually.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using this function, IMP_ISP_EnableTuning has been called.
 */
int IMP_ISP_Tuning_Awb_GetRgbCoefft(IMPVI_NUM num, IMPISPCoefftWb *isp_core_rgb_coefft_wb_attr);

/**
 * @fn IMP_ISP_Tuning_Awb_SetRgbCoefft(IMPVI_NUM num, IMPISPCoefftWb *isp_core_rgb_coefft_wb_attr)
 *
 * Set the AWB RGB channel offset parameter manually.
 *
 * @retval 0 means success.
 * @retval Other values mean failure, its value is an error code.
 *
 * @attention Before using this function, IMP_ISP_EnableTuning has been called.
 *
 * example：
 * @code
 * IMPISPCoefftWb isp_core_rgb_coefft_wb_attr;
 *
 *isp_core_rgb_coefft_wb_attr.rgb_coefft_wb_r=x;
 *isp_core_rgb_coefft_wb_attr.rgb_coefft_wb_g=y;
 *isp_core_rgb_coefft_wb_attr.rgb_coefft_wb_b=z;
 *IMP_ISP_Tuning_Awb_SetRgbCoefft(&isp_core_rgb_coefft_wb_attr);
 if(ret){
 IMP_LOG_ERR(TAG, "IMP_ISP_Tuning_Awb_SetRgbCoefft error !\n");
 return -1;
 }
 * @endcode
 *
*/
int IMP_ISP_Tuning_Awb_SetRgbCoefft(IMPVI_NUM num, IMPISPCoefftWb *isp_core_rgb_coefft_wb_attr);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

/**
 * @}
 */

#endif /* __IMP_ISP_H__ */
