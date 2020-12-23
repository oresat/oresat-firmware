#ifndef _C3_H_
#define _C3_H_

#include "ch.h"
#include "hal.h"

/* Main Command, Communications, and Control Thread Prototypes */
extern THD_WORKING_AREA(c3_wa, 0x40);
extern THD_FUNCTION(c3, arg);

#endif
