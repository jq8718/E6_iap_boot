/**
 *******************************************************************************
 * @file  lpuart.h
 * @brief This file contains all the functions prototypes of the LPUART driver
 *        library
 @verbatim
   Change Logs:
   Date             Author          Notes
   2024-09-18       MADS            First version
   2025-07-08       MADS            Add u32BaudRateGenSelect and
                                    modify funciton and macro etc
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2024~2025, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

#ifndef __LPUART_H__
#define __LPUART_H__

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
 * @addtogroup DDL_LPUART LPUART模块驱动库
 * @{
 */
/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup LPUART_Global_Types LPUART全局类型定义
 * @{
 */

/**
 * @brief  LPUART通道Mode1和Mode3波特率计算参数
 * @note   当stc_lpuart_init_t结构体中u32BaudRateGenSelect选择为LPUART_BAUD_NORMAL时需配置
 */
typedef struct
{
    uint32_t u32SclkSelect; /*!< 传输时钟源选择 @ref LPUART_SCLK_Select */
    uint32_t u32Sclk;       /*!< SCLK 时钟频率值 单位Hz */
    uint32_t u32Baud;       /*!< 波特率 */
} stc_lpuart_baud_t;

/**
 * @brief  LPUART LPUART初始化配置结构体
 */
typedef struct
{
    uint32_t          u32TransMode;         /*!< 数据传输方式配置 @ref LPUART_Trans_Mode_Select */
    uint32_t          u32FrameLength;       /*!< 数据帧长度8/9bits @ref LPUART_Frame_Len */
    uint32_t          u32Parity;            /*!< 校验方式 @ref LPUART_Parity_Config */
    uint32_t          u32StopBits;          /*!< 停止位长度 @ref LPUART_Stop_Len_Config */
    uint32_t          u32HwControl;         /*!< 硬件流控选择 @ref LPUART_HW_Flow_Control */
    uint32_t          u32BaudRateGenSelect; /*!< 波特率产生方式选择 @ref LPUART_Baud_Rate_Gen_Select */
    stc_lpuart_baud_t stcBaudRate;          /*!< 波特率配置 */
} stc_lpuart_init_t;

/**
 * @}
 */
/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup LPUART_Global_Macros LPUART全局宏定义
 * @{
 */

/**
 * @defgroup LPUART_Trans_Mode_Select LPUART传输模式选择
 * @{
 */
#define LPUART_MODE_TX       (0x0u)                                        /*!< 发送 */
#define LPUART_MODE_RX       (LPUART_SCON_REN_Msk)                         /*!< 同步模式接收 */
#define LPUART_MODE_TX_RX    (LPUART_SCON_REN_Msk)                         /*!< 异步模式接收/发送 */
#define LPUART_MODE_HD_TX_RX (LPUART_SCON_REN_Msk | LPUART_SCON_HDSEL_Msk) /*!< 异步模式单线半双工接收/发送 */
/**
 * @}
 */

/** @defgroup LPUART_Parity_Config LPUART奇偶校验配置 仅模式3（含奇偶校验位时）设置有效
 * @{
 */
#define LPUART_B8_MULTI_DATA_OR_ADDR (0x00u << LPUART_SCON_B8CONT_Pos) /*!< 多机模式时，通过读写SBUF[8]决定帧为数据帧或地址帧 */
#define LPUART_B8_PARITY_EVEN        (0x01u << LPUART_SCON_B8CONT_Pos) /*!< 偶校验 */
#define LPUART_B8_PARITY_ODD         (0x02u << LPUART_SCON_B8CONT_Pos) /*!< 奇校验 */
/**
 * @}
 */

/** @defgroup LPUART_Frame_Len LPUART帧长配置
 * @{
 */
#define LPUART_FRAME_LEN_8B_NOPAR (0x1u << LPUART_SCON_SM_Pos) /*!< 模式1 数据帧长8Bits 无校验位 */
#define LPUART_FRAME_LEN_8B_PAR   (0x3u << LPUART_SCON_SM_Pos) /*!< 模式3 数据帧长9Bits 含校验位 */
/**
 * @}
 */

/**
 * @defgroup LPUART_Stop_Len_Config LPUART Stop位长度配置
 * @{
 */
#define LPUART_STOPBITS_1   (0x00u << LPUART_SCON_STOPBIT_Pos) /*!< 1位停止位 */
#define LPUART_STOPBITS_1P5 (0x01u << LPUART_SCON_STOPBIT_Pos) /*!< 1.5位停止位 */
#define LPUART_STOPBITS_2   (0x02u << LPUART_SCON_STOPBIT_Pos) /*!< 2位停止位 */
/**
 * @}
 */

/**
 * @defgroup LPUART_SCLK_Select LPUART传输时钟选择
 * @{
 */
#define LPUART_SCLK_SEL_PCLK (0x00u << LPUART_SCON_SCLKSEL_Pos) /*!< PCLK */
#define LPUART_SCLK_SEL_XTL  (0x02u << LPUART_SCON_SCLKSEL_Pos) /*!< 外部低速晶振 */
#define LPUART_SCLK_SEL_RCL  (0x03u << LPUART_SCON_SCLKSEL_Pos) /*!< 内部低速晶振 */
/**
 * @}
 */

/** @defgroup LPUART_HW_Flow_Control LPUART硬件流控配置
 * @{
 */
#define LPUART_HWCONTROL_NONE    (0x00u)                                         /*!< 无硬件流控 */
#define LPUART_HWCONTROL_RTS     (LPUART_SCON_RTSEN_Msk)                         /*!< RTS使能 */
#define LPUART_HWCONTROL_CTS     (LPUART_SCON_CTSEN_Msk)                         /*!< CTS使能 */
#define LPUART_HWCONTROL_RTS_CTS (LPUART_SCON_CTSEN_Msk | LPUART_SCON_RTSEN_Msk) /*!< RTS/CTS 使能 */
/**
 * @}
 */

/**
 * @defgroup LPUART_Baud_Rate_Gen_Select LPUART XTL为32768时的波特率设定
 * @{
 */
#define LPUART_BAUD_NORMAL   (0x00u)                         /*!< 用OVER和SCNT产生波特率 */
#define LPUART_XTL_BAUD_9600 (0x02u << LPUART_BSEL_BSEL_Pos) /*!< 时钟源是XTL，由调制生成9600波特率 */
#define LPUART_XTL_BAUD_4800 (0x03u << LPUART_BSEL_BSEL_Pos) /*!< 时钟源是XTL，由调制生成4800波特率 */
/**
 * @}
 */

/**
 * @defgroup LPUART_Func_Enable LPUART功能使能
 * @{
 */
#define LPUART_FUN_REN    (LPUART_SCON_REN_Msk)    /*!< 0-TX; 1-非mode0模式代表RX&TX,mode0模式代表RX */
#define LPUART_FUN_HDSEL  (LPUART_SCON_HDSEL_Msk)  /*!< 单线半双工功能 */
#define LPUART_FUN_ADRDET (LPUART_SCON_ADRDET_Msk) /*!< 多机通信地址自动识别功能 */
/**
 * @}
 */

/**
 * @defgroup LPUART_Int_Select LPUART中断选择
 * @{
 */
#define LPUART_INT_RC  (LPUART_SCON_RCIE_Msk)  /*!< 接收中断使能 */
#define LPUART_INT_TC  (LPUART_SCON_TCIE_Msk)  /*!< 发送中断使能 */
#define LPUART_INT_TXE (LPUART_SCON_TXEIE_Msk) /*!< TX空中断使能 */
#define LPUART_INT_PE  (LPUART_SCON_PEIE_Msk)  /*!< 奇偶校验中断使能 */
#define LPUART_INT_FE  (LPUART_SCON_FEIE_Msk)  /*!< 帧错误中断使能 */
#define LPUART_INT_CTS (LPUART_SCON_CTSIE_Msk) /*!< CTS信号翻转中断使能 */
/**
 * @}
 */

/**
 * @defgroup LPUART_Status_Select LPUART状态选择
 * @{
 */
#define LPUART_FLAG_TXE     (LPUART_ISR_TXE_Msk)   /*!< TX缓冲空标记 注：该位可获取不可清除 */
#define LPUART_FLAG_RC      (LPUART_ISR_RC_Msk)    /*!< 接收数据完成标记 */
#define LPUART_FLAG_TC      (LPUART_ISR_TC_Msk)    /*!< 发送数据完成标记 */
#define LPUART_FLAG_FE      (LPUART_ISR_FE_Msk)    /*!< 帧错误标记 */
#define LPUART_FLAG_PE      (LPUART_ISR_PE_Msk)    /*!< 奇偶校验错误标记 */
#define LPUART_FLAG_CTSIF   (LPUART_ISR_CTSIF_Msk) /*!< CTS中断标记 */
#define LPUART_FLAG_CTS     (LPUART_ISR_CTS_Msk)   /*!< CTS管脚电平 0：低电平 1：高电平 */

#define LPUART_FLAG_CLR_ALL (LPUART_ISR_RC_Msk | LPUART_ISR_TC_Msk | LPUART_ISR_FE_Msk | LPUART_ISR_PE_Msk | LPUART_ISR_CTSIF_Msk) /*!< 所有清除标志位 */
/**
 * @}
 */

/**
 * @defgroup LPUART_D8_Select LPUART Data8地址数据选择
 * @{
 */
#define LPUART_D8_DATA (0x00u)                 /*!< Data8=0, 发送数据帧 */
#define LPUART_D8_ADDR (LPUART_SBUF_DATA8_Msk) /*!< Data8=0, 发送地址帧 */
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
 * @addtogroup LPUART_Global_Functions LPUART全局函数定义
 * @{
 */
uint32_t LPUART_Init(LPUART_TypeDef *LPUARTx, stc_lpuart_init_t *pstcLpuartInit); /* 总初始化处理 */

en_result_t LPUART_ReceivePoll(LPUART_TypeDef *LPUARTx, uint8_t *pu8Data, uint32_t u32Size);                              /* 数据查询接收 */
en_result_t LPUART_ReceivePollTimeOut(LPUART_TypeDef *LPUARTx, uint8_t *pu8Data, uint32_t u32Size, uint32_t u32TimeOut);  /* 数据查询接收 */
en_result_t LPUART_TransmitPoll(LPUART_TypeDef *LPUARTx, uint8_t *pu8Data, uint32_t u32Size);                             /* 数据查询发送 */
en_result_t LPUART_TransmitPollTimeOut(LPUART_TypeDef *LPUARTx, uint8_t *pu8Data, uint32_t u32Size, uint32_t u32TimeOut); /* 数据查询发送 */
uint8_t     LPUART_DataReceive(LPUART_TypeDef *LPUARTx);                                                                  /* 数据接收 */
void        LPUART_DataTransmit(LPUART_TypeDef *LPUARTx, uint8_t u8Data);                                                 /* 数据发送 */

void LPUART_HdModeEnable(LPUART_TypeDef *LPUARTx);  /* LPUART 单线模式使能 */
void LPUART_HdModeDisable(LPUART_TypeDef *LPUARTx); /* LPUART 单线模式禁止 */

void LPUART_FuncEnable(LPUART_TypeDef *LPUARTx, uint32_t u32Func);  /* 特殊功能使能 */
void LPUART_FuncDisable(LPUART_TypeDef *LPUARTx, uint32_t u32Func); /* 特殊功能禁止 */

void LPUART_MultiModeConfig(LPUART_TypeDef *LPUARTx, uint8_t u8Addr, uint8_t u8AddrMask); /* LPUART通道多主机模式配置 */

void      LPUART_IntEnable(LPUART_TypeDef *LPUARTx, uint32_t u32IntSelect);    /* 中断使能 */
void      LPUART_IntDisable(LPUART_TypeDef *LPUARTx, uint32_t u32IntSelect);   /* 中断禁止 */
boolean_t LPUART_IntEnableGet(LPUART_TypeDef *LPUARTx, uint32_t u32IntSelect); /* 中断使能位获取 */

boolean_t LPUART_IntFlagGet(LPUART_TypeDef *LPUARTx, uint32_t u32IntFlag);   /* 状态位获取 */
void      LPUART_IntFlagClear(LPUART_TypeDef *LPUARTx, uint32_t u32IntFlag); /* 状态位清除 */
uint8_t   LPUART_IntFlagGetAll(LPUART_TypeDef *LPUARTx);                     /* 整个状态寄存器获取 */
void      LPUART_IntFlagClearAll(LPUART_TypeDef *LPUARTx);                   /* 整个状态寄存器清除 */

en_result_t LPUART_XtlBselSet(LPUART_TypeDef *LPUARTx, uint32_t u32BselConfig); /* LPUART XTL波特率产生寄存器 */

boolean_t LPUART_Bit8Get(LPUART_TypeDef *LPUARTx); /* 数据寄存器bit8位获取 */

void LPUART_StcInit(stc_lpuart_init_t *pstcInit); /* 结构体初始化 */
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

#endif /* __LPUART_H__ */
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
