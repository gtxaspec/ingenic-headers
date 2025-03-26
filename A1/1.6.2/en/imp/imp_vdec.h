/*
 * IMP VDEC func header file.
 *
 * Copyright (C) 2014 Ingenic Semiconductor Co.,Ltd
 */

#ifndef __IMP_VDEC_H__
#define __IMP_VDEC_H__

#include <stdint.h>
#include "imp/imp_common.h"
#include "imp/imp_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

/**
 * @file
 * IMP video decoding header file
 */

/**
 * The enumeration of stream sending methods(currently only support VIDEO_MODE_FRAME)
 */
typedef enum VIDEO_MODE_E {
	VIDEO_MODE_STREAM, /* send by stream */
	VIDEO_MODE_FRAME, /* send by frame */
	VIDEO_MODE_LOWLATENCY /* send by low latency mode */
} VIDEO_MODE_E;

/**
 * The structure of decoding device attribute
 */
typedef struct VDEC_DEV_ATTR_S {
	PAYLOAD_TYPE_E	enType; /* stream type */
	VIDEO_MODE_E	enMode; /* stream sending method */
	IMP_U32			u32PicWidth; /* width of picture */
	IMP_U32			u32PicHeight; /* height of picture */
	IMP_U32			u32StreamBufSize; /* stream buffer size(Byte) */
	IMP_U32			u32RefFrameNum; /* reference frame number */
} VDEC_DEV_ATTR_S;

/**
 * The enumeration of decoding mode(currently only support VIDEO_DEC_MODE_IP)
 */
typedef enum VDEC_DECODE_MODE_E {
	VIDEO_DEC_MODE_IPB, /* decode all IPB frames */
	VIDEO_DEC_MODE_IP, /* decode only IP frames */
	VIDEO_DEC_MODE_I, /* decode only I frames */
} VDEC_DECODE_MODE_E;

/**
 * The enumeration of decoding output order(currently only support VIDEO_OUTPUT_ORDER_DEC)
 */
typedef enum VDEC_OUTPUT_ORDER_E {
	VIDEO_OUTPUT_ORDER_DISP, /* display order */
	VIDEO_OUTPUT_ORDER_DEC /* decode order */
} VDEC_OUTPUT_ORDER_E;

/**
 * The structure of decoding device advanced parameter
 */
typedef struct VDEC_DEV_PARAM_S {
	VDEC_DECODE_MODE_E		enDecMode; /* decoding method */
	VDEC_OUTPUT_ORDER_E		enOutputOrder; /* output order */
	IMP_BOOL				bEnableRFC; /* enable reference frame compression */
} VDEC_DEV_PARAM_S;

/**
 * The structure of decoding channel attribute
 */
typedef struct VDEC_CHN_ATTR_S {
	PIXEL_FORMAT_E			enOutputFormat; /* output format */
	IMP_U32					u32OutputWidth; /* output picture width */
	IMP_U32					u32OutputHeight; /* output picture height */
	IMP_BOOL				bEnableCrop; /* enable cropping */
	IMP_U32					u32CropX; /* x coordinate of cropping area */
	IMP_U32                 u32CropY; /* y coordinate of cropping area */
	IMP_U32					u32CropWidth; /* cropping width */
	IMP_U32                 u32CropHeight; /* cropping height */
	IMP_U32					u32FrameBufCnt; /* frame buffer count */
} VDEC_CHN_ATTR_S;

/**
 * The structure of decoding channel cropping attribute
 */
typedef struct VDEC_CHN_CROP_ATTR_S {
	IMP_BOOL				bEnableCrop; /* enable cropping */
	IMP_U32					u32CropX; /* x coordinate of cropping area */
	IMP_U32                 u32CropY; /* y coordinate of cropping area */
	IMP_U32					u32CropWidth; /* cropping width */
	IMP_U32                 u32CropHeight; /* cropping height */
} VDEC_CHN_CROP_ATTR_S;

/**
 * The structure of decoding error information
 */
typedef struct VDEC_DECODE_ERROR_S {
	IMP_U32		u32FormatErr; /* unsupported stream type */
	IMP_U32		u32PicSizeErr; /* unsupported picture size */
	IMP_U32		u32StreamUnsprt; /* unsupported stream specifications */
	IMP_U32		u32PackErr; /* stream package error */
	IMP_U32		u32PrtNumErrSet; /* parameter set miss */
	IMP_U32		u32RefErr; /* no enough reference frames */
	IMP_U32     u32FormatErrSet; /* parameter set format error */
	IMP_U32     u32CountErrSet; /* too many parameter sets */
	IMP_U32		u32StreamSizeOver; /* stream size too large */
	IMP_U32		u32VdecStreamNotRelease; /* the stream not released for too long time */
} VDEC_DECODE_ERROR_S;

/**
 * The structure of decoding status
 */
typedef struct VDEC_DEV_STATUS_S {
	PAYLOAD_TYPE_E			enType; /* stream type */
	IMP_U32					u32LeftStreamBytes; /* remained stream size(Byte) */
	IMP_U32					u32LeftStreamFrames; /* remained frame counts(only valid in frame mode) */
	IMP_U32					u32LeftPics; /* number of pictures waiting to be outputted */
	IMP_BOOL				bStartRecvStream; /* had started recieving stream? */
	IMP_U32					u32RecvStreamFrames; /* recieved frame counts(only valid in frame mode) */
	IMP_U32					u32DecodeStreamFrames; /* decoded frame counts(only valid in frame mode) */
	VDEC_DECODE_ERROR_S		stVdecDecErr; /* decoding error information */
} VDEC_DEV_STATUS_S;

/**
 * The structure of decoding stream
 */
typedef struct VDEC_STREAM_S {
	IMP_U32		u32Len; /* stream lenght */
	IMP_U64		u64PTS; /* stream timestamp */
	IMP_BOOL	bEndOfFrame; /* end of a whole frame */
	IMP_BOOL	bEndOfStream; /* end of total stream */
	IMP_U8		*pu8Addr; /* stream address */
	IMP_BOOL	bDisplay; /* current stream display?(only valid in frame mode) */
} VDEC_STREAM_S;

/**
 * The enumeration of display mode
 */
typedef enum VIDEO_DISPLAY_MODE_E {
	VIDEO_DISPLAY_MODE_PREVIEW, /* preview mode */
	VIDEO_DISPLAY_MODE_PLAYBACK /* playback mode */
} VIDEO_DISPLAY_MODE_E;

/**
 * The structure of user data(currently not enabled)
 */
typedef struct VDEC_USERDATA_S {
	IMP_U64		u64PhyAddr; /* physical address of user data */
	IMP_U32		u32Len; /* user data lenght */
	IMP_BOOL	bValid; /* is valid? */
	IMP_U8*		pu8Addr; /* virtual address of user data */
} VDEC_USERDATA_S;

/**
 * The structure of decoding buffer
 */
typedef struct VDEC_BUFFER_PARAM_S {
	IMP_BOOL			bEnableZoom; /* enable zoom */
	IMP_BOOL			bEnableChn0; /* enable decoding channel 0 */
	IMP_BOOL			bEnableChn1; /* enable decoding channel 1 */
	VDEC_DEV_ATTR_S		stDevAttr; /* device attribute */
	VDEC_CHN_ATTR_S		stChn0Attr; /* channel0 attribute */
	VDEC_CHN_ATTR_S		stChn1Attr; /* channel1 attribute */
} VDEC_BUFFER_PARAM_S;

/**
 * The structure of software jpeg decoding
 */
typedef struct JPEGD_INSTANCE_S {
	IMP_U32			u32ImageWidth; /* image width */
	IMP_U32			u32ImageHeight; /* image height */
	PIXEL_FORMAT_E	enOutputFormat; /* output format,only support NV12、ARGB1555 */
	IMP_U32			u32Len; /* jpeg picture lenght */
	IMP_U8*			pu8SrcAddr; /* jpeg picture address */
	IMP_U8*			pu8DstAddr; /* output picture address */
	IMP_VOID*		priv; /* private data used internally */
} JPEGD_INSTANCE_S;

/**
 * @fn IMP_S32 IMP_VDEC_CreateDev(IMP_S32 s32DevId, const VDEC_DEV_ATTR_S *pstAttr)
 *
 * Create decoding device
 *
 * @param[in] s32DevId Device id,range:[0, @ref NR_MAX_VDEC_DEV - 1]
 * @param[in] pstAttr Pointer of decoding device attribute
 *
 * @retval 0 Success
 * @retval Non 0 Failure
 *
 * @remarks A device corresponds to one stream,and a device contains two channels.
 *
 * @attention Device id should not bigger than max device count.
 * @attention If a specific device has been created,return failure.
 */
