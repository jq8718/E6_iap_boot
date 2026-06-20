/**
 *******************************************************************************
 * @file  utils.h
 * @brief This file contains macro definition of IAP
 @verbatim
   Change Logs:
   Date             Author          Notes
   2025-03-25       MADS            First version
   2026-06-16       Claude          I2C IAP refactor: add protocol constants,
                                    virtual register addresses, status/error codes,
                                    command codes, update IRQ mapping
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

#ifndef __UTILS_H__
#define __UTILS_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "base_types.h"
#include "hc32l021.h"
#include "interrupts_hc32l021.h"
/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*===================================================================
 *  I2C Slave Configuration
 *===================================================================*/
#define I2C_SLAVE_ADDR (0x20u) /* 7-bit I2C slave address, configurable */

/*===================================================================
 *  Clock Configuration
 *===================================================================*/
#define SYS_CLK_INIT_HZ (48000000u) /* System clock, Hz (Boot init) */

/*===================================================================
 *  FLASH Configuration
 *===================================================================*/
#define FLASH_SECTOR_SIZE (0x200u)                               /* Sector size */
#define FLASH_SECTOR_NUM  (0x80u)                                /* Sector count */
#define FLASH_START_ADDR  ((uint32_t)0x00000000u)                /* FLASH base address */
#define FLASH_SIZE        (FLASH_SECTOR_NUM * FLASH_SECTOR_SIZE) /* FLASH size */
#define FLASH_END_ADDR    ((uint32_t)(FLASH_START_ADDR + FLASH_SIZE - 1u))

/*===================================================================
 *  RAM Configuration
 *===================================================================*/
#define SRAM_BASE ((uint32_t)0x20000000) /* RAM base address */
#define RAM_SIZE  (0x1800u)              /* RAM size (6KB) */

/*===================================================================
 *  Bootloader FLASH Layout
 *===================================================================*/
#define BOOT_SIZE      (8u * FLASH_SECTOR_SIZE) /* Boot FLASH size (4KB) */
/* Boot parameter placed at the LAST sector of Flash so the bootloader
 * can use the full BOOT_SIZE region for code. */
#define BOOT_PARAM_ADDR (FLASH_START_ADDR + FLASH_SIZE - FLASH_SECTOR_SIZE)

/*===================================================================
 *  APP FLASH Configuration
 *===================================================================*/
#define APP_ADDR      (FLASH_START_ADDR + BOOT_SIZE)                    /* APP start address */
#define APP_MAX_SIZE  (FLASH_SIZE - BOOT_SIZE - FLASH_SECTOR_SIZE)      /* APP max size (excludes boot_param sector) */

/*===================================================================
 *  Protocol Constants
 *===================================================================*/
#define IAP_MAILBOX_SIZE     (530u) /* 530 bytes, sub-addresses 0x20~0x231 */
#define IAP_PAYLOAD_MAX      (512u) /* Max payload bytes per frame */
#define IAP_HEADER_SIZE      (8u)   /* Fixed header size */
#define IAP_CRC_SIZE         (2u)   /* CRC16 field size */
#define IAP_FRAME_MIN        (10u)  /* Header(8) + CRC(2), PayloadLen=0 */
#define IAP_FRAME_MAX        (522u) /* Header(8) + Payload(512) + CRC(2) */
#define IAP_PROTOCOL_VERSION (0x01u)

/* Frame header offsets (in MAILBOX) */
#define HDR_OFFSET_MAGIC0     (0u)
#define HDR_OFFSET_MAGIC1     (1u)
#define HDR_OFFSET_VERSION    (2u)
#define HDR_OFFSET_CMD        (3u)
#define HDR_OFFSET_SEQ        (4u)
#define HDR_OFFSET_FLAGS      (5u)
#define HDR_OFFSET_PAYLOADLEN (6u)
#define HDR_OFFSET_PAYLOAD    (8u)

#define FRAME_MAGIC0 (0x6Du)
#define FRAME_MAGIC1 (0xACu)

/*===================================================================
 *  Virtual Register Addresses
 *===================================================================*/
#define REG_STATUS        (0x00u) /* R  1B  Boot status */
#define REG_ERROR         (0x01u) /* R  1B  Last error code */
#define REG_CTRL          (0x02u) /* W  1B  Control command */
#define REG_TX_LEN        (0x06u) /* R  2B  Response frame length */
#define REG_MAILBOX_START (0x20u) /* R/W 530B  Data window start */
#define REG_MAILBOX_END   (0x231u) /* R/W 530B  Data window end */

/*===================================================================
 *  CTRL Register Values
 *===================================================================*/
#define CTRL_COMMIT (0xA5u) /* Submit MAILBOX for execution */
#define CTRL_CLEAR  (0x5Au) /* Acknowledge response, clear to IDLE */
#define CTRL_ABORT  (0xC3u) /* Abort current operation, return to IDLE */

/*===================================================================
 *  STATUS Register Values
 *===================================================================*/
#define STATUS_IDLE       (0x00u) /* Ready to accept new command */
#define STATUS_BUSY       (0x02u) /* Executing (Flash erase/write/CRC), do not write */
#define STATUS_RESP_READY (0x03u) /* Response ready in MAILBOX, host may read */
#define STATUS_ERROR      (0x04u) /* Error occurred, read ERROR register */

/*===================================================================
 *  ERROR Codes (same as response Payload[0])
 *===================================================================*/
#define ERROR_CODE_OK            (0x00u) /* No error (OK) */
#define ERROR_CODE_CRC           (0x01u) /* Request frame CRC mismatch */
#define ERROR_CODE_FRAME         (0x02u) /* Magic, PayloadLen, or Version invalid */
#define ERROR_CODE_UNSUPPORTED   (0x03u) /* Unsupported command code */
#define ERROR_CODE_ADDR          (0x04u) /* Flash address out of range or unaligned */
#define ERROR_CODE_FLASH         (0x05u) /* Flash erase/write failed */
#define ERROR_CODE_BUSY          (0x06u) /* Operation not allowed in current state */
#define ERROR_CODE_SEQ           (0x07u) /* Duplicate or invalid sequence number */
#define ERROR_CODE_APP_INVALID   (0x08u) /* APP vector table invalid */

/*===================================================================
 *  Command Codes
 *===================================================================*/
#define CMD_HANDSHAKE    (0x20u) /* Protocol handshake, exchange versions */
#define CMD_JUMP_TO_APP  (0x21u) /* Verify CRC and jump to APP */
#define CMD_APP_DOWNLOAD (0x22u) /* Download firmware chunk */
#define CMD_ERASE_FLASH  (0x24u) /* Erase APP flash area */
#define CMD_CRC_FLASH    (0x25u) /* Compute and store Flash CRC */

/*===================================================================
 *  Interrupt Handler Name Redefinition
 *===================================================================*/
#define MODEM_I2cIrqHandler(void) HSI2C_IRQHandler(void)    /* I2C slave ISR */
#define MODEM_TimIrqHandler(void) CTIM0_IRQHandler(void)    /* Timer ISR (1ms) */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/
/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* __UTILS_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
