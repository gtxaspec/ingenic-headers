/*
 * IMP Two Dimension Engine header file.
 *
 * Copyright (C) 2021 Ingenic Semiconductor Co.,Ltd
 */
#ifndef __IMP_TDE_H__
#define __IMP_TDE_H__

#include <imp/imp_common.h>

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

/**
 * @file
 * TDE API Header file
 */

/**
 * Task handle
 */
typedef IMP_S32 TDE_HANDLE;

/**
 * Operator Attribute structure
 */
typedef enum IMP_TDE_OPT_TYPE
{
	TDE_OPT_MIXER_1 = 0,
	TDE_OPT_MIXER_2,
	TDE_OPT_QUICKCOPY,
	TDE_OPT_QUICKFILL,
	TDE_OPT_RESIZE,
	TDE_OPT_OVERTURN,
	TDE_OPT_MIRROR,
	TDE_OPT_CLIP,
	TDE_OPT_CSC,
	TDE_OPT_ROP,
	TDE_OPT_BLEND,
	TDE_OPT_COLORKEY,
	TDE_OPT_ROP_WITHMASK,
	TDE_OPT_BLEND_WITHMASK,
	TDE_OPT_BUTT
} TDE_OPT_TYPE_E;

/**
 * Supported pixel formats
 */
typedef enum IMP_TDE_PIXFMT {
	TDE_PIXFMT_RGB444 = 0,
	TDE_PIXFMT_BGR444,
	TDE_PIXFMT_RGB555,
	TDE_PIXFMT_BGR555,
	TDE_PIXFMT_RGB565,
	TDE_PIXFMT_BGR565,
	TDE_PIXFMT_RGB888,
	TDE_PIXFMT_BGR888,
	TDE_PIXFMT_ARGB4444,
	TDE_PIXFMT_ABGR4444,
	TDE_PIXFMT_RGBA4444,
	TDE_PIXFMT_BGRA4444,
	TDE_PIXFMT_ARGB1555,
	TDE_PIXFMT_ABGR1555,
	TDE_PIXFMT_RGBA1555,
	TDE_PIXFMT_BGRA1555,
	TDE_PIXFMT_ARGB8565,
	TDE_PIXFMT_ABGR8565,
	TDE_PIXFMT_RGBA8565,
	TDE_PIXFMT_BGRA8565,
	TDE_PIXFMT_ARGB8888,
	TDE_PIXFMT_ABGR8888,
	TDE_PIXFMT_RGBA8888,
	TDE_PIXFMT_BGRA8888,
	TDE_PIXFMT_RABG8888,
	TDE_PIXFMT_NV12,
	TDE_PIXFMT_NV21,
	TDE_PIXFMT_NV16,
	TDE_PIXFMT_NV61,
	TDE_PIXFMT_A1,
	TDE_PIXFMT_BUTT
} TDE_PIXFMT_E;

/**
 * Function Enable structure
 */
typedef struct IMP_TDE_OPERATE_ENABLE
{
	IMP_BOOL bQuickCopy;
	IMP_BOOL bQuickFill;
	IMP_BOOL bResize;
	IMP_BOOL bOverturn;
	IMP_BOOL bMirror;
	IMP_BOOL bClip;
	IMP_BOOL bCsc;
	IMP_BOOL bColorkey;
	IMP_BOOL bRop;
	IMP_BOOL bBlend;
} TDE_OPERATE_ENABLE_S;

/**
 * Overlay logical operation attribute
 */
typedef enum IMP_TDE_ALUCMD
{
	TDE_ALUCMD_NONE = 0,
	TDE_ALUCMD_BLEND,
	TDE_ALUCMD_ROP,
	TDE_ALUCMD_BUTT
} TDE_ALUCMD_E;

/**
 * Cliping operation attribute
 */
typedef enum IMP_CLIPMODE
{
	TDE_CLIPMODE_OUTSIDE = 0,	/* clip outside */
	TDE_CLIPMODE_INSIDE,		/* clip inside*/
	TDE_CLIPMODE_BUTT
} TDE_CLIPMODE_E;