IMP_S32 IMP_VDEC_CreateDev(IMP_S32 s32DevId, const VDEC_DEV_ATTR_S *pstAttr);

/**
 * @fn IMP_S32 IMP_VDEC_DestroyDev(IMP_S32 s32DevId)
 *
 * Destroy decoding device
 *
 * @param[in] s32DevId Device id,range:[0, @ref NR_MAX_VDEC_DEV - 1]
 *
 * @retval 0 Success
 * @retval Non 0 Failure
 *
 * @remarks Null.
 *
 * @attention When destroy device,channels belonging to the device must be destroyed and device must stop recieving stream.Otherwise, returr failure.
 * @attention If destroy a device that do not exist or have not been created,retrun failure.
 */
IMP_S32 IMP_VDEC_DestroyDev(IMP_S32 s32DevId);

/**
 * @fn IMP_S32 IMP_VDEC_GetDevAttr(IMP_S32 s32DevId, VDEC_DEV_ATTR_S *pstAttr)
 *
 * Get decoding device attribute
 *
 * @param[in] s32DevId Device id,range:[0, @ref NR_MAX_VDEC_DEV - 1]
 * @param[out] pstAttr Pointer of decoding device attribute
 *
 * @remarks Null.
 *
 * @retval 0 Success
 * @retval Non 0 Failure
 *
 * @attention Device must been created before getting device attribute.Otherwise,return failure.
 */
IMP_S32 IMP_VDEC_GetDevAttr(IMP_S32 s32DevId, VDEC_DEV_ATTR_S *pstAttr);

/**
 * @fn IMP_S32 IMP_VDEC_SetDevParam(IMP_S32 s32DevId, const VDEC_DEV_PARAM_S *pstParam)
 *
 * Set decoding device parameter
 *
 * @param[in] s32DevId Device id,range:[0, @ref NR_MAX_VDEC_DEV - 1]
 * @param[in] pstParam Pointer of decoding device parameter
 *
 * @retval 0 Success
 * @retval Non 0 Failure
 *
 * @remarks Null.
 *
 * @attention Device id should not bigger than max device count.
 * @attention If device has been created,return failure.
 */
IMP_S32 IMP_VDEC_SetDevParam(IMP_S32 s32DevId, const VDEC_DEV_PARAM_S *pstParam);

/**
 * @fn IMP_S32 IMP_VDEC_GetDevParam(IMP_S32 s32DevId, VDEC_DEV_PARAM_S *pstParam)
 *
 * Get decoding device parameter
 *
 * @param[in] s32DevId Device id,range:[0, @ref NR_MAX_VDEC_DEV - 1]
 * @param[in] pstParam Pointer of device parameter
 *
 * @retval 0 Success
 * @retval Non 0 Failure
 *
 * @remarks Null.
 *
 * @attention Device must been created before getting device parameter.Otherwise,return failure.
 */
IMP_S32 IMP_VDEC_GetDevParam(IMP_S32 s32DevId, VDEC_DEV_PARAM_S *pstParam);

/**
 * @fn IMP_S32 IMP_VDEC_SetChnAttr(IMP_S32 s32DevId, IMP_S32 s32ChnId, const VDEC_CHN_ATTR_S *pstAttr)
 *
 * Set decoding output channel attribute
 *
 * @param[in] s32DevId Device id,range:[0, @ref NR_MAX_VDEC_DEV - 1]
 * @param[in] s32ChnId Channel id,range:[0, @ref NR_MAX_VDEC_CHN - 1]
 * @param[in] pstAttr Pointer of decoding channel attribute
 *
 * @retval 0 Success
 * @retval Non 0 Failure
 *
 * @remarks A device has only two channels.Channel0 supports max 3840x2160,and channel1 supports max 1920x1080.
 *
 * @attention Setting channel attribute before enabling channel is allowed.
 * @attention Setting channel attribute dynamically during decoding is allowed.
 * @attention Decoding channel must be disabled if you want to set channel attribute.
 */
IMP_S32 IMP_VDEC_SetChnAttr(IMP_S32 s32DevId, IMP_S32 s32ChnId, const VDEC_CHN_ATTR_S *pstAttr);

