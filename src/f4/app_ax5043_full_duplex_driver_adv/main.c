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
 *     08/09/2019    Malay Das    Initial Driver.
 *     08/23/2019    Malay Das    Add mailbox functionality.
 ***************************************************/


/*
 * Include Files
 */
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "ch.h"
#include "hal.h"
#include "shell.h"

#include "chprintf.h"
#include "ax5043_common.h"
#include "ax5043_setup.h"
#include "ax5043_driver.h"


//#include "adf7030.h"

#define     DEBUG_SERIAL                    SD2
#define     DEBUG_CHP                       ((BaseSequentialStream *) &DEBUG_SERIAL)

#define SHELL_WA_SIZE   THD_WORKING_AREA_SIZE(2048)


axradio_address_t remoteaddr = {
	{ 0x33, 0x34, 0x00, 0x00}
};
axradio_address_mask_t localaddr = {
	{ 0x33, 0x34, 0x00, 0x00},
	{ 0xFF, 0x00, 0x00, 0x00}         // make it { 0x00, 0x00, 0x00, 0x00} to receive AX25 packets
};

uint8_t axradio_rxbuffer[256];  //buffer to receive radio data

const uint8_t demo_packet[] =  { 0x86, 0xA2, 0x40, 0x40, 0x40, 0x40, 0x60, 0x96, 0x8E, 0x6E, 0xB4, 0xAC, 0xAC, 0x61, 0x3F, 0xF0, 0x3E, 0x54, 0x65, 0x73, 0x74 };

char cw_message[] = "KG7ZVV Malay Das testing AX5043";
//const uint8_t framing_insert_counter = 1;    //uncomment for normal packets
const uint8_t framing_counter_pos = 0;
const uint8_t framing_insert_counter = 0;     //uncomment for Ax.25 packets


//semaphores to indicate idle/busy radio
binary_semaphore_t radio1_bsem;
binary_semaphore_t radio2_bsem;


//mailboxes to receive the radio packets
#define NUM_BUFFERS 16

static msg_t radio1_rx_queue[NUM_BUFFERS];
static mailbox_t radio1_rx_mb;
static msg_t radio2_rx_queue[NUM_BUFFERS];
static mailbox_t radio2_rx_mb;


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
  AX5043_F4,
  AX5043_RX,
  AX5043_TX,
  LINE_SX_INT0,
  LINE_SX_INT1,
  &radio1_bsem,
  &radio2_bsem,
  &remoteaddr,
  &localaddr,
  &radio1_rx_mb,
  &radio2_rx_mb
};

/*
 * Initialize the SPI drivers and configure the ax5043 chips
 */
static void app_init(void)
{
 // Start up debug output, chprintf(DEBUG_CHP,...)
    sdStart(&DEBUG_SERIAL, &ser_cfg);

    spiStart(&SPID1, &spicfg1);
    spiStart(&SPID2, &spicfg2);

  /* Creating the mailboxes.*/
    chMBObjectInit(&radio1_rx_mb, radio1_rx_queue, NUM_BUFFERS);
    chMBObjectInit(&radio2_rx_mb, radio2_rx_queue, NUM_BUFFERS);
}





THD_WORKING_AREA(waAx5043_tx_thd, 1024);
THD_FUNCTION(ax5043_tx_thd, arg)
{
  (void)arg;
  uint16_t pkt_counter = 0;
    uint8_t ret_value[3]={0,0,0};

  chThdSleepMilliseconds(500);


/* //This is for packet
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
  */

  // This is for CW


  for (;;) {
    chprintf(DEBUG_CHP,"INFO: Sending CW %d\r\n", sizeof(cw_message));

    ax5043_radio2_cw_tx(&ax5043_driver, cw_message, sizeof(cw_message));

    chThdSleepMilliseconds(500);
  }

}


THD_WORKING_AREA(waradio1_rx, 1024);
THD_FUNCTION(radio1_rx, arg)
{
  (void)arg;

  while (true) {
    msg_t pbuf;
    /* Waiting for radio1 rx buffer.*/
    msg_t msg = chMBFetchTimeout(&radio1_rx_mb, &pbuf, TIME_MS2I(10000));
    if (msg == MSG_OK)
      chprintf(DEBUG_CHP,"INFO: rx on radio 1\r\n");
  }

}

THD_WORKING_AREA(waradio2_rx, 1024);
THD_FUNCTION(radio2_rx, arg)
{
  (void)arg;

  while (true) {
    msg_t pbuf;
    /* Waiting for radio1 rx buffer.*/
    msg_t msg = chMBFetchTimeout(&radio2_rx_mb, &pbuf, TIME_MS2I(10000));
    if (msg == MSG_OK)
      chprintf(DEBUG_CHP,"INFO: rx on radio 2\r\n");
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
 * shell commands
 */
static void mmd(BaseSequentialStream *sd, int argc, char *argv[]) {

  (void)argv;
  if (argc > 0) {
    chprintf(sd, "Usage: mmd\r\n");
    return;
  }

  chprintf(sd, "testing\r\n");
}


static const ShellCommand commands[] = {
  {"mmd", mmd},
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
  thread_t *shelltp1;

  halInit();
  chSysInit();
  app_init();

  ax5043_init(&ax5043_driver);
  chThdSleepMilliseconds(5000);
  chThdCreateStatic(waAx5043_tx_thd, sizeof(waAx5043_tx_thd), NORMALPRIO,ax5043_tx_thd, NULL);
  chThdCreateStatic(waradio1_rx, sizeof(waradio1_rx), NORMALPRIO,radio1_rx, NULL);
  chThdCreateStatic(waradio2_rx, sizeof(waradio2_rx), NORMALPRIO,radio2_rx, NULL);

  /*
   * Shell manager initialization.
   * Event zero is shell exit.
   */
  shellInit();
  shelltp1 = chThdCreateFromHeap(NULL, SHELL_WA_SIZE,
                                       "shell1", NORMALPRIO + 1,
                                       shellThread, (void *)&shell_cfg1);

  main_loop();
  return 0;
}
