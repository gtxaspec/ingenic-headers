/*
 * IMP HDMI header file.
 *
 * Copyright (C) 2021 Ingenic Semiconductor Co.,Ltd
 */
#ifndef __IMP_HDMI_H__
#define __IMP_HDMI_H__

#include <imp/imp_common.h>

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

/**the max audio smprate count*/
#define IMP_HDMI_MAX_SAMPE_RATE_NUM		8

/**the max audio bit depth count*/
#define IMP_HDMI_MAX_BIT_DEPTH_NUM		6
/**
 *Define HDMI interface number
 */
typedef enum{
	IMP_HDMI_ID_0 = 0,		/**< HDMI ID 0 */
	IMP_HDMI_ID_BUTT
}IMP_HDMI_ID_E;

/**
 *Define HDMI Video Format,refer to《CEA-861-D》&《CEA-861-F》
 */
typedef enum{
	IMP_HDMI_VIDEO_FMT_1080P_60 = 0,
	IMP_HDMI_VIDEO_FMT_1080P_100,
	IMP_HDMI_VIDEO_FMT_1080P_120,
	IMP_HDMI_VIDEO_FMT_1080P_50,
	IMP_HDMI_VIDEO_FMT_1080P_30,
	IMP_HDMI_VIDEO_FMT_1080P_25,
	IMP_HDMI_VIDEO_FMT_1080P_24,
	IMP_HDMI_VIDEO_FMT_1080i_60,
	IMP_HDMI_VIDEO_FMT_1080i_50,
	IMP_HDMI_VIDEO_FMT_720P_60,
	IMP_HDMI_VIDEO_FMT_720P_50,
	IMP_HDMI_VIDEO_FMT_576P_50,
	IMP_HDMI_VIDEO_FMT_480P_60,
	IMP_HDMI_VIDEO_FMT_PAL,						/**< B D G H I PAL */
	IMP_HDMI_VIDEO_FMT_PAL_N,					/**< (N)PAL */
	IMP_HDMI_VIDEO_FMT_PAL_Nc,					/**< (Nc)PAL */
	IMP_HDMI_VIDEO_FMT_NTSC,					/**< (M)NTSC */
	IMP_HDMI_VIDEO_FMT_NTSC_J,					/**< NTSC-J */
	IMP_HDMI_VIDEO_FMT_NTSC_PAL_M,				/**< (M)PAL */
	IMP_HDMI_VIDEO_FMT_SECAM_SIN,				/**< SECAM_SIN*/
	IMP_HDMI_VIDEO_FMT_SECAM_COS,				/**< SECAM_COS*/
	IMP_HDMI_VIDEO_FMT_861D_640X480_60,
	IMP_HDMI_VIDEO_FMT_VESA_800X600_60,
	IMP_HDMI_VIDEO_FMT_VESA_1024X768_60,
	IMP_HDMI_VIDEO_FMT_VESA_1152X864_60,
	IMP_HDMI_VIDEO_FMT_VESA_1280X720_60,
	IMP_HDMI_VIDEO_FMT_VESA_1280X800_60,
	IMP_HDMI_VIDEO_FMT_VESA_1280X1024_60,
	IMP_HDMI_VIDEO_FMT_VESA_1366X768_60,
	IMP_HDMI_VIDEO_FMT_VESA_1440X900_60,
	IMP_HDMI_VIDEO_FMT_VESA_1440X900_60_RB,
	IMP_HDMI_VIDEO_FMT_VESA_1600X900_60_RB,
	IMP_HDMI_VIDEO_FMT_VESA_1600X1200_60,
	IMP_HDMI_VIDEO_FMT_VESA_1680X1050_60,
	IMP_HDMI_VIDEO_FMT_VESA_1920X1080_60,
	IMP_HDMI_VIDEO_FMT_VESA_1920X1200_60,
	IMP_HDMI_VIDEO_FMT_VESA_2048X1152_60,
	IMP_HDMI_VIDEO_FMT_2560x1440_30,
	IMP_HDMI_VIDEO_FMT_2560x1440_60,
	IMP_HDMI_VIDEO_FMT_2560x1600_60,
	IMP_HDMI_VIDEO_FMT_1920x2160_30,

	IMP_HDMI_VIDEO_FMT_3840X2160P_24,
	IMP_HDMI_VIDEO_FMT_3840X2160P_25,
	IMP_HDMI_VIDEO_FMT_3840X2160P_30,
	IMP_HDMI_VIDEO_FMT_3840X2160P_50,
	IMP_HDMI_VIDEO_FMT_3840X2160P_60,

	IMP_HDMI_VIDEO_FMT_4096X2160P_24,
	IMP_HDMI_VIDEO_FMT_4096X2160P_25,
	IMP_HDMI_VIDEO_FMT_4096X2160P_30,
	IMP_HDMI_VIDEO_FMT_4096X2160P_50,
	IMP_HDMI_VIDEO_FMT_4096X2160P_60,
	IMP_HDMI_VIDEO_FMT_VESA_CUSTOMER_DEFINE,
	IMP_HDMI_VIDEO_FMT_BUTT,
}IMP_HDMI_VIDEO_FMT_E;

/**
 *Defines the HDMI Color Space type enumeration
 */
typedef enum{
	IMP_HDMI_VIDEO_MODE_RGB444,			/**< RGB444 Mode,default RGB444*/
	IMP_HDMI_VIDEO_MODE_YCBCR422,		/**< YCBCR422 Mode*/
	IMP_HDMI_VIDEO_MODE_YCBCR444,		/**< YCBCR444 Mode*/
	IMP_HDMI_VIDEO_MODE_YCBCR420,		/**< YCBCR420 Mode*/
	IMP_HDMI_VIDEO_MODE_BUTT
}IMP_HDMI_VIDEO_MODE_E;

/**
 *Define HDMI Deep Color Pattern Enumeration
 */
typedef enum{
	IMP_HDMI_DEEP_COLOR_24BIT	= 0x00,	/**< HDMI Deep Color 24bit Mode*/
	IMP_HDMI_DEEP_COLOR_30BIT,			/**< HDMI Deep Color 30bit Mode*/
	IMP_HDMI_DEEP_COLOR_36BIT,			/**< HDMI Deep Color 36bit Mode*/
	IMP_HDMI_DEEP_COLOR_BUTT
}IMP_HDMI_DEEP_COLOR_E;

/**
 *Defines the enumeration of the CSC output quantization range.
 *The default is HDMI_QUANTIZATION_FULL_RANGE, which is not supported by the current HDMI_QUANTIZATION_LIMITED_RANGE
 */
