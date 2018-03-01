/*
 * CAN Subsystem header file
 */
#ifndef _CAN_H_
#define _CAN_H_

//ChibiOS headers
#include "ch.h"
#include "hal.h"

//Project headers

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




/*
 * CAN Register configuration
 * See section 22.7.7 on the STM32 reference manual.
 * Timing calculator:
 * http://www.bittiming.can-wiki.info/
 */
static const CANConfig cancfg = {
    // MCR (Master Control Register)
    CAN_MCR_ABOM      |     //Automatic Bus-Off Management
    CAN_MCR_AWUM      |     //Automatic Wakeup Mode
    CAN_MCR_TXFP      ,     //Transmit FIFO Priority
    // BTR (Bit Timing Register)
    // Note: Convert to zero based values here when using the calculator
    // CAN_BTR_LBKM     |     //Loopback Mode (Debug)
    CAN_BTR_SJW(0)    |     //Synchronization Jump Width
    CAN_BTR_TS1(12)   |     //Time Segment 1
    CAN_BTR_TS2(1)    |     //Time Segment 2
    CAN_BTR_BRP(5)          //Bit Rate Prescaler
};

//CAN subsystem initialization and invocation functions
void can_init(void);
void can_start(void);

#endif
