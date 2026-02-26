/*
 * IMP common data structure header file.
 *
 * Copyright (C) 2014 Ingenic Semiconductor Co.,Ltd
 */

#ifndef __IMP_COMMON_H__
#define __IMP_COMMON_H__

#include <stdint.h>
#include <pthread.h>
#include <stdio.h>
#include "imp_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

/**
 * @file
 * IMP Common header file
 */

/**
 * IMP Device ID enum definition
 */
typedef enum {
	MOD_ID_VI,		/**< Video intput */
	MOD_ID_VDEC,		/**< Decoder */
	MOD_ID_VENC,		/**< Encoder */
	MOD_ID_OSD,		/**< Image Overlay */
	MOD_ID_VO,		/**< Video output */
	MOD_ID_IVS,		/**< Algorithm */
	MOD_ID_FB,		/**< framebuffer */
	MOD_ID_TDE,		/**< Image 2D processing*/
	MOD_ID_RESERVED_START,
	MOD_ID_RESERVED_END = 15,
	NR_MAX_MODULES,
} MODULE_ID_E;

/**
 * IMP Image format definition.
 */
typedef enum {
	PIX_FMT_YUV420P,   /**< planar YUV 4:2:0, 12bpp, (1 Cr & Cb sample per 2x2 Y samples) */
	PIX_FMT_YUYV422,   /**< packed YUV 4:2:2, 16bpp, Y0 Cb Y1 Cr */
	PIX_FMT_UYVY422,   /**< packed YUV 4:2:2, 16bpp, Cb Y0 Cr Y1 */
	PIX_FMT_YUV422P,   /**< planar YUV 4:2:2, 16bpp, (1 Cr & Cb sample per 2x1 Y samples) */
	PIX_FMT_YUV444P,   /**< planar YUV 4:4:4, 24bpp, (1 Cr & Cb sample per 1x1 Y samples) */
	PIX_FMT_YUV410P,   /**< planar YUV 4:1:0,  9bpp, (1 Cr & Cb sample per 4x4 Y samples) */
	PIX_FMT_YUV411P,   /**< planar YUV 4:1:1, 12bpp, (1 Cr & Cb sample per 4x1 Y samples) */
	PIX_FMT_GRAY8,     /**<	   Y	    ,  8bpp */
	PIX_FMT_MONOWHITE, /**<	   Y	    ,  1bpp, 0 is white, 1 is black, in each byte pixels are ordered from the msb to the lsb */
	PIX_FMT_MONOBLACK, /**<	   Y	    ,  1bpp, 0 is black, 1 is white, in each byte pixels are ordered from the msb to the lsb */

	PIX_FMT_NV12,      /**< planar YUV 4:2:0, 12bpp, 1 plane for Y and 1 plane for the UV components, which are interleaved (first byte U and the following byte V) */
	PIX_FMT_NV21,      /**< as above, but U and V bytes are swapped */
	PIX_FMT_NV16,      /**< planar YUV 4:2:0, 12bpp, 1 plane for Y and 1 plane for the UV components, which are interleaved (first byte U and the following byte V) */
	PIX_FMT_NV61,      /**< as above, but U and V bytes are swapped */

	PIX_FMT_RGB24,     /**< packed RGB 8:8:8, 24bpp, RGBRGB... */
	PIX_FMT_BGR24,     /**< packed RGB 8:8:8, 24bpp, BGRBGR... */

	PIX_FMT_ARGB,      /**< packed ARGB 8:8:8:8, 32bpp, ARGBARGB... */
	PIX_FMT_RGBA,	   /**< packed RGBA 8:8:8:8, 32bpp, RGBARGBA... */
	PIX_FMT_ABGR,	   /**< packed ABGR 8:8:8:8, 32bpp, ABGRABGR... */
	PIX_FMT_BGRA,	   /**< packed BGRA 8:8:8:8, 32bpp, BGRABGRA... */

	PIX_FMT_RGB565BE,  /**< packed RGB 5:6:5, 16bpp, (msb)	  5R 6G 5B(lsb), big-endian */
	PIX_FMT_RGB565LE,  /**< packed RGB 5:6:5, 16bpp, (msb)	  5R 6G 5B(lsb), little-endian */
	PIX_FMT_RGB555BE,  /**< packed RGB 5:5:5, 16bpp, (msb)1A 5R 5G 5B(lsb), big-endian, most significant bit to 0 */
	PIX_FMT_RGB555LE,  /**< packed RGB 5:5:5, 16bpp, (msb)1A 5R 5G 5B(lsb), little-endian, most significant bit to 0 */

	PIX_FMT_BAYER_BGGR8,    /**< bayer, BGBG..(odd line), GRGR..(even line), 8-bit samples */
	PIX_FMT_BAYER_RGGB8,    /**< bayer, RGRG..(odd line), GBGB..(even line), 8-bit samples */
	PIX_FMT_BAYER_GBRG8,    /**< bayer, GBGB..(odd line), RGRG..(even line), 8-bit samples */
	PIX_FMT_BAYER_GRBG8,    /**< bayer, GRGR..(odd line), BGBG..(even line), 8-bit samples */

	PIX_FMT_RAW,

	PIX_FMT_HSV,

	PIX_FMT_NB,
	PIX_FMT_YUV422,
	PIX_FMT_YVU422,
	PIX_FMT_UVY422,
	PIX_FMT_VUY422,
	PIX_FMT_RAW8,
	PIX_FMT_RAW16,
} PIXEL_FORMAT_E;

