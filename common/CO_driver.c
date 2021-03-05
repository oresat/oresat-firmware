/*
 * CAN module object for generic microcontroller.
 *
 * This file is a template for other microcontrollers.
 *
 * @file        CO_driver.c
 * @ingroup     CO_driver
 * @author      Janez Paternoster
 * @copyright   2004 - 2020 Janez Paternoster
 *
 * This file is part of CANopenNode, an opensource CANopen Stack.
 * Project home page is <https://github.com/CANopenNode/CANopenNode>.
 * For more information on CANopen see <http://www.can-cia.org/>.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include "301/CO_driver.h"
#include "can_hw.h"
#include "oresat.h"

#define container_of(ptr, type, member) ({const typeof(((type *)0)->member) *__mptr = (ptr); (type *)((char *)__mptr - offsetof(type,member));})

MUTEX_DECL(emcy_mutex);
MUTEX_DECL(od_mutex);

/* Interrupt callback prototypes*/
void CO_CANrx_cb(CANDriver *canp, uint32_t flags);
void CO_CANtx_cb(CANDriver *canp, uint32_t flags);
void CO_CANerr_cb(CANDriver *canp, uint32_t flags);

/******************************************************************************/
void CO_CANsetConfigurationMode(void *CANptr)
{
    /* Put CAN module in configuration mode */
    canStop(((oresat_config_t*)CANptr)->cand);
}

/******************************************************************************/
void CO_CANsetNormalMode(CO_CANmodule_t *CANmodule)
{
    /* Put CAN module in normal mode */
    canSTM32SetFilters(CANmodule->cand, 0, CANmodule->useCANrxFilters,
            CANmodule->canFilters);
    canStart(CANmodule->cand, &CANmodule->cancfg);
    CANmodule->CANnormal = true;
}

/******************************************************************************/
void CO_CANsetFilters(CO_CANmodule_t *CANmodule)
{
    canStop(CANmodule->cand);
    canSTM32SetFilters(CANmodule->cand, 0, CANmodule->useCANrxFilters,
            CANmodule->canFilters);
    canStart(CANmodule->cand, &CANmodule->cancfg);
}

/******************************************************************************/
CO_ReturnError_t CO_CANmodule_init(
        CO_CANmodule_t         *CANmodule,
        void                   *CANptr,
        CO_CANrx_t              rxArray[],
        uint16_t                rxSize,
        CO_CANtx_t              txArray[],
        uint16_t                txSize,
        uint16_t                CANbitRate)
{
    uint16_t i;

    /* Verify arguments */
    if (CANmodule==NULL || rxArray==NULL || txArray==NULL) {
        return CO_ERROR_ILLEGAL_ARGUMENT;
    }

    /* Configure object variables */
    CANmodule->CANptr = CANptr;
    CANmodule->cand = ((oresat_config_t*)CANptr)->cand;
    CANmodule->cand->rxfull_cb = CO_CANrx_cb;
    CANmodule->cand->txempty_cb = CO_CANtx_cb;
    CANmodule->cand->error_cb = CO_CANerr_cb;
    chEvtObjectInit(&CANmodule->rx_event);
    CANmodule->rxArray = rxArray;
    CANmodule->rxSize = rxSize;
    CANmodule->txArray = txArray;
    CANmodule->txSize = txSize;
    CANmodule->CANerrorStatus = 0;
    CANmodule->CANnormal = false;
    CANmodule->useCANrxFilters = (rxSize <= (STM32_CAN_MAX_FILTERS * 4) ? (rxSize / 4) + 1 : 0);
    CANmodule->bufferInhibitFlag = false;
    CANmodule->firstCANtxMessage = true;
    CANmodule->CANtxCount = 0U;
    CANmodule->errOld = 0U;

    for (i=0U; i<rxSize; i++) {
        rxArray[i].ident = 0U;
        rxArray[i].mask = 0xFFFFU;
        rxArray[i].object = NULL;
        rxArray[i].CANrx_callback = NULL;
    }
    for (i=0U; i<txSize; i++) {
        txArray[i].bufferFull = false;
    }

    /* Configure CAN module registers */
    CANmodule->cancfg.mcr = (
            /* MCR (Master Control Register) */
            CAN_MCR_ABOM      |     //Automatic Bus-Off Management
            CAN_MCR_AWUM      |     //Automatic Wakeup Mode
            CAN_MCR_TXFP      );    //Transmit FIFO Priority

    /* Configure CAN timing */
    CANmodule->cancfg.btr = (
            /* BTR (Bit Timing Register) */
            /*CAN_BTR_LBKM     |     //Loopback Mode (Debug) */
            CAN_BTR(CANbitRate));   //Calculate BTR value and set

    /* Configure CAN module hardware filters */
    /* CAN module filters are used, they will be configured with */
    /* CO_CANrxBufferInit() functions, called by separate CANopen */
    /* init functions. */
    /* Initialize all filter entries */
    for (i = 0U; i < CANmodule->useCANrxFilters; i++) {
        CANmodule->canFilters[i].filter = i;
        CANmodule->canFilters[i].mode = 1;                  /* List Mode */
        CANmodule->canFilters[i].scale = 0;                 /* 16bit scale */
        CANmodule->canFilters[i].assignment = 0;            /* Assign FIFO0 */
        CANmodule->canFilters[i].register1 = 0;             /* Clear out the IDs */
        CANmodule->canFilters[i].register2 = 0;             /* Clear out the IDs */
    }

    return CO_ERROR_NO;
}


