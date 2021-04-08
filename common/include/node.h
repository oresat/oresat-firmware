#ifndef _NODE_H_
#define _NODE_H_

#include "ch.h"
#include "hal.h"
#include "opd.h"
#include "CANopen.h"

typedef enum {
    NODE_OFFLINE,
    NODE_INIT,
    NODE_ONLINE,
    NODE_FAILED
} node_state_t;

typedef struct oresat_node {
    uint8_t     node_id;
    opd_addr_t  opd_addr;
    uint16_t    timeout;
    char        *desc;
} oresat_node_t;

#ifdef __cplusplus
extern "C" {
#endif

void init_nodes(CO_HBconsumer_t *hb_cons, const oresat_node_t *node_list);
void node_start(uint8_t node_id);
void node_stop(uint8_t node_id);

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif /*_NODE_H_*/
