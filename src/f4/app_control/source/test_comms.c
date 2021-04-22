#include <stdlib.h>
#include <string.h>
#include "test_comms.h"
#include "c3.h"
#include "cmd.h"
#include "comms.h"
#include "uslp.h"
#include "chprintf.h"

#define COMMS_EVENT_LOOPBACK_RX EVENT_MASK(0)

extern const uslp_mc_t mc;

static fb_t *tx_fb;

static uint8_t resp_buf[64];
static thread_t *cli_tp;

void loopback_tx(fb_t *fb);
void loopback_rx(fb_t *fb);

static const uslp_map_t map_cmd = {
    .sdu            = SDU_MAP_ACCESS,
    .upid           = UPID_MAPA_SDU,
    .max_pkt_len    = 1024,
    .incomplete     = false,
    .map_recv       = loopback_rx,
};

static const uslp_vc_t vc0 = {
    .seq_ctrl_len   = 0,
    .expedited_len  = 0,
    .seq_ctrl_cnt   = NULL,
    .expedited_cnt  = NULL,
    .fop            = NULL,
    .farm           = NULL,
    .mapid[0]       = &map_cmd,
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
    .fecf           = true,
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

void loopback_tx(fb_t *fb)
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

void loopback_rx(fb_t *fb)
{
    osalDbgCheck(fb != NULL);
    memcpy(resp_buf, fb->data, fb->len);
    chEvtSignal(cli_tp, COMMS_EVENT_LOOPBACK_RX);
}

/*===========================================================================*/
/* OreSat C3 EDL                                                             */
/*===========================================================================*/
void cmd_edl(BaseSequentialStream *chp, int argc, char *argv[])
{
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

    cli_tp = chThdGetSelfX();

    if (argc < 1) {
        goto edl_usage;
    }
    if (!strcmp(argv[0], "tx_enable")) {
        cmd_t *cmd;
        tx_fb = fb_alloc(64);
        cmd = fb_put(tx_fb, sizeof(cmd_t) + 1);
        cmd->cmd = CMD_TX_CTRL;
        cmd->arg[0] = 1;
        uslp_map_send(&edl_loopback_tx_link, tx_fb, 0, 0, true);
        chEvtWaitAnyTimeout(COMMS_EVENT_LOOPBACK_RX, TIME_INFINITE);
        chprintf(chp, "Response buffer:");
        for (size_t i = 0; i < 64; i++) {
            if (i % 0x10) chprintf(chp, "\r\n%04X:", i);
            chprintf(chp, " %02X", resp_buf[i]);
        }
    } else if (!strcmp(argv[0], "tx_disable")) {
        cmd_t *cmd;
        tx_fb = fb_alloc(64);
        cmd = fb_put(tx_fb, sizeof(cmd_t) + 1);
        cmd->cmd = CMD_TX_CTRL;
        cmd->arg[0] = 0;
        uslp_map_send(&edl_loopback_tx_link, tx_fb, 0, 0, true);
        chEvtWaitAnyTimeout(COMMS_EVENT_LOOPBACK_RX, TIME_INFINITE);
        chprintf(chp, "Response buffer:");
        for (size_t i = 0; i < 64; i++) {
            if (i % 0x10) chprintf(chp, "\r\n%04X:", i);
            chprintf(chp, " %02X", resp_buf[i]);
        }
    } else if (!strcmp(argv[0], "send")) {
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
                   "    tx_enable:\r\n"
                   "        Post a TX Enable command to EDL RX queue\r\n"
                   "    tx_disable:\r\n"
                   "        Post a TX Disable command to EDL RX queue\r\n"
                   "    send:\r\n"
                   "        Send a packet on EDL link\r\n"
                   "\r\n");
    return;
}
