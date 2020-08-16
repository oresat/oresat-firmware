#include "blink.h"

/* Example blinker thread */
THD_WORKING_AREA(blink_wa, 0x40);
THD_FUNCTION(blink, arg)
{
    (void)arg;

    palSetLineMode(LINE_LED,PAL_MODE_OUTPUT_PUSHPULL);

    while (!chThdShouldTerminateX()) {
        palToggleLine(LINE_LED);
        chThdSleepMilliseconds(500);
    }

    while(1) {
        palClearLine(LINE_LED);
        chThdSleepMilliseconds(500);
        palSetLine(LINE_LED);
        chThdSleepMilliseconds(500);
    }

    palClearLine(LINE_LED);
    chThdExit(MSG_OK);
}
