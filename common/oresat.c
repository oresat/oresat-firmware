#include "oresat.h"
#include "CANopen.h"
#include "can_threads.h"

typedef struct {
    void *wa;
    size_t wa_size;
    tprio_t prio;
    tfunc_t thread_func;
    void *arg;
} worker_thread_t;

worker_thread_t worker_threads[ORESAT_MAX_THREADS];
uint32_t num_workers = 0;

int reg_worker(void *wa, size_t wa_size, tprio_t prio, tfunc_t thread_func, void *arg)
{
    if (num_workers == ORESAT_MAX_THREADS) {
        return -1;
    }

    worker_threads[num_workers].wa = wa;
    worker_threads[num_workers].wa_size = wa_size;
    worker_threads[num_workers].prio = prio;
    worker_threads[num_workers].thread_func = thread_func;
    worker_threads[num_workers].arg = arg;

    return num_workers++;
}

void oresat_init(uint8_t node_id)
{
    /*uint8_t obr_node_id = (FLASH->OBR & FLASH_OBR_DATA0) >> FLASH_OBR_DATA0_Pos;*/
    uint8_t obr_node_id = 0xFF;
    CO_ReturnError_t err;

    //If node ID is not overridden, set node ID
    if (node_id == ORESAT_DEFAULT_ID) {
        //TODO: If node ID is not set or is invalid, get new node ID
        if (obr_node_id  == 0xFF) {
            obr_node_id = 0x7F;
        }
        node_id = obr_node_id;
    }

    //TODO: If the node_id is out of range, get new node ID
    if (node_id > 0x7F)
        node_id = 0x7F;

    //Initialize CAN Subsystem
    err = CO_init((uint32_t)&CAND1, node_id, 1000);
    if (err != CO_ERROR_NO) {
        CO_errorReport(CO->em, CO_EM_MEMORY_ALLOCATION_ERROR, CO_EMC_SOFTWARE_INTERNAL, err);
    }

    return;
}

void oresat_start(void)
{
    uint32_t i;

    chThdCreateStatic(can_rx_wa, sizeof(can_rx_wa), HIGHPRIO, can_rx, &CO->CANmodule[0]);
    chThdCreateStatic(can_tx_wa, sizeof(can_tx_wa), HIGHPRIO, can_tx, &CO->CANmodule[0]);

    CO_CANsetNormalMode(CO->CANmodule[0]);

    for (i = 0; i < num_workers; i++) {
        chThdCreateStatic(worker_threads[i].wa, worker_threads[i].wa_size, worker_threads[i].prio, worker_threads[i].thread_func, worker_threads[i].arg);
    }

    while (true) {
        chThdSleepMilliseconds(1000);
    }
}
