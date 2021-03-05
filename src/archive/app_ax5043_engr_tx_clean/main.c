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
#include "ax5043_engr.h"


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
 * Initialize the SPI drivers and configure the adf7030 chips
 */
static void app_init(void)
{

    uint16_t pkt_counter = 0;

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

    chThdSleepMilliseconds(1000);
    spiStart(&SPID1, &spicfg_rx);
    spiStart(&SPID2, &spicfg_tx);
	//spiSelect(&SPID2);
    chThdSleepMilliseconds(1000);



    //uint16_t reg=0;
    //uint8_t value=0;
    //uint8_t value1=0x55;
    //uint8_t ret_value[3]={0,0,0};
    //int i;


    chprintf(DEBUG_CHP, "Configuring AX5043\r\n");
    chThdSleepMilliseconds(50);
    ax5043_init(&SPID2);
    ax5043_set_addr(&SPID2, localaddr_tx);
    ax5043_prepare_tx(&SPID2);
    chprintf(DEBUG_CHP, "done reseting AX5043\r\n");


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
		transmit_packet(&SPID2, &remoteaddr_tx, demo_packet_, sizeof(demo_packet));

        chThdSleepMilliseconds(3000);
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

    // Enabling events on both edges of the button line.*/
    //palEnableLineEvent(GPIOC_SX_DIO3, PAL_EVENT_MODE_RISING_EDGES);

	//chThdCreateStatic(waThread_sx1236_rx,      sizeof(waThread_sx1236_rx),   NORMALPRIO, Thread_sx1236_rx, NULL);
    //chThdSleepMilliseconds(500);
    //chThdCreateStatic(waThread_sx1236_tx,      sizeof(waThread_sx1236_tx),   NORMALPRIO, Thread_sx1236_tx, NULL);
    chThdSleepMilliseconds(500);

    main_loop();
    return 0;
}
