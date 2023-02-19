#include "301/CO_ODinterface.h"
#include "CANopen.h"
#include "node_mgr.h"
#include "rtc.h"

ODR_t OD_read_2010(OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead)
{
    time_scet_t scet;

    if (buf == NULL || stream == NULL || countRead == NULL) {
        return ODR_DEV_INCOMPAT;
    }

    if (count > stream->dataLength) {
        count = stream->dataLength;
    }

    if (stream->subIndex == 0) {
        rtcGetTimeSCET(&scet);
        memcpy(buf, &scet, stream->dataLength);
    }

    *countRead = count;
    return ODR_OK;
}

ODR_t OD_write_2010(OD_stream_t *stream, const void *buf, OD_size_t count, OD_size_t *countWritten)
{
    time_scet_t scet;

    if (buf == NULL || stream == NULL || countWritten == NULL) {
        return ODR_DEV_INCOMPAT;
    }

    if (stream->subIndex == 0) {
        scet.raw = *(uint64_t *)stream->object;
        rtcSetTimeSCET(&scet);
    }

    *countWritten = count;
    return ODR_OK;
}

ODR_t OD_read_2011(OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead)
{
    time_utc_t utc;

    if (buf == NULL || stream == NULL || countRead == NULL) {
        return ODR_DEV_INCOMPAT;
    }

    if (count > stream->dataLength) {
        count = stream->dataLength;
    }

    if (stream->subIndex == 0) {
        rtcGetTimeUTC(&utc);
        memcpy(buf, &utc, stream->dataLength);
    }

    *countRead = count;
    return ODR_OK;
}

ODR_t OD_write_2011(OD_stream_t *stream, const void *buf, OD_size_t count, OD_size_t *countWritten)
{
    time_utc_t utc;

    if (buf == NULL || stream == NULL || countWritten == NULL) {
        return ODR_DEV_INCOMPAT;
    }
    
    if (stream->subIndex == 0) {
        utc.raw = *(uint64_t *)stream->object;
        rtcSetTimeUTC(&utc);
    }

    *countWritten = count;
    return ODR_OK;
}

static OD_extension_t scet_extension = {
    .object = NULL,
    .read = OD_read_2010,
    .write = OD_write_2010,
};

static OD_extension_t utc_extension = {
    .object = NULL,
    .read = OD_read_2011,
    .write = OD_write_2011,
};

void ecss_extension_init(void)
{
    OD_entry_t *scet_entry = OD_find(OD, 0x2010);
    OD_entry_t *utc_entry = OD_find(OD, 0x2011);

    OD_extension_init(scet_entry, &scet_extension);
    OD_extension_init(utc_entry, &utc_extension);
}
