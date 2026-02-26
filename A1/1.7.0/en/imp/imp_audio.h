/*
 * Audio utils header file.

 * Copyright (C) 2014 Ingenic Semiconductor Co.,Ltd
 */

#ifndef __IMP_AUDIO_H__
#define __IMP_AUDIO_H__
#include <stdint.h>
#include "imp_type.h"
#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

/**
 * @file
 * IMP Audio header file
 */

/**
 * @defgroup IMP_Audio
 * @ingroup imp
 * @brief Audio module, including recording and playback, codec, volume and
 * gain settings, echo cancellation, automatic gain and other funtions.
 *
 *
 * @section 1 audio_summary
 * Audio function contains 5 modules: audio input, audio output,
 * echo cancellation, audio encodingand audio decoding.
 *
 * Where audio input and audio output exist the concept of device and channel.
 * One of the mics we consider as a Device, while a MIC can have multiple
 * channel inputs. The same SPK we consider as a playback Device, and a SPK
 * can also have multiple Channeloutputs.
 * The current version of the audio API only supports one Channel per Device.
 *
 * Echo cancellation is located in the audio input interface, and the specific
 * instructions are reflected in the functional description.
 *
 * Audio Encoding and decoding The current audio API supports PT_G711A,
 * PT_G711U and PT_G726 format audio encoding and decoding,
 * if you need to add a new codec, you need to register.
 *
 *
 * @section 2 audio_function_description
 * The following is a description of each module:
 *
 * @subsection 2.1 audio_in
 * Audio input Device ID correspondence:  0:  Digital MIC 	1: Analog MIC
 * Audio input Channel Currently the API only supports 1 channel.
 *
 * @subsection 2.2 audio_out
 * Audio output Device ID correspondence: 0: Default SPK 	1: Other SPKs
 * Audio output Channel Currently the API only supports 1 channel.
 *
 * The volume setting for the audio INPUT(OUTPUT), ranging from [-30 to 120].
 * -30 means mute, 120 means amplify the sound by 30dB, and the step size is
 * 0.5dB. Where 60 is a critical point for the volume setting.
 * At this value, the software does not increase or decrease the volume. When
 * the volume value is less than 60, the volume is reduced by 0.5dB for every
 * 1 drop. When the volume value is greater than 60, the upper is increased
 * by 1, and the volume is increased by 0.5dB.
 *
 * @subsection 2.3 audio_aec
 * Echo cancellation is a function of audio input interface, so audio input
 * device and channel must be enabled before echo cancellation is enabled.
 * Echo cancellation currently supports 8K and 16K audio sampling rates, and
 * the number of data samples in a frame is an integer multiple of 10ms audio
 * data (e.g., 8K sampling rate, the data sent is an integer multiple
 * of 8000 × 2/100 = 160byte).
 *
 * Echo cancellation For different devices, different packages, echo cancellation
 * will have different effects.Currently, adaptation is not supported, so there
 * are separate echo cancellation parameters for different devices.The parameters
 * file for echo cancellation is located in the /etc/webrtc_profile.ini
 * configuration file.
 *
 * The configuration file format is as follows (the three main parameters to
 * debug are listed below):
 * 		[Set_Far_Frame]
 * 		Frame_V=0.3
 * 		[Set_Near_Frame]
 * 		Frame_V=0.1
 * 		delay_ms=150
 *
 * The contents of the first tag [Set_Far_Frame] represent the remote parameters,
 * which are the playback data parameters on the SPK side.
 * Frame_V represents the audio amplitude ratio,which is adjusted to adjust the
 * amplitude of the playback data (this amplitude is only used for echo cancellation).
 * The first TAB, [Set_Near_Frame], represents the proximal parameters, which
 * are the MIC recording data parameters.
 * Frame_V represents the audio amplitude ratio, and adjusting this parameter
 * will adjust the amplitude of the recorded data (this amplitude is only used
 * for echo cancellation).
 * delay_ms Because of the delay of software and hardware, and there is a
 * certain distance between SPK and MIC,SPK playback data will be re-sampled by
 * MIC, so there will be a certain delay in SPK data reflected in MIC data.
 * This time represents the time difference between the playback data and the
 * recorded data.
 *
 * @subsection 2.4 audio_enc
 * Audio Encodings The audio API currently supports PT_G711A, PT_G711U, and
 * PT_G726 audio encodings. If you need to add a new encoder, you need to call
 * IMP_AENC_RegisterEncoder interface to register the encoder.
 *
 * @subsection 2.5 audio_dec
 * Audio decoding The audio API currently supports PT_G711A, PT_G711U and
 * PT_G726 format audio decoding. If you need to add a new decoding method, you
 * need to call the IMP_ADEC_RegisterDecoder interface to register the decoder
 * @{
 */

/**
 * Maximum number of audio frame buffers.
 */
#define MAX_AUDIO_FRAME_NUM 50

/**
 * Audio stream blocking type.
 */
typedef enum {
	NOBLOCK = 0,
	BLOCK = 1,
} IMP_BLOCK_E;

/**
 * Audio sampling rate definition.
 */
typedef enum {
	AUDIO_SAMPLE_RATE_8000	= 8000,	 /* 8KHz sampling frequency */
	AUDIO_SAMPLE_RATE_16000 = 16000, /* 16KHz sampling frequency */
	AUDIO_SAMPLE_RATE_24000 = 24000, /* 24KHz sampling frequency */
	AUDIO_SAMPLE_RATE_32000 = 32000, /* 32KHz sampling frequency */
	AUDIO_SAMPLE_RATE_44100 = 44100, /* 44.1KHz sampling frequency */
	AUDIO_SAMPLE_RATE_48000 = 48000, /* 48KHz sampling frequency */
	AUDIO_SAMPLE_RATE_96000 = 96000, /* 96KHz sampling frequency */
} IMP_AUDIO_SAMPLE_RATE_E;

/**
 * Definition of audio sampling accuracy.
 */
typedef enum {
	AUDIO_BIT_WIDTH_16 = 16, /* 16bit sampling accuracy */
	AUDIO_BIT_WIDTH_20 = 20, /* 20bit sampling accuracy */
	AUDIO_BIT_WIDTH_24 = 24, /* 24bit sampling accuracy */
} IMP_AUDIO_BIT_WIDTH_E;

/**
 * Audio channel mode definition.
 */
typedef enum {
	AUDIO_SOUND_MODE_MONO	= 1, /* Mono */
	AUDIO_SOUND_MODE_STEREO = 2, /* stereo */
} IMP_AUDIO_SOUND_MODE_E;

/**
 * Echo cancellation channel selection.
 */
typedef enum {
	AUDIO_AEC_CHANNEL_FIRST_LEFT   	= 0, /* Select the left channel or channel 1 for echo cancellation */
	AUDIO_AEC_CHANNEL_SECOND_RIGHT 	= 1, /* Select the right channel or channel 2 for echo cancellation */
	AUDIO_AEC_CHANNEL_THIRD			= 2, /* Select channel 3 for echo cancellation */
	AUDIO_AEC_CHANNEL_FOURTH 		= 3, /* Select channel 4 for echo cancellation */
} IMP_AUDIO_AEC_CHN_E;

/**
 * Defines an audio payload type enumeration.
 */
typedef enum {
	PT_PCM		= 0,
	PT_G711A	= 1,
	PT_G711U	= 2,
	PT_G726 	= 3,
	PT_AEC		= 4,
	PT_ADPCM	= 5,
	PT_MAX		= 6,
} IMP_AUDIO_PALY_LOAD_TYPE_E;

/**
 * Define the decoding mode.
 */
typedef enum {
	ADEC_MODE_PACK   = 0,	/* Pack */
	ADEC_MODE_STREAM = 1,	/* Stream */
} IMP_AUDIO_ADEC_MODE_S;

/**
 * Audio input and output device properties.
 */
typedef struct {
	IMP_AUDIO_SAMPLE_RATE_E eSamplerate; /* Audio sample rate */
	IMP_AUDIO_BIT_WIDTH_E   eBitwidth; /* Audio sample accuracy */
	IMP_AUDIO_SOUND_MODE_E  eSoundmode;	/* Audio channel mode */
	IMP_S32 				s32NumPerFrm; /* Number of sampling points per frame */
	IMP_S16 				s16ChnCnt; /* Support channel counts */
} IMP_AUDIO_IOATTR_S;

/**
 * Audio frame structure
 */
typedef struct {
	IMP_AUDIO_BIT_WIDTH_E  	eBitwidth; /* Audio sample accuracy */
	IMP_AUDIO_SOUND_MODE_E 	eSoundmode;	/* Audio sound mode */
	IMP_U32 				*pu32VirAddr; /* Audio frame data virtual address */
	IMP_U32  				u32PhyAddr;	/* Audio frame data physical address */
	IMP_S64  				s64TimeStamp; /* Audio frame timestamp */
	IMP_S32  				s32Seq;	/* Audio frame sequence number */
	IMP_S32  				s32Len;	/* Audio frame len */
} IMP_AUDIO_FRAME_S;

/**
 * Audio channel structure
 */
typedef struct {
	IMP_AUDIO_AEC_CHN_E 	eAecChn; /* Select the channel for echo cancellation */
	IMP_S32 				s32Rev;	/* reserved */
} IMP_AUDIO_CHN_PARAM_S;

/**
 * Audio bitstream structure
 */
typedef struct {
	IMP_U8 				*pu8Stream;			/* Data stream pointer */
	IMP_U32 			u32PhyAddr;			/* Data stream physical address */
	IMP_S32 			s32Len;				/* Data stream len */
	IMP_S64 			S64TimeStamp;		/* timestamp */
	IMP_S32 			s32Seq;				/* Data stream sequence number */
} IMP_AUDIO_STREAM_S;

/**
 * Defines an audio coding channel property structure.
 */
typedef struct {
	IMP_AUDIO_PALY_LOAD_TYPE_E 	eType; /* Audio payload data type */
	IMP_S32 					s32BufSize;	/* Buffer size，in frames，[2～MAX_AUDIO_FRAME_NUM] */
	IMP_U32 					*pu32Value;	/* Protocol property pointer */
} IMP_AUDIO_ENC_CHN_ATTR_S;

/**
 * Define the encoder property struct.
 */
typedef struct {
	IMP_AUDIO_PALY_LOAD_TYPE_E 	eType;	/* Encoding protocol type */
	IMP_S32  					s32MaxFrmLen; /* Maximum bitstream length */
	IMP_CHAR 					charName[16]; /* Encoding name */
	IMP_S32 					(*openEncoder)(IMP_VOID *pvoidEncoderAttr, IMP_VOID **pvoidEncoder);
	IMP_S32 					(*encoderFrm)(IMP_VOID **pvoidEncoder, IMP_AUDIO_FRAME_S *pstData,
						 					 IMP_U8 *pu8Outbuf, IMP_S32 *ps32OutLen);
	IMP_S32 					(*closeEncoder)(IMP_VOID **pvoidEncoder);
} IMP_AUDIO_ENCODER_S;

