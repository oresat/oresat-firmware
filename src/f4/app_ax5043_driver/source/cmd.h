#ifndef _CMD_H_
#define _CMD_H_

#include "ch.h"
#include "hal.h"
#include "ax5043.h"

extern AX5043Driver lband;
extern AX5043Driver uhf;

/* Example blinker thread prototypes */
extern THD_WORKING_AREA(cmd_wa, 0x200);
extern THD_FUNCTION(cmd, arg);

#endif
