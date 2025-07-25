#include "ch.h"
#include "hal.h"
#include "CANopen.h"
#include "OD.h"

#include <sys/param.h>

#ifdef DEBUG_PRINT
#include "chprintf.h"
#define DEBUG_SD (BaseSequentialStream *) &SD2
#define dbgprintf(str, ...) chprintf(DEBUG_SD, str, ##__VA_ARGS__)
#else
#define dbgprintf(str, ...)
#endif

#define ARRAY_SIZE(n) (sizeof(n)/sizeof(n[0]))

// The i2c driver returns two separate kinds of errors, a msg_t or a i2cflags_t
// The only unique error from msg_t is MSG_TIMEOUT though so if we make a new
// i2cflags_t value that represents that we can just have one error type.
#define I2C_DRIVER_TIMEOUT 0x80

i2cflags_t transmit(I2CDriver * i2c, i2caddr_t addr,
    const uint8_t *txbuf, size_t txbytes,
    uint8_t *rxbuf, size_t rxbytes) {

    i2cflags_t errs = I2C_NO_ERROR;
    i2cAcquireBus(i2c);
    switch(i2cMasterTransmitTimeout(i2c, addr, txbuf, txbytes, rxbuf, rxbytes,
        TIME_MS2I(50))) {
    case MSG_RESET:
        errs = i2cGetErrors(i2c);
        break;
    case MSG_TIMEOUT:
        errs = I2C_DRIVER_TIMEOUT;
        // On TIMEOUT the i2c driver goes into LOCKED and needs to be restarted
        i2cStart(i2c, i2c->config);
        break;
    case MSG_OK:
        break;
    }
    i2cReleaseBus(i2c);
    return errs;
}


// I2C addresses
#define CELL_1  (0x48)
#define CELL_2  (0x4A)

// Register addresses
static const uint8_t TEMPERATURE   = 0x00;
static const uint8_t CONFIGURATION = 0x01;

// Configure register bits
#define SD     (1 << 0)
#define TM     (1 << 1)
#define POL    (1 << 2)
#define FQ_1   (0 << 3)
#define FQ_2   (1 << 3)
#define FQ_4   (2 << 3)
#define FQ_6   (3 << 3)
#define RES_09 (0 << 5)
#define RES_10 (1 << 5)
#define RES_11 (2 << 5)
#define RES_12 (3 << 5)
#define OS     (1 << 7)


msg_t OneShot(I2CDriver * i2c, i2caddr_t addr) {
    uint8_t buf[2] = {CONFIGURATION, RES_09 | SD | OS};
    return transmit(i2c, addr, buf, ARRAY_SIZE(buf), NULL, 0);
}

// The OD Records for cells 1 and 2 are the same type but our OD generator
// doesn't yet know how to indicate that. This union is a quick hack to get the
// types to work out.
typedef union {
    typeof(OD_RAM.x4001_cell_1) * cell;
    typeof(OD_RAM.x4001_cell_1) * cell1;
    typeof(OD_RAM.x4002_cell_2) * cell2;
} CellRecord;

i2cflags_t ReadTemperature(I2CDriver * i2c, i2caddr_t addr, CellRecord record) {
    // The temperature register is two bytes but we only have one byte assigned
    // in the OD. Conveniently the high byte corresponds to signed degrees C
    // which is also what the OD wants, so we just take the high byte and stuff
    // it in the OD.
    int8_t buf = 0;
    i2cflags_t errs = transmit(i2c, addr, &TEMPERATURE, sizeof(TEMPERATURE),
        (uint8_t*)&buf, sizeof(buf));

    // dbgprintf("Cell %X: %dC\r\n", addr, buf);

    if(!errs) {
        record.cell->temperature = buf;
        record.cell->temperature_max = MAX(buf, record.cell->temperature_max);
        record.cell->temperature_min = MIN(buf, record.cell->temperature_min);
    }
    return errs;
}


THD_WORKING_AREA(sensor_mon_wa, 0x200);
THD_FUNCTION(sensor_mon, arg) {
    I2CDriver *i2c = arg;
    osalDbgCheck(i2c->state > I2C_STOP);

    dbgprintf("Starting TMP101\r\n");

    CellRecord record1 = {.cell1 = &OD_RAM.x4001_cell_1};
    CellRecord record2 = {.cell2 = &OD_RAM.x4002_cell_2};

    // FIXME: remove once oresat-configs is updated
    record1.cell->temperature_max = INT8_MIN;
    record1.cell->temperature_min = INT8_MAX;

    record2.cell->temperature_max = INT8_MIN;
    record2.cell->temperature_min = INT8_MAX;

    while (!chThdShouldTerminateX()) {
        systime_t start = chVTGetSystemTime();
        i2cflags_t errs = I2C_NO_ERROR;

        if((errs = OneShot(i2c, CELL_1))) {
            // FIXME: CO_errorReport(CO->em, CO_EM_GENERIC_ERROR,
            //  CO_EMC_COMMUNICATION, SOLAR_OD_ERROR_TYPE_TMP101_1_COMM_ERROR);
            dbgprintf("Failed to read cell 1 temperature: %d\r\n", errs);
        }
        if((errs = OneShot(i2c, CELL_2))) {
            // FIXME: CO_errorReport(CO->em, CO_EM_GENERIC_ERROR,
            //  CO_EMC_COMMUNICATION, SOLAR_OD_ERROR_TYPE_TMP101_1_COMM_ERROR);
            dbgprintf("Failed to read cell 1 temperature: %d\r\n", errs);
        }

        // 9 bit conversion takes a max of 75ms, see datasheet section 6.5
        // There's no way to get an interrupt from the chip
        chThdSleepUntil(start + TIME_MS2I(75));

        if((errs = ReadTemperature(i2c, CELL_1, record1))) {
            // FIXME: CO_errorReport(CO->em, CO_EM_GENERIC_ERROR,
            //  CO_EMC_COMMUNICATION, SOLAR_OD_ERROR_TYPE_TMP101_1_COMM_ERROR);
            dbgprintf("Failed to read cell 1 temperature: %d\r\n", errs);
        }
        if((errs = ReadTemperature(i2c, CELL_2, record2))) {
            // FIXME: CO_errorReport(CO->em, CO_EM_GENERIC_ERROR,
            //  CO_EMC_COMMUNICATION, SOLAR_OD_ERROR_TYPE_TMP101_2_COMM_ERROR);
            dbgprintf("Failed to read cell 2 temperature: %d\r\n", errs);
        }

        chThdSleepUntil(start + TIME_MS2I(
            OD_RAM.x1803_tpdo_4_communication_parameters.event_timer));
    }
    chThdExit(MSG_OK);
}
