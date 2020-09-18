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
 *  RF1 output = 1265 MHz
 *  RF2 output = disabled
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
    .if_n = 873,
    .if_r = 16,
    .rf1_n = 1265,
    .rf1_r = 32,
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
 * This lets the user update RF1 registers via the chibios shell
 * Requires frequency and phase values in KHz.
 */
static void rf1(BaseSequentialStream *sd, int argc, char *argv[]) {

    uint32_t freq;
    uint32_t phase;
    uint32_t ndiv;
    uint32_t rdiv;

    if (argc < 2) {
        chprintf(sd, "Usage: rf1 <frequency in KHz> <Phase detector in KHz>\r\n");
        return;
    }

    freq = strtoul(argv[0], NULL, 10);
    phase = strtoul(argv[1], NULL, 10);

    if (freq == 0) {
        chprintf(sd, "ERROR: freqency cannot be 0. \r\nUsage: rf1 <frequency in KHz> <Phase detector in KHz>\r\n");
        return;
    }
    if (phase == 0) {
        chprintf(sd, "ERROR: phase value cannot be 0. \r\nUsage: rf1 <frequency in KHz> <Phase detector in KHz>\r\n");
        return;
    }
    rdiv = SI41XX_FREF * 1000/phase;
    ndiv = freq * rdiv / (1000*SI41XX_FREF);

    si41xxWriteRaw(&synth, SI41XX_REG_RF1_NDIV, ndiv);
    si41xxWriteRaw(&synth, SI41XX_REG_RF1_RDIV, rdiv);

    chprintf(sd, "INFO: freqency set at %d Khz, phase set at %d Khz.\r\n", freq, phase);
}


/*
 * shell commands for user entry
 * This lets the user update RF2 registers via the chibios shell
 * Requires frequency and phase values in KHz. This should not be used for si4123
 */
static void rf2(BaseSequentialStream *sd, int argc, char *argv[]) {

    uint32_t freq;
    uint32_t phase;
    uint32_t ndiv;
    uint32_t rdiv;

    if (argc < 2) {
        chprintf(sd, "Usage: rf1 <frequency in KHz> <Phase detector in KHz>\r\n");
        return;
    }

    freq = strtoul(argv[0], NULL, 10);
    phase = strtoul(argv[1], NULL, 10);

    if (freq == 0) {
        chprintf(sd, "ERROR: freqency cannot be 0. \r\nUsage: rf1 <frequency in KHz> <Phase detector in KHz>\r\n");
        return;
    }
    if (phase == 0) {
        chprintf(sd, "ERROR: phase value cannot be 0. \r\nUsage: rf1 <frequency in KHz> <Phase detector in KHz>\r\n");
        return;
    }
    rdiv = SI41XX_FREF * 1000/phase;
    ndiv = freq * rdiv / (1000*SI41XX_FREF);

    si41xxWriteRaw(&synth, SI41XX_REG_RF2_NDIV, ndiv);
    si41xxWriteRaw(&synth, SI41XX_REG_RF2_RDIV, rdiv);

    chprintf(sd, "INFO: freqency set at %d Khz, phase set at %d Khz.\r\n", freq, phase);
}


/*
 * shell commands for user entry
 * This lets the user update IF registers via the chibios shell
 * Requires frequency and phase values in KHz.
 */
static void ifr(BaseSequentialStream *sd, int argc, char *argv[]) {

    uint32_t freq;
    uint32_t phase;
    uint32_t ndiv;
    uint32_t rdiv;

    if (argc < 2) {
        chprintf(sd, "Usage: rf1 <frequency in KHz> <Phase detector in KHz>\r\n");
        return;
    }

    freq = strtoul(argv[0], NULL, 10);
    phase = strtoul(argv[1], NULL, 10);

    if (freq == 0) {
        chprintf(sd, "ERROR: freqency cannot be 0. \r\nUsage: rf1 <frequency in KHz> <Phase detector in KHz>\r\n");
        return;
    }
    if (phase == 0) {
        chprintf(sd, "ERROR: phase value cannot be 0. \r\nUsage: rf1 <frequency in KHz> <Phase detector in KHz>\r\n");
        return;
    }
    rdiv = SI41XX_FREF * 1000/phase;
    ndiv = freq * rdiv / (1000*SI41XX_FREF);

    si41xxWriteRaw(&synth, SI41XX_REG_IF_NDIV, ndiv);
    si41xxWriteRaw(&synth, SI41XX_REG_IF_RDIV, rdiv);

    chprintf(sd, "INFO: freqency set at %d Khz, phase set at %d Khz.\r\n", freq, phase);
}


/*
 * shell commands for user entry
 * Provides a list of comamnds and their description to Chibios shell user.
 */
static void si_help(BaseSequentialStream *sd, int argc, char *argv[]) {

    (void) argc;
    (void) argv;

    chprintf(sd, "Available commands:\r\n");
    chprintf(sd, "    reg:   Update registers,Usage reg <register address> <register value>\r\n");
    chprintf(sd, "    rf1:   Update RF1 registers,Usage: rf1 <frequency in KHz> <Phase detector in KHz>\r\n");
    chprintf(sd, "    rf2:   Update RF2 registers,Usage: rf2 <frequency in KHz> <Phase detector in KHz>\r\n");
    chprintf(sd, "    if:   Update IF registers,Usage: ifr <frequency in KHz> <Phase detector in KHz>\r\n");
    chprintf(sd, "    ?:   provides list of commands\n\n\r\n");
}


/*
 * shell commands for user entry
 * This is the list of shell commands defined in this program
 */
static const ShellCommand commands[] = {
    {"reg", reg},
    {"rf1", rf1},
    {"rf2", rf2},
    {"if", ifr},
    {"?", si_help},
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
