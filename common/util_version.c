/*! \file util_version.c
 * 
 * Version utilities
 *
 * @defgroup util_version  Version Utilities
 * @{
 */

#include <string.h>

#include "util_version.h"

VERSIONData version_info;

/*! \brief Firmware GIT Hash
 * GIT_COMMIT_VERSION is inserted by the build system 
 *     generated in common/marionette.mk
 */
void set_util_fwversion(VERSIONData * ver_data)
{
#ifndef GIT_COMMIT_VERSION
#define GIT_COMMIT_VERSION "Unknown"
#endif
    strncpy(ver_data->firmware, GIT_COMMIT_VERSION, MAX_FW_VERSION_LENGTH);
}

/*! \brief  HW Version
 * 4 32 bit registers: base address: 0x1FFF 7A10
 * ST Ref. STM32f40x Page 1399 section 34 'Device Electronic Signature'
 */
void set_util_hwversion(VERSIONData * ver_data)
{
        ver_data->hardware.id_low    = *STM32F4_UNIQUE_ID_LOW;
        ver_data->hardware.id_center = *STM32F4_UNIQUE_ID_CENTER;
        ver_data->hardware.id_high   = *STM32F4_UNIQUE_ID_HIGH;
}

//! @}