typedef enum{
	HDMI_QUANTIZATION_LIMITED_RANGE,
	HDMI_QUANTIZATION_FULL_RANGE,
	HDMI_QUANTIZATION_BUTT
}IMP_HDMI_QUANTIZATION_E;

/**
 *Defines the audio sampling frequency enumeration.
 *Just for HDMI Infoframe, if you want to set the audio properties, please refer to the related SDK interface of HDMI Audio
 */
typedef enum{
	IMP_HDMI_SAMPLE_RATE_UNKNOW = 0,
	IMP_HDMI_SAMPLE_RATE_8K		= 8000,		/**< Audio Sample Rate 8KHz*/
	IMP_HDMI_SAMPLE_RATE_11K	= 11025,	/**< Audio Sample Rate 11KHz*/
	IMP_HDMI_SAMPLE_RATE_12K	= 12000,	/**< Audio Sample Rate 12KHz*/
	IMP_HDMI_SAMPLE_RATE_16K	= 16000,	/**< Audio Sample Rate 16KHz*/
	IMP_HDMI_SAMPLE_RATE_22K	= 22000,	/**< Audio Sample Rate 22KHz*/
	IMP_HDMI_SAMPLE_RATE_24K	= 24000,	/**< Audio Sample Rate 24KHz*/
	IMP_HDMI_SAMPLE_RATE_32K	= 32000,	/**< Audio Sample Rate 32KHz*/
	IMP_HDMI_SAMPLE_RATE_44K	= 44000,	/**< Audio Sample Rate 44KHz*/
	IMP_HDMI_SAMPLE_RATE_48K	= 48000,	/**< Audio Sample Rate 48KHz*/
	IMP_HDMI_SAMPLE_RATE_88K	= 88000,	/**< Audio Sample Rate 88KHz*/
	IMP_HDMI_SAMPLE_RATE_96K	= 96000,	/**< Audio Sample Rate 96KHz*/
	IMP_HDMI_SAMPLE_RATE_176K	= 176000,	/**< Audio Sample Rate 176KHz*/
	IMP_HDMI_SAMPLE_RATE_192K	= 192000,	/**< Audio Sample Rate 192KHz*/
	IMP_HDMI_SAMPLE_RATE_768K	= 768000,	/**< Audio Sample Rate 768KHz*/
	IMP_HDMI_SAMPLE_RATE_BUTT
}IMP_HDMI_SAMPLE_RATE_E;

/**
 *Defines an audio sampling bit-width enumeration.
 *Just for HDMI Infoframe, please refer to HDMI Audio related SDK interface to set audio properties
 */
typedef enum{
	IMP_HDMI_BIT_DEPTH_UNKNOWN =0,
	IMP_HDMI_BIT_DEPTH_8 = 8,			/**< Audio Sample Bit Deepth8Bit*/
	IMP_HDMI_BIT_DEPTH_16 = 16,			/**< Audio Sample Bit Deepth16Bit*/
	IMP_HDMI_BIT_DEPTH_18 = 18,			/**< Audio Sample Bit Deepth18Bit*/
	IMP_HDMI_BIT_DEPTH_20 = 20,			/**< Audio Sample Bit Deepth20Bit*/
	IMP_HDMI_BIT_DEPTH_24 = 24,			/**< Audio Sample Bit Deepth24Bit*/
	IMP_HDMI_BIT_DEPTH_BUTT
}IMP_HDMI_AUDIO_BIT_WIDTH_E;

/**
 *Defines the forced output mode enumeration used when an HDMI internal EDID read fails
 */
typedef enum{
	IMP_HDMI_FORCE_NULL,		/**< Default(HDMI Mode)*/
	IMP_HDMI_FORCE_HDMI,		/**< HDMI Mode*/
	IMP_HDMI_FORCE_DVI,			/**< DVI Mode*/
	IMP_HDMI_INIT_BOOT_CONFIG
}IMP_HDMI_FORCE_ACTION_E;

/**
 *Defines an HDMI audio format enumeration.
 *Just for HDMI Infoframe, this property cannot be set, can only be obtained from the EDID, and can only be read by the user
 **/
typedef enum{
	IMP_HDMI_AUDIO_FORMAT_CODE_RESERVED = 0x00,
	IMP_HDMI_AUDIO_FORMAT_CODE_PCM,				/**< PCM Format*/
	IMP_HDMI_AUDIO_FORMAT_CODE_AC3,				/**< AC3 Format*/
	IMP_HDMI_AUDIO_FORMAT_CODE_MPEG1,			/**< MPEG1 Format*/
	IMP_HDMI_AUDIO_FORMAT_CODE_MP3,				/**< MP3 Format*/
	IMP_HDMI_AUDIO_FORMAT_CODE_MPEG2,			/**< MPEG2 Format*/
	IMP_HDMI_AUDIO_FORMAT_CODE_AAC,				/**< AAC Format*/
	IMP_HDMI_AUDIO_FORMAT_CODE_DTS,				/**< DTS Format*/
	IMP_HDMI_AUDIO_FORMAT_CODE_ATRAC,			/**< ATRAC Format*/
	IMP_HDMI_AUDIO_FORMAT_CODE_ONE_BIT,			/**< ONE_BIT Format*/
	IMP_HDMI_AUDIO_FORMAT_CODE_DDP,				/**< DDP Format*/
	IMP_HDMI_AUDIO_FORMAT_CODE_DTS_HD,			/**< DTS_HD Format*/
	IMP_HDMI_AUDIO_FORMAT_CODE_MAT,				/**< MAT Format*/
	IMP_HDMI_AUDIO_FORMAT_CODE_DST,				/**< DST Format*/
	IMP_HDMI_AUDIO_FORMAT_CODE_WMA_PRO,			/**< WMA_PRO Format*/
	IMP_HDMI_AUDIO_FORMAT_CODE_BUTT,
}IMP_HDMI_AUDIO_FORMAT_CODE_E;

/**
 *Define speaker position, refer to CEA-861-F 7.5.3
 */
typedef enum{
	HDMI_AUDIO_SPEAKER_FL_FR,
	HDMI_AUDIO_SPEAKER_LFE,
	HDMI_AUDIO_SPEAKER_FC,
	HDMI_AUDIO_SPEAKER_RL_RR,
	HDMI_AUDIO_SPEAKER_RC,
	HDMI_AUDIO_SPEAKER_FLC_FRC,
	HDMI_AUDIO_SPEAKER_RLC_RRC,
	HDMI_AUDIO_SPEAKER_FLW_FRW,
	HDMI_AUDIO_SPEAKER_FLH_FRH,
	HDMI_AUDIO_SPEAKER_TC,
	HDMI_AUDIO_SPEAKER_FCH,
	HDMI_AUDIO_SPEAKER_BUTT,
}IMP_HDMI_AUDIO_SPEAKER_E;

