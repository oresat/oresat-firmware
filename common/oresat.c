#include "oresat.h"
#include "CANopen.h"

typedef struct {
    thread_descriptor_t desc;
    thread_t *tp;
} worker_t;

static worker_t workers[ORESAT_MAX_THREADS];
static uint32_t num_workers;

static evhandler_t evhandlers[] = {
    NULL
};

EVENTSOURCE_DECL(oresat_event);

/* CAN Worker Threads */
THD_WORKING_AREA(can_rt_wa, 0x40);
THD_FUNCTION(can_rt, p)
{
    systime_t prev_time, cur_time, diff_time;
    CO_t *CO = p;

    // Set thread name
    chRegSetThreadName("can_rt");

    prev_time = chVTGetSystemTimeX();
    // Start Loop
    while (!chThdShouldTerminateX()) {
        if (CO->CANmodule[0]->CANnormal) {
            bool_t syncWas;

            /* Process Sync and read inputs */
            diff_time = chTimeDiffX(prev_time, cur_time = chVTGetSystemTimeX());
            syncWas = CO_process_SYNC_RPDO(CO, chTimeI2US(diff_time));
            /* Further I/O or nonblocking application code may go here. */
            /* Write outputs */
            diff_time = chTimeDiffX(prev_time, cur_time = chVTGetSystemTimeX());
            CO_process_TPDO(CO, syncWas, chTimeI2US(diff_time));
            prev_time = cur_time;
        }

        chThdSleepMicroseconds(1000);
    }

    chThdExit(MSG_OK);
}

THD_WORKING_AREA(can_wrk_wa, 0x40);
THD_FUNCTION(can_wrk, p)
{
    event_listener_t can_el;
    eventmask_t events;
    (void)p;

    // Set thread name
    chRegSetThreadName("can_wrk");
    // Register RX event
    chEvtRegisterMask(&oresat_event, &can_el, 0);

    /* Start app workers */
    for (uint32_t i = 0; i < num_workers; i++) {
        workers[i].tp = chThdCreate(&workers[i].desc);
    }

    while (!chThdShouldTerminateX()) {
        events = chEvtWaitAnyTimeout(ALL_EVENTS, TIME_MS2I(100));
        if (events == 0)
            continue;
        chEvtDispatch(evhandlers, events);
    }

    for (uint32_t i = 0; i < num_workers; i++) {
        chThdTerminate(workers[i].tp);
        chThdWait(workers[i].tp);
    }

    chEvtUnregister(&oresat_event, &can_el);
    chThdExit(MSG_OK);
}

int reg_worker(const char *name, void *wa, size_t wa_size, tprio_t prio, tfunc_t funcp, void *arg)
{
    worker_t *wp;
    if (num_workers == ORESAT_MAX_THREADS) {
        return -1;
    }

    wp = &workers[num_workers];
    wp->desc.name = name;
    wp->desc.wbase = THD_WORKING_AREA_BASE(wa);
    wp->desc.wend = THD_WORKING_AREA_END(wa + wa_size);
    wp->desc.prio = prio;
    wp->desc.funcp = funcp;
    wp->desc.arg = arg;

    return num_workers++;
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
    CO_NMT_reset_cmd_t reset = CO_RESET_NOT;
    thread_t *can_rt_tp, *can_wrk_tp;
    uint16_t sleep_ms;
    systime_t prev_time, cur_time, diff_time;

    while (reset != CO_RESET_APP) {
        CO_ReturnError_t err;

        /* Initialize CAN Subsystem */
        err = CO_init((uint32_t)cand, OD_CANNodeID, OD_CANBitRate);
        if (err != CO_ERROR_NO) {
            CO_errorReport(CO->em, CO_EM_MEMORY_ALLOCATION_ERROR, CO_EMC_SOFTWARE_INTERNAL, err);
        }

        can_rt_tp = chThdCreateStatic(can_rt_wa, sizeof(can_rt_wa), HIGHPRIO, can_rt, CO);
        can_wrk_tp = chThdCreateStatic(can_wrk_wa, sizeof(can_wrk_wa), HIGHPRIO, can_wrk, CO);

        cand->rxfull_cb = CO_CANrx_cb;
        cand->txempty_cb = CO_CANtx_cb;

        CO_CANsetNormalMode(CO->CANmodule[0]);

        reset = CO_RESET_NOT;
        prev_time = chVTGetSystemTimeX();
        while (reset == CO_RESET_NOT) {
            sleep_ms = 50U;
            diff_time = chTimeDiffX(prev_time, cur_time = chVTGetSystemTimeX());
            prev_time = cur_time;
            reset = CO_process(CO, chTimeI2MS(diff_time), &sleep_ms);
            chThdSleepMilliseconds(sleep_ms);
        }

        chThdTerminate(can_rt_tp);
        chThdTerminate(can_wrk_tp);
        chThdWait(can_rt_tp);
        chThdWait(can_wrk_tp);
    }

    CO_delete((uint32_t)cand);

    /* Reset */
    NVIC_SystemReset();
    return;
}
