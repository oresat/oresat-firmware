#ifndef _PROTOCARD_H_
#define _PROTOCARD_H_

#include "ch.h"
#include "hal.h"

/**
 * blinking example thread declaration 
*/
extern THD_WORKING_AREA(blink_wa, 0x400);
extern THD_FUNCTION(blink, arg);

#endif
