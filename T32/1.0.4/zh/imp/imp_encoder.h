/*
 * IMP Encoder func header file.
 *
 * Copyright (C) 2014 Ingenic Semiconductor Co.,Ltd
 */

#ifndef __IMP_ENCODER_H__
#define __IMP_ENCODER_H__

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

/**
 * @file
 * IMP视频编码头文件
 */

/**
 * @defgroup IMP_Encoder
 * @ingroup imp
 * @brief 视频编码（JPEG, H264, H265）模块，包含编码通道管理，编码参数设置等功能
 * @section enc_struct 1 模块结构
 * Encoder模块内部结构如下如：
 * @image html encoder_struct.jpg
 * 如上图所示，编码模块由若干个Group组成，每个Group由编码Channel组成。
 * 每个编码Channel附带一个输出码流缓冲区，这个缓冲区由多个buffer组成。
 * @section enc_channel 2 编码Channel
 * 一个编码Channel可以完成一种协议的编码, 每个Group可以添加2个编码channel。
 * @section enc_rc 3 码率控制
 * @subsection enc_cbr 3.1 CBR
 * CBR（Constent Bit Rate）恒定比特率，即在码率统计时间内编码码率恒定。
 * 以H.264 编码为例，用户可设置maxQp，minQp，bitrate等。
 * maxQp，minQp 用于控制图像的质量范围， bitrate 用于钳位码率统计时间内的平均编码码率。
 * 当编码码率大于恒定码率时，图像QP 会逐步向maxQp 调整，当编码码率远小于恒定码率时，图像QP 会逐步向minQp 调整。
 * 当图像QP 达到maxQp 时，QP 被钳位到最大值，bitrate 的钳位效果失效，编码码率有可能会超出bitrate。
 * 当图像QP 达到minQp 时，QP 被钳位到最小值，此时编码的码率已经达到最大值，而且图像质量最好。
 * @subsection enc_FixQP 3.2 FixQP
 * Fix Qp 固定Qp 值。在码率统计时间内，编码图像所有宏块Qp 值相同，采用用户设定的图像Qp值。
 * @{
 */

#define IMP_ENC_ROI_WIN_COUNT 16

#define IMP_ENC_AVC_PROFILE_IDC_BASELINE        66
#define IMP_ENC_AVC_PROFILE_IDC_MAIN            77
#define IMP_ENC_AVC_PROFILE_IDC_HIGH            100
#define IMP_ENC_HEVC_PROFILE_IDC_MAIN           1

/**
* 定义返回值
*/
enum
{
	IMP_OK_ENC_ALL 					= 0x0 , 		/* 运行正常 */
	/* Encoder */
	IMP_ERR_ENC_CHNID 				= 0x80040001,	/* 通道 ID 超出合法范围 */
	IMP_ERR_ENC_PARAM 				= 0x80040002,	/* 参数超出合法范围 */
	IMP_ERR_ENC_EXIST 				= 0x80040004,	/* 试图申请或者创建已经存在的设备、通道或者资源 */
	IMP_ERR_ENC_UNEXIST 			= 0x80040008,	/* 试图使用或者销毁不存在的设备、通道或者资源 */
	IMP_ERR_ENC_NULL_PTR 			= 0x80040010,	/* 函数参数中有空指针 */
	IMP_ERR_ENC_NOT_CONFIG 			= 0x80040020,	/* 使用前未配置 */
	IMP_ERR_ENC_NOT_SUPPORT 		= 0x80040040,	/* 不支持的参数或者功能 */
	IMP_ERR_ENC_PERM 				= 0x80040080,	/* 操作不允许 */
	IMP_ERR_ENC_NOMEM 				= 0x80040100,	/* 分配内存失败 */
	IMP_ERR_ENC_NOBUF 				= 0x80040200,	/* 分配缓冲区失败 */
	IMP_ERR_ENC_BUF_EMPTY 			= 0x80040400,	/* 缓冲区中无数据 */
	IMP_ERR_ENC_BUF_FULL 			= 0x80040800,	/* 缓冲区中数据满 */
	IMP_ERR_ENC_BUF_SIZE 			= 0x80041000,	/* 缓冲区空间不足 */
	IMP_ERR_ENC_SYS_NOTREADY 		= 0x80042000,	/* 系统没有初始化或没有加载相应模块 */
	IMP_ERR_ENC_OVERTIME 			= 0x80044000,	/* 等待超时 */
	IMP_ERR_ENC_RESOURCE_REQUEST 	= 0x80048000,	/* 资源创建、申请失败 */
};

/**
 * 定义编码Channel码流Profile
 */
typedef enum {
	IMP_ENC_PROFILE_AVC_BASELINE    = ((PT_H264 << 24) | (IMP_ENC_AVC_PROFILE_IDC_BASELINE)),
	IMP_ENC_PROFILE_AVC_MAIN        = ((PT_H264 << 24) | (IMP_ENC_AVC_PROFILE_IDC_MAIN)),
	IMP_ENC_PROFILE_AVC_HIGH        = ((PT_H264 << 24) | (IMP_ENC_AVC_PROFILE_IDC_HIGH)),
	IMP_ENC_PROFILE_HEVC_MAIN       = ((PT_H265 << 24) | (IMP_ENC_HEVC_PROFILE_IDC_MAIN)),
	IMP_ENC_PROFILE_JPEG            = (PT_JPEG << 24),
} IMPEncoderProfile;

/**
 * 定义编码Channel码率控制器模式
 */
typedef enum {
	ENC_RC_MODE_FIXQP               = 0,	/**< Fixqp 模式 */
	ENC_RC_MODE_CBR                 = 1,	/**< CBR 模式 */
	ENC_RC_MODE_VBR                 = 2,	/**< VBR 模式*/
	ENC_RC_MODE_SMART               = 3,	/**< Smart 模式*/
	ENC_RC_MODE_CVBR                = 4,	/**< CVBR 模式*/
	ENC_RC_MODE_AVBR                = 5,	/**< AVBR 模式*/
	ENC_RC_MODE_INV                 = 6,	/**< INV 模式 */
} IMPEncoderRcMode;

/**
 * 定义编码channel帧率结构体,frmRateNum和frmRateDen经过最大公约数整除后两者之间的最小公倍数不能超过64，最好在设置之前就被最大公约数整除
 */
typedef struct {
	uint32_t	frmRateNum;				/**< 在一秒钟内的时间单元的数量, 以时间单元为单位。即帧率的分子 */
	uint32_t	frmRateDen;				/**< 在一帧内的时间单元的数量, 以时间单元为单位。即帧率的分母 */
} IMPEncoderFrmRate;

/**
 * 定义H.264编码Channel Fixqp属性结构
 */
typedef struct {
	uint32_t			IQp;			/**< I帧Qp值 */
	uint32_t			PQp;			/**< P帧Qp值 */
	uint32_t			BQp;			/**< B帧Qp值,暂不支持B帧 */
	bool				blkQpEn;		/**< Qp是否作用于块级qp */
} IMPEncoderAttrH264FixQP;

/**
 * 定义H.264编码Channel CBR属性结构
 */
typedef struct {
	uint8_t				maxQp;				/**< 编码器支持图像最大QP */
	uint8_t				minQp;				/**< 编码器支持图像最小QP */
	bool				blkQpEn;			/**< Qp范围是否作用于块级qp */
	uint8_t				initialQp;			/**< 编码器支持图像首帧QP */
	uint8_t				maxIQp;				/**< 编码器支持图像最大I帧QP */
	uint8_t				minIQp;				/**< 编码器支持图像最小I帧QP */
	uint32_t			outBitRate;			/**< 编码器输出码率,以kbps为单位 */
	int8_t				iBiasLvl;			/**< 调整I帧QP偏移值以调节I帧的图像质量及其码流大小,范围:[-10,10] */
	uint16_t			IPfrmQPDelta;		/**< IP帧间QP变化步长,范围:[0,15] */
	uint16_t			PPfrmQPDelta;		/**< PP帧间QP变化步长,范围:[0,15] */
	uint32_t			staticTime;			/**< 统计时间,单位为秒,码率在统计时间内保持稳定,范围:[1,60] */
	uint8_t				flucLvl;			/**< 波动等级,限制码率波动范围,范围:[0,8] */
	uint32_t            qualityLvl;			/**< 质量等级, 范围[0,7], 等级越高图像质量越好, 但码流波动越大 */
	uint32_t			maxIprop;			/**< 最大IP比,范围:[1,100] */
	uint32_t			minIprop;			/**< 最小IP比,范围:[1,maxIprop] */
	uint32_t			maxIPictureSize;	/**< I帧最大图像大小,单位："Kbits" */
	uint32_t			maxPPictureSize;	/**< P帧最大图像大小,单位："Kbits" */
} IMPEncoderAttrH264CBR;

/**
 * 定义H.264编码Channel VBR属性结构
 */
typedef struct {
	uint8_t				maxQp;				/**< 编码器支持图像最大QP */
	uint8_t				minQp;				/**< 编码器支持图像最小QP */
	bool				blkQpEn;			/**< Qp范围是否作用于块级qp */
	uint8_t				initialQp;			/**< 编码器支持图像首帧QP */
	uint8_t				maxIQp;				/**< 编码器支持图像最大I帧QP */
	uint8_t				minIQp;				/**< 编码器支持图像最小I帧QP */
	uint32_t			maxBitRate;			/**< 编码器输出最大码率,以kbps为单位 */
	int8_t				iBiasLvl;			/**< 调整I帧QP偏移值以调节I帧的图像质量及其码流大小,范围:[-10,10] */
	uint32_t			changePos;			/**< VBR 开始调整 Qp 时的码率相对于最大码率的比例,取值范围:[50, 100] */
	uint32_t			staticTime;			/**< 统计时间,单位为秒,码率在统计时间内保持稳定,范围:[1,60] */
	uint32_t            qualityLvl;			/**< 质量等级, 范围[0,7], 等级越高图像质量越好, 但码流波动越大 */
	uint32_t			maxIprop;			/**< 最大IP比,范围:[1,100] */
	uint32_t			minIprop;			/**< 最小IP比,范围:[1,maxIprop] */
	uint32_t			maxIPictureSize;	/**< I帧最大图像大小,单位："Kbits" */
	uint32_t			maxPPictureSize;	/**< P帧最大图像大小,单位："Kbits" */
} IMPEncoderAttrH264VBR;

/**
 * 定义H.264编码Channel Smart属性结构
 */
typedef struct {
	uint8_t				maxQp;				/**< 编码器支持图像最大QP */
	uint8_t				minQp;				/**< 编码器支持图像最小QP */
	bool				blkQpEn;			/**< Qp范围是否作用于块级qp */
	uint8_t				initialQp;			/**< 编码器支持图像首帧QP */
	uint8_t				maxIQp;				/**< 编码器支持图像最大I帧QP */
	uint8_t				minIQp;				/**< 编码器支持图像最小I帧QP */
	uint32_t			maxBitRate;			/**< 编码器输出最大码率,以kbps为单位 */
	int8_t				iBiasLvl;			/**< 调整I帧QP偏移值以调节I帧的图像质量及其码流大小,范围:[-10,10] */
	uint32_t			changePos;			/**< VBR 开始调整 Qp 时的码率相对于最大码率的比例,取值范围:[50, 100] */
	uint32_t			staticTime;			/**< 统计时间,单位为秒,码率在统计时间内保持稳定,范围:[1,60] */
	uint32_t            qualityLvl;			/**< 质量等级, 范围[0,7], 等级越高图像质量越好, 但码流波动越大 */
	uint32_t			maxIprop;			/**< 最大IP比,范围:[1,100] */
	uint32_t			minIprop;			/**< 最小IP比,范围:[1,maxIprop] */
	uint8_t				minStillRate;		/**< 静止场景最小目标码率百分比,范围:[1,100] */
	uint8_t				maxStillQp;			/**< 静止场景I帧QP最大值,范围:[1,51] */
	bool				superSmartEn;		/**< 静止场景超低码率使能 */
	uint8_t				supSmtStillLvl;		/**< 静止场景判定等级,等级越高,更倾向于判定为静止场景,仅superSmart模式有效,范围:[0,10] */
	uint8_t				supSmtStillRateLvl;	/**< 静止场景超低码率等级,等级越高码率越低,仅superSmart模式有效,范围:[0,3] */
	uint8_t				maxSupSmtStillRate;	/**< 静止场景最大目标码率百分比,仅superSmart模式有效,范围:[1,100] */
	uint32_t			maxIPictureSize;	/**< I帧最大图像大小,单位："Kbits" */
	uint32_t			maxPPictureSize;	/**< P帧最大图像大小,单位："Kbits" */
} IMPEncoderAttrH264Smart;

