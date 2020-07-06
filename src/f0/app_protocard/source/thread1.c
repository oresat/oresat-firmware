#include "thread1.h"

/* Example blinker thread */
THD_WORKING_AREA(waThread1, 64);
THD_FUNCTION(Thread1, arg)
{
    (void)arg;

    while (!chThdShouldTerminateX()) {
        palToggleLine(LINE_LED);
        chThdSleepMilliseconds(500);
    }

    palClearLine(LINE_LED);
    chThdExit(MSG_OK);
}
