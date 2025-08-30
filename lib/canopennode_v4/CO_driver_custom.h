#ifndef CO_DRIVER_CUSTOM_H
#define CO_DRIVER_CUSTOM_H

#define CO_USE_GLOBALS
#define CO_CONFIG_GLOBAL_FLAG_CALLBACK_PRE CO_CONFIG_FLAG_CALLBACK_PRE
#define CO_CONFIG_GLOBAL_FLAG_TIMERNEXT    CO_CONFIG_FLAG_TIMERNEXT

#ifndef CO_CONFIG_NMT
#define CO_CONFIG_NMT                                                                              \
	(CO_CONFIG_NMT_CALLBACK_CHANGE | CO_CONFIG_GLOBAL_FLAG_CALLBACK_PRE |                      \
	 CO_CONFIG_GLOBAL_FLAG_TIMERNEXT)
#endif

#ifndef CO_CONFIG_HB_CONS
#define CO_CONFIG_HB_CONS 0
#endif

#ifndef CO_CONFIG_EM
#define CO_CONFIG_EM (CO_CONFIG_EM_PRODUCER | CO_CONFIG_EM_STATUS_BITS)
#endif

#ifndef CO_CONFIG_SDO_SRV
#define CO_CONFIG_SDO_SRV                                                                          \
	(CO_CONFIG_SDO_SRV_SEGMENTED | CO_CONFIG_GLOBAL_FLAG_CALLBACK_PRE |                        \
	 CO_CONFIG_GLOBAL_FLAG_TIMERNEXT | CO_CONFIG_GLOBAL_FLAG_OD_DYNAMIC)
#endif

#ifndef CO_CONFIG_SDO_CLI
#define CO_CONFIG_SDO_CLI 0
#endif

#ifndef CO_CONFIG_TIME
#define CO_CONFIG_TIME 0
#endif

#ifndef CO_CONFIG_SYNC
#define CO_CONFIG_SYNC 0
#endif

#ifndef CO_CONFIG_PDO
#define CO_CONFIG_PDO                                                                              \
	(CO_CONFIG_TPDO_ENABLE | CO_CONFIG_TPDO_TIMERS_ENABLE | CO_CONFIG_PDO_OD_IO_ACCESS |       \
	 CO_CONFIG_GLOBAL_FLAG_CALLBACK_PRE | CO_CONFIG_GLOBAL_FLAG_TIMERNEXT |                    \
	 CO_CONFIG_GLOBAL_FLAG_OD_DYNAMIC)
#endif

#ifndef CO_CONFIG_STORAGE
#define CO_CONFIG_STORAGE 0
#endif

#ifndef CO_CONFIG_LEDS
#define CO_CONFIG_LEDS 0
#endif

#ifndef CO_CONFIG_GFC
#define CO_CONFIG_GFC 0
#endif

#ifndef CO_CONFIG_SRDO
#define CO_CONFIG_SRDO 0
#endif

#ifndef CO_CONFIG_SRDO_MINIMUM_DELAY
#define CO_CONFIG_SRDO_MINIMUM_DELAY 0
#endif

#ifndef CO_CONFIG_LSS
#define CO_CONFIG_LSS 0
#endif

#ifndef CO_CONFIG_GTW
#define CO_CONFIG_GTW 0
#endif

#ifndef CO_CONFIG_CRC16
#define CO_CONFIG_CRC16 (CO_CONFIG_CRC16_ENABLE)
#endif

#ifndef CO_CONFIG_FIFO
#define CO_CONFIG_FIFO                                                                             \
	(CO_CONFIG_FIFO_ENABLE | CO_CONFIG_FIFO_ALT_READ | CO_CONFIG_FIFO_CRC16_CCITT)
#endif

#ifndef CO_CONFIG_TRACE
#define CO_CONFIG_TRACE 0
#endif

#ifndef CO_CONFIG_DEBUG
#define CO_CONFIG_DEBUG 0
#endif

#endif
