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

static const AX5043Config lbandcfg = {
    .spip       = &SPID1,
    .spicfg     = &lband_spicfg,
    .miso       = LINE_SPI1_MISO,
    .irq        = LINE_LBAND_IRQ,
    .xtal_freq  = 16000000,
};

static const AX5043Config uhfcfg = {
    .spip       = &SPID1,
    .spicfg     = &uhf_spicfg,
    .miso       = LINE_SPI1_MISO,
    .irq        = LINE_LBAND_IRQ,
    .xtal_freq  = 16000000,
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

