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
    /* TODO: Sanity checks */

    /* Set configuration values */
    /* If node ID is not overridden, use default node ID */
    if (config->node_id == ORESAT_DEFAULT_ID) {
        /* TODO: Implement Node ID system properly */
    }

    /* Set priority to max */
    chThdSetPriority(HIGHPRIO);

    /* Start critical worker threads */
    start_crit_workers();

    /* Initialize CANopen Subsystem */
    CO_init(config, config->node_id, config->bitrate);

    /* Run CO subsystem */
    CO_run(CO);

    /* Stop all workers, including critical ones  */
    stop_workers(true);

    /* Deinitialize CO stack */
    CO_delete(config);

    /* Initiate System Reset */
    NVIC_SystemReset();
    return;
}
