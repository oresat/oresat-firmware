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

static worker_t blink_worker;
static thread_descriptor_t blink_desc = {
    .name = "Blink",
    .wbase = THD_WORKING_AREA_BASE(blink_wa),
    .wend = THD_WORKING_AREA_END(blink_wa),
    .prio = NORMALPRIO,
    .funcp = blink,
    .arg = NULL
};
static worker_t solar_worker;
static thread_descriptor_t solar_desc = {
    .name = "Solar MPPT",
    .wbase = THD_WORKING_AREA_BASE(solar_wa),
    .wend = THD_WORKING_AREA_END(solar_wa),
    .prio = NORMALPRIO,
    .funcp = solar,
    .arg = NULL
};
static worker_t sensor_mon_worker;
static thread_descriptor_t sensor_mon_desc = {
    .name = "Sensor Monitor",
    .wbase = THD_WORKING_AREA_BASE(sensor_mon_wa),
    .wend = THD_WORKING_AREA_END(sensor_mon_wa),
    .prio = NORMALPRIO,
    .funcp = sensor_mon,
    .arg = NULL
};

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
    reg_worker(&blink_worker, &blink_desc, false, true);
    reg_worker(&solar_worker, &solar_desc, true, true);
    reg_worker(&sensor_mon_worker, &sensor_mon_desc, true, true);

    /* Start up debug output */
    sdStart(&SD2, NULL);
}

/**
 * @brief Main Application
 */
int main(void)
{
    // Initialize and start
    oresat_init(&oresat_conf);
    app_init();
    oresat_start();
    return 0;
}
