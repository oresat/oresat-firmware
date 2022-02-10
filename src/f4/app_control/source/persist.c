#include <stdlib.h>
#include "persist.h"
#include "fram.h"
#include "crc.h"
#include "CANopen.h"
#include "OD.h"

typedef struct {
    uint32_t crc;
    uint8_t data[];
} buf_t;

typedef struct {
    void        *data;
    size_t      len;
    uint16_t    fram_addr;
} persist_group_t;

persist_group_t storage[] = {
    {&OD_PERSIST_KEYS, sizeof(OD_PERSIST_KEYS), FRAM_KEYS_ADDR},
    {&OD_PERSIST_STATE, sizeof(OD_PERSIST_STATE), FRAM_STATE_ADDR},
    {&OD_PERSIST_COMM, sizeof(OD_PERSIST_COMM), FRAM_COMM_ADDR},
    {&OD_PERSIST_MFR, sizeof(OD_PERSIST_MFR), FRAM_MFR_ADDR},
    {&OD_PERSIST_APP, sizeof(OD_PERSIST_APP), FRAM_APP_ADDR},
    {NULL, 0, 0}
};

void storeGroup(void *group)
{
    persist_group_t *ptr = storage;
    while (ptr->data != NULL && ptr->data != group)
        ptr++;
    osalDbgCheck(ptr != NULL);

    /* Checksum data and store */
    buf_t *buf = malloc(sizeof(buf_t) + ptr->len);
    memcpy(buf->data, ptr->data, ptr->len);
    buf->crc = crc32(buf->data, ptr->len, 0);
    framWrite(&FRAMD1, ptr->fram_addr, buf, sizeof(buf) + ptr->len);
    free(buf);
}

void restoreGroup(void *group)
{
    persist_group_t *ptr = storage;
    while (ptr->data != NULL && ptr->data != group)
        ptr++;
    osalDbgCheck(ptr != NULL);

    /* Check that data is valid and restore */
    buf_t *buf = malloc(sizeof(buf_t) + ptr->len);
    framRead(&FRAMD1, ptr->fram_addr, buf, sizeof(buf) + ptr->len);
    if (buf->crc == crc32(buf->data, ptr->len, 0)) {
        memcpy(ptr->data, buf->data, ptr->len);
    }
    free(buf);
}
