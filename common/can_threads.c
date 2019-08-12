/*
 * CAN Subsystem Threads
 */

//Project headers
#include "can_threads.h"
#include "CANopen.h"

/*
 * CAN Worker Thread
 */
THD_WORKING_AREA(can_rt_wa, 0x40);
THD_FUNCTION(can_rt, p)
{
    systime_t prev_time, cur_time, diff_time;
    CO_t *CO = p;

    // Set thread name
    chRegSetThreadName("can_worker");

    prev_time = chVTGetSystemTimeX();
    // Start Loop
    while (!chThdShouldTerminateX()) {
        if(CO->CANmodule[0]->CANnormal) {
            bool_t syncWas;

            /* Process Sync and read inputs */
            diff_time = chTimeDiffX(prev_time, cur_time = chVTGetSystemTimeX());
            syncWas = CO_process_SYNC_RPDO(CO, chTimeI2US(diff_time));
            /* Further I/O or nonblocking application code may go here. */
            /* Write outputs */
            diff_time = chTimeDiffX(prev_time, cur_time = chVTGetSystemTimeX());
            CO_process_TPDO(CO, syncWas, chTimeI2US(diff_time));
            prev_time = cur_time;
        }

        chThdSleepMicroseconds(1000);
    }

    chThdExit(MSG_OK);
}
