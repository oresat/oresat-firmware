#ifndef _ACS_COMMAND_H_
#define _ACS_COMMAND_H_

#include "ch.h"
#include "hal.h"
//#include "opd.h"

/* Example blinker thread prototypes */
extern THD_WORKING_AREA(cmd_wa, 0x200);
extern THD_FUNCTION(cmd, arg);

#endif
