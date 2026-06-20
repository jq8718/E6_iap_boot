/**
 *******************************************************************************
 * @file  ddl.h
 * @brief This file contains all the functions prototypes of the DDL driver
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

#ifndef __DDL_H__
#define __DDL_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "base_types.h"
#include "board_stkhc32l021.h"
#include "hc32l021.h"
#include "interrupts_hc32l021.h"
#include "sysctrl.h"
#include "system_hc32l021.h"

/**
 * @addtogroup HC32L021_DDL 驱动库
 * @{
 */

/**
 * @addtogroup DDL_DDL DDL模块驱动库
 * @{
 */
/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup DDL_Global_Macros DDL全局宏定义
 * @{
 */

/**
 * @defgroup DDL_Struct_Clear DDL结构体清零
 * @{
 */
#define DDL_ZERO_STRUCT(x) DDL_MemoryClear((uint8_t *)&(x), (uint32_t)(sizeof(x))) /*!< 结构体清零 */
/**
 * @}
 */

/**
 * @defgroup DDL_BCD_DEC_Convert DDL十进制与BCD转换
 * @{
 */
#define DEC2BCD(x) ((((x) / 10) << 4) + ((x) % 10))    /*!< 十进制转BCD */
#define BCD2DEC(x) ((((x) >> 4) * 10) + ((x) & 0x0Fu)) /*!< BCD转十进制 */
/**
 * @}
 */

/**
 * @defgroup DDL_Register_Func DDL寄存器操作函数
 * @{
 */
#define RW_MEM8(addr)                      (*(volatile uint8_t *)(addr))
#define RW_MEM16(addr)                     (*(volatile uint16_t *)(addr))
#define RW_MEM32(addr)                     (*(volatile uint32_t *)(addr))

#define SET_REG_BIT(REG, BIT)              ((REG) |= (BIT))
#define SET_REG8_BIT(REG, BIT)             ((REG) |= ((uint8_t)(BIT)))
#define SET_REG16_BIT(REG, BIT)            ((REG) |= ((uint16_t)(BIT)))
#define SET_REG32_BIT(REG, BIT)            ((REG) |= ((uint32_t)(BIT)))

#define CLR_REG_BIT(REG, BIT)              ((REG) &= (~(BIT)))
#define CLR_REG8_BIT(REG, BIT)             ((REG) &= ((uint8_t)(~((uint8_t)(BIT)))))
#define CLR_REG16_BIT(REG, BIT)            ((REG) &= ((uint16_t)(~((uint16_t)(BIT)))))
#define CLR_REG32_BIT(REG, BIT)            ((REG) &= ((uint32_t)(~((uint32_t)(BIT)))))

#define READ_REG_BIT(REG, BIT)             ((REG) & (BIT))
#define READ_REG8_BIT(REG, BIT)            ((REG) & ((uint8_t)(BIT)))
#define READ_REG16_BIT(REG, BIT)           ((REG) & ((uint16_t)(BIT)))
#define READ_REG32_BIT(REG, BIT)           ((REG) & ((uint32_t)(BIT)))

#define CLR_REG(REG)                       ((REG) = (0U))
#define CLR_REG8(REG)                      ((REG) = ((uint8_t)(0U)))
#define CLR_REG16(REG)                     ((REG) = ((uint16_t)(0U)))
#define CLR_REG32(REG)                     ((REG) = ((uint32_t)(0UL)))

#define WRITE_REG(REG, VAL)                ((REG) = (VAL))
#define WRITE_REG8(REG, VAL)               ((REG) = ((uint8_t)(VAL)))
#define WRITE_REG16(REG, VAL)              ((REG) = ((uint16_t)(VAL)))
#define WRITE_REG32(REG, VAL)              ((REG) = ((uint32_t)(VAL)))

#define READ_REG(REG)                      (REG)
#define READ_REG8(REG)                     (REG)
#define READ_REG16(REG)                    (REG)
#define READ_REG32(REG)                    (REG)

#define MODIFY_REG(REGS, CLRMASK, SETMASK) (WRITE_REG((REGS), (((READ_REG(REGS)) & (~(CLRMASK))) | ((SETMASK) & (CLRMASK)))))
#define MODIFY_REG8(REGS, CLRMASK, SETMASK) \
    (WRITE_REG8((REGS), (((READ_REG8((REGS))) & ((uint8_t)(~((uint8_t)(CLRMASK))))) | ((uint8_t)(SETMASK) & (uint8_t)(CLRMASK)))))
#define MODIFY_REG16(REGS, CLRMASK, SETMASK) \
    (WRITE_REG16((REGS), (((READ_REG16((REGS))) & ((uint16_t)(~((uint16_t)(CLRMASK))))) | ((uint16_t)(SETMASK) & (uint16_t)(CLRMASK)))))
#define MODIFY_REG32(REGS, CLRMASK, SETMASK) \
    (WRITE_REG32((REGS), (((READ_REG32((REGS))) & ((uint32_t)(~((uint32_t)(CLRMASK))))) | ((uint32_t)(SETMASK) & (uint32_t)(CLRMASK)))))
/**
 * @}
 */

/**
 * @defgroup DDL_Device_Series DDL系列
 * @{
 */
#define DDL_DEVICE_SERIES_HC32L021 (0u)
/**
 * @}
 */

/**
 * @defgroup DDL_Release_Version DDL Release Version
 * @{
 */
#define HC32_DDL_REV_MAIN  (0x01u) /*!< [31:24] main version  */
#define HC32_DDL_REV_SUB1  (0x01u) /*!< [23:16] sub1 version  */
#define HC32_DDL_REV_SUB2  (0x00u) /*!< [15:8]  sub2 version  */
#define HC32_DDL_REV_PATCH (0x00u) /*!< [7:0]   patch version */
#define HC32_DDL_REV       ((HC32_DDL_REV_MAIN << 24) | (HC32_DDL_REV_SUB1 << 16) | (HC32_DDL_REV_SUB2 << 8) | (HC32_DDL_REV_PATCH))
/**
 * @}
 */

/**
 * @}
 */

#include "ddl_device.h" /* MUST be included here! */
/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/
/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup DDL_Global_Functions DDL全局函数定义
 * @{
 */
uint32_t Log2(uint32_t u32Value);

void DDL_MemoryClear(void *pu8StartAddr, uint32_t u32Count); /* Memory清零*/

void DDL_Delay1ms(uint32_t u32Count);   /* 1ms延时函数 */
void DDL_Delay100us(uint32_t u32Count); /* 100us延时函数 */
void DDL_Delay10us(uint32_t u32Count);  /* 1ous延时函数 */
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

#endif /* __DDL_H__ */
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