/**
 * 定义H.264编码Channel CVBR属性结构
 */
typedef struct {
	uint8_t				maxQp;				/**< 编码器支持图像最大QP */
	uint8_t				minQp;				/**< 编码器支持图像最小QP */
	bool				blkQpEn;			/**< Qp范围是否作用于块级qp */
	uint8_t				initialQp;			/**< 编码器支持图像首帧QP */
	uint8_t				maxIQp;				/**< 编码器支持图像最大I帧QP */
	uint8_t				minIQp;				/**< 编码器支持图像最小I帧QP */
	uint32_t			maxBitRate;			/**< 编码器输出最大码率,以kbps为单位 */
	uint32_t			longMaxBitRate;		/**< 编码器输出的长期最大码率,以kbps为单位 */
	uint32_t			longMinBitRate;		/**< 编码器输出的长期最小码率,以kbps为单位 */
	int8_t				iBiasLvl;			/**< 调整I帧QP偏移值以调节I帧的图像质量及其码流大小,范围:[-10,10] */
	uint32_t			changePos;			/**< VBR 开始调整 Qp 时的码率相对于最大码率的比例,取值范围:[50, 100] */
	uint32_t			shortStatTime;		/**< 短期统计时间,单位为秒,码率在统计时间内保持稳定,范围:[1,60] */
	uint32_t			longStatTime;		/**< 长期统计时间,单位为秒,码率在统计时间内保持稳定,范围:[1,1440] */
	uint32_t			qualityLvl;			/**< 质量等级, 范围[0,7], 等级越高图像质量越好, 但码流波动越大 */
	uint32_t			maxIprop;			/**< 最大IP比,范围:[1,100] */
	uint32_t			minIprop;			/**< 最小IP比,范围:[1,maxIprop] */
	uint16_t			extraBitRate;		/**< 编码器输出码流最大可透支比特数占长期最大码率的千分比,范围:[0,1000] */
	uint32_t			maxIPictureSize;	/**< I帧最大图像大小,单位："Kbits" */
	uint32_t			maxPPictureSize;	/**< P帧最大图像大小,单位："Kbits" */
} IMPEncoderAttrH264CVBR;

/**
 * 定义H.264编码Channel AVBR属性结构
 */
typedef struct {
	uint8_t				maxQp;				/**< 编码器支持图像最大QP */
	uint8_t				minQp;				/**< 编码器支持图像最小QP */
	bool				blkQpEn;			/**< Qp范围是否作用于块级qp */
	uint8_t				initialQp;			/**< 编码器支持图像首帧QP */
	uint8_t				maxIQp;				/**< 编码器支持图像最大I帧QP */
	uint8_t				minIQp;				/**< 编码器支持图像最小I帧QP */
	uint32_t			maxBitRate;			/**< 编码器输出最大码率,以kbps为单位 */
	int8_t				iBiasLvl;			/**< 调整I帧QP偏移值以调节I帧的图像质量及其码流大小,范围:[-10,10] */
	uint32_t			changePos;			/**< VBR 开始调整 Qp 时的码率相对于最大码率的比例,取值范围:[50, 100] */
	uint32_t			staticTime;			/**< 统计时间,单位为秒,码率在统计时间内保持稳定,范围:[1,60] */
	uint32_t            qualityLvl;			/**< 质量等级, 范围[0,7], 等级越高图像质量越好, 但码流波动越大 */
	uint32_t			maxIprop;			/**< 最大IP比,范围:[1,100] */
	uint32_t			minIprop;			/**< 最小IP比,范围:[1,maxIprop] */
	uint8_t				minStillRate;		/**< 静止场景最小目标码率百分比,范围:[1,100] */
	uint8_t				maxStillQp;			/**< 静止场景I帧QP最大值,范围:[1,51] */
	uint32_t			maxIPictureSize;	/**< I帧最大图像大小,单位："Kbits" */
	uint32_t			maxPPictureSize;	/**< P帧最大图像大小,单位："Kbits" */
} IMPEncoderAttrH264AVBR;

/**
 * 定义H.265编码Channel Fixqp属性结构
 */
typedef struct {
	uint32_t			IQp;			/**< I帧Qp值 */
	uint32_t			PQp;			/**< P帧Qp值 */
	uint32_t			BQp;			/**< B帧Qp值,暂不支持B帧 */
	bool				blkQpEn;		/**< Qp是否作用于块级qp */
} IMPEncoderAttrH265FixQP;

/**
 * 定义H.265编码Channel CBR属性结构
 */
typedef struct {
	uint8_t				maxQp;				/**< 编码器支持图像最大QP */
	uint8_t				minQp;				/**< 编码器支持图像最小QP */
	bool				blkQpEn;			/**< Qp范围是否作用于块级qp */
	uint8_t				initialQp;			/**< 编码器支持图像首帧QP */
	uint8_t				maxIQp;				/**< 编码器支持图像最大I帧QP */
	uint8_t				minIQp;				/**< 编码器支持图像最小I帧QP */
	uint32_t			outBitRate;			/**< 编码器输出码率,以kbps为单位 */
	int8_t				iBiasLvl;			/**< 调整I帧QP偏移值以调节I帧的图像质量及其码流大小,范围:[-10,10] */
	uint16_t			IPfrmQPDelta;		/**< IP帧间QP变化步长,范围:[0,15] */
	uint16_t			PPfrmQPDelta;		/**< PP帧间QP变化步长,范围:[0,15] */
	uint32_t			staticTime;			/**< 统计时间,单位为秒,码率在统计时间内保持稳定,范围:[1,60] */
	uint8_t				flucLvl;			/**< 波动等级,限制码率波动范围,范围:[0,8] */
	uint32_t            qualityLvl;			/**< 质量等级, 范围[0,7], 等级越高图像质量越好, 但码流波动越大 */
	uint32_t			maxIprop;			/**< 最大IP比,范围:[1,100] */
	uint32_t			minIprop;			/**< 最小IP比,范围:[1,maxIprop] */
	uint32_t			maxIPictureSize;	/**< I帧最大图像大小,单位："Kbits" */
	uint32_t			maxPPictureSize;	/**< P帧最大图像大小,单位："Kbits" */
} IMPEncoderAttrH265CBR;

/**
 * 定义H.265编码Channel VBR属性结构
 */
typedef struct {
	uint8_t				maxQp;				/**< 编码器支持图像最大QP */
	uint8_t				minQp;				/**< 编码器支持图像最小QP */
	bool				blkQpEn;			/**< Qp范围是否作用于块级qp */
	uint8_t				initialQp;			/**< 编码器支持图像首帧QP */
	uint8_t				maxIQp;				/**< 编码器支持图像最大I帧QP */
	uint8_t				minIQp;				/**< 编码器支持图像最小I帧QP */
	uint32_t			maxBitRate;			/**< 编码器输出最大码率,以kbps为单位 */
	int8_t				iBiasLvl;			/**< 调整I帧QP偏移值以调节I帧的图像质量及其码流大小,范围:[-10,10] */
	uint32_t			changePos;			/**< VBR 开始调整 Qp 时的码率相对于最大码率的比例,取值范围:[50, 100] */
	uint32_t			staticTime;			/**< 统计时间,单位为秒,码率在统计时间内保持稳定,范围:[1,60] */
	uint32_t            qualityLvl;			/**< 质量等级, 范围[0,7], 等级越高图像质量越好, 但码流波动越大 */
	uint32_t			maxIprop;			/**< 最大IP比,范围:[1,100] */
	uint32_t			minIprop;			/**< 最小IP比,范围:[1,maxIprop] */
	uint32_t			maxIPictureSize;	/**< I帧最大图像大小,单位："Kbits" */
	uint32_t			maxPPictureSize;	/**< P帧最大图像大小,单位："Kbits" */
} IMPEncoderAttrH265VBR;

/**
 * 定义H.265编码Channel Smart属性结构
 */
typedef struct {
	uint8_t				maxQp;				/**< 编码器支持图像最大QP */
	uint8_t				minQp;				/**< 编码器支持图像最小QP */
	bool				blkQpEn;			/**< Qp范围是否作用于块级qp */
	uint8_t				initialQp;			/**< 编码器支持图像首帧QP */
	uint8_t				maxIQp;				/**< 编码器支持图像最大I帧QP */
	uint8_t				minIQp;				/**< 编码器支持图像最小I帧QP */
	uint32_t			maxBitRate;			/**< 编码器输出最大码率,以kbps为单位 */
	int8_t				iBiasLvl;			/**< 调整I帧QP偏移值以调节I帧的图像质量及其码流大小,范围:[-10,10] */
	uint32_t			changePos;			/**< VBR 开始调整 Qp 时的码率相对于最大码率的比例,取值范围:[50, 100] */
	uint32_t			staticTime;			/**< 统计时间,单位为秒,码率在统计时间内保持稳定,范围:[1,60] */
	uint32_t            qualityLvl;			/**< 质量等级, 范围[0,7], 等级越高图像质量越好, 但码流波动越大 */
	uint32_t			maxIprop;			/**< 最大IP比,范围:[1,100] */
	uint32_t			minIprop;			/**< 最小IP比,范围:[1,maxIprop] */
	uint8_t				minStillRate;		/**< 静止场景最小目标码率百分比,范围:[1,100] */
	uint8_t				maxStillQp;			/**< 静止场景I帧QP最大值,范围:[1,51] */
	bool				superSmartEn;		/**< 静止场景超低码率使能 */
	uint8_t				supSmtStillLvl;		/**< 静止场景判定等级,等级越高,更倾向于判定为静止场景,仅superSmart模式有效,范围:[0,10] */
	uint8_t				supSmtStillRateLvl;	/**< 静止场景超低码率等级,等级越高码率越低,仅superSmart模式有效,范围:[0,3] */
	uint8_t				maxSupSmtStillRate;	/**< 静止场景最大目标码率百分比,仅superSmart模式有效,范围:[1,100] */
	uint32_t			maxIPictureSize;	/**< I帧最大图像大小,单位："Kbits" */
	uint32_t			maxPPictureSize;	/**< P帧最大图像大小,单位："Kbits" */
} IMPEncoderAttrH265Smart;

/**
 * 定义H.265编码Channel CVBR属性结构
 */
typedef struct {
	uint8_t				maxQp;				/**< 编码器支持图像最大QP */
	uint8_t				minQp;				/**< 编码器支持图像最小QP */
	bool				blkQpEn;			/**< Qp范围是否作用于块级qp */
	uint8_t				initialQp;			/**< 编码器支持图像首帧QP */
	uint8_t				maxIQp;				/**< 编码器支持图像最大I帧QP */
	uint8_t				minIQp;				/**< 编码器支持图像最小I帧QP */
	uint32_t			maxBitRate;			/**< 编码器输出最大码率,以kbps为单位 */
	uint32_t			longMaxBitRate;		/**< 编码器输出的长期最大码率,以kbps为单位 */
	uint32_t			longMinBitRate;		/**< 编码器输出的长期最小码率,以kbps为单位 */
	int8_t				iBiasLvl;			/**< 调整I帧QP偏移值以调节I帧的图像质量及其码流大小,范围:[-10,10] */
	uint32_t			changePos;			/**< VBR 开始调整 Qp 时的码率相对于最大码率的比例,取值范围:[50, 100] */
	uint32_t			shortStatTime;		/**< 短期统计时间,单位为秒,码率在统计时间内保持稳定,范围:[1,60] */
	uint32_t			longStatTime;		/**< 长期统计时间,单位为秒,码率在统计时间内保持稳定,范围:[1,1440] */
	uint32_t			qualityLvl;			/**< 质量等级, 范围[0,7], 等级越高图像质量越好, 但码流波动越大 */
	uint32_t			maxIprop;			/**< 最大IP比,范围:[1,100] */
	uint32_t			minIprop;			/**< 最小IP比,范围:[1,maxIprop] */
	uint16_t			extraBitRate;		/**< 编码器输出码流最大可透支比特数占长期最大码率的千分比,范围:[0,1000] */
	uint32_t			maxIPictureSize;	/**< I帧最大图像大小,单位："Kbits" */
	uint32_t			maxPPictureSize;	/**< P帧最大图像大小,单位："Kbits" */
} IMPEncoderAttrH265CVBR;

