/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

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

/* ChibiOS header files */
#include "ch.h"
#include "hal.h"
#include "shell.h"

/* Project header files */
#include "oresat.h"
#include "wdt.h"
#include "opd.h"
#include "time_sync.h"
#include "CO_master.h"
#include "si41xx.h"
#include "ax5043.h"
#ifdef SHELL_ENABLE
#include "cmd.h"
#endif

/*
static const oresat_node_t nodes[] = {
    {0x02, 0x00, 2000, "Battery 1"},
    {0x03, 0x00, 2000, "Battery 2"},
    {0x04, 0x00, 2000, "Solar Panel 1"},
    {0x05, 0x00, 2000, "Solar Panel 2"},
    {0x06, 0x00, 2000, "Solar Panel 3"},
    {0x07, 0x00, 2000, "Solar Panel 4"},
    {0x08, 0x00, 2000, "Solar Panel 5"},
    {0x09, 0x00, 2000, "Solar Panel 6"},
    {0x0A, 0x00, 2000, "Solar Panel 7"},
    {0x0B, 0x00, 2000, "Solar Panel 8"},
    {0x31, 0x18, 2000, "Protocard 1"},
    {0x32, 0x19, 2000, "Protocard 2"},
    {0x33, 0x1A, 2000, "Protocard 3"},
    {0x11, 0x1D, 2000, "Star Tracker"}
};
*/

static const SPIConfig lband_spicfg = {
    false,
    NULL,                                   // Operation complete callback
    LINE_LBAND_CS,
    // SPI cr1 data                            (see 446 ref man.)
    SPI_CR1_SPE     |                       // SPI enable
    SPI_CR1_MSTR    |                       // Master
    //SPI_CR1_BR_2    |
    SPI_CR1_BR_1    |
    SPI_CR1_BR_0   |                        // fpclk/16  approx 5Mhz? BR = 0x011
    SPI_CR1_SSM,
    0, // SPI_CR2_SSOE,
};

static const SPIConfig uhf_spicfg = {
    false,
    NULL,                                   // Operation complete callback
    LINE_UHF_CS,
    // SPI cr1 data                         (see 446 ref man.)
    SPI_CR1_SPE     |                       // SPI enable
    SPI_CR1_MSTR    |                       // Master
    //SPI_CR1_BR_2    |
    SPI_CR1_BR_1    |
    SPI_CR1_BR_0   |                        // fpclk/16  approx 5Mhz? BR = 0x011
    SPI_CR1_SSM,
    0, // SPI_CR2_SSOE,
};

static const ax5043_profile_t lband_eng[] = {
    /* Modulation and Framing */
    {AX5043_REG_MODULATION, AX5043_MODULATION_MSK, 1},
    {AX5043_REG_ENCODING, AX5043_ENCODING_NRZI_SCRAM, 1},
    {AX5043_REG_FRAMING, _VAL2FLD(AX5043_FRAMING_FRMMODE, AX5043_FRMMODE_HDLC) |
                         _VAL2FLD(AX5043_FRAMING_CRCMODE, AX5043_CRCMODE_CCITT), 1},
    /* Pin Configuration */
    {AX5043_REG_PINFUNCSYSCLK, AX5043_PFSYSCLK_OUT_XTAL_DIV1, 1},
    /* Synthesizer */
    {AX5043_REG_FREQA, 0x1C900001, 4},
    /* PHY Layer Parameters */
    /* Receiver Parameters */
    {AX5043_REG_IFFREQ, 0x170A, 2},
    {AX5043_REG_DECIMATION, 0x01, 1},
    {AX5043_REG_RXDATARATE, 0x0042AB, 3},
    {AX5043_REG_MAXRFOFFSET, 0x0019E8 | AX5043_MAXRFOFFSET_FREQOFFSCORR, 3},
    /* Receiver Parameter Set 0 */
    /* TODO */
    /* Receiver Parameter Set 1 */
    /* TODO */
    /* Receiver Parameter Set 2 */
    /* TODO */
    /* Receiver Parameter Set 3 */
    /* TODO */
    /* MAC Layer Parameters */
    /* Packet Format */
    {AX5043_REG_PKTLENCFG, _VAL2FLD(AX5043_PKTLENCFG_LENBITS, 0xF), 1},
    {AX5043_REG_PKTMAXLEN, 0xFF, 1},
    /* Pattern Match */
    /* Packet Controller */
    {AX5043_REG_PKTCHUNKSIZE, AX5043_PKTCHUNKSIZE_240, 1},
    {AX5043_REG_PKTACCEPTFLAGS, AX5043_PKTACCEPTFLAGS_LRGP, 1},
    /* Performance Tuning Registers */
    {AX5043_REG_0xF00, AX5043_0xF00_DEFVAL, 1},
    {AX5043_REG_0xF0C, AX5043_0xF0C_DEFVAL, 1},
    {AX5043_REG_0xF0D, AX5043_0xF0D_DEFVAL, 1},
    {AX5043_REG_0xF10, AX5043_0xF10_TCXO, 1},
    {AX5043_REG_0xF11, AX5043_0xF11_TCXO, 1},
    {AX5043_REG_0xF1C, AX5043_0xF1C_DEFVAL, 1},
    {AX5043_REG_0xF21, AX5043_0xF21_DEFVAL, 1},
    {AX5043_REG_0xF22, AX5043_0xF22_DEFVAL, 1},
    {AX5043_REG_0xF23, AX5043_0xF23_DEFVAL, 1},
    {AX5043_REG_0xF26, AX5043_0xF26_DEFVAL, 1},
    {AX5043_REG_0xF30, AX5043_0xF30_DEFVAL, 1},
    {AX5043_REG_0xF31, AX5043_0xF31_DEFVAL, 1},
    {AX5043_REG_0xF32, AX5043_0xF32_DEFVAL, 1},
    {AX5043_REG_0xF33, AX5043_0xF33_DEFVAL, 1},
    {AX5043_REG_0xF35, AX5043_0xF35_XTALDIV1, 1},
    {AX5043_REG_0xF44, AX5043_0xF44_DEFVAL, 1},
    {AX5043_REG_0xF72, AX5043_0xF72_NORAWSOFTBITS, 1},
    {0, 0, 0}
};

