#ifndef _SOLAR_H_
#define _SOLAR_H_

#include "ch.h"
#include "hal.h"

#define INA226_SADDR          (0x40)
#define TMP101_ADDR_SENSOR_01 (0x48)
#define TMP101_ADDR_SENSOR_02 (0x4A)

extern const I2CConfig i2cconfig;

/* Solar application thread prototypes */
extern THD_WORKING_AREA(solar_wa, 0x400);
extern THD_FUNCTION(solar, arg);
extern THD_WORKING_AREA(read_temperature_wa, 0x200);
extern THD_FUNCTION(read_temperature, arg);

#endif