/**
 * 定义H.265编码Channel AVBR属性结构
 */
typedef struct {
	uint8_t				maxQp;				/**< 编码器支持图像最大QP */
	uint8_t				minQp;				/**< 编码器支持图像最小QP */
	bool				blkQpEn;			/**< Qp范围是否作用于块级qp */
	uint8_t				initialQp;			/**< 编码器支持图像首帧QP */
	uint8_t				maxIQp;				/**< 编码器支持图像最大I帧QP */
	uint8_t				minIQp;				/**< 编码器支持图像最小I帧QP */
	uint32_t			maxBitRate;			/**< 编码器输出最大码率,以kbps为单位 */
	int8_t				iBiasLvl;			/**< 调整I帧QP偏移值以调节I帧的图像质量及其码流大小,范围:[-10,10] */
	uint32_t			changePos;			/**< VBR 开始调整 Qp 时的码率相对于最大码率的比例,取值范围:[50, 100] */
	uint32_t			staticTime;			/**< 统计时间,单位为秒,码率在统计时间内保持稳定,范围:[1,60] */
	uint32_t            qualityLvl;			/**< 质量等级, 范围[0,7], 等级越高图像质量越好, 但码流波动越大 */
	uint32_t			maxIprop;			/**< 最大IP比,范围:[1,100] */
	uint32_t			minIprop;			/**< 最小IP比,范围:[1,maxIprop] */
	uint8_t				minStillRate;		/**< 静止场景最小目标码率百分比,范围:[1,100] */
	uint8_t				maxStillQp;			/**< 静止场景I帧QP最大值,范围:[1,51] */
	uint32_t			maxIPictureSize;	/**< I帧最大图像大小,单位："Kbits" */
	uint32_t			maxPPictureSize;	/**< P帧最大图像大小,单位："Kbits" */
} IMPEncoderAttrH265AVBR;

/**
 * 定义JPEG编码Channel Fixqp属性结构
 */
typedef struct {
	uint32_t			qp;			/**< qp值,范围:[0,98] */
} IMPEncoderAttrJPEGFixQP;

/**
 * 定义H.264和H.265编码Channel去噪属性,一经使能不能改变,但去噪类型可以动态改变;
 */
typedef struct {
	bool				enable;			/**< 是否使能去噪功能, 0:忽略,1:按当前帧类型去噪,信息损失最大,2:按I帧去噪，信息损失中等 */
	int					dnType;			/**< 去噪类型,0:忽略，不降噪,1:使用IP帧类型降噪,2:使用I帧类型降噪 */
	int					dnIQp;			/**< 去噪I帧量化参数 */
	int					dnPQp;			/**< 去噪P帧量化参数 */
} IMPEncoderAttrDenoise;

/**
 * 定义H.264和H.265编码Channel输入帧使用模式
 */
typedef enum {
	ENC_FRM_BYPASS	= 0,		/**< 顺序全使用模式-默认模式 */
	ENC_FRM_REUSED	= 1,		/**< 重复使用帧模式 */
	ENC_FRM_SKIP	= 2,		/**< 丢帧模式 */
} EncFrmUsedMode;

/**
 * 定义H.264和H.265编码Channel输入帧使用模式属性
 */
typedef struct {
	bool				enable;			/**< 是否使能输入帧使用模式 */
	EncFrmUsedMode		frmUsedMode;	/**< 输入帧使用模式 */
	uint32_t			frmUsedTimes;	/**< 在重复帧或丢帧模式下每次使用的帧间隔 */
} IMPEncoderAttrFrmUsed;

/**
 * 定义H.264和H.265编码Channel跳帧模式
 */
typedef enum {
	IMP_Encoder_STYPE_N1X			= 0,	/**< 1倍跳帧参考 */
	IMP_Encoder_STYPE_N2X			= 1,	/**< 2倍跳帧参考 */
	IMP_Encoder_STYPE_N4X			= 2,	/**< 4倍跳帧参考 */
	IMP_Encoder_STYPE_HN1_FALSE	    = 3,	/**< 高级跳帧模式：N1开放跳帧 */
	IMP_Encoder_STYPE_HN1_TRUE		= 4,	/**< 高级跳帧模式：N1封闭跳帧 */
	IMP_Encoder_STYPE_H1M_FALSE	    = 5,	/**< 高级跳帧模式：1M开放跳帧 */
	IMP_Encoder_STYPE_H1M_TRUE		= 6,	/**< 高级跳帧模式：1M封闭跳帧 */
} IMPSkipType;

/**
 * 定义H.264和H.265编码Channel帧参考类型
 */
typedef enum {
	IMP_Encoder_FSTYPE_IDR		= 0,	/**< 高级跳帧模式中的关键帧(IDR帧) */
	IMP_Encoder_FSTYPE_LBASE	= 1,	/**< 高级跳帧模式中的长期基本帧(P帧) */
	IMP_Encoder_FSTYPE_SBASE	= 2,	/**< 高级跳帧模式中的短期基本帧(P帧) */
	IMP_Encoder_FSTYPE_ENHANCE	= 3,	/**< 高级跳帧模式中的增强帧(P帧) */
} IMPRefType;

/**
 * 定义H.264和H.265编码Channel高级跳帧类型结构体
 */
typedef struct {
	IMPSkipType	    skipType;	    /**< 跳帧类型 */
	int				m;				/**< 增强帧间隔数 */
	int				n;				/**< 参考帧间隔数 */
	int				maxSameSceneCnt;/**< 同一场景占用gop最大数目,仅对H1M Skip类型有效,若设为未大于0,则m值不起作用 */
	int				bEnableScenecut;/**< 是否使能场景切换,仅对H1M Skip类型有效,仅在SMART码控模式生效 */
	int				bBlackEnhance;	/**< 是否使得增强帧以空码流输出 */
} IMPEncoderAttrHSkip;

/**
 * 定义H.264和H.265编码Channel高级跳帧类型初始化结构体
 */
typedef struct {
	IMPEncoderAttrHSkip	hSkipAttr;	 /**< 高级跳帧属性 */
	IMPSkipType			maxHSkipType;/**< 需要使用的最大跳帧类型，影响rmem内存大小, N1X 到 N2X 需要分配2个参考重建帧空间, N4X 到 H1M_TRUE 需要分配3个参考重建帧空间, 请按需要的跳帧类型设定 */
} IMPEncoderAttrInitHSkip;

/**
 * 定义H.264,H.265和JPEG编码Channel码率控制器码率控制模式属性
 */
typedef struct {
	IMPEncoderRcMode rcMode;						/**< RC 模式 */
	union {
		IMPEncoderAttrH264FixQP	 attrH264FixQp;		/**< H.264 协议编码Channel Fixqp 模式属性 */
		IMPEncoderAttrH264CBR	 attrH264Cbr;		/**< H.264 协议编码Channel Cbr 模式属性 */
		IMPEncoderAttrH264VBR	 attrH264Vbr;		/**< H.264 协议编码Channel Vbr 模式属性 */
		IMPEncoderAttrH264Smart	 attrH264Smart;		/**< H.264 协议编码Channel Smart 模式属性 */
		IMPEncoderAttrH264CVBR	 attrH264CVbr;		/**< H.264 协议编码Channel CVBR 模式属性 */
		IMPEncoderAttrH264AVBR	 attrH264AVbr;		/**< H.264 协议编码Channel AVBR 模式属性 */

		IMPEncoderAttrH265FixQP	 attrH265FixQp;		/**< H.265 协议编码Channel Fixqp 模式属性 */
		IMPEncoderAttrH265CBR	 attrH265Cbr;		/**< H.265 协议编码Channel Cbr 模式属性 */
		IMPEncoderAttrH265VBR	 attrH265Vbr;		/**< H.265 协议编码Channel Vbr 模式属性 */
		IMPEncoderAttrH265Smart	 attrH265Smart;		/**< H.265 协议编码Channel Smart 模式属性 */
		IMPEncoderAttrH265CVBR	 attrH265CVbr;		/**< H.265 协议编码Channel CVBR 模式属性 */
		IMPEncoderAttrH265AVBR	 attrH265AVbr;		/**< H.265 协议编码Channel AVBR 模式属性 */

		IMPEncoderAttrJPEGFixQP	 attrJPEGFixQp;		/**< JPEG 协议编码Channel Fixqp 模式属性 */
	};
} IMPEncoderAttrRcMode;

/**
 * 定义H.264,H.265和JPEG编码Channel码率控制器属性
 */
typedef struct {
	IMPEncoderFrmRate	        outFrmRate;		/**< 编码Channel的输出帧率（输出帧率不能大于输入帧率）*/
	uint32_t			        maxGop;			/**< gop值，必须是帧率的整数倍 */
	IMPEncoderAttrRcMode        attrRcMode;     /**< 码率控制模式属性 */
	IMPEncoderAttrFrmUsed	    attrFrmUsed;	/**< 输入帧使用模式属性 */
	IMPEncoderAttrDenoise	    attrDenoise;	/**< 去噪属性 */
	IMPEncoderAttrInitHSkip	    attrHSkip;		/**< 高级跳帧初始化属性 */
} IMPEncoderRcAttr;

/**
 * 定义H.264码流NALU类型
 */
typedef enum {
	IMP_H264_NAL_UNKNOWN		= 0,	/**< 未指定 */
	IMP_H264_NAL_SLICE		    = 1,	/**< 一个非IDR图像的编码条带  */
	IMP_H264_NAL_SLICE_DPA	    = 2,	/**< 编码条带数据分割块A */
	IMP_H264_NAL_SLICE_DPB	    = 3,	/**< 编码条带数据分割块B */
	IMP_H264_NAL_SLICE_DPC	    = 4,	/**< 编码条带数据分割块C */
	IMP_H264_NAL_SLICE_IDR	    = 5,	/**< IDR图像的编码条带 */
	IMP_H264_NAL_SEI			= 6,	/**< 辅助增强信息 (SEI) */
	IMP_H264_NAL_SPS			= 7,	/**< 序列参数集 */
	IMP_H264_NAL_PPS			= 8,	/**< 图像参数集 */
	IMP_H264_NAL_AUD			= 9,	/**< 访问单元分隔符 */
	IMP_H264_NAL_FILLER		    = 12,	/**< 填充数据 */
} IMPEncoderH264NaluType;

/**
 * 定义H.265码流NALU类型
 */
