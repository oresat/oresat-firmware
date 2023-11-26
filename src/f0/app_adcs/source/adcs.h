#ifndef _IMU_H_
#define _IMU_H_

#include "ch.h"
#include "hal.h"

extern THD_WORKING_AREA(adcs_wa, 0x800);
extern THD_FUNCTION(adcs, arg);

#endif
