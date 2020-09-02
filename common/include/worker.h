#ifndef _WORKER_H_
#define _WORKER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ch.h"
#include "hal.h"

typedef struct worker {
    thread_descriptor_t desc;
    bool critical;
    thread_t *tp;
    struct worker *next;
    struct worker *prev;
} worker_t;

/* OreSat worker thread API */
void init_worker(worker_t *worker, const char *name, void *wa, size_t wa_size, tprio_t prio, tfunc_t funcp, void *arg, bool critical);
void reg_worker(worker_t *worker);
void unreg_worker(worker_t *worker);
void start_crit_workers(void);
void start_workers(void);
void stop_workers(bool stop_crit);

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif /*_WORKER_H_*/
