#ifndef _HEARTBEAT_H_
#define _HEARTBEAT_H_

#include "ch.h"
#include "hal.h"

// heartbeat monitoring thread prototypes 
extern THD_WORKING_AREA(heartbeat_wa, 0x400);
extern THD_FUNCTION(heartbeat, arg);

#endif
