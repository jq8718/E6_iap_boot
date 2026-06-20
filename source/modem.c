/**
 *******************************************************************************
 * @file  modem.c
 * @brief This file provides firmware functions of MODEM
 @verbatim
   Change Logs:
   Date             Author          Notes
   2025-03-25       MADS            First version
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
/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
/**
 * @brief  Packet status enumeration
 */
typedef enum
{
    FRAME_RECV_IDLE_STATUS   = 0x00,
    FRAME_RECV_HEADER_STATUS = 0x01,
    FRAME_RECV_DATA_STATUS   = 0x02,
    FRAME_RECV_PROC_STATUS   = 0x03,
} en_frame_recv_status_t;

/**
 * @brief  Packet status enumeration
 */
typedef enum
{
    PACKET_ACK_OK               = 0x00,
    PACKET_ACK_ERROR            = 0x01,
    PACKET_ACK_ABORT            = 0x02,
    PACKET_ACK_TIMEOUT          = 0x03,
    PACKET_ACK_ADDR_ERROR       = 0x04,
    PACKET_ACK_FLASH_SIZE_ERROR = 0x05,
} en_packet_status_t;

/**
 * @brief  Packet command enumeration
 */
typedef enum
{
    PACKET_CMD_HANDSHAKE    = 0x20,
    PACKET_CMD_JUMP_TO_APP  = 0x21,
    PACKET_CMD_APP_DOWNLOAD = 0x22,
    PACKET_CMD_APP_UPLOAD   = 0x23,
    PACKET_CMD_ERASE_FLASH  = 0x24,
    PACKET_CMD_CRC_FLASH    = 0x25,
    PACKET_CMD_START_UPDATE = 0x26,
} en_packet_cmd_t;

/**
 * @brief  Packet command type enumeration
 */
typedef enum
{
    PACKET_CMD_TYPE_CONTROL = 0x11,
    PACKET_CMD_TYPE_DATA    = 0x12,
} en_packet_cmd_type_t;
/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define FRAME_HEAD_L 0x6Du
#define FRAME_HEAD_H 0xACu

/* Frame and packet size */
#define FRAME_SHELL_SIZE             8
#define PACKET_INSTRUCT_SEGMENT_SIZE 10
#define PACKET_DATA_SEGMENT_SIZE     512
#define FRAME_MIN_SIZE               PACKET_INSTRUCT_SEGMENT_SIZE
#define FRAME_MAX_SIZE               (PACKET_DATA_SEGMENT_SIZE + PACKET_INSTRUCT_SEGMENT_SIZE + FRAME_SHELL_SIZE)

/* Frame structure defines */
#define FRAME_HEAD_H_INDEX 0x00
#define FRAME_HEAD_L_INDEX 0x01
#define FRAME_NUM_INDEX    0x02
#define FRAME_XORNUM_INDEX 0x03
#define FRAME_LENGTH_INDEX 0x04
#define FRAME_PACKET_INDEX 0x06

#define FRAME_RECV_TIMEOUT 5 /* ms */
#define FRAME_NUM_XOR_BYTE 0xFF

/* Packet structure defines */
#define PACKET_CMD_INDEX       (FRAME_PACKET_INDEX + 0x00)
#define PACKET_TYPE_INDEX      (FRAME_PACKET_INDEX + 0x01)
#define PACKET_RESULT_INDEX    (FRAME_PACKET_INDEX + 0x01)
#define PACKET_ADDRESS_INDEX   (FRAME_PACKET_INDEX + 0x02)
#define PACKET_FLASH_CRC_INDEX (FRAME_PACKET_INDEX + 0x0A)
#define PACKET_DATA_INDEX      (FRAME_PACKET_INDEX + PACKET_INSTRUCT_SEGMENT_SIZE)
/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void        MODEM_SendFrame(uint8_t *u8TxBuff, uint16_t u16TxLength);
static uint16_t    MODEM_FlashPageNum(uint32_t u32Size);
static void        MODEM_UartSendData(uint8_t *pu8TxBuff, uint16_t u16Length);
static en_result_t MODEM_FlashEraseSector(uint32_t u32Addr);
static en_result_t MODEM_FlashWriteBytes(uint32_t u32Addr, const uint8_t *pu8WriteBuff, uint32_t u32ByteLength);
static void        MODEM_FlashReadBytes(uint32_t u32Addr, uint8_t *pu8ReadBuff, uint32_t u32ByteLength);
/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static uint8_t  u8FrameData[FRAME_MAX_SIZE]; /* 帧存储缓存 */
static uint32_t u32FrameDataIndex;           /* 帧存储缓存索引 */
static uint32_t u32FrameSize;

