#ifndef _READ_TEMPERATURE_H_
#define _READ_TEMPERATURE_H_

#include "ch.h"

extern THD_WORKING_AREA(read_temperature_wa, 0x80);
extern THD_FUNCTION(read_temperature, arg);

#endif