/**
 *Defines HDMI audio capability set information
 */
typedef struct{
	IMP_HDMI_AUDIO_FORMAT_CODE_E enAudFmtCode;										/**< Supported audio formats*/
	IMP_HDMI_SAMPLE_RATE_E enSupportSampleRate[IMP_HDMI_MAX_SAMPE_RATE_NUM];		/**< Supported audio sampling rate*/
	IMP_U8 u8AudChannel;															/**< Number of supported audio channels*/
	IMP_HDMI_AUDIO_BIT_WIDTH_E enSupportBitDepth[IMP_HDMI_MAX_BIT_DEPTH_NUM];		/**< Supported sampling bit depth*/
	IMP_U32 u32SupportBitDepthNum;													/**< Supports different bit depth types*/
	IMP_U32 u32MaxBitRate;															/**< Maximum bit rate*/
}IMP_HDMI_AUDIO_INFO_S;

/**
 *Define the capability set structure of the HDMI Sink
 */
typedef struct{
	IMP_BOOL bConnected;											/**< Device connection*/
	IMP_BOOL bSupportHdmi;											/**< Whether the device supports HDMI (HDMI1.4 by default). If not,it is a DVI device*/
	IMP_BOOL bIsSinkPowerOn;										/**< Sink is powered on*/
	IMP_BOOL bIsRealEDID;											/**< Whether EDID actually obtains the flag from the sink device*/
	IMP_HDMI_VIDEO_FMT_E enNativeVideoFormat;						/**< Displays the physical resolution of the device*/
	IMP_BOOL bVideoFmtSupported[IMP_HDMI_VIDEO_FMT_BUTT];			/**< Video capability set*/
	IMP_BOOL bSupportYCbCr;											/**< Whether to support YCBCR display*/
	IMP_BOOL bSupportxvYCC601;										/**< Whether the xvYCC601 color format is supported*/
	IMP_BOOL bSupportxvYCC709;										/**< Whether the xvYCC709 color format is supported*/
	IMP_U8 u8MDBit;													/**< xvYCC601 Supported transfers*/
	IMP_U32 u32AudioInfoNum;										/**< Number of supported audio messages, value range [1 to 16]*/
	IMP_HDMI_AUDIO_INFO_S  stAudioInfo;								/**< Supported audio information*/
	IMP_BOOL bSpeaker[HDMI_AUDIO_SPEAKER_BUTT];						/**< Loudspeaker position*/
	IMP_U8 u8IDManufactureName[4];									/**< Device manufacturer identification*/
	IMP_U32 u32IDProductCode;										/**< Device ID*/
	IMP_U32 u32IDSerialNumber;										/**< Device serial number*/
	IMP_U32 u32WeekOfManufacture;									/**< Device production date (week)*/
	IMP_U32 u32YearOfManufacture;									/**< Device production date (year)*/
	IMP_U8 u8Version;												/**< Device version number*/
	IMP_U8 u8Revision;												/**< Device subversion number*/
	IMP_U8 u8EDIDExternBlockNum;									/**< Number of EDID extension blocks*/
	IMP_BOOL bIsPhyAddrValid;										/**< Indicates whether the CEC physical address is valid*/
	IMP_U8 u8PhyAddr_A;												/**< CEC Physical address A*/
	IMP_U8 u8PhyAddr_B;												/**< CEC Physical address B*/
	IMP_U8 u8PhyAddr_C;												/**< CEC Physical address C*/
	IMP_U8 u8PhyAddr_D;												/**< CEC Physical address D*/
	IMP_BOOL bSupportDVIDual;										/**< Whether DVI dual-link operation is supported*/
	IMP_BOOL bSupportDeepColorYCBCR444;								/**< Whether the YCBCR 4:4:4 Deep Color mode is supported*/
	IMP_BOOL bSupportDeepColor30Bit;								/**< Whether the Deep Color 30bit mode is supported*/
	IMP_BOOL bSupportDeepColor36Bit;								/**< Whether the Deep Color 36bit mode is supported*/
	IMP_BOOL bSupportDeepColor48Bit;								/**< Whether the Deep Color 48bit mode is supported*/
	IMP_BOOL bSupportAI;											/**< Whether the Supports_AI mode is supported*/
	IMP_U32 u32MaxTMDSClock;										/**< Max TMDS Clock*/
	IMP_BOOL bI_Latency_Fields_Present;								/**< Interlaced Transfer Delay flag bit*/
	IMP_BOOL bLatency_Fields_Present;								/**< Progressive Transfer Delay flag bit*/
	IMP_BOOL bHDMI_Video_Present;									/**< Special HDMI flag(not used)*/
	IMP_U8 u8Video_Latency;											/**< Progressive video delay*/
	IMP_U8 u8Audio_Latency;											/**< Progressive audio delay*/
	IMP_U8 u8Interlaced_Video_Latency;								/**< Interlaced video delay*/
	IMP_U8 u8Interlaced_Audio_Latency;								/**< Interlaced audio delay*/
	IMP_BOOL bSupportY420DC30Bit;									/**< Specifies whether the deep-color 30bit mode of YCbCr420 is supported*/
	IMP_BOOL bSupportY420DC36Bit;									/**< Specifies whether the deep-color 36bit mode of YCbCr420 is supported*/
	IMP_BOOL bSupportY420DC48Bit;									/**< Specifies whether the deep-color 48bit mode of YCbCr420 is supported*/
	IMP_BOOL bSupportHdmi_2_0;										/**< Specifies whether hdmi2.0 is supported*/
	IMP_BOOL bSupportY420Format[IMP_HDMI_VIDEO_FMT_BUTT];			/**< Supports YCbCr420 video format*/
	IMP_BOOL bOnlySupportY420Format[IMP_HDMI_VIDEO_FMT_BUTT];		/**< Only the YCbCr420 video format is supported*/
}IMP_HDMI_SINK_CAPABILITY_S;

/**
 *Define the HDMI attribute structure
 */