/**
 * Define the decoder channel property struct.
 */
typedef struct {
	IMP_AUDIO_PALY_LOAD_TYPE_E 	eType; /* Decoding protocol type */
	IMP_S32 					s32BufSize; /* Audio decoding cache size */
	IMP_AUDIO_ADEC_MODE_S 		stMode;	/* Decoding mode */
	IMP_VOID 					*pvoidValue; /* Protocol property pointer */
} IMP_AUDIO_DEC_CHN_ATTR_S;

/**
 * Define the decoder property struct.
 */
typedef struct {
	IMP_AUDIO_PALY_LOAD_TYPE_E 	eType; /* Decoding protocol type */
	IMP_CHAR 					charName[16]; /* Decoding name */
	IMP_S32 					(*openDecoder)(IMP_VOID *pvoidDecoderAttr, IMP_VOID **pvoidDecoder);
	IMP_S32 					(*decodeFrm)(IMP_VOID **pvoidDecoder, IMP_U8 *pu8Inbuf, IMP_S32 s32InLen,
											 IMP_U16 *pu16Outbuf, IMP_S32* ps32OutLen, IMP_S32 *ps32Chns);
	IMP_S32 					(*getFrmInfo)(IMP_VOID *pvoidDecoder, IMP_VOID *pvoidInfo);
	IMP_S32 					(*closeDecoder)(IMP_VOID **decoder);
} IMP_AUDIO_DECODER_S;

/**
 * Define the AGC gain structure.
 */
typedef struct {
	IMP_S32 s32TargetLevelDbfs;	/* Gain level, which takes the value [0, 31]; this is the target volume level in db and is negative. The lower the value, the higher the volume. */
	IMP_S32 s32CompressionGaindB; /* Set the maximum gain value,[0, 90], where 0 represents no gain and higher values indicate higher gain. */
} IMP_AUDIO_AGC_CONFIG_S;

/**
 * Define the noise suppression level.
 */
enum Level_ns {
	NS_LOW,			/* Low level noise suppression */
	NS_MODERATE,	/* Medium level noise suppression */
	NS_HIGH,		/* High level noise suppression */
	NS_VERYHIGH		/* Highest level noise suppression */
};

/**
 * @fn IMP_S32 IMP_AI_SetPubAttr(IMP_S32 s32DevId, IMP_AUDIO_IOATTR_S *pstAttr)
 *
 * Set audio input device properties.
 *
 * @param[in] s32DevId Audio device ID.
 * @param[in] pstAttr  Audio device property pointer.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks sample code
 * @code
 * IMP_S32 devID = 1;
 * IMP_AUDIO_IOATTR_S attr;
 * attr.samplerate = AUDIO_SAMPLE_RATE_8000;
 * attr.bitwidth   = AUDIO_BIT_WIDTH_16;
 * attr.soundmode  = AUDIO_SOUND_MODE_MONO;
 * attr.numPerFrm  = 320;
 * attr.chnCnt = 1;
 * ret = IMP_AI_SetPubAttr(devID, &attr);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "Set Audio in %d attr err: %d\n", devID, ret);
 *		return ret;
 * }
 * @endcode
 *
 * @attention Need to be called before IMP_AI_Enable.
 */
IMP_S32 IMP_AI_SetPubAttr(IMP_S32 s32DevId, IMP_AUDIO_IOATTR_S *pstAttr);

/**
 * @fn IMP_S32 IMP_AI_GetPubAttr(IMP_S32 s32DevId, IMP_AUDIO_IOATTR_S *pstAttr)
 *
 * Get audio input device properties.
 *
 * @param[in]  s32DevId Audio device ID.
 * @param[out] pstAttr  Audio device property pointer.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention None.
 */
IMP_S32 IMP_AI_GetPubAttr(IMP_S32 s32DevId, IMP_AUDIO_IOATTR_S *pstAttr);

/**
 * @fn IMP_S32 IMP_AI_Enable(IMP_S32 s32DevId)
 * Start the audio input device.
 *
 * @param[in] s32DevId Audio device ID.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention Must call IMP_AI_SetPubAttr() before calling this function.
 */
IMP_S32 IMP_AI_Enable(IMP_S32 s32DevId);

/**
 * @fn IMP_S32 IMP_AI_Disable(IMP_S32 s32DevId)
 *
 * Disable the audio input device.
 *
 * @param[in] s32DevId Audio device ID.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention Used in conjunction with IMP_AI_Enable(),IMP_AI_Disable must be executed before the system can sleep.
 */
IMP_S32 IMP_AI_Disable(IMP_S32 s32DevId);

/**
 * @fn IMP_S32 IMP_AI_EnableChn(IMP_S32 s32DevId, IMP_S32 s32Chn)
 *
 * Enable the audio input channel.
 *
 * @param[in] s32DevId Audio device ID.
 * @param[in] s32Chn   Audio input channel ID.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention Must enable device first.
 */
IMP_S32 IMP_AI_EnableChn(IMP_S32 s32DevId, IMP_S32 s32Chn);

/**
 * @fn IMP_S32 IMP_AI_DisableChn(IMP_S32 s32DevId, IMP_S32 s32Chn)
 *
 * Disable the audio input channel.
 *
 * @param[in] s32DevId Audio device ID.
 * @param[in] s32Chn   Audio input channel ID.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention Used in conjunction with IMP_AI_EnableChn.
 */
IMP_S32 IMP_AI_DisableChn(IMP_S32 s32DevId, IMP_S32 s32Chn);

/**
 * @fn IMP_S32 IMP_AI_GetFrame(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_AUDIO_FRAME_S *pstFrm)
 *
 * Get audio frame.
 *
 * @param[in]  s32DevId Audio device ID.
 * @param[in]  s32Chn   Audio input channel ID.
 * @param[out] pstFrm   Audio frame structure pointer.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks sampele code
 * @code
 * IMP_AUDIO_FRAME_S frm;
 * // get audio frame
 * ret = IMP_AI_GetFrame(devID, chnID, &frm);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "Audio Get Frame Data error\n");
 *		return ret;
 * }
 *
 * fwrite(frm.virAddr, 1, frm.len, record_file); // save audio frame data
 * @endcode
 *
 * @attention None.
 */
IMP_S32 IMP_AI_GetFrame(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_AUDIO_FRAME_S *pstFrm);

/**
 * @fn IMP_S32 IMP_AI_GetFrameTimeout(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_AUDIO_FRAME_S *pstFrm, IMP_S32 s32Timeout)
 *
 * Get audio frame data.
 *
 * @param[in]  s32DevId Audio device ID.
 * @param[in]  s32Chn   Audio input channel ID.
 * @param[out] pstFrm   Audio frame structure pointer.
 * @param[in] s32Timeout   Get the audio frame blocking wait time, -1 for blocking mode, 0 for non-blocking mode, >0 for blocking how many milliseconds, timeout will return an error.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks sample code
 * @code
 * IMP_AUDIO_FRAME_S frm;
 * // get audio frame
 * ret = IMP_AI_GetFrameTimeout(devID, chnID, &frm, -1);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "Audio Get Frame Data error\n");
 *		return ret;
 * }
 *
 * fwrite(frm.virAddr, 1, frm.len, record_file); // save audio frame data
 * @endcode
 *
 * @attention s32Timeout If the blocking time is set, it is generally recommended to set it to twice the audio frame time or more.
 */
IMP_S32 IMP_AI_GetFrameTimeout(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_AUDIO_FRAME_S *pstFrm, IMP_S32 s32Timeout);

/**
 * @fn IMP_S32 IMP_AI_SetChnParam(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_AUDIO_CHN_PARAM_S *pstParam)
 *
 * Set audio input channel param.
 *
 * @param[in] s32DevId  Audio device ID.
 * @param[in] s32Chn 	Audio input channel ID.
 * @param[in] pstParam  Audio input channel param pointer.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks sample code
 * @code
 * IMP_S32 chnID = 0;
 * IMP_AUDIO_CHN_PARAM_S chnParam;
 * chnParam.usrFrmDepth = 20;	// the range of valid value is [2, MAX_AUDIO_FRAME_NUM].
 * ret = IMP_AI_SetChnParam(devID, chnID, &chnParam);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "set ai %d channel %d attr err: %d\n", devID, chnID, ret);
 *		return ret;
 * }
 * @endcode
 *
 * @attention Must be called before IMP_AI_EnableChn.
 */
IMP_S32 IMP_AI_SetChnParam(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_AUDIO_CHN_PARAM_S *pstParam);

/**
 * @fn IMP_S32 IMP_AI_GetChnParam(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_AUDIO_CHN_PARAM_S *pstParam)
 *
 * Get audio input channel param.
 *
 * @param[in]  s32DevId Audio device ID.
 * @param[in]  s32Chn   Audio intput channel ID.
 * @param[out] pstParam Audio input channel param pointer.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention None.
 */
IMP_S32 IMP_AI_GetChnParam(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_AUDIO_CHN_PARAM_S *pstParam);

/**
 * @fn IMP_S32 IMP_AI_EnableAec(IMP_S32 s32DevId, IMP_S32 s32Chn)
 *
 * Enable echo cancellation for specified audio input and audio output.
 *
 * @param[in] s32DevId Audio input device ID for echo cancellation.
 * @param[in] s32Chn Audio input channel ID for echo cancellation.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks Echo cancellation is a function of audio input interface, so audio
 * @remarks input device and channel must be enabled before echo cancellation
 * @remarks is enabled.
 * @remarks Echo cancellation currently supports 8K and 16K audio sampling
 * @remarks rates, and the number of data samples in a frame is an integer
 * @remarks multiple of 10ms audio data (e.g., 8K sampling rate, the data sent
 * @remarks is an integer multiple of 8000 × 2/100 = 160byte).
 * @remarks
 * @remarks Echo cancellation For different devices, different packages, echo
 * @remarks cancellation will have different effects.Currently, adaptation is
 * @remarks not supported, so there are separate echo cancellation parameters
 * @remarks for different devices.The parameters file for echo cancellation is
 * @remarks located in the /etc/webrtc_profile.ini configuration file.
 * @remarks
 * @remarks The configuration file format is as follows (the three main
 * @remarks parameters to debug are listed below):
 * @remarks 		[Set_Far_Frame]
 * @remarks 		Frame_V=0.3
 * @remarks 		[Set_Near_Frame]
 * @remarks 		Frame_V=0.1
 * @remarks 		delay_ms=150
 * @remarks
 * @remarks The contents of the first tag [Set_Far_Frame] represent the remote
 * @remarks parameters, which are the playback data parameters on the SPK side.
 * @remarks Frame_V represents the audio amplitude ratio,which is adjusted to
 * @remarks adjust the amplitude of the playback data (this amplitude is only
 * @remarks used for echo cancellation).
 * @remarks
 * @remarks Frame_V represents the audio amplitude ratio, and adjusting this
 * @remarks parameter will adjust the amplitude of the recorded data (this
 * @remarks amplitude is only used for echo cancellation).
 * @remarks delay_ms Because of the delay of software and hardware, and there
 * @remarks is a certain distance between SPK and MIC,SPK playback data will
 * @remarks be re-sampled by MIC, so there will be a certain delay in SPK data
 * @remarks reflected in MIC data.
 * @remarks This time represents the time difference between the playback data
 * @remarks and the recorded data.
 *
 * @attention Actually the interface will only check aiDevId and s32Chn. But it
 * is better to call it after both channels are enabled.
 * When the audio input channel is closed, the echo cancellation function is
 * turned off at the same time. If you use it again, you need to open it again.
 */
