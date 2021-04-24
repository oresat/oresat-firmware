#include "CO_threads.h"

#define CO_EVT_WAKEUP       EVENT_MASK(0)
#define CO_EVT_TERMINATE    EVENT_MASK(1)

#define CO_OPERATIONAL (CO->NMT->operatingState == CO_NMT_PRE_OPERATIONAL || \
                        CO->NMT->operatingState == CO_NMT_OPERATIONAL)

static thread_t *nmt_tp;
static thread_t *sdo_tp[CO_NO_SDO_SERVER];
static thread_t *em_tp;
static thread_t *pdo_sync_tp;
static thread_t *hbcons_tp;

event_source_t nmt_event;

/* General purpose CANopen callback to wake up data processing threads */
void process_cb(void *thread)
{
    syssts_t sts;
    sts = chSysGetStatusAndLockX();
    /* Signal processing thread from critical section */
    chEvtSignalI(thread, CO_EVT_WAKEUP);
    chSysRestoreStatusX(sts);
}

void nmt_change_cb(CO_NMT_internalState_t state)
{
    syssts_t sts;
    sts = chSysGetStatusAndLockX();
    chEvtBroadcastFlagsI(&nmt_event, state);
    chSysRestoreStatusX(sts);

}

#if CO_NO_SDO_CLIENT > 0
/* CANopen SDO client thread */
/* TODO: Implement CO_master code here */
THD_FUNCTION(sdo_client_wip, arg)
{
    CO_SDOclient_t *SDOclient = arg;
    systime_t prev_time;
    CO_SDO_return_t ret = CO_SDO_RT_waitingResponse;
    CO_SDO_abortCode_t abort_code = CO_SDO_AB_NONE;
    bool abort = false;

    /* Register the callback function to wake up thread when message received */
    CO_SDOclient_initCallbackPre(SDOclient, chThdGetSelfX(), process_cb);

    prev_time = chVTGetSystemTime();
    while (!chThdShouldTerminateX()) {
        uint32_t timeout = ((typeof(timeout))-1);

        if (SDOclient->state & CO_SDO_ST_FLAG_DOWNLOAD) {
            do {
                ret = CO_SDOclientDownload(SDOclient,
                        TIME_I2US(chVTTimeElapsedSinceX(prev_time)),
                        abort,          /* TODO: Implement logic for this */
                        false,          /* TODO: Implement logic for this */
                        &abort_code,    /* TODO: Implement logic for this */
                        NULL,           /* TODO: Implement logic for this */
                        &timeout);
            } while (ret == CO_SDO_RT_blockDownldInProgress);
        } else if (SDOclient->state & CO_SDO_ST_FLAG_UPLOAD) {
            ret = CO_SDOclientUpload(SDOclient,
                    TIME_I2US(chVTTimeElapsedSinceX(prev_time)),
                    abort,          /* TODO: Implement logic for this */
                    &abort_code,    /* TODO: Implement logic for this */
                    NULL,           /* TODO: Implement logic for this */
                    NULL,           /* TODO: Implement logic for this */
                    &timeout);
        } else {

        }

        prev_time = chVTGetSystemTime();
        chEvtWaitAnyTimeout(CO_EVT_WAKEUP | CO_EVT_TERMINATE, TIME_US2I(timeout));
    }
    CO_SDOclient_initCallbackPre(SDOclient, NULL, NULL);
    chThdExit(MSG_OK);
}
#endif

/* CANopen SDO server thread */
THD_FUNCTION(sdo_server, arg)
{
    CO_SDO_t *SDO = arg;
    systime_t prev_time;

    /* Register the callback function to wake up thread when message received */
    CO_SDO_initCallbackPre(SDO, chThdGetSelfX(), process_cb);

    prev_time = chVTGetSystemTime();
    while (!chThdShouldTerminateX()) {
        uint32_t timeout = ((typeof(timeout))-1);

        CO_SDO_process(SDO, CO_OPERATIONAL, TIME_I2US(chVTTimeElapsedSinceX(prev_time)), &timeout);

        prev_time = chVTGetSystemTime();
        chEvtWaitAnyTimeout(CO_EVT_WAKEUP | CO_EVT_TERMINATE, TIME_US2I(timeout));
    }
    CO_SDO_initCallbackPre(SDO, NULL, NULL);
    chThdExit(MSG_OK);
}

