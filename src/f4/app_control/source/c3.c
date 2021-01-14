#include "c3.h"
#include "comms.h"

#define C3_EVENT_NEXT                       EVENT_MASK(0)
#define C3_EVENT_TX_ENABLE                  EVENT_MASK(1)
#define C3_EVENT_BAT_GOOD                   EVENT_MASK(2)

/* Global State Variables */
c3_state_t c3_state = PREDEPLOY;

/* Main Command, Communications, and Control Thread */
THD_WORKING_AREA(c3_wa, 0x400);
THD_FUNCTION(c3, arg)
{
    (void)arg;

    while (!chThdShouldTerminateX()) {
        switch (c3_state) {
        case PREDEPLOY:
            /* TODO: Wait for elapsed time */
            c3_state = DEPLOY;
            break;
        case DEPLOY:
            /* TODO: Deploy and test antennas */
            c3_state = STANDBY;
            break;
        case STANDBY:
            comms_beacon(false);
            break;
        case BEACON:
            comms_beacon(true);
            break;
        case EDL:
            break;
        default:
            c3_state = PREDEPLOY;
            break;
        };
    }

    chThdExit(MSG_OK);
}
