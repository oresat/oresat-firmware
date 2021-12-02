/**
 * @file    radio.c
 * @brief   OreSat radio support library.
 *
 * @addtogroup RADIO
 * @{
 */
#include <string.h>
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

/* Frame buffer allocation pool */
objects_fifo_t rx_fifo;
static msg_t rx_fifo_msgs[RADIO_FIFO_COUNT];
static fb_t rx_fifo_buf[RADIO_FIFO_COUNT];
objects_fifo_t tx_fifo;
static msg_t tx_fifo_msgs[RADIO_FIFO_COUNT];
static fb_t tx_fifo_buf[RADIO_FIFO_COUNT];

/*===========================================================================*/
/* Local functions.                                                          */
/*===========================================================================*/

/*===========================================================================*/
/* Interface implementation.                                                 */
/*===========================================================================*/

fb_t *__fb_alloc(size_t len, void *arg) {
    (void)len;
    osalDbgCheck(arg != NULL);
    objects_fifo_t *fifo = arg;
    fb_t *fb = chFifoTakeObjectTimeout(fifo, TIME_INFINITE);
    memset(fb, 0, sizeof(fb_t));
    return fb;
}

void __fb_free(fb_t *fb, void *arg) {
    osalDbgCheck(fb != NULL && arg != NULL);
    objects_fifo_t *fifo = arg;
    chFifoReturnObject(fifo, fb);
}

/*===========================================================================*/
/* Exported functions.                                                       */
/*===========================================================================*/

void radio_init(void)
{
    /* Initialize frame buffer FIFO */
    chFifoObjectInit(&rx_fifo, sizeof(fb_t), RADIO_FIFO_COUNT, rx_fifo_buf, rx_fifo_msgs);
    chFifoObjectInit(&tx_fifo, sizeof(fb_t), RADIO_FIFO_COUNT, tx_fifo_buf, tx_fifo_msgs);

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

void pdu_send(fb_t *fb, void *arg)
{
    osalDbgCheck(fb != NULL && arg != NULL);
    objects_fifo_t *fifo = arg;
    chFifoSendObject(fifo, fb);
}

void pdu_send_ahead(fb_t *fb, void *arg)
{
    osalDbgCheck(fb != NULL && arg != NULL);
    objects_fifo_t *fifo = arg;
    chFifoSendObjectAhead(fifo, fb);
}

fb_t *pdu_recv(void *arg)
{
    osalDbgCheck(arg != NULL);
    fb_t *fb;
    objects_fifo_t *fifo = arg;
    if (chFifoReceiveObjectTimeout(fifo, (void**)&fb, TIME_MS2I(1000)) != MSG_OK) {
        fb = NULL;
    }
    return fb;
}

/** @} */
