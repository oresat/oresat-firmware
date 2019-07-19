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

//Function prototypes
uint8_t can_hw_init(void);

#endif
