#ifndef CO_DRIVER_CUSTOM_H
#define CO_DRIVER_CUSTOM_H

#ifdef __cplusplus
extern "C" {
#endif

/* TODO: These should be in CO_OD.h, but libedssharp does not support this yet */
#define CO_NO_GFC 0
#define CO_NO_SRDO 0

#define CO_CONFIG_SDO_CLI (CO_CONFIG_FLAG_CALLBACK_PRE | \
                           CO_CONFIG_FLAG_TIMERNEXT | \
                           CO_CONFIG_SDO_CLI_SEGMENTED | \
                           CO_CONFIG_SDO_CLI_BLOCK | \
                           CO_CONFIG_SDO_CLI_LOCAL)

#define CO_CONFIG_GTW (CO_CONFIG_GTW_ASCII | \
                       CO_CONFIG_GTW_ASCII_SDO | \
                       CO_CONFIG_GTW_ASCII_NMT | \
                       CO_CONFIG_GTW_ASCII_LOG | \
                       CO_CONFIG_GTW_ASCII_ERROR_DESC | \
                       CO_CONFIG_GTW_ASCII_PRINT_HELP)
#define CO_CONFIG_GTW_BLOCK_DL_LOOP 1
#define CO_CONFIG_GTWA_COMM_BUF_SIZE 2000
#define CO_CONFIG_GTWA_LOG_BUF_SIZE 2000

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CO_DRIVER_CUSTOM_H */
