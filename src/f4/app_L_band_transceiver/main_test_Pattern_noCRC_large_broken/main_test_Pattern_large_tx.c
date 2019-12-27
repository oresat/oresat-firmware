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

/******************************************************************************************
 *  Modification Log
 *  04/15/2018    Malay Das    Initial Code.
 *  11/24/2019    Vigely M.    AX5043 config for custom eval board. Include Si4112 code.
 *  12/22/2019    Vigely M.    Organize code for one AX5043. Add Si4112 calculations.
 *
 ******************************************************************************************/


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
#include "si41xx.h"

#define     DEBUG_SERIAL                    SD2
#define     DEBUG_CHP                       ((BaseSequentialStream *) &DEBUG_SERIAL)


// TX: fcarrier=436.500MHz dev=  2.500kHz br= 10.000kBit/s pwr=-10.0dBm
// RX: fcarrier=436.500MHz bw= 15.000kHz br= 10.000kBit/s
// XTAL reference = 16.000000 MHz
ax5043_regval_t reg_values[] = {
  {AX5043_REG_MODULATION,          0x08,common},
  {AX5043_REG_ENCODING,            0x01,common},  // INV 0x01, INV+DIFF 0x03
  {AX5043_REG_FRAMING,             0x06,common},  // HDLC 0x04, Pattern 0x06 (both NO CRC)
  {AX5043_REG_PINFUNCSYSCLK,       0x04,common},
  {AX5043_REG_PINFUNCDCLK,         0x00,common},
  {AX5043_REG_PINFUNCDATA,         0x00,common},
  {AX5043_REG_PINFUNCANTSEL,       0x01,common},
  {AX5043_REG_PINFUNCPWRAMP,       0x07,common},
  {AX5043_REG_WAKEUPXOEARLY,       0x01,common},
  {AX5043_REG_IFFREQ1,             0x03,common},
  {AX5043_REG_IFFREQ0,             0x33,common},
  {AX5043_REG_DECIMATION,          0x0D,common},
  {AX5043_REG_RXDATARATE2,         0x00,common},
  {AX5043_REG_RXDATARATE1,         0x3D,common},
  {AX5043_REG_RXDATARATE0,         0x89,common},
  {AX5043_REG_MAXDROFFSET2,        0x00,common},
  {AX5043_REG_MAXDROFFSET1,        0x00,common},
  {AX5043_REG_MAXDROFFSET0,        0x00,common},
  {AX5043_REG_MAXRFOFFSET2,        0x80,common},
  {AX5043_REG_MAXRFOFFSET1,        0x03,common},
  {AX5043_REG_MAXRFOFFSET0,        0x93,common},
  {AX5043_REG_FSKDMAX1,            0x00,common},
  {AX5043_REG_FSKDMAX0,            0xA6,common},
  {AX5043_REG_FSKDMIN1,            0xFF,common},
  {AX5043_REG_FSKDMIN0,            0x5A,common},
  {AX5043_REG_AMPLFILTER,          0x00,common},
  {AX5043_REG_RXPARAMSETS,         0xF4,common},
  {AX5043_REG_AGCGAIN0,            0xB4,common},
  {AX5043_REG_AGCTARGET0,          0x84,common},
  {AX5043_REG_TIMEGAIN0,           0xF8,common},
  {AX5043_REG_DRGAIN0,             0xF2,common},
  {AX5043_REG_PHASEGAIN0,          0xC3,common},
  {AX5043_REG_FREQUENCYGAINA0,     0x0F,common},
  {AX5043_REG_FREQUENCYGAINB0,     0x1F,common},
  {AX5043_REG_FREQUENCYGAINC0,     0x07,common},
  {AX5043_REG_FREQUENCYGAIND0,     0x07,common},
  {AX5043_REG_AMPLITUDEGAIN0,      0x06,common},
  {AX5043_REG_FREQDEV10,           0x00,common},
  {AX5043_REG_FREQDEV00,           0x00,common},
  {AX5043_REG_BBOFFSRES0,          0x00,common},
  {AX5043_REG_AGCGAIN1,            0xB4,common},
  {AX5043_REG_AGCTARGET1,          0x84,common},
  {AX5043_REG_AGCAHYST1,           0x00,common},
  {AX5043_REG_AGCMINMAX1,          0x00,common},
  {AX5043_REG_TIMEGAIN1,           0xF6,common},
  {AX5043_REG_DRGAIN1,             0xF1,common},
  {AX5043_REG_PHASEGAIN1,          0xC3,common},
  {AX5043_REG_FREQUENCYGAINA1,     0x0F,common},
  {AX5043_REG_FREQUENCYGAINB1,     0x1F,common},
  {AX5043_REG_FREQUENCYGAINC1,     0x07,common},
  {AX5043_REG_FREQUENCYGAIND1,     0x07,common},
  {AX5043_REG_AMPLITUDEGAIN1,      0x06,common},
  {AX5043_REG_FREQDEV11,           0x00,common},
  {AX5043_REG_FREQDEV01,           0x1C,common},
  {AX5043_REG_FOURFSK1,            0x16,common},
  {AX5043_REG_BBOFFSRES1,          0x00,common},
  {AX5043_REG_AGCGAIN3,            0xFF,common},
  {AX5043_REG_AGCTARGET3,          0x84,common},
  {AX5043_REG_AGCAHYST3,           0x00,common},
  {AX5043_REG_AGCMINMAX3,          0x00,common},
  {AX5043_REG_TIMEGAIN3,           0xF5,common},
  {AX5043_REG_DRGAIN3,             0xF0,common},
  {AX5043_REG_PHASEGAIN3,          0xC3,common},
  {AX5043_REG_FREQUENCYGAINA3,     0x0F,common},
  {AX5043_REG_FREQUENCYGAINB3,     0x1F,common},
  {AX5043_REG_FREQUENCYGAINC3,     0x0B,common},
  {AX5043_REG_FREQUENCYGAIND3,     0x0B,common},
  {AX5043_REG_AMPLITUDEGAIN3,      0x06,common},
  {AX5043_REG_FREQDEV13,           0x00,common},
  {AX5043_REG_FREQDEV03,           0x1C,common},
  {AX5043_REG_FOURFSK3,            0x16,common},
  {AX5043_REG_BBOFFSRES3,          0x00,common},
  {AX5043_REG_MODCFGF,             0x02,common},
  {AX5043_REG_FSKDEV2,             0x00,common},
  {AX5043_REG_FSKDEV1,             0x0A,common},
  {AX5043_REG_FSKDEV0,             0x3D,common},
  {AX5043_REG_MODCFGA,             0x05,common},  // 0x05 PA diff, 0x06 PA SE (both with RC)
  {AX5043_REG_TXRATE2,             0x00,common},
  {AX5043_REG_TXRATE1,             0x28,common},
  {AX5043_REG_TXRATE0,             0xF6,common},
  {AX5043_REG_TXPWRCOEFFB1,        0x00,common},
  {AX5043_REG_TXPWRCOEFFB0,        0xAA,common},
  {AX5043_REG_PLLVCOI,             0x98,common},
  {AX5043_REG_PLLRNGCLK,           0x03,common},
  {AX5043_REG_BBTUNE,              0x0F,common},
  {AX5043_REG_BBOFFSCAP,           0x77,common},
  {AX5043_REG_PKTADDRCFG,          0x00,common},
  {AX5043_REG_PKTLENCFG,           0xF0,common},  // 0xFx for large packet, p. 65
  {AX5043_REG_PKTLENOFFSET,        0x08,common},
  {AX5043_REG_PKTMAXLEN,           0xFF,common},  // 0xFF for large packet, p. 65
  {AX5043_REG_MATCH0PAT3,          0xAA,common},
  {AX5043_REG_MATCH0PAT2,          0xCC,common},
  {AX5043_REG_MATCH0PAT1,          0xAA,common},
  {AX5043_REG_MATCH0PAT0,          0xCC,common},
  {AX5043_REG_MATCH0LEN,           0x9F,common},  // For Pattern Match
  {AX5043_REG_MATCH0MAX,           0x1F,common},  // For Pattern Match
  {AX5043_REG_MATCH1PAT1,          0x55,common},
  {AX5043_REG_MATCH1PAT0,          0x55,common},
  {AX5043_REG_MATCH1LEN,           0x8A,common},
  {AX5043_REG_MATCH1MAX,           0x0A,common},
  {AX5043_REG_TMGTXBOOST,          0x32,common},
  {AX5043_REG_TMGTXSETTLE,         0x14,common},
  {AX5043_REG_TMGRXBOOST,          0x32,common},
  {AX5043_REG_TMGRXSETTLE,         0x14,common},
  {AX5043_REG_TMGRXOFFSACQ,        0x00,common},
  {AX5043_REG_TMGRXCOARSEAGC,      0x73,common},
  {AX5043_REG_TMGRXRSSI,           0x03,common},
  {AX5043_REG_TMGRXPREAMBLE2,      0x35,common},
  {AX5043_REG_RSSIABSTHR,          0xE3,common},
  {AX5043_REG_BGNDRSSITHR,         0x00,common},
  {AX5043_REG_PKTCHUNKSIZE,        0x0D,common},
  {AX5043_REG_PKTACCEPTFLAGS,      0x30,common},  // 0x30 for ACCPT SZF, LRGP , p. 71
  {AX5043_REG_DACVALUE1,           0x00,common},
  {AX5043_REG_DACVALUE0,           0x00,common},
  {AX5043_REG_DACCONFIG,           0x00,common},
  {AX5043_REG_REF,                 0x03,common},
  {AX5043_REG_XTALOSC,             0x04,common},
  {AX5043_REG_XTALAMPL,            0x00,common},
  {AX5043_REG_0xF1C,               0x07,common},
  {AX5043_REG_0xF21,               0x68,common},
  {AX5043_REG_0xF22,               0xFF,common},
  {AX5043_REG_0xF23,               0x84,common},
  {AX5043_REG_0xF26,               0x98,common},
  {AX5043_REG_0xF34,               0x28,common},
  {AX5043_REG_0xF35,               0x10,common},
  {AX5043_REG_0xF44,               0x25,common},
  // PINFUNCIRQ & PKTSTOREFLAGS not in RadioLab config.c, calculated in easyax5043.c
  {AX5043_REG_PINFUNCIRQ,          0x03,common},
  {AX5043_REG_PKTSTOREFLAGS,       0x14,common},
  {AX5043_REG_PLLLOOP,             0x09,tx},
  {AX5043_REG_PLLCPI,              0x02,tx},
  {AX5043_REG_PLLVCODIV,           0x24,tx},
  {AX5043_REG_XTALCAP,             0x00,tx},
  {AX5043_REG_0xF00,               0x0F,tx},
  {AX5043_REG_0xF18,               0x06,tx},
  {AX5043_REG_PLLLOOP,             0x0B,rx},
  {AX5043_REG_PLLCPI,              0x10,rx},
  {AX5043_REG_PLLVCODIV,           0x24,rx},
  {AX5043_REG_XTALCAP,             0x00,rx},
  {AX5043_REG_0xF00,               0x0F,rx},
  {AX5043_REG_0xF18,               0x02,rx},
  {AX5043_REG_TMGRXAGC,            0x00,rx_cont},
  {AX5043_REG_TMGRXPREAMBLE1,      0x00,rx_cont},
  {AX5043_REG_PKTMISCFLAGS,        0x00,rx_cont},
  {AX5043_REG_PKTADDR0,            0x32,local_address},  // 0x32 Tx, 0x33 Rx
  {AX5043_REG_PKTADDR1,            0x34,local_address},
  {AX5043_REG_PKTADDR2,            0x00,local_address},
  {AX5043_REG_PKTADDR3,            0x00,local_address},
  {AX5043_REG_PKTADDRMASK0,        0xFF,local_address},
  {AX5043_REG_PKTADDRMASK1,        0xFF,local_address},
  {AX5043_REG_PKTADDRMASK2,        0x00,local_address},
  {AX5043_REG_PKTADDRMASK3,        0x00,local_address},    
  {AX5043_REG_END,                 0x00,common}
};

