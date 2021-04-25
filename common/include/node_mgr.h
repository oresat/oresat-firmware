#ifndef _NODE_MGR_H_
#define _NODE_MGR_H_

#include "ch.h"
#include "hal.h"

typedef struct oresat_node {
    uint8_t         id;
    i2caddr_t       opd_addr;
    uint16_t        timeout;
    char            *name;
} oresat_node_t;

#ifdef __cplusplus
extern "C" {
#endif

extern THD_WORKING_AREA(node_mgr_wa, 0x400);
extern THD_FUNCTION(node_mgr, arg);
bool node_enable(uint8_t id, bool enable);

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif /*_NODE_MGR_H_*/