/******************************************************************************/
void CO_CANmodule_disable(CO_CANmodule_t *CANmodule)
{
    /* turn off the module */
    canStop(CANmodule->cand);
}


/******************************************************************************/
CO_ReturnError_t CO_CANrxBufferInit(
        CO_CANmodule_t         *CANmodule,
        uint16_t                index,
        uint16_t                ident,
        uint16_t                mask,
        bool_t                  rtr,
        void                   *object,
        void                  (*CANrx_callback)(void *object, void *message))
{
    CO_ReturnError_t ret = CO_ERROR_NO;

    if ((CANmodule != NULL) && (object != NULL) && (CANrx_callback != NULL) && (index < CANmodule->rxSize)) {
        /* buffer, which will be configured */
        CO_CANrx_t *buffer = &CANmodule->rxArray[index];

        /* Configure object variables */
        buffer->object = object;
        buffer->CANrx_callback = CANrx_callback;

        /* CAN identifier and CAN mask */
        buffer->ident = ident & 0x07FFU;
        if (rtr) {
            buffer->ident |= 0x0800U;
        }
        buffer->mask = (mask & 0x07FFU) | 0x0800U;

        /* Set CAN hardware module filter and mask. */
        if (CANmodule->useCANrxFilters) {
            flt_reg_t *filter;

            if ((index % 4) < 2) {
                filter = (flt_reg_t*)(&CANmodule->canFilters[index / 4].register1);
            } else {
                filter = (flt_reg_t*)(&CANmodule->canFilters[index / 4].register2);
            }
            filter->scale16.id_mask[index % 2].STID = ident;
            filter->scale16.id_mask[index % 2].RTR = rtr;

            if (CANmodule->CANnormal) {
                CO_CANsetFilters(CANmodule);
            }
        }
    } else {
        ret = CO_ERROR_ILLEGAL_ARGUMENT;
    }

    return ret;
}


/******************************************************************************/
CO_CANtx_t *CO_CANtxBufferInit(
        CO_CANmodule_t         *CANmodule,
        uint16_t                index,
        uint16_t                ident,
        bool_t                  rtr,
        uint8_t                 noOfBytes,
        bool_t                  syncFlag)
{
    CO_CANtx_t *buffer = NULL;

    if ((CANmodule != NULL) && (index < CANmodule->txSize)) {
        /* get specific buffer */
        buffer = &CANmodule->txArray[index];

        /* CAN identifier, DLC and rtr, bit aligned with CAN module transmit buffer.
         * Microcontroller specific. */
        buffer->SID = ident;
        buffer->DLC = noOfBytes;
        buffer->RTR = rtr;

        buffer->bufferFull = false;
        buffer->syncFlag = syncFlag;
    }

    return buffer;
}


