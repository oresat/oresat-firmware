#include "c3.h"
#include "comms.h"

#define C3_EVENT_TIMER                      EVENT_MASK(0)
#define C3_EVENT_TX                         EVENT_MASK(1)
#define C3_EVENT_BAT                        EVENT_MASK(2)
#define C3_EVENT_EDL                        EVENT_MASK(3)

/* Global State Variables */
c3_state_t c3_state = PREDEPLOY;
thread_t *c3_tp;

/* Main Command, Communications, and Control Thread */
THD_WORKING_AREA(c3_wa, 0x400);
THD_FUNCTION(c3, arg)
{
    (void)arg;

    c3_tp = chThdGetSelfX();

    while (!chThdShouldTerminateX()) {
        switch (c3_state) {
        case PREDEPLOY:
            /* TODO: Check for timer elapsed condition */
            if (1) {
                c3_state = DEPLOY;
            } else {
                chEvtWaitAny(C3_EVENT_TIMER);
            }
            break;
        case DEPLOY:
            /* TODO: Deploy and test antennas */
            c3_state = STANDBY;
            break;
        case STANDBY:
            comms_beacon(false);

            if (0) {
                c3_state = EDL;
            } else if (0) {
                c3_state = BEACON;
            } else {
                chEvtWaitAny(C3_EVENT_TX | C3_EVENT_BAT | C3_EVENT_EDL);
            }
            break;
        case BEACON:
            comms_beacon(true);

            if (0) {
                c3_state = EDL;
            } else if (0) {
                c3_state = STANDBY;
            } else {
                chEvtWaitAny(C3_EVENT_TX | C3_EVENT_BAT | C3_EVENT_EDL);
            }
            break;
        case EDL:
            comms_beacon(false);

            if (0) {
                c3_state = STANDBY;
            } else if (0) {
                c3_state = BEACON;
            } else {
                chEvtWaitAny(C3_EVENT_EDL);
            }
            break;
        default:
            c3_state = PREDEPLOY;
            break;
        };
    }

    chThdExit(MSG_OK);
}