/**
 * ROP attribute
 */
typedef enum IMP_TDE_ROP_CODE
{
	TDE_ROP_BLACK = 0,	/* Blackness */
	TDE_ROP_NOTMERGEPEN,	/* ~(S2+S1) */
	TDE_ROP_MASKNOTPEN,	/* ~S2&S1 */
	TDE_ROP_NOTCOPYPEN, 	/* ~S2 */
	TDE_ROP_MASKPENNOT, 	/* S2&~S1 */
	TDE_ROP_NOT, 		/* ~S1 */
	TDE_ROP_XORPEN, 	/* S2^S1 */
	TDE_ROP_NOTMASKPEN, 	/* ~(S2&S1) */
	TDE_ROP_MASKPEN, 	/* S2&S1 */
	TDE_ROP_NOTXORPEN, 	/* ~(S2^S1) */
	TDE_ROP_NOP, 		/* S1 */
	TDE_ROP_MERGENOTPEN, 	/* ~S2+S1 */
	TDE_ROP_COPYPEN, 	/* S2 */
	TDE_ROP_MERGEPENNOT, 	/* S2+~S1 */
	TDE_ROP_MERGEPEN, 	/* S2+S1 */
	TDE_ROP_WHITE, 		/* Whiteness */
	TDE_ROP_BUTT
} TDE_ROP_CODE_E;

/**
 * Colorkey mode attribute
 */
typedef enum IMP_TDE_COLORKEY_MODE
{
	TDE_COLORKEY_MODE_NONE = 0,
	TDE_COLORKEY_MODE_BACKGROUND,	/* 背景进行colorkey操作 */
	TDE_COLORKEY_MODE_FOREGROUND,	/* 前景进行colorkey操作 */
	TDE_COLORKEY_MODE_BUTT
} TDE_COLORKEY_MODE_E;

/**
 * key color properties of individual color components
 */
typedef struct IMP_TDE_COLORKEY_COMP
{
	IMP_U8 u8CompMin;
	IMP_U8 u8CompMax;
	IMP_U8 bCompOut;
	IMP_U8 bCompIgnore;
	IMP_U8 u8CompMask;
	IMP_U8 u8Reserved;
	IMP_U8 u8Reserved1;
	IMP_U8 u8Reserved2;
} TDE_COLORKEY_COMP_S;

/**
 * colorkey attribute
 */
typedef union IMP_TDE_COLORKEY
{
	struct
	{
		TDE_COLORKEY_COMP_S stAlpha;
		TDE_COLORKEY_COMP_S stRed;
		TDE_COLORKEY_COMP_S stGreen;
		TDE_COLORKEY_COMP_S stBlue;
	} stCkARGB;
	struct
	{
		TDE_COLORKEY_COMP_S stAlpha;
		TDE_COLORKEY_COMP_S stY;
		TDE_COLORKEY_COMP_S stCb;
		TDE_COLORKEY_COMP_S stCr;
	} stCkYCbCr;
} TDE_COLORKEY_U;

/**
 * mirror attribute
 */
typedef enum IMP_TDE_MIRROR
{
	TDE_MIRROR_NONE = 0,
	TDE_MIRROR_VERTICAL,
	TDE_MIRROR_BUTT
} TDE_MIRROR_E;

/**
 * alpha source of the output image
 */
typedef enum IMP_TDE_OUTALPHA_FROM
{
	TDE_OUTALPHA_FROM_BACKGROUND = 0,
	TDE_OUTALPHA_FROM_FOREGROUND,
	TDE_OUTALPHA_FROM_GLOBALALPHA,
	TDE_OUTALPHA_FROM_BUTT
} TDE_OUTALPHA_FROM_E;

/**
 * aloha mode attribute
 */
