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
 * Sysutils battery management header file
 */

/**
 * @defgroup Sysutils_Battery
 * @ingroup sysutils
 * @brief Battery management
 * @{
 */

/**
 * Battery status.
 */
typedef enum {
        Unknown = -1,           /**< Unknown status or no battery */
        Charging,               /**< Charging */
        Discharging,            /**< Not charging */
        Full,                   /**< Fully charged */
} SUBatStatus;

/**
 * Battery events.
 */
typedef enum {
        AC_ONLINE,              /**< AC Adapter plugged in */
        AC_OFFLINE,             /**< AC Adapter unplugged */
        USB_ONLINE,             /**< USB plugged in */
        USB_OFFLINE,            /**< USB unplugged */
} SUBatEvent;

/**
 * @fn int SU_Battery_GetStatus(SUBatStatus *status)
 *
 * Get battery status.
 *
 * @param[in] status Pointer to battery status.
 *
 * @retval 0 Success.
 * @retval Non-zero Failure.
 *
 * @remarks This function returns directly without blocking.
 *
 * @attention None.
 */
int SU_Battery_GetStatus(SUBatStatus *status);

/**
 * @fn int SU_Battery_GetEvent(SUBatEvent *event)
 *
 * Get battery event.
 *
 * @param[out] event Pointer to battery event.
 *
 * @retval 0 Success.
 * @retval Non-zero Failure.
 *
 * @remarks This function blocks until an event occurs.
 *
 * @attention None.
 */
int SU_Battery_GetEvent(SUBatEvent *event);

/**
 * @fn int SU_Battery_GetCapacity(void)
 *
 * Get battery capacity percentage.
 *
 * @param None.
 *
 * @retval >=0 Battery capacity percentage.
 * @retval Non-zero Failure.
 *
 * @remarks None.
 *
 * @attention None.
 */
int SU_Battery_GetCapacity(void);

/**
 * @fn int SU_Battery_GetVoltageUV(void)
 *
 * Get current battery voltage.
 *
 * @param None.
 *
 * @retval >=0 Battery voltage in microvolts (uV).
 * @retval Non-zero Failure.
 *
 * @remarks None.
 *
 * @attention None.
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
