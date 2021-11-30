#ifndef RTC_H
#define RTC_H

#include <time.h>
#include "ch.h"
#include "hal.h"
#include "CANopen.h"

/* Preamble definitions
 * While Level 1 Time Codes are generally preferred by CCSDS, we are using
 * Level 2 Time Codes (meaning Agency Defined). In this case we are using
 * the UNIX Epoch of Jan 1, 1970.
 * Refer to CCSDS 301.0-B-4 for Time Code Formats.
 * TODO: Verify that the bit order is correct for preambles
 */
#define TIME_CUC_PREAMBLE   0x2E    /* CCSDS Unsegmented Time Code (CUC) Preamble */
#define TIME_CDS_PREAMBLE   0x49    /* CCSDS Day Segmented Time Code (CDS) Preamble */

#define RTC_WEEKDAY_SEL     RTC_ALRMAR_WDSEL
#define RTC_DATE_MASK       RTC_ALRMAR_MSK4
#define RTC_HOUR_MASK       RTC_ALRMAR_MSK3
#define RTC_MIN_MASK        RTC_ALRMAR_MSK2
#define RTC_SEC_MASK        RTC_ALRMAR_MSK1

/* CCSDS Unsegmented Time Code (CUC) data type */
typedef union {
    uint64_t raw;
    struct {
        uint32_t coarse:32;
        uint32_t fine:24;
    };
} time_scet_t;

/* CCSDS Day Segmented Time Code (CDS) data type */
typedef union {
    uint64_t raw;
    struct {
        uint16_t day:16;
        uint32_t ms:32;
        uint16_t us:16;
    };
} time_utc_t;

#ifdef __cplusplus
extern "C" {
#endif

time_t rtcConvertDateTimeToUnix(const RTCDateTime *timespec, uint32_t *msec);
void rtcConvertUnixToDateTime(RTCDateTime *timespec, time_t unix_time, uint32_t msec);

void rtcGetTimeTm(struct tm *tim, uint32_t *msec);
void rtcSetTimeTm(const struct tm *tim, uint32_t msec);
time_t rtcGetTimeUnix(uint32_t *msec);
void rtcSetTimeUnix(time_t unix_time, uint32_t msec);
void rtcGetTimeSCET(time_scet_t *scet);
void rtcSetTimeSCET(const time_scet_t *scet);
void rtcGetTimeUTC(time_utc_t *utc);
void rtcSetTimeUTC(const time_utc_t *utc);

uint32_t rtcEncodeAlarm(const RTCDateTime *timespec, uint32_t flags);
uint32_t rtcEncodeRelAlarm(const RTCDateTime *timespec, int days, int hours, int minutes, int seconds);

/*
CO_SDO_abortCode_t OD_SCET_Func(CO_ODF_arg_t *ODF_arg);
CO_SDO_abortCode_t OD_UTC_Func(CO_ODF_arg_t *ODF_arg);
*/

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif /*RTC_H*/