static const ax5043_profile_t uhf_ax25[] = {
    /* Modulation and Framing */
    {AX5043_REG_MODULATION, AX5043_MODULATION_FSK, 1},
    {AX5043_REG_ENCODING, AX5043_ENCODING_NRZI_SCRAM, 1},
    {AX5043_REG_FRAMING, _VAL2FLD(AX5043_FRAMING_FRMMODE, AX5043_FRMMODE_HDLC) |
                         _VAL2FLD(AX5043_FRAMING_CRCMODE, AX5043_CRCMODE_CCITT), 1},
    /* Synthesizer */
    {AX5043_REG_FREQA, 0x1B480001, 4},
    {AX5043_REG_FREQB, 0x1B4A0001, 4},
    /* PHY Layer Parameters */
    /* Receiver Parameters */
    {AX5043_REG_IFFREQ, 0x126F, 2},
    {AX5043_REG_DECIMATION, 0x01, 1},
    {AX5043_REG_RXDATARATE, 0x005355, 3},
    {AX5043_REG_MAXRFOFFSET, 0x008F1 | AX5043_MAXRFOFFSET_FREQOFFSCORR, 3},
    /* Receiver Parameter Set 0 */
    /* TODO */
    /* Receiver Parameter Set 1 */
    /* TODO */
    /* Receiver Parameter Set 2 */
    /* TODO */
    /* Receiver Parameter Set 3 */
    /* TODO */
    /* Transmitter Parameters */
    {AX5043_REG_FSKDEV, 0x0009D5, 3},
    {AX5043_REG_MODCFGA, AX5043_MODCFGA_TXSE | _VAL2FLD(AX5043_MODCFGA_AMPLSHAPE, AX5043_AMPLSHAPE_RAISEDCOS) |
                         AX5043_MODCFGA_PTTLCKGATE | AX5043_MODCFGA_BROWNGATE, 1},
    {AX5043_REG_TXRATE, 0x002752, 3},
    /* MAC Layer Parameters */
    /* Packet Format */
    {AX5043_REG_PKTLENCFG, _VAL2FLD(AX5043_PKTLENCFG_LENBITS, 0xF), 1},
    {AX5043_REG_PKTMAXLEN, 0xFF, 1},
    /* Pattern Match */
    /* Packet Controller */
    {AX5043_REG_PKTCHUNKSIZE, AX5043_PKTCHUNKSIZE_240, 1},
    {AX5043_REG_PKTACCEPTFLAGS, AX5043_PKTACCEPTFLAGS_LRGP, 1},
    /* Performance Tuning Registers */
    {AX5043_REG_0xF00, AX5043_0xF00_DEFVAL, 1},
    {AX5043_REG_0xF0C, AX5043_0xF0C_DEFVAL, 1},
    {AX5043_REG_0xF0D, AX5043_0xF0D_DEFVAL, 1},
    {AX5043_REG_0xF10, AX5043_0xF10_TCXO, 1},
    {AX5043_REG_0xF11, AX5043_0xF11_TCXO, 1},
    {AX5043_REG_0xF1C, AX5043_0xF1C_DEFVAL, 1},
    {AX5043_REG_0xF21, AX5043_0xF21_DEFVAL, 1},
    {AX5043_REG_0xF22, AX5043_0xF22_DEFVAL, 1},
    {AX5043_REG_0xF23, AX5043_0xF23_DEFVAL, 1},
    {AX5043_REG_0xF26, AX5043_0xF26_DEFVAL, 1},
    {AX5043_REG_0xF30, AX5043_0xF30_DEFVAL, 1},
    {AX5043_REG_0xF31, AX5043_0xF31_DEFVAL, 1},
    {AX5043_REG_0xF32, AX5043_0xF32_DEFVAL, 1},
    {AX5043_REG_0xF33, AX5043_0xF33_DEFVAL, 1},
    {AX5043_REG_0xF35, AX5043_0xF35_XTALDIV1, 1},
    {AX5043_REG_0xF44, AX5043_0xF44_DEFVAL, 1},
    {AX5043_REG_0xF72, AX5043_0xF72_NORAWSOFTBITS, 1},
    {0, 0, 0}
};

