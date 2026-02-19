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
 * IMP video encoding header file
 */

/**
 * @defgroup IMP_Encoder
 * @ingroup imp
 * @brief video encoding （JPEG, H264, H265）modules，including video encoding channel management and it's parameter setting and so on
 *
 * @section enc_struct 1 module structure
 * Encoder module internal structure as following:
 * @image html encoder_struct.jpg
 * In this mentioned picture, The coding module consists of a number of Group, each Group consists of encoding Channel.
 * each encoding Channel comes with an output stream buffer, which is composed of a number of buffer.
 *
 * @section enc_channel 2 encoder Channel
 * One coding channel can only deal with one coding protocol entity, each group can add 2 encoding channel;
 *
 * @section enc_rc 3 encoder bitrate control
 * @subsection enc_cbr 3.1 CBR
 * CBR, Constant Bit Rate, the code rate is constant in the rate statistical time.
 * Such as H264 encode, users can set maxQp,minQp,bitrate and so on.
 * maxQp, minQp is used to control the quality range.
 * bitrate is used to control the constant bitrate. (Average coding bit rate for a certain time)
 * when the coding rate is greater than the constant bit rate, the image maxQp will gradually adjust to the QP, when the coding rate is much smaller than the constant bit rate, the image QP will gradually adjust to the minQp.
 * when the image QP reaches maxQP, Qp is clamped to the maximum value, bitrate clamping effect fails, the coding rate might exceed bitrate.
 * when the image QP reaches minQp, QP is clamped to the minimum value, and when the coding rate has reaches the maximum value, the image quality will get better.
 *
 * @subsection enc_FixQP 3.2 FixQP
 * Fix Qp fixes the value of Qp. In the rate statistics time, all the Qp value of the coded image is the same, and the image Qp value is adopted by the user.
 * @{
 */

#define IMP_ENC_ROI_WIN_COUNT 16

#define IMP_ENC_AVC_PROFILE_IDC_BASELINE 66
#define IMP_ENC_AVC_PROFILE_IDC_MAIN 77
#define IMP_ENC_AVC_PROFILE_IDC_HIGH 100
#define IMP_ENC_HEVC_PROFILE_IDC_MAIN 1

/**
* Define the return value
*/
enum
{
	IMP_OK_ENC_ALL					= 0x0 ,			/* Runs fine */
	/* Encoder */
	IMP_ERR_ENC_CHNID				= 0x80040001,	/* Channel ID out of legal range */ /* Encoder */
	IMP_ERR_ENC_PARAM				= 0x80040002, 	/* Parameter out of legal range */
	IMP_ERR_ENC_EXIST				= 0x80040004, 	/* Attempted to request or create a device, channel, or resource that already exists */
	IMP_ERR_ENC_UNEXIST				= 0x80040008, 	/* Attempted to use or destroy a non-existing device, channel or resource */
	IMP_ERR_ENC_NULL_PTR			= 0x80040010, 	/* Null pointer in function parameter */
	IMP_ERR_ENC_NOT_CONFIG			= 0x80040020, 	/* Not configured before use */
	IMP_ERR_ENC_NOT_SUPPORT			= 0x80040040, 	/* Unsupported parameter or function */
	IMP_ERR_ENC_PERM				= 0x80040080, 	/* Operation not allowed */
	IMP_ERR_ENC_NOMEM				= 0x80040100, 	/* Failed to allocate memory */
	IMP_ERR_ENC_NOBUF 				= 0x80040200, 	/* Failed to allocate buffer */
	IMP_ERR_ENC_BUF_EMPTY			= 0x80040400, 	/* No data in buffer */
	IMP_ERR_ENC_BUF_FULL			= 0x80040800, 	/* Buffer full */
	IMP_ERR_ENC_BUF_SIZE 			= 0x80041000, 	/* Insufficient space in buffer */
	IMP_ERR_ENC_SYS_NOTREADY		= 0x80042000, 	/* System is not initialized or corresponding module is not loaded */
	IMP_ERR_ENC_OVERTIME			= 0x80044000, 	/* Wait for timeout */
	IMP_ERR_ENC_RESOURCE_REQUEST	= 0x80048000, 	/* Resource creation, request failure */
};

/**
 * Define the Encoding Channel Stream Profile.
 */
typedef enum {
	IMP_ENC_PROFILE_AVC_BASELINE    = ((PT_H264 << 24) | (IMP_ENC_AVC_PROFILE_IDC_BASELINE)),
	IMP_ENC_PROFILE_AVC_MAIN        = ((PT_H264 << 24) | (IMP_ENC_AVC_PROFILE_IDC_MAIN)),
	IMP_ENC_PROFILE_AVC_HIGH        = ((PT_H264 << 24) | (IMP_ENC_AVC_PROFILE_IDC_HIGH)),
	IMP_ENC_PROFILE_HEVC_MAIN       = ((PT_H265 << 24) | (IMP_ENC_HEVC_PROFILE_IDC_MAIN)),
	IMP_ENC_PROFILE_JPEG            = (PT_JPEG << 24),
} IMPEncoderProfile;

/**
 * Define the Coding Channel code rate controller mode.
 */
typedef enum {
	ENC_RC_MODE_FIXQP               = 0,	/**< Fixqp mode */
	ENC_RC_MODE_CBR                 = 1,	/**< CBR mode */
	ENC_RC_MODE_VBR                 = 2,	/**< VBR mode */
	ENC_RC_MODE_SMART               = 3,	/**< Smart mode */
	ENC_RC_MODE_CVBR                = 4,	/**< CVBR Mode */
	ENC_RC_MODE_AVBR                = 5,	/**< AVBR mode */
	ENC_RC_MODE_INV                 = 6,	/**< INV mode */
} IMPEncoderRcMode;

/**
 * Define video encode channel framerate structure
 * frmRateNum and frmRateDen is LCM must be 1 and GCD must be not greater than 64
 * The least common multiple of the greatest common divisor divisibility between frmRateNum and frmRateDen  can not be more than 64, it is better to get the greatest common divisor number before the settings.
 */
typedef struct {
	uint32_t	frmRateNum;				/**< the tick num in one second, the numerator of framerate */
	uint32_t	frmRateDen;				/**< the tick num in one frame, the denominator of framerate */
} IMPEncoderFrmRate;

/**
 * Define the FixQp ratecontrol attribute of h264 channel
 */
typedef struct {
	uint32_t			IQp;			/**< I frame QP value */
	uint32_t			PQp;			/**< P frame QP value */
	uint32_t			BQp;			/**< B-frame QP value, B-frame is not supported yet */
	bool				blkQpEn;		/**< This determines whether the QP value applies to block QP. */
} IMPEncoderAttrH264FixQP;

/**
 * Define the CBR ratecontrol attribute of h264 channel
 */
typedef struct {
	uint8_t				maxQp;				/**< Maximum QP of image supported by encoder */
	uint8_t				minQp;				/**< Minimum QP of image supported by encoder */
	bool				blkQpEn;			/**< This determines whether the QP value range applies to block QP. */
	uint8_t				initialQp;			/**< First frame QP of image supported by encoder */
	uint8_t				maxIQp;				/**< Maximum I-frame QP of image supported by encoder */
	uint8_t				minIQp;				/**< Minimum I-frame QP of image supported by encoder */
	uint32_t			outBitRate;			/**< Encoder output bitrate in kbps */
	int8_t				iBiasLvl;			/**< Adjust the I-frame QP offset to adjust the I-frame image quality and its stream size, range:[-10,10] */
	uint16_t			IPfrmQPDelta;		/**< IP frame QP change step, range [0,15] */
	uint16_t			PPfrmQPDelta;		/**< PP frame QP change step, range [0,15] */
	uint32_t			staticTime;			/**< Static time, in seconds, the bit rate is stabilized during the statistic time, range [1,60] */
	uint8_t				flucLvl;			/**< Fluctuation level, limit code rate fluctuation range, range:[0,8] */
	uint32_t			qualityLvl;			/**< Quality level, range [0,7], the higher the level, the better the image quality, but the bigger the stream fluctuation */
	uint32_t			maxIprop;			/**< Maximum IP ratio, range[1,100] */
	uint32_t			minIprop;			/**< Minimum IP ratio, range: [1,maxIprop] */
	uint32_t			maxIPictureSize;	/**< Maximum I-frame picture size, unit: "Kbits" */
	uint32_t			maxPPictureSize;	/**< Maximum P-frame picture size, unit: "Kbits" */
} IMPEncoderAttrH264CBR;

/**
 * Define the VBR ratecontrol attribute of h264 channel
 */
typedef struct {
	uint8_t				maxQp;				/**< Maximum QP of image supported by encoder */
	uint8_t				minQp;				/**< Minimum QP of image supported by encoder */
	bool				blkQpEn;			/**< This determines whether the QP value range applies to block QP. */
	uint8_t				initialQp;			/**< First frame QP of image supported by encoder */
	uint8_t				maxIQp;				/**< Maximum I-frame QP of image supported by encoder */
	uint8_t				minIQp;				/**< Minimum I-frame QP of image supported by encoder */
	uint32_t			maxBitRate;			/**< Maximum bit rate of encoder output in kbps */
	int8_t				iBiasLvl;			/**< Adjust I-frame QP offset value to adjust I-frame image quality and its stream size, range:[-10,10] */
	uint32_t			changePos;			/**< Ratio of bitrate to maximum bitrate when VBR starts to adjust Qp, range: [50, 100] */
	uint32_t			staticTime;			/**< Static time, in seconds, the bit rate is stabilized during the statistic time, range [1,60] */
	uint32_t			qualityLvl;			/**< Quality level, range[0,7], the higher the level, the better the image quality, but the bigger the fluctuation of the bitrate */
	uint32_t			maxIprop;			/**< Maximum IP ratio, range[1,100] */
	uint32_t			minIprop;			/**< Minimum IP ratio, range: [1,maxIprop] */
	uint32_t			maxIPictureSize;	/**< Maximum I-frame picture size, unit: "Kbits" */
	uint32_t			maxPPictureSize;	/**< Maximum P-frame picture size, unit: "Kbits" */
} IMPEncoderAttrH264VBR;

/**
 * Define the Smart ratecontrol attribute of h264 channel
 */
typedef struct {
	uint8_t				maxQp;				/**< Maximum QP of image supported by encoder */
	uint8_t				minQp;				/**< Minimum QP of image supported by encoder */
	bool				blkQpEn;			/**< This determines whether the QP value range applies to block QP. */
	uint8_t				initialQp;			/**< First frame QP of image supported by encoder */
	uint8_t				maxIQp;				/**< Maximum I-frame QP of image supported by encoder */
	uint8_t				minIQp;				/**< Minimum I-frame QP of image supported by encoder */
	uint32_t			maxBitRate;			/**< Maximum bit rate of encoder output in kbps */
	int8_t				iBiasLvl;			/**< Adjust I-frame QP offset value to adjust I-frame image quality and its stream size, range:[-10,10] */
	uint32_t			changePos;			/**< Ratio of bitrate to maximum bitrate when VBR starts to adjust Qp, range: [50, 100] */
	uint32_t			staticTime;			/**< Static time, in seconds, the bit rate is stabilized during the statistic time, range [1,60] */
	uint32_t 			qualityLvl;			/**< Quality level, range[0,7], the higher the level, the better the image quality, but the bigger the fluctuation of the bitrate */
	uint32_t 			maxIprop;			/**< Maximum IP ratio, range[1,100] */
	uint32_t 			minIprop;			/**< Minimum IP ratio, range: [1,maxIprop] */
	uint8_t				minStillRate;		/**< Minimum target bit rate percentage for stationary scene,range:[1,100] */
	uint8_t				maxStillQp;			/**< Maximum QP value of I-frame for still scene, range: [1,51] */
	bool				superSmartEn;		/**< Still scene super low bit rate enable */
	uint8_t 			supSmtStillLvl;		/**< Still scene level, the higher the level the more likely it is to be judged as a still scene, only valid in superSmart mode, range:[0,10] */
	uint8_t				supSmtStillRateLvl;	/**< Still scene super low bit rate level, the higher the level the lower the bit rate, only superSmart mode is valid, range:[0,3] */
	uint8_t 			maxSupSmtStillRate;	/**< Percentage of maximum target bitrate for stationary scene, only valid in superSmart mode, range: [1,100] */
	uint32_t			maxIPictureSize;	/**< Maximum I-frame picture size, unit: "Kbits" */
	uint32_t			maxPPictureSize;	/**< Maximum P-frame picture size, unit: "Kbits" */
} IMPEncoderAttrH264Smart;

/**
 * Define the CVBR ratecontrol attribute of h264 channel
 */
