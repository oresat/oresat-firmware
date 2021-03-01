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
#include "ax5043.h"


//#include "adf7030.h"

#define SHELL_WA_SIZE   THD_WORKING_AREA_SIZE(2048)

ax5043_address_t remoteaddr = {
    { 0x33, 0x34, 0x00, 0x00}
};
ax5043_address_mask_t localaddr = {
    { 0x33, 0x34, 0x00, 0x00},
    { 0xFF, 0x00, 0x00, 0x00}         // make it { 0x00, 0x00, 0x00, 0x00} to receive AX25 packets
};

ax5043_regval_t reg_values[] = {
    {AX5043_REG_MODULATION,     0x08},
    {AX5043_REG_ENCODING,       0x07},
    {AX5043_REG_FRAMING,        0x14},
    //{AX5043_REG_FEC,            0x13},
    {AX5043_REG_CRCINIT3,       0x00},
    {AX5043_REG_CRCINIT2,       0x00},
    {AX5043_REG_CRCINIT1,       0xFF},
    {AX5043_REG_CRCINIT0,       0xFF},
    {AX5043_REG_PINFUNCSYSCLK,  0x01},
    {AX5043_REG_PINFUNCDCLK,    0x01},
    {AX5043_REG_PINFUNCDATA,    0x01},
    {AX5043_REG_PINFUNCANTSEL,  0x01},
    {AX5043_REG_PINFUNCPWRAMP,  0x07},
    {AX5043_REG_WAKEUPXOEARLY,  0x01},
    {AX5043_REG_IFFREQ1,        0x02},
    {AX5043_REG_IFFREQ0,        0x0C},
    {AX5043_REG_DECIMATION,     0x14},
    {AX5043_REG_RXDATARATE2,    0x00},
    {AX5043_REG_RXDATARATE1,    0x3E},
    {AX5043_REG_RXDATARATE0,    0x80},
    {AX5043_REG_MAXDROFFSET2,   0x00},
    {AX5043_REG_MAXDROFFSET1,   0x00},
    {AX5043_REG_MAXDROFFSET0,   0x00},
    {AX5043_REG_MAXRFOFFSET2,   0x80},
    {AX5043_REG_MAXRFOFFSET1,   0x01},
    {AX5043_REG_MAXRFOFFSET0,   0x2F},
    {AX5043_REG_FSKDMAX1,       0x00},
    {AX5043_REG_FSKDMAX0,       0xA6},
    {AX5043_REG_FSKDMIN1,       0xFF},
    {AX5043_REG_FSKDMIN0,       0x5A},
    {AX5043_REG_AMPLFILTER,     0x00},
    {AX5043_REG_RXPARAMSETS,    0xF4},
    {AX5043_REG_AGCGAIN0,       0xC5},
    {AX5043_REG_AGCTARGET0,     0x84},
    {AX5043_REG_TIMEGAIN0,      0xF8},
    {AX5043_REG_DRGAIN0,        0xF2},
    {AX5043_REG_PHASEGAIN0,     0xC3},
    {AX5043_REG_FREQUENCYGAINA0,0x0F},
    {AX5043_REG_FREQUENCYGAINB0,0x1F},
    {AX5043_REG_FREQUENCYGAINC0,0x0A},
    {AX5043_REG_FREQUENCYGAIND0,0x0A},
    {AX5043_REG_AMPLITUDEGAIN0, 0x06},
    {AX5043_REG_FREQDEV10,      0x00},
    {AX5043_REG_FREQDEV00,      0x00},
    {AX5043_REG_BBOFFSRES0,     0x00},
    {AX5043_REG_AGCGAIN1,       0xC5},
    {AX5043_REG_AGCTARGET1,     0x84},
    {AX5043_REG_AGCAHYST1,      0x00},
    {AX5043_REG_AGCMINMAX1,     0x00},
    {AX5043_REG_TIMEGAIN1,      0xF6},
    {AX5043_REG_DRGAIN1,        0xF1},
    {AX5043_REG_PHASEGAIN1,     0xC3},
    {AX5043_REG_FREQUENCYGAINA1,0x0F},
    {AX5043_REG_FREQUENCYGAINB1,0x1F},
    {AX5043_REG_FREQUENCYGAINC1,0x0A},
    {AX5043_REG_FREQUENCYGAIND1,0x0A},
    {AX5043_REG_AMPLITUDEGAIN1, 0x06},
    {AX5043_REG_FREQDEV11,      0x00},
    {AX5043_REG_FREQDEV01,      0x25},
    {AX5043_REG_FOURFSK1,       0x16},
    {AX5043_REG_BBOFFSRES1,     0x00},
    {AX5043_REG_AGCGAIN3,       0xFF},
    {AX5043_REG_AGCTARGET3,     0x84},
    {AX5043_REG_AGCAHYST3,      0x00},
    {AX5043_REG_AGCMINMAX3,     0x00},
    {AX5043_REG_TIMEGAIN3,      0xF5},
    {AX5043_REG_DRGAIN3,        0xF0},
    {AX5043_REG_PHASEGAIN3,     0xC3},
    {AX5043_REG_FREQUENCYGAINA3,0x0F},
    {AX5043_REG_FREQUENCYGAINB3,0x1F},
    {AX5043_REG_FREQUENCYGAINC3,0x0D},
    {AX5043_REG_FREQUENCYGAIND3,0x0D},
    {AX5043_REG_AMPLITUDEGAIN3, 0x06},
    {AX5043_REG_FREQDEV13,      0x00},
    {AX5043_REG_FREQDEV03,      0x25},
    {AX5043_REG_FOURFSK3,       0x16},
    {AX5043_REG_BBOFFSRES3,     0x00},
    {AX5043_REG_MODCFGF,        0x02},
    {AX5043_REG_FSKDEV2,        0x00},
    {AX5043_REG_FSKDEV1,        0x04},
    {AX5043_REG_FSKDEV0,        0x5E},
    {AX5043_REG_MODCFGA,        0x05},
    {AX5043_REG_TXRATE2,        0x00},
    {AX5043_REG_TXRATE1,        0x0D},
    {AX5043_REG_TXRATE0,        0x1B},
    {AX5043_REG_TXPWRCOEFFB1,   0x07},
    {AX5043_REG_TXPWRCOEFFB0,   0x00},
    {AX5043_REG_PLLVCOI,        0x99},
    {AX5043_REG_PLLRNGCLK,      0x05},
    {AX5043_REG_BBTUNE,         0x0F},
    {AX5043_REG_BBOFFSCAP,      0x77},
    {AX5043_REG_PKTADDRCFG,     0x00},
    {AX5043_REG_PKTLENCFG,      0x00},
    {AX5043_REG_PKTLENOFFSET,   0x15},
    {AX5043_REG_PKTMAXLEN,      0xF0},
    {AX5043_REG_MATCH0PAT3,     0xAA},
    {AX5043_REG_MATCH0PAT2,     0xCC},
    {AX5043_REG_MATCH0PAT1,     0xAA},
    {AX5043_REG_MATCH0PAT0,     0xCC},
    //{AX5043_REG_MATCH0LEN,      0x9F},
    //{AX5043_REG_MATCH0MAX,      0x1F},
    {AX5043_REG_MATCH1PAT1,     0x55},
    {AX5043_REG_MATCH1PAT0,     0x55},
    {AX5043_REG_MATCH1LEN,      0x0A},
    {AX5043_REG_MATCH1MAX,      0x0A},
    {AX5043_REG_TMGTXBOOST,     0x5B},
    {AX5043_REG_TMGTXSETTLE,    0x3E},
    {AX5043_REG_TMGRXBOOST,     0x5B},
    {AX5043_REG_TMGRXSETTLE,    0x3E},
    {AX5043_REG_TMGRXOFFSACQ,   0x00},
    {AX5043_REG_TMGRXCOARSEAGC, 0x9C},
    {AX5043_REG_TMGRXRSSI,      0x03},
    {AX5043_REG_TMGRXPREAMBLE2, 0x17},
    {AX5043_REG_RSSIABSTHR,     0xE3},
    {AX5043_REG_BGNDRSSITHR,    0x00},
    {AX5043_REG_PKTCHUNKSIZE,   0x0D},
    {AX5043_REG_PKTACCEPTFLAGS, 0x39}, //original 20, 3f=accept all errors
    {AX5043_REG_DACVALUE1,      0x00},
    {AX5043_REG_DACVALUE0,      0x00},
    {AX5043_REG_DACCONFIG,      0x00},
    {AX5043_REG_REF,            0x03},
    {AX5043_REG_XTALOSC,        0x04},
    {AX5043_REG_XTALAMPL,       0x00},
    {AX5043_REG_0xF1C,          0x07},
    {AX5043_REG_0xF21,          0x68},
    {AX5043_REG_0xF22,          0XFF},
    {AX5043_REG_0xF23,          0x84},
    {AX5043_REG_0xF26,          0x98},
    {AX5043_REG_0xF34,          0x28},
    {AX5043_REG_0xF35,          0x11},
    {AX5043_REG_0xF44,          0x25},
    {AX5043_REG_PINFUNCIRQ,     0x03},
    {AX5043_REG_PKTSTOREFLAGS,  0x14},
    {0x00, 0x00}
};

