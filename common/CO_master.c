#include "ch.h"
#include "CO_master.h"

int sdo_upload(
        CO_SDOclient_t *SDOclient,
        uint8_t         node_id,
        uint16_t        index,
        uint8_t         subindex,
        void           *data,
        uint32_t        max_len,
        uint32_t       *ret_len,
        uint32_t       *abrt_code,
        uint16_t        timeout,
        bool            block)
{
        CO_SDOclient_return_t ret;
        systime_t prev_time, cur_time, diff_time;

        if (CO_SDOclient_setup(SDOclient, 0, 0, node_id) != CO_SDOcli_ok_communicationEnd)
            return 1;
        if (CO_SDOclientUploadInitiate(SDOclient, index, subindex, data, max_len, timeout, block) != CO_SDOcli_ok_communicationEnd)
            return 1;

        prev_time = chVTGetSystemTimeX();
        do {
            diff_time = chTimeDiffX(prev_time, cur_time = chVTGetSystemTimeX());
            prev_time = cur_time;
            ret = CO_SDOclientUpload(SDOclient, chTimeI2MS(diff_time), ret_len, abrt_code, NULL);
            chThdSleepMilliseconds(10);
        } while (ret > 0);
        CO_SDOclientClose(SDOclient);

        return 0;
}

int sdo_download(
        CO_SDOclient_t *SDOclient,
        uint8_t         node_id,
        uint16_t        index,
        uint8_t         subindex,
        void           *data,
        uint32_t        len,
        uint32_t       *abrt_code,
        uint16_t        timeout,
        bool            block)
{
    CO_SDOclient_return_t ret;
    systime_t prev_time, cur_time, diff_time;

    if (CO_SDOclient_setup(SDOclient, 0, 0, node_id) != CO_SDOcli_ok_communicationEnd)
        return 1;
    if (CO_SDOclientDownloadInitiate(SDOclient, index, subindex, data, len, timeout, block) != CO_SDOcli_ok_communicationEnd)
        return 1;

    prev_time = chVTGetSystemTimeX();
    do {
        diff_time = chTimeDiffX(prev_time, cur_time = chVTGetSystemTimeX());
        prev_time = cur_time;
        ret = CO_SDOclientDownload(SDOclient, chTimeI2US(diff_time), abrt_code, NULL);
        chThdSleepMilliseconds(5);
    } while (ret > 0);
    CO_SDOclientClose(SDOclient);

    return 0;
}