static uint32_t               u32FrameRecvOverTime; /* 帧接收超时计数器，在(1ms)定时器中断中计数，在串口中断中清零 */
static en_frame_recv_status_t enFrameRecvStatus;
/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @brief  应答帧处理
 * @param  [in] u8TxBuff 发送缓存指针
 * @param  [in] u16TxLength 待发送数据长度
 * @retval None
 */
static void MODEM_SendFrame(uint8_t *u8TxBuff, uint16_t u16TxLength)
{
    uint16_t u16Crc16;

    u8TxBuff[FRAME_LENGTH_INDEX]                   = u16TxLength & 0x00FF; /* 存储数据包长度 */
    u8TxBuff[FRAME_LENGTH_INDEX + 1]               = u16TxLength >> 8;
    u16Crc16                                       = HC32_CalCrc16(u8TxBuff, FRAME_PACKET_INDEX, u16TxLength); /* 计算数据包的CRC校验值 */
    u8TxBuff[FRAME_PACKET_INDEX + u16TxLength]     = u16Crc16 & 0x00FF;                                        /* 存储CRC至数据包 */
    u8TxBuff[FRAME_PACKET_INDEX + u16TxLength + 1] = u16Crc16 >> 8;
    MODEM_UartSendData(&u8TxBuff[0], FRAME_PACKET_INDEX + u16TxLength + 2); /* 发送应答帧 */
}

/**
 * @brief  上位机数据帧解析及处理
 * @retval en_result_t
 *           - Ok: APP程序升级完成，并接受到跳转至APP命令
 *           - OperationInProgress: 数据处理中
 *           - Error: 通讯错误
 */
