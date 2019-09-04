#include "oresat.h"
#include "CANopen.h"

EVENTSOURCE_DECL(cos_event);

void oresat_init(uint8_t node_id, uint16_t bitrate)
{
    /*
     * System initializations.
     * - HAL initialization, this also initializes the configured device drivers
     *   and performs the board-specific initializations.
     * - Kernel initialization, the main() function becomes a thread and the
     *   RTOS is active.
     */
    halInit();
    chSysInit();

    /* If node ID is not overridden, use default node ID */
    if (node_id != ORESAT_DEFAULT_ID && node_id <= 0x7F) {
        /* TODO: Implement Node ID system properly */
        OD_CANNodeID = node_id;
    }

    OD_CANBitRate = bitrate;

    return;
}

void oresat_start(CANDriver *cand)
{
    event_listener_t can_el, cos_el;
    eventmask_t events;
    CO_NMT_reset_cmd_t reset = CO_RESET_NOT;
    sysinterval_t timeout, maxtimeout;
    systime_t prev_time;
    uint16_t timecheck;

    while (reset != CO_RESET_APP) {
        CO_ReturnError_t err;

        /* Initialize CAN Subsystem */
        err = CO_init((uint32_t)cand, OD_CANNodeID, OD_CANBitRate);
        if (err != CO_ERROR_NO) {
            CO_errorReport(CO->em, CO_EM_MEMORY_ALLOCATION_ERROR, CO_EMC_SOFTWARE_INTERNAL, err);
        }

        maxtimeout = TIME_MS2I(OD_producerHeartbeatTime);

        chEvtRegisterMask(&CO->CANmodule[0]->rx_event, &can_el, ALL_EVENTS);
        chEvtRegisterMask(&cos_event, &cos_el, ALL_EVENTS);

        cand->rxfull_cb = CO_CANrx_cb;
        cand->txempty_cb = CO_CANtx_cb;

        CO_CANsetNormalMode(CO->CANmodule[0]);

        reset = CO_RESET_NOT;
        timeout = 0;
        prev_time = chVTGetSystemTime();
        while (reset == CO_RESET_NOT) {
            bool_t syncWas;
            timecheck = 50;
            events = chEvtWaitAnyTimeout(ALL_EVENTS, timeout);

            /* Process CO objects */
            syncWas = CO_process_SYNC_RPDO(CO, chTimeI2US(chVTTimeElapsedSinceX(prev_time)));
            CO_process_TPDO(CO, syncWas, chTimeI2US(chVTTimeElapsedSinceX(prev_time)));
            reset = CO_process(CO, chTimeI2MS(chVTTimeElapsedSinceX(prev_time)), &timecheck);
            prev_time = chVTGetSystemTime();
            if (timecheck == 50  && syncWas = false) {
                timeout = maxtimeout;
            } else {
                timeout = 0;
            }
        }

        chEvtUnregister(&cos_event, &cos_el);
        chEvtUnregister(&CO->CANmodule[0]->rx_event, &can_el);
    }

    CO_delete((uint32_t)cand);

    /* Reset */
    NVIC_SystemReset();
    return;
}
