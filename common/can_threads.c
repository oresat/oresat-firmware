/*
 * CAN Subsystem Threads
 */

//Project headers
#include "can_threads.h"
#include "CANopen.h"

/*
 * CAN Worker Thread
 */
THD_WORKING_AREA(can_rt_wa, 0x40);
THD_FUNCTION(can_rt, p)
{
    systime_t prev_time, cur_time, diff_time;
    CO_t *CO = p;

    // Set thread name
    chRegSetThreadName("can_worker");

    prev_time = chVTGetSystemTimeX();
    // Start Loop
    while (!chThdShouldTerminateX()) {
        if(CO->CANmodule[0]->CANnormal) {
            bool_t syncWas;

            /* Process Sync and read inputs */
            diff_time = chTimeDiffX(prev_time, cur_time = chVTGetSystemTimeX());
            syncWas = CO_process_SYNC_RPDO(CO, chTimeI2US(diff_time));
            /* Further I/O or nonblocking application code may go here. */
            /* Write outputs */
            diff_time = chTimeDiffX(prev_time, cur_time = chVTGetSystemTimeX());
            prev_time = cur_time;
            CO_process_TPDO(CO, syncWas, chTimeI2US(diff_time));
        }

        chThdSleepMicroseconds(1000);
    }

    chThdExit(MSG_OK);
}

THD_WORKING_AREA(can_rx_wa, 0x40);
THD_FUNCTION(can_rx, p)
{
    CO_CANmodule_t      *CANmodule;         /* CANmodule of this worker */
    CANDriver           *cand;              /* CAN driver for this module */
    CO_CANrxMsg_t       rcvMsg;             /* Received message */
    uint16_t            index;              /* index of received message */
    uint32_t            rcvMsgIdent;        /* identifier of the received message */
    CO_CANrx_t          *buffer = NULL;     /* receive message buffer from CO_CANmodule_t object. */
    bool_t              msgMatched = false;

    /* Validate CANmodule pointer */
    if (p == NULL)
        return;
    CANmodule = p;
    cand = CANmodule->cand;

    /* Set thread name */
    chRegSetThreadName("rx_worker");
    /* Register RX event */
    chEvtRegister(&cand->rxfull_event, &CANmodule->rx_el, 0);

    while (!chThdShouldTerminateX()) {
        if (chEvtWaitAnyTimeout(ALL_EVENTS, TIME_MS2I(100)) == 0)
            continue;
        while (canReceive(cand, CAN_ANY_MAILBOX, &rcvMsg.rxFrame, TIME_IMMEDIATE) == MSG_OK) {
            rcvMsgIdent = rcvMsg.SID | (rcvMsg.RTR << 11);
            if(CANmodule->useCANrxFilters){
                /* CAN module filters are used. Message with known 11-bit identifier has */
                /* been received */
                index = rcvMsg.FMI;  /* Get index of the received message */
                if(index < CANmodule->rxSize){
                    buffer = &CANmodule->rxArray[index];
                    /* verify also RTR */
                    if(((rcvMsgIdent ^ buffer->ident) & buffer->mask) == 0U){
                        msgMatched = true;
                    }
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
    chEvtUnregister(&cand->rxfull_event, &CANmodule->rx_el);
    chThdExit(MSG_OK);
}

THD_WORKING_AREA(can_tx_wa, 0x40);
THD_FUNCTION(can_tx, p)
{
    CO_CANmodule_t      *CANmodule;         /* CANmodule of this worker */
    CANDriver           *cand;              /* CAN driver for this module */

    /* Validate CANmodule pointer */
    if (p == NULL)
        return;
    CANmodule = p;
    cand = CANmodule->cand;

    /* Set thread name */
    chRegSetThreadName("tx_worker");
    /* Register TX event */
    chEvtRegister(&cand->txempty_event, &CANmodule->tx_el, 0);

    while (!chThdShouldTerminateX()) {
        if (chEvtWaitAnyTimeout(ALL_EVENTS, TIME_MS2I(100)) == 0)
            continue;
        /* First CAN message (bootup) was sent successfully */
        CANmodule->firstCANtxMessage = false;
        /* clear flag from previous message */
        CANmodule->bufferInhibitFlag = false;
        /* Are there any new messages waiting to be send */
        if(CANmodule->CANtxCount > 0U){
            uint16_t i;             /* index of transmitting message */

            /* first buffer */
            CO_CANtx_t *buffer = &CANmodule->txArray[0];
            /* search through whole array of pointers to transmit message buffers. */
            for(i = CANmodule->txSize; i > 0U; i--){
                /* if message buffer is full, send it. */
                if(buffer->bufferFull){
                    buffer->bufferFull = false;
                    CANmodule->CANtxCount--;

                    /* Copy message to CAN buffer */
                    CANmodule->bufferInhibitFlag = buffer->syncFlag;
                    CO_CANsend(CANmodule, buffer);
                    break;                      /* exit for loop */
                }
                buffer++;
            }/* end of for loop */

            /* Clear counter if no more messages */
            if(i == 0U){
                CANmodule->CANtxCount = 0U;
            }
        }
    }

    //Unregister TX event before terminating thread
    chEvtUnregister(&cand->txempty_event, &CANmodule->tx_el);
    chThdExit(MSG_OK);
}