en_result_t MODEM_Process(void)
{
    uint8_t  u8Cmd, u8FlashAddrValid, u8Cnt, u8Ret;
    uint16_t u16DataLength, u16PageNum, u16Ret;
    uint32_t u32FlashAddr, u32FlashLength, u32Temp;

    if (enFrameRecvStatus == FRAME_RECV_PROC_STATUS) /* 有数据帧待处理, enFrameRecvStatus值在串口中断中调整 */
    {
        u8Cmd = u8FrameData[PACKET_CMD_INDEX];                      /* 获取帧指令码 */
        if (PACKET_CMD_TYPE_DATA == u8FrameData[PACKET_TYPE_INDEX]) /* 如果是数据指令 */
        {
            u8FlashAddrValid = 0u;

            u32FlashAddr = u8FrameData[PACKET_ADDRESS_INDEX] + /* 读取地址值 */
                           (u8FrameData[PACKET_ADDRESS_INDEX + 1] << 8) + (u8FrameData[PACKET_ADDRESS_INDEX + 2] << 16)
                           + (u8FrameData[PACKET_ADDRESS_INDEX + 3] << 24);
            if ((u32FlashAddr >= (FLASH_START_ADDR + BOOT_SIZE)) && (u32FlashAddr < (FLASH_START_ADDR + FLASH_SIZE))) /* 如果地址值在有效范围内 */
            {
                u8FlashAddrValid = 1u; /* 标记地址有效 */
            }
        }

        switch (u8Cmd) /* 根据指令码跳转执行 */
        {
            case PACKET_CMD_HANDSHAKE:                                          /* 握手帧 指令码 */
                u8FrameData[PACKET_RESULT_INDEX] = PACKET_ACK_OK;               /* 返回状态为：正确 */
                MODEM_SendFrame(&u8FrameData[0], PACKET_INSTRUCT_SEGMENT_SIZE); /* 发送应答帧给上位机 */
                break;
            case PACKET_CMD_ERASE_FLASH:                     /* 擦除FLASH 指令码 */
                if ((u32FlashAddr % FLASH_SECTOR_SIZE) != 0) /* 如果擦除地址不是页首地址 */
                {
                    u8FlashAddrValid = 0u; /* 标记地址无效 */
                }

                if (1u == u8FlashAddrValid) /* 如果地址有效 */
                {
                    u32Temp = u8FrameData[PACKET_DATA_INDEX] + /* 获取待擦除FLASH尺寸 */
                              (u8FrameData[PACKET_DATA_INDEX + 1] << 8) + (u8FrameData[PACKET_DATA_INDEX + 2] << 16)
                              + (u8FrameData[PACKET_DATA_INDEX + 3] << 24);
                    u16PageNum = MODEM_FlashPageNum(u32Temp);    /* 计算需擦除多少页 */
                    for (u8Cnt = 0; u8Cnt < u16PageNum; u8Cnt++) /* 根据需要擦除指定数量的扇区 */
                    {
                        u8Ret = MODEM_FlashEraseSector(u32FlashAddr + (u8Cnt * FLASH_SECTOR_SIZE));
                        if (Ok != u8Ret) /* 如果擦除失败，反馈上位机错误代码 */
                        {
                            u8FrameData[PACKET_RESULT_INDEX] = PACKET_ACK_ERROR;
                            break;
                        }
                    }
                    if (Ok == u8Ret) /* 如果全部擦除成功，反馈上位机成功 */
                    {
                        u8FrameData[PACKET_RESULT_INDEX] = PACKET_ACK_OK;
                    }
                    else /* 如果擦除失败，反馈上位机错误超时标志 */
                    {
                        u8FrameData[PACKET_RESULT_INDEX] = PACKET_ACK_TIMEOUT;
                    }
                }
                else /* 地址无效，反馈上位机地址错误 */
                {
                    u8FrameData[PACKET_RESULT_INDEX] = PACKET_ACK_ADDR_ERROR;
                }
                MODEM_SendFrame(&u8FrameData[0], PACKET_INSTRUCT_SEGMENT_SIZE); /* 发送应答帧到上位机 */
                break;
            case PACKET_CMD_APP_DOWNLOAD:   /* 数据下载 指令码 */
                if (1u == u8FlashAddrValid) /* 如果地址有效 */
                {
                    u16DataLength = u8FrameData[FRAME_LENGTH_INDEX] + (u8FrameData[FRAME_LENGTH_INDEX + 1] << 8)
                                    - PACKET_INSTRUCT_SEGMENT_SIZE; /* 获取数据包中的数据长度(不包含指令码指令类型等等) */
                    if (u16DataLength > PACKET_DATA_SEGMENT_SIZE)   /* 如果数据长度大于最大长度 */
                    {
                        u16DataLength = PACKET_DATA_SEGMENT_SIZE; /* 设置数据最大值 */
                    }
                    u8Ret = MODEM_FlashWriteBytes(u32FlashAddr, (uint8_t *)&u8FrameData[PACKET_DATA_INDEX], u16DataLength); /* 把所有数据写入FLASH */
                    if (Ok != u8Ret)                                                                                        /* 如果写数据失败 */
                    {
                        u8FrameData[PACKET_RESULT_INDEX] = PACKET_ACK_ERROR; /* 反馈上位机错误 标志 */
                    }
                    else /* 如果写数据成功 */
                    {
                        u8FrameData[PACKET_RESULT_INDEX] = PACKET_ACK_OK; /* 反馈上位机成功 标志 */
                    }
                }
                else /* 如果地址无效 */
                {
                    u8FrameData[PACKET_RESULT_INDEX] = PACKET_ACK_ADDR_ERROR; /* 反馈上位机地址错误 */
                }
                MODEM_SendFrame(&u8FrameData[0], PACKET_INSTRUCT_SEGMENT_SIZE); /* 发送应答帧到上位机 */
                break;
            case PACKET_CMD_CRC_FLASH:      /* 查询FLASH校验值 指令码 */
                if (1u == u8FlashAddrValid) /* 如果地址有效 */
                {
                    u32FlashLength = u8FrameData[PACKET_DATA_INDEX] + (u8FrameData[PACKET_DATA_INDEX + 1] << 8) + (u8FrameData[PACKET_DATA_INDEX + 2] << 16)
                                     + (u8FrameData[PACKET_DATA_INDEX + 3] << 24);         /* 获取待校验FLASH大小 */
                    if ((u32FlashLength + u32FlashAddr) > (FLASH_START_ADDR + FLASH_SIZE)) /* 如果FLASH长度超出有效范围 */
                    {
                        u8FrameData[PACKET_RESULT_INDEX] = PACKET_ACK_FLASH_SIZE_ERROR; /* 反馈上位机FLASH尺寸错误 */
                    }
                    else
                    {
                        u16Ret = HC32_CalCrc16(((unsigned char *)u32FlashAddr), 0, u32FlashLength); /* 读取FLASH指定区域的值并计算crc值 */
                        u8FrameData[PACKET_FLASH_CRC_INDEX]     = (uint8_t)u16Ret;                  /* 把crc值存储到应答帧 */
                        u8FrameData[PACKET_FLASH_CRC_INDEX + 1] = (uint8_t)(u16Ret >> 8);
                        u8FrameData[PACKET_RESULT_INDEX]        = PACKET_ACK_OK; /* 反馈上位机成功 标志 */
                    }
                }
                else /* 如果地址无效 */
                {
                    u8FrameData[PACKET_RESULT_INDEX] = PACKET_ACK_ADDR_ERROR; /* 反馈上位机地址错误 */
                }
                MODEM_SendFrame(&u8FrameData[0], PACKET_INSTRUCT_SEGMENT_SIZE + 2); /* 发送应答帧到上位机 */
                break;
            case PACKET_CMD_JUMP_TO_APP:                                        /* 跳转至APP 指令码 */
                MODEM_FlashEraseSector(BOOT_PARA_ADDR);                         /* 擦除BOOT parameter 扇区 */
                u8FrameData[PACKET_RESULT_INDEX] = PACKET_ACK_OK;               /* 反馈上位机成功 */
                MODEM_SendFrame(&u8FrameData[0], PACKET_INSTRUCT_SEGMENT_SIZE); /* 发送应答帧到上位机 */
                return Ok;                                                      /* APP更新完成，返回OK，接下来执行跳转函数，跳转至APP */
            case PACKET_CMD_APP_UPLOAD:                                         /* 数据上传 */
                if (1u == u8FlashAddrValid)                                     /* 如果地址有效 */
                {
                    u32Temp = u8FrameData[PACKET_DATA_INDEX] + (u8FrameData[PACKET_DATA_INDEX + 1] << 8) + (u8FrameData[PACKET_DATA_INDEX + 2] << 16)
                              + (u8FrameData[PACKET_DATA_INDEX + 3] << 24); /* 读取上传数据长度 */
                    if (u32Temp > PACKET_DATA_SEGMENT_SIZE)                 /* 如果数据长度大于最大值 */
                    {
                        u32Temp = PACKET_DATA_SEGMENT_SIZE; /* 设置数据长度为最大值 */
                    }
                    MODEM_FlashReadBytes(u32FlashAddr, (uint8_t *)&u8FrameData[PACKET_DATA_INDEX], u32Temp); /* 读FLASH数据 */
                    u8FrameData[PACKET_RESULT_INDEX] = PACKET_ACK_OK;                                        /* 反馈上位机成功 标志 */
                    MODEM_SendFrame(&u8FrameData[0], PACKET_INSTRUCT_SEGMENT_SIZE + u32Temp);                /* 发送应答帧到上位机 */
                }
                else /* 如果地址无效 */
                {
                    u8FrameData[PACKET_RESULT_INDEX] = PACKET_ACK_ADDR_ERROR;       /* 反馈上位机地址错误 标志 */
                    MODEM_SendFrame(&u8FrameData[0], PACKET_INSTRUCT_SEGMENT_SIZE); /* 发送应答帧到上位机 */
                }
                break;
            case PACKET_CMD_START_UPDATE:                                       /* 启动APP更新(此指令正常在APP程序中调用) */
                u8FrameData[PACKET_RESULT_INDEX] = PACKET_ACK_OK;               /* 反馈上位机成功 标志 */
                MODEM_SendFrame(&u8FrameData[0], PACKET_INSTRUCT_SEGMENT_SIZE); /* 发送应答帧到上位机 */
                break;
        }
        enFrameRecvStatus = FRAME_RECV_IDLE_STATUS; /* 帧数据处理完成，帧接收状态恢复到空闲状态 */
    }

    return OperationInProgress; /* 返回，APP更新中 */
}

