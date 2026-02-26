/*
 * IMP VideoOutput header file.
 *
 * Copyright (C) 2021 Ingenic Semiconductor Co.,Ltd
 */
#ifndef __IMP_VIDEOOUTPUT_H__
#define __IMP_VIDEOOUTPUT_H__

#include <imp/imp_common.h>

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

/**
 * @file
 * IMP video output header file
 */

 /**
  * @defgroup IMP_VO
  * @ingroup imp
  * @brief Video output module, including video output, HD video layer, video output channel, video layer algorithm
  * @section vo_summary 1 Overview
  * The video output module mainly reads video and graphic data from the corresponding memory location, and then outputs through the corresponding display interface.
  * 1. Support two HD video layers (L0 and L1), L0 supports 36 channels, L1 supports 2 channels
  * 2. Support for a graphics layer (G0)
  * 3. Support for a mouse layer (M0)
  * 4. Maximum output timing 3840x2160@60Hz
  * 5. Output interface supports HDMI, VGA and TFT screens
  * @section vo_video_layer 2 Video layer introduction
  * 1. Support formats: NV12/21 and NV16/61.
  * 2. Support resolution range: 32x32 to 3840x2160, width and height must be multiples of 2.
  * 3. Minimum resolution for each channel supported is 32x32.
  * 4. Video layer L0 supports BCSH algorithm processing for the whole layer.
  * 5. Video layer L0 supports PEAK processing for up to 9 windows.
  * 6. Video layer L0 supports DLI processing for up to 9 windows.
  * 7. The priority of video layer L1 is higher than that of video layer L0, and the display effect is L1 superimposed on L0.
  * @section vo_graphics_layer 3 graphics layer introduction
  * 1. Support formats: ARGB8888, ARGB1555 and compressed images.
  * 2. Support resolution range: 32x32 to 3840x2160, width and height must be multiples of 2.
  * @section vo_mouse_layer 4 Introduction to the mouse layer
  * 1. Support format: ARGB8888, ARGB1555.
  * 2. Support resolution range: 16x16 to 32x32, width and height must be multiples of 2.
  * @section vo_interface 5 Output Interface Introduction
  * 1. VGA maximum support 2k@60Hz video output.
  * 2. HDMI supports maximum 4K@60Hz video output.
  * 3. TFT supports maximum 2K@60Hz video output.
  * 4. Support VGA and HDMI simultaneous source output.
  * 5. TFT and VGA cannot be output from the same source at the same time.
  * @section vo_layer_priority
  * 6 Layer priority * L0 < L1 < G0 < M0'
  * @{
  * */

/**
 * The macro definition of video output interface
 */
#define VO_INTF_VGA		(0x01L<<0)
#define VO_INTF_HDMI	(0x01L<<1)
#define VO_INTF_TFT		(0x01L<<2)

typedef IMP_S32 VO_INTF_TYPE_E;

/**
 * The enumeration of video ouput resolution
 */
typedef enum {
	VO_OUTPUT_PAL = 0,
	VO_OUTPUT_NTSC,

	VO_OUTPUT_1080P24,
	VO_OUTPUT_1080P25,
	VO_OUTPUT_1080P30,

	VO_OUTPUT_720P50,
	VO_OUTPUT_720P60,
	VO_OUTPUT_1080P50,
	VO_OUTPUT_1080P60,
	VO_OUTPUT_1080P100,
	VO_OUTPUT_1080P120,

	VO_OUTPUT_576P50,
	VO_OUTPUT_480P60,

	VO_OUTPUT_640x480_60,            /* VESA 640 x 480 at 60 Hz (non-interlaced) CVT */
	VO_OUTPUT_800x600_60,            /* VESA 800 x 600 at 60 Hz (non-interlaced) */
	VO_OUTPUT_1024x768_60,           /* VESA 1024 x 768 at 60 Hz (non-interlaced) */
	VO_OUTPUT_1280x1024_60,          /* VESA 1280 x 1024 at 60 Hz (non-interlaced) */
	VO_OUTPUT_1152x864_60,           /* VESA 1152 x 864 at 60 Hz (non-interlaced) */
	VO_OUTPUT_1366x768_60,           /* VESA 1366 x 768 at 60 Hz (non-interlaced) */
	VO_OUTPUT_1440x900_60_RB,	     /* VESA 1440 x 900 at 60 Hz (non-interlaced) Reduced Blanking */
	VO_OUTPUT_1440x900_60,           /* VESA 1440 x 900 at 60 Hz (non-interlaced) CVT Compliant */
	VO_OUTPUT_1280x800_60,           /* 1280*800@60Hz VGA@60Hz*/
	VO_OUTPUT_1680x1050_60,          /* VESA 1680 x 1050 at 60 Hz (non-interlaced) */
	VO_OUTPUT_1600x1200_60,          /* VESA 1600 x 1200 at 60 Hz (non-interlaced) */
	VO_OUTPUT_1920x1200_60,          /* VESA 1920 x 1600 at 60 Hz (non-interlaced) CVT (Reduced Blanking)*/
	VO_OUTPUT_2560x1440_30,          /* 2560x1440_30 */
	VO_OUTPUT_2560x1440_60,          /* 2560x1440_60 */
	VO_OUTPUT_2560x1600_60,          /* 2560x1600_60 */
	VO_OUTPUT_3840x2160_24,
	VO_OUTPUT_3840x2160_25,          /* 3840x2160_25 */
	VO_OUTPUT_3840x2160_30,          /* 3840x2160_30 */
	VO_OUTPUT_3840x2160_50,          /* 3840x2160_50 */
	VO_OUTPUT_3840x2160_60,          /* 3840x2160_60 */
	VO_OUTPUT_USER,
	VO_OUTPUT_BUTT
}VO_INTF_SYNC_E;