/**
 * IMPCell structure definition.
 */
typedef struct {
	MODULE_ID_E		enModId;		/**< Mode ID */
	IMP_U32			u32DevId;		/**< Device ID */
	IMP_U32			u32ChnId;		/**< Channel ID */
} IMP_CELL_S;

/**
 * IMP Frame information structure.
 */
typedef struct {
	IMP_S32 s32Index;			/**< Frame index */

	IMP_U32 u32Width;			/**< Frame width */
	IMP_U32 u32Height;			/**< Frame heigth */
	IMP_U32 u32Stride;			/**< Frame stride */
	PIXEL_FORMAT_E stPixfmt;	/**< Frame pixel format */
	IMP_U32 u32Size;			/**< Frame size */

	IMP_U32 u32PhyAddr;			/**< Frame physics address */
	IMP_U32 u32VirAddr;			/**< Frame virtual address */

	IMP_U64 u64FrameTimeStamp;		/**< Frame timestamp */
	IMP_U64 u64SysTimeStamp;	/**< System timestamp */
	IMP_VOID*  Priv;			/* Private point */
} FRAME_INFO_S;

/**
 * IMP Definition of Private Data for Frame Images.
 */
typedef struct {
    IMP_U32 u32PhyAddr[2];          /**< The Y and UV physical addresses of the frame 0:Y 1:UV*/
    IMP_U32 u32VirAddr[2];          /**< The Y and UV virtual addresses of frames 0:Y 1:UV*/
	IMP_U32 y_stride;
	IMP_U32 uv_stride;
} FRAME_PRIV_S;


/**
 * IMP Frame time information.
 */
typedef struct {
	IMP_U64 u64Ts;						/**< time */
	IMP_U64 u64Minus;						/**< lower bound */
	IMP_U64 u64Plus;						/**< upper bound */
} FRAME_TIMESTAMP_S;

/**
 * Codec protected type
 */
typedef enum {
	PT_JPEG,					/**< JPEG */
	PT_H264,					/**< H264 */
	PT_H265,					/**< H265 */
} PAYLOAD_TYPE_E;

/**
 * IMP Point coordinate information.
 */
typedef struct {
	IMP_S32		s32X;			/**< abscissa */
	IMP_S32		s32Y;			/**< ordinate */
} IMP_POINT_S;

/**
 * IMP Rect region information.
 */
typedef struct {
	IMP_S32		s32X;			/** abscissa */
	IMP_S32		s32Y;			/**< ordinate */
	IMP_U32		u32Width;		/**< width */
	IMP_U32		u32Height;		/**< heigth */
} IMP_RECT_S;

typedef struct {
	IMP_U32		u32Width;		/**< width */
	IMP_U32		u32Height;		/**< heigth */
}IMP_SIZE_S;

typedef struct {
	IMP_POINT_S		stP0;		/**< the endpoint of a straight line p0 */
	IMP_POINT_S		stP1;		/**< the endpoint of a straight line p0*/
}IMP_LINE_S;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __IMP_COMMON_H__ */
