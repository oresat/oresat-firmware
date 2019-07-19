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

#define CAN_FLT_MASK    (0U)
#define CAN_FLT_LIST    (1U)
#define CAN_FLT_16BIT   (0U)
#define CAN_FLT_32BIT   (1U)
#define CAN_FLT_FIFO(n) (n)
#define CAN_FLT_EID0(n) (n)
#define CAN_FLT_IDE0(n) (n << 3)
#define CAN_FLT_RTR0(n) (n << 4)
#define CAN_FLT_SID0(n) (n << 5)
#define CAN_FLT_EID1(n) (n << 16)
#define CAN_FLT_IDE1(n) (n << 19)
#define CAN_FLT_RTR1(n) (n << 20)
#define CAN_FLT_SID1(n) (n << 21)

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

static const CANFilter can_filters[] = {
    {   0,                                                                          // Filter Number
        CAN_FLT_MASK,                                                               // Mode
        CAN_FLT_16BIT,                                                              // Scale
        CAN_FLT_FIFO(0),                                                            // Assigned FIFO
        CAN_FLT_EID0(0) | CAN_FLT_IDE0(0) | CAN_FLT_RTR0(0) | CAN_FLT_SID0(0x000) | // ID
        CAN_FLT_EID1(0) | CAN_FLT_IDE1(0) | CAN_FLT_RTR1(0) | CAN_FLT_SID1(0x07F) , // Mask/ID
        CAN_FLT_EID0(0) | CAN_FLT_IDE0(0) | CAN_FLT_RTR0(0) | CAN_FLT_SID0(0x000) | // ID
        CAN_FLT_EID1(0) | CAN_FLT_IDE1(0) | CAN_FLT_RTR1(0) | CAN_FLT_SID1(0x07F) },// Mask/ID
};

void can_filter_init(CANFilter *cfp, uint16_t filter_num, flt_reg_t reg1, flt_reg_t reg2, uint8_t flags) {

}

uint8_t can_hw_init(void) {
    /*
     * Activates CAN driver 1.
     */
    canSTM32SetFilters(&CAND1, 0xE, sizeof(can_filters)/sizeof(can_filters[0]), can_filters);
    canStart(&CAND1, &cancfg);

    return true;
}
