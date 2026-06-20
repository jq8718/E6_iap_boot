/**
 *******************************************************************************
 * @file  system_hc32l021.c
 * @brief Source file for SYSTEM functions
 @verbatim
   Change Logs:
   Date             Author          Notes
   2024-12-09       MADS            First version
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

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "system_hc32l021.h"
#include "ddl.h"
#include "hc32l021.h"
#include "sysctrl.h"

/**
 * @addtogroup HC32L021_DDL 驱动库
 * @{
 */

/**
 * @defgroup DDL_SYSTEM SYSTEM模块驱动库
 * @brief SYSTEM Driver Library SYSTEM模块驱动库
 * @{
 */
/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
/**
 * @addtogroup SYSTEM_Global_Variables SYSTEM全局变量定义
 * @{
 */
/**
 * @brief  System clock frequency (Core Clock) variable according to CMSIS
 */
uint32_t SystemCoreClock = 4000000;
/**
 * @}
 */
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
 * @defgroup SYSTEM_Global_Functions SYSTEM全局函数定义
 * @{
 */

/**
 * @brief  Update SystemCoreClock variable
 * @retval None
 * @note   当程序运行时切换了系统时钟，必须调用SystemCoreClockUpdate()函数更新SystemCoreClock
 */
void SystemCoreClockUpdate(void)
{
    SystemCoreClock = SYSCTRL_HclkFreqGet();
}

/**
 * @brief  Setup the microcontroller system.
 *         Initialize the System and update the SystemCoreClock variable
 * @param [in] None
 * @retval None
 */
void SystemInit(void)
{
    SYSCTRL->RC48M_CR = (*((volatile uint32_t *)(0x001007BCul))); /* 加载RC48M Trim值 */
    FLASH->BYPASS = 0x5A5Au;
    FLASH->BYPASS = 0xA5A5u;
    FLASH->CR_f.RO = 1u; /* FLASH只读、不可编程或擦写 */

    SystemCoreClockUpdate();

    SysTick->LOAD = 0xFFFFFF;
    SysTick->VAL  = 0;
    SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk;
}

#if defined(__CC_ARM)
extern int32_t $Super$$main(void);
/* re-define main function */
int $Sub$$main(void)
{
    SystemInit();
    $Super$$main();
    return 0;
}
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
extern int32_t $Super$$main(void);
/* re-define main function */
int32_t $Sub$$main(void)
{
    SystemInit();
    $Super$$main();
    return 0;
}
#elif defined(__ICCARM__)
extern int32_t main(void);
/* __low_level_init will auto called by IAR cstartup */
extern void __iar_data_init3(void);
int32_t     __low_level_init(void)
{
    /* call IAR table copy function */
    __iar_data_init3();
    SystemInit();
    main();
    return 0;
}
#endif
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
