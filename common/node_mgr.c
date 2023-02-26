#include "node_mgr.h"
#include "opd.h"

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

/* TODO: Don't use extern, switch to some system config/object struct */
extern CO_t *CO;

node_state_t node_state[OD_CNT_ARR_1016];
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
        OD_IO_t hbcons_io;
        uint32_t hbcons_entry = node[i].id << 16 | node[i].timeout;
        OD_size_t count;
        OD_getSub(OD_ENTRY_H1016_consumerHeartbeatTime, i + 1, &hbcons_io, false);
        hbcons_io.write(&hbcons_io.stream, &hbcons_entry, sizeof(hbcons_entry), &count);
        node_state[i].desc = &node[i];
        node_state[i].attempts = 0;
        if (node[i].opd_addr == 0x00 || node[i].autostart)
            node_enable(node[i].id, true);
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
                        node_enable(node->desc->id, false);
                        chThdSleepMilliseconds(500);
                        node_enable(node->desc->id, true);
                        node->attempts++;
                    } else {
                        node_enable(node->desc->id, false);
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
        node_enable(node[i].id, false);
        OD_IO_t hbcons_io;
        uint32_t hbcons_entry = 0;
        OD_size_t count;
        OD_getSub(OD_ENTRY_H1016_consumerHeartbeatTime, i + 1, &hbcons_io, false);
        hbcons_io.write(&hbcons_io.stream, &hbcons_entry, sizeof(hbcons_entry), &count);
    }
    opd_stop();
}

int node_enable(uint8_t id, bool enable)
{
    int8_t idx = CO_HBconsumer_getIdxByNodeId(CO->HBcons, id);
    if (idx < 0)
        return -1;
    node_state_t *node = &node_state[idx];
    node->enable = enable;
    if (enable) {
        CO_HBconsumer_initCallbackNmtChanged(CO->HBcons, idx, node, node_change_cb);
    } else {
        CO_HBconsumer_initCallbackNmtChanged(CO->HBcons, idx, NULL, NULL);
    }
    if (node->desc->opd_addr) {
        return opd_enable(node->desc->opd_addr, enable);
    }
    return 0;
}

int node_status(uint8_t id, CO_NMT_internalState_t *state)
{
    int8_t idx = CO_HBconsumer_getIdxByNodeId(CO->HBcons, id);
    if (idx < 0)
        return -1;
    node_state_t *node = &node_state[idx];
    if (state)
        *state = node->state;
    return node->enable;
}
