#include "oresat.h"
#include "events.h"
#include "sensors.h"
#include "CANopen.h"

typedef enum {
    ORESAT_RX_EVENT = 0,
    ORESAT_COS_EVENT,
    ORESAT_NMT_NONOPERATIONAL,
    ORESAT_NMT_OPERATIONAL,
} oresat_eventid_t;

EVENTSOURCE_DECL(cos_event);
static thread_t *oresat_tp;
evreg_t event_registry;

void CO_NMT_cb(CO_NMT_internalState_t state)
{
    syssts_t sts;
    sts = chSysGetStatusAndLockX();
    if (state == CO_NMT_OPERATIONAL) {
        chEvtSignalI(oresat_tp, EVENT_MASK(ORESAT_NMT_OPERATIONAL));
    } else {
        chEvtSignalI(oresat_tp, EVENT_MASK(ORESAT_NMT_NONOPERATIONAL));
    }
    chSysRestoreStatusX(sts);
}

void nmt_handler(eventid_t eventid)
{
    if (eventid == ORESAT_NMT_OPERATIONAL) {
        start_workers();
    } else {
        stop_workers();
    }
}

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
    sensors_init();

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

    oresat_tp = chThdGetSelfX();

    while (reset != CO_RESET_APP) {
        CO_ReturnError_t err;

        /* Initialize CAN Subsystem */
        err = CO_init(cand, OD_CANNodeID, OD_CANBitRate);
        if (err != CO_ERROR_NO) {
            CO_errorReport(CO->em, CO_EM_MEMORY_ALLOCATION_ERROR, CO_EMC_SOFTWARE_INTERNAL, err);
        }

        /* Register events */
        chEvtRegister(&CO->CANmodule[0]->rx_event, &can_el, ORESAT_RX_EVENT);
        chEvtRegister(&cos_event, &cos_el, ORESAT_COS_EVENT);
        reg_event(&event_registry, ORESAT_NMT_OPERATIONAL, nmt_handler);
        reg_event(&event_registry, ORESAT_NMT_NONOPERATIONAL, nmt_handler);

        /* Register CAN interrupt callbacks */
        cand->rxfull_cb = CO_CANrx_cb;
        cand->txempty_cb = CO_CANtx_cb;
        CO_NMT_initCallback(CO->NMT, CO_NMT_cb);

        /* Enter normal operating mode */
        CO_CANsetNormalMode(CO->CANmodule[0]);

        reset = CO_RESET_NOT;
        prev_time = chVTGetSystemTime();
        while (reset == CO_RESET_NOT) {
            uint32_t timeout = ((typeof(timeout))-1);
            uint16_t timeout_ms = ((typeof(timeout_ms))-1);

            /* Process all CO objects */
            sensors_trig();
            reset = CO_process(CO, TIME_I2MS(chVTTimeElapsedSinceX(prev_time)), &timeout_ms);
            if (reset != CO_RESET_NOT)
                continue;
            CO_process_SYNC_PDO(CO, TIME_I2US(chVTTimeElapsedSinceX(prev_time)), &timeout);

            /* Wait for an event or timeout if no pending actions, whichever comes first */
            prev_time = chVTGetSystemTime();
            if ((timeout_ms * 1000) < timeout) timeout = timeout_ms * 1000;
            events = chEvtWaitAnyTimeout(ALL_EVENTS, TIME_US2I(timeout));
            if (events) event_dispatch(&event_registry, events);
        }

        /* Shutting down */
        /* Deregister all events */
        clear_evreg(&event_registry);
        chEvtUnregister(&cos_event, &cos_el);
        chEvtUnregister(&CO->CANmodule[0]->rx_event, &can_el);
    }

    /* Deinitialize CO stack */
    CO_delete(cand);

    /* Initiate System Reset */
    NVIC_SystemReset();
    return;
}
