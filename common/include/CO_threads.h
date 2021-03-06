#include "ch.h"
#include "CANopen.h"

extern event_source_t nmt_event;

void CO_init(CANDriver *CANptr, uint8_t node_id, uint16_t bitrate, const flt_reg_t *fifo1_filters, size_t filter_count);
void CO_run(CO_t *CO);
void CO_kill(void);