ax5043_confval_t conf_values[]={
  {AXRADIO_PHY_PN9                     ,0},
  {AXRADIO_PHY_NRCHANNELS              ,1},
  {AXRADIO_PHY_CHANFREQ                ,0x1b480001},
  {AXRADIO_PHY_CHANPLLRNGINIT          ,0x0A},
  {AXRADIO_PHY_CHANVCOIINIT            ,0x98},
  {AXRADIO_PHY_CHANPLLRNG              ,1},
  {AXRADIO_PHY_CHANVCOI                ,1},
  {AXRADIO_PHY_VCOCALIB                ,0},
  {AXRADIO_PHY_MAXFREQOFFSET           ,2746},
  {AXRADIO_PHY_RSSIOFFSET              ,64},
  {AXRADIO_PHY_RSSIREFERENCE           ,314},  // 0xFA + 64
  {AXRADIO_PHY_CHANNELBUSY             ,-29},  // -93 + 64
  {AXRADIO_PHY_CS_PERIOD               ,7},
  {AXRADIO_PHY_CS_ENABLED              ,0},
  {AXRADIO_PHY_LBT_RETRIES             ,0},
  {AXRADIO_PHY_LBT_FORCETX             ,0},
  {AXRADIO_PHY_PREAMBLE_WOR_LONGLEN    ,9}, 
  {AXRADIO_PHY_PREAMBLE_WOR_LEN        ,128},
  {AXRADIO_PHY_PREAMBLE_LONGLEN        ,0},
  {AXRADIO_PHY_PREAMBLE_LEN            ,32},
  {AXRADIO_PHY_PREAMBLE_BYTE           ,0x55},
  {AXRADIO_PHY_PREAMBLE_FLAGS          ,0x38},
  {AXRADIO_PHY_PREAMBLE_APPENDBITS     ,0},
  {AXRADIO_PHY_PREAMBLE_APPENDPATTERN  ,0x00},
  {AXRADIO_FRAMING_MACLEN              ,2},
  {AXRADIO_FRAMING_ADDRLEN             ,2},
  {AXRADIO_FRAMING_DESTADDRPOS         ,0},
  {AXRADIO_FRAMING_SOURCEADDRPOS       ,0xFF},
  {AXRADIO_FRAMING_LENPOS              ,0},
  {AXRADIO_FRAMING_LENOFFS             ,8},
  {AXRADIO_FRAMING_LENMASK             ,0x00},
  {AXRADIO_FRAMING_SWCRCLEN            ,0},
  {AXRADIO_FRAMING_SYNCLEN             ,32},
  {AXRADIO_FRAMING_SYNCWORD3           ,0x33},
  {AXRADIO_FRAMING_SYNCWORD2           ,0x55},
  {AXRADIO_FRAMING_SYNCWORD1           ,0x33},
  {AXRADIO_FRAMING_SYNCWORD0           ,0x55},
  {AXRADIO_FRAMING_SYNCFLAGS           ,0x38},
  {AXRADIO_FRAMING_ENABLE_SFDCALLBACK  ,0},
  {AXRADIO_FRAMING_ACK_TIMEOUT         ,11},
  {AXRADIO_FRAMING_ACK_DELAY           ,313},
  {AXRADIO_FRAMING_ACK_RETRANSMISSIONS ,0},
  {AXRADIO_FRAMING_ACK_SEQNRPOS        ,0xFF},
  {AXRADIO_FRAMING_MINPAYLOADLEN       ,0},
  {AXRADIO_WOR_PERIOD                  ,128},
  {AXRADIO_PHY_INNERFREQLOOP           ,0},
  {AXRADIO_PHY_END                     ,0}
};


