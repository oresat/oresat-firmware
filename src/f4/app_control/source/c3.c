#include "c3.h"
#include "rtc.h"
#include "fram.h"
#include "persist.h"
#include "comms.h"
#include "deployer.h"
#include "fw.h"
#include "worker.h"
#include "CANopen.h"
#include "OD.h"

/* TODO: Re-implement with OD interface */

#define CHIBIOS_EPOCH                       315532800U  /* ChibiOS Epoch in Unix Time */

/* Alarm allocations */
#define ALARM_A                             0
#define ALARM_B                             1
#define PREDEPLOY_ALARM                     ALARM_A     /* Predeploy timeout alarm number */
#define TX_ENABLE_ALARM                     ALARM_B     /* TX enable timeout alarm number */
#define EDL_ALARM                           ALARM_A     /* EDL timeout alarm number */
#define RESET_ALARM                         ALARM_A     /* Hard reset alarm number */

#define BAT_LEVEL_LOW                       6500U
#define BAT_LEVEL_HIGH                      7000U
#define BAT_LOW                             (OD_RAM.x7001_battery.VBattBP1 < BAT_LEVEL_LOW && OD_RAM.x7001_battery.VBattBP2 < BAT_LEVEL_LOW)

/* Global State Variables */
thread_t *c3_tp;
static time_t boot_time;

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
    chSysLockFromISR();
    switch (event) {
    case RTC_EVENT_ALARM_A:
        rtcSetAlarm(rtcp, ALARM_A, NULL);
        chEvtSignalI(c3_tp, C3_EVENT_WAKEUP);
        break;
    case RTC_EVENT_ALARM_B:
        rtcSetAlarm(rtcp, ALARM_B, NULL);
        chEvtSignalI(c3_tp, C3_EVENT_WAKEUP);
        break;
    case RTC_EVENT_WAKEUP:
        chEvtSignalI(c3_tp, C3_EVENT_WAKEUP);
        break;
    default:
        break;
    }
    chSysUnlockFromISR();
}

static void c3StateSave(void)
{
    /* Do not store state in predeploy */
    if (OD_RAM.x6000_C3_State[0] == PREDEPLOY)
        return;

    /* Get the current state of RTC */
    rtcGetTime(&RTCD1, (RTCDateTime*)(&OD_PERSIST_STATE.x6004_persistentState.timestamp));
    if (RTCD1.rtc->CR & RTC_CR_ALRAE) {
        rtcGetAlarm(&RTCD1, ALARM_A, (RTCAlarm*)(&OD_PERSIST_STATE.x6004_persistentState.alarmA));
    } else {
        OD_PERSIST_STATE.x6004_persistentState.alarmA = 0;
    }
    if (RTCD1.rtc->CR & RTC_CR_ALRBE) {
        rtcGetAlarm(&RTCD1, ALARM_B, (RTCAlarm*)(&OD_PERSIST_STATE.x6004_persistentState.alarmB));
    } else {
        OD_PERSIST_STATE.x6004_persistentState.alarmB = 0;
    }
    if (RTCD1.rtc->CR & RTC_CR_WUTE) {
        rtcSTM32GetPeriodicWakeup(&RTCD1, (RTCWakeup*)(&OD_PERSIST_STATE.x6004_persistentState.wakeup));
    } else {
        OD_PERSIST_STATE.x6004_persistentState.wakeup = 0;
    }
    /* Write state to FRAM */
    persistStoreGroup(&OD_PERSIST_STATE);
    /* TODO: Backup/sync with external RTC */
}

static void c3StateRestore(void)
{
    time_t unix;

    /* Read the stored state from FRAM */
    persistRestoreGroup(&OD_PERSIST_STATE);
    unix = rtcConvertDateTimeToUnix((RTCDateTime*)(&OD_PERSIST_STATE.x6004_persistentState.timestamp), NULL);

    /* TODO: Get RTC values from external RTC and reach quorum */
    if (difftime(unix, rtcGetTimeUnix(NULL)) > 0) {
        /* Stored state timestamp is greater */
        rtcSetTime(&RTCD1, (RTCDateTime*)(&OD_PERSIST_STATE.x6004_persistentState.timestamp));
    }

    /* Apply state */
    if (OD_PERSIST_STATE.x6004_persistentState.alarmA != 0) {
        rtcSetAlarm(&RTCD1, ALARM_A, (RTCAlarm*)(&OD_PERSIST_STATE.x6004_persistentState.alarmA));
    }
    if (OD_PERSIST_STATE.x6004_persistentState.alarmB != 0) {
        rtcSetAlarm(&RTCD1, ALARM_B, (RTCAlarm*)(&OD_PERSIST_STATE.x6004_persistentState.alarmB));
    }
    if (OD_PERSIST_STATE.x6004_persistentState.wakeup != 0) {
        rtcSTM32SetPeriodicWakeup(&RTCD1, (RTCWakeup*)(&OD_PERSIST_STATE.x6004_persistentState.wakeup));
    }
}