/**
 * The structure of video ouput sync
 */
typedef struct{
	IMP_BOOL bSyncMode;
	IMP_BOOL bIop;
	IMP_U8	 u8Intfb;
	IMP_U16   u16Freq;
	IMP_U16   u16Vact;  /* vertical active area */
	IMP_U16   u16Vbp;    /* vertical back blank porch */
	IMP_U16   u16Vfp;    /* vertical front blank porch */

	IMP_U16   u16Hact;   /* herizontal active area */
	IMP_U16   u16Hbp;    /* herizontal back blank porch */
	IMP_U16   u16Hfp;    /* herizontal front blank porch */

	IMP_U16   u16Hpw;    /* horizontal pulse width */
	IMP_U16   u16Vpw;    /* vertical pulse width */

	IMP_BOOL  bIhs;      /* inverse horizontal synch signal */
	IMP_BOOL  bIvs;      /* inverse vertical syncv signal */
}VO_SYNC_INFO_S;

/**
 * The enumeration of video ouput color space matrix
 */
typedef enum{
    VO_CSC_MATRIX_BT601_FULL,
    VO_CSC_MATRIX_BT601_LIMIT,
    VO_CSC_MATRIX_BT709_FULL,
    VO_CSC_MATRIX_BT709_LIMIT,
    VO_CSC_MATRIX_BT2020_FULL,
    VO_CSC_MATRIX_BT2020_LIMIT,
    VO_CSC_MATRIX_INVALID,
}VO_CSC_E;

/**
 * The structure of video ouput public attribute
 */
typedef struct{
   	IMP_U32			u32BgColor;
	IMP_SIZE_S		stCanvasSize;
    VO_INTF_TYPE_E	enIntfType;
    VO_INTF_SYNC_E	enIntfSync;
    VO_SYNC_INFO_S	stSyncInfo;
}VO_PUB_ATTR_S;

/**
 * The enumeration of video ouput interface status
 */
typedef enum{
	VO_DEV_STATUS_NOPLUG = 0,
	VO_DEV_STATUS_PLUG,
	VO_DEV_STATUS_BUTT,
}VO_DEVINTF_STATUS_E;

/**
 * The structure of video ouput interface status
 */
typedef struct{
    VO_DEVINTF_STATUS_E enPlugStatus;
}VO_DEVINTF_STATUS_S;

/**
 * @fn IMP_S32 IMP_VO_SetPubAttr(IMP_S32 s32VoMod,VO_PUB_ATTR_S *pstPubAttr)
 *
 * Set the public attributes of the video output module.
 *
 * @param[in] s32VoMod Video output module ID.
 * @param[in] pstPubAttr Video output module public attributes.
 *
 * @retval 0 Success
 * @retval Non 0 Failure，For details, see the error code description.
 *
 * @remarks Null.
 *
 * @attention Before enabling the video output module,
 * @attention you must set the public attributes of the video output module.
 */
IMP_S32 IMP_VO_SetPubAttr(IMP_S32 s32VoMod,VO_PUB_ATTR_S *pstPubAttr);

/**
 * @fn IMP_S32 IMP_VO_GetPubAttr(IMP_S32 s32VoMod,VO_PUB_ATTR_S *pstPubAttr)
 *
 * Get the public attributes of the video output module.
 *
 * @param[in] s32VoMod Video output module ID.
 * @param[in] pstPubAttr Video output module public attributes.
 *
 * @retval 0 Success
 * @retval Non 0 Failure，For details, see the error code description.
 *
 * @remarks Null.
 *
 * @attention Null.
 */
IMP_S32 IMP_VO_GetPubAttr(IMP_S32 s32VoMod,VO_PUB_ATTR_S *pstPubAttr);

/**
 * @fn IMP_S32 IMP_VO_Enable(IMP_S32 s32VoMod)
 *
 * Enable the video output module.
 *
 * @param[in] s32VoMod Video output module ID.
 *
 * @retval 0 Success
 * @retval Non 0 Failure，For details, see the error code description.
 *
 * @remarks Null.
 *
 * @attention Before enabling the video output module,
 * @attention you must set the public attributes of the video output module.
 */
IMP_S32 IMP_VO_Enable(IMP_S32 s32VoMod);

/**
 * @fn IMP_S32 IMP_VO_Disable(IMP_S32 s32VoMod)
 *
 * Disable the video output module.
 *
 * @param[in] s32VoMod Video output module ID.
 *
 * @retval 0 Success
 * @retval Non 0 Failure，For details, see the error code description.
 *
 * @remarks To change the resolution, disable the video output module first.
 *
 * @attention Before disabling the video output module, disable the video layer.
 */
IMP_S32 IMP_VO_Disable(IMP_S32 s32VoMod);

/**
 * @fn IMP_S32 IMP_VO_QueryDevInfStatus(VO_INTF_TYPE_E enDevIntf,VO_DEVINTF_STATUS_S *pstIntfStatus)
 *
 * Get the HDMI/VGA status of the display interface on the video output module.
 *
 * @param[in] enDevIntf Interface.
 * @param[in] pstIntfStatus Interface status.
 *
 * @retval 0 Success
 * @retval Non 0 Failure，For details, see the error code description.
 *
 * @remarks Null.
 *
 * @attention Null.
 */
IMP_S32 IMP_VO_QueryDevInfStatus(VO_INTF_TYPE_E enDevIntf,VO_DEVINTF_STATUS_S *pstIntfStatus);

/**
 * @fn IMP_S32 IMP_VO_SetCSC(IMP_S32 s32VoMod,VO_CSC_E enCscMatrix)
 *
 * Set the color space matrix mode of video ouput module.
 *
 * @param[in] s32VoMod Video output module ID.
 * @param[in] enCscMatrix The enumeration of video ouput color space matrix mode.
 *
 * @retval 0 Success
 * @retval Non 0 Failure，For details, see the error code description.
 *
 * @remarks Null.
 *
 * @attention Null.
 */
IMP_S32 IMP_VO_SetCSC(IMP_S32 s32VoMod,VO_CSC_E	enCscMatrix);

/**
 * @fn IMP_S32 IMP_VO_GetCSC(IMP_S32 s32VoMod,VO_CSC_E enCscMatrix)
 *
 * Get the color space matrix mode of video ouput module.
 *
 * @param[in] s32VoMod Video output module ID.
 * @param[in] penCscMatrix the pointer of video ouput color space matrix mode.
 *
 * @retval 0 Success
 * @retval Non 0 Failure，For details, see the error code description.
 *
 * @remarks Null.
 *
 * @attention Null.
 */
IMP_S32 IMP_VO_GetCSC(IMP_S32 s32VoMod,VO_CSC_E	*penCscMatrix);

/**
 * The structure of video layer attributes
 */
typedef struct{
	IMP_U32			u32DispFrmRt;
	IMP_RECT_S		stDispRect;
	IMP_SIZE_S		stImageSize;
	PIXEL_FORMAT_E	enPixFmt;
}VO_VIDEO_LAYER_ATTR_S;

/**
 * @fn IMP_S32 IMP_VO_SetVideoLayerAttr(IMP_S32 s32VoLayer,const VO_VIDEO_LAYER_ATTR_S *pstLayerAttr)
 *
 * Set the video layer attributes.
 *
 * @param[in] s32VoLayer Video layer ID.
 * @param[in] pstLayerAttr The pointer of the video layer attributes.
 *
 * @retval 0 Success
 * @retval Non 0 Failure，For details, see the error code description.
 *
 * @remarks Don't mind whether binding relationships are established when setting video layer attributes.
 *
 * @attention Setting the video layer attributes must be done when the video layer is disabled.
 */
