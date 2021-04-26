#include "beacon.h"
#include "comms.h"
#include "CANopen.h"
#include "ax25.h"
#include "rtc.h"
#include "crc.h"
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
    { .type = TLM_PTR, .len = 4, .ptr = &OD_persistentState.LBandRX_Bytes },
    /* L-Band Valid Packets */
    { .type = TLM_PTR, .len = 4, .ptr = &OD_persistentState.LBandRX_Packets },
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
    { .type = TLM_PTR, .len = 4, .ptr = &OD_persistentState.UHF_RX_Bytes },
    /* UHF Valid Packets */
    { .type = TLM_PTR, .len = 4, .ptr = &OD_persistentState.UHF_RX_Packets },
    /* UHF Last RSSI */
    { .type = TLM_PTR, .len = 1, .ptr = &uhf.rssi },
    /* UHF PLL Lock TODO */
    { .type = TLM_VAL, .len = 1, .val = 0 },
    /* Deployer TODO */
    { .type = TLM_VAL, .len = 1, .val = 0 },
    /* CAN1 Status TODO */
    { .type = TLM_VAL, .len = 1, .val = 0 },
    /* CAN2 Status TODO */
    { .type = TLM_VAL, .len = 1, .val = 0 },
    /* OPD Current */
    { .type = TLM_PTR, .len = 1, .ptr = &OD_C3Telemetry.OPD_Current },
    /* OPD State TODO */
    { .type = TLM_VAL, .len = 1, .val = 0 },
    /* Battery 0 Pack 1 VBatt */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_battery[0].VBattBP1 },
    /* Battery 0 Pack 1 VCell */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_battery[0].VCellBP1 },
    /* Battery 0 Pack 1 VCell Max */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_battery[0].VCellMaxBP1 },
    /* Battery 0 Pack 1 VCell Min */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_battery[0].VCellMinBP1 },
    /* Battery 0 Pack 1 VCell 1 */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_battery[0].VCell1BP1 },
    /* Battery 0 Pack 1 VCell 2 */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_battery[0].VCell2BP1 },
    /* Battery 0 Pack 1 VCell Avg */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_battery[0].VCellAvgBP1 },
    /* Battery 0 Pack 1 Temperature */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_battery[0].temperatureBP1 },
    /* Battery 0 Pack 1 Temperature Avg */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_battery[0].temperatureAvgBP1 },
    /* Battery 0 Pack 1 Temperature Max */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_battery[0].temperatureMaxBP1 },
    /* Battery 0 Pack 1 Temperature Min */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_battery[0].temperatureMinBP1 },
    /* Battery 0 Pack 1 Current */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_battery[0].currentBP1 },
    /* Battery 0 Pack 1 Current Avg */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_battery[0].currentAvgBP1 },
    /* Battery 0 Pack 1 Current Max */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_battery[0].currentMaxBP1 },
    /* Battery 0 Pack 1 Current Min */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_battery[0].currentMinBP1 },
    /* Battery 0 Pack 1 State */
    { .type = TLM_PTR, .len = 1, .ptr = &OD_battery[0].stateBP1 },
    /* Battery 0 Pack 1 Reported State Of Charge */
    { .type = TLM_PTR, .len = 1, .ptr = &OD_battery[0].reportedStateOfChargeBP1 },
    /* Battery 0 Pack 1 Full Capacity */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_battery[0].fullCapacityBP1 },
    /* Battery 0 Pack 1 Reported Capacity */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_battery[0].reportedCapacityBP1 },
    /* Battery 0 Pack 2 VBatt */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_battery[0].VBattBP2 },
    /* Battery 0 Pack 2 VCell */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_battery[0].VCellBP2 },
    /* Battery 0 Pack 2 VCell Max */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_battery[0].VCellMaxBP2 },
    /* Battery 0 Pack 2 VCell Min */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_battery[0].VCellMinBP2 },
    /* Battery 0 Pack 2 VCell 1 */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_battery[0].VCell1BP2 },
    /* Battery 0 Pack 2 VCell 2 */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_battery[0].VCell2BP2 },
    /* Battery 0 Pack 2 VCell Avg */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_battery[0].VCellAvgBP2 },
    /* Battery 0 Pack 2 Temperature */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_battery[0].temperatureBP2 },
    /* Battery 0 Pack 2 Temperature Avg */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_battery[0].temperatureAvgBP2 },
    /* Battery 0 Pack 2 Temperature Max */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_battery[0].temperatureMaxBP2 },
    /* Battery 0 Pack 2 Temperature Min */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_battery[0].temperatureMinBP2 },
    /* Battery 0 Pack 2 Current */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_battery[0].currentBP2 },
    /* Battery 0 Pack 2 Current Avg */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_battery[0].currentAvgBP2 },
    /* Battery 0 Pack 2 Current Max */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_battery[0].currentMaxBP2 },
    /* Battery 0 Pack 2 Current Min */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_battery[0].currentMinBP2 },
    /* Battery 0 Pack 2 State */
    { .type = TLM_PTR, .len = 1, .ptr = &OD_battery[0].stateBP2 },
    /* Battery 0 Pack 2 Reported State Of Charge */
    { .type = TLM_PTR, .len = 1, .ptr = &OD_battery[0].reportedStateOfChargeBP2 },
    /* Battery 0 Pack 2 Full Capacity */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_battery[0].fullCapacityBP2 },
    /* Battery 0 Pack 2 Reported Capacity */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_battery[0].reportedCapacityBP2 },
    /* Solar 0 Voltage Avg */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_solarPanel[0].voltageAvg },
    /* Solar 0 Current Avg */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_solarPanel[0].currentAvg },
    /* Solar 0 Power Avg */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_solarPanel[0].powerAvg },
    /* Solar 0 Voltage Max */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_solarPanel[0].voltageMax },
    /* Solar 0 Current Max */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_solarPanel[0].currentMax },
    /* Solar 0 Power Max */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_solarPanel[0].powerMax },
    /* Solar 0 Energy */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_solarPanel[0].energy },
    /* Solar 1 Voltage Avg */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_solarPanel[1].voltageAvg },
    /* Solar 1 Current Avg */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_solarPanel[1].currentAvg },
    /* Solar 1 Power Avg */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_solarPanel[1].powerAvg },
    /* Solar 1 Voltage Max */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_solarPanel[1].voltageMax },
    /* Solar 1 Current Max */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_solarPanel[1].currentMax },
    /* Solar 1 Power Max */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_solarPanel[1].powerMax },
    /* Solar 1 Energy */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_solarPanel[1].energy },
    /* Solar 2 Voltage Avg */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_solarPanel[2].voltageAvg },
    /* Solar 2 Current Avg */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_solarPanel[2].currentAvg },
    /* Solar 2 Power Avg */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_solarPanel[2].powerAvg },
    /* Solar 2 Voltage Max */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_solarPanel[2].voltageMax },
    /* Solar 2 Current Max */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_solarPanel[2].currentMax },
    /* Solar 2 Power Max */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_solarPanel[2].powerMax },
    /* Solar 2 Energy */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_solarPanel[2].energy },
    /* Solar 3 Voltage Avg */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_solarPanel[3].voltageAvg },
    /* Solar 3 Current Avg */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_solarPanel[3].currentAvg },
    /* Solar 3 Power Avg */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_solarPanel[3].powerAvg },
    /* Solar 3 Voltage Max */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_solarPanel[3].voltageMax },
    /* Solar 3 Current Max */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_solarPanel[3].currentMax },
    /* Solar 3 Power Max */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_solarPanel[3].powerMax },
    /* Solar 3 Energy */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_solarPanel[3].energy },
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
    size_t len, total = 0;;
    uint32_t crc;

    for (unsigned int i = 0; i < pkt->item_cnt; i++) {
        const tlm_item_t *item = &pkt->item[i];
        switch (item->type) {
        case TLM_MSG:
            len = strlen(item->msg);
            memcpy(fb_put(fb, len), item->msg, len);
            break;
        case TLM_PTR:
            len = item->len;
            memcpy(fb_put(fb, len), item->ptr, len);
            break;
        case TLM_VAL:
            len = item->len;
            memcpy(fb_put(fb, len), &item->val, len);
            break;
        default:
            return NULL;
        }
        total += len;
    }
    crc = crc32(tlm_start, total, 0);
    memcpy(fb_put(fb, sizeof(crc)), &crc, sizeof(crc));

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
