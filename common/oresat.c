#include "oresat.h"
#include "sensors.h"
#include "CO_threads.h"

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

    /* Init sensors */
    sensors_init();

    /* Record the config being used */
    cand = config->cand;

    /* Set configuration values */
    /* If node ID is not overridden, use default node ID */
    if (config->node_id == ORESAT_DEFAULT_ID) {
        /* TODO: Implement Node ID system properly */
    }

    /* Initialize CANopen Subsystem */
    CO_init(cand, config->node_id, config->bitrate);

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
    CO_delete(cand);

    /* Initiate System Reset */
    NVIC_SystemReset();
    return;
}