typedef struct {
	uint8_t				maxQp;				/**< Maximum QP of image supported by encoder */
	uint8_t				minQp;				/**< Minimum QP of image supported by encoder */
	bool				blkQpEn;			/**< This determines whether the QP value range applies to block QP. */
	uint8_t				initialQp;			/**< First frame QP of image supported by encoder */
	uint8_t				maxIQp;				/**< Maximum I-frame QP of image supported by encoder */
	uint8_t				minIQp;				/**< Minimum I-frame QP of image supported by encoder */
	uint32_t			maxBitRate;			/**< Maximum encoder bit rate in kbps */
	uint32_t			longMaxBitRate;		/**< Long term Maximum bit rate of encoder output, in kbps */
	uint32_t			longMinBitRate;		/**< Encoder's long term minimum bitrate in kbps */
	int8_t				iBiasLvl;			/**< Adjust the QP offset value of I-frame to adjust the image quality of I-frame and its stream size, range:[-10,10] */
	uint32_t			changePos;			/**< Ratio of bitrate to maximum bitrate when VBR starts to adjust Qp, range:[50, 100] */
	uint32_t 			shortStatTime;		/**< Short StatTime, in seconds, the bitrate will be stabilized in the stat time, range [1,60] */
	uint32_t 			longStatTime;		/**< Long StatTime, in seconds, bitrate is stable during the statistic time, range [1, 1440] */
	uint32_t 			qualityLvl;			/**< Quality level, range [0,7], the higher the level, the better the image quality, but the bigger the fluctuation of the bitrate */
	uint32_t 			maxIprop;			/**< Maximum IP ratio, range [1,100] */
	uint32_t 			minIprop;			/**< Minimum IP ratio, range: [1,maxIprop] */
	uint16_t 			extraBitRate;		/**< Encoder output stream maximum overdrawable bits as a percentage of the long term maximum bit rate,range:[0,1000] */
	uint32_t			maxIPictureSize;	/**< Maximum I-frame picture size, unit: "Kbits" */
	uint32_t			maxPPictureSize;	/**< Maximum P-frame picture size, unit: "Kbits" */
} IMPEncoderAttrH264CVBR;

/**
 * Define the AVBR ratecontrol attribute of h264 channel
 */
typedef struct {
	uint8_t				maxQp;				/**< Maximum QP of image supported by encoder */
	uint8_t				minQp;				/**< Minimum QP of image supported by encoder */
	bool				blkQpEn;			/**< This determines whether the QP value range applies to block QP. */
	uint8_t				initialQp;			/**< First frame QP of image supported by encoder */
	uint8_t				maxIQp;				/**< Maximum I-frame QP of image supported by encoder */
	uint8_t				minIQp;				/**< Minimum I-frame QP of image supported by encoder */
	uint32_t			maxBitRate;			/**< Maximum bit rate of encoder output in kbps */
	int8_t				iBiasLvl;			/**< Adjust I-frame QP offset value to adjust I-frame image quality and its stream size, range:[-10,10] */
	uint32_t			changePos;			/**< Ratio of bitrate to maximum bitrate when VBR starts to adjust Qp, range: [50, 100] */
	uint32_t			staticTime;			/**< Static time, in seconds, the bit rate is stabilized during the statistic time, range [1,60] */
	uint32_t			qualityLvl;			/**< qualityLvl, range [0,7], the higher the level, the better the image quality, but the bigger the fluctuation of the bitrate */
	uint32_t			maxIprop;			/**< Maximum IP ratio, range[1,100] */
	uint32_t			minIprop;			/**< Minimum IP ratio, range:[1,maxIprop] */
	uint8_t				minStillRate;		/**< Minimum target bit rate percentage for stationary scene,range:[1,100] */
	uint8_t				maxStillQp;			/**< Maximum I-frame QP for still scene, range:[1,51] */
	uint32_t			maxIPictureSize;	/**< Maximum I-frame picture size, unit: "Kbits" */
	uint32_t			maxPPictureSize;	/**< Maximum P-frame picture size, unit: "Kbits" */
} IMPEncoderAttrH264AVBR;

/**
 * Define the FixQp ratecontrol attribute of h265 channel
 */
typedef struct {
	uint32_t			IQp;			/**< I frame Qp value */
	uint32_t			PQp;			/**< P frame Qp value */
	uint32_t			BQp;			/**< B-frame Qp value, B-frame is not supported yet */
	bool				blkQpEn;		/**< This determines whether the QP value applies to block QP. */
} IMPEncoderAttrH265FixQP;

/**
 * Define the CBR ratecontrol attribute of h265 channel
 */
typedef struct {
	uint8_t				maxQp;				/**< Maximum QP of image supported by encoder */
	uint8_t				minQp;				/**< Minimum QP of image supported by encoder */
	bool				blkQpEn;			/**< This determines whether the QP value range applies to block QP. */
	uint8_t				initialQp;			/**< First frame QP of image supported by encoder */
	uint8_t				maxIQp;				/**< Maximum I-frame QP of image supported by encoder */
	uint8_t				minIQp;				/**< Minimum I-frame QP of image supported by encoder */
	uint32_t			outBitRate;			/**< Encoder output bitrate in kbps */
	int8_t				iBiasLvl;			/**< Adjust the I-frame QP offset to adjust the I-frame image quality and its stream size, range:[-10,10] */
	uint16_t			IPfrmQPDelta;		/**< IP frame QP change step, range [0,15] */
	uint16_t			PPfrmQPDelta;		/**< PP frame QP change step, range [0,15] */
	uint32_t			staticTime;			/**< Static time, in seconds, the bit rate is stabilized during the statistic time, range [1,60] */
	uint8_t				flucLvl;			/**< fluctuation level, limit code rate fluctuation range, range:[0,8] */
	uint32_t			qualityLvl;			/**< Quality level, range [0,7], the higher the level, the better the image quality, but the bigger the stream fluctuation */
	uint32_t			maxIprop;			/**< Maximum IP ratio, range[1,100] */
	uint32_t			minIprop;			/**< Minimum IP ratio, range: [1,maxIprop] */
	uint32_t			maxIPictureSize;	/**< Maximum I-frame picture size, unit: "Kbits" */
	uint32_t			maxPPictureSize;	/**< Maximum P-frame picture size, unit: "Kbits" */
} IMPEncoderAttrH265CBR;

/**
 * Define the VBR ratecontrol attribute of h265 channel
 */
typedef struct {
	uint8_t				maxQp;				/**< Maximum QP of image supported by encoder */
	uint8_t				minQp;				/**< Minimum QP of image supported by encoder */
	bool				blkQpEn;			/**< This determines whether the QP value range applies to block QP. */
	uint8_t				initialQp;			/**< First frame QP of image supported by encoder */
	uint8_t				maxIQp;				/**< Maximum I-frame QP of image supported by encoder */
	uint8_t				minIQp;				/**< Minimum I-frame QP of image supported by encoder */
	uint32_t			maxBitRate;			/**< Maximum bit rate of encoder output in kbps */
	int8_t				iBiasLvl;			/**< Adjust I-frame QP offset value to adjust I-frame image quality and its stream size, range:[-10,10] */
	uint32_t			changePos;			/**< Ratio of bitrate to maximum bitrate when VBR starts to adjust Qp, range: [50, 100] */
	uint32_t			staticTime;			/**< Static time, in seconds, the bit rate is stabilized during the statistic time, range [1,60] */
	uint32_t			qualityLvl;			/**< qualityLvl, range[0,7], the higher the level, the better the image quality, but the bigger the fluctuation of the bitrate */
	uint32_t			maxIprop;			/**< Maximum IP ratio, range[1,100] */
	uint32_t			minIprop;			/**< Minimum IP ratio, range: [1,maxIprop] */
	uint32_t			maxIPictureSize;	/**< Maximum I-frame picture size, unit: "Kbits" */
	uint32_t			maxPPictureSize;	/**< Maximum P-frame picture size, unit: "Kbits" */
} IMPEncoderAttrH265VBR;

/**
 * Define the Smart ratecontrol attribute of h265 channel
 */
typedef struct {
	uint8_t				maxQp;				/**< Maximum QP of image supported by encoder */
	uint8_t				minQp;				/**< Minimum QP of image supported by encoder */
	bool				blkQpEn;			/**< This determines whether the QP value range applies to block QP. */
	uint8_t				initialQp;			/**< First frame QP of image supported by encoder */
	uint8_t				maxIQp;				/**< Maximum I-frame QP of image supported by encoder */
	uint8_t				minIQp;				/**< Minimum I-frame QP of image supported by encoder */
	uint32_t			maxBitRate;			/**< Maximum bit rate of encoder output in kbps */
	int8_t				iBiasLvl;			/**< Adjust I-frame QP offset value to adjust I-frame image quality and its stream size, range:[-10,10] */
	uint32_t			changePos;			/**< Ratio of bitrate to maximum bitrate when VBR starts to adjust Qp, range: [50, 100] */
	uint32_t			staticTime;			/**< Static time, in seconds, the bit rate is stabilized during the statistic time, range [1,60] */
	uint32_t 			qualityLvl;			/**< qualityLvl, range[0,7], the higher the level, the better the image quality, but the bigger the fluctuation of the bitrate */
	uint32_t 			maxIprop;			/**< Maximum IP ratio, range[1,100] */
	uint32_t 			minIprop;			/**< Minimum IP ratio, range: [1,maxIprop] */
	uint8_t				minStillRate;		/**< Minimum target bit rate percentage for stationary scene,range:[1,100] */
	uint8_t				maxStillQp;			/**< Maximum QP value of I-frame for still scene, range: [1,51] */
	bool				superSmartEn;		/**< Still scene super low bit rate enable */
	uint8_t 			supSmtStillLvl;		/**< Still scene level, the higher the level the more likely it is to be judged as a still scene, only valid in superSmart mode, range:[0,10] */
	uint8_t				supSmtStillRateLvl;	/**< Still scene super low bit rate level, the higher the level the lower the bit rate, only superSmart mode is valid, range:[0,3] */
	uint8_t 			maxSupSmtStillRate;	/**< Percentage of maximum target bitrate for stationary scene, only valid in superSmart mode, range: [1,100] */
	uint32_t			maxIPictureSize;	/**< Maximum I-frame picture size, unit: "Kbits" */
	uint32_t			maxPPictureSize;	/**< Maximum P-frame picture size, unit: "Kbits" */
} IMPEncoderAttrH265Smart;

/**
 * Define the CVBR ratecontrol attribute of h265 channel
 */
typedef struct {
	uint8_t				maxQp;				/**< Maximum QP of image supported by encoder */
	uint8_t				minQp;				/**< Minimum QP of image supported by encoder */
	bool				blkQpEn;			/**< This determines whether the QP value range applies to block QP. */
	uint8_t				initialQp;			/**< First frame QP of image supported by encoder */
	uint8_t				maxIQp;				/**< Maximum I-frame QP of image supported by encoder */
	uint8_t				minIQp;				/**< Minimum I-frame QP of image supported by encoder */
	uint32_t			maxBitRate;			/**< Maximum encoder bit rate in kbps */
	uint32_t			longMaxBitRate;		/**< Long term Maximum bit rate of encoder output, in kbps */
	uint32_t			longMinBitRate;		/**< Encoder's long term minimum bitrate in kbps */
	int8_t				iBiasLvl;			/**< Adjust the QP offset value of I-frame to adjust the image quality of I-frame and its stream size, range:[-10,10] */
	uint32_t			changePos;			/**< Ratio of bitrate to maximum bitrate when VBR starts to adjust Qp, range:[50, 100] */
	uint32_t 			shortStatTime;		/**< Short StatTime, in seconds, the bitrate will be stabilized in the stat time, range [1,60] */
	uint32_t 			longStatTime;		/**< Long StatTime, in seconds, bitrate is stable during the statistic time, range [1, 1440] */
	uint32_t 			qualityLvl;			/**< Quality level, range [0,7], the higher the level, the better the image quality, but the bigger the fluctuation of the bitrate */
	uint32_t 			maxIprop;			/**< Maximum IP ratio, range [1,100] */
	uint32_t 			minIprop;			/**< Minimum IP ratio, range: [1,maxIprop] */
	uint16_t 			extraBitRate;		/**< Encoder output stream maximum overdrawable bits as a percentage of the long term maximum bit rate,range:[0,1000] */
	uint32_t			maxIPictureSize;	/**< Maximum I-frame picture size, unit: "Kbits" */
	uint32_t			maxPPictureSize;	/**< Maximum P-frame picture size, unit: "Kbits" */
} IMPEncoderAttrH265CVBR;

/**
 * Define the AVBR ratecontrol attribute of h265 channel
 */