/******************************************************************************/
CO_ReturnError_t CO_CANsend(CO_CANmodule_t *CANmodule, CO_CANtx_t *buffer)
{
    CO_ReturnError_t err = CO_ERROR_NO;

    /* Verify overflow */
    if (buffer->bufferFull) {
        if (!CANmodule->firstCANtxMessage) {
            /* Don't set error, if bootup message is still on buffers */
            CANmodule->CANerrorStatus |= CO_CAN_ERRTX_OVERFLOW;
        }
        err = CO_ERROR_TX_OVERFLOW;
    }

    CO_LOCK_CAN_SEND();
    /* If CAN TX buffer is free, attempt to send it */
    if (CANmodule->CANtxCount == 0 &&
            !canTryTransmitI(CANmodule->cand, CAN_ANY_MAILBOX, &buffer->txFrame)) {
        CANmodule->bufferInhibitFlag = buffer->syncFlag;
    } else {
        /* If no buffer is free, message will be sent by interrupt */
        buffer->bufferFull = true;
        CANmodule->CANtxCount++;
    }
    CO_UNLOCK_CAN_SEND();

    return err;
}


/******************************************************************************/
void CO_CANclearPendingSyncPDOs(CO_CANmodule_t *CANmodule)
{
    uint32_t tpdoDeleted = 0U;

    CO_LOCK_CAN_SEND();
    /* Abort message from CAN module, if there is synchronous TPDO.
     * Take special care with this functionality. */
    /* TODO: Figure out how to distinguish synchronous TPDOs in TX mailboxes */
    if (/*messageIsOnCanBuffer && */CANmodule->bufferInhibitFlag) {
        /* clear TXREQ */
        CANmodule->bufferInhibitFlag = false;
        tpdoDeleted = 1U;
    }
    /* delete also pending synchronous TPDOs in TX buffers */
    if (CANmodule->CANtxCount != 0U) {
        uint16_t i;
        CO_CANtx_t *buffer = &CANmodule->txArray[0];
        for (i = CANmodule->txSize; i > 0U; i--) {
            if (buffer->bufferFull) {
                if (buffer->syncFlag) {
                    buffer->bufferFull = false;
                    CANmodule->CANtxCount--;
                    tpdoDeleted = 2U;
                }
            }
            buffer++;
        }
    }
    CO_UNLOCK_CAN_SEND();


    if (tpdoDeleted != 0U) {
        CANmodule->CANerrorStatus |= CO_CAN_ERRTX_PDO_LATE;
    }
}


/******************************************************************************/
/* Get error counters from the module. If necessary, function may use
    * different way to determine errors. */

void CO_CANmodule_process(CO_CANmodule_t *CANmodule)
{
    CAN_TypeDef *can = CANmodule->cand->can;
    uint32_t err;
    uint8_t rxErrors, txErrors;

    /* Get ESR and FOVRx values */
    err = (can->ESR | ((can->RF0R & CAN_RF0R_FOVR0_Msk) << 4) | ((can->RF1R & CAN_RF1R_FOVR1_Msk) << 5));
    rxErrors = _FLD2VAL(CAN_ESR_REC, err);
    txErrors = _FLD2VAL(CAN_ESR_TEC, err);

    if (CANmodule->errOld != err) {
        uint16_t status = CANmodule->CANerrorStatus;

        CANmodule->errOld = err;

        if (err & CAN_ESR_BOFF) {
            /* bus off */
            status |= CO_CAN_ERRTX_BUS_OFF;
        } else {
            /* not bus off */
            /* recalculate CANerrorStatus, first clear some flags */
            status &= 0xFFFF ^ (CO_CAN_ERRTX_BUS_OFF | CO_CAN_ERR_WARN_PASSIVE);

            /* rx bus warning or passive */
            if (rxErrors >= 128) {
                status |= CO_CAN_ERRRX_WARNING | CO_CAN_ERRRX_PASSIVE;
            } else if (rxErrors >= 96) {
                status |= CO_CAN_ERRRX_WARNING;
            }

            /* tx bus warning or passive */
            if (txErrors >= 128) {
                status |= CO_CAN_ERRTX_WARNING | CO_CAN_ERRTX_PASSIVE;
            } else if (rxErrors >= 96) {
                status |= CO_CAN_ERRTX_WARNING;
            }

            /* if not tx passive clear also overflow */
            if ((status & CO_CAN_ERRTX_PASSIVE) == 0) {
                status &= 0xFFFF ^ CO_CAN_ERRTX_OVERFLOW;
            }
        }

        /* Check for overflow of RX FIFOs */
        if ((can->RF0R & CAN_RF0R_FOVR0_Msk) | (can->RF1R & CAN_RF1R_FOVR1_Msk)) {
            /* CAN RX bus overflow */
            status |= CO_CAN_ERRRX_OVERFLOW;
        }

        CANmodule->CANerrorStatus = status;
    }
}


