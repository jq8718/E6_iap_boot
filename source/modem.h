/**
 *******************************************************************************
 * @file  modem.h
 * @brief This file contains all the functions prototypes of MODEM
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

#ifndef __MODEM_H__
#define __MODEM_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "utils.h"
/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/
/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
en_result_t MODEM_Process(void);
void        MODEM_RamInit(void);

#ifdef __cplusplus
}
#endif

#endif /* __MODEM_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