typedef struct {
	uint8_t				maxQp;				/**< Maximum QP of image supported by encoder */
	uint8_t				minQp;				/**< Minimum QP of image supported by encoder */
	bool				blkQpEn;			/**< This determines whether the QP value range applies to block QP. */
	uint8_t				initialQp;			/**< First frame QP of image supported by encoder */
	uint8_t				maxIQp;				/**< Maximum I-frame QP of image supported by encoder */
	uint8_t				minIQp;				/**< Minimum I-frame QP of image supported by encoder */
	uint32_t			maxBitRate;			/**< Maximum bit rate of encoder output in kbps */
	int8_t				iBiasLvl;			/**< Adjust I-frame QP offset value to adjust I-frame image quality and its stream size, range:[-10,10] */
	uint32_t			changePos;			/**< Ratio of bitrate to maximum bitrate when VBR starts to adjust Qp, range: [50, 100] */
	uint32_t			staticTime;			/**< Static time, in seconds, the bit rate is stabilized during the statistic time, range [1,60] */
	uint32_t			qualityLvl;			/**< qualityLvl, range [0,7], the higher the level, the better the image quality, but the bigger the fluctuation of the bitrate */
	uint32_t			maxIprop;			/**< Maximum IP ratio, range[1,100] */
	uint32_t			minIprop;			/**< Minimum IP ratio, range:[1,maxIprop] */
	uint8_t				minStillRate;		/**< Minimum target bit rate percentage for stationary scene,range:[1,100] */
	uint8_t				maxStillQp;			/**< Maximum I-frame QP for still scene, range:[1,51] */
	uint32_t			maxIPictureSize;	/**< Maximum I-frame picture size, unit: "Kbits" */
	uint32_t			maxPPictureSize;	/**< Maximum P-frame picture size, unit: "Kbits" */
} IMPEncoderAttrH265AVBR;

/**
 * Define the FixQP ratecontrol attribute of jpeg channel
 */
typedef struct {
	uint32_t			qp;			/**< qp value, range:[0,98] */
} IMPEncoderAttrJPEGFixQP;

/**
 * Define the denoise attribute of h264 and h265 channel, the enable member can't be changed after create channel, buf other members can be changed any time after create channel
 */
typedef struct {
	bool			enable;			/**< whether denoise function is enabled/disabled , 0:disable, 1:enable */
	int				dnType;			/**< denoise type,0:NONE-no denoise, 1:IP-loss info most, 2:II-loss info less */
	int				dnIQp;			/**< I slice quantization parameter */
	int				dnPQp;			/**< P slice quantization parameter */
} IMPEncoderAttrDenoise;

/**
 * Define the input frame usage mode of h264 and h265 channel
 */
typedef enum {
	ENC_FRM_BYPASS	= 0,		/**< Sequential full use mode - default mode */
	ENC_FRM_REUSED	= 1,		/**< repeat use of a frame mode*/
	ENC_FRM_SKIP	= 2,		/**< Frame loss mode */
} EncFrmUsedMode;

/**
 * Define the input frame usage mode attribute of h264 and h265 channel
 */
typedef struct {
	bool				enable;			/**< whether enale/disable input frame usage mode */
	EncFrmUsedMode		frmUsedMode;	/**< input frame usage mode variable */
	uint32_t			frmUsedTimes;	/**< the frame interval (repeat or skip mode) */
} IMPEncoderAttrFrmUsed;

/**
 * Define the encode skip type of h264 and h265 channel
 */
typedef enum {
	IMP_Encoder_STYPE_N1X       = 0,	/**< 1 time (skip frame reference) */
	IMP_Encoder_STYPE_N2X       = 1,	/**< 2 times (skip frame reference) */
	IMP_Encoder_STYPE_N4X       = 2,	/**< 4 times (skip frame reference) */
	IMP_Encoder_STYPE_HN1_FALSE = 3,	/**< high skip frame reference mode:N1 open skip frame */
	IMP_Encoder_STYPE_HN1_TRUE	= 4,	/**< high skip frame reference mode:N1 close skip frame */
	IMP_Encoder_STYPE_H1M_FALSE = 5,	/**< high skip frame reference mode:1M open skip frame */
	IMP_Encoder_STYPE_H1M_TRUE  = 6,	/**< high skip frame reference mode:1M close skip frame */
} IMPSkipType;

/**
 * Define the encode ref type of h264 and h265 channel
 */
typedef enum {
	IMP_Encoder_FSTYPE_IDR		= 0,	/**< the idr frame in high skip frame reference mode */
	IMP_Encoder_FSTYPE_LBASE	= 1,	/**< the long base(p) frame in high skip frame reference mode */
	IMP_Encoder_FSTYPE_SBASE	= 2,	/**< the short base(p) frame in high skip frame reference mode */
	IMP_Encoder_FSTYPE_ENHANCE	= 3,	/**< the enhance(p) frame in high skip frame reference mode */
} IMPRefType;

/**
 * Define high skip frame type structure of h264 and h265 channel
 */
typedef struct {
	IMPSkipType	skipType;           /**< skip type */
	int			m;                  /**< enhance frame interval */
	int			n;                  /**< base frame interval */
	int			maxSameSceneCnt;    /**< one scene over gop num, only effect to H1M skip type, when set more than 1, m no effect */
	int			bEnableScenecut;    /**< is enable scenecut? 0: not, 1: yes, only effect to H1M Skip type, only effect to SMART rc mode */
	int			bBlackEnhance;      /**< be made to use black coded bitstream to enhance frame? */
} IMPEncoderAttrHSkip;

/**
 * Define high skip frame type init structure of h264 and h265 channel
 */
typedef struct {
	IMPEncoderAttrHSkip	hSkipAttr;	  /**< high skip frame type attr */
	IMPSkipType			maxHSkipType; /**< must used max skip type, effect rmem size, N1X to N2X need 2 rd frame space, N4X to H1M_TRUE need 3 rd frame space size, should set according to your hskip requirement*/
} IMPEncoderAttrInitHSkip;

/**
 * Define the h264, h265 and jpeg encoder channel ratecontroller mode attribute
 */
typedef struct {
	IMPEncoderRcMode rcMode;						/**< ratecontrol mode */
	union {
		IMPEncoderAttrH264FixQP	 attrH264FixQp;		/**< the H.264 protocol FixQp ratecontrol attribute  */
		IMPEncoderAttrH264CBR	 attrH264Cbr;		/**< the H.264 protocol CBR ratecontrol attribute */
		IMPEncoderAttrH264VBR	 attrH264Vbr;		/**< the H.264 protocol VBR ratecontrol attribute */
		IMPEncoderAttrH264Smart	 attrH264Smart;		/**< the H.264 protocol Smart ratecontrol attribute */
		IMPEncoderAttrH264CVBR   attrH264CVbr; 		/**< the H.264 protocol CVBR ratecontrol attribute */
		IMPEncoderAttrH264AVBR   attrH264AVbr; 		/**< the H.264 protocol AVBR ratecontrol attribute */

		IMPEncoderAttrH265FixQP	 attrH265FixQp;		/**< the H.265 protocol FixQp ratecontrol attribute  */
		IMPEncoderAttrH265CBR	 attrH265Cbr;		/**< the H.265 protocol CBR ratecontrol attribute */
		IMPEncoderAttrH265VBR	 attrH265Vbr;		/**< the H.265 protocol VBR ratecontrol attribute */
		IMPEncoderAttrH265Smart	 attrH265Smart;		/**< the H.265 protocol Smart ratecontrol attribute */
		IMPEncoderAttrH265CVBR   attrH265CVbr; 		/**< the H.265 protocol CVBR ratecontrol attribute */
		IMPEncoderAttrH265AVBR   attrH265AVbr; 		/**< the H.265 protocol AVBR ratecontrol attribute */

		IMPEncoderAttrJPEGFixQP	 attrJPEGFixQp;		/**< the JPEG protocol Fixqp ratecontrol attribute */
	};
} IMPEncoderAttrRcMode;

/**
 * Define the h264, h265 and jpeg encoder channel ratecontroller attribute
 */
typedef struct {
	IMPEncoderFrmRate           outFrmRate;		/**< output framerate, (frame output shouldn't be bigger than input framerate) */
	uint32_t			        maxGop;			/**< gop value，suggested to be an integer multiple of the framerate */
    IMPEncoderAttrRcMode        attrRcMode;     /**< ratecontrol mode attribute */
	IMPEncoderAttrFrmUsed	    attrFrmUsed;	/**< input frame usage mode attribute */
	IMPEncoderAttrDenoise	    attrDenoise;	/**< denoise attribute */
	IMPEncoderAttrInitHSkip	    attrHSkip;		/**< high skip frame type attribute */
} IMPEncoderRcAttr;

/**
 * H264 stream NAL unit type codes
 */
typedef enum {
	IMP_H264_NAL_UNKNOWN	= 0,	/**< Unspecified */
	IMP_H264_NAL_SLICE		= 1,	/**< Coded slice of a non-IDR picture  */
	IMP_H264_NAL_SLICE_DPA	= 2,	/**< Coded slice data partition A */
	IMP_H264_NAL_SLICE_DPB	= 3,	/**< Coded slice data partition B */
	IMP_H264_NAL_SLICE_DPC	= 4,	/**< Coded slice data partition C */
	IMP_H264_NAL_SLICE_IDR	= 5,	/**< Coded slice of an IDR picture */
	IMP_H264_NAL_SEI		= 6,	/**< Supplemental enhancement information(SEI) */
	IMP_H264_NAL_SPS		= 7,	/**< Sequence parameter set */
	IMP_H264_NAL_PPS		= 8,	/**< Picture parameter set */
	IMP_H264_NAL_AUD		= 9,	/**< Access unit delimiter */
	IMP_H264_NAL_FILLER		= 12,	/**< Filler data */
} IMPEncoderH264NaluType;

/**
 * H265 stream NAL unit type codes
 */
typedef enum {
    IMP_H265_NAL_SLICE_TRAIL_N      = 0,        /**< Coded slice segment of a non-TSA, non-STSA trailing picture, none reference */
    IMP_H265_NAL_SLICE_TRAIL_R      = 1,        /**< Coded slice segment of a non-TSA, non-STSA trailing picture, with reference */
    IMP_H265_NAL_SLICE_TSA_N        = 2,        /**< Coded slice segment of a temporal sub-layer access picture, none reference */
    IMP_H265_NAL_SLICE_TSA_R        = 3,        /**< Coded slice segment of a temporal sub-layer access picture, with reference */
    IMP_H265_NAL_SLICE_STSA_N       = 4,        /**< Coded slice segment of a step-wise temporal sub-layer access picture, none reference */
    IMP_H265_NAL_SLICE_STSA_R       = 5,        /**< Coded slice segment of a step-wise temporal sub-layer access picture, with reference */
    IMP_H265_NAL_SLICE_RADL_N       = 6,        /**< Coded slice segment of a random access decodable leading picture, none reference */
    IMP_H265_NAL_SLICE_RADL_R       = 7,        /**< Coded slice segment of a random access decodable leading picture, with reference */
    IMP_H265_NAL_SLICE_RASL_N       = 8,        /**< Coded slice segment of a random access skipped leading picture, none reference*/
    IMP_H265_NAL_SLICE_RASL_R       = 9,        /**< Coded slice segment of a random access skipped leading picture, with reference */
    IMP_H265_NAL_SLICE_BLA_W_LP     = 16,       /**< Coded slice segment of a broken link access picture, with leading picture */
    IMP_H265_NAL_SLICE_BLA_W_RADL   = 17,       /**< Coded slice segment of a broken link access picture, with leading RADL */
    IMP_H265_NAL_SLICE_BLA_N_LP     = 18,       /**< Coded slice segment of a broken link access picture, none leading picture */
    IMP_H265_NAL_SLICE_IDR_W_RADL   = 19,       /**< Coded slice segment of an instantaneous decoding refresh picture, with RADL */
    IMP_H265_NAL_SLICE_IDR_N_LP     = 20,       /**< Coded slice segment of an instantaneous decoding refresh picture, none leading picture */
    IMP_H265_NAL_SLICE_CRA          = 21,       /**< Coded slice segment of a clean random access picture, with leading picture */
    IMP_H265_NAL_VPS                = 32,       /**< video parameter set */
    IMP_H265_NAL_SPS                = 33,       /**< sequence parameter set */
    IMP_H265_NAL_PPS                = 34,       /**< picture parameter set */
    IMP_H265_NAL_AUD                = 35,       /**< access unit delimiter */
    IMP_H265_NAL_EOS                = 36,       /**< end of sequence */
    IMP_H265_NAL_EOB                = 37,       /**< end of bitstream */
    IMP_H265_NAL_FILLER_DATA        = 38,       /**< filler data */
    IMP_H265_NAL_PREFIX_SEI         = 39,       /**< prifix supplemental enhancement information */
    IMP_H265_NAL_SUFFIX_SEI         = 40,       /**< suffix supplemental enhancement information */
    IMP_H265_NAL_INVALID            = 64,       /**< invalid nal unit type */
} IMPEncoderH265NaluType;

