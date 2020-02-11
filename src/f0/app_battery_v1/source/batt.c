#include "batt.h"

/* Battery monitoring thread */
THD_WORKING_AREA(batt_wa, 0x40);
THD_FUNCTION(batt, arg)
{
    (void)arg;

    palSetLineMode(LINE_LED_GREEN,PAL_MODE_OUTPUT_PUSHPULL);

    while (!chThdShouldTerminateX()) {
        palToggleLine(LINE_LED_GREEN);
        chThdSleepMilliseconds(500);
    }

    palClearLine(LINE_LED_GREEN);
    chThdExit(MSG_OK);
}
