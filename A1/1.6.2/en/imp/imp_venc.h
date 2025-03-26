/*
 * IMP Encoder func header file.
 *
 * Copyright (C) 2014 Ingenic Semiconductor Co.,Ltd
 */

#ifndef __IMP_VENC_H__
#define __IMP_VENC_H__

#include <stdint.h>
#include <stdio.h>
#include "imp_type.h"
#include "imp_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

/**
 * @file
 * IMP video encoding header file
 */

/**
 * The structure of stream package
 */
typedef struct {
	IMP_U32 u32PhyAddr;   /**< stream physical address */
	IMP_U32 u32VirAddr;   /**< stream virtual address */
	IMP_U32 u32Len;       /**< stream length */
	IMP_U64 u64Ts;        /**< timestamp,us */
	IMP_BOOL bFrameEnd;   /**< end of all frames */
} VENC_PACK_S;

/**
 * The structure of stream
 */
typedef struct {
	VENC_PACK_S *pack;       /**< stream package pointer */
	IMP_U32 u32PackCount;    /**< stream package count */
	IMP_U32 u32Seq;          /**< stream sequence number */
} VENC_STREAM_S;

/**
 * The structure of encoder crop attribute
 */
typedef struct {
	IMP_BOOL enCrop;
	IMP_U32 u32X;
	IMP_U32 u32Y;
	IMP_U32 u32W;
	IMP_U32 u32H;
} VENC_CROP_S;

/**
 * The structure of encoder attribute
 */
typedef struct {
	PAYLOAD_TYPE_E enType;    /**< encoding protocol */
	IMP_U32 u32BufSize;       /**< buffer size */
	IMP_U32 u32ProFile;       /**< encoding profile, 0: baseline; 1:MP; 2:HP */
	IMP_U32 u32PicWidth;      /**< input picture width */
	IMP_U32 u32PicHeight;     /**< input picture height */
	IMP_U32 u32OutPicWidth;   /**< output picture width */
	IMP_U32 u32OutPicHeight;  /**< output picture height */
	VENC_CROP_S stCrop;       /**< crop attribute */
} VENC_CHN_ATTR_S;

/**
 * The structure of encoding channel status
 */
typedef struct {
	IMP_U32 u32LeftStreamBytes;   /**< remained size(Byte) in stream buffer */
	IMP_U32 u32LeftStreamFrames;  /**< remained frame count int stream buffer */
	IMP_U32 u32CurPacks;          /**< stream package count of current frame */
	IMP_BOOL bWorkDone;           /**< channel working status, 0:not working; 1:working */
} VENC_CHN_STATUS_S;

/*
 * The structure of jpeg quantization table
 */
typedef struct {
    IMP_BOOL bUserQl;          /**< 0: use default table; 1:use custom table */
    IMP_U8 u8QmemTable[128];   /**< custom quantization table */
} VENC_JPEGQL_S;

/**
 * @fn IMP_S32 IMP_VENC_CreateChn(IMP_S32 s32Chn, VENC_CHN_ATTR_S *pstChnAttr)
 *
 * Create encoding channel
 *
 * @param[in] s32Chn Channel id,range: [0, NR_MAX_ENC_CHN - 1]
 * @param[in] pstChnAttr Pointer of channel attribute
 *
 * @retval 0 Success
 * @retval Non 0 Failure, return error code
 *
 * @remarks If pstChnAttr is NULL, return error code.
 */
IMP_S32 IMP_VENC_CreateChn(IMP_S32 s32Chn, VENC_CHN_ATTR_S *pstChnAttr);

/**
 * @fn IMP_S32 IMP_Encoder_DestroyChn(IMP_S32 s32Chn)
 *
 * Destroy encoding channel
 *
 * @param[in] s32Chn Channel id,range: [0, NR_MAX_ENC_CHN - 1]
 *
 * @retval 0 Success
 * @retval Non 0 Failure, return error code
 *
 * @remarks Channel must have been created before calling this interface.
 */
IMP_S32 IMP_VENC_DestroyChn(IMP_S32 s32Chn);

/**
 * @fn IMP_S32 IMP_VENC_GetChnAttr(IMP_S32 s32Chn, VENC_CHN_ATTR_S *pstChnAttr)
 *
 * Get encoding channel attribute
 *
 * @param[in] s32Chn Channel id,range: [0, NR_MAX_ENC_CHN - 1]
 * @param[in] pstChnAttr Pointer of channel attribute
 *
 * @retval 0 Success
 * @retval Non 0 Failure, return error code
 *
 * @remarks Channel must have been created before calling this interface.
 */
IMP_S32 IMP_VENC_GetChnAttr(IMP_S32 s32Chn, VENC_CHN_ATTR_S *pstChnAttr);