uint8_t ax5043_rxbuffer[256];  //buffer to receive radio data

const uint8_t demo_packet[] =  { 0x86, 0xA2, 0x40, 0x40, 0x40, 0x40, 0x60, 0x96, 0x8E, 0x6E, 0xB4, 0xAC, 0xAC, 0x61, 0x3F, 0xF0, 0x3E, 0x54, 0x65, 0x73, 0x74 };

char cw_message[] = "KG7ZVV Malay Das testing AX5043";
//const uint8_t framing_insert_counter = 1;    //uncomment for normal packets
const uint8_t framing_counter_pos = 0;
const uint8_t framing_insert_counter = 0;     //uncomment for Ax.25 packets


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
    LINE_AX1_CS,
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
    LINE_AX2_CS,
    // SPI cr1 data                         (see 446 ref man.)
    SPI_CR1_SPE     |                       // SPI enable
    SPI_CR1_MSTR    |                       // Master
    //SPI_CR1_BR_2    |
    SPI_CR1_BR_1    |
    SPI_CR1_BR_0   |                        // fpclk/16  approx 5Mhz? BR = 0x011
    SPI_CR1_SSM,
    0, // SPI_CR2_SSOE,
};



static AX5043Config axcfg1 =
{
  &SPID1,
  &spicfg1,
  LINE_AX1_IRQ,
  reg_values,
  &radio1_rx_mb,
  remoteaddr.addr,
  localaddr.addr,
  localaddr.mask
};

