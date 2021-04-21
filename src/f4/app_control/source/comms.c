#include "ch.h"
#include "hal.h"
#include "comms.h"
#include "beacon.h"
#include "c3.h"
#include "rtc.h"
#include "uslp.h"
#include "CANopen.h"

#define EDL_WORKERS                         2

#define XTAL_CLK                            16000000U

#define SCID                                0x4F53U
#define MCID                                ((USLP_TFVN << 16) | SCID)
/* 16-bit FECF provided by AX5043 driver */
#define FECF_LEN                            2
#define USLP_MAX_LEN                        (FB_MAX_LEN + FECF_LEN)

static const SPIConfig lband_spicfg = {
    false,
    NULL,                                   /* Operation complete callback */
    LINE_LBAND_CS,
    // SPI_CR1
    SPI_CR1_SPE     |                       /* SPI enable */
    SPI_CR1_MSTR    |                       /* Master */
    SPI_CR1_BR_1    |                       /* f_pclk/8 (f_pclk = 84MHz, so 10.5MHz) */
    SPI_CR1_SSM,
    0,
};

static const SPIConfig uhf_spicfg = {
    false,
    NULL,                                   /* Operation complete callback */
    LINE_UHF_CS,
    // SPI_CR1
    SPI_CR1_SPE     |                       /* SPI enable */
    SPI_CR1_MSTR    |                       /* Master */
    SPI_CR1_BR_1    |                       /* f_pclk/8 (f_pclk = 84MHz, so 10.5MHz) */
    SPI_CR1_SSM,
    0,
};

