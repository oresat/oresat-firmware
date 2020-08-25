#ifndef _BLINK_H_
#define _BLINK_H_

#include "ch.h"

extern THD_WORKING_AREA(blink_wa, 0x40);
extern THD_FUNCTION(blink, arg);

#endif
