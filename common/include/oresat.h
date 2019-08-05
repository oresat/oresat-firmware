#ifndef _ORESAT_H_
#define _ORESAT_H_

#include "ch.h"

#ifndef ORESAT_MAX_THREADS
#define ORESAT_MAX_THREADS 5
#endif

#define ORESAT_DEFAULT_ID 0

int reg_worker(void *wa, size_t wa_size, tprio_t prio, tfunc_t thread_func, void *arg);

void oresat_init(uint8_t node_id);
void oresat_start(void);

#endif
