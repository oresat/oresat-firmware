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

#define CAN_FLT_MODE_POS    0
#define CAN_FLT_MODE_MASK   (1 << CAN_FLT_MODE_POS)
#define CAN_FLT_MASK_MODE   (0 << CAN_FLT_MODE_POS)
#define CAN_FLT_LIST_MODE   (1 << CAN_FLT_MODE_POS)
#define CAN_FLT_SCALE_POS   1
#define CAN_FLT_SCALE_MASK  (1 << CAN_FLT_SCALE_POS)
#define CAN_FLT_16BIT       (0 << CAN_FLT_SCALE_POS)
#define CAN_FLT_32BIT       (1 << CAN_FLT_SCALE_POS)
#define CAN_FLT_FIFO_POS    2
#define CAN_FLT_FIFO_MASK   (1 << CAN_FLT_FIFO_POS)
#define CAN_FLT_FIFO0       (0 << CAN_FLT_FIFO_POS)
#define CAN_FLT_FIFO1       (1 << CAN_FLT_FIFO_POS)

//Function prototypes
int canFilterAdd(uint32_t id, uint32_t mask_id, uint8_t mode);
uint8_t canHWInit(uint16_t node_id);

#endif
