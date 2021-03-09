#ifndef CO_DRIVER_CUSTOM_H
#define CO_DRIVER_CUSTOM_H

#ifdef __cplusplus
extern "C" {
#endif

#define CO_CONFIG_NMT (CO_CONFIG_NMT_CALLBACK_CHANGE | \
                       CO_CONFIG_NMT_MASTER | \
                       CO_CONFIG_GLOBAL_FLAG_CALLBACK_PRE | \
                       CO_CONFIG_GLOBAL_FLAG_TIMERNEXT)

#define CO_CONFIG_SDO_CLI (CO_CONFIG_SDO_CLI_ENABLE | \
                           CO_CONFIG_SDO_CLI_SEGMENTED | \
                           CO_CONFIG_SDO_CLI_BLOCK | \
                           CO_CONFIG_SDO_CLI_LOCAL | \
                           CO_CONFIG_GLOBAL_FLAG_CALLBACK_PRE | \
                           CO_CONFIG_GLOBAL_FLAG_TIMERNEXT | \
                           CO_CONFIG_GLOBAL_FLAG_OD_DYNAMIC)

#define CO_CONFIG_GTW (CO_CONFIG_GTW_ASCII | \
                       CO_CONFIG_GTW_ASCII_SDO | \
                       CO_CONFIG_GTW_ASCII_NMT | \
                       CO_CONFIG_GTW_ASCII_LOG | \
                       CO_CONFIG_GTW_ASCII_ERROR_DESC | \
                       CO_CONFIG_GTW_ASCII_PRINT_HELP)
#define CO_CONFIG_GTW_BLOCK_DL_LOOP 1
#define CO_CONFIG_GTWA_COMM_BUF_SIZE 2000
#define CO_CONFIG_GTWA_LOG_BUF_SIZE 2000

#define CO_CONFIG_FIFO (CO_CONFIG_FIFO_ENABLE | \
                        CO_CONFIG_FIFO_ALT_READ | \
                        CO_CONFIG_FIFO_CRC16_CCITT | \
                        CO_CONFIG_FIFO_ASCII_COMMANDS | \
                        CO_CONFIG_FIFO_ASCII_DATATYPES)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CO_DRIVER_CUSTOM_H */
