#ifndef __IMP_FB_H__
#define __IMP_FB_H__

#include "imp_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

/**
 * IMP FB device info
 */
typedef struct {
	int fbXres;					/**< FB device width */
	int fbYres;					/**< FB device height */
} IMPFBDevInfo;


/**
 * IMP FB Attributes.
 */
typedef struct {
	IMPPixelFormat inPixfmt;		/**< input picture fmt */
	int inWidth;					/**< input picture width */
	int inHeight;					/**< input picture height */

	int outOffsetX;					/**< output to FB Display starting abscissa */
	int outOffsetY;					/**< output to FB Display starting ordinate */
	int outWidth;					/**< output to FB Display width */
	int outHeight;					/**< output to FB Display height */
} IMPFBAttr;


/**
 * @fn int IMP_FB_CreateGroup(int gNum)
 *
 * create FB region 
 *
 * @param[in] gNum FB group number, range: [0, @ref NR_MAX_FB_GROUPS - 1]
 *
 * @retval 0 success
 * @retval non-0 failure
 *
 * @remarks no。
 *
 * @attention no。
 */
int IMP_FB_CreateGroup(int gNum);

/**
 * @fn int IMP_FB_DestroyGroup(int gNum)
 *
 * Destory FB region
 *
 * @param[in] grpNum FB group number, range: [0, @ref NR_MAX_OSD_GROUPS - 1]
 *
 * @retval 0 success
 * @retval non-0 failure 
 *
 * @remarks no.
 *
 * @attention no.
 */
int IMP_FB_DestroyGroup(int gNum);

/**
 * @fn int IMP_FB_EnableDev(void)
 *
 * enable FB device.
 *
 * @param no.
 *
 * @retval 0 success.
 * @retval non-0 failure.
 *
 * @remarks This API will initialize the power of the LCD screen, PWM and other hardware resources.
 *
 * @attention no.
 */
int IMP_FB_EnableDev(void);

/**
 * @fn int IMP_FB_DisableDev(void)
 *
 * close FB device.
 *
 * @param no.
 *
 * @retval 0 success.
 * @retval non-0 failure.
 *
 * @remarks This API will turn off the power of the LCD screen, PWM and other hardware resources.
 *
 * @attention no.
 */
int IMP_FB_DisableDev(void);

/**
 * @fn int IMP_FB_GetDevInfo(IMPFBDevInfo *fbDevInfo)
 *
 * get FB device info.
 *
 * @param[out] fbDevInfo FB Device information structure pointe.
 *
 * @retval 0 success.
 * @retval non-0 failure.
 *
 * @remarks You can call this API to get the width and height information of the FB device as the second channel output size of the FrameSource.
 *
 * @attention no.
 */
int IMP_FB_GetDevInfo(IMPFBDevInfo *fbDevInfo);

/**
 * @}
 */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */





#endif  /*__IMP_FB_H__*/