typedef struct{
	IMP_BOOL					bEnableHdmi;				/**< Whether to output HDMI*/

	IMP_BOOL					bEnableVideo;				/**< Whether to enable video*/
	IMP_HDMI_VIDEO_FMT_E		enVideoFmt;					/**< Video resolution. This parameter must be consistent with the VO configuration*/

	IMP_HDMI_VIDEO_MODE_E		enVideoMode;				/**< HDMI output video mode*/
	IMP_HDMI_DEEP_COLOR_E		enDeepColor;				/**< DeepColor Output mode*/
	IMP_HDMI_QUANTIZATION_E		enOutQuantization;			/**< HDMI output video quantization range*/
	IMP_BOOL					bxvYCCMode;					/**< Whether to enable the xvYCC output mode*/

	IMP_BOOL					bEnableAudio;				/**< Whether to enable audio*/

	IMP_BOOL					bEnableAviInfoframe;		/**< Whether to enable AVI InfoFrame*/
	IMP_BOOL					bEnableAudInfoframe;		/**< Whether to enable AUDIO InfoFrame*/
	IMP_BOOL					bEnableSpdInfoframe;		/**< Whether to enable SPD InfoFrame*/
	IMP_BOOL					bEnableMpegInfoframe;		/**< Whether to enable MPEG InfoFrame*/

	IMP_BOOL					bDebugFlag;					/**< Whether to enable hdmi internal debug messages*/
	IMP_BOOL					bHDCPEnable;				/**< Whether to activate the HDCP*/

	IMP_BOOL					b3DEnable;					/**< Whether to activate the 3D mode*/
	IMP_U8						u83DParam;					/**< 3D parameter. The default value is 0*/
	IMP_BOOL					bAuthMode;					/**< When EDID read failed, HDMI internal mandatory video output mode enumeration*/
	IMP_HDMI_FORCE_ACTION_E		enDefaultMode;				/**< If this mode is enabled, HDMI forces output*/
	IMP_BOOL					bEnableVidModeAdapt;		/**< Whether to enable the driver color space adaptive function*/
	IMP_BOOL					bEnableDeepClrAdapt;		/**< Whether to enable the drive Deepcolor adaptive policy*/
	IMP_U32						u32PixelClk;				/**< User set pixel clock with custom timing (unit: kHz)*/

}IMP_HDMI_ATTR_S;

/**
 *Defines the HDMI event notification enumeration
 */
typedef enum{
	IMP_HDMI_EVENT_HOTPLUG = 0x10,				/**< HDMI Cable insertion event*/
	IMP_HDMI_EVENT_NO_PLUG,						/**< HDMI Cable unplug event*/
	IMP_HDMI_EVENT_EDID_FAIL,					/**< HDMI EDID read failure event*/
	IMP_HDMI_EVENT_HDCP_FAIL,					/**< HDCP validation failure event*/
	IMP_HDMI_EVENT_HDCP_SUCCESS,				/**< HDCP validates the success event*/
	IMP_HDMI_EVENT_HDCP_USERSETTING = 0x17,		/**< HDCP Reset*/
	IMP_HDMI_EVENT_BUTT
}IMP_HDMI_EVENT_TYPE_E;

/**
 *Define the HDMI callback function pointer type
 */
typedef void (*IMP_HDMI_CallBack)(IMP_HDMI_EVENT_TYPE_E event, IMP_VOID *pPrivateData);

/**
 *Define the HDMI callback structure
 */
typedef struct{
	IMP_HDMI_CallBack pfnHdmiEventCallback;		/**< Event handling callback function*/
	IMP_VOID *pPrivateData;						/**< Callback function parameter private data*/
}IMP_HDMI_CALLBACK_FUNC_S;

/**
 *Define the HDMI color space structure
 */
typedef struct{
	IMP_HDMI_VIDEO_MODE_E enVideoMode;			/**< Video Mode Enum*/
	IMP_HDMI_DEEP_COLOR_E enDeepColor;			/**< Deep Color Enum*/
}IMP_HDMI_COLOR_SPACE_S;

/**
 *Define the HDMI EDID information structure
 */
typedef struct{
	IMP_U32 u32Edidlength;			/**< EDID information data length*/
	IMP_U8 u8Edid[512];				/**< EDID content*/
}IMP_HDMI_EDID_S;

/**
 *Define the type of HDMI information frame
 */
typedef enum{
	IMP_INFOFRAME_TYPE_AVI,			/**< AVI Infoframe*/
	IMP_INFOFRAME_TYPE_SPD,			/**< SPD Infoframe*/
	IMP_INFOFRAME_TYPE_AUDIO,		/**< AUDIO Infoframe*/
	IMP_INFOFRAME_TYPE_MPEG,		/**< MPEG Infoframe*/
	IMP_INFOFRAME_TYPE_VENDORSPEC,	/**< VENDORSPEC Infoframe*/
	IMP_INFOFRAME_TYPE_BUTT
}IMP_HDMI_INFOFRAME_TYPE_E;

/**
 *Define the Color_Space Enum
 */
typedef enum{
	IMP_HDMI_COLOR_SPACE_RGB444,		/**< RGB444   Mode*/
	IMP_HDMI_COLOR_SPACE_YCBCR422,		/**< YCBCR422 Mode*/
	IMP_HDMI_COLOR_SPACE_YCBCR444,		/**< YCBCR444 Mode*/
	IMP_HDMI_COLOR_SPACE_YCBCR420,		/**< YCBCR420 Mode*/
}IMP_HDMI_COLOR_SPACE_E;

/**
 *Define Bar Enum
 */
typedef enum{
	IMP_HDMI_BAR_INFO_NOT_VALID,
	IMP_HDMI_BAR_INFO_V,
	IMP_HDMI_BAR_INFO_H,
	IMP_HDMI_BAR_INFO_VH
}IMP_HDMI_BARINFO_E;

/**
 *Define Scan Enum
 */
typedef enum{
	HDMI_SCAN_INFO_NO_DATA = 0,
	HDMI_SCAN_INFO_OVERSCANNED = 1,		/**< Sink Supports Overscan*/
	HDMI_SCAN_INFO_UNDERSCANNED = 2,	/**< Sink Unsupports Overscan*/
	HDMI_SCAN_INFO_FUTURE
}IMP_HDMI_SCANINFO_E;

/**
 *Define Colorimetry Enum
 */
typedef enum{
	HDMI_COLORIMETRY_NO_DATA,
	HDMI_COLORIMETRY_ITU601,			/**< Colorimetry 601*/
	HDMI_COLORIMETRY_ITU709,			/**< Colorimetry 709*/
	HDMI_COLORIMETRY_EXTENDED,
}IMP_HDMI_COLORIMETRY_E;

/**
 *Define Extend Colorimetry Enum
 */
