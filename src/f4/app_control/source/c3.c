#include "c3.h"
#include "rtc.h"
#include "comms.h"
#include "CANopen.h"

#define CHIBIOS_EPOCH                       315532800U  /* ChibiOS Epoch in Unix Time */

/* Placeholder variables for satellite state from object dictionary */
/* TODO: Switch to actual OD variables */
bool bat_good = true;
bool edl = false;
uint32_t predeploy_timeout = 2700;

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
    chSysLockFromISR();
    switch (event) {
    case RTC_EVENT_ALARM_A:
    case RTC_EVENT_ALARM_B:
    case RTC_EVENT_WAKEUP:
        chEvtSignalI(c3_tp, C3_EVENT_WAKEUP);
        break;
    default:
        break;
    }
    chSysUnlockFromISR();
}

static void rtcStateSave(void)
{
    rtcGetTime(&RTCD1, &rtc_state.timestamp);
    if (RTCD1.rtc->CR & RTC_CR_ALRAE) {
        rtcGetAlarm(&RTCD1, 0, &rtc_state.alarm_a);
    } else {
        rtc_state.alarm_a.alrmr = 0;
    }
    if (RTCD1.rtc->CR & RTC_CR_ALRBE) {
        rtcGetAlarm(&RTCD1, 1, &rtc_state.alarm_b);
    } else {
        rtc_state.alarm_b.alrmr = 0;
    }
    if (RTCD1.rtc->CR & RTC_CR_WUTE) {
        rtcSTM32GetPeriodicWakeup(&RTCD1, &rtc_state.wakeup);
    } else {
        rtc_state.wakeup.wutr = 0;
    }
}

static void rtcStateRestore(void)
{
    if (rtc_state.alarm_a.alrmr != 0) {
        rtcSetAlarm(&RTCD1, 0, &rtc_state.alarm_a);
    }
    if (rtc_state.alarm_b.alrmr != 0) {
        rtcSetAlarm(&RTCD1, 1, &rtc_state.alarm_b);
    }
    if (rtc_state.wakeup.wutr != 0) {
        rtcSTM32SetPeriodicWakeup(&RTCD1, &rtc_state.wakeup);
    }
}

/* Main Command, Communications, and Control Thread */
THD_WORKING_AREA(c3_wa, 0x400);
THD_FUNCTION(c3, arg)
{
    (void)arg;

    c3_tp = chThdGetSelfX();
    rtcSetCallback(&RTCD1, alarmcb);

    /* Restore saved state */
    rtcStateRestore();

    /* State loop */
    while (!chThdShouldTerminateX()) {
        switch (OD_C3State[0]) {
        case PREDEPLOY:
            /* Check if pre-deployment timeout has occured */
            if (difftime(rtcGetTimeUnix(NULL), CHIBIOS_EPOCH) >= predeploy_timeout) {
                /* Ready to deploy */
                rtcSetAlarm(&RTCD1, 0, NULL);
                /* TODO: Start state tracking */
                /*rtc_state.wakeup.wutr = 0;*/
                /*rtcSTM32SetPeriodicWakeup(&RTCD1, &rtc_state.wakeup);*/
                OD_C3State[0] = DEPLOY;
            } else {
                /* Must wait for pre-deployment timeout */
                RTCDateTime timespec = {
                    .year = 0,
                    .month = 1,
                    .dstflag = 0,
                    .dayofweek = 1,
                    .day = 1,
                    .millisecond = 0,
                };
                rtc_state.alarm_a.alrmr = rtcEncodeRelAlarm(&timespec, 0, 0, 0, predeploy_timeout);
                rtcSetAlarm(&RTCD1, 0, &rtc_state.alarm_a);
                chEvtWaitAny(C3_EVENT_WAKEUP | C3_EVENT_TERMINATE);
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
        if (OD_C3State[0] > PREDEPLOY) {
            rtcStateSave();
        }
    }

    rtcSetCallback(&RTCD1, NULL);
    chThdExit(MSG_OK);
}