// Serial Driver Configuration
static SerialConfig ser_cfg =
{
    115200,                                 //Baud rate
    0,                                      //
    0,                                      //
    0,                                      //
};


// SPI Configuration
static const SPIConfig spicfg1 =
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


// Mailboxes to receive the radio packets
#define NUM_BUFFERS 16
static msg_t radio1_rx_queue[NUM_BUFFERS];
static mailbox_t radio1_rx_mb;


// Radio driver configurations
static AX5043Config axcfg1 =
{
  &SPID2,
  LINE_SX_INT0,
  reg_values,
  conf_values,
  AX5043_MODE_TX, // AX5043_MODE_CW, AX5043_MODE_TX, AX5043_MODE_RX
  &radio1_rx_mb,
};
AX5043Driver axd1;


// Initialize app ??
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


// Initialize Si4112 Synthesizer
static void synth_init(void)
{
    uint32_t freq = 760000; // Fc in kHz
    uint16_t phase = 500;   // PD in kHz, 1 to 1000
    uint8_t pllref = 16;    // External PLL reference

    uint32_t ndiv;
    uint32_t rdiv;

    rdiv = pllref * 1000 / phase;
    ndiv = freq * rdiv / (1000 * pllref);

    palSetLine(LINE_SI_SENB);
    palSetLine(LINE_SI_SDATA);
    palSetLine(LINE_SI_SCLK);
    si_write_reg(SI41XX_REG_MAIN_CONFIG, 0b000011000000000100);
    si_write_reg(SI41XX_REG_PHASE_GAIN,  0b000000000000000000);
    si_write_reg(SI41XX_REG_PWRDOWN,     0b000000000000000000);
    si_write_reg(SI41XX_REG_IF_NDIV, ndiv);
    si_write_reg(SI41XX_REG_IF_RDIV, rdiv);
    si_write_reg(SI41XX_REG_PWRDOWN,     0b000000000000000010);
    palSetLine(LINE_SI_SENB);
    palSetLine(LINE_SI_SDATA);
    palSetLine(LINE_SI_SCLK);

    chThdSleepMilliseconds(500);
}