/**
 * Define the h264 and h265 bitstream nal type
 */
typedef union {
	IMPEncoderH264NaluType		h264Type;		/**< H264 stream NAL unit type code */
	IMPEncoderH265NaluType		h265Type;		/**< H265 stream NAL unit type code */
} IMPEncoderDataType;

/**
 * Define frame bitstream packet structure
 */
typedef struct {
	uint32_t	phyAddr;			/**< bitstream packet physical address */
	uint32_t	virAddr;			/**< bitstream packet virtual address */
	uint32_t	length;				/**< bitstram packet length */
	int64_t		timestamp;			/**< timestamp，unit:us */
	bool		frameEnd;			/**< frame end mark */
	IMPEncoderDataType	dataType;	/**< h264 and h265 bitstream nal unit type */
} IMPEncoderPack;

/**
 * Define the bitstream structure of one frame
 */
typedef struct {
	IMPEncoderPack  *pack;			/**< bitstream packet */
	uint32_t        packCount;		/**< packet count related to one frame */
	uint32_t        seq;			/**< bitstream sequence number */
    IMPRefType      refType;		/**< h264 and h265 reference type of encode frame */
} IMPEncoderStream;

/**
 * Define the encoder crop attribute(crop first, scaler second)
 */
typedef struct {
    bool	enable;			/**< whether enable/disable crop, false:disable, true: enable */
    uint32_t	x;			/**< the left-top x-coordinate of crop region */
    uint32_t	y;			/**< the left-top y-coordinate of crop region */
    uint32_t	w;			/**< the width of crop region */
    uint32_t	h;			/**< the height of crop region */
} IMPEncoderCropCfg;

/**
 * Define insert user data attribute of h264 and h265 channel
 */
typedef struct {
	uint32_t			maxUserDataCnt;		/**< User's Maximum number of insert data cache, range:0-2 */
	uint32_t			maxUserDataSize;	/**< User's Maximum size of insert data cache, range:16-1024 */
} IMPEncoderUserDataCfg;

/**
 * Define encoder attribute structure
 */
typedef struct {
	IMPPayloadType			enType;			/**< encode protocal type */
	uint32_t				bufSize;		/**< Configure buffer size，shouldn't be less than width*height*3/2. When setting the channel encoding property, set this parameter to 0, IMP will automatically calculate the size*/
	uint32_t				profile;		/**< encode profile, 0: baseline; 1:MP; 2:HP */
	uint32_t				picWidth;		/**< frame width, must be 16 aligned,shouldn't less than 256 */
	uint32_t				picHeight;		/**< frame height, shouldn't less than 16 */
	IMPEncoderCropCfg		crop;			/**< crop attributel */
	IMPEncoderUserDataCfg	userData;		/**< insert userdata attribute, only for h264 and h265*/
} IMPEncoderAttr;

/**
 * Define encoder channel attribute structure
 */
typedef struct {
	IMPEncoderAttr      encAttr;     /**< encoder attribute */
	IMPEncoderRcAttr    rcAttr;      /**< ratecontrol attribute, only for h264 and h265 */
	bool                bEnableIvdc; /**< Enable ISP VPU Direct Connect */
} IMPEncoderCHNAttr;

/**
 * Define encode channel state attribute structure
 */
typedef struct {
	bool		registered;			/**< registered to group variable, 0:no,1:yes */
	uint32_t	leftPics;			/**< Number of images to be encoded */
	uint32_t	leftStreamBytes;	/**< Number of Stream buffer remaining byte */
	uint32_t	leftStreamFrames;	/**< Number of Stream buffer remaining frames */
	uint32_t	curPacks;			/**< Number of packets in current frame */
	uint32_t	work_done;			/**< work done state，0：running，1，not running */
} IMPEncoderCHNStat;

/**
 * Define color to grey parameter
 */
typedef struct {
    bool	enable;			/**< variable to enable color to grey, 0: no, 1: yes */
} IMPEncoderColor2GreyCfg;

/**
 * Define the h264 and h265 channel enalbe IDR parameter
 */
typedef struct {
    bool	enable;			/**< Configuration of EnableIDR, 0:disable, 1:enable */
} IMPEncoderEnIDRCfg;

/**
 * Define the h264 and h265 channel gopsize parameter
 */
typedef struct {
	int		gopsize;		/**< IDR parameters */
} IMPEncoderGOPSizeCfg;

/**
 * Define H.264 and H.265 channel ROI QP mode
 */
typedef enum {
	IMP_ROI_QPMODE_DISABLE		= 0,	/**< Disable ROI */
	IMP_ROI_QPMODE_FIXED_QP		= 1,	/**< Absolute ROI */
	IMP_ROI_QPMODE_DELTA		= 2,	/**< Relative ROI */
	IMP_ROI_QPMODE_MAX_ENUM,
} IMPEncoderQPMode;

/**
 * Define H.264 and H.265 channel ROI parameters
 */
typedef struct {
	uint32_t	u32Index;	/**< ROI region index value, support 0-7 */
	bool		bEnable;	/**< Whether to enable the ROI function of this region */
	bool		bRelatedQp;	/**< 0: absolute ROI, 1: relative ROI */
	int			s32Qp;		/**< Relative or absolute qp value of the ROI region */
	IMPRect		rect;		/**< Region attribute */
} IMPEncoderROICfg;

/**
 * Define the H.264 and H.265 channel ROI attribute
 */
typedef struct {
	IMPEncoderROICfg roi[IMP_ENC_ROI_WIN_COUNT];	/**< ROI attribute */
} IMPEncoderROIAttr;

/**
 * Define the Map ROI QP values at different targets
 */
typedef struct {
	uint8_t *mapdata;
	uint32_t length;
} IMPEncoderMappingList;

/**
 * Define the Map ROI type of mapping
 */
typedef enum {
	IMP_MAPPINGTYPE_DIRECT,		/**< Direct mapping */
	IMP_MAPPINGTYPE_DEVIOUS,	/**< Devious mapping */
	IMP_MAPPINGTYPE_BUTT,		/**< Used to determine the validity of parameters, it must be less than this value */
} IMPEncoderMappingType;

/**
 * Define H.264 and H.265 channel Map ROI attribute
 */
typedef struct {
	uint8_t*				map;		/**< Pointer to Map ROI attribute array */
	uint32_t				mapSize;	/**< Map ROI attribute array size */
	IMPEncoderMappingType	type;		/**< Map ROI type of mapping */
	int32_t					reserved;	/**< Reserved parameters */
} IMPEncoderMapRoiCfg;

/**
 * Define H.264 and H.265 channel QpgAI attribute
 */
typedef struct {
	uint8_t*				map;			/**< Pointer to Qpg AI attribute array */
	uint32_t				width;			/**< Algorithm output width */
	uint32_t				height;			/**< Algorithm output height */
	uint8_t					foreBackMode;	/**< Intelligent encoding mode, range: [0,2], 0:default effect, 1:save bitrate, 2:enhance quality */
	uint8_t					markLvl;		/**< Intelligent encoding mode, range: [0,3], only AVBR, SMART mode */
	int32_t					reserved;		/**< Reserved parameter */
} IMPEncoderQpgAICfg;

/**
 * Define h264 and h265 channel process strategy of ratecontrol super frame
 */
typedef enum {
    IMP_RC_SUPERFRM_NONE        = 0,    /**< no strategy (supported) */
    IMP_RC_SUPERFRM_DISCARD     = 1,    /**< drop super frame (unsupported), users should decide whether drop or not */
    IMP_RC_SUPERFRM_REENCODE    = 2,    /**< reencoder super frame (supported), default, and only effective when bufShare is not enabled */
    IMP_RC_SUPERFRM_BUTT        = 3,
} IMPEncoderSuperFrmMode;

/**
 * Define h264 and h265 channel priority type of ratecontrol
 */
typedef enum {
    IMP_RC_PRIORITY_RDO                 = 0,    /**< rdo priority */
    IMP_RC_PRIORITY_BITRATE_FIRST       = 1,    /**< target frame rate first */
    IMP_RC_PRIORITY_FRAMEBITS_FIRST     = 2,    /**< super frame threshold first */
    IMP_RC_PRIORITY_BUTT                = 3,
} IMPEncoderRcPriority;

/**
 * Define h264 and h265 channel Paramete of super frame process strategy
 */
typedef struct {
    IMPEncoderSuperFrmMode      superFrmMode;       /**< super frame process strategy, default:IMP_RC_SUPERFRM_NONE  */
    uint32_t                    superIFrmBitsThr;   /**< super I frame threshold, default: bufSize*8 */
    uint32_t                    superPFrmBitsThr;   /**< super P frame threadhold, default:super I frame threshold divide by 1.4 */
    uint32_t                    superBFrmBitsThr;   /**< super B frame threadhold, default:super P frame threshold divide by 1.3 */
    IMPEncoderRcPriority        rcPriority;         /**< priority of ratecontrol, default: RDO */
	uint8_t 					maxReEncodeTimes; 	/**< maximum Re-Encode Times, only valid in IMP_RC_SUPERFRM_REENCODE mode, range:[1,3] */
} IMPEncoderSuperFrmCfg;

/**
 * Define H.264 encoder channel chroma quantization struct
 */
typedef struct {
    int         chroma_qp_index_offset;     /**< refer to  H.264 prococol, system default value is 0; range:[-12, 12] */
} IMPEncoderH264TransCfg;

/**
 * Define H.265 encoder channel chroma quantization struct
 */
typedef struct {
    int         chroma_cr_qp_offset;     /**< refer to  H.265 prococol, system default value is 0; range:[-12, 12] */
    int         chroma_cb_qp_offset;     /**< refer to  H.265 prococol, system default value is 0; range:[-12, 12] */
} IMPEncoderH265TransCfg;

/**
 * Define macroblock ratecontrol mode struct
 */
typedef enum {
	ENC_MBQP_AUTO        = 0,    /**< Automatically select macroblock level encoding control mode (default) */
	ENC_MBQP_MAD         = 1,    /**< Enable MAD mode */
	ENC_MBQP_TEXT        = 2,    /**< Enable TEXT mode */
	ENC_MBQP_ROWRC       = 3,    /**< Enable ROWRC mode */
	ENC_MBQP_MAD_ROWRC   = 4,    /**< Enable MAD mode and ROWRC mode */
	ENC_MBQP_TEXT_ROWRC  = 5,    /**< Enables TEXT mode and ROWRC mode */
} IMPEncoderQpgMode;

/**
 * Define the H.265 channel SRD configuration structure
 */
typedef struct {
	bool            enable; 	/**< Whether to enable SRD function */
	uint8_t         level;		/**< SRD function level, the higher the level, the lower the bitrate of static scene, range: [0,3] */
} IMPEncoderSrdCfg;

/**
 * Define unbound encoding mode output structure
 */
typedef struct {
	void *outAddr;			/**< Output stream address */
	uint32_t outLen;		/**< Output stream length */
} IMPEncoderYuvOut;

/**
 * Define the unbound encoding mode input structure
 */
typedef struct {
	IMPPayloadType type;			/**< Encoding type */
	IMPEncoderAttrRcMode mode;		/**< Ratecontrol mode */
	IMPEncoderFrmRate outFrmRate;	/**< Frame rate */
	uint32_t maxGop;				/**< GOP length */
} IMPEncoderYuvIn;

/**
 * Define kernel decode struct
 */
typedef struct {
	IMPPayloadType		type;			/**< Stream type */
	uint32_t			bufAddr;		/**< Virtual address of stream buffer */
	uint32_t			bufLen;			/**< Stream buffer total length */
	uint32_t			strmCnt;		/**< Stream counts */
	uint32_t			index;			/**< Current stream index */
	uint32_t			strmAddr;		/**< Current stream virtual address */
	uint32_t			strmLen;		/**< Current stream length */
	int64_t				timestamp;		/**< Current stream timestamp, uint: us */
} IMPEncoderKernEncOut;

/**
 * @fn int IMP_Encoder_CreateGroup(int encGroup)
 *
 * Create encode Group
 *
 * @param[in] encGroup Group number,range:[0, @ref NR_MAX_ENC_GROUPS - 1]
 *
 * @retval 0 success
 * @retval not 0 failure
 *
 * @remark one Group only support one resolution, and can allow 2 encode channel to be registered into.
 *
 * @attention return failure if group has been created.
 */
int IMP_Encoder_CreateGroup(int encGroup);