/**
 * @fn IMP_S32 IMP_VDEC_GetChnAttr(IMP_S32 s32DevId, IMP_S32 s32ChnId, const VDEC_CHN_ATTR_S *pstAttr)
 *
 * Get decoding output channel attribute
 *
 * @param[in] s32DevId Device id,range:[0, @ref NR_MAX_VDEC_DEV - 1]
 * @param[in] s32ChnId Channel id,range:[0, @ref NR_MAX_VDEC_CHN - 1]
 * @param[out] pstAttr Pointer of decoding channel attribute
 *
 * @retval 0 Success
 * @retval Non 0 Failure
 *
 * @remarks Null.
 *
 * @attention Channel must been created before getting channel attribute.Otherwise,return failure.
 */
IMP_S32 IMP_VDEC_GetChnAttr(IMP_S32 s32DevId, IMP_S32 s32ChnId, VDEC_CHN_ATTR_S *pstAttr);

/**
 * @fn IMP_S32 IMP_VDEC_EnableChn(IMP_S32 s32DevId, IMP_S32 s32ChnId)
 *
 * Enable decoding output channel
 *
 * @param[in] s32DevId Device id,range:[0, @ref NR_MAX_VDEC_DEV - 1]
 * @param[in] s32ChnId Channel id,range:[0, @ref NR_MAX_VDEC_CHN - 1]
 *
 * @retval 0 Success
 * @retval Non 0 Failure
 *
 * @remarks Setting channel attribute before enabling channel is needed.
 *
 * @attention Channel must been created before getting channel attribute.Otherwise,return failure.
 * @attention It will return failure if there is no enough memory when enable channel.
 */
IMP_S32 IMP_VDEC_EnableChn(IMP_S32 s32DevId, IMP_S32 s32ChnId);

/**
 * @fn IMP_S32 IMP_VDEC_DisableChn(IMP_S32 s32DevId, IMP_S32 s32ChnId)
 *
 * Disable decoding output channel
 *
 * @param[in] s32DevId Device id,range:[0, @ref NR_MAX_VDEC_DEV - 1]
 * @param[in] s32ChnId Channel id,range:[0, @ref NR_MAX_VDEC_CHN - 1]
 *
 * @retval 0 Success
 * @retval Non 0 Failure
 *
 * @remarks Null.
 *
 * @attention Repeatedly disabling decoding channel returns success.
 */
IMP_S32 IMP_VDEC_DisableChn(IMP_S32 s32DevId, IMP_S32 s32ChnId);

/**
 * @fn IMP_S32 IMP_VDEC_QueryStatus(IMP_S32 s32DevId, VDEC_DEV_STATUS_S *pstStatus)
 *
 * Query decoding device status
 *
 * @param[in] s32DevId Device id,range:[0, @ref NR_MAX_VDEC_DEV - 1]
 * @param[in] pstStatus Pointer of device status
 *
 * @retval 0 Success
 * @retval Non 0 Faliure
 *
 * @remarks Null.
 *
 * @attention Null.
 */
IMP_S32 IMP_VDEC_QueryStatus(IMP_S32 s32DevId, VDEC_DEV_STATUS_S *pstStatus);

/**
 * @fn IMP_S32 IMP_VDEC_SetChnCropAttr(IMP_S32 s32DevId, IMP_S32 s32ChnId, const VDEC_CHN_CROP_ATTR_S *pstCropAttr);
 *
 * Set the cropping attribute of the decoding output channel
 *
 * @param[in] s32DevId Device id,range:[0, @ref NR_MAX_VDEC_DEV - 1]
 * @param[in] s32ChnId Channel id,range:[0, @ref NR_MAX_VDEC_CHN - 1]
 * @param[in] pstCropAttr Pointer of cropping attribute
 *
 * @retval 0 Success
 * @retval Non 0 Failure
 *
 * @remarks Null.
 *
 * @attention Channel must been enabled when dynamically modify cropping attributes.
 */
IMP_S32 IMP_VDEC_SetChnCropAttr(IMP_S32 s32DevId, IMP_S32 s32ChnId, const VDEC_CHN_CROP_ATTR_S *pstCropAttr);

/**
 * @fn IMP_S32 IMP_VDEC_StartRecvStream(IMP_S32 s32DevId)
 *
 * Decoding device starts to recieve stream
 *
 * @param[in] s32DevId Device id,range:[0, @ref NR_MAX_VDEC_DEV - 1]
 *
 * @retval 0 Success
 * @retval Non 0 Failure
 *
 * @remarks Null.
 *
 * @attention Device must been created before starting to recieve stream.Otherwise,return failure.
 */
IMP_S32 IMP_VDEC_StartRecvStream(IMP_S32 s32DevId);

