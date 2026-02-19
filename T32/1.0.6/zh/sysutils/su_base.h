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
 * Sysutils 基础功能头文件
 */

/**
 * @defgroup sysutils System Utils
 */

/**
 * @defgroup Sysutils_Base
 * @ingroup sysutils
 * @brief 系统基础功能.
 * @{
 */

/**
 * 设备ID逻辑编码
 */
#define DEVICE_ID_MAGIC     "53ef"

/**
 * 设备ID逻辑编码长度
 */
#define DEVICE_ID_MAGIC_LEN 4

/**
 * 设备ID长度
 */
#define DEVICE_ID_LEN       32

/**
 * 设备型号\设备ID\固件版本信息的最大长度
 */
#define MAX_INFO_LEN        64

/**
 * 设备型号.
 */
typedef struct {
	char chr[MAX_INFO_LEN];		/**< 设备型号字符串 */
} SUModelNum;

/**
 * 设备软件版本.
 */
typedef struct {
	char chr[MAX_INFO_LEN];		/**< 设备软件版本字符串 */
} SUVersion;

/**
 * 设备ID.设备ID为唯一值，不同的CPU芯片间的值有差异
 */
typedef union {
	char chr[MAX_INFO_LEN];		/**< 设备ID字符串 */
	uint8_t hex[MAX_INFO_LEN];	/**< 设备ID二进制 */
} SUDevID;

/**
 * 系统时间结构体.
 */
typedef struct {
	int sec;	/**< 秒数，范围：0~59 */
	int min;	/**< 分钟数，范围：0~59 */
	int hour;	/**< 小时数，范围：0~23 */
	int mday;	/**< 一个月中的第几天，范围：1~31 */
	int mon;	/**< 月份，范围：1~12 */
	int year;	/**< 年份，范围：>1900 */
} SUTime;

typedef enum {
	WKUP_ALARM = 1,         /*定时唤醒*/
	WKUP_KEY,               /*按键唤醒*/
	WKUP_MAX,               /*最大*/
}SUWkup;

typedef enum {
	PM_DISABLE_PAUSE = 0,   /*<线程睡眠接口失能*/
	PM_ENABLE_PAUSE,        /*<线程睡眠接口使能*/
	PM_IS_INVAL,
}eSUPM_EVENT_MODE;

typedef enum {
	PM_EVENT_SYNC = 0,      /*<同步方式*/
	PM_EVENT_ASYNC,         /*<异步方式*/
	PM_EVENT_INVAL,
}eSUPM_EVENT_TYPE;