/**
 * @fn IMP_S32 IMP_VENC_StartRecvStream(IMP_S32 s32Chn)
 *
 * Start recieving picture
 *
 * @param[in] s32Chn Channel id,range: [0, NR_MAX_ENC_CHN - 1]
 *
 * @retval 0 Success
 * @retval Non 0 Failure, return error code
 *
 * @remarks Encoding only can start after starting recieving picture.
 * @remarks Channel must have been created before calling this interface.
 */
IMP_S32 IMP_VENC_StartRecvStream(IMP_S32 s32Chn);

/**
 * @fn IMP_S32 IMP_VENC_StopRecvStream(IMP_S32 s32Chn)
 *
 * Stop recieving picture
 *
 * @param[in] s32Chn Channel id,range: [0, NR_MAX_ENC_CHN - 1]
 *
 * @retval 0 Success
 * @retval Non 0 Failure, return error code
 *
 * @remarks This interface only stops recieving picture, but doesn't release stream buffer.
 * @remarks Channel must have been created before calling this interface.
 */
IMP_S32 IMP_VENC_StopRecvStream(IMP_S32 s32Chn);

/**
 * @fn IMP_S32 IMP_VENC_SendFrame(IMP_S32 s32Chn, FRAME_INFO_S *pstFrame, IMP_S64 s64MillSec)
 *
 * Send picture to encoder
 *
 * @param[in] s32Chn Channel id,range: [0, NR_MAX_ENC_CHN - 1]
 * @param[in] pstFrame Pointer of frame
 * @param[in] s64MillSec sending method, -1:block, 0:non block, >0:timeout
 *
 * @retval 0 Success
 * @retval Non 0 Failure, return error code
 *
 * @remarks If pstFrame is NULL, return error code.
 * @remarks Channel must have been created and started recieving picture before calling this interface.
 */
IMP_S32 IMP_VENC_SendFrame(IMP_S32 s32Chn, FRAME_INFO_S *pstFrame, IMP_S64 s64MillSec);

/**
 * @fn IMP_S32 IMP_VENC_Query(IMP_S32 s32Chn, VENC_CHN_STATUS_S *pstChnStat)
 *
 * Query encoding channel status
 *
 * @param[in] s32Chn Channel id,range: [0, NR_MAX_ENC_CHN - 1]
 * @param[out] pstChnStat Pointer of channel status
 *
 * @retval 0 Success
 * @retval Non 0 Failure, return error code
 *
 * @remarks Channel must have been created before calling this interface.
 */
IMP_S32 IMP_VENC_Query(IMP_S32 s32Chn, VENC_CHN_STATUS_S *pstChnStat);

/**
 * @fn IMP_S32 IMP_VENC_GetStream(IMP_S32 s32Chn, VENC_STREAM_S *pstStream, IMP_S64 s64MillSec)
 *
 * Get stream after encoding
 *
 * @param[in] s32Chn Channel id,range: [0, NR_MAX_ENC_CHN - 1]
 * @param[in] pstStream Pointer of stream
 * @param[in] s64MillSec getting method, -1:block, 0:non block, >0:timeout
 *
 * @retval 0 Success
 * @retval Non 0 Failure, return error code
 *
 * @remarks IMP_VENC_ReleaseStream and IMP_VENC_GetStream must use together.
 * @remarks If pstStream is NULL, return error code.
 * @remarks Channel must have been created before calling this interface.
 */
IMP_S32 IMP_VENC_GetStream(IMP_S32 s32Chn, VENC_STREAM_S *pstStream, IMP_S64 s64MillSec);

/**
 * @fn IMP_S32 IMP_VENC_ReleaseStream(IMP_S32 s32Chn, VENC_STREAM_S *pstStream)
 *
 * Release stream
 *
 * @param[in] s32Chn Channel id,range: [0, NR_MAX_ENC_CHN - 1]
 * @param[in] pstStream Pointer of stream
 *
 * @retval 0 Success
 * @retval Non 0 Failure, return error code
 *
 * @remarks IMP_VENC_ReleaseStream and IMP_VENC_GetStream must use together.
 * @remarks If pststream is NULL, return error code.
 * @remarks Channel must have been created before calling this interface.
 */
IMP_S32 IMP_VENC_ReleaseStream(IMP_S32 s32Chn, VENC_STREAM_S *pstStream);

/**
 * @fn IMP_S32 IMP_VENC_GetFd(IMP_S32 s32Chn)
 *
 * Get encoding channel file descriptor
 *
 * @param[in] s32Chn Channel id,range: [0, NR_MAX_ENC_CHN - 1]
 *
 * @retval >=0 Success, return file descriptor
 * @retval < 0 Failure
 *
 * @remarks Channel must have been created before calling this interface.
 */
IMP_S32 IMP_VENC_GetFd(IMP_S32 s32Chn);

/**
 * @fn IMP_S32 IMP_VENC_CloseFd(IMP_S32 s32Chn)
 *
 * Close encoding channel file descriptor
 *
 * @param[in] s32Chn Channel id,range: [0, NR_MAX_ENC_CHN - 1]
 *
 * @retval >=0 Success
 * @retval < 0 Failure
 *
 * @remarks Channel must have been created before calling this interface.
 */
