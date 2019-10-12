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
#include "util_version.h"
#include "util_numbers.h"
#include "shell.h"

#include "si41xx.h"


#define     DEBUG_SERIAL                    SD2
#define     DEBUG_CHP                       ((BaseSequentialStream *) &DEBUG_SERIAL)


/*
 * Serial Driver Configuration
 */
static SerialConfig ser_cfg =
{
    115200,                                 //Baud rate
    0,                                      //
    0,                                      //
    0,                                      //
};



/*
 * Initialize the SPI drivers and configure the ax5043 chips
 */
static void app_init(void)
{
 // Start up debug output, chprintf(DEBUG_CHP,...)
    sdStart(&DEBUG_SERIAL, &ser_cfg);
    set_util_fwversion(&version_info);
    set_util_hwversion(&version_info);


    //Print FW/HW information
    chprintf(DEBUG_CHP, "\r\nFirmware Info\r\n");
    chprintf(DEBUG_CHP, "FW HASH: %s\r\n", version_info.firmware);
    chprintf(DEBUG_CHP, "STF0x UNIQUE HW ID (H,C,L):\r\n0x%x\t0x%x\t0x%x\r\n"
             , version_info.hardware.id_high
             , version_info.hardware.id_center
             , version_info.hardware.id_low
            );

}


/*
 *This function bit bangs the si41xx registers with default values.
 *The dafult values are set as
 *  RF1 output = 1265 MHz
 *  RF2 output = disabled
 *  IF output  = 436.5 MHz
 *The following pins are connected between M4 and si41xx chip
 *LINE_SI_SCLK                PAL_LINE(GPIOC, 2U)
 *LINE_SI_SDATA               PAL_LINE(GPIOC, 3U)
 *LINE_SI_SENB                PAL_LINE(GPIOC, 4U)  
 */

static void si41xx_init(void) 
{   

  palSetLine(LINE_SI_SENB);
  palSetLine(LINE_SI_SDATA);
  palSetLine(LINE_SI_SCLK);
  
  si_write_reg(SI41XX_REG_MAIN_CONFIG, 0b000011000000000100);
  si_write_reg(SI41XX_REG_PHASE_GAIN,  0b000000000000000000);

  // RF1 and IF default for 1265 / 436.5 MHz w/ 500 kHz
  si_write_reg(SI41XX_REG_PWRDOWN,     0b000000000000000011);
  si_write_reg(SI41XX_REG_RF1_NDIV,    0b000000100111100010);
  si_write_reg(SI41XX_REG_RF1_RDIV,    0b000000000000100000);
  si_write_reg(SI41XX_REG_IF_NDIV,     0b000000001101101001);
  si_write_reg(SI41XX_REG_IF_RDIV,     0b000000000000100000);
  
  // IF default for 808 MHz w/ 500 kHz
  //si_write_reg(SI41XX_REG_PWRDOWN,     0b000000000000000010);
  //si_write_reg(SI41XX_REG_IF_NDIV,     0b000000011001010000);
  //si_write_reg(SI41XX_REG_IF_RDIV,     0b000000000000100000);

  palSetLine(LINE_SI_SENB);
  palSetLine(LINE_SI_SDATA);
  palSetLine(LINE_SI_SCLK);

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
  
  si_write_reg(reg_address, reg_value);
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
  
  si_write_reg(SI41XX_REG_RF1_NDIV, ndiv);
  si_write_reg(SI41XX_REG_RF1_RDIV, rdiv);
  
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
  
  si_write_reg(SI41XX_REG_RF2_NDIV, ndiv);
  si_write_reg(SI41XX_REG_RF2_RDIV, rdiv);
  
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
  
  si_write_reg(SI41XX_REG_IF_NDIV, ndiv);
  si_write_reg(SI41XX_REG_IF_RDIV, rdiv);
  
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

static const ShellConfig shell_cfg1 = {
  (BaseSequentialStream *)&SD2,
  commands
};


/*
 * Entry to our code
 */
int main(void)
{
  
  halInit();
  chSysInit();
  app_init();

  si41xx_init();
    
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
