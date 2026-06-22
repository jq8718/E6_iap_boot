/**
 *******************************************************************************
 * @file  config_hc32l021.h
 * @brief This file contains all the functions prototypes of peripherial init
 @verbatim
   Change Logs:
   Date             Author          Notes
   2025-03-25       MADS            First version
   2026-06-16       Claude          Replace LPUART1 with HSI2C slave
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2025, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

#ifndef __PERI_INIT__H__
#define __PERI_INIT__H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "utils.h"
/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/
/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
void HC32_PeriModuleInit(void);   /* Peripheral init (HSI2C + BTIM0 + GPIO + SysClock) */
void HC32_PeriModuleDeInit(void); /* Peripheral deinit (reset all to default) */

/* I2C Slave functions */
void HC32_I2cSlaveInit(void);   /* HSI2C slave init */
void HC32_I2cSlaveDeInit(void); /* HSI2C slave deinit */

/* CRC16 calculation */
uint32_t HC32_CalCrc16(uint8_t *pu8Data, uint32_t u32Offset, uint32_t u32Size); /* CRC16 compute */

/* Timer functions (1ms timeout) */
uint32_t HC32_GetTimUIFStatus(void); /* TIMER overflow flag get */
void     HC32_ClrTimUIFStatus(void); /* TIMER overflow flag clear */

/* Flash driver functions */
en_result_t HC32_FlashEraseSector(uint32_t u32SectorAddr);                                       /* FLASH sector erase */
en_result_t HC32_FlashWriteBytes(uint32_t u32Addr, uint8_t *pu8Data, uint32_t u32Len);           /* FLASH byte write */
void        HC32_FlashReadBytes(uint32_t u32Addr, uint8_t *pu8ReadBuff, uint32_t u32ByteLength); /* FLASH byte read */

/* Debug UART (LPUART1, PA01 TX only, 115200) */
void HC32_DbgUartInit(void);
void HC32_DbgPrint(const char *pstr);
void HC32_DbgPutHex32(uint32_t u32Val);

#ifdef __cplusplus
}
#endif

#endif /* __PERI_INIT__H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
