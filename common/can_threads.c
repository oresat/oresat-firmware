/*
 * CAN Subsystem Threads
 */

//Project headers
#include "can_threads.h"
#include "CO_driver.h"

/*
 * CAN Worker Thread
 */
THD_WORKING_AREA(can_wa, 0x40);
THD_FUNCTION(can, p)
{
    CO_CANmodule_t      *CANmodule = p;

    // Set thread name
    chRegSetThreadName("can_worker");

    // Start Loop
    while (!chThdShouldTerminateX()) {
        chThdSleepMilliseconds(1000);
    }

    chThdExit(MSG_OK);
}
