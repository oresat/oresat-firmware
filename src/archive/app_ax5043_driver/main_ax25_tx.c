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

#define     DEBUG_SERIAL                    SD2
#define     DEBUG_CHP                       ((BaseSequentialStream *) &DEBUG_SERIAL)

const struct axradio_address remoteaddr_tx = {
	{ 0x33, 0x34, 0x00, 0x00}
};

const uint8_t demo_packet[] =  { 0x86, 0xA2, 0x40, 0x40, 0x40, 0x40, 0x60, 0x96, 0x8E, 0x6E, 0xB4, 0xAC, 0xAC, 0x61, 0x3F, 0xF0, 0x3E, 0x54, 0x65, 0x73, 0x74 };
const uint8_t framing_insert_counter = 0;
const uint8_t framing_counter_pos = 0;

// TX: fcarrier=435.500MHz dev=  3.200kHz br=  9.600kBit/s pwr= 10.0dBm
// RX: fcarrier=435.500MHz bw= 14.400kHz br=  9.600kBit/s
ax5043_regval_t reg_values[] = {
  {AX5043_REG_MODULATION,     0x08,common},
  {AX5043_REG_ENCODING,       0x07,common},
  {AX5043_REG_FRAMING,        0x14,common},
  {AX5043_REG_CRCINIT3,       0x00,common},
  {AX5043_REG_CRCINIT2,       0x00,common},
  {AX5043_REG_CRCINIT1,       0xFF,common},
  {AX5043_REG_CRCINIT0,       0xFF,common},
  {AX5043_REG_PINFUNCSYSCLK,  0x01,common},
  {AX5043_REG_PINFUNCDCLK,    0x01,common},
  {AX5043_REG_PINFUNCDATA,    0x01,common},
  {AX5043_REG_PINFUNCANTSEL,  0x01,common},
  {AX5043_REG_PINFUNCPWRAMP,  0x07,common},
  {AX5043_REG_WAKEUPXOEARLY,  0x01,common},
  {AX5043_REG_IFFREQ1,        0x02,common},
  {AX5043_REG_IFFREQ0,        0x0C,common},
  {AX5043_REG_DECIMATION,     0x14,common},
  {AX5043_REG_RXDATARATE2,    0x00,common},
  {AX5043_REG_RXDATARATE1,    0x3E,common},
  {AX5043_REG_RXDATARATE0,    0x80,common},
  {AX5043_REG_MAXDROFFSET2,   0x00,common},
  {AX5043_REG_MAXDROFFSET1,   0x00,common},
  {AX5043_REG_MAXDROFFSET0,   0x00,common},
  {AX5043_REG_MAXRFOFFSET2,   0x80,common},
  {AX5043_REG_MAXRFOFFSET1,   0x01,common},
  {AX5043_REG_MAXRFOFFSET0,   0x2F,common},
  {AX5043_REG_FSKDMAX1,       0x00,common},
  {AX5043_REG_FSKDMAX0,       0xA6,common},
  {AX5043_REG_FSKDMIN1,       0xFF,common},
  {AX5043_REG_FSKDMIN0,       0x5A,common},
  {AX5043_REG_AMPLFILTER,     0x00,common},
  {AX5043_REG_RXPARAMSETS,    0xF4,common},
  {AX5043_REG_AGCGAIN0,       0xC5,common},
  {AX5043_REG_AGCTARGET0,     0x84,common},
  {AX5043_REG_TIMEGAIN0,      0xF8,common},
  {AX5043_REG_DRGAIN0,        0xF2,common},
  {AX5043_REG_PHASEGAIN0,     0xC3,common},
  {AX5043_REG_FREQUENCYGAINA0,0x0F,common},
  {AX5043_REG_FREQUENCYGAINB0,0x1F,common},
  {AX5043_REG_FREQUENCYGAINC0,0x0A,common},
  {AX5043_REG_FREQUENCYGAIND0,0x0A,common},
  {AX5043_REG_AMPLITUDEGAIN0, 0x06,common},
  {AX5043_REG_FREQDEV10,      0x00,common},
  {AX5043_REG_FREQDEV00,      0x00,common},
  {AX5043_REG_BBOFFSRES0,     0x00,common},
  {AX5043_REG_AGCGAIN1,       0xC5,common},
  {AX5043_REG_AGCTARGET1,     0x84,common},
  {AX5043_REG_AGCAHYST1,      0x00,common},
  {AX5043_REG_AGCMINMAX1,     0x00,common},
  {AX5043_REG_TIMEGAIN1,      0xF6,common},
  {AX5043_REG_DRGAIN1,        0xF1,common},
  {AX5043_REG_PHASEGAIN1,     0xC3,common},
  {AX5043_REG_FREQUENCYGAINA1,0x0F,common},
  {AX5043_REG_FREQUENCYGAINB1,0x1F,common},
  {AX5043_REG_FREQUENCYGAINC1,0x0A,common},
  {AX5043_REG_FREQUENCYGAIND1,0x0A,common},
  {AX5043_REG_AMPLITUDEGAIN1, 0x06,common},
  {AX5043_REG_FREQDEV11,      0x00,common},
  {AX5043_REG_FREQDEV01,      0x25,common},
  {AX5043_REG_FOURFSK1,       0x16,common},
  {AX5043_REG_BBOFFSRES1,     0x00,common},
  {AX5043_REG_AGCGAIN3,       0xFF,common},
  {AX5043_REG_AGCTARGET3,     0x84,common},
  {AX5043_REG_AGCAHYST3,      0x00,common},
  {AX5043_REG_AGCMINMAX3,     0x00,common},
  {AX5043_REG_TIMEGAIN3,      0xF5,common},
  {AX5043_REG_DRGAIN3,        0xF0,common},
  {AX5043_REG_PHASEGAIN3,     0xC3,common},
  {AX5043_REG_FREQUENCYGAINA3,0x0F,common},
  {AX5043_REG_FREQUENCYGAINB3,0x1F,common},
  {AX5043_REG_FREQUENCYGAINC3,0x0D,common},
  {AX5043_REG_FREQUENCYGAIND3,0x0D,common},
  {AX5043_REG_AMPLITUDEGAIN3, 0x06,common},
  {AX5043_REG_FREQDEV13,      0x00,common},
  {AX5043_REG_FREQDEV03,      0x25,common},
  {AX5043_REG_FOURFSK3,       0x16,common},
  {AX5043_REG_BBOFFSRES3,     0x00,common},
  {AX5043_REG_MODCFGF,        0x02,common},
  {AX5043_REG_FSKDEV2,        0x00,common},
  {AX5043_REG_FSKDEV1,        0x04,common},
  {AX5043_REG_FSKDEV0,        0x5E,common},
  {AX5043_REG_MODCFGA,        0x05,common},
  {AX5043_REG_TXRATE2,        0x00,common},
  {AX5043_REG_TXRATE1,        0x0D,common},
  {AX5043_REG_TXRATE0,        0x1B,common},
  {AX5043_REG_TXPWRCOEFFB1,   0x07,common},
  {AX5043_REG_TXPWRCOEFFB0,   0x00,common},
  {AX5043_REG_PLLVCOI,        0x99,common},
  {AX5043_REG_PLLRNGCLK,      0x05,common},
  {AX5043_REG_BBTUNE,         0x0F,common},
  {AX5043_REG_BBOFFSCAP,      0x77,common},
  {AX5043_REG_PKTADDRCFG,     0x00,common},
  {AX5043_REG_PKTLENCFG,      0x00,common},
  {AX5043_REG_PKTLENOFFSET,   0x15,common},
  {AX5043_REG_PKTMAXLEN,      0xF0,common},
  {AX5043_REG_MATCH0PAT3,     0xAA,common},
  {AX5043_REG_MATCH0PAT2,     0xCC,common},
  {AX5043_REG_MATCH0PAT1,     0xAA,common},
  {AX5043_REG_MATCH0PAT0,     0xCC,common},
  {AX5043_REG_MATCH1PAT1,     0x55,common},
  {AX5043_REG_MATCH1PAT0,     0x55,common},
  {AX5043_REG_MATCH1LEN,      0x0A,common},
  {AX5043_REG_MATCH1MAX,      0x0A,common},
  {AX5043_REG_TMGTXBOOST,     0x5B,common},
  {AX5043_REG_TMGTXSETTLE,    0x3E,common},
  {AX5043_REG_TMGRXOFFSACQ,   0x00,common},
  {AX5043_REG_TMGRXCOARSEAGC, 0x9C,common},
  {AX5043_REG_TMGRXRSSI,      0x03,common},
  {AX5043_REG_TMGRXPREAMBLE2, 0x17,common},
  {AX5043_REG_RSSIABSTHR,     0xE3,common},
  {AX5043_REG_BGNDRSSITHR,    0x00,common},
  {AX5043_REG_PKTCHUNKSIZE,   0x0D,common},
  {AX5043_REG_PKTACCEPTFLAGS, 0x39,common},
  {AX5043_REG_DACVALUE1,      0x00,common},
  {AX5043_REG_DACVALUE0,      0x00,common},
  {AX5043_REG_DACCONFIG,      0x00,common},
  {AX5043_REG_REF,            0x03,common},
  {AX5043_REG_XTALOSC,        0x04,common},
  {AX5043_REG_XTALAMPL,       0x00,common},
  {AX5043_REG_0xF1C,          0x07,common},
  {AX5043_REG_0xF21,          0x68,common},
  {AX5043_REG_0xF22,          0XFF,common},
  {AX5043_REG_0xF23,          0x84,common},
  {AX5043_REG_0xF26,          0x98,common},
  {AX5043_REG_0xF34,          0x28,common},
  {AX5043_REG_0xF35,          0x11,common},
  {AX5043_REG_0xF44,          0x25,common},
  {AX5043_REG_PINFUNCIRQ,     0x03,common},
  {AX5043_REG_PKTSTOREFLAGS,  0x14,common},
  {AX5043_REG_PLLLOOP,        0x09,tx},
  {AX5043_REG_PLLCPI,         0x02,tx},
  {AX5043_REG_PLLVCODIV,      0x24,tx},
  {AX5043_REG_XTALCAP,        0x00,tx},
  {AX5043_REG_0xF00,          0x0F,tx},
  {AX5043_REG_0xF18,          0x06,tx},
  {AX5043_REG_PLLLOOP,        0x0B,rx},
  {AX5043_REG_PLLCPI,         0x10,rx},
  {AX5043_REG_PLLVCODIV,      0x25,rx},
  {AX5043_REG_XTALCAP,        0x00,rx},
  {AX5043_REG_0xF00,          0x0F,rx},
  {AX5043_REG_0xF18,          0x02,rx},
  {AX5043_REG_TMGRXAGC,       0x00,rx_cont},
  {AX5043_REG_TMGRXPREAMBLE1, 0x00,rx_cont},
  {AX5043_REG_PKTMISCFLAGS,   0x00,rx_cont},
  {AX5043_REG_PKTADDR0,       0x00,local_address},
  {AX5043_REG_PKTADDR1,       0x00,local_address},
  {AX5043_REG_PKTADDR2,       0x00,local_address},
  {AX5043_REG_PKTADDR3,       0x00,local_address},
  {AX5043_REG_PKTADDRMASK0,   0x00,local_address},
  {AX5043_REG_PKTADDRMASK1,   0x00,local_address},
  {AX5043_REG_PKTADDRMASK2,   0x00,local_address},
  {AX5043_REG_PKTADDRMASK3,   0x00,local_address},
  {AX5043_REG_END,            0x00,common}
};


