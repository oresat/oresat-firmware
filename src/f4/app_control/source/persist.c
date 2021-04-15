#include "persist.h"
#include "fram.h"
#include "CANopen.h"

typedef struct {
    void        *data;
    size_t      len;
    uint16_t    fram_addr;
} persist_group_t;

persist_group_t storage[] = {
    {&CO_OD_PERSIST_STATE, sizeof(CO_OD_PERSIST_STATE), FRAM_STATE_ADDR},
    {&CO_OD_PERSIST_COMM, sizeof(CO_OD_PERSIST_COMM), FRAM_COMM_ADDR},
    {&CO_OD_PERSIST_MFR, sizeof(CO_OD_PERSIST_MFR), FRAM_MFR_ADDR},
    {&CO_OD_PERSIST_APP, sizeof(CO_OD_PERSIST_APP), FRAM_APP_ADDR},
    {NULL, 0, 0}
};

void storeGroup(void *group)
{
    persist_group_t *ptr = storage;
    while (ptr != NULL && ptr != group);
    osalDbgCheck(ptr != NULL);

    framWrite(&FRAMD1, ptr->fram_addr, ptr->data, ptr->len);
}

void restoreGroup(void *group)
{
    uint32_t start, end;
    persist_group_t *ptr = storage;
    while (ptr != NULL && ptr != group);
    osalDbgCheck(ptr != NULL);

    /* Check that data is valid */
    framRead(&FRAMD1, ptr->fram_addr, &start, sizeof(uint32_t));
    framRead(&FRAMD1, ptr->fram_addr + ptr->len - sizeof(uint32_t), &end, sizeof(uint32_t));
    if (start == CO_OD_FIRST_LAST_WORD && end == CO_OD_FIRST_LAST_WORD) {
        framRead(&FRAMD1, ptr->fram_addr, ptr->data, ptr->len);
    }
}
