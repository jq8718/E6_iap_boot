/**
 *******************************************************************************
 * @file  sysctrl.c
 * @brief This file provides firmware functions to manage the SYSCTRL
 @verbatim
   Change Logs:
   Date             Author          Notes
   2024-09-18       MADS            First version
   2025-09-09       MADS            Change RCL trim address to 32-bit
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "sysctrl.h"

/**
 * @addtogroup HC32L021_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_SYSCTRL SYSCTRL模块驱动库
 * @brief Sysctrl Driver Library SYSCTRL模块驱动库
 * @{
 */
/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup SYSCTRL_Local_Macros SYSCTRL局部宏定义
 * @{
 */

/**
 * @brief  RCL Trim值
 */
#define RCL_CR_TRIM_38400_VAL (*((volatile uint32_t *)(0x001007ACul)))
#define RCL_CR_TRIM_32768_VAL (*((volatile uint32_t *)(0x001007A8ul)))

/**
 * @brief  RC48M Trim值
 */
#define RC48M_CR_TRIM_48M_VAL (*((volatile uint32_t *)(0x001007B0ul)))
#define RC48M_CR_TRIM_32M_VAL (*((volatile uint32_t *)(0x001007B4ul)))
#define RC48M_CR_TRIM_6M_VAL  (*((volatile uint32_t *)(0x001007B8ul)))
#define RC48M_CR_TRIM_4M_VAL  (*((volatile uint32_t *)(0x001007BCul)))

/**
 * @brief  Clock时钟源切换选择
 */
#define SYSCTRL_CLK_SWITCH_RC48M (0x0u << SYSCTRL_SYSCTRL0_CLKSW_Pos) /*!< 内部RC48M时钟 */
#define SYSCTRL_CLK_SWITCH_EXTH  (0x1u << SYSCTRL_SYSCTRL0_CLKSW_Pos) /*!< 从PA11输入的EXTH时钟 */
#define SYSCTRL_CLK_SWITCH_RCL   (0x2u << SYSCTRL_SYSCTRL0_CLKSW_Pos) /*!< 内部低速时钟RCL */
#define SYSCTRL_CLK_SWITCH_XTL   (0x3u << SYSCTRL_SYSCTRL0_CLKSW_Pos) /*!< 外部低速晶振XTL或从PA07输入的EXTL时钟 */
/**
 * @}
 */
/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup SYSCTRL_Global_Functions SYSCTRL全局函数定义
 * @{
 */

/**
 * @brief  时钟初始化函数 (用于上电后，系统工作之前对主频及外设时钟进行初始化)
 * @param  [in] pstcClocklInit 初始化配置结构体指针 @ref stc_sysctrl_clock_init_t
 * @retval en_result_t
 *           - Ok: 成功
 *           - ErrorInvalidParameter：无效参数
 * @note   若使用外部晶振，用户需根据实际情况提前设置好其相关参数，如振幅、驱动能力等
 * @note   本驱动默认宏定义：SYSTEM_EXTH=8MHz,SYSTEM_EXTL=32768Hz,如使用其它频率外部时钟或晶振，必须修改这两个宏定义的值
 * @note   如手动修改或者调用CTRIM修改RC48M/RCL时钟的TRIM值，需根据实际频率值设置正确的FLASH wait cycle
 */
en_result_t SYSCTRL_ClockInit(stc_sysctrl_clock_init_t *pstcClocklInit)
{
    if (pstcClocklInit->u32SysClockSrc > SYSCTRL_CLK_SRC_EXTL)
    {
        return ErrorInvalidParameter;
    }

    /* 时钟源使能 */
    SYSCTRL_ClockSrcEnable(pstcClocklInit->u32SysClockSrc);

    /* 设置FLASH wait cycle = 1 */
    WRITE_REG16(FLASH->BYPASS, 0x5A5Au);
    WRITE_REG16(FLASH->BYPASS, 0xA5A5u);
    MODIFY_REG32(FLASH->CR, FLASH_CR_WAIT_Msk, 0x1u << FLASH_CR_WAIT_Pos);

    /* 时钟源切换 */
    SYSCTRL_SysClockSwitch(pstcClocklInit->u32SysClockSrc);

    /* HCLK分频设置 */
    SYSCTRL_HclkDivSet(pstcClocklInit->u32HclkDiv);

    /* 更新Core时钟（HCLK）*/
    SystemCoreClockUpdate();
    /* 设置FLASH wait cycle */
    if (SystemCoreClock <= 24000000u)
    {
        if (READ_REG32_BIT(FLASH->CR, FLASH_CR_WAIT_Msk) != (0x0u << FLASH_CR_WAIT_Pos))
        {
            WRITE_REG16(FLASH->BYPASS, 0x5A5Au);
            WRITE_REG16(FLASH->BYPASS, 0xA5A5u);
            MODIFY_REG32(FLASH->CR, FLASH_CR_WAIT_Msk, 0x0u << FLASH_CR_WAIT_Pos); /* <= 24MHz, 设置FLASH wait cycle = 0 */
        }
    }

    return Ok;
}

/**
 * @brief  时钟源使能
 * @param  [in] u32ClockSrc 目标时钟源 @ref SYSCTRL_Clock_Src_Select
 * @retval en_result_t
 *           - Ok: 成功
 *           - ErrorInvalidParameter：无效参数
 * @note   调用此函数使能时钟之前，必须先设置目标时钟的相关参数，如驱动能力、稳定时间等
 */
en_result_t SYSCTRL_ClockSrcEnable(uint32_t u32ClockSrc)
{
    en_result_t enRet = Ok;

    if (u32ClockSrc > SYSCTRL_CLK_SRC_EXTL)
    {
        return ErrorInvalidParameter;
    }

    switch (u32ClockSrc)
    {
        case SYSCTRL_CLK_SRC_RC48M_4M:
        case SYSCTRL_CLK_SRC_RC48M_6M:
        case SYSCTRL_CLK_SRC_RC48M_32M:
        case SYSCTRL_CLK_SRC_RC48M_48M:
            if (READ_REG32_BIT(SYSCTRL->SYSCTRL0, SYSCTRL_SYSCTRL0_RC48M_EN_Msk) == 0u) /* RC48M关闭*/
            {
                SYSCTRL_SysctrlUnlock();
                SET_REG32_BIT(SYSCTRL->SYSCTRL0, SYSCTRL_SYSCTRL0_RC48M_EN_Msk);                                      /* 使能RC48M */
                while (READ_REG32_BIT(SYSCTRL->RC48M_CR, SYSCTRL_RC48M_CR_STABLE_Msk) != SYSCTRL_RC48M_CR_STABLE_Msk) /* 等待RC48M时钟稳定 */
                {
                    ;
                }
            }
            break;
        case SYSCTRL_CLK_SRC_EXTH:
            if (READ_REG32_BIT(SYSCTRL->SYSCTRL1, SYSCTRL_SYSCTRL1_EXTH_EN_Msk) == 0u) /* EXTH时钟输入关闭*/
            {
                SET_REG32_BIT(SYSCTRL->PERI_CLKEN0, SYSCTRL_PERI_CLKEN0_GPIO_EN_Msk); /* 使能GPIO外设时钟 */
                CLR_REG32_BIT(GPIOA->ADS, GPIO_ADS_PIN11_Msk);                        /* 配置为数字端口 */
                CLR_REG32_BIT(GPIOA->PIN11_SEL, GPIO_PIN11_SEL_SEL_Msk);              /* 设置为GPIO */
                SET_REG32_BIT(GPIOA->DIR, GPIO_DIR_PIN11_Msk);                        /* 配置为输入 */
                SYSCTRL_SysctrlUnlock();
                SET_REG32_BIT(SYSCTRL->SYSCTRL1, SYSCTRL_SYSCTRL1_EXTH_EN_Msk); /* 使能EXTH时钟输入 */
            }
            break;
        case SYSCTRL_CLK_SRC_RCL_32768:
        case SYSCTRL_CLK_SRC_RCL_38400:
            if (READ_REG32_BIT(SYSCTRL->SYSCTRL0, SYSCTRL_SYSCTRL0_RCL_EN_Msk) == 0u) /* RCL关闭*/
            {
                SYSCTRL_SysctrlUnlock();
                SET_REG32_BIT(SYSCTRL->SYSCTRL0, SYSCTRL_SYSCTRL0_RCL_EN_Msk);                                  /* 使能RCL */
                while (READ_REG32_BIT(SYSCTRL->RCL_CR, SYSCTRL_RCL_CR_STABLE_Msk) != SYSCTRL_RCL_CR_STABLE_Msk) /* 等待RCL时钟稳定 */
                {
                    ;
                }
            }
            break;
        case SYSCTRL_CLK_SRC_XTL:
            if (READ_REG32_BIT(SYSCTRL->SYSCTRL0, SYSCTRL_SYSCTRL0_XTL_EN_Msk) == 0u) /* XTL关闭*/
            {
                SYSCTRL_SysctrlUnlock();
                SET_REG32_BIT(SYSCTRL->SYSCTRL0, SYSCTRL_SYSCTRL0_XTL_EN_Msk); /* 使能XTL */
                SYSCTRL_SysctrlUnlock();
                CLR_REG32_BIT(SYSCTRL->SYSCTRL1, SYSCTRL_SYSCTRL1_EXTL_EN_Msk);                                 /* 禁止EXTL */
                while (READ_REG32_BIT(SYSCTRL->XTL_CR, SYSCTRL_XTL_CR_STABLE_Msk) != SYSCTRL_XTL_CR_STABLE_Msk) /* 等待XTL时钟稳定 */
                {
                    ;
                }
            }
            break;
        case SYSCTRL_CLK_SRC_EXTL:
            if (READ_REG32_BIT(SYSCTRL->SYSCTRL1, SYSCTRL_SYSCTRL1_EXTL_EN_Msk) == 0u) /* EXTL时钟输入关闭*/
            {
                SET_REG32_BIT(SYSCTRL->PERI_CLKEN0, SYSCTRL_PERI_CLKEN0_GPIO_EN_Msk); /* 使能GPIO外设时钟 */
                CLR_REG32_BIT(GPIOA->ADS, GPIO_ADS_PIN07_Msk);                        /* 配置为数字端口 */
                CLR_REG32_BIT(GPIOA->PIN07_SEL, GPIO_PIN07_SEL_SEL_Msk);              /* 设置为GPIO */
                SET_REG32_BIT(GPIOA->DIR, GPIO_DIR_PIN07_Msk);                        /* 配置为输入 */
                SYSCTRL_SysctrlUnlock();
                SET_REG32_BIT(SYSCTRL->SYSCTRL1, SYSCTRL_SYSCTRL1_EXTL_EN_Msk);                                 /* 使能EXTL时钟输入 */
                while (READ_REG32_BIT(SYSCTRL->XTL_CR, SYSCTRL_XTL_CR_STABLE_Msk) != SYSCTRL_XTL_CR_STABLE_Msk) /* 等待EXTL时钟稳定 */
                {
                    ;
                }
                SYSCTRL_SysctrlUnlock();
                CLR_REG32_BIT(SYSCTRL->SYSCTRL0, SYSCTRL_SYSCTRL0_XTL_EN_Msk); /* 禁止XTL */
            }
            break;
        default:
            enRet = ErrorInvalidParameter;
            break;
    }
    return enRet;
}

/**
 * @brief  系统时钟源禁止
 * @param  [in] u32ClockSrc 目标时钟源 @ref SYSCTRL_Clock_Src_Select
 * @retval en_result_t
 *           - Ok: 设定成功
 *           - ErrorInvalidParameter：无效参数
 * @note   系统时钟源禁止前，必须确认被关闭的时钟源没有被使用
 */
en_result_t SYSCTRL_ClockSrcDisable(uint32_t u32ClockSrc)
{
    en_result_t enRet = Ok;

    if (u32ClockSrc > SYSCTRL_CLK_SRC_EXTL)
    {
        return ErrorInvalidParameter;
    }

    switch (u32ClockSrc)
    {
        case SYSCTRL_CLK_SRC_RC48M_4M:
        case SYSCTRL_CLK_SRC_RC48M_6M:
        case SYSCTRL_CLK_SRC_RC48M_32M:
        case SYSCTRL_CLK_SRC_RC48M_48M:
            SYSCTRL_SysctrlUnlock();
            CLR_REG32_BIT(SYSCTRL->SYSCTRL0, SYSCTRL_SYSCTRL0_RC48M_EN_Msk); /* 禁止RC48M */
            break;
        case SYSCTRL_CLK_SRC_EXTH:
            SYSCTRL_SysctrlUnlock();
            CLR_REG32_BIT(SYSCTRL->SYSCTRL1, SYSCTRL_SYSCTRL1_EXTH_EN_Msk); /* 禁止EXTH时钟输入 */
            break;
        case SYSCTRL_CLK_SRC_RCL_32768:
        case SYSCTRL_CLK_SRC_RCL_38400:
            SYSCTRL_SysctrlUnlock();
            CLR_REG32_BIT(SYSCTRL->SYSCTRL0, SYSCTRL_SYSCTRL0_RCL_EN_Msk); /* 禁止RCL */
            break;
        case SYSCTRL_CLK_SRC_XTL:
            SYSCTRL_SysctrlUnlock();
            CLR_REG32_BIT(SYSCTRL->SYSCTRL0, SYSCTRL_SYSCTRL0_XTL_EN_Msk); /* 禁止XTL */
            break;
        case SYSCTRL_CLK_SRC_EXTL:
            SYSCTRL_SysctrlUnlock();
            CLR_REG32_BIT(SYSCTRL->SYSCTRL1, SYSCTRL_SYSCTRL1_EXTL_EN_Msk); /* 禁止EXTL时钟输入 */
            break;
        default:
            enRet = ErrorInvalidParameter;
            break;
    }
    return enRet;
}

/**
 * @brief  系统时钟切换
 * @param  [in] u32ClockSrc 时钟源 @ref SYSCTRL_Clock_Src_Select
 * @retval en_result_t
 *           - Ok: 设定成功
 *           - ErrorInvalidParameter：无效参数
 * @note   调用此函数前，必须确保新的系统时钟源的相关参数已经初始化，并且新时钟源已经使能且稳定运行
 * @note   本驱动默认宏定义：SYSTEM_EXTH=8MHz,SYSTEM_EXTL=32768Hz,如使用其它外部晶振值，必须修改这两个宏定义的值
 * @note   如手动修改或者调用CTRIM修改RC48M/RCL时钟的TRIM值，必须根据实际频率值设置正确的FLASH wait cycle
 * @note   如单独调用该函数，必须根据实际频率值设置正确的FLASH wait cycle
 */
en_result_t SYSCTRL_SysClockSwitch(uint32_t u32ClockSrc)
{
    if (u32ClockSrc > SYSCTRL_CLK_SRC_EXTL)
    {
        return ErrorInvalidParameter;
    }

    /* 加载Trim值 */
    switch (u32ClockSrc)
    {
        case SYSCTRL_CLK_SRC_RC48M_4M:
            /* 加载4M Trim值 */
            SYSCTRL->RC48M_CR = RC48M_CR_TRIM_4M_VAL;
            break;
        case SYSCTRL_CLK_SRC_RC48M_6M:
            /* 加载6M Trim值 */
            SYSCTRL->RC48M_CR = RC48M_CR_TRIM_6M_VAL;
            break;
        case SYSCTRL_CLK_SRC_RC48M_32M:
            /* 加载32M Trim值 */
            SYSCTRL->RC48M_CR = RC48M_CR_TRIM_32M_VAL;
            break;
        case SYSCTRL_CLK_SRC_RC48M_48M:
            /* 加载48M Trim值 */
            SYSCTRL->RC48M_CR = RC48M_CR_TRIM_48M_VAL;
            break;
        case SYSCTRL_CLK_SRC_EXTH:
            break;
        case SYSCTRL_CLK_SRC_RCL_32768:
            /* 加载32768 Trim值 */
            SYSCTRL->RCL_CR = RCL_CR_TRIM_32768_VAL;
            break;
        case SYSCTRL_CLK_SRC_RCL_38400:
            /* 加载38400 Trim值 */
            SYSCTRL->RCL_CR = RCL_CR_TRIM_38400_VAL;
            break;
        case SYSCTRL_CLK_SRC_XTL:
            break;
        case SYSCTRL_CLK_SRC_EXTL:
            break;
        default:
            break;
    }

    /* 切换时钟源 */
    switch (u32ClockSrc)
    {
        case SYSCTRL_CLK_SRC_RC48M_4M:
        case SYSCTRL_CLK_SRC_RC48M_6M:
        case SYSCTRL_CLK_SRC_RC48M_32M:
        case SYSCTRL_CLK_SRC_RC48M_48M:
            SYSCTRL_SysctrlUnlock();
            MODIFY_REG32(SYSCTRL->SYSCTRL0, SYSCTRL_SYSCTRL0_CLKSW_Msk, SYSCTRL_CLK_SWITCH_RC48M);
            break;
        case SYSCTRL_CLK_SRC_EXTH:
            SYSCTRL_SysctrlUnlock();
            MODIFY_REG32(SYSCTRL->SYSCTRL0, SYSCTRL_SYSCTRL0_CLKSW_Msk, SYSCTRL_CLK_SWITCH_EXTH);
            break;
        case SYSCTRL_CLK_SRC_RCL_32768:
        case SYSCTRL_CLK_SRC_RCL_38400:
            SYSCTRL_SysctrlUnlock();
            MODIFY_REG32(SYSCTRL->SYSCTRL0, SYSCTRL_SYSCTRL0_CLKSW_Msk, SYSCTRL_CLK_SWITCH_RCL);
            break;
        case SYSCTRL_CLK_SRC_XTL:
        case SYSCTRL_CLK_SRC_EXTL:
            SYSCTRL_SysctrlUnlock();
            MODIFY_REG32(SYSCTRL->SYSCTRL0, SYSCTRL_SYSCTRL0_CLKSW_Msk, SYSCTRL_CLK_SWITCH_XTL);
            break;
        default:
            break;
    }

    return Ok;
}

/**
 * @brief  系统时钟（HCLK）分频设定
 * @param  [in] u32HclkDiv 分频设定值 @ref SYSCTRL_Hclk_Div_Select
 * @retval None
 * @note   如单独调用该函数，必须根据实际频率值设置正确的FLASH wait cycle
 */
void SYSCTRL_HclkDivSet(uint32_t u32HclkDiv)
{
    SYSCTRL_SysctrlUnlock();
    MODIFY_REG32(SYSCTRL->SYSCTRL0, SYSCTRL_SYSCTRL0_HCLK_PRS_Msk, u32HclkDiv);
}

/**
 * @brief  系统时钟（HCLK）频率值获取
 * @retval uint32_t HCLK频率值
 * @note   本驱动默认宏定义：SYSTEM_EXTH=8MHz,SYSTEM_EXTL=32768Hz,如使用其它频率外部时钟或晶振，必须修改这两个宏定义的值
 * @note   如果手动修改或者调用CTRIM修改RC48M/RCL时钟的TRIM值，必须修改为实际时钟频率值
 */

uint32_t SYSCTRL_HclkFreqGet(void)
{
    uint32_t u32Fre         = 0u;
    uint32_t u32Temp        = 0u;
    uint32_t u32ClockSwitch = READ_REG32_BIT(SYSCTRL->SYSCTRL0, SYSCTRL_SYSCTRL0_CLKSW_Msk);

    switch (u32ClockSwitch)
    {
        case SYSCTRL_CLK_SWITCH_RC48M:
            u32Temp = READ_REG32_BIT(SYSCTRL->RC48M_CR, SYSCTRL_RC48M_CR_FSEL_Msk);
            switch (u32Temp)
            {
                case SYSCTRL_RC48M_FREQ_4M:
                    u32Fre = 4000000u;
                    break;
                case SYSCTRL_RC48M_FREQ_6M:
                    u32Fre = 6000000u;
                    break;
                case SYSCTRL_RC48M_FREQ_32M:
                    u32Fre = 32000000u;
                    break;
                case SYSCTRL_RC48M_FREQ_48M:
                    u32Fre = 48000000u;
                    break;
                default:
                    break;
            }
            break;
        case SYSCTRL_CLK_SWITCH_EXTH:
            u32Fre = SYSTEM_EXTH;
            break;
        case SYSCTRL_CLK_SWITCH_RCL:
            u32Temp = SYSCTRL->RCL_CR;
            if (u32Temp == RCL_CR_TRIM_32768_VAL)
            {
                u32Fre = 32768u;
            }
            else if (u32Temp == RCL_CR_TRIM_38400_VAL)
            {
                u32Fre = 38400u;
            }
            else
            {
                ;
            }
            break;
        case SYSCTRL_CLK_SWITCH_XTL:
            u32Fre = SYSTEM_EXTL;
            break;
        default:
            break;
    }

    return (u32Fre >> SYSCTRL->SYSCTRL0_f.HCLK_PRS);
}

/**
 * @brief  内部高速时钟RC48M频率TRIM值加载
 * @param  [in] u32Rc48mFre 设定的RC48M目标频率值 @ref SYSCTRL_RC48M_Freq_Select
 * @retval None
 */
void SYSCTRL_RC48MTrimSet(uint32_t u32Rc48mFre)
{
    /* 加载Trim值 */
    switch (u32Rc48mFre)
    {
        case SYSCTRL_RC48M_FREQ_4M:
            /* 加载4M Trim值 */
            SYSCTRL->RC48M_CR = RC48M_CR_TRIM_4M_VAL;
            break;
        case SYSCTRL_RC48M_FREQ_6M:
            /* 加载6M Trim值 */
            SYSCTRL->RC48M_CR = RC48M_CR_TRIM_6M_VAL;
            break;
        case SYSCTRL_RC48M_FREQ_32M:
            /* 加载32M Trim值 */
            SYSCTRL->RC48M_CR = RC48M_CR_TRIM_32M_VAL;
            break;
        case SYSCTRL_RC48M_FREQ_48M:
            /* 加载48M Trim值 */
            SYSCTRL->RC48M_CR = RC48M_CR_TRIM_48M_VAL;
            break;
        default:
            break;
    }
}

/**
 * @brief  内部低速时钟RCL频率TRIM值加载
 * @param  [in] u32RclFre 设定的RCL目标频率值 @ref SYSCTRL_RCL_Freq_Select
 * @retval None
 */
void SYSCTRL_RCLTrimSet(uint32_t u32RclFre)
{
    if (u32RclFre == SYSCTRL_RCL_FREQ_32768)
    {
        /* 加载32768 Trim值 */
        SYSCTRL->RCL_CR = RCL_CR_TRIM_32768_VAL;
    }
    else
    {
        /* 加载38400 Trim值 */
        SYSCTRL->RCL_CR = RCL_CR_TRIM_38400_VAL;
    }
}

/**
 * @brief  外部低速时钟稳定周期配置
 * @param  [in] u32XtlStableTime 外部低速时钟稳定周期设置 @ref SYSCTRL_XTL_Stable_Cycle_Select
 * @retval None
 */
void SYSCTRL_XTLStableTimeSet(uint32_t u32XtlStableTime)
{
    MODIFY_REG32(SYSCTRL->XTL_CR, SYSCTRL_XTL_CR_STARTUP_Msk, u32XtlStableTime);
}

/**
 * @brief  外部低速晶振驱动配置
 * @param  [in] u32XtlAmp 外部低速晶振幅选择 @ref SYSCTRL_XTL_Amp_Select
 * @param  [in] u32XtlDrv 外部低速晶振驱动能力选择 @ref SYSCTRL_XTL_Drv_Select
 * @retval None
 */
void SYSCTRL_XTLDrvConfig(uint32_t u32XtlAmp, uint32_t u32XtlDrv)
{
    MODIFY_REG32(SYSCTRL->XTL_CR, SYSCTRL_XTL_CR_AMP_SEL_Msk | SYSCTRL_XTL_CR_DRIVER_Msk, u32XtlAmp | u32XtlDrv);
}

/**
 * @brief  外部低速晶振停振检测配置
 * @param  [in] u32XtlFailure XTL停振检测配置 @ref SYSCTRL_XTL_Failure_Config
 * @retval None
 * @note   当XTL_EN=1时，不要修改DETTIME位
 */
void SYSCTRL_XTLFailureConfig(uint32_t u32XtlFailure)
{
    if (READ_REG32_BIT(SYSCTRL->SYSCTRL0, SYSCTRL_SYSCTRL0_XTL_EN_Msk) == 0u)
    {
        MODIFY_REG32(SYSCTRL->XTL_CR, SYSCTRL_XTL_CR_DETTIME_Msk, u32XtlFailure);
    }
    MODIFY_REG32(SYSCTRL->XTL_CR, SYSCTRL_XTL_CR_DETEN_Msk, u32XtlFailure);
}

/**
 * @brief  使能XTL失效检测中断
 * @retval None
 */
void SYSCTRL_XTLFailureIntEnable(void)
{
    SET_REG32_BIT(SYSCTRL->XTL_CR, SYSCTRL_XTL_CR_DETIE_Msk);
}

/**
 * @brief  禁止XTL失效检测中断
 * @retval None
 */
void SYSCTRL_XTLFailureIntDisable(void)
{
    CLR_REG32_BIT(SYSCTRL->XTL_CR, SYSCTRL_XTL_CR_DETIE_Msk);
}

/**
 * @brief  获取XTL失效检测中断标志
 * @retval boolean_t
 *           - TRUE: 中断标志置位
 *           - FALSE: 中断标志未置位
 */
boolean_t SYSCTRL_XTLFailureIntFlagGet(void)
{
    return READ_REG32_BIT(SYSCTRL->XTL_CR, SYSCTRL_XTL_CR_FAULT_STATE_Msk) ? TRUE : FALSE;
}

/**
 * @brief  清除XTL失效检测中断标志
 * @retval None
 */
void SYSCTRL_XTLFailureIntFlagClear(void)
{
    CLR_REG32_BIT(SYSCTRL->XTL_CR, SYSCTRL_XTL_CR_FAULT_STATE_Msk);
}

/**
 * @brief  XTL always on使能
 * @retval None
 */
void SYSCTRL_XTLAlwaysOnEnable(void)
{
    SYSCTRL_SysctrlUnlock();
    SET_REG32_BIT(SYSCTRL->SYSCTRL1, SYSCTRL_SYSCTRL1_XTL_ALWAYS_ON_Msk);
}

/**
 * @brief  XTL always on禁止
 * @retval None
 */
void SYSCTRL_XTLAlwaysOnDisable(void)
{
    SYSCTRL_SysctrlUnlock();
    CLR_REG32_BIT(SYSCTRL->SYSCTRL1, SYSCTRL_SYSCTRL1_XTL_ALWAYS_ON_Msk);
}

/**
 * @brief  外设时钟使能
 * @param  [in] enPeriph 目标外设 @ref en_sysctrl_periph_clock_t
 * @retval None
 */
void SYSCTRL_PeriphClockEnable(en_sysctrl_periph_clock_t enPeriph)
{
    if (enPeriph & 0x20u)
    {
        enPeriph &= ~0x20u;
        SET_REG32_BIT(SYSCTRL->PERI_CLKEN1, 0x1u << enPeriph);
    }
    else
    {
        SET_REG32_BIT(SYSCTRL->PERI_CLKEN0, 0x1u << enPeriph);
    }
}

/**
 * @brief  外设时钟禁止
 * @param  [in] enPeriph 目标外设 @ref en_sysctrl_periph_clock_t
 * @retval None
 */
void SYSCTRL_PeriphClockDisable(en_sysctrl_periph_clock_t enPeriph)
{
    if (enPeriph & 0x20u)
    {
        enPeriph &= ~0x20u;
        CLR_REG32_BIT(SYSCTRL->PERI_CLKEN1, 0x1u << enPeriph);
    }
    else
    {
        CLR_REG32_BIT(SYSCTRL->PERI_CLKEN0, 0x1u << enPeriph);
    }
}

/**
 * @brief  获得外设时钟门控开关状态
 * @param  [in] enPeripheral 目标外设 @ref en_sysctrl_periph_clock_t
 * @retval boolean_t
 *           - TRUE: 开启
 *           - FALSE: 关闭
 */
boolean_t SYSCTRL_PeriphClockStatusGet(en_sysctrl_periph_clock_t enPeriph)
{
    if (enPeriph & 0x20u)
    {
        enPeriph &= ~0x20u;
        return READ_REG32_BIT(SYSCTRL->PERI_CLKEN1, 0x1u << enPeriph) ? TRUE : FALSE;
    }
    else
    {
        return READ_REG32_BIT(SYSCTRL->PERI_CLKEN0, 0x1u << enPeriph) ? TRUE : FALSE;
    }
}

/**
 * @brief 系统功能使能
 * @param [in] u32Func 系统功能类型 @ref SYSCTRL_Func_Config
 * @retval None
 */
void SYSCTRL_FuncEnable(uint32_t u32Func)
{
    SYSCTRL_SysctrlUnlock();
    SET_REG32_BIT(SYSCTRL->SYSCTRL1, u32Func);
}

/**
 * @brief 系统功能禁止
 * @param [in] u32Func 系统功能类型 @ref SYSCTRL_Func_Config
 * @retval None
 */
void SYSCTRL_FuncDisable(uint32_t u32Func)
{
    SYSCTRL_SysctrlUnlock();
    CLR_REG32_BIT(SYSCTRL->SYSCTRL1, u32Func);
}

/**
 * @brief  从Deep Sleep唤醒后system clock来源配置
 * @param  [in] u32WakeupSrc 从Deep Sleep唤醒后system clock来源 @ref SYSCTRL_Wakeup_By_RC48M_Config
 * @retval None
 */
void SYSCTRL_WakeupByRC48M(uint32_t u32WakeupSrc)
{
    SYSCTRL_SysctrlUnlock();
    MODIFY_REG32(SYSCTRL->SYSCTRL0, SYSCTRL_SYSCTRL0_WAKEUP_BYRC48M_Msk, u32WakeupSrc);
}

/**
 * @brief  时钟去初始化函数
 * @retval None
 */
void SYSCTRL_ClockDeInit(void)
{
    /* 时钟源使能 */
    SYSCTRL_ClockSrcEnable(SYSCTRL_CLK_SRC_RC48M_4M);

    /* 时钟源切换 */
    SYSCTRL_SysClockSwitch(SYSCTRL_CLK_SRC_RC48M_4M);

    /* 其它时钟源使能关闭 */
    SYSCTRL_ClockSrcDisable(SYSCTRL_CLK_SRC_EXTH);      /* 禁止EXTH端口输入时钟 */
    SYSCTRL_ClockSrcDisable(SYSCTRL_CLK_SRC_RCL_32768); /* 禁止RCL */
    SYSCTRL_ClockSrcDisable(SYSCTRL_CLK_SRC_XTL);       /* 禁止XTL */
    SYSCTRL_ClockSrcDisable(SYSCTRL_CLK_SRC_EXTL);      /* 禁止EXTL端口输入时钟*/

    /* 时钟分频设置 */
    SYSCTRL_HclkDivSet(SYSCTRL_HCLK_PRS_DIV1);

    /* 更新Core时钟（HCLK）*/
    SystemCoreClockUpdate();
}

/**
 * @brief  外设模块复位
 * @param  [in] enPeriph 复位外设选择 @ref en_sysctrl_periph_reset_t
 * @retval None
 */
void SYSCTRL_PeriphReset(en_sysctrl_periph_reset_t enPeriph)
{
    if (enPeriph & 0x20u)
    {
        enPeriph &= ~0x20u;
        CLR_REG32_BIT(SYSCTRL->PERI_RESET1, 0x1u << enPeriph);
        SET_REG32_BIT(SYSCTRL->PERI_RESET1, 0x1u << enPeriph);
    }
    else
    {
        CLR_REG32_BIT(SYSCTRL->PERI_RESET0, 0x1u << enPeriph);
        SET_REG32_BIT(SYSCTRL->PERI_RESET0, 0x1u << enPeriph);
    }
}

/**
 * @brief  获取复位源类型
 * @param  [in] u32ResetFlag 复位类型选择 @ref SYSCTRL_Reset_Flag_Select
 * @retval boolean_t
 *           - TRUE: 置位
 *           - FALSE: 未置位
 */
boolean_t SYSCTRL_ResetFlagGet(uint32_t u32ResetFlag)
{
    return READ_REG32_BIT(SYSCTRL->RESET_FLAG, u32ResetFlag) ? TRUE : FALSE;
}

/**
 * @brief  清除复位源类型
 * @param  [in] u32ResetFlag 复位类型选择 @ref SYSCTRL_Reset_Flag_Select
 * @retval None
 */
void SYSCTRL_ResetFlagClear(uint32_t u32ResetFlag)
{
    CLR_REG32_BIT(SYSCTRL->RESET_FLAG, u32ResetFlag);
}

/**
 * @brief  清除所有复位源类型
 * @retval None
 */
void SYSCTRL_ResetFlagClearAll(void)
{
    CLR_REG32(SYSCTRL->RESET_FLAG);
}

/**
 * @brief  调试模式下模块功能计数使能
 * @param  [in] u32DebugActiveConfig 调试模式下各模块 @ref SYSCTRL_Debug_Active_Config
 * @retval None
 */
void SYSCTRL_DebugActiveEnable(uint32_t u32DebugActiveConfig)
{
    CLR_REG32_BIT(SYSCTRL->DEBUG_ACTIVE, u32DebugActiveConfig);
}

/**
 * @brief  调试模式下模块功能计数暂停
 * @param  [in] u32DebugActiveConfig 调试模式下各模块 @ref SYSCTRL_Debug_Active_Config
 * @retval None
 */
void SYSCTRL_DebugActiveDisable(uint32_t u32DebugActiveConfig)
{
    SET_REG32_BIT(SYSCTRL->DEBUG_ACTIVE, u32DebugActiveConfig);
}

/**
 * @brief  结构体初始化
 * @param  [in] pstcInit 初始化结构体 @ref stc_sysctrl_clock_init_t
 * @retval None
 */
void SYSCTRL_ClockStcInit(stc_sysctrl_clock_init_t *pstcInit)
{
    pstcInit->u32SysClockSrc = SYSCTRL_CLK_SRC_RC48M_4M;
    pstcInit->u32HclkDiv     = SYSCTRL_HCLK_PRS_DIV1;
}
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
 * EOF (not truncated)
 ******************************************************************************/