// Initialize SPI and AX5043 driver
static void radio_init(void)
{
    chThdSleepMilliseconds(1000);
    spiStart(&SPID2, &spicfg1);
    chThdSleepMilliseconds(1000);

    // Creating the mailboxes.
    chMBObjectInit(&radio1_rx_mb, radio1_rx_queue, NUM_BUFFERS);
    
    //initiating radio driver
    ax5043ObjectInit(&axd1);
    ax5043Start(&axd1, &axcfg1);

    chThdSleepMilliseconds(500);
}


const struct axradio_address remoteaddr_tx = {
    { 0x33, 0x34, 0x00, 0x00}
};


// Tx Short Packet
static void tx_short(void)
{
    uint8_t tx_error;
    uint16_t packet_len = 16;

    uint8_t demo_packet[packet_len];
    for (uint16_t i = 0; i < packet_len; ++i)
    {
        demo_packet[i] = (uint8_t)(i & 0xFF);
    }

    chprintf(DEBUG_CHP,"INFO: Tx wait...\r\n");
    chThdSleepMilliseconds(1000);
    chprintf(DEBUG_CHP,"INFO: Packet size %d\r\n",sizeof(demo_packet));
    // chprintf(DEBUG_CHP,"INFO: Packet data\r\n");
    // for (uint16_t i = 0; i < packet_len; ++i)
    // {
    //     chprintf(DEBUG_CHP,"[%d] = 0x%02X\r\n", i, demo_packet[i]);
    // }
    tx_error=transmit_packet(&axd1, &remoteaddr_tx, demo_packet, sizeof(demo_packet));
    chprintf(DEBUG_CHP,"INFO: Tx return = 0x%02X\r\n", tx_error);
    chprintf(DEBUG_CHP,"INFO: Status %d\r\n", (int)axd1.status_code);
    chprintf(DEBUG_CHP,"INFO: Error %d\r\n\r\n", (int)axd1.error_code);

    chThdSleepMilliseconds(10000);

}