/**
 * @fn IMP_S32 IMP_VDEC_StopRecvStream(IMP_S32 s32DevId)
 *
 * Decoding device stop recieving stream
 *
 * @param[in] s32DevId Device id,range:[0, @ref NR_MAX_VDEC_DEV - 1]
 *
 * @retval 0 Success
 * @retval Non 0 Failure
 *
 * @remarks Null.
 *
 * @attention Device must been created before getting device parameter.Otherwise,return failure.
 */
IMP_S32 IMP_VDEC_StopRecvStream(IMP_S32 s32DevId);

/**
 * @fn IMP_S32 IMP_VDEC_SendStream(IMP_S32 s32DevId, VDEC_STREAM_S *pstStream, IMP_S32 s32MilliSec)
 *
 * Send stream to decoding device
 *
 * @param[in] s32DevId Device id,range:[0, @ref NR_MAX_VDEC_DEV - 1]
 * @param[in] pstStream Pointer of stream data
 * @param[in] s32MilliSec sending methods
 *
 * @retval 0 Success
 * @retval Non 0 Failure
 *
 * @remarks Null.
 *
 * @attention Device must have been created and started reciving stream before sending stream.Otherwise,return failure.
 * @attention Stream must be sent according to the sending method.Otherwise,return failure.
 * @attention Send the bitstream in a non blocking way,and if the bitstream buffer is full, it will return IMP_EBUFFULL.
 * @attention Sending the stream in a timeout way,if the stream cannot be successfully sent after reaching the timeout time, it will return IMP_EBUFFULL.
 * @attention If the receiving stream is stopped during the sending process, the interface will return IMP_EPERM.
 * @attention The optional parameters for PTS in frame mode are as follows:
 * @attention    0:User does not perform frame rate control
 * @attention   -1:The image will not be displayed by the video output module(VO).
 * @attention	others:Video output module(VO) plays based on user set PTS.
 *
 */
IMP_S32 IMP_VDEC_SendStream(IMP_S32 s32DevId, VDEC_STREAM_S *pstStream, IMP_S32 s32MilliSec);

/**
 * @fn IMP_S32 IMP_VDEC_SetDepth(IMP_S32 s32DevId, IMP_S32 s32ChnId, IMP_U32 u32Depth, IMP_BOOL bCopy)
 *
 * Set the output queue depth for decoding output channel
 *
 * @param[in] s32DevId Device id,range:[0, @ref NR_MAX_VDEC_DEV - 1]
 * @param[in] s32ChnId Channel id,range:[0, @ref NR_MAX_VDEC_CHN - 1]
 * @param[in] u32Depth Decoding Channel Output Queue Depth
 * @param[in] bCopy Set the method for obtaining channel data whether alloc physical memory for NV12 frame copy or not
 *
 * @retval 0 Success
 * @retval Non 0 Failure
 *
 * @remarks Null.
 *
 * @attention Device must have been created and channel must have been enabled before setting queue depth.
 * @attention If using copy mode, it will consume system memory, but it will not occupy frame buffer and will not affect subsequent modules.
 * @attention If non copying is used, the frame buffer will be directly placed in the queue.
 * @attention If the cached frames are not returned in a timely manner, it will affect the subsequent modules.
 */
IMP_S32 IMP_VDEC_SetDepth(IMP_S32 s32DevId, IMP_S32 s32ChnId, IMP_U32 u32Depth, IMP_BOOL bCopy);

/**
 * @fn IMP_S32 IMP_VDEC_GetFrame(IMP_S32 s32DevId, IMP_S32 s32ChnId, FRAME_INFO_S *pstFrameInfo)
 *
 * Get a frame from the output queue for decoding output channel
 *
 * @param[in] s32DevId Device id,range:[0, @ref NR_MAX_VDEC_DEV - 1]
 * @param[in] s32ChnId Channel id,range:[0, @ref NR_MAX_VDEC_CHN - 1]
 * @param[in] pstFrameInfo Pointer of frame
 *
 * @retval 0 Success
 * @retval Non 0 Failure
 *
 * @remarks Null.
 *
 * @attention Device must have been created and channel must have been enabled before getting frame.
 * @attention If get no frames, retrun failure.
 */
IMP_S32 IMP_VDEC_GetFrame(IMP_S32 s32DevId, IMP_S32 s32ChnId, FRAME_INFO_S **pstFrameInfo);

