/**
 *******************************************************************************
 * @file  boot_param.c
 * @brief Boot parameter area management for I2C IAP Bootloader
 @verbatim
   Change Logs:
   Date             Author          Notes
   2026-06-16       Claude          First version (I2C IAP refactor)
 @endverbatim
 *******************************************************************************
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "boot_param.h"
#include "config_hc32l021.h"

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/* Size of stc_boot_param_t before header_crc field */
#define BOOT_PARAM_PAYLOAD_SIZE (7u * sizeof(uint32_t)) /* 28 bytes */

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
/* BootParam_CalcHeaderCrc is declared in boot_param.h */

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  Calculate CRC16 of the first 28 bytes of boot_param_t
 * @param  [in] pstcParam  Pointer to boot parameter structure
 * @retval CRC16 value
 */
uint16_t BootParam_CalcHeaderCrc(const stc_boot_param_t *pstcParam)
{
    return (uint16_t)HC32_CalCrc16((uint8_t *)pstcParam, 0u, BOOT_PARAM_PAYLOAD_SIZE);
}

/**
 * @brief  Initialize boot parameter area
 * @retval None
 */
void BootParam_Init(void)
{
    stc_boot_param_t stcParam;

    /* Read current parameter area */
    BootParam_Read(&stcParam);

    /* If magic is already valid, keep existing parameters */
    if (stcParam.magic == BOOT_PARAM_MAGIC)
    {
        return;
    }

    /* Magic mismatch or first boot — initialize with defaults */
    stcParam.magic       = BOOT_PARAM_MAGIC;
    stcParam.state       = BOOT_PARAM_STATE_UPDATE_REQUEST;
    stcParam.app_addr    = APP_ADDR;
    stcParam.app_size    = 0u;
    stcParam.app_crc     = 0u;
    stcParam.boot_count  = 0u;
    stcParam.app_version = 0u;

    /* Calculate and write header CRC */
    stcParam.header_crc = BootParam_CalcHeaderCrc(&stcParam);

    BootParam_Write(&stcParam);
}

/**
 * @brief  Read boot parameter from Flash
 * @param  [out] pstcParam  Pointer to receive boot parameters
 * @retval None
 */
void BootParam_Read(stc_boot_param_t *pstcParam)
{
    HC32_FlashReadBytes(BOOT_PARAM_ADDR, (uint8_t *)pstcParam, sizeof(stc_boot_param_t));
}

/**
 * @brief  Write boot parameter to Flash (erase sector then program)
 * @param  [in] pstcParam  Pointer to boot parameters to write
 * @retval en_result_t
 *           - Ok:  Write successful
 *           - Error: Flash operation failed
 */
en_result_t BootParam_Write(const stc_boot_param_t *pstcParam)
{
    en_result_t enRet;

    /* Erase the parameter sector */
    enRet = HC32_FlashEraseSector(BOOT_PARAM_ADDR);
    if (Ok != enRet)
    {
        return enRet;
    }

    /* Write the structure byte-by-byte */
    enRet = HC32_FlashWriteBytes(BOOT_PARAM_ADDR, (uint8_t *)pstcParam, sizeof(stc_boot_param_t));

    return enRet;
}

/**
 * @brief  Write only the state field (preserves other fields)
 * @note   Writes the full structure to ensure header_crc consistency.
 *         Single-word programming of state field is deferred to avoid
 *         partial-write issues on this Flash controller.
 * @param  [in] u32State  New state value
 * @retval en_result_t
 *           - Ok:  Write successful
 *           - Error: Flash operation failed
 */
en_result_t BootParam_WriteState(uint32_t u32State)
{
    stc_boot_param_t stcParam;

    BootParam_Read(&stcParam);
    stcParam.magic     = BOOT_PARAM_MAGIC;   /* Always restore fixed fields */
    stcParam.app_addr  = APP_ADDR;
    stcParam.state     = u32State;
    stcParam.header_crc = BootParam_CalcHeaderCrc(&stcParam);

    return BootParam_Write(&stcParam);
}

/**
 * @brief  Write app_size and app_crc fields (CRC_FLASH command)
 * @note   Only called from CRC_FLASH handler. State should already be
 *         IMAGE_STATE_UPDATE_REQUEST. Does NOT change state.
 * @param  [in] u32Size  APP firmware size
 * @param  [in] u16Crc   APP firmware CRC16
 * @retval en_result_t
 *           - Ok:  Write successful
 *           - Error: Flash operation failed
 */
en_result_t BootParam_WriteAppInfo(uint32_t u32Size, uint16_t u16Crc)
{
    stc_boot_param_t stcParam;

    BootParam_Read(&stcParam);

    stcParam.magic     = BOOT_PARAM_MAGIC;  /* Always restore fixed fields */
    stcParam.app_addr  = APP_ADDR;
    stcParam.app_size  = u32Size;
    stcParam.app_crc   = (uint32_t)u16Crc;  /* Store in low 16 bits */
    stcParam.header_crc = BootParam_CalcHeaderCrc(&stcParam);

    return BootParam_Write(&stcParam);
}

/**
 * @brief  Erase the boot parameter sector
 * @retval None
 */
void BootParam_Erase(void)
{
    HC32_FlashEraseSector(BOOT_PARAM_ADDR);
}

/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
