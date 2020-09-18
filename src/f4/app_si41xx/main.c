/*
    ChibiOS - Copyright (C) 2006..2015 Giovanni Di Sirio

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

/********************************************************************
 *     Modification Log
 *     09/05/2019    Malay Das    Initial Code.
 *     09/12/2019    Malay Das    Added user entry via chibios shell.
 ********************************************************************/


/*
 * Include Files
 */
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "shell.h"

#include "si41xx.h"

/*
 *The dafult values are set as
 *  IF output  = 436.5 MHz
 *The following pins are connected between M4 and si41xx chip
 *LINE_LO_SCLK              PAL_LINE(GPIOC, 2U)
 *LINE_LO_SDATA             PAL_LINE(GPIOC, 3U)
 *LINE_LO_SEN               PAL_LINE(GPIOC, 4U)
 */

static const SI41XXConfig synth_cfg = {
    .sen = LINE_LO_SEN,
    .sclk = LINE_LO_SCLK,
    .sdata = LINE_LO_SDATA,
    .ref_freq = 16000000,
    .if_div = 2,
    .if_n = 873,
    .if_r = 16,
};

SI41XXDriver synth;

/*
 * Initialize the SPI drivers and configure the ax5043 chips
 */
static void app_init(void)
{
    sdStart(&SD3, NULL);
    si41xxObjectInit(&synth);
}

/*
 * The main loop.
 * Currently it does not have any utility. It keeps waiting.
 */
static void main_loop(void)
{

    while (true)
    {
        chThdSleepMilliseconds(15000);
    }

}


/*
 * shell commands for user entry.
 * This lets the user update any register via the chibios shell.
 * Requires register address and register value as entry.
 */
static void reg(BaseSequentialStream *sd, int argc, char *argv[]) {

    uint32_t reg_address;
    uint32_t reg_value;

    if (argc < 2) {
        chprintf(sd, "Usage: reg <register address in decimal/hexadecimal> <register value in binary/decimal/hexadecimal>\r\n");
        chprintf(sd, "Example:   reg 2 12\r\n");
        chprintf(sd, "           reg 2 0xCA\r\n");
        chprintf(sd, "           reg 2 0b10\r\n");
    }

    reg_address = strtoul(argv[0], NULL, 0);
    reg_value = strtoul((argv[1][0] == '0' && argv[1][1] == 'b') ?  argv[1]+2: argv[1], NULL, (argv[1][0] == '0' && argv[1][1] == 'b') ? 2 : 0);

    si41xxWriteRaw(&synth, reg_address, reg_value);
    chprintf(sd, "INFO: Updated register %d with value 0x%x.\r\n", reg_address, reg_value);
}


/*
 * shell commands for user entry
 * This lets the user update IF registers via the chibios shell
 * Requires frequency and phase values in KHz.
 */
static void ifr(BaseSequentialStream *sd, int argc, char *argv[]) {
    uint32_t freq;

    if (argc < 1) {
        goto ifr_usage;
    }

    freq = strtoul(argv[0], NULL, 0);

    if (freq == 0) {
        chprintf(sd, "ERROR: Freqency cannot be 0.\r\n");
        goto ifr_usage;
    }

    if (si41xxSetIF(&synth, freq)) {
        chprintf(sd, "INFO: IF freqency set to %u Hz.\r\n", freq);
    } else {
        chprintf(sd, "ERROR: IF freqency could not be set to this value.\r\n", freq);
    }

    return;

ifr_usage:
    chprintf(sd, "Usage: ifr <frequency in Hz>\r\n");
    return;
}

/*
 * shell commands for user entry
 * This is the list of shell commands defined in this program
 */
static const ShellCommand commands[] = {
    {"reg", reg},
    {"if", ifr},
    {NULL, NULL}
};

static char histbuf[SHELL_MAX_HIST_BUFF];

static const ShellConfig shell_cfg1 = {
    (BaseSequentialStream *)&SD3,
    commands,
    histbuf,
    sizeof(histbuf),
};


/*
 * Entry to our code
 */
int main(void)
{

    halInit();
    chSysInit();
    app_init();

    si41xxStart(&synth, &synth_cfg);

    /*
     * Shell manager initialization.
     */
    shellInit();
    chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(2048),
            "shell1", NORMALPRIO + 1,
            shellThread, (void *)&shell_cfg1);

    main_loop();
    return 0;
}
