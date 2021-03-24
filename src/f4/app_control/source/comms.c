#include <stdio.h>

#include "ch.h"
#include "hal.h"
#include "rtc.h"
#include "comms.h"
#include "uslp.h"
#include "CANopen.h"

#define XTAL_CLK                            16000000
#define RADIO_PDU_COUNT                     8U
#define RADIO_PDU_SIZE                      512U

static objects_fifo_t pdu_fifo;
static msg_t pdu_fifo_msgs[RADIO_PDU_COUNT];
static uint8_t pdu_fifo_buf[RADIO_PDU_COUNT][RADIO_PDU_SIZE];

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

static const ax5043_profile_t uhf_cw[] = {
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
    .pdu_fifo       = &pdu_fifo,
    .pdu_size       = RADIO_PDU_SIZE,
    .profile        = lband_eng,
};

static const AX5043Config uhfcfg = {
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
    .phy_send       = NULL,
    .phy_arg        = NULL,
};

static const uslp_pc_t lband_pc = {
    .name           = "L-Band",
    .tf_len         = RADIO_PDU_SIZE,
    .fecf           = true,
    .fecf_len       = 2,
};

radio_dev_t radio_devices[] = {
    {&lband, &lbandcfg, "L-Band"},
    {&uhf, &uhfcfg, "UHF"},
    {NULL, NULL, ""},
};

radio_profile_t radio_profiles[] = {
    {lband_eng, "L-Band Engineering"},
    {uhf_eng, "UHF Engineering"},
    {uhf_ax25, "UHF AX.25"},
    {uhf_cw, "UHF CW"},
    {NULL, ""},
};

synth_dev_t synth_devices[] = {
    {&synth, &synthcfg, "LO"},
    {NULL, NULL, ""},
};

static thread_t *rx_tp = NULL;
static thread_t *beacon_tp = NULL;

THD_WORKING_AREA(radio_rx_wa, 0x400);
THD_FUNCTION(radio_rx, arg) {
    (void)arg;
    uint8_t *pdu;

    chRegSetThreadName("EDL RX");

    while (!chThdShouldTerminateX()) {
        if (chFifoReceiveObjectTimeout(&pdu_fifo, (void**)&pdu, TIME_MS2I(1000)) != MSG_OK) {
            continue;
        }

        /* TODO: Process received PDU */

        chFifoReturnObject(&pdu_fifo, pdu);
    }

    chThdExit(MSG_OK);
}

THD_WORKING_AREA(radio_beacon_wa, 0x800);
THD_FUNCTION(radio_beacon, arg) {
    (void)arg;
    uint8_t mac_hdr[] = {'S' << 1, 'P' << 1, 'A' << 1, 'C' << 1, 'E' << 1, ' ' << 1, 0x60U,  /* APRS Destination                         */
                         'K' << 1, 'J' << 1, '7' << 1, 'S' << 1, 'A' << 1, 'T' << 1, 0x61U,  /* APRS Source                              */
                         0x03, 0xF0};                                                        /* UI Frame, No protocol ID                 */
    uint8_t net_hdr[] = {':'};                                                               /* APRS Message                             */
    char telem_data[256];
    uint8_t buf[512];

    pdu_t pdu = {
        .net_hdr = net_hdr,
        .net_len = sizeof(net_hdr),
        .mac_hdr = mac_hdr,
        .mac_len = sizeof(mac_hdr),
        .data = telem_data,
        .data_len = sizeof(telem_data),
        .buf = buf,
        .buf_max = sizeof(buf),
    };

    while (!chThdShouldTerminateX()) {
        time_t unix_time = rtcGetTimeUnix(NULL);
        pdu.data_len = sprintf(telem_data, "KJ7SAT - Test beacon from AX5043 driver. %s", ctime(&unix_time));
        /* TODO: CW Beacon */
        /*ax5043_SetProfile(&uhf, uhf_cw);*/
        /*ax5043TX(&uhf, pdu.buf, pdu.buf_len, pdu.buf_len, NULL, NULL, false);*/

        /* APRS Beacon */
        pdu_gen(&pdu);
        ax5043SetProfile(&uhf, uhf_ax25);
        ax5043TX(&uhf, pdu.buf, pdu.buf_len, pdu.buf_len, NULL, NULL, false);

        chThdSleepMilliseconds(OD_TX_Control.beaconInterval);
    }

    chThdExit(MSG_OK);
}

void comms_init(void)
{
    /* Initialize PDU FIFO */
    chFifoObjectInit(&pdu_fifo, RADIO_PDU_SIZE, RADIO_PDU_COUNT, pdu_fifo_buf, pdu_fifo_msgs);

    /* Initialize radio systems */
    for (int i = 0; radio_devices[i].devp != NULL; i++) {
        ax5043ObjectInit(radio_devices[i].devp);
    }
    for (int i = 0; synth_devices[i].devp != NULL; i++) {
        si41xxObjectInit(synth_devices[i].devp);
    }
}

void comms_start(void)
{
    /* Start radio systems */
    for (int i = 0; radio_devices[i].devp != NULL; i++) {
        ax5043Start(radio_devices[i].devp, radio_devices[i].cfgp);
    }
    for (int i = 0; synth_devices[i].devp != NULL; i++) {
        si41xxStart(synth_devices[i].devp, synth_devices[i].cfgp);
    }

    rx_tp = chThdCreateStatic(radio_rx_wa, sizeof(radio_rx_wa), NORMALPRIO, radio_rx, NULL);

    ax5043RX(&lband, false, false);
    ax5043RX(&uhf, false, false);
}

void comms_stop(void)
{
    for (int i = 0; radio_devices[i].devp != NULL; i++) {
        ax5043Stop(radio_devices[i].devp);
    }

    chThdTerminate(rx_tp);
    chThdWait(rx_tp);
    rx_tp = NULL;
}

void comms_beacon(bool enable)
{
    if (enable && beacon_tp == NULL) {
        beacon_tp = chThdCreateStatic(radio_beacon_wa, sizeof(radio_beacon_wa), NORMALPRIO, radio_beacon, NULL);
    } else if (!enable && beacon_tp != NULL) {
        chThdTerminate(beacon_tp);
        chThdWait(beacon_tp);
        beacon_tp = NULL;
    }
}
