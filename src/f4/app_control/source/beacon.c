#include "beacon.h"
#include "comms.h"
#include "CANopen.h"
#include "ax25.h"
#include "rtc.h"
#include "fs.h"

static const ax25_link_t ax25 = {
    .dest = "SPACE ",
    .dest_ssid = 0,
    .src = "KJ7SAT",
    .src_ssid = 0,
    .control = AX25_CTRL_UFRAME | _VAL2FLD(AX25_CTRL_U_FLD, AX25_UFRAME_UI),
    .sid = AX25_PID_NONE,
};

static time_t unix_time;

static const tlm_item_t tlm_aprs0[] = {
    /* User-Defined APRS Start */
    { .type = TLM_MSG, .msg = "{" },
    /* Telemetry Version */
    { .type = TLM_VAL, .len = 1, .val = 0 },
    /* C3 State */
    { .type = TLM_PTR, .len = 1, .ptr = &OD_C3State },
    /* Uptime */
    { .type = TLM_PTR, .len = 4, .ptr = &OD_C3Telemetry.uptime },
    /* RTC Time */
    { .type = TLM_PTR, .len = 4, .ptr = &unix_time },
    /* MCU Temperature */
    { .type = TLM_PTR, .len = 1, .ptr = &OD_MCU_Sensors.temperature },
    /* MCU VREFINT */
    { .type = TLM_PTR, .len = 1, .ptr = &OD_MCU_Sensors.VREFINT },
    /* VBUSP Voltage */
    { .type = TLM_PTR, .len = 1, .ptr = &OD_MCU_Sensors.VBAT },
    /* VBUSP Current */
    { .type = TLM_PTR, .len = 1, .ptr = &OD_MCU_Sensors.VBUSP_Current },
    /* WDT Timeouts */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_persistentState.powerCycles },
    /* eMMC Usage */
    { .type = TLM_PTR, .len = 1, .ptr = &OD_C3Telemetry.EMMC_Usage },
    /* L-Band RX Bytes */
    { .type = TLM_PTR, .len = 1, .ptr = &OD_persistentState.LBandRX_Bytes },
    /* L-Band Valid Packets */
    { .type = TLM_PTR, .len = 1, .ptr = &OD_persistentState.LBandRX_Packets },
    /* L-Band Last RSSI */
    { .type = TLM_PTR, .len = 1, .ptr = &lband.rssi },
    /* L-Band PLL Lock TODO */
    { .type = TLM_VAL, .len = 1, .val = 0 },
    /* UHF Temperature */
    { .type = TLM_PTR, .len = 1, .ptr = &OD_C3Telemetry.UHF_Temperature },
    /* UHF Forward Power */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_C3Telemetry.UHF_FWD_Pwr },
    /* UHF Reverse Power */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_C3Telemetry.UHF_REV_Pwr },
    /* UHF RX Bytes */
    { .type = TLM_PTR, .len = 1, .ptr = &OD_persistentState.UHF_RX_Bytes },
    /* UHF Valid Packets */
    { .type = TLM_PTR, .len = 1, .ptr = &OD_persistentState.UHF_RX_Packets },
    /* UHF Last RSSI */
    { .type = TLM_PTR, .len = 1, .ptr = &uhf.rssi },
    /* UHF PLL Lock TODO */
    { .type = TLM_VAL, .len = 1, .val = 0 },
    /* User-Defined APRS End */
    { .type = TLM_MSG, .msg = "}" }
};

static const tlm_pkt_t aprs0 = {
    .item_cnt = sizeof(tlm_aprs0) / sizeof(tlm_item_t),
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
            len = strlen(item->msg);
            memcpy(fb_put(fb, len), item->msg, len);
            break;
        case TLM_VAL:
            len = item->len;
            memcpy(fb_put(fb, len), &item->val, len);
            break;
        case TLM_PTR:
            len = item->len;
            memcpy(fb_put(fb, len), item->ptr, len);
            break;
        case TLM_OD:
            od_entry = CO_OD_find(CO->SDO[0], item->index);
            if (od_entry != 0xFFFF) {
                len = CO_OD_getLength(CO->SDO[0], od_entry, item->subindex);
                data = CO_OD_getDataPointer(CO->SDO[0], od_entry, item->subindex);
                if (len == item->len && data != NULL) {
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

void beacon_send(const radio_cfg_t *cfg)
{
    fb_t *fb = NULL;
    while (fb == NULL) {
        fb = fb_alloc(AX25_MAX_FRAME_LEN);
    }

    OD_C3Telemetry.uptime = TIME_I2S(chVTGetSystemTime());
    unix_time = rtcGetTimeUnix(NULL);
    OD_C3Telemetry.EMMC_Usage = fs_usage(&FSD1);

    fb_reserve(fb, AX25_MAX_HDR_LEN);
    fb->data_ptr = tlm_payload(fb, &aprs0);
    fb->mac_hdr = ax25_sdu(fb, &ax25);

    /* APRS Beacon */
    ax5043TX(cfg->devp, cfg->profile, fb->data, fb->len, fb->len, NULL, NULL, false);
    fb_free(fb);
    fb = NULL;
}

THD_FUNCTION(beacon, arg)
{
    const radio_cfg_t *cfg = arg;

    while (!chThdShouldTerminateX()) {
        beacon_send(cfg);
        chThdSleepMilliseconds(OD_TX_Control.beaconInterval);
    }

    chThdExit(MSG_OK);
}