/**
 * @fn int IMP_Encoder_DestroyGroup(int encGroup)
 *
 * destroy the encoding Group
 *
 * @param[in] encGroup Group number,range:[0, @ref NR_MAX_ENC_GROUPS - 1]
 *
 * @retval 0 success
 * @retval not 0 failure
 *
 * @remark Destroy a Group, requires that the group must be empty, that is to say,no channel is registered into, otherwise it will return a failure value.
 *
 * @attention the group must have been created, otherwise it will return a failure value.
 */
int IMP_Encoder_DestroyGroup(int encGroup);

/**
 * @fn int IMP_Encoder_SetDefaultParam(IMPEncoderCHNAttr *chnAttr, IMPEncoderProfile profile, IMPEncoderRcMode rcMode, uint16_t uWidth, uint16_t uHeight, uint32_t frmRateNum, uint32_t frmRateDen, uint32_t uGopLength, uint32_t uBufSize, int iInitialQP, uint32_t uTargetBitRate);
 *
 * Set encoding default properties.
 *
 * @param[out] chnAttr struct for encoding.
 * @param[in]  profile encoding profile.
 * @param[in]  rcMode  rate control mode.
 * @param[in]  uWidth  encoding width.
 * @param[in]  uHeight encoding height.
 * @param[in]  frmRateNum encoding fps num.
 * @param[in]  frmRateDen encoding fps den.
 * @param[in]  uGopLength GOP length.
 * @param[in]  uBufSize stream buf size.
 * @param[in]  iInitialQP initialize QP, Default is -1.
 * @param[in]  uTargetBitRate target bitrate.
 *
 * @retval 0 success.
 * @retval not 0 failure.
 *
 * @remarks If you are not familiar with coding related parameters, please use the default values.
 *
 * @attention none
 */
int IMP_Encoder_SetDefaultParam(IMPEncoderCHNAttr *chnAttr, IMPEncoderProfile profile, IMPEncoderRcMode rcMode, uint16_t uWidth, uint16_t uHeight, uint32_t frmRateNum, uint32_t frmRateDen, uint32_t uGopLength, uint32_t uBufSize, int iInitialQP, uint32_t uTargetBitRate);

/**
 * @fn int IMP_Encoder_CreateChn(int encChn, const IMPEncoderCHNAttr *attr)
 *
 * create encoding channel
 *
 * @param[in] encChn encoder channel num,range:[0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] attr encode channel attribute pointer
 *
 * @retval 0 success
 * @retval not 0 failure
 *
 * @remark encoder channel contains encoder attribute and ratecontroller attribute
 * @remark encoder should choose encoder protocol, and then set the attribute to the encoder
 */
int IMP_Encoder_CreateChn(int encChn, const IMPEncoderCHNAttr *attr);

/**
 * @fn int IMP_Encoder_DestroyChn(int encChn)
 *
 * destroy encode Channel
 *
 * @param[in] encChn encoder channel num,range:[0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0 success
 * @retval not 0 failure
 *
 * @attention destroy uncreated channel will cause failure
 * @attention Before destroying a channel, make sure that it is not registered, otherwise it will return a failure value.
 */
int IMP_Encoder_DestroyChn(int encChn);

/**
 * @fn int IMP_Encoder_GetChnAttr(int encChn, IMPEncoderCHNAttr *const attr)
 *
 * get encode channel attribute
 *
 * @param[in] encChn encode channel num,range:[0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] attr encode channel attribute
 *
 * @retval 0 success
 * @retval not 0 failure
 */
int IMP_Encoder_GetChnAttr(int encChn, IMPEncoderCHNAttr *const attr);

/**
 * @fn int IMP_Encoder_RegisterChn(int encGroup, int encChn)
 *
 * register encode channel to Group
 *
 * @param[in] encGroup encode group num, range:[0, @ref NR_MAX_ENC_GROUPS - 1]
 * @param[in] encChn encode channel num,range:[0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0 success
 * @retval not 0 failure
 *
 * @attention registration of a channel to an uncreated Group will cause failure
 * @attention One channel can be registed to only one group, if it has already been registered to another Group, it will return failure;
 * @attention If one Group is already used by a Channel, so it can not be used again by another one unless this Group's Channel is first destroyed, otherwise it wil return failure.
 */

int IMP_Encoder_RegisterChn(int encGroup, int encChn);
/**
 * @fn int IMP_Encoder_UnRegisterChn(int encChn)
 *
 * unregister encode channel from group
 *
 * @param[in] encGroup encode group num, range:[0, @ref NR_MAX_ENC_GROUPS - 1]
 * @param[in] encChn encode channel num,range:[0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0 success
 * @retval not 0 failure
 *
 * @remark After unregistering a Channel, the channel bitstream buffer will be flushed.
 * if the bitstream hasn't been released, the data in bitstream buffer might be invalid.
 * so, users can use the IMP_Encoder_Query interface to check the status of the buffer's Channel code in order to confirm Confirm code stream buffer in the code stream to take over and then we can make new registration.
 *
 * @attention To unregister uncreated channel will return failure.
 * @attention To unregister unregistered channel will return failure
 * @attention if the channel is running, then it will return failure
 */
int IMP_Encoder_UnRegisterChn(int encChn);

/**
 * @fn int IMP_Encoder_StartRecvPic(int encChn)
 *
 * start encode channel to receive frames
 *
 * @param[in] encChn encode channel num,range:[0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0 success
 * @retval not 0 failure
 *
 * @remark First open the encoded Channel (receive the image) then this function can be used.
 *
 * @attention uncreated channel will cause failure
 * @attention unregistered channel whill cause failure
 */
int IMP_Encoder_StartRecvPic(int encChn);

/**
 * @fn int IMP_Encoder_StopRecvPic(int encChn)
 *
 * stop encode channel to receive frames
 *
 * @param[in] encChn encode channel num,range:[0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0 success
 * @retval not 0 failure
 *
 * @remark the function can be successly used repeatedly
 * @remark Call this interface only to stop receiving the original data encoding, code stream buffer and will not be eliminated.
 *
 * @attention stop uncreated channel will cause failure
 * @attention stop unregistered channel whill cause failure
 */
int IMP_Encoder_StopRecvPic(int encChn);

/**
 * @fn int IMP_Encoder_Query(int encChn, IMPEncoderCHNStat *stat)
 *
 * query encode channel state
 *
 * @param[in] encChn encode channel num,range:[0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] stat encode channel stat pointer
 *
 * @retval 0 success
 * @retval not 0 failure
 */
int IMP_Encoder_Query(int encChn, IMPEncoderCHNStat *stat);

/**
 * @fn int IMP_Encoder_GetStream(int encChn, IMPEncoderStream *stream, bool blockFlag)
 *
 * Get encode bitstream
 *
 * @param[in] encChn encode channel num,range:[0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] stream the bitstream pointer
 * @param[in] blockFlag use block mode variable，0：no，1：yes
 *
 * @retval 0 success
 * @retval not 0 failure
 *
 * @remark each time get one frame bitstream

 * @remark If the user does not get any stream for a long time, the stream buffer will be full. If a code Channel is full, The last received images will be lost until the user starts getting some streams, in order to have enough code stream buffer for encoding.
 *
 * It is suggested that the users access the code stream interface and the release of the code stream interface in pairs , and then release the stream as soon as possible, in order to prevent the user state to get the stream, when the release is not timely it might lead to the case where the stream
buffer is full, and then stop coding.

 * @remark For H264 and h265 type code stream, each time that it is called successfully, it is to get one frame stream, this frame stream may contain multiple packages.
 * @remark For JPEG type code stream,  each time that it is called successfully, it is to get one frame stream, this frame can contain only one package, this frame contains the complete information of the JPEG image file.
 *
 * examples：
 * @code
 * int ret;
 * ret = IMP_Encoder_PollingStream(ENC_H264_CHANNEL, 1000); //Polling the bitstream buffer
 * if (ret < 0) {
 *     printf("Polling stream timeout\n");
 *     return -1;
 * }
 *
 * IMPEncoderStream stream;
 * ret = IMP_Encoder_GetStream(ENC_H264_CHANNEL, &stream, 1); //get a frame stream; block mode
 * if (ret < 0) {
 *     printf("Get Stream failed\n");
 *     return -1;
 * }
 *
 * int i, nr_pack = stream.packCount;
 * for (i = 0; i < nr_pack; i++) {        //save each package of the frame stream
 *     ret = write(stream_fd, (void *)stream.pack[i].virAddr,
 *                stream.pack[i].length);
 *     if (ret != stream.pack[i].length) {
 *         printf("stream write error:%s\n", strerror(errno));
 *         return -1;
 *     }
 * }
 * @endcode
 *
 * @attention if pstStream is NULL,then return failure；
 * @attention if the channel uncreated，then return failure；
 */
int IMP_Encoder_GetStream(int encChn, IMPEncoderStream *stream, bool blockFlag);

/**
 * @fn int IMP_Encoder_ReleaseStream(int encChn, IMPEncoderStream *stream)
 *
 * release the bitstream buffer
 *
 * @param[in] encChn encode channel num,range:[0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] stream the bitstream pointer
 *
 * @retval 0 success
 * @retval not 0 failure
 *
 * @remark This interface should be paired up with IMP_Encoder_GetStream
 * users after getting the stream must release in time the obtained stream caches, otherwise it might cause the stream buffer to be full, this fact will have an impact the encoder. \n
* and the user must use FIFO process for the releasing.
 * @remark After cancelling the registration of the encoding Channel, all of the non-released stream packages are invalid, they can no longer be used or released. this current function is invalid when the channel is unregistered
 *
 * @attention if pstStream is NULL,then return failure；
 * @attention if the channel uncreated，then return failure；
 * @attention invalid release bitstream will cause failure
 */
int IMP_Encoder_ReleaseStream(int encChn, IMPEncoderStream *stream);

/**
 * @fn int IMP_Encoder_PollingStream(int encChn, uint32_t timeoutMsec)
 *
 * Polling bitstream buffer
 *
 * @param[in] encChn encode channel num,range:[0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] timeoutMsec polling timeout，unit:ms
 *
 * @retval 0 success
 * @retval not 0 failure
 *
 * @remark call this interface before calling IMP_Encoder_GetStream
 *
 */
int IMP_Encoder_PollingStream(int encChn, uint32_t timeoutMsec);

/**
 * @fn int IMP_Encoder_GetFd(int encChn)
 *
 * Get encode channel's device file descriptor handler
 *
 * @param[in] encChn encode channel num,range:[0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval >=0 success, return the file descriptor
 * @retval <0  failure
 *
 * @remark when getting mult channel's bitstream in one place, IMP_Encoder_PollingStream may be not suitable,
 * you can use the descriptor and select or poll and similar to poll the encode finish state.
 * @remark uncreated channel will cause failure
 */
int IMP_Encoder_GetFd(int encChn);

/**
 * @fn int IMP_Encoder_RequestIDR(int encChn)
 *
 * Requst IDR frame
 *
 * @param[in] encChn encode channel num,range:[0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0 success
 * @retval not 0 failure
 *
 * @remark  After calling this current function there will be an application for IDR frame coding.
 *
 * @attention this API only used to H264 and H265 channel
 */
int IMP_Encoder_RequestIDR(int encChn);

/**
 * @fn int IMP_Encoder_FlushStream(int encChn)
 *
 * flush old bitstream of encoder and start with idr frame to encode
 *
 * @param[in] encChn encode channel num,range:[0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0 success
 * @retval not 0 failure
 *
 * @remark  After calling this current function there will be an application for IDR frame coding.
 */
int IMP_Encoder_FlushStream(int encChn);

/**
 * @fn int IMP_Encoder_SetMaxStreamCnt(int encChn, int nrMaxStream)
 *
 * Set bitstream buffer number
 *
 * @param[in] encChn encode channel num,range:[0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] nrMaxStream bitstream buffer num,range:[1, @ref NR_MAX_ENC_CHN_STREAM]
 *
 * @retval 0 success
 * @retval not 0 failure
 *
 * @remark Since the stream cache Buffer number has been fixed during the channel creation, so the API needs to call this current before creating the Channel.
 * @remark If you do not call this API before the creation of the channel to set the number of stream cache Buffer, then the H264 channel default number is 5, JPEG channel default number is 1.
 */
int IMP_Encoder_SetMaxStreamCnt(int encChn, int nrMaxStream);

/**
 * @fn int IMP_Encoder_GetMaxStreamCnt(int encChn, int *nrMaxStream)
 *
 * Get bitstream buffer number
 *
 * @param[in] encChn encode channel num,range:[0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] nrMaxStream bitstream buffer num pointer
 *
 * @retval 0 success
 * @retval not 0 failure
 */
int IMP_Encoder_GetMaxStreamCnt(int encChn, int *nrMaxStream);

