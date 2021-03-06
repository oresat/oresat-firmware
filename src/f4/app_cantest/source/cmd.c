#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "cmd.h"
#include "test_time.h"
#include "test_lfs.h"
#include "test_bootloader.h"
#include "chprintf.h"
#include "shell.h"

static thread_t *shell_tp;

/*===========================================================================*/
/* Placeholder                                                               */
/*===========================================================================*/

/*===========================================================================*/
/* Shell                                                                     */
/*===========================================================================*/
static const ShellCommand commands[] = {
    {"time", cmd_time},
    {"lfs", cmd_lfs},
    {"bootloader", cmd_bootloader},
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

    /* Start a shell */
    while (!chThdShouldTerminateX()) {
        shell_tp = chThdCreateStatic(shell_wa, sizeof(shell_wa), NORMALPRIO, shellThread, (void *)&shell_cfg);
        chThdWait(shell_tp);
        chThdSleepMilliseconds(500);
    }

    chThdExit(MSG_OK);
}
