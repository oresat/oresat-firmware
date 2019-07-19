/*
 * CAN Subsystem Hardware header file
 */
#ifndef _CAN_HW_H_
#define _CAN_HW_H_

//ChibiOS headers
#include "ch.h"
#include "hal.h"

//Project headers
#include "can.h"

//Definitions
#define INIT 0x01
#define CERR 0x02
#define ERPA 0x04
#define RXOR 0x08
#define TXOR 0x10
#define BOFF 0x80

#define CAN_FLT_EID0(n) (n)
#define CAN_FLT_IDE0(n) (n << 3)
#define CAN_FLT_RTR0(n) (n << 4)
#define CAN_FLT_SID0(n) (n << 5)
#define CAN_FLT_EID1(n) (n << 16)
#define CAN_FLT_IDE1(n) (n << 19)
#define CAN_FLT_RTR1(n) (n << 20)
#define CAN_FLT_SID1(n) (n << 21)

//Function prototypes
uint8_t can_hw_init(void);

#endif
