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

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CO_DRIVER_CUSTOM_H */
