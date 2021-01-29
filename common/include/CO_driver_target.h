/*
 * Device and application specific definitions for CANopenNode.
 *
 * @file        CO_driver_target.h
 * @author      Janez Paternoster
 * @copyright   2020 Janez Paternoster
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


#ifndef CO_DRIVER_TARGET_H
#define CO_DRIVER_TARGET_H

/* This file contains device and application specific definitions.
 * It is included from CO_driver.h, which contains documentation
 * for common definitions below. */

#include "ch.h"
#include "hal.h"
#include "oresat.h"

#ifdef CO_DRIVER_CUSTOM
#include "CO_driver_custom.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Stack configuration override default values.
 * For more information see file CO_config.h. */
#define CO_CONFIG_GLOBAL_FLAG_CALLBACK_PRE CO_CONFIG_FLAG_CALLBACK_PRE
#define CO_CONFIG_GLOBAL_FLAG_TIMERNEXT CO_CONFIG_FLAG_TIMERNEXT

#ifndef CO_CONFIG_NMT
#define CO_CONFIG_NMT (CO_CONFIG_NMT_CALLBACK_CHANGE | \
                       CO_CONFIG_GLOBAL_FLAG_CALLBACK_PRE | \
                       CO_CONFIG_GLOBAL_FLAG_TIMERNEXT)
#endif

#ifndef CO_CONFIG_HB_CONS
#define CO_CONFIG_HB_CONS (CO_CONFIG_HB_CONS_ENABLE | \
                           CO_CONFIG_HB_CONS_CALLBACK_MULTI | \
                           CO_CONFIG_HB_CONS_QUERY_FUNCT | \
                           CO_CONFIG_GLOBAL_FLAG_CALLBACK_PRE | \
                           CO_CONFIG_GLOBAL_FLAG_TIMERNEXT)
#endif

#ifndef CO_CONFIG_EM
#define CO_CONFIG_EM (CO_CONFIG_EM_PRODUCER | \
                      CO_CONFIG_EM_PROD_CONFIGURABLE | \
                      CO_CONFIG_EM_PROD_INHIBIT | \
                      CO_CONFIG_EM_HISTORY | \
                      CO_CONFIG_EM_STATUS_BITS | \
                      CO_CONFIG_EM_CONSUMER | \
                      CO_CONFIG_GLOBAL_FLAG_CALLBACK_PRE | \
                      CO_CONFIG_GLOBAL_FLAG_TIMERNEXT)
#endif

#ifndef CO_CONFIG_SDO_SRV
#define CO_CONFIG_SDO_SRV (CO_CONFIG_SDO_SRV_SEGMENTED | \
                           CO_CONFIG_SDO_SRV_BLOCK | \
                           CO_CONFIG_GLOBAL_FLAG_CALLBACK_PRE | \
                           CO_CONFIG_GLOBAL_FLAG_TIMERNEXT | \
                           CO_CONFIG_GLOBAL_FLAG_OD_DYNAMIC)
#endif

#ifndef CO_CONFIG_SDO_SRV_BUFFER_SIZE
#define CO_CONFIG_SDO_SRV_BUFFER_SIZE (127*7)
#endif

#ifndef CO_CONFIG_SDO_CLI
#define CO_CONFIG_SDO_CLI 0
#endif

#ifndef CO_CONFIG_TIME
#define CO_CONFIG_TIME 0
#endif

#ifndef CO_CONFIG_SYNC
#define CO_CONFIG_SYNC (CO_CONFIG_SYNC_ENABLE | \
                        CO_CONFIG_SYNC_PRODUCER | \
                        CO_CONFIG_GLOBAL_FLAG_CALLBACK_PRE | \
                        CO_CONFIG_GLOBAL_FLAG_TIMERNEXT | \
                        CO_CONFIG_GLOBAL_FLAG_OD_DYNAMIC)
#endif

