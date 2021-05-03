/**
 * @file    frame_buf.h
 * @brief   Frame buffer support library.
 *
 * @addtogroup CCSDS
 * @{
 */
#ifndef _FRAME_BUF_H_
#define _FRAME_BUF_H_

#include <stdlib.h>
#include <stdint.h>

/*===========================================================================*/
/* Constants.                                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Pre-compile time settings.                                                */
/*===========================================================================*/

#if !defined(FB_MAX_LEN) || defined(__DOXYGEN__)
#define FB_MAX_LEN                          4096U
#endif

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Data structures and types.                                                */
/*===========================================================================*/

/**
 * @name    Frame buffer data structures and types.
 * @{
 */

/**
 * @brief   Frame buffer structure
 */
typedef struct {
    /* Application Layer */
    void            *data_arg;      /* Application layer argument           */
    void            *data_ptr;      /* Application layer data pointer       */
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
    void            *phy_tx;        /* Physical layer TX device pointer     */
    void            *phy_rx;        /* Physical layer RX device pointer     */
    /* Buffer */
    size_t          max_len;        /* Maximum size of frame buffer         */
    size_t          len;            /* Buffer length                        */
    uint8_t         *head;          /* Head of frame buffer                 */
    uint8_t         *data;          /* Start of frame data                  */
    uint8_t         *tail;          /* End of frame data                    */
    uint8_t         *end;           /* End of frame buffer                  */
    uint8_t         buf[FB_MAX_LEN];/* The actual buffer                    */
} fb_t;

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

fb_t *__fb_alloc(void);
void __fb_free(fb_t *fb);
fb_t *fb_alloc(size_t len);
void fb_free(fb_t *fb);

void __fb_post(fb_t *fb);
void __fb_post_first(fb_t *fb);
fb_t *__fb_get(void);
void fb_post(fb_t *fb);
void fb_post_first(fb_t *fb);
fb_t *fb_get(void);

void fb_reserve(fb_t *fb, size_t len);
void *fb_put(fb_t *fb, size_t len);
void *fb_push(fb_t *fb, size_t len);
void *fb_pull(fb_t *fb, size_t len);
void fb_trim(fb_t *fb, size_t len);

size_t fb_headroom(fb_t *fb);
size_t fb_tailroom(fb_t *fb);

#ifdef __cplusplus
}
#endif

#endif /* _FRAME_BUF_H_ */

/** @} */
