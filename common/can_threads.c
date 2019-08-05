/*
 * CAN Subsystem Threads
 */

//Project headers
#include "can_threads.h"
#include "CO_driver.h"

/*
 * Receiver thread.
 */
THD_WORKING_AREA(can_rx_wa, 128);
THD_FUNCTION(can_rx, p) {
    event_listener_t    can_el;
    CO_CANrxMsg_t       rcvMsg;             /* Received message */
    uint8_t             index;              /* index of received message */
    uint32_t            rcvMsgIdent;        /* identifier of the received message */
    CO_CANrx_t          *buffer = NULL;     /* receive message buffer from CO_CANmodule_t object. */
    bool_t              msgMatched = false;
    CO_CANmodule_t      *CANmodule = p;
    CANDriver           *candev = (CANDriver *)CANmodule->CANbaseAddress;

    // Set thread name
    chRegSetThreadName("CAN Receiver");
    // Register RX event
    chEvtRegister(&candev->rxfull_event, &can_el, 0);

    // Start RX Loop
    while (!chThdShouldTerminateX()) {
        if (chEvtWaitAnyTimeout(ALL_EVENTS, TIME_MS2I(100)) == 0) {
            /* No activity, continue and check if thread should terminate */
            continue;
        }

        while (canReceiveTimeout(candev, CAN_ANY_MAILBOX, &rcvMsg.rxFrame, TIME_IMMEDIATE) == MSG_OK) {
            /* Process message.*/
            rcvMsgIdent = rcvMsg.SID | (rcvMsg.RTR << 11);
            if(CANmodule->useCANrxFilters){
                /* CAN module filters are used. Message with known 11-bit identifier has */
                /* been received */
                index = rcvMsg.FMI;  /* Get index of the received message */
                if(index < CANmodule->rxSize){
                    buffer = &CANmodule->rxArray[index];
                    msgMatched = true;
                }
            }
            else{
                /* CAN module filters are not used, message with any standard 11-bit identifier */
                /* has been received. Search rxArray form CANmodule for the same CAN-ID. */
                buffer = &CANmodule->rxArray[0];
                for(index = CANmodule->rxSize; index > 0U; index--){
                    if(((rcvMsgIdent ^ buffer->ident) & buffer->mask) == 0U){
                        msgMatched = true;
                        break;
                    }
                    buffer++;
                }
            }

            /* Call specific function, which will process the message */
            if(msgMatched && (buffer != NULL) && (buffer->pFunct != NULL)){
                buffer->pFunct(buffer->object, &rcvMsg);
            }

        }
    }

    //Unregister RX event before terminating thread
    chEvtUnregister(&candev->rxfull_event, &can_el);
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

    }
    chThdExit(MSG_OK);
}

void can_start_threads(void) {
    /*
     * Starting the transmitter and receiver threads.
     */
    chThdCreateStatic(can_rx_wa, sizeof(can_rx_wa), NORMALPRIO + 7, can_rx, NULL);
    chThdCreateStatic(can_tpdo_wa, sizeof(can_tpdo_wa), NORMALPRIO + 7, can_tpdo, NULL);
}