IMP_S32 IMP_AI_EnableAec(IMP_S32 s32DevId, IMP_S32 s32Chn);

/**
 * @fn IMP_S32 IMP_AI_DisableAec(IMP_S32 s32DevId, IMP_S32 s32Chn)
 * Disable echo cancellation.
 *
 * @param[in] aiDevId Audio input device ID.
 * @param[in] s32Chn Audio input channel ID.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention None.
 */
IMP_S32 IMP_AI_DisableAec(IMP_S32 s32DevId, IMP_S32 s32Chn);

/**
 * @fn IMP_S32 IMP_AI_EnableNs(IMP_AUDIO_IOATTR_S *pstAttr, IMP_S32 s32Mode)
 *
 * Enable noise suppression for the specified audio input.
 *
 * @param[in] pstAttr Audio properties for which noise suppression is required.
 * @param[in] s32Mode Levels 0 to 3 for noise suppression,see Level ns.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks The mode parameter of noise suppression indicates the level of noise
 * @remarks supression,ranging from [0, 3],the higher the level,the cleaner the
 * @remarks noise suupression. However,the cleaner the noise suppression, the
 * @remarks more details of the sound are lost,so there is a contradiction here
 * @remarks that needs to be weighed when using.
 *
 * @attention Echo cancellation contains a noise suppression function, if echo
 * cancellation is enabled, no noise suppression is required.
 */
IMP_S32 IMP_AI_EnableNs(IMP_AUDIO_IOATTR_S *pstAttr, IMP_S32 s32Mode);

/**
 * @fn IMP_S32 IMP_AI_DisableNs(IMP_VOID)
 *
 * Disable noise suppression.
 *
 * @param None.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention None.
 */
IMP_S32 IMP_AI_DisableNs(IMP_VOID);

/**
 * @fn IMP_S32 IMP_AI_EnableAgc(IMP_AUDIO_IOATTR_S *pstAttr, IMP_AUDIO_AGC_CONFIG_S stAgcConfig)
 *
 * Enable automatic gain for audio input.
 *
 * @param[in] pstAttr Audio properties for which auto-gain is required.
 * @param[in] stAgcConfig Automatic gain parameter configuration, configuration
 * magnification.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks It is necessary to pay attention to the configuration of agcConfig,
 * @remarks the magnification of AGC is mainly configured by this parameter,
 * @remarks and the specific gain is described in IMP_AUDIO_AGC_CONFIG_S.
 * @remarks It should be noted that AGC can amplify the gain of the sound, but
 * @remarks if the parameters of the gain are not appropriate, it will lead to
 * @remarks broken sound and other conditions. Please adjust it by yourself in
 * @remarks the specific use.
 *
 * @attention Echo cancellation contains a noise suppression function, if echo
 * cancellation is enabled, no noise suppression is required.
 */
IMP_S32 IMP_AI_EnableAgc(IMP_AUDIO_IOATTR_S *pstAttr, IMP_AUDIO_AGC_CONFIG_S stAgcConfig);

/**
 * @fn IMP_S32 IMP_AI_DisableAgc(IMP_VOID)
 *
 * Disable automatic gain for audio input.
 *
 * @param None.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention None.
 */
IMP_S32 IMP_AI_DisableAgc(IMP_VOID);

/**
 * @fn IMP_S32 IMP_AO_EnableAgc(IMP_AUDIO_IOATTR_S *pstAttr, IMP_AUDIO_AGC_CONFIG_S stAgcConfig)
 *
 * Enable automatic gain for audio output.
 *
 * @param[in] pstAttr Audio properties for which auto-gain is required.
 * @param[in] stAgcConfig Automatic gain parameter configuration, configuration
 * magnification.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks It is necessary to pay attention to the configuration of agcConfig,
 * @remarks the magnification of AGC is mainly configured by this parameter,
 * @remarks and the specific gain is described in IMP_AUDIO_AGC_CONFIG_S.
 * @remarks It should be noted that AGC can amplify the gain of the sound, but
 * @remarks if the parameters of the gain are not appropriate, it will lead to
 * @remarks broken sound and other conditions. Please adjust it by yourself in
 * @remarks the specific use.
 *
 * @attention Echo cancellation contains a noise suppression function, if echo
 * cancellation is enabled, no noise suppression is required.
 */
IMP_S32 IMP_AO_EnableAgc(IMP_AUDIO_IOATTR_S *pstAttr, IMP_AUDIO_AGC_CONFIG_S stAgcConfig);

/**
 * @fn IMP_S32 IMP_AO_DisableAgc(IMP_VOID)
 *
 * Disable automatic gain for audio output.
 *
 * @param None.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention None.
 */
IMP_S32 IMP_AO_DisableAgc(IMP_VOID);

/**
 * @fn IMP_S32 IMP_AO_EnableNs(IMP_AUDIO_IOATTR_S *pstAttr, IMP_S32 s32Mode)
 *
 * Enable noise suppression for the specified audio output.
 *
 * @param[in] pstAttr Audio properties for which noise suppression is required.
 * @param[in] s32Mode Levels 0 to 3 for noise suppression,see Level_ns.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks The mode parameter of noise suppression indicates the level of noise
 * @remarks supression,ranging from [0, 3],the higher the level,the cleaner the
 * @remarks noise suupression. However,the cleaner the noise suppression, the
 * @remarks more details of the sound are lost,so there is a contradiction here
 * @remarks that needs to be weighed when using.
 *
 * @attention Echo cancellation contains a noise suppression function, if echo
 * cancellation is enabled, no noise suppression is required.
 */
IMP_S32 IMP_AO_EnableNs(IMP_AUDIO_IOATTR_S *pstAttr, IMP_S32 s32Mode);

/**
 * @fn IMP_S32 IMP_AO_DisableNs(IMP_VOID)
 *
 * Disable noise suppression for the specified audio output.
 *
 * @param None.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention None.
 */
IMP_S32 IMP_AO_DisableNs(IMP_VOID);

/**
 * @fn IMP_S32 IMP_HDMI_AO_EnableAgc(IMP_AUDIO_IOATTR_S *pstAttr, IMP_AUDIO_AGC_CONFIG_S stAgcConfig)
 *
 * Enable automatic gain for audio output.
 *
 * @param[in] pstAttr Audio properties for which auto-gain is required.
 * @param[in] stAgcConfig Automatic gain parameter configuration, configuration
 * magnification.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks It is necessary to pay attention to the configuration of agcConfig,
 * @remarks the magnification of AGC is mainly configured by this parameter,
 * @remarks and the specific gain is described in IMP_AUDIO_AGC_CONFIG_S.
 * @remarks It should be noted that AGC can amplify the gain of the sound, but
 * @remarks if the parameters of the gain are not appropriate, it will lead to
 * @remarks broken sound and other conditions. Please adjust it by yourself in
 * @remarks the specific use.
 *
 * @attention Echo cancellation contains a noise suppression function, if echo
 * cancellation is enabled, no noise suppression is required.
 */
IMP_S32 IMP_HDMI_AO_EnableAgc(IMP_AUDIO_IOATTR_S *pstAttr, IMP_AUDIO_AGC_CONFIG_S stAgcConfig);

/**
 * @fn IMP_S32 IMP_HDMI_AO_DisableAgc(IMP_VOID)
 *
 * Disable automatic gain for audio HDMI output.
 *
 * @param None.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention None.
 */
IMP_S32 IMP_HDMI_AO_DisableAgc(IMP_VOID);

/**
 * @fn IMP_S32 IMP_HDMI_AO_EnableNs(IMP_AUDIO_IOATTR_S *pstAttr, IMP_S32 s32Mode)
 *
 * Enable noise suppression for the specified audio HDMI output.
 *
 * @param[in] pstAttr Audio properties for which noise suppression is required.
 * @param[in] s32Mode Levels 0 to 3 for noise suppression,see Level_ns.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks The mode parameter of noise suppression indicates the level of noise
 * @remarks supression,ranging from [0, 3],the higher the level,the cleaner the
 * @remarks noise suupression. However,the cleaner the noise suppression, the
 * @remarks more details of the sound are lost,so there is a contradiction here
 * @remarks that needs to be weighed when using.
 *
 * @attention Echo cancellation contains a noise suppression function, if echo
 * cancellation is enabled, no noise suppression is required.
 */
IMP_S32 IMP_HDMI_AO_EnableNs(IMP_AUDIO_IOATTR_S *pstAttr, IMP_S32 s32Mode);

/**
 * @fn IMP_S32 IMP_HDMI_AO_DisableNs(IMP_VOID)
 *
 * Disable noise suppression for the specified audio HDMI output.
 *
 * @param None.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention None.
 */
IMP_S32 IMP_HDMI_AO_DisableNs(IMP_VOID);

/**
 * @fn IMP_S32 IMP_AI_EnableHpf(IMP_AUDIO_IOATTR_S *pstAttr)
 *
 * Enable high-pass filtering of audio input.
 *
 * @param[in] pstAttr Audio attributes that require high-pass filtering.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention Echo cancellation incorporates HPF functionality and does not
 * need to be done if echo cancellation is enabled.
 */
IMP_S32 IMP_AI_EnableHpf(IMP_AUDIO_IOATTR_S *pstAttr);

/**
 * @fn IMP_S32 IMP_AI_SetHpfCoFrequency(IMP_S32 s32Cofrequency)
 *
 * Set the cutoff frequency of the high-pass filter for the audio input.
 *
 * @param[in] s32Cofrequency Cutoff frequency of the high-pass filter
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention Set the cutoff frequency before turning on the high-pass filter
 */
