#ifndef _CLI_H_
#define _CLI_H_

#include "ch.h"
#include "hal.h"

extern THD_WORKING_AREA(cli_wa, 0x100);
extern THD_FUNCTION(cli, arg);

#endif
