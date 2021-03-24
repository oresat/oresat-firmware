#include "rtc.h"

/**
 * @brief   Get time as struct tm
 *
 * @param[out] tim          Pointer to struct tm to fill
 * @param[out] msec         Pointer to millisecond variable
 *
 * @api
 */
void rtcGetTimeTm(struct tm *tim, uint32_t *msec)
{
    osalDbgCheck(tim != NULL);
    RTCDateTime timespec;

    rtcGetTime(&RTCD1, &timespec);
    rtcConvertDateTimeToStructTm(&timespec, tim, msec);
}

/**
 * @brief   Set time from struct tm
 *
 * @param[in]  tim          Pointer to struct tm to use
 * @param[in]  msec         Milliseconds value
 *
 * @api
 */
void rtcSetTimeTm(const struct tm *tim, uint32_t msec)
{
    osalDbgCheck(tim != NULL);
    RTCDateTime timespec;

    rtcConvertStructTmToDateTime(tim, msec, &timespec);
    rtcSetTime(&RTCD1, &timespec);
}

/**
 * @brief   Get time as Unix time_t
 *
 * @param[out] msec         Pointer to millisecond variable
 *
 * @return                  Current time as time_t
 * @api
 */
time_t rtcGetTimeUnix(uint32_t *msec)
{
    struct tm tim;

    rtcGetTimeTm(&tim, msec);

    return mktime(&tim);
}

/**
 * @brief   Set time from Unix time_t
 *
 * @param[in]  unix_time    Unix time to set RTC to
 * @param[in]  msec         Milliseconds value
 *
 * @api
 */
void rtcSetTimeUnix(time_t unix_time, uint32_t msec)
{
    struct tm tim;
    struct tm *canary;

    canary = gmtime_r(&unix_time, &tim);
    osalDbgCheck(&tim == canary);

    rtcSetTimeTm(&tim, msec);
}

/**
 * @brief   Get time as CCSDS SCET object
 *
 * @param[out] scet         Pointer to SCET struct
 *
 * @api
 */
void rtcGetTimeSCET(time_scet_t *scet)
{
    osalDbgCheck(scet != NULL);
    uint32_t fine;
    scet->coarse = rtcGetTimeUnix(&fine);
    scet->fine = fine & 0xFFFFFFU;
}

/**
 * @brief   Set time from CCSDS SCET object
 *
 * @param[in]  scet         Pointer to SCET struct
 *
 * @api
 */
void rtcSetTimeSCET(const time_scet_t *scet)
{
    osalDbgCheck(scet != NULL);
    rtcSetTimeUnix(scet->coarse, scet->fine);
}

/**
 * @brief   Get time as CCSDS UTC object
 *
 * @param[out] scet         Pointer to UTC struct
 *
 * @api
 */
void rtcGetTimeUTC(time_utc_t *utc)
{
    osalDbgCheck(utc != NULL);
    RTCDateTime timespec;
    struct tm tim;

    rtcGetTime(&RTCD1, &timespec);
    rtcConvertDateTimeToStructTm(&timespec, &tim, NULL);
    mktime(&tim);

    utc->day = (tim.tm_year - 70) * 365 + tim.tm_yday;
    utc->ms = timespec.millisecond;
    utc->us = 0;
}

/**
 * @brief   Set time from CCSDS UTC object
 *
 * @param[in]  scet         Pointer to UTC struct
 *
 * @api
 */
void rtcSetTimeUTC(const time_utc_t *utc)
{
    osalDbgCheck(utc != NULL);
    /* TODO: Implement */
    (void)utc;
}

/**
 * @brief   Converts time from timespec to ALRMxR register encoding
 *
 * @param[in]  timespec     Pointer to a @p RTCDateTime structure
 * @param[in]  flags        Configuration flags
 *
 * @return                  The ALRMxR register encoding.
 * @api
 */
uint32_t rtcEncodeAlarm(const RTCDateTime *timespec, uint32_t flags)
{
    osalDbgCheck(timespec != NULL);
    uint32_t n, alrmr = 0;

    /* Subseconds cannot be set.*/
    n = timespec->millisecond / 1000;

    /* Seconds conversion.*/
    if ((flags & RTC_SEC_MASK) == 0) {
        alrmr |= ((n % 10) << RTC_ALRMAR_SU_Pos);
        n /= 10;
        alrmr |= ((n % 6) << RTC_ALRMAR_ST_Pos);
        n /= 6;
    }

    /* Minutes conversion.*/
    if ((flags & RTC_MIN_MASK) == 0) {
        alrmr |= ((n % 10) << RTC_ALRMAR_MNU_Pos);
        n /= 10;
        alrmr |= ((n % 6) << RTC_ALRMAR_MNT_Pos);
        n /= 6;
    }

    /* Hours conversion.*/
    if ((flags & RTC_HOUR_MASK) == 0) {
        alrmr |= ((n % 10) << RTC_ALRMAR_HU_Pos);
        n /= 10;
        alrmr |= (n << RTC_ALRMAR_HT_Pos);
    }

    /* Days conversion.*/
    if ((flags & RTC_DATE_MASK) == 0) {
        if (flags & RTC_WEEKDAY_SEL) {
            n = timespec->dayofweek;
            alrmr |= (n << RTC_ALRMAR_DU_Pos);
        } else {
            n = timespec->day;
            alrmr |= ((n % 10) << RTC_ALRMAR_DU_Pos);
            n /= 10;
            alrmr |= ((n % 10) << RTC_ALRMAR_DT_Pos);
        }
    }

    /* Set flags */
    alrmr |= flags;

    return alrmr;
}

/**
 * @brief   Generates ALRMxR register value for time relative to timespec
 *
 * @param[in]  timespec     Pointer to a @p RTCDateTime structure
 * @param[in]  days         Days to elapse
 * @param[in]  hours        Hours to elapse
 * @param[in]  minutes      Minutes to elapse
 * @param[in]  seconds      Seconds to elapse
 *
 * @return                  The ALRMxR register encoding.
 * @api
 */
uint32_t rtcEncodeRelAlarm(const RTCDateTime *timespec, int days, int hours, int minutes, int seconds)
{
    RTCDateTime alarm_timespec;
    struct tm tim;

    /* Get current time */
    rtcConvertDateTimeToStructTm(timespec, &tim, NULL);
    /* Add offsets for desired elapsed time */
    tim.tm_yday += days;
    tim.tm_hour += hours;
    tim.tm_min += minutes;
    tim.tm_sec += seconds;
    /* Recalculate struct tm and convert to timespec */
    mktime(&tim);
    rtcConvertStructTmToDateTime(&tim, 0, &alarm_timespec);
    /* Return the encoded alarm value */
    return rtcEncodeAlarm(&alarm_timespec, 0);
}

/* TODO: Move these out of RTC probably */
CO_SDO_abortCode_t OD_SCET_Func(CO_ODF_arg_t *ODF_arg)
{
    if (ODF_arg->reading) {
        rtcGetTimeSCET((time_scet_t*)ODF_arg->data);
    } else {
        rtcSetTimeSCET((time_scet_t*)ODF_arg->data);
    }

    return CO_SDO_AB_NONE;
}

CO_SDO_abortCode_t OD_UTC_Func(CO_ODF_arg_t *ODF_arg)
{
    if (ODF_arg->reading) {
        rtcGetTimeUTC((time_utc_t*)ODF_arg->data);
    } else {
        rtcSetTimeUTC((time_utc_t*)ODF_arg->data);
    }

    return CO_SDO_AB_NONE;
}