IMP_S32 IMP_VO_SetVideoLayerAttr(IMP_S32 s32VoLayer,const VO_VIDEO_LAYER_ATTR_S *pstLayerAttr);

/**
 * @fn IMP_S32 IMP_VO_GetVideoLayerAttr(IMP_S32 s32VoLayer,VO_VIDEO_LAYER_ATTR_S *pstLayerAttr)
 *
 * Get the video layer attributes.
 *
 * @param[in] s32VoLayer Video layer ID.
 * @param[in] pstLayerAttr The pointer of the video layer attributes.
 *
 * @retval 0 Success
 * @retval Non 0 Failure，For details, see the error code description.
 *
 * @remarks Null.
 *
 * @attention Null.
 */
IMP_S32 IMP_VO_GetVideoLayerAttr(IMP_S32 s32VoLayer,VO_VIDEO_LAYER_ATTR_S *pstLayerAttr);

/**
 * @fn IMP_S32 IMP_VO_EnableVideoLayer(IMP_S32 s32VoLayer)
 *
 * Enable the video layer.
 *
 * @param[in] s32VoLayer Video layer ID.
 *
 * @retval 0 Success
 * @retval Non 0 Failure，For details, see the error code description.
 *
 * @remarks Null.
 *
 * @attention Before enabling the video layer, ensure that the video layer has been configured.
 */
IMP_S32 IMP_VO_EnableVideoLayer(IMP_S32 s32VoLayer);

/**
 * @fn IMP_S32 IMP_VO_DisableVideoLayer(IMP_S32 s32VoLayer)
 *
 * Disable the video layer.
 *
 * @param[in] s32VoLayer Video layer ID.
 *
 * @retval 0 Success
 * @retval Non 0 Failure，For details, see the error code description.
 *
 * @remarks Null.
 *
 * @attention Before disabling the video layer, ensure that all the video output channels on the video layer are disabled.
 */
IMP_S32 IMP_VO_DisableVideoLayer(IMP_S32 s32VoLayer);

/**
 * The structure of video channel attributes
 */
typedef struct{
    IMP_U32		u32Priority;
    IMP_BOOL	bDeflicker;
    IMP_RECT_S	stRect;
}VO_CHN_ATTR_S;

/**
 * @fn IMP_S32 IMP_VO_SetChnAttr(IMP_S32 s32VoLayer,IMP_S32 s32VoChn,const VO_CHN_ATTR_S *pstChnAttr)
 *
 * Set the video channel attributes
 *
 * @param[in] s32VoLayer Video layer ID.
 * @param[in] s32VoChn Video channel ID.
 * @param[in] pstChnAttr The pointer of video channel attributes.
 *
 * @retval 0 Success
 * @retval Non 0 Failure，For details, see the error code description.
 *
 * @remarks Null.
 *
 * @attention The display area of the channel cannot exceed the canvas size set in the video layer.
 */
IMP_S32 IMP_VO_SetChnAttr(IMP_S32 s32VoLayer,IMP_S32 s32VoChn,const VO_CHN_ATTR_S *pstChnAttr);

/**
 * @fn IMP_S32 IMP_VO_GetChnAttr(IMP_S32 s32VoLayer,IMP_S32 s32VoChn,VO_CHN_ATTR_S *pstChnAttr)
 *
 * Get the video channel attributes
 *
 * @param[in] s32VoLayer Video layer ID.
 * @param[in] s32VoChn Video channel ID.
 * @param[in] pstChnAttr The pointer of video channel attributes.
 *
 * @retval 0 Success
 * @retval Non 0 Failure，For details, see the error code description.
 *
 * @remarks Null.
 *
 * @attention Null.
 */
IMP_S32 IMP_VO_GetChnAttr(IMP_S32 s32VoLayer,IMP_S32 s32VoChn,VO_CHN_ATTR_S *pstChnAttr);

/**
 * @fn IMP_S32 IMP_VO_EnableChn(IMP_S32 s32VoLayer,IMP_S32 s32VoChn)
 *
 * Enable the video channel.
 *
 * @param[in] s32VoLayer Video layer ID.
 * @param[in] s32VoChn Video channel ID.
 *
 * @retval 0 Success
 * @retval Non 0 Failure，For details, see the error code description.
 *
 * @remarks Null.
 *
 * @attention Before enabling a video channel, you need to configure the channel properties.
 */
IMP_S32 IMP_VO_EnableChn(IMP_S32 s32VoLayer,IMP_S32 s32VoChn);

