#include <stdlib.h>
#include <string.h>
#include "test_comms.h"
#include "c3.h"
#include "cmd.h"
#include "file_xfr.h"
#include "comms.h"
#include "uslp.h"
#include "hmac.h"
#include "CANopen.h"
#include "OD.h"
#include "chprintf.h"

#define COMMS_EVENT_LOOPBACK_RX EVENT_MASK(0)

extern const uslp_mc_t mc;

static fb_t *tx_fb;

static thread_t *cli_tp;

static uint8_t resp_buf[CMD_RESP_LEN];
static size_t buf_len;

static void pdu_loopback(fb_t *fb, void *arg);
static void resp_recv(fb_t *fb, void *arg);

#if (USLP_USE_SDLS == TRUE)
static const sdls_cfg_t sdls_cfg = {
    .spi            = 1,
    .iv_len         = 0,
    .seq_num_len    = sizeof(OD_PERSIST_STATE.x6004_persistentState.EDL_SequenceCount),
    .pad_len        = 0,
    .mac_len        = 32,
    .send_func      = hmac_send,
    .send_arg       = OD_PERSIST_KEYS.x6005_cryptoKeys[0],
    .recv_func      = NULL,
    .recv_arg       = NULL,
};
#endif

static const uslp_map_t map_cmd = {
    .sdu            = SDU_MAP_ACCESS,
    .upid           = UPID_MAPA_SDU,
    .max_pkt_len    = CMD_RESP_LEN,
    .incomplete     = false,
    .map_recv       = resp_recv,
};

static const uslp_map_t map_file = {
    .sdu            = SDU_MAP_ACCESS,
    .upid           = UPID_MAPA_SDU,
    .max_pkt_len    = FILE_BUF_LEN + sizeof(file_xfr_t),
    .incomplete     = false,
    .map_recv       = resp_recv,
};

static const uslp_vc_t vc0 = {
    .seq_ctrl_len   = 0,
    .expedited_len  = 0,
    .seq_ctrl_cnt   = NULL,
    .expedited_cnt  = NULL,
    .cop            = COP_NONE,
    .mapid[0]       = &map_cmd,
    .trunc_tf_len   = USLP_MAX_LEN,
    .ocf            = false,
#if (USLP_USE_SDLS == TRUE)
    .sdls_cfg       = &sdls_cfg,
#endif
};

static const uslp_vc_t vc1 = {
    .seq_ctrl_len   = 0,
    .expedited_len  = 0,
    .seq_ctrl_cnt   = NULL,
    .expedited_cnt  = NULL,
    .cop            = COP_NONE,
    .mapid[0]       = &map_file,
    .trunc_tf_len   = USLP_MAX_LEN,
    .ocf            = false,
#if (USLP_USE_SDLS == TRUE)
    .sdls_cfg       = NULL,
#endif
};

static const uslp_mc_t loopback_mc = {
    .scid           = &OD_PERSIST_APP.x6006_CCSDS.spacecraftID,
    .owner          = false,
    .vcid[0]        = &vc0,
    .vcid[1]        = &vc1,
};

static const uslp_pc_t loopback_pc = {
    .name           = "Loopback",
    .tf_len         = USLP_MAX_LEN,
    .fecf           = FECF_SW,
    .fecf_len       = FECF_LEN,
    .phy_send       = pdu_loopback,
    .phy_send_ahead = pdu_loopback,
};

static const uslp_link_t edl_loopback_rx_link = {
    .mc = &mc,
    .pc_rx = &loopback_pc,
    .pc_tx = &loopback_pc,
};

static const uslp_link_t edl_loopback_tx_link = {
    .mc = &loopback_mc,
    .pc_rx = &loopback_pc,
    .pc_tx = &loopback_pc,
};

static void pdu_loopback(fb_t *fb, void *arg)
{
    (void)arg;
    if (fb == tx_fb) {
        fb->phy_arg = (void*)&edl_loopback_rx_link;
        pdu_send(fb, &rx_fifo);
    } else {
        uslp_recv(&edl_loopback_tx_link, fb);
        fb_free(fb, &tx_fifo);
    }
}

