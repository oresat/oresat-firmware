#include "node.h"
#include "opd.h"

void node_boot_cb(uint8_t node_id, uint8_t idx, node_t *node)
{

}

void node_online_cb(uint8_t node_id, uint8_t idx, node_t *node)
{

}

void node_offline_cb(uint8_t node_id, uint8_t idx, node_t *node)
{

}

void init_nodes(CO_HBconsumer_t *hb_cons, const oresat_node_t *node_list)
{
    /* TODO: Sanity/error checking */

    for (uint32_t i = 0; i < list_size; i++) {
        CO_HBconsumer_initEntry(hb_cons, i, node_list[i]->node_id, node_list[i]->timeout);
    }
}

void node_start(uint8_t node_id)
{
    uint8_t index;

    /* TODO: Sanity/error checking */

    index = CO_HBconsumer_getIdxByNodeId(hb_cons, node_id);

    CO_HBconsumer_initCallbackRemoteReset(hb_cons, index, node, node_boot_cb);
    CO_HBconsumer_initCallbackHeartbeatStarted(hb_cons, index, node, node_online_cb);
    CO_HBconsumer_initCallbackTimeout(hb_cons, index, node, node_offline_cb);

    if (node->opd_addr) {
        opd_probe(node->opd_addr);
        opd_enable(node->opd_addr);
    }
}

void node_stop(uint8_t node_id)
{
    uint8_t index;

    /* TODO: Sanity/error checking */

    index = CO_HBconsumer_getIdxByNodeId(hb_cons, node_id);

    CO_HBconsumer_initCallbackRemoteReset(hb_cons, index, NULL, NULL);
    CO_HBconsumer_initCallbackHeartbeatStarted(hb_cons, index, NULL, NULL);
    CO_HBconsumer_initCallbackTimeout(hb_cons, index, NULL, NULL);
    if (node->opd_addr) {
        opd_disable(node->opd_addr);
    }
    node->state = NODE_OFFLINE;
}