/**
 * @fn IMP_S32 IMP_VO_DisableChn(IMP_S32 s32VoLayer,IMP_S32 s32VoChn)
 *
 * Disable the video channel.
 *
 * @param[in] s32VoLayer Video layer ID.
 * @param[in] s32VoChn Video channel ID.
 *
 * @retval 0 Success
 * @retval Non 0 Failure，For details, see the error code description.
 *
 * @remarks Null.
 *
 * @attention Null.
 */
IMP_S32 IMP_VO_DisableChn(IMP_S32 s32VoLayer,IMP_S32 s32VoChn);

/**
 * @fn IMP_S32 IMP_VO_SetChnDispPos(IMP_S32 s32VoLayer,IMP_S32 s32VoChn,const IMP_POINT_S *pstPoint)
 *
 * Set position of the video channel.
 *
 * @param[in] s32VoLayer Video layer ID.
 * @param[in] s32VoChn Video channel ID.
 * @param[in] pstPoint The pointer of position.
 *
 * @retval 0 Success
 * @retval Non 0 Failure，For details, see the error code description.
 *
 * @remarks Null.
 *
 * @attention Enable the video layer and video output channel before invoking this interface.
 * @attention The video channel display area cannot exceed the video layer.
 */
IMP_S32 IMP_VO_SetChnDispPos(IMP_S32 s32VoLayer,IMP_S32 s32VoChn,const IMP_POINT_S *pstPoint);

/**
 * @fn IMP_S32 IMP_VO_GetChnDispPos(IMP_S32 s32VoLayer,IMP_S32 s32VoChn,IMP_POINT_S *pstPoint)
 *
 * Get position of the video channel.
 *
 * @param[in] s32VoLayer Video layer ID.
 * @param[in] s32VoChn Video channel ID.
 * @param[in] pstPoint The pointer of position.
 *
 * @retval 0 Success
 * @retval Non 0 Failure，For details, see the error code description.
 *
 * @remarks Null.
 *
 * @attention Null.
 */
IMP_S32 IMP_VO_GetChnDispPos(IMP_S32 s32VoLayer,IMP_S32 s32VoChn,IMP_POINT_S *pstPoint);

/**
 * @fn IMP_S32 IMP_VO_PauseChn(IMP_S32 s32VoLayer,IMP_S32 s32VoChn)
 *
 * Pause the video channel.
 *
 * @param[in] s32VoLayer Video layer ID.
 * @param[in] s32VoChn Video channel ID.
 *
 * @retval 0 Success
 * @retval Non 0 Failure，For details, see the error code description.
 *
 * @remarks Null.
 *
 * @attention Null.
 */
IMP_S32 IMP_VO_PauseChn(IMP_S32 s32VoLayer,IMP_S32 s32VoChn);

/**
 * @fn IMP_S32 IMP_VO_ResumeChn(IMP_S32 s32VoLayer,IMP_S32 s32VoChn)
 *
 * Resume the video channel.
 *
 * @param[in] s32VoLayer Video layer ID.
 * @param[in] s32VoChn Video channel ID.
 *
 * @retval 0 Success
 * @retval Non 0 Failure，For details, see the error code description.
 *
 * @remarks This interface is used to restore the display of a paused channel or a channel that is playing in a single frame.
 *
 * @attention Null.
 */
IMP_S32 IMP_VO_ResumeChn(IMP_S32 s32VoLayer,IMP_S32 s32VoChn);

/**
 * @fn IMP_S32 IMP_VO_StepChn(IMP_S32 s32VoLayer,IMP_S32 s32VoChn)
 *
 * Step the video channel.
 *
 * @param[in] s32VoLayer Video layer ID.
 * @param[in] s32VoChn Video channel ID.
 *
 * @retval 0 Success
 * @retval Non 0 Failure，For details, see the error code description.
 *
 * @remarks Null.
 *
 * @attention Pause the video channel display before using this interface.
 */
IMP_S32 IMP_VO_StepChn(IMP_S32 s32VoLayer,IMP_S32 s32VoChn);

/**
 * @fn IMP_S32 IMP_VO_ShowChn(IMP_S32 s32VoLayer,IMP_S32 s32VoChn)
 *
 * Show the video channel.
 *
 * @param[in] s32VoLayer Video layer ID.
 * @param[in] s32VoChn Video channel ID.
 *
 * @retval 0 Success
 * @retval Non 0 Failure，For details, see the error code description.
 *
 * @remarks By default, the video channel is displayed.
 *
 * @attention Null.
 */
IMP_S32 IMP_VO_ShowChn(IMP_S32 s32VoLayer,IMP_S32 s32VoChn);

