/*******************************************************************************
 * @file  modem.c
 * @brief This file provides firmware functions of MODEM for I2C IAP Bootloader
 @verbatim
   Change Logs:
   Date             Author          Notes
   2025-03-25       MADS            First version (UART)
   2026-06-20       Claude          Rewrite for I2C slave + virtual registers
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "modem.h"
#include "config_hc32l021.h"
#include "boot_param.h"

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
/**
 * @brief  Command handler result
 */
typedef struct
{
    uint8_t  u8ErrCode;       /*!< Error code (0x00 = OK) */
    uint8_t  au8Payload[16];  /*!< Response payload (excluding result code) */
    uint16_t u16PayloadLen;   /*!< Length of response payload */
} stc_cmd_result_t;

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void MODEM_SetError(uint8_t u8ErrCode);
static void MODEM_BuildResponse(uint8_t u8Cmd, uint8_t u8Seq, uint8_t u8ErrCode,
                                const uint8_t *pu8Payload, uint16_t u16PayloadLen);

static stc_cmd_result_t CmdHandshake(void);
static stc_cmd_result_t CmdEraseFlash(const uint8_t *pu8Payload, uint16_t u16PayloadLen);
static stc_cmd_result_t CmdAppDownload(const uint8_t *pu8Payload, uint16_t u16PayloadLen);
static stc_cmd_result_t CmdCrcFlash(const uint8_t *pu8Payload, uint16_t u16PayloadLen);
static stc_cmd_result_t CmdJumpToApp(const uint8_t *pu8Payload, uint16_t u16PayloadLen);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
/* Virtual registers */
static volatile uint8_t  s_u8RegStatus;     /*!< STATUS register (0x00) */
static volatile uint8_t  s_u8RegError;      /*!< ERROR register (0x01) */
static volatile uint16_t s_u16RegTxLen;     /*!< TX_LEN register (0x06) */

/* MAILBOX buffers */
static uint8_t  s_au8RxMailbox[IAP_MAILBOX_SIZE]; /*!< Request frame buffer */
static uint8_t  s_au8TxMailbox[IAP_MAILBOX_SIZE]; /*!< Response frame buffer */

/* I2C transaction state */
static volatile uint16_t s_u16RxMailboxIdx;   /*!< Current RX MAILBOX write offset */
static volatile uint16_t s_u16TxMailboxIdx;   /*!< Current TX MAILBOX read offset */
static volatile uint8_t  s_u8SubAddr;         /*!< Current sub-address */
static volatile boolean_t s_bSubAddrValid;    /*!< Sub-address received in current transaction */
static volatile boolean_t s_bTransactionActive; /*!< I2C transaction in progress */
static volatile uint8_t  s_u8TxLenByteIdx;    /*!< TX_LEN byte index (0=low, 1=high) */

/* Control flags set by ISR, consumed by MODEM_Process */
static volatile boolean_t s_bCtrlCommit;
static volatile boolean_t s_bCtrlClear;
static volatile boolean_t s_bCtrlAbort;

/* Jump to APP state */
static volatile boolean_t s_bJumpPending;
static volatile boolean_t s_bClearedAfterJump;

/* 1ms tick counter (incremented by timer ISR) */
static volatile uint32_t s_u32TickMs;

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  MODEM RAM variables init
 * @retval None
 */
void MODEM_RamInit(void)
{
    s_u8RegStatus        = STATUS_IDLE;
    s_u8RegError         = ERROR_CODE_OK;
    s_u16RegTxLen        = 0u;
    s_u16RxMailboxIdx    = 0u;
    s_u16TxMailboxIdx    = 0u;
    s_u8SubAddr          = 0u;
    s_bSubAddrValid      = FALSE;
    s_bTransactionActive = FALSE;
    s_u8TxLenByteIdx     = 0u;
    s_bCtrlCommit        = FALSE;
    s_bCtrlClear         = FALSE;
    s_bCtrlAbort         = FALSE;
    s_bJumpPending       = FALSE;
    s_bClearedAfterJump  = FALSE;
    s_u32TickMs          = 0u;

    (void)memset(s_au8RxMailbox, 0, sizeof(s_au8RxMailbox));
    (void)memset(s_au8TxMailbox, 0, sizeof(s_au8TxMailbox));
}

/**
 * @brief  1ms timer interrupt handler
 * @retval None
 */
