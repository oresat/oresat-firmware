#ifndef _ACS_COMMAND_H_
#define _ACS_COMMAND_H_

#include "ch.h"
#include "hal.h"
//#include "opd.h"

/* Example blinker thread prototypes */
extern THD_WORKING_AREA(cmd_wa, 0x200);
extern THD_FUNCTION(cmd, arg);

extern void cmd_dbgon(BaseSequentialStream *chp, int argc, char *argv[]);
extern void cmd_dbgoff(BaseSequentialStream *chp, int argc, char *argv[]);
extern void cmd_changeState(BaseSequentialStream *chp, int argc, char *argv[]);
extern void cmd_reactionWheelCtrl(BaseSequentialStream *chp, int argc, char *argv[]);
extern void cmd_magnetorquerCtrl(BaseSequentialStream *chp, int argc, char *argv[]);

#endif
