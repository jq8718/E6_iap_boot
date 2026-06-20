/**
 *******************************************************************************
 * @file  flash.h
 * @brief This file contains all the functions prototypes of the FLASH driver
 *        library
 @verbatim
   Change Logs:
   Date             Author          Notes
   2024-09-18       MADS            First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2024, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

#ifndef __FLASH_H__
#define __FLASH_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "ddl.h"

/**
 * @addtogroup HC32L021_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_FLASH FLASH模块驱动库
 * @{
 */
/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup FLASH_Global_Macros FLASH全局宏定义
 * @{
 */

/**
 * @defgroup FLASH_Mode FLASH模式
 * @{
 */
#define FLASH_MD_RD           (0x0u << FLASH_CR_OP_Pos) /*!< FLASH读模式 */
#define FLASH_MD_WR           (0x1u << FLASH_CR_OP_Pos) /*!< FLASH写（编程）模式 */
#define FLASH_MD_SECTOR_ERASE (0x2u << FLASH_CR_OP_Pos) /*!< FLASH扇区（页）擦除模式 */
#define FLASH_MD_CHIP_ERASE   (0x3u << FLASH_CR_OP_Pos) /*!< FLASH全片擦除模式 */
#define FLASH_MD_CONT_WR      (FLASH_CR_CONTP_Msk)      /*!< FLASH连续写模式 */
/**
 * @}
 */

/**
 * @defgroup FLASH_Int_Enable_Types FLASH中断使能类型定义
 * @{
 */
#define FLASH_INT_ENABLE_PC   (0x1u << FLASH_CR_IE_Pos) /*!< 擦写保护报警中断使能 */
#define FLASH_INT_ENABLE_PROT (0x2u << FLASH_CR_IE_Pos) /*!< 擦写PC地址报警中断使能*/
/**
 * @}
 */

/**
 * @defgroup FLASH_Int_Flag_Types FLASH中断状态类型定义
 * @{
 */
#define FLASH_INT_FLAG_PC   (FLASH_IFR_PC_Msk)   /*!< 擦写保护报警中断状态 */
#define FLASH_INT_FLAG_PROT (FLASH_IFR_PROT_Msk) /*!< 擦写PC地址报警中断状态 */
/**
 * @}
 */

/**
 * @defgroup FLASH_Wait_Cycles FLASH读等待周期
 * @{
 */
#define FLASH_WAIT_CYCLE0 (0x0u)                      /*!< 读等待周期设置为0-即读周期为1（HCLK:0 ~ 24MHz时） */
#define FLASH_WAIT_CYCLE1 (0x1u << FLASH_CR_WAIT_Pos) /*!< 读等待周期设置为1-即读周期为2（HCLK:24MHz ~ 48MHz) */
/**
 * @}
 */

/**
 * @defgroup FLASH_Protect_Status FLASH保护状态
 * @{
 */
#define FLASH_PROTECT_LVL0 (0x0u << FLASH_LOCK_ST_Pos) /*!< Level0，ISP 可读写，SWD 可读写 */
#define FLASH_PROTECT_LVL1 (0x1u << FLASH_LOCK_ST_Pos) /*!< Level1，ISP 可降级，SWD 可降级；数据不可读出 */
#define FLASH_PROTECT_LVL2 (0x2u << FLASH_LOCK_ST_Pos) /*!< Level2，ISP 可降级，SWD 无功能；数据不可读出 */
#define FLASH_PROTECT_LVL3 (0x3u << FLASH_LOCK_ST_Pos) /*!< Level3，ISP 无功能，SWD 无功能；数据不可读出 */
/**
 * @}
 */

/**
 * @defgroup FLASH_Bypass FLASH寄存器解锁
 * @{
 */
#define FLASH_BYPASS() \
    do \
    { \
        WRITE_REG16(FLASH->BYPASS, 0x5A5Au); \
        WRITE_REG16(FLASH->BYPASS, 0xA5A5u); \
    } while (0);
/**
 * @}
 */

/**
 * @}
 */
/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/
/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup FLASH_Global_Functions FLASH全局函数定义
 * @{
 */
#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
#define RAMFUNC __attribute__((section(".ramfunc")))
#elif defined(__ICCARM__)
#define RAMFUNC __ramfunc
#endif
en_result_t FLASH_OperateModeConfig(uint32_t u32FlashOperateMode);                      /* FLASH操作模式配置 */
en_result_t FLASH_SectorErase(uint32_t u32SectorAddr);                                  /* FLASH扇区擦除 */
en_result_t FLASH_WriteByte(uint32_t u32Addr, uint8_t *pu8Data, uint32_t u32Len);       /* FLASH连续字节（8位方式） 编程 */
en_result_t FLASH_WriteHalfWord(uint32_t u32Addr, uint16_t *pu16Data, uint32_t u32Len); /* FLASH连续半字（16位方式）编程 */
en_result_t FLASH_WriteWord(uint32_t u32Addr, uint32_t *pu32Data, uint32_t u32Len);     /* FLASH连续字  （32位方式）编程 */

RAMFUNC en_result_t FLASH_OperateModeConfigRamFunc(uint32_t u32FlashOperateMode);                  /* FLASH操作模式配置 (RAM中执行) */
RAMFUNC en_result_t FLASH_ChipErase(void);                                                         /* FLASH全片擦除 (RAM中执行) */
RAMFUNC en_result_t FLASH_ContinousWriteByte(uint32_t u32Addr, uint8_t *pu8Data, uint32_t u32Len); /* FLASH字节（8位方式） 连续写 (RAM中执行) */
RAMFUNC en_result_t FLASH_ContinousWriteHalfWord(uint32_t u32Addr, uint16_t *pu16Data, uint32_t u32Len); /* FLASH半字（16位方式）连续写 (RAM中执行) */
RAMFUNC en_result_t FLASH_ContinousWriteWord(uint32_t u32Addr, uint32_t *pu32Data, uint32_t u32Len); /* FLASH字  （32位方式）连续写 (RAM中执行) */

void      FLASH_IntEnable(uint32_t u32FlashIntEnable);  /* FLASH中断使能 */
void      FLASH_IntDisable(uint32_t u32FlashIntEnable); /* FLASH中断禁止 */
boolean_t FLASH_IntFlagGet(uint32_t u32FlashIntFlag);   /* FLASH中断标志获取 */
void      FLASH_IntFlagClear(uint32_t u32FlashIntFlag); /* FLASH中断标志清除 */

en_result_t FLASH_LockAllSector(void);                      /* FLASH所有Sector不允许擦写保护 */
en_result_t FLASH_UnlockAllSector(void);                    /* FLASH所有Sector允许擦写保护 */
en_result_t FLASH_LockUnlockSectors(uint32_t u32LockValue); /* FLASH Sector LOCK 设置 */

en_result_t FLASH_WaitCycle(uint32_t u32FlashWaitCycle); /* FLASH读等待周期设置 */

en_result_t FLASH_LowPowerEnable(void);  /* FLASH低功耗模式使能 */
en_result_t FLASH_LowPowerDisable(void); /* FLASH低功耗模式禁止 */

uint32_t FLASH_ProtectStatusGet(void); /* FLASH保护状态获取 */

void FLASH_ReadOnlyEnable(void);  /* FLASH只读、不可编程或擦写 */
void FLASH_ReadOnlyDisable(void); /* FLASH可读、可编程、可擦写 */
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __FLASH_H__ */
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
