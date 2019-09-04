#ifndef _ORESAT_H_
#define _ORESAT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ch.h"
#include "hal.h"
#include "worker.h"

#define ORESAT_DEFAULT_ID 0
#define ORESAT_DEFAULT_BITRATE 1000

extern event_source_t cos_event;

/* OreSat initialization and main process */
void oresat_init(uint8_t node_id, uint16_t bitrate);
void oresat_start(CANDriver *cand);

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif
