/**
 *******************************************************************************
 * @file  boot_param.h
 * @brief Boot parameter area management for I2C IAP Bootloader
 @verbatim
   Change Logs:
   Date             Author          Notes
   2026-06-16       Claude          First version (I2C IAP refactor)
 @endverbatim
 *******************************************************************************
 */

#ifndef __BOOT_PARAM_H__
#define __BOOT_PARAM_H__

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

/**
 * @brief  Boot parameter area structure (32 bytes, fits in one Flash row)
 */
typedef struct
{
    uint32_t magic;        /*!< BOOT_PARAM_MAGIC (0x48434C42 = "HCLB") */
    uint32_t state;        /*!< State machine value @ref BOOT_PARAM_STATE_* */
    uint32_t app_addr;     /*!< APP start address in Flash */
    uint32_t app_size;     /*!< APP firmware size in bytes */
    uint32_t app_crc;      /*!< APP firmware CRC16 */
    uint32_t boot_count;   /*!< Reserved (not incremented, Flash wear concern) */
    uint32_t app_version;  /*!< APP firmware version number */
    uint32_t header_crc;   /*!< CRC16 of the first 28 bytes for integrity check */
} stc_boot_param_t;

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/* Boot parameter area magic ("HCLB" = HC32L Boot) */
#define BOOT_PARAM_MAGIC        ((uint32_t)0x48434C42u)

/* State machine values (mutually exclusive, stored in Flash) */
#define BOOT_PARAM_STATE_UPDATE_REQUEST   ((uint32_t)0xA5A55A5Au)  /* APP requested bootloader stay for IAP */
#define BOOT_PARAM_STATE_IMAGE_PENDING    ((uint32_t)0x5AA55AA5u)  /* JUMP_TO_APP passed CRC/vector check */
#define BOOT_PARAM_STATE_IMAGE_VALID      ((uint32_t)0x55AAAA55u)  /* APP confirmed running OK */

/*===================================================================
 *  Boot Parameter Area Initialization Policy
 *===================================================================*/
/* 0: Production — parameter area must be pre-programmed with bootloader.
 *    If magic is invalid, stay in bootloader (do not auto-init).
 * 1: Debug — auto-initialize parameter area when magic is invalid.
 *    Useful during development when parameter area is erased. */
#define BOOT_PARAM_AUTO_INIT    (0u)

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
void        BootParam_Init(void);
void        BootParam_Read(stc_boot_param_t *pstcParam);
en_result_t BootParam_Write(const stc_boot_param_t *pstcParam);
en_result_t BootParam_WriteState(uint32_t u32State);
en_result_t BootParam_WriteAppInfo(uint32_t u32Size, uint16_t u16Crc);
void        BootParam_Erase(void);
uint16_t    BootParam_CalcHeaderCrc(const stc_boot_param_t *pstcParam); /* Calculate header CRC16 */

#ifdef __cplusplus
}
#endif

#endif /* __BOOT_PARAM_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
