#include <stdlib.h>
#include <string.h>

#include "command.h"
#include "time_sync.h"
#include "chprintf.h"
#include "shell.h"

/*===========================================================================*/
/* Support functions                                                         */
/*===========================================================================*/
size_t read_cb(void *chp, const char *buf, size_t count)
{
    chprintf(chp, "%s\r\n", buf);

    return count;
}

/*===========================================================================*/
/* OreSat CAN Bus                                                            */
/*===========================================================================*/
void cmd_can(BaseSequentialStream *chp, int argc, char *argv[])
{

}
/*===========================================================================*/
/* Time                                                                      */
/*===========================================================================*/
void time_usage(BaseSequentialStream *chp)
{
    chprintf(chp, "Usage: time set|get <UNIX Time>\r\n");
}

void cmd_time(BaseSequentialStream *chp, int argc, char *argv[])
{
    time_t unix_time;
    uint32_t msec;
    if (argc < 1) {
        time_usage(chp);
        return;
    }
    if (!strcmp(argv[0], "get")) {
        unix_time = get_time_unix(&msec);
        chprintf(chp, "UNIX Time: %s\r\n", ctime(&unix_time));
    } else if (!strcmp(argv[0], "set") && argc > 1) {
        set_time_unix(strtoul(argv[1], NULL, 0), 0);
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
    (BaseSequentialStream *)&SD2,
    commands,
    histbuf,
    sizeof(histbuf),
};

THD_WORKING_AREA(shell_wa, 0x200);
THD_WORKING_AREA(cmd_wa, 0x200);
THD_FUNCTION(cmd, arg)
{
    (void)arg;

    while (!chThdShouldTerminateX()) {
        thread_t *shell_tp = chThdCreateStatic(shell_wa, sizeof(shell_wa), NORMALPRIO, shellThread, (void *)&shell_cfg);
        chThdWait(shell_tp);
        chThdSleepMilliseconds(500);
    }

    chThdExit(MSG_OK);
}
