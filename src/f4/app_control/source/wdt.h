#ifndef _WDT_H_
#define _WDT_H_

#include "ch.h"
#include "hal.h"

/* Watchdog Timer Thread Prototypes */
extern THD_WORKING_AREA(wdt_wa, 0x40);
extern THD_FUNCTION(wdt, arg);

#endif
