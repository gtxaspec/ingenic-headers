/*
 * IMP System header file.
 *
 * Copyright (C) 2014 Ingenic Semiconductor Co.,Ltd
 */

#ifndef __IMP_SYSTEM_H__
#define __IMP_SYSTEM_H__

#include "imp_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

/**
 * @file
 * IMP System modulus header file
 */

/**
 * @defgroup imp IMP(Ingenic Media Platform)
 */

/**
 * @defgroup IMP_System
 * @ingroup imp
 * @brief system control modulus, including the basic functions or IMP and related functions such as modulus binding.
 * @section concept
 * system control mainly realizes the connection of various modulus and defined data flow.
 *
 * @{
 */

/**
 * IMP system version definition.
 */
typedef struct {
	char cVersion[64];	/**< system version */
} IMP_VERSION_S;

#define IMP_MAX_SCALER_TABLE_NUM 16
/*
 * The static parameters of the IMP System must be set before system initialization.
 * u32AlignWidth The string byte alignment of image used in the system must be an integer multiple of 16; The system default is 16.
 * u32Scaler The pre-set scaling factor or the system scaling modulus. if using the system default value ,please set the first factor to 0.
 * */
typedef struct {
	/*
	 *  stride of picture buffer must be aligned with this value.
	 *  it must be multiple of 16.
	 * */
	IMP_U32	u32AlignWidth;
    /*
     * The scaling table in sdk corresponds to one scaling parameter table for each factor, and the scaling table will occupy rmem memory.
     * parameter ：(srcsize * 10 ) / dstsize； 0 means end. SDK will select application parameters based on the actual scaling factor.
     * {3,5,7,9,11,12,0}
     * */
    IMP_U32 u32Scaler[IMP_MAX_SCALER_TABLE_NUM];
} IMP_SYS_CONF_S;

/**
 * @fn IMP_S32 IMP_System_SetConf(const IMP_SYS_CONF_S *pstSysConf)
 *
 * Set IMP system static parameters.
 *
 * @param[in] pstSysConf system static parameters pointer.
 *
 * @retval IMP_SUCCESS success
 * @retval un IMP_SUCCESS failure.
 *
 * @remarks setting system parameters.
 *
 * @attention Must be called before system initialization, otherwise an error is return.
 */
IMP_S32 IMP_System_SetConf(const IMP_SYS_CONF_S *pstSysConf);

/**
 * @fn IMP_S32 IMP_System_GetConf(IMP_SYS_CONF_S *pstSysConf)
 *
 * get IMP system static parameters.
 *
 * @param[in] pstSysConf system static parameters pointer.
 *
 * @retval IMP_SUCCESS success
 * @retval un IMP_SUCCESS failure.
 *
 * @remarks get system static parameters.
 *
 * @attention
 */
IMP_S32 IMP_System_GetConf(IMP_SYS_CONF_S *pstSysConf);


/**
 * @fn int IMP_System_Init(void)
 *
 * IMP system initialization.
 *
 * @param null.
 *
 * @retval IMP_SUCCESS success
 * @retval un IMP_SUCCESS failure.
 *
 * @remarks will initialize the basic data structure.
 *
 * @attention  Must be called before other operations.
 */
IMP_S32 IMP_System_Init(void);

/**
 * @fn int IMP_System_Exit(void)
 *
 * IMP system exit.
 *
 * @param null.
 *
 * @retval IMP_SUCCESS success
 * @retval un IMP_SUCCESS failure.
 *
 * @remarks rele IMP memory and handles, and close hardware.
 *
 */
IMP_S32 IMP_System_Exit(void);

/**
 * @fn int IMP_System_Bind(IMP_CELL_S *srcCell, IMP_CELL_S *dstCell)
 *
 * bind source Cell and destination Cell.
 *
 * @param[in] srcCell .
 * @param[in] dstCell .
 *
 * @retval IMP_SUCCESS success
 * @retval un IMP_SUCCESS failure.
 *
 * @remarks base module, device and channel, the same hardware can virtual multiple time-sharing mult device,
 * each device including multiple channels. binding is a direct relationaship between channels.
 * @remarks after successful binding, the data generate by the source call is auto sent to the destination call.
 *
 * @attention null.
 */
