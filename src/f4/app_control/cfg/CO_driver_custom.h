#ifndef CO_DRIVER_CUSTOM_H
#define CO_DRIVER_CUSTOM_H

#ifdef __cplusplus
extern "C" {
#endif

/* TODO: These should be in CO_OD.h, but libedssharp does not support this yet */
#define CO_NO_GFC 0
#define CO_NO_SRDO 0

#define CO_CONFIG_GTW (CO_CONFIG_GTW_ASCII | \
                       CO_CONFIG_GTW_ASCII_SDO | \
                       CO_CONFIG_GTW_ASCII_NMT | \
                       CO_CONFIG_GTW_ASCII_LSS | \
                       CO_CONFIG_GTW_ASCII_LOG | \
                       CO_CONFIG_GTW_ASCII_ERROR_DESC | \
                       CO_CONFIG_GTW_ASCII_PRINT_HELP)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CO_DRIVER_CUSTOM_H */