static const ax5043_profile_t lband_high[] = {
    /* Modulation and Framing */
    {AX5043_REG_MODULATION, AX5043_MODULATION_MSK, 1},
    {AX5043_REG_ENCODING, AX5043_ENCODING_NRZI_SCRAM, 1},
    {AX5043_REG_FRAMING, _VAL2FLD(AX5043_FRAMING_FRMMODE, AX5043_FRMMODE_HDLC) |
                         _VAL2FLD(AX5043_FRAMING_CRCMODE, AX5043_CRCMODE_CCITT), 1},

    /* Pin Configuration */
    {AX5043_REG_PINFUNCSYSCLK, AX5043_PFSYSCLK_OUT_XTAL_DIV1, 1},

    /* Synthesizer */
    {AX5043_REG_PLLCPI, 0x01, 1},
    {AX5043_REG_FREQA, 0x1C900001, 4},

    /* PHY Layer Parameters */
    /* Receiver Parameters */
    {AX5043_REG_IFFREQ, 0x170A, 2},
    {AX5043_REG_DECIMATION, 0x01, 1},
    {AX5043_REG_RXDATARATE, 0x0042AB, 3},
    {AX5043_REG_MAXDROFFSET, 0x000000, 3},
    {AX5043_REG_MAXRFOFFSET, 0x0003BE | AX5043_MAXRFOFFSET_FREQOFFSCORR, 3},

    /* Receiver Parameter Set 0 */
    {AX5043_REG_AGCGAIN0, _VAL2FLD(AX5043_AGCGAIN_AGCDECAY, 0x04) |
                          _VAL2FLD(AX5043_AGCGAIN_AGCATTACK, 0x00), 1},
    {AX5043_REG_AGCTARGET0, 0x89, 1},
    {AX5043_REG_TIMEGAIN0, _VAL2FLD(AX5043_TIMEGAIN_E, 0x09) |
                           _VAL2FLD(AX5043_TIMEGAIN_M, 0x08), 1},
    {AX5043_REG_DRGAIN0, _VAL2FLD(AX5043_DRGAIN_E, 0x03) |
                         _VAL2FLD(AX5043_DRGAIN_M, 0x08), 1},
    {AX5043_REG_FREQDEV0, 0x0000, 2},

    /* Receiver Parameter Set 1 */
    /* TODO */

    /* Receiver Parameter Set 2 */
    /* TODO */

    /* Receiver Parameter Set 3 */
    /* TODO */

    /* Transmitter Parameters */
    {AX5043_REG_TXPWRCOEFFB, 0x0000, 2},

    /* PLL Parameters */
    {AX5043_REG_PLLVCOI, _VAL2FLD(AX5043_PLLVCOI_VCOI, 0x16) |
                         AX5043_PLLVCOI_VCOIE, 1},

    /* MAC Layer Parameters */
    /* Packet Format */
    {AX5043_REG_PKTADDRCFG, AX5043_PKTADDRCFG_MSBFIRST | AX5043_PKTADDRCFG_FECSYNCDIS, 1},
    {AX5043_REG_PKTLENCFG, _VAL2FLD(AX5043_PKTLENCFG_LENBITS, 0xF), 1},
    {AX5043_REG_PKTMAXLEN, 0xFF, 1},
    {AX5043_REG_PKTADDR, _VAL2FLD(USLP_TFPH_ID_MCID, MCID) | USLP_TFPH_ID_SRC_DST, 4},
    {AX5043_REG_PKTADDRMASK, USLP_TFPH_ID_MCID | USLP_TFPH_ID_SRC_DST, 4},

    /* Pattern Match */

    /* Packet Controller */
    {AX5043_REG_PKTCHUNKSIZE, AX5043_PKTCHUNKSIZE_240, 1},
    {AX5043_REG_PKTACCEPTFLAGS, AX5043_PKTACCEPTFLAGS_LRGP, 1},

    /* Performance Tuning Registers */
    {AX5043_REG_0xF00, AX5043_0xF00_DEFVAL, 1},
    {AX5043_REG_0xF08, AX5043_0xF08_DEFVAL, 1},
    {AX5043_REG_0xF0D, AX5043_0xF0D_DEFVAL, 1},
    {AX5043_REG_0xF10, AX5043_0xF10_TCXO, 1},
    {AX5043_REG_0xF11, AX5043_0xF11_TCXO, 1},
    {AX5043_REG_0xF18, 0x02, 1},
    {AX5043_REG_0xF1C, AX5043_0xF1C_DEFVAL, 1},
    {AX5043_REG_0xF21, 0x68, 1},
    {AX5043_REG_0xF22, 0xFF, 1},
    {AX5043_REG_0xF23, 0x84, 1},
    {AX5043_REG_0xF26, 0x98, 1},
    {AX5043_REG_0xF35, AX5043_0xF35_XTALDIV1, 1},
    {AX5043_REG_0xF44, 0x25, 1},
    {AX5043_REG_0xF72, AX5043_0xF72_NORAWSOFTBITS, 1},
    {0, 0, 0}
};

static const ax5043_profile_t lband_low[] = {
    /* Modulation and Framing */
    {AX5043_REG_MODULATION, AX5043_MODULATION_FSK, 1},
    {AX5043_REG_ENCODING, AX5043_ENCODING_NRZI_SCRAM, 1},
    {AX5043_REG_FRAMING, _VAL2FLD(AX5043_FRAMING_FRMMODE, AX5043_FRMMODE_HDLC) |
                         _VAL2FLD(AX5043_FRAMING_CRCMODE, AX5043_CRCMODE_CCITT), 1},

    /* Pin Configuration */
    {AX5043_REG_PINFUNCSYSCLK, AX5043_PFSYSCLK_OUT_XTAL_DIV1, 1},

    /* Synthesizer */
    {AX5043_REG_PLLCPI, 0x01, 1},
    {AX5043_REG_FREQA, 0x1C900001, 4},

    /* PHY Layer Parameters */
    /* Receiver Parameters */
    {AX5043_REG_IFFREQ, 0x0E78, 2},
    {AX5043_REG_DECIMATION, 0x02, 1},
    {AX5043_REG_RXDATARATE, 0x0042AB, 3},
    {AX5043_REG_MAXDROFFSET, 0x000000, 3},
    {AX5043_REG_MAXRFOFFSET, 0x0003BE | AX5043_MAXRFOFFSET_FREQOFFSCORR, 3},

    /* Receiver Parameter Set 0 */
    {AX5043_REG_AGCGAIN0, _VAL2FLD(AX5043_AGCGAIN_AGCDECAY, 0x05) |
                          _VAL2FLD(AX5043_AGCGAIN_AGCATTACK, 0x01), 1},
    {AX5043_REG_AGCTARGET0, 0x89, 1},
    {AX5043_REG_TIMEGAIN0, _VAL2FLD(AX5043_TIMEGAIN_E, 0x09) |
                           _VAL2FLD(AX5043_TIMEGAIN_M, 0x08), 1},
    {AX5043_REG_DRGAIN0, _VAL2FLD(AX5043_DRGAIN_E, 0x03) |
                         _VAL2FLD(AX5043_DRGAIN_M, 0x08), 1},
    {AX5043_REG_FREQDEV0, 0x0000, 2},

    /* Receiver Parameter Set 1 */
    /* TODO */

    /* Receiver Parameter Set 2 */
    /* TODO */

    /* Receiver Parameter Set 3 */
    /* TODO */

    /* Transmitter Parameters */
    {AX5043_REG_TXPWRCOEFFB, 0x0000, 2},

    /* PLL Parameters */
    {AX5043_REG_PLLVCOI, _VAL2FLD(AX5043_PLLVCOI_VCOI, 0x16) |
                         AX5043_PLLVCOI_VCOIE, 1},

    /* MAC Layer Parameters */
    /* Packet Format */
    {AX5043_REG_PKTADDRCFG, AX5043_PKTADDRCFG_MSBFIRST | AX5043_PKTADDRCFG_FECSYNCDIS, 1},
    {AX5043_REG_PKTLENCFG, _VAL2FLD(AX5043_PKTLENCFG_LENBITS, 0xF), 1},
    {AX5043_REG_PKTMAXLEN, 0xFF, 1},
    {AX5043_REG_PKTADDR, _VAL2FLD(USLP_TFPH_ID_MCID, MCID) | USLP_TFPH_ID_SRC_DST, 4},
    {AX5043_REG_PKTADDRMASK, USLP_TFPH_ID_MCID | USLP_TFPH_ID_SRC_DST, 4},

    /* Pattern Match */

    /* Packet Controller */
    {AX5043_REG_PKTCHUNKSIZE, AX5043_PKTCHUNKSIZE_240, 1},
    {AX5043_REG_PKTACCEPTFLAGS, AX5043_PKTACCEPTFLAGS_LRGP, 1},

    /* Performance Tuning Registers */
    {AX5043_REG_0xF00, AX5043_0xF00_DEFVAL, 1},
    {AX5043_REG_0xF08, AX5043_0xF08_DEFVAL, 1},
    {AX5043_REG_0xF0D, AX5043_0xF0D_DEFVAL, 1},
    {AX5043_REG_0xF10, AX5043_0xF10_TCXO, 1},
    {AX5043_REG_0xF11, AX5043_0xF11_TCXO, 1},
    {AX5043_REG_0xF18, 0x02, 1},
    {AX5043_REG_0xF1C, AX5043_0xF1C_DEFVAL, 1},
    {AX5043_REG_0xF21, 0x68, 1},
    {AX5043_REG_0xF22, 0xFF, 1},
    {AX5043_REG_0xF23, 0x84, 1},
    {AX5043_REG_0xF26, 0x98, 1},
    {AX5043_REG_0xF35, AX5043_0xF35_XTALDIV1, 1},
    {AX5043_REG_0xF44, 0x25, 1},
    {AX5043_REG_0xF72, AX5043_0xF72_NORAWSOFTBITS, 1},
    {0, 0, 0}
};

