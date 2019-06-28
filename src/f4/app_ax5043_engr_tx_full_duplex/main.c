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
#include "ax5043.h"


//#include "adf7030.h"

#define     DEBUG_SERIAL                    SD2
#define     DEBUG_CHP                       ((BaseSequentialStream *) &DEBUG_SERIAL)

const struct axradio_address remoteaddr_tx = {
	{ 0x33, 0x34, 0x00, 0x00}
};
const struct axradio_address_mask localaddr_tx = {
	{ 0x32, 0x34, 0x00, 0x00},
	{ 0xFF, 0x00, 0x00, 0x00}
};
const uint8_t demo_packet[] =  { 0x86, 0xA2, 0x40, 0x40, 0x40, 0x40, 0x60, 0x96, 0x8E, 0x6E, 0xB4, 0xAC, 0xAC, 0x61, 0x3F, 0xF0, 0x3A, 0x43, 0x51, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3A, 0x54, 0x65, 0x73, 0x74, 0x7B, 0x30, 0x30, 0x30, 0x30, 0x31 };
const uint8_t framing_insert_counter = 1;
const uint8_t framing_counter_pos = 0;

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
 * Receive and Transmit SPI Configurations
 */
static const SPIConfig spicfg_rx =
{
    false,
    NULL,                                   // Operation complete callback
    GPIOA,                                  // Slave select port
    GPIOA_SPI1_NSS,                         // Slave select pad
    // SPI cr1 data                            (see 446 ref man.)
    SPI_CR1_SPE     |                       // SPI enable
    SPI_CR1_MSTR    |                       // Master
    //SPI_CR1_BR_2    |
    SPI_CR1_BR_1    |
    SPI_CR1_BR_0   |                        // fpclk/16  approx 5Mhz? BR = 0x011
    SPI_CR1_SSM,
    0, // SPI_CR2_SSOE,
};

static const SPIConfig spicfg_tx =
{
    false,
    NULL,                                   // Operation complete callback
    GPIOB,                                  // Slave select port
    GPIOB_SPI2_NSS,                         // Slave select pad
    // SPI cr1 data                         (see 446 ref man.)
    SPI_CR1_SPE     |                       // SPI enable
    SPI_CR1_MSTR    |                       // Master
    //SPI_CR1_BR_2    |
    SPI_CR1_BR_1    |
    SPI_CR1_BR_0   |                        // fpclk/16  approx 5Mhz? BR = 0x011
    SPI_CR1_SSM,
    0, // SPI_CR2_SSOE,
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

    spiStart(&SPID1, &spicfg_rx);
    spiStart(&SPID2, &spicfg_tx);
}


THD_WORKING_AREA(waAx5043_tx, 256);
THD_FUNCTION(ax5043_tx, arg)
{
  (void)arg;
  uint16_t pkt_counter = 0;

  chThdSleepMilliseconds(50);
  ax5043_f1_init(&SPID1);
  ax5043_set_addr(&SPID1, localaddr_tx);
  ax5043_f1_prepare_tx(&SPID1);
  chprintf(DEBUG_CHP, "done reseting AX5043 tx\r\n");


	for (;;) {
	    static uint8_t demo_packet_[sizeof(demo_packet)];
	    //uint16_t pkt_counter = 0;

	    ++pkt_counter;
	    memcpy(demo_packet_, demo_packet, sizeof(demo_packet));
	    if (framing_insert_counter) {
	        demo_packet_[framing_counter_pos] = (uint8_t)(pkt_counter & 0xFF);
	        demo_packet_[framing_counter_pos+1] = (uint8_t)((pkt_counter>>8) & 0xFF);
	    }

		chprintf(DEBUG_CHP,"INFO: Sending packet %d\r\n",pkt_counter);
		transmit_f1_packet(&SPID1, &remoteaddr_tx, demo_packet_, sizeof(demo_packet));

    chThdSleepMilliseconds(5000);
	}

}

THD_WORKING_AREA(waAx5043_rx, 256);
THD_FUNCTION(ax5043_rx, arg) 
{
  (void)arg;
  uint8_t packet_len=0;
  uint8_t ret_value[3]={0,0,0}

  ax5043_f2_init(&SPID2);
  ax5043_set_addr(&SPID2, localaddr_tx);
  chprintf(DEBUG_CHP, "done reseting AX5043 rx \r\n");
  chThdSleepMilliseconds(50);
  
  ax5043_f2_init(&SPID2);
  ax5043_f2_prepare_rx(&SPID2);

  /* Enabling events on both edges of the button line.*/
  //palEnableLineEvent(LINE_BUTTON, PAL_EVENT_MODE_RISING_EDGE);
  palEnableLineEvent(LINE_ARD_A5, PAL_EVENT_MODE_RISING_EDGE);



  //palWaitLineTimeout(LINE_BUTTON, TIME_INFINITE);
  //palWaitLineTimeout(LINE_ARD_A5, TIME_INFINITE);
  palWaitLineTimeout(LINE_ARD_A5, TIME_MS2I(5000));

  if (palReadLine(LINE_ARD_A5))
    chprintf(DEBUG_CHP, "\r\r int line is HIGH ** \r\n");
  else
    chprintf(DEBUG_CHP, "\r\r int line is LOW ** \r\n");
    
  packet_len=receive_loop(&SPID2, axradio_rxbuffer);

  if(packet_len > 0)
    chprintf(DEBUG_CHP,"INFO: Received packet %d\r\n",axradio_rxbuffer[3]);


}



/*
 * main loop blinks the led
 */
static void main_loop(void)
{
    chThdSleepMilliseconds(500);


	while (true)
    {
      chThdSleepMilliseconds(500);
      chprintf(DEBUG_CHP, ".");
		  palTogglePad(GPIOA, GPIOA_SX_TESTOUT);
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

    chThdCreateStatic(waAx5043_rx, sizeof(waAx5043_rx), NORMALPRIO, ax5043_rx, NULL);
    chThdCreateStatic(waAx5043_tx, sizeof(waAx5043_tx), NORMALPRIO, ax5043_tx, NULL);
    chThdSleepMilliseconds(15000);

    main_loop();
    return 0;
}