IMP_S32 IMP_System_Bind(IMP_CELL_S *srcCell, IMP_CELL_S *dstCell);

/**
 * @fn int IMP_System_UnBind(IMP_CELL_S *srcCell, IMP_CELL_S *dstCell)
 *
 * unbind source Cell and destination Cell.
 *
 * @param[in] srcCell .
 * @param[in] dstCell .
 *
 * @retval IMP_SUCCESS success
 * @retval un IMP_SUCCESS failure.
 *
 *
 * @remarks null.
 *
 * @attention null.
 */
IMP_S32 IMP_System_UnBind(IMP_CELL_S *srcCell, IMP_CELL_S *dstCell);

/**
 * @fn int IMP_System_GetBindbyDest(IMP_CELL_S *dstCell, IMP_CELL_S *srcCell)
 *
 * unbind source Cell and destination Cell information.
 *
 * @param[in] srcCell .
 * @param[in] dstCell .
 *
 * @retval IMP_SUCCESS success
 * @retval un IMP_SUCCESS failure.
 *
 * @remarks null.
 *
 * @attention null
 */
IMP_S32 IMP_System_GetBindbyDest(IMP_CELL_S *dstCell, IMP_CELL_S *srcCell);

/**
 * @fn int IMP_System_GetVersion(IMP_VERSION_S *pstVersion)
 *
 * get system version.
 *
 * @param[out] pstVersion imp version structure pointer.
 *
 * @retval IMP_SUCCESS success
 * @retval un IMP_SUCCESS failure.
 *
 * @remarks null.
 *
 * @attention null
 */
IMP_S32 IMP_System_GetVersion(IMP_VERSION_S *pstVersion);


/**
 * @fn IMP_S32 IMP_System_GetCurPts(IMP_U64 *pu64CurPts)
 *
 * get system timestamp(ms).
 *
 * @param[in] pu64CurPts
 *
 * @retval IMP_SUCCESS success
 * @retval un IMP_SUCCESS failure.
 *
 * @remarks null.
 *
 * @attention null
 */
IMP_S32 IMP_System_GetCurPts(IMP_U64 *pu64CurPts);

/**
 * @fn IMP_S32 IMP_System_InitPtsBase(IMP_U64 u64Ptsbase)
 *
 * set system timestamp(ms).
 *
 * @param[in] pu64CurPts
 *
 * @retval IMP_SUCCESS success
 * @retval un IMP_SUCCESS failure.
 *
 * @remarks null.
 *
 * @attention null
 */
IMP_S32 IMP_System_InitPtsBase(IMP_U64 u64Ptsbase);

/**
 * @fn IMP_S32 IMP_System_SyncPts(IMP_U64 u64Ptsbase)
 *
 * set system sync timestamp(ms).
 *
 * @param[in] pu64CurPts
 *
 * @retval IMP_SUCCESS success
 * @retval un IMP_SUCCESS failure.
 *
 * @remarks null.
 *
 * @attention null
 */
IMP_S32 IMP_System_SyncPts(IMP_U64 u64Ptsbase);

/**
 * @fn uint32_t IMP_System_ReadReg32(uint32_t u32Addr)
 *
 * read register value
 *
 * @param[in] regAddr 	register address
 *
 * @retval register value
 *
 * @remarks null.
 *
 * @attention null
 */
IMP_U32 IMP_System_ReadReg32(IMP_U32 regAddr);

/**
 * @fn void IMP_System_WriteReg32(uint32_t regAddr, uint32_t value)
 *
 * write register
 *
 * @param[in] regAddr 	register address
 *
 * @retval null
 *
 * @remarks null.
 *
 * @attention use the interface with caution
 */
void IMP_System_WriteReg32(IMP_U32 regAddr, IMP_U32 value);

/**
 * @fn const char* IMP_System_GetCPUInfo(void)
 *
 * get CPU mode information.
 *
 * @param null.
 *
 * @retval CPU mode string.
 *
 * @remarks return cpu mode string, eg "A1-N" or "A1-X".
 *
 * @attention null.
 */
