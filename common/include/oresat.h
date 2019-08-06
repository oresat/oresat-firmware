#ifndef _ORESAT_H_
#define _ORESAT_H_

#include "ch.h"
#include "hal.h"

#ifndef ORESAT_MAX_THREADS
#define ORESAT_MAX_THREADS 5
#endif

#define ORESAT_DEFAULT_ID 0
#define ORESAT_DEFAULT_BITRATE 1000

int reg_worker(void *wa, size_t wa_size, tprio_t prio, tfunc_t thread_func, void *arg);

void oresat_init(uint8_t node_id);
void oresat_start(CANDriver *cand, uint16_t bitrate);

#endif