typedef enum {
	IMP_H265_NAL_SLICE_TRAIL_N      = 0,        /**< 尾随图像, 不带参考信息 */
	IMP_H265_NAL_SLICE_TRAIL_R      = 1,        /**< 尾随图像, 带参考信息 */
	IMP_H265_NAL_SLICE_TSA_N        = 2,        /**< 时域子层接入点图像, 不带参考信息 */
	IMP_H265_NAL_SLICE_TSA_R        = 3,        /**< 时域子层接入点图像, 带参考信息 */
	IMP_H265_NAL_SLICE_STSA_N       = 4,        /**< 逐步时域子层接入点图像, 不带参考信息 */
	IMP_H265_NAL_SLICE_STSA_R       = 5,        /**< 逐步时域子层接入点图像, 带参考信息 */
	IMP_H265_NAL_SLICE_RADL_N       = 6,        /**< 可解码随机接入前置图像, 不带参考信息 */
	IMP_H265_NAL_SLICE_RADL_R       = 7,        /**< 可解码随机接入前置图像, 带参考信息 */
	IMP_H265_NAL_SLICE_RASL_N       = 8,        /**< 跳过随机接入的前置图像, 不带参考信息 */
	IMP_H265_NAL_SLICE_RASL_R       = 9,        /**< 跳过随机接入的前置图像, 带参考信息 */
	IMP_H265_NAL_SLICE_BLA_W_LP     = 16,       /**< 断点连接接入, 带前置图像 */
	IMP_H265_NAL_SLICE_BLA_W_RADL   = 17,       /**< 断点连接接入, 带前置图像RADL */
	IMP_H265_NAL_SLICE_BLA_N_LP     = 18,       /**< 断点连接接入, 不带前置图像 */
	IMP_H265_NAL_SLICE_IDR_W_RADL   = 19,       /**< 即时解码刷新, 带前置图像RADL */
	IMP_H265_NAL_SLICE_IDR_N_LP     = 20,       /**< 即时解码刷新, 不带前置图像 */
	IMP_H265_NAL_SLICE_CRA          = 21,       /**< 纯随机接入, 带前置图像*/
	IMP_H265_NAL_VPS                = 32,       /**< 视频参数集 */
	IMP_H265_NAL_SPS                = 33,       /**< 序列参数集 */
	IMP_H265_NAL_PPS                = 34,       /**< 图像参数集 */
	IMP_H265_NAL_AUD                = 35,       /**< 访问单元分隔符 */
	IMP_H265_NAL_EOS                = 36,       /**< 序列结束 */
	IMP_H265_NAL_EOB                = 37,       /**< 比特流结束 */
	IMP_H265_NAL_FILLER_DATA        = 38,       /**< 填充数据 */
	IMP_H265_NAL_PREFIX_SEI         = 39,       /**< 辅助增强信息 (SEI) */
	IMP_H265_NAL_SUFFIX_SEI         = 40,       /**< 辅助增强信息 (SEI) */
	IMP_H265_NAL_INVALID            = 64,       /**< 无效NAL类型 */
} IMPEncoderH265NaluType;

/**
 * 定义H.264和H.265编码Channel码流NAL类型
 */
typedef union {
	IMPEncoderH264NaluType		h264Type;		/**< H264E NALU 码流包类型 */
	IMPEncoderH265NaluType		h265Type;		/**< H265E NALU 码流包类型 */
} IMPEncoderDataType;

/**
 * 定义编码帧码流包结构体
 */
typedef struct {
	uint32_t	phyAddr;						/**< 码流包物理地址 */
	uint32_t	virAddr;						/**< 码流包虚拟地址 */
	uint32_t	length;							/**< 码流包长度 */
	int64_t		timestamp;						/**< 时间戳，单位us */
	bool		frameEnd;						/**< 帧结束标识 */
	IMPEncoderDataType	dataType;				/**< H.264和H.265编码Channel码流NAL类型 */
} IMPEncoderPack;

/**
 * 定义编码帧码流类型结构体
 */
typedef struct {
	IMPEncoderPack  *pack;				/**< 帧码流包结构 */
	uint32_t        packCount;			/**< 一帧码流的所有包的个数 */
	uint32_t        seq;				/**< 编码帧码流序列号 */
    IMPRefType      refType;            /**< 编码帧参考类型, 只针对H264和h265 */
} IMPEncoderStream;

/**
 * 定义编码器裁剪属性，针对输入编码器的图像先做裁剪，与编码通道的尺寸进行比较再做缩放
 */
typedef struct {
	bool		enable;		/**< 是否进行裁剪,取值范围:[FALSE, TRUE],TRUE:使能裁剪,FALSE:不使能裁剪 */
	uint32_t	x;			/**< 裁剪的区域,左上角x坐标 */
	uint32_t	y;			/**< 裁剪的区域,左上角y坐标 */
	uint32_t	w;			/**< 裁剪的区域,宽 */
	uint32_t	h;			/**< 裁剪的区域,高 */
} IMPEncoderCropCfg;

/**
 * 定义编码器插入用户数据属性,只针对H264和H.265
 */
typedef struct {
	uint32_t			maxUserDataCnt;		/**< 最大用户插入数据缓存空间个数,范围：0-2 */
	uint32_t			maxUserDataSize;	/**< 最大用户插入数据缓存空间大小,范围：16-1024 */
} IMPEncoderUserDataCfg;

/**
 * 定义编码器属性结构体
 */
typedef struct {
	IMPPayloadType			enType;			/**< 编码协议类型 */
	uint32_t				bufSize;		/**< 配置 buffer 大小，取值范围:不小于图像宽高乘积的1.5倍。设置通道编码属性时，将此参数设置为0，IMP内部会自动计算大小 */
	uint32_t				profile;		/**< 编码的等级, 0: baseline; 1:MP; 2:HP */
	uint32_t				picWidth;		/**< 编码图像宽度 */
	uint32_t				picHeight;		/**< 编码图像高度 */
	IMPEncoderCropCfg		crop;			/**< 编码器裁剪属性 */
	IMPEncoderUserDataCfg	userData;		/**< 插入用户数据属性,只针对H264和h265 */
} IMPEncoderAttr;

/**
 * 定义编码Channel属性结构体
 */
typedef struct {
	IMPEncoderAttr      encAttr;     /**< 编码器属性结构体 */
	IMPEncoderRcAttr    rcAttr;      /**< 码率控制器属性结构体,只针对H264和h265 */
	bool                bEnableIvdc; /**< ISP VPU Direct Connect使能标志 */
} IMPEncoderCHNAttr;

/**
 * 定义编码Channel的状态结构体
 */
typedef struct {
	bool		registered;			/**< 注册到Group标志，取值范围:{TRUE, FALSE}，TRUE:注册，FALSE:未注册 */
	uint32_t	leftPics;			/**< 待编码的图像数 */
	uint32_t	leftStreamBytes;	/**< 码流buffer剩余的byte数 */
	uint32_t	leftStreamFrames;	/**< 码流buffer剩余的帧数 */
	uint32_t	curPacks;			/**< 当前帧的码流包个数 */
	uint32_t	work_done;			/**< 通道程序运行状态，0：正在运行，1，未运行 */
} IMPEncoderCHNStat;

/**
 * 定义彩转灰(C2G)参数
 */
typedef struct {
	bool	enable;			/**< 开启或关闭彩转灰功能 */
} IMPEncoderColor2GreyCfg;

/**
 * 定义H.264和H.265编码Channel设置EnableIDR参数
 */
typedef struct {
	bool	enable;			/**< 是否设置EnableIDR */
} IMPEncoderEnIDRCfg;

/**
 * 定义H.264和H.265编码Channel设置gopsize参数
 */
typedef struct {
	int		gopsize;		/**< IDR参数 */
} IMPEncoderGOPSizeCfg;

/**
 * 定义H.264和H.265编码Channel设置ROI QP模式
 */
typedef enum {
	IMP_ROI_QPMODE_DISABLE		= 0,	/**< 关闭ROI */
	IMP_ROI_QPMODE_FIXED_QP		= 1,	/**< 绝对ROI */
	IMP_ROI_QPMODE_DELTA		= 2,	/**< 相对ROI */
	IMP_ROI_QPMODE_MAX_ENUM,
} IMPEncoderQPMode;

/**
 * 定义H.264和H.265编码Channel设置ROI参数
 */
typedef struct {
	uint32_t	u32Index;	/**< ROI区域索引值，支持0-7 */
	bool		bEnable;	/**< 是否使能本区域ROI功能 */
	bool		bRelatedQp;	/**< 0：绝对ROI，1：相对ROI */
	int			s32Qp;		/**< ROI区域的相对或绝对qp值 */
	IMPRect		rect;		/**< 区域坐标属性 */
} IMPEncoderROICfg;

/**
 * 定义H.264和H.265编码Channel设置ROI属性
 */
typedef struct {
	IMPEncoderROICfg roi[IMP_ENC_ROI_WIN_COUNT];	/**< ROI属性 */
} IMPEncoderROIAttr;

/**
 * 定义Map ROI在不同目标时的QP值
 */
typedef struct {
	uint8_t *mapdata;
	uint32_t length;
} IMPEncoderMappingList;

/**
 * 定义Map ROI映射类型
 */
typedef enum {
	IMP_MAPPINGTYPE_DIRECT,		/**< 直接映射 */
	IMP_MAPPINGTYPE_DEVIOUS,	/**< 间接映射 */
	IMP_MAPPINGTYPE_BUTT,		/**< 用于判断参数的有效性，必须小于此值 */
} IMPEncoderMappingType;

/**
 * 定义H.264和H.265编码Channel设置Map ROI属性
 */
typedef struct {
	uint8_t*				map;		/**< Map ROI属性数组指针 */
	uint32_t				mapSize;	/**< Map ROI属性数组大小 */
	IMPEncoderMappingType	type;		/**< Map映射类型 */
	int32_t					reserved;	/**< 保留参数 */
} IMPEncoderMapRoiCfg;

/**
 * 定义H.264和H.265编码Channel设置QpgAI属性
 */
typedef struct {
	uint8_t*				map;			/**< Qpg AI属性数组指针 */
	uint32_t				width;			/**< 算法输出宽度 */
	uint32_t				height;			/**< 算法输出高度 */
	uint8_t					foreBackMode;	/**< 智能编码模式,范围:[0,2],0:默认效果,1:节省码率,2:增强质量 */
	uint8_t					markLvl;		/**< 智能编码作用程度,范围:[0,3],仅AVBR、SMART模式有效 */
	int32_t					reserved;		/**< 保留参数 */
} IMPEncoderQpgAICfg;

/**
 * 定义H.264和H.265编码Channel码率控制中超大帧处理模式
 */
typedef enum {
	IMP_RC_SUPERFRM_NONE        = 0,    /**< 无特殊策略, 支持 */
	IMP_RC_SUPERFRM_DISCARD     = 1,    /**< 丢弃超大帧, 不支持, 由调用者自己决定是否丢弃 */
	IMP_RC_SUPERFRM_REENCODE    = 2,    /**< 重编超大帧, 支持, 仅在未开启bufShare时生效 */
	IMP_RC_SUPERFRM_BUTT        = 3,
} IMPEncoderSuperFrmMode;

/**
 * 定义H.264和H.265编码Channel码率控制优先级枚举
 */
typedef enum {
	IMP_RC_PRIORITY_RDO                 = 0,    /**< 目标码率与质量平衡 */
	IMP_RC_PRIORITY_BITRATE_FIRST       = 1,    /**< 目标码率优先 */
	IMP_RC_PRIORITY_FRAMEBITS_FIRST     = 2,    /**< 超大帧阈值优先 */
	IMP_RC_PRIORITY_BUTT                = 3,
} IMPEncoderRcPriority;

/**
 * 定义H.264和H.265编码Channel超大帧处理策略参数
 */
typedef struct {
	IMPEncoderSuperFrmMode      superFrmMode;       /**< 超大帧处理模式,默认为 IMP_RC_SUPERFRM_NONE */
	uint32_t                    superIFrmBitsThr;   /**< I 帧超大阈值, 默认为bufSize*8 */
	uint32_t                    superPFrmBitsThr;   /**< P 帧超大阈值, 默认为I帧超大阈值除以1.4 */
	uint32_t                    superBFrmBitsThr;   /**< B 帧超大阈值, 默认为P帧超大阈值除以1.3, 暂不支持B帧 */
	IMPEncoderRcPriority        rcPriority;         /**< 码率控制优先级, 默认为 IMP_RC_PRIORITY_RDO */
	uint8_t                     maxReEncodeTimes;   /**< 最大重编次数,仅在IMP_RC_SUPERFRM_REENCODE模式下生效,范围:[1,3] */
} IMPEncoderSuperFrmCfg;

/**
 * 定义 H.264 协议编码通道色度量化结构体
 */
typedef struct {
	int         chroma_qp_index_offset;     /**< 具体含义请参见 H.264 协议, 系统默认值为 0; 取值范围:[-12, 12] */
} IMPEncoderH264TransCfg;

