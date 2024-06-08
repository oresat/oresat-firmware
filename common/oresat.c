#include "oresat.h"
#include "sensors.h"
#include "CO_threads.h"
#include "CANopen.h"

CO_t *CO;
CANDriver *cand;

void oresat_init(oresat_config_t *config)
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

    /* Enumerate UID */
    /*
    for (int i = 0; i < 3; i++) {
        OD_RAM.x2020_MCU_UniqueDeviceID[i] = ((uint32_t*)UID_BASE)[i];
    }
    */

    /* Init sensors */
    sensors_init();

    /* Record the config being used */
    cand = config->cand;

    /* Set configuration values */
    /* If node ID is not overridden, use default node ID */
    if (config->node_id == ORESAT_DEFAULT_ID) {
#if defined(STM32F0XX)
        uint8_t node_id = ((FLASH->OBR & FLASH_OBR_DATA0_Msk) >> FLASH_OBR_DATA0_Pos);
        if (node_id <= 0x7C) {
            config->node_id = node_id;
        } else
#endif
            config->node_id = 0x7C;
    }

    /* Initialize CANopen Subsystem */
    CO_init(&CO, cand, config->node_id, config->bitrate, config->fifo1_filters, config->filter_count);

    return;
}

void oresat_start(void)
{
    thread_t *thread_mgr_tp;
    /* TODO: Sanity checks */

    /* Set priority to max */
    chThdSetPriority(HIGHPRIO);

    /* Start the sensors */
    sensors_start();

    /* Start worker thread manager */
    thread_mgr_tp = chThdCreateStatic(thread_mgr_wa, sizeof(thread_mgr_wa), HIGHPRIO, thread_mgr, NULL);

    /* Run CO subsystem */
    CO_run(CO);

    /* Stop worker thread manager */
    /* TODO: Use common event mask macro */
    chEvtSignal(thread_mgr_tp, EVENT_MASK(1));
    chThdWait(thread_mgr_tp);

    /* Deinitialize CO stack */
    CO_delete(CO);

    /* Initiate System Reset */
    NVIC_SystemReset();
    return;
}
