/**
 * @file    pdu.c
 * @brief   Protocol Data Unit (PDU) support library.
 *
 * @addtogroup PDU
 * @{
 */
#include <string.h>
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

void pdu_init(pdu_t *pdu)
{
    pdu->data = NULL;
    pdu->data_len = 0;
    pdu->data_offset = 0;
    pdu->trans_hdr = NULL;
    pdu->trans_len = 0;
    pdu->net_hdr = NULL;
    pdu->net_len = 0;
    pdu->mac_hdr = NULL;
    pdu->mac_len = 0;
    pdu->buf = NULL;
    pdu->buf_len = 0;
    pdu->buf_max = 0;
}

size_t pdu_gen(pdu_t *pdu)
{
    if (pdu->buf == NULL) {
        return 0;
    }

    pdu->buf_len = 0;
    if (pdu->mac_hdr) {
        if (pdu->buf_len + pdu->mac_len > pdu->buf_max) {
            return 0;
        }
        memcpy(pdu->buf, pdu->mac_hdr, pdu->mac_len);
        pdu->buf_len += pdu->mac_len;
    }

    if (pdu->net_hdr) {
        if (pdu->buf_len + pdu->net_len > pdu->buf_max) {
            return 0;
        }
        memcpy(pdu->buf, pdu->net_hdr, pdu->net_len);
        pdu->buf_len += pdu->net_len;
    }

    if (pdu->trans_hdr) {
        if (pdu->buf_len + pdu->trans_len > pdu->buf_max) {
            return 0;
        }
        memcpy(pdu->buf, pdu->trans_hdr, pdu->trans_len);
        pdu->buf_len += pdu->trans_len;
    }

    if (pdu->data) {
        if (pdu->buf_len + pdu->data_len > pdu->buf_max) {
            return 0;
        }
        memcpy(pdu->buf, &((uint8_t*)pdu->data)[pdu->data_offset], pdu->data_len);
        pdu->buf_len += pdu->data_len;
    }

    return pdu->buf_len;
}

/** @} */
