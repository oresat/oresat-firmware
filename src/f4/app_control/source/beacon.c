#include "beacon.h"
#include "comms.h"
#include "CANopen.h"
#include "OD.h"
#include "ax25.h"
#include "rtc.h"
#include "crc.h"
#include "fs.h"

/* TODO: Re-implement with OD interface */
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
    { .type = TLM_MSG, .msg = "{{z" },
    /* Telemetry Version */
    { .type = TLM_VAL, .len = 1, .val = 0 },
    /* C3 State */
    { .type = TLM_PTR, .len = 1, .ptr = &OD_RAM.x6000_C3_State },
    /* Uptime */
    { .type = TLM_PTR, .len = 4, .ptr = &OD_RAM.x7000_C3_Telemetry.uptime },
    /* RTC Time */
    { .type = TLM_PTR, .len = 4, .ptr = &unix_time },
    /* MCU Temperature */
    { .type = TLM_PTR, .len = 1, .ptr = &OD_RAM.x2022_MCU_Sensors.temperature },
    /* MCU VREFINT */
    { .type = TLM_PTR, .len = 1, .ptr = &OD_RAM.x2022_MCU_Sensors.VREFINT },
    /* VBUSP Voltage */
    { .type = TLM_PTR, .len = 1, .ptr = &OD_RAM.x2022_MCU_Sensors.VBAT },
    /* VBUSP Current */
    { .type = TLM_PTR, .len = 1, .ptr = &OD_RAM.x2022_MCU_Sensors.VBUSP_Current },
    /* WDT Timeouts */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_PERSIST_STATE.x6004_persistentState.powerCycles },
    /* eMMC Usage */
    { .type = TLM_PTR, .len = 1, .ptr = &OD_RAM.x7000_C3_Telemetry.eMMC_Usage },
    /* L-Band RX Bytes */
    { .type = TLM_PTR, .len = 4, .ptr = &OD_PERSIST_STATE.x6004_persistentState.LBandRX_Bytes },
    /* L-Band Valid Packets */
    { .type = TLM_PTR, .len = 4, .ptr = &OD_PERSIST_STATE.x6004_persistentState.LBandRX_Packets },
    /* L-Band Last RSSI */
    { .type = TLM_PTR, .len = 1, .ptr = &lband.rssi },
    /* L-Band PLL Lock TODO */
    { .type = TLM_VAL, .len = 1, .val = 0 },
    /* UHF Temperature */
    { .type = TLM_PTR, .len = 1, .ptr = &OD_RAM.x7000_C3_Telemetry.UHF_Temperature },
    /* UHF Forward Power */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7000_C3_Telemetry.UHF_FWD_Pwr },
    /* UHF Reverse Power */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7000_C3_Telemetry.UHF_REV_Pwr },
    /* UHF RX Bytes */
    { .type = TLM_PTR, .len = 4, .ptr = &OD_PERSIST_STATE.x6004_persistentState.UHF_RX_Bytes },
    /* UHF Valid Packets */
    { .type = TLM_PTR, .len = 4, .ptr = &OD_PERSIST_STATE.x6004_persistentState.UHF_RX_Packets },
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
    { .type = TLM_PTR, .len = 1, .ptr = &OD_RAM.x7000_C3_Telemetry.OPD_Current },
    /* OPD State TODO */
    { .type = TLM_VAL, .len = 1, .val = 0 },
    /* Battery 0 Pack 1 VBatt */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7001_battery.VBattBP1 },
    /* Battery 0 Pack 1 VCell */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7001_battery.VCellBP1 },
    /* Battery 0 Pack 1 VCell Max */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7001_battery.VCellMaxBP1 },
    /* Battery 0 Pack 1 VCell Min */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7001_battery.VCellMinBP1 },
    /* Battery 0 Pack 1 VCell 1 */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7001_battery.VCell1_BP1 },
    /* Battery 0 Pack 1 VCell 2 */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7001_battery.VCell2_BP1 },
    /* Battery 0 Pack 1 VCell Avg */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7001_battery.VCellAvgBP1 },
    /* Battery 0 Pack 1 Temperature */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7001_battery.temperatureBP1 },
    /* Battery 0 Pack 1 Temperature Avg */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7001_battery.temperatureAvgBP1 },
    /* Battery 0 Pack 1 Temperature Max */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7001_battery.temperatureMaxBP1 },
    /* Battery 0 Pack 1 Temperature Min */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7001_battery.temperatureMinBP1 },
    /* Battery 0 Pack 1 Current */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7001_battery.currentBP1 },
    /* Battery 0 Pack 1 Current Avg */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7001_battery.currentAvgBP1 },
    /* Battery 0 Pack 1 Current Max */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7001_battery.currentMaxBP1 },
    /* Battery 0 Pack 1 Current Min */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7001_battery.currentMinBP1 },
    /* Battery 0 Pack 1 State */
    { .type = TLM_PTR, .len = 1, .ptr = &OD_RAM.x7001_battery.stateBP1 },
    /* Battery 0 Pack 1 Reported State Of Charge */
    { .type = TLM_PTR, .len = 1, .ptr = &OD_RAM.x7001_battery.reportedStateOfChargeBP1 },
    /* Battery 0 Pack 1 Full Capacity */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7001_battery.fullCapacityBP1 },
    /* Battery 0 Pack 1 Reported Capacity */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7001_battery.reportedCapacityBP1 },
    /* Battery 0 Pack 2 VBatt */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7001_battery.VBattBP2 },
    /* Battery 0 Pack 2 VCell */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7001_battery.VCellBP2 },
    /* Battery 0 Pack 2 VCell Max */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7001_battery.VCellMaxBP2 },
    /* Battery 0 Pack 2 VCell Min */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7001_battery.VCellMinBP2 },
    /* Battery 0 Pack 2 VCell 1 */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7001_battery.VCell1_BP2 },
    /* Battery 0 Pack 2 VCell 2 */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7001_battery.VCell2_BP2 },
    /* Battery 0 Pack 2 VCell Avg */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7001_battery.VCellAvgBP2 },
    /* Battery 0 Pack 2 Temperature */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7001_battery.temperatureBP2 },
    /* Battery 0 Pack 2 Temperature Avg */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7001_battery.temperatureAvgBP2 },
    /* Battery 0 Pack 2 Temperature Max */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7001_battery.temperatureMaxBP2 },
    /* Battery 0 Pack 2 Temperature Min */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7001_battery.temperatureMinBP2 },
    /* Battery 0 Pack 2 Current */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7001_battery.currentBP2 },
    /* Battery 0 Pack 2 Current Avg */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7001_battery.currentAvgBP2 },
    /* Battery 0 Pack 2 Current Max */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7001_battery.currentMaxBP2 },
    /* Battery 0 Pack 2 Current Min */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7001_battery.currentMinBP2 },
    /* Battery 0 Pack 2 State */
    { .type = TLM_PTR, .len = 1, .ptr = &OD_RAM.x7001_battery.stateBP2 },
    /* Battery 0 Pack 2 Reported State Of Charge */
    { .type = TLM_PTR, .len = 1, .ptr = &OD_RAM.x7001_battery.reportedStateOfChargeBP2 },
    /* Battery 0 Pack 2 Full Capacity */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7001_battery.fullCapacityBP2 },
    /* Battery 0 Pack 2 Reported Capacity */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7001_battery.reportedCapacityBP2 },
    /* Solar 0 Voltage Avg */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7003_solarPanel.voltageAvg },
    /* Solar 0 Current Avg */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7003_solarPanel.currentAvg },
    /* Solar 0 Power Avg */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7003_solarPanel.powerAvg },
    /* Solar 0 Voltage Max */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7003_solarPanel.voltageMax },
    /* Solar 0 Current Max */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7003_solarPanel.currentMax },
    /* Solar 0 Power Max */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7003_solarPanel.powerMax },
    /* Solar 0 Energy */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7003_solarPanel.energy },
    /* Solar 1 Voltage Avg */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7004_solarPanel.voltageAvg },
    /* Solar 1 Current Avg */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7004_solarPanel.currentAvg },
    /* Solar 1 Power Avg */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7004_solarPanel.powerAvg },
    /* Solar 1 Voltage Max */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7004_solarPanel.voltageMax },
    /* Solar 1 Current Max */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7004_solarPanel.currentMax },
    /* Solar 1 Power Max */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7004_solarPanel.powerMax },
    /* Solar 1 Energy */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7004_solarPanel.energy },
    /* Solar 2 Voltage Avg */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7005_solarPanel.voltageAvg },
    /* Solar 2 Current Avg */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7005_solarPanel.currentAvg },
    /* Solar 2 Power Avg */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7005_solarPanel.powerAvg },
    /* Solar 2 Voltage Max */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7005_solarPanel.voltageMax },
    /* Solar 2 Current Max */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7005_solarPanel.currentMax },
    /* Solar 2 Power Max */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7005_solarPanel.powerMax },
    /* Solar 2 Energy */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7005_solarPanel.energy },
    /* Solar 3 Voltage Avg */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7006_solarPanel.voltageAvg },
    /* Solar 3 Current Avg */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7006_solarPanel.currentAvg },
    /* Solar 3 Power Avg */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7006_solarPanel.powerAvg },
    /* Solar 3 Voltage Max */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7006_solarPanel.voltageMax },
    /* Solar 3 Current Max */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7006_solarPanel.currentMax },
    /* Solar 3 Power Max */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7006_solarPanel.powerMax },
    /* Solar 3 Energy */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x7006_solarPanel.energy },
    /* Star Tracker FS Usage */
    { .type = TLM_PTR, .len = 1, .ptr = &OD_RAM.x700B_starTracker.rootPartitionPercent },
    /* Star Tracker Readable Files TODO */
    { .type = TLM_VAL, .len = 1, .val = 0 },
    /* Star Tracker Updater Status */
    { .type = TLM_PTR, .len = 1, .ptr = &OD_RAM.x700B_starTracker.updaterStatus },
    /* Star Tracker Updates Cached TODO */
    { .type = TLM_VAL, .len = 1, .val = 0 },
    /* Star Tracker Right Ascension */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x700B_starTracker.rightAscension },
    /* Star Tracker Declination */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x700B_starTracker.declination },
    /* Star Tracker Roll */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x700B_starTracker.roll },
    /* Star Tracker Timestamp TODO */
    { .type = TLM_VAL, .len = 4, .val = 0 },
    /* GPS FS Usage */
    { .type = TLM_PTR, .len = 1, .ptr = &OD_RAM.x700D_GPS.rootPartitionPercent },
    /* GPS Readable Files TODO */
    { .type = TLM_VAL, .len = 1, .val = 0 },
    /* GPS Updater Status */
    { .type = TLM_PTR, .len = 1, .ptr = &OD_RAM.x700D_GPS.updaterStatus },
    /* GPS Updates Cached TODO */
    { .type = TLM_VAL, .len = 1, .val = 0 },
    /* GPS Status */
    { .type = TLM_PTR, .len = 1, .ptr = &OD_RAM.x700D_GPS.GPS_Status },
    /* GPS Number of Satellites Locked */
    { .type = TLM_PTR, .len = 1, .ptr = &OD_RAM.x700D_GPS.satellitesLocked },
    /* GPS X Pos */
    { .type = TLM_PTR, .len = 4, .ptr = &OD_RAM.x700D_GPS.positionX },
    /* GPS Y Pos */
    { .type = TLM_PTR, .len = 4, .ptr = &OD_RAM.x700D_GPS.positionY },
    /* GPS Z Pos */
    { .type = TLM_PTR, .len = 4, .ptr = &OD_RAM.x700D_GPS.positionZ },
    /* GPS X Velocity */
    { .type = TLM_PTR, .len = 4, .ptr = &OD_RAM.x700D_GPS.velocityX },
    /* GPS Y Velocity */
    { .type = TLM_PTR, .len = 4, .ptr = &OD_RAM.x700D_GPS.velocityY },
    /* GPS Z Velocity */
    { .type = TLM_PTR, .len = 4, .ptr = &OD_RAM.x700D_GPS.velocityZ },
    /* GPS Timestamp TODO */
    { .type = TLM_VAL, .len = 4, .val = 0 },
    /* ACS Roll */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x700E_ACS.gyroRoll },
    /* ACS Pitch */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x700E_ACS.gyroPitch },
    /* ACS Yaw */
    { .type = TLM_PTR, .len = 2, .ptr = &OD_RAM.x700E_ACS.gyroYaw },
    /* ACS IMU Temperature */
    { .type = TLM_PTR, .len = 1, .ptr = &OD_RAM.x700E_ACS.IMUTemp },
    /* DxWiFi FS Usage */
    { .type = TLM_PTR, .len = 1, .ptr = &OD_RAM.x7013_dxWiFi.rootPartitionPercent },
    /* DxWiFi Readable Files TODO */
    { .type = TLM_VAL, .len = 1, .val = 0 },
    /* DxWiFi Updater Status */
    { .type = TLM_PTR, .len = 1, .ptr = &OD_RAM.x7013_dxWiFi.updaterStatus },
    /* DxWiFi Updates Cached TODO */
    { .type = TLM_VAL, .len = 1, .val = 0 },
    /* DxWiFi Transmitting */
    { .type = TLM_PTR, .len = 1, .ptr = &OD_RAM.x7013_dxWiFi.transmitting },
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
        fb = fb_alloc(AX25_MAX_FRAME_LEN, &tx_fifo);
    }

    OD_RAM.x7000_C3_Telemetry.uptime = TIME_I2S(chVTGetSystemTime());
    unix_time = rtcGetTimeUnix(NULL);
    OD_RAM.x7000_C3_Telemetry.eMMC_Usage = fs_usage(&FSD1);

    fb_reserve(fb, AX25_MAX_HDR_LEN);
    fb->data_ptr = tlm_payload(fb, &aprs0);
    fb->mac_hdr = ax25_sdu(fb, &ax25);

    /* APRS Beacon */
    ax5043TX(cfg->devp, cfg->profile, fb->data, fb->len, fb->len, NULL, NULL, false);
    fb_free(fb, &tx_fifo);
    fb = NULL;
}

THD_FUNCTION(beacon, arg)
{
    const radio_cfg_t *cfg = arg;

    while (!chThdShouldTerminateX()) {
        beacon_send(cfg);
        chThdSleepMilliseconds(OD_PERSIST_APP.x6003_TX_Control.beaconInterval);
    }

    chThdExit(MSG_OK);
}