/******************************************************************************/
/* TODO: Switch to error callback */
void CO_CANerr_cb(CANDriver *canp, uint32_t flags)
{
    CO_CANmodule_t      *CANmodule;
    CAN_TypeDef         *can;
    uint16_t            status;

    CANmodule = container_of(canp->config, CO_CANmodule_t, cancfg);
    can = CANmodule->cand->can;
    status = CANmodule->CANerrorStatus;

    /* TODO: Remove these when implemented. Suppressing warnings. */
    (void)can;
    (void)flags;

    CANmodule->CANerrorStatus = status;
}

void CO_CANrx_cb(CANDriver *canp, uint32_t flags)
{
    CO_CANmodule_t      *CANmodule;
    CO_CANrxMsg_t       rcvMsg;             /* Received message */
    uint8_t             index;              /* index of received message */
    uint32_t            rcvMsgIdent;        /* identifier of the received message */
    CO_CANrx_t          *buffer = NULL;     /* receive message buffer from CO_CANmodule_t object. */
    bool_t              msgMatched = false;
    (void)flags;

    if (canp == NULL)
        return;
    CANmodule = container_of(canp->config, CO_CANmodule_t, cancfg);

    chSysLockFromISR();
    canTryReceiveI(canp, CAN_ANY_MAILBOX, &rcvMsg.rxFrame);
    rcvMsgIdent = rcvMsg.SID | (rcvMsg.RTR << 11);
    if (CANmodule->useCANrxFilters) {
        /* CAN module filters are used. Message with known 11-bit identifier has */
        /* been received */
        index = rcvMsg.FMI;  /* Get index of the received message */
        if (index < CANmodule->rxSize) {
            buffer = &CANmodule->rxArray[index];
            msgMatched = true;
        }
    } else {
        /* CAN module filters are not used, message with any standard 11-bit identifier */
        /* has been received. Search rxArray form CANmodule for the same CAN-ID. */
        buffer = &CANmodule->rxArray[0];
        for (index = CANmodule->rxSize; index > 0U; index--) {
            if (((rcvMsgIdent ^ buffer->ident) & buffer->mask) == 0U) {
                msgMatched = true;
                break;
            }
            buffer++;
        }
    }

    /* Call specific function, which will process the message */
    if (msgMatched && (buffer != NULL) && (buffer->CANrx_callback != NULL)) {
        buffer->CANrx_callback(buffer->object, &rcvMsg);
    }
    chEvtBroadcastI(&CANmodule->rx_event);
    chSysUnlockFromISR();
}

void CO_CANtx_cb(CANDriver *canp, uint32_t flags)
{
    CO_CANmodule_t      *CANmodule;
    (void)flags;

    if (canp == NULL)
        return;
    CANmodule = container_of(canp->config, CO_CANmodule_t, cancfg);

    chSysLockFromISR();
    /* First CAN message (bootup) was sent successfully */
    CANmodule->firstCANtxMessage = false;
    /* clear flag from previous message */
    CANmodule->bufferInhibitFlag = false;
    /* Are there any new messages waiting to be send */
    if (CANmodule->CANtxCount > 0U) {
        uint16_t i;             /* index of transmitting message */

        /* first buffer */
        CO_CANtx_t *buffer = &CANmodule->txArray[0];
        /* search through whole array of pointers to transmit message buffers. */
        for (i = CANmodule->txSize; i > 0U; i--) {
            /* if message buffer is full, send it. */
            if (buffer->bufferFull) {
                buffer->bufferFull = false;
                CANmodule->CANtxCount--;

                /* Copy message to CAN buffer */
                CANmodule->bufferInhibitFlag = buffer->syncFlag;
                canTryTransmitI(canp, CAN_ANY_MAILBOX, &buffer->txFrame);
                break;                      /* exit for loop */
            }
            buffer++;
        }/* end of for loop */

        /* Clear counter if no more messages */
        if (i == 0U) {
            CANmodule->CANtxCount = 0U;
        }
    }
    chSysUnlockFromISR();
}