typedef enum{
	HDMI_COLORIMETRY_XVYCC_601,					/**< Colorimetry 601*/
	HDMI_COLORIMETRY_XVYCC_709,					/**< Colorimetry 709*/
	HDMI_COLORIMETRY_S_YCC_601,					/**< Colorimetry YCC601*/
	HDMI_COLORIMETRY_ADOBE_YCC_601,				/**< Colorimetry RGB*/
	HDMI_COLORIMETRY_ADOBE_RGB,					/**< Colorimetry 601*/
	HDMI_COLORIMETRY_2020_CONST_LUMINOUS,		/**< Colorimetry 2020 Luminous*/
	HDMI_COLORIMETRY_2020_NON_CONST_LUMINOUS,	/**< Colorimetry 2020 no Luminous*/
	HDMI_COLORIMETRY_RESERVED
}IMP_HDMI_EXT_COLORIMETRY_E;

/**
 *Define image aspect ratio enumeration
 */
typedef enum{
	IMP_HDMI_PIC_ASP_RATIO_NO_DATA,
	IMP_HDMI_PIC_ASP_RATIO_4TO3,				/**< 4:3 Mode*/
	IMP_HDMI_PIC_ASP_RATIO_16TO9,				/**< 16:9 Mode*/
	IMP_HDMI_PIC_ASP_RATIO_64TO27,				/**< 64:27 Mode*/
	IMP_HDMI_PIC_ASP_RATIO_256TO135,			/**< 256:135 Mode*/
	IMP_HDMI_PIC_ASP_RATIO_RESERVED,
}IMP_HDMI_PIC_ASPECT_RATIO_E;

/**
 *Defines the actual image aspect ratio enumeration
 */
typedef enum{
	IMP_HDMI_ACT_ASP_RATIO_RESERVED_0,
	IMP_HDMI_ACT_ASP_RATIO_RESERVED_1,
	IMP_HDMI_ACT_ASP_RATIO_16TO9_TOP,
	IMP_HDMI_ACT_ASP_RATIO_14TO9_TOP,
	IMP_HDMI_ACT_ASP_RATIO_16TO9_BOX_CENTER,
	IMP_HDMI_ACT_ASP_RATIO_RESERVED_5,
	IMP_HDMI_ACT_ASP_RATIO_RESERVED_6,
	IMP_HDMI_ACT_ASP_RATIO_RESERVED_7,
	IMP_HDMI_ACT_ASP_RATIO_SAME_PIC,
	IMP_HDMI_ACT_ASP_RATIO_4TO3_CENTER,
	IMP_HDMI_ACT_ASP_RATIO_16TO9_CENTER,
	IMP_HDMI_ACT_ASP_RATIO_14TO9_CENTER,
	IMP_HDMI_ACT_ASP_RATIO_RESERVED_12,
	IMP_HDMI_ACT_ASP_RATIO_4TO3_14_9,
	IMP_HDMI_ACT_ASP_RATIO_16TO9_14_9,
	IMP_HDMI_ACT_ASP_RATIO_16TO9_4_3,
}IMP_HDMI_ACT_ASPECT_RATIO_E;

/**
 *Defines an image scan information enumeration
 */
typedef enum{
	IMP_HDMI_PICTURE_NON_UNIFORM_SCALING,
	IMP_HDMI_PICTURE_SCALING_H,
	IMP_HDMI_PICTURE_SCALING_V,
	IMP_HDMI_PICTURE_SCALING_HV
}IMP_HDMI_PICTURE_SCALING_E;

/**
 *Defines an RGB quantization range enumeration
 */
typedef enum{
	IMP_HDMI_RGB_QUANTIZATION_DEFAULT_RANGE,
	IMP_HDMI_RGB_QUANTIZATION_LIMITED_RANGE,
	IMP_HDMI_RGB_QUANTIZATION_FULL_RANGE,
	IMP_HDMI_RGB_QUANTIZATION_FULL_RESERVED
}IMP_HDMI_RGB_QUAN_RAGE_E;

/**
 *Defines an enumeration of pixel copy times
 */
typedef enum{
	IMP_HDMI_PIXEL_REPET_NO,
	IMP_HDMI_PIXEL_REPET_2_TIMES,
	IMP_HDMI_PIXEL_REPET_3_TIMES,
	IMP_HDMI_PIXEL_REPET_4_TIMES,
	IMP_HDMI_PIXEL_REPET_5_TIMES,
	IMP_HDMI_PIXEL_REPET_6_TIMES,
	IMP_HDMI_PIXEL_REPET_7_TIMES,
	IMP_HDMI_PIXEL_REPET_8_TIMES,
	IMP_HDMI_PIXEL_REPET_9_TIMES,
	IMP_HDMI_PIXEL_REPET_10_TIMES,
	IMP_HDMI_PIXEL_REPET_RESERVED_A,
	IMP_HDMI_PIXEL_REPET_RESERVED_B,
	IMP_HDMI_PIXEL_REPET_RESERVED_C,
	IMP_HDMI_PIXEL_REPET_RESERVED_D,
	IMP_HDMI_PIXEL_REPET_RESERVED_E,
	IMP_HDMI_PIXEL_REPET_RESERVED_F,
}IMP_HDMI_PIXEL_REPETITION_E;

/**
 *Define the content information enumeration
 */
typedef enum{
	IMP_HDMI_CONTNET_GRAPHIC,
	IMP_HDMI_CONTNET_PHOTO,
	IMP_HDMI_CONTNET_CINEMA,
	IMP_HDMI_CONTNET_GAME
}IMP_HDMI_CONTENT_TYPE_E;

/**
 *Define the YCC quantization range enumeration
 */
typedef enum{
	IMP_HDMI_YCC_QUANTIZATION_LIMITED_RANGE,
	IMP_HDMI_YCC_QUANTIZATION_FULL_RANGE,
	IMP_HDMI_YCC_QUANTIZATION_RESERVED_2,
	IMP_HDMI_YCC_QUANTIZATION_RESERVED_3
}IMP_HDMI_YCC_QUAN_RAGE_E;

/**
 *Defines the audio channel enumeration
 */
typedef enum{
	IMP_HDMI_AUDIO_CHANEL_CNT_STREAM,
	IMP_HDMI_AUDIO_CHANEL_CNT_2,
	IMP_HDMI_AUDIO_CHANEL_CNT_3,
	IMP_HDMI_AUDIO_CHANEL_CNT_4,
	IMP_HDMI_AUDIO_CHANEL_CNT_5,
	IMP_HDMI_AUDIO_CHANEL_CNT_6,
	IMP_HDMI_AUDIO_CHANEL_CNT_7,
	IMP_HDMI_AUDIO_CHANEL_CNT_8,
}IMP_HDMI_AUDIO_CHANEL_CNT_E;

/**
 *Defines an audio encoding type enumeration
 */
