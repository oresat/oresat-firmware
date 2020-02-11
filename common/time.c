#include "time.h"

CO_SDO_abortCode_t OD_SCET_Func(CO_ODF_arg_t *ODF_arg)
{
    RTCDateTime timespec;

    if (ODF_arg->reading) {
        rtcGetTime(&RTCD1, &timespec);
    } else {
        rtcSetTime(&RTCD1, &timespec);
    }
}

CO_SDO_abortCode_t OD_UTC_Func(CO_ODF_arg_t *ODF_arg)
{
    RTCDateTime timespec;

    if (ODF_arg->reading) {
        rtcGetTime(&RTCD1, &timespec);
    } else {
        rtcSetTime(&RTCD1, &timespec);
    }
}
