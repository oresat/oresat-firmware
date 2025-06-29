#include "ch.h"
#include "hal.h"

#include "oresat.h"
#include "batt.h"

#ifdef DEBUG_PRINT
#include "chprintf.h"
#define DEBUG_SD (BaseSequentialStream *) &SD2
#define dbgprintf(str, ...) chprintf(DEBUG_SD, str, ##__VA_ARGS__)
#else
#define dbgprintf(str, ...)
#endif

static worker_t battery_worker;
static thread_descriptor_t battery_worker_desc = {
    .name = "Battery management thread",
    .wbase = THD_WORKING_AREA_BASE(batt_wa),
    .wend = THD_WORKING_AREA_END(batt_wa),
    .prio = NORMALPRIO,
    .funcp = batt,
    .arg = NULL
};

static oresat_config_t oresat_conf = {
    .cand = &CAND1,
    .node_id = ORESAT_DEFAULT_ID,
    .bitrate = ORESAT_DEFAULT_BITRATE,
};

static const I2CConfig i2cconfig_1 = {
    STM32_TIMINGR_PRESC(0xBU) |
    STM32_TIMINGR_SCLDEL(0x4U) | STM32_TIMINGR_SDADEL(0x2U) |
    STM32_TIMINGR_SCLH(0xFU)  | STM32_TIMINGR_SCLL(0x13U),
    0,
    0
};

//TODO timing for i2c2 is different the i2c1. Scope the lines and match them up.
static const I2CConfig i2cconfig_2 = {
    STM32_TIMINGR_PRESC(0xFU) |
    STM32_TIMINGR_SCLDEL(0x4U) | STM32_TIMINGR_SDADEL(0x2U) |
    STM32_TIMINGR_SCLH(0xFU)  | STM32_TIMINGR_SCLL(0x13U),
    0,
    0
};

int main(void) {
    oresat_init(&oresat_conf);
#ifdef DEBUG_PRINT
    sdStart(&SD2, NULL);
#endif
    dbgprintf("\r\nStarting battery Node ID: 0x%x\r\n", oresat_conf.node_id);

    i2cStart(&I2CD1, &i2cconfig_1);
    i2cStart(&I2CD2, &i2cconfig_2);
    reg_worker(&battery_worker, &battery_worker_desc, true, true);

    oresat_start();
    return 0;
}

