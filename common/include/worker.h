#ifndef _WORKER_H_
#define _WORKER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ch.h"
#include "hal.h"

typedef struct worker {
    thread_descriptor_t *desc;
    bool critical;
    bool autostart;
    thread_t *tp;
    struct worker *next;
    struct worker *prev;
} worker_t;

extern THD_WORKING_AREA(thread_mgr_wa, 0x100);
extern THD_FUNCTION(thread_mgr, arg);

/* OreSat worker thread API */
void reg_worker(worker_t *wp, thread_descriptor_t *desc, bool critical, bool autostart);
void unreg_worker(worker_t *wp);
thread_t *start_worker(worker_t *wp);
msg_t stop_worker(worker_t *wp);
void start_workers(void);
void stop_workers(bool stop_crit);

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif /*_WORKER_H_*/