void MODEM_TimIrqHandler(void)
{
    if (HC32_GetTimUIFStatus())
    {
        HC32_ClrTimUIFStatus();
        s_u32TickMs++;
    }
}

/**
 * @brief  I2C slave interrupt handler
 * @retval None
 */
void MODEM_I2cIrqHandler(void)
{
    uint32_t u32Flags = HSI2C->SSR;

    /* Address valid / repeated start: a transaction is active */
    if (u32Flags & (HSI2C_SLAVE_FLAG_AVF | HSI2C_SLAVE_FLAG_RSF))
    {
        s_bTransactionActive = TRUE;
        s_u8TxLenByteIdx     = 0u;
        (void)HSI2C->SASR; /* Read SASR to clear AVF */
    }

    /* STOP: transaction ended */
    if (u32Flags & HSI2C_SLAVE_FLAG_SDF)
    {
        s_bTransactionActive = FALSE;
        s_bSubAddrValid      = FALSE;
    }

    /* Receive data */
    if (u32Flags & HSI2C_SLAVE_FLAG_RDF)
    {
        uint8_t u8Data;
        if (Ok == HSI2C_SlaveReadData(HSI2C, &u8Data))
        {
            if (!s_bSubAddrValid)
            {
                /* First byte after address is the sub-address */
                s_u8SubAddr     = u8Data;
                s_bSubAddrValid = TRUE;
                if ((s_u8SubAddr >= REG_MAILBOX_START) && (s_u8SubAddr <= REG_MAILBOX_END))
                {
                    s_u16RxMailboxIdx = (uint16_t)(s_u8SubAddr - REG_MAILBOX_START);
                    s_u16TxMailboxIdx = (uint16_t)(s_u8SubAddr - REG_MAILBOX_START);
                }
                else
                {
                    s_u16RxMailboxIdx = 0u;
                    s_u16TxMailboxIdx = 0u;
                }
            }
            else
            {
                /* Route data based on sub-address */
                switch (s_u8SubAddr)
                {
                    case REG_CTRL:
                        if (CTRL_COMMIT == u8Data)
                        {
                            if (STATUS_IDLE == s_u8RegStatus)
                            {
                                s_bCtrlCommit = TRUE;
                            }
                        }
                        else if (CTRL_CLEAR == u8Data)
                        {
                            s_bCtrlClear = TRUE;
                        }
                        else if (CTRL_ABORT == u8Data)
                        {
                            s_bCtrlAbort = TRUE;
                        }
                        break;

                    default:
                        if ((s_u8SubAddr >= REG_MAILBOX_START) && (s_u8SubAddr <= REG_MAILBOX_END))
                        {
                            if (STATUS_IDLE == s_u8RegStatus)
                            {
                                if (s_u16RxMailboxIdx < IAP_MAILBOX_SIZE)
                                {
                                    s_au8RxMailbox[s_u16RxMailboxIdx++] = u8Data;
                                }
                            }
                            /* Else: discard write when not IDLE */
                            s_u8SubAddr++; /* Auto-increment virtual register address */
                        }
                        break;
                }
            }
        }
    }

    /* Transmit data */
    if (u32Flags & HSI2C_SLAVE_FLAG_TDF)
    {
        uint8_t u8TxData = 0x00u;

        switch (s_u8SubAddr)
        {
            case REG_STATUS:
                u8TxData = s_u8RegStatus;
                break;

            case REG_ERROR:
                u8TxData = s_u8RegError;
                break;

            case REG_TX_LEN:
                if (0u == s_u8TxLenByteIdx)
                {
                    u8TxData         = (uint8_t)s_u16RegTxLen;
                    s_u8TxLenByteIdx = 1u;
                }
                else
                {
                    u8TxData = (uint8_t)(s_u16RegTxLen >> 8);
                }
                break;

            default:
                if ((s_u8SubAddr >= REG_MAILBOX_START) && (s_u8SubAddr <= REG_MAILBOX_END))
                {
                    if (s_u16TxMailboxIdx < s_u16RegTxLen)
                    {
                        u8TxData = s_au8TxMailbox[s_u16TxMailboxIdx++];
                    }
                    else
                    {
                        u8TxData = 0x00u;
                    }
                    s_u8SubAddr++; /* Auto-increment virtual register address */
                }
                break;
        }

        HSI2C_SlaveWriteData(HSI2C, u8TxData);
    }

    /* Error flags: clear them */
    if (u32Flags & (HSI2C_SLAVE_FLAG_FEF | HSI2C_SLAVE_FLAG_BEF))
    {
        HSI2C_SlaveFlagClear(HSI2C, HSI2C_SLAVE_FLAG_CLR_ALL);
    }
    else
    {
        HSI2C_SlaveFlagClear(HSI2C, u32Flags & HSI2C_SLAVE_FLAG_CLR_ALL);
    }
}

