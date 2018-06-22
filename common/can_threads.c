/*
 * CAN Subsystem Threads
 */

#include "can_threads.h"

/*
 * Receiver thread.
 */
THD_WORKING_AREA(can_rpdo_wa, 128);
THD_FUNCTION(can_rpdo, p) {
    event_listener_t        can_el;
    CANRxFrame              rxmsg;

    (void)p;
    // Set thread name
    chRegSetThreadName("receiver");
    // Register RX event
    chEvtRegister(&CAND1.rxfull_event, &can_el, 0);

    // Start RX Loop
    while (!chThdShouldTerminateX()) {
        if (chEvtWaitAnyTimeout(ALL_EVENTS, TIME_MS2I(100)) == 0) {
            continue;
        }

        while (canReceive(&CAND1, CAN_ANY_MAILBOX, &rxmsg, TIME_IMMEDIATE) == MSG_OK) {
            /* Process message.*/
            for (uint8_t i = 0; i < 4; ++i) {
                if (rpdo[i].pdata == NULL) {
                    // RPDO is undefined. Continue to next
                    continue;
                }

                // If the data received matches this RPDO, copy the data
                if (rxmsg.SID == rpdo[i].can_id){
                    if (rxmsg.DLC != rpdo[i].len) {
                        // TODO: Exception
                        continue;
                    }

                    chSysLock();
                    for (uint8_t j = 0; j < rxmsg.DLC; ++j) {
                        rpdo[i].pdata[j] = rxmsg.data8[j];
                    }
                    chSysUnlock();
                    chEvtBroadcast(&rpdo_event);
                }
            }
        }
    }

    //Unregister RX event before terminating thread
    chEvtUnregister(&CAND1.rxfull_event, &can_el);
    chThdExit(MSG_OK);
}

/*
 * Transmitter thread.
 */
THD_WORKING_AREA(can_tpdo_wa, 128);
THD_FUNCTION(can_tpdo, p) {
    (void)p;
    chRegSetThreadName("transmitter");

    // Start TX Loop
    while (!chThdShouldTerminateX()) {
        for (uint8_t i = 0; i < 4; ++i)
        {
            if (tpdo[i].pdata == NULL) {
                // TPDO is undefined. Continue to next
                continue;
            }

            chSysLock();
            for (uint8_t j = 0; j < tpdo[i].msg.DLC; ++j)
            {
                tpdo[i].msg.data8[j] = tpdo[i].pdata[j];
            }
            chSysUnlock();

            // Transmit the PDO
            canTransmit(&CAND1, CAN_ANY_MAILBOX, &tpdo[i].msg, TIME_MS2I(100));
        }
        chThdSleepMilliseconds(200);
    }
    chThdExit(MSG_OK);
}

/*
 * Heartbeat thread.
 */
THD_WORKING_AREA(can_hb_wa, 64);
THD_FUNCTION(can_hb, p) {
    (void)p;
    chRegSetThreadName("heartbeat");

    // Start TX Loop
    while (!chThdShouldTerminateX()) {
        canTransmit(&CAND1, CAN_ANY_MAILBOX, &node.heartbeat_msg, TIME_MS2I(100));
        chThdSleepMilliseconds(node.heartbeat_time);
    }

    chThdExit(MSG_OK);
}

void can_start_threads(void) {
    /*
     * Starting the transmitter and receiver threads.
     */
    chThdCreateStatic(can_rpdo_wa, sizeof(can_rpdo_wa), NORMALPRIO + 7, can_rpdo, NULL);
    chThdCreateStatic(can_tpdo_wa, sizeof(can_tpdo_wa), NORMALPRIO + 7, can_tpdo, NULL);
    chThdCreateStatic(can_hb_wa, sizeof(can_hb_wa), NORMALPRIO + 7, can_hb, NULL);
}
