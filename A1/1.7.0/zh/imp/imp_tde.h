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
 * TDE接口头文件
 */

/**
 * 任务句柄
 */
typedef IMP_S32 TDE_HANDLE;

/**
 * 操作属性结构体
 */
typedef enum{
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
 * 支持的像素格式
 */
typedef enum{
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
 * 功能使能结构体
 */
typedef struct{
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
 * 叠加逻辑运算属性
 */
typedef enum{
	TDE_ALUCMD_NONE = 0,
	TDE_ALUCMD_BLEND, /* 支持图像按比例叠加，支持手动配置前景和背景使用不同叠加因子 */
	TDE_ALUCMD_ROP,
	TDE_ALUCMD_BUTT
} TDE_ALUCMD_E;

/**
 * 裁剪操作类型
 */
typedef enum{
	TDE_CLIPMODE_OUTSIDE = 0,	/* 输出clip区域外的图像 */
	TDE_CLIPMODE_INSIDE,		/* 输出clip区域内的图像 */
	TDE_CLIPMODE_BUTT
} TDE_CLIPMODE_E;

/**
 * TDE支持的ROP参数
 */
typedef enum{
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
 * Colorkey模式属性
 */
typedef enum{
	TDE_COLORKEY_MODE_NONE = 0,
	TDE_COLORKEY_MODE_BACKGROUND,	/* 背景进行colorkey操作 */
	TDE_COLORKEY_MODE_FOREGROUND,	/* 前景进行colorkey操作 */
	TDE_COLORKEY_MODE_BUTT
} TDE_COLORKEY_MODE_E;

/**
 * 单个颜色分量的关键色属性
 */
typedef struct{
	IMP_U8 u8CompMin;	/* 分量最小值 */
	IMP_U8 u8CompMax;	/* 分量最大值 */
	IMP_U8 bCompOut;	/* 分量关键色在范围内或范围外 */
	IMP_U8 bCompIgnore;	/* 分量是否忽略 */
	IMP_U8 u8CompMask;	/* 分量掩码 */
	IMP_U8 u8Reserved;
	IMP_U8 u8Reserved1;
	IMP_U8 u8Reserved2;
} TDE_COLORKEY_COMP_S;

/**
 * 关键色属性
 */
typedef union{
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
 * TDE 图像镜像属性
 */
typedef enum{
	TDE_MIRROR_NONE = 0, 	/* 输出图像不进行镜像操作 */
	TDE_MIRROR_VERTICAL,	/* 输出图像垂直镜像 */
	TDE_MIRROR_BUTT
} TDE_MIRROR_E;

/**
 * 输出图像alpha来源类型
 */
typedef enum{
	TDE_OUTALPHA_FROM_BACKGROUND = 0,	/* 输入图像的alpha来源于背景图 */
	TDE_OUTALPHA_FROM_FOREGROUND, 		/* 输入图像的alpha来源于前景图 */
	TDE_OUTALPHA_FROM_GLOBALALPHA, 		/* 输入图像的alpha来源于全局alpha */
	TDE_OUTALPHA_FROM_BUTT
} TDE_OUTALPHA_FROM_E;

/**
 * 自定义alpha混合模式
 */
typedef enum{
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
 * Alpha混合命令，用于计算alpha混合以后的像素值
 */
typedef enum{
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
 * Alpha混合操作选项
 */
typedef struct{
	IMP_BOOL bGlobalAlphaEnable; 	/* 是否使能全局alpha */
	IMP_BOOL bPixelAlphaEnable; 	/* 是否使能像素alpha */
	IMP_BOOL bSrc1AlphaPremulti;	/* 是否使能src1 alpha premultir */
	IMP_BOOL bSrc2AlphaPremulti; 	/* 是否使能src2 alpha premulti */
	TDE_BLENDCMD_E eBlendCmd;
	TDE_BLEND_MODE_E eSrc1BlendMode;
	TDE_BLEND_MODE_E eSrc2BlendMode;
} TDE_BLEND_OPT_S;

/**
 * TDE CSC格式转换参数选项
 */
typedef enum{
	TDE_CSCMODE_BYPASS = 0,
	TDE_CSCMODE_RGBTOYUV,
	TDE_CSCMODE_YUVTORGB,
	TDE_CSCMODE_BUTT
} TDE_CSCMODE_E;

/**
 * CSC 格式转换参数
 */
typedef struct{
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
 * CSC 操作属性
 */
typedef struct{
	IMP_BOOL bCscUserEnable;
	TDE_CSCMODE_E enCscMode;
	TDE_CSCPARAM_S stCscParam;
}TDE_CSC_OPT_S;

/**
 * Alpha1555 模式选项
 */
typedef enum{
	ALPHA1555_MODE_IN = 0,
	ALPHA1555_MODE_OUT,
	ALPHA1555_MODE_BUTT
} TDE_ALPHA1555_MODE_E;

/**
 * Alpha1555 操作结构体
 */
typedef struct{
	TDE_ALPHA1555_MODE_E enMode;
	IMP_U8 u8Min;
	IMP_U8 u8Max;
} TDE_ALPHA1555_S;

/**
 * Alpha 模式类型
 */
typedef enum{
	ALPHA_MODE_ZERO = 0,
	ALPHA_MODE_PIXELALPHA,
	ALPHA_MODE_GLOBALALPHA,
	ALPHA_MODE_GLOBAL_X_PIXEL,
	ALPHA_MODE_BUTT
} TDE_ALPHA_MODE_E;

/**
 * 多图层定义结构体
 */
typedef struct{
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
	TDE_ALPHA1555_S stAlpha1555;	/* ARGB1555 alpha mode选择和配置 */
} TDE_SURFACE_S;

/**
 * 操作区域结构体
 */
typedef struct{
	IMP_S32 s32Xpos;
	IMP_S32 s32Ypos;
	IMP_U32 u32Width;
	IMP_U32 u32Height;
} TDE_RECT_S;

/**
 * TDE操作属性结构体
 */
typedef struct{
	TDE_OPT_TYPE_E enOptType;		/* 操作的类型 */
	TDE_OPERATE_ENABLE_S stOptsEn;		/* 操作需要使能的模块 */
	IMP_U32 u32FillData;			/* 填充值 */
	TDE_CSC_OPT_S stCscOpt;			/* Csc 操作属性 */
	TDE_RECT_S stClipRect;			/* clip区域定义 */
	TDE_CLIPMODE_E enClipMode;		/* 区域内或者区域外clip */
	TDE_MIRROR_E enMirror;			/* 镜像类型 */
	TDE_COLORKEY_MODE_E enColorKeyMode;	/* colorkey方式 */
	TDE_COLORKEY_U unColorKeyValue;		/* colorkey设置值 */
	TDE_ROP_CODE_E enRopCode_Color;		/* 颜色空间ROP类型 IIP_OSD_INFO, 0x0108 寄存器mode2 控制 */
	TDE_ROP_CODE_E enRopCode_Alpha;		/* Alpha的ROP类型IIP_OSD_INFO, 0x0108 寄存器mode1 控制 */
	TDE_BLEND_OPT_S stBlendOpt;
} TDE_OPERATE_S;

/**
 * @fn TDE_HANDLE IMP_TDE_BeginJob(IMP_U8 u8OptNum)
 *
 * 创建TDE任务
 *
 * @param[in] u8OptNum 创建的TDE任务个数
 *
 * @retval >0 成功
 * @retval <0 失败
 *
 * @remarks 无。
 *
 * @attention 在调用此接口之前必须先调用IMP_System_Init 初始化SDK。
 */
TDE_HANDLE IMP_TDE_BeginJob(IMP_U8 u8OptNum);

/**
 * @fn IMP_S32 IMP_TDE_CancelJob(TDE_HANDLE Handle)
 *
 * 取消TDE对应任务和已经成功加入到该任务中的所以操作
 *
 * @param[in] Handle TDE任务句柄
 *
 * @retval =0 成功
 * @retval !=0 失败
 *
 * @remarks 无。
 */
IMP_S32 IMP_TDE_CancelJob(TDE_HANDLE Handle);

/**
 * @fn IMP_S32 IMP_TDE_QuickCopy(TDE_HANDLE Handle, TDE_SURFACE_S *pstSrc, TDE_RECT_S *pstSrcRect,
 * 		TDE_SURFACE_S *pstDst, TDE_RECT_S *pstDstRect);
 *
 * 向指定任务中添加快速拷贝操作
 *
 * @param[in] Handle 任务句柄
 * @param[in] pstSrc 源位图
 * @param[in] pstSrcRect 源位图操作区域
 * @param[in] pstDst 目的位图
 * @param[in] pstDstRect 目的位图操作区域
 *
 * @retval =0 成功
 * @retval !=0 失败
 *
 * @remarks 无。
 */
IMP_S32 IMP_TDE_QuickCopy(TDE_HANDLE Handle, TDE_SURFACE_S *pstSrc, TDE_RECT_S *pstSrcRect,
		TDE_SURFACE_S *pstDst, TDE_RECT_S *pstDstRect);

/**
 * @fn IMP_S32 IMP_DMA_QuickCopy(IMP_U32 u32SrcPaddr,IMP_U32 u32DstPaddr,IMP_U32 u32Size)
 *
 * 通用DMA快速拷贝
 *
 * @param[in] u32SrcPaddr 源位图物理地址
 * @param[in] u32DstPaddr 目的位图物理地址
 * @param[in] u32Size	拷贝的数据大小
 *
 * @retval =0 成功
 * @retval !=0 失败
 *
 * @remarks 无。
 */
IMP_S32 IMP_DMA_QuickCopy(IMP_U32 u32SrcPaddr,IMP_U32 u32DstPaddr,IMP_U32 u32Size);

/**
 * @fn IMP_S32 IMP_TDE_QuickFill(TDE_HANDLE Handle, TDE_SURFACE_S *pstSrc, TDE_RECT_S *pstSrcRect,
		TDE_SURFACE_S *pstDst, TDE_RECT_S *pstDstRect, IMP_U32 u32FillData);
 *
 * 向指定任务中添加快速填充操作
 *
 * @param[in] Handle 任务句柄
 * @param[in] pstSrc 源位图
 * @param[in] pstSrcRect 源位图操作区域
 * @param[in] pstDst 目的位图
 * @param[in] pstDstRect 目的位图操作区域
 * @param[in] u32FillData 填充像素的值
 *
 * @retval =0 成功
 * @retval !=0 失败
 *
 * @remarks 无。
 */
IMP_S32 IMP_TDE_QuickFill(TDE_HANDLE Handle, TDE_SURFACE_S *pstSrc, TDE_RECT_S *pstSrcRect,
		TDE_SURFACE_S *pstDst, TDE_RECT_S *pstDstRect, IMP_U32 u32FillData);

/**
 * @fn IMP_S32 IMP_TDE_Resize(TDE_HANDLE Handle, TDE_SURFACE_S *pstSrc, TDE_RECT_S *pstSrcRect,
		TDE_SURFACE_S *pstDst, TDE_RECT_S *pstDstRect);
 *
 * 向指定任务中添加缩放操作
 *
 * @param[in] Handle 任务句柄
 * @param[in] pstSrc 源位图
 * @param[in] pstSrcRect 源位图操作区域
 * @param[in] pstDst 目的位图
 * @param[in] pstDstRect 目的位图操作区域
 *
 * @retval =0 成功
 * @retval !=0 失败
 *
 * @remarks 无。
 */
IMP_S32 IMP_TDE_Resize(TDE_HANDLE Handle, TDE_SURFACE_S *pstSrc, TDE_RECT_S *pstSrcRect,
		TDE_SURFACE_S *pstDst, TDE_RECT_S *pstDstRect);

/**
 * @fn IMP_S32 IMP_TDE_Overturn(TDE_HANDLE Handle, TDE_SURFACE_S *pstSrc, TDE_RECT_S *pstSrcRect,
		TDE_SURFACE_S *pstDst, TDE_RECT_S *pstDstRect);
 *
 * 向指定任务中添加翻转操作
 *
 * @param[in] Handle 任务句柄
 * @param[in] pstSrc 源位图
 * @param[in] pstSrcRect 源位图操作区域
 * @param[in] pstDst 目的位图
 * @param[in] pstDstRect 目的位图操作区域
 *
 * @retval =0 成功
 * @retval !=0 失败
 *
 * @remarks 无。
 */
IMP_S32 IMP_TDE_Overturn(TDE_HANDLE Handle, TDE_SURFACE_S *pstSrc, TDE_RECT_S *pstSrcRect,
		TDE_SURFACE_S *pstDst, TDE_RECT_S *pstDstRect);

/**
 * @fn IMP_S32 IMP_TDE_Clip(TDE_HANDLE Handle, TDE_SURFACE_S *pstSrc, TDE_RECT_S *pstSrcRect,
		TDE_SURFACE_S *pstDst, TDE_RECT_S *pstDstRect,
		TDE_OPERATE_S *pstOpt);
 *
 * 向指定任务中添加裁剪操作
 *
 * @param[in] Handle 任务句柄
 * @param[in] pstSrc 源位图
 * @param[in] pstSrcRect 源位图操作区域
 * @param[in] pstDst 目的位图
 * @param[in] pstDstRect 目的位图操作区域
 * @param[in] pstOpt 操作属性
 *
 * @retval =0 成功
 * @retval !=0 失败
 *
 * @remarks 无。
 */
IMP_S32 IMP_TDE_Clip(TDE_HANDLE Handle, TDE_SURFACE_S *pstForeGround, TDE_RECT_S *pstForeGroundRect,
		TDE_SURFACE_S *pstDst, TDE_RECT_S *pstDstRect,
		TDE_OPERATE_S *pstOpt);

/**
 * @fn IMP_S32 IMP_TDE_CSC(TDE_HANDLE Handle, TDE_SURFACE_S *pstSrc, TDE_RECT_S *pstSrcRect,
		TDE_SURFACE_S *pstDst, TDE_RECT_S *pstDstRect,
		TDE_OPERATE_S *pstOpt);
 *
 * 向指定任务中添加格式转换操作
 *
 * @param[in] Handle 任务句柄
 * @param[in] pstSrc 源位图
 * @param[in] pstSrcRect 源位图操作区域
 * @param[in] pstDst 目的位图
 * @param[in] pstDstRect 目的位图操作区域
 * @param[in] pstOpt 操作属性
 *
 * @retval =0 成功
 * @retval !=0 失败
 *
 * @remarks 无。
 */
IMP_S32 IMP_TDE_CSC(TDE_HANDLE Handle, TDE_SURFACE_S *pstForeGround, TDE_RECT_S *pstForeGroundRect,
		TDE_SURFACE_S *pstDst, TDE_RECT_S *pstDstRect,
		TDE_OPERATE_S *pstOpt);

/**
 * @fn IMP_S32 IMP_TDE_Mirror(TDE_HANDLE Handle, TDE_SURFACE_S *pstSrc, TDE_RECT_S *pstSrcRect,
		TDE_SURFACE_S *pstDst, TDE_RECT_S *pstDstRect);
 *
 * 向指定任务中添加镜像操作
 *
 * @param[in] Handle 任务句柄
 * @param[in] pstSrc 源位图
 * @param[in] pstSrcRect 源位图操作区域
 * @param[in] pstDst 目的位图
 * @param[in] pstDstRect 目的位图操作区域
 * @param[in] pstOpt 操作属性
 *
 * @retval =0 成功
 * @retval !=0 失败
 *
 * @remarks 无。
 */
IMP_S32 IMP_TDE_Mirror(TDE_HANDLE Handle, TDE_SURFACE_S *pstForeGround, TDE_RECT_S *pstForeGroundRect,
		TDE_SURFACE_S *pstDst, TDE_RECT_S *pstDstRect);

/**
 * @fn IMP_S32 IMP_TDE_Bitblit(TDE_HANDLE Handle, TDE_SURFACE_S *pstBackGround, TDE_RECT_S *pstBackGroundRect,
		TDE_SURFACE_S *pstForeGround, TDE_RECT_S *pstForeGroundRect,
		TDE_SURFACE_S *pstDst, TDE_RECT_S *pstDstRect,
		TDE_OPERATE_S *pstOpt);
 *
 * 向指定任务中添加位图的复合操作
 *
 * @param[in] Handle 任务句柄
 * @param[in] pstBackGround 背景位图
 * @param[in] pstBackGroudRect 背景位图操作区域
 * @param[in] pstForeGround 前景位图
 * @param[in] pstForeGroundRect 前景位图操作区域
 * @param[in] pstDst 目的位图
 * @param[in] pstDstRect 目的位图操作区域
 * @param[in] pstOpt 操作属性
 *
 * @retval =0 成功
 * @retval !=0 失败
 *
 * @remarks 无。
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
 * 向指定任务中添加对位图进行rop操作
 *
 * @param[in] Handle 任务句柄
 * @param[in] pstBackGround 背景位图
 * @param[in] pstBackGroudRect 背景位图操作区域
 * @param[in] pstForeGround 前景位图
 * @param[in] pstForeGroundRect 前景位图操作区域
 * @param[in] pstDst 目的位图
 * @param[in] pstDstRect 目的位图操作区域
 * @param[in] pstOpt 操作属性
 *
 * @retval =0 成功
 * @retval !=0 失败
 *
 * @remarks 无。
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
 * 向指定任务中添加对位图进行blend操作
 *
 * @param[in] Handle 任务句柄
 * @param[in] pstBackGround 背景位图
 * @param[in] pstBackGroudRect 背景位图操作区域
 * @param[in] pstForeGround 前景位图
 * @param[in] pstForeGroundRect 前景位图操作区域
 * @param[in] pstDst 目的位图
 * @param[in] pstDstRect 目的位图操作区域
 * @param[in] pstOpt 操作属性
 *
 * @retval =0 成功
 * @retval !=0 失败
 *
 * @remarks 无。
 */
IMP_S32 IMP_TDE_BitmapMaskBlend(TDE_HANDLE Handle, TDE_SURFACE_S *pstBackGround, TDE_RECT_S *pstBackGroundRect,
		TDE_SURFACE_S *pstForeGround, TDE_RECT_S *pstForeGroundRect,
		TDE_SURFACE_S *pstMask, TDE_RECT_S *pstMaskRect,
		TDE_SURFACE_S *pstDst, TDE_RECT_S *pstDstRect,
		TDE_OPERATE_S *pstOpt);

/**
 * @fn IMP_S32 IMP_TDE_EndJob(TDE_HANDLE Handle, IMP_BOOL bSync, IMP_BOOL bBlock, IMP_S32 s32TimeOut);
 *
 * 提交已经创建的TDE任务
 *
 * @param[in] Handle 任务句柄
 * @param[in] bSync 同步标志（没有使用）
 * @param[in] bBlock 阻塞标志（没有使用）
 * @param[in] s32TimeOut 超时时间（ms）
 *
 * @retval >0 成功
 * @retval <0 失败
 *
 * @remarks 无。
 */
IMP_S32 IMP_TDE_EndJob(TDE_HANDLE Handle, IMP_BOOL bSync, IMP_BOOL bBlock, IMP_S32 s32TimeOut);

/**
 * @fn IMP_S32 IMP_TDE_WaitAllDone(IMP_VOID);
 *
 * 等待TDE所以任务完成
 *
 * @param[in] null
 *
 * @retval >0 成功
 * @retval <0 失败
 *
 * @remarks 无。
 */
IMP_S32 IMP_TDE_WaitAllDone(IMP_VOID);

/**
 * @fn IMP_S32 IMP_TDE_WaitForDone(TDE_HANDLE Handle);
 *
 * 等待指定任务完成
 *
 * @param[in] Handle 任务句柄
 *
 * @retval >0 成功
 * @retval <0 失败
 *
 * @remarks 无。
 *
 */
IMP_S32 IMP_TDE_WaitForDone(TDE_HANDLE Handle);



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