#ifndef CO_CONFIG_PDO
#define CO_CONFIG_PDO (CO_CONFIG_RPDO_ENABLE | \
                       CO_CONFIG_TPDO_ENABLE | \
                       CO_CONFIG_PDO_SYNC_ENABLE | \
                       CO_CONFIG_RPDO_CALLS_EXTENSION | \
                       CO_CONFIG_TPDO_CALLS_EXTENSION | \
                       CO_CONFIG_GLOBAL_FLAG_CALLBACK_PRE | \
                       CO_CONFIG_GLOBAL_FLAG_TIMERNEXT)
#endif

#ifndef CO_CONFIG_GFC
#define CO_CONFIG_GFC 0
#endif

#ifndef CO_CONFIG_SRDO
#define CO_CONFIG_SRDO 0
#endif

#ifndef CO_CONFIG_SRDO_MINIMUM_DELAY
#define CO_CONFIG_SRDO_MINIMUM_DELAY 0
#endif

#ifndef CO_CONFIG_LSS
#define CO_CONFIG_LSS 0
#endif

#ifndef CO_CONFIG_GTW
#define CO_CONFIG_GTW 0
#endif

#ifndef CO_CONFIG_CRC16
#define CO_CONFIG_CRC16 (CO_CONFIG_CRC16_ENABLE)
#endif

#ifndef CO_CONFIG_FIFO
#define CO_CONFIG_FIFO (CO_CONFIG_FIFO_ENABLE | \
                        CO_CONFIG_FIFO_ALT_READ | \
                        CO_CONFIG_FIFO_CRC16_CCITT)
#endif

#ifndef CO_CONFIG_TRACE
#define CO_CONFIG_TRACE 0
#endif


/* Basic definitions. If big endian, CO_SWAP_xx macros must swap bytes. */
#define CO_LITTLE_ENDIAN
#define CO_SWAP_16(x) x
#define CO_SWAP_32(x) x
#define CO_SWAP_64(x) x
/* NULL is defined in stddef.h */
/* true and false are defined in stdbool.h */
/* int8_t to uint64_t are defined in stdint.h */
typedef uint_fast8_t            bool_t;
typedef float                   float32_t;
typedef double                  float64_t;
typedef char                    char_t;
typedef unsigned char           oChar_t;
typedef unsigned char           domain_t;


/* Access to received CAN message */
#define CO_CANrxMsg_readIdent(msg) ((uint16_t)((CO_CANrxMsg_t*)msg)->SID)
#define CO_CANrxMsg_readDLC(msg)   ((uint8_t)((CO_CANrxMsg_t*)msg)->DLC)
#define CO_CANrxMsg_readData(msg)  ((uint8_t *)((CO_CANrxMsg_t*)msg)->data)

/* Received message frame */
typedef struct {
    /** CAN identifier. It must be read through CO_CANrxMsg_readIdent() function. */
    union {
        CANRxFrame              rxFrame;
        struct {
            uint8_t             FMI;            /**< Filter id.          */
            uint16_t            TIME;           /**< Time stamp.         */
            uint8_t             DLC:4;          /**< Data length.        */
            uint8_t             RTR:1;          /**< Frame type.         */
            uint8_t             IDE:1;          /**< Identifier type.    */
            union {
                struct {
                    uint32_t    SID:11;         /**< Standard identifier.*/
                };
                struct {
                    uint32_t    EID:29;         /**< Extended identifier.*/
                };
            };
            union {
                uint8_t         data[8];        /**< Frame data.         */
                uint16_t        data16[4];      /**< Frame data.         */
                uint32_t        data32[2];      /**< Frame data.         */
                uint64_t        data64[1];      /**< Frame data.         */
            };
        };
    };
} CO_CANrxMsg_t;

/* Received message object */
typedef struct {
    uint16_t ident;
    uint16_t mask;
    void *object;
    void (*CANrx_callback)(void *object, void *message);
} CO_CANrx_t;

