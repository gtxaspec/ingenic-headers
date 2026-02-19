/*
 * System utils header file.
 *
 * Copyright (C) 2014 Ingenic Semiconductor Co.,Ltd
 */

#ifndef __SU_BASE_H__
#define __SU_BASE_H__

#include <stdint.h>

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

/**
 * @file
 * Sysutils Basic Function Header File
 */

/**
 * @defgroup sysutils System Utils
 */

/**
 * @defgroup Sysutils_Base
 * @ingroup sysutils
 * @brief Basic system functionality.
 * @{
 */

/**
 * Device ID logical encoding
 */
#define DEVICE_ID_MAGIC     "53ef"

/**
 * Length of device ID logical encoding
 */
#define DEVICE_ID_MAGIC_LEN 4

/**
 * Length of device ID
 */
#define DEVICE_ID_LEN       32

/**
 * Maximum length of device model, device ID, and firmware version information
 */
#define MAX_INFO_LEN        64

/**
 * Device model number.
 */
typedef struct {
	char chr[MAX_INFO_LEN];     /**< Device model number string */
} SUModelNum;

/**
 * Device software version.
 */
typedef struct {
	char chr[MAX_INFO_LEN];     /**< Device software version string */
} SUVersion;

/**
 * Device ID. The device ID is a unique value, and it may vary between different CPU chips.
 */
typedef union {
	char chr[MAX_INFO_LEN];     /**< Device ID string */
	uint8_t hex[MAX_INFO_LEN];  /**< Device ID in binary */
} SUDevID;

/**
 * System time structure.
 */
typedef struct {
	int sec;	/**< Second,Range：0~59 */
	int min;	/**< Minute,Range：0~59 */
	int hour;	/**< Hour,Range：0~23 */
	int mday;	/**< Day,Range：1~31 */
	int mon;	/**< Month,Range：1~12 */
	int year;	/**< Year,Range：>1900 */
} SUTime;

typedef enum {
	WKUP_ALARM = 1,         /*Timed wake-up*/
	WKUP_KEY,               /*Key wake-up*/
	WKUP_MAX,               /*Maximum*/
}SUWkup;

typedef enum {
	PM_DISABLE_PAUSE = 0,   /*Thread sleep interface disabled*/
	PM_ENABLE_PAUSE,        /*Thread sleep interface enabled*/
	PM_IS_INVAL,
}eSUPM_EVENT_MODE;

typedef enum {
	PM_EVENT_SYNC,          /*Synchronous mode*/
	PM_EVENT_ASYNC,         /*Asynchronous mode*/
	PM_EVENT_INVAL,
}eSUPM_EVENT_TYPE;

typedef enum {
	PM_API_ENABLE = 0,      /*Enable PM related interfaces*/
	PM_API_DISABLE,     	/*Disable PM related interfaces*/
	PM_API_INVAL,           /*Invalid*/
}eSUPM_API_SET;

typedef struct SUPM_Init_Cfg{
	union{
		unsigned int cfg;
		struct {
			char pm_api_init        :2;/*<eSUPM_API_SET*/
			char event_mode_init    :2;/*<eSUPM_EVENT_MODE*/
			char event_type_init    :2;/*<eSUPM_EVENT_TYPE*/
		};
	}init;
}SUPM_Init_Cfg_t;

/**
 * @fn int SU_Base_GetModelNumber(SUModelNum *modelNum)
 *
 * @brief: Get the device model number.
 *
 * @param[out]: modelNum Pointer to the device model number structure.
 *
 * @retval: 0 Success. Non-zero Failure.
 *
 * @remarks: None
 *
 * @attention: None.
 */
int SU_Base_GetModelNumber(SUModelNum *modelNum);

/**
 * @fn int SU_Base_GetVersion(SUVersion *version)
 *
 * @brief: Get the device version.
 *
 * @param[out]: version Pointer to the device version structure.
 *
 * @retval: 0 Success. Non-zero Failure.
 *
 * @remarks: None.
 *
 * @attention: None.
 */
int SU_Base_GetVersion(SUVersion *version);

/**
 * @fn int SU_Base_GetDevID(SUDevID *devID)
 *
 * @brief: Get the device ID.
 *
 * @param[out] devID Pointer to the device ID structure.
 *
 * @retval: 0 Success. Non-zero Failure.
 *
 * @remarks: None.
 *
 * @attention: The device ID is unique for each CPU chip.
 */
int SU_Base_GetDevID(SUDevID *devID);

