/*
 * CAN Subsystem Hardware header file
 */
#ifndef _CAN_THREADS_H_
#define _CAN_THREADS_H_

//ChibiOS headers
#include "ch.h"
#include "hal.h"

//Thread prototypes
extern THD_WORKING_AREA(can_wa, 0x40);
extern THD_FUNCTION(can, p);
#endif