static const ax5043_profile_t uhf_eng[] = {
    /* Modulation and Framing */
    {AX5043_REG_MODULATION, AX5043_MODULATION_MSK, 1},
    {AX5043_REG_ENCODING, AX5043_ENCODING_NRZI_SCRAM, 1},
    {AX5043_REG_FRAMING, _VAL2FLD(AX5043_FRAMING_FRMMODE, AX5043_FRMMODE_HDLC) |
                         _VAL2FLD(AX5043_FRAMING_CRCMODE, AX5043_CRCMODE_CCITT), 1},

    /* Pin Configuration */
    {AX5043_REG_PINFUNCSYSCLK, AX5043_PFSYSCLK_OUT_0, 1},

    /* Synthesizer */
    {AX5043_REG_PLLCPI, 0x02, 1},
    {AX5043_REG_FREQA, 0x1B480001, 4},

    /* PHY Layer Parameters */
    /* Receiver Parameters */
    {AX5043_REG_IFFREQ, 0x1058, 2},
    {AX5043_REG_DECIMATION, 0x01, 1},
    {AX5043_REG_RXDATARATE, 0x005355, 3},
    {AX5043_REG_MAXDROFFSET, 0x000000, 3},
    {AX5043_REG_MAXRFOFFSET, 0x000393 | AX5043_MAXRFOFFSET_FREQOFFSCORR, 3},

    /* Receiver Parameter Set 0 */
    {AX5043_REG_AGCGAIN0, _VAL2FLD(AX5043_AGCGAIN_AGCDECAY, 0x04) |
                          _VAL2FLD(AX5043_AGCGAIN_AGCATTACK, 0x00), 1},
    {AX5043_REG_AGCTARGET0, 0x89, 1},
    {AX5043_REG_TIMEGAIN0, _VAL2FLD(AX5043_TIMEGAIN_E, 0x09) |
                           _VAL2FLD(AX5043_TIMEGAIN_M, 0x0A), 1},
    {AX5043_REG_DRGAIN0, _VAL2FLD(AX5043_DRGAIN_E, 0x03) |
                         _VAL2FLD(AX5043_DRGAIN_M, 0x0A), 1},
    {AX5043_REG_FREQDEV0, 0x0000, 2},

    /* Receiver Parameter Set 1 */
    /* TODO */

    /* Receiver Parameter Set 2 */
    /* TODO */

    /* Receiver Parameter Set 3 */
    /* TODO */

    /* Transmitter Parameters */
    {AX5043_REG_MODCFGF, AX5043_FREQSHAPE_GAUSS_BT_0_5, 1},
    {AX5043_REG_FSKDEV, 0x00624E, 3},
    {AX5043_REG_MODCFGA, AX5043_MODCFGA_TXSE | _VAL2FLD(AX5043_MODCFGA_AMPLSHAPE, AX5043_AMPLSHAPE_RAISEDCOS), 1},
    {AX5043_REG_TXRATE, 0x018937, 3},
    {AX5043_REG_TXPWRCOEFFB, 0x0700, 2},

    /* PLL Parameters */
    {AX5043_REG_PLLVCOI, _VAL2FLD(AX5043_PLLVCOI_VCOI, 0x16) |
                         AX5043_PLLVCOI_VCOIE, 1},

    /* MAC Layer Parameters */
    /* Packet Format */
    {AX5043_REG_PKTADDRCFG, AX5043_PKTADDRCFG_MSBFIRST | AX5043_PKTADDRCFG_FECSYNCDIS, 1},
    {AX5043_REG_PKTLENCFG, _VAL2FLD(AX5043_PKTLENCFG_LENBITS, 0xF), 1},
    {AX5043_REG_PKTMAXLEN, 0xFF, 1},
    {AX5043_REG_PKTADDR, _VAL2FLD(USLP_TFPH_ID_MCID, MCID) | USLP_TFPH_ID_SRC_DST, 4},
    {AX5043_REG_PKTADDRMASK, USLP_TFPH_ID_MCID | USLP_TFPH_ID_SRC_DST, 4},

    /* Pattern Match */

    /* Packet Controller */
    {AX5043_REG_PKTCHUNKSIZE, AX5043_PKTCHUNKSIZE_240, 1},
    {AX5043_REG_PKTACCEPTFLAGS, AX5043_PKTACCEPTFLAGS_LRGP, 1},

    /* Performance Tuning Registers */
    {AX5043_REG_0xF00, AX5043_0xF00_DEFVAL, 1},
    {AX5043_REG_0xF08, AX5043_0xF08_DEFVAL, 1},
    {AX5043_REG_0xF0D, AX5043_0xF0D_DEFVAL, 1},
    {AX5043_REG_0xF10, AX5043_0xF10_TCXO, 1},
    {AX5043_REG_0xF11, AX5043_0xF11_TCXO, 1},
    {AX5043_REG_0xF18, 0x06, 1},
    {AX5043_REG_0xF1C, AX5043_0xF1C_DEFVAL, 1},
    {AX5043_REG_0xF21, 0x68, 1},
    {AX5043_REG_0xF22, 0xFF, 1},
    {AX5043_REG_0xF23, 0x84, 1},
    {AX5043_REG_0xF26, 0x98, 1},
    {AX5043_REG_0xF35, AX5043_0xF35_XTALDIV1, 1},
    {AX5043_REG_0xF44, 0x25, 1},
    {AX5043_REG_0xF72, AX5043_0xF72_NORAWSOFTBITS, 1},
    {0, 0, 0}
};

