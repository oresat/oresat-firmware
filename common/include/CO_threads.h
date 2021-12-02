#include "ch.h"
#include "CANopen.h"
#include "OD.h"

#ifndef OD_CNT_SDO_CLI
#define OD_CNT_SDO_CLI 0
#endif
#ifndef OD_CNT_SDO_SRV
#define OD_CNT_SDO_SRV 0
#endif

extern event_source_t nmt_event;

void CO_init(CO_t **pCO, CANDriver *CANptr, uint8_t node_id, uint16_t bitrate, const flt_reg_t *fifo1_filters, size_t filter_count);
void CO_run(CO_t *CO);
void CO_kill(CO_t *CO);