IMP_S32 IMP_AI_SetHpfCoFrequency(IMP_S32 s32Cofrequency);

/**
 * @fn IMP_S32 IMP_AI_DisableHpf(IMP_VOID)
 *
 * Disable high-pass filtering of audio input.
 *
 * @param None.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention None.
 */
IMP_S32 IMP_AI_DisableHpf(IMP_VOID);

/**
 * @fn IMP_S32 IMP_AO_EnableHpf(IMP_AUDIO_IOATTR_S *pstAttr)
 *
 * Enable high-pass filtering of audio output.
 *
 * @param[in] attr Audio attributes that require high-pass filtering.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention Echo cancellation incorporates HPF functionality and does not
 * need to be done if echo cancellation is enabled.
 */
IMP_S32 IMP_AO_EnableHpf(IMP_AUDIO_IOATTR_S *pstAttr);

/**
 * @fn IMP_S32 IMP_AO_SetHpfCoFrequency(IMP_S32 s32Cofrequency)
 *
 * Set the cutoff frequency of the high-pass filter for the audio output.
 *
 * @param[in] s32Cofrequency Cutoff frequency of the high-pass filter
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention Set the cutoff frequency before turning on the high-pass filter
 */
IMP_S32 IMP_AO_SetHpfCoFrequency(IMP_S32 s32Cofrequency);

/**
 * @fn IMP_S32 IMP_AO_DisableHpf(IMP_VOID)
 *
 * Disable high-pass filtering of audio output.
 *
 * @param None.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention None.
 */
IMP_S32 IMP_AO_DisableHpf(IMP_VOID);

/**
 * @fn IMP_S32 IMP_HDMI_AO_EnableHpf(IMP_AUDIO_IOATTR_S *pstAttr)
 *
 * Enable high-pass filtering of audio HDMI output.
 *
 * @param[in] pstAttr Audio attributes that require high-pass filtering.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention Echo cancellation incorporates HPF functionality and does not
 * need to be done if echo cancellation is enabled.
 */
IMP_S32 IMP_HDMI_AO_EnableHpf(IMP_AUDIO_IOATTR_S *pstAttr);

/**
 * @fn IMP_S32 IMP_HDMI_AO_SetHpfCoFrequency(IMP_S32 s32Cofrequency)
 *
 * Set the cutoff frequency of the high-pass filter for the audio HDMI output.
 *
 * @param[in] s32Cofrequency Cutoff frequency of the high-pass filter
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention Set the cutoff frequency before turning on the high-pass filter
 */
IMP_S32 IMP_HDMI_AO_SetHpfCoFrequency(IMP_S32 s32Cofrequency);

/**
 * @fn IMP_S32 IMP_HDMI_AO_DisableHpf(IMP_VOID)
 *
 * Disable high-pass filtering of audio output.
 *
 * @param None.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention None.
 */
IMP_S32 IMP_HDMI_AO_DisableHpf(IMP_VOID);

/**
 * @fn IMP_S32 IMP_AO_SetPubAttr(IMP_S32 s32DevId, IMP_AUDIO_IOATTR_S *pstAttr)
 *
 * Set audio output device properties.
 *
 * @param[in] s32DevId Audio device ID.
 * @param[in] pstAttr  Audio output device property pointer.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention None.
 */
IMP_S32 IMP_AO_SetPubAttr(IMP_S32 s32DevId, IMP_AUDIO_IOATTR_S *pstAttr);

/**
 * @fn IMP_S32 IMP_HDMI_AO_SetPubAttr(IMP_S32 s32DevId, IMP_AUDIO_IOATTR_S *pstAttr)
 *
 * Set audio output HDMI device properties.
 *
 * @param[in] s32DevId Audio device ID.
 * @param[in] pstAttr  Audio output device property pointer.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention None.
 */
IMP_S32 IMP_HDMI_AO_SetPubAttr(IMP_S32 s32DevId, IMP_AUDIO_IOATTR_S *pstAttr);

/**
 * @fn IMP_S32 IMP_AO_GetPubAttr(IMP_S32 s32DevId, IMP_AUDIO_IOATTR_S *pstAttr);
 *
 * Get audio output HDMI device properties.
 *
 * @param[in] s32DevId Audio device ID.
 * @param[in] pstAttr  Audio output device property pointer.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention None.
 */
IMP_S32 IMP_AO_GetPubAttr(IMP_S32 s32DevId, IMP_AUDIO_IOATTR_S *pstAttr);

/**
 * @fn IMP_S32 IMP_HDMI_AO_GetPubAttr(IMP_S32 s32DevId, IMP_AUDIO_IOATTR_S *pstAttr);
 *
 * Get audio HDMI output HDMI device properties.
 *
 * @param[in] s32DevId Audio device ID.
 * @param[in] pstAttr  Audio output device property pointer.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention None.
 */
IMP_S32 IMP_HDMI_AO_GetPubAttr(IMP_S32 s32DevId, IMP_AUDIO_IOATTR_S *pstAttr);

/**
 * @fn IMP_S32 IMP_AO_Enable(IMP_S32 s32DevId)
 *
 * Enable audio output device.
 *
 * @param[in] s32DevId Audio device ID.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention IMP_AO_SetPubAttr must be invoked before enabling.
 */
IMP_S32 IMP_AO_Enable(IMP_S32 s32DevId);

/**
 * @fn IMP_S32 IMP_HDMI_AO_Enable(IMP_S32 s32DevId)
 *
 * Enable audio HDMI output device.
 *
 * @param[in] s32DevId Audio device ID.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention IMP_HDMI_AO_SetPubAttr must be invoked before enabling.
 */
IMP_S32 IMP_HDMI_AO_Enable(IMP_S32 s32DevId);

/**
 * @fn IMP_S32 IMP_AO_Disable(IMP_S32 s32DevId)
 *
 * Disable audio output device.
 *
 * @param[in] s32DevId Audio output device.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention None.
 */
IMP_S32 IMP_AO_Disable(IMP_S32 s32DevId);

/**
 * @fn IMP_S32 IMP_HDMI_AO_Disable(IMP_S32 s32DevId)
 *
 * Disable audio HDMI output device.
 *
 * @param[in] s32DevId Audio output device.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention None.
 */
IMP_S32 IMP_HDMI_AO_Disable(IMP_S32 s32DevId);

/**
 * @fn IMP_S32 IMP_AO_EnableChn(IMP_S32 s32DevId, IMP_S32 s32Chn)
 *
 * Enable audio output channel
 *
 * @param[in] s32DevId Audio device ID.
 * @param[in] s32Chn   Audio channel ID.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention None.
 */
IMP_S32 IMP_AO_EnableChn(IMP_S32 s32DevId, IMP_S32 s32Chn);

/**
 * @fn IMP_S32 IMP_HDMI_AO_EnableChn(IMP_S32 s32DevId, IMP_S32 s32Chn)
 *
 * Enable audio HDMI output channel
 *
 * @param[in] s32DevId Audio device ID.
 * @param[in] s32Chn   Audio channel ID.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention None.
 */
IMP_S32 IMP_HDMI_AO_EnableChn(IMP_S32 s32DevId, IMP_S32 s32Chn);

/**
 * @fn IMP_S32 IMP_AO_DisableChn(IMP_S32 s32DevId, IMP_S32 s32Chn)
 *
 * Disable audio output channel
 *
 * @param[in] s32DevId Audio device ID.
 * @param[in] s32Chn   Audio channel ID.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention None.
 */
IMP_S32 IMP_AO_DisableChn(IMP_S32 s32DevId, IMP_S32 s32Chn);

/**
 * @fn IMP_S32 IMP_HDMI_AO_DisableChn(IMP_S32 s32DevId, IMP_S32 s32Chn)
 *
 * Disable HDMI audio output channel
 *
 * @param[in] s32DevId Audio device ID.
 * @param[in] s32Chn   Audio channel ID.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention None.
 */
IMP_S32 IMP_HDMI_AO_DisableChn(IMP_S32 s32DevId, IMP_S32 s32Chn);

/**
 * @fn IMP_S32 IMP_AO_SendFrame(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_AUDIO_FRAME_S *pstFrm, IMP_BLOCK_E enBlock)
 *
 * Send audio output frames.
 *
 * @param[in] s32DevId Audio device ID.
 * @param[in] s32Chn   Audio channel ID.
 * @param[in] pstFrm   Audio frame structure pointer.
 * @param[in] enBlock  Block/NoBlock
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks sample code
 * @code
 * while(1) {
 *		size = fread(buf, 1, IMP_AUDIO_BUF_SIZE, play_file);
 *		if(size < IMP_AUDIO_BUF_SIZE)
 *			break;
 *
 *		IMP_AUDIO_FRAME_S frm;
 *		frm.virAddr = (IMP_U32 *)buf;
 *		frm.len = size;
 *		ret = IMP_AO_SendFrame(devID, chnID, &frm, BLOCK);
 *		if(ret != 0) {
 *			IMP_LOG_ERR(TAG, "send Frame Data error\n");
 *			return ret;
 *		}
 * }
 * @endcode
 *
 * @attention None.
 */
IMP_S32 IMP_AO_SendFrame(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_AUDIO_FRAME_S *pstFrm, IMP_BLOCK_E enBlock);

/**
 * @fn IMP_S32 IMP_AO_SendFrame_EXT(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_AUDIO_FRAME_S *pstFrm, IMP_BLOCK_E enBlock)
 *
 * Non-standard byte streaming audio frames are sent to the audio output channel.
 *
 * @param[in] s32DevId Audio device ID.
 * @param[in] s32Chn   Audio channel ID.
 * @param[in] pstFrm   Audio frame structure pointer.
 * @param[in] enBlock  Block/NoBlock
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *Send audio output frames
 * @remarks sample code
 * @code
 * while(1) {
 *		size = fread(buf, 1, IMP_AUDIO_BUF_SIZE, play_file);
 *		if(size < IMP_AUDIO_BUF_SIZE)
 *			break;
 *
 *		IMP_AUDIO_FRAME_S frm;
 *		frm.virAddr = (IMP_U32 *)buf;
 *		frm.len = size;
 *		ret = IMP_AO_SendFrame_EXT(devID, chnID, &frm, BLOCK);
 *		if(ret != 0) {
 *			IMP_LOG_ERR(TAG, "send Frame Data error\n");
 *			return ret;
 *		}
 * }
 * s32Ret = IMP_AO_ClearChnBuf(s32DevID, s32ChnID);
 * if (s32Ret != IMP_SUCCESS) {
 * 		IMP_LOG_ERR(TAG, "IMP_AO_ClearChnBuf error: %x\n",s32Ret);
 *		return NULL;
 * }
 * @endcode
 *
 * @attention The interface is compatible with playing a frame of audio stream
 * which is not 40ms. Compared with IMP_AO_SendFrame, the advantage is that it
 * increases the flexibility of playing data. The disadvantage is the
 * additional memory consumption of a standard frame buffer size. Be careful to
 * call IMP_AO_ClearChnBuf after the audio is finished playing to avoid losing
 * data.
 *
 */
