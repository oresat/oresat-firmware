#ifndef _IMU_H_
#define _IMU_H_

#include "ch.h"
#include "hal.h"

extern THD_WORKING_AREA(imu_wa, 0x400);
extern THD_FUNCTION(imu, arg);

#endif
