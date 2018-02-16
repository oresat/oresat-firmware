/*! \file main.c
 *  app_blinky
 *
 */

/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio
    Licensed under the Apache License, Version 2.0 (the "License");

    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/*!
 * \defgroup main app_blinky main
 *
 * @{
 */

/*
 * ChibiOS header files
 */
#include "ch.h"
#include "hal.h"

/*
 * Project header files
 */

/*
 * Serial configuration
 */
static SerialConfig ser_cfg =
{
    115200,     //Baud rate
    0,          //
    0,          //
    0,          //
};

/*
 * Green LED blinker thread, times are in milliseconds.
 */
static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg) {

  (void)arg;
  chRegSetThreadName("blinker");

  while (!chThdShouldTerminateX()) {
    palClearLine(LINE_LED_GREEN);
    chThdSleepMilliseconds(500);
    palSetLine(LINE_LED_GREEN);
    chThdSleepMilliseconds(500);
  }
}


static void app_init(void)
{
    // Start up debug output
    sdStart(&SD2, &ser_cfg);

}

static void main_app(void)
{
    /*
     * Starting the blinker thread
     */
    chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);

    /*
     * Begin main loop
     */
    while (true)
    {
        chThdSleepMilliseconds(1000);
    }
}

int main(void)
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
    app_init();

    main_app();

    return 0;
}

//! @}

