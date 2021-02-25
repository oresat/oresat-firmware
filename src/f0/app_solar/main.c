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

/* ChibiOS header files */
#include "ch.h"
#include "hal.h"

/* Project header files */
#include "oresat.h"
#include "solar.h"
#include "blink.h"
#include "read_temperature.h"

static worker_t worker1;
static worker_t worker2;
static worker_t worker3;

const I2CConfig i2cconfig = {
    STM32_TIMINGR_PRESC(0xBU) |
    STM32_TIMINGR_SCLDEL(0x4U) | STM32_TIMINGR_SDADEL(0x2U) |
    STM32_TIMINGR_SCLH(0xFU)  | STM32_TIMINGR_SCLL(0x13U),
    0,
    0
};

static oresat_config_t oresat_conf = {
    &CAND1,
    0x04,
    ORESAT_DEFAULT_BITRATE
};

/**
 * @brief App Initialization
 */
static void app_init(void)
{
    /* App initialization */
    init_worker(&worker1, "Blink", blink_wa, sizeof(blink_wa), NORMALPRIO, blink, NULL, true);
    init_worker(&worker2, "Solar Application", solar_wa, sizeof(solar_wa), NORMALPRIO, solar, NULL, true);
    init_worker(&worker3, "Read Temperature", read_temperature_wa, sizeof(read_temperature_wa), NORMALPRIO, read_temperature, NULL, true);

    reg_worker(&worker1);
    reg_worker(&worker2);
    reg_worker(&worker3);

    /* Start up debug output */
    sdStart(&SD2, NULL);

//    reg_worker(&worker3);
}

/**
 * @brief Main Application
 */
int main(void)
{
    // Initialize and start
    oresat_init();
    app_init();
    oresat_start(&oresat_conf);
    return 0;
}