/**
 * @brief  串口中断，接收上位机发送帧
 * @retval None
 */
void MODEM_UartIrqHandler(void)
{
    uint8_t  recvData;
    uint16_t u16Crc16;

    if (HC32_GetUartErrStatus()) /* 获取串口异常标志位 */
    {
        HC32_ClrUartErrStatus(); /* 清除串口异常标志位 */
    }

    if (HC32_GetUartRCStatus()) /* 获取串口数据接收标志位 */
    {
        HC32_ClrUartRCStatus(); /* 清除串口数据接收标志位 */

        u32FrameRecvOverTime = 0;                  /* 帧接收超时计数器，清零 */
        recvData             = HC32_GetUartBuff(); /* 获取串口接收数据 */
        switch (enFrameRecvStatus)
        {
            case FRAME_RECV_IDLE_STATUS:      /* 当前处于空闲状态 */
                if (recvData == FRAME_HEAD_L) /* 收到帧头第一个字节 */
                {
                    u8FrameData[FRAME_HEAD_H_INDEX] = recvData;                 /* 保存数据 */
                    enFrameRecvStatus               = FRAME_RECV_HEADER_STATUS; /* 帧接收进入下一状态:  空闲状态 */
                }
                break;
            case FRAME_RECV_HEADER_STATUS:    /* 当前处于接收帧头状态 */
                if (recvData == FRAME_HEAD_H) /* 收到帧头第二个字节 */
                {
                    u8FrameData[FRAME_HEAD_L_INDEX] = recvData;               /* 保存数据 */
                    u32FrameDataIndex               = FRAME_NUM_INDEX;        /* 数组下标从帧头的下一位置开始计数 */
                    enFrameRecvStatus               = FRAME_RECV_DATA_STATUS; /* 帧接收进入下一状态:  接收帧数据状态 */
                }
                else if (recvData == FRAME_HEAD_L) /* 收到帧头第一个字节 */
                {
                    u8FrameData[FRAME_HEAD_H_INDEX] = recvData;                 /* 保存数据 */
                    enFrameRecvStatus               = FRAME_RECV_HEADER_STATUS; /* 帧接收进入下一状态 */
                }
                else /* 数据错误 */
                {
                    enFrameRecvStatus = FRAME_RECV_IDLE_STATUS; /* 帧接收恢复到初始状态:  空闲状态 */
                }
                break;
            case FRAME_RECV_DATA_STATUS: /* 当前处于接收帧数据状态 */
                u8FrameData[u32FrameDataIndex++] = recvData;
                if (u32FrameDataIndex == (FRAME_NUM_INDEX + 2)) /* 已经接收到数据帧序号及校验值 */
                {
                    if ((u8FrameData[FRAME_NUM_INDEX] != (u8FrameData[FRAME_XORNUM_INDEX] ^ FRAME_NUM_XOR_BYTE))) /* 数据帧序号及校验值不匹配 */
                    {
                        enFrameRecvStatus = FRAME_RECV_IDLE_STATUS; /* 帧接收恢复到初始状态 */
                        return;                                     /* 错误返回 */
                    }
                }
                else if (u32FrameDataIndex == (FRAME_LENGTH_INDEX + 2)) /* 已经收到包长度数据 */
                {
                    u32FrameSize = u8FrameData[FRAME_LENGTH_INDEX] + (u8FrameData[FRAME_LENGTH_INDEX + 1] << 8) + FRAME_SHELL_SIZE; /* 计算此帧的长度 */
                    if ((u32FrameSize < FRAME_MIN_SIZE) || (u32FrameSize > FRAME_MAX_SIZE)) /* 帧长度不在有效范围内 */
                    {
                        enFrameRecvStatus = FRAME_RECV_IDLE_STATUS; /* 帧接收恢复到初始状态 */
                        return;                                     /* 错误返回 */
                    }
                }
                else if ((u32FrameDataIndex > (FRAME_LENGTH_INDEX + 2)) && (u32FrameDataIndex == u32FrameSize)) /* 帧数据接收完毕 */
                {
                    u16Crc16 = u8FrameData[u32FrameDataIndex - 2] + (u8FrameData[u32FrameDataIndex - 1] << 8);
                    if (HC32_CalCrc16(u8FrameData, FRAME_PACKET_INDEX, (u32FrameSize - FRAME_SHELL_SIZE)) == u16Crc16) /* 如果CRC校验通过 */
                    {
                        enFrameRecvStatus = FRAME_RECV_PROC_STATUS; /* 帧接收进入下一状态:  帧处理状态 */
                    }
                    else /* 校验失败 */
                    {
                        enFrameRecvStatus = FRAME_RECV_IDLE_STATUS; /* 帧接收恢复到初始状态 */
                        return;                                     /* 错误返回 */
                    }
                }
                break;
            case FRAME_RECV_PROC_STATUS: /* 当前处于帧处理状态 */
                break;
        }
    }
}

