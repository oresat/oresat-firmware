#ifndef _DEMO_H_
#define _DEMO_H_

#include "ch.h"
#include "hal.h"

#include "ltc2990.h"
#include "solar_v1.h"

// Example blinker thread prototypes
extern THD_WORKING_AREA(demo_measure_wa, 128);
extern THD_FUNCTION(demo_measure, arg);

#endif