/**
 * @fn IMP_S32 IMP_VO_HideChn(IMP_S32 s32VoLayer,IMP_S32 s32VoChn)
 *
 * Hide the video channel.
 *
 * @param[in] s32VoLayer Video layer ID.
 * @param[in] s32VoChn Video channel ID.
 *
 * @retval 0 Success
 * @retval Non 0 Failure，For details, see the error code description.
 *
 * @remarks Null.
 *
 * @attention Null.
 */
IMP_S32 IMP_VO_HideChn(IMP_S32 s32VoLayer,IMP_S32 s32VoChn);

/**
 * @fn IMP_S32 IMP_VO_HideChnPart(IMP_S32 s32VoLayer,IMP_S32 *pS32VoChnPart,IMP_S32 s32VoChnCnt)
 *
 * Hide the part of video channel
 *
 * @param[in] s32VoLayer the video layer ID.
 * @param[in] pS32VoChnPart the pointer of video channel array.
 * @param[in] s32VoChnCnt video channel count.
 *
 * @retval 0 success
 * @retval Non 0 Failure，For details, see the error code description.
 *
 * @remarks 无.
 *
 * @attention 无.
 */
IMP_S32 IMP_VO_HideChnPart(IMP_S32 s32VoLayer,IMP_S32 *pS32VoChnPart,IMP_S32 s32VoChnCnt);

/**
 * @fn IMP_S32 IMP_VO_HideChnAll(IMP_S32 s32VoLayer)
 *
 * Hide all the video channel.
 *
 * @param[in] s32VoLayer Video layer ID.
 *
 * @retval 0 Success
 * @retval Non 0 Failure，For details, see the error code description.
 *
 * @remarks Null.
 *
 * @attention Null.
 */
IMP_S32 IMP_VO_HideChnAll(IMP_S32 s32VoLayer);

/**
 * The structure of video channel zoom attributes
 */
typedef struct{
	IMP_RECT_S stZoomRect;
}VO_ZOOM_ATTR_S;

/**
 * @fn IMP_S32 IMP_VO_SetZoomInWindow(IMP_S32 s32VoLayer,IMP_S32 s32VoChn,VO_ZOOM_ATTR_S *stZoomAttr)
 *
 * Set zoom attributes of the video channel.
 *
 * @param[in] s32VoLayer Video layer ID.
 * @param[in] s32VoChn Video channel ID.
 * @param[in] stZoomAttr The pointer of zoom attributes.
 *
 * @retval 0 Success
 * @retval Non 0 Failure，For details, see the error code description.
 *
 * @remarks Make sure the video layer and channel are enabled.
 *
 * @attention Only HD Video Layer 0 has this feature. This interface can be used only in single-channel full-screen mode.
 */
IMP_S32 IMP_VO_SetZoomInWindow(IMP_S32 s32VoLayer,IMP_S32 s32VoChn,VO_ZOOM_ATTR_S *stZoomAttr);

/**
 * @fn IMP_S32 IMP_VO_GetZoomInWindow(IMP_S32 s32VoLayer,IMP_S32 s32VoChn,VO_ZOOM_ATTR_S *stZoomAttr)
 *
 * Get zoom attributes of the video channel.
 *
 * @param[in] s32VoLayer Video layer ID.
 * @param[in] s32VoChn Video channel ID.
 * @param[in] stZoomAttr The pointer of zoom attributes.
 *
 * @retval 0 Success
 * @retval Non 0 Failure，For details, see the error code description.
 *
 * @remarks Null.
 *
 * @attention Null.
 */
IMP_S32 IMP_VO_GetZoomInWindow(IMP_S32 s32VoLayer,IMP_S32 s32VoChn,VO_ZOOM_ATTR_S *stZoomAttr);

/**
 * @fn IMP_S32 IMP_VO_ClearChnBuffer(IMP_S32 s32VoLayer,IMP_S32 s32VoChn,IMP_BOOL bClrAll)
 *
 * Clear cached frame of the video channel.
 *
 * @param[in] s32VoLayer Video layer ID.
 * @param[in] s32VoChn Video channel ID.
 * @param[in] bClrAll Whether to clear all frame in the channel buffer.
 *
 * @retval 0 Success
 * @retval Non 0 Failure，For details, see the error code description.
 *
 * @remarks Null.
 *
 * @attention Null.
 */
IMP_S32 IMP_VO_ClearChnBuffer(IMP_S32 s32VoLayer,IMP_S32 s32VoChn,IMP_BOOL bClrAll);

