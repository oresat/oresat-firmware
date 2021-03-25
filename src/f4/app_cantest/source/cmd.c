#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "cmd.h"
#include "rtc.h"
#include "chprintf.h"
#include "shell.h"

static thread_t *shell_tp;

/*===========================================================================*/
/* Support functions                                                         */
/*===========================================================================*/
size_t gtwa_read_cb(void *chp, const char *buf, size_t count, uint8_t *conn_ok)
{
    size_t written;
    (void)conn_ok;

    written = streamWrite((BaseSequentialStream *)chp, (const unsigned char *)buf, count);

    chEvtSignal(shell_tp, (eventmask_t)1);

    return written;
}

/*===========================================================================*/
/* OreSat CAN Bus                                                            */
/*===========================================================================*/
void cmd_can(BaseSequentialStream *chp, int argc, char *argv[])
{
    char cmd[CO_CONFIG_GTWA_COMM_BUF_SIZE];
    size_t space;
    (void)chp;

    if (argc < 1) {
        strncpy(cmd, "[0] help\r\n", CO_CONFIG_GTWA_COMM_BUF_SIZE);
    } else {
        strncpy(cmd, argv[0], CO_CONFIG_GTWA_COMM_BUF_SIZE);
        space = CO_CONFIG_GTWA_COMM_BUF_SIZE - strlen(argv[0]);
        for (int i = 1; i < argc; i++) {
            strncat(cmd, " ", space);
            strncat(cmd, argv[i], space - 1);
            space -= strlen(argv[i]) + 1;
        }
    }
    strncat(cmd, "\r\n", space);

    /*space = CO_GTWA_write_getSpace(CO->gtwa);*/

    CO_GTWA_write(CO->gtwa, cmd, strlen(cmd));
    chEvtWaitAny((eventmask_t)1);

}
/*===========================================================================*/
/* Time                                                                      */
/*===========================================================================*/
void time_usage(BaseSequentialStream *chp)
{
    chprintf(chp, "Usage: time unix|scet|utc|raw get|set <values>\r\n");
}

void cmd_time(BaseSequentialStream *chp, int argc, char *argv[])
{
    RTCDateTime timespec;
    time_t unix_time;
    uint32_t msec;
    time_scet_t scet;
    time_utc_t utc;
    if (argc < 1) {
        time_usage(chp);
        return;
    }
    if (!strcmp(argv[0], "unix")) {
        if (!strcmp(argv[1], "get")) {
            unix_time = get_time_unix(&msec);
            chprintf(chp, "UNIX Time: %s\r\n", ctime(&unix_time));
        } else if (!strcmp(argv[1], "set") && argc > 2) {
            set_time_unix(strtoul(argv[2], NULL, 0), 0);
        } else {
            time_usage(chp);
            return;
        }
    } else if (!strcmp(argv[0], "scet")) {
        if (!strcmp(argv[1], "get")) {
            get_time_scet(&scet);
            chprintf(chp, "SCET Time: %u.%u\r\n", scet.coarse, scet.fine);
        } else if (!strcmp(argv[1], "set") && argc > 3) {
            scet.coarse = strtoul(argv[2], NULL, 0);
            scet.fine = strtoul(argv[3], NULL, 0);
            set_time_scet(&scet);
        } else {
            time_usage(chp);
            return;
        }
    } else if (!strcmp(argv[0], "utc")) {
        if (!strcmp(argv[1], "get")) {
            get_time_utc(&utc);
            chprintf(chp, "UTC Time: Day: %u ms: %u us: %u\r\n", utc.day, utc.ms, utc.us);
        } else if (!strcmp(argv[1], "set") && argc > 4) {
            utc.day = strtoul(argv[2], NULL, 0);
            utc.ms = strtoul(argv[3], NULL, 0);
            utc.us = strtoul(argv[4], NULL, 0);
            set_time_utc(&utc);
        } else {
            time_usage(chp);
            return;
        }
    } else if (!strcmp(argv[0], "raw")) {
        rtcGetTime(&RTCD1, &timespec);
        chprintf(chp, "Year: %u Month: %u DST: %u DoW: %u Day: %u ms: %u\r\n", timespec.year, timespec.month, timespec.dstflag, timespec.dayofweek, timespec.day, timespec.millisecond);
    } else {
        time_usage(chp);
        return;
    }
}

/*===========================================================================*/
/* Shell                                                                     */
/*===========================================================================*/
static const ShellCommand commands[] = {
    {"can", cmd_can},
    {"time", cmd_time},
    {NULL, NULL}
};

static char histbuf[SHELL_MAX_HIST_BUFF];

static const ShellConfig shell_cfg = {
    (BaseSequentialStream *)&SD3,
    commands,
    histbuf,
    sizeof(histbuf),
};

THD_WORKING_AREA(shell_wa, 0x1000);
THD_WORKING_AREA(cmd_wa, 0x200);
THD_FUNCTION(cmd, arg)
{
    (void)arg;

    /* Initialize ASCII Gateway callback to print returned text */
    CO_GTWA_initRead(CO->gtwa, gtwa_read_cb, shell_cfg.sc_channel);

    /* Start a shell */
    while (!chThdShouldTerminateX()) {
        shell_tp = chThdCreateStatic(shell_wa, sizeof(shell_wa), NORMALPRIO, shellThread, (void *)&shell_cfg);
        chThdWait(shell_tp);
        chThdSleepMilliseconds(500);
    }

    chThdExit(MSG_OK);
}