/**
 * @brief  Set error state
 * @param  [in] u8ErrCode Error code
 * @retval None
 */
static void MODEM_SetError(uint8_t u8ErrCode)
{
    s_u8RegStatus = STATUS_ERROR;
    s_u8RegError  = u8ErrCode;
}

/**
 * @brief  Build response frame in TX MAILBOX
 * @param  [in] u8Cmd          Command code (echo)
 * @param  [in] u8Seq          Sequence number (echo)
 * @param  [in] u8ErrCode      Result code (Payload[0])
 * @param  [in] pu8Payload     Additional response payload (Payload[1..])
 * @param  [in] u16PayloadLen  Length of additional payload
 * @retval None
 */
static void MODEM_BuildResponse(uint8_t u8Cmd, uint8_t u8Seq, uint8_t u8ErrCode,
                                const uint8_t *pu8Payload, uint16_t u16PayloadLen)
{
    uint16_t u16TotalPayloadLen = 1u + u16PayloadLen; /* +1 for result code */
    uint16_t u16CrcOffset;
    uint16_t u16Crc;

    s_au8TxMailbox[HDR_OFFSET_MAGIC0]     = FRAME_MAGIC0;
    s_au8TxMailbox[HDR_OFFSET_MAGIC1]     = FRAME_MAGIC1;
    s_au8TxMailbox[HDR_OFFSET_VERSION]    = IAP_PROTOCOL_VERSION;
    s_au8TxMailbox[HDR_OFFSET_CMD]        = u8Cmd;
    s_au8TxMailbox[HDR_OFFSET_SEQ]        = u8Seq;
    s_au8TxMailbox[HDR_OFFSET_FLAGS]      = 0x00u;
    s_au8TxMailbox[HDR_OFFSET_PAYLOADLEN] = (uint8_t)u16TotalPayloadLen;
    s_au8TxMailbox[HDR_OFFSET_PAYLOADLEN + 1u] = (uint8_t)(u16TotalPayloadLen >> 8);

    s_au8TxMailbox[HDR_OFFSET_PAYLOAD] = u8ErrCode;
    if ((NULL != pu8Payload) && (u16PayloadLen > 0u))
    {
        (void)memcpy(&s_au8TxMailbox[HDR_OFFSET_PAYLOAD + 1u], pu8Payload, u16PayloadLen);
    }

    u16CrcOffset = IAP_HEADER_SIZE + u16TotalPayloadLen;
    u16Crc       = (uint16_t)HC32_CalCrc16(s_au8TxMailbox, 0u, u16CrcOffset);

    s_au8TxMailbox[u16CrcOffset]     = (uint8_t)u16Crc;
    s_au8TxMailbox[u16CrcOffset + 1u] = (uint8_t)(u16Crc >> 8);

    s_u16RegTxLen    = u16CrcOffset + IAP_CRC_SIZE;
    s_u16TxMailboxIdx = 0u; /* Reset read index for host read */
}

/**
 * @brief  MODEM process function, called in main loop
 * @retval en_result_t
 *           - Ok: Jump to APP requested
 *           - OperationInProgress: Normal operation
 */
