/*
 * CAN Subsystem Hardware Implementation
 */

#include "can_hw.h"

/*
 * Receiver thread.
 */
THD_WORKING_AREA(can_rx_wa, 256);
THD_FUNCTION(can_rx, p) {
    event_listener_t        el;
    CANRxFrame              rxmsg;

    (void)p;
    // Set thread name
    chRegSetThreadName("receiver");
    // Register RX event
    chEvtRegister(&CAND1.rxfull_event, &el, 0);

    // Start RX Loop
    while (!chThdShouldTerminateX()) {
        if (chEvtWaitAnyTimeout(ALL_EVENTS, TIME_MS2I(100)) == 0) {
            continue;
        }
        while (canReceive(&CAND1, CAN_ANY_MAILBOX, &rxmsg, TIME_IMMEDIATE) == MSG_OK) {
            /* Process message.*/

        }
    }

    //Unregister RX event before terminating thread
    chEvtUnregister(&CAND1.rxfull_event, &el);
}

/*
 * Transmitter thread.
 */
THD_WORKING_AREA(can_tx_wa, 256);
THD_FUNCTION(can_tx, p) {
    CANTxFrame txmsg;

    (void)p;
    chRegSetThreadName("transmitter");

    //Initialize txmsg struct
    txmsg.IDE = CAN_IDE_STD;
    txmsg.SID = 0x7FF;
    txmsg.RTR = CAN_RTR_DATA;
    txmsg.DLC = 8;
    txmsg.data8[0] = 0x00;
    txmsg.data8[1] = 0x00;
    txmsg.data8[2] = 0x00;
    txmsg.data8[3] = 0x00;
    txmsg.data8[4] = 0x00;
    txmsg.data8[5] = 0x00;
    txmsg.data8[6] = 0x00;
    txmsg.data8[7] = 0x00;

    // Start TX Loop
    while (!chThdShouldTerminateX()) {
        canTransmit(&CAND1, CAN_ANY_MAILBOX, &txmsg, TIME_MS2I(100));
        chThdSleepMilliseconds(500);
    }
}
