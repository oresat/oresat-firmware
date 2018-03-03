/*
 * CAN Subsystem Hardware Implementation
 */

#include "can.h"

void can_init(uint8_t node_id) {

    /*
     * Activates CAN driver 1.
     */
    canStart(&CAND1, &cancfg);
    return;
}

void can_start(void) {
    /*
     * Starting the transmitter and receiver threads.
     */
    chThdCreateStatic(can_rx_wa, sizeof(can_rx_wa), NORMALPRIO + 7, can_rx, NULL);
    chThdCreateStatic(can_tx_wa, sizeof(can_tx_wa), NORMALPRIO + 7, can_tx, NULL);
    return;
}


void can_initTPDO(uint8_t pdo_num, uint32_t can_id, uint32_t event_tim, uint32_t inhibit_tim, uint8_t len, uint8_t offset) {

    return;
}

void can_initRPDO(uint8_t pdo_num, uint32_t can_id, uint8_t len, uint8_t offset) {

    return;
}

uint8_t can_processStack(void) {
    uint8_t status = 0;

    return status;
}

void can_reset_app(void) {

    return;
}
void can_reset_comms(void) {

    return;
}

void can_fatal_error(uint32_t err_code) {

    return;
}