/**
 * 定义 H.265 协议编码通道色度量化结构体
 */
typedef struct {
	int         chroma_cr_qp_offset;     /**< 具体含义请参见 H.265 协议, 系统默认值为 0; 取值范围:[-12, 12] */
	int         chroma_cb_qp_offset;     /**< 具体含义请参见 H.265 协议, 系统默认值为 0; 取值范围:[-12, 12] */
} IMPEncoderH265TransCfg;

/**
 * 定义宏块级编码控制模式结构体
 */
typedef enum {
	ENC_MBQP_AUTO        = 0,    /**< 自动选择宏块级编码控制模式(默认) */
	ENC_MBQP_MAD         = 1,    /**< 开启MAD模式 */
	ENC_MBQP_TEXT        = 2,    /**< 开启TEXT模式 */
	ENC_MBQP_ROWRC       = 3,    /**< 开启ROWRC模式 */
	ENC_MBQP_MAD_ROWRC   = 4,    /**< 开启MAD模式和ROWRC模式 */
	ENC_MBQP_TEXT_ROWRC  = 5,    /**< 开启TEXT模式和ROWRC模式 */
} IMPEncoderQpgMode;

/**
 * 定义H.265编码Channel SRD配置结构体
 */
typedef struct {
	bool            enable;     /**< 是否使能SRD功能 */
	uint8_t         level;      /**< SRD功能作用等级,等级越高,静止场景码率越低,范围:[0,3] */
} IMPEncoderSrdCfg;

/**
 * 定义非绑定编码模式输出结构体
 */
typedef struct {
	void *outAddr;			/**< 输出码流地址 */
	uint32_t outLen;		/**< 输出码流长度 */
} IMPEncoderYuvOut;

/**
 * 定义非绑定编码模式输入结构体
 */
typedef struct {
	IMPPayloadType type;			/**< 编码类型, 必须设置 */
	IMPEncoderAttrRcMode mode;		/**< 码率控制模式属性 */
	IMPEncoderFrmRate outFrmRate;	/**< 编码输出帧率, 必须设置*/
	uint32_t maxGop;				/**< gop值，必须是帧率的整数倍 */
} IMPEncoderYuvIn;

/**
 * 定义内核编码结构体
 */
typedef struct {
	IMPPayloadType		type;			/**< 码流类型 */
	uint32_t			bufAddr;		/**< 码流buffer的起始虚拟地址 */
	uint32_t			bufLen;			/**< 码流总长度 */
	uint32_t			strmCnt;		/**< 码流总帧数 */
	uint32_t			index;			/**< 当前码流序号 */
	uint32_t			strmAddr;		/**< 当前码流的虚拟地址 */
	uint32_t			strmLen;		/**< 当前码流的长度 */
	int64_t				timestamp;		/**< 当前码流时间戳，单位us */
} IMPEncoderKernEncOut;

/**
 * @fn int IMP_Encoder_CreateGroup(int encGroup)
 *
 * 创建编码Group
 *
 * @param[in] encGroup Group号,取值范围:[0, @ref NR_MAX_ENC_GROUPS - 1]
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark 一路Group仅支持一路分辨率，不同分辨率需启动新的Group。一路Group允许最多注册2个编码channel
 *
 * @attention 如果指定的Group已经存在，则返回失败
 */
int IMP_Encoder_CreateGroup(int encGroup);

/**
 * @fn int IMP_Encoder_DestroyGroup(int encGroup)
 *
 * 销毁编码Grouop.
 *
 * @param[in] encGroup Group号,取值范围:[0, @ref NR_MAX_ENC_GROUPS - 1]
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark 销毁Group时，必须保证Group为空，即没有任何Channel在Group中注册，或注册到Group中的Channel已经反注册，否则返回失败
 *
 * @attention 销毁并不存在的Group，则返回失败
 */
int IMP_Encoder_DestroyGroup(int encGroup);

/**
 * @fn int IMP_Encoder_SetDefaultParam(IMPEncoderCHNAttr *chnAttr, IMPEncoderProfile profile, IMPEncoderRcMode rcMode, uint16_t uWidth, uint16_t uHeight, uint32_t frmRateNum, uint32_t frmRateDen, uint32_t uGopLength, uint32_t uBufSize, int iInitialQP, uint32_t uTargetBitRate);
 *
 * 设置编码默认属性
 *
 * @param[out] chnAttr 编码属性结构体
 * @param[in]  profile 编码协议
 * @param[in]  rcMode  码率控制模式
 * @param[in]  uWidth  编码图片宽度
 * @param[in]  uHeight 编码图片高度
 * @param[in]  frmRateNum 编码帧率分子
 * @param[in]  frmRateDen 编码帧率分母
 * @param[in]  uGopLength GOP长度
 * @param[in]  uBufSize 码流buf大小
 * @param[in]  iInitialQP 初始化QP, 默认设置为-1
 * @param[in]  uTargetBitRate 目标码率
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remarks 相关编码属性如果不是非常了解，请使用默认值。
 *
 * @attention 无
 */
int IMP_Encoder_SetDefaultParam(IMPEncoderCHNAttr *chnAttr, IMPEncoderProfile profile, IMPEncoderRcMode rcMode, uint16_t uWidth, uint16_t uHeight, uint32_t frmRateNum, uint32_t frmRateDen, uint32_t uGopLength, uint32_t uBufSize, int iInitialQP, uint32_t uTargetBitRate);

/**
 * @fn int IMP_Encoder_CreateChn(int encChn, const IMPEncoderCHNAttr *attr)
 *
 * 创建编码Channel
 *
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] attr 编码Channel属性指针
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark 编码Channel属性由两部分组成，编码器属性和码率控制属性
 * @remark 编码器属性首先需要选择编码协议，然后分别对各种协议对应的属性进行赋值
 */
int IMP_Encoder_CreateChn(int encChn, const IMPEncoderCHNAttr *attr);

/**
 * @fn int IMP_Encoder_DestroyChn(int encChn)
 *
 * 销毁编码Channel
 *
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @attention 销毁并不存在的Channel，则返回失败
 * @attention 销毁前必须保证Channel已经从Group反注册，否则返回失败
 */
int IMP_Encoder_DestroyChn(int encChn);

/**
 * @fn int IMP_Encoder_GetChnAttr(int encChn, IMPEncoderCHNAttr *const attr)
 *
 * 获取编码Channel的属性
 *
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] attr 编码Channel属性
 *
 * @retval 0 成功
 * @retval 非0 失败
 */
int IMP_Encoder_GetChnAttr(int encChn, IMPEncoderCHNAttr *const attr);

/**
 * @fn int IMP_Encoder_RegisterChn(int encGroup, int encChn)
 *
 * 注册编码Channel到Group
 *
 * @param[in] encGroup 编码Group号,取值范围: [0, @ref NR_MAX_ENC_GROUPS - 1]
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @attention 注册并不存在的Channel，则返回失败
 * @attention 注册Channel到不存在的Group，否则返回失败
 * @attention 同一个编码Channel只能注册到一个Group，如果该Channel已经注册到某个Group，则返回失败
 * @attention 如果一个Group已经被注册，那么这个Group就不能再被其他的Channel注册，除非之前注册关系被解除
 */
int IMP_Encoder_RegisterChn(int encGroup, int encChn);

/**
 * @fn int IMP_Encoder_UnRegisterChn(int encChn)
 *
 * 反注册编码Channel到Group
 *
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark Channel注销之后，编码Channel会被复位，编码Channel里的码流buffer都会被清空，如果用户还在使用未及时释放的码流buffer，将不能保证buffer数据的正确性
 * @remark 用户可以使用IMP_Encoder_Query接口来查询编码Channel码流buffer状态，确认码流buffer里的码流取完之后再反注册Channel
 *
 * @attention 注销未创建的Channel，则返回失败
 * @attention 注销未注册的Channel，则返回失败
 * @attention 如果编码Channel未停止接收图像编码，则返回失败
 */
int IMP_Encoder_UnRegisterChn(int encChn);

/**
 * @fn int IMP_Encoder_StartRecvPic(int encChn)
 *
 * 开启编码Channel接收图像
 *
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark 开启编码Channel接收图像后才能开始编码
 *
 * @attention 如果Channel未创建，则返回失败
 * @attention 如果Channel没有注册到Group，则返回失败
 */
int IMP_Encoder_StartRecvPic(int encChn);

/**
 * @fn int IMP_Encoder_StopRecvPic(int encChn)
 *
 * 停止编码Channel接收图像
 *
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark 此接口并不判断当前是否停止接收，即允许重复停止接收不返回错误
 * @remark 调用此接口仅停止接收原始数据编码，码流buffer并不会被消除
 *
 * @attention 如果Channel未创建，则返回失败
 * @attention 如果Channel没有注册到Group，则返回失败
 */
int IMP_Encoder_StopRecvPic(int encChn);

/**
 * @fn int IMP_Encoder_Query(int encChn, IMPEncoderCHNStat *stat)
 *
 * 查询编码Channel状态
 *
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] stat 编码Channel状态
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark 无
 *
 * @attention 无
 */
int IMP_Encoder_Query(int encChn, IMPEncoderCHNStat *stat);

/**
 * @fn int IMP_Encoder_GetStream(int encChn, IMPEncoderStream *stream, bool blockFlag)
 *
 * 获取编码的码流
 *
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] stream 码流结构体指针
 * @param[in] blockFlag 是否使用阻塞方式获取，0：非阻塞，1：阻塞
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark 每次获取一帧码流的数据
 * @remark 如果用户长时间不获取码流,码流缓冲区就会满。一个编码Channel如果发生码流缓冲区满,就会把后 \n
 * 面接收的图像丢掉,直到用户获取码流,从而有足够的码流缓冲可以用于编码时,才开始继续编码。建议用户   \n
 * 获取码流接口调用与释放码流的接口调用成对出现,且尽快释放码流,防止出现由于用户态获取码流,释放不   \n
 * 及时而导致的码流 buffer 满,停止编码。
 * @remark 对于H264和H265类型码流，一次调用成功获取一帧的码流，这帧码流可能包含多个包。
 * @remark 对于JPEG类型码流，一次调用成功获取一帧的码流，这帧码流只包含一个包，这一帧包含了JPEG图片文件的完整信息。
 *
 * 示例：
 * @code
 * int ret;
 * ret = IMP_Encoder_PollingStream(ENC_H264_CHANNEL, 1000); //Polling码流Buffer，等待可获取状态
 * if (ret < 0) {
 *     printf("Polling stream timeout\n");
 *     return -1;
 * }
 *
 * IMPEncoderStream stream;
 * ret = IMP_Encoder_GetStream(ENC_H264_CHANNEL, &stream, 1); //获取一帧码流，阻塞方式
 * if (ret < 0) {
 *     printf("Get Stream failed\n");
 *     return -1;
 * }
 *
 * int i, nr_pack = stream.packCount;
 * for (i = 0; i < nr_pack; i++) { //保存这一帧码流的每个包
 *     ret = write(stream_fd, (void *)stream.pack[i].virAddr,
 *                stream.pack[i].length);
 *     if (ret != stream.pack[i].length) {
 *         printf("stream write error:%s\n", strerror(errno));
 *         return -1;
 *     }
 * }
 * @endcode
 *
 * @attention 如果pstStream为NULL,则返回失败；
 * @attention 如果Channel未创建，则返回失败；
 */
int IMP_Encoder_GetStream(int encChn, IMPEncoderStream *stream, bool blockFlag);

/**
 * @fn int IMP_Encoder_ReleaseStream(int encChn, IMPEncoderStream *stream)
 *
 * 释放码流缓存
 *
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] stream 码流结构体指针
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark 此接口应当和IMP_Encoder_GetStream配对起来使用，\n
 * 用户获取码流后必须及时释放已经获取的码流缓存，否则可能会导致码流buffer满，影响编码器编码。\n
 * 并且用户必须按先获取先释放的顺序释放已经获取的码流缓存。
 * @remark 在编码Channel反注册后，所有未释放的码流包均无效，不能再使用或者释放这部分无效的码流缓存。
 *
 * @attention 如果pstStream为NULL,则返回失败；
 * @attention 如果Channel未创建，则返回失败；
 * @attention 释放无效的码流会返回失败。
 */