typedef enum{
	IMP_HDMI_AUDIO_CODING_REFER_STREAM_HEAD,
	IMP_HDMI_AUDIO_CODING_PCM,
	IMP_HDMI_AUDIO_CODING_AC3,
	IMP_HDMI_AUDIO_CODING_MPEG1,
	IMP_HDMI_AUDIO_CODING_MP3,
	IMP_HDMI_AUDIO_CODING_MPEG2,
	IMP_HDMI_AUDIO_CODING_AACLC,
	IMP_HDMI_AUDIO_CODING_DTS,
	IMP_HDMI_AUDIO_CODING_ATRAC,
	IMP_HDMI_AUDIO_CODIND_ONE_BIT_AUDIO,
	IMP_HDMI_AUDIO_CODING_ENAHNCED_AC3,
	IMP_HDMI_AUDIO_CODING_DTS_HD,
	IMP_HDMI_AUDIO_CODING_MAT,
	IMP_HDMI_AUDIO_CODING_DST,
	IMP_HDMI_AUDIO_CODING_WMA_PRO,
	IMP_HDMI_AUDIO_CODING_MAX
}IMP_HDMI_CODING_TYPE_E;

/**
 *Defines an audio sample size enumeration
 */
typedef enum{
	IMP_HDMI_AUDIO_SAMPLE_SIZE_STREAM,
	IMP_HDMI_AUDIO_SAMPLE_SIZE_16,
	IMP_HDMI_AUDIO_SAMPLE_SIZE_20,
	IMP_HDMI_AUDIO_SAMPLE_SIZE_24,
}IMP_HDMI_AUDIO_SAMPLE_SIZE_E;

/**
 *Defines an audio sampling frequency enumeration
 */
typedef enum{
	IMP_HDMI_AUDIO_SAMPLE_FREQ_STREAM,
	IMP_HDMI_AUDIO_SAMPLE_FREQ_32000,
	IMP_HDMI_AUDIO_SAMPLE_FREQ_44100,
	IMP_HDMI_AUDIO_SAMPLE_FREQ_48000,
	IMP_HDMI_AUDIO_SAMPLE_FREQ_88200,
	IMP_HDMI_AUDIO_SAMPLE_FREQ_96000,
	IMP_HDMI_AUDIO_SAMPLE_FREQ_176400,
	IMP_HDMI_AUDIO_SAMPLE_FREQ_192000,
}IMP_HDMI_AUDIO_SAMPLE_FREQ_E;

/**
 *Define an audio Shift information enumeration
 */
typedef enum{
	IMP_HDMI_LEVEL_SHIFT_VALUE_0_DB,
	IMP_HDMI_LEVEL_SHIFT_VALUE_1_DB,
	IMP_HDMI_LEVEL_SHIFT_VALUE_2_DB,
	IMP_HDMI_LEVEL_SHIFT_VALUE_3_DB,
	IMP_HDMI_LEVEL_SHIFT_VALUE_4_DB,
	IMP_HDMI_LEVEL_SHIFT_VALUE_5_DB,
	IMP_HDMI_LEVEL_SHIFT_VALUE_6_DB,
	IMP_HDMI_LEVEL_SHIFT_VALUE_7_DB,
	IMP_HDMI_LEVEL_SHIFT_VALUE_8_DB,
	IMP_HDMI_LEVEL_SHIFT_VALUE_9_DB,
	IMP_HDMI_LEVEL_SHIFT_VALUE_10_DB,
	IMP_HDMI_LEVEL_SHIFT_VALUE_11_DB,
	IMP_HDMI_LEVEL_SHIFT_VALUE_12_DB,
	IMP_HDMI_LEVEL_SHIFT_VALUE_13_DB,
	IMP_HDMI_LEVEL_SHIFT_VALUE_14_DB,
	IMP_HDMI_LEVEL_SHIFT_VALUE_15_DB,
}IMP_HDMI_LEVEL_SHIFT_VALUE_E;

/**
 *Defines the Audio Playback information enumeration
 */
typedef enum{
	IMP_HDMI_LFE_PLAYBACK_NO,
	IMP_HDMI_LFE_PLAYBACK_0_DB,
	IMP_HDMI_LFE_PLAYBACK_10_DB,
	IMP_HDMI_LFE_PLAYBACK_RESEVED,
}IMP_HDMI_LFE_PLAYBACK_LEVEL_E;

/**
 *Defines the CSC output quantization range enumeration
 */
typedef struct{
	IMP_HDMI_VIDEO_FMT_E enTimingMode;
	IMP_HDMI_COLOR_SPACE_E enColorSpace;
	IMP_BOOL bActive_Infor_Present;
	IMP_HDMI_BARINFO_E enBarInfo;
	IMP_HDMI_SCANINFO_E enScanInfo;

	IMP_HDMI_COLORIMETRY_E enColorimetry;
	IMP_HDMI_EXT_COLORIMETRY_E enExtColorimetry;
	IMP_HDMI_PIC_ASPECT_RATIO_E enAspectRatio;
	IMP_HDMI_ACT_ASPECT_RATIO_E enActiveAspectRatio;
	IMP_HDMI_PICTURE_SCALING_E enPictureScaling;

	IMP_HDMI_RGB_QUAN_RAGE_E enRGBQuantization;
	IMP_BOOL bIsITContent;
	IMP_HDMI_PIXEL_REPETITION_E enPixelRepetition;
	IMP_HDMI_CONTENT_TYPE_E enContentType;
	IMP_HDMI_YCC_QUAN_RAGE_E enYCCQuantization;
	IMP_U16 u16LineNEndofTopBar;
	IMP_U16 u16LineNStartofBotBar;
	IMP_U16 u16PixelNEndofLeftBar;
	IMP_U16 u16PixelNStartofRightBar;
}IMP_HDMI_AVI_INFOFRAME_VER2_S;

/**
 *Defines the HDMI AUDIO Information Frame (version 1) unit structure
 */
typedef struct{
	IMP_HDMI_AUDIO_CHANEL_CNT_E enChannelCount;				/**< Number of audio channels*/
	IMP_HDMI_CODING_TYPE_E enCodingType;					/**< Audio format*/
	IMP_HDMI_AUDIO_SAMPLE_SIZE_E enSampleSize;				/**< Audio sampling depth (bit width)*/
	IMP_HDMI_AUDIO_SAMPLE_FREQ_E enSamplingFrequency;		/**< Audio sampling rate*/
	IMP_U8 u8ChannelAlloc;									/**< Channel/Speaker allocate*/
	IMP_HDMI_LEVEL_SHIFT_VALUE_E enLevelShift;				/**< Level Shift Value*/
	IMP_HDMI_LFE_PLAYBACK_LEVEL_E enLfePlaybackLevel;		/**< LFE playback level information，LFE*/
	IMP_BOOL bDownmixInhibit;								/**< Down-mix Inhibit bit flag*/
}IMP_HDMI_AUD_INFOFRAME_VER1_S;

