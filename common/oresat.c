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
    systime_t prev_time;

    while (reset != CO_RESET_APP) {
        CO_ReturnError_t err;

        /* Initialize CAN Subsystem */
        err = CO_init((uint32_t)cand, OD_CANNodeID, OD_CANBitRate);
        if (err != CO_ERROR_NO) {
            CO_errorReport(CO->em, CO_EM_MEMORY_ALLOCATION_ERROR, CO_EMC_SOFTWARE_INTERNAL, err);
        }

        chEvtRegisterMask(&CO->CANmodule[0]->rx_event, &can_el, ALL_EVENTS);
        /*chEvtRegisterMask(&cos_event, &cos_el, ALL_EVENTS);*/

        cand->rxfull_cb = CO_CANrx_cb;
        cand->txempty_cb = CO_CANtx_cb;

        CO_CANsetNormalMode(CO->CANmodule[0]);

        reset = CO_RESET_NOT;
        prev_time = chVTGetSystemTime();
        while (reset == CO_RESET_NOT) {
            uint32_t timeout = ((typeof(timeout))-1);
            uint16_t timeout_ms = ((typeof(timeout_ms))-1);

            /* Process all CO objects */
            reset = CO_process(CO, TIME_I2MS(chVTTimeElapsedSinceX(prev_time)), &timeout_ms);
            if (reset != CO_RESET_NOT)
                continue;
            CO_process_SYNC_PDO(CO, TIME_I2US(chVTTimeElapsedSinceX(prev_time)), &timeout);

            /* Wait for an event or timeout if no pending actions, whichever comes first */
            prev_time = chVTGetSystemTime();
            if ((timeout_ms * 1000) < timeout) timeout = timeout_ms * 1000;
            events = chEvtWaitAnyTimeout(ALL_EVENTS, TIME_US2I(timeout));
        }

        /*chEvtUnregister(&cos_event, &cos_el);*/
        chEvtUnregister(&CO->CANmodule[0]->rx_event, &can_el);
    }

    CO_delete((uint32_t)cand);

    /* Reset */
    NVIC_SystemReset();
    return;
}