const IMP_CHAR* IMP_System_GetCPUInfo(IMP_VOID);

/**
 * @fn IMP_S32 IMP_System_GetChipId(IMP_U32 *pu32ChipId)
 *
 * get CPU CHIP ID,length 96bit.
 *
 * @param[in] pu32ChipId 	CPUID storage address, this address space must be at least 96bit.
 *
 * @retval IMP_SUCCESS success
 * @retval un IMP_SUCCESS failure.
 *
 * @remarks null.
 *
 * @attention null.
 */
IMP_S32 IMP_System_GetChipId(IMP_U32 *pu32ChipId);

/**
 * @fn IMP_S32 IMP_System_CloseFd(IMP_VOID)
 *
 * close all sdk open log、system、mem fd.
 *
 * @param null.
 *
 * @retval IMP_SUCCESS success
 * @retval un IMP_SUCCESS failure.
 *
 * @remarks null.
 *
 * @attention null.
 */
IMP_S32 IMP_System_CloseFd(IMP_VOID);


/**
 * @fn IMP_S32 IMP_System_CreatPool(IMP_U32 *pu32PoolId, IMP_U32 u32BlkSize, IMP_U32 u32BlkCnt, const char *pcPoolName);
 *
 * create mempool on rmem
 *
 * @param[in] pu32PoolId 	mempool id address.
 * @param[in] u32BlkSize	block size in mempool,unit bytes.
 * @param[in] u32BlkSize	number of blocks in mempool.
 * @param[in] pcPoolName	mempool name.
 *
 * @retval IMP_SUCCESS success
 * @retval un IMP_SUCCESS failure.
 *
 * @remarks
 * Mempool mainly provides large continues physical memory management for media businesses,
 * responside for memory allocation and recycling, fully leverage the role of mempool and ensure that
 * each modulu uses memory in a reasonable manner.
 * Mempool is built on the basis of RMEM(not building page table through the kernel) of memory management.
 * If using a mempool, the size of the mempool must be configured before system initialization.
 * Depending on the businesses,the size and quantity of mempool requests vary.
 *
 * @attention pcPoolName cannot be null or duplicate.
 */
IMP_S32 IMP_System_CreatPool(IMP_U32 *pu32PoolId, IMP_U32 u32BlkSize, IMP_U32 u32BlkCnt, const char *pcPoolName);

/**
 * @fn IMP_S32 IMP_System_CreatPool_Align(IMP_U32 *pu32PoolId, IMP_U32 u32BlkSize, IMP_U32 u32BlkCnt, const char *pcPoolName,IMP_S32 s32AlignWidth);
 *
 * Create mempool on rmem aligned.
 *
 * @param[in] pu32PoolId 	mempool id address.
 * @param[in] u32BlkSize	block size in mempool,unit bytes.
 * @param[in] u32BlkSize	number of blocks in mempool.
 * @param[in] pcPoolName	mempool name.
 * @param[in] s32AlignWidth	aligned bytes.
 *
 * @retval IMP_SUCCESS success
 * @retval un IMP_SUCCESS failure.
 *
 * @remarks
 * Mempool mainly provides large continues physical memory management for media businesses,
 * responside for memory allocation and recycling, fully leverage the role of mempool and ensure that
 * each modulu uses memory in a reasonable manner.
 * Mempool is built on the basis of RMEM(not building page table through the kernel) of memory management.
 * If using a mempool, the size of the mempool must be configured before system initialization.
 * Depending on the businesses,the size and quantity of mempool requests vary.
 *
 * @attention pcPoolName cannot be null or duplicate.
 */
IMP_S32 IMP_System_CreatPool_Align(IMP_U32 *pu32PoolId, IMP_U32 u32BlkSize, IMP_U32 u32BlkCnt, const char *pcPoolName,IMP_S32 s32AlignWidth);