/**
 * @fn int IMP_Encoder_SetChnCrop(int encChn, const IMPEncoderCropCfg *pstCropCfg).
 *
 * Set encoding channel clipping properties
 *
 * @param[in] encChn encode channel num,range:[0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] pstCropCfg Crop Properties
 *
 * @retval 0 success
 * @retval not 0 failure
 *
 * @remark Calling this API will set the cropping function properties of the channel, which will take effect in the next IDR or P frame.
 *
 * @attention This API is only applicable to H264 and H265 encoded channels
 */
int IMP_Encoder_SetChnCrop(int encChn, const IMPEncoderCropCfg *pstCropCfg);

/**
 * @fn int IMP_Encoder_GetChnCrop(int encChn, IMPEncoderCropCfg *pstCropCfg).
 *
 * Get encoding channel clipping properties
 *
 * @param[in] encChn encode channel num,range:[0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstCropCfg Crop Properties
 *
 * @retval 0 success
 * @retval not 0 failure
 *
 * @remark Calling this API will obtain the cropping function properties of the channel, and calling this API requires that the channel already exists.
 *
 * @attention This API is only applicable to H264 and H265 encoded channels
 */
int IMP_Encoder_GetChnCrop(int encChn, IMPEncoderCropCfg *pstCropCfg);

/**
 * @fn int IMP_Encoder_SetChnAttrRcMode(int encChn, const IMPEncoderAttrRcMode *pstRcModeCfg).
 *
 * Set encoding channel rate controller mode attribute(s)
 *
 * @param[in] encChn encode channel num,range:[0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] pstRcCfg encode channel ratecontrol mode attribute
 *
 * @retval 0 success
 * @retval not 0 failure
 *
 * @remark This function configures the current Channel rate controller attribute(s) until it is deactivated,  \n
 * the channel should be created before calling this function.
 *
 * @attention this API only used to H264 and H265 channel
 * @attention this API can set all rc parameters dynamically
 */
int IMP_Encoder_SetChnAttrRcMode(int encChn, const IMPEncoderAttrRcMode *pstRcModeCfg);

/**
 * @fn int IMP_Encoder_GetChnAttrRcMode(int encChn, IMPEncoderAttrRcMode *pstRcModeCfg).
 *
 * Get encode channel rate controller mode attribute(s)
 *
 * @param[in] encChn encode channel num,range:[0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] pstRcCfg encode channel rate control mode attribute
 *
 * @retval 0 success
 * @retval not 0 failure
 *
 * @remark this function gets the mode attribute(s) of the current Channel rate controller. \n
 * The channel must have been created before calling this function.
 *
 * @attention this API only used to H264 and H265 channel
 */
int IMP_Encoder_GetChnAttrRcMode(int encChn, IMPEncoderAttrRcMode *pstRcModeCfg);

/**
 * @fn int IMP_Encoder_GetChnEncType(int encChn, IMPPayloadType *payLoadType)
 *
 * Get encode channel protocol type
 *
 * @param[in] encChn encode channel num, range:[0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] payLoadType return encode channel protocol type
 *
 * @retval 0 success
 * @retval not 0 failure
 *
 * @remark the channel must have been created before calling this function.
 */
int IMP_Encoder_GetChnEncType(int encChn, IMPPayloadType *payLoadType);

/**
 * @fn int IMP_Encoder_SetChnFrmRate(int encChn, const IMPEncoderFrmRate *pstFps)
 *
 * Set encode channel framerate controlled attribute
 *
 * @param[in] encChn encode channel num,range:[0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] pstFpsCfg framerate controlled attribute pointer
 *
 * @retval 0 success
 * @retval not 0 failure
 *
 * @remark this function can reset encode frame rate attribute(s), and it will take effect at the next GOP(delay to be effective:1s).
 * @remark if you want to use IMP_FrameSource_SetChnFPS() to set isp framerate, you need to first call this current function in order to set encoder framerate
 * @remark the channel must have been created before calling this function
 *
 * @attention this API only used to H264 and H265 channel
 * @attention this API can use dynamically
 */
int IMP_Encoder_SetChnFrmRate(int encChn, const IMPEncoderFrmRate *pstFps);

/**
 * @fn int IMP_Encoder_GetChnFrmRate(int encChn, IMPEncoderFrmRate *pstFps)
 *
 * Get encode channel framerate controlled attribute
 *
 * @param[in] encChn encode channel num,range:[0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstFpsCfg framerate controlled attribute pointer
 *
 * @retval 0 success
 * @retval not 0 failure
 *
 * @remark this function gets the Channel 's frame rate control attribute(s). The channel must have been created before calling this function
 *
 * @attention this API only used to H264 and H265 channel
 */
int IMP_Encoder_GetChnFrmRate(int encChn, IMPEncoderFrmRate *pstFps);

/**
 * @fn int IMP_Encoder_SetChnBitRate(int encChn, int iTargetBitRate, int iMaxBitRate)
 *
 * Dynamically set bit rate control properties
 *
 * @param[in] encChn encoding channel number, value range: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] iTargetBitRate target bitrate, iMaxBitRate maximum bitrate. Note that the bit rate unit is : "kbit/s".
 *
 * @retval 0 success
 * @retval Non-0 failure
 *
 * @remarks Calling this API will reset the encoder bitrate attribute, the bitrate attribute will take effect at the next GOP, with a maximum delay of 1 second to take effect, calling this API requires that the channel already exists.
 *
 * @attention This API can't set CVBR long term bitrate.Only iTargetBitRate is valid in CBR, and only iMaxBitRate is valid in the rest of RC modes.
 * @attention This API only applies to H264 and h265 encoding channels.
 * @attention This API can use dynamically
 */
int IMP_Encoder_SetChnBitRate(int encChn, int iTargetBitRate, int iMaxBitRate);

/**
 * @fn int IMP_Encoder_SetChnQpBounds(int encChn, int iMinQP, int iMaxQP);
 *
 * Dynamically sets the bitrate control attributes MaxQP and MinQP.
 *
 * @param[in] encChn encoding channel number, value range: [0, @ref NR_MAX_ENC_CHN - 1].
 * @param[in] iMinQP MinQP value, range: [1, 51].
 * @param[in] iMaxQP MaxQP value, range: [1, 51]
 *
 * @retval 0 success
 * @retval Non-0 failure
 *
 * @remarks Calling this API resets frame QP range.Calling this API requires that the channel already exists.
 *
 * @attention This API is only available for h264 and h265 encoding channels.
 * @attention This API can use dynamically
 */
int IMP_Encoder_SetChnQpBounds(int encChn, int iMinQP, int iMaxQP);

/**
 * @fn int IMP_Encoder_SetChnQpBoundsPerFrame(int encChn, int iMinQP_I, int iMaxQP_I, int iMinQP_P, int iMaxQP_P)
 *
 * Dynamically set the MaxQP and MinQP of the I and P frames.
 *
 * @param[in] encChn Encoding Channel number, range: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] iMinQP_I iMinQP_P MinQP value, range: [1, 51].
 * @param[in] iMaxQP_I iMaxQP_P MaxQP value, range: [1, 51].
 *
 * @retval 0 success
 * @retval Non-0 failure
 *
 * @remarks Calling this API resets frame QP range.Calling this API requires that the channel already exists.
 *
 * @attention This API is only available for h264 and h265 encoding channels.
 * @attention This API can use dynamically
 */
int IMP_Encoder_SetChnQpBoundsPerFrame(int encChn, int iMinQP_I, int iMaxQP_I, int iMinQP_P, int iMaxQP_P);

/**
 * @fn int IMP_Encoder_SetChnMaxPictureSize(int encChn, uint32_t MaxPictureSize_I, uint32_t MaxPictureSize_P)
 *
 * Dynamically configure MaxPictureSize for I and P frames.
 *
 * @param[in] encChn Encoded Channel number, value range: [0, @ref NR_MAX_ENC_CHN - 1].
 * @param[in] MaxPictureSize_I Maximum I-frame Size in "Kbits".
 * @param[in] MaxPictureSize_P Maximum P-frame size in "Kbits".
 *
 * @retval 0 success
 * @retval Non-0 failure
 *
 * @remarks This API needs to be called after the channel is created.
 *
 * @attention This API is only available for H264 and h265 encoding channels.
 * @attention This API can use dynamically
 */
int IMP_Encoder_SetChnMaxPictureSize(int encChn, uint32_t MaxPictureSize_I, uint32_t MaxPictureSize_P);

/**
 * @fn int IMP_Encoder_SetChnROI(int encChn, const IMPEncoderROIAttr *pstVencRoiAttr)
 *
 * Set encoder channel ROI attribute
 *
 * @param[in] encChn encode channel number, range: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstVencRoiAttr ROI attribute parameter.
 *
 * @retval 0 success
 * @retval Non-0 failure
 *
 * @remark Calling this API sets the ROI attribute of the channel, calling this API requires that the channel already exists.
 *
 * @attention This API only applies to h264 and h265 encoding channels.
 */
int IMP_Encoder_SetChnROI(int encChn, const IMPEncoderROIAttr *pstVencRoiAttr);

/**
 * @fn int IMP_Encoder_GetChnROI(int encChn, IMPEncoderROIAttr *pstVencRoiAttr)
 *
 * Get channel ROI attribute
 *
 * @param[in] encChn Encoded Channel number, value range: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstVencRoiAttr ROI attribute parameter.
 *
 * @retval 0 success
 * @retval Non-0 failure
 *
 * @remark Calling this API will get the ROI attribute of the channel, calling this API requires that the channel already exists.
 *
 * @attention This API is only available for h264 and h265 encoding channels.
 */
int IMP_Encoder_GetChnROI(int encChn, IMPEncoderROIAttr *pstVencRoiAttr);

/**
 * @fn int IMP_Encoder_SetChnMapRoi(int encChn, IMPEncoderMapRoiCfg *pstVencMapRoiCfg, IMPEncoderMappingList *list)
 *
 * Set the channel Map ROI attribute
 *
 * @param[in] encChn encode channel number, range: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstVencMapRoiCfg Map ROI attribute parameter.
 *
 * @retval 0 success
 * @retval Non-0 failure
 *
 * @remark Calling this API sets the Map ROI attribute of the channel, calling this API requires that the channel already exists.
 *
 * @attention This API is only available for H264 and h265 encoding channels.
 */
int IMP_Encoder_SetChnMapRoi(int encChn, IMPEncoderMapRoiCfg *pstVencMapRoiCfg, IMPEncoderMappingList *list);

/**
 * @fn int IMP_Encoder_SetChnQpgAI(int encChn, IMPEncoderQpgAICfg *pstVencQpgAICfg)
 *
 * Set the channel Qpg AI attribute
 *
 * @param[in] encChn encoding Channel number, range: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstVencQpgAICfg QpgAI attribute parameter.
 *
 * @retval 0 success
 * @retval Non-0 failure
 *
 * @remark Calling this API sets the Qpg AI attribute of the channel, calling this API requires that the channel already exists.
 *
 * @attention This API is only available for H264 and h265 encoding channels.
 */
int IMP_Encoder_SetChnQpgAI(int encChn, IMPEncoderQpgAICfg *pstVencQpgAICfg);

/**
 * @fn int IMP_Encoder_SetGOPSize(int encChn, const IMPEncoderGOPSizeCfg *pstGOPSizeCfg)
 *
 * Set encoder channel gop attribute
 *
 * @param[in] encChn encode channel num,range:[0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] pstGOPSizeCfg GOPSize attribute pointer
 *
 * @retval 0 success
 * @retval not 0 failure
 *
 * @remark It sets the Channel's GOPSize attribute(s), and the channel must have been created before calling this function
 *
 * @attention this API only used to H264 and H265 channel
 */
int IMP_Encoder_SetGOPSize(int encChn, const IMPEncoderGOPSizeCfg *pstGOPSizeCfg);

/**
 * @fn int IMP_Encoder_GetGOPSize(int encChn, IMPEncoderGOPSizeCfg *pstGOPSizeCfg)
 *
 * Get encoder channel GOP attribute
 *
 * @param[in] encChn encode channel num,range:[0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstGOPSizeCfg GOPSize attribute pointer
 *
 * @retval 0 success
 * @retval not 0 failure
 *
 * @remark It gets the Channel's GOPSize attribute(s), and the channel must have been created before calling this function
 *
 * @attention this API only used to H264 and H265 channel
 */
int IMP_Encoder_GetGOPSize(int encChn, IMPEncoderGOPSizeCfg *pstGOPSizeCfg);

/**
 * @fn int IMP_Encoder_SetChnFrmUsedMode(int encChn, const IMPEncoderAttrFrmUsed *pfrmUsedAttr)
 *
 * Set encoder channel input frame usage mode attribute
 *
 * @param[in] encChn encode channel num,range:[0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pfrmUsedAttr input frame usage mode attribute pointer
 *
 * @retval 0 success
 * @retval not 0 failure
 *
 * @remark It sets the Channel's input frame usage mode attribute(s), and the channel must have been created before calling this function.
 *
 * @attention this API only used to H264 and H265 channel
 */