typedef enum IMP_TDE_BLEND_MODE
{
	TDE_BLEND_ZERO = 0x0,
	TDE_BLEND_ONE,
	TDE_BLEND_SRC2COLOR,
	TDE_BLEND_INVSRC2COLOR,
	TDE_BLEND_SRC2ALPHA,
	TDE_BLEND_INVSRC2ALPHA,
	TDE_BLEND_SRC1COLOR,
	TDE_BLEND_INVSRC1COLOR,
	TDE_BLEND_SRC1ALPHA,
	TDE_BLEND_INVSRC1ALPHA,
	TDE_BLEND_SRC2ALPHASAT,
	TDE_BLEND_BUTT
} TDE_BLEND_MODE_E;

/**
 * Alpha mux computing command
 */
typedef enum IMP_TDE_BLENDCMD
{
	TDE_BLENDCMD_NONE = 0x0,
	TDE_BLENDCMD_CLEAR,
	TDE_BLENDCMD_SRC,
	TDE_BLENDCMD_SRCOVER,
	TDE_BLENDCMD_DSTOVER,
	TDE_BLENDCMD_SRCIN,
	TDE_BLENDCMD_DSTIN,
	TDE_BLENDCMD_SRCOUT,
	TDE_BLENDCMD_DSTOUT,
	TDE_BLENDCMD_SRCATOP,
	TDE_BLENDCMD_DSTATOP,
	TDE_BLENDCMD_ADD,
	TDE_BLENDCMD_XOR,
	TDE_BLENDCMD_DST,
	TDE_BLENDCMD_CONFIG,
	TDE_BLENDCMD_BUTT
} TDE_BLENDCMD_E;

/**
 * Alpha mux operation structure
 */
typedef struct IMP_TDE_BLEND_OPT
{
	IMP_BOOL bGlobalAlphaEnable;
	IMP_BOOL bPixelAlphaEnable;
	IMP_BOOL bSrc1AlphaPremulti;
	IMP_BOOL bSrc2AlphaPremulti;
	TDE_BLENDCMD_E eBlendCmd;
	TDE_BLEND_MODE_E eSrc1BlendMode;
	TDE_BLEND_MODE_E eSrc2BlendMode;
} TDE_BLEND_OPT_S;

/**
 * CSC mode
 */
typedef enum IMP_TDE_CSCMODE {
	TDE_CSCMODE_BYPASS = 0,
	TDE_CSCMODE_RGBTOYUV,
	TDE_CSCMODE_YUVTORGB,
	TDE_CSCMODE_BUTT
} TDE_CSCMODE_E;

/**
 * CSC conversion parameter
 */
typedef struct IMP_TDE_CSC_PARAM {
	IMP_S16 s16Luma;
	IMP_S16 s16Chrom;
	IMP_S16 s16C00;
	IMP_S16 s16C01;
	IMP_S16 s16C10;
	IMP_S16 s16C11;
	IMP_S16 s16C20;
	IMP_S16 s16C21;
	IMP_S16 s16C02;
	IMP_S16 s16C12;
	IMP_S16 s16C22;
} TDE_CSCPARAM_S;

/**
 * CSC operation
 */
typedef struct IMP_TDE_CSC_OPT {
	IMP_BOOL bCscUserEnable;
	TDE_CSCMODE_E enCscMode;
	TDE_CSCPARAM_S stCscParam;
}TDE_CSC_OPT_S;

/**
 * Alpha1555 operation
 */
typedef enum IMP_TDE_ALPHA1555_MODE
{
	ALPHA1555_MODE_IN = 0,
	ALPHA1555_MODE_OUT,
	ALPHA1555_MODE_BUTT
} TDE_ALPHA1555_MODE_E;

/**
 * Alpha1555 mode structure
 */
typedef struct IMP_TDE_ALPHA1555
{
	TDE_ALPHA1555_MODE_E enMode;
	IMP_U8 u8Min;
	IMP_U8 u8Max;
} TDE_ALPHA1555_S;

/**
 * Alpha type
 */
typedef enum IMP_TDE_ALPHA_MODE
{
	ALPHA_MODE_ZERO = 0,
	ALPHA_MODE_PIXELALPHA,
	ALPHA_MODE_GLOBALALPHA,
	ALPHA_MODE_GLOBAL_X_PIXEL,
	ALPHA_MODE_BUTT
} TDE_ALPHA_MODE_E;