IMP_S32 IMP_AO_SendFrame_EXT(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_AUDIO_FRAME_S *pstFrm, IMP_BLOCK_E enBlock);

/**
 * @fn IMP_S32 IMP_S32 IMP_HDMI_AO_SendFrame(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_AUDIO_FRAME_S *pstFrm, IMP_BLOCK_E enBlock)
 *
 * Send HDMI audio output frames.
 *
 * @param[in] s32DevId Audio device ID.
 * @param[in] s32Chn   Audio channel ID.
 * @param[in] pstFrm   Audio frame structure pointer.
 * @param[in] enBlock  Block/NoBlock
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks sample code
 * @code
 * while(1) {
 *		size = fread(buf, 1, IMP_AUDIO_BUF_SIZE, play_file);
 *		if(size < IMP_AUDIO_BUF_SIZE)
 *			break;
 *
 *		IMP_AUDIO_FRAME_S frm;
 *		frm.virAddr = (IMP_U32 *)buf;
 *		frm.len = size;
 *		ret = IMP_HDMI_AO_SendFrame(devID, chnID, &frm, BLOCK);
 *		if(ret != 0) {
 *			IMP_LOG_ERR(TAG, "send Frame Data error\n");
 *			return ret;
 *		}
 * }
 * @endcode
 *
 * @attention None.
 */
IMP_S32 IMP_HDMI_AO_SendFrame(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_AUDIO_FRAME_S *pstFrm, IMP_BLOCK_E enBlock);

/**
 * @fn IMP_S32 IMP_HDMI_AO_SendFrame_EXT(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_AUDIO_FRAME_S *pstFrm, IMP_BLOCK_E enBlock)
 *
 * Non-standard byte streaming audio frames are sent to the audio HDMI output channel.
 *
 * @param[in] s32DevId Audio device ID.
 * @param[in] s32Chn   Audio channel ID.
 * @param[in] pstFrm   Audio frame structure pointer.
 * @param[in] enBlock  Block/NoBlock
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks sample code
 * @code
 * while(1) {
 *		size = fread(buf, 1, IMP_AUDIO_BUF_SIZE, play_file);
 *		if(size < IMP_AUDIO_BUF_SIZE)
 *			break;
 *
 *		IMP_AUDIO_FRAME_S frm;
 *		frm.virAddr = (IMP_U32 *)buf;
 *		frm.len = size;
 *		ret = IMP_HDMI_AO_SendFrame_EXT(devID, chnID, &frm, BLOCK);
 *		if(ret != 0) {
 *			IMP_LOG_ERR(TAG, "send Frame Data error\n");
 *			return ret;
 *		}
 * }
 * s32Ret = IMP_HDMI_AO_ClearChnBuf(s32DevID, s32ChnID);
 * if (s32Ret != IMP_SUCCESS) {
 * 		IMP_LOG_ERR(TAG, "IMP_HDMI_AO_ClearChnBuf error: %x\n",s32Ret);
 *		return NULL;
 * }
 * @endcode
 *
 * @attention The interface is compatible with playing a frame of audio stream
 * which is not 40ms. Compared with IMP_HDMI_AO_SendFrame, the advantage is
 * that it increases the flexibility of playing data. The disadvantage is the
 * additional memory consumption of a standard frame buffer size. Be careful to
 * call IMP_HDMI_AO_ClearChnBuf after the audio is finished playing to avoid
 * losing data.
 */
IMP_S32 IMP_HDMI_AO_SendFrame_EXT(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_AUDIO_FRAME_S *pstFrm, IMP_BLOCK_E enBlock);

/**
 * @fn IMP_S32 IMP_AO_ClearChnBuf(IMP_S32 s32DevId, IMP_S32 s32Chn)
 *
 * Clear the current audio data cache in the audio output channel
 *
 * @param[in] s32DevId Audio device ID.
 * @param[in] s32Chn   Audio channel ID.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention None.
 */
IMP_S32 IMP_AO_ClearChnBuf(IMP_S32 s32DevId, IMP_S32 s32Chn);

/**
 * @fn IMP_S32 IMP_HDMI_AO_ClearChnBuf(IMP_S32 s32DevId, IMP_S32 s32Chn)
 *
 * Clear the current audio data cache in the HDMI audio output channel
 *
 * @param[in] s32DevId Audio device ID.
 * @param[in] s32Chn   Audio channel ID.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention None.
 */
IMP_S32 IMP_HDMI_AO_ClearChnBuf(IMP_S32 s32DevId, IMP_S32 s32Chn);

/**
 * @fn IMP_S32 IMP_AO_FlushChnBuf(IMP_S32 s32DevId, IMP_S32 s32Chn);
 *
 * Wait for the last piece of audio data to play out
 *
 * @param[in] s32DevId Audio device ID.
 * @param[in] s32Chn Audio channel ID.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 * @attention None.
 */
IMP_S32 IMP_AO_FlushChnBuf(IMP_S32 s32DevId, IMP_S32 s32Chn);

/**
 * @fn IMP_S32 IMP_HDMI_AO_FlushChnBuf(IMP_S32 s32DevId, IMP_S32 s32Chn);
 *
 * Wait for the last piece of audio data to play out
 *
 * @param[in] s32DevId Audio device ID.
 * @param[in] s32Chn Audio channel ID.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 * @attention None.
 */
IMP_S32 IMP_HDMI_AO_FlushChnBuf(IMP_S32 s32DevId, IMP_S32 s32Chn);

/**
 * @fn IMP_S32 IMP_AENC_CreateChn(IMP_S32 s32AeChn, IMP_AUDIO_ENC_CHN_ATTR_S *pstAttr)
 *
 * Create an audio encoding channel
 *
 * @param[in] s32AeChn Audio encodec channel ID.
 * @param[in] pstAttr  Audio coding channel property pointer.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks sample code
 * @code
 * IMP_S32 AeChn = 0;
 * IMP_AUDIO_ENC_CHN_ATTR_S attr;
 * attr.type = PT_G711A;
 * attr.bufSize = 20;
 * ret = IMP_AENC_CreateChn(AeChn, &attr);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "Audio encode create channel failed\n");
 *		return ret;
 * }
 * @endcode
 *
 * @attention Audio Encodings The audio API currently supports PT_G711A,
 * PT_G711U, and PT_G726 audio encodings. If you need to add a new encoder,
 * you need to call IMP_AENC_RegisterEncoder interface to register the encoder.
 */
IMP_S32 IMP_AENC_CreateChn(IMP_S32 s32AeChn, IMP_AUDIO_ENC_CHN_ATTR_S *pstAttr);

/**
 * @fn IMP_S32 IMP_AENC_DestroyChn(IMP_S32 s32AeChn)
 *
 * Destroy the audio encoding channel.
 *
 * @param[in] s32AeChn Audio encodec channel ID.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks failed.
 *
 * @attention Used in conjunction with IMP_AENC_CreateChn.
 */
IMP_S32 IMP_AENC_DestroyChn(IMP_S32 s32AeChn);

/**
 * @fn IMP_S32 IMP_AENC_SendFrame(IMP_S32 s32AeChn, IMP_AUDIO_FRAME_S *pstFrm)
 *
 * Send audio encoded audio frames.
 *
 * @param[in] s32AeChn Audio encodec channel ID.
 * @param[in] pstFrm   Audio frame structure pointer.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks sample codec
 * @code
 * while(1) {
 *		// read a frame of data
 *		ret = fread(buf_pcm, 1, IMP_AUDIO_BUF_SIZE, file_pcm);
 *		if(ret < IMP_AUDIO_BUF_SIZE)
 *			break;
 *
 *		// encoding
 *		IMP_AUDIO_FRAME_S frm;
 *		frm.virAddr = (uIMP_S3232_t *)buf_pcm;
 *		frm.len = ret;
 *		ret = IMP_AENC_SendFrame(AeChn, &frm);
 *		if(ret != 0) {
 *			IMP_LOG_ERR(TAG, "imp audio encode send frame failed\n");
 *			return ret;
 *		}
 *
 *		// Get the encoded bitstream
 *		IMP_AUDIO_STREAM_S stream;
 *		ret = IMP_AENC_GetStream(AeChn, &stream, BLOCK);
 *		if(ret != 0) {
 *			IMP_LOG_ERR(TAG, "imp audio encode get stream failed\n");
 *			return ret;
 *		}
 *
 *		// Save the encoded bitstream
 *		fwrite(stream.stream, 1, stream.len, file_g711);
 *
 *		// Free the encoded bitstream
 *		ret = IMP_AENC_ReleaseStream(AeChn, &stream);
 *		if(ret != 0) {
 *			IMP_LOG_ERR(TAG, "imp audio encode release stream failed\n");
 *			return ret;
 *		}
 * }
 * @endcode
 *
 * @attention None.
 */
IMP_S32 IMP_AENC_SendFrame(IMP_S32 s32AeChn, IMP_AUDIO_FRAME_S *pstFrm);

/**
 * @fn IMP_S32 IMP_AENC_PollingStream(IMP_S32 s32AeChn, IMP_U32 u32TimeMs)
 *
 * Polling encoded audio stream caching.
 *
 * @param[in] s32AeChn  Audio encoding input channel number.
 * @param[in] u32TimeMs Polling timeout.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention We use this interface before we use IMP_AENC_GetStream, which
 * indicates that the encoded audio data is ready and can be retrieved using
 * IMP_AENC_GetStream.
 */
IMP_S32 IMP_AENC_PollingStream(IMP_S32 s32AeChn, IMP_U32 u32TimeMs);

/**
 * @fn IMP_S32 IMP_AENC_GetStream(IMP_S32 s32AeChn, IMP_AUDIO_STREAM_S *pstStream, IMP_BLOCK_E eBlock)
 *
 * Get the encoded stream.
 *
 * @param[in] s32AeChn  Audio encoded channel.
 * @param[in] pstStream Gets the audio bitstream pointer.
 * @param[in] eBlock    Block/NoBlock.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks See IMP_AENC_SendFrame function description for example code.
 *
 * @attention None.
 */