int IMP_Encoder_ReleaseStream(int encChn, IMPEncoderStream *stream);

/**
 * @fn int IMP_Encoder_PollingStream(int encChn, uint32_t timeoutMsec)
 *
 * Polling码流缓存
 *
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] timeoutMsec 超时时间，单位：毫秒
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark 在获取码流之前可以用过此API进行Polling，当码流缓存不为空时或超时时函数返回。
 *
 * @attention 无
 */
int IMP_Encoder_PollingStream(int encChn, uint32_t timeoutMsec);

/**
 * @fn int IMP_Encoder_GetFd(int encChn)
 *
 * 获取编码Channel对应的设备文件句柄
 *
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval >=0 成功, 返回设备文件描述符
 * @retval < 0 失败
 *
 * @remark 在使用IMP_Encoder_PollingStream不合适的场合，比如在同一个地方Polling多个编码channel的编码完成情况时, \n
 * 可以使用此文件句柄调用select, poll等类似函数来阻塞等待编码完成事件
 * @remark 调用此API需要通道已经存在
 *
 * @attention 无
 */
int IMP_Encoder_GetFd(int encChn);

/**
 * @fn int IMP_Encoder_RequestIDR(int encChn)
 *
 * 请求IDR帧
 *
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark 在调用此API后，会在最近的编码帧申请IDR帧编码。
 *
 * @attention 此API只适用于H264和h265编码channel
 */
int IMP_Encoder_RequestIDR(int encChn);

/**
 * @fn int IMP_Encoder_FlushStream(int encChn)
 *
 * 刷掉编码器里残留的旧码流，并以IDR帧开始编码
 *
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark 在调用此API后，会在最近的编码帧申请IDR帧编码。
 *
 * @attention 无
 */
int IMP_Encoder_FlushStream(int encChn);

/**
 * @fn int IMP_Encoder_SetMaxStreamCnt(int encChn, int nrMaxStream)
 *
 * 设置码流缓存Buffer个数
 *
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] nrMaxStream 码流Buffer数,取值范围: [1, @ref NR_MAX_ENC_CHN_STREAM]
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark 由于码流缓存Buffer个数在通道创建时就已经固定，因此次API需要在通道创建之前调用。
 * @remark 若通道创建之前不调用此API设置码流缓存Buffer个数，则使用SDK默认的buffer个数。
 *
 * @attention 无
 */
int IMP_Encoder_SetMaxStreamCnt(int encChn, int nrMaxStream);

/**
 * @fn int IMP_Encoder_GetMaxStreamCnt(int encChn, int *nrMaxStream)
 *
 * 获取码流Buffer数
 *
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] nrMaxStream 码流Buffer数变量指针
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark 无
 *
 * @attention 无
 */
int IMP_Encoder_GetMaxStreamCnt(int encChn, int *nrMaxStream);

/**
 * @fn int IMP_Encoder_SetChnCrop(int encChn, const IMPEncoderCropCfg *pstCropCfg).
 *
 * 设置编码通道裁剪属性
 *
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] pstCropCfg 裁剪属性
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark 调用此API会设置通道的裁剪功能属性，在下一个IDR或者P帧生效。
 *
 * @attention 此API只适用于H264和h265编码channel
 */
int IMP_Encoder_SetChnCrop(int encChn, const IMPEncoderCropCfg *pstCropCfg);

/**
 * @fn int IMP_Encoder_GetChnCrop(int encChn, IMPEncoderCropCfg *pstCropCfg).
 *
 * 获取编码通道裁剪属性
 *
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstCropCfg 裁剪属性
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark 调用此API会获取通道的裁剪功能属性，调用此API需要通道已经存在。
 *
 * @attention 此API只适用于H264和h265编码channel
 */
int IMP_Encoder_GetChnCrop(int encChn, IMPEncoderCropCfg *pstCropCfg);

/**
 * @fn int IMP_Encoder_SetChnAttrRcMode(int encChn, const IMPEncoderAttrRcMode *pstRcModeCfg).
 *
 * 设置码率控制模式属性
 *
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] pstRcCfg 码率控制模式属性参数
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark 调用此API会设置通道的码率控制模式属性，下一个IDR生效,调用此API需要通道已经存在。
 *
 * @attention 此API只适用于H264和h265编码channel
 * @attention 此API可以动态设置码率控制所有参数
 */
int IMP_Encoder_SetChnAttrRcMode(int encChn, const IMPEncoderAttrRcMode *pstRcModeCfg);

/**
 * @fn int IMP_Encoder_GetChnAttrRcMode(int encChn, IMPEncoderAttrRcMode *pstRcModeCfg).
 *
 * 获取码率控制模式属性
 *
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstRcCfg 码率控制模式属性参数
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark 调用此API会获取通道的码率控制模式属性，调用此API需要通道已经存在。
 *
 * @attention 此API只适用于H264和h265编码channel
 */
int IMP_Encoder_GetChnAttrRcMode(int encChn, IMPEncoderAttrRcMode *pstRcModeCfg);

/**
 * @fn int IMP_Encoder_GetChnEncType(int encChn, IMPPayloadType *payLoadType)
 *
 * 获取图像编码协议类型
 *
 * @param[in] encChn 编码Channel号, 取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] payLoadType 返回获取图像编码协议类型
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark 如果通道未创建, 则返回失败
 *
 * @attention 无
 */
int IMP_Encoder_GetChnEncType(int encChn, IMPPayloadType *payLoadType);

/**
 * @fn int IMP_Encoder_SetChnFrmRate(int encChn, const IMPEncoderFrmRate *pstFps)
 *
 * 动态设置帧率控制属性
 *
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstFpsCfg 帧率控制属性参数
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark 调用此API会重新设置编码器帧率属性，帧率属性在下一个GOP生效，最大延时1秒钟生效，调用此API需要通道已经存在。
 * @remark 如果调用IMP_FrameSource_SetChnFPS()函数动态改变系统帧率，那么需要调用该函数修改编码器帧率，完成正确参数配置。
 *
 * @attention 此API只适用于H264和h265编码channel
 * @attention 此API可动态调用
 */
int IMP_Encoder_SetChnFrmRate(int encChn, const IMPEncoderFrmRate *pstFps);

/**
 * @fn int IMP_Encoder_GetChnFrmRate(int encChn, IMPEncoderFrmRate *pstFps)
 *
 * 获取帧率控制属性
 *
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstFpsCfg 帧率控制属性参数
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark 调用此API会获取通道的帧率控制属性，调用此API需要通道已经存在。
 *
 * @attention 此API只适用于H264和h265编码channel
 */
int IMP_Encoder_GetChnFrmRate(int encChn, IMPEncoderFrmRate *pstFps);

/**
 * @fn int IMP_Encoder_SetChnBitRate(int encChn, int iTargetBitRate, int iMaxBitRate)
 *
 * 动态设置码率控制属性
 *
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] iTargetBitRate 目标码率，iMaxBitRate 最大码率。注意码率单位是:"kbit/s"。
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remarks 调用此API会重新设置编码器码率属性，码率属性在下一个GOP生效，最大延时1秒钟生效，调用此API需要通道已经存在。
 *
 * @attention 此API无法设置CVBR的长期码率；CBR模式下仅iTargetBitRate有效，其余模式下仅iMaxBitRate有效
 * @attention 此API只适用于H264和h265编码channel
 * @attention 此API可动态调用
 */
int IMP_Encoder_SetChnBitRate(int encChn, int iTargetBitRate, int iMaxBitRate);

/**
 * @fn int IMP_Encoder_SetChnQpBounds(int encChn, int iMinQP, int iMaxQP);
 *
 * 动态设置码率控制属性MaxQP和MinQP
 *
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] iMinQP iMinQP值,取值范围: [1, 51]
 * @param[in] iMaxQP iMaxQP值,取值范围: [1, 51]
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remarks 调用此API会重新设置编码QP范围。
 *          调用此API需要通道已经存在。
 *
 * @attention 此API只适用于H264和h265编码channel
 * @attention 此API可动态调用
 */
int IMP_Encoder_SetChnQpBounds(int encChn, int iMinQP, int iMaxQP);

/**
 * @fn int IMP_Encoder_SetChnQpBoundsPerFrame(int encChn, int iMinQP_I, int iMaxQP_I, int iMinQP_P, int iMaxQP_P)
 *
 * 动态设置码率控制属性I帧和P帧的MaxQP和MinQP
 *
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] iMinQP_I iMinQP_P值,取值范围: [1, 51]
 * @param[in] iMaxQP_I iMaxQP_P值,取值范围: [1, 51]
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remarks 调用此API会重新设置编码QP范围。
 *          调用此API需要通道已经存在。
 *
 * @attention 此API只适用于H264和h265编码channel
 * @attention 此API可动态调用
 */
int IMP_Encoder_SetChnQpBoundsPerFrame(int encChn, int iMinQP_I, int iMaxQP_I, int iMinQP_P, int iMaxQP_P);

/**
 * @fn int IMP_Encoder_SetChnMaxPictureSize(int encChn, uint32_t MaxPictureSize_I, uint32_t MaxPictureSize_P)
 *
 * 动态配置I帧和P帧的MaxPictureSize
 *
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] MaxPictureSize_I 最大I帧Size，单位："Kbits"
 * @param[in] MaxPictureSize_P 最大P帧Size，单位："Kbits
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remarks 此API需要在通道创建之后调用
 *
 * @attention 此API只适用于H264和h265编码channel
 * @attention 此API可动态调用
 */
int IMP_Encoder_SetChnMaxPictureSize(int encChn, uint32_t MaxPictureSize_I, uint32_t MaxPictureSize_P);

/**
 * @fn int IMP_Encoder_SetChnROI(int encChn, const IMPEncoderROIAttr *pstVencRoiAttr)
 *
 * 设置通道ROI属性
 *
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstVencRoiAttr ROI属性参数
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark 调用此API会设置通道的ROI属性，调用此API需要通道已经存在。
 *
 * @attention 此API只适用于H264和h265编码channel
 */
int IMP_Encoder_SetChnROI(int encChn, const IMPEncoderROIAttr *pstVencRoiAttr);

/**
 * @fn int IMP_Encoder_GetChnROI(int encChn, IMPEncoderROIAttr *pstVencRoiAttr)
 *
 * 获取通道ROI属性
 *
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstVencRoiAttr ROI属性参数
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark 调用此API会获取通道的ROI属性，调用此API需要通道已经存在。
 *
 * @attention 此API只适用于H264和h265编码channel
 */
int IMP_Encoder_GetChnROI(int encChn, IMPEncoderROIAttr *pstVencRoiAttr);

/**
 * @fn int IMP_Encoder_SetChnMapRoi(int encChn, IMPEncoderMapRoiCfg *pstVencMapRoiCfg, IMPEncoderMappingList *list)
 *
 * 设置通道Map ROI属性
 *
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstVencMapRoiCfg Map ROI属性参数
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark 调用此API会设置通道的Map ROI属性，调用此API需要通道已经存在。
 *
 * @attention 此API只适用于H264和h265编码channel
 */
int IMP_Encoder_SetChnMapRoi(int encChn, IMPEncoderMapRoiCfg *pstVencMapRoiCfg, IMPEncoderMappingList *list);

/**
 * @fn int IMP_Encoder_SetChnQpgAI(int encChn, IMPEncoderQpgAICfg *pstVencQpgAICfg)
 *
 * 设置通道Qpg AI属性
 *
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstVencQpgAICfg AI属性参数
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark 调用此API会设置通道的Qpg AI属性，调用此API需要通道已经存在。
 *
 * @attention 此API只适用于H264和h265编码channel
 */
int IMP_Encoder_SetChnQpgAI(int encChn, IMPEncoderQpgAICfg *pstVencQpgAICfg);

