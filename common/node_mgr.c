#include "node_mgr.h"
#include "opd.h"
#include "CANopen.h"

#define MGR_EVENT_WAKEUP            EVENT_MASK(0)
#define MGR_EVENT_TERMINATE         EVENT_MASK(1)
#define MGR_EVENT_CHANGE            EVENT_MASK(2)
#define MGR_EVENT_ONLINE            EVENT_MASK(3)
#define MGR_EVENT_OFFLINE           EVENT_MASK(4)
#define MGR_EVENT_BOOT              EVENT_MASK(5)

typedef struct oresat_node_state {
    const oresat_node_t     *desc;
    CO_NMT_internalState_t  state;
    uint8_t                 attempts;
    bool                    enable;
} node_state_t;

node_state_t node_state[CO_NO_HB_CONS];
EVENTSOURCE_DECL(mgr_change_event);

void node_change_cb(uint8_t nodeId, uint8_t idx, CO_NMT_internalState_t state, void *object)
{
    (void)nodeId;
    node_state_t *node = object;
    syssts_t sts;
    sts = chSysGetStatusAndLockX();
    node->state = state;
    chEvtBroadcastFlagsI(&mgr_change_event, idx);
    chSysRestoreStatusX(sts);
}

THD_WORKING_AREA(node_mgr_wa, 0x400);
THD_FUNCTION(node_mgr, arg)
{
    const oresat_node_t *node = arg;
    event_listener_t mgr_change_el;
    eventmask_t event;
    eventflags_t idx;

    opd_init();
    opd_start();

    for (int i = 0; node[i].id != 0; i++) {
        CO_HBconsumer_initEntry(CO->HBcons, i, node[i].id, node[i].timeout);
        node_state[i].desc = &node[i];
        node_state[i].attempts = 0;
        if (node[i].opd_addr == 0x00)
            node_enable(i, true);
    }

    chEvtRegisterMaskWithFlags(&mgr_change_event, &mgr_change_el, MGR_EVENT_CHANGE, ALL_EVENTS);

    while (!chThdShouldTerminateX()) {
        event = chEvtWaitAnyTimeout(MGR_EVENT_WAKEUP | MGR_EVENT_TERMINATE | MGR_EVENT_CHANGE, TIME_INFINITE);
        if (event & MGR_EVENT_TERMINATE)
            continue;
        if (event & MGR_EVENT_CHANGE) {
            idx = chEvtGetAndClearFlags(&mgr_change_el);
            node_state_t *node =  &node_state[idx];
            switch (node->state) {
            case CO_NMT_UNKNOWN:
                if (node->desc->opd_addr && node->enable) {
                    if (node->attempts < 3) {
                        node_enable(idx, false);
                        chThdSleepMilliseconds(500);
                        node_enable(idx, true);
                        node->attempts++;
                    } else {
                        node_enable(idx, false);
                    }
                }
                break;
            case CO_NMT_INITIALIZING:
                break;
            case CO_NMT_PRE_OPERATIONAL:
            case CO_NMT_OPERATIONAL:
                node->attempts = 0;
                break;
            case CO_NMT_STOPPED:
                break;
            default:
                break;
            }
        }
    }

    chEvtUnregister(&mgr_change_event, &mgr_change_el);
    for (int i = 0; node[i].id != 0; i++) {
        node_enable(i, false);
        CO_HBconsumer_initEntry(CO->HBcons, i, 0, 0);
    }
    opd_stop();
}

bool node_enable(uint8_t id, bool enable)
{
    uint8_t idx = CO_HBconsumer_getIdxByNodeId(CO->HBcons, id);
    node_state_t *node = &node_state[idx];
    node->enable = enable;
    if (enable) {
        CO_HBconsumer_initCallbackNmtChanged(CO->HBcons, idx, node, node_change_cb);
    } else {
        CO_HBconsumer_initCallbackNmtChanged(CO->HBcons, idx, NULL, NULL);
    }
    if (node->desc->opd_addr) {
        return opd_state(node->desc->opd_addr, enable);
    }
    return false;
}
