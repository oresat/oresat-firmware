
#include <stdlib.h>
#include <string.h>

#include "acs_command.h"
#include "acs.h"
//#include "CO_master.h"
#include "chprintf.h"
#include "shell.h"

void cmd_dbgon(BaseSequentialStream *chp, int argc, char *argv[])
{
  (void)argc;
  (void)argv;
  //chprintf(chp, "Dbg LEDs on\n\r");
  palSetPad(GPIOB,1U);
  palSetPad(GPIOB,2U);
}

void cmd_dbgoff(BaseSequentialStream *chp, int argc, char *argv[])
{
  (void)argc;
  (void)argv;
  //chprintf(chp, "Dbg LEDs off");
  palClearPad(GPIOB,1U);
  palClearPad(GPIOB,2U);
}

void cmd_changeState(BaseSequentialStream *chp, int argc, char *argv[])
{
  
}

void cmd_reactionWheelCtrl(BaseSequentialStream *chp, int argc, char *argv[])
{
    
}

static const ShellCommand commands[] = {
  {"dbgon", cmd_dbgon},
  {"dbgoff", cmd_dbgoff},
  {"cs", cmd_changeState},
  {"rw", cmd_reactionWheelCtrl},
  {NULL, NULL}
};

static const ShellConfig shell_cfg = {
  (BaseSequentialStream *)&LPSD1,
  commands
};

THD_WORKING_AREA(shell_wa, 0x200);
THD_WORKING_AREA(cmd_wa, 0x200);
THD_FUNCTION(cmd, arg)
{
  (void)arg;

  while (!chThdShouldTerminateX()) {
    thread_t *shell_tp = chThdCreateStatic(
      shell_wa,
      sizeof(shell_wa),
      NORMALPRIO, shellThread,
      (void *)&shell_cfg
    );
    chThdWait(shell_tp);
    chThdSleepMilliseconds(500);
  }

  chThdExit(MSG_OK);
}
