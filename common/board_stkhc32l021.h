/**
 *******************************************************************************
 * @file  board_stkhc32l021.h
 * @brief Header file for BSP functions
 @verbatim
   Change Logs:
   Date             Author          Notes
   2024-12-02       MADS            First version
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

#ifndef __BOARD_STKHC32L021_H__
#define __BOARD_STKHC32L021_H__

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
 * @addtogroup DDL_STK STK模块驱动库
 * @{
 */
/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup STK_Global_Types STK全局类型定义
 * @{
 */

/**
 * @brief 芯片信息结构体指针
 */
typedef struct
{
    uint8_t  u8UID[10];          /*!< 10字节UID(唯一识别号) */
    char_t  *pcProductNum;       /*!< 32字节产品型号"HC32xxx……" */
    uint32_t u32FlashSize;       /*!< FLASH容量(Byte) */
    uint32_t u32RamSize;         /*!< RAM容量(Byte) */
    uint16_t u16PinCount;        /*!< 管脚数量 */
    uint16_t u16FlashSectorSize; /*!< FLASH Sector大小(Byte) */
} stc_stk_chip_info_t;
/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup STK_Global_Macros STK全局宏定义
 * @{
 */

/**
 * @brief  USER KEY
 */
#define STK_USER_PORT          GPIOA
#define STK_USER_PIN           GPIO_PIN_12

#define STK_USER_KEY_PRESSED() (GPIO_PA12_READ() ? FALSE : TRUE)

/**
 * @brief  LED
 */
#define STK_LED_PORT   GPIOA
#define STK_LED_PIN    GPIO_PIN_06

#define STK_LED_ON()   GPIO_PA06_SET()
#define STK_LED_OFF()  GPIO_PA06_RESET()
#define STK_LED_READ() GPIO_PA06_READ()

/**
 * @brief  EXTH频率和端口配置
 * @note   当使用外灌时钟时，请修改SYSTEM_EXTH为实际灌入时钟频率
 */
#define SYSTEM_EXTH   (8 * 1000 * 1000u) /* 8MHz 本芯片仅支持EXTH外灌时钟 */
#define STK_EXTH_PORT GPIOA              /* EXTH外灌时钟端口 */
#define STK_EXTH_PIN  GPIO_PIN_11        /* EXTH外灌时钟引脚 */

/**
 * @brief  EXTL频率和端口配置
 * @note   当使用外灌时钟时，请修改SYSTEM_EXTL为实际灌入时钟频率
 */
#define SYSTEM_EXTL   (32768u)    /* 32768Hz 本硬件板上低频频率为32768Hz,本芯片还支持EXTL外灌时钟 */
#define STK_EXTL_PORT GPIOA       /* EXTL外灌时钟端口 */
#define STK_EXTL_PIN  GPIO_PIN_07 /* EXTL外灌时钟引脚 */
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
 * @addtogroup STK_Global_Functions STK全局函数定义
 * @{
 */
void STK_UserKeyConfig(void); /* STK 按键初始化 */
void STK_LedConfig(void);     /* STK LED初始化 */

void STK_ChipInfoGet(stc_stk_chip_info_t *pstcChipInfo); /* 获取芯片相关信息 */
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

#endif /* __BOARD_STKHC32L021_H__ */
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
