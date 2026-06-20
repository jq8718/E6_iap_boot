/**
 *******************************************************************************
 * @file  sysctrl.h
 * @brief This file contains all the functions prototypes of the SYSCTRL driver
 *        library
 @verbatim
   Change Logs:
   Date             Author          Notes
   2024-09-18       MADS            First version
   2025-05-19       MADS            Modify macro name
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

#ifndef __SYSCTRL_H__
#define __SYSCTRL_H__

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
 * @addtogroup DDL_SYSCTRL SYSCTRL模块驱动库
 * @{
 */
/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup SYSCTRL_Global_Types SYSCTRL全局类型定义
 * @{
 */

/**
 * @brief 时钟初始化配置结构体定义
 */
typedef struct
{
    uint32_t u32SysClockSrc; /*!< 系统时钟源选择 @ref SYSCTRL_Clock_Src_Select */
    uint32_t u32HclkDiv;     /*!< HCLK分频系数 @ref SYSCTRL_Hclk_Div_Select */
} stc_sysctrl_clock_init_t;

/**
 * @brief 外设模块时钟结构体定义
 */
typedef enum
{
    PeriphClockLpuart0 = (SYSCTRL_PERI_CLKEN0_LPUART0_EN_Pos),       /*!< LPUART0 */
    PeriphClockLpuart1 = (SYSCTRL_PERI_CLKEN0_LPUART1_EN_Pos),       /*!< LPUART1 */
    PeriphClockSpi     = (SYSCTRL_PERI_CLKEN0_SPI_EN_Pos),           /*!< SPI */
    PeriphClockAtim3   = (SYSCTRL_PERI_CLKEN0_ATIM3_EN_Pos),         /*!< ATIMER3 */
    PeriphClockIwdt    = (SYSCTRL_PERI_CLKEN0_IWDT_EN_Pos),          /*!< IWDT */
    PeriphClockAdc     = (SYSCTRL_PERI_CLKEN0_ADC_EN_Pos),           /*!< ADC */
    PeriphClockVc      = (SYSCTRL_PERI_CLKEN0_VC_EN_Pos),            /*!< VC */
    PeriphClockTrng    = (SYSCTRL_PERI_CLKEN0_TRNG_EN_Pos),          /*!< TRNG */
    PeriphClockRtc     = (SYSCTRL_PERI_CLKEN0_RTC_EN_Pos),           /*!< RTC */
    PeriphClockGpio    = (SYSCTRL_PERI_CLKEN0_GPIO_EN_Pos),          /*!< GPIO */
    PeriphClockHsi2c   = (SYSCTRL_PERI_CLKEN0_HSI2C_EN_Pos),         /*!< HSI2C */
    PeriphClockFlash   = (SYSCTRL_PERI_CLKEN0_FLASH_EN_Pos),         /*!< FLASH */
    PeriphClockCtim0   = (SYSCTRL_PERI_CLKEN1_CTIM0_EN_Pos + 0x20u), /*!< CTIM0 */
    PeriphClockCtim1   = (SYSCTRL_PERI_CLKEN1_CTIM1_EN_Pos + 0x20u), /*!< CTIM1 */
    PeriphClockCtrim   = (SYSCTRL_PERI_CLKEN1_CTRIM_EN_Pos + 0x20u), /*!< CTRIM */
} en_sysctrl_periph_clock_t;

/**
 * @brief 外设模块复位结构体定义
 */
typedef enum
{
    PeriphResetLpuart0 = (SYSCTRL_PERI_RESET0_LPUART0_RST_Pos),       /*!< LPUART0 */
    PeriphResetLpuart1 = (SYSCTRL_PERI_RESET0_LPUART1_RST_Pos),       /*!< LPUART1 */
    PeriphResetSpi     = (SYSCTRL_PERI_RESET0_SPI_RST_Pos),           /*!< SPI */
    PeriphResetAtim3   = (SYSCTRL_PERI_RESET0_ATIM3_RST_Pos),         /*!< ATIMER3 */
    PeriphResetAdc     = (SYSCTRL_PERI_RESET0_ADC_RST_Pos),           /*!< ADC */
    PeriphResetVc      = (SYSCTRL_PERI_RESET0_VC_RST_Pos),            /*!< VC */
    PeriphResetTrng    = (SYSCTRL_PERI_RESET0_TRNG_RST_Pos),          /*!< TRNG */
    PeriphResetRtc     = (SYSCTRL_PERI_RESET0_RTC_RST_Pos),           /*!< RTC */
    PeriphResetGpio    = (SYSCTRL_PERI_RESET0_GPIO_RST_Pos),          /*!< GPIO */
    PeriphResetHsi2c   = (SYSCTRL_PERI_RESET0_HSI2C_RST_Pos),         /*!< HSI2C */
    PeriphResetCtim0   = (SYSCTRL_PERI_RESET1_CTIM0_RST_Pos + 0x20u), /*!< CTIM0 */
    PeriphResetCtim1   = (SYSCTRL_PERI_RESET1_CTIM1_RST_Pos + 0x20u), /*!< CTIM1 */
    PeriphResetCtrim   = (SYSCTRL_PERI_RESET1_CTRIM_RST_Pos + 0x20u), /*!< CTRIM */
} en_sysctrl_periph_reset_t;
/**
 * @}
 */
/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup SYSCTRL_Global_Macros SYSCTRL全局宏定义
 * @{
 */

/**
 * @defgroup SYSCTRL_Clock_Src_Select Clock时钟源选择
 * @{
 */
#define SYSCTRL_CLK_SRC_RC48M_4M  (0x0u) /*!< 内部RC48M时钟4MHz */
#define SYSCTRL_CLK_SRC_RC48M_6M  (0x1u) /*!< 内部RC48M时钟6MHz */
#define SYSCTRL_CLK_SRC_RC48M_32M (0x2u) /*!< 内部RC48M时钟32MHz */
#define SYSCTRL_CLK_SRC_RC48M_48M (0x3u) /*!< 内部RC48M时钟48MHz */
#define SYSCTRL_CLK_SRC_EXTH      (0x4u) /*!< 从PA11输入的EXTH时钟 */
#define SYSCTRL_CLK_SRC_RCL_32768 (0x5u) /*!< 内部低速时钟RCL 32768 */
#define SYSCTRL_CLK_SRC_RCL_38400 (0x6u) /*!< 内部低速时钟RCL 38400 */
#define SYSCTRL_CLK_SRC_XTL       (0x7u) /*!< 外部低速晶振XTL */
#define SYSCTRL_CLK_SRC_EXTL      (0x8u) /*!< 从PA07输入的EXTL时钟 */
/**
 * @}
 */

/**
 * @defgroup SYSCTRL_Hclk_Div_Select HCLK分频选择
 * @{
 */
#define SYSCTRL_HCLK_PRS_DIV1   (0x0u << SYSCTRL_SYSCTRL0_HCLK_PRS_Pos) /*!< SystemClk */
#define SYSCTRL_HCLK_PRS_DIV2   (0x1u << SYSCTRL_SYSCTRL0_HCLK_PRS_Pos) /*!< SystemClk/2 */
#define SYSCTRL_HCLK_PRS_DIV4   (0x2u << SYSCTRL_SYSCTRL0_HCLK_PRS_Pos) /*!< SystemClk/4 */
#define SYSCTRL_HCLK_PRS_DIV8   (0x3u << SYSCTRL_SYSCTRL0_HCLK_PRS_Pos) /*!< SystemClk/8 */
#define SYSCTRL_HCLK_PRS_DIV16  (0x4u << SYSCTRL_SYSCTRL0_HCLK_PRS_Pos) /*!< SystemClk/16 */
#define SYSCTRL_HCLK_PRS_DIV32  (0x5u << SYSCTRL_SYSCTRL0_HCLK_PRS_Pos) /*!< SystemClk/32 */
#define SYSCTRL_HCLK_PRS_DIV64  (0x6u << SYSCTRL_SYSCTRL0_HCLK_PRS_Pos) /*!< SystemClk/64 */
#define SYSCTRL_HCLK_PRS_DIV128 (0x7u << SYSCTRL_SYSCTRL0_HCLK_PRS_Pos) /*!< SystemClk/128 */
/**
 * @}
 */

/**
 * @defgroup SYSCTRL_RC48M_Freq_Select RC48M频率选择
 * @{
 */
#define SYSCTRL_RC48M_FREQ_4M  (0x0u << SYSCTRL_RC48M_CR_FSEL_Pos) /*!< 4MHz */
#define SYSCTRL_RC48M_FREQ_6M  (0x1u << SYSCTRL_RC48M_CR_FSEL_Pos) /*!< 6MHz */
#define SYSCTRL_RC48M_FREQ_32M (0x2u << SYSCTRL_RC48M_CR_FSEL_Pos) /*!< 32MHz */
#define SYSCTRL_RC48M_FREQ_48M (0x3u << SYSCTRL_RC48M_CR_FSEL_Pos) /*!< 48MHz */
/**
 * @}
 */

/**
 * @defgroup SYSCTRL_RCL_Freq_Select RCL频率选择
 * @{
 */
#define SYSCTRL_RCL_FREQ_32768 (0x0u) /*!< 32.768KHz */
#define SYSCTRL_RCL_FREQ_38400 (0x1u) /*!< 38.4KHz */
/**
 * @}
 */

/**
 * @defgroup SYSCTRL_XTL_Drv_Select XTL驱动能力选择
 * @{
 */
#define SYSCTRL_XTL_DRV0 (0x0u << SYSCTRL_XTL_CR_DRIVER_Pos) /*!< 最弱驱动能力 */
#define SYSCTRL_XTL_DRV1 (0x1u << SYSCTRL_XTL_CR_DRIVER_Pos) /*!< 较弱驱动能力 */
#define SYSCTRL_XTL_DRV2 (0x2u << SYSCTRL_XTL_CR_DRIVER_Pos) /*!< 较强驱动能力 推荐值 */
#define SYSCTRL_XTL_DRV3 (0x3u << SYSCTRL_XTL_CR_DRIVER_Pos) /*!< 最强驱动能力 */
/**
 * @}
 */

/**
 * @defgroup SYSCTRL_XTL_Amp_Select XTL振荡幅度选择
 * @{
 */
#define SYSCTRL_XTL_AMP0 (0x0u << SYSCTRL_XTL_CR_AMP_SEL_Pos) /*!< 最小振幅 */
#define SYSCTRL_XTL_AMP1 (0x1u << SYSCTRL_XTL_CR_AMP_SEL_Pos) /*!< 正常振幅 */
#define SYSCTRL_XTL_AMP2 (0x2u << SYSCTRL_XTL_CR_AMP_SEL_Pos) /*!< 较大振幅 推荐值 */
#define SYSCTRL_XTL_AMP3 (0x3u << SYSCTRL_XTL_CR_AMP_SEL_Pos) /*!< 最大振幅 */
/**
 * @}
 */

/**
 * @defgroup SYSCTRL_XTL_Stable_Cycle_Select XTL稳定时间选择
 * @{
 */
#define SYSCTRL_XTL_STB_CYCLE4096  (0x0u << SYSCTRL_XTL_CR_STARTUP_Pos) /*!< 4096 个周期数 */
#define SYSCTRL_XTL_STB_CYCLE8192  (0x1u << SYSCTRL_XTL_CR_STARTUP_Pos) /*!< 8192 个周期数 */
#define SYSCTRL_XTL_STB_CYCLE16384 (0x2u << SYSCTRL_XTL_CR_STARTUP_Pos) /*!< 16384个周期数 推荐值 */
#define SYSCTRL_XTL_STB_CYCLE32768 (0x3u << SYSCTRL_XTL_CR_STARTUP_Pos) /*!< 32768个周期数 */
/**
 * @}
 */

/**
 * @defgroup SYSCTRL_XTL_Failure_Config XTL失效配置
 * @{
 */
#define SYSCTRL_XTL_FAILURE_DETECT_DISABLE (0x0u)                                                  /*!< 停振检测禁止 */
#define SYSCTRL_XTL_FAILURE_DETECT_2MS     (SYSCTRL_XTL_CR_DETEN_Msk)                              /*!< 停振检测使能, 2ms检测间隔 */
#define SYSCTRL_XTL_FAILURE_DETECT_8MS     (SYSCTRL_XTL_CR_DETEN_Msk | SYSCTRL_XTL_CR_DETTIME_Msk) /*!< 停振检测使能，8ms检测间隔 */
/**
 * @}
 */

/**
 * @defgroup SYSCTRL_Func_Config 系统控制模块功能配置
 * @{
 */
#define SYSCTRL_FUNC_RST_USE_IO       (SYSCTRL_SYSCTRL1_RESET_USE_IO_Msk)    /*!< RESET Pad作为GPIO使用 */
#define SYSCTRL_FUNC_EXTH_EN          (SYSCTRL_SYSCTRL1_EXTH_EN_Msk)         /*!< XTH输出时钟从PA11输入 */
#define SYSCTRL_FUNC_EXTL_EN          (SYSCTRL_SYSCTRL1_EXTL_EN_Msk)         /*!< XTL输出时钟从PA07输入 */
#define SYSCTRL_FUNC_XTL_ALWAYS_ON    (SYSCTRL_SYSCTRL1_XTL_ALWAYS_ON_Msk)   /*!< SYSCTRL0.XTL_EN只可置位 */
#define SYSCTRL_FUNC_CLK_FAULT_EN     (SYSCTRL_SYSCTRL1_CLOCK_FAULT_EN_Msk)  /*!< 时钟错误检测使能 */
#define SYSCTRL_FUNC_LOCKUP_EN        (SYSCTRL_SYSCTRL1_LOCKUP_EN_Msk)       /*!< Cortex-M0+ LockUp功能使能 */
#define SYSCTRL_FUNC_SPI_CTRL_BY_GPIO (SYSCTRL_SYSCTRL1_SPI_PCTRL_Msk)       /*!< SPI端口控制选择 */
#define SYSCTRL_FUNC_SWD_USE_IO       (SYSCTRL_SYSCTRL1_SWD_USE_IO_Msk)      /*!< SWD端口作为GPIO使用 */
#define SYSCTRL_FUNC_CTIMER0_USE_BTIM (SYSCTRL_SYSCTRL1_CTIMER0_FUN_SEL_Msk) /*!< CTIMER0作为BTIM012使用 */
#define SYSCTRL_FUNC_CTIMER1_USE_BTIM (SYSCTRL_SYSCTRL1_CTIMER1_FUN_SEL_Msk) /*!< CTIMER1作为BTIM345使用 */
/**
 * @}
 */

/**
 * @defgroup SYSCTRL_Wakeup_By_RC48M_Config Deep Sleep唤醒后system clock来源配置
 * @{
 */
#define SYSCTRL_WAKEUP_SRC_KEEP  (0x0u)                                /*!< 从Deep Sleep唤醒后，不改变system clock来源 */
#define SYSCTRL_WAKEUP_SRC_RC48M (SYSCTRL_SYSCTRL0_WAKEUP_BYRC48M_Msk) /*!< 从Deep Sleep唤醒后，system clock来源为RC48M，原时钟继续使能 */
/**
 * @}
 */

/**
 * @defgroup SYSCTRL_Reset_Flag_Select 复位标志选择
 * @{
 */
#define SYSCTRL_RST_POR5V   (SYSCTRL_RESET_FLAG_POR5V_Msk)     /*!< VCC电源域复位标志 */
#define SYSCTRL_RST_POR1P5V (SYSCTRL_RESET_FLAG_POR15V_Msk)    /*!< VCAP域复位标志 */
#define SYSCTRL_RST_LVD     (SYSCTRL_RESET_FLAG_LVD_FLAG_Msk)  /*!< LVD */
#define SYSCTRL_RST_IWDT    (SYSCTRL_RESET_FLAG_IWDT_FLAG_Msk) /*!< IWDT */
#define SYSCTRL_RST_LOCKUP  (SYSCTRL_RESET_FLAG_LOCKUP_Msk)    /*!< LOCKUP */
#define SYSCTRL_RST_SYSREQ  (SYSCTRL_RESET_FLAG_SYSREQ_Msk)    /*!< SYSREQ */
#define SYSCTRL_RST_RSTB    (SYSCTRL_RESET_FLAG_RSTB_Msk)      /*!< Pad Reset */
/**
 * @}
 */

/**
 * @defgroup SYSCTRL_Debug_Active_Config 调试模式下各模块工作状态配置
 * @{
 */
#define SYSCTRL_DEBUG_IWDT_ACTIVE  (SYSCTRL_DEBUG_ACTIVE_IWDT_DEBUG_Msk)  /*!< IWDT */
#define SYSCTRL_DEBUG_RTC_ACTIVE   (SYSCTRL_DEBUG_ACTIVE_RTC_DEBUG_Msk)   /*!< RTC */
#define SYSCTRL_DEBUG_ATIM3_ACTIVE (SYSCTRL_DEBUG_ACTIVE_ATIM3_DEBUG_Msk) /*!< ATIMER3 */
#define SYSCTRL_DEBUG_CTIM0_ACTIVE (SYSCTRL_DEBUG_ACTIVE_CTIM0_DEBUG_Msk) /*!< CTIM0 */
#define SYSCTRL_DEBUG_CTIM1_ACTIVE (SYSCTRL_DEBUG_ACTIVE_CTIM1_DEBUG_Msk) /*!< CTIM1 */
/**
 * @}
 */

/**
 * @defgroup SYSCTRL_Unlock SYSCTRL寄存器解锁
 * @{
 */
#define SYSCTRL_SysctrlUnlock() \
    do \
    { \
        WRITE_REG16(SYSCTRL->SYSCTRL2, 0x5A5Au); \
        WRITE_REG16(SYSCTRL->SYSCTRL2, 0xA5A5u); \
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
 * @addtogroup SYSCTRL_Global_Functions SYSCTRL全局函数定义
 * @{
 */
en_result_t SYSCTRL_ClockInit(stc_sysctrl_clock_init_t *pstcClocklInit); /* 时钟初始化函数 */
void        SYSCTRL_ClockDeInit(void);                                   /* 时钟去初始化函数 */

en_result_t SYSCTRL_ClockSrcEnable(uint32_t u32ClockSrc);  /* 时钟源使能 */
en_result_t SYSCTRL_ClockSrcDisable(uint32_t u32ClockSrc); /* 系统时钟源禁止 */
en_result_t SYSCTRL_SysClockSwitch(uint32_t u32ClockSrc);  /* 系统时钟切换 */

void     SYSCTRL_HclkDivSet(uint32_t u32HclkDiv); /* 系统时钟（Hclk）分频设定 */
uint32_t SYSCTRL_HclkFreqGet(void);               /* 系统时钟（Hclk）频率值获取 */

void SYSCTRL_RC48MTrimSet(uint32_t u32Rc48mFre); /* 内部高速时钟RC48M频率TRIM值加载 */
void SYSCTRL_RCLTrimSet(uint32_t u32RclFre);     /* 内部低速时钟RCL频率TRIM值加载 */

void      SYSCTRL_XTLStableTimeSet(uint32_t u32XtlStableTime);          /* 外部低速时钟稳定周期配置 */
void      SYSCTRL_XTLDrvConfig(uint32_t u32XtlAmp, uint32_t u32XtlDrv); /* 外部低速晶振驱动配置 */
void      SYSCTRL_XTLFailureConfig(uint32_t u32XtlFailure);             /* 外部低速晶振停振检测配置 */
void      SYSCTRL_XTLFailureIntEnable(void);                            /* 使能XTL失效检测中断 */
void      SYSCTRL_XTLFailureIntDisable(void);                           /* 禁止XTL失效检测中断 */
boolean_t SYSCTRL_XTLFailureIntFlagGet(void);                           /* 获取XTL失效检测中断标志 */
void      SYSCTRL_XTLFailureIntFlagClear(void);                         /* 清除XTL失效检测中断标志 */
void      SYSCTRL_XTLAlwaysOnEnable(void);                              /* XTL always on使能 */
void      SYSCTRL_XTLAlwaysOnDisable(void);                             /* XTL always on禁止 */

void      SYSCTRL_PeriphClockEnable(en_sysctrl_periph_clock_t enPeriph);    /* 外设时钟使能 */
void      SYSCTRL_PeriphClockDisable(en_sysctrl_periph_clock_t enPeriph);   /* 外设时钟禁止 */
boolean_t SYSCTRL_PeriphClockStatusGet(en_sysctrl_periph_clock_t enPeriph); /* 获得外设时钟门控开关状态 */

void SYSCTRL_FuncEnable(uint32_t u32Func);  /* 系统功能使能 */
void SYSCTRL_FuncDisable(uint32_t u32Func); /* 系统功能禁止 */

void SYSCTRL_WakeupByRC48M(uint32_t u32WakeupSrc); /* 从Deep Sleep唤醒后system clock来源配置 */

void      SYSCTRL_PeriphReset(en_sysctrl_periph_reset_t enPeriph); /* 外设模块复位 */
boolean_t SYSCTRL_ResetFlagGet(uint32_t u32ResetFlag);             /* 获取复位源类型 */
void      SYSCTRL_ResetFlagClear(uint32_t u32ResetFlag);           /* 清除复位源类型 */
void      SYSCTRL_ResetFlagClearAll(void);                         /* 清除所有复位源类型 */

void SYSCTRL_DebugActiveEnable(uint32_t u32DebugActiveConfig);  /* 在SWD调试模式下，使能模块计数功能 */
void SYSCTRL_DebugActiveDisable(uint32_t u32DebugActiveConfig); /* 在SWD调试模式下，暂停模块计数功能 */

void SYSCTRL_ClockStcInit(stc_sysctrl_clock_init_t *pstcInit); /* 结构体初始化 */
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

#endif /* __SYSCTRL_H__ */
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
