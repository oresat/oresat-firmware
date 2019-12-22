#include "node.h"
#include "opd.h"

void node_boot(uint8_t node_id, uint8_t idx, node_t *node)
{

}

void node_online(uint8_t node_id, uint8_t idx, node_t *node)
{

}

void node_offline(uint8_t node_id, uint8_t idx, node_t *node)
{

}

void init_node(node_t *node, opd_addr_t opd_addr, uint8_t node_id)
{
    node->state = NODE_OFFLINE;
    node->opd_addr = opd_addr;
    node->node_id = node_id;
}

void node_start(node_t *node)
{

}

void node_stop(node_t *node)
{

}