/**
 * surface layer definition
 */
typedef struct IMP_TDE_SURFACE
{
	IMP_U32 u32PhyAddr;
	IMP_U32 u32CbCrPhyAddr;
	TDE_PIXFMT_E enPixFmt;
	IMP_U16 u16Height;
	IMP_U16 u16Width;
	IMP_U16 u16Stride;
	IMP_U16 u16CbCrStride;
	TDE_ALPHA_MODE_E enAlphaMode;
	IMP_U8 u8GlobalAlpha;
	IMP_U8 u8Alpha0;
	IMP_U8 u8Alpha1;
	TDE_ALPHA1555_S stAlpha1555;	/* ARGB1555 alpha mode*/
} TDE_SURFACE_S;

/**
 * rect operation structure
 */
typedef struct IMP_TDE_RECT
{
	IMP_S32 s32Xpos;
	IMP_S32 s32Ypos;
	IMP_U32 u32Width;
	IMP_U32 u32Height;
} TDE_RECT_S;

/**
 * TDE operation structure
 */
typedef struct IMP_TDE_OPERATE
{
	TDE_OPT_TYPE_E enOptType;
	TDE_OPERATE_ENABLE_S stOptsEn;
	IMP_U32 u32FillData;
	TDE_CSC_OPT_S stCscOpt;
	TDE_RECT_S stClipRect;
	TDE_CLIPMODE_E enClipMode;
	TDE_MIRROR_E enMirror;
	TDE_COLORKEY_MODE_E enColorKeyMode;
	TDE_COLORKEY_U unColorKeyValue;
	TDE_ROP_CODE_E enRopCode_Color;
	TDE_ROP_CODE_E enRopCode_Alpha;
	TDE_BLEND_OPT_S stBlendOpt;
} TDE_OPERATE_S;

/**
 * @fn TDE_HANDLE IMP_TDE_BeginJob(IMP_U8 u8OptNum)
 *
 * Create TDE tasks
 *
 * @param[in] u8OptNum operation number
 *
 * @retval >0 success
 * @retval <0 failure
 *
 * @remarks null。
 *
 */
TDE_HANDLE IMP_TDE_BeginJob(IMP_U8 u8OptNum);

/**
 * @fn IMP_S32 IMP_TDE_CancelJob(TDE_HANDLE Handle)
 *
 * cancel the tde task
 *
 * @param[in] Handle TDE take handle
 *
 * @retval =0 success
 * @retval !=0 failure
 *
 * @remarks null。
 *
 */
IMP_S32 IMP_TDE_CancelJob(TDE_HANDLE Handle);

/**
 * @fn IMP_S32 IMP_TDE_QuickCopy(TDE_HANDLE Handle, TDE_SURFACE_S *pstSrc, TDE_RECT_S *pstSrcRect,
 * 		TDE_SURFACE_S *pstDst, TDE_RECT_S *pstDstRect);
 *
 * Adds a copy operation to a specified task
 *
 * @param[in] Handle task handle
 * @param[in] pstSrc srouce bitmap
 * @param[in] pstSrcRect source bitmap region
 * @param[in] pstDst destination bitmap
 * @param[in] pstDstRect destination bitmap region
 *
 * @retval =0 succsee
 * @retval !=0 failure
 *
 * @remarks null
 *
 */
IMP_S32 IMP_TDE_QuickCopy(TDE_HANDLE Handle, TDE_SURFACE_S *pstSrc, TDE_RECT_S *pstSrcRect,
		TDE_SURFACE_S *pstDst, TDE_RECT_S *pstDstRect);

/**
 * @fn IMP_S32 IMP_DMA_QuickCopy(IMP_U32 u32SrcPaddr,IMP_U32 u32DstPaddr,IMP_U32 u32Size);
 *
 * Adds a dma copy operation to a specified task
 *
 * @param[in] u32SrcPaddr source physics address
 * @param[in] u32DstPaddr destination physics address
 * @param[in] u32Size	size
 *
 * @retval =0 success
 * @retval !=0 failure
 *
 * @remarks null
 *
 */
