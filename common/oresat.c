#include "oresat.h"
#include "sensors.h"
#include "CO_threads.h"

void oresat_init(void)
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

    /* Init sensors */
    sensors_init();

    /* Setup CANopen subsystem */
    CO_ReturnError_t err = CO_new(NULL);
    chDbgAssert(err == CO_ERROR_NO, "CO_new failed");

    return;
}

void oresat_start(oresat_config_t *config)
{
    thread_t *thread_mgr_tp;
    /* TODO: Sanity checks */

    /* Set configuration values */
    /* If node ID is not overridden, use default node ID */
    if (config->node_id == ORESAT_DEFAULT_ID) {
        /* TODO: Implement Node ID system properly */
    }

    /* Set priority to max */
    chThdSetPriority(HIGHPRIO);

    /* Start worker thread manager */
    thread_mgr_tp = chThdCreateStatic(thread_mgr_wa, sizeof(thread_mgr_wa), HIGHPRIO, thread_mgr, NULL);

    /* Initialize CANopen Subsystem */
    CO_init(config, config->node_id, config->bitrate);

    /* Run CO subsystem */
    CO_run(CO);

    /* Stop worker thread manager */
    chEvtSignal(thread_mgr_tp, EVENT_MASK(1));
    chThdWait(thread_mgr_tp);

    /* Deinitialize CO stack */
    CO_delete(config);

    /* Initiate System Reset */
    NVIC_SystemReset();
    return;
}
