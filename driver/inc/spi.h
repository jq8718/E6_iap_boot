/**
 *******************************************************************************
 * @file  spi.h
 * @brief This file contains all the functions prototypes of the SPI driver
 *        library
 @verbatim
   Change Logs:
   Date             Author          Notes
   2024-11-14       MADS            First version
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

#ifndef __SPI_H__
#define __SPI_H__

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
 * @addtogroup DDL_SPI SPI模块驱动库
 * @{
 */
/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup SPI_Global_Types SPI全局类型定义
 * @{
 */

/**
 * @brief  SPI Init structure definition
 */
typedef struct
{
    uint32_t u32BaudRate;    /*!< 波特率分频                           @ref SPI_Baudrate_Select */
    uint32_t u32Mode;        /*!< 主从模式选择                         @ref SPI_Mode_Select */
    uint32_t u32TransDir;    /*!< 通信方式选择                         @ref SPI_Transfer_Direction_Select */
    uint32_t u32CPHA;        /*!< 时钟相位选择                         @ref SPI_Clock_Phase_Select */
    uint32_t u32CPOL;        /*!< 时钟极性选择                         @ref SPI_Clock_Polarity_Select */
    uint32_t u32BitOrder;    /*!< 数据传输高低位顺序选择                @ref SPI_Bit_Order_Select */
    uint32_t u32DataWidth;   /*!< 每帧的数据宽度                       @ref SPI_Data_Width_Select */
    uint32_t u32NSS;         /*!< 配置NSS片选信号是硬件控制还是软件控制  @ref SPI_NSS_CFG */
    uint32_t u32SampleDelay; /*!< 主机模式延后采样                     @ref SPI_Sample_Delay_Select */
} stc_spi_init_t;
/**
 * @}
 */
/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup SPI_Global_Macros SPI全局宏定义
 * @{
 */

/**
 * @defgroup SPI_CR0_Macros  SPI_CR0全局宏定义
 * @{
 */

/** @defgroup SPI_Enable  SPI使能控制
 * @{
 */
#define SPI_ENABLE  (SPI_CR0_EN_Msk) /*!< SPI使能 */
#define SPI_DISABLE (0x0u)           /*!< SPI关闭 */
/**
 * @}
 */

/** @defgroup SPI_Baudrate_Select  SPI主机模式波特率选择
 * @{
 */
#define SPI_BAUDRATE_PCLK_DIV2   (0x0u << SPI_CR0_BRR_Pos) /*!< PCLK/2 */
#define SPI_BAUDRATE_PCLK_DIV4   (0x1u << SPI_CR0_BRR_Pos) /*!< PCLK/4 */
#define SPI_BAUDRATE_PCLK_DIV8   (0x2u << SPI_CR0_BRR_Pos) /*!< PCLK/8 */
#define SPI_BAUDRATE_PCLK_DIV16  (0x3u << SPI_CR0_BRR_Pos) /*!< PCLK/16 */
#define SPI_BAUDRATE_PCLK_DIV32  (0x4u << SPI_CR0_BRR_Pos) /*!< PCLK/32 */
#define SPI_BAUDRATE_PCLK_DIV64  (0x5u << SPI_CR0_BRR_Pos) /*!< PCLK/64 */
#define SPI_BAUDRATE_PCLK_DIV128 (0x6u << SPI_CR0_BRR_Pos) /*!< PCLK/128 */
/**
 * @}
 */

/** @defgroup SPI_Clock_Phase_Select  SPI串行时钟相位选择
 * @{
 */
#define SPI_CLK_PHASE_1EDGE (0x0u)             /*!< 前边沿采样/后边沿移位 */
#define SPI_CLK_PHASE_2EDGE (SPI_CR0_CPHA_Msk) /*!< 前边沿移位/后边沿采样 */
/**
 * @}
 */

/** @defgroup SPI_Clock_Polarity_Select  SPI串行时钟极性选择
 * @{
 */
#define SPI_CLK_POLARITY_LOW  (0x0u)             /*!< 待机时低电平 */
#define SPI_CLK_POLARITY_HIGH (SPI_CR0_CPOL_Msk) /*!< 待机时高电平 */
/**
 * @}
 */

/** @defgroup SPI_Mode_Select  SPI工作模式选择
 * @{
 */
#define SPI_MD_SLAVE  (0x0u)             /*!< 从机模式 */
#define SPI_MD_MASTER (SPI_CR0_MSTR_Msk) /*!< 主机模式 */
/**
 * @}
 */

/** @defgroup SPI_Bit_Order_Select  SPI串行数据高低位顺序发送选择
 * @{
 */
#define SPI_MSB_FIRST (0x0u)             /*!< 最高有效位MSB收发在前 */
#define SPI_LSB_FIRST (SPI_CR0_LSBF_Msk) /*!< 最低有效位LSB收发在前 */
/**
 * @}
 */

/** @defgroup SPI_Data_Width_Select  SPI串行数据帧宽度选择
 * @{
 */
#define SPI_DATA_WIDTH_4BIT  (0x3u << SPI_CR0_WIDTH_Pos) /*!< DATA WIDTH 4Bit  */
#define SPI_DATA_WIDTH_5BIT  (0x4u << SPI_CR0_WIDTH_Pos) /*!< DATA WIDTH 5Bit  */
#define SPI_DATA_WIDTH_6BIT  (0x5u << SPI_CR0_WIDTH_Pos) /*!< DATA WIDTH 6Bit  */
#define SPI_DATA_WIDTH_7BIT  (0x6u << SPI_CR0_WIDTH_Pos) /*!< DATA WIDTH 7Bit  */
#define SPI_DATA_WIDTH_8BIT  (0x7u << SPI_CR0_WIDTH_Pos) /*!< DATA WIDTH 8Bit  */
#define SPI_DATA_WIDTH_9BIT  (0x8u << SPI_CR0_WIDTH_Pos) /*!< DATA WIDTH 9Bit  */
#define SPI_DATA_WIDTH_10BIT (0x9u << SPI_CR0_WIDTH_Pos) /*!< DATA WIDTH 10Bit */
#define SPI_DATA_WIDTH_11BIT (0xAu << SPI_CR0_WIDTH_Pos) /*!< DATA WIDTH 11Bit */
#define SPI_DATA_WIDTH_12BIT (0xBu << SPI_CR0_WIDTH_Pos) /*!< DATA WIDTH 12Bit */
#define SPI_DATA_WIDTH_13BIT (0xCu << SPI_CR0_WIDTH_Pos) /*!< DATA WIDTH 13Bit */
#define SPI_DATA_WIDTH_14BIT (0xDu << SPI_CR0_WIDTH_Pos) /*!< DATA WIDTH 14Bit */
#define SPI_DATA_WIDTH_15BIT (0xEu << SPI_CR0_WIDTH_Pos) /*!< DATA WIDTH 15Bit */
#define SPI_DATA_WIDTH_16BIT (0xFu << SPI_CR0_WIDTH_Pos) /*!< DATA WIDTH 16Bit */
/**
 * @}
 */

/** @defgroup SPI_NSS_CFG  NSS片选信号配置
 * @{
 */
#define SPI_NSS_HARD_INPUT  (0x0u)            /*!< NSS IO的外部输入 */
#define SPI_NSS_HARD_OUTPUT (SPI_CR0_SSM_Msk) /*!< 主机模式下，由SSI寄存器来决定NSS信号IO的输出值 */
#define SPI_NSS_SOFT        (SPI_CR0_SSM_Msk) /*!< 从机模式下，由SSI寄存器值决定NSS信号的输入值 */
/**
 * @}
 */

/** @defgroup SPI_Transfer_Direction_Select  SPI通讯方式选择
 * @{
 */
#define SPI_FULL_DUPLEX (0x0u)                   /*!< 全双工双向 */
#define SPI_SIMPLE_TX   (0x1u << SPI_CR0_CM_Pos) /*!< 单工只发 */
#define SPI_SIMPLE_RX   (0x2u << SPI_CR0_CM_Pos) /*!< 单工只收 */
#define SPI_HALF_DUPLEX (0x3u << SPI_CR0_CM_Pos) /*!< 单线半双工 */
/**
 * @}
 */

/** @defgroup SPI_Half_Duplex_Direction_Select  SPI半双工传输方向选择
 * @{
 */
#define SPI_HALF_DUPLEX_RX (0x0u)              /*!< 单线半双工只收 */
#define SPI_HALF_DUPLEX_TX (SPI_HDOE_HDOE_Msk) /*!< 单线半双工只发 */
/**
 * @}
 */

/** @defgroup SPI_Sample_Delay_Select  SPI主机模式延后采样
 * @{
 */
#define SPI_SAMPLE_NORMAL (0x0u)            /*!< 正常采样 */
#define SPI_SAMPLE_DELAY  (SPI_CR0_SMP_Msk) /*!< 延后采样 */
/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup SPI_CR1_Macros  SPI_CR1全局宏定义
 * @{
 */

/** @defgroup SPI_INT_Select  SPI中断使能选择
 * @{
 */
#define SPI_INT_TXE   (SPI_CR1_TXEIE_Msk)   /*!< 使能发送缓冲空中断 */
#define SPI_INT_RXNE  (SPI_CR1_RXNEIE_Msk)  /*!< 使能接收缓冲非空中断 */
#define SPI_INT_SSF   (SPI_CR1_SSFIE_Msk)   /*!< 使能从机选择输入下降沿中断 */
#define SPI_INT_SSR   (SPI_CR1_SSRIE_Msk)   /*!< 使能从机选择输入上升沿中断 */
#define SPI_INT_UDF   (SPI_CR1_UDFIE_Msk)   /*!< 使能从机模式下发送缓冲下溢错误中断 */
#define SPI_INT_OVF   (SPI_CR1_OVFIE_Msk)   /*!< 使能接收缓冲上溢错误 */
#define SPI_INT_SSERR (SPI_CR1_SSERRIE_Msk) /*!< 使能从机模式下的从机选择错误中断 */
#define SPI_INT_MODF  (SPI_CR1_MODFIE_Msk)  /*!< 使能模式错误中断 */
/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup SPI_NSS_Soft_Value  SPI_SSI设定值
 * @{
 */
#define SPI_NSS_CONFIG_ENABLE  (0x0u)            /*!< 片选使能 */
#define SPI_NSS_CONFIG_DISABLE (SPI_SSI_SSI_Msk) /*!< 片选禁止 */
/**
 * @}
 */

/**
 * @defgroup SPI_SR_Macros  SPI_SR全局宏定义
 * @{
 */

/** @defgroup SPI_Flag_Select  SPI中断标志位选择
 * @{
 */
#define SPI_FLAG_TXE   (SPI_SR_TXE_Msk)   /*!< 发送缓冲空 标志  */
#define SPI_FLAG_RXNE  (SPI_SR_RXNE_Msk)  /*!< 接收缓冲非空 标志  */
#define SPI_FLAG_SSF   (SPI_SR_SSF_Msk)   /*!< 从机选择输入出现下降沿 标志 */
#define SPI_FLAG_SSR   (SPI_SR_SSR_Msk)   /*!< 从机选择输入出现上升沿 标志 */
#define SPI_FLAG_UDF   (SPI_SR_UDF_Msk)   /*!< 从机模式下发送缓冲下溢错误 标志 */
#define SPI_FLAG_OVF   (SPI_SR_OVF_Msk)   /*!< 接收缓冲上溢错误 标志 */
#define SPI_FLAG_SSERR (SPI_SR_SSERR_Msk) /*!< 从机模式下的从机选择错误 标志 */
#define SPI_FLAG_MODF  (SPI_SR_MODF_Msk)  /*!< 模式错误 标志 */
#define SPI_FLAG_BUSY  (SPI_SR_BUSY_Msk)  /*!< 总线忙 标志,注：该位可获取不可清除 */
/**
 * @}
 */

/**
 * @defgroup SPI_NSS_Extern_Input_Level  SPI_NSS管脚上输入电平
 * @{
 */
#define SPI_NSS_EXTERN_INPUT_LOW_LEVEL  (0x0u)             /*!<  NSS管脚上输入的是低电平    */
#define SPI_NSS_EXTERN_INPUT_HIGH_LEVEL (SPI_SR_SSLVL_Msk) /*!<  NSS管脚上输入的是高电平    */
/**
 * @}
 */

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
 * @addtogroup SPI_Global_Functions SPI全局函数定义
 * @{
 */
en_result_t SPI_Init(SPI_TypeDef *SPIx, stc_spi_init_t *pstcInitConfig); /* SPI 总体初始化 */

en_result_t SPI_DataTransmit(SPI_TypeDef *SPIx, uint16_t u16Data); /* SPI 发送一数据函数 */
uint16_t    SPI_DataReceive(SPI_TypeDef *SPIx);                    /* SPI 接收一数据函数 */

en_result_t SPI_SlaveDummyDataTransmit(SPI_TypeDef *SPIx, uint16_t u16Data);                             /* SPI 从机预准备第一个数据 */
en_result_t SPI_SlaveDummyDataTransmitTimeout(SPI_TypeDef *SPIx, uint16_t u16Data, uint32_t u32Timeout); /* SPI 从机预准备第一个数据超时等待 */

en_result_t SPI_TransmitReceive(SPI_TypeDef *SPIx, uint16_t pu16SendBuf[], uint16_t pu16RecBuf[], uint32_t u32Len); /* SPI 连续发送接收多个数据函数 */
/* SPI 连续发送接收多个数据函数超时等待 */
en_result_t SPI_TransmitReceiveTimeout(SPI_TypeDef *SPIx, uint16_t pu16SendBuf[], uint16_t pu16RecBuf[], uint32_t u32Len, uint32_t u32Timeout);

void SPI_Enable(SPI_TypeDef *SPIx);  /* 开启SPI模块 */
void SPI_Disable(SPI_TypeDef *SPIx); /* 禁止SPI模块 */

void SPI_BaudRateSet(SPI_TypeDef *SPIx, uint32_t u32BaudRate); /* 设定SPI主机模式波特率 */

void SPI_ClockPhaseSet(SPI_TypeDef *SPIx, uint32_t u32ClockPhase);       /* 设定SPI串行时钟相位 */
void SPI_ClockPolaritySet(SPI_TypeDef *SPIx, uint32_t u32ClockPolarity); /* 设定SPI串行时钟极性选择 */

void SPI_ModeSet(SPI_TypeDef *SPIx, uint32_t u32Mode); /* 设定SPI模式，主机模式或者从机模式 */

void SPI_TransBitOrderSet(SPI_TypeDef *SPIx, uint32_t u32TransBitOrder); /* 设定SPI数据传输高低位顺序 */

void SPI_DataWidthSet(SPI_TypeDef *SPIx, uint32_t u32DataWidth); /* 设定SPI每帧的数据宽度 */

void     SPI_NSSModeSet(SPI_TypeDef *SPIx, uint32_t u32NSSMode);        /* 设定SPI NSS模式 */
void     SPI_SlaveNSSConfig(SPI_TypeDef *SPIx, uint32_t u32NSSConfig);  /* 从机时，配置NSS片选使能或禁止 */
void     SPI_MasterNSSOutput(SPI_TypeDef *SPIx, uint32_t u32NSSConfig); /* 主机时，配置NSS片选输出(到从机) */
uint32_t SPI_NSSSoftValueGet(SPI_TypeDef *SPIx);                        /* 获取SPI SSI的值 */
uint32_t SPI_NSSExternInputGet(SPI_TypeDef *SPIx);                      /* 获取SPI SSLVL的值 */

void SPI_TransDirSet(SPI_TypeDef *SPIx, uint32_t u32TransDir); /* 设定SPI 通信方式选择 */

void SPI_HalfDuplexDirSet(SPI_TypeDef *SPIx, uint32_t u32TransDir); /* 设定SPI 半双工通信方式选择 */

void SPI_IntEnable(SPI_TypeDef *SPIx, uint32_t u32IntEn); /* SPI 中断使能 */
void SPI_IntDisable(SPI_TypeDef *SPIx, uint32_t u32Int);  /* SPI 中断禁止 */

boolean_t SPI_FlagGet(SPI_TypeDef *SPIx, uint32_t u32Flag);   /* 获取 SPI 标志位 */
void      SPI_FlagClear(SPI_TypeDef *SPIx, uint32_t u32Flag); /* 清除 SPI 标志位 */
void      SPI_FlagClearALL(SPI_TypeDef *SPIx);                /* 清除 SPI 所有标志 */
void      SPI_TXEFlagSet(SPI_TypeDef *SPIx);                  /* SPI 发送缓冲空标志 置位 */

void SPI_StcInit(stc_spi_init_t *pstcInit); /*结构体初始化 */
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

#endif /* __SPI_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