/**
 * @fn IMP_S32 IMP_System_DestroyPool(IMP_U32 u32PoolId, const char *pcPoolName);
 *
 * Destroy the mempool
 *
 * @param[in] u32PoolId 	ID of destroy mempool，priority matching ID, ignore pcName if matching is successful.
 * @param[in] pcPoolName	mempool name. matching name when u32PoolId is invalid.
 *
 * @retval IMP_SUCCESS success
 * @retval un IMP_SUCCESS failure.
 *
 * @remarks
 * destroy mempool，priority matching ID, ignore pcName if matching is successful,
 * matching name when u32PoolId is invalid.
 *
 * @attention null.
 */
IMP_S32 IMP_System_DestroyPool(IMP_U32 u32PoolId, const char *pcPoolName);

/**
 * @fn IMP_VOID *IMP_System_GetBlock(IMP_U32 u32PoolId, const char *pcPoolName, IMP_U32 u32Size, const char *pcBlkName);
 *
 * get block from u32PoolId or pcPoolName
 *
 * @param[in] u32PoolId 	priority matching ID, ignore pcName if matching is successful.
 * @param[in] pcName		matching name when u32PoolId is invalid. after successful matching, allocate blocks from the pool.
 * @param[in] Size		 	block size.
 * @param[in] pcBlkName		block name, cannot be null.
 *
 *
 * @retval successful return the virtual address of the block
 * @retval failure return IMP_NULL
 *
 * @remarks
 *
 * @attention null.
 */
IMP_VOID *IMP_System_GetBlock(IMP_U32 u32PoolId, const char *pcPoolName, IMP_U32 u32Size, const char *pcBlkName);

/**
 * @fn IMP_S32 IMP_System_ReleaseBlock(IMP_U32 u32PoolId, IMP_VOID *pBlockVaddr);
 *
 * release the block space for pBlockVaddr from u32PoolId.
 *
 * @param[in] u32PoolId		mempool ID.
 * @param[in] pBlockVaddr	virtual address of the block.
 *
 *
 * @retval IMP_SUCCESS success
 * @retval un IMP_SUCCESS failure.
 *
 * @remarks
 *
 * @attention
 */
IMP_S32 IMP_System_ReleaseBlock(IMP_U32 u32PoolId, IMP_VOID *pBlockVaddr);

/**
 * @fn IMP_U32 IMP_System_Block2PhyAddr(IMP_VOID *pBlockVaddr);
 *
 * virtual address to physical address translation
 *
 * @param[in] pBlockVaddr	virtual address of the block
 *
 *
 * @retval successful return the physics address of the block
 * @retval failure return IMP_NULL
 *
 * @remarks
 *
 * @attention null.
 */
IMP_U32 IMP_System_Block2PhyAddr(IMP_VOID *pBlockVaddr);

/**
 * @fn IMP_U32 IMP_System_Block2PoolId(IMP_VOID *pBlockVaddr);
 *
 * get the mempool ID that the block belongs to
 *
 * @param[in] pBlockVaddr	virtual address of the block
 *
 *
 * @retval successful return the mempool ID
 * @retval failure return IMP_NULL
 *
 * @remarks
 *
 * @attention null.
 */
IMP_U32 IMP_System_Block2PoolId(IMP_VOID *pBlockVaddr);

/**
 * @fn IMP_S32 IMP_System_FlushCache(IMP_VOID *pBlockVaddr, IMP_U32 u32Size);
 *
 * users refresh the contents or the cache into memory and invalidate the contents of the cache
 *
 * @param[in] pBlockVaddr	virtual address of the block
 * @param[in] u32Size		block size
 *
 *
 * @retval successful return the mempool ID
 * @retval failure return IMP_NULL
 *
 * @remarks
 *
 * @attention null.
 */
IMP_S32 IMP_System_FlushCache(IMP_VOID *pBlockVaddr, IMP_U32 u32Size);

/**
 * @fn IMP_CHAR *IMP_System_PixfmtToString(PIXEL_FORMAT_E Pixfmt);
 *
 * get the format of the image string.
 *
 * @param[in] Pixfmt	pixel format
 *
 *
 * @retval successful return the pixel format string
 * @retval failure return IMP_NULL
 *
 * @remarks
 *
 * @attention null.
 */
IMP_CHAR *IMP_System_PixfmtToString(PIXEL_FORMAT_E Pixfmt);
/**
 * @}
 */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __IMP_SYSTEM_H__ */