IMP_S32 IMP_DMA_QuickCopy(IMP_U32 u32SrcPaddr,IMP_U32 u32DstPaddr,IMP_U32 u32Size);

/**
 * @fn IMP_S32 IMP_TDE_QuickFill(TDE_HANDLE Handle, TDE_SURFACE_S *pstSrc, TDE_RECT_S *pstSrcRect,
		TDE_SURFACE_S *pstDst, TDE_RECT_S *pstDstRect, IMP_U32 u32FillData);
 *
 * Adds a fill operation to a specified task
 *
 * @param[in] Handle task handle
 * @param[in] pstSrc srouce bitmap
 * @param[in] pstSrcRect source bitmap region
 * @param[in] pstDst destination bitmap
 * @param[in] pstDstRect destination bitmap region
 * @param[in] u32FillData fill data value
 *
 * @retval =0 success
 * @retval !=0 failure
 *
 * @remarks null
 *
 */
IMP_S32 IMP_TDE_QuickFill(TDE_HANDLE Handle, TDE_SURFACE_S *pstSrc, TDE_RECT_S *pstSrcRect,
		TDE_SURFACE_S *pstDst, TDE_RECT_S *pstDstRect, IMP_U32 u32FillData);

/**
 * @fn IMP_S32 IMP_TDE_Resize(TDE_HANDLE Handle, TDE_SURFACE_S *pstSrc, TDE_RECT_S *pstSrcRect,
		TDE_SURFACE_S *pstDst, TDE_RECT_S *pstDstRect);
 *
 * Adds a resize operation to a specified task
 *
 * @param[in] Handle task handle
 * @param[in] pstSrc srouce bitmap
 * @param[in] pstSrcRect source bitmap region
 * @param[in] pstDst destination bitmap
 * @param[in] pstDstRect destination bitmap region
 *
 * @retval =0 success
 * @retval !=0 failure
 *
 * @remarks null
 *
 */
IMP_S32 IMP_TDE_Resize(TDE_HANDLE Handle, TDE_SURFACE_S *pstSrc, TDE_RECT_S *pstSrcRect,
		TDE_SURFACE_S *pstDst, TDE_RECT_S *pstDstRect);

/**
 * @fn IMP_S32 IMP_TDE_Overturn(TDE_HANDLE Handle, TDE_SURFACE_S *pstSrc, TDE_RECT_S *pstSrcRect,
		TDE_SURFACE_S *pstDst, TDE_RECT_S *pstDstRect);
 *
 * Adds a overturn operation to a specified task
 *
 * @param[in] Handle task handle
 * @param[in] pstSrc srouce bitmap
 * @param[in] pstSrcRect source bitmap region
 * @param[in] pstDst destination bitmap
 * @param[in] pstDstRect destination bitmap region
 *
 * @retval =0 success
 * @retval !=0 failure
 *
 * @remarks null
 *
 */
IMP_S32 IMP_TDE_Overturn(TDE_HANDLE Handle, TDE_SURFACE_S *pstSrc, TDE_RECT_S *pstSrcRect,
		TDE_SURFACE_S *pstDst, TDE_RECT_S *pstDstRect);

/**
 * @fn IMP_S32 IMP_TDE_Clip(TDE_HANDLE Handle, TDE_SURFACE_S *pstSrc, TDE_RECT_S *pstSrcRect,
		TDE_SURFACE_S *pstDst, TDE_RECT_S *pstDstRect,
		TDE_OPERATE_S *pstOpt);
 *
 * Adds a clip operation to a specified task
 *
 * @param[in] Handle task handle
 * @param[in] pstSrc srouce bitmap
 * @param[in] pstSrcRect source bitmap region
 * @param[in] pstDst destination bitmap
 * @param[in] pstDstRect destination bitmap region
 * @param[in] pstOpt  operation attribute
 *
 * @retval =0 success
 * @retval !=0 failure
 *
 * @remarks null
 *
 */
