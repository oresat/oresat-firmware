/**
 * @file    pdu.h
 * @brief   Protocol Data Unit (PDU) support library.
 *
 * @addtogroup PDU
 * @{
 */
#ifndef _PDU_H_
#define _PDU_H_

#include <stdlib.h>
#include <stdint.h>

/*===========================================================================*/
/* Constants.                                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Pre-compile time settings.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Data structures and types.                                                */
/*===========================================================================*/

/**
 * @name    PDU data structure
 * @{
 */
typedef struct {
    /* Application Layer */
    void            *data_arg;      /* Application layer argument           */
    void            *data;          /* Application layer data pointer       */
    size_t          data_len;       /* Application layer data length        */
    size_t          data_total_len; /* Application layer total data length  */
    size_t          data_offset;    /* Application layer data offset        */
    /* Transport Layer (Layer 4) */
    void            *trans_arg;     /* Transport layer argument             */
    void            *trans_hdr;     /* Transport layer header pointer       */
    size_t          trans_len;      /* Transport layer header length        */
    /* Network Layer (Layer 3) */
    void            *net_arg;       /* Network layer argument               */
    void            *net_hdr;       /* Network layer header pointer         */
    size_t          net_len;        /* Network layer header length          */
    /* MAC Layer (Layer 2) */
    void            *mac_arg;       /* Data link layer argument             */
    void            *mac_hdr;       /* Data link layer header               */
    size_t          mac_len;        /* Data link layer header length        */
    /* PHY Layer (Layer 1) */
    void            *phy_arg;       /* Physical layer argument              */
    void            *buf;           /* PDU buffer for physical layer        */
    size_t          buf_len;        /* PDU buffer length                    */
    size_t          buf_max;        /* Maximum size of PDU buffer           */
} pdu_t;
/** @} */

/*===========================================================================*/
/* Macros.                                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

void pdu_init(pdu_t *pdu);
size_t pdu_gen(pdu_t *pdu);

#ifdef __cplusplus
}
#endif

#endif /* _PDU_H_ */

/** @} */
