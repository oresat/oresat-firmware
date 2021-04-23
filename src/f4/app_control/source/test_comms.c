#include <stdlib.h>
#include <string.h>
#include "test_comms.h"
#include "c3.h"
#include "cmd.h"
#include "file_xfr.h"
#include "comms.h"
#include "uslp.h"
#include "chprintf.h"

#define COMMS_EVENT_LOOPBACK_RX EVENT_MASK(0)

extern const uslp_mc_t mc;

static fb_t *tx_fb;

static thread_t *cli_tp;

static uint8_t resp_buf[CMD_RESP_LEN];
static size_t buf_len;

static void loopback_tx(fb_t *fb);
static void loopback_rx(fb_t *fb);

static const uslp_map_t map_cmd = {
    .sdu            = SDU_MAP_ACCESS,
    .upid           = UPID_MAPA_SDU,
    .max_pkt_len    = CMD_RESP_LEN,
    .incomplete     = false,
    .map_recv       = loopback_rx,
};

static const uslp_map_t map_file = {
    .sdu            = SDU_MAP_ACCESS,
    .upid           = UPID_MAPA_SDU,
    .max_pkt_len    = FILE_BUF_LEN,
    .incomplete     = false,
    .map_recv       = loopback_rx,
};

static const uslp_vc_t vc0 = {
    .seq_ctrl_len   = 0,
    .expedited_len  = 0,
    .seq_ctrl_cnt   = NULL,
    .expedited_cnt  = NULL,
    .cop            = COP_NONE,
    .mapid[0]       = &map_cmd,
    .mapid[1]       = &map_file,
    .trunc_tf_len   = USLP_MAX_LEN,
    .ocf            = false,
#if (USLP_USE_SDLS == TRUE)
    .sdls_hdr_len   = 0,
    .sdls_tlr_len   = 0,
#endif
};

static const uslp_mc_t loopback_mc = {
    .scid           = SCID,
    .vcid[0]        = &vc0,
};

static const uslp_pc_t loopback_pc = {
    .name           = "Loopback",
    .tf_len         = USLP_MAX_LEN,
    .fecf           = FECF_HW,
    .fecf_len       = FECF_LEN,
    .phy_send       = loopback_tx,
    .phy_send_prio  = loopback_tx,
};

static const uslp_link_t edl_loopback_tx_link = {
    .mc = &mc,
    .pc_rx = &loopback_pc,
    .pc_tx = &loopback_pc,
};

static const uslp_link_t edl_loopback_rx_link = {
    .mc = &loopback_mc,
    .pc_rx = &loopback_pc,
    .pc_tx = &loopback_pc,
};

static void loopback_tx(fb_t *fb)
{
    osalDbgCheck(fb != NULL);
    if (fb == tx_fb) {
        fb->phy_arg = (void*)&edl_loopback_tx_link;
        fb_post(fb);
    } else {
        uslp_recv(&edl_loopback_rx_link, fb);
        fb_free(fb);
    }
}

static void loopback_rx(fb_t *fb)
{
    osalDbgCheck(fb != NULL);
    memcpy(resp_buf, fb->data, fb->len);
    buf_len = fb->len;
    chEvtSignal(cli_tp, COMMS_EVENT_LOOPBACK_RX);
}

static void send_cmd(cmd_code_t cmd_code, uint8_t arg[], size_t arg_len)
{
    cmd_t *cmd;
    tx_fb = fb_alloc(CMD_RESP_ALLOC);
    fb_reserve(tx_fb, USLP_MAX_HEADER_LEN);
    cmd = fb_put(tx_fb, sizeof(cmd_t) + arg_len);
    cmd->cmd = cmd_code;
    if (arg != NULL)
        memcpy(cmd->arg, arg, arg_len);
    uslp_map_send(&edl_loopback_tx_link, tx_fb, 0, 0, true);
    chEvtWaitAnyTimeout(COMMS_EVENT_LOOPBACK_RX, TIME_INFINITE);
}

static void print_response(BaseSequentialStream *chp)
{
        chprintf(chp, "Response buffer:");
        for (size_t i = 0; i < buf_len; i++) {
            if (i % 0x10 == 0) chprintf(chp, "\r\n%04X:", i);
            chprintf(chp, " %02X", resp_buf[i]);
        }
        chprintf(chp, "\r\n");
}

