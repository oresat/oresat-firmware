#include "c3.h"
#include "rtc.h"
#include "fram.h"
#include "comms.h"
#include "CANopen.h"

#define CHIBIOS_EPOCH                       315532800U  /* ChibiOS Epoch in Unix Time */

/* Placeholder variables for satellite state from object dictionary */
/* TODO: Switch to actual OD variables */
bool bat_good = true;
bool edl = false;

/* Global State Variables */
thread_t *c3_tp;

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
    rtc_state_t state = {0};
    /* Get the current state of RTC */
    rtcGetTime(&RTCD1, &state.timestamp);
    if (RTCD1.rtc->CR & RTC_CR_ALRAE) {
        rtcGetAlarm(&RTCD1, 0, &state.alarm_a);
    }
    if (RTCD1.rtc->CR & RTC_CR_ALRBE) {
        rtcGetAlarm(&RTCD1, 1, &state.alarm_b);
    }
    if (RTCD1.rtc->CR & RTC_CR_WUTE) {
        rtcSTM32GetPeriodicWakeup(&RTCD1, &state.wakeup);
    }
    /* Write RTC state to FRAM */
    framWrite(&FRAMD1, 0x0000, &state, sizeof(state));
    /* TODO: Backup/sync with external RTC */
}

static void rtcStateRestore(void)
{
    rtc_state_t state;
    time_t unix;

    /* Read the stored RTC state from FRAM */
    framRead(&FRAMD1, 0x0000, &state, sizeof(state));
    unix = rtcConvertDateTimeToUnix(&state.timestamp, NULL);

    /* TODO: Get RTC values from external RTC and reach quorum */
    if (difftime(unix, rtcGetTimeUnix(NULL)) > 0) {
        /* Stored state timestamp is greater */
        rtcSetTime(&RTCD1, &state.timestamp);
    }

    /* Apply state */
    if (state.alarm_a.alrmr != 0) {
        rtcSetAlarm(&RTCD1, 0, &state.alarm_a);
    }
    if (state.alarm_b.alrmr != 0) {
        rtcSetAlarm(&RTCD1, 1, &state.alarm_b);
    }
    if (state.wakeup.wutr != 0) {
        rtcSTM32SetPeriodicWakeup(&RTCD1, &state.wakeup);
    }
}

/* Main Command, Communications, and Control Thread */
THD_WORKING_AREA(c3_wa, 0x400);
THD_FUNCTION(c3, arg)
{
    (void)arg;
    rtc_state_t rtc_state;
    eventmask_t event = 0;

    c3_tp = chThdGetSelfX();
    rtcSetCallback(&RTCD1, alarmcb);

    /* Restore saved state */
    rtcStateRestore();

    /* State loop */
    while (!chThdShouldTerminateX()) {
        switch (OD_C3State[0]) {
        case PREDEPLOY:
            /* Check if pre-deployment timeout has occured */
            while (difftime(rtcGetTimeUnix(NULL), CHIBIOS_EPOCH) < OD_preDeployTimeout) {
                /* Must wait for pre-deployment timeout */
                if ((RTCD1.rtc->CR & RTC_CR_ALRAE) == 0) {
                    /* ref_time is the ChibiOS epoch */
                    RTCDateTime ref_time;
                    rtcConvertUnixToDateTime(&ref_time, CHIBIOS_EPOCH, 0);
                    rtc_state.alarm_a.alrmr = rtcEncodeRelAlarm(&ref_time, 0, 0, 0, OD_preDeployTimeout);
                    rtcSetAlarm(&RTCD1, 0, &rtc_state.alarm_a);
                }
                event = chEvtWaitAny(C3_EVENT_WAKEUP | C3_EVENT_TERMINATE);
                if (event & C3_EVENT_TERMINATE)
                    break;
            }

            /* Ready to deploy */
            rtcSetAlarm(&RTCD1, 0, NULL);
            OD_C3State[0] = DEPLOY;
            break;
        case DEPLOY:
            /* Set 9 + 1 second RTC wakeup alarm for state tracking */
            rtc_state.wakeup.wutr = (RTC_CR_WUCKSEL_2 << 16) | 9;
            rtcSTM32SetPeriodicWakeup(&RTCD1, &rtc_state.wakeup);
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
    rtcSTM32SetPeriodicWakeup(&RTCD1, NULL);
    rtcSetAlarm(&RTCD1, 0, NULL);
    rtcSetAlarm(&RTCD1, 1, NULL);
    chThdExit(MSG_OK);
}

void factory_reset(void)
{
    chThdTerminate(c3_tp);
    chEvtSignal(c3_tp, C3_EVENT_TERMINATE);
    chThdWait(c3_tp);
    framEraseAll(&FRAMD1);
    RCC->BDCR |= RCC_BDCR_BDRST;
    RCC->BDCR &= ~RCC_BDCR_BDRST;
    NVIC_SystemReset();
}