static const ax5043_profile_t uhf_ax25[] = {
    /* Modulation and Framing */
    {AX5043_REG_MODULATION, AX5043_MODULATION_MSK, 1},
    {AX5043_REG_ENCODING, AX5043_ENCODING_NRZI_SCRAM, 1},
    {AX5043_REG_FRAMING, _VAL2FLD(AX5043_FRAMING_FRMMODE, AX5043_FRMMODE_HDLC) |
                         _VAL2FLD(AX5043_FRAMING_CRCMODE, AX5043_CRCMODE_CCITT), 1},

    /* Pin Configuration */
    {AX5043_REG_PINFUNCSYSCLK, AX5043_PFSYSCLK_OUT_0, 1},

    /* Synthesizer */
    {AX5043_REG_PLLCPI, 0x02, 1},
    {AX5043_REG_FREQA, 0x1B480001, 4},

    /* PHY Layer Parameters */
    /* Receiver Parameters */
    {AX5043_REG_IFFREQ, 0x01D8, 2},
    {AX5043_REG_DECIMATION, 0x11, 1},
    {AX5043_REG_RXDATARATE, 0x003106, 3},
    {AX5043_REG_MAXDROFFSET, 0x000000, 3},
    {AX5043_REG_MAXRFOFFSET, 0x000EBF | AX5043_MAXRFOFFSET_FREQOFFSCORR, 3},

    /* Receiver Parameter Set 0 */
    {AX5043_REG_AGCGAIN0, _VAL2FLD(AX5043_AGCGAIN_AGCDECAY, 0x07) |
                          _VAL2FLD(AX5043_AGCGAIN_AGCATTACK, 0x04), 1},
    {AX5043_REG_AGCTARGET0, 0x89, 1},
    {AX5043_REG_TIMEGAIN0, _VAL2FLD(AX5043_TIMEGAIN_E, 0x08) |
                           _VAL2FLD(AX5043_TIMEGAIN_M, 0x09), 1},
    {AX5043_REG_DRGAIN0, _VAL2FLD(AX5043_DRGAIN_E, 0x04) |
                         _VAL2FLD(AX5043_DRGAIN_M, 0x09), 1},
    {AX5043_REG_FREQDEV0, 0x0000, 2},

    /* Receiver Parameter Set 1 */
    /* TODO */

    /* Receiver Parameter Set 2 */
    /* TODO */

    /* Receiver Parameter Set 3 */
    /* TODO */

    /* Transmitter Parameters */
    {AX5043_REG_MODCFGF, AX5043_FREQSHAPE_GAUSS_BT_0_5, 1},
    {AX5043_REG_FSKDEV, 0x0009D5, 3},
    {AX5043_REG_MODCFGA, AX5043_MODCFGA_TXSE | _VAL2FLD(AX5043_MODCFGA_AMPLSHAPE, AX5043_AMPLSHAPE_RAISEDCOS), 1},
    {AX5043_REG_TXRATE, 0x002753, 3},
    {AX5043_REG_TXPWRCOEFFB, 0x0700, 2},

    /* PLL Parameters */
    {AX5043_REG_PLLVCOI, _VAL2FLD(AX5043_PLLVCOI_VCOI, 0x16) |
                         AX5043_PLLVCOI_VCOIE, 1},

    /* MAC Layer Parameters */
    /* Packet Format */
    {AX5043_REG_PKTADDRCFG, AX5043_PKTADDRCFG_FECSYNCDIS, 1},
    {AX5043_REG_PKTLENCFG, _VAL2FLD(AX5043_PKTLENCFG_LENBITS, 0xF), 1},
    {AX5043_REG_PKTMAXLEN, 0xFF, 1},
    {AX5043_REG_PKTADDR, _VAL2FLD(USLP_TFPH_ID_MCID, MCID) | USLP_TFPH_ID_SRC_DST, 4},
    {AX5043_REG_PKTADDRMASK, USLP_TFPH_ID_MCID | USLP_TFPH_ID_SRC_DST, 4},

    /* Pattern Match */

    /* Packet Controller */
    {AX5043_REG_PKTCHUNKSIZE, AX5043_PKTCHUNKSIZE_240, 1},
    {AX5043_REG_PKTACCEPTFLAGS, AX5043_PKTACCEPTFLAGS_LRGP, 1},

    /* Performance Tuning Registers */
    {AX5043_REG_0xF00, AX5043_0xF00_DEFVAL, 1},
    {AX5043_REG_0xF08, AX5043_0xF08_DEFVAL, 1},
    {AX5043_REG_0xF0D, AX5043_0xF0D_DEFVAL, 1},
    {AX5043_REG_0xF10, AX5043_0xF10_TCXO, 1},
    {AX5043_REG_0xF11, AX5043_0xF11_TCXO, 1},
    {AX5043_REG_0xF18, 0x06, 1},
    {AX5043_REG_0xF1C, AX5043_0xF1C_DEFVAL, 1},
    {AX5043_REG_0xF21, 0x68, 1},
    {AX5043_REG_0xF22, 0xFF, 1},
    {AX5043_REG_0xF23, 0x84, 1},
    {AX5043_REG_0xF26, 0x98, 1},
    {AX5043_REG_0xF35, AX5043_0xF35_XTALDIV1, 1},
    {AX5043_REG_0xF44, 0x25, 1},
    {AX5043_REG_0xF72, AX5043_0xF72_NORAWSOFTBITS, 1},
    {0, 0, 0}
};

