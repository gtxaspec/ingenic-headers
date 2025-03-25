/*
 * IMP Framebuf header file.
 *
 * Copyright (C) 2022 Ingenic Semiconductor Co.,Ltd
 */
#ifndef __IMP_FRAMEBUF_H__
#define __IMP_FRAMEBUF_H__

#include <imp/imp_common.h>
#include <linux/fb.h>

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */


/* *
 * The enumeration of frambuffer pixel format
 * */
typedef enum {
	FB_LAYER_FORMAT_ARGB8888 = 0x00,
	FB_LAYER_FORMAT_ARBG8888 = 0x01,
	FB_LAYER_FORMAT_AGBR8888 = 0x02,
	FB_LAYER_FORMAT_AGRB8888 = 0x03,
	FB_LAYER_FORMAT_ABGR8888 = 0x04,
	FB_LAYER_FORMAT_ABRG8888 = 0x05,
	FB_LAYER_FORMAT_RGBA8888 = 0x06,
	FB_LAYER_FORMAT_RBGA8888 = 0x07,
	FB_LAYER_FORMAT_GBRA8888 = 0x08,
	FB_LAYER_FORMAT_GRBA8888 = 0x09,
	FB_LAYER_FORMAT_BGRA8888 = 0x0a,
	FB_LAYER_FORMAT_BRGA8888 = 0x0b,
	FB_LAYER_FORMAT_ARGB1555 = 0x0c,
	FB_LAYER_FORMAT_ARBG1555 = 0x0d,
	FB_LAYER_FORMAT_AGBR1555 = 0x0e,
	FB_LAYER_FORMAT_AGRB1555 = 0x0f,
	FB_LAYER_FORMAT_ABGR1555 = 0x10,
	FB_LAYER_FORMAT_ABRG1555 = 0x11,
	FB_LAYER_FORMAT_RGBA5551 = 0x12,
	FB_LAYER_FORMAT_RBGA5551 = 0x13,
	FB_LAYER_FORMAT_GBRA5551 = 0x14,
	FB_LAYER_FORMAT_GRBA5551 = 0x15,
	FB_LAYER_FORMAT_BGRA5551 = 0x16,
	FB_LAYER_FORMAT_BRGA5551 = 0x17,
	FB_LAYER_FORMAT_NV12 = 0x20,
	FB_LAYER_FORMAT_NV21 = 0x24,
	FB_LAYER_FORMAT_NV16 = 0x21,
	FB_LAYER_FORMAT_NV61 = 0x25,
}FB_LAYER_PIXFMT_E;

/* *
 * The enumeration of frambuffer alpha mode.
 * */
typedef enum {
	ALPHA_GLOBAL,		/* global alpha */
	ALPHA_PIXEL,		/* pixel alpha */
	ALPHA_FUSIONS,		/* fusions alpha */
}FB_ALPHA_MODE_E;

/* *
 * The structure of framebuffer colorkey.
 * */
typedef struct {
	IMP_S32 s32KeyEnable;
	IMP_U32 u32KeyColor;
}FB_COLORKEY_S;

/* *
 * The structure of framebuffer alpha.
 * */
typedef struct {
	FB_ALPHA_MODE_E	enAlphaMode; /* alpha mode */
	IMP_U8 u8Alpha0; /* alpha0, Used when the alpha channel occupies only 1 bit*/
	IMP_U8 u8Alpha1; /* alpha1, Used when the alpha channel occupies only 1 bit */
	IMP_U8 u8GlobalAlpha; /* the value of alpha */
}FB_ALPHA_S;

 /* *
  * The structure of framebuffer surface.
  * */
typedef struct {
	IMP_U32 u32Width;
	IMP_U32 u32Height;
	IMP_U32 u32Stride;
	FB_LAYER_PIXFMT_E enPixfmt;
}FB_SURFACE_S;

/* *
  * The structure of framebuffer point.
 * */
typedef struct {
	IMP_S32 s32X; /* horizontal position */
	IMP_S32 s32Y; /* vertical position*/
}FB_POINT_S;

#define IOC_TYPE_JZFB       		'F'
/* Set Colorkey*/
#define FBIOGET_COLORKEY		_IOR(IOC_TYPE_JZFB, 10, FB_COLORKEY_S)
/* Get Colorkey*/
#define FBIOPUT_COLORKEY		_IOW(IOC_TYPE_JZFB, 11, FB_COLORKEY_S)
/* Set Alpha*/
#define FBIOGET_ALPHA			_IOR(IOC_TYPE_JZFB, 12, FB_ALPHA_S)
/* Get Alpha*/
#define FBIOPUT_ALPHA			_IOW(IOC_TYPE_JZFB, 13, FB_ALPHA_S)
/* Set coordinates of framebuffer*/
#define FBIOPUT_SCREEN_ORIGIN   _IOW(IOC_TYPE_JZFB, 15, FB_POINT_S)
/* Get coordinates of framebuffer*/
#define FBIOGET_SCREEN_ORIGIN   _IOR(IOC_TYPE_JZFB, 14, FB_POINT_S)
/* Set display state of framebuffer*/
#define FBIOPUT_SHOW			_IOW(IOC_TYPE_JZFB, 21, IMP_S32)
/* Get display state of framebuffer*/
#define FBIOGET_SHOW			_IOR(IOC_TYPE_JZFB, 22, IMP_S32)
/* Set Surface of framebuffer*/
#define FBIOPUT_SCREEN_SIZE		_IOW(IOC_TYPE_JZFB, 23, FB_SURFACE_S)
/* Get Surface of framebuffer*/
#define FBIOGET_SCREEN_SIZE		_IOR(IOC_TYPE_JZFB, 24, FB_SURFACE_S)
/* Set compress state of framebuffer*/
#define FBIOPUT_COMPRESSION		_IOW(IOC_TYPE_JZFB, 25, IMP_S32)
/* Get compress state of framebuffer*/
#define FBIOGET_COMPRESSION		_IOR(IOC_TYPE_JZFB, 26, IMP_S32)

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
