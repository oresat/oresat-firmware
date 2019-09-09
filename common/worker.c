#include "worker.h"

static worker_t *workers = NULL;

void init_worker(worker_t *worker, const char *name, void *wa, size_t wa_size, tprio_t prio, tfunc_t funcp, void *arg)
{
    worker->tp = NULL;
    worker->next = NULL;
    worker->prev = NULL;
    worker->desc.name = name;
    worker->desc.wbase = THD_WORKING_AREA_BASE(wa);
    worker->desc.wend = THD_WORKING_AREA_END(wa + wa_size);
    worker->desc.prio = prio;
    worker->desc.funcp = funcp;
    worker->desc.arg = arg;
}

void reg_worker(worker_t *worker)
{
    osalDbgCheck(worker != NULL);

    if (workers != NULL) {
        worker->next = workers;
        workers->prev = worker;
    }
    workers = worker;
}

void unreg_worker(worker_t *worker)
{
    osalDbgCheck(worker != NULL);

    if (worker->next != NULL) {
        worker->next->prev = worker->prev;
    }
    if (worker->prev != NULL) {
        worker->prev->next = worker->next;
    } else {
        workers = worker->next;
    }
}

void start_workers(void)
{
    for (worker_t *wp = workers; wp; wp = wp->next) {
        if (wp->tp == NULL) {
            wp->tp = chThdCreate(&wp->desc);
        }
    }
}

void stop_workers(void)
{
    for (worker_t *wp = workers; wp; wp = wp->next) {
        if (wp->tp) {
            chThdTerminate(wp->tp);
            chThdWait(wp->tp);
            wp->tp = NULL;
        }
    }

}
