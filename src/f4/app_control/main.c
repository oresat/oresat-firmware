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
    {AX5043_REG_MODULATION, AX5043_MODULATION_MSK},
    {AX5043_REG_ENCODING, AX5043_ENCODING_NRZI_SCRAM},
    {AX5043_REG_FRAMING, _VAL2FLD(AX5043_FRAMING_FRMMODE, AX5043_FRAMING_FRMMODE_HDLC) |
                         _VAL2FLD(AX5043_FRAMING_CRCMODE, AX5043_FRAMING_CRCMODE_CRC32)},
    {AX5043_REG_PINFUNCSYSCLK, AX5043_PFSYSCLK_OUT_XTAL_DIV1},
    {AX5043_REG_0xF00, AX5043_0xF00_DEFVAL},
    {AX5043_REG_0xF0C, AX5043_0xF0C_DEFVAL},
    {AX5043_REG_0xF0D, AX5043_0xF0D_DEFVAL},
    {AX5043_REG_0xF10, AX5043_0xF10_TCXO},
    {AX5043_REG_0xF11, AX5043_0xF11_TCXO},
    {AX5043_REG_0xF1C, AX5043_0xF1C_DEFVAL},
    {AX5043_REG_0xF21, AX5043_0xF21_DEFVAL},
    {AX5043_REG_0xF22, AX5043_0xF22_DEFVAL},
    {AX5043_REG_0xF23, AX5043_0xF23_DEFVAL},
    {AX5043_REG_0xF26, AX5043_0xF26_DEFVAL},
    {AX5043_REG_0xF30, AX5043_0xF30_DEFVAL},
    {AX5043_REG_0xF31, AX5043_0xF31_DEFVAL},
    {AX5043_REG_0xF32, AX5043_0xF32_DEFVAL},
    {AX5043_REG_0xF33, AX5043_0xF33_DEFVAL},
    {AX5043_REG_0xF35, AX5043_0xF35_XTALDIV1},
    {AX5043_REG_0xF44, AX5043_0xF44_DEFVAL},
    {0, 0}
};

static const ax5043_profile_t uhf_eng[] = {
    {AX5043_REG_MODULATION, AX5043_MODULATION_MSK},
    {AX5043_REG_ENCODING, AX5043_ENCODING_NRZI_SCRAM},
    {AX5043_REG_FRAMING, _VAL2FLD(AX5043_FRAMING_FRMMODE, AX5043_FRAMING_FRMMODE_HDLC) |
                         _VAL2FLD(AX5043_FRAMING_CRCMODE, AX5043_FRAMING_CRCMODE_CRC32)},
    {AX5043_REG_MODCFGF, AX5043_FREQSHAPE_GAUSS_BT_0_3},
    {AX5043_REG_0xF00, AX5043_0xF00_DEFVAL},
    {AX5043_REG_0xF0C, AX5043_0xF0C_DEFVAL},
    {AX5043_REG_0xF0D, AX5043_0xF0D_DEFVAL},
    {AX5043_REG_0xF10, AX5043_0xF10_TCXO},
    {AX5043_REG_0xF11, AX5043_0xF11_TCXO},
    {AX5043_REG_0xF1C, AX5043_0xF1C_DEFVAL},
    {AX5043_REG_0xF21, AX5043_0xF21_DEFVAL},
    {AX5043_REG_0xF22, AX5043_0xF22_DEFVAL},
    {AX5043_REG_0xF23, AX5043_0xF23_DEFVAL},
    {AX5043_REG_0xF26, AX5043_0xF26_DEFVAL},
    {AX5043_REG_0xF30, AX5043_0xF30_DEFVAL},
    {AX5043_REG_0xF31, AX5043_0xF31_DEFVAL},
    {AX5043_REG_0xF32, AX5043_0xF32_DEFVAL},
    {AX5043_REG_0xF33, AX5043_0xF33_DEFVAL},
    {AX5043_REG_0xF35, AX5043_0xF35_XTALDIV1},
    {AX5043_REG_0xF44, AX5043_0xF44_DEFVAL},
    {0, 0}
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
    .profile    = uhf_eng,
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
