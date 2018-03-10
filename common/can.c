/*
 * CAN Subsystem Implementation
 */

#include "can.h"

node_cfg node;
tpdo_cfg tpdo[4];
rpdo_cfg rpdo[4];

void can_init(uint8_t node_id, uint32_t heartbeat) {
    // If node_id is greater than maximum node ID (127), set to maximum node ID
    // TODO: Exception
    if (node_id > 0x7F) {
        node_id = 0x7F;
    }

    // Initialize node configuration data
    node.node_id = node_id;
    node.err_code = 0x00;
    //TODO: Implement actual bitrate handling
    node.bitrate = 500U;
    node.heartbeat_time = heartbeat;
    node.heartbeat_timestamp = 0x00;
    node.error_reg = 0x00;

    // Initialize the node heartbeat message
    // CAN ID for heartbeat is 0x700 + Node ID
    node.heartbeat_msg.IDE = CAN_IDE_STD;
    node.heartbeat_msg.SID = CAN_ID_HEARTBEAT + node_id;
    node.heartbeat_msg.RTR = CAN_RTR_DATA;
    node.heartbeat_msg.DLC = 1;
    node.heartbeat_msg.data8[0] = 0x05;

    // Initialize all TPDO and RPDO objects
    for (uint8_t i = 0; i < 4; ++i) {
        can_initTPDO(i, CAN_ID_DEFAULT, 0, 0, 0, NULL);
        can_initRPDO(i, CAN_ID_DEFAULT, 0, NULL);
    }

    // Initialize the hardware
    can_hw_init();

    return;
}

void can_start(void) {
    // Start the CAN subsystem threads
    can_start_threads();

    return;
}

// TPDO Initialization
// pdo_num is a zero-based index of TPDO 1-4
// can_id is the CAN Message ID the TPDO is sent with. Set to zero (0) to use default
void can_initTPDO(CAN_PDO_t pdo_num, CAN_ID_t can_id, uint32_t event_tim, uint32_t inhibit_tim, uint8_t len, uint8_t *pdata) {
    // If the pdo_num is greater than 3 (TPDO 4), set to maximum value 3.
    // TODO: Exception
    if (pdo_num > 3) {
        pdo_num = 3;
    }

    // Initialize TPDO configuration data
    tpdo[pdo_num].event_time = event_tim;
    tpdo[pdo_num].event_timestamp = 0x00;
    tpdo[pdo_num].inhibit_time = inhibit_tim;
    tpdo[pdo_num].inhibit_timestamp = 0x00;
    tpdo[pdo_num].inhibit_status = 0x00;
    tpdo[pdo_num].pdata = pdata;

    // Initialize TPDO TX Frame
    tpdo[pdo_num].msg.IDE = CAN_IDE_STD;
    tpdo[pdo_num].msg.RTR = CAN_RTR_DATA;
    tpdo[pdo_num].msg.DLC = len;

    // If the can_id is zero, set the default value (TPDO# base ID + Node ID)
    if (!can_id) {
        tpdo[pdo_num].msg.SID = (((pdo_num + 1) << 8) | 0x80) + node.node_id;
    } else {
        tpdo[pdo_num].msg.SID = can_id;
    }

    return;
}

// RPDO Initialization
// pdo_num is a zero-based index of RRDO 1-4
// can_id is the CAN Message ID the RPDO is watching for. Set to zero (0) to use default
void can_initRPDO(CAN_PDO_t pdo_num, CAN_ID_t can_id, uint8_t len, uint8_t *pdata) {
    // If the pdo_num is greater than 3 (RPDO 4), set to maximum value 3.
    // TODO: Exception
    if (pdo_num > 3) {
        pdo_num = 3;
    }

    // Initialize RPDO configuration data
    rpdo[pdo_num].len = len;
    rpdo[pdo_num].pdata = pdata;

    // If the can_id is zero, set the default value (RPDO# base ID + Node ID)
    if (!can_id) {
        rpdo[pdo_num].can_id = ((pdo_num + 2) << 8) + node.node_id;
    } else {
        rpdo[pdo_num].can_id = can_id;
    }

    return;
}

uint8_t can_processStack(void) {
    uint8_t status = 0;

    return status;
}

void can_reset_app(void) {

    return;
}
void can_reset_comms(void) {

    return;
}
