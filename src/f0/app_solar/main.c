#include "ch.h"
#include "chmtx.h"
#include "hal.h"

#include "CANopen.h"
#include "OD.h"
#include "oresat.h"
#include "solar.h"
#include "blink.h"

#ifdef DEBUG_PRINT
#include "chprintf.h"
#define DEBUG_SD (BaseSequentialStream *) &SD2
#define dbgprintf(str, ...) chprintf(DEBUG_SD, str, ##__VA_ARGS__)
#else
#define dbgprintf(str, ...)
#endif

static const I2CConfig i2cconfig = {
    STM32_TIMINGR_PRESC(0xBU) |
    STM32_TIMINGR_SCLDEL(0x4U) | STM32_TIMINGR_SDADEL(0x2U) |
    STM32_TIMINGR_SCLH(0xFU)  | STM32_TIMINGR_SCLL(0x13U),
    0,
    0
};

static worker_t blink_worker;
static thread_descriptor_t blink_desc = {
    .name = "Blink",
    .wbase = THD_WORKING_AREA_BASE(blink_wa),
    .wend = THD_WORKING_AREA_END(blink_wa),
    .prio = NORMALPRIO,
    .funcp = blink,
    .arg = NULL
};

static worker_t solar_worker;
static thread_descriptor_t solar_desc = {
    .name = "Solar MPPT",
    .wbase = THD_WORKING_AREA_BASE(solar_wa),
    .wend = THD_WORKING_AREA_END(solar_wa),
    .prio = NORMALPRIO,
    .funcp = solar,
};

static worker_t sensor_mon_worker;
static thread_descriptor_t sensor_mon_desc = {
    .name = "Sensor Monitor",
    .wbase = THD_WORKING_AREA_BASE(sensor_mon_wa),
    .wend = THD_WORKING_AREA_END(sensor_mon_wa),
    .prio = NORMALPRIO,
    .funcp = sensor_mon,
};

static oresat_config_t oresat_conf = {
    .cand = &CAND1,
    .node_id = ORESAT_DEFAULT_ID,
    .bitrate = ORESAT_DEFAULT_BITRATE,
};

int main(void) {
    oresat_init(&oresat_conf);

    // dbgprintf("Node ID: %X\r\n", oresat_conf.node_id);

    sdStart(&SD2, NULL);
    i2cStart(&I2CD2, &i2cconfig);

    struct SharedTempSample share = {};
    chMtxObjectInit(&share.guard);

    struct SolarArgs solar_desc_args = {
        .i2c = &I2CD2,
        .sample = &share,
    };

    struct SolarArgs sensor_mon_desc_args = {
        .i2c = &I2CD2,
        .sample = &share,
    };

    sensor_mon_desc.arg = &sensor_mon_desc_args;
    solar_desc.arg = &solar_desc_args;

    reg_worker(&blink_worker, &blink_desc, false, true);
    reg_worker(&solar_worker, &solar_desc, true, true);
    reg_worker(&sensor_mon_worker, &sensor_mon_desc, true, true);

    oresat_start();

    return 0;
}
