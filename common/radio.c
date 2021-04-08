/**
 * @file    radio.c
 * @brief   OreSat radio support library.
 *
 * @addtogroup RADIO
 * @{
 */
#include "ch.h"
#include "hal.h"
#include "radio.h"

/*===========================================================================*/
/* Local definitions.                                                        */
/*===========================================================================*/

/*===========================================================================*/
/* Exported variables.                                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Local variables and types.                                                */
/*===========================================================================*/

static objects_fifo_t fb_fifo;
static msg_t fb_fifo_msgs[RADIO_FB_COUNT];
static fb_t fb_fifo_buf[RADIO_FB_COUNT];

/*===========================================================================*/
/* Local functions.                                                          */
/*===========================================================================*/

/*===========================================================================*/
/* Interface implementation.                                                 */
/*===========================================================================*/

fb_t *__fb_alloc(void) {
    return chFifoTakeObjectTimeout(&fb_fifo, TIME_INFINITE);
}

void __fb_free(fb_t *fb) {
    chFifoReturnObject(&fb_fifo, fb);
}

void __fb_post(fb_t *fb) {
    chFifoSendObject(&fb_fifo, fb);
}

void __fb_post_first(fb_t *fb) {
    chFifoSendObjectAhead(&fb_fifo, fb);
}

fb_t *__fb_get(void) {
    fb_t *fb;
    if (chFifoReceiveObjectTimeout(&fb_fifo, (void**)&fb, TIME_MS2I(1000)) != MSG_OK) {
        fb = NULL;
    }
    return fb;
}

/*===========================================================================*/
/* Exported functions.                                                       */
/*===========================================================================*/

void radio_init(void)
{
    /* Initialize frame buffer FIFO */
    chFifoObjectInit(&fb_fifo, sizeof(fb_t), RADIO_FB_COUNT, fb_fifo_buf, fb_fifo_msgs);

    /* Initialize radio systems */
    for (int i = 0; radio_devices[i].devp != NULL; i++) {
        ax5043ObjectInit(radio_devices[i].devp);
    }
    for (int i = 0; synth_devices[i].devp != NULL; i++) {
        si41xxObjectInit(synth_devices[i].devp);
    }
}

void radio_start(void)
{
    /* Start radio systems */
    for (int i = 0; radio_devices[i].devp != NULL; i++) {
        ax5043Start(radio_devices[i].devp, radio_devices[i].cfgp);
    }
    for (int i = 0; synth_devices[i].devp != NULL; i++) {
        si41xxStart(synth_devices[i].devp, synth_devices[i].cfgp);
    }
}

void radio_stop(void)
{
    for (int i = 0; radio_devices[i].devp != NULL; i++) {
        ax5043Stop(radio_devices[i].devp);
    }
    for (int i = 0; synth_devices[i].devp != NULL; i++) {
        si41xxStop(synth_devices[i].devp);
    }
}

/** @} */
