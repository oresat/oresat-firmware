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

//=== ChibiOS header files
#include "ch.h"
#include "hal.h"
#include "chprintf.h"

//=== Project header files
#include "oresat.h"

#include "demo.h"

//=== Serial configuration
static SerialConfig ser_cfg =
{
    115200,     //Baud rate
    0,          //
    0,          //
    0,          //
};

/*
 * I2C configuration
 */
static const I2CConfig i2cfg1 =
{
    I2C_100KHZ_TIMINGR,
    0,
    0,
};

uint8_t data[8];

static void app_init(void) {
    //=== App initialization

    // Start up debug output
    sdStart(&SD2, &ser_cfg);

    i2cInit();
    i2cStart(&I2CD1, &i2cfg1);

    for (uint8_t i = 0; i < 8; ++i) {
        data[i] = 0;
    }

    can_initTPDO(CAN_PDO_1, CAN_ID_DEFAULT, 0, 0, 8, data);
}

static void main_app(void) {
    //=== Start application threads

    //Example thread creation
    chThdCreateStatic(demo_measure_wa, sizeof(demo_measure_wa), NORMALPRIO, demo_measure, NULL);

    /*
     * Begin main loop
     */
    while (true)
    {
        chThdSleepMilliseconds(1000);
    }
}

int main(void) {
    /*
     * System initializations.
     * - HAL initialization, this also initializes the configured device drivers
     *   and performs the board-specific initializations.
     * - Kernel initialization, the main() function becomes a thread and the
     *   RTOS is active.
     */
    halInit();
    chSysInit();
    oresat_init();

    // Initialize and start app
    app_init();
    main_app();

    return 0;
}
