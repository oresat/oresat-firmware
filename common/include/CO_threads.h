#include "ch.h"
#include "CANopen.h"

void CO_init(void *CANptr, uint8_t node_id, uint16_t bitrate);
void CO_run(CO_t *CO);
void CO_kill(void);