/**
 * @fn IMP_VO_GetChnFrame(IMP_S32 s32VoLayer,IMP_S32 s32VoChn,FRAME_INFO_S **pstFrame)
 *
 * Get frame of the video channel.
 *
 * @param[in] s32VoLayer Video layer ID.
 * @param[in] s32VoChn Video channel ID.
 * @param[out] pstFrame The pointer of frame.
 *
 * @retval 0 Success
 * @retval Non 0 Failure，For details, see the error code description.
 *
 * @remarks Null.
 *
 * @attention Null.
 */
IMP_S32 IMP_VO_GetChnFrame(IMP_S32 s32VoLayer,IMP_S32 s32VoChn,FRAME_INFO_S **pstFrame);

/**
 * @fn IMP_VO_QueryChnDisplayFrame(IMP_S32 s32VoLayer,IMP_S32 s32VoChn,FRAME_INFO_S **pstFrame)
 *
 * Query the displaying frame of channel
 *
 * @param[in] s32VoLayer Video layer ID.
 * @param[in] s32VoChn Video channel ID.
 * @param[out] pstFrame The pointer of frame.
 *
 * @retval 0 Success
 * @retval Non 0 Failure，For details, see the error code description.
 *
 * @remarks Null.
 *
 * @attention Null.
 */
IMP_S32 IMP_VO_QueryChnDisplayFrame(IMP_S32 s32VoLayer,IMP_S32 s32VoChn,FRAME_INFO_S **pstFrame);

/**
 * @fn IMP_S32 IMP_VO_ReleaseChnFrame(IMP_S32 s32VoLayer,IMP_S32 s32VoChn,FRAME_INFO_S *pstFrame)
 *
 * Release frame of the video channel.
 *
 * @param[in] s32VoLayer Video layer ID.
 * @param[in] s32VoChn Video channel ID.
 * @param[in] pstFrame The pointer of frame.
 *
 * @retval 0 Success
 * @retval Non 0 Failure，For details, see the error code description.
 *
 * @remarks Null.
 *
 * @attention Null.
 */
IMP_S32 IMP_VO_ReleaseChnFrame(IMP_S32 s32VoLayer,IMP_S32 s32VoChn,FRAME_INFO_S *pstFrame);

/**
 * @fn IMP_VO_GetChnPts(IMP_S32 s32VoLayer,IMP_S32 s32VoChn,IMP_U64 *u64Pts)
 *
 * Get the timestamp of the current channel display frame
 *
 * @param[in] s32VoLayer Video layer ID.
 * @param[in] s32VoChn Video channel ID.
 * @param[in] u64Pts The timestamp of the current channel display frame.
 *
 * @retval 0 Success
 * @retval Non 0 Failure，For details, see the error code description.
 *
 * @remarks Null.
 *
 * @attention Null.
 */
IMP_S32 IMP_VO_GetChnPts(IMP_S32 s32VoLayer,IMP_S32 s32VoChn,IMP_U64 *u64Pts);

/**
 * The structure of video layer brightness contrast saturation chroma algorithm.
 */
typedef struct{
    IMP_U8		u8Brightness;
    IMP_U8		u8Contrast;
    IMP_U8		u8Saturation;
    IMP_U8		u8Hue;
}VO_BCSH_S;

/**
 * @fn IMP_S32 IMP_VO_EnableBcsh(IMP_S32 s32VoLayer)
 *
 * Enable brightness contrast saturation hue algorithm of the video layer.
 *
 * @param[in] s32VoLayer Video layer ID.
 *
 * @retval 0 Success
 * @retval Non 0 Failure，For details, see the error code description.
 *
 * @remarks Only HD Video Layer 0 has this feature.
 *
 * @attention Ensure that the video output module and video layer are enabled before use.
 */
IMP_S32 IMP_VO_EnableBcsh(IMP_S32 s32VoLayer);

/**
 * @fn IMP_S32 IMP_VO_EnableBcsh(IMP_S32 s32VoLayer)
 *
 * Disable brightness contrast saturation hue algorithm of the video layer.
 *
 * @param[in] s32VoLayer Video layer ID.
 *
 * @retval 0 Success
 * @retval Non 0 Failure，For details, see the error code description.
 *
 * @remarks Null.
 *
 * @attention Null.
 */
IMP_S32 IMP_VO_DisableBcsh(IMP_S32 s32VoLayer);

/**
 * @fn IMP_S32 IMP_VO_SetVideoLayerBcsh(IMP_S32 s32VoLayer,const VO_BCSH_S *pstBcsh)
 *
 * Config brightness contrast saturation hue algorithm of the video layer.
 *
 * @param[in] s32VoLayer Video layer ID.
 * @param[in] pstBcsh The pointer of brightness contrast saturation hue algorithm.
 *
 * @retval 0 Success
 * @retval Non 0 Failure，For details, see the error code description.
 *
 * @remarks Null.
 *
 * @attention Enable brightness contrast saturation hue algorithm first.
 */
IMP_S32 IMP_VO_SetVideoLayerBcsh(IMP_S32 s32VoLayer,const VO_BCSH_S *pstBcsh);

/**
 * @fn IMP_S32 IMP_VO_GetVideoLayerBcsh(IMP_S32 s32VoLayer,VO_BCSH_S *pstBcsh)
 *
 * Get brightness contrast saturation hue algorithm of the video layer.
 *
 * @param[in] s32VoLayer Video layer ID.
 *
 * @retval 0 Success
 * @retval Non 0 Failure，For details, see the error code description.
 *
 * @remarks Null.
 *
 * @attention Null.
 */
IMP_S32 IMP_VO_GetVideoLayerBcsh(IMP_S32 s32VoLayer,VO_BCSH_S *pstBcsh);

/**
 * @fn IMP_S32 IMP_VO_EnablePeak(IMP_S32 s32VoLayer)
 *
 * Enable peak algorithm of the video layer.
 *
 * @param[in] s32VoLayer Video layer ID.
 *
 * @retval 0 Success
 * @retval Non 0 Failure，For details, see the error code description.
 *
 * @remarks Only HD Video Layer 0 has this feature.
 *
 * @attention Ensure that the video output module and video layer are enabled before use.
 */
IMP_S32 IMP_VO_EnablePeak(IMP_S32 s32VoLayer);

/**
 * @fn IMP_S32 IMP_VO_DisablePeak(IMP_S32 s32VoLayer)
 *
 * Disable peak algorithm of the video layer.
 *
 * @param[in] s32VoLayer Video layer ID.
 *
 * @retval 0 Success
 * @retval Non 0 Failure，For details, see the error code description.
 *
 * @remarks Null.
 *
 * @attention Null.
 */
IMP_S32 IMP_VO_DisablePeak(IMP_S32 s32VoLayer);

/**
 * @fn IMP_S32 IMP_VO_SetVideoLayerPeak(IMP_S32 s32VoLayer,const IMP_U8 u8PeakStrength)
 *
 * Set peak strength of the video layer.
 *
 * @param[in] s32VoLayer Video layer ID.
 * @param[in] u8PeakStrength The peak strength.
 *
 * @retval 0 Success
 * @retval Non 0 Failure，For details, see the error code description.
 *
 * @remarks Null.
 *
 * @attention Enable peak algorithm first.
 */
IMP_S32 IMP_VO_SetVideoLayerPeak(IMP_S32 s32VoLayer,const IMP_U8 u8PeakStrength);

/**
 * @fn IMP_S32 IMP_VO_GetVideoLayerPeak(IMP_S32 s32VoLayer,IMP_U8 *pu8PeakStrength)
 *
 * Get peak strength of the video layer.
 *
 * @param[in] s32VoLayer Video layer ID.
 * @param[in] pu8PeakStrength The pointer of peak strength.
 *
 * @retval 0 Success
 * @retval Non 0 Failure，For details, see the error code description.
 *
 * @remarks Null.
 *
 * @attention Enable peak algorithm first.
 */
IMP_S32 IMP_VO_GetVideoLayerPeak(IMP_S32 s32VoLayer,IMP_U8 *pu8PeakStrength);

/**
 * @fn IMP_S32 IMP_VO_SetAttrBegin(IMP_VOID);
 *
 * Set the properties of the channel on the video layer to start.
 *
 * @param Null.
 *
 * @retval 0 Success
 * @retval Non 0 Failure，For details, see the error code description.
 *
 * @remarks Null.
 *
 * @attention Null.
 */
IMP_S32 IMP_VO_SetAttrBegin(IMP_VOID);

/**
 * @fn IMP_S32 IMP_VO_SetAttrEnd(IMP_VOID)
 *
 * Set the properties of the channel on the video layer to end.
 *
 * @param Null.
 *
 * @retval 0 Success
 * @retval Non 0 Failure，For details, see the error code description.
 *
 * @remarks Null.
 *
 * @attention Null.
 */
IMP_S32 IMP_VO_SetAttrEnd(IMP_VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
