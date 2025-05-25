#include "version.h"
#include "301/CO_ODinterface.h"
#include "OD.h"
#include <string.h>

static ODR_t version_read(OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead);

static OD_extension_t ext = {
    .object = NULL,
    .read = version_read,
    .write = OD_writeOriginal,
};

void version_extension_init(void) {
    OD_entry_t *entry = OD_find(OD, OD_INDEX_VERSIONS);
    if (entry != NULL) {
        OD_extension_init(entry, &ext);
    }
}

static ODR_t version_read(OD_stream_t *stream, void *buf, OD_size_t count, OD_size_t *countRead) {
    ODR_t r = ODR_DATA_LOC_CTRL;
    void *p = NULL;
    switch (stream->subIndex) {
    case OD_SUBINDEX_VERSIONS_HW_VERSION:
        memcpy(buf, BOARD, strlen(BOARD) + 1);
        if (p) {
            *countRead = strlen(BOARD) + 1;
            r = ODR_OK;
        }
        break;
    case OD_SUBINDEX_VERSIONS_FW_VERSION:
        p = memcpy(buf, FW_VERSION, strlen(FW_VERSION) + 1);
        if (p) {
            *countRead = strlen(FW_VERSION) + 1;
            r = ODR_OK;
        }
        break;
    default:
        r = OD_readOriginal(stream, buf, count, countRead);
        break;
    }
    return r;
}