/**
 * @fn IMP_S32 IMP_VDEC_ReleaseFrame(IMP_S32 s32DevId, IMP_S32 s32ChnId, FRAME_INFO_S *pstFrameInfo)
 *
 * Release a frame from the output queue for decoding output channel
 *
 * @param[in] s32DevId Device id,range:[0, @ref NR_MAX_VDEC_DEV - 1]
 * @param[in] s32ChnId Channel id,range:[0, @ref NR_MAX_VDEC_CHN - 1]
 * @param[in] pstFrameInfo Pointer of frame
 *
 * @retval 0 Success
 * @retval Non 0 Failure
 *
 * @remarks Null.
 *
 * @attention Device must have been created and channel must have been enabled before releasing frame.
 * @attention The incoming frame information does not match the frame information in the cache, and the release will fail with an error.
 */
IMP_S32 IMP_VDEC_ReleaseFrame(IMP_S32 s32DevId, IMP_S32 s32ChnId, FRAME_INFO_S *pstFrameInfo);

/**
 * @fn IMP_S32 IMP_VDEC_GetFd(IMP_S32 s32DevId, IMP_S32 s32ChnId)
 *
 * Get the file descriptor of the decoding output channel
 *
 * @param[in] s32DevId Device id,range:[0, @ref NR_MAX_VDEC_DEV - 1]
 * @param[in] s32ChnId Channel id,range:[0, @ref NR_MAX_VDEC_CHN - 1]
 *
 * @retval >=0 Success
 * @retval <0 Failure
 *
 * @remarks Null.
 *
 * @attention Device must have been created and channel must have been enabled before getting file descriptor.
 */
IMP_S32 IMP_VDEC_GetFd(IMP_S32 s32DevId, IMP_S32 s32ChnId);

/**
 * @fn IMP_S32 IMP_VDEC_SetUserPic(IMP_S32 s32DevId, const FRAME_INFO_S *pstUsrPic)
 *
 * Set user picture attribute(this interface is currently not enabled)
 *
 * @param[in] s32DevId Device号,取值范围:[0, @ref NR_MAX_VDEC_DEV - 1]
 * @param[in] pstUsrPic
 *
 * @retval 0 Success
 * @retval Non 0 Failure
 *
 * @remarks Null.
 *
 * @attention Null.
 */
IMP_S32 IMP_VDEC_SetUserPic(IMP_S32 s32DevId, const FRAME_INFO_S *pstUsrPic);

/**
 * @fn IMP_S32 IMP_VDEC_EnableUserPic(IMP_S32 s32DevId, IMP_BOOL bInstant)
 *
 * Enable user picture(this interface is currently not enabled)
 *
 * @param[in] s32DevId Device id,range:[0, @ref NR_MAX_VDEC_DEV - 1]
 * @param[in] bInstant User picture inserting method
 *
 * @retval 0 Success
 * @retval Non 0 Failure
 *
 * @remarks Null.
 *
 * @attention Null.
 */
IMP_S32 IMP_VDEC_EnableUserPic(IMP_S32 s32DevId, IMP_BOOL bInstant);

/**
 * @fn IMP_S32 IMP_VDEC_DisableUserPic(IMP_S32 s32DevId, IMP_BOOL bInstant)
 *
 * Disable user picture(this interface is currently not enabled)
 *
 * @param[in] s32DevId Device id,range:[0, @ref NR_MAX_VDEC_DEV - 1]
 *
 * @retval 0 Success
 * @retval Non 0 Failure
 *
 * @remarks Null.
 *
 * @attention Null.
 */
IMP_S32 IMP_VDEC_DisableUserPic(IMP_S32 s32DevId);

/**
 * @fn IMP_S32 IMP_VDEC_SetDisplayMode(IMP_S32 s32DevId, VIDEO_DISPLAY_MODE_E enDisplayMode)
 *
 * Set decoding device display mode
 *
 * @param[in] s32DevId Device id,range:[0, @ref NR_MAX_VDEC_DEV - 1]
 * @param[in] enDisplayMode Enumeration of display mode
 *
 * @retval 0 Success
 * @retval Non 0 Failure
 *
 * @remarks In preview mode, decoder gets output buffer in a non blocking way,
	and even if the subsequent module occupies all the output buffers, decoder can continue to achieve real-time preview effect.
 * @remarks In playback mode, decoder gets output buffer in a blocking way. If the subsequent module occupies all the output buffers,
	decoder will also stop until the output buffer is obtained
 *
 * @attention Device must have been created before setting display mode.
 */
