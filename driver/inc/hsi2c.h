/**
 *******************************************************************************
 * @file  hsi2c.h
 * @brief This file contains all the functions prototypes of the HSI2C driver
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

#ifndef __HSI2C_H__
#define __HSI2C_H__

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
 * @addtogroup DDL_HSI2C HSI2C模块驱动库
 * @{
 */
/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup HSI2C_Global_Types HSI2C全局类型定义
 * @{
 */

/**
 * @brief HSI2C通信方向
 */
typedef enum
{
    Hsi2cMasterWriteSlaveRead = 0x0u, /*!< 主机写从机读 */
    Hsi2cMasterReadSlaveWrite = 0x1u, /*!< 主机读从机写 */
} en_hsi2c_dir_t;

/**
 * @brief HSI2C主机配置寄存器MCFGR1结构体定义
 */
typedef struct
{
    /* MCFGR1 */
    uint32_t u32MatchConfig;          /*!< Match configuration @ref HSI2C_Master_Config1_MATCFG */
    uint32_t u32ReceiveDataMatchOnly; /*!< Receive data match only @ref HSI2C_Master_Config1_RDMO */
    uint32_t u32TimeoutConfig;        /*!< Timeout config for pin low @ref HSI2C_Master_Config1_TIMECFG */
    uint32_t u32IgnoreNack;           /*!< Whether to ignore ACK/NACK @ref HSI2C_Master_Config1_IGNACK */
    uint32_t u32AutoStop;             /*!< Whether to enable auto stop @ref HSI2C_Master_Config1_AUTOSTOP*/
} stc_hsi2c_master_config1_t;

/**
 * @brief HSI2C主机配置寄存器MCFGR2结构体定义
 */
typedef struct
{
    /* MCFGR2 */
    uint32_t u32SdaFilterEnable;       /*!< Analog filter SDA bypass @ref HSI2C_Master_Config2_FILTBPSDA */
    uint32_t u32SclFilterEnable;       /*!< Analog filter SCL bypass @ref HSI2C_Master_Config2_FILTBPSCL */
    uint32_t u32SdaGlitchFilterConfig; /*!< Configures the I2C master digital glitch filters for SDA input. Set to 0 to disable. 数据范围：0 ~ 0xF */
    uint32_t u32SclGlitchFilterConfig; /*!< Configures the I2C master digital glitch filters for SCL input. Set to 0 to disable. 数据范围：0 ~ 0xF */
    uint32_t u32BusIdleTimeout;        /*!< Configures the bus idle timeout period in clock cycles. Set to 0 to disable. 数据范围：0 ~ 0xFFF */
} stc_hsi2c_master_config2_t;

/**
 * @brief HSI2C主机配置寄存器MCFGR3结构体定义
 */
typedef struct
{
    /* MCFGR3 */
    uint32_t u32PinLowTimeout; /*!< Configures the pin low timeout flag in clock cycles. Set to 0 to disable. 数据范围：0 ~ 0xFFF */
} stc_hsi2c_master_config3_t;

/**
 * @brief HSI2C主机配置结构体定义
 */
typedef struct
{
    boolean_t                  bResetBeforeInit; /*!< Whether to reset hsi2c before configure it @ref boolean_t */
    uint32_t                   u32EnableDebug;   /*!< Enable transfers to continue when halted in debug mode @ref HSI2C_Master_Debug_Select */
    uint32_t                   u32BaudRateHz;    /*!< Desired baud rate in Hz */
    uint8_t                    u8SlaveAddr;      /*!< The 10-bit or 7-bit slave address */
    en_hsi2c_dir_t             enDir;            /*!< Direction setting @ref en_hsi2c_dir_t */
    stc_hsi2c_master_config1_t stcMasterConfig1; /*!< Master MCFGR1 configuration @ref stc_hsi2c_master_config1_t */
    stc_hsi2c_master_config2_t stcMasterConfig2; /*!< Master MCFGR2 configuration @ref stc_hsi2c_master_config2_t */
    stc_hsi2c_master_config3_t stcMasterConfig3; /*!< Master MCFGR3 configuration @ref stc_hsi2c_master_config3_t */
    struct
    {
        union /*!< Sub address. MSB transmit first */
        {
            uint32_t u32SubAddr;
            uint8_t  u8SubAddr[4];
        };
        uint8_t u8SubAddrSize; /*!< Length of sub address. Max size is 4 bytes */
    };
} stc_hsi2c_master_init_t;

/**
 * @brief HSI2C从机控制寄存器SCR1结构体定义
 */
typedef struct
{
    /* SCR1 */
    uint32_t u32FuncSelect;          /*!< Function select @ref HSI2C_Slave_Scr1_Func_Select */
    uint32_t u32ConfigAddrMatchMode; /*!< Configure address match mode@ref HSI2C_Slave_Scr1_Addr_Match_Mode */
} stc_hsi2c_slave_control1_t;

/**
 * @brief HSI2C从机控制寄存器SCR2结构体定义
 */
typedef struct
{
    /* SCR2 */
    uint32_t u32FilterEnable;         /*!< Filter enable @ref HSI2C_Slave_Filter_Enable */
    uint32_t u32SdaGlitchFilterWidth; /*!< Width in nanoseconds of the digital filter on the SDA signal. Set to 0 to disable. 数据范围：0 ~ 0xF */
    uint32_t u32SclGlitchFilterWidth; /*!< Width in nanoseconds of the digital filter on the SCL signal. Set to 0 to disable. 数据范围：0 ~ 0xF */
    uint32_t u32TimingDataValidDelay; /*!< Width in nanoseconds of the data valid delay. 数据范围：0 ~ 0x3F */
    uint32_t u32TimingClockHoldTime;  /*!< Width in nanoseconds of the clock hold time.  数据范围：0 ~ 0xF */
} stc_hsi2c_slave_control2_t;

/**
 * @brief HSI2C从机配置结构体定义
 */
typedef struct
{
    boolean_t                  bResetBeforeInit; /*!< Enable reset hsi2c before init it @ref boolean_t */
    stc_hsi2c_slave_control1_t stcSlaveConfig1;  /*!< Slave SCR1 configuration @ref stc_hsi2c_slave_control1_t */
    stc_hsi2c_slave_control2_t stcSlaveConfig2;  /*!< Slave SCR2 configuration @ref stc_hsi2c_slave_control2_t */
    uint32_t                   u32SlaveAddr0;    /*!< The 10-bit or 7-bit slave address0 */
    uint32_t                   u32SlaveAddr1;    /*!< The 10-bit or 7-bit slave address1 */
    en_hsi2c_dir_t             enDir;            /*!< Direction setting @ref en_hsi2c_dir_t */
    uint8_t                    u8SubAddrSize;    /*!< Length of sub address to receive in bytes. Maximum size is 4 bytes */
} stc_hsi2c_slave_init_t;

/**
 * @brief HSI2C通信状态
 */
typedef enum
{
    Hsi2cComBusy = 0x1u,
    Hsi2cComIdle = 0x0u,
} en_hsi2c_com_status_t;

/**
 * @brief HSI2C通信结果
 */
typedef enum
{
    Hsi2cComSuccess              = 0x0u, /* The operation is successful */
    Hsi2cComErrorNack            = 0x1u, /* The slave device sent a NACK in response to a byte */
    Hsi2cComErrorBitError        = 0x2u, /* Transferred bit was not seen on the bus */
    Hsi2cComErrorArbitrationLost = 0x3u, /* Arbitration lost error */
    Hsi2cComErrorPinLowTimeout   = 0x4u, /* SCL or SDA were held low longer than the timeout */
    Hsi2cComErrorBufError        = 0x5u, /* Buffer error */
    Hsi2cComErrorTimeout         = 0x6u, /* Timeout polling status flags */
    Hsi2cComErrorInvalidPara     = 0x7u, /* Invalid parameter */
} en_hsi2c_com_error_t;

/**
 * @brief HSI2C通信配置结构体定义
 */
typedef struct
{
    HSI2C_TypeDef             *HSI2CxBaseAddr; /*!< HSI2C base address */
    uint32_t                   u32Len;         /*!< HSI2C communication data length */
    uint8_t                   *pu8Buf;         /*!< HSI2C communication data buffer pointer */
    __IO uint32_t              u32DataIndex;   /*!< HSI2C communication data transfer index */
    __IO en_hsi2c_com_status_t enComStatus;    /*!< HSI2C communication status */
    uint32_t                   u32RxSize;      /*!< Master: HSI2C receive data length */
                                               /*!< Slave:  HSI2C sub address length */
    struct
    {
        union /*!< Sub address. Receive MSB first */
        {
            uint32_t u32SubAddr;
            uint8_t  u8SubAddr[4];
        };
    };
} stc_hsi2c_com_t;

/**
 * @brief HSI2C状态机定义
 */
typedef enum
{
    Hsi2cStatusStart     = 0x0u, /*!< HSI2C status machine: start/restart */
    Hsi2cStatusSubAddr   = 0x1u, /*!< HSI2C status machine: sub address */
    Hsi2cStatusTransData = 0x2u, /*!< HSI2C status machine: data transfer */
    Hsi2cStatusRxCmd     = 0x3u, /*!< HSI2C status machine: receive command */
    Hsi2cStatusStop      = 0x4u, /*!< HSI2C status machine: stop */
    Hsi2cStatusWaitEnd   = 0x5u, /*!< HSI2C status machine: wait for end */
    Hsi2cStatusRestart   = 0x6u, /*!< HSI2C status machine: reset */
} en_hsi2c_status_machine_t;
/**
 * @}
 */
/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup HSI2C_Global_Macros HSI2C全局宏定义
 * @{
 */

/**
 * @defgroup HSI2C_Master_Cmd HSI2C主机命令选择
 * @{
 */
#define HSI2C_CMD_TX_DATA       (0x0u)                       /*!< Transmit DATA[7:0] */
#define HSI2C_CMD_RX_DATA       (0x1u << HSI2C_MTDR_CMD_Pos) /*!< Receive (DATA[7:0] + 1) bytes */
#define HSI2C_CMD_STOP          (0x2u << HSI2C_MTDR_CMD_Pos) /*!< Generate STOP condition */
#define HSI2C_CMD_RX_DISCARD    (0x3u << HSI2C_MTDR_CMD_Pos) /*!< Receive and discard (DATA[7:0] + 1) bytes */
#define HSI2C_CMD_START_TX_DATA (0x4u << HSI2C_MTDR_CMD_Pos) /*!< Generate (repeated) START and transmit address in DATA[7:0] */
#define HSI2C_CMD_START_TX_DATA_NACK \
    (0x5u << HSI2C_MTDR_CMD_Pos) /*!< Generate (repeated) START and transmit address in DATA[7:0]. This transfer expects a NACK to be returned */
/**
 * @}
 */

/**
 * @defgroup HSI2C_Master_Flag HSI2C主机状态选择
 * @{
 */
#define HSI2C_MASTER_FLAG_BBF  (HSI2C_MSR_BBF_Msk)  /*!< Bus busy flag 注：该位可获取不可清除 */
#define HSI2C_MASTER_FLAG_MBF  (HSI2C_MSR_MBF_Msk)  /*!< Master busy flag 注：该位可获取不可清除 */
#define HSI2C_MASTER_FLAG_DMF  (HSI2C_MSR_DMF_Msk)  /*!< Data match flag */
#define HSI2C_MASTER_FLAG_PLTF (HSI2C_MSR_PLTF_Msk) /*!< Pin low timeout flag */
#define HSI2C_MASTER_FLAG_FEF  (HSI2C_MSR_FEF_Msk)  /*!< Buffer error flag */
#define HSI2C_MASTER_FLAG_ALF  (HSI2C_MSR_ALF_Msk)  /*!< Arbitration lost flag */
#define HSI2C_MASTER_FLAG_NDF  (HSI2C_MSR_NDF_Msk)  /*!< NACK detect flag */
#define HSI2C_MASTER_FLAG_SDF  (HSI2C_MSR_SDF_Msk)  /*!< STOP detect flag */
#define HSI2C_MASTER_FLAG_EPF  (HSI2C_MSR_EPF_Msk)  /*!< End packet flag */
#define HSI2C_MASTER_FLAG_RDF  (HSI2C_MSR_RDF_Msk)  /*!< Receive data flag 注：该位可获取不可清除 */
#define HSI2C_MASTER_FLAG_TDF  (HSI2C_MSR_TDF_Msk)  /*!< Transmit data flag 注：该位可获取不可清除 */

#define HSI2C_MASTER_FLAG_CLR_ALL \
    (HSI2C_MASTER_FLAG_DMF | HSI2C_MASTER_FLAG_PLTF | HSI2C_MASTER_FLAG_FEF | HSI2C_MASTER_FLAG_ALF | HSI2C_MASTER_FLAG_NDF | HSI2C_MASTER_FLAG_SDF \
     | HSI2C_MASTER_FLAG_EPF) /*!< 所有清除标志位 */
/**
 * @}
 */

/**
 * @defgroup HSI2C_Slave_Flag HSI2C从机状态选择
 * @{
 */
#define HSI2C_SLAVE_FLAG_BBF     (HSI2C_SSR_BBF_Msk)  /*!< Bus busy flag 注：该位可获取不可清除 */
#define HSI2C_SLAVE_FLAG_SBF     (HSI2C_SSR_SBF_Msk)  /*!< Slave busy flag 注：该位可获取不可清除 */
#define HSI2C_SLAVE_FLAG_SARF    (HSI2C_SSR_SARF_Msk) /*!< SMBus alert Response flag 注：该位可获取不可清除 */
#define HSI2C_SLAVE_FLAG_GCF     (HSI2C_SSR_GCF_Msk)  /*!< General call flag 注：该位可获取不可清除 */
#define HSI2C_SLAVE_FLAG_AM1F    (HSI2C_SSR_AM1F_Msk) /*!< Address match 1 flag　注：该位可获取不可清除 */
#define HSI2C_SLAVE_FLAG_AM0F    (HSI2C_SSR_AM0F_Msk) /*!< Address match 0 flag　注：该位可获取不可清除 */
#define HSI2C_SLAVE_FLAG_FEF     (HSI2C_SSR_FEF_Msk)  /*!< Buffer Eerror flag */
#define HSI2C_SLAVE_FLAG_BEF     (HSI2C_SSR_BEF_Msk)  /*!< Bit error flag */
#define HSI2C_SLAVE_FLAG_SDF     (HSI2C_SSR_SDF_Msk)  /*!< STOP detect flag */
#define HSI2C_SLAVE_FLAG_RSF     (HSI2C_SSR_RSF_Msk)  /*!< Repeated start flag */
#define HSI2C_SLAVE_FLAG_TAF     (HSI2C_SSR_TAF_Msk)  /*!< Transmit ACK flag 注：该位可获取不可清除 */
#define HSI2C_SLAVE_FLAG_AVF     (HSI2C_SSR_AVF_Msk)  /*!< Address valid flag 注：该位可获取不可清除 */
#define HSI2C_SLAVE_FLAG_RDF     (HSI2C_SSR_RDF_Msk)  /*!< Receive data flag 注：该位可获取不可清除 */
#define HSI2C_SLAVE_FLAG_TDF     (HSI2C_SSR_TDF_Msk)  /*!< Transmit data flag 注：该位可获取不可清除 */

#define HSI2C_SLAVE_FLAG_CLR_ALL (HSI2C_SLAVE_FLAG_FEF | HSI2C_SLAVE_FLAG_BEF | HSI2C_SLAVE_FLAG_SDF | HSI2C_SLAVE_FLAG_RSF) /*!< 所有清除标志位 */
/**
 * @}
 */

/**
 * @defgroup HSI2C_Master_Int HSI2C主机中断选择
 * @{
 */
#define HSI2C_MASTER_INT_DMIE  (HSI2C_MIER_DMIE_Msk)  /*!< Data match interrupt enable */
#define HSI2C_MASTER_INT_PLTIE (HSI2C_MIER_PLTIE_Msk) /*!< Pin low timeout interrupt enable */
#define HSI2C_MASTER_INT_FEIE  (HSI2C_MIER_FEIE_Msk)  /*!< FIFO error interrupt enable */
#define HSI2C_MASTER_INT_ALIE  (HSI2C_MIER_ALIE_Msk)  /*!< Arbitration lost interrupt enable */
#define HSI2C_MASTER_INT_NDIE  (HSI2C_MIER_NDIE_Msk)  /*!< NACK detect interrupt enable */
#define HSI2C_MASTER_INT_SDIE  (HSI2C_MIER_SDIE_Msk)  /*!< Stop detect interrupt enable */
#define HSI2C_MASTER_INT_EPIE  (HSI2C_MIER_EPIE_Msk)  /*!< End packet interrupt enable */
#define HSI2C_MASTER_INT_RDIE  (HSI2C_MIER_RDIE_Msk)  /*!< Receive data interrupt enable */
#define HSI2C_MASTER_INT_TDIE  (HSI2C_MIER_TDIE_Msk)  /*!< Transmit data interrupt enable */

#define HSI2C_MASTER_INT_ALL \
    (HSI2C_MIER_DMIE_Msk | HSI2C_MIER_PLTIE_Msk | HSI2C_MIER_FEIE_Msk | HSI2C_MIER_ALIE_Msk | HSI2C_MIER_NDIE_Msk | HSI2C_MIER_SDIE_Msk | HSI2C_MIER_EPIE_Msk \
     | HSI2C_MIER_RDIE_Msk | HSI2C_MIER_TDIE_Msk) /*!< All interrupt enable */

/**
 * @}
 */

/**
 * @defgroup HSI2C_Slave_Int HSI2C从机中断选择
 * @{
 */
#define HSI2C_SLAVE_INT_SARIE (HSI2C_SIER_SARIE_Msk) /*!< SMBus alert response interrupt enable */
#define HSI2C_SLAVE_INT_GCIE  (HSI2C_SIER_GCIE_Msk)  /*!< General call interrupt enable */
#define HSI2C_SLAVE_INT_AM1IE (HSI2C_SIER_AM1IE_Msk) /*!< Address match 1 interrupt enable */
#define HSI2C_SLAVE_INT_AM0IE (HSI2C_SIER_AM0IE_Msk) /*!< Address match 0 interrupt enable */
#define HSI2C_SLAVE_INT_FEIE  (HSI2C_SIER_FEIE_Msk)  /*!< Buffer error interrupt enable */
#define HSI2C_SLAVE_INT_BEIE  (HSI2C_SIER_BEIE_Msk)  /*!< Bit error interrupt enable */
#define HSI2C_SLAVE_INT_SDIE  (HSI2C_SIER_SDIE_Msk)  /*!< STOP detect interrupt enable */
#define HSI2C_SLAVE_INT_RSIE  (HSI2C_SIER_RSIE_Msk)  /*!< Repeated start interrupt enable */
#define HSI2C_SLAVE_INT_TAIE  (HSI2C_SIER_TAIE_Msk)  /*!< Transmit ACK interrupt enable */
#define HSI2C_SLAVE_INT_AVIE  (HSI2C_SIER_AVIE_Msk)  /*!< Address valid interrupt enable*/
#define HSI2C_SLAVE_INT_RDIE  (HSI2C_SIER_RDIE_Msk)  /*!< Receive data interrupt enable */
#define HSI2C_SLAVE_INT_TDIE  (HSI2C_SIER_TDIE_Msk)  /*!< Transmit data interrupt enable */

#define HSI2C_SLAVE_INT_ALL \
    (HSI2C_SIER_SARIE_Msk | HSI2C_SIER_GCIE_Msk | HSI2C_SIER_AM1IE_Msk | HSI2C_SIER_AM0IE_Msk | HSI2C_SIER_FEIE_Msk | HSI2C_SIER_BEIE_Msk \
     | HSI2C_SIER_SDIE_Msk | HSI2C_SIER_RSIE_Msk | HSI2C_SIER_TAIE_Msk | HSI2C_SIER_AVIE_Msk | HSI2C_SIER_RDIE_Msk \
     | HSI2C_SIER_TDIE_Msk) /*!< All interrupt enable */
/**
 * @}
 */

/**
 * @defgroup HSI2C_Master_Debug_Select HSI2C调试使能选择
 * @{
 */
#define HSI2C_MASTER_DEBUG_OFF (0x0u)                /*!< Debug off */
#define HSI2C_MASTER_DEBUG_ON  (HSI2C_MCR_DBGEN_Msk) /*!< Debug on */
/**
 * @}
 */

/**
 * @defgroup HSI2C_Master_Config1_MATCFG HSI2C主机匹配配置
 * @{
 */
#define HSI2C_MASTER_MATCFG_DISABLE  (0x0u)                            /*!< Match is disabled */
#define HSI2C_MASTER_MATCFG_ENABLE_2 (0x2u << HSI2C_MCFGR1_MATCFG_Pos) /*!< Match is enabled */
                                                                       /*!< 1st data word equals MDMR.MATCH0 OR MDMR.MATCH1) */
#define HSI2C_MASTER_MATCFG_ENABLE_3 (0x3u << HSI2C_MCFGR1_MATCFG_Pos) /*!< Match is enabled */
                                                                       /*!< Any data word equals MDMR.MATCH0 OR MDMR.MATCH1) */
#define HSI2C_MASTER_MATCFG_ENABLE_4 (0x4u << HSI2C_MCFGR1_MATCFG_Pos) /*!< Match is enabled */
                                                                       /*!< 1st data word equals MDMR.MATCH0 AND 2nd data word equals MDMR.MATCH1 */
#define HSI2C_MASTER_MATCFG_ENABLE_5 (0x5u << HSI2C_MCFGR1_MATCFG_Pos) /*!< Match is enabled */
                                                                       /*!< Any data word equals MDMR.MATCH0 AND next data word equals MDMR.MATCH1) */
#define HSI2C_MASTER_MATCFG_ENABLE_6 (0x6u << HSI2C_MCFGR1_MATCFG_Pos) /*!< Match is enabled */
                                                                       /*!< 1st data word AND MDMR.MATCH1 equals MDMR.MATCH0 AND MDMR.MATCH1) */
#define HSI2C_MASTER_MATCFG_ENABLE_7 (0x7u << HSI2C_MCFGR1_MATCFG_Pos) /*!< Match is enabled */
                                                                       /*!< Any data word AND MDMR.MATCH1 equals MDMR.MATCH0 AND MDMR.MATCH1) */
/**
 * @}
 */

/**
 * @defgroup HSI2C_Master_Config1_RDMO HSI2C主机仅接收数据匹配配置
 * @{
 */
#define HSI2C_MASTER_RDMO_STORE   (0x0u)                  /*!< Received data is stored in the receive buffer */
#define HSI2C_MASTER_RDMO_DISCARD (HSI2C_MCFGR1_RDMO_Msk) /*!< Received data is discarded unless the the Data Match Flag (MSR.DMF) is set */
/**
 * @}
 */

/**
 * @defgroup HSI2C_Master_Config1_TIMECFG HSI2C主机超时配置
 * @{
 */
#define HSI2C_MASTER_TIMECFG_SCL     (0x0u)                     /*!< MSR.PLTF sets if SCL is low for longer than the configured timeout */
#define HSI2C_MASTER_TIMECFG_SCL_SDA (HSI2C_MCFGR1_TIMECFG_Msk) /*!< MSR.PLTF sets if either SCL or SDA is low for longer than the configured timeout */
/**
 * @}
 */

/**
 * @defgroup HSI2C_Master_Config1_IGNACK HSI2C主机NACK配置
 * @{
 */
#define HSI2C_MASTER_IGNACK_NORMAL      (0x0u)                    /*!< I2C Master receives ACK and NACK normally */
#define HSI2C_MASTER_IGNACK_IGNORE_NACK (HSI2C_MCFGR1_IGNACK_Msk) /*!< I2C Master treats a received NACK as if it (NACK) was an ACK */
/**
 * @}
 */

/**
 * @defgroup HSI2C_Master_Config1_AUTOSTOP HSI2C主机自动产生STOP配置
 * @{
 */
#define HSI2C_MASTER_AUTOSTOP_DISABLE (0x0u)                      /*!< No effect */
#define HSI2C_MASTER_AUTOSTOP_ENABLE  (HSI2C_MCFGR1_AUTOSTOP_Msk) /*!< STOP condition is automatically generated */
/**
 * @}
 */

/**
 * @defgroup HSI2C_Master_Config2_FILTBPSDA HSI2C主机SDA bypass配置
 * @{
 */
#define HSI2C_MASTER_FILTBPSDA_DISABLE (0x0u)                       /*!< SDA pass the analog filter */
#define HSI2C_MASTER_FILTBPSDA_ENABLE  (HSI2C_MCFGR2_FILTBPSDA_Msk) /*!< SDA bypass the analog filter */
/**
 * @}
 */

/**
 * @defgroup HSI2C_Master_Config2_FILTBPSCL HSI2C主机SCL bypass配置
 * @{
 */
#define HSI2C_MASTER_FILTBPSCL_DISABLE (0x0u)                       /*!< SCL pass the analog filter */
#define HSI2C_MASTER_FILTBPSCL_ENABLE  (HSI2C_MCFGR2_FILTBPSCL_Msk) /*!< SCL bypass the analog filter */
/**
 * @}
 */

/**
 * @defgroup HSI2C_Slave_Scr1_Addr_Match_Mode HSI2C从机SCR1地址配置模式
 * @{
 */
#define HSI2C_SLAVE_ADDR0_7B               (0x0u)                            /*!< Address match 0 (7-bit) */
#define HSI2C_SLAVE_ADDR0_10B              (0x1u << HSI2C_SCR1_ADDRMODE_Pos) /*!< Address match 0 (10-bit) */
#define HSI2C_SLAVE_ADDR0_7B_OR_ADDR1_7B   (0x2u << HSI2C_SCR1_ADDRMODE_Pos) /*!< Address match 0 (7-bit) or Address match 1 (7-bit) */
#define HSI2C_SLAVE_ADDR0_10B_OR_ADDR1_10B (0x3u << HSI2C_SCR1_ADDRMODE_Pos) /*!< Address match 0 (10-bit) or Address match 1 (10-bit) */
#define HSI2C_SLAVE_ADDR0_7B_OR_ADDR1_10B  (0x4u << HSI2C_SCR1_ADDRMODE_Pos) /*!< Address match 0 (7-bit) or Address match 1 (10-bit) */
#define HSI2C_SLAVE_ADDR0_10B_OR_ADDR1_7B  (0x5u << HSI2C_SCR1_ADDRMODE_Pos) /*!< Address match 0 (10-bit) or Address match 1 (7-bit) */
#define HSI2C_SLAVE_ADDR0_7B_TO_ADDR1_7B   (0x6u << HSI2C_SCR1_ADDRMODE_Pos) /*!< From Address match 0 (7-bit) to Address match 1 (7-bit) */
#define HSI2C_SLAVE_ADDR0_10B_TO_ADDR1_10B (0x7u << HSI2C_SCR1_ADDRMODE_Pos) /*!< From Address match 0 (10-bit) to Address match 1 (10-bit) */
/**
 * @}
 */

/**
 * @defgroup HSI2C_Slave_Scr1_Func_Select HSI2C从机SCR1功能选择
 * @{
 */
#define HSI2C_SLAVE_ADRSTALL_ENABLE (HSI2C_SCR1_ADRSTALL_Msk) /*!< Address SCL stall */
#define HSI2C_SLAVE_RXSTALL_ENABLE  (HSI2C_SCR1_RXSTALL_Msk)  /*!< RX SCL stall */
#define HSI2C_SLAVE_TXDSTALL_ENABLE (HSI2C_SCR1_TXDSTALL_Msk) /*!< TX data SCL stall */
#define HSI2C_SLAVE_ACKSTALL_ENABLE (HSI2C_SCR1_ACKSTALL_Msk) /*!< ACK SCL stall */
#define HSI2C_SLAVE_GCEN_ENABLE     (HSI2C_SCR1_GCEN_Msk)     /*!< General call enable */
#define HSI2C_SLAVE_SAEN_ENABLE     (HSI2C_SCR1_SAEN_Msk)     /*!< SMBus alert enable  */
#define HSI2C_SLAVE_TXCFG_ENABLE    (HSI2C_SCR1_TXCFG_Msk)    /*!< Transmit flag configuration */
#define HSI2C_SLAVE_RXCFG_ENABLE    (HSI2C_SCR1_RXCFG_Msk)    /*!< Receive data configuration */
#define HSI2C_SLAVE_IGNACK_ENABLE   (HSI2C_SCR1_IGNACK_Msk)   /*!< Ignore NACK */
#define HSI2C_SLAVE_HSMEN_ENABLE    (HSI2C_SCR1_HSMEN_Msk)    /*!< High speed mode enable */
/**
 * @}
 */

/**
 * @defgroup HSI2C_Slave_Filter_Enable HSI2C从机控制寄存器SCR2 Glitch Filter使能选择
 * @{
 */
#define HSI2C_SLAVE_FILTER_OFF (0x0u)                  /*!< Glitch filter off */
#define HSI2C_SLAVE_FILTER_ON  (HSI2C_SCR2_FILTEN_Msk) /*!< Glitch filter on */
/**
 * @}
 */

/**
 * @defgroup HSI2C_Slave_Transfer_Ack_Nack HSI2C从机发送ACK/NACK
 * @{
 */
#define HSI2C_SLAVE_TX_ACK  (0x0u)                  /*!< Write a transmit ACK for each received word */
#define HSI2C_SLAVE_TX_NACK (HSI2C_STAR_TXNACK_Msk) /*!< Write a transmit NACK for each received word */
/**
 * @}
 */

/**
 * @}
 */
/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/
/**
 * @addtogroup HSI2C_Global_Variables HSI2C全局变量定义
 * @{
 */
extern stc_hsi2c_com_t           stcHsi2cCom;
extern en_hsi2c_status_machine_t enMasterStatusMachine;
extern stc_hsi2c_master_init_t   stcHsi2cMasterInit;
extern stc_hsi2c_slave_init_t    stcHsi2cSlaveInit;
/**
 * @}
 */
/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup HSI2C_Global_Functions HSI2C全局函数定义
 * @{
 */
en_result_t HSI2C_MasterInit(HSI2C_TypeDef *HSI2Cx, stc_hsi2c_master_init_t *pstcHsi2cInit, uint32_t u32SrcClockHz);              /* 主机初始化 */
en_result_t HSI2C_MasterBaudRateSet(HSI2C_TypeDef *HSI2Cx, const stc_hsi2c_master_init_t *pstcHsi2cInit, uint32_t u32SrcClockHz); /* 主机波特率设置 */
en_result_t HSI2C_MasterTransferInt(HSI2C_TypeDef *HSI2Cx, uint8_t *pu8Data, uint32_t u32Size);                                   /* 主机中断传输设置 */
en_result_t HSI2C_MasterTransferPoll(HSI2C_TypeDef *HSI2Cx, uint8_t *pu8Data, uint32_t u32Size, uint32_t u32Timeout);             /* 主机轮询传输 */

void        HSI2C_SlaveInit(HSI2C_TypeDef *HSI2Cx, stc_hsi2c_slave_init_t *pstcHsi2cInit, uint32_t u32SrcClockHz);   /* 从机初始化 */
en_result_t HSI2C_SlaveTransferInt(HSI2C_TypeDef *HSI2Cx, uint8_t *pu8Data, uint32_t u32Size);                       /* 从机中断传输设置 */
en_result_t HSI2C_SlaveTransferPoll(HSI2C_TypeDef *HSI2Cx, uint8_t *pu8Data, uint32_t u32Size, uint32_t u32Timeout); /* 从机轮询传输 */

void HSI2C_MasterMcfgr1Config(HSI2C_TypeDef *HSI2Cx, stc_hsi2c_master_config1_t *pstcHsi2cConfig); /* 主机配置寄存器1设置(MCFGR1寄存器设置) */
void HSI2C_MasterMcfgr2Config(HSI2C_TypeDef *HSI2Cx, stc_hsi2c_master_config2_t *pstcHsi2cConfig); /* 主机配置寄存器2设置(MCFGR2寄存器设置) */
void HSI2C_MasterMcfgr3Config(HSI2C_TypeDef *HSI2Cx, stc_hsi2c_master_config3_t *pstcHsi2cConfig); /* 主机配置寄存器3设置(MCFGR3寄存器设置) */
void HSI2C_MasterDataMatchConfig(HSI2C_TypeDef *HSI2Cx, uint32_t u32MatchValue0, uint32_t u32MatchValue1); /* 主机数据配置设置(MDMR寄存器设置) */

void HSI2C_SlaveScr1Config(HSI2C_TypeDef *HSI2Cx, stc_hsi2c_slave_control1_t *pstcHsi2cConfig); /* 从机SCR1寄存器设置 */
void HSI2C_SlaveScr2Config(HSI2C_TypeDef *HSI2Cx, stc_hsi2c_slave_control2_t *pstcHsi2cConfig); /* 从机SCR2寄存器设置 */

void HSI2C_MasterReset(HSI2C_TypeDef *HSI2Cx); /* 主机软件复位 */
void HSI2C_SlaveReset(HSI2C_TypeDef *HSI2Cx);  /* 从机软件复位 */

void HSI2C_MasterEnable(HSI2C_TypeDef *HSI2Cx);  /* 主机使能 */
void HSI2C_SlaveEnable(HSI2C_TypeDef *HSI2Cx);   /* 从机使能 */
void HSI2C_MasterDisable(HSI2C_TypeDef *HSI2Cx); /* 主机禁止 */
void HSI2C_SlaveDisable(HSI2C_TypeDef *HSI2Cx);  /* 从机禁止 */

boolean_t HSI2C_MasterFlagGet(HSI2C_TypeDef *HSI2Cx, uint32_t u32Hsi2cFlag);   /* 主机标志位获取 */
boolean_t HSI2C_SlaveFlagGet(HSI2C_TypeDef *HSI2Cx, uint32_t u32Hsi2cFlag);    /* 从机标志位获取 */
void      HSI2C_MasterFlagClear(HSI2C_TypeDef *HSI2Cx, uint32_t u32Hsi2cFlag); /* 主机标志位清除 */
void      HSI2C_SlaveFlagClear(HSI2C_TypeDef *HSI2Cx, uint32_t u32Hsi2cFlag);  /* 从机标志位清除 */

void     HSI2C_MasterIntEnable(HSI2C_TypeDef *HSI2Cx, uint32_t u32Hsi2cInt);  /* 主机中断允许 */
void     HSI2C_MasterIntDisable(HSI2C_TypeDef *HSI2Cx, uint32_t u32Hsi2cInt); /* 主机中断禁止 */
void     HSI2C_SlaveIntEnable(HSI2C_TypeDef *HSI2Cx, uint32_t u32Hsi2cInt);   /* 从机中断使能 */
void     HSI2C_SlaveIntDisable(HSI2C_TypeDef *HSI2Cx, uint32_t u32Hsi2cInt);  /* 从机中断禁止 */
uint32_t HSI2C_MasterIntGet(HSI2C_TypeDef *HSI2Cx);                           /* 主机中断使能获取 */
uint32_t HSI2C_SlaveIntGet(HSI2C_TypeDef *HSI2Cx);                            /* 从机中断使能获取 */

void                 HSI2C_MasterStart(HSI2C_TypeDef *HSI2Cx, uint8_t u8SlaveAddr, en_hsi2c_dir_t enTransDir); /* 主机Start命令 */
void                 HSI2C_MasterStop(HSI2C_TypeDef *HSI2Cx);                                                  /* 主机Stop命令 */
void                 HSI2C_MasterWriteData(HSI2C_TypeDef *HSI2Cx, uint8_t u8Data);                             /* 主机写数据 */
void                 HSI2C_MasterReceiveCmd(HSI2C_TypeDef *HSI2Cx, uint8_t u8Len);                             /* 主机读数据命令 */
en_result_t          HSI2C_MasterReadData(HSI2C_TypeDef *HSI2Cx, uint8_t *pu8Data);                            /* 主机读数据 */
en_hsi2c_com_error_t HSI2C_MasterErrorGet(uint32_t u32MasterFlag);                                             /* 主机传输Error类型输出 */
void                 HSI2C_MasterTransAbort(HSI2C_TypeDef *HSI2Cx);                                            /* 主机传输终止 */

void                 HSI2C_SlaveWriteAddr(HSI2C_TypeDef *HSI2Cx, uint16_t u16Addr0, uint16_t u16Addr1); /* 从机写地址 */
void                 HSI2C_SlaveWriteData(HSI2C_TypeDef *HSI2Cx, uint8_t u8Data);                       /* 从机写数据 */
en_result_t          HSI2C_SlaveReadData(HSI2C_TypeDef *HSI2Cx, uint8_t *pu8Data);                      /* 从机读数据 */
en_result_t          HSI2C_SlaveReadAddr(HSI2C_TypeDef *HSI2Cx, uint16_t *pu16Data);                    /* 从机读接收的地址 */
en_hsi2c_com_error_t HSI2C_SlaveErrorGet(uint32_t u32SlaveFlag);                                        /* 从机传输Error类型输出 */
void                 HSI2C_SlaveTransAbort(HSI2C_TypeDef *HSI2Cx);                                      /* 从机传输终止 */
void                 HSI2C_SlaveTransNack(HSI2C_TypeDef *HSI2Cx, uint32_t u32AckNack);                  /* 从机发送ACK/NACK */

void HSI2C_MasterStatusMachineStart(void);                /* 主机状态机控制（Start） */
void HSI2C_MasterStatusMachineSubAddr(void);              /* 主机状态机控制（Sub address） */
void HSI2C_MasterStatusMachineRestart(void);              /* 主机状态机控制（Restart） */
void HSI2C_MasterStatusMachineStop(void);                 /* 主机状态机控制（Stop） */
void HSI2C_MasterStatusMachineTrans(void);                /* 主机状态机控制（Data transfer） */
void HSI2C_MasterStatusMachineRxCmd(uint32_t *pu32RxLen); /* 主机状态机控制（Receive command） */

uint8_t HSI2C_10BitAddrMdHighBitsGet(uint16_t u16AddrData); /* 10位地址模式获取高字节 */
uint8_t HSI2C_10BitAddrMdLowBitsGet(uint16_t u16AddrData);  /* 10位地址模式获取低字节 */

void HSI2C_MasterStcInit(stc_hsi2c_master_init_t *pstcInit); /* 主机结构体初始化 */
void HSI2C_SlaveStcInit(stc_hsi2c_slave_init_t *pstcInit);   /* 从机结构体初始化 */
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

#endif /* __HSI2C_H__ */
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