/**
 * @fn int IMP_Encoder_SetGOPSize(int encChn, const IMPEncoderGOPSizeCfg *pstGOPSizeCfg)
 *
 * 设置通道GOP属性
 *
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstGOPSizeCfg GOP属性参数
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark 调用此API会设置通道的GOPSize属性，调用此API需要通道已经存在。
 *
 * @attention 此API只适用于H264和h265编码channel
 */
int IMP_Encoder_SetGOPSize(int encChn, const IMPEncoderGOPSizeCfg *pstGOPSizeCfg);

/**
 * @fn int IMP_Encoder_GetGOPSize(int encChn, IMPEncoderGOPSizeCfg *pstGOPSizeCfg)
 *
 * 获取通道GOP属性
 *
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstGOPSizeCfg GOPSize属性参数
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark 调用此API会获取通道的GOPSize属性，调用此API需要通道已经存在。
 *
 * @attention 此API只适用于H264和h265编码channel
 */
int IMP_Encoder_GetGOPSize(int encChn, IMPEncoderGOPSizeCfg *pstGOPSizeCfg);

/**
 * @fn int IMP_Encoder_SetChnFrmUsedMode(int encChn, const IMPEncoderAttrFrmUsed *pfrmUsedAttr)
 *
 * 设置通道输入帧使用模式属性
 *
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pfrmUsedAttr 输入帧使用模式属性参数
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark 调用此API会设置通道的输入帧使用模式属性，调用此API需要通道已经存在。
 *
 * @attention 此API只适用于H264和h265编码channel
 */
int IMP_Encoder_SetChnFrmUsedMode(int encChn, const IMPEncoderAttrFrmUsed *pfrmUsedAttr);

/**
 * @fn int IMP_Encoder_GetChnFrmUsedMode(int encChn, IMPEncoderAttrFrmUsed *pfrmUsedAttr)
 *
 * 获取通道输入帧使用模式属性
 *
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pfrmUsedAttr 输入帧使用模式属性参数
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark 调用此API会获取通道的输入帧使用模式属性，调用此API需要通道已经存在。
 *
 * @attention 此API只适用于H264和h265编码channel
 */
int IMP_Encoder_GetChnFrmUsedMode(int encChn, IMPEncoderAttrFrmUsed *pfrmUsedAttr);

/**
 * @fn int IMP_Encoder_SetChnHSkip(int encChn, const IMPEncoderAttrHSkip *phSkipAttr)
 *
 * 设置通道高级跳帧属性
 *
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] phSkipAttr 高级跳帧属性参数
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark 调用此API会设置通道高级跳帧属性，调用此API需要通道已经存在。
 * @remark 若创建通道时设置的高级跳帧类型是 IMP_Encoder_STYPE_N1X 到 IMP_Encoder_STYPE_N2X 中的一个,
 * 此API设置跳帧类型只能为 IMP_Encoder_STYPE_N1X 或 IMP_Encoder_STYPE_N2X 中的任意一个
 * @remark 若创建通道时设置的高级跳帧类型是 IMP_Encoder_STYPE_N4X 到 IMP_Encoder_STYPE_H1M_TRUE 中的一个,
 * 则可以设置为任意一个高级跳帧类型
 *
 * @attention 此API只适用于H264和H265编码channel
 */
int IMP_Encoder_SetChnHSkip(int encChn, const IMPEncoderAttrHSkip *phSkipAttr);

/**
 * @fn int IMP_Encoder_GetChnHSkip(int encChn, IMPEncoderAttrHSkip *phSkipAttr)
 *
 * 获取通道高级跳帧属性
 *
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] phSkipAttr 高级跳帧属性参数
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark 调用此API会获取通道高级跳帧属性，调用此API需要通道已经存在。
 *
 * @attention 此API只适用于H264和H265编码channel
 */
int IMP_Encoder_GetChnHSkip(int encChn, IMPEncoderAttrHSkip *phSkipAttr);

/**
 * @fn int IMP_Encoder_SetChnHSkipBlackEnhance(int encChn, const int bBlackEnhance)
 *
 * 设置通道高级跳帧中bBlackEnhance属性
 *
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] bBlackEnhance 逻辑值，对应IMPEncoderAttrHSkip中bBlackEnhance值
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark 调用此API会设置通道高级跳帧中bBlackEnhance属性，调用此API需要通道已经存在。
 *
 * @attention 此API只适用于H264和H265编码channel
 */
int IMP_Encoder_SetChnHSkipBlackEnhance(int encChn, const int bBlackEnhance);

/**
 * @fn int IMP_Encoder_InsertUserData(int encChn, void *userData, uint32_t userDataLen)
 *
 * 插入用户数据
 *
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] userData 用户数据指针
 * @param[in] userDataLen 用户数据长度, 取值范围:(0, 1024],以 byte 为单位
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark 调用此API需要通道已经存在
 * @remark 如果通道未创建,则返回失败
 * @remark 如果userData为空或userDataLen为0,则返回失败
 * @remark 插入用户数据,只支持H.264和H.265编码协议
 * @remark 最多分配2块内存空间用于缓存用户数据,且每段用户数据大小不超过1k byte。
 * 如果用户插入的数据多余2块,或插入的一段用户数据大于1k byte 时,此接口会返回错误。
 * @remark 每段用户数据以SEI包的形式被插入到最新的图像码流包之前。在某段用户数据包被编码发送之后,
 * 通道内缓存这段用户数据的内存空间被清零,用于存放新的用户数据
 *
 * @attention 此API只适用于H264和h265编码channel
 */
int IMP_Encoder_InsertUserData(int encChn, void *userData, uint32_t userDataLen);

/**
 * @fn int IMP_Encoder_SetIvpuBsSize(uint32_t ivpuBsSize)
 *
 * 设置ivpu码流buffer的大小
 *
 * @param[in] ivpuBsSize ivpu码流buffer的大小
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remarks 该接口可以设置H264、H265码流buffer大小
 *
 * @attention 调用此函数必须在IMP_System_Init之前
 * @attention 开启分块编码后，内存分配由分块编码属性决定，该接口设置失效
 */
int IMP_Encoder_SetIvpuBsSize(uint32_t ivpuBsSize);

/**
 * @fn int IMP_Encoder_SetJpegBsSize(uint32_t jpegBsSize)
 *
 * 设置jpeg码流buffer的大小
 *
 * @param[in] jpegBsSize jpeg码流buffer的大小
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remarks 该接口可以设置jpeg码流buffer大小
 *
 * @attention 调用此函数必须在IMP_System_Init之前
 */
int IMP_Encoder_SetJpegBsSize(uint32_t jpegBsSize);

/**
 * @fn int IMP_Encoder_SetSuperFrameCfg(int encChn, const IMPEncoderSuperFrmCfg *pstSuperFrmParam)
 *
 * 设置编码超大帧配置
 *
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] pstSuperFrmParam 编码超大帧配置
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark 如果通道未创建,则返回失败
 *
 * @attention 此API只适用于H264和h265编码channel，直通模式下不能使用
 */
int IMP_Encoder_SetSuperFrameCfg(int encChn, const IMPEncoderSuperFrmCfg *pstSuperFrmParam);

/**
 * @fn int IMP_Encoder_GetSuperFrameCfg(int encChn, IMPEncoderSuperFrmCfg *pstSuperFrmParam)
 *
 * 获取编码超大帧配置
 *
 * @param[in] encChn 编码Channel号, 取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstSuperFrmParam 返回编码超大帧配置
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark 如果通道未创建, 则返回失败
 *
 * @attention 此API只适用于H264和h265编码channel
 */
int IMP_Encoder_GetSuperFrameCfg(int encChn, IMPEncoderSuperFrmCfg *pstSuperFrmParam);

/**
 * @fn int IMP_Encoder_SetH264TransCfg(int encChn, const IMPEncoderH264TransCfg *pstH264TransCfg)
 *
 * 设置 H.264 协议编码通道的色度量化属性
 *
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] pstH264TransCfg H.264 协议编码通道的色度量化属性
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark 如果通道未创建,则返回失败
 * @remark 此API只适用于H264
 * @remark 建议在创建编码channel之后，startRecvPic之前调用, 设置时先GetH264TransCfg，然后再SetH264TransCfg
 *
 * @attention 无
 */
int IMP_Encoder_SetH264TransCfg(int encChn, const IMPEncoderH264TransCfg *pstH264TransCfg);

/**
 * @fn int IMP_Encoder_GetH264TransCfg(int encChn, IMPEncoderH264TransCfg *pstH264TransCfg)
 *
 * 获取 H.264 协议编码通道的色度量化属性
 *
 * @param[in] encChn 编码Channel号, 取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstH264TransCfg 返回H.264 协议编码通道的色度量化属性
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark 如果通道未创建, 则返回失败
 * @remark 此API只适用于H264
 *
 * @attention 无
 */
int IMP_Encoder_GetH264TransCfg(int encChn, IMPEncoderH264TransCfg *pstH264TransCfg);

/**
 * @fn int IMP_Encoder_SetH265TransCfg(int encChn, const IMPEncoderH265TransCfg *pstH265TransCfg)
 *
 * 设置 H.265 协议编码通道的色度量化属性
 *
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] pstH265TransCfg H.265 协议编码通道的色度量化属性
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark 如果通道未创建,则返回失败
 * @remark 此API只适用于H265
 * @remark 建议在创建编码channel之后，startRecvPic之前调用, 设置时先GetH265TransCfg，然后再SetH265TransCfg
 *
 * @attention 无
 */
int IMP_Encoder_SetH265TransCfg(int encChn, const IMPEncoderH265TransCfg *pstH265TransCfg);

/**
 * @fn int IMP_Encoder_GetH265TransCfg(int encChn, IMPEncoderH265TransCfg *pstH265TransCfg)
 *
 * 获取 H.265 协议编码通道的色度量化属性
 *
 * @param[in] encChn 编码Channel号, 取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstH265TransCfg 返回H.265 协议编码通道的色度量化属性
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark 如果通道未创建, 则返回失败
 * @remark 此API只适用于H265
 *
 * @attention 无
 */
int IMP_Encoder_GetH265TransCfg(int encChn, IMPEncoderH265TransCfg *pstH265TransCfg);

/**
 * @fn int IMP_Encoder_SetQpgMode(int encChn, const IMPEncoderQpgMode *pstQpgMode)
 *
 * 设置宏块级编码模式
 *
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] pstQpgMode 宏块级编码模式
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark 如果通道未创建,则返回失败
 *
 * @attention 无
 */
int IMP_Encoder_SetQpgMode(int encChn, const IMPEncoderQpgMode *pstQpgMode);

/**
 * @fn int IMP_Encoder_GetQpgMode(int encChn, IMPEncoderQpgMode *pstQpgMode)
 *
 * 获取宏块级编码模式
 *
 * @param[in] encChn 编码Channel号, 取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstQpgMode 返回宏块级编码模式
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark 如果通道未创建, 则返回失败
 *
 * @attention 无
 */
int IMP_Encoder_GetQpgMode(int encChn, IMPEncoderQpgMode *pstQpgMode);

/**
 * @fn int IMP_Encoder_SetSrdCfg(int encChn, const IMPEncoderSrdCfg *pstSrdCfg)
 *
 * 设置SRD功能配置
 *
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] pstSrdCfg SRD配置
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark 如果通道未创建,则返回失败
 * @remark 目前仅H265支持该功能
 *
 * @attention 无
 */
int IMP_Encoder_SetSrdCfg(int encChn, const IMPEncoderSrdCfg *pstSrdCfg);

/**
 * @fn int IMP_Encoder_GetSrdCfg(int encChn, IMPEncoderSrdCfg *pstSrdCfg)
 *
 * 获取SRD功能配置
 *
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstSrdCfg 返回SRD配置
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark 如果通道未创建,则返回失败
 * @remark 目前仅H265支持该功能
 *
 * @attention 无
 */
int IMP_Encoder_GetSrdCfg(int encChn, IMPEncoderSrdCfg *pstSrdCfg);

