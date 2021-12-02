/**
 * @file    radio.h
 * @brief   OreSat radio support library.
 *
 * @addtogroup RADIO
 * @ingroup ORESAT
 * @{
 */
#ifndef _RADIO_H_
#define _RADIO_H_

#include "ch.h"
#include "hal.h"
#include "ax5043.h"
#include "si41xx.h"
#include "frame_buf.h"

/*===========================================================================*/
/* Constants.                                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Pre-compile time settings.                                                */
/*===========================================================================*/

#if !defined(RADIO_FIFO_COUNT) || defined(__DOXYGEN__)
#define RADIO_FIFO_COUNT                    8U
#endif

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Data structures and types.                                                */
/*===========================================================================*/

typedef struct {
    SI41XXDriver            *devp;
    SI41XXConfig            *cfgp;
    const char              *name;
} synth_dev_t;

typedef struct {
    AX5043Driver            *devp;
    const AX5043Config      *cfgp;
    const char              *name;
} radio_dev_t;

typedef struct {
    AX5043Driver            *devp;
    const ax5043_profile_t  *profile;
    const char              *name;
} radio_cfg_t;

/*===========================================================================*/
/* Macros.                                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

extern synth_dev_t synth_devices[];
extern radio_dev_t radio_devices[];
extern radio_cfg_t radio_cfgs[];
extern objects_fifo_t rx_fifo;
extern objects_fifo_t tx_fifo;

void radio_init(void);
void radio_start(void);
void radio_stop(void);

void pdu_send(fb_t *fb, void *arg);
void pdu_send_ahead(fb_t *fb, void *arg);
fb_t *pdu_recv(void *arg);

#ifdef __cplusplus
}
#endif

#endif /* _RADIO_H_ */

/** @} */
