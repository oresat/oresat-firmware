#include "c3.h"
#include "rtc.h"
#include "comms.h"
#include "CANopen.h"

#define PREDEPLOY_TIMEOUT                   2700000 /* 45 Minutes in ms */

/* Placeholder variables for satellite state from object dictionary */
/* TODO: Switch to actual OD variables */
bool bat_good = true;
bool edl = false;

/* Global State Variables */
thread_t *c3_tp;

/* Main Command, Communications, and Control Thread */
THD_WORKING_AREA(c3_wa, 0x400);
THD_FUNCTION(c3, arg)
{
    (void)arg;

    c3_tp = chThdGetSelfX();

    while (!chThdShouldTerminateX()) {
        RTCDateTime timespec;
        rtcGetTime(rtcp, &timespec);

        switch (OD_C3State[0]) {
        case PREDEPLOY:
            /* Check if pre-deployment timeout has occured */
            if (1) {
                /* Ready to deploy */
                /* TODO: Start state tracking */
                OD_C3State[0] = DEPLOY;
            } else {
                /* Must wait for pre-deployment timeout */
                /* TODO: Set alarm */
                chEvtWaitAny(C3_EVENT_WAKEUP | C3_EVENT_TERMINATE | C3_EVENT_TIMER);
            }
            break;
        case DEPLOY:
            /* TODO: Deploy and test antennas */
            OD_C3State[0] = STANDBY;
            break;
        case STANDBY:
            comms_beacon(false);

            if (edl) {
                OD_C3State[0] = EDL;
            } else if (OD_TX_Control.enabled && bat_good) {
                OD_C3State[0] = BEACON;
            } else {
                chEvtWaitAny(C3_EVENT_WAKEUP | C3_EVENT_TERMINATE | C3_EVENT_TX | C3_EVENT_BAT | C3_EVENT_EDL);
            }
            break;
        case BEACON:
            comms_beacon(true);

            if (edl) {
                OD_C3State[0] = EDL;
            } else if (!OD_TX_Control.enabled || !bat_good) {
                OD_C3State[0] = STANDBY;
            } else {
                chEvtWaitAny(C3_EVENT_WAKEUP | C3_EVENT_TERMINATE | C3_EVENT_TX | C3_EVENT_BAT | C3_EVENT_EDL);
            }
            break;
        case EDL:
            comms_beacon(false);

            if (!edl) {
                if (OD_TX_Control.enabled && bat_good) {
                    OD_C3State[0] = BEACON;
                } else {
                    OD_C3State[0] = STANDBY;
                }
            } else {
                chEvtWaitAny(C3_EVENT_WAKEUP | C3_EVENT_TERMINATE | C3_EVENT_EDL);
            }
            break;
        default:
            OD_C3State[0] = PREDEPLOY;
            break;
        };
    }

    chThdExit(MSG_OK);
}
