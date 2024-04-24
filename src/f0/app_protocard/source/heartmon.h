#ifndef _BLINK_H_
#define _BLINK_H_

#include "ch.h"
#include "hal.h"

/**
 *
 * blinking example thread declaration 
 *
*/
extern THD_WORKING_AREA(blink_wa, 0x400);
extern THD_FUNCTION(blink, arg);

#endif
