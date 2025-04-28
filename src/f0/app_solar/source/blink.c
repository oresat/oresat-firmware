#include "ch.h"
#include "hal.h"

THD_WORKING_AREA(blink_wa, 0x40);
THD_FUNCTION(blink, arg) {
    (void)arg;

    while (!chThdShouldTerminateX()) {
        palToggleLine(LINE_LED);
        chThdSleepMilliseconds(250);
    }

    palClearLine(LINE_LED);
    chThdExit(MSG_OK);
}
