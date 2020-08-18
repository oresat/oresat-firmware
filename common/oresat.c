#include "oresat.h"
#include "events.h"
#include "sensors.h"
#include "CANopen.h"

typedef enum {
    ORESAT_NMT_NONOPERATIONAL,
    ORESAT_NMT_OPERATIONAL,
} oresat_eventid_t;

evreg_t event_registry;
thread_t *oresat_tp;

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

/* General purpose CANopen callback to wake up data processing threads */
void process_cb(void *thread)
{
    /* Signal processing thread from critical section */
    chEvtSignalI((thread_t *)thread, (eventmask_t)1);
}

/* CANopen SDO server thread */
THD_FUNCTION(sdo_server, SDO)
{
    systime_t prev_time;

    /* Register the callback function to wake up thread when message received */
    CO_SDO_initCallbackPre((CO_SDO_t *)SDO, chThdGetSelfX(), process_cb);

    prev_time = chVTGetSystemTime();
    while (!chThdShouldTerminateX()) {
        uint32_t timeout = ((typeof(timeout))-1);

        CO_SDO_process((CO_SDO_t *)SDO, (CO->NMT->operatingState == CO_NMT_PRE_OPERATIONAL || CO->NMT->operatingState == CO_NMT_OPERATIONAL),
                TIME_I2US(chVTTimeElapsedSinceX(prev_time)), &timeout);

        prev_time = chVTGetSystemTime();
        chEvtWaitAnyTimeout(ALL_EVENTS, TIME_US2I(timeout));
    }
    CO_SDO_initCallbackPre((CO_SDO_t *)SDO, NULL, NULL);
    chThdExit(MSG_OK);
}

/* CANopen Emergency thread */
THD_FUNCTION(em_worker, emPr)
{
    systime_t prev_time;

    /* Register the callback function to wake up thread when message received */
    CO_EM_initCallbackPre(((CO_EMpr_t *)emPr)->em, chThdGetSelfX(), process_cb);

    prev_time = chVTGetSystemTime();
    while (!chThdShouldTerminateX()) {
        uint32_t timeout = ((typeof(timeout))-1);

        CO_EM_process((CO_EMpr_t *)emPr, (CO->NMT->operatingState == CO_NMT_PRE_OPERATIONAL || CO->NMT->operatingState == CO_NMT_OPERATIONAL),
                TIME_I2US(chVTTimeElapsedSinceX(prev_time)), OD_inhibitTimeEMCY, &timeout);

        prev_time = chVTGetSystemTime();
        chEvtWaitAnyTimeout(ALL_EVENTS, TIME_US2I(timeout));
    }
    CO_EM_initCallbackPre(((CO_EMpr_t *)emPr)->em, NULL, NULL);
    chThdExit(MSG_OK);
}

/* CANopen PDO/SYNC worker thread */
THD_FUNCTION(pdo_sync_worker, co)
{
    systime_t prev_time;

    /* Register the callback function to wake up thread when message received */
    CO_SYNC_initCallbackPre(((CO_t *)co)->SYNC, chThdGetSelfX(), process_cb);
    for (int i = 0; i < CO_NO_RPDO; i++) {
        CO_RPDO_initCallbackPre(((CO_t *)co)->RPDO[i], chThdGetSelfX(), process_cb);
    }

    prev_time = chVTGetSystemTime();
    while (!chThdShouldTerminateX()) {
        bool_t syncWas;
        uint32_t timeout = ((typeof(timeout))-1);

        /* Trigger sensors */
        sensors_trig();
        /* Process SYNC */
        syncWas = CO_process_SYNC((CO_t *)co,
                TIME_I2US(chVTTimeElapsedSinceX(prev_time)), &timeout);
        /* Read inputs */
        CO_process_RPDO((CO_t *)co, syncWas);
        /* Write outputs */
        CO_process_TPDO((CO_t *)co, syncWas,
                TIME_I2US(chVTTimeElapsedSinceX(prev_time)), &timeout);

        prev_time = chVTGetSystemTime();
        chEvtWaitAnyTimeout(ALL_EVENTS, TIME_US2I(timeout));
    }
    CO_SYNC_initCallbackPre(((CO_t *)co)->SYNC, NULL, NULL);
    for (int i = 0; i < CO_NO_RPDO; i++) {
        CO_RPDO_initCallbackPre(((CO_t *)co)->RPDO[i], NULL, NULL);
    }
    chThdExit(MSG_OK);
}

/* CANopen Heartbeat Consumer thread */
THD_FUNCTION(hb_cons, HBcons)
{
    systime_t prev_time;

    /* Register the callback function to wake up thread when message received */
    CO_HBconsumer_initCallbackPre((CO_HBconsumer_t *)HBcons, chThdGetSelfX(), process_cb);

    prev_time = chVTGetSystemTime();
    while (!chThdShouldTerminateX()) {
        uint32_t timeout = ((typeof(timeout))-1);

        CO_HBconsumer_process((CO_HBconsumer_t *)HBcons, (CO->NMT->operatingState == CO_NMT_PRE_OPERATIONAL || CO->NMT->operatingState == CO_NMT_OPERATIONAL),
                TIME_I2US(chVTTimeElapsedSinceX(prev_time)), &timeout);

        prev_time = chVTGetSystemTime();
        chEvtWaitAnyTimeout(ALL_EVENTS, TIME_US2I(timeout));
    }
    CO_HBconsumer_initCallbackPre((CO_HBconsumer_t *)HBcons, NULL, NULL);
    chThdExit(MSG_OK);
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

    /* Init sensors */
    sensors_init();

    /* Setup CANopen subsystem */
    CO_ReturnError_t err = CO_new(NULL);
    chDbgAssert(err == CO_ERROR_NO, "CO_new failed");

    return;
}

