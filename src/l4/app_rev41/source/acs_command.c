
#include <stdlib.h>
#include <string.h>

#include "acs_command.h"
#include "acs.h"
//#include "CO_master.h"
#include "chprintf.h"
#include "shell.h"

ACS *pacs = NULL;

void cmd_dbgon(BaseSequentialStream *chp, int argc, char *argv[])
{
  (void)argc;
  (void)argv;
  (void)chp;
  //chprintf(chp, "Dbg LEDs on\n\r");
  palSetPad(GPIOB,1U);
  palSetPad(GPIOB,2U);
}

void cmd_dbgoff(BaseSequentialStream *chp, int argc, char *argv[])
{
  (void)argc;
  (void)argv;
  (void)chp;
  //chprintf(chp, "Dbg LEDs off");
  palClearPad(GPIOB,1U);
  palClearPad(GPIOB,2U);
}

void cmd_changeState(BaseSequentialStream *chp, int argc, char *argv[])
{
  (void)argc;
  (void)argv;
 // (void)chp;
  
  chprintf(chp, "change state\n\r");
  pacs->can_buf.cmd[CAN_CMD_0] = CMD_CHANGE_STATE;
  pacs->can_buf.cmd[CAN_CMD_ARG] = ST_MAX_PWR;
  transitionState(pacs);
  /*
  if(strcmp(argv[1],"active"))
  {
//    chSysLockFromISR();
    pacs->can_buf.cmd[CAN_CMD_ARG] = CMD_CHANGE_STATE;
    pacs->can_buf.cmd[CAN_CMD_2] = ST_MAX_PWR;
    transitionState(pacs);
//    chEvtSignalI(uart_thread, events);
//    chSysUnlockFromISR();
  }
  //*/
}

void cmd_reactionWheelCtrl(BaseSequentialStream *chp, int argc, char *argv[])
{
  (void)argc;
  (void)argv;
  (void)chp;

}

void cmd_magnetorquerCtrl(BaseSequentialStream *chp, int argc, char *argv[])
{
  (void)argc;
  (void)argv;
  (void)chp;
    
}

//*
static const ShellCommand commands[] = {
  {"dbgon", cmd_dbgon},
  {"dbgoff", cmd_dbgoff},
  {"cs", cmd_changeState},
  {"rw", cmd_reactionWheelCtrl},
  {"mtqr", cmd_reactionWheelCtrl},
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
//  (void)arg;
  pacs = (ACS *)&arg;

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

//*/