en_result_t MODEM_Process(void)
{
    /* Handle COMMIT */
    if (s_bCtrlCommit)
    {
        s_bCtrlCommit = FALSE;

        /* Basic frame size check */
        if (s_u16RxMailboxIdx < IAP_FRAME_MIN)
        {
            MODEM_SetError(ERROR_CODE_FRAME);
            return OperationInProgress;
        }

        uint16_t u16PayloadLen = (uint16_t)(s_au8RxMailbox[HDR_OFFSET_PAYLOADLEN] |
                                            ((uint16_t)s_au8RxMailbox[HDR_OFFSET_PAYLOADLEN + 1u] << 8));
        uint16_t u16FrameLen   = (uint16_t)(IAP_HEADER_SIZE + u16PayloadLen + IAP_CRC_SIZE);

        if ((u16PayloadLen > IAP_PAYLOAD_MAX) || (u16FrameLen > IAP_FRAME_MAX) ||
            (s_u16RxMailboxIdx < u16FrameLen))
        {
            MODEM_SetError(ERROR_CODE_FRAME);
            return OperationInProgress;
        }

        /* Validate header */
        if ((s_au8RxMailbox[HDR_OFFSET_MAGIC0] != FRAME_MAGIC0) ||
            (s_au8RxMailbox[HDR_OFFSET_MAGIC1] != FRAME_MAGIC1) ||
            (s_au8RxMailbox[HDR_OFFSET_VERSION] != IAP_PROTOCOL_VERSION) ||
            (s_au8RxMailbox[HDR_OFFSET_FLAGS] != 0x00u))
        {
            MODEM_SetError(ERROR_CODE_FRAME);
            return OperationInProgress;
        }

        /* Validate CRC */
        uint16_t u16CrcOffset = (uint16_t)(IAP_HEADER_SIZE + u16PayloadLen);
        uint16_t u16CrcRecv   = (uint16_t)(s_au8RxMailbox[u16CrcOffset] |
                                           ((uint16_t)s_au8RxMailbox[u16CrcOffset + 1u] << 8));
        uint16_t u16CrcCalc   = (uint16_t)HC32_CalCrc16(s_au8RxMailbox, 0u, u16CrcOffset);

        if (u16CrcRecv != u16CrcCalc)
        {
            MODEM_SetError(ERROR_CODE_CRC);
            return OperationInProgress;
        }

        /* Mark busy */
        s_u8RegStatus = STATUS_BUSY;
        s_u8RegError  = ERROR_CODE_OK;

        uint8_t  u8Cmd  = s_au8RxMailbox[HDR_OFFSET_CMD];
        uint8_t  u8Seq  = s_au8RxMailbox[HDR_OFFSET_SEQ];
        uint8_t *pu8ReqPayload = &s_au8RxMailbox[HDR_OFFSET_PAYLOAD];
        stc_cmd_result_t stcResult;

        switch (u8Cmd)
        {
            case CMD_HANDSHAKE:
                stcResult = CmdHandshake();
                break;

            case CMD_ERASE_FLASH:
                stcResult = CmdEraseFlash(pu8ReqPayload, u16PayloadLen);
                break;

            case CMD_APP_DOWNLOAD:
                stcResult = CmdAppDownload(pu8ReqPayload, u16PayloadLen);
                break;

            case CMD_CRC_FLASH:
                stcResult = CmdCrcFlash(pu8ReqPayload, u16PayloadLen);
                break;

            case CMD_JUMP_TO_APP:
                stcResult = CmdJumpToApp(pu8ReqPayload, u16PayloadLen);
                break;

            default:
                stcResult.u8ErrCode     = ERROR_CODE_UNSUPPORTED;
                stcResult.u16PayloadLen = 0u;
                break;
        }

        MODEM_BuildResponse(u8Cmd, u8Seq, stcResult.u8ErrCode,
                            stcResult.au8Payload, stcResult.u16PayloadLen);

        if (ERROR_CODE_OK == stcResult.u8ErrCode)
        {
            s_u8RegStatus = STATUS_RESP_READY;
        }
        else
        {
            s_u8RegStatus = STATUS_ERROR;
            s_u8RegError  = stcResult.u8ErrCode;
        }
    }

    /* Handle CLEAR */
    if (s_bCtrlClear)
    {
        s_bCtrlClear = FALSE;
        if (STATUS_RESP_READY == s_u8RegStatus)
        {
            if (s_bJumpPending)
            {
                s_bClearedAfterJump = TRUE;
            }
            s_u8RegStatus = STATUS_IDLE;
            s_u8RegError  = ERROR_CODE_OK;
            s_u16RegTxLen = 0u;
        }
    }

    /* Handle ABORT */
    if (s_bCtrlAbort)
    {
        s_bCtrlAbort        = FALSE;
        s_u8RegStatus       = STATUS_IDLE;
        s_u8RegError        = ERROR_CODE_OK;
        s_u16RegTxLen       = 0u;
        s_bJumpPending      = FALSE;
        s_bClearedAfterJump = FALSE;
    }

    /* Jump to APP after CLEAR */
    if (s_bJumpPending && s_bClearedAfterJump)
    {
        s_bJumpPending      = FALSE;
        s_bClearedAfterJump = FALSE;

        /* Delay ~5ms per protocol */
        uint32_t u32StartTick = s_u32TickMs;
        while ((s_u32TickMs - u32StartTick) < 5u)
        {
            ;
        }

        return Ok;
    }

    return OperationInProgress;
}

