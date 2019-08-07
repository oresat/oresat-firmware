#include "oresat.h"
#include "CANopen.h"
#include "can_threads.h"

static struct {
    thread_descriptor_t workers[ORESAT_MAX_THREADS];
    uint32_t num_workers;
    uint8_t node_id;
} node_cfg;

int reg_worker(void *wa, size_t wa_size, tprio_t prio, tfunc_t thread_func, void *arg)
{
    if (node_cfg.num_workers == ORESAT_MAX_THREADS) {
        return -1;
    }

    /* TODO: Register worker threads */

    return node_cfg.num_workers++;
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
        node_id = (FLASH->OBR & FLASH_OBR_DATA0_Msk) >> FLASH_OBR_DATA0_Pos;
    }

    //TODO: If node ID is invalid, get new node ID
    if (node_id > 0x7F) {
        node_id = 0x7F;
    }
    node_cfg.node_id = node_id;

    return;
}

void oresat_start(CANDriver *cand, uint16_t bitrate)
{
    CO_NMT_reset_cmd_t reset = CO_RESET_NOT;
    uint16_t sleep_ms;
    systime_t prev_time, cur_time, diff_time;

    while (reset != CO_RESET_APP) {
        CO_ReturnError_t err;

        /* Initialize CAN Subsystem */
        err = CO_init((uint32_t)cand, node_cfg.node_id, bitrate);
        if (err != CO_ERROR_NO) {
            CO_errorReport(CO->em, CO_EM_MEMORY_ALLOCATION_ERROR, CO_EMC_SOFTWARE_INTERNAL, err);
        }

        chThdCreateStatic(can_wa, sizeof(can_wa), HIGHPRIO, can, CO);

        cand->rxfull_cb = CO_CANrx_cb;
        cand->txempty_cb = CO_CANtx_cb;

        CO_CANsetNormalMode(CO->CANmodule[0]);

        /* Start app workers */
        for (uint32_t i = 0; i < node_cfg.num_workers; i++) {
            /* TODO: Start worker threads */
        }

        reset = CO_RESET_NOT;
        prev_time = chVTGetSystemTimeX();
        while (reset == CO_RESET_NOT) {
            sleep_ms = 50U;
            diff_time = chTimeDiffX(prev_time, cur_time = chVTGetSystemTimeX());
            prev_time = cur_time;
            reset = CO_process(CO, chTimeI2MS(diff_time), &sleep_ms);
            chThdSleepMilliseconds(sleep_ms);
        }
    }

    CO_delete((uint32_t)cand);

    /* Reset */
    NVIC_SystemReset();
    return;
}
