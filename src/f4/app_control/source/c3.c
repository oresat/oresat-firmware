#include "c3.h"

/* Main Command, Communications, and Control Thread */
THD_WORKING_AREA(c3_wa, 0x40);
THD_FUNCTION(c3, arg)
{
    (void)arg;

    while (!chThdShouldTerminateX()) {
        chThdSleepMilliseconds(250);
    }

    chThdExit(MSG_OK);
}