IMP_S32 IMP_VDEC_SetDisplayMode(IMP_S32 s32DevId, VIDEO_DISPLAY_MODE_E enDisplayMode);

/**
 * @fn IMP_S32 IMP_VDEC_GetDisplayMode(IMP_S32 s32DevId, VIDEO_DISPLAY_MODE_E *penDisplayMode)
 *
 * Set decoding device display mode
 *
 * @param[in] s32DevId Device id,range:[0, @ref NR_MAX_VDEC_DEV - 1]
 * @param[in] penDisplayMode Pointer of display mode
 *
 * @retval 0 Success
 * @retval Non 0 Failure
 *
 * @remarks Null.
 *
 * @attention Device must have been created before getting display mode.
 */
IMP_S32 IMP_VDEC_GetDisplayMode(IMP_S32 s32DevId, VIDEO_DISPLAY_MODE_E *penDisplayMode);

/**
 * @fn IMP_S32 IMP_VDEC_GetUserData(IMP_S32 s32DevId, VDEC_USERDATA_S *pstUserData, IMP_S32 s32MilliSec)
 *
 * Get decoding device user data(this interface is currently not enabled)
 *
 * @param[in] s32DevId Device id,range:[0, @ref NR_MAX_VDEC_DEV - 1]
 * @param[out] pstUserData Pointer of user data
 * @param[in] s32MilliSec User data getting method
 *
 * @retval 0 Success
 * @retval Non 0 Failure
 *
 * @remarks User data is SEI information in the bitstream.
 *
 * @attention Device must have been created before getting user data.
 */
IMP_S32 IMP_VDEC_GetUserData(IMP_S32 s32DevId, VDEC_USERDATA_S *pstUserData, IMP_S32 s32MilliSec);

/**
 * @fn IMP_S32 IMP_VDEC_ReleaseUserData(IMP_S32 s32DevId, const VDEC_USERDATA_S* pstUserData)
 *
 * Release decoding device user data(this interface is currently not enabled)
 *
 * @param[in] s32DevId Device id,range:[0, @ref NR_MAX_VDEC_DEV - 1]
 * @param[in] pstUserData Pointer of user data
 *
 * @retval 0 Success
 * @retval Non 0 Failure
 *
 * @remarks Null.
 *
 * @attention Device must have been created before releasing user data.
 * @attention The incoming user data pointer must be consistent with that in the cache, otherwise it will fail to be released.
 */
IMP_S32 IMP_VDEC_ReleaseUserData(IMP_S32 s32DevId, const VDEC_USERDATA_S* pstUserData);

/**
 * @fn IMP_S32 IMP_VDEC_AttachVbPool(IMP_S32 s32DevId, IMP_U32 u32PoolId)
 *
 * Attach decoding device to a specific video buffer pool
 *
 * @param[in] s32DevId Device id,range:[0, @ref NR_MAX_VDEC_DEV - 1]
 * @param[in] u32PoolId Video buffer pool id
 *
 * @retval 0 Success
 * @retval Non 0 Failure
 *
 * @remarks Null.
 *
 * @attention The interface must be called before the decoding device is created.
 */
IMP_S32 IMP_VDEC_AttachVbPool(IMP_S32 s32DevId, IMP_U32 u32PoolId);

/**
 * @fn IMP_S32 IMP_VDEC_DetachVbPool(IMP_S32 s32DevId)
 *
 * Detach decoding device from a video buffer pool
 *
 * @param[in] s32DevId Device id,range:[0, @ref NR_MAX_VDEC_DEV - 1]
 *
 * @retval 0 Success
 * @retval Non 0 Failure
 *
 * @remarks Null.
 *
 * @attention The interface must be called after the decoding device is destroyed.
 */
IMP_S32 IMP_VDEC_DetachVbPool(IMP_S32 s32DevId);

/**
 * @fn IMP_S32 IMP_VDEC_GetBufferSize(VDEC_BUFFER_PARAM_S *pstBufferParam)
 *
 * Get the required memory size for decoding device
 *
 * @param[in] pstBufferParam Pointer of decoding buffer parameter
 *
 * @retval >0 Success
 * @retval <=0 Failure
 *
 * @remarks Null.
 *
 * @attention Null.
 */
IMP_S32 IMP_VDEC_GetBufferSize(VDEC_BUFFER_PARAM_S *pstBufferParam);