static AX5043Config axcfg2 =
{
  &SPID2,
  &spicfg2,
  LINE_AX2_IRQ,
  reg_values,
  &radio2_rx_mb,
  remoteaddr.addr,
  localaddr.addr,
  localaddr.mask
};


static AX5043Driver axd1;
static AX5043Driver axd2;

/*
 * Initialize the SPI drivers and configure the ax5043 chips
 */
static void app_init(void)
{
    sdStart(&SD2, &ser_cfg);

  /* Creating the mailboxes.*/
    chMBObjectInit(&radio1_rx_mb, radio1_rx_queue, NUM_BUFFERS);
    chMBObjectInit(&radio2_rx_mb, radio2_rx_queue, NUM_BUFFERS);

    ax5043Start(&axd1, &axcfg1);
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

    chprintf((BaseSequentialStream *)&SD2,"INFO: Sending packet %d\r\n",pkt_counter);
    ax5043_radio2_packet_tx(&ax5043_driver, demo_packet_, sizeof(demo_packet));

    chThdSleepMilliseconds(5000);
  }
  */

  // This is for CW


  for (;;) {
    chprintf((BaseSequentialStream *)&SD2,"INFO: Sending CW %d\r\n", sizeof(cw_message));

    /*ax5043_radio2_cw_tx(&ax1d, cw_message, sizeof(cw_message));*/

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
      chprintf((BaseSequentialStream *)&SD2,"INFO: rx on radio 1\r\n");
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
      chprintf((BaseSequentialStream *)&SD2,"INFO: rx on radio 2\r\n");
  }

}

/*
 * shell commands
 */
static void mmd(BaseSequentialStream *chp, int argc, char *argv[]) {

  (void)argv;
  if (argc > 0) {
    chprintf(chp, "Usage: mmd\r\n");
    return;
  }

  chprintf(chp, "testing\r\n");
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

  ax5043ObjectInit(&axd1);
  chThdSleepMilliseconds(5000);
  chThdCreateStatic(waAx5043_tx_thd, sizeof(waAx5043_tx_thd), NORMALPRIO,ax5043_tx_thd, NULL);
  chThdCreateStatic(waradio1_rx, sizeof(waradio1_rx), NORMALPRIO,radio1_rx, NULL);
  chThdCreateStatic(waradio2_rx, sizeof(waradio2_rx), NORMALPRIO,radio2_rx, NULL);

  /*
   * Shell manager initialization.
   * Event zero is shell exit.
   */
  shellInit();
  while (true) {
      shelltp1 = chThdCreateFromHeap(NULL, SHELL_WA_SIZE,
              "shell1", NORMALPRIO + 1,
              shellThread, (void *)&shell_cfg1);
      chThdWait(shelltp1);
  }
  return 0;
}