static const uint8_t preamble[] = {
    AX5043_CHUNKCMD_TXCTRL | _VAL2FLD(AX5043_FIFOCHUNK_SIZE, 1),
    AX5043_CHUNK_TXCTRL_SETPA | AX5043_CHUNK_TXCTRL_PASTATE,
    AX5043_CHUNKCMD_REPEATDATA | _VAL2FLD(AX5043_FIFOCHUNK_SIZE, 3),
    AX5043_CHUNK_REPEATDATA_RAW | AX5043_CHUNK_REPEATDATA_NOCRC,
    50,
    0x7E
};

static const uint8_t postamble[] = {
    AX5043_CHUNKCMD_REPEATDATA | _VAL2FLD(AX5043_FIFOCHUNK_SIZE, 3),
    AX5043_CHUNK_REPEATDATA_RAW | AX5043_CHUNK_REPEATDATA_NOCRC,
    5,
    0x7E,
    AX5043_CHUNKCMD_TXCTRL | _VAL2FLD(AX5043_FIFOCHUNK_SIZE, 1),
    AX5043_CHUNK_TXCTRL_SETPA
};

static const AX5043Config lbandcfg = {
    .spip           = &SPID1,
    .spicfg         = &lband_spicfg,
    .miso           = LINE_SPI1_MISO,
    .irq            = LINE_LBAND_IRQ,
    .xtal_freq      = XTAL_CLK,
    .profile        = lband_high,
};

