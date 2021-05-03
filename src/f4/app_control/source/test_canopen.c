#include <stdlib.h>
#include "test_canopen.h"
#include "CO_master.h"
#include "chprintf.h"

/*===========================================================================*/
/* Support functions                                                         */
/*===========================================================================*/
/*
bool sdo_file_cb(sdocli_t *sdocli, CO_SDO_return_t ret, CO_SDO_abortCode_t *abort_code, void *arg)
{
    struct cb_arg *data = arg;
    ssize_t size, space;

    if (ret < 0) {
        chprintf((BaseSequentialStream*)&SD3, "Error in SDO transfer. Ret: %d Abort: %X", ret, *abort_code);
        return true;
    }

    if (sdocli->state == SDOCLI_ST_DOWNLOAD) {
        space = CO_fifo_getSpace(&sdocli->sdo_c->bufFifo);
        do {
            size = file_read(&FSD1, data->file, data->buf, lfs_min(space, BUF_SIZE));
            if (size < 0) {
                *abort_code = CO_SDO_AB_NO_DATA;
                return true;
            }
            CO_SDOclientDownloadBufWrite(sdocli->sdo_c, data->buf, size);
        } while (size && (space -= size));
    } else if (sdocli->state == SDOCLI_ST_UPLOAD) {
        if (ret == CO_SDO_RT_uploadDataBufferFull || ret == CO_SDO_RT_ok_communicationEnd) {
            do {
                size = CO_SDOclientUploadBufRead(sdocli->sdo_c, data->buf, BUF_SIZE);
                file_write(&FSD1, data->file, data->buf, size);
            } while (size);
        }
    }

    return false;
}
*/

/*===========================================================================*/
/* OreSat CAN Bus NMT                                                        */
/*===========================================================================*/
void cmd_nmt(BaseSequentialStream *chp, int argc, char *argv[])
{
    CO_ReturnError_t err;
    uint8_t node_id = 0;

    if (argc < 1) {
        goto nmt_usage;
    }

    if (argc > 1) {
        node_id = strtoul(argv[1], NULL, 0);
    }

    if (!strcmp(argv[0], "op")) {
        err = CO_NMT_sendCommand(CO->NMT, CO_NMT_ENTER_OPERATIONAL, node_id);
    } else if (!strcmp(argv[0], "preop")) {
        err = CO_NMT_sendCommand(CO->NMT, CO_NMT_ENTER_PRE_OPERATIONAL, node_id);
    } else if (!strcmp(argv[0], "stop")) {
        err = CO_NMT_sendCommand(CO->NMT, CO_NMT_ENTER_STOPPED, node_id);
    } else if (!strcmp(argv[0], "resetcomms")) {
        err = CO_NMT_sendCommand(CO->NMT, CO_NMT_RESET_COMMUNICATION, node_id);
    } else if (!strcmp(argv[0], "resetnode")) {
        err = CO_NMT_sendCommand(CO->NMT, CO_NMT_RESET_NODE, node_id);
    } else {
        goto nmt_usage;
    }
    if (err != CO_ERROR_NO) {
        chprintf(chp, "Error executing NMT command: %d\r\n", err);
    }
    return;

nmt_usage:
    chprintf(chp,  "Usage: nmt <command> <node_id>\r\n"
                   "    op:         Set device operational\r\n"
                   "    preop:      Set device pre-operational\r\n"
                   "    stop:       Stop device\r\n"
                   "    resetcomms: Reset CAN communications on device\r\n"
                   "    resetnode:  Reset device\r\n"
                   "\r\n");
    return;
}

/*===========================================================================*/
/* OreSat CAN Bus SDO Client                                                 */
/*===========================================================================*/
/*
void cmd_sdo(BaseSequentialStream *chp, int argc, char *argv[])
{
    struct cb_arg data;
    thread_t *tp;
    int err = 0;
    uint16_t index = 0;
    uint8_t node_id = 0, subindex = 0;
    size_t size = 0;

    if (argc < 5 || (argv[0][0] != 'r' && argv[0][0] != 'w')) {
        goto sdo_usage;
    }

    node_id = strtoul(argv[1], NULL, 0);
    index = strtoul(argv[2], NULL, 0);
    subindex = strtoul(argv[3], NULL, 0);

    data.file = file_open(&FSD1, argv[4], LFS_O_RDWR | LFS_O_CREAT);
    if (data.file == NULL) {
        chprintf(chp, "Error in file open: %d\r\n", err);
        goto sdo_usage;
    }
    if (argv[0][0] == 'w') {
        size = file_size(&FSD1, data.file);
    }

    chprintf(chp, "Initiating transfer... ");
    tp = sdo_transfer(argv[0][0], node_id, index, subindex, size, sdo_file_cb, &data);
    if (tp == NULL) {
        chprintf(chp, "Failed to initiate transfer\r\n");
        return;
    }
    chThdWait(tp);
    file_close(&FSD1, data.file);
    chprintf(chp, "Done!\r\n");
    return;

sdo_usage:
    chprintf(chp, "Usage: sdo (r)ead|(w)rite <node_id> <index> <subindex> <filename>\r\n");
    return;
}
*/

