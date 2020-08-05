#include "oresat.h"
#include "events.h"
#include "sensors.h"
#include "time_sync.h"
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

void oresat_init(void)
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

    return;
}

void oresat_start(oresat_config_t *config)
{
    CO_ReturnError_t err;
    event_listener_t can_el, cos_el;
    eventmask_t events;
    CO_NMT_reset_cmd_t reset = CO_RESET_NOT;
    systime_t prev_time;

    /* TODO: Sanity check */

    /* Set configuration values */
    /* If node ID is not overridden, use default node ID */
    if (config->node_id != ORESAT_DEFAULT_ID && config->node_id <= 0x7F) {
        /* TODO: Implement Node ID system properly */
        OD_CANNodeID = config->node_id;
    }

    OD_CANBitRate = config->bitrate;

    oresat_tp = chThdGetSelfX();

    err = CO_new(NULL);
    chDbgAssert(err == CO_ERROR_NO, "CO_new failed");

    while (reset != CO_RESET_APP) {

        /* Initialize CANopen Subsystem */
        err = CO_CANinit(config, OD_CANBitRate);
        chDbgAssert(err == CO_ERROR_NO, "CO_CANinit failed");
        err = CO_CANopenInit(OD_CANNodeID);
        chDbgAssert(err == CO_ERROR_NO, "CO_CANopenInit failed");

        /* Register events */
        chEvtRegister(&CO->CANmodule[0]->rx_event, &can_el, ORESAT_RX_EVENT);
        chEvtRegister(&cos_event, &cos_el, ORESAT_COS_EVENT);
        reg_event(&event_registry, ORESAT_NMT_OPERATIONAL, nmt_handler);
        reg_event(&event_registry, ORESAT_NMT_NONOPERATIONAL, nmt_handler);

        /* Register CAN callbacks */
        CO_NMT_initCallbackChanged(CO->NMT, CO_NMT_cb);

        CO_OD_configure(CO->SDO[0], OD_2010_SCET, OD_SCET_Func, NULL, 0, 0);

        /* Enter normal operating mode */
        CO_CANsetNormalMode(CO->CANmodule[0]);

        reset = CO_RESET_NOT;
        prev_time = chVTGetSystemTime();
        while (reset == CO_RESET_NOT) {
            bool_t syncWas;
            uint32_t timeout = ((typeof(timeout))-1);

            /* Process all CO objects */
            /* Trigger sensors */
            sensors_trig();
            /* CANopen process */
            reset = CO_process(CO, TIME_I2US(chVTTimeElapsedSinceX(prev_time)), &timeout);
            if (reset != CO_RESET_NOT)
                continue;
            /* Process SYNC */
            syncWas = CO_process_SYNC(CO, TIME_I2US(chVTTimeElapsedSinceX(prev_time)), &timeout);
            /* Read inputs */
            CO_process_RPDO(CO, syncWas);
            /* Write outputs */
            CO_process_TPDO(CO, syncWas, TIME_I2US(chVTTimeElapsedSinceX(prev_time)), &timeout);

            /* Wait for an event or timeout if no pending actions, whichever comes first */
            prev_time = chVTGetSystemTime();
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
    CO_delete(config);

    /* Initiate System Reset */
    NVIC_SystemReset();
    return;
}