bool delay_deploy(void)
{
    return (difftime(rtcGetTimeUnix(NULL), CHIBIOS_EPOCH) < OD_PERSIST_APP.x6002_deploymentControl.timeout);
}

/* TODO: Re-enable battery monitoring using new OD interface */
/*
CO_SDO_abortCode_t OD_BATT_CALLBACK(CO_ODF_arg_t *ODF_arg)
{
    if (!ODF_arg->reading) {
        chEvtSignal(c3_tp, C3_EVENT_BAT);
    }

    return CO_SDO_AB_NONE;
}
*/

bool bat_good(void)
{
    static bool good = true;

    if (good && BAT_LOW) {
        good = false;
    } else if (!good && !BAT_LOW) {
        good = true;
    }

    return good;
}

bool tx_enabled(void)
{
    return (difftime(rtcGetTimeUnix(NULL), OD_PERSIST_STATE.x6004_persistentState.lastTX_Enable) < OD_PERSIST_APP.x6003_TX_Control.timeout);
}

bool edl_enabled(void)
{
    return (difftime(rtcGetTimeUnix(NULL), OD_PERSIST_STATE.x6004_persistentState.lastEDL) < OD_PERSIST_APP.x6001_stateControl.EDL_Timeout);
}

bool trigger_reset(void)
{
    return (difftime(rtcGetTimeUnix(NULL), boot_time) >= OD_PERSIST_APP.x6001_stateControl.resetTimeout);
}

void set_alarm(rtcalarm_t alrm, time_t start, int days, int hours, int minutes, int seconds)
{
    RTCDateTime ref_time;
    RTCAlarm alarm;

    /* Encode alarm value */
    rtcConvertUnixToDateTime(&ref_time, start, 0);
    alarm.alrmr = rtcEncodeRelAlarm(&ref_time, days, hours, minutes, seconds);

    /* Set alarm */
    rtcSetAlarm(&RTCD1, alrm, &alarm);
}

