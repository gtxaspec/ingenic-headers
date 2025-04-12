/*
 * Misc utils header file.
 *
 * Copyright (C) 2014 Ingenic Semiconductor Co.,Ltd
 */

#ifndef __SU_MISC_H__
#define __SU_MISC_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

/**
 * @file
 * Sysutils header file of miscellaneous functions.
 */

/**
 * @defgroup Sysutils_Misc
 * @ingroup sysutils
 * @brief misc functions.
 * @{
 */

/**
 * key event.
 */
typedef enum {
	KEY_RELEASED,	/**< key release */
	KEY_PRESSED,	/**< key press */
} SUKeyEvent;

/**
 * LED command.
 */
typedef enum {
	LED_OFF,		/**< LED off */
	LED_ON,			/**< LED on */
} SULedCmd;

/**
 * @fn int SU_Key_OpenEvent(void)
 *
 * Get handler of key event.
 *
 * @param none
 *
 * @retval >0 handler.
 * @retval <=0 fail.
 *
 * @remarks Recording of key event will be start upon successfully got a handler, until closing of the handler.
 * @remarks If you open multiple handlers, key event will be recording by every handler.
 * @remarks For example, if two threads separately open a keystroke event and each thread holds a handle,
 *			both threads read the same sequence of events.
 * 			However, if two threads share the same handle, each keystroke event can be read only once.
 *
 * @attention none.
 */
int SU_Key_OpenEvent(void);

/**
 * @fn int SU_Key_CloseEvent(int evfd)
 *
 * close key event.
 *
 * @param[in] evfd handler
 *
 * @retval 0 succeed.
 * @retval not 0 fail.
 *
 * @remarks none
 *
 * @attention none.
 */
int SU_Key_CloseEvent(int evfd);

/**
 * @fn int SU_Key_ReadEvent(int evfd, int *keyCode, SUKeyEvent *event)
 *
 * read key event.
 *
 * @param[in] evfd handler
 * @param[in] keyCode code of key
 * @param[out] event ptr of event
 *
 * @retval 0 succeed.
 * @retval not 0 fail.
 *
 * @remarks This function blocks until a key event occurs.
 * @remarks keyCode defined at linux/input.h, mapping relationship with GPIO is defined at kernel board-level file.
 * @remarks here are some common keyCode：
 * @code
	#define KEY_HOME                102 //HOME key
	#define KEY_POWER               116 //power on/off, also used for wake-up
	#define KEY_WAKEUP              143 //wake-up key, other than power key
	#define KEY_F13                 183 //PIR is defined as an F13 key when used as a key.
 * @endcode
 *
 * @remarks The definition of key code and GPIO number, whether it is used as wake-up source, and
 *			effective electrical equality information are all defined in the kernel board level file, as shown below:
 *
 * @code
	struct gpio_keys_button __attribute__((weak)) board_buttons[] = {
	#ifdef GPIO_HOME
		{
			.gpio           = GPIO_HOME,		//GPIO index
			.code           = KEY_HOME,			//key code index
			.desc           = "home key",
			.active_low     = ACTIVE_LOW_HOME,	//active level
	#ifdef WAKEUP_HOME
			.wakeup         = WAKEUP_HOME,		//Defines whether it can be used as a wakeup source, where 1 is a wakeup
	#endif
	#ifdef CAN_DISABLE_HOME
			.can_disable    = CAN_DISABLE_HOME,	//defines whether it can be disabled.
	#endif
		},
	#endif
	#ifdef GPIO_POWER
		{
			.gpio           = GPIO_POWER,
			.code           = KEY_POWER,
			.desc           = "power key",
			.active_low     = ACTIVE_LOW_POWER,
	#ifdef WAKEUP_POWER
			.wakeup         = WAKEUP_POWER,
	#endif
	#ifdef CAN_DISABLE_POWER
			.can_disable    = CAN_DISABLE_POWER,
	#endif
		},
	#endif
	}
 * @endcode
 * @remarks One way to use the digital PIR is to define the PIR as a key, with the PIR triggering equivalent
 			to a key press event (@ref KEY_PRESSED) and the PIR resuming equivalent to
			a key release event (@ref KEY_RELEASED). If the PIR wake-up function is required, the corresponding
			button of PIR can be defined as the wake-up source.
 * @remarks For details about how to use the API, see sample-keyevent.c.
 *
 * @attention none.
 */