static void resp_recv(fb_t *fb, void *arg)
{
    (void)arg;
    osalDbgCheck(fb != NULL);
    memcpy(resp_buf, fb->data, fb->len);
    buf_len = fb->len;
    chEvtSignal(cli_tp, COMMS_EVENT_LOOPBACK_RX);
}

static void print_response(BaseSequentialStream *chp)
{
    if (chEvtWaitAnyTimeout(COMMS_EVENT_LOOPBACK_RX, TIME_S2I(30)) != 0) {
        chprintf(chp, "Response buffer:");
        for (size_t i = 0; i < buf_len; i++) {
            if (i % 0x10 == 0) chprintf(chp, "\r\n%04X:", i);
            chprintf(chp, " %02X", resp_buf[i]);
        }
        chprintf(chp, "\r\n");
    } else {
        chprintf(chp, "No response!\r\n");
    }
}

static void send_cmd(cmd_code_t cmd_code, void *arg, size_t arg_len)
{
    cmd_t *cmd;
    tx_fb = fb_alloc(CMD_RESP_ALLOC, &rx_fifo);
    /* TODO: What's the 2 for? */
    fb_reserve(tx_fb, USLP_MAX_HEADER_LEN + 2 + 6); /* TODO: Replace 6 with some calculation of SDLS overhead */
    cmd = fb_put(tx_fb, sizeof(cmd_t) + arg_len);
    cmd->cmd = cmd_code;
    if (arg != NULL)
        memcpy(cmd->arg, arg, arg_len);
    uslp_map_send(&edl_loopback_tx_link, tx_fb, 0, 0, true);
}

static int send_file_seg(BaseSequentialStream *chp, char *src, char *dest, lfs_soff_t off, lfs_size_t len)
{
    file_xfr_t *xfr;
    lfs_file_t *file;
    uint8_t *data;
    int ret;

    file = file_open(&FSD1, src, LFS_O_RDONLY);
    if (file == NULL) {
        return FSD1.err;
    }
    ret = file_seek(&FSD1, file, off, LFS_SEEK_SET);
    if (ret < 0) {
        file_close(&FSD1, file);
        return ret;
    }

    tx_fb = fb_alloc(FB_MAX_LEN, &rx_fifo);
    /* TODO: What's the 2 for? */
    fb_reserve(tx_fb, USLP_MAX_HEADER_LEN + sizeof(file_xfr_t) + 2 + 6); /* TODO: Replace 6 with some calculation of SDLS overhead */
    data = fb_put(tx_fb, len);
    ret = file_read(&FSD1, file, data, len);
    file_close(&FSD1, file);
    if (ret < 0) {
        fb_free(tx_fb, &rx_fifo);
        return ret;
    }
    xfr = fb_push(tx_fb, sizeof(file_xfr_t));
    memcpy(xfr->filename, dest, strlen(dest) + 1);
    xfr->off = off;
    xfr->len = len;
    chprintf(chp, "Sending %d byte block to offset %d...\r\n", len, off);
    uslp_map_send(&edl_loopback_tx_link, tx_fb, 0, 1, true);
    print_response(chp);

    return ret;
}

