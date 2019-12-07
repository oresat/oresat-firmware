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
#include "shell.h"

/* Project header files */
#include "oresat.h"
#include "wdt.h"
#include "opd.h"
#include "command.h"

static SPIConfig hs_spicfg = {
    false,
    NULL,
    LINE_MMC_CS,
    0,
    0
};

static SPIConfig ls_spicfg = {
    false,
    NULL,
    LINE_MMC_CS,
    SPI_CR1_BR_2 | SPI_CR1_BR_1,
    0
};

/*
 * MMC configuration.
 */
static MMCConfig mmccfg = {
    &SPID2,
    &ls_spicfg,
    &hs_spicfg
};

MMCDriver MMCD1;

/**
 * @brief App Initialization
 */
static void app_init(void)
{
    /* App initialization */
    chThdCreateStatic(wdt_wa, sizeof(wdt_wa), NORMALPRIO, wdt, NULL);
    chThdCreateStatic(cmd_wa, sizeof(cmd_wa), NORMALPRIO, cmd, NULL);

    palClearLine(LINE_OPD_ENABLE);

    /* Initialize OPD */
    opd_init();
    opd_start();

    /* Initialize shell and start serial interface */
    shellInit();
    sdStart(&SD2, NULL);

    /* Initializes MMC SPI driver */
    mmcObjectInit(&MMCD1);
    mmcStart(&MMCD1, &mmccfg);
}

/**
 * @brief Main Application
 */
int main(void)
{
    // Initialize and start
    oresat_init(0x01, ORESAT_DEFAULT_BITRATE);
    app_init();
    oresat_start(&CAND1);
    return 0;
}
