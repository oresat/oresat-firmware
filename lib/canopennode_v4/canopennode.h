#ifndef CANOPENNODE_H
#define CANOPENNODE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <CANopen.h>

extern CO_t *CO;

int canopennode_init(const struct device *dev, uint16_t bit_rate, uint8_t node_id);
bool canopennode_is_running(void);
void canopennode_stop(const struct device *dev);

#ifdef __cplusplus
}
#endif

#endif
