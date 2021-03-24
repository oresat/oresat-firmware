#include "c3.h"
#include "rtc.h"
#include "comms.h"
#include "CANopen.h"

#define CHIBIOS_EPOCH                       315532800U  /* ChibiOS Epoch in Unix Time */
#define PREDEPLOY_TIMEOUT                   45U         /* Deployment timeout in minutes */

/* Placeholder variables for satellite state from object dictionary */
/* TODO: Switch to actual OD variables */
bool bat_good = true;
bool edl = false;

/* Global State Variables */
thread_t *c3_tp;
rtc_state_t rtc_state;

/**
 * @brief   Alarm event callback
 *
 * @param[in]  rtcp     Pointer to @p RTCDriver instance
 * @param[in]  event    Alarm event
 *
 * @notapi
 */
static void alarmcb(RTCDriver *rtcp, rtcevent_t event)
{
    (void)rtcp;
    switch (event) {
    case RTC_EVENT_ALARM_A:
        chEvtSignalI(c3_tp, C3_EVENT_TIMER);
        break;
    case RTC_EVENT_ALARM_B:
        break;
    case RTC_EVENT_WAKEUP:
        break;
    default:
        break;
    }
}

/* Main Command, Communications, and Control Thread */
THD_WORKING_AREA(c3_wa, 0x400);
THD_FUNCTION(c3, arg)
{
    (void)arg;

    c3_tp = chThdGetSelfX();
    rtcSetCallback(&RTCD1, alarmcb);

    while (!chThdShouldTerminateX()) {
        switch (OD_C3State[0]) {
        case PREDEPLOY:
            /* Check if pre-deployment timeout has occured */
            if (difftime(CHIBIOS_EPOCH, rtcGetTimeUnix(NULL) > PREDEPLOY_TIMEOUT)) {
                /* Ready to deploy */
                rtcSetAlarm(&RTCD1, 0, NULL);
                /* TODO: Start state tracking */
                OD_C3State[0] = DEPLOY;
            } else {
                /* Must wait for pre-deployment timeout */
                rtc_state.alarm_a.alrmr = rtcEncodeElapsedAlarm(0, 0, PREDEPLOY_TIMEOUT, 0);
                rtcSetAlarm(&RTCD1, 0, &rtc_state.alarm_a);
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

    rtcSetCallback(&RTCD1, NULL);
    chThdExit(MSG_OK);
}