/* CANopen Emergency thread */
THD_FUNCTION(em, arg)
{
    CO_EMpr_t *emPr = arg;
    systime_t prev_time;

    /* Register the callback function to wake up thread when message received */
    CO_EM_initCallbackPre(emPr->em, chThdGetSelfX(), process_cb);

    prev_time = chVTGetSystemTime();
    while (!chThdShouldTerminateX()) {
        uint32_t timeout = ((typeof(timeout))-1);

        CO_EM_process(emPr, CO_OPERATIONAL, TIME_I2US(chVTTimeElapsedSinceX(prev_time)), OD_inhibitTimeEMCY, &timeout);

        prev_time = chVTGetSystemTime();
        chEvtWaitAnyTimeout(CO_EVT_WAKEUP | CO_EVT_TERMINATE, TIME_US2I(timeout));
    }
    CO_EM_initCallbackPre(emPr->em, NULL, NULL);
    chThdExit(MSG_OK);
}

/* CANopen PDO/SYNC thread */
THD_FUNCTION(pdo_sync, arg)
{
    CO_t *co = arg;
    systime_t prev_time;

    /* Register the callback function to wake up thread when message received */
    CO_SYNC_initCallbackPre(co->SYNC, chThdGetSelfX(), process_cb);
    for (int i = 0; i < CO_NO_RPDO; i++) {
        CO_RPDO_initCallbackPre(co->RPDO[i], chThdGetSelfX(), process_cb);
    }

    prev_time = chVTGetSystemTime();
    while (!chThdShouldTerminateX()) {
        uint32_t timeout = ((typeof(timeout))-1);
        bool_t syncWas;

        /* Process SYNC */
        syncWas = CO_process_SYNC(co, TIME_I2US(chVTTimeElapsedSinceX(prev_time)), &timeout);
        /* Read inputs */
        CO_process_RPDO(co, syncWas);
        /* Write outputs */
        CO_process_TPDO(co, syncWas, TIME_I2US(chVTTimeElapsedSinceX(prev_time)), &timeout);

        prev_time = chVTGetSystemTime();
        chEvtWaitAnyTimeout(CO_EVT_WAKEUP | CO_EVT_TERMINATE, TIME_US2I(timeout));
    }
    CO_SYNC_initCallbackPre(co->SYNC, NULL, NULL);
    for (int i = 0; i < CO_NO_RPDO; i++) {
        CO_RPDO_initCallbackPre(co->RPDO[i], NULL, NULL);
    }
    chThdExit(MSG_OK);
}

/* CANopen Heartbeat Consumer thread */
THD_FUNCTION(hb_cons, arg)
{
    CO_HBconsumer_t *HBcons = arg;
    systime_t prev_time;

    /* Register the callback function to wake up thread when message received */
    CO_HBconsumer_initCallbackPre(HBcons, chThdGetSelfX(), process_cb);

    prev_time = chVTGetSystemTime();
    while (!chThdShouldTerminateX()) {
        uint32_t timeout = ((typeof(timeout))-1);

        CO_HBconsumer_process(HBcons, CO_OPERATIONAL, TIME_I2US(chVTTimeElapsedSinceX(prev_time)), &timeout);

        prev_time = chVTGetSystemTime();
        chEvtWaitAnyTimeout(CO_EVT_WAKEUP | CO_EVT_TERMINATE, TIME_US2I(timeout));
    }
    CO_HBconsumer_initCallbackPre(HBcons, NULL, NULL);
    chThdExit(MSG_OK);
}

