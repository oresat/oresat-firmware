/*
 * CAN Subsystem Header file
 */
#ifndef _CAN_H_
#define _CAN_H_

//ChibiOS headers
#include "ch.h"
#include "hal.h"

//Project headers
#include "can_hw.h"

//Definitions
typedef enum {
    CAN_ID_NMT_SERVICE       = 0x000,   //Network management
    CAN_ID_SYNC              = 0x080,   //Synchronous message
    CAN_ID_EMERGENCY         = 0x080,   //Emergency messages (+nodeID)
    CAN_ID_TIME_STAMP        = 0x100,   //Time stamp message
    CAN_ID_TPDO_1            = 0x180,   //TPDO1 (+nodeID)
    CAN_ID_RPDO_1            = 0x200,   //RPDO1 (+nodeID)
    CAN_ID_TPDO_2            = 0x280,   //TPDO2 (+nodeID)
    CAN_ID_RPDO_2            = 0x300,   //RPDO2 (+nodeID)
    CAN_ID_TPDO_3            = 0x380,   //TPDO3 (+nodeID)
    CAN_ID_RPDO_3            = 0x400,   //RPDO3 (+nodeID)
    CAN_ID_TPDO_4            = 0x480,   //TPDO4 (+nodeID)
    CAN_ID_RPDO_4            = 0x500,   //RPDO5 (+nodeID)
    CAN_ID_TSDO              = 0x580,   //SDO response (+nodeID)
    CAN_ID_RSDO              = 0x600,   //SDO request (+nodeID)
    CAN_ID_HEARTBEAT         = 0x700    //Heartbeat message
} CAN_ID_t;

typedef struct {
    uint8_t     node_id;
    uint8_t     err_code;
    uint32_t    bitrate;
    uint32_t    heartbeat_time;
    uint32_t    heartbeat_timestamp;
    CANTxFrame  heartbeat_msg;
    uint8_t     error_reg;
} node_cfg;

typedef struct {
#ifdef USE_EVENT_TIME
    uint32_t    event_time;
    uint32_t    event_timestamp;
#endif
#ifdef USE_INHIBIT_TIME
    uint32_t    inhibit_time;
    uint32_t    inhibit_timestamp;
    uint8_t     inhibit_status;
#endif
    uint8_t     offset;
    CANTxFrame  msg;
} tpdo_cfg;

typedef struct {
    uint32_t    canid;
    uint8_t     len;
    uint8_t     offset;
} rpdo_cfg;

//Function prototypes

//CAN subsystem initialization and invocation functions
void can_init(uint8_t node_id);
void can_start(void);

void can_initTPDO(uint8_t pdo_num, uint32_t can_id, uint32_t event_tim, uint32_t inhibit_tim, uint8_t len, uint8_t offset);
void can_initRPDO(uint8_t pdo_num, uint32_t can_id, uint8_t len, uint8_t offset);

uint8_t can_processStack(void);

void can_reset_app(void);
void can_reset_comms(void);

void can_fatal_error(uint32_t err_code);

#endif