int IMP_Encoder_SetChnFrmUsedMode(int encChn, const IMPEncoderAttrFrmUsed *pfrmUsedAttr);

/**
 * @fn int IMP_Encoder_GetChnFrmUsedMode(int encChn, IMPEncoderAttrFrmUsed *pfrmUsedAttr)
 *
 * Get encoder channel input frame usage mode attribute
 *
 * @param[in] encChn encode channel num,range:[0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pfrmUsedAttr input frame usage mode attribute pointer
 *
 * @retval 0 success
 * @retval not 0 failure
 *
 * @remark It gets the Channel's input frame usage mode attribute(s), and the channel must have been created before calling this function.
 *
 * @attention this API only used to H264 and H265 channel
 */
int IMP_Encoder_GetChnFrmUsedMode(int encChn, IMPEncoderAttrFrmUsed *pfrmUsedAttr);

/**
 * @fn int IMP_Encoder_SetChnHSkip(int encChn, const IMPEncoderAttrHSkip *phSkipAttr)
 *
 * Set encode channel high skip reference attribute
 *
 * @param[in] encChn encode channel num,range:[0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] phSkipAttr high skip reference attribute pointer
 *
 * @retval 0 success
 * @retval not 0 failure
 *
 * @remark It sets the Channel's high skip reference attribute(s), and the channel must have been created before calling this function.
 * @remark If the Channel's created high skip reference type is one of IMP_Encoder_STYPE_N1X or IMP_Encoder_STYPE_N2X,
 * this function only be permited to set to be IMP_Encoder_STYPE_N1X or IMP_Encoder_STYPE_N2X;
 * @remark If the Channel's created high skip reference type is one of the type from IMP_Encoder_STYPE_N4X to
 * IMP_Encoder_STYPE_H1M_TRUE, then this function can set any one enum skip type of IMPSkipType;
 *
 * @attention this API only used to H264 and H265 channel
 */
int IMP_Encoder_SetChnHSkip(int encChn, const IMPEncoderAttrHSkip *phSkipAttr);

/**
 * @fn int IMP_Encoder_GetChnHSkip(int encChn, IMPEncoderAttrHSkip *phSkipAttr)
 *
 * Get encode channel high skip reference attribute
 *
 * @param[in] encChn encode channel num,range:[0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] phSkipAttr high skip reference attribute pointer
 *
 * @retval 0 success
 * @retval not 0 failure
 *
 * @remark It gets the Channel's high skip reference attribute(s), and the channel must have been created
 *
 * @attention this API only used to H264 and H265 channel
 */
int IMP_Encoder_GetChnHSkip(int encChn, IMPEncoderAttrHSkip *phSkipAttr);

/**
 * @fn int IMP_Encoder_SetChnHSkipBlackEnhance(int encChn, const int bBlackEnhance)
 *
 * Set encode channel'bBlackEnhance in high skip reference attribute
 *
 * @param[in] encChn encode channel num,range:[0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] bBlackEnhance bool value, mean to bBlackEnhance in IMPEncoderAttrHSkip attribute
 *
 * @retval 0 success
 * @retval not 0 failure
 *
 * @remark It sets the Channel' bBlackEnhance in high skip reference attribute(s), and the channel must have been created
 * before calling this function.
 *
 * @attention this API only used to H264 and H265 channel
 */
int IMP_Encoder_SetChnHSkipBlackEnhance(int encChn, const int bBlackEnhance);

/**
 * @fn int IMP_Encoder_InsertUserData(int encChn, void *userData, uint32_t userDataLen)
 *
 * insert userdata
 *
 * @param[in] encChn encode channel num,range:[0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] userData userdata virtual address pointer
 * @param[in] userDataLen user data length, range:(0, 1024], unit:byte
 *
 * @retval 0 success
 * @retval not 0 failure
 *
 * @remark the channel must have been created before call this function, otherwise it will return a failure value.
 * @remark if userData is null or userDataLen is 0, then return a failure value
 * @remark this function only supports h264 and H265 protocol
 * @remark H.264 and H.265 protocol channel allocation is up to 2 blocks of memory space for caching user data, and each user data size does not exceed 1K byte.
 * This interface will return an error if the data inserted by the user is more than 2 blocks, or if the user data is more than byte 1K.
 * @remark Each user data in SEI package is inserted into the previous new image codestream package.  After a user data package is encoded and transmitted, the H.264 and H.265 channel customer data in the cache memory space is cleared for new user data storage.
 * @remark each userdata is encapsulated to sei nal and placed at the front of the latest frame nal.
 * @remark when the userdata is encapsulated, the userdata buffer will be set to zero
 * @remark the channel must have been created before call this function
 *
 * @attention this API only used to H264 and H265 channel
 */
int IMP_Encoder_InsertUserData(int encChn, void *userData, uint32_t userDataLen);

/**
 * @fn int IMP_Encoder_SetIvpuBsSize(uint32_t ivpuBsSize)
 *
 * Set the size of the ivpu encoding stream buffer.
 *
 * @param[in] ivpuBsSize ivpu encoding stream buffer size
 *
 * @retval 0 success
 * @retval non-zero failure
 *
 * @remarks this interface can set the bitstream buffer size for H264 and H265.
 *
 * @attention Calls to this function must be made before IMP_System_Init.
 * @attention After enabling multi-section encoding, memory allocation is determined by the multi-section encoding attribute, and this interface setting is invalid.
 */
int IMP_Encoder_SetIvpuBsSize(uint32_t ivpuBsSize);

/**
 * @fn int IMP_Encoder_SetJpegBsSize(uint32_t jpegBsSize)
 *
 * Set the size of the jpeg encoding stream buffer.
 *
 * @param[in] jpegBsSize jpeg encoding stream buffer size
 *
 * @retval 0 success
 * @retval non-zero failure
 *
 * @remarks this interface can set the bitstream buffer size for jpeg.
 *
 * @attention Calls to this function must be made before IMP_System_Init.
 */
int IMP_Encoder_SetJpegBsSize(uint32_t JpegBsSize);

/**
 * @fn int IMP_Encoder_SetSuperFrameCfg(int encChn, const IMPEncoderSuperFrmCfg *pstSuperFrmParam)
 *
 * Set video coded supper frame configuration
 *
 * @param[in] encChn encode channel num, range:[0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] pstSuperFrmParam video coded supper frame configuration
 *
 * @retval 0 success
 * @retval not 0 failure
 *
 * @remark the channel must have been created before calling this function.
 * @attention this API only used to H264 and H265 channel
 */
int IMP_Encoder_SetSuperFrameCfg(int encChn, const IMPEncoderSuperFrmCfg *pstSuperFrmParam);

/**
 * @fn int IMP_Encoder_GetSuperFrameCfg(int encChn, IMPEncoderSuperFrmCfg *pstSuperFrmParam)
 *
 * Get video coded supper frame configuration
 *
 * @param[in] encChn encode channel num, range:[0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstSuperFrmParam return video coded supper frame configuration
 *
 * @retval 0 success
 * @retval not 0 failure
 *
 * @remark the channel must have been created before calling this function.
 * @attention this API only used to H264 and H265 channel
 */
int IMP_Encoder_GetSuperFrameCfg(int encChn, IMPEncoderSuperFrmCfg *pstSuperFrmParam);

/**
 * @fn int IMP_Encoder_SetH264TransCfg(int encChn, const IMPEncoderH264TransCfg *pstH264TransCfg)
 *
 * Set H.264 encode channel chroma quantization attribute
 *
 * @param[in] encChn encode channel num, range:[0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] pstH264TransCfg H.264 encode channel chroma quantization attribute
 *
 * @retval 0 success
 * @retval not 0 failure
 *
 * @remark the channel must have been created before calling this function.
 * @remark this api only used by h264;
 * @remark advice used after IMP_Encoder_CreateChn and before IMP_Encoder_StartRecvPic function, should GetH264TransCfg first, \n
 * and then use this API to set h264 transform configuration
 */
int IMP_Encoder_SetH264TransCfg(int encChn, const IMPEncoderH264TransCfg *pstH264TransCfg);

/**
 * @fn int IMP_Encoder_GetH264TransCfg(int encChn, IMPEncoderH264TransCfg *pstH264TransCfg)
 *
 * Get H.264 encode channel chroma quantization attribute
 *
 * @param[in] encChn encode channel num, range:[0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstH264TransCfg returned H.264 encode channel chroma quantization attribute
 *
 * @retval 0 success
 * @retval not 0 failure
 *
 * @remark the channel must have been created before calling this function.
 * @remark this api only used by h264;
 */
int IMP_Encoder_GetH264TransCfg(int encChn, IMPEncoderH264TransCfg *pstH264TransCfg);

/**
 * @fn int IMP_Encoder_SetH265TransCfg(int encChn, const IMPEncoderH265TransCfg *pstH265TransCfg)
 *
 * Set H.265 encode channel chroma quantization attribute
 *
 * @param[in] encChn encode channel num, range:[0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] pstH265TransCfg H.265 encode channel chroma quantization attribute
 *
 * @retval 0 success
 * @retval not 0 failure
 *
 * @remark the channel must have been created before calling this function.
 * @remark this api only used by h265;
 * @remark advice used after IMP_Encoder_CreateChn and before IMP_Encoder_StartRecvPic function, should GetH265TransCfg first,
 * and then use this API to set h265 transform configuration
 */
int IMP_Encoder_SetH265TransCfg(int encChn, const IMPEncoderH265TransCfg *pstH265TransCfg);

/**
 * @fn int IMP_Encoder_GetH265TransCfg(int encChn, IMPEncoderH265TransCfg *pstH265TransCfg)
 *
 * Get H.265 encode channel chroma quantization attribute
 *
 * @param[in] encChn encode channel num, range:[0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstH265TransCfg returned H.265 encode channel chroma quantization attribute
 *
 * @retval 0 success
 * @retval not 0 failure
 *
 * @remark the channel must have been created before calling this function.
 * @remark this api only used by h265;
 */
int IMP_Encoder_GetH265TransCfg(int encChn, IMPEncoderH265TransCfg *pstH265TransCfg);

/**
 * @fn int IMP_Encoder_SetQpgMode(int encChn, const IMPEncoderQpgMode *pstQpgMode)
 *
 * Set macroblock encode mode
 *
 * @param[in] encChn encode channel num,range: [0, @ref NR_MAX_ENC_CHN - 1]
 * @param[in] pstQpgMode macroblock encode mode
 *
 * @retval 0 success
 * @retval not 0 failure
 *
 * @remark the channel must have been created before calling this function.
 * @remark this api only used by T30
 *
 */
int IMP_Encoder_SetQpgMode(int encChn, const IMPEncoderQpgMode *pstQpgMode);

/**
 * @fn int IMP_Encoder_GetQpgMode(int encChn, IMPEncoderQpgMode *pstQpgMode)
 *
 * Get macroblock encode mode
 *
 * @param[in] encChn encode channel num, range:[0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] pstQpgMode returned macroblock encode mode
 *
 * @retval 0 success
 * @retval not 0 failure
 *
 * @remark the channel must have been created before calling this function.
 * @remark this api only used by T30;
 */
int IMP_Encoder_GetQpgMode(int encChn, IMPEncoderQpgMode *pstQpgMode);

/**
 * @fn int IMP_Encoder_SetSrdCfg(int encChn, const IMPEncoderSrdCfg *pstSrdCfg)
 *
 * Set SRD function configuration
 *
 * @param[in] encChn encoder channel number, range: [0, @ref NR_MAX_ENC_CHN - 1].
 * @param[in] pstSrdCfg SRD configuration.
 *
 * @retval 0 success
 * @retval Non-0 failure
 *
 * @remark Returns failure if channel not created.
 * @remark Only H265 support this function.
 *
 * @attention None
 */
int IMP_Encoder_SetSrdCfg(int encChn, const IMPEncoderSrdCfg *pstSrdCfg);

/**
 * @fn int IMP_Encoder_GetSrdCfg(int encChn, IMPEncoderSrdCfg *pstSrdCfg)
 *
 * Get SRD function configuration
 *
 * @param[in] encChn encoder channel number, range: [0, @ref NR_MAX_ENC_CHN - 1].
 * @param[out] pstSrdCfg return SRD configuration.
 *
 * @retval 0 success.
 * @retval Non-0 failure
 *
 * @remark Returns failure if channel is not created.
 * @remark Only H265 support this function.
 *
 * @attention None
 */