/* CANopen NMT and Heartbeat thread */
THD_FUNCTION(nmt, arg)
{
    CO_t *CO = arg;
    systime_t prev_time;
    eventmask_t events;
    CO_NMT_reset_cmd_t reset = CO_RESET_NOT;

    /* Register the callback function to wake up thread when message received */
    CO_NMT_initCallbackPre(CO->NMT, chThdGetSelfX(), process_cb);
    /* Register the callback function for NMT state changes */
    CO_NMT_initCallbackChanged(CO->NMT, nmt_change_cb);

    /* Start CANopen threads */
    /* TODO: Optimize stack usage */
    for (int i = 0; i < CO_NO_SDO_SERVER; i++) {
        sdo_tp[i] = chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(0x800), "SDO Server", HIGHPRIO-1, sdo_server, CO->SDO[i]);
    }
    em_tp = chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(0x200), "Emergency", HIGHPRIO-2, em, CO->emPr);
    pdo_sync_tp = chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(0x200), "PDO SYNC", HIGHPRIO-2, pdo_sync, CO);
    hbcons_tp = chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(0x200), "HB Consumer", HIGHPRIO-3, hb_cons, CO->HBcons);

    /* Enter normal operating mode */
    CO_CANsetNormalMode(CO->CANmodule[0]);

    prev_time = chVTGetSystemTime();
    while (reset == CO_RESET_NOT) {
        uint32_t timeout = ((typeof(timeout))-1);

        /* TODO: Get error callbacks working and get rid of CANmodule_process */
        CO_CANmodule_process(CO->CANmodule[0]);
        reset = CO_NMT_process(CO->NMT, TIME_I2US(chVTTimeElapsedSinceX(prev_time)),
                OD_producerHeartbeatTime, OD_NMTStartup, OD_errorRegister,
                OD_errorBehavior, &timeout);
        if (reset != CO_RESET_NOT)
            continue;

        prev_time = chVTGetSystemTime();
        events = chEvtWaitAnyTimeout(CO_EVT_WAKEUP | CO_EVT_TERMINATE, TIME_US2I(timeout));
        if (events & CO_EVT_TERMINATE) {
            reset = CO_RESET_APP;
        }
    }

    /* Shutting down */
    /* Unregister callbacks */
    CO_NMT_initCallbackChanged(CO->NMT, NULL);
    CO_NMT_initCallbackPre(CO->NMT, NULL, NULL);

    /* Terminate CANopen threads */
    for (int i = 0; i < CO_NO_SDO_SERVER; i++) {
        chThdTerminate(sdo_tp[i]);
        chEvtSignal(sdo_tp[i], CO_EVT_TERMINATE);
    }
    chThdTerminate(em_tp);
    chEvtSignal(em_tp, CO_EVT_TERMINATE);
    chThdTerminate(pdo_sync_tp);
    chEvtSignal(pdo_sync_tp, CO_EVT_TERMINATE);
    chThdTerminate(hbcons_tp);
    chEvtSignal(hbcons_tp, CO_EVT_TERMINATE);

    /* Wait for CANopen threads to end */
    for (int i = 0; i < CO_NO_SDO_SERVER; i++) {
        chThdWait(sdo_tp[i]);
    }
    chThdWait(em_tp);
    chThdWait(pdo_sync_tp);
    chThdWait(hbcons_tp);

    /* Terminate and return reset value */
    chThdExit(reset);
}

void CO_init(CANDriver *CANptr, uint8_t node_id, uint16_t bitrate, const flt_reg_t *fifo1_filters, size_t filter_count)
{
    CO_ReturnError_t err;
    err = CO_new(NULL);
    chDbgAssert(err == CO_ERROR_NO, "CO_new failed");
    CO->CANmodule[0]->canFIFO1Filters = fifo1_filters;
    CO->CANmodule[0]->canFIFO1FilterCount = filter_count;
    err = CO_CANinit(CANptr, bitrate);
    chDbgAssert(err == CO_ERROR_NO, "CO_CANinit failed");
    for (int i = 0; i < CO_NO_TPDO; i++) {
        if (OD_TPDOCommunicationParameter[i].COB_IDUsedByTPDO == 0x180U + (0x100U * (i % 4)))
            OD_TPDOCommunicationParameter[i].COB_IDUsedByTPDO += node_id + i / 4;
    }
    for (int i = 0; i < CO_NO_RPDO; i++) {
        if (OD_RPDOCommunicationParameter[i].COB_IDUsedByRPDO == 0x200U + (0x100U * (i % 4)))
            OD_RPDOCommunicationParameter[i].COB_IDUsedByRPDO += node_id + i / 4;
    }
    err = CO_CANopenInit(node_id);
    chDbgAssert(err == CO_ERROR_NO, "CO_CANopenInit failed");
    chEvtObjectInit(&nmt_event);
}

void CO_run(CO_t *CO)
{
    CO_NMT_reset_cmd_t reset = CO_RESET_NOT;

    do {
        nmt_tp = chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(0x200), "NMT", HIGHPRIO, nmt, CO);
        reset = chThdWait(nmt_tp);
    } while (reset != CO_RESET_APP);

}

void CO_kill(void)
{
    chThdTerminate(nmt_tp);
    chEvtSignal(nmt_tp, CO_EVT_TERMINATE);
}