/**
 *Defines the HDMI SPD information frame unit structure
 */
typedef struct{
	IMP_U8 u8VendorName[8];				/**< Source Indicates the vendor name*/
	IMP_U8 u8ProductDescription[16];	/**< Source Product type description*/
}IMP_HDMI_SPD_INFOFRAME_S;

/**
 *Defines the HDMI MPEG information frame unit structure
 */
typedef struct{
	IMP_U32 u32MPEGBitRate;				/**< MPEG bit rate*/
	IMP_BOOL bIsFieldRepeated;			/**< Whether the current frame is a repeate frame*/
}IMP_HDMI_MPEGSOURCE_INFOFRAME_S;

/**
 *Defines the HDMI VS information frame unit structure
 */
typedef struct{
	IMP_U32 u32RegistrationId;			/**< IEEE registration code*/
}IMP_HDMI_VENDORSPEC_INFOFRAME_S;

/**
 *Defines the HDMI information frame unit association
 */
typedef union{
	IMP_HDMI_AVI_INFOFRAME_VER2_S stAVIInfoFrame;				/**< AVI information frame unit*/
	IMP_HDMI_AUD_INFOFRAME_VER1_S stAUDInfoFrame;				/**< AUDIO information frame unit*/
	IMP_HDMI_SPD_INFOFRAME_S stSPDInfoFrame;					/**< SPD information frame unit*/
	IMP_HDMI_MPEGSOURCE_INFOFRAME_S stMPEGSourceInfoFrame;		/**< MPEG information frame unit*/
	IMP_HDMI_VENDORSPEC_INFOFRAME_S stVendorSpecInfoFrame;		/**< VS information frame unit*/
}IMP_HMDI_INFORFRAME_UNIT_U;

/**
 *Defines the HDMI information frame structure
 */
typedef struct{
	IMP_HDMI_INFOFRAME_TYPE_E enInfoFrameType;					/**< Information frame type*/
	IMP_HMDI_INFORFRAME_UNIT_U unInforUnit;						/**< Information frame unit*/
}IMP_HDMI_INFOFRAME_S;

/**
 *Defines the HDMI CSC schema enumeration
 */
typedef enum{
	BT601_FULL = 0,
	BT601_LIMITED,
	BT709_FULL,
	BT709_LIMITED,
	BT2020_FULL,
	BT2020_LIMITED,
	CSC_VERSION_BUTT,
}IMP_HDMI_CSC_E;

/**
 * @fn IMP_S32 IMP_HDMI_Init(IMP_VOID)

 * HDMI initialization.

 * @param[in] NULL.

 * @retval 0 Success.
 * @retval non0 Failed.

 * @remarks NULL.
 * @attention Needs to be called after VO Enable.
 */
IMP_S32 IMP_HDMI_Init(IMP_VOID);

/**
 * @fn IMP_S32 IMP_HDMI_DeInit(IMP_VOID)

 * HDMI deinitializes.

 * @param[in] NULL.

 * @retval 0 Success.
 * @retval non0 Failed.

 * @remarks NULL.
 * @attention Needs to be called after VO Enable.
 */
IMP_S32 IMP_HDMI_DeInit(IMP_VOID);

/**
 * @fn IMP_S32 IMP_HDMI_SetAttr(IMP_HDMI_ID_E enHdmi,IMP_HDMI_ATTR_S *pstAttr)

 * Set HDMI parameters.

 * @param[in] enHdmi HDMI ID.
 * @param[in] pstAttr HDMI attribute structure pointer.

 * @retval 0 Success.
 * @retval non0 Failed.

 * @remarks NULL.
 * @attention Need to be called after VO Enable;
 *			  If you want to set only some attributes, obtain the attributes before setting them,
 *			  assign values to the attributes, and then set them.
 */
IMP_S32 IMP_HDMI_SetAttr(IMP_HDMI_ID_E enHdmi,IMP_HDMI_ATTR_S *pstAttr);

/**
 * @fn IMP_S32 IMP_HDMI_GetAttr(IMP_HDMI_ID_E enHdmi,IMP_HDMI_ATTR_S *pstAttr)

 * Get HDMI parameters.

 * @param[in]  enHdmi HDMI ID.
 * @param[in] pstAttr HDMI attribute structure pointer.

 * @retval 0 Success.
 * @retval non0 Failed.

 * @remarks NULL.
 * @attention Need to be called after VO Enable;
 *			  If you want to set only some attributes, obtain the attributes before setting them,
 *			  assign values to the attributes, and then set them.
 */
IMP_S32 IMP_HDMI_GetAttr(IMP_HDMI_ID_E enHdmi,IMP_HDMI_ATTR_S *pstAttr);

/**
 * @fn IMP_S32 IMP_HDMI_Start(IMP_HDMI_ID_E enHdmi)
 *
 * Start HDMI output.

 * @param[in]  enHdmi HDMI ID.

 * @retval 0 Success.
 * @retval non0 Failed.

 * @remarks NULL.
 * @attention Needs to be called after VO Enable.
 */
IMP_S32 IMP_HDMI_Start(IMP_HDMI_ID_E enHdmi);

/**
 * @fn IMP_S32 IMP_HDMI_Stop(IMP_HDMI_ID_E enHdmi)
 *
 * Stop HDMI output.

 * @param[in]  enHdmi HDMI ID.

 * @retval 0 Success.
 * @retval non0 Failed.

 * @remarks NULL.
 * @attention Needs to be called after VO Enable.
 */
IMP_S32 IMP_HDMI_Stop(IMP_HDMI_ID_E enHdmi);

/**
 * @fn IMP_S32 IMP_HDMI_GetSinkCapability(IMP_HDMI_ID_E enHdmi,IMP_HDMI_SINK_CAPABILITY_S *pstSinkCap)
 *
 * Obtain the Sink capability set.

 * @param[in]  enHdmi HDMI ID号.
 * @param[out]  pstSinkCap HDMI Sink Capability structure pointer.

 * @retval 0 Success.
 * @retval non0 Failed.

 * @remarks NULL.
 * @attention Need to be called after VO Enable;
 *            It should be called after HDMI is started and the cable is plugged in.
 */
IMP_S32 IMP_HDMI_GetSinkCapability(IMP_HDMI_ID_E enHdmi,IMP_HDMI_SINK_CAPABILITY_S *pstSinkCap);