IMP_S32 IMP_AENC_GetStream(IMP_S32 s32AeChn, IMP_AUDIO_STREAM_S *pstStream, IMP_BLOCK_E eBlock);

/**
 * @fn IMP_S32 IMP_AENC_ReleaseStream(IMP_S32 s32AeChn, IMP_AUDIO_STREAM_S *pstStream)
 *
 * Release the bitstream obtained from the audio encoding channel.
 *
 * @param[in] s32AeChn  Audio encoded channel.
 * @param[in] pstStream Audio bitsteam pointer.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks See IMP_AENC_SendFrame function description for example code.
 *
 * @attention None.
 */
IMP_S32 IMP_AENC_ReleaseStream(IMP_S32 s32AeChn, IMP_AUDIO_STREAM_S *pstStream);

/**
 * @fn IMP_S32 IMP_AENC_RegisterEncoder(IMP_S32 *ps32Handle, IMP_AUDIO_ENCODER_S *pstEncoder)
 *
 * Registering the encoder.
 *
 * @param[in] ps32Handle Register the handle pointer.
 * @param[in] pstEncoder Encoder property struct pointer.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks sample code
 * @code
 * IMP_S32 handle_g711a = 0;
 * IMP_AUDIO_ENCODER_S my_encoder;
 * my_encoder.maxFrmLen = 1024;
 * sprIMP_S32f(my_encoder.name, "%s", "MY_G711A");
 * my_encoder.openEncoder = NULL;
 * my_encoder.encoderFrm = MY_G711A_Encode_Frm;
 * my_encoder.closeEncoder = NULL;
 *
 * ret = IMP_AENC_RegisterEncoder(&handle_g711a, &my_encoder);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "IMP_AENC_RegisterEncoder failed\n");
 *		return ret;
 * }
 *
 * IMP_S32 AeChn = 0;
 * IMP_AUDIO_ENC_CHN_ATTR_S attr;
 * attr.type = handle_g711a; //Encoder type is equal to the value of handle_g711a
 * 							   returned by successful registration.
 * attr.bufSize = 20;
 * ret = IMP_AENC_CreateChn(AeChn, &attr);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "imp audio encode create channel failed\n");
 *		return ret;
 * }
 * @endcode
 *
 * @attention Once registered, use it the same way as using the SDK's built-in encoder.
 */
IMP_S32 IMP_AENC_RegisterEncoder(IMP_S32 *ps32Handle, IMP_AUDIO_ENCODER_S *pstEncoder);

/**
 * @fn IMP_S32 IMP_AENC_UnRegisterEncoder(IMP_S32 *ps32Handle)
 *
 * Log out the encoder.
 *
 * @param[in] ps32handle Register handle pointer (the handle obtained when
 * registering the encoder).
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention None.
 */
IMP_S32 IMP_AENC_UnRegisterEncoder(IMP_S32 *ps32Handle);

/**
 * @fn IMP_S32 IMP_ADEC_CreateChn(IMP_S32 s32AdChn, IMP_AUDIO_DEC_CHN_ATTR_S *pstAttr)
 *
 * Create an audio decoding channel.
 *
 * @param[in] s32AdChn Audio decoded channel.
 * @param[in] pstAttr  Channel property pointer.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks sample codec
 * @code
 * IMP_S32 adChn = 0;
 * IMP_AUDIO_DEC_CHN_ATTR_S attr;
 * attr.type = PT_G711A;
 * attr.bufSize = 20;
 * attr.mode = ADEC_MODE_PACK;
 * ret = IMP_ADEC_CreateChn(adChn, &attr);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "imp audio decoder create channel failed\n");
 *		return ret;
 * }
 * @endcode
 *
 * @attention None.
 */
IMP_S32 IMP_ADEC_CreateChn(IMP_S32 s32AdChn, IMP_AUDIO_DEC_CHN_ATTR_S *pstAttr);

/**
 * @fn IMP_S32 IMP_ADEC_DestroyChn(IMP_S32 s32AdChn)
 *
 * Destroy the audio decoder channel.
 *
 * @param[in] s32AdChn Audio decoded channel.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention None.
 */
IMP_S32 IMP_ADEC_DestroyChn(IMP_S32 s32AdChn);

/**
 * @fn IMP_S32 IMP_ADEC_SendStream(IMP_S32 s32AdChn, IMP_AUDIO_STREAM_S *pstStream, IMP_BLOCK_E eBlock)
 *
 * Send audio code stream to audio decoding channel.
 *
 * @param[in] s32AdChn  Audio decoded channel.
 * @param[in] pstStream Audio bitsteam pointer.
 * @param[in] eBlock    Block/NoBlock.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks sample code
 * @code
 * while(1) {
 *		// Retrieve the data to be decoded
 *		ret = fread(buf_g711, 1, IMP_AUDIO_BUF_SIZE/2, file_g711);
 *		if(ret < IMP_AUDIO_BUF_SIZE/2)
 *			break;
 *
 *		// Send decoded data
 *		IMP_AUDIO_STREAM_S stream_in;
 *		stream_in.stream = (uIMP_S328_t *)buf_g711;
 *		stream_in.len = ret;
 *		ret = IMP_ADEC_SendStream(adChn, &stream_in, BLOCK);
 *		if(ret != 0) {
 *			IMP_LOG_ERR(TAG, "imp audio encode send frame failed\n");
 *			return ret;
 *		}
 *
 *		// Get the decoded data
 *		IMP_AUDIO_STREAM_S stream_out;
 *		ret = IMP_ADEC_GetStream(adChn, &stream_out, BLOCK);
 *		if(ret != 0) {
 *			IMP_LOG_ERR(TAG, "imp audio decoder get stream failed\n");
 *			return ret;
 *		}
 *
 *		// save the decoded data
 *		fwrite(stream_out.stream, 1, stream_out.len, file_pcm);
 *
 *		// free the decoded data
 *		ret = IMP_ADEC_ReleaseStream(adChn, &stream_out);
 *		if(ret != 0) {
 *			IMP_LOG_ERR(TAG, "imp audio decoder release stream failed\n");
 *			return ret;
 *		}
 * }
 * @endcode
 *
 * @attention None.
 */
IMP_S32 IMP_ADEC_SendStream(IMP_S32 s32AdChn, IMP_AUDIO_STREAM_S *pstStream, IMP_BLOCK_E eBlock);

/**
 * @fn IMP_S32 IMP_ADEC_PollingStream(IMP_S32 s32AdChn, IMP_U32 u32TimeMs)
 *
 * Polling encoded audio stream caching.
 *
 * @param[in] s32AdChn  Audio decoding channel number.
 * @param[in] u32TimeMs Polling timeout.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention This interface is used before IMP_ADEC_GetStream is used, which
 * indicates that the decoded audio data is ready and can be retrieved using
 * IMP_ADEC_GetStream.
 */
IMP_S32 IMP_ADEC_PollingStream(IMP_S32 s32AdChn, IMP_U32 u32TimeMs);

/**
 * @fn IMP_S32 IMP_ADEC_GetStream(IMP_S32 s32AdChn, IMP_AUDIO_STREAM_S *pstStream, IMP_BLOCK_E eBlock)
 *
 * Get the decoded stream.
 *
 * @param[in] s32AdChn  Audio decoding channel number.
 * @param[in] pstStream Gets the decoded codestream pointer.
 * @param[in] eBlock    Block/NoBlock.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks See the IMP_ADEC_SendStream function description for example code.
 *
 * @attention None.
 */
IMP_S32 IMP_ADEC_GetStream(IMP_S32 s32AdChn, IMP_AUDIO_STREAM_S *pstStream, IMP_BLOCK_E eBlock);

/**
 * @fn IMP_S32 IMP_ADEC_ReleaseStream(IMP_S32 s32AdChn, IMP_AUDIO_STREAM_S *pstStream)
 *
 * Release the bitstream obtained from the audio decoding channel.
 *
 * @param[in] s32AdChn  Audio decoding channel number.
 * @param[in] pstStream Decoded codestream pointer.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks See the IMP_ADEC_SendStream function description for example code.
 *
 * @attention None.
 */
IMP_S32 IMP_ADEC_ReleaseStream(IMP_S32 s32AdChn, IMP_AUDIO_STREAM_S *pstStream);

/**
 * @fn IMP_S32 IMP_ADEC_ClearChnBuf(IMP_S32 s32AdChn)
 *
 * Clear the current audio data cache in the audio decoding channel.
 *
 * @param[in] s32AdChn Audio decoding channel number.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention None.
 */
IMP_S32 IMP_ADEC_ClearChnBuf(IMP_S32 s32AdChn);

/**
 * @fn IMP_S32 IMP_ADEC_RegisterDecoder(IMP_S32 *ps32Handle, IMP_AUDIO_DECODER_S *pstDecoder)
 *
 * register the decoder.
 *
 * @param[in] ps32handle Register the handle pointer.
 * @param[in] pstDecoder Decoder property struct pointer..
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks sample code
 * @code
 * IMP_S32 handle_g711a = 0;
 * IMP_AUDIO_DECODER_S my_decoder;
 * sprIMP_S32f(my_decoder.name, "%s", "MY_G711A");
 * my_decoder.openDecoder = NULL;
 * my_decoder.decodeFrm = MY_G711A_Decode_Frm;
 * my_decoder.getFrmInfo = NULL;
 * my_decoder.closeDecoder = NULL;
 *
 * ret = IMP_ADEC_RegisterDecoder(&handle_g711a, &my_decoder);
 * if (ret != 0) {
 *		IMP_LOG_ERR(TAG, "IMP_ADEC_RegisterDecoder failed\n");
 *		return ret;
 * }
 *
 * IMP_S32 adChn = 0;
 * IMP_AUDIO_DEC_CHN_ATTR_S attr;
 * attr.type = handle_g711a; //The decoded type is equal to the handle_g711a
 * 							   returned by the decoder registration
 * attr.bufSize = 20;
 * attr.mode = ADEC_MODE_PACK;
 *
 * ret = IMP_ADEC_CreateChn(adChn, &attr);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "imp audio decoder create channel failed\n");
 *		return ret;
 * }
 * @endcode
 *
 * @attention Once registered, use it the same way as the SDK's built-in decoder
 */
IMP_S32 IMP_ADEC_RegisterDecoder(IMP_S32 *ps32Handle, IMP_AUDIO_DECODER_S *pstDecoder);

/**
 * @fn IMP_S32 IMP_ADEC_UnRegisterDecoder(IMP_S32 *ps32Handle)
 *
 * Log out the decoder.
 *
 * @param[in] ps32handle Register handle (the handle obtained when registering the decoder).
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention None.
 */