static const AX5043Config uhfcfg = {
    .spip           = &SPID1,
    .spicfg         = &uhf_spicfg,
    .miso           = LINE_SPI1_MISO,
    .irq            = LINE_UHF_IRQ,
    .xtal_freq      = XTAL_CLK,
    .profile        = uhf_eng,
    .preamble       = preamble,
    .preamble_len   = sizeof(preamble),
    .postamble      = postamble,
    .postamble_len  = sizeof(postamble),
};

static SI41XXConfig synthcfg = {
    .sen            = LINE_LO_SEN,
    .sclk           = LINE_LO_SCLK,
    .sdata          = LINE_LO_SDATA,
    .ref_freq       = XTAL_CLK,
    .if_div         = SI41XX_IFDIV_DIV1,
    .if_n           = 1616,
    .if_r           = 32,
};

static AX5043Driver lband;
static AX5043Driver uhf;
static SI41XXDriver synth;

static const uslp_map_t map0 = {
    .sdu            = SDU_MAP_PKT,
    .upid           = UPID_SPP_ENCAPS,
    .max_pkt_len    = 1024,
    .incomplete     = false,
    .pvn_cnt        = 1,
    .pvn            = {PVN_SPACE},
};

static const uslp_vc_t vc0 = {
    .seq_ctrl_len   = VC0_SEQ_CTRL_LEN,
    .expedited_len  = VC0_EXPEDITED_LEN,
    .seq_ctrl_cnt   = NULL,
    .expedited_cnt  = NULL,
    .cop            = COP_NONE,
    .mapid[0]       = &map0,
    .trunc_tf_len   = USLP_MAX_LEN,
    .ocf            = false,
#if (USLP_USE_SDLS == TRUE)
    .sdls_hdr_len   = 0,
    .sdls_tlr_len   = 0,
#endif
};

static const uslp_mc_t mc = {
    .scid           = SCID,
    .vcid[0]        = &vc0,
};

static const uslp_pc_t uhf_pc = {
    .name           = "UHF",
    .tf_len         = USLP_MAX_LEN,
    .fecf           = true,
    .fecf_len       = FECF_LEN,
};

static const uslp_pc_t lband_pc = {
    .name           = "L-Band",
    .tf_len         = USLP_MAX_LEN,
    .fecf           = true,
    .fecf_len       = FECF_LEN,
};

static const uslp_link_t edl_uhf_link = {
    .mc = &mc,
    .pc_rx = &uhf_pc,
    .pc_tx = &uhf_pc,
};

static const uslp_link_t edl_lband_link = {
    .mc = &mc,
    .pc_rx = &lband_pc,
    .pc_tx = &uhf_pc,
};

static const radio_cfg_t lband_high_cfg = {
    .devp = &lband,
    .profile = lband_high,
    .name = "L-Band High Data Rate Engineering",
};

static const radio_cfg_t lband_low_cfg = {
    .devp = &lband,
    .profile = lband_low,
    .name = "L-Band Low Data Rate Engineering",
};

static const radio_cfg_t uhf_eng_cfg = {
    .devp = &uhf,
    .profile = uhf_eng,
    .name = "UHF Engineering",
};

static const radio_cfg_t uhf_ax25_cfg = {
    .devp = &uhf,
    .profile = uhf_ax25,
    .name = "UHF AX.25",
};