// Tx Long Packet
static void tx_long(void)
{
    uint8_t tx_error;
    uint16_t packet_len = 64;

    uint8_t demo_packet[packet_len];
    for (uint16_t i = 0; i < packet_len; ++i)
    {
        demo_packet[i] = (uint8_t)(i & 0xFF);
    }

    chprintf(DEBUG_CHP,"INFO: Tx wait...\r\n");
    chThdSleepMilliseconds(1000);
    chprintf(DEBUG_CHP,"INFO: Packet size %d\r\n",sizeof(demo_packet));
    // chprintf(DEBUG_CHP,"INFO: Packet data\r\n");
    // for (uint16_t i = 0; i < packet_len; ++i)
    // {
    //     chprintf(DEBUG_CHP,"[%d] = 0x%02X\r\n", i, demo_packet[i]);
    // }
    tx_error=transmit_packet(&axd1, &remoteaddr_tx, demo_packet, sizeof(demo_packet));
    chprintf(DEBUG_CHP,"INFO: Tx return = 0x%02X\r\n", tx_error);
    chprintf(DEBUG_CHP,"INFO: Status %d\r\n", (int)axd1.status_code);
    chprintf(DEBUG_CHP,"INFO: Error %d\r\n\r\n", (int)axd1.error_code);
}


