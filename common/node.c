#include "node.h"
#include "opd.h"

#define NODE_DEFAULT_RETRIES    3

void node_boot_cb(uint8_t node_id, uint8_t idx, node_t *node)
{
    node->state = NODE_ONLINE;
}

void node_online_cb(uint8_t node_id, uint8_t idx, node_t *node)
{
    node->state = NODE_ONLINE;
}

void node_offline_cb(uint8_t node_id, uint8_t idx, node_t *node)
{
    node->state = NODE_OFFLINE;
    if (node->opd_addr) {

    }
}

void init_node(node_t *node, CO_HBconsumer_t *hb_cons, opd_addr_t opd_addr, uint8_t node_id)
{
    /* TODO: Sanity/error checking */

    node->state = NODE_OFFLINE;
    node->opd_addr = opd_addr;
    node->node_id = node_id;
    node->retries = NODE_DEFAULT_RETRIES;
    node->hb_cons = hb_cons;
}

void node_start(node_t *node)
{
    uint8_t index;

    /* TODO: Sanity/error checking */

    /* TODO: This indexing method might need reconsideration */
    index = node->node_id - 1;

    node->state = NODE_INIT;
    CO_HBconsumer_initEntry(node->hb_cons, index, node->node_id, 2000);
    CO_HBconsumer_initCallbackRemoteReset(node->hb_cons, index, node, node_boot_cb);
    CO_HBconsumer_initCallbackHeartbeatStarted(node->hb_cons, index, node, node_online_cb);
    CO_HBconsumer_initCallbackTimeout(node->hb_cons, index, node, node_offline_cb);

    if (node->opd_addr) {
        /*opd_probe(node->opd_addr);*/
        opd_enable(node->opd_addr);
    }
}

void node_stop(node_t *node)
{
    uint8_t index;

    /* TODO: Sanity/error checking */

    /* TODO: This indexing method might need reconsideration */
    index = node->node_id - 1;

    CO_HBconsumer_initCallbackRemoteReset(node->hb_cons, index, NULL, NULL);
    CO_HBconsumer_initCallbackHeartbeatStarted(node->hb_cons, index, NULL, NULL);
    CO_HBconsumer_initCallbackTimeout(node->hb_cons, index, NULL, NULL);
    CO_HBconsumer_initEntry(node->hb_cons, index, 0, 0);
    if (node->opd_addr) {
        opd_disable(node->opd_addr);
    }
    node->state = NODE_OFFLINE;
}