IMP_S32 IMP_ADEC_UnRegisterDecoder(IMP_S32 *ps32Handle);

/**
 * ACODEC Settings.
 */
/**
 * @fn IMP_S32 IMP_AI_SetVolDb(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_FLOAT *pfVolDb)
 *
 * Set the audio input volume.
 *
 * @param[in] s32DevId Audio input device ID.
 * @param[in] s32Chn   Audio input channel ID.
 * @param[in] pfVolDb  Audio input volume pointer.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks The volume is in the range [-45.0, 30]. -45 represents silence, and
 * @remarks the volume can be amplified up to 30dB in 0.5dB steps, which must
 * @remarks be multiples of 0.5.Where 0 is a critical point in the volume
 * @remarks setting at which the software does not increase or decrease the
 * @remarks volume
 *
 * sample code
 * @code
 * IMP_S32 fVolDb = 10.0;
 * ret = IMP_AI_SetVolDb(devID, chnID, &fVolDb);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "Audio Record set fVolDb failed\n");
 *		return ret;
 * }
 * @endcode
 * @attention If the input fVolDb exceeds the range [-45.0, 30], anything less
 * than -45 will get -45 and anything greater than 30 will get 30db.
 */
IMP_S32 IMP_AI_SetVolDb(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_FLOAT *pfVolDb);

/**
 * @fn IMP_S32 IMP_AI_SetVol(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_S32 s32Vol)
 *
 * Set the audio input volume.
 *
 * @param[in] s32DevId Audio input device number.
 * @param[in] s32Chn   Audio input channel number.
 * @param[in] s32Vol   Audio input volume size.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks The volume can range from [-30, 120].-30 means mute the sound,and
 * @remarks 120 means amplify the sound by 30dB in 0.5dB steps.
 * @remarks Where 60 is a critical point of the volume setting,the software
 * @remarks does not increase or decrease the volume at this value, when the
 * @remarks volume value is less than 60, the volume is reduced by 0.5dB for
 * @remarks every 1 drop; When the volume value is greater than 60, the upper
 * @remarks is increased by 1, and the volume is increased by 0.5dB.
 *
 * sample code
 * @code
 * int volume = 60;
 * ret = IMP_AI_SetVol(devID, chnID, volume);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "Audio Record set volume failed\n");
 *		return ret;
 * }
 * @endcode
 *
 * @attention If the input aiVol exceeds the range [-30, 120], -30 will be used
 * for the value less than -30 and 120 will be used for the value greater than 120.
 */
IMP_S32 IMP_AI_SetVol(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_S32 s32Vol);

/**
 * @fn IMP_S32 IMP_AI_GetVolDb(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_FLOAT* pfVolDb)
 *
 * Gets the audio input volume.
 *
 * @param[in]  s32DevId Audio input device number.
 * @param[in]  s32Chn   Audio input channel number.
 * @param[out] pfVolDb  Audio input channel volume pointer.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention None.
 */
IMP_S32 IMP_AI_GetVolDb(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_FLOAT* pfVolDb);

/**
 * @fn IMP_S32 IMP_AI_GetVol(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_S32 *ps32Vol)
 *
 * Get the audio input volume.
 *
 * @param[in]  s32DevId Audio input device number.
 * @param[in]  s32Chn   Audio input channel number.
 * @param[out] ps32Vol  Audio input channel volume pointer.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention None.
 */
IMP_S32 IMP_AI_GetVol(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_S32 *ps32Vol);

/**
 * @fn IMP_S32 IMP_AI_SetVolMute(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_S32 s32Mute)
 *
 * Mute the audio input.
 *
 * @param[in]  aiDevId Audio input device number.
 * @param[in]  s32Chn  Audio input channel number.
 * @param[out] s32Mute Audio input mute flag, s32Mute = 0: turn off mute,
 * 			   s32Mute = 1: turn on mute.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks Calls to this interface are silenced immediately.
 *
 * @attention None.
 */
IMP_S32 IMP_AI_SetVolMute(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_S32 s32Mute);

/**
 * @fn IMP_S32 IMP_AO_SetVolDb(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_FLOAT *pfVolDb);
 *
 * Set the audio output channel volume.
 *
 * @param[in] s32DevId Audio input device number.
 * @param[in] s32Chn   Audio input channel number.
 * @param[in] fVolDb   Audio output channel volume pointer.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @attention If the output fVolDb exceeds the range [-45.0, 30], anything less
 * than -45 will get -45 and anything greater than 30 will get 30db.
 */
IMP_S32 IMP_AO_SetVolDb(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_FLOAT *pfVolDb);

/**
 * @fn IMP_S32 IMP_IMP_HDMI_AO_SetVolDb(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_FLOAT *pfVolDb);
 *
 * Set the HDMI audio output channel volume.
 *
 * @param[in] s32DevId Audio HDMI output device number.
 * @param[in] s32Chn   Audio HDMI output channel number.
 * @param[in] fVolDb   Audio output channel volume pointer.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @attention If the output fVolDb exceeds the range [-45.0, 30], anything less
 * than -45 will get -45 and anything greater than 30 will get 30db.
 */
IMP_S32 IMP_HDMI_AO_SetVolDb(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_FLOAT *pfVolDb);

/**
 * @fn IMP_S32 IMP_AO_SetVol(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_S32 s32Vol)
 *
 * Set the audio output channel volume.
 *
 * @param[in] s32DevId Audio input device number.
 * @param[in] s32Chn   Audio input channel number.
 * @param[in] s32Vol   audio output channel volume.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks The volume can range from [-30, 120].-30 means mute the sound,and
 * @remarks 120 means amplify the sound by 30dB in 0.5dB steps.
 * @remarks Where 60 is a critical point of the volume setting,the software
 * @remarks does not increase or decrease the volume at this value, when the
 * @remarks volume value is less than 60, the volume is reduced by 0.5dB for
 * @remarks every 1 drop; When the volume value is greater than 60, the upper
 * @remarks is increased by 1, and the volume is increased by 0.5dB.
 *
 * @attention If the input aoVol exceeds the range [-30 to 120], -30 will be
 * used for the value less than -30, and 120 will be used for the value greater than 120.
 */
IMP_S32 IMP_AO_SetVol(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_S32 s32Vol);

/**
 * @fn IMP_S32 IMP_HDMI_AO_SetVol(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_S32 s32Vol)
 *
 * Set the HDMI audio output channel volume.
 *
 * @param[in] s32DevId Audio device number.
 * @param[in] s32Chn   Audio channel number.
 * @param[in] s32Vol   Audio channel volume.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks The volume can range from [-30, 120].-30 means mute the sound,and
 * @remarks 120 means amplify the sound by 30dB in 0.5dB steps.
 * @remarks Where 60 is a critical point of the volume setting,the software
 * @remarks does not increase or decrease the volume at this value, when the
 * @remarks volume value is less than 60, the volume is reduced by 0.5dB for
 * @remarks every 1 drop; When the volume value is greater than 60, the upper
 * @remarks is increased by 1, and the volume is increased by 0.5dB.
 *
 * @attention If the input aoVol exceeds the range [-30 to 120], -30 will be
 * used for the value less than -30, and 120 will be used for the value greater than 120.
 */
IMP_S32 IMP_HDMI_AO_SetVol(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_S32 s32Vol);

/**
 * @fn IMP_S32 IMP_AO_GetVolDb(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_FLOAT* pfVolDb)
 *
 * Gets the audio output channel volume.
 *
 * @param[in]  s32DevId Audio device ID.
 * @param[in]  s32Chn   Audio channel ID.
 * @param[out] pfVolDb  Audio output volume pointer.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention None.
 */
IMP_S32 IMP_AO_GetVolDb(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_FLOAT* pfVolDb);

/**
 * @fn IMP_S32 IMP_HDMI_AO_GetVolDb(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_FLOAT* pfVolDb)
 *
 * Gets the HDMI audio output channel volume.
 *
 * @param[in]  s32DevId Audio Device ID.
 * @param[in]  s32Chn   Audio channel ID.
 * @param[out] pfVolDb  Audio output volumn pointer.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention None.
 */
IMP_S32 IMP_HDMI_AO_GetVolDb(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_FLOAT* pfVolDb);

/**
 * @fn IMP_S32 IMP_AO_GetVol(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_S32 *ps32Vol);
 *
 * Get the audio output channel volume.
 *
 * @param[in]  s32DevId Audio Device ID.
 * @param[in]  s32Chn   Audio channel ID.
 * @param[out] ps32Vol  Audio output volumn pointer.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention None.
 */
IMP_S32 IMP_AO_GetVol(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_S32 *ps32Vol);

/**
 * @fn IMP_S32 IMP_HDMI_AO_GetVol(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_S32 *ps32Vol);
 *
 * Get the audio output channel volume.
 *
 * @param[in]  s32DevId Audio Device ID.
 * @param[in]  s32Chn   Audio channel ID.
 * @param[out] ps32Vol  Audio output volume pointer.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention None.
 */
IMP_S32 IMP_HDMI_AO_GetVol(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_S32 *ps32Vol);

/**
 * @fn IMP_S32 IMP_AO_SetVolMute(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_S32 s32Mute)
 *
 * Mute the audio output.
 *
 * @param[in]  s32DevId Audio device ID.
 * @param[in]  s32Chn   Audio channel ID.
 * @param[out] s32Mute  Audio output mute flag, s32Mute = 0: turn off mute,
 * 						s32Mute = 1: turn on mute.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks Calls to this interface are silenced immediately.
 *
 * @attention None.
 */
IMP_S32 IMP_AO_SetVolMute(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_S32 s32Mute);

/**
 * @fn IMP_S32 IMP_HDMI_AO_SetVolMute(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_S32 s32Mute)
 *
 * Mute the HDMI audio output.
 *
 * @param[in]  s32DevId Audio device ID.
 * @param[in]  s32Chn   Audio channel ID.
 * @param[out] s32Mute  Audio output mute flag, s32Mute = 0: turn off mute,
 * 						s32Mute = 1: turn on mute.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks Calls to this interface are silenced immediately.
 *
 * @attention None.
 */
IMP_S32 IMP_HDMI_AO_SetVolMute(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_S32 s32Mute);

/**
 * @fn IMP_S32 IMP_AI_SetGainDb(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_FLOAT *pfGainDb)
 *
 * Set the audio input analog gain.
 *
 * @param[in] s32DevId Audio device ID.
 * @param[in] s32Chn   Audio channel ID.
 * @param[in] fGainDb Audio channel input gain. It must be a multiple of 1.5 or
 * 			  an error will be generated
 *
 * Corresponding to [-18dB to 28.5dB] with a step size of 1.5dB..
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 */
IMP_S32 IMP_AI_SetGainDb(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_FLOAT *pfGainDb);