/**
 * @fn: int SU_Base_GetTime(SUTime *time)
 *
 * @brief: Get the system time.
 *
 * @param[in] time Pointer to the system time structure.
 *
 * @retval: 0 Success. Non-zero Failure.
 *
 * @remarks: None.
 *
 * @attention: None.
 */
int SU_Base_GetTime(SUTime *time);

/**
 * @fn: int SU_Base_SetTime(SUTime *time)
 *
 * @brief: Set the system time.
 *
 * @param[out] time Pointer to the system time structure.
 *
 * @retval: 0 Success. Non-zero Failure.
 *
 * @remarks: None.
 *
 * @attention: The system time parameters must be within a reasonable range, or the function call will fail.
 */
int SU_Base_SetTime(SUTime *time);

/**
 * @fn: int SU_Base_SUTime2Raw(SUTime *suTime, uint32_t *rawTime)
 *
 * @brief: Convert SUTime type time to Raw time in seconds.
 *
 * @param[in] suTime Pointer to the system time structure.
 * @param[out] rawTime Raw time (measured from 1970-01-01 00:00:00).
 *
 * @retval: 0 Success. Non-zero Failure.
 *
 * @remarks: This function can be used to set relative seconds for alarms.
 *
 * @attention: None.
 */
int SU_Base_SUTime2Raw(SUTime *suTime, uint32_t *rawTime);

/**
 * @fn: int SU_Base_Raw2SUTime(uint32_t *rawTime, SUTime *suTime)
 *
 * @brief: Convert Raw time in seconds to SUTime type time.
 *
 * @param[in] rawTime Raw time (measured from 1970-01-01 00:00:00).
 * @param[out] suTime Pointer to the system time structure.
 *
 * @retval 0 Success. Non-zero Failure.
 *
 * @remarks: This function can be used to set relative seconds for alarms.
 *
 * @attention: None.
 */
int SU_Base_Raw2SUTime(uint32_t *rawTime, SUTime *suTime);

/**
 * @fn: int SU_Base_SetAlarm(SUTime *time)
 *
 * @brief: Set the alarm time.
 *
 * @param[in] time Pointer to the system time structure.
 *
 * @retval: 0 Success. Non-zero Failure.
 *
 * @remarks: Supports setting alarms within 24 hours.
 *
 * @attention: The system time parameters must be within a reasonable range, or the function call will fail.
 */
int SU_Base_SetAlarm(SUTime *time);

/**
 * @fn: int SU_Base_GetAlarm(SUTime *time)
 *
 * @brief: Get the alarm timing.
 *
 * @param[out] time Pointer to the system time structure.
 *
 * @retval: 0 Success. Non-zero Failure.
 *
 * @remarks: None.
 *
 * @attention: None.
 */
int SU_Base_GetAlarm(SUTime *time);

/**
 * @fn: int SU_Base_EnableAlarm()
 *
 * @brief: Enable the alarm.
 *
 * @param: None.
 *
 * @retval: 0 Success. Non-zero Failure.
 *
 * @remarks: None.
 *
 * @attention: Before calling this function, please call SU_Base_GetAlarm(SUTime *time) to set the alarm time.
 * If the alarm time is earlier than the current system time, the function will fail.
 */
int SU_Base_EnableAlarm(void);

/**
 * @fn: int SU_Base_DisableAlarm()
 *
 * @brief: Disable the alarm.
 *
 * @param: None.
 *
 * @retval: 0 Success. Non-zero Failure.
 *
 * @remarks: None.
 *
 * @attention: None.
 */
int SU_Base_DisableAlarm(void);

/**
 * @fn: int SU_Base_PollingAlarm(uint32_t timeoutMsec)
 *
 * @brief: Wait for the alarm.
 *
 * @param[in] timeoutMsec Timeout period in milliseconds.
 *
 * @retval: 0 Success. Non-zero Failure.
 *
 * @remarks: After calling this function, the program will enter a blocking state until the alarm is triggered or a timeout occurs.
 *
 * @attention: None.
 */
int SU_Base_PollingAlarm(uint32_t timeoutMsec);

/**
 * @fn: int SU_Base_Shutdown(void)
 *
 * @brief: Shutdown the device.
 *
 * @param: None.
 *
 * @retval: 0 Success. Non-zero Failure.
 *
 * @remarks: After calling this function, the device will immediately shut down and turn off the main power source.
 *
 * @attention: Make sure to save all files before calling this function.
 **/
int SU_Base_Shutdown(void);

