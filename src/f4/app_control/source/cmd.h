#ifndef _CMD_H_
#define _CMD_H_

#include "ch.h"
#include "hal.h"

extern THD_WORKING_AREA(cmd_wa, 0x100);
extern THD_FUNCTION(cmd, arg);

#endif