IMP_S32 IMP_VENC_CloseFd(IMP_S32 s32Chn);

/**
 * @fn IMP_S32 IMP_VENC_GetBufferSize(VENC_CHN_ATTR_S *pstChnAttr)
 *
 * Get encoding channel buffer size
 *
 * @param[in] pstChnAttr Pointer of channel attribute
 *
 * @retval >=0 Success
 * @retval < 0 Failure
 *
 * @remarks Channel must have been created before calling this interface.
 */
IMP_S32 IMP_VENC_GetBufferSize(VENC_CHN_ATTR_S *pstChnAttr);

/**
 * @fn IMP_S32 IMP_VENC_AttachVbPool(IMP_S32 s32Chn, IMP_U32 u32PoolId)
 *
 * Attach encoding channel to a specific video buffer pool
 *
 * @param[in] s32Chn Channel id,range: [0, NR_MAX_ENC_CHN - 1]
 * @param[in] u32PoolId video buffer pool id
 *
 * @retval >=0 Success
 * @retval < 0 Failure
 *
 * @remarks Channel must have not been created before calling this interface.
 */
IMP_S32 IMP_VENC_AttachVbPool(IMP_S32 s32Chn, IMP_U32 u32PoolId);

/**
 * @fn IMP_S32 IMP_VENC_DetachVbPool(IMP_S32 s32Chn)
 *
 * Detach encoding channel from a video buffer pool
 *
 * @param[in] s32Chn Channel id,range: [0, NR_MAX_ENC_CHN - 1]
 *
 * @retval >=0 Success
 * @retval < 0 Failure
 *
 * @remarks Channel must have been created before calling this interface.
 */
IMP_S32 IMP_VENC_DetachVbPool(IMP_S32 s32Chn);

/**
 * @fn IMP_S32 IMP_VENC_SetJpegeQl(IMP_S32 s32Chn, const VENC_JPEGQL_S *pstJpegeQl)
 *
 * Set jpeg encoding quantization table
 *
 * @param[in] s32Chn Channel id,range: [0, NR_MAX_ENC_CHN - 1]
 * @param[in] pstJpegeQl Pointer of jpeg encoding quantization table, 128 Bytes.
 *
 * @retval 0 Success
 * @retval Non 0 Failure, return error code
 *
 * @remarks Channel must have been created before calling this interface.
 */
IMP_S32 IMP_VENC_SetJpegeQl(IMP_S32 s32Chn, const VENC_JPEGQL_S *pstJpegeQl);

/**
 * @fn IMP_S32 IMP_VENC_GetJpegeQl(IMP_S32 s32Chn, VENC_JPEGQL_S *pstJpegeQl)
 *
 * Get custom jpeg encoding quantization table
 *
 * @param[in] s32Chn Channel id, range: [0, NR_MAX_ENC_CHN - 1]
 * @param[out] pstJpegeQl Pointer of jpeg encoding quantization table
 *
 * @retval 0 Success
 * @retval Non 0 Failure, return error code
 *
 * @remarks Channel must have been created before calling this interface.
 */
IMP_S32 IMP_VENC_GetJpegeQl(IMP_S32 s32Chn, VENC_JPEGQL_S *pstJpegeQl);

/**
 * @fn IMP_S32 IMP_VENC_GetStreamCnt(IMP_S32 s32Chn, IMP_U32 *u32StreamCnt)
 *
 * Get jpeg encoding channel stream buffer count
 *
 * @param[in] s32Chn Channel id, range: [0, NR_MAX_ENC_CHN - 1]
 * @param[out] u32StreamCnt Stream buffer count
 *
 * @retval 0 Success
 * @retval Non 0 Failure, return error code
 *
 * @remarks Channel must have been created before calling this interface.
 */
IMP_S32 IMP_VENC_GetStreamCnt(IMP_S32 s32Chn, IMP_U32 *u32StreamCnt);

/*
 * @fn IMP_S32 IMP_VENC_CreateChnEXT(IMP_S32 s32Chn, VENC_CHN_ATTR_S *pstChnAttr, IMP_U32 u32StreamCnt)
 *
 * Expanding interface for creating encoding channel
 *
 * @param[in] s32Chn Channel id,range: [0, NR_MAX_ENC_CHN - 1]
 * @param[in] pstChnAttr Pointer of encoding channel attribute
 * @param[in] u32StreamCnt Stream buffer count, 0:default count; >0:custom count
 *
 * @retval 0 Success
 * @retval Non 0 Failure, return error code
 *
 * @remarks If pstChnAttr is NULL, return error code.
 */
IMP_S32 IMP_VENC_CreateChnEXT(IMP_S32 s32Chn, VENC_CHN_ATTR_S *pstChnAttr, IMP_U32 u32StreamCnt);
/**
 * @}
 */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __IMP_ENCODER_H__ */