void oresat_start(oresat_config_t *config)
{
    CO_NMT_reset_cmd_t reset = CO_RESET_NOT;
    CO_ReturnError_t err;
    systime_t prev_time;
    eventmask_t events;
    thread_t *sdo_tp[CO_NO_SDO_SERVER];
    thread_t *em_tp;
    thread_t *pdo_sync_tp;
    thread_t *hbcons_tp;

    /* TODO: Sanity checks */

    /* Set configuration values */
    /* If node ID is not overridden, use default node ID */
    if (config->node_id != ORESAT_DEFAULT_ID && config->node_id <= 0x7F) {
        /* TODO: Implement Node ID system properly */
        OD_CANNodeID = config->node_id;
    }

    /* Set bitrate from provided config */
    OD_CANBitRate = config->bitrate;

    /* Get thread ID for main thread and set priority to max */
    oresat_tp = chThdGetSelfX();
    chThdSetPriority(HIGHPRIO);

    while (reset != CO_RESET_APP) {
        /* Initialize CANopen Subsystem */
        err = CO_CANinit(config, OD_CANBitRate);
        chDbgAssert(err == CO_ERROR_NO, "CO_CANinit failed");
        err = CO_CANopenInit(OD_CANNodeID);
        chDbgAssert(err == CO_ERROR_NO, "CO_CANopenInit failed");

        /* Register events */
        reg_event(&event_registry, ORESAT_NMT_OPERATIONAL, nmt_handler);
        reg_event(&event_registry, ORESAT_NMT_NONOPERATIONAL, nmt_handler);

        /* Register CAN callbacks */
        CO_NMT_initCallbackPre(CO->NMT, oresat_tp, process_cb);
        CO_NMT_initCallbackChanged(CO->NMT, CO_NMT_cb);

        /* Start CANopen threads */
        /* TODO: Optimize stack usage */
        for (int i = 0; i < CO_NO_SDO_SERVER; i++) {
            sdo_tp[i] = chThdCreateFromHeap(NULL, 0x1000, "SDO Server", HIGHPRIO-1, sdo_server, CO->SDO[i]);
        }
        em_tp = chThdCreateFromHeap(NULL, 0x200, "Emergency", HIGHPRIO-2, em_worker, CO->emPr);
        pdo_sync_tp = chThdCreateFromHeap(NULL, 0x200, "PDO SYNC", HIGHPRIO-2, pdo_sync_worker, CO);
        hbcons_tp = chThdCreateFromHeap(NULL, 0x200, "HB Consumer", HIGHPRIO-3, hb_cons, CO->HBcons);

        /* Enter normal operating mode */
        CO_CANsetNormalMode(CO->CANmodule[0]);

        reset = CO_RESET_NOT;
        prev_time = chVTGetSystemTime();
        while (reset == CO_RESET_NOT) {
            uint32_t timeout = ((typeof(timeout))-1);

            /* CANopen process */
            /* TODO: Get error callbacks working and get rid of CANmodule_process */
            CO_CANmodule_process(CO->CANmodule[0]);
            reset = CO_NMT_process(CO->NMT, TIME_I2US(chVTTimeElapsedSinceX(prev_time)),
                    OD_producerHeartbeatTime, OD_NMTStartup, OD_errorRegister,
                    OD_errorBehavior, &timeout);
            if (reset != CO_RESET_NOT)
                continue;

            /* Wait for an event or timeout if no pending actions, whichever comes first */
            prev_time = chVTGetSystemTime();
            events = chEvtWaitAnyTimeout(ALL_EVENTS, TIME_US2I(timeout));
            if (events) event_dispatch(&event_registry, events);
        }

        /* Shutting down */
        /* Terminate CANopen threads */
        for (int i = 0; i < CO_NO_SDO_SERVER; i++) {
            chThdTerminate(sdo_tp[i]);
            chEvtSignal(sdo_tp[i], (eventmask_t)1);
        }
        chThdTerminate(em_tp);
        chEvtSignal(em_tp, (eventmask_t)1);
        chThdTerminate(pdo_sync_tp);
        chEvtSignal(pdo_sync_tp, (eventmask_t)1);
        chThdTerminate(hbcons_tp);
        chEvtSignal(hbcons_tp, (eventmask_t)1);

        /* Wait for CANopen threads to end */
        for (int i = 0; i < CO_NO_SDO_SERVER; i++) {
            chThdWait(sdo_tp[i]);
        }
        chThdWait(em_tp);
        chThdWait(pdo_sync_tp);
        chThdWait(hbcons_tp);

        /* Deregister callbacks */
        CO_NMT_initCallbackPre(CO->NMT, NULL, NULL);
        CO_NMT_initCallbackChanged(CO->NMT, NULL);

        /* Deregister all events */
        clear_evreg(&event_registry);
    }

    /* Deinitialize CO stack */
    CO_delete(config);

    /* Initiate System Reset */
    NVIC_SystemReset();
    return;
}