IMP_S32 IMP_TDE_Clip(TDE_HANDLE Handle, TDE_SURFACE_S *pstForeGround, TDE_RECT_S *pstForeGroundRect,
		TDE_SURFACE_S *pstDst, TDE_RECT_S *pstDstRect,
		TDE_OPERATE_S *pstOpt);

/**
 * @fn IMP_S32 IMP_TDE_CSC(TDE_HANDLE Handle, TDE_SURFACE_S *pstSrc, TDE_RECT_S *pstSrcRect,
		TDE_SURFACE_S *pstDst, TDE_RECT_S *pstDstRect,
		TDE_OPERATE_S *pstOpt);
 *
 * Adds a csc operation to a specified task
 *
 * @param[in] Handle task handle
 * @param[in] pstSrc srouce bitmap
 * @param[in] pstSrcRect source bitmap region
 * @param[in] pstDst destination bitmap
 * @param[in] pstDstRect destination bitmap region
 * @param[in] pstOpt  operation attribute
 *
 * @retval =0 success
 * @retval !=0 failure
 *
 * @remarks null
 *
 */
IMP_S32 IMP_TDE_CSC(TDE_HANDLE Handle, TDE_SURFACE_S *pstForeGround, TDE_RECT_S *pstForeGroundRect,
		TDE_SURFACE_S *pstDst, TDE_RECT_S *pstDstRect,
		TDE_OPERATE_S *pstOpt);

/**
 * @fn IMP_S32 IMP_TDE_Mirror(TDE_HANDLE Handle, TDE_SURFACE_S *pstSrc, TDE_RECT_S *pstSrcRect,
		TDE_SURFACE_S *pstDst, TDE_RECT_S *pstDstRect);
 *
 * Adds a mirror operation to a specified task
 *
 * @param[in] Handle task handle
 * @param[in] pstSrc srouce bitmap
 * @param[in] pstSrcRect source bitmap region
 * @param[in] pstDst destination bitmap
 * @param[in] pstDstRect destination bitmap region
 * @param[in] pstOpt  operation attribute
 *
 * @retval =0 success
 * @retval !=0 failure
 *
 * @remarks null
 *
 */
IMP_S32 IMP_TDE_Mirror(TDE_HANDLE Handle, TDE_SURFACE_S *pstForeGround, TDE_RECT_S *pstForeGroundRect,
		TDE_SURFACE_S *pstDst, TDE_RECT_S *pstDstRect);

/**
 * @fn IMP_S32 IMP_TDE_Bitblit(TDE_HANDLE Handle, TDE_SURFACE_S *pstBackGround, TDE_RECT_S *pstBackGroundRect,
		TDE_SURFACE_S *pstForeGround, TDE_RECT_S *pstForeGroundRect,
		TDE_SURFACE_S *pstDst, TDE_RECT_S *pstDstRect,
		TDE_OPERATE_S *pstOpt);
 *
 * Adds a bitblit operation to a specified task
 *
 * @param[in] Handle 任务句柄
 * @param[in] pstBackGround
 * @param[in] pstBackGroudRect
 * @param[in] pstForeGround
 * @param[in] pstForeGroundRect
 * @param[in] pstDst
 * @param[in] pstDstRect
 * @param[in] pstOpt
 *
 * @retval =0 success
 * @retval !=0 failure
 *
 * @remarks null
 *
 */
IMP_S32 IMP_TDE_Bitblit(TDE_HANDLE Handle, TDE_SURFACE_S *pstBackGround, TDE_RECT_S *pstBackGroundRect,
		TDE_SURFACE_S *pstForeGround, TDE_RECT_S *pstForeGroundRect,
		TDE_SURFACE_S *pstDst, TDE_RECT_S *pstDstRect,
		TDE_OPERATE_S *pstOpt);