static const ax5043_profile_t uhf_eng[] = {
    /* Modulation and Framing */
    {AX5043_REG_MODULATION, AX5043_MODULATION_MSK, 1},
    {AX5043_REG_ENCODING, AX5043_ENCODING_NRZI_SCRAM, 1},
    {AX5043_REG_FRAMING, _VAL2FLD(AX5043_FRAMING_FRMMODE, AX5043_FRMMODE_HDLC) |
                         _VAL2FLD(AX5043_FRAMING_CRCMODE, AX5043_CRCMODE_CCITT), 1},
    /* Synthesizer */
    {AX5043_REG_FREQA, 0x1B480001, 4},
    {AX5043_REG_FREQB, 0x1B4A0001, 4},
    /* PHY Layer Parameters */
    /* Receiver Parameters */
    {AX5043_REG_IFFREQ, 0x126F, 2},
    {AX5043_REG_DECIMATION, 0x01, 1},
    {AX5043_REG_RXDATARATE, 0x005355, 3},
    {AX5043_REG_MAXRFOFFSET, 0x008F1 | AX5043_MAXRFOFFSET_FREQOFFSCORR, 3},
    /* Receiver Parameter Set 0 */
    /* TODO */
    /* Receiver Parameter Set 1 */
    /* TODO */
    /* Receiver Parameter Set 2 */
    /* TODO */
    /* Receiver Parameter Set 3 */
    /* TODO */
    /* Transmitter Parameters */
    {AX5043_REG_MODCFGF, AX5043_FREQSHAPE_GAUSS_BT_0_5, 1},
    {AX5043_REG_FSKDEV, 0x00624E, 3},
    {AX5043_REG_MODCFGA, AX5043_MODCFGA_TXSE | _VAL2FLD(AX5043_MODCFGA_AMPLSHAPE, AX5043_AMPLSHAPE_RAISEDCOS) |
                         AX5043_MODCFGA_PTTLCKGATE | AX5043_MODCFGA_BROWNGATE, 1},
    {AX5043_REG_TXRATE, 0x018937, 3},
    /* MAC Layer Parameters */
    /* Packet Format */
    {AX5043_REG_PKTLENCFG, _VAL2FLD(AX5043_PKTLENCFG_LENBITS, 0xF), 1},
    {AX5043_REG_PKTMAXLEN, 0xFF, 1},
    /* Pattern Match */
    /* Packet Controller */
    {AX5043_REG_PKTCHUNKSIZE, AX5043_PKTCHUNKSIZE_240, 1},
    {AX5043_REG_PKTACCEPTFLAGS, AX5043_PKTACCEPTFLAGS_LRGP, 1},
    /* Performance Tuning Registers */
    {AX5043_REG_0xF00, AX5043_0xF00_DEFVAL, 1},
    {AX5043_REG_0xF0C, AX5043_0xF0C_DEFVAL, 1},
    {AX5043_REG_0xF0D, AX5043_0xF0D_DEFVAL, 1},
    {AX5043_REG_0xF10, AX5043_0xF10_TCXO, 1},
    {AX5043_REG_0xF11, AX5043_0xF11_TCXO, 1},
    {AX5043_REG_0xF1C, AX5043_0xF1C_DEFVAL, 1},
    {AX5043_REG_0xF21, AX5043_0xF21_DEFVAL, 1},
    {AX5043_REG_0xF22, AX5043_0xF22_DEFVAL, 1},
    {AX5043_REG_0xF23, AX5043_0xF23_DEFVAL, 1},
    {AX5043_REG_0xF26, AX5043_0xF26_DEFVAL, 1},
    {AX5043_REG_0xF30, AX5043_0xF30_DEFVAL, 1},
    {AX5043_REG_0xF31, AX5043_0xF31_DEFVAL, 1},
    {AX5043_REG_0xF32, AX5043_0xF32_DEFVAL, 1},
    {AX5043_REG_0xF33, AX5043_0xF33_DEFVAL, 1},
    {AX5043_REG_0xF35, AX5043_0xF35_XTALDIV1, 1},
    {AX5043_REG_0xF44, AX5043_0xF44_DEFVAL, 1},
    {AX5043_REG_0xF72, AX5043_0xF72_NORAWSOFTBITS, 1},
    {0, 0, 0}
};