/* Main Command, Communications, and Control Thread */
THD_WORKING_AREA(c3_wa, 0x400);
THD_FUNCTION(c3, arg)
{
    (void)arg;

    c3_tp = chThdGetSelfX();
    rtcSetCallback(&RTCD1, alarmcb);
    /*CO_OD_configure(CO->SDO[0], OD_7001_battery, OD_BATT_CALLBACK, NULL, NULL, 0);*/

    /* Restore saved state */
    c3StateRestore();

    /* Log boot time */
    boot_time = rtcGetTimeUnix(NULL);

    /* Increment power cycles */
    OD_PERSIST_STATE.x6004_persistentState.powerCycles++;

    /* State loop */
    while (!chThdShouldTerminateX()) {
        RTCWakeup wakeup;
        switch (OD_RAM.x6000_C3_State[0]) {
        case PREDEPLOY:
            /* Check if pre-deployment timeout has occured */
            if (delay_deploy()) {
                /* Must wait for pre-deployment timeout */
                set_alarm(PREDEPLOY_ALARM, CHIBIOS_EPOCH, 0, 0, 0, OD_PERSIST_APP.x6002_deploymentControl.timeout);
                /* Initially enable TX */
                tx_enable(true);
                chEvtWaitAny(C3_EVENT_WAKEUP | C3_EVENT_TERMINATE);
            } else {
                /* Enter deploy state */
                OD_RAM.x6000_C3_State[0] = DEPLOY;
            }
            break;
        case DEPLOY:
            /* Set RTC wakeup alarm for state saving */
            wakeup.wutr = (RTC_CR_WUCKSEL_2 << 16) | (OD_PERSIST_APP.x6001_stateControl.saveInterval - 1);
            rtcSTM32SetPeriodicWakeup(&RTCD1, &wakeup);

            /* Initiate antenna deployment if needed */
            static uint8_t attempts = 0;
            if (!OD_PERSIST_STATE.x6004_persistentState.deployed && attempts < OD_PERSIST_APP.x6002_deploymentControl.attempts) {
                if (bat_good()) {
                    deploy_heli(OD_PERSIST_APP.x6002_deploymentControl.actuationTime);
                    deploy_turn(OD_PERSIST_APP.x6002_deploymentControl.actuationTime);
                    attempts++;
                } else {
                    chEvtWaitAny(C3_EVENT_WAKEUP | C3_EVENT_TERMINATE | C3_EVENT_BAT);
                }
            } else {
                /* Enter standy state */
                OD_RAM.x6000_C3_State[0] = STANDBY;
                OD_PERSIST_STATE.x6004_persistentState.deployed = 1;
                attempts = 0;
            }
            break;
        case STANDBY:
            beacon_enable(false);

            if (edl_enabled()) {
                OD_RAM.x6000_C3_State[0] = EDL;
            } else if (trigger_reset()) {
                hard_reset();
            } else if (tx_enabled() && bat_good()) {
                OD_RAM.x6000_C3_State[0] = BEACON;
            } else {
                chEvtWaitAny(C3_EVENT_WAKEUP | C3_EVENT_TERMINATE | C3_EVENT_TX | C3_EVENT_BAT | C3_EVENT_EDL);
            }
            break;
        case BEACON:
            beacon_enable(true);

            if (edl_enabled()) {
                OD_RAM.x6000_C3_State[0] = EDL;
            } else if (trigger_reset()) {
                hard_reset();
            } else if (!tx_enabled() || !bat_good()) {
                OD_RAM.x6000_C3_State[0] = STANDBY;
            } else {
                chEvtWaitAny(C3_EVENT_WAKEUP | C3_EVENT_TERMINATE | C3_EVENT_TX | C3_EVENT_BAT | C3_EVENT_EDL);
            }
            break;
        case EDL:
            beacon_enable(false);

            if (!edl_enabled()) {
                set_alarm(RESET_ALARM, rtcGetTimeUnix(NULL), 0, 0, 0, OD_PERSIST_APP.x6001_stateControl.resetTimeout);
                if (tx_enabled() && bat_good()) {
                    OD_RAM.x6000_C3_State[0] = BEACON;
                } else {
                    OD_RAM.x6000_C3_State[0] = STANDBY;
                }
            } else {
                chEvtWaitAny(C3_EVENT_WAKEUP | C3_EVENT_TERMINATE | C3_EVENT_EDL);
            }
            break;
        default:
            OD_RAM.x6000_C3_State[0] = PREDEPLOY;
            break;
        };

        c3StateSave();
    }

    rtcSetCallback(&RTCD1, NULL);
    rtcSTM32SetPeriodicWakeup(&RTCD1, NULL);
    rtcSetAlarm(&RTCD1, 0, NULL);
    rtcSetAlarm(&RTCD1, 1, NULL);
    chThdExit(MSG_OK);
}

void tx_enable(bool state)
{
    if (state) {
        OD_PERSIST_STATE.x6004_persistentState.lastTX_Enable = rtcGetTimeUnix(NULL);
        set_alarm(TX_ENABLE_ALARM, OD_PERSIST_STATE.x6004_persistentState.lastTX_Enable, 0, 0, 0, OD_PERSIST_APP.x6003_TX_Control.timeout);
    } else {
        OD_PERSIST_STATE.x6004_persistentState.lastTX_Enable = 0;
        rtcSetAlarm(&RTCD1, TX_ENABLE_ALARM, NULL);
    }
    chEvtSignal(c3_tp, C3_EVENT_TX);
}

void edl_enable(bool state)
{
    /* Do not enable EDL if in predeploy state */
    if (OD_RAM.x6000_C3_State[0] == PREDEPLOY)
        return;

    if (state) {
        OD_PERSIST_STATE.x6004_persistentState.lastEDL = rtcGetTimeUnix(NULL);
        set_alarm(EDL_ALARM, OD_PERSIST_STATE.x6004_persistentState.lastEDL, 0, 0, 0, OD_PERSIST_APP.x6001_stateControl.EDL_Timeout);
    } else {
        OD_PERSIST_STATE.x6004_persistentState.lastEDL = 0;
        rtcSetAlarm(&RTCD1, TX_ENABLE_ALARM, NULL);
    }
    chEvtSignal(c3_tp, C3_EVENT_EDL);
}

void soft_reset(void)
{
    c3StateSave();
    NVIC_SystemReset();
}

void hard_reset(void)
{
    c3StateSave();
    stop_workers(true);
    chThdSleepSeconds(60);
    NVIC_SystemReset();
}

void factory_reset(void)
{
    chThdTerminate(c3_tp);
    chEvtSignal(c3_tp, C3_EVENT_TERMINATE);
    chThdWait(c3_tp);
    framErase(&FRAMD1, FRAM_STATE_ADDR, FRAM_SIZE - FRAM_STATE_ADDR);
    RCC->BDCR |= RCC_BDCR_BDRST;
    RCC->BDCR &= ~RCC_BDCR_BDRST;
    NVIC_SystemReset();
}
