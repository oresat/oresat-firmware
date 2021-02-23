#ifndef _BLINK_H_
#define _BLINK_H_

#include "ch.h"
#include "hal.h"

/* Example blinker thread prototypes */
extern THD_WORKING_AREA(blink_wa, 0x40);
extern THD_FUNCTION(blink, arg);

#endif
