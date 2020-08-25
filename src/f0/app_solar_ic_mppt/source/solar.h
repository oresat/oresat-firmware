#ifndef _SOLAR_H_
#define _SOLAR_H_

#include "ch.h"
#include "hal.h"

#define MAX5805_SADDR       0x18
#define INA226_SADDR        0x40
#define TMP101_SADDR        0x4A

/* Example blinker thread prototypes */
extern THD_WORKING_AREA(solar_wa, 0x400);
extern THD_FUNCTION(solar, arg);

#endif