/**
 * @brief  HANDSHAKE command handler
 * @retval stc_cmd_result_t
 */
static stc_cmd_result_t CmdHandshake(void)
{
    stc_cmd_result_t stcResult;

    stcResult.u8ErrCode     = ERROR_CODE_OK;
    stcResult.au8Payload[0] = IAP_PROTOCOL_VERSION;
    stcResult.au8Payload[1] = (uint8_t)IAP_PAYLOAD_MAX;
    stcResult.au8Payload[2] = (uint8_t)(IAP_PAYLOAD_MAX >> 8);
    stcResult.u16PayloadLen = 3u;

    return stcResult;
}

/**
 * @brief  ERASE_FLASH command handler
 * @param  [in] pu8Payload      Request payload
 * @param  [in] u16PayloadLen   Request payload length
 * @retval stc_cmd_result_t
 */
static stc_cmd_result_t CmdEraseFlash(const uint8_t *pu8Payload, uint16_t u16PayloadLen)
{
    stc_cmd_result_t stcResult;
    uint32_t u32AppSize;
    uint32_t u32SectorCount;
    uint32_t i;

    stcResult.u8ErrCode     = ERROR_CODE_OK;
    stcResult.u16PayloadLen = 0u;

    if (u16PayloadLen != 4u)
    {
        stcResult.u8ErrCode = ERROR_CODE_FRAME;
        return stcResult;
    }

    u32AppSize = ((uint32_t)pu8Payload[0]) |
                 ((uint32_t)pu8Payload[1] << 8) |
                 ((uint32_t)pu8Payload[2] << 16) |
                 ((uint32_t)pu8Payload[3] << 24);

    if ((u32AppSize == 0u) || (u32AppSize > (FLASH_SIZE - BOOT_SIZE)))
    {
        stcResult.u8ErrCode = ERROR_CODE_ADDR;
        return stcResult;
    }

    /* Power-loss protection: mark UPDATE_REQUEST before erasing */
    if (Ok != BootParam_WriteState(BOOT_PARAM_STATE_UPDATE_REQUEST))
    {
        stcResult.u8ErrCode = ERROR_CODE_FLASH;
        return stcResult;
    }

    /* Erase required sectors */
    u32SectorCount = (u32AppSize + FLASH_SECTOR_SIZE - 1u) / FLASH_SECTOR_SIZE;
    for (i = 0u; i < u32SectorCount; i++)
    {
        if (Ok != HC32_FlashEraseSector(APP_ADDR + (i * FLASH_SECTOR_SIZE)))
        {
            stcResult.u8ErrCode = ERROR_CODE_FLASH;
            return stcResult;
        }
    }

    return stcResult;
}

/**
 * @brief  APP_DOWNLOAD command handler
 * @param  [in] pu8Payload      Request payload
 * @param  [in] u16PayloadLen   Request payload length
 * @retval stc_cmd_result_t
 */
static stc_cmd_result_t CmdAppDownload(const uint8_t *pu8Payload, uint16_t u16PayloadLen)
{
    stc_cmd_result_t stcResult;
    uint32_t u32FlashAddr;
    uint16_t u16DataLen;

    stcResult.u8ErrCode     = ERROR_CODE_OK;
    stcResult.u16PayloadLen = 0u;

    if (u16PayloadLen < 4u)
    {
        stcResult.u8ErrCode = ERROR_CODE_FRAME;
        return stcResult;
    }

    u32FlashAddr = ((uint32_t)pu8Payload[0]) |
                   ((uint32_t)pu8Payload[1] << 8) |
                   ((uint32_t)pu8Payload[2] << 16) |
                   ((uint32_t)pu8Payload[3] << 24);
    u16DataLen   = u16PayloadLen - 4u;

    if ((u32FlashAddr < APP_ADDR) ||
        ((u32FlashAddr + u16DataLen) > (FLASH_START_ADDR + FLASH_SIZE)))
    {
        stcResult.u8ErrCode = ERROR_CODE_ADDR;
        return stcResult;
    }

    if (Ok != HC32_FlashWriteBytes(u32FlashAddr, (uint8_t *)&pu8Payload[4], u16DataLen))
    {
        stcResult.u8ErrCode = ERROR_CODE_FLASH;
        return stcResult;
    }

    return stcResult;
}

