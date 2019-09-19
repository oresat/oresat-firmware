
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
 // (void)argv;
 // (void)chp;
 
 // eventmask_t events = 0;
  
  //chprintf(chp, "changeState %s\n\r", argv[1]);
  //*
  if(strcmp(argv[1],"active"))
  {
    pacs->can_buf.cmd[CAN_CMD_0] = CMD_CHANGE_STATE;
    pacs->can_buf.cmd[CAN_CMD_ARG] = ST_MAX_PWR;
    chprintf(chp, "changeState active%s\n\r",argv[1]);
//    chSysLock();
//    chEvtSignal(pacs->pacsthread, CMD_CHANGE_STATE);
//    chSysUnlock();
  }
  else if(strcmp(argv[1],"passive"))
  {
    pacs->can_buf.cmd[CAN_CMD_0] = CMD_CHANGE_STATE;
    pacs->can_buf.cmd[CAN_CMD_ARG] = ST_RDY;
    chprintf(chp, "changeState passive %s\n\r", argv[1]);
  }
  else
  {
    chprintf(chp, "Invalid state change request %s\n\r", argv[1]);
    return;
  }
  chprintf(chp, "sending signal\n\r", argv[1]);
  //chEvtSignal(pacs->pacsthread, 0);
  chEvtSignal(pacs->pacsthread, CMD_CHANGE_STATE);
  //chEvtSignal(pacs->pacsthread,EVENT_MASK(0));
//  handleEvent(pacs);
  //*/
}

void cmd_reactionWheelCtrl(BaseSequentialStream *chp, int argc, char *argv[])
{
  (void)argc;
  (void)argv;
  (void)chp;
  
  if(strcmp(argv[1],"on"))
  {
    pacs->can_buf.cmd[CAN_CMD_0] = CMD_CALL_FUNCTION;
    pacs->can_buf.cmd[CAN_CMD_ARG] = FN_RW_START;
  }
  else if(strcmp(argv[1],"on"))
  {
    pacs->can_buf.cmd[CAN_CMD_0] = CMD_CALL_FUNCTION;
    pacs->can_buf.cmd[CAN_CMD_ARG] = FN_RW_STOP;
  }
  else
  {
    chprintf(chp, "Invalid option: %s\n\r", argv[1]);
    return;
  }
  handleEvent(pacs);
}

void cmd_magnetorquerCtrl(BaseSequentialStream *chp, int argc, char *argv[])
{
  (void)argc;
  (void)argv;
  (void)chp;
    
  //pacs->can_buf.cmd[CAN_CMD_0] = CMD_CALL_FUNCTION;
  //pacs->can_buf.cmd[CAN_CMD_ARG] = FN_RW_STOP;
  //handleEvent(pacs);
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
  pacs = (ACS *)arg;

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
