#ifndef _ACS_THREADS_H_
#define _ACS_THREADS_H_

#include "ch.h"
#include "hal.h"

// Example blinker thread prototypes
extern THD_WORKING_AREA(waACSThread, 128);
extern THD_FUNCTION(ACSThread, arg);

#endif