// Tx Test Packets
static void tx_test(void)
{

    uint8_t tx_error;

    for (int j = 245; j < 248; ++j)
    {

        uint8_t ret_value[3]={0,0,0};
        uint8_t fifo_stat;

        uint16_t packet_len = j;

        uint8_t demo_packet[packet_len];
        for (uint16_t i = 0; i < packet_len; ++i)
        {
            demo_packet[i] = (uint8_t)(i & 0xFF);
        }

        chprintf(DEBUG_CHP,"INFO: Tx packet length %d\r\n",packet_len);
        tx_error=transmit_packet(&axd1, &remoteaddr_tx, demo_packet, packet_len);
        chprintf(DEBUG_CHP,"INFO: Tx return = 0x%02X\r\n", tx_error);
        chprintf(DEBUG_CHP,"INFO: Status %d\r\n", (int)axd1.status_code);
        chprintf(DEBUG_CHP,"INFO: Error %d\r\n\r\n", (int)axd1.error_code);

        fifo_stat=ax5043_read_reg(&SPID2,AX5043_REG_FIFOSTAT, (uint8_t)0x00, ret_value);
        chprintf(DEBUG_CHP,"INFO: FIFOSTAT = 0x%02X\r\n", fifo_stat);
        chThdSleepMilliseconds(500);
        fifo_stat=ax5043_read_reg(&SPID2,AX5043_REG_FIFOSTAT, (uint8_t)0x00, ret_value);
        chprintf(DEBUG_CHP,"INFO: FIFOSTAT = 0x%02X\r\n\r\n", fifo_stat);

        chThdSleepMilliseconds(1000);

    }

}


// Main loop - Blink LED
static void main_loop(void)
{
    chprintf(DEBUG_CHP,"INFO: Blink LED\r\n");
    palSetLineMode(LINE_LED_GREEN,PAL_MODE_OUTPUT_PUSHPULL);
    while (true)
    {
        palClearLine(LINE_LED_GREEN);
        chThdSleepMilliseconds(500);
        palSetLine(LINE_LED_GREEN);
        chThdSleepMilliseconds(500);
        chprintf(DEBUG_CHP,".");
    }
}

// Main program
int main(void)
{
    halInit();
    chSysInit();
    app_init();

    // Initialize SPI and AX5043 driver
    radio_init();

    // Initialize Si4112 Synthesizer
    // synth_init();

    tx_short();
    // tx_long();
    tx_test();

    // Main loop
    main_loop();

    return 0;
}
