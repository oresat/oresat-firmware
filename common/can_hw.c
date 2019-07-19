/*
 * CAN Subsystem Hardware Implementation
 */

#include "can_hw.h"

/*
 * CAN Register configuration
 * Timing calculator:
 * http://www.bittiming.can-wiki.info/
 */
#if defined(STM32F0xx_MCUCONF)
// ~87.5% sample point 1Mbps based on 48MHz APB Clock
#define CAN_BTR (CAN_BTR_SJW(0)|CAN_BTR_TS1(12)|CAN_BTR_TS2(1)|CAN_BTR_BRP(2))
#elif defined(STM32F4xx_MCUCONF)
// ~87.5% sample point 1Mbps based on 45MHz APB1 Clock
#define CAN_BTR (CAN_BTR_SJW(0)|CAN_BTR_TS1(11)|CAN_BTR_TS2(1)|CAN_BTR_BRP(2))
#elif defined(STM32L4xx_MCUCONF)
// ~87.5% sample point 1Mbps based on 80MHz APB1 Clock
#define CAN_BTR (CAN_BTR_SJW(0)|CAN_BTR_TS1(12)|CAN_BTR_TS2(1)|CAN_BTR_BRP(4))
#else
#error "No CAN Config for this MCU"
#endif

static const CANConfig cancfg = {
    // MCR (Master Control Register)
    CAN_MCR_ABOM      |     //Automatic Bus-Off Management
    CAN_MCR_AWUM      |     //Automatic Wakeup Mode
    CAN_MCR_TXFP      ,     //Transmit FIFO Priority
    // BTR (Bit Timing Register)
    // Note: Convert to zero based values here when using the calculator
    //CAN_BTR_LBKM     |     //Loopback Mode (Debug)
    CAN_BTR
};

static CANFilter can_filters[STM32_CAN_MAX_FILTERS];
static uint32_t filter_entries = 0;

void canFilterInit(CANFilter *cfp, uint16_t filter_num, flt_reg_t reg1, flt_reg_t reg2, uint8_t flags) {
    cfp->filter     = filter_num;
    cfp->mode       = (flags && CAN_FLT_MODE_MASK) >> CAN_FLT_MODE_POS;
    cfp->scale      = (flags && CAN_FLT_SCALE_MASK) >> CAN_FLT_SCALE_POS;
    cfp->assignment = (flags && CAN_FLT_FIFO_MASK) >> CAN_FLT_FIFO_POS;
    cfp->register1  = reg1;
    cfp->register2  = reg2;
}

uint8_t can_hw_init(void) {
    /*
     * Activates CAN driver 1.
     */
    canSTM32SetFilters(&CAND1, 0xE, filter_entries, can_filters);
    canStart(&CAND1, &cancfg);

    return true;
}
