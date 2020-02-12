#include "time.h"

static void get_time_tm(struct tm *timp)
{
    RTCDateTime timespec;

    rtcGetTime(&RTCD1, &timespec);
    rtcConvertDateTimeToStructTm(&timespec, timp, NULL);
}

static time_t get_time_unix(void)
{
    struct tm tim;

    get_time_tm(&tim);
    return mktime(&tim);
}

CO_SDO_abortCode_t OD_SCET_Func(CO_ODF_arg_t *ODF_arg)
{
    RTCDateTime timespec;

    if (ODF_arg->reading) {
    } else {
    }
}

CO_SDO_abortCode_t OD_UTC_Func(CO_ODF_arg_t *ODF_arg)
{
    RTCDateTime timespec;

    if (ODF_arg->reading) {
    } else {
    }
}