/*===========================================================================*/
/* OreSat C3 EDL                                                             */
/*===========================================================================*/
void cmd_edl(BaseSequentialStream *chp, int argc, char *argv[])
{
    cli_tp = chThdGetSelfX();

    if (argc < 1) {
        goto edl_usage;
    }
    if (!strcmp(argv[0], "tx_enable") && argc > 1) {
        uint8_t arg = strtoul(argv[1], NULL, 0);
        send_cmd(CMD_TX_CTRL, &arg, sizeof(arg));
        print_response(chp);
    } else if (!strcmp(argv[0], "c3_flash") && argc > 2) {
        struct {
            uint32_t crc;
            char filename[strlen(argv[1])];
        } arg;
        arg.crc = strtoul(argv[2], NULL, 0);
        memcpy(arg.filename, argv[1], strlen(argv[1]));
        send_cmd(CMD_C3_FLASH, (uint8_t*)&arg, sizeof(arg));
        print_response(chp);
    } else if (!strcmp(argv[0], "c3_bank") && argc > 1) {
        uint8_t arg = strtoul(argv[1], NULL, 0);
        send_cmd(CMD_C3_BANK, &arg, sizeof(arg));
        print_response(chp);
    } else if (!strcmp(argv[0], "opd_sysenable")) {
        send_cmd(CMD_OPD_SYSENABLE, NULL, 0);
        print_response(chp);
    } else if (!strcmp(argv[0], "opd_sysdisable")) {
        send_cmd(CMD_OPD_SYSDISABLE, NULL, 0);
        print_response(chp);
    } else if (!strcmp(argv[0], "opd_enable") && argc > 1) {
        uint8_t arg = strtoul(argv[1], NULL, 0);
        send_cmd(CMD_OPD_ENABLE, &arg, sizeof(arg));
        print_response(chp);
    } else if (!strcmp(argv[0], "opd_disable") && argc > 1) {
        uint8_t arg = strtoul(argv[1], NULL, 0);
        send_cmd(CMD_OPD_DISABLE, &arg, sizeof(arg));
        print_response(chp);
    } else if (!strcmp(argv[0], "opd_reset") && argc > 1) {
        uint8_t arg = strtoul(argv[1], NULL, 0);
        send_cmd(CMD_OPD_RESET, &arg, sizeof(arg));
        print_response(chp);
    } else if (!strcmp(argv[0], "send")) {
        uint8_t buf[] = {
            0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
            0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
            0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
            0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
            0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
            0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
            0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
            0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F
        };
        edl_enable(true);
        tx_fb = fb_alloc(sizeof(buf));
        tx_fb->data_ptr = fb_put(tx_fb, sizeof(buf));
        memcpy(tx_fb->data_ptr, buf, sizeof(buf));
        comms_send(tx_fb);
    } else {
        goto edl_usage;
    }

    return;

edl_usage:
    chprintf(chp,  "Usage: edl <command>\r\n"
                   "    tx_enable <value>:\r\n"
                   "        Post a TX Enable command to EDL RX queue with <value>\r\n"
                   "    c3_flash <filename> <crc32>:\r\n"
                   "        Post a C3 Flash command to EDL RX queue\r\n"
                   "    c3_bank <bank>:\r\n"
                   "        Post a C3 Bank command to EDL RX queue\r\n"
                   "    opd_sysenable:\r\n"
                   "        Post a OPD SysEnable command to EDL RX queue\r\n"
                   "    opd_sysdisable:\r\n"
                   "        Post a OPD SysDisable command to EDL RX queue\r\n"
                   "    opd_enable <addr>:\r\n"
                   "        Post a OPD Enable command for <addr> to EDL RX queue\r\n"
                   "    opd_disable <addr>:\r\n"
                   "        Post a OPD Disable command for <addr> to EDL RX queue\r\n"
                   "    opd_reset <addr>:\r\n"
                   "        Post a OPD Reset command for <addr> to EDL RX queue\r\n"
                   "    send:\r\n"
                   "        Send a packet on EDL link\r\n"
                   "\r\n");
    return;
}
