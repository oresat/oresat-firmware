/*
 * CAN Subsystem Hardware header file
 */
#ifndef _CAN_HW_H_
#define _CAN_HW_H_

#ifdef __cplusplus
extern "C" {
#endif

//ChibiOS headers
#include "ch.h"
#include "hal.h"

/*
 * CAN Register configuration
 * Timing calculator:
 * http://www.bittiming.can-wiki.info/
 * Note: Convert to zero based values here when using the calculator
 */
#if defined(STM32F0XX)
// ~87.5% sample point 1Mbps based on 48MHz APB Clock
#define CAN_BTR(n) (CAN_BTR_SJW(0)|CAN_BTR_TS1(12)|CAN_BTR_TS2(1)|CAN_BTR_BRP((3000/n)-1))
#else
#error "No CAN Config for this MCU"
#endif

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
        } id_mask[2];
    } scale16;
    uint32_t raw;
} flt_reg_t;

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif
