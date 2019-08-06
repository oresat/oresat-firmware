#include "oresat.h"
#include "CANopen.h"
#include "can_threads.h"

thread_descriptor_t workers[ORESAT_MAX_THREADS];
uint32_t num_workers = 0;

int reg_worker(void *wa, size_t wa_size, tprio_t prio, tfunc_t thread_func, void *arg)
{
    if (num_workers == ORESAT_MAX_THREADS) {
        return -1;
    }

    /* TODO: Register worker threads */

    return num_workers++;
}

void oresat_init(uint8_t node_id)
{
    /*
     * System initializations.
     * - HAL initialization, this also initializes the configured device drivers
     *   and performs the board-specific initializations.
     * - Kernel initialization, the main() function becomes a thread and the
     *   RTOS is active.
     */
    halInit();
    chSysInit();

    /* If node ID is not overridden, set node ID from user data byte */
    if (node_id == ORESAT_DEFAULT_ID) {
        node_id = (FLASH->OBR & FLASH_OBR_DATA0) >> FLASH_OBR_DATA0_Pos;
    }

    //TODO: If node ID is invalid, get new node ID
    if (node_id > 0x7F) {
        node_id = 0x7F;
    }

    return;
}

void oresat_start(void)
{
    CO_NMT_reset_cmd_t reset = CO_RESET_NOT;
    uint32_t i;

    while (reset != CO_RESET_APP) {
        CO_ReturnError_t err;

        /* Initialize CAN Subsystem */
        /*err = CO_init((uint32_t)&CAND1, node_id, 1000);*/
        /*if (err != CO_ERROR_NO) {*/
            /*while(1);*/
            /*CO_errorReport(CO->em, CO_EM_MEMORY_ALLOCATION_ERROR, CO_EMC_SOFTWARE_INTERNAL, err);*/
        /*}*/

        /*chThdCreateStatic(can_rx_wa, sizeof(can_rx_wa), HIGHPRIO, can_rx, &CO->CANmodule[0]);*/
        /*chThdCreateStatic(can_tx_wa, sizeof(can_tx_wa), HIGHPRIO, can_tx, &CO->CANmodule[0]);*/

        /*CO_CANsetNormalMode(CO->CANmodule[0]);*/

        /* Start app workers */
        for (i = 0; i < num_workers; i++) {
            /* TODO: Start worker threads */
        }

        chThdSleepMilliseconds(1000);
    }

    CO_delete((uint32_t)&CAND1);

    /* Reset */
    return;
}
