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
#include "cmd.h"
#include "test_radio.h"
#include "test_synth.h"

static const SI41XXConfig synth_cfg = {
    .sen = LINE_LO_SEN,
    .sclk = LINE_LO_SCLK,
    .sdata = LINE_LO_SDATA,
    .ref_freq = 16000000,
    .if_div = 2,
    .if_n = 873,
    .if_r = 16,
};

/**
 * @brief App Initialization
 */
static void app_init(void)
{
    ax5043ObjectInit(&lband);
    ax5043ObjectInit(&uhf);
    si41xxObjectInit(&synth);
    si41xxStart(&synth, &synth_cfg);

    /* Initialize shell and start serial interface */
    shellInit();
    sdStart(&SD3, NULL);
}

/**
 * @brief Main Application
 */
int main(void)
{
    halInit();
    chSysInit();

    // Initialize and start
    app_init();

    /* Initialize shell worker thread */
    chThdCreateStatic(cmd_wa, sizeof(cmd_wa), NORMALPRIO, cmd, NULL);

    while (true) {
        palToggleLine(LINE_WDT);
        chThdSleepMilliseconds(250);
    }
    return 0;
}
