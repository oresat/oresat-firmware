#ifndef _BATT_H_
#define _BATT_H_

#include "ch.h"
#include "hal.h"

/* Battery monitoring thread prototypes */
extern THD_WORKING_AREA(batt_wa, 0x40);
extern THD_FUNCTION(batt, arg);

#endif
