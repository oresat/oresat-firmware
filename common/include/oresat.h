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

typedef struct {
    CANDriver *cand;
    uint8_t node_id;
    uint16_t bitrate;
} oresat_config_t;

/* OreSat initialization and main process */
void oresat_init(void);
void oresat_start(oresat_config_t *config);

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif
