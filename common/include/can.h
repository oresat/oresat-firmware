/*
 * CAN Subsystem Header
 */
#ifndef _CAN_H_
#define _CAN_H_

//ChibiOS headers
#include "ch.h"
#include "hal.h"

//Project headers
#include "can_hw.h"
#include "can_threads.h"

//Definitions
#define CAN_ID_TPDO(n)  ((n << 8) | 0x80)
#define CAN_ID_RPDO(n)  ((n + 1) << 8)

#undef HAL_USE_CAN
#undef STM32_CAN_USE_CAN1
#undef STM32_CAN_CAN1_IRQ_PRIORITY

#define HAL_USE_CAN                 TRUE
#define STM32_CAN_USE_CAN1          TRUE
#define STM32_CAN_CAN1_IRQ_PRIORITY 3

//typedef enum {
    //CAN_ID_NMT_SERVICE       = 0x000,   //Network management
    //CAN_ID_SYNC              = 0x080,   //Synchronous message
    //CAN_ID_EMERGENCY         = 0x080,   //Emergency messages (+nodeID)
    //CAN_ID_TIME_STAMP        = 0x100,   //Time stamp message
    //CAN_ID_TPDO_1            = 0x180,   //TPDO1 (+nodeID)
    //CAN_ID_RPDO_1            = 0x200,   //RPDO1 (+nodeID)
    //CAN_ID_TPDO_2            = 0x280,   //TPDO2 (+nodeID)
    //CAN_ID_RPDO_2            = 0x300,   //RPDO2 (+nodeID)
    //CAN_ID_TPDO_3            = 0x380,   //TPDO3 (+nodeID)
    //CAN_ID_RPDO_3            = 0x400,   //RPDO3 (+nodeID)
    //CAN_ID_TPDO_4            = 0x480,   //TPDO4 (+nodeID)
    //CAN_ID_RPDO_4            = 0x500,   //RPDO5 (+nodeID)
    //CAN_ID_TSDO              = 0x580,   //SDO response (+nodeID)
    //CAN_ID_RSDO              = 0x600,   //SDO request (+nodeID)
    //CAN_ID_HEARTBEAT         = 0x700    //Heartbeat message
//} CAN_ID_t;

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
    uint32_t    event_time;
    uint32_t    event_timestamp;
    uint32_t    inhibit_time;
    uint32_t    inhibit_timestamp;
    uint8_t     inhibit_status;
    uint8_t     *pdata;
    CANTxFrame  msg;
} tpdo_cfg;

typedef struct {
    uint32_t    can_id;
    uint8_t     len;
    uint8_t     *pdata;
} rpdo_cfg;

extern node_cfg node;
extern tpdo_cfg tpdo[];
extern rpdo_cfg rpdo[];

/*
 * Function prototypes
 */

//CAN subsystem initialization and invocation functions
void can_init(uint8_t node_id, uint32_t heartbeat);
void can_start(void);

//TPDO/RPDO initializations
void can_initTPDO(uint8_t pdo_num, uint32_t can_id, uint32_t event_tim, uint32_t inhibit_tim, uint8_t len, uint8_t *pdata);
void can_initRPDO(uint8_t pdo_num, uint32_t can_id, uint8_t len, uint8_t *pdata);

//CAN Process
uint8_t can_processStack(void);

//Reset functions
void can_reset_app(void);
void can_reset_comms(void);

#endif
