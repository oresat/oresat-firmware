#include "wdt.h"

/* Watchdog Timer Thread */
THD_WORKING_AREA(wdt_wa, 0x40);
THD_FUNCTION(wdt, arg)
{
    (void)arg;

    while (!chThdShouldTerminateX()) {
        palToggleLine(LINE_WDT);
        chThdSleepMilliseconds(250);
    }

    palClearLine(LINE_WDT);
    chThdExit(MSG_OK);
}