static int send_file(BaseSequentialStream *chp, char *src, char *dest)
{
    lfs_ssize_t len;
    lfs_soff_t off = 0;
    lfs_file_t *file;

    if (!strcmp(src, dest)) {
        return LFS_ERR_INVAL;
    }

    file = file_open(&FSD1, src, LFS_O_RDONLY);
    if (file == NULL) {
        return FSD1.err;
    }
    len = file_size(&FSD1, file);
    file_close(&FSD1, file);
    if (len < 0) {
        return FSD1.err;
    }

    while (len) {
        lfs_ssize_t n = (len > FILE_BUF_LEN ? FILE_BUF_LEN : len);
        n = send_file_seg(chp, src, dest, off, n);
        if (n < 0) {
            return n;
        }
        off += n;
        len -= n;
    }
    return off;
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
    } else if (!strcmp(argv[0], "fw_flash") && argc > 2) {
        struct {
            uint32_t crc;
            char filename[strlen(argv[1]) + 1];
        } arg;
        arg.crc = strtoul(argv[2], NULL, 0);
        memcpy(arg.filename, argv[1], strlen(argv[1]) + 1);
        send_cmd(CMD_FW_FLASH, &arg, sizeof(arg));
        print_response(chp);
    } else if (!strcmp(argv[0], "fw_bank") && argc > 1) {
        uint8_t arg = strtoul(argv[1], NULL, 0);
        send_cmd(CMD_FW_BANK, &arg, sizeof(arg));
        print_response(chp);
    } else if (!strcmp(argv[0], "fw_verify") && argc > 1) {
        uint8_t arg = strtoul(argv[1], NULL, 0);
        send_cmd(CMD_FW_VERIFY, &arg, sizeof(arg));
        print_response(chp);
    } else if (!strcmp(argv[0], "c3_softreset")) {
        uint32_t arg[] = {0x01234567U, 0x89ABCDEFU};
        send_cmd(CMD_C3_SOFTRESET, arg, sizeof(arg));
    } else if (!strcmp(argv[0], "c3_hardreset")) {
        uint32_t arg[] = {0x01234567U, 0x89ABCDEFU};
        send_cmd(CMD_C3_HARDRESET, arg, sizeof(arg));
    } else if (!strcmp(argv[0], "c3_factoryreset")) {
        uint32_t arg[] = {0x01234567U, 0x89ABCDEFU};
        send_cmd(CMD_C3_FACTORYRESET, arg, sizeof(arg));
    } else if (!strcmp(argv[0], "fs_upload") && argc > 2) {
        chprintf(chp, "File send result: %d\r\n", send_file(chp, argv[1], argv[2]));
    } else if (!strcmp(argv[0], "fs_upload_seg") && argc > 4) {
        lfs_soff_t off = strtoul(argv[3], NULL, 0);
        lfs_ssize_t len = strtoul(argv[4], NULL, 0);
        chprintf(chp, "File send result: %d\r\n", send_file_seg(chp, argv[1], argv[2], off, len));
    } else if (!strcmp(argv[0], "fs_format")) {
        send_cmd(CMD_FS_FORMAT, NULL, 0);
        print_response(chp);
    } else if (!strcmp(argv[0], "fs_unmount")) {
        send_cmd(CMD_FS_UNMOUNT, NULL, 0);
        print_response(chp);
    } else if (!strcmp(argv[0], "fs_remove") && argc > 1) {
        send_cmd(CMD_FS_REMOVE, argv[1], strlen(argv[1]) + 1);
        print_response(chp);
    } else if (!strcmp(argv[0], "fs_crc") && argc > 1) {
        send_cmd(CMD_FS_CRC, argv[1], strlen(argv[1]) + 1);
        print_response(chp);
    } else if (!strcmp(argv[0], "node_enable") && argc > 2) {
        uint8_t arg[2];
        arg[0] = strtoul(argv[1], NULL, 0);
        arg[1] = strtoul(argv[2], NULL, 0);
        send_cmd(CMD_NODE_ENABLE, arg, sizeof(arg));
        print_response(chp);
    } else if (!strcmp(argv[0], "node_status") && argc > 1) {
        uint8_t arg = strtoul(argv[1], NULL, 0);
        send_cmd(CMD_NODE_STATUS, &arg, sizeof(arg));
        print_response(chp);
    } else if (!strcmp(argv[0], "opd_sysenable")) {
        send_cmd(CMD_OPD_SYSENABLE, NULL, 0);
        print_response(chp);
    } else if (!strcmp(argv[0], "opd_sysdisable")) {
        send_cmd(CMD_OPD_SYSDISABLE, NULL, 0);
        print_response(chp);
    } else if (!strcmp(argv[0], "opd_scan") && argc > 1) {
        uint8_t arg = strtoul(argv[1], NULL, 0);
        send_cmd(CMD_OPD_SCAN, &arg, sizeof(arg));
        print_response(chp);
    } else if (!strcmp(argv[0], "opd_enable") && argc > 2) {
        uint8_t arg[2];
        arg[0] = strtoul(argv[1], NULL, 0);
        arg[1] = strtoul(argv[2], NULL, 0);
        send_cmd(CMD_OPD_ENABLE, arg, sizeof(arg));
        print_response(chp);
    } else if (!strcmp(argv[0], "opd_reset") && argc > 1) {
        uint8_t arg = strtoul(argv[1], NULL, 0);
        send_cmd(CMD_OPD_RESET, &arg, sizeof(arg));
        print_response(chp);
    } else if (!strcmp(argv[0], "opd_status") && argc > 1) {
        uint8_t arg = strtoul(argv[1], NULL, 0);
        send_cmd(CMD_OPD_STATUS, &arg, sizeof(arg));
        print_response(chp);
    } else if (!strcmp(argv[0], "rtc_settime") && argc > 1) {
        uint32_t arg = strtoul(argv[1], NULL, 0);
        send_cmd(CMD_RTC_SETTIME, &arg, sizeof(arg));
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
        tx_fb = fb_alloc(sizeof(buf), &tx_fifo);
        tx_fb->data_ptr = fb_put(tx_fb, sizeof(buf));
        memcpy(tx_fb->data_ptr, buf, sizeof(buf));
        pdu_send(tx_fb, &tx_fifo);
    } else {
        goto edl_usage;
    }

    return;

