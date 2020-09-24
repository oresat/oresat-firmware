#ifndef _CMD_H_
#define _CMD_H_

#include "ch.h"
#include "hal.h"
#include "test_radio.h"

extern THD_WORKING_AREA(cmd_wa, 0x400);
extern THD_FUNCTION(cmd, arg);

#endif
