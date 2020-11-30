/**
 * @file    pdu.c
 * @brief   Protocol Data Unit (PDU) support library.
 *
 * @addtogroup PDU
 * @{
 */
#include "pdu.h"

/*===========================================================================*/
/* Local definitions.                                                        */
/*===========================================================================*/

/*===========================================================================*/
/* Exported variables.                                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Local variables and types.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Local functions.                                                          */
/*===========================================================================*/

/*===========================================================================*/
/* Interface implementation.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Exported functions.                                                       */
/*===========================================================================*/

size_t pdu_gen(pdu_t *pdu)
{
    pdu->buf_len = 0;
    if (pdu->mac_hdr) {
        if (pdu->buf_len + pdu->mac_len > pdu->buf_max) {
            return 0;
        }
        memcpy(pdu->buf, pdu->mac_hdr, pdu->mac_len);
        pdu->buf_len += pdu->mac_len;
    }

    if (net_hdr) {
        if (pdu->buf_len + pdu->net_len > pdu->buf_max) {
            return 0;
        }
        memcpy(pdu->buf, pdu->net_hdr, pdu->net_len);
        pdu->buf_len += pdu->net_len;
    }

    if (trans_hdr) {
        if (pdu->buf_len + pdu->trans_len > pdu->buf_max) {
            return 0;
        }
        memcpy(pdu->buf, pdu->trans_hdr, pdu->trans_len);
        pdu->buf_len += pdu->trans_len;
    }

    if (data) {
        if (pdu->buf_len + pdu->data_len > pdu->buf_max) {
            return 0;
        }
        memcpy(pdu->buf, &pdu->data[pdu->data_offset], pdu->data_len);
        pdu->buf_len += pdu->data_len;
    }

    return pdu->buf_len;
}

/** @} */
