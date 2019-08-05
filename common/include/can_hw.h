/*
 * CAN Subsystem Hardware header file
 */
#ifndef _CAN_HW_H_
#define _CAN_HW_H_

//ChibiOS headers
#include "ch.h"
#include "hal.h"

//Definitions
#define INIT 0x01
#define CERR 0x02
#define ERPA 0x04
#define RXOR 0x08
#define TXOR 0x10
#define BOFF 0x80

/*
 * CAN Register configuration
 * Timing calculator:
 * http://www.bittiming.can-wiki.info/
 * Note: Convert to zero based values here when using the calculator
 */
#if defined(STM32F0xx_MCUCONF)
// ~87.5% sample point 1Mbps based on 48MHz APB Clock
#define CAN_BTR(n) (CAN_BTR_SJW(0)|CAN_BTR_TS1(12)|CAN_BTR_TS2(1)|CAN_BTR_BRP((3000/n)-1))
#elif defined(STM32F4xx_MCUCONF)
// ~87.5% sample point 1Mbps based on 45MHz APB1 Clock
#define CAN_BTR(n) (CAN_BTR_SJW(0)|CAN_BTR_TS1(11)|CAN_BTR_TS2(1)|CAN_BTR_BRP((3000/n)-1))
#elif defined(STM32L4xx_MCUCONF)
// ~87.5% sample point 1Mbps based on 80MHz APB1 Clock
#define CAN_BTR(n) (CAN_BTR_SJW(0)|CAN_BTR_TS1(12)|CAN_BTR_TS2(1)|CAN_BTR_BRP((5000/n)-1))
#else
#error "No CAN Config for this MCU"
#endif

typedef struct {
    CANDriver *candev;
    CANConfig cancfg;
} candev_t;

typedef struct {
    uint32_t stdid   :11 ;
    uint32_t extid   :18 ;
    uint32_t rtr     :1  ;
    uint32_t ide     :1  ;
    uint32_t fifo    :1  ;
} can_flt_t;

typedef union {
    struct {
        uint32_t            :1 ;
        uint32_t RTR        :1 ;
        uint32_t IDE        :1 ;
        uint32_t EXID       :18;
        uint32_t STID       :11;
    } scale32;
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
    } scale16;
    uint32_t raw;
} flt_reg_t;

#endif
