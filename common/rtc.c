#include "rtc.h"

RTCDriver *rtcp = &RTCD1;

RTCAlarm    alarm_a;
RTCAlarm    alarm_b;
RTCWakeup   wakeupspec;

static void alarmcb(RTCDriver *rtcp, rtcevent_t event)
{
    switch (event) {
    case RTC_EVENT_ALARM_A:
        break;
    case RTC_EVENT_ALARM_B:
        break;
    case RTC_EVENT_TS:
        break;
    case RTC_EVENT_TS_OVF:
        break;
    case RTC_EVENT_WAKEUP:
        break;
    default:
        break;
    }
}

void rtc_init(void)
{
    rtcSetCallback(rtcp, alarmcb);
}

void get_time_tm(struct tm *tim, uint32_t *msec)
{
    RTCDateTime timespec;

    rtcGetTime(rtcp, &timespec);
    rtcConvertDateTimeToStructTm(&timespec, tim, msec);
}

void set_time_tm(const struct tm *tim, uint32_t msec)
{
    RTCDateTime timespec;

    rtcConvertStructTmToDateTime(tim, msec, &timespec);
    rtcSetTime(rtcp, &timespec);
}

time_t get_time_unix(uint32_t *msec)
{
    struct tm tim;

    get_time_tm(&tim, msec);

    return mktime(&tim);
}

void set_time_unix(time_t unix_time, uint32_t msec)
{
    struct tm tim;

    gmtime_r(&unix_time, &tim);
    set_time_tm(&tim, msec);
}

void get_time_scet(time_scet_t *scet)
{
    uint32_t fine;
    scet->coarse = get_time_unix(&fine);
    scet->fine = fine & 0xFFFFFFU;
}

void set_time_scet(const time_scet_t *scet)
{
    set_time_unix(scet->coarse, scet->fine);
}

void get_time_utc(time_utc_t *utc)
{
    RTCDateTime timespec;
    struct tm tim;

    rtcGetTime(rtcp, &timespec);
    rtcConvertDateTimeToStructTm(&timespec, &tim, NULL);
    mktime(&tim);

    utc->day = (tim.tm_year - 70) * 365 + tim.tm_yday;
    utc->ms = timespec.millisecond;
    utc->us = 0;
}

void set_time_utc(const time_utc_t *utc)
{
    /* TODO: Implement */
    (void)utc;
}

CO_SDO_abortCode_t OD_SCET_Func(CO_ODF_arg_t *ODF_arg)
{
    if (ODF_arg->reading) {
        get_time_scet((time_scet_t*)ODF_arg->data);
    } else {
        set_time_scet((time_scet_t*)ODF_arg->data);
    }

    return CO_SDO_AB_NONE;
}

CO_SDO_abortCode_t OD_UTC_Func(CO_ODF_arg_t *ODF_arg)
{
    if (ODF_arg->reading) {
        get_time_utc((time_utc_t*)ODF_arg->data);
    } else {
        set_time_utc((time_utc_t*)ODF_arg->data);
    }

    return CO_SDO_AB_NONE;
}
