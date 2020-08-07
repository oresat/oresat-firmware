#include "oresat.h"
#include "CANopen.h"
#include "CO_master.h"

typedef enum {
    SDOCLI_ST_IDLE,
    SDOCLI_ST_DOWNLOAD,
    SDOCLI_ST_UPLOAD
} sdocli_state_t;

typedef struct {
    thread_t           *tp;
    CO_SDOclient_t     *sdo_c;
    sdocli_state_t      state;
} sdocli_t;

SEMAPHORE_DECL(sdocli_sem, CO_NO_SDO_CLIENT);
sdocli_t sdo_client[CO_NO_SDO_CLIENT];

/* CANopen SDO client thread */
THD_FUNCTION(sdo_client_thd, arg)
{
    sdocli_t *sdocli = arg;
    systime_t prev_time;

    /* Register the callback function to wake up thread when message received */
    CO_SDOclient_initCallbackPre(sdocli->sdo_c, chThdGetSelfX(), process_cb);

    prev_time = chVTGetSystemTime();
    while (!chThdShouldTerminateX()) {
        uint32_t timeout = ((typeof(timeout))-1);
        CO_SDO_return_t ret;
        CO_SDO_abortCode_t abort_code;
        size_t size_transferred, size_indicated;
        bool_t abort = false;

        if (sdocli->state == SDOCLI_ST_DOWNLOAD) {
            ret = CO_SDOclientDownload(sdocli->sdo_c, TIME_I2US(chVTTimeElapsedSinceX(prev_time)),
                    abort, &abort_code, &size_transferred, &timeout);
        } else if (sdocli->state == SDOCLI_ST_UPLOAD) {
            ret = CO_SDOclientUpload(sdocli->sdo_c, TIME_I2US(chVTTimeElapsedSinceX(prev_time)),
                    &abort_code, &size_transferred, &size_indicated, &timeout);
        } else {
            break;
        }

        prev_time = chVTGetSystemTime();
        chEvtWaitAnyTimeout(ALL_EVENTS, TIME_US2I(timeout));
    }
    CO_SDOclient_initCallbackPre(sdocli->sdo_c, NULL, NULL);
    chThdExit(MSG_OK);
}

thread_t *sdo_transfer(void)
{
    int i;

    chSysLock();
    if (chSemWaitS(&sdocli_sem) != MSG_OK) {
        return NULL;
    }
    i = chSemGetCounterI(&sdocli_sem);
    chSysUnlock();

    sdo_client[i].tp = chThdCreateFromHeap(NULL, 0x1000, "SDO Client", HIGHPRIO-1, sdo_client_thd, &sdo_client[i]);

    return sdo_client[i].tp;
}