ax5043_confval_t conf_values[]={
  {AXRADIO_PHY_PN9                     ,0},
  {AXRADIO_PHY_NRCHANNELS              ,1},
  {AXRADIO_PHY_CHANFREQ                ,0X0912AAAB },
  {AXRADIO_PHY_CHANPLLRNGINIT          ,0X0A },
  {AXRADIO_PHY_CHANVCOIINIT            ,0X98},
  {AXRADIO_PHY_CHANPLLRNG              ,0},
  {AXRADIO_PHY_CHANVCOI                ,0},
  {AXRADIO_PHY_VCOCALIB                ,0},
  {AXRADIO_PHY_MAXFREQOFFSET           ,913},
  {AXRADIO_PHY_RSSIOFFSET              ,64},
  {AXRADIO_PHY_RSSIREFERENCE           ,313},
  {AXRADIO_PHY_CHANNELBUSY             ,-23},
  {AXRADIO_PHY_CS_PERIOD               ,7},
  {AXRADIO_PHY_CS_ENABLED              ,0},
  {AXRADIO_PHY_LBT_RETRIES             ,0},
  {AXRADIO_PHY_LBT_FORCETX             ,0},
  {AXRADIO_PHY_PREAMBLE_WOR_LONGLEN    ,9},
  {AXRADIO_PHY_PREAMBLE_WOR_LEN        ,40},
  {AXRADIO_PHY_PREAMBLE_LONGLEN        ,0},
  {AXRADIO_PHY_PREAMBLE_LEN            ,40},
  {AXRADIO_PHY_PREAMBLE_BYTE           ,0X7E},
  {AXRADIO_PHY_PREAMBLE_FLAGS          ,0X18},
  {AXRADIO_PHY_PREAMBLE_APPENDBITS     ,0},
  {AXRADIO_PHY_PREAMBLE_APPENDPATTERN  ,0X00},
  {AXRADIO_FRAMING_MACLEN              ,0},
  {AXRADIO_FRAMING_ADDRLEN             ,0},
  {AXRADIO_FRAMING_DESTADDRPOS         ,0},
  {AXRADIO_FRAMING_SOURCEADDRPOS       ,0XFF},
  {AXRADIO_FRAMING_LENPOS              ,0},
  {AXRADIO_FRAMING_LENOFFS             ,21},
  {AXRADIO_FRAMING_LENMASK             ,0X00},
  {AXRADIO_FRAMING_SWCRCLEN            ,0},
  {AXRADIO_FRAMING_SYNCLEN             ,32},
  {AXRADIO_FRAMING_SYNCWORD0           ,0XCC},
  {AXRADIO_FRAMING_SYNCWORD1           ,0XAA},
  {AXRADIO_FRAMING_SYNCWORD2           ,0XCC},
  {AXRADIO_FRAMING_SYNCWORD3           ,0XAA},
  {AXRADIO_FRAMING_SYNCFLAGS           ,0X18},
  {AXRADIO_FRAMING_ENABLE_SFDCALLBACK  ,0},
  {AXRADIO_FRAMING_ACK_TIMEOUT         ,8},
  {AXRADIO_FRAMING_ACK_DELAY           ,313},
  {AXRADIO_FRAMING_ACK_RETRANSMISSIONS ,0},
  {AXRADIO_FRAMING_ACK_SEQNRPOS        ,0XFF},
  {AXRADIO_FRAMING_MINPAYLOADLEN       ,0},
  {AXRADIO_WOR_PERIOD                  ,128},
  {AXRADIO_PHY_INNERFREQLOOP           ,0},
  {AXRADIO_PHY_END                     ,0}
};

uint8_t axradio_rxbuffer[256];  //buffer to receive radio data

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
    0
};

//mailboxes to receive the radio packets
#define NUM_BUFFERS 16
static msg_t radio1_rx_queue[NUM_BUFFERS];
static mailbox_t radio1_rx_mb;


//Radio driver configurations

static AX5043Config axcfg1 =
{
  &SPID2,
  LINE_SX_INT0,
  reg_values,
  conf_values,
  AX5043_MODE_TX,
  &radio1_rx_mb
};
AX5043Driver axd1;

/*
 * Initialize the SPI drivers and configure the ax5043 chips
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

    spiStart(&SPID1, &spicfg_rx);
    spiStart(&SPID2, &spicfg_tx);

    // Creating the mailboxes.
    chMBObjectInit(&radio1_rx_mb, radio1_rx_queue, NUM_BUFFERS);

    //initiating radio driver
    ax5043ObjectInit(&axd1);
    ax5043Start(&axd1, &axcfg1);



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
		transmit_packet(&axd1, &remoteaddr_tx, demo_packet_, sizeof(demo_packet));

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

    chThdSleepMilliseconds(500);

    main_loop();
    return 0;
}
