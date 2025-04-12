/*
 * Battery utils header file.
 *
 * Copyright (C) 2014 Ingenic Semiconductor Co.,Ltd
 */

#ifndef __SU_BATTERY_H__
#define __SU_BATTERY_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

/**
 * @file
 * Sysutils header file of battery management
 */

/**
 * @defgroup Sysutils_Battery
 * @ingroup sysutils
 * @brief battery management
 * @{
 */

/**
 * battery status.
 */
typedef enum {
	Unknown = -1,		/**< unknown state or do not have a battery*/
	Charging,			/**< Charging */
	Discharging,		/**< Discharging */
	Full,				/**< Full */
} SUBatStatus;

/**
 * 电池事件.
 */
typedef enum {
	AC_ONLINE,			/**< AC Adapter inserted */
	AC_OFFLINE,			/**< AC Adapter pull out */
	USB_ONLINE,			/**< USB inserted */
	USB_OFFLINE,		/**< USB pullout */
} SUBatEvent;

/**
 * @fn int SU_Battery_GetStatus(SUBatStatus *status)
 *
 * Get state of battery.
 *
 * @param[out] status ptr of status.
 *
 * @retval 0 succeed.
 * @retval not 0 fail.
 *
 * @remarks this function will not blocking.
 *
 * @attention none.
 */
int SU_Battery_GetStatus(SUBatStatus *status);

/**
 * @fn int SU_Battery_GetEvent(SUBatEvent *event)
 *
 * get event of battery.
 *
 * @param[out] event ptr of event.
 *
 * @retval 0 succeed.
 * @retval not 0 fail.
 *
 * @remarks this function will blocking until event occur.
 *
 * @attention none.
 */
int SU_Battery_GetEvent(SUBatEvent *event);

/**
 * @fn int SU_Battery_GetCapacity(void)
 *
 * Get percent of battery capacity.
 *
 * @param none.
 *
 * @retval >=0 percent of capacity.
 * @retval <0 fail.
 *
 * @remarks none.
 *
 * @attention none.
 */
int SU_Battery_GetCapacity(void);

/**
 * @fn int SU_Battery_GetVoltageUV(void)
 *
 * Get voltage of battery.
 *
 * @param none.
 *
 * @retval >=0 voltage, unit uV.
 * @retval <0 fail.
 *
 * @remarks none.
 *
 * @attention none.
 */
int SU_Battery_GetVoltageUV(void);

/**
 * @}
 */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __SU_BATTERY_H__ */