/**
 * @brief  定时器中断函数，1ms中断一次，用于监测串口数据接收超时，及帧数据处理超时
 * @retval None
 */
void MODEM_TimIrqHandler(void)
{
    if (HC32_GetTimUIFStatus()) /* 获取定时器溢出中断标志位 */
    {
        HC32_ClrTimUIFStatus(); /* 清除定时器溢出中断标志位 */

        u32FrameRecvOverTime++;
        if ((enFrameRecvStatus == FRAME_RECV_HEADER_STATUS) || (enFrameRecvStatus == FRAME_RECV_DATA_STATUS)) /* 处于帧接收过程中 */
        {
            if (u32FrameRecvOverTime++ > 10) /* 超过10ms没有收到到数据，异常 */
            {
                enFrameRecvStatus = FRAME_RECV_IDLE_STATUS; /* 帧接收恢复到初始状态 */
            }
        }
        else if (enFrameRecvStatus == FRAME_RECV_PROC_STATUS) /* 处于帧处理状态 */
        {
            if (u32FrameRecvOverTime++ > 4500) /* 超过4.5s没有收到到数据，异常 (上位机超过5s没收到应答帧，会重发数据帧) */
            {
                enFrameRecvStatus = FRAME_RECV_IDLE_STATUS; /* 帧接收恢复到初始状态 */
            }
        }
    }
}

