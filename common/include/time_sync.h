#ifndef TIME_H
#define TIME_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ch.h"
#include "hal.h"
#include "CANopen.h"

time_t get_time_unix(void);
void set_time_unix(time_t unix_time);

CO_SDO_abortCode_t OD_SCET_Func(CO_ODF_arg_t *ODF_arg);
CO_SDO_abortCode_t OD_UTC_Func(CO_ODF_arg_t *ODF_arg);

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif
