#include "beacon.h"
#include "radio.h"
#include "CANopen.h"
#include "ax25.h"

static const ax25_link_t ax25 = {
    .dest = "SPACE ",
    .dest_ssid = 0,
    .src = "KJ7SAT",
    .src_ssid = 0,
    .control = AX25_CTRL_UFRAME | _VAL2FLD(AX25_CTRL_U_FLD, AX25_UFRAME_UI),
    .sid = AX25_PID_NONE,
};

static const tlm_item_t tlm_aprs0[] = {
    {   /* User-Defined APRS Start */
        .type = TLM_MSG,
        .msg = "{",
    },
    {   /* Telemetry Version */
        .type = TLM_LIT,
        .len = 1,
        .val = 0,
    },
    {   /* MCU Temperature */
        .type = TLM_OD,
        .len = 1,
        .index = OD_2021_MCU_Sensors,
        .subindex = OD_2021_1_MCU_Sensors_temperature,
    },
    {   /* User-Defined APRS End */
        .type = TLM_MSG,
        .msg = "}"
    }
};

static const tlm_pkt_t aprs0 = {
    .item_cnt = sizeof(tlm_aprs0),
    .item = tlm_aprs0,
};

void *tlm_payload(fb_t *fb, const tlm_pkt_t *pkt)
{
    void *tlm_start = fb->tail;
    uint16_t od_entry;
    void *data;
    size_t len;

    for (unsigned int i = 0; i < pkt->item_cnt; i++) {
        const tlm_item_t *item = &pkt->item[i];
        switch (item->type) {
        case TLM_MSG:
            len = item->len;
            memcpy(fb_put(fb, len), item->msg, len);
            break;
        case TLM_LIT:
            len = item->len;
            memcpy(fb_put(fb, len), &item->val, len);
            break;
        case TLM_OD:
            od_entry = CO_OD_find(CO->SDO[0], item->index);
            if (od_entry != 0xFFFF) {
                len = CO_OD_getLength(CO->SDO[0], od_entry, item->subindex);
                data = CO_OD_getDataPointer(CO->SDO[0], od_entry, item->subindex);
                if (len == item->len || data != NULL) {
                    memcpy(fb_put(fb, len), data, len);
                }
            }
            break;
        default:
            return NULL;
        }
    }

    return tlm_start;
}

THD_FUNCTION(beacon, arg) {
    const radio_cfg_t *cfg = arg;
    fb_t *fb;

    while (!chThdShouldTerminateX()) {
        while (fb == NULL) {
            fb = fb_alloc(AX25_MAX_FRAME_LEN);
        }

        fb_reserve(fb, AX25_MAX_HDR_LEN);
        fb->data_ptr = tlm_payload(fb, &aprs0);
        fb->mac_hdr = ax25_sdu(fb, &ax25);

        /* APRS Beacon */
        ax5043TX(cfg->devp, cfg->profile, fb->data, fb->len, fb->len, NULL, NULL, false);
        fb_free(fb);

        chThdSleepMilliseconds(OD_TX_Control.beaconInterval);
    }

    chThdExit(MSG_OK);
}
