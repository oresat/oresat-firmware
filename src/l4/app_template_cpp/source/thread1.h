#ifndef _THREAD1_H_
#define _THREAD1_H_

#include "ch.h"
#include "hal.h"

/// Example blinker thread prototypes
extern THD_WORKING_AREA(waThread1, 128);
extern THD_FUNCTION(Thread1, arg);

#endif
