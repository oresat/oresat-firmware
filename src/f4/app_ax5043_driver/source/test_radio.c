#include <stdlib.h>
#include <string.h>
#include "ch.h"
#include "hal.h"
#include "test_radio.h"
#include "ax5043.h"
#include "chprintf.h"

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

static const ax5043_regval_t lband_regs[] = {
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
    {AX5043_REG_0xF34, AX5043_0xF34_RFDIV},
    {AX5043_REG_0xF35, AX5043_0xF35_XTALDIV1},
    {AX5043_REG_0xF44, AX5043_0xF44_DEFVAL},
    {0, 0}
};
static const ax5043_regval_t uhf_regs[] = {
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
    {AX5043_REG_0xF34, AX5043_0xF34_RFDIV},
    {AX5043_REG_0xF35, AX5043_0xF35_XTALDIV1},
    {AX5043_REG_0xF44, AX5043_0xF44_DEFVAL},
    {0, 0}
};

static const AX5043Config lbandcfg = {
    .spip       = &SPID1,
    .spicfg     = &lband_spicfg,
    .miso       = LINE_SPI1_MISO,
    .irq        = LINE_LBAND_IRQ,
    .xtal_freq  = 16000000,
    .reg_values = lband_regs,
};

static const AX5043Config uhfcfg = {
    .spip       = &SPID1,
    .spicfg     = &uhf_spicfg,
    .miso       = LINE_SPI1_MISO,
    .irq        = LINE_LBAND_IRQ,
    .xtal_freq  = 16000000,
    .reg_values = uhf_regs,
};

AX5043Driver lband;
AX5043Driver uhf;

/*===========================================================================*/
/* OreSat Radio Control                                                      */
/*===========================================================================*/
void cmd_radio(BaseSequentialStream *chp, int argc, char *argv[])
{
    if (argc < 1) {
        goto radio_usage;
    }

    if (!strcmp(argv[0], "start")) {
        chprintf(chp, "Starting AX5043 driver...");
        ax5043Start(&lband, &lbandcfg);
        chprintf(chp, "OK\r\n");
    } else if (!strcmp(argv[0], "stop")) {
        chprintf(chp, "Stopping AX5043 driver...");
        ax5043Stop(&lband);
        chprintf(chp, "OK\r\n");
    } else if (!strcmp(argv[0], "setfreq")) {
        uint32_t freq;
        uint8_t vcor = 0;
        bool chan_b = false;
        if (lband.state != AX5043_READY) {
            chprintf(chp, "Please start the AX5043 driver first\r\n");
            goto radio_usage;
        }
        if (argc < 2) {
            goto radio_usage;
        }
        freq = strtoul(argv[1], NULL, 0);
        if (argc > 2) {
            vcor = strtoul(argv[2], NULL, 0);
            if (argc == 4) {
                chan_b = !strcmp(argv[3], "true");
            }
        }
        ax5043SetFreq(&lband, freq, vcor, chan_b);
    } else {
        goto radio_usage;
    }

    return;

radio_usage:
    chprintf(chp, "Usage: radio <cmd>\r\n"
                  "    start:   Start AX5043 device\r\n"
                  "    stop:    Stop AX5043 device\r\n"
                  "    setfreq <freq> [vcor] [chan_b]:\r\n"
                  "             Sets frequency of channel A/B to <freq>\r\n"
                  "             Optionally provide VCOR. [chan_b] specifies channel B\r\n"
                  "\r\n");
    return;
}

