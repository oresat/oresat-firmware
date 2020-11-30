/**
 * @file    radio.c
 * @brief   OreSat radio support library.
 *
 * @addtogroup RADIO
 * @{
 */
#include "ch.h"
#include "hal.h"
#include "radio.h"
#include "ax5043.h"
#include "si41xx.h"
#include "uslp.h"

/*===========================================================================*/
/* Local definitions.                                                        */
/*===========================================================================*/

#define XTAL_CLK                            16000000

/*===========================================================================*/
/* Exported variables.                                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Local variables and types.                                                */
/*===========================================================================*/

static objects_fifo_t pdu_fifo;
static msg_t pdu_fifo_msgs[RADIO_PDU_COUNT];
static uint8_t pdu_fifo_buf[RADIO_PDU_COUNT][RADIO_PDU_SIZE];
static thread_t *rx_tp = NULL;

static const SPIConfig lband_spicfg = {
    false,
    NULL,                                   // Operation complete callback
    LINE_LBAND_CS,
    // SPI cr1 data                         (see 446 ref man.)
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

const ax5043_profile_t lband_eng[] = {
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

const ax5043_profile_t uhf_eng[] = {
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
    {AX5043_REG_MODCFGA, AX5043_MODCFGA_TXSE | _VAL2FLD(AX5043_MODCFGA_AMPLSHAPE, AX5043_AMPLSHAPE_RAISEDCOS), 1},
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

const ax5043_profile_t uhf_ax25[] = {
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
    {AX5043_REG_MODCFGA, AX5043_MODCFGA_TXSE | _VAL2FLD(AX5043_MODCFGA_AMPLSHAPE, AX5043_AMPLSHAPE_RAISEDCOS), 1},
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

const ax5043_profile_t uhf_cw[] = {
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
    {AX5043_REG_MODCFGA, AX5043_MODCFGA_TXSE | _VAL2FLD(AX5043_MODCFGA_AMPLSHAPE, AX5043_AMPLSHAPE_RAISEDCOS), 1},
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

const uint8_t preamble[] = {
    AX5043_CHUNKCMD_TXCTRL | _VAL2FLD(AX5043_FIFOCHUNK_SIZE, 1),
    AX5043_CHUNK_TXCTRL_SETPA | AX5043_CHUNK_TXCTRL_PASTATE,
    AX5043_CHUNKCMD_REPEATDATA | _VAL2FLD(AX5043_FIFOCHUNK_SIZE, 3),
    AX5043_CHUNK_REPEATDATA_UNENC | AX5043_CHUNK_REPEATDATA_NOCRC,
    20,
    0x55,
    AX5043_CHUNKCMD_REPEATDATA | _VAL2FLD(AX5043_FIFOCHUNK_SIZE, 3),
    AX5043_CHUNK_REPEATDATA_RAW | AX5043_CHUNK_REPEATDATA_NOCRC,
    30,
    0x7E
};

const uint8_t postamble[] = {
    AX5043_CHUNKCMD_REPEATDATA | _VAL2FLD(AX5043_FIFOCHUNK_SIZE, 3),
    AX5043_CHUNK_REPEATDATA_RAW | AX5043_CHUNK_REPEATDATA_NOCRC,
    5,
    0x7E,
    AX5043_CHUNKCMD_TXCTRL | _VAL2FLD(AX5043_FIFOCHUNK_SIZE, 1),
    AX5043_CHUNK_TXCTRL_SETPA
};

const AX5043Config lbandcfg = {
    .spip           = &SPID1,
    .spicfg         = &lband_spicfg,
    .miso           = LINE_SPI1_MISO,
    .irq            = LINE_LBAND_IRQ,
    .xtal_freq      = XTAL_CLK,
    .pdu_fifo       = &pdu_fifo,
    .pdu_size       = RADIO_PDU_SIZE,
    .profile        = lband_eng,
};

const AX5043Config uhfcfg = {
    .spip           = &SPID1,
    .spicfg         = &uhf_spicfg,
    .miso           = LINE_SPI1_MISO,
    .irq            = LINE_UHF_IRQ,
    .xtal_freq      = XTAL_CLK,
    .pdu_fifo       = &pdu_fifo,
    .pdu_size       = RADIO_PDU_SIZE,
    .profile        = uhf_eng,
    .preamble       = preamble,
    .preamble_len   = sizeof(preamble),
    .postamble      = postamble,
    .postamble_len  = sizeof(postamble),
};

SI41XXConfig synthcfg = {
    .sen            = LINE_LO_SEN,
    .sclk           = LINE_LO_SCLK,
    .sdata          = LINE_LO_SDATA,
    .ref_freq       = XTAL_CLK,
    .if_div         = SI41XX_IFDIV_DIV1,
    .if_n           = 1616,
    .if_r           = 32,
};

AX5043Driver lband;
AX5043Driver uhf;
SI41XXDriver synth;

static const uslp_pkt_t spp = {
    .pvn            = PVN_SPACE,
    .max_pkt_len    = 512,
    .incomplete     = false,
};

static const uslp_map_t map0 = {
    .sdu            = SDU_MAP_PKT,
    .upid           = UPID_SPP_ENCAPS,
    .pkt            = &spp,
};

static const uslp_vc_t vc0 = {
    .cop            = COP_NONE,
    .mapid[0]       = &map0,
    .trunc_tf_len   = 128,
    .sdls_hdr       = NULL,
    .sdls_tlr       = NULL,
    .sdls_hdr_len   = 0,
    .sdls_tlr_len   = 0,
};

static const uslp_mc_t mc = {
    .scid           = 0x4F53,
    .vcid[0]        = &vc0,
};

static const uslp_pc_t uhf_pc = {
    .name           = "UHF",
    .tf_len         = RADIO_PDU_SIZE,
    .fecf           = true,
    .fecf_len       = 2,
    .phy_send       = uhf_send,
    .phy_arg        = uhf_eng,
};

static const uslp_pc_t lband_pc = {
    .name           = "L-Band",
    .tf_len         = RADIO_PDU_SIZE,
    .fecf           = true,
    .fecf_len       = 2,
};

/*===========================================================================*/
/* Local functions.                                                          */
/*===========================================================================*/

THD_WORKING_AREA(radio_rx_wa, 0x400);
THD_FUNCTION(radio_rx, arg) {
    (void)arg;
    uint8_t *pdu;

    while (!chThdShouldTerminateX()) {
        if (chFifoReceiveObjectTimeout(&pdu_fifo, (void**)&pdu, TIME_MS2I(1000)) != MSG_OK) {
            continue;
        }

        /*uslp_recv(pdu, RADIO_PDU_SIZE, 0, &mc);*/

        chFifoReturnObject(&pdu_fifo, pdu);
    }

    chThdExit(MSG_OK);
}

/*===========================================================================*/
/* Interface implementation.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Exported functions.                                                       */
/*===========================================================================*/

void radio_init(void)
{
    /* Initialize radio systems */
    chFifoObjectInit(&pdu_fifo, RADIO_PDU_SIZE, RADIO_PDU_COUNT, pdu_fifo_buf, pdu_fifo_msgs);
    ax5043ObjectInit(&lband);
    ax5043ObjectInit(&uhf);
    si41xxObjectInit(&synth);
}

void radio_start(void)
{
    /* Start radio systems */
    ax5043Start(&lband, &lbandcfg);
    ax5043Start(&uhf, &uhfcfg);
    si41xxStart(&synth, &synthcfg);

    rx_tp = chThdCreateStatic(radio_rx_wa, sizeof(radio_rx_wa), NORMALPRIO, radio_rx, NULL);

    ax5043RX(&lband, false, false);
    ax5043RX(&uhf, false, false);
}

void radio_stop(void)
{
    ax5043Stop(&lband);
    ax5043Stop(&uhf);

    chThdTerminate(rx_tp);
    chThdWait(rx_tp);
    rx_tp = NULL;
}

void uhf_send(pdu_t *pdu, void *arg)
{
    if (arg) {
        ax5043SetProfile(&uhf, arg);
    }

    ax5043TX(&uhf, pdu->buf, pdu->buf_len, pdu->buf_len, NULL, NULL, false);
}

/** @} */
