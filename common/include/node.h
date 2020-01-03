#ifndef _NODE_H_
#define _NODE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ch.h"
#include "hal.h"
#include "opd.h"

typedef enum {
    NODE_OFFLINE,
    NODE_INIT,
    NODE_ONLINE,
    NODE_FAILED
} node_state_t;

typedef struct node {
    CO_HBconsumer_t *hb_cons;
    node_state_t state;
    opd_addr_t opd_addr;
    uint8_t node_id;
    uint8_t retries;
} node_t;

void init_node(node_t *node, opd_addr_t opd_addr, uint8_t node_id);
void node_start(node_t *node);
void node_stop(node_t *node);

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif /*_NODE_H_*/
