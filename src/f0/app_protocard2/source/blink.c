#include "blink.h"
#include "chprintf.h"

/* Example blinker thread */
THD_WORKING_AREA(blink_wa, 0x40);
THD_FUNCTION(blink, arg)
{
    (void)arg;

    palSetLineMode(LINE_LED,PAL_MODE_OUTPUT_PUSHPULL);

    uint32_t i = 0;
    while (!chThdShouldTerminateX()) {
        palToggleLine(LINE_LED);
        chThdSleepMilliseconds(500);
        chprintf((BaseSequentialStream *) &SD2, "%u\r\n", i++);
    }

    palClearLine(LINE_LED);
    chThdExit(MSG_OK);
}
