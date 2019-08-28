#ifndef _NMT_H_
#define _NMT_H_

#include "ch.h"
#include "hal.h"

/* Example blinker thread prototypes */
extern THD_WORKING_AREA(nmt_wa, 0x200);
extern THD_FUNCTION(nmt, arg);

#endif
