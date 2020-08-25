#include "oresat.h"
#include "CO_master.h"

#define SDOCLI_TIMEOUT 1000

sdocli_t sdo_client[CO_NO_SDO_CLIENT];

/* CANopen SDO client thread */
THD_FUNCTION(sdo_client_thd, arg)
{
    sdocli_t *sdocli = arg;
    CO_SDO_return_t ret = CO_SDO_RT_waitingResponse;
    CO_SDO_abortCode_t abort_code = CO_SDO_AB_NONE;
    systime_t prev_time;
    bool_t abort = false;

    /* Sanity check on arguments */
    chDbgCheck(sdocli != NULL && sdocli->sdo_c != NULL && sdocli->buf_cb != NULL);

    /* Register the callback function to wake up thread when message received */
    CO_SDOclient_initCallbackPre(sdocli->sdo_c, chThdGetSelfX(), process_cb);

    prev_time = chVTGetSystemTime();
    while (!abort && ret > 0) {
        uint32_t timeout = ((typeof(timeout))-1);

        /* Check if thread should terminate */
        if (chThdShouldTerminateX()) {
            abort = true;
            abort_code = CO_SDO_AB_GENERAL;
        }

        if (sdocli->state == SDOCLI_ST_DOWNLOAD) {
            /* Download (write) operation */
            /* Fill buffer */
            abort = sdocli->buf_cb(sdocli, ret, &abort_code, sdocli->buf_cb_arg);

            /* While we have transmit buffers available, fill them */
            do {
                ret = CO_SDOclientDownload(sdocli->sdo_c, TIME_I2US(chVTTimeElapsedSinceX(prev_time)),
                        abort, &abort_code, &sdocli->size_transferred, &timeout);
            } while (ret == CO_SDO_RT_blockDownldInProgress);
        } else if (sdocli->state == SDOCLI_ST_UPLOAD) {
            /* Upload (read) operation */
            ret = CO_SDOclientUpload(sdocli->sdo_c, TIME_I2US(chVTTimeElapsedSinceX(prev_time)),
                    &abort_code, &sdocli->size_transferred, &sdocli->size_indicated, &timeout);

            /* Empty buffer if it is full */
            if (ret == CO_SDO_RT_uploadDataBufferFull) {
                sdocli->buf_cb(sdocli, ret, &abort_code, sdocli->buf_cb_arg);
            }
        } else {
            break;
        }

        prev_time = chVTGetSystemTime();
        chEvtWaitAnyTimeout(ALL_EVENTS, TIME_US2I(timeout));
    }

    /* Final call to buffer callback */
    sdocli->buf_cb(sdocli, ret, &abort_code, sdocli->buf_cb_arg);

    /* Clear the callbacks for the SDO client object, free the client, and terminate */
    CO_SDOclient_initCallbackPre(sdocli->sdo_c, NULL, NULL);
    sdocli->state = SDOCLI_ST_IDLE;
    sdocli->size_transferred = 0;
    sdocli->size_indicated = 0;
    sdocli->buf_cb = NULL;
    sdocli->buf_cb_arg = NULL;
    chSemSignal(&sdocli->sem);
    chThdExit(MSG_OK);
}

void sdo_init(void)
{
    for (int i = 0; i < CO_NO_SDO_CLIENT; i++) {
        sdo_client[i].tp = NULL;
        chSemObjectInit(&sdo_client[i].sem, 1);
        sdo_client[i].sdo_c = CO->SDOclient[i];
        sdo_client[i].state = SDOCLI_ST_IDLE;
        sdo_client[i].size_transferred = 0;
        sdo_client[i].size_indicated = 0;
        sdo_client[i].buf_cb = NULL;
        sdo_client[i].buf_cb_arg = NULL;
    }
}

thread_t *sdo_transfer(char type, uint8_t node_id, uint16_t index, uint8_t subindex, size_t size, bool (*buf_cb)(struct sdocli *sdocli, CO_SDO_return_t ret, CO_SDO_abortCode_t *abort_code, void *arg), void *buf_cb_arg)
{
    int i;

    /* Attempt to acquire an SDO client object for the transfer */
    for (i = 0; i < CO_NO_SDO_CLIENT; i++) {
        if (chSemWaitTimeout(&sdo_client[i].sem, TIME_IMMEDIATE) == MSG_OK)
            break;
    }
    if (i == CO_NO_SDO_CLIENT) {
        /* Failed to acquire a free SDO client object */
        return NULL;
    }

    /* Set up SDO client object for transaction */
    CO_SDOclient_setup(sdo_client[i].sdo_c, 0, 0, node_id);

    /* Type is either (w)rite (download) or (r)ead (upload). Set state accordingly */
    if (type == 'w') {
        if (CO_SDOclientDownloadInitiate(sdo_client[i].sdo_c, index, subindex, size, SDOCLI_TIMEOUT, true) != CO_SDO_RT_ok_communicationEnd) {
            chSemSignal(&sdo_client[i].sem);
            return NULL;
        }
        sdo_client[i].state = SDOCLI_ST_DOWNLOAD;
    } else if (type == 'r') {
        if (CO_SDOclientUploadInitiate(sdo_client[i].sdo_c, index, subindex, SDOCLI_TIMEOUT, true) != CO_SDO_RT_ok_communicationEnd) {
            chSemSignal(&sdo_client[i].sem);
            return NULL;
        }
        sdo_client[i].state = SDOCLI_ST_UPLOAD;
    } else {
        /* Invalid operation */
        chSemSignal(&sdo_client[i].sem);
        return NULL;
    }

    sdo_client[i].size_indicated = size;
    sdo_client[i].buf_cb = buf_cb;
    sdo_client[i].buf_cb_arg = buf_cb_arg;

    sdo_client[i].tp = chThdCreateFromHeap(NULL, 0x1000, "SDO Client", HIGHPRIO-1, sdo_client_thd, &sdo_client[i]);

    return sdo_client[i].tp;
}
