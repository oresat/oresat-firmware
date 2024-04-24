#ifndef _HEARTMON_H_
#define _HEARTMON_H_

#include "ch.h"
#include "hal.h"

// heartbeat monitoring thread prototypes 
extern THD_WORKING_AREA(heartmon_wa, 0x400);
extern THD_FUNCTION(heartmon, arg);

#endif
