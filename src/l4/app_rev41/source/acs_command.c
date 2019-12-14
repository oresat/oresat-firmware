
#include <stdlib.h>
#include <string.h>
#include "acs_command.h"
#include "acs.h"
#include "chprintf.h"
#include "shell.h"

ACS *pacs = NULL;

void cmd_leds(BaseSequentialStream *chp, int argc, char *argv[])
{
  (void)argc;
  (void)argv;
  (void)chp;
  
  chprintf(chp, "LEDs %s\n\r",argv[0]);
  
  if(!strcmp(argv[0],"on"))
  {
    palSetPad(GPIOB,1U);
    palSetPad(GPIOB,2U);
  }
  else if(!strcmp(argv[0],"off"))
  {
    palClearPad(GPIOB,1U);
    palClearPad(GPIOB,2U);
  }
  else
  {
    chprintf(chp, "Invalid LED command:  %s\n\r", argv[0]);
    return;
  }
}

void cmd_changeState(BaseSequentialStream *chp, int argc, char *argv[])
{
  (void)argc;
 
//  chprintf(chp, "changeState %s\n\r", argv[0]);
  //*
  if(!strcmp(argv[0],"active"))
  {
    pacs->can_buf.cmd[CAN_CMD_0] = CMD_CHANGE_STATE;
    pacs->can_buf.cmd[CAN_CMD_ARG] = ST_MAX_PWR;
  }
  else if(!strcmp(argv[0],"passive"))
  {
    pacs->can_buf.cmd[CAN_CMD_0] = CMD_CHANGE_STATE;
    pacs->can_buf.cmd[CAN_CMD_ARG] = ST_RDY;
  }
  else
  {
    chprintf(chp, "Invalid state change request %s\n\r", argv[0]);
    return;
  }

//  chprintf(chp, "sending signal for state change to \n\r", argv[0]);

  chSysLock();
  chEvtSignal(pacs->pacsthread, CMD_CHANGE_STATE);
  chSysUnlock();
  
}

void cmd_reactionWheelCtrl(BaseSequentialStream *chp, int argc, char *argv[])
{
  (void)argc;
  (void)argv;
  (void)chp;
  
  if(!strcmp(argv[0],"on"))
  {
//    pacs->can_buf.cmd[CAN_CMD_0] = CMD_CALL_FUNCTION;
//    pacs->can_buf.cmd[CAN_CMD_ARG] = FN_RW_START;
  }
  else if(!strcmp(argv[0],"off"))
  {
//    pacs->can_buf.cmd[CAN_CMD_0] = CMD_CALL_FUNCTION;
//    pacs->can_buf.cmd[CAN_CMD_ARG] = FN_RW_STOP;
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
  {"leds", cmd_leds},
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
 // chprintf((BaseSequentialStream *)&LPSD1, "Testing ACS structure: %s\n\r",pacs->teststring);
  
  chprintf((BaseSequentialStream *)&LPSD1, "Current state: %d\n\r",pacs->can_buf.status[CAN_SM_STATE]);
  
  while (!chThdShouldTerminateX()) {
    thread_t *shell_tp = chThdCreateStatic(
      shell_wa,
      sizeof(shell_wa),
      NORMALPRIO, 
      shellThread,
      (void *)&shell_cfg
    );
    chprintf((BaseSequentialStream *)&LPSD1, "Current state: %d\n\r",pacs->can_buf.status[CAN_SM_STATE]);
    chThdWait(shell_tp);
    chThdSleepMilliseconds(2000);
  }

  chThdExit(MSG_OK);
}

//*/