/**
 * @fn IMP_S32 IMP_TDE_BitmapMaskRop(TDE_HANDLE Handle, TDE_SURFACE_S *pstBackGround, TDE_RECT_S *pstBackGroundRect,
		TDE_SURFACE_S *pstForeGround, TDE_RECT_S *pstForeGroundRect,
		TDE_SURFACE_S *pstDst, TDE_RECT_S *pstDstRect,
		TDE_OPERATE_S *pstOpt);
 *
 * Adds a rop bitblit operation to a specified task
 *
 * @param[in] handle
 * @param[in] pstbackground
 * @param[in] pstbackgroudrect
 * @param[in] pstforeground
 * @param[in] pstforegroundrect
 * @param[in] pstdst
 * @param[in] pstdstrect
 * @param[in] pstopt
 *
 * @retval =0 success
 * @retval !=0 failure
 *
 * @remarks null
 *
 */
IMP_S32 IMP_TDE_BitmapMaskRop(TDE_HANDLE Handle, TDE_SURFACE_S *pstBackGround, TDE_RECT_S *pstBackGroundRect,
		TDE_SURFACE_S *pstForeGround, TDE_RECT_S *pstForeGroundRect,
		TDE_SURFACE_S *pstMask, TDE_RECT_S *pstMaskRect,
		TDE_SURFACE_S *pstDst, TDE_RECT_S *pstDstRect,
		TDE_OPERATE_S *pstOpt);

/**
 * @fn IMP_S32 IMP_TDE_BitmapMaskBlend(TDE_HANDLE Handle, TDE_SURFACE_S *pstBackGround, TDE_RECT_S *pstBackGroundRect,
		TDE_SURFACE_S *pstForeGround, TDE_RECT_S *pstForeGroundRect,
		TDE_SURFACE_S *pstDst, TDE_RECT_S *pstDstRect,
		TDE_OPERATE_S *pstOpt);
 *
 * Adds a blend bitblit operation to a specified task
 *
 * @param[in] handle
 * @param[in] pstbackground
 * @param[in] pstbackgroudrect
 * @param[in] pstforeground
 * @param[in] pstforegroundrect
 * @param[in] pstdst
 * @param[in] pstdstrect
 * @param[in] pstopt
 *
 * @retval =0 success
 * @retval !=0 failure
 *
 * @remarks null
 *
 */
IMP_S32 IMP_TDE_BitmapMaskBlend(TDE_HANDLE Handle, TDE_SURFACE_S *pstBackGround, TDE_RECT_S *pstBackGroundRect,
		TDE_SURFACE_S *pstForeGround, TDE_RECT_S *pstForeGroundRect,
		TDE_SURFACE_S *pstMask, TDE_RECT_S *pstMaskRect,
		TDE_SURFACE_S *pstDst, TDE_RECT_S *pstDstRect,
		TDE_OPERATE_S *pstOpt);

/**
 * @fn IMP_S32 IMP_TDE_EndJob(TDE_HANDLE Handle, IMP_BOOL bSync, IMP_BOOL bBlock, IMP_S32 s32TimeOut);
 *
 * commit an already create task
 *
 * @param[in] Handle
 * @param[in] bSync
 * @param[in] bBlock
 * @param[in] s32TimeOut
 *
 * @retval =0 success
 * @retval !=0 failure
 *
 * @remarks null
 *
 */
IMP_S32 IMP_TDE_EndJob(TDE_HANDLE Handle, IMP_BOOL bSync, IMP_BOOL bBlock, IMP_S32 s32TimeOut);

/**
 * @fn IMP_S32 IMP_TDE_WaitAllDone(IMP_VOID);
 *
 * wait for all task to complete
 *
 * @param[in] null
 *
 * @retval =0 success
 * @retval !=0 failure
 *
 * @remarks null
 *
 */
IMP_S32 IMP_TDE_WaitAllDone(IMP_VOID);

/**
 * @fn IMP_S32 IMP_TDE_WaitForDone(TDE_HANDLE Handle);
 *
 * wait for the specified task to complete
 *
 * @param[in] Handle
 *
 * @retval =0 success
 * @retval !=0 failure
 *
 * @remarks null
 *
 */
IMP_S32 IMP_TDE_WaitForDone(TDE_HANDLE Handle);



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