/**
 * @fn int IMP_Encoder_SetJpegQp(int encChn, int jpegQp)
 *
 * 动态设置JpegQp
 *
 * @param[in] jpegQp jpeg量化Qp值
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remarks 此API必须在通道创建之后调用.
 */
int IMP_Encoder_SetJpegQp(int encChn, int jpegQp);

/**
 * @fn int IMP_Encoder_GetJpegQp(int encChn, int *jpegQp)
 *
 * 获取JpegQp
 *
 * @param[out] jpegQp 返回jpeg量化Qp值
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remarks 此API必须在通道创建之后调用.
 */
int IMP_Encoder_GetJpegQp(int encChn, int *jpegQp);

/**
 * @fn int IMP_Encoder_SetPool(int chnNum, int poolID);
 *
 * 绑定chnnel 到内存池中，即Encoder申请mem从pool申请
 *
 * @param[in] chnNum        通道编号
 * @param[in] poolID        内存池编号
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remarks	  为了解决rmem碎片化，将该channel Encoder绑定到对应的mempool
 * 中, Encoder 申请mem就在mempool中申请，若不调用，Encoder会在rmem中申请
 * 此时对于rmem来说会存在碎片的可能
 *
 * @attention ChannelId 必须大于等于0 且小于32
 */
int IMP_Encoder_SetPool(int chnNum, int poolID);

/**
 * @fn int IMP_Encoder_GetPool(int chnNum);
 *
 * 通过channel ID 获取poolID
 *
 * @param[in] chnNum       通道编号
 *
 * @retval  0 成功
 * @retval  非0 失败
 *
 * @remarks 通过ChannelId 获取PoolId
 *
 * @attention 无
 */
int IMP_Encoder_GetPool(int chnNum);

/**
 * @fn int IMP_Encoder_SetRdBufShare(int encChn, int bEnable)
 *
 * 设置编码通道参考和重建buf的共享
 *
 * @param[in] chnNum       通道编号
 * @param[in] bEnable      是否使能
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remarks 调用此API可设置编码通道参考和重建buf的共享,调用API必须在创建通道之前
 *
 * @attention 默认开启BufShare功能，可以调用该接口关闭
 */
int IMP_Encoder_SetRdBufShare(int encChn, int bEnable);

/**
 * @fn int IMP_Encoder_SetMultiSectionMode(int mode, int size, int cnt)
 *
 * 设置分块编码功能
 *
 * @param[in] mode       设置分块编码模式
 * @param[in] size       设置分块编码每块码流buffer大小，单位KByte
 * @param[in] cnt        设置分块编码码流buffer个数
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remarks mode取值范围为[0,2]
 * @remarks 0:关闭分块编码功能
 * @remarks 1:开启分块编码功能,每次输出为完整一帧码流
 * @remarks 2:开启分块编码功能,每次输出一个片段，可能不是完整一帧,mode2模式下可以通过stream->pack[0].frameEnd == 1判断是否是最后一块
 * @remarks cnt最小取值为2
 *
 * @attention 调用此函数必须在IMP_System_Init之前
 * @attention 默认开启分块编码功能
 * @attention 该接口仅适用于H264/H265
 */
int IMP_Encoder_SetMultiSectionMode(int mode, int size, int cnt);

/**
 * @fn void *IMP_Encoder_VbmAlloc(uint32_t size, uint32_t align);
 *
 * 申请一块size大小，align对齐的物理地址连续内存
 *
 * @param[in] size       内存大小
 * @param[in] align      内存对齐
 *
 * @retval  非NULL       成功
 * @retval  NULL         失败
 *
 * @remarks   无
 *
 * @attention 无
 */
void *IMP_Encoder_VbmAlloc(uint32_t size, uint32_t align);

/**
 * @fn void IMP_Encoder_VbmFree(void *vaddr);
 *
 * 释放一块vaddr的物理地址连续内存
 *
 * @param[in] vaddr     物理地址连续内存地址
 *
 * @retval    NULL      成功
 *
 * @remarks   无
 *
 * @attention 无
 */
void IMP_Encoder_VbmFree(void *vaddr);

/**
 * @fn intptr_t IMP_Encoder_VbmV2P(intptr_t vaddr);
 *
 * 通过物理地址连续内存虚拟地址获取物理地址
 *
 * @param[in] vaddr  物理地址连续内存虚拟地址
 *
 * @retval  非0      成功
 * @retval  0        失败
 *
 * @remarks   无
 *
 * @attention 无
 */
intptr_t IMP_Encoder_VbmV2P(intptr_t vaddr);

/**
 * @fn intptr_t IMP_Encoder_VbmP2V(intptr_t paddr);
 *
 * 通过物理地址连续内存物理地址获取虚拟地址
 *
 * @param[in] vaddr  物理地址连续内存物理地址
 *
 * @retval  非0      成功
 * @retval  0        失败
 *
 * @remarks   无
 *
 * @attention 无
 */
intptr_t IMP_Encoder_VbmP2V(intptr_t paddr);

/**
 * @fn int IMP_Encoder_YuvInit(void **h, int inWidth, int inHeight, IMPEncoderYuvIn *encIn);
 *
 * 编码yuv初始化
 *
 * @param[in] h        编码yuv初始化句柄
 * @param[in] inWidth  编码宽
 * @param[in] inHeight 编码高
 * @param[in] encIn    编码属性结构体
 *
 * @retval  >=0 && < 32     成功
 * @retval  <0              失败
 *
 * @remarks   无
 *
 * @attention 无
 */
int IMP_Encoder_YuvInit(void **h, int inWidth, int inHeight, IMPEncoderYuvIn *encIn);

/**
 * @fn int IMP_Encoder_YuvEncode(void *h, IMPFrameInfo frame, IMPEncoderYuvOut *encOut);
 *
 * 编码yuv
 *
 * @param[in] h			编码yuv初始化句柄
 * @param[in] frame		帧信息
 * @param[in] encOut	码流结构体
 *
 * @retval  >=0 && < 32     成功
 * @retval  <0              失败
 *
 * @remarks   无
 *
 * @attention 无
 */
int IMP_Encoder_YuvEncode(void *h, IMPFrameInfo frame, IMPEncoderYuvOut *encOut);

/**
 * @fn int IMP_Encoder_YuvExit(void *h);
 *
 * 编码yuv反初始化
 *
 * @param[in] h			编码yuv初始化句柄
 *
 * @retval  >=0 && < 32     成功
 * @retval  <0              失败
 *
 * @remarks   无
 *
 * @attention 无
 */
int IMP_Encoder_YuvExit(void *h);

/**
 * @fn int IMP_Encoder_InputJpege(uint8_t *src, uint8_t *dst, int src_w, int src_h, int q, int *stream_length);
 *
 * 外部输入NV12编码JPEG
 *
 * @param[in] *src 源数据地址指针
 * @param[in] *dst 码流数据地址指针
 * @param[in] src_w 图像高
 * @param[in] src_h 图像宽
 * @param[in] q 图像质量控制
 * @param[out] stream_length 码流数据长度
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remarks JPEG宽高2对齐，stride需要16对齐
 *
 * @attention 无
 */
int IMP_Encoder_InputJpege(uint8_t *src, uint8_t *dst, int src_w, int src_h, int q, int *stream_length);

/**
 * @fn void *IMP_Encoder_VbmAlloc_Ex(uint32_t size, uint32_t align);
 *
 * 次进程申请一块size大小，align对齐的物理地址连续内存
 *
 * @param[in] size        内存大小
 * @param[in] align       内存对齐
 *
 * @retval  >=0 && < 32     成功
 * @retval  <0              失败
 *
 * @remarks   无
 *
 * @attention 无
 */
void *IMP_Encoder_VbmAlloc_Ex(uint32_t size, uint32_t align);

/**
 * @fn void IMP_Encoder_VbmFree_Ex(void *vaddr);
 *
 * 次进程释放一块vaddr的物理地址连续内存
 *
 * @param[in] vaddr        物理地址连续内存地址
 *
 * @retval  >=0 && < 32     成功
 * @retval  <0              失败
 *
 * @remarks   无
 *
 * @attention 无
 */
void IMP_Encoder_VbmFree_Ex(void *vaddr);

/**
 * @fn int IMP_Encoder_YuvInit_Ex(int *h, int inWidth, int inHeight, IMPEncoderYuvIn *encIn);
 *
 * 次进程编码yuv初始化.
 *
 * @param[in] h        编码yuv初始化句柄序号
 * @param[in] inWidth  编码宽
 * @param[in] inHeight 编码高
 * @param[in] encIn    编码属性结构体
 *
 * @retval  >=0 && < 32     成功
 * @retval  <0              失败
 *
 * @remarks   无
 *
 * @attention 无
 */
int IMP_Encoder_YuvInit_Ex(int *h, int inWidth, int inHeight, IMPEncoderYuvIn *encIn);

/**
 * @fn int IMP_Encoder_YuvEncode_Ex(int h, IMPFrameInfo frame, IMPEncoderYuvOut *encOut);
 *
 * 次进程编码yuv.
 *
 * @param[in] h			编码yuv初始化句柄序号
 * @param[in] frame		帧信息
 * @param[in] encOut	码流结构体
 *
 * @retval  >=0 && < 32     成功
 * @retval  <0              失败
 *
 * @remarks   无
 *
 * @attention 无
 */
int IMP_Encoder_YuvEncode_Ex(int h, IMPFrameInfo frame, IMPEncoderYuvOut *encOut);

/**
 * @fn int IMP_Encoder_YuvExit_Ex(int h);
 *
 * 次进程编码yuv反初始化.
 *
 * @param[in] h			编码yuv初始化句柄序号
 *
 * @retval  >=0 && < 32     成功
 * @retval  <0              失败
 *
 * @remarks   无
 *
 * @attention 无
 */
int IMP_Encoder_YuvExit_Ex(int h);

/**
 * @fn int IMP_Encoder_InputJpege_Ex(uint8_t *src, uint8_t *dst, int src_w, int src_h, int q, int *stream_length);
 *
 * 次进程外部输入NV12编码JPEG
 *
 * @param[in] *src 源数据地址指针
 * @param[in] *dst 码流数据地址指针
 * @param[in] src_w 图像高
 * @param[in] src_h 图像宽
 * @param[in] q 图像质量控制
 * @param[out] stream_length 码流数据长度
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remarks JPEG宽高2对齐，stride需要16对齐
 *
 * @attention 无
 */
int IMP_Encoder_InputJpege_Ex(uint8_t *src, uint8_t *dst, int src_w, int src_h, int q, int *stream_length);

/**
 * @fn int IMP_Encoder_KernEnc_Stop()
 *
 * 停止所有内核编码通道
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark 无
 *
 * @attention 该接口目前仅低功耗使用
 */
int IMP_Encoder_KernEnc_Stop();

/**
 * @fn int IMP_Encoder_KernEnc_GetStream(int encChn, IMPEncoderKernEncOut *encOut)
 *
 * 获取内核编码通道码流
 *
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] encOut 输出码流结构体
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark 无
 *
 * @attention 该接口目前仅低功耗使用
 */
int IMP_Encoder_KernEnc_GetStream(int encChn, IMPEncoderKernEncOut *encOut);

/**
 * @fn int IMP_Encoder_KernEnc_Release(int encChn)
 *
 * 释放内核编码通道
 *
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark 无
 *
 * @attention 该接口目前仅低功耗使用
 */
int IMP_Encoder_KernEnc_Release(int encChn);

/**
 * @fn int IMP_Encoder_KernEnc_GetStatus(int encChn, int *enable)
 *
 * 获取内核编码通道状态
 *
 * @param[in] encChn 编码Channel号,取值范围: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] enable 内核编码通道状态,0:未使能,1:使能
 *
 * @retval 0 成功
 * @retval 非0 失败
 *
 * @remark 无
 *
 * @attention 该接口目前仅低功耗使用
 */
int IMP_Encoder_KernEnc_GetStatus(int encChn, int *enable);

/**
 * @}
 */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __IMP_ENCODER_H__ */