const AX5043Config lbandcfg = {
    .spip       = &SPID1,
    .spicfg     = &lband_spicfg,
    .miso       = LINE_SPI1_MISO,
    .irq        = LINE_LBAND_IRQ,
    .xtal_freq  = 16000000,
    .profile    = lband_eng,
};

const AX5043Config uhfcfg = {
    .spip       = &SPID1,
    .spicfg     = &uhf_spicfg,
    .miso       = LINE_SPI1_MISO,
    .irq        = LINE_UHF_IRQ,
    .xtal_freq  = 16000000,
    .profile    = uhf_ax25,
};

SI41XXConfig synthcfg = {
    .sen        = LINE_LO_SEN,
    .sclk       = LINE_LO_SCLK,
    .sdata      = LINE_LO_SDATA,
    .ref_freq   = 16000000,
    .if_div     = SI41XX_IFDIV_DIV1,
    .if_n       = 1616,
    .if_r       = 32,
};

AX5043Driver lband;
AX5043Driver uhf;
SI41XXDriver synth;

#ifdef SHELL_ENABLE
radio_dev_t radio_devices[] = {
    {&lband, &lbandcfg, "L-Band"},
    {&uhf, &uhfcfg, "UHF"},
    {NULL, NULL, ""},
};

radio_profile_t radio_profiles[] = {
    {lband_eng, "L-Band Engineering"},
    {uhf_ax25, "UHF AX.25"},
    {uhf_eng, "UHF Engineering"},
    {NULL, ""},
};

synth_dev_t synth_devices[] = {
    {&synth, &synthcfg, "LO"},
    {NULL, NULL, ""},
};
#endif

static worker_t wdt_worker;
#ifdef SHELL_ENABLE
static worker_t cmd_worker;
#endif

static oresat_config_t oresat_conf = {
    &CAND1,
    0x01,
    ORESAT_DEFAULT_BITRATE
};

/**
 * @brief App Initialization
 */
static void app_init(void)
{
    /* Initialize WDT worker thread */
    init_worker(&wdt_worker, "WDT", wdt_wa, sizeof(wdt_wa), NORMALPRIO, wdt, NULL, true);
    reg_worker(&wdt_worker);

    /* Initialize shell worker thread */
#ifdef SHELL_ENABLE
    init_worker(&cmd_worker, "Shell", cmd_wa, sizeof(cmd_wa), NORMALPRIO, cmd, NULL, true);
    reg_worker(&cmd_worker);
#endif

    /* Initialize OPD */
    opd_init();
    opd_start();

    /* Initialize SDO client */
    sdo_init();

    /* Initialize and start radio systems */
    ax5043ObjectInit(&lband);
    ax5043ObjectInit(&uhf);
    si41xxObjectInit(&synth);

    ax5043Start(&lband, &lbandcfg);
    ax5043Start(&uhf, &uhfcfg);
    si41xxStart(&synth, &synthcfg);

    /* Initialize shell and start serial interface */
#ifdef SHELL_ENABLE
    shellInit();
#endif
    sdStart(&SD3, NULL);

    /* Configure SCET time object */
    CO_OD_configure(CO->SDO[0], OD_2010_SCET, OD_SCET_Func, NULL, 0, 0);
}

/**
 * @brief Main Application
 */
int main(void)
{
    // Initialize and start
    oresat_init();
    app_init();
    oresat_start(&oresat_conf);
    return 0;
}
