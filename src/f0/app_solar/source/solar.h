#ifndef _SOLAR_H_
#define _SOLAR_H_

#include "ch.h"
#include "hal.h"

#define INA226_SADDR            (0x40)



/* Solar application thread prototypes */
extern THD_WORKING_AREA(solar_wa, 0x400);
extern THD_FUNCTION(solar, arg);
extern THD_WORKING_AREA(sensor_mon_wa, 0x200);
extern THD_FUNCTION(sensor_mon, arg);

#endif