/**
 * @fn IMP_S32 IMP_AI_SetGain(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_S32 s32Gain)
 *
 * Set the audio input analog gain.
 *
 * @param[in] s32DevId Audio device ID.
 * @param[in] s32Chn   Audio channel ID.
 * @param[in] s32Gain  Audio gain size pointer.
 *
 * Range [0 to 31], corresponding to [-18dB to 28.5dB], with a step size of 1.5dB.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention aiGain ranges from [0 to 31], if the input value is less than 0,
 * aiGain will be set to 0. If the value is greater than 31,aiGain is set to 31.
 *
 */
IMP_S32 IMP_AI_SetGain(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_S32 s32Gain);

/**
 * @fn IMP_S32 IMP_AI_GetGainDb(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_FLOAT *pfGainDb)
 *
 * Get the audio input analog gain value.
 *
 * @param[in]  s32DevId Audio device ID.
 * @param[in]  s32Chn   Audio channel ID.
 * @param[out] pfGainDb Audio channel input gain attribute pointer.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention None.
 */
IMP_S32 IMP_AI_GetGainDb(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_FLOAT *pfGainDb);

/**
 * @fn IMP_S32 IMP_AI_GetGain(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_S32 *ps32Gain)
 *
 * Get the audio input analog gain value.
 *
 * @param[in]  s32DevId Audio device ID.
 * @param[in]  s32Chn   Audio channel ID.
 * @param[out] ps32Gain Audio channel input gain attribute pointer.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention None.
 */
IMP_S32 IMP_AI_GetGain(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_S32 *ps32Gain);

/**
 * @fn IMP_S32 IMP_AO_SetGainDb(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_FLOAT *pfGainDb)
 *
 * Set the audio output gain.
 *
 * @param[in]  s32DevId Audio device ID.
 * @param[in]  s32Chn   Audio channel ID.
 * @param[out] pfGainDb  Range [-18dB to 28.5dB] with a step size of 1.5dB
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 */
IMP_S32 IMP_AO_SetGainDb(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_FLOAT *pfGainDb);

/**
 * @fn IMP_S32 IMP_AO_SetGain(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_S32 s32Gain)
 *
 * Set the audio output gainDB.
 *
 * @param[in]  s32DevId Audio device ID.
 * @param[in]  s32Chn   Audio channel ID.
 * @param[out] s32Gain  Audio output gain, range [0 to 0x1f], corresponding to
 * 				[-18dB to 28.5dB], step size 1.5dB.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention aoGain ranges from [0 to 31], if the input value is less than 0,
 * aoGain will be set to 0. If the value is greater than 31,aoGain is set to 31.
 */
IMP_S32 IMP_AO_SetGain(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_S32 s32Gain);

/**
 * @fn IMP_S32 IMP_AO_GetGainDb(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_FLOAT *pfGainDb)
 *
 * The audio output gain is obtained.
 *
 * @param[in]  s32DevId Audio device ID.
 * @param[in]  s32Chn   Audio channel ID.
 * @param[out] s32Gain  Audio output gain.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention None.
 */
IMP_S32 IMP_AO_GetGainDb(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_FLOAT *pfGainDb);

/**
 * @fn IMP_S32 IMP_AO_GetGain(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_S32* ps32Gain)
 *
 * The audio output gain is obtained.
 *
 * @param[in]  s32DevId  Audio device ID.
 * @param[in]  s32Chn    Audio channel ID.
 * @param[out] ps32Gain Audio output gainDb.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 *
 * @attention None.
 */
IMP_S32 IMP_AO_GetGain(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_S32* ps32Gain);

/**
 * @fn IMP_S32 IMP_AI_GetFrameAndRef(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_AUDIO_FRAME_S *pstFrm, IMP_AUDIO_FRAME_S *pstRef);
 *
 * The audio frame and the output reference frame are acquired.
 *
 * @param[in]  s32DevId Audio device ID.
 * @param[in]  s32Chn   Audio channel ID.
 * @param[out] pstFrm   Audio frame structure pointer.
 * @param[out] pstRef   Reference frame structure pointer.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks sample code
 * @code
 * IMP_AUDIO_FRAME_S frm;
 * IMP_AUDIO_FRAME_S ref;
 * // Get audio frame and reference frame
 * ret = IMP_AI_GetFrameAndRef(devID, chnID, &frm, &ref);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "Audio Get Frame Data error\n");
 *		return ret;
 * }
 *
 * fwrite(frm.virAddr, 1, frm.len, record_file);
 * fwrite(ref.virAddr, 1, ref.len, ref_file);
 *
 * @endcode
 *
 * @attention None.
 */
IMP_S32 IMP_AI_GetFrameAndRef(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_AUDIO_FRAME_S *pstFrm, IMP_AUDIO_FRAME_S *pstRef);

/**
 * @fn IMP_S32 IMP_AI_GetFrameAndRefTimeout(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_AUDIO_FRAME_S *pstFrm, IMP_AUDIO_FRAME_S *pstRef, IMP_S32 s32Timeout);
 *
 * The audio frame and the output reference frame are acquired.
 *
 * @param[in]  s32DevId Audio device ID.
 * @param[in]  s32Chn   Audio channel ID.
 * @param[out] pstFrm   Audio frame structure pointer.
 * @param[out] pstRef   Reference frame structure pointer.
 * @param[in] s32Timeout Get the audio frame blocking wait time, -1 indicates
 * blocking mode, 0 indicates non-blocking mode, >0 indicates how many
 * milliseconds to block, timeout will return an error.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks sample code
 * @code
 * IMP_AUDIO_FRAME_S frm;
 * IMP_AUDIO_FRAME_S ref;
 * // Get audio frame and reference frame
 * ret = IMP_AI_GetFrameAndRef(devID, chnID, &frm, &ref);
 * if(ret != 0) {
 *		IMP_LOG_ERR(TAG, "Audio Get Frame Data error\n");
 *		return ret;
 * }
 *
 * fwrite(frm.virAddr, 1, frm.len, record_file);
 * fwrite(ref.virAddr, 1, ref.len, ref_file);
 *
 * @endcode
 *
 * @attention s32Timeout If the blocking time is set, it is generally recommended
 * to set it to twice the audio frame time or more.
 */
IMP_S32 IMP_AI_GetFrameAndRefTimeout(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_AUDIO_FRAME_S *pstFrm, IMP_AUDIO_FRAME_S *pstRef, IMP_S32 s32Timeout);

/**
 * @fn IMP_S32 IMP_AI_EnableAecRefFrame(IMP_S32 s32DevId, IMP_S32 s32Chn)
 *
 * Enable to get reference frame.
 *
 * @param[in] s32DevId Audio device ID.
 * @param[in] s32Chn   Audio channel ID.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks This interface is called before IMP_AI_GetFrameAndRef is called.
 *
 * @attention None.
 */
IMP_S32 IMP_AI_EnableAecRefFrame(IMP_S32 s32DevId, IMP_S32 s32Chn);

/**
 * @fn IMP_S32 IMP_AI_DisableAecRefFrame(IMP_S32 s32DevId, IMP_S32 s32Chn)
 *
 * Disable to get reference frame.
 *
 * @param[in] s32DevId Audio device ID.
 * @param[in] s32Chn   Audio channel ID.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 * @attention None.
 */
IMP_S32 IMP_AI_DisableAecRefFrame(IMP_S32 s32DevId, IMP_S32 s32Chn);

/**
 * @fn IMP_S32 IMP_AO_EnableReSmp(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_AUDIO_SAMPLE_RATE_E enSrcSampleRate)
 *
 * Enable audio output resampling.
 *
 * @param[in] s32DevId Audio device ID.
 * @param[in] s32Chn   Audio channel ID.
 * @param[in] enSrcSampleRate Sampling rate of the input data.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 * @attention None.
 */
IMP_S32 IMP_AO_EnableReSmp(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_AUDIO_SAMPLE_RATE_E enSrcSampleRate);

/**
 * @fn IMP_S32 IMP_AO_DisableReSmp(IMP_S32 s32DevId, IMP_S32 s32Chn)
 *
 * Disable audio output resampling.
 *
 * @param[in] s32DevId Audio device ID.
 * @param[in] s32Chn   Audio channel ID.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 * @attention None.
 */
IMP_S32 IMP_AO_DisableReSmp(IMP_S32 s32DevId, IMP_S32 s32Chn);

/**
 * @fn IMP_S32 IMP_AI_EnableReSmp(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_AUDIO_SAMPLE_RATE_E enDstSampleRate)
 *
 * Enable audio output resampling.
 *
 * @param[in] s32DevId Audio device ID.
 * @param[in] s32Chn   Audio channel ID.
 * @param[in] enDstSampleRate Sampling rate of the output data.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 * @attention None.
 */
IMP_S32 IMP_AI_EnableReSmp(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_AUDIO_SAMPLE_RATE_E enDstSampleRate);

/**
 * @fn IMP_S32 IMP_S32 IMP_AI_DisableReSmp(IMP_S32 s32DevId, IMP_S32 s32Chn)
 *
 * Disable audio input resampling.
 *
 * @param[in] s32DevId Audio device ID.
 * @param[in] s32Chn   Audio channel ID.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 * @attention None.
 */
IMP_S32 IMP_AI_DisableReSmp(IMP_S32 s32DevId, IMP_S32 s32Chn);

/**
 * @fn IMP_S32 IMP_HDMI_AO_EnableReSmp(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_AUDIO_SAMPLE_RATE_E enSrcSampleRate)
 *
 * Enable audio HDMI input resampling
 *
 * @param[in] s32DevId Audio device ID.
 * @param[in] s32Chn   Audio channel ID.
 * @param[in] enSrcSampleRate Sampling rate of the input data.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 * @attention None.
 */
IMP_S32 IMP_HDMI_AO_EnableReSmp(IMP_S32 s32DevId, IMP_S32 s32Chn, IMP_AUDIO_SAMPLE_RATE_E enSrcSampleRate);

/**
 * @fn IMP_S32 IMP_HDMI_AO_DisableReSmp(IMP_S32 s32DevId, IMP_S32 s32Chn)
 *
 * Disable audio HDMI input resampling.
 *
 * @param[in] s32DevId Audio device ID.
 * @param[in] s32Chn   Audio channel ID.
 *
 * @retval 0 success.
 * @retval Non-zero failed.
 *
 * @remarks None.
 * @attention None.
 */
IMP_S32 IMP_HDMI_AO_DisableReSmp(IMP_S32 s32DevId, IMP_S32 s32Chn);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __IMP_AUDIO_H__ */
