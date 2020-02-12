#include "time_sync.h"

time_t get_time_unix(void)
{
    RTCDateTime timespec;
    struct tm tim;

    rtcGetTime(&RTCD1, &timespec);
    rtcConvertDateTimeToStructTm(&timespec, &tim, NULL);
    return mktime(&tim);
}

void set_time_unix(time_t unix_time)
{
    RTCDateTime timespec;

    rtcConvertStructTmToDateTime(localtime(&unix_time), 0, &timespec);
    rtcSetTime(&RTCD1, &timespec);
}

CO_SDO_abortCode_t OD_SCET_Func(CO_ODF_arg_t *ODF_arg)
{
    if (ODF_arg->reading) {
    } else {
    }

    return CO_SDO_AB_NONE;
}

CO_SDO_abortCode_t OD_UTC_Func(CO_ODF_arg_t *ODF_arg)
{
    if (ODF_arg->reading) {
    } else {
    }

    return CO_SDO_AB_NONE;
}