int IMP_Encoder_GetSrdCfg(int encChn, IMPEncoderSrdCfg *pstSrdCfg);

/**
 * @fn int IMP_Encoder_SetJpegQp(int encChn, int jpegQp)
 *
 * Dynamically set JpegQp
 *
 * @param[in] encChn encoder channel number, range: [0, @ref NR_MAX_ENC_CHN - 1].
 * @param[in] jpegQp jpeg quantizedQp value
 *
 * @retval 0 success
 * @retval Non-0 failure
 *
 * @remarks This API must be called after the channel has been created.
 */
int IMP_Encoder_SetJpegQp(int encChn, int jpegQp);

/**
 * @fn int IMP_Encoder_GetJpegQp(int encChn, int *jpegQp)
 *
 * GetJpegQp
 *
 * @param[in] encChn encoder channel number, range: [0, @ref NR_MAX_ENC_CHN - 1].
 * @param[out] jpegQp Returns the jpeg quantized Qp value.
 *
 * @retval 0 success
 * @retval Non-0 failure
 *
 * @remarks This API must be called after the channel has been created.
 */
int IMP_Encoder_GetJpegQp(int encChn, int *jpegQp);

/**
 * @fn int IMP_Encoder_SetPool(int chnNum, int poolID);
 *
 * bind channel to mempool, let chnNum malloc from pool
 *
 * @param[in] chnNum		Channnel ID
 * @param[in] poolID		Pool ID
 *
 * @retval 0				success
 * @retval other values		failed
 *
 * @remarks In order to solve the fragmentation of rmem, the channel encoder is bound to
 * the corresponding MemPool. The encoder applies for MEM in the MemPool. If it is not
 * called, the encoder will apply in rmem. At this time, there is the possibility of
 * fragmentation for rmem
 *
 * @attention: chnNum is greater than or equal to 0 and less than 32
 */
int IMP_Encoder_SetPool(int chnNum, int poolID);

/**
 * @fn int IMP_Encoder_GetPool(int chnNum);
 *
 * Get Pool ID by chnannel ID
 *
 * @param[in] chnNum		Channel ID
 *
 * @retval  >=0 && < 32     success
 * @retval other values		failed
 *
 * @remarks obtains poolid through channelid
 *
 * @attention	none
 */
int IMP_Encoder_GetPool(int chnNum);

/**
 * @fn int IMP_Encoder_SetRdBufShare(int encChn, int bEnable)
 *
 * Set the encoding channel reference and reconstruction buf share
 *
 * @param[in] chnNum Channel number
 * @param[in] bEnable Whether to enable
 *
 * @retval 0 success
 * @retval Non-zero failure
 *
 * @remarks Calls to this API set the encoding channel reference and rebuild the share of the buf, calls to the API must be made before the channel is created.
 * Calls to this API must be made before the channel is created
 * @attention By default, the bufshare function is enabled, and this interface can be called to disable it.
 */
int IMP_Encoder_SetRdBufShare(int encChn, int bEnable);

/**
 * @fn int IMP_Encoder_SetMultiSectionMode(int mode, int size, int cnt)
 *
 * Set multi section encoding function
 *
 * @param[in] mode       multi section encoding mode
 * @param[in] size       multi section encoding buffer size, unit:KByte
 * @param[in] cnt        multi section encoding buffer cnt
 *
 * @retval 0 success
 * @retval Non-zero failure
 *
 * @remarks mode range[0,2]
 * @remarks 0:disable multi section encoding
 * @remarks 1:enable multi section encoding, and output an integrated frame each time
 * @remarks 2:enable multi section encoding, and output a section of a frame, it may not be an integrated frame. In mode2, it can be determined whether it is the last block through "stream->pack[0].frameEnd == 1"
 * @remarks the minimum value of cnt is 2
 *
 * @attention Calls to this function must be made before IMP_System_Init
 * @attention By default, multi section encoding is turned on
 * @attention This function is only applicable to H264/H265
 */
int IMP_Encoder_SetMultiSectionMode(int mode, int size, int cnt);

/**
 * @fn void *IMP_Encoder_VbmAlloc(uint32_t size, uint32_t align);
 *
 * Alloc a contiguous memory and it's size alignment with align
 *
 * @param[in] size       Memory size
 * @param[in] align      Memory align
 *
 * @retval  0 success
 * @retval  not 0 failure
 *
 * @remarks none
 *
 * @attention none
 */
void *IMP_Encoder_VbmAlloc(uint32_t size, uint32_t align);

/**
 * @fn void IMP_Encoder_VbmFree(void *vaddr);
 *
 * Free a physical addr continuous memory and it's addr is vaddr
 *
 * @param[in] vaddr        virtual addr of continuous memory
 *
 * @retval  0 success
 * @retval  not 0 failure
 *
 * @remarks none
 *
 * @attention none
 */
void IMP_Encoder_VbmFree(void *vaddr);

/**
 * @fn intptr_t IMP_Encoder_VbmV2P(intptr_t vaddr);
 *
 * Convert a virtual addr to a physical addr
 *
 * @param[in] vaddr        virtual addr of continuous memory
 *
 * @retval  0 success
 * @retval  not 0 failure
 *
 * @remarks none
 *
 * @attention none
 */
intptr_t IMP_Encoder_VbmV2P(intptr_t vaddr);

/**
 * @fn intptr_t IMP_Encoder_VbmP2V(intptr_t paddr);
 *
 * Convert a physical addr to a virtual addr
 *
 * @param[in] paddr        physical addr of continuous memory
 *
 * @retval  0 success
 * @retval  not 0 failure
 *
 * @remarks none
 *
 * @attention none
 */
intptr_t IMP_Encoder_VbmP2V(intptr_t paddr);

/**
 * @fn int IMP_Encoder_YuvInit(void **h, int inWidth, int inHeight, IMPEncoderYuvIn *encIn);
 *
 * Encode init
 *
 * @param[in] h        Encode interface
 * @param[in] inWidth  Width
 * @param[in] inHeight Height
 * @param[in] encIn    Encode attr
 *
 * @retval  0 success
 * @retval  not 0 failure
 *
 * @remarks none
 *
 * @attention none
 */
int IMP_Encoder_YuvInit(void **h, int inWidth, int inHeight, IMPEncoderYuvIn *encIn);

/**
 * @fn int IMP_Encoder_YuvEncode(void *h, IMPFrameInfo frame, IMPEncoderYuvOut *encOut);
 *
 * Encode process
 *
 * @param[in] h			Encode interface
 * @param[in] frame		frame
 * @param[in] encOut	stream
 *
 * @retval  0 success
 * @retval  not 0 failure
 *
 * @remarks none
 *
 * @attention none
 */
int IMP_Encoder_YuvEncode(void *h, IMPFrameInfo frame, IMPEncoderYuvOut *encOut);

/**
 * @fn int IMP_Encoder_YuvExit(void *h);
 *
 * Encode exit
 *
 * @param[in] h			Encode interface
 *
 * @retval  0 success
 * @retval  not 0 failure
 *
 * @remarks none
 *
 * @attention none
 */
int IMP_Encoder_YuvExit(void *h);

/**
 * @fn int IMP_Encoder_InputJpege(uint8_t *src, uint8_t *dst, int src_w, int src_h, int q, int *stream_length);
 *
 * External input NV12 for encoding JPEG
 *
 * @param[in] *src pointer to source data address
 * @param[in] *dst stream data address pointer
 * @param[in] src_w image height
 * @param[in] src_h image height
 * @param[in] q image quality control
 * @param[out] stream_length stream data length
 *
 * @retval 0 success
 * @retval non-0 failure
 *
 * @remarks JPEG width and height must be aligned to 2, stride must be aligned to 16.
 *
 * @attention None
 */
int IMP_Encoder_InputJpege(uint8_t *src, uint8_t *dst, int src_w, int src_h, int q, int *stream_length);

/**
 * @fn void *IMP_Encoder_VbmAlloc_Ex(uint32_t size, uint32_t align);
 *
 * Secondary process Alloc a contiguous memory and it's size alignment with align.
 *
 * @param[in] size       Memory size
 * @param[in] align      Memory align
 *
 * @retval  0 success
 * @retval  not 0 failure
 *
 * @remarks none
 *
 * @attention none
 */
void *IMP_Encoder_VbmAlloc_Ex(uint32_t size, uint32_t align);

/**
 * @fn void IMP_Encoder_VbmFree_Ex(void *vaddr);
 *
 * Secondary process Free a physical addr continuous memory and it's addr is vaddr
 *
 * @param[in] vaddr        virtual addr of continuous memory
 *
 * @retval  0 success
 * @retval  not 0 failure
 *
 * @remarks none
 *
 * @attention none
 */
void IMP_Encoder_VbmFree_Ex(void *vaddr);

/**
 * @fn int IMP_Encoder_YuvInit_Ex(int *h, int inWidth, int inHeight, IMPEncoderYuvIn *encIn);
 *
 * Secondary process Encode init
 *
 * @param[in] h        Encode interface
 * @param[in] inWidth  Width
 * @param[in] inHeight Height
 * @param[in] encIn    Encode attr
 *
 * @retval  0 success
 * @retval  not 0 failure
 *
 * @remarks none
 *
 * @attention none
 */
int IMP_Encoder_YuvInit_Ex(int *h, int inWidth, int inHeight, IMPEncoderYuvIn *encIn);

/**
 * @fn int IMP_Encoder_YuvEncode_Ex(int h, IMPFrameInfo frame, IMPEncoderYuvOut *encOut);
 *
 * Secondary process Encode process
 *
 * @param[in] h			Encode interface
 * @param[in] frame		frame
 * @param[in] encOut	stream
 *
 * @retval  0 success
 * @retval  not 0 failure
 *
 * @remarks none
 *
 * @attention none
 */
int IMP_Encoder_YuvEncode_Ex(int h, IMPFrameInfo frame, IMPEncoderYuvOut *encOut);

/**
 * @fn int IMP_Encoder_YuvExit_Ex(int h);
 *
 * Secondary process Encode exit
 *
 * @param[in] h			Encode interface
 *
 * @retval  0 success
 * @retval  not 0 failure
 *
 * @remarks none
 *
 * @attention none
 */
int IMP_Encoder_YuvExit_Ex(int h);

/**
 * @fn int IMP_Encoder_InputJpege_Ex(uint8_t *src, uint8_t *dst, int src_w, int src_h, int q,int *stream_length);.
 *
 * Sub-process external input NV12 for encoding JPEG
 *
 * @param[in] *src pointer to source data address
 * @param[in] *dst stream data address pointer
 * @param[in] src_w image height
 * @param[in] src_h image width
 * @param[in] q image quality control
 * @param[out] stream_length stream data length
 *
 * @retval 0 success
 * @retval non-0 failure
 *
 * @remarks JPEG width and height must be aligned to 2, stride must be aligned to 16
 *
 * @attention None
 */
int IMP_Encoder_InputJpege_Ex(uint8_t *src, uint8_t *dst, int src_w, int src_h, int q, int *stream_length);

/**
 * @fn int IMP_Encoder_KernEnc_Stop()
 *
 * Stop all kernel encoding channels
 *
 * @retval 0 success
 * @retval non-0 failure
 *
 * @remark None
 *
 * @attention This interface is currently only used for low-power products.
 */
int IMP_Encoder_KernEnc_Stop();

/**
 * @fn int IMP_Encoder_KernEnc_GetStream(int encChn, IMPEncoderKernEncOut *encOut)
 *
 * Get kernal encoding stream
 *
 * @param[in] encChn encoder channel num,range:[0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] encOut struct of output stream
 *
 * @retval 0 success
 * @retval non-0 failure
 *
 * @remark None
 *
 * @attention This interface is currently only used for low-power products.
 */
int IMP_Encoder_KernEnc_GetStream(int encChn, IMPEncoderKernEncOut *encOut);

/**
 * @fn int IMP_Encoder_KernEnc_Release(int encChn)
 *
 * Release kernal encoding channel
 *
 * @param[in] encChn encoder channel num,range:[0, @ref NR_MAX_ENC_CHN - 1]
 *
 * @retval 0 success
 * @retval non-0 failure
 *
 * @remark None
 *
 * @attention This interface is currently only used for low-power products.
 */
int IMP_Encoder_KernEnc_Release(int encChn);

/**
 * @fn int IMP_Encoder_KernEnc_GetStatus(int encChn, int *enable)
 *
 * Get kernel encoding channel status
 *
 * @param[in] encChn encoder channel num,range:[0, @ref NR_MAX_ENC_CHN - 1]
 * @param[out] enable kernel encoding channel status, 0:disabled, 1:enabled
 *
 * @retval 0 success
 * @retval non-0 failure
 *
 * @remark None
 *
 * @attention This interface is currently only used for low-power products.
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
