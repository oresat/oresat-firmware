#include "wdt.h"

/* Watchdog Timer Thread */
THD_WORKING_AREA(wdt_wa, 0x40);
THD_FUNCTION(wdt, arg)
{
    (void)arg;

    palSetLineMode(LINE_LED_GREEN,PAL_MODE_OUTPUT_PUSHPULL);

    while (!chThdShouldTerminateX()) {
        palToggleLine(LINE_LED_GREEN);
        chThdSleepMilliseconds(250);
    }

    palClearLine(LINE_LED_GREEN);
    chThdExit(MSG_OK);
}