typedef enum {
	PM_API_ENABLE = 0,      /*<使能PM相关接口*/
	PM_API_DISABLE,         /*<失能PM相关接口*/
	PM_API_INVAL,           /*<无效位*/
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
 * @brief: 获取设备型号.
 *
 * @param[out]: modelNum 设备型号结构体指针.
 *
 * @retval: 0 成功. 非0 失败.
 *
 * @remarks: 无
 *
 * @attention 无.
 */
int SU_Base_GetModelNumber(SUModelNum *modelNum);

/**
 * @fn int SU_Base_GetVersion(SUVersion *version)
 *
 * @brief: 获取设备版本.
 *
 * @param[out]: version 设备版本结构体指针.
 *
 * @retval: 0 成功.非0 失败.
 *
 * @remarks: 无
 *
 * @attention 无.
 */
int SU_Base_GetVersion(SUVersion *version);

/**
 * @fn int SU_Base_GetDevID(SUDevID *devID)
 *
 * @brief: 获取设备ID.
 *
 * @param[out] devID 设备ID结构体指针.
 *
 * @retval: 0 成功. 非0 失败.
 *
 * @remarks: 无
 *
 * @attention: 每颗CPU芯片的设备ID是唯一的.
 */
int SU_Base_GetDevID(SUDevID *devID);

/**
 * @fn: int SU_Base_GetTime(SUTime *time)
 *
 * @brief: 获得系统时间.
 *
 * @param[in] time 系统时间结构体指针.
 *
 * @retval: 0 成功. 非0 失败.
 *
 * @remarks: 无
 *
 * @attention 无.
 */
int SU_Base_GetTime(SUTime *time);

/**
 * @fn: int SU_Base_SetTime(SUTime *time)
 *
 * @brief: 设置系统时间.
 *
 * @param[out] time 系统时间结构体指针.
 *
 * @retval: 0 成功. 非0 失败.
 *
 * @remarks: 无
 *
 * @attention: 系统时间参数需在合理范围，否则函数调用失败.
 */
int SU_Base_SetTime(SUTime *time);

/**
 * @fn: int SU_Base_SUTime2Raw(SUTime *suTime, uint32_t *rawTime)
 *
 * @brief: 将SUTime类型的时间转换为以秒为单位的Raw时间.
 *
 * @param[in] suTime 系统时间结构体指针.
 * @param[out] rawTime Raw时间(从1970-01-01 00:00:00开始算起).
 *
 * @retval: 0 成功. 非0 失败.
 *
 * @remarks: 此函数可以用在设置相对秒数的Alarm.
 *
 * @attention: 无.
 */
int SU_Base_SUTime2Raw(SUTime *suTime, uint32_t *rawTime);

/**
 * @fn: int SU_Base_Raw2SUTime(uint32_t *rawTime, SUTime *suTime)
 *
 * @brief: 将以秒为单位的Raw时间转换为SUTime类型的时间.
 *
 * @param[in] rawTime Raw时间(从1970-01-01 00:00:00开始算起).
 * @param[out] suTime 系统时间结构体指针.
 *
 * @retval: 0 成功. retval 非0 失败.
 *
 * @remarks: 此函数可以用在设置相对秒数的Alarm.
 *
 * @attention: 无.
 */
int SU_Base_Raw2SUTime(uint32_t *rawTime, SUTime *suTime);

/**
 * @fn: int SU_Base_SetAlarm(SUTime *time)
 *
 * @brief: 设定闹钟时间.
 *
 * @param[in] time 系统时间结构体指针.
 *
 * @retval: 0 成功. 非0 失败.
 *
 * @remarks: 暂支持24小时内的闹钟设定.
 *
 * @attention: 系统时间参数需在合理范围，否则函数调用失败.
 */
int SU_Base_SetAlarm(SUTime *time);

/**
 * @fn: int SU_Base_GetAlarm(SUTime *time)
 *
 * @brief: 获得闹钟定时时间.
 *
 * @param[out] time 系统时间结构体指针.
 *
 * @retval: 0 成功. 非0 失败.
 *
 * @remarks: 无.
 *
 * @attention: 无.
 */
int SU_Base_GetAlarm(SUTime *time);

/**
 * @fn: int SU_Base_EnableAlarm()
 *
 * @brief: 使能闹钟.
 *
 * @param: 无.
 *
 * @retval: 0 成功. 非0 失败.
 *
 * @remarks: 调用该函数之前，请调用SU_Base_GetAlarm（SUTime *time）设定闹钟时间.
 *
 * @attention: 调用该函数之前，请调用SU_Base_GetAlarm（SUTime *time）设定闹钟时间.
 * 如果闹钟时间在当前系统时间之前返回失败.
 */
int SU_Base_EnableAlarm(void);

/**
 * @fn: int SU_Base_DisableAlarm()
 *
 * @brief: 关闭闹钟.
 *
 * @param: 无.
 *
 * @retval: 0 成功. 非0 失败.
 *
 * @remarks: 无.
 *
 * @attention: 无.
 */
int SU_Base_DisableAlarm(void);

/**
 * @fn: int SU_Base_PollingAlarm(uint32_t timeoutMsec)
 *
 * @brief: 等待闹钟.
 *
 * @param[in] timeoutMsec超时时间, 单位: 毫秒.
 *
 * @retval: 0 成功. 非0 失败.
 *
 * @remarks: 调用该函数后，程序会进入阻塞状态，一直到闹钟响应退出或超时退出.
 *
 * @attention: 无.
 */
int SU_Base_PollingAlarm(uint32_t timeoutMsec);

/**
 * @fn: int SU_Base_Shutdown(void)
 *
 * @brief: 设备关机.
 *
 * @param: 无.
 *
 * @retval: 0 成功. 非0 失败.
 *
 * @remarks: 调用该函数后设备会立即关机并关闭主电源.
 *
 * @attention: 在调用此函数之前请确保已保存所有文件.
 **/
int SU_Base_Shutdown(void);

/**
 * @fn: int SU_Base_Reboot(void)
 *
 * @brief: 设备重启.
 *
 * @param: 无.
 *
 * @retval: 0 成功.非0 失败.
 *
 * @remarks: 无
 *
 * @attention: 调用该函数后设备会立即重启.在调用此函数之前请确保已保存所有文件.
 **/
int SU_Base_Reboot(void);

/**
 * @fn: int SU_Base_Suspend()
 *
 * @brief: 调用该函数后设备会立即进入休眠,函数正常退出后说明系统已经唤醒.
 *
 * @param: 无.
 *
 * @retval:0 成功.非0 失败.
 *
 * @remarks: 无
 *
 * @attention: 注意,为了保护Suspend的安全. 加入了wake lock/unlock机制
 * 所以直接调用SU_Base_Suspend可能并不会直接进入睡眠(主要判断wake锁是否释放完毕)
 * 详细请查看文档wake
 **/
int SU_Base_Suspend();

/**
 * @fn: int SU_Base_SetWkupMode(SUWkup mode)
 *
 * @brief:设置休眠模式.
 *
 * @param:按键唤醒、定时唤醒
 *
 * @retval:0 成功.非0 失败.
 *
 * @remarks: 无
 *
 * @attention:调用SU_Base_Suspend之前调用该函数
 **/
int SU_Base_SetWkupMode(SUWkup mode);

/**
 * @fn: void SU_Base_CtlPwrDown();
 *
 * @brief: 控制T32 SoC PWRON 引脚拉低.
 *
 * @param  无
 *
 * @retval: -1 失败, 0 成功
 *
 * @remarks: 无
 *
 * @attention: 注意一旦调用此接口,意味着RTC将不在读写
 **/
int SU_Base_CtlPwrDown(void);

/**
 * @fn:int SU_Base_GetWkupMode(void)
 *
 * @brief: 获取本次真实唤醒方式
 *
 * @param: 无
 *
 * @remarks: 无
 *
 * @retval:
 *   WKUP_ALARM = 1 定时唤醒
 *   WKUP_KEY = 2   按键唤醒
 *
 * @attention: 无
 **/

int SU_Base_GetWkupMode(void);

/*
 * System PM related interfaces
 *
 * */

/*
 * @fn: int SU_PM_Init(SUPM_Init_Cfg_t *cfg_p);
 *
 * @brief: PM相关接口初始化
 *
 * @param:
 *
 * @retval: -1 失败, 0 成功
 *
 * @remarks: 无
 *
 * @attention: 在媒体启动之前调用.
 * */
int SU_PM_Init(SUPM_Init_Cfg_t *cfg_p);

/*
 * @fn: int SU_PM_DeInit(void)
 *
 * @brief: PM相关接口反初始化
 *
 * @param: 无
 *
 * @retval: -1 失败, 0 成功
 *
 * @remarks: 无
 *
 * @attention: SU_PM_Init 已调用
 * */
int SU_PM_DeInit(void);


/*
 * @fn: int SU_PM_WaitThreadSuspend(int timeout);
 *
 * @brief: 等待加入SU_PM_AddThreadListen接口的线程完全被挂起.
 *  且挂起的数量等于SU_PM_ListenThreadNums设置的num
 *
 * @param: timeout: 超时时间,-1 一直等待, >0 超时等待
 *
 * @retval: -1 失败, 0 成功
 *
 * @remarks: 无
 *
 * @attention: 无
 * */
int SU_PM_WaitThreadSuspend(int timeout);


/*
 * @fn: int SU_PM_InitListenLock(int num)
 *
 * @brief: 设置预先监听线程数量
 *
 * @param: 无
 *
 * @retval: -1 失败, >0 成功
 *
 * @remarks: 无
 *
 * @attention: SU_PM_AddThreadListen之前调用
 * */
int SU_PM_InitListenLock(int num);


/*
 * @fn: int SU_PM_GetListenLockNums(void)
 *
 * @brief: 获得监听锁的个数
 *
 * @param: 无
 *
 * @retval: -1 失败, >0 监听锁数
 *
 * @remarks: 无
 *
 * @attention: 无
 * */
int SU_PM_GetListenLockNums(void);

/*
 * @fn: int SU_PM_AddThreadListen(void)
 *
 * @brief: 将调用的线程加入监听队列中
 *
 * @param: 无
 *
 * @retval: -1 失败, 0 成功
 *
 * @remarks: 无
 *
 * @attention: 需要和SU_PM_DelThreadListen成对使用
 * */
int SU_PM_AddThreadListen(void);

/*
 * @fn: int SU_PM_DelThreadListen(int tpid)
 *
 * @brief: 将调用的线程删除监听队列
 *
 * @param: tpid: SU_PM_AddThreadListen 返回值
 *
 * @retval: -1 失败, 0 成功
 *
 * @remarks: 无
 *
 * @attention: 需要和SU_PM_AddThreadListen成对使用
 * */
int SU_PM_DelThreadListen(int tpid);


/*
 * @fn: int SU_PM_TheadSuspend(void)
 *
 * @brief: 调用此接口的线程被系统挂起，进入睡眠状态
 *
 * @param: 无
 *
 * @retval:
 *      睡眠成功: 0,
 *      睡眠失败: -2,
 *      睡眠功能关闭: -1,
 *
 * @remarks: 无
 *
 * @attention: 需要先调用SU_PM_AddThreadListen
 * */
int SU_PM_TheadSuspend(void);


/*
 * @fn: int SU_PM_ThreadResume(void)
 *
 * @brief: 将挂起的线程全部恢复运行状态
 *
 * @param: 无
 *
 * @retval: -1 失败, 0 成功
 *
 * @remarks: 无
 *
 * @attention: 无
 * */
int SU_PM_ThreadResume(void);


/*
 * @fn: int SU_PM_EventSend(int event, eSUPM_EVENT_SET sync_t)
 *
 * @brief: 事件发送.目前支持SU_PM_TheadSuspend是否使能
 *
 * @param:
 *       event: 要发送的事件
 *       sync_t: 事件发送方式
 *
 * @retval: -1 失败, 0 成功
 *
 * @remarks: 无
 *
 * @attention: 无
 * */
int SU_PM_EventSend(eSUPM_EVENT_MODE mode, eSUPM_EVENT_TYPE type);

/*
 * @fn: int SU_PM_GetEvent(void)
 *
 * @brief: 判断当前PM 事件
 *
 * @param: 无
 *
 * @retval: -1 失败, 0 成功
 *
 * @remarks: 无
 *
 * @attention: 无
 * */
eSUPM_EVENT_MODE SU_PM_GetEvent(void);


/*
 * @fn: int SU_PM_RequestWakeLock(const char *name)
 *
 * @brief: 申请唤醒锁
 *
 * @param: name,锁名字
 *
 * @retval: -1 失败, 0 成功
 *
 * @remarks: 无
 *
 * @attention: 和SU_PM_ReleaseWakeLock成对使用
 * */
int SU_PM_RequestWakeLock(const char *name);


/*
 * @fn: int SU_PM_ReleaseWakeLock(const char *name)
 *
 * @brief: 释放唤醒锁
 *
 * @param: name,锁名字
 *
 * @retval: -1 失败, 0 成功
 *
 * @remarks: 无
 *
 * @attention: 和SU_PM_RequestWakeLock成对使用
 * */
int SU_PM_ReleaseWakeLock(const char *name);


/*
 * @fn: int SU_Base_GetWakeupCount(void)
 *
 * @brief: 阻塞式获取wakeup count
 *
 * @param: 无
 *
 * @retval: -1 失败, 0 成功
 *
 * @remarks: 无
 *
 * @attention: 睡眠前调用
 * */
int SU_Base_GetWakeupCount(void);

/*
 * @fn: int SU_PM_Set_CPUOnline(int online)
 *
 * @brief: 设置CPU1是否启动
 *
 * @param:
 *  online = 1启用CPU1
 *  online = 0关闭CPU1
 *
 * @retval: -1 失败, 0 成功
 *
 * @remarks: 无
 *
 * @attention: 无
 * */
int SU_PM_Set_CPUOnline(int online);


/*
 * @fn: int SU_PM_Get_CPUOnlineNums()
 *
 * @brief: 获得CPU online活动数量
 *
 * @param:  无
 *
 * @retval: >0 CPU数量, -1 失败
 *
 * @remarks: 无
 *
 * @attention: 无
 * */
int SU_PM_Get_CPUOnlineNums();

/*
 * @fn: void SU_PM_Sleep(unsigned int msec)
 *
 * @brief:补偿SOC睡眠时长
 *
 * @param:单位毫秒
 *
 * @retval: 0 正常, -1失败
 *
 * @remarks: 无
 *
 * @attention: 无
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
