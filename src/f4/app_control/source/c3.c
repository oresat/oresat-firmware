#include "c3.h"
#include "comms.h"

/* Global State Variables */
c3_state_t c3_state = PRE_DEPLOY;

/* Main Command, Communications, and Control Thread */
THD_WORKING_AREA(c3_wa, 0x400);
THD_FUNCTION(c3, arg)
{
    (void)arg;

    while (!chThdShouldTerminateX()) {
    }

    chThdExit(MSG_OK);
}