/**
 * @brief  CRC_FLASH command handler
 * @param  [in] pu8Payload      Request payload
 * @param  [in] u16PayloadLen   Request payload length
 * @retval stc_cmd_result_t
 */
static stc_cmd_result_t CmdCrcFlash(const uint8_t *pu8Payload, uint16_t u16PayloadLen)
{
    stc_cmd_result_t stcResult;
    uint32_t u32AppSize;
    uint16_t u16Crc;

    stcResult.u8ErrCode     = ERROR_CODE_OK;
    stcResult.u16PayloadLen = 0u;

    if (u16PayloadLen != 4u)
    {
        stcResult.u8ErrCode = ERROR_CODE_FRAME;
        return stcResult;
    }

    u32AppSize = ((uint32_t)pu8Payload[0]) |
                 ((uint32_t)pu8Payload[1] << 8) |
                 ((uint32_t)pu8Payload[2] << 16) |
                 ((uint32_t)pu8Payload[3] << 24);

    if ((u32AppSize == 0u) || (u32AppSize > (FLASH_SIZE - BOOT_SIZE)))
    {
        stcResult.u8ErrCode = ERROR_CODE_ADDR;
        return stcResult;
    }

    u16Crc = (uint16_t)HC32_CalCrc16((uint8_t *)APP_ADDR, 0u, u32AppSize);

    /* Store app_size and app_crc to boot parameter area */
    if (Ok != BootParam_WriteAppInfo(u32AppSize, u16Crc))
    {
        stcResult.u8ErrCode = ERROR_CODE_FLASH;
        return stcResult;
    }

    stcResult.au8Payload[0] = (uint8_t)u16Crc;
    stcResult.au8Payload[1] = (uint8_t)(u16Crc >> 8);
    stcResult.u16PayloadLen = 2u;

    return stcResult;
}

/**
 * @brief  JUMP_TO_APP command handler
 * @param  [in] pu8Payload      Request payload
 * @param  [in] u16PayloadLen   Request payload length
 * @retval stc_cmd_result_t
 */
static stc_cmd_result_t CmdJumpToApp(const uint8_t *pu8Payload, uint16_t u16PayloadLen)
{
    stc_cmd_result_t stcResult;
    stc_boot_param_t stcParam;
    uint32_t u32StackTop;
    uint16_t u16Crc;

    (void)pu8Payload;

    stcResult.u8ErrCode     = ERROR_CODE_OK;
    stcResult.u16PayloadLen = 0u;

    if (u16PayloadLen != 0u)
    {
        stcResult.u8ErrCode = ERROR_CODE_FRAME;
        return stcResult;
    }

    BootParam_Read(&stcParam);

    /* Boot self-verification: re-calculate CRC and compare */
    u16Crc = (uint16_t)HC32_CalCrc16((uint8_t *)APP_ADDR, 0u, stcParam.app_size);
    if (u16Crc != (uint16_t)stcParam.app_crc)
    {
        stcResult.u8ErrCode = ERROR_CODE_APP_INVALID;
        return stcResult;
    }

    /* Vector table sanity check */
    u32StackTop = *((volatile uint32_t *)APP_ADDR);
    if ((u32StackTop < SRAM_BASE) || (u32StackTop > (SRAM_BASE + RAM_SIZE)))
    {
        stcResult.u8ErrCode = ERROR_CODE_APP_INVALID;
        return stcResult;
    }

    /* Mark image as pending (single attempt, no retry) */
    if (Ok != BootParam_WriteState(BOOT_PARAM_STATE_IMAGE_PENDING))
    {
        stcResult.u8ErrCode = ERROR_CODE_FLASH;
        return stcResult;
    }

    /* Signal MODEM_Process to jump after host CLEAR */
    s_bJumpPending      = TRUE;
    s_bClearedAfterJump = FALSE;

    return stcResult;
}

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
