/*
 * CAN Subsystem Threads
 */

#include "can_threads.h"

/*
 * Receiver thread.
 */
THD_WORKING_AREA(can_rx_wa, 128);
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
            for (uint8_t i = 0; i < 4; ++i) {
                if (!rpdo_objects[i].pdata) {
                    continue;
                }
                if (rxmsg.SID == rpdo_objects[i].can_id){
                    if (rxmsg.DLC != rpdo_objects[i].len) {
                        // TODO: Exception
                        continue;
                    }
                    for (uint8_t j = 0; j < rxmsg.DLC; ++j) {
                        rpdo_objects[i].pdata[j] = rxmsg.data8[j];
                    }
                }
            }
        }
    }

    //Unregister RX event before terminating thread
    chEvtUnregister(&CAND1.rxfull_event, &el);
}

/*
 * Transmitter thread.
 */
THD_WORKING_AREA(can_tx_wa, 128);
THD_FUNCTION(can_tx, p) {
    (void)p;
    chRegSetThreadName("transmitter");

    // Start TX Loop
    while (!chThdShouldTerminateX()) {
        for (uint8_t i = 0; i < 4; ++i)
        {
            if (!tpdo_objects[i].pdata) {
                continue;
            }
            for (uint8_t j = 0; j < tpdo_objects[i].msg.DLC; ++j)
            {
                tpdo_objects[i].msg.data8[j] = tpdo_objects[i].pdata[j];
            }
            canTransmit(&CAND1, CAN_ANY_MAILBOX, &tpdo_objects[i].msg, TIME_MS2I(100));
        }
        chThdSleepMilliseconds(20);
    }
}

THD_WORKING_AREA(can_hb_wa, 64);
THD_FUNCTION(can_hb, p) {
    (void)p;
    chRegSetThreadName("heartbeat");

    // Start TX Loop
    while (!chThdShouldTerminateX()) {
        canTransmit(&CAND1, CAN_ANY_MAILBOX, &node.heartbeat_msg, TIME_MS2I(100));
        chThdSleepMilliseconds(node.heartbeat_time);
    }

}

void can_start_threads(void) {
    /*
     * Starting the transmitter and receiver threads.
     */
    chThdCreateStatic(can_rx_wa, sizeof(can_rx_wa), NORMALPRIO + 7, can_rx, NULL);
    chThdCreateStatic(can_tx_wa, sizeof(can_tx_wa), NORMALPRIO + 7, can_tx, NULL);
    chThdCreateStatic(can_hb_wa, sizeof(can_hb_wa), NORMALPRIO + 7, can_hb, NULL);
}