edl_usage:
    chprintf(chp,  "Usage: edl <command>\r\n"
                   "    tx_enable <value>:\r\n"
                   "        Post a TX Enable command to EDL RX queue with <value>\r\n"
                   "    fw_flash <filename> <crc32>:\r\n"
                   "        Post a FW Flash command to EDL RX queue\r\n"
                   "    fw_bank <bank>:\r\n"
                   "        Post a FW Bank command to EDL RX queue\r\n"
                   "    fw_verify <bank>:\r\n"
                   "        Post a FW Verify command to EDL RX queue\r\n"
                   "    c3_softreset:\r\n"
                   "        Post a C3 Soft Reset command to EDL RX queue\r\n"
                   "    c3_hardreset:\r\n"
                   "        Post a C3 Hard Reset command to EDL RX queue\r\n"
                   "    c3_factoryreset:\r\n"
                   "        Post a C3 Factory Reset command to EDL RX queue\r\n"
                   "    fs_upload <src> <dest>:\r\n"
                   "        Upload <src> to <dest> via EDL\r\n"
                   "    fs_upload_seg <src> <dest> <offset> <len>:\r\n"
                   "        Upload <len> bytes starting at <offset> from <src> to <dest> via EDL\r\n"
                   "    fs_format:\r\n"
                   "        Post FS Format command to EDL RX queue\r\n"
                   "    fs_unmount:\r\n"
                   "        Post FS Unmount command to EDL RX queue\r\n"
                   "    fs_remove <filename>:\r\n"
                   "        Post FS Remove command to EDL RX queue\r\n"
                   "    fs_crc <filename>:\r\n"
                   "        Post FS CRC command to EDL RX queue\r\n"
                   "    node_enable <nodeid> <enable>:\r\n"
                   "        Post a Node Enable command for <nodeid> to EDL RX queue\r\n"
                   "    node_status <nodeid>:\r\n"
                   "        Post a Node Status command for <nodeid> to EDL RX queue\r\n"
                   "    opd_sysenable:\r\n"
                   "        Post a OPD SysEnable command to EDL RX queue\r\n"
                   "    opd_sysdisable:\r\n"
                   "        Post a OPD SysDisable command to EDL RX queue\r\n"
                   "    opd_scan <restart>:\r\n"
                   "        Post a OPD Scan command for <addr> to EDL RX queue\r\n"
                   "    opd_enable <addr> <enable>:\r\n"
                   "        Post a OPD Enable command for <addr> to EDL RX queue\r\n"
                   "    opd_reset <addr>:\r\n"
                   "        Post a OPD Reset command for <addr> to EDL RX queue\r\n"
                   "    opd_status <addr>:\r\n"
                   "        Post a OPD Status command for <addr> to EDL RX queue\r\n"
                   "    send:\r\n"
                   "        Send a packet on EDL link\r\n"
                   "\r\n");
    return;
}
