/*
 * CAN Subsystem Hardware header file
 */
#ifndef _CAN_THREADS_H_
#define _CAN_THREADS_H_

//ChibiOS headers
#include "ch.h"
#include "hal.h"

//Thread prototypes
extern THD_WORKING_AREA(can_rx_wa, 128);
extern THD_FUNCTION(can_rx, p);
extern THD_WORKING_AREA(can_tpdo_wa, 128);
extern THD_FUNCTION(can_tpdo, p);

void can_start_threads(void);
#endif