synth_dev_t synth_devices[] = {
    {&synth, &synthcfg, "LO"},
    {NULL, NULL, ""},
};

radio_dev_t radio_devices[] = {
    {&lband, &lbandcfg, "L-Band"},
    {&uhf, &uhfcfg, "UHF"},
    {NULL, NULL, ""},
};

radio_cfg_t radio_cfgs[] = {
    lband_high_cfg,
    lband_low_cfg,
    uhf_eng_cfg,
    uhf_ax25_cfg,
    {NULL, NULL, ""},
};

const radio_cfg_t *tx_eng = &uhf_eng_cfg;
const radio_cfg_t *tx_ax25 = &uhf_ax25_cfg;

static thread_t *edl_tp[EDL_WORKERS] = {NULL};
static thread_t *tx_tp = NULL;
static thread_t *beacon_tp = NULL;

static mailbox_t tx_mb;
static msg_t tx_mb_msgs[RADIO_FB_COUNT];

THD_FUNCTION(edl_thd, arg)
{
    (void)arg;
    fb_t *rx_fb;

    while (!chThdShouldTerminateX()) {
        rx_fb = fb_get();
        if (rx_fb == NULL) {
            continue;
        }

        /* TODO: Process received frame */
        edl_enable(true);

        fb_free(rx_fb);
    }

    chThdExit(MSG_OK);
}

THD_FUNCTION(tx_worker, arg)
{
    const radio_cfg_t *cfg = arg;
    fb_t *fb;

    while (!chThdShouldTerminateX()) {
        if (chMBFetchTimeout(&tx_mb, (msg_t*)(&fb), TIME_MS2I(1000)) != MSG_OK)
            continue;
        ax5043TX(cfg->devp, cfg->profile, fb->data, fb->len, fb->len, NULL, NULL, false);
        fb_free(fb);
    }

    /* Free remaining frame buffers */
    while (chMBFetchTimeout(&tx_mb, (msg_t*)(&fb), TIME_IMMEDIATE) == MSG_OK) {
        fb_free(fb);
    }

    chThdExit(MSG_OK);
}

void comms_init(void)
{
    radio_init();
    chMBObjectInit(&tx_mb, tx_mb_msgs, RADIO_FB_COUNT);
}

void comms_start(void)
{
    radio_start();
    for (int i = 0; i < EDL_WORKERS; i++) {
        edl_tp[i] = chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(0x400), "EDL Worker", NORMALPRIO, edl_thd, NULL);
    }
    ax5043RX(&lband, false, false);
    ax5043RX(&uhf, false, false);
    tx_tp = chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(0x400), "TX Worker", NORMALPRIO, tx_worker, (void*)tx_eng);
}

void comms_stop(void)
{
    /* Stop transmissions */
    comms_beacon(false);
    chThdTerminate(tx_tp);
    chThdWait(tx_tp);
    tx_tp = NULL;

    /* Stop receiving */
    radio_stop();

    /* Terminate receive threads */
    for (int i = 0; i < EDL_WORKERS; i++) {
        chThdTerminate(edl_tp[i]);
        chThdWait(edl_tp[i]);
        edl_tp[i] = NULL;
    }
}

void comms_beacon(bool enable)
{
    if (enable && beacon_tp == NULL) {
        beacon_tp = chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(0x800), "Beacon", NORMALPRIO, beacon, (void*)tx_ax25);
    } else if (!enable && beacon_tp != NULL) {
        chThdTerminate(beacon_tp);
        chThdWait(beacon_tp);
        beacon_tp = NULL;
    }
}

void comms_send(fb_t *fb)
{
    osalDbgCheck(fb != NULL);
    chMBPostTimeout(&tx_mb, (msg_t)(fb), TIME_INFINITE);
}

void comms_send_ahead(fb_t *fb)
{
    osalDbgCheck(fb != NULL);
    chMBPostAheadTimeout(&tx_mb, (msg_t)(fb), TIME_INFINITE);
}
