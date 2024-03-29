/**
 * @file    ax25.c
 * @brief   AX.25 protocol support library.
 *
 * @addtogroup AX25
 * @{
 */
#include <string.h>
#include "ax25.h"

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

void *ax25_sdu(fb_t *fb, const void *arg)
{
    const ax25_link_t *link = arg;
    ax25_hdr_t *mac_hdr;

    mac_hdr = fb_push(fb, sizeof(ax25_hdr_t));
    if (mac_hdr != NULL) {
        for (int i = 0; i < 6; i++) {
            /* Shift characters and convert NULL's to spaces */
            mac_hdr->dest[i] = (link->dest[i] != 0 ? link->dest[i] << 1 : 0x20 << 1);
            mac_hdr->src[i] = (link->src[i] != 0 ? link->src[i] << 1 : 0x20 << 1);
        }
        mac_hdr->dest_ssid = AX25_SSID(link->dest_ssid);
        mac_hdr->src_ssid = AX25_SSID(link->src_ssid) | AX25_SSID_EXT;
        mac_hdr->control = link->control;
        mac_hdr->sid = link->sid;
    }

    return mac_hdr;
}

/** @} */
