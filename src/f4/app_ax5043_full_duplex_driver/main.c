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
#include "ax5043_common.h"
#include "ax5043_engr_f1.h"
#include "ax5043_engr_f2.h"
#include "ax5043_driver.h"


//#include "adf7030.h"

#define     DEBUG_SERIAL                    SD2
#define     DEBUG_CHP                       ((BaseSequentialStream *) &DEBUG_SERIAL)


axradio_address_t remoteaddr = {
	{ 0x33, 0x34, 0x00, 0x00}
};
axradio_address_mask_t localaddr = {
	{ 0x33, 0x34, 0x00, 0x00},
	{ 0xFF, 0x00, 0x00, 0x00}
};

uint8_t axradio_rxbuffer[256];  //buffer to receive radio data

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
static const SPIConfig spicfg1 =
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

static const SPIConfig spicfg2 =
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



static ax5043_drv_t ax5043_driver =
{
  &SPID1,
  &SPID2,
  AX5043_F1,
  AX5043_F2,
  AX5043_RX,
  AX5043_TX,
  LINE_SX_INT0,
  LINE_SX_INT1,
  AX5043_IDLE,
  AX5043_IDLE,
  &remoteaddr,
  &localaddr 
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

    spiStart(&SPID1, &spicfg1);
    spiStart(&SPID2, &spicfg2);
}





THD_WORKING_AREA(waAx5043_tx_thd, 1024);
THD_FUNCTION(ax5043_tx_thd, arg)
{
  (void)arg;
  uint16_t pkt_counter = 0;

  chThdSleepMilliseconds(500);



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
		ax5043_radio2_packet_tx(&ax5043_driver, demo_packet_, sizeof(demo_packet));

    chThdSleepMilliseconds(5000);
	}

}


/*
 * main loop blinks the led
 */
static void main_loop(void)
{
    chThdSleepMilliseconds(500);


	while (true)
    {
      chThdSleepMilliseconds(15000);
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

    ax5043_init(&ax5043_driver);
    chThdSleepMilliseconds(5000);
    chThdCreateStatic(waAx5043_tx_thd, sizeof(waAx5043_tx_thd), NORMALPRIO,ax5043_tx_thd, NULL);

    main_loop();
    return 0;
}