/**
 * @fn: int SU_Base_Reboot(void)
 *
 * @brief: Reboot the device.
 *
 * @param: None.
 *
 * @retval: 0 Success. Non-zero Failure.
 *
 * @remarks: None.
 *
 * @attention: After calling this function, the device will immediately reboot. Make sure to save all files before calling this function.
 **/
int SU_Base_Reboot(void);

/**
 * @fn: int SU_Base_Suspend()
 *
 * @brief: Put the device to sleep immediately. The function will return when the system wakes up.
 *
 * @param: None.
 *
 * @retval: 0 Success. Non-zero Failure.
 *
 * @remarks: None.
 *
 * @attention: Note that to protect the safety of the suspend operation, a wake lock/unlock mechanism has been added.
 * So, calling SU_Base_Suspend directly may not put the system to sleep immediately (mainly dependent on whether the wake lock is released).
 * Please refer to the documentation for more details on wake locks.
 **/
int SU_Base_Suspend();

/**
 * @fn: int SU_Base_SetWkupMode(SUWkup mode)
 *
 * @brief: Set the wake-up mode for the device.
 *
 * @param: Key wake-up or timed wake-up.
 *
 * @retval: 0 Success. Non-zero Failure.
 *
 * @remarks: None.
 *
 * @attention: Call this function before calling SU_Base_Suspend.
 **/
int SU_Base_SetWkupMode(SUWkup mode);

/**
 * @fn: void SU_Base_CtlPwrDown();
 *
 * @brief: Control the T32 SoC PWRON pin to pull it low.
 *
 * @param: None.
 *
 * @retval: -1 Failure, 0 Success.
 *
 * @remarks: None.
 *
 * @attention: Once this interface is called, it means that RTC will no longer be readable or writable.
 **/
int SU_Base_CtlPwrDown(void);

/**
 * @fn: int SU_Base_GetWkupMode(void)
 *
 * @brief: Get the actual wake-up mode for the current wake-up event.
 *
 * @param: None.
 *
 * @remarks: None.
 *
 * @retval:
 *   WKUP_ALARM = 1 Timed wake-up
 *   WKUP_KEY = 2 Key wake-up
 *
 * @attention: None.
 **/

int SU_Base_GetWkupMode(void);

/*
 * System PM related interfaces
 *
 * */

/*
 * @fn: int SU_PM_Init(SUPM_Init_Cfg_t *cfg_p);
 *
 * @brief: Initialization of PM-related interfaces
 *
 * @param:
 *
 * @retval: -1 failure, 0 success
 *
 * @remarks: None
 *
 * @attention: Call before media startup.
 * */
int SU_PM_Init(SUPM_Init_Cfg_t *cfg_p);

/*
 * @fn: int SU_PM_DeInit(void)
 *
 * @brief: Deinitialization of PM-related interfaces
 *
 * @param: None
 *
 * @retval: -1 failure, 0 success
 *
 * @remarks: None
 *
 * @attention: Call after SU_PM_Init.
 * */
int SU_PM_DeInit(void);


/*
 * @fn: int SU_PM_WaitThreadSuspend(int timeout);
 *
 * @brief: Wait for the threads added via SU_PM_AddThreadListen to be fully suspended.
 *  And the number of suspended threads equals the 'num' set by SU_PM_ListenThreadNums.
 *
 * @param: timeout: Timeout duration, -1 to wait indefinitely, >0 for a timeout
 *
 * @retval: -1 failure, 0 success
 *
 * @remarks: None
 *
 * @attention: None
 * */
int SU_PM_WaitThreadSuspend(int timeout);


/*
 * @fn: int SU_PM_InitListenLock(int num)
 *
 * @brief: Set the number of threads to be pre-listened
 *
 * @param: None
 *
 * @retval: -1 failure, 0 success
 *
 * @remarks: None
 *
 * @attention: Call before SU_PM_AddThreadListen.
 * */
int SU_PM_InitListenLock(int num);


/*
 * @fn: int SU_PM_GetListenLockNums(void)
 *
 * @brief: Number of listening locks obtained
 *
 * @param: 无
 *
 * @retval: -1 失败, >0 Number of listening locks
 *
 * @remarks: 无
 *
 * @attention: 无
 * */
int SU_PM_GetListenLockNums(void);

/*
 * @fn: int SU_PM_AddThreadListen(void)
 *
 * @brief: Add the calling thread to the listening queue
 *
 * @param: None
 *
 * @retval: -1 failure, > 0 success
 *
 * @remarks: None
 *
 * @attention: Should be used in pairs with SU_PM_DelThreadListen.
 * */