/**
 * @fn IMP_S32 IMP_HDMI_SetAVMute(IMP_HDMI_ID_E enHdmi,IMP_BOOL bAVmute)
 *
 * Set HDMI audio and video Mute.

 * @param[in]  enHdmi HDMI ID.
 * @param[in]  bAVmute HDMI audio and video Mute flag bit.

 * @retval 0 Success.
 * @retval non0 Failed.

 * @remarks NULL.
 * @attention Needs to be called after VO Enable.
 */
IMP_S32 IMP_HDMI_SetAVMute(IMP_HDMI_ID_E enHdmi,IMP_BOOL bAVmute);

/**
 * @fn IMP_S32 IMP_HDMI_Force_GetEDID(IMP_HDMI_ID_E enHdmi,IMP_HDMI_EDID_S *pstEdidData)
 *
 * Get HDMI raw EDID data.

 * @param[in]  enHdmi HDMI ID.
 * @param[out]  pstEdidData HDMI EDID structure pointer.

 * @retval 0 Success.
 * @retval non0 Failed.

 * @remarks NULL.
 * @attention Need to be called after VO Enable;
 *            It should be called after HDMI is started and the cable is plugged in.
 */
IMP_S32 IMP_HDMI_Force_GetEDID(IMP_HDMI_ID_E enHdmi,IMP_HDMI_EDID_S *pstEdidData);

/**
 * @fn IMP_S32 IMP_HDMI_RegCallbackFunc(IMP_HDMI_ID_E enHdmi,IMP_HDMI_CALLBACK_FUNC_S *pstCallbackFunc)
 *
 * Register the HDMI event callback function.

 * @param[in]  enHdmi HDMI ID.
 * @param[in]  pstCallbackFunc HDMI Callback function structure pointer.

 * @retval 0 Success.
 * @retval non0 Failed.

 * @remarks NULL.
 * @attention Need to be called after VO Enable;
 *            If the user has registered the event callback function,
 *            the undo event callback function should be used before exiting HDMI.
 */
IMP_S32 IMP_HDMI_RegCallbackFunc(IMP_HDMI_ID_E enHdmi,IMP_HDMI_CALLBACK_FUNC_S *pstCallbackFunc);

/**
 * @fn IMP_S32 IMP_HDMI_UnRegCallbackFunc(IMP_HDMI_ID_E enHdmi,IMP_HDMI_CALLBACK_FUNC_S *pstCallbackFunc)
 *
 * Unregister the HDMI event callback function.

 * @param[in]  enHdmi HDMI ID.
 * @param[in]  pstCallbackFunc HDMI Callback function structure pointer.

 * @retval 0 Success.
 * @retval non0 Failed.

 * @remarks NULL.
 * @attention Need to be called after VO Enable;
 *            If the user has registered the event callback function,
 *            the undo event callback function should be used before exiting HDMI.
 */
IMP_S32 IMP_HDMI_UnRegCallbackFunc(IMP_HDMI_ID_E enHdmi,IMP_HDMI_CALLBACK_FUNC_S *pstCallbackFunc);

/**
 * @fn IMP_S32 IMP_HDMI_SetDeepColor(IMP_HDMI_ID_E enHdmi,IMP_HDMI_COLOR_SPACE_S *pstColorSpace)
 *
 * Set the HDMI DeepColor mode.

 * @param[in]  enHdmi HDMI ID.
 * @param[in]  pstColorSpace HDMI Deep Color Mode.

 * @retval 0 Success.
 * @retval non0 Failed.

 * @remarks NULL.
 * @attention Need to be called after VO Enable
 */
IMP_S32 IMP_HDMI_SetDeepColor(IMP_HDMI_ID_E enHdmi,IMP_HDMI_COLOR_SPACE_S *pstColorSpace);

/**
 * @fn IMP_S32 IMP_HDMI_SetDeepColor(IMP_HDMI_ID_E enHdmi,IMP_HDMI_COLOR_SPACE_S *pstColorSpace)
 *
 * Get the HDMI DeepColor mode.

 * @param[in]   enHdmi HDMI ID.
 * @param[out]  pstColorSpace HDMI Deep Color Mode.

 * @retval 0 Success.
 * @retval non0 Failed.

 * @remarks NULL.
 * @attention Need to be called after VO Enable
 */
IMP_S32 IMP_HDMI_GetDeepColor(IMP_HDMI_ID_E enHdmi,IMP_HDMI_COLOR_SPACE_S *pstColorSpace);

/**
 * @fn IMP_S32 IMP_HDMI_SetInfoFrame(IMP_HDMI_ID_E enHdmi,IMP_HDMI_INFOFRAME_S *pstInfoFrame)
 *
 * Set the HDMI Infoframe.

 * @param[in]   enHdmi HDMI ID.
 * @param[in]   pstInfoFrame HDMI information frame structure pointer.

 * @retval 0 Success.
 * @retval non0 Failed.

 * @remarks NULL.
 * @attention Need to be called after VO Enable;
 *            All information frames set in DVI mode cannot take effect,
 */
IMP_S32 IMP_HDMI_SetInfoFrame(IMP_HDMI_ID_E enHdmi,IMP_HDMI_INFOFRAME_S *pstInfoFrame);

/**
 * @fn IMP_S32 IMP_HDMI_GetInfoFrame(IMP_HDMI_ID_E enHdmi,IMP_HDMI_INFOFRAME_S *pstInfoFrame)
 *
 * Get the HDMI Infoframe.

 * @param[in]   enHdmi HDMI ID.
 * @param[in]   pstInfoFrame HDMI information frame structure pointer.

 * @retval 0 Success.
 * @retval non0 Failed.

 * @remarks NULL.
 * @attention Need to be called after VO Enable;
 */
IMP_S32 IMP_HDMI_GetInfoFrame(IMP_HDMI_ID_E enHdmi,IMP_HDMI_INFOFRAME_S *pstInfoFrame);

/**
 * @fn IMP_S32 IMP_HDMI_SET_CSC(IMP_HDMI_ID_E enHdmi,IMP_HDMI_CSC_E enCsc_Version);
 *
 * Set HDMI CSC Mode.

 * @param[in]   enHdmi HDMI ID.
 * @param[in]   enCsc_Version HDMI CSC Mode enumeration.

 * @retval 0 Success.
 * @retval non0 Failed.

 * @remarks NULL.
 * @attention Need to be called after VO Enable;
 */
IMP_S32 IMP_HDMI_SET_CSC(IMP_HDMI_ID_E enHdmi,IMP_HDMI_CSC_E enCsc_Version);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