/**
 * @brief  MODEM文件中相关变量参数初始化
 * @retval None
 */
void MODEM_RamInit(void)
{
    uint32_t i;

    enFrameRecvStatus = FRAME_RECV_IDLE_STATUS; /* 帧状态初始化为空闲状态 */

    for (i = 0; i < FRAME_MAX_SIZE; i++)
    {
        u8FrameData[i] = 0; /* 帧数据缓存初始化为零 */
    }

    u32FrameDataIndex = 0; /* 帧缓存数组索引值初始化为零 */
}

/**
 * @brief  串口发送数据
 * @param  [in] pu8TxBuff 地址指针
 * @param  [in] u16Length 字节长度
 * @retval None
 */
static void MODEM_UartSendData(uint8_t *pu8TxBuff, uint16_t u16Length)
{
    while (u16Length--)
    {
        HC32_UartSendByte(*pu8TxBuff);
        pu8TxBuff++;
    }
}

/**
 * @brief  FLASH扇区擦除
 * @param  [in] u32Addr 所擦除扇区内的地址
 * @retval en_result_t
 *           - Ok: 擦除成功
 *           - ErrorInvalidParameter: 无效参数
 *           - ErrorTimeout: 操作超时
 */
static en_result_t MODEM_FlashEraseSector(uint32_t u32Addr)
{
    en_result_t enRet = Ok;

    if (u32Addr > (FLASH_START_ADDR + FLASH_SIZE)) /* 判断地址有效性 */
    {
        return ErrorInvalidParameter;
    }

    if ((u32Addr % 4) != 0)
    {
        u32Addr = (u32Addr / FLASH_SECTOR_SIZE) * FLASH_SECTOR_SIZE;
    }

    enRet = HC32_FlashEraseSector(u32Addr);

    return enRet;
}

/**
 * @brief  计算有多少sector页待擦除
 * @param  [in] u32Size 大小
 * @retval Sector number
 */
static uint16_t MODEM_FlashPageNum(uint32_t u32Size)
{
    uint16_t u32PageNum = u32Size / FLASH_SECTOR_SIZE;

    if ((u32Size % FLASH_SECTOR_SIZE) != 0)
    {
        u32PageNum += 1u;
    }

    return u32PageNum;
}

/**
 * @brief  FLASH写数据
 * @param  [in] u32Addr 写FLASH首地址
 * @retval en_result_t
 *           - Ok: 擦除成功
 *           - ErrorTimeout: 操作超时
 */
static en_result_t MODEM_FlashWriteBytes(uint32_t u32Addr, const uint8_t *pu8WriteBuff, uint32_t u32ByteLength)
{
    return HC32_FlashWriteBytes(u32Addr, (uint8_t *)pu8WriteBuff, u32ByteLength);
}

/**
 * @brief  FLASH读数据
 * @param  [in] u32Addr 读首地址
 * @param  [in] *pu8ReadBuff 数据指针
 * @param  [in] u32ByteLength 数据长度
 * @retval None
 */
static void MODEM_FlashReadBytes(uint32_t u32Addr, uint8_t *pu8ReadBuff, uint32_t u32ByteLength)
{
    HC32_FlashReadBytes(u32Addr, pu8ReadBuff, u32ByteLength);
}
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
