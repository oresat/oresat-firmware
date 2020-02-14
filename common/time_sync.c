#include "time_sync.h"

#define EPOCH_CONV_SEC ((TIME_UNIX_EPOCH - TIME_TAI_EPOCH) * 31536000)

time_t get_time_unix(uint32_t *msec)
{
    RTCDateTime timespec;
    struct tm tim;

    rtcGetTime(&RTCD1, &timespec);
    rtcConvertDateTimeToStructTm(&timespec, &tim, msec);
    return mktime(&tim);
}

void set_time_unix(time_t unix_time, uint32_t msec)
{
    RTCDateTime timespec;
    struct tm tim;

    localtime_r(&unix_time, &tim);
    rtcConvertStructTmToDateTime(&tim, msec, &timespec);
    rtcSetTime(&RTCD1, &timespec);
}

void get_time_scet(time_scet_t *scet)
{
    uint32_t fine;
    scet->coarse = get_time_unix(&fine) + EPOCH_CONV_SEC;
    scet->fine = fine & 0xFFFFFFU;
}

void set_time_scet(const time_scet_t *scet)
{
    set_time_unix(scet->coarse - EPOCH_CONV_SEC, scet->fine);
}

void get_time_utc(time_utc_t *utc)
{

}

void set_time_utc(const time_utc_t *utc)
{

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
