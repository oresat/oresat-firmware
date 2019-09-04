#include "oresat.h"
#include "events.h"
#include "CANopen.h"

typedef struct {
    thread_descriptor_t desc;
    thread_t *tp;
} worker_t;

static worker_t workers[ORESAT_MAX_THREADS];
static uint32_t num_workers;

EVENTSOURCE_DECL(cos_event);

void oresat_NMT_event(eventid_t id)
{
    if (id == ORESAT_NMT_OPERATIONAL) {
        /* Start app workers */
        for (uint32_t i = 0; i < num_workers; i++) {
            if (workers[i].tp == NULL) {
                workers[i].tp = chThdCreate(&workers[i].desc);
            }
        }
    } else {
        for (uint32_t i = 0; i < num_workers; i++) {
            if (workers[i].tp) {
                chThdTerminate(workers[i].tp);
                chThdWait(workers[i].tp);
                workers[i].tp = NULL;
            }
        }
    }
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
    event_listener_t el;
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

        chEvtRegisterMask(&CO->CANmodule[0]->rx_event, &el, ALL_EVENTS);
        chEvtRegisterMask(&cos_event, &el, ALL_EVENTS);

        cand->rxfull_cb = CO_CANrx_cb;
        cand->txempty_cb = CO_CANtx_cb;

        CO_CANsetNormalMode(CO->CANmodule[0]);

        reset = CO_RESET_NOT;
        timeout = 0;
        prev_time = chVTGetSystemTime();
        while (reset == CO_RESET_NOT) {
            events = chEvtWaitAnyTimeout(ALL_EVENTS, timeout);
            timecheck = 50;

            /* Process CO objects */
            CO_process_TPDO(CO, CO_process_SYNC_RPDO(CO, chTimeI2US(chVTTimeElapsedSinceX(prev_time))),
                    chTimeI2US(chVTTimeElapsedSinceX(prev_time)));
            reset = CO_process(CO, chTimeI2MS(chVTTimeElapsedSinceX(prev_time)), &timecheck);
            prev_time = chVTGetSystemTime();
            if (timecheck == 50) {
                timeout = maxtimeout;
            } else {
                timeout = TIME_MS2I(timecheck);
            }
        }

        chEvtUnregister(&CO->CANmodule[0]->rx_event, &el);
    }

    CO_delete((uint32_t)cand);

    /* Reset */
    NVIC_SystemReset();
    return;
}
