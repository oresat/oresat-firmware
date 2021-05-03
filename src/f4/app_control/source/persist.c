#include "persist.h"
#include "fram.h"
#include "CANopen.h"

typedef struct {
    void        *data;
    void        *last_word;
    size_t      len;
    uint16_t    fram_addr;
} persist_group_t;

persist_group_t storage[] = {
    {&CO_OD_PERSIST_STATE, &CO_OD_PERSIST_STATE.LastWord, sizeof(CO_OD_PERSIST_STATE), FRAM_STATE_ADDR},
    {&CO_OD_PERSIST_COMM, &CO_OD_PERSIST_COMM.LastWord, sizeof(CO_OD_PERSIST_COMM), FRAM_COMM_ADDR},
    {&CO_OD_PERSIST_MFR, &CO_OD_PERSIST_MFR.LastWord, sizeof(CO_OD_PERSIST_MFR), FRAM_MFR_ADDR},
    {&CO_OD_PERSIST_APP, &CO_OD_PERSIST_APP.LastWord, sizeof(CO_OD_PERSIST_APP), FRAM_APP_ADDR},
    {NULL, NULL, 0, 0}
};

void storeGroup(void *group)
{
    persist_group_t *ptr = storage;
    while (ptr->data != NULL && ptr->data != group)
        ptr++;
    osalDbgCheck(ptr != NULL);

    framWrite(&FRAMD1, ptr->fram_addr, ptr->data, ptr->len);
}

void restoreGroup(void *group)
{
    uint32_t first_word, last_word;
    persist_group_t *ptr = storage;
    while (ptr->data != NULL && ptr->data != group)
        ptr++;
    osalDbgCheck(ptr != NULL);

    /* Check that data is valid */
    framRead(&FRAMD1, ptr->fram_addr, &first_word, sizeof(uint32_t));
    framRead(&FRAMD1, ptr->fram_addr + (ptr->last_word - ptr->data), &last_word, sizeof(uint32_t));
    if (first_word == CO_OD_FIRST_LAST_WORD && last_word == CO_OD_FIRST_LAST_WORD) {
        framRead(&FRAMD1, ptr->fram_addr, ptr->data, ptr->len);
    }
}
