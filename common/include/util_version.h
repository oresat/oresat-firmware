/*! \file util_version.h
 * \addtogroup util_version
 * @{
 */

#ifndef UTIL_VERSION_H_
#define UTIL_VERSION_H_

#include <stdint.h>

#define         MAX_FW_VERSION_LENGTH       50

#define         STM32F0_UNIQUE_ID_LOW       ((uint32_t*)0x1FFFF7AC)
#define         STM32F0_UNIQUE_ID_CENTER    ((uint32_t*)0x1FFFF7B0)
#define         STM32F0_UNIQUE_ID_HIGH      ((uint32_t*)0x1FFFF7B4)
#define         STM32F4_UNIQUE_ID_LOW       ((uint32_t*)0x1FFF7A10)
#define         STM32F4_UNIQUE_ID_CENTER    ((uint32_t*)0x1FFF7A14)
#define         STM32F4_UNIQUE_ID_HIGH      ((uint32_t*)0x1FFF7A18)

#ifdef __cplusplus
extern "C" {
#endif

typedef struct hw_version
{
    uint32_t id_high;
    uint32_t id_center;
    uint32_t id_low;
} HW_Version;

typedef struct versiondata
{
    char         firmware[MAX_FW_VERSION_LENGTH];
    HW_Version   hardware;
} VERSIONData;

extern VERSIONData version_info;

void set_util_fwversion(VERSIONData * ver_data);
void set_util_hwversion(VERSIONData * ver_data);

#ifdef __cplusplus
}
#endif

#endif

//! @}