int SU_PM_AddThreadListen(void);

/*
 * @fn: int SU_PM_DelThreadListen(int tpid)
 *
 * @brief: Remove the calling thread from the listening queue
 *
 * @param: tpid: SU_PM_AddThreadListen return value
 *
 * @retval: -1 failure, 0 success
 *
 * @remarks: None
 *
 * @attention: Should be used in pairs with SU_PM_AddThreadListen.
 * */
int SU_PM_DelThreadListen(int tpid);


/*
 * @fn: int SU_PM_TheadSuspend(void)
 *
 * @brief: The calling thread is suspended by the system and enters a sleep state
 *
 * @param: None
 *
 * @retval:
 *      Successful sleep: 0,
 *      Sleep failure: -2,
 *      Sleep function disabled: -1,
 *
 * @remarks: None
 *
 * @attention: Should call SU_PM_AddThreadListen first.
 * */
int SU_PM_TheadSuspend(void);


/*
 * @fn: int SU_PM_ThreadResume(void)
 *
 * @brief: Resume all suspended threads to the running state
 *
 * @param: None
 *
 * @retval: -1 failure, 0 success
 *
 * @remarks: None
 *
 * @attention: None
 * */
int SU_PM_ThreadResume(void);


/*
 * @fn: int SU_PM_EventSend(int event, eSUPM_EVENT_SET sync_t)
 *
 * @brief: Event sending. Currently supports whether SU_PM_ThreadSuspend is enabled.
 *
 * @param:
 *       event: The event to send
 *       sync_t: Event sending mode
 *
 * @retval: -1 failure, 0 success
 *
 * @remarks: None
 *
 * @attention: None
 * */
int SU_PM_EventSend(eSUPM_EVENT_MODE mode, eSUPM_EVENT_TYPE type);

/*
 * @fn: int SU_PM_GetEvent(void)
 *
 * @brief: Judge current PM events
 *
 * @param: None
 *
 * @retval: -1 fail, 0 sucess
 *
 * @remarks: None
 *
 * @attention: None
 * */
eSUPM_EVENT_MODE SU_PM_GetEvent(void);


/*
 * @fn: int SU_PM_RequestWakeLock(const char *name)
 *
 * @brief: Request wake lock
 *
 * @param: name: lock name
 *
 * @retval: -1 failure, 0 success
 *
 * @remarks: None
 *
 * @attention: Used in pairs with SU_PM_ReleaseWakeLock.
 * */
int SU_PM_RequestWakeLock(const char *name);


/*
 * @fn: int SU_PM_ReleaseWakeLock(const char *name)
 *
 * @brief: Release wake lock
 *
 * @param: name: lock name
 *
 * @retval: -1 failure, 0 success
 *
 * @remarks: None
 *
 * @attention: Used in pairs with SU_PM_RequestWakeLock.
 * */
int SU_PM_ReleaseWakeLock(const char *name);


/*
 * @fn: int SU_Base_GetWakeupCount(void)
 *
 * @brief: Blocking acquisition of wakeup count
 *
 * @param: None
 *
 * @retval: -1 failure, 0 sucess
 *
 * @remarks: None
 *
 * @attention: Call before sleeping
 * */
int SU_Base_GetWakeupCount(void);

/*
 * @fn: int SU_PM_Set_CPUOnline(int online)
 *
 * @brief: Set whether CPU1 is enabled
 *
 * @param:
 *  online = 1 to enable CPU1
 *  online = 0 to disable CPU1
 *
 * @retval: -1 for failure, 0 for success
 *
 * @remarks: None
 *
 * @attention: None
 * */
int SU_PM_Set_CPUOnline(int online);


/*
 * @fn: int SU_PM_Get_CPUOnlineNums()
 *
 * @brief: Get the number of actively online CPUs
 *
 * @param: None
 *
 * @retval: >0 for the number of CPUs, -1 for failure
 *
 * @remarks: None
 *
 * @attention: None
 * */
int SU_PM_Get_CPUOnlineNums();

/*
 * @fn: void SU_PM_Sleep(unsigned int msec)
 *
 * @brief:Compensate for the sleep duration in SOC
 *
 * @param: millisecond
 *
 * @retval: -1 for failure, 0 for success
 *
 * @remarks: None
 *
 * @attention: None
 * */
void SU_PM_Sleep(unsigned int msec);

/**
 * @}
 */



/**
 * @}
 */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __SU_BASE_H__ */