/* Transmit message object */
typedef struct {
    union {
        CANTxFrame              txFrame;        /* ChibiOS CANTxFrame  */
        struct {
            uint8_t             DLC:4;          /* Data length.        */
            uint8_t             RTR:1;          /* Frame type.         */
            uint8_t             IDE:1;          /* Identifier type.    */
            union {
                struct {
                    uint32_t    SID:11;         /* Standard identifier.*/
                };
                struct {
                    uint32_t    EID:29;         /* Extended identifier.*/
                };
            };
            union {
                uint8_t         data[8];        /* Frame data.         */
                uint16_t        data16[4];      /* Frame data.         */
                uint32_t        data32[2];      /* Frame data.         */
                uint64_t        data64[1];      /* Frame data.         */
            };
        };
    };
    volatile bool_t     bufferFull;             /* True if previous message is still in buffer */
    /* Synchronous PDO messages has this flag set. It prevents them to be sent outside the synchronous window */
    volatile bool_t     syncFlag;
} CO_CANtx_t;

/* CAN module object */
typedef struct {
    void               *CANptr;
    CANDriver          *cand;           /* CANDriver for ChibiOS */
    CANConfig           cancfg;         /* CANConfig for ChibiOS */
    event_source_t      rx_event;       /* Receive event */
    CO_CANrx_t         *rxArray;        /* From CO_CANmodule_init() */
    uint16_t            rxSize;         /* From CO_CANmodule_init() */
    CO_CANtx_t         *txArray;        /* From CO_CANmodule_init() */
    uint16_t            txSize;         /* From CO_CANmodule_init() */
    uint16_t            CANerrorStatus; /* Error Status */
    volatile bool_t     CANnormal;      /* CAN module is in normal mode */
    /* Value different than zero indicates, that CAN module hardware filters
     * are used for CAN reception. If there is not enough hardware filters,
     * they won't be used. In this case will be *all* received CAN messages
     * processed by software. */
    CANFilter           canFilters[STM32_CAN_MAX_FILTERS];
    volatile uint32_t   useCANrxFilters;
    /* If flag is true, then message in transmitt buffer is synchronous PDO
     * message, which will be aborted, if CO_clearPendingSyncPDOs() function
     * will be called by application. This may be necessary if Synchronous
     * window time was expired. */
    volatile bool_t     bufferInhibitFlag;
    /* Equal to 1, when the first transmitted message (bootup message) is in CAN TX buffers */
    volatile bool_t     firstCANtxMessage;
    /* Number of messages in transmit buffer, which are waiting to be copied to the CAN module */
    volatile uint16_t   CANtxCount;
    uint32_t            errOld;         /**< Previous state of CAN errors */
} CO_CANmodule_t;


/* (un)lock critical section in CO_CANsend() */
#define CO_LOCK_CAN_SEND()      chSysLock()             /* Lock critical section in CO_CANsend() */
#define CO_UNLOCK_CAN_SEND()    chSysUnlock()           /* Unlock critical section in CO_CANsend() */

/* (un)lock critical section in CO_errorReport() or CO_errorReset() */
extern mutex_t emcy_mutex;
#define CO_LOCK_EMCY()          chMtxLock(&emcy_mutex)  /* Lock critical section in CO_errorReport() or CO_errorReset() */
#define CO_UNLOCK_EMCY()        chMtxUnlock(&emcy_mutex)/* Unlock critical section in CO_errorReport() or CO_errorReset() */

/* (un)lock critical section when accessing Object Dictionary */
extern mutex_t od_mutex;
#define CO_LOCK_OD()            chMtxLock(&od_mutex)    /* Lock critical section when accessing Object Dictionary */
#define CO_UNLOCK_OD()          chMtxUnlock(&od_mutex)  /* Unock critical section when accessing Object Dictionary */

/* Synchronization between CAN receive and message processing threads. */
#define CO_MemoryBarrier()
#define CO_FLAG_READ(rxNew) ((rxNew) != NULL)
#define CO_FLAG_SET(rxNew) {CO_MemoryBarrier(); rxNew = (void*)1L;}
#define CO_FLAG_CLEAR(rxNew) {CO_MemoryBarrier(); rxNew = NULL;}


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CO_DRIVER_TARGET_H */
