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

/***************************************************
 *     Modification Log
 *     04/15/2018    Malay Das    Initial Code.
 ***************************************************/


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

#include "si4123.h"


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




THD_WORKING_AREA(waSI4123_thd, 1024);
THD_FUNCTION(SI4123_thd, arg)
{
  (void)arg;    
 
  palSetLine(LINE_SI_SENB);
  palSetLine(LINE_SI_SDATA);
  palSetLine(LINE_SI_SCLK);
  
  si_write_reg(SI4123_REG_MAIN_CONFIG, 0b000011000000000100);
  si_write_reg(SI4123_REG_PHASE_GAIN,  0b000000000000000000);
  si_write_reg(SI4123_REG_PWRDOWN,     0b000000000000000011);
  si_write_reg(SI4123_REG_RF1_NDIV,    0b000000010011110001);
  //si_write_reg(SI4123_REG_RF2_NDIV,    0b000000000000000000);
  si_write_reg(SI4123_REG_IF_NDIV,     0b000000001101101001);
  si_write_reg(SI4123_REG_RF1_RDIV,    0b000000000000010000);
  //si_write_reg(SI4123_REG_RF2_RDIV,    0b000000000000000000);
  si_write_reg(SI4123_REG_IF_RDIV,     0b000000000000100000);

  palSetLine(LINE_SI_SENB);
  palSetLine(LINE_SI_SDATA);
  palSetLine(LINE_SI_SCLK);
  
  //palClearLine(LINE_SI_SCLK);

}


/*
 * main loop blinks the led
 */
static void main_loop(void)
{
    chThdSleepMilliseconds(500);


	while (true)
    {
      chThdSleepMilliseconds(5000);
      chprintf(DEBUG_CHP, ".");
      //palTogglePad(GPIOA, GPIOA_SX_TESTOUT);
    }

}


/*
 * Entry to our code
 */
int main(void)
{
    halInit();
    chSysInit();
    app_init();

    //chThdSleepMilliseconds(5000);
    chThdCreateStatic(waSI4123_thd, sizeof(waSI4123_thd), NORMALPRIO,SI4123_thd, NULL);

    main_loop();
    return 0;
}
