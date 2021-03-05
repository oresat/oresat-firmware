#include "worker.h"
#include "CO_threads.h"

#define WRK_EVT_WAKEUP      EVENT_MASK(0)
#define WRK_EVT_TERMINATE   EVENT_MASK(1)
#define WRK_EVT_NMT         EVENT_MASK(2)

static CO_NMT_internalState_t state;
static worker_t *workers = NULL;

void reg_worker(worker_t *wp, thread_descriptor_t *desc, bool critical, bool autostart)
{
    osalDbgCheck(wp != NULL);

    wp->desc = desc;
    wp->critical = critical;
    wp->autostart = autostart;
    wp->tp = NULL;

    if (workers != NULL) {
        wp->next = workers;
        workers->prev = wp;
    } else {
        wp->next = NULL;
        wp->prev = NULL;
    }
    workers = wp;
}

void unreg_worker(worker_t *wp)
{
    osalDbgCheck(wp != NULL);

    if (wp->next != NULL) {
        wp->next->prev = wp->prev;
    }
    if (wp->prev != NULL) {
        wp->prev->next = wp->next;
    } else {
        workers = wp->next;
    }
}

thread_t *start_worker(worker_t *wp)
{
    osalDbgCheck(wp != NULL);

    /* Verify worker is registered */
    worker_t *wp_check;
    for (wp_check = workers; wp_check != wp && wp_check; wp_check = wp_check->next);
    if (!wp_check) {
        /* If not, return NULL */
        return NULL;
    }

    /* Start if operational or critical */
    if (state == CO_NMT_OPERATIONAL || wp->critical) {
        if (wp->tp == NULL) {
            wp->tp = chThdCreate(wp->desc);
        }
    }
    return wp->tp;
}

msg_t stop_worker(worker_t *wp)
{
    msg_t ret;

    osalDbgCheck(wp != NULL);

    if (wp->tp) {
        chThdTerminate(wp->tp);
        ret = chThdWait(wp->tp);
        wp->tp = NULL;
    }
    return ret;
}

void start_workers(void)
{
    for (worker_t *wp = workers; wp; wp = wp->next) {
        if (wp->autostart) {
            start_worker(wp);
        }
    }
}

void stop_workers(bool stop_crit)
{
    for (worker_t *wp = workers; wp; wp = wp->next) {
        if (!wp->critical || stop_crit) {
            stop_worker(wp);
        }
    }
}

THD_WORKING_AREA(thread_mgr_wa, 0x100);
THD_FUNCTION(thread_mgr, arg)
{
    (void)arg;
    event_listener_t nmt_el;

    /* Register on the NMT state change event */
    chEvtRegisterMaskWithFlags(&nmt_event, &nmt_el, WRK_EVT_NMT, ALL_EVENTS);

    /* Start critical workers */
    start_workers();

    while (!chThdShouldTerminateX()) {
        if (chEvtWaitAny(WRK_EVT_WAKEUP | WRK_EVT_TERMINATE | WRK_EVT_NMT) & WRK_EVT_NMT) {
            /* If NMT state event, handle state change */
            state = chEvtGetAndClearFlags(&nmt_el);
            if (state == CO_NMT_OPERATIONAL) {
                /* Operational state, start all workers */
                start_workers();
            } else {
                /* Non-operational, stop the non-critical workers */
                stop_workers(false);
            }
        }
    }

    /* Shutting down, terminate all workers */
    stop_workers(true);

    chEvtUnregister(&nmt_event, &nmt_el);
    chThdExit(MSG_OK);
}
