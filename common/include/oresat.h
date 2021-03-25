#ifndef _ORESAT_H_
#define _ORESAT_H_

#include "ch.h"
#include "hal.h"
#include "worker.h"

#define CO_USE_GLOBALS
#define CO_DRIVER_CUSTOM
#define ORESAT_DEFAULT_ID 0
#define ORESAT_DEFAULT_BITRATE 1000

#define ORESAT_SOLAR_NODE_ID         0x04
#define ORESAT_PROTOCARD_NODE_ID     0x30

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    CANDriver *cand;
    uint8_t node_id;
    uint16_t bitrate;
} oresat_config_t;


/* General purpose CANopen callback to wake up data processing threads */
void process_cb(void *thread);

/* OreSat initialization and main process */
void oresat_init(void);
void oresat_start(oresat_config_t *config);

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif
