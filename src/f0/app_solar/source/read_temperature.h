#ifndef _READ_TEMPERATURE_H_
#define _READ_TEMPERATURE_H_

#include "ch.h"

#define WORKING_AREA_SIZE_FOR_READ_TEMPERATURE_THREAD (0x200)

extern THD_WORKING_AREA(read_temperature_wa, WORKING_AREA_SIZE_FOR_READ_TEMPERATURE_THREAD);
extern THD_FUNCTION(read_temperature, arg);

#endif