/**
 * @fn IMP_S32 IMP_VDEC_SetCacheTime(IMP_S32 s32DevId, IMP_U64 u64CacheTime)
 *
 * Set the cache duration, and the decoder will only start working after a certain cache time
 *
 * @param[in] s32DevId Device id,range:[0, @ref NR_MAX_VDEC_DEV - 1]
 * @param[in] u64CacheTime Cache time,us
 *
 * @retval =0 Success
 * @retval <0 Failure
 *
 * @remarks Null.
 *
 * @attention Cache time is only valid in preview mode.
 */
IMP_S32 IMP_VDEC_SetCacheTime(IMP_S32 s32DevId, IMP_U64 u64CacheTime);

/**
 * @fn IMP_S32 IMP_VDEC_SetQuickDecodeRate(IMP_S32 s32DevId, IMP_U32 u32Rate)
 *
 * Set decoder's fast decoding rate due to the accumulation of streams caused by network fluctuations
 *
 * @param[in] s32DevId Device id,range:[0, @ref NR_MAX_VDEC_DEV - 1]
 * @param[in] u32Rate Fast decoding rate,range:[0, 10]
 *
 * @retval =0 Success
 * @retval <0 Failure
 *
 * @remarks Null.
 *
 * @attention The rate of fast decoding only takes effect when preview mode is enabled and timestamp is enabled.
 * @attention U32Rate defaults to 0, which means fast decoding is not enabled; 1 indicates a 10% reduction in decoding time interval,
	and so on, until the backlog of frames caused by network latency is eliminated.
 */
IMP_S32 IMP_VDEC_SetQuickDecodeRate(IMP_S32 s32DevId, IMP_U32 u32Rate);

/**
 * @fn IMP_S32 IMP_VDEC_AttachCPU(IMP_U32 u32CPUNum)
 *
 * Set the CPU bound by the decoding thread
 *
 * @param[in] u32CPUNum CPU number,only CPU0 and CPU1 valid
 *
 * @retval =0 Success
 * @retval <0 Failure
 *
 * @remarks Null.
 *
 * @attention If this interface is not called, vdec thread is balanced between multiple CPUs.
 * @attention This interface must be called before IMP_System_Init.
 */
IMP_S32 IMP_VDEC_AttachCPU(IMP_U32 u32CPUNum);

/**
 * @fn IMP_S32 IMP_VDEC_EnablePtsCtrl(IMP_S32 s32DevId)
 *
 * Enable decoding PTS control
 *
 * @param[in] s32DevId Device id,range:[0, @ref NR_MAX_VDEC_DEV - 1]
 *
 * @retval =0 Success
 * @retval <0 Failure
 *
 * @remarks 无。
 *
 * @attention By default PTS function is disabled.
 * @attention PTS must be enabled before first stream package.
 * @attention PTS will be disabled after destroying decoding device.
 */
IMP_S32 IMP_VDEC_EnablePtsCtrl(IMP_S32 s32DevId);

/**
 * @fn IMP_S32 IMP_JPEGD_Init(JPEGD_INSTANCE_S *pstInstance)
 *
 * Init software jpeg decoding instance
 *
 * @param[in] pstInstance Pointer of jpeg decoding instance
 *
 * @retval =0 Success
 * @retval <0 Failure
 *
 * @remarks Null.
 *
 * @attention Null.
 */
IMP_S32 IMP_JPEGD_Init(JPEGD_INSTANCE_S *pstInstance);

/**
 * @fn IMP_S32 IMP_JPEGD_Decode(JPEGD_INSTANCE_S *pstInstance)
 *
 * Start software jpeg decoding
 *
 * @param[in] pstInstance Pointer of jpeg decoding instance
 *
 * @retval =0 Success
 * @retval <0 Failure
 *
 * @remarks Null.
 *
 * @attention Null.
 */
IMP_S32 IMP_JPEGD_Decode(JPEGD_INSTANCE_S *pstInstance);

/**
 * @fn IMP_S32 IMP_JPEGD_DeInit(JPEGD_INSTANCE_S *pstInstance)
 *
 * DeInit software jpeg decoding instance
 *
 * @param[in] pstInstance Pointer of jpeg decoding instance
 *
 * @retval =0 Success
 * @retval <0 Failure
 *
 * @remarks Null.
 *
 * @attention The instance during inverse initialization needs to be consistent with the instance during initialization.
 */
IMP_S32 IMP_JPEGD_DeInit(JPEGD_INSTANCE_S *pstInstance);

/**
 * @}
 */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __IMP_VDEC_H__ */
