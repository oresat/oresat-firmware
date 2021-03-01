#include "c3.h"
#include "comms.h"

/* Placeholder variables for satellite state from object dictionary */
/* TODO: Switch to actual OD variables */
bool timeout_complete = true;
bool tx_enable = false;
bool bat_good = false;
bool edl = false;

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
            if (timeout_complete) {
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

            if (edl) {
                c3_state = EDL;
            } else if (tx_enable && bat_good) {
                c3_state = BEACON;
            } else {
                chEvtWaitAny(C3_EVENT_TX | C3_EVENT_BAT | C3_EVENT_EDL);
            }
            break;
        case BEACON:
            comms_beacon(true);

            if (edl) {
                c3_state = EDL;
            } else if (!tx_enable || !bat_good) {
                c3_state = STANDBY;
            } else {
                chEvtWaitAny(C3_EVENT_TX | C3_EVENT_BAT | C3_EVENT_EDL);
            }
            break;
        case EDL:
            comms_beacon(false);

            if (!edl) {
                if (tx_enable && bat_good) {
                    c3_state = BEACON;
                } else {
                    c3_state = STANDBY;
                }
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
