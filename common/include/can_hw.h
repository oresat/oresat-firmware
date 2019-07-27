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

typedef union {
    struct {
        uint32_t            :1 ;
        uint32_t RTR        :1 ;
        uint32_t IDE        :1 ;
        uint32_t EXID       :18;
        uint32_t STID       :11;
    } scale_32;
    struct {
        struct {
            uint16_t EXIT   :3 ;
            uint16_t IDE    :1 ;
            uint16_t RTR    :1 ;
            uint16_t STID   :11;
        } id;
        struct {
            uint16_t EXIT   :3 ;
            uint16_t IDE    :1 ;
            uint16_t RTR    :1 ;
            uint16_t STID   :11;
        } mask_id;
    } scale_16;
    uint32_t raw;
} flt_reg_t;


//Function prototypes
void canFilterObjectCreate(CANFilter *cfp, uint16_t filter_num, flt_reg_t reg1, flt_reg_t reg2, uint8_t flags);
uint8_t canHWInit(void);

#endif