int SU_Key_ReadEvent(int evfd, int *keyCode, SUKeyEvent *event);

/**
 * @fn int SU_Key_DisableEvent(int keyCode)
 *
 * Disable key event.
 *
 * @param[in] keyCode
 *
 * @retval 0 succeed.
 * @retval not 0 fail.
 *
 * @remarks If the key is configured as a wake source, pressing the key (whether or not the key is Open) causes
 *			the system to wake up while the system is suspending. After the Disable key event, the system
 *			turns off the interruption of the key event, and the key cannot wake up the system.
 * @remarks The API can be used to disable PIR "key" wake-up mechanism.
 *
 * @attention none.
 */
int SU_Key_DisableEvent(int keyCode);

/**
 * @fn int SU_Key_EnableEvent(int keyCode)
 *
 * Enable key event.
 *
 * @param[in] keyCode
 *
 * @retval 0 succeed.
 * @retval not 0 fail.
 *
 * @remarks As the reverse of disable key event, see @ref SU_Key_DisableEvent(int keyCode)
 *
 * @attention none.
 */
int SU_Key_EnableEvent(int keyCode);

/**
 * @fn int SU_LED_Command(int ledNum, SULedCmd cmd)
 *
 * Order LED command.
 *
 * @param[in] ledNum LED number.
 * @param[in] cmd LED command.
 *
 * @retval 0 succeed.
 * @retval not 0 fail.
 *
 * @remarks The LED number varies according to the development board. The LED number is defined in kernel
 *			board-level files and registered as a Linux standard Fixed Regulator device. The GPIO number,
 *			active level, power recursive relationship and other information of LED are defined
 *			in the board level file. Below is a example that defined two LED fixed regulator:
 * @code
    FIXED_REGULATOR_DEF(
            led0,
            "LED0",         3300000,        GPIO_PA(14),
            HIGH_ENABLE,    UN_AT_BOOT,     0,
            "ldo7",         "vled0",        NULL);

    FIXED_REGULATOR_DEF(
            led1,
            "LED1",         3300000,        GPIO_PA(15),
            HIGH_ENABLE,    UN_AT_BOOT,     0,
            "ldo7",         "vled1",        NULL);

    static struct platform_device *fixed_regulator_devices[] __initdata = {
            &gsensor_regulator_device,
            &led0_regulator_device,
            &led1_regulator_device,
    };

    static int __init fix_regulator_init(void)  //register regulator with subsys_initcall_sync
    {
            int i;

            for (i = 0; i < ARRAY_SIZE(fixed_regulator_devices); i++)
                    fixed_regulator_devices[i]->id = i;

            return platform_add_devices(fixed_regulator_devices,
                                        ARRAY_SIZE(fixed_regulator_devices));
    }
    subsys_initcall_sync(fix_regulator_init);
 * @endcode
 * @remarks usage showcase:
 * @code
   if (SU_LED_Command(0, LED_ON) < 0)  //enable LED0
       printf("LED0 turn on error\n");
   if (SU_LED_Command(1, LED_ON) < 0)  //enable LED1
       printf("LED0 turn on error\n");
   if (SU_LED_Command(0, LED_OFF) < 0)  //disable LED0
       printf("LED1 turn off error\n");
   if (SU_LED_Command(1, LED_OFF) < 0)  //disable LED1
       printf("LED1 turn off error\n");
 * @endcode
 * @attention none.
 */
int SU_LED_Command(int ledNum, SULedCmd cmd);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __SU_MISC_H__ */
