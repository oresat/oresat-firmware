#include <stdlib.h>
#include <string.h>
#include "test_time.h"
#include "rtc.h"
#include "chprintf.h"

/*===========================================================================*/
/* Time                                                                      */
/*===========================================================================*/
void cmd_time(BaseSequentialStream *chp, int argc, char *argv[])
{
    RTCDateTime timespec;
    uint32_t msec;
    time_scet_t scet;
    time_utc_t utc;
    if (argc < 1) {
        goto time_usage;
    }
    if (!strcmp(argv[0], "unix")) {
        if (!strcmp(argv[1], "get")) {
            time_t unix_time = rtcGetTimeUnix(&msec);
            char *timestr = ctime(&unix_time);
            chprintf(chp, "UNIX Time: %d\r\n"
                          "Date:      %s\r\n",
                          unix_time, timestr);
        } else if (!strcmp(argv[1], "set") && argc > 2) {
            rtcSetTimeUnix(strtoul(argv[2], NULL, 0), 0);
        } else {
            goto time_usage;
        }
    } else if (!strcmp(argv[0], "scet")) {
        if (!strcmp(argv[1], "get")) {
            rtcGetTimeSCET(&scet);
            chprintf(chp, "SCET Time: %u.%u\r\n", scet.coarse, scet.fine);
        } else if (!strcmp(argv[1], "set") && argc > 3) {
            scet.coarse = strtoul(argv[2], NULL, 0);
            scet.fine = strtoul(argv[3], NULL, 0);
            rtcSetTimeSCET(&scet);
        } else {
            goto time_usage;
        }
    } else if (!strcmp(argv[0], "utc")) {
        if (!strcmp(argv[1], "get")) {
            rtcGetTimeUTC(&utc);
            chprintf(chp, "UTC Time: Day: %u ms: %u us: %u\r\n", utc.day, utc.ms, utc.us);
        } else if (!strcmp(argv[1], "set") && argc > 4) {
            utc.day = strtoul(argv[2], NULL, 0);
            utc.ms = strtoul(argv[3], NULL, 0);
            utc.us = strtoul(argv[4], NULL, 0);
            rtcSetTimeUTC(&utc);
        } else {
            goto time_usage;
        }
    } else if (!strcmp(argv[0], "raw")) {
        rtcGetTime(&RTCD1, &timespec);
        chprintf(chp, "Year: %u Month: %u DST: %u DoW: %u Day: %u ms: %u\r\n",
                      timespec.year, timespec.month, timespec.dstflag, timespec.dayofweek, timespec.day, timespec.millisecond);
    } else {
        goto time_usage;
    }

    return;

time_usage:
    chprintf(chp, "Usage: time unix|scet|utc|raw get|set <values>\r\n");
    return;
}

