#include "hal.h"
#include "max7310.h"
#include "opd.h"

#define OPD_ADDR_MAX        (MAX7310_MAX_ADDR + 1)

static struct {
    MAX7310Driver dev;
    MAX7310Config config;
    bool valid;
} opd_dev[OPD_ADDR_MAX];

static const I2CConfig i2cconfig = {
    OPMODE_I2C,
    100000,
    STD_DUTY_CYCLE,
};

static MAX7310Config defconfig = {
    &I2CD1,
    &i2cconfig,
    0x00,
    OPD_ODR_VAL,
    OPD_POL_VAL,
    OPD_MODE_VAL,
    MAX7310_TIMEOUT_ENABLED
};

void opd_init(void)
{
    for (i2caddr_t i = MAX7310_MIN_ADDR; i <= MAX7310_MAX_ADDR; i++) {
        max7310ObjectInit(&opd_dev[i].dev);
        opd_dev[i].config = defconfig;
        opd_dev[i].config.saddr = i;
        opd_dev[i].valid = false;
    }
}

void opd_start(void)
{
#ifdef LINE_OPD_ENABLE
    /* Enable the subsystem if the device has a control line */
    palClearLine(LINE_OPD_ENABLE);
    chThdSleepMilliseconds(10);
#endif /* LINE_OPD_ENABLE */

    /* Start the I2C driver */
    i2cStart(&I2CD1, &i2cconfig);
    /* Probe all devices on the bus */
    for (i2caddr_t i = MAX7310_MIN_ADDR; i <= MAX7310_MAX_ADDR; i++) {
        opd_probe(i);
    }
}

void opd_stop(void)
{
    /* Forcefully disable all devices */
    for (i2caddr_t i = MAX7310_MIN_ADDR; i <= MAX7310_MAX_ADDR; i++) {
        max7310Stop(&opd_dev[i].dev);
        opd_dev[i].valid = false;
    }
    /* Stop the I2C driver */
    i2cStop(&I2CD1);
#ifdef LINE_OPD_ENABLE
    /* Disable the subsystem if the device has a control line */
    palSetLine(LINE_OPD_ENABLE);
#endif /* LINE_OPD_ENABLE */
}

bool opd_probe(opd_addr_t addr)
{
    msg_t result;
    uint8_t temp;

    /* Probe the device */
    i2cAcquireBus(&I2CD1);
    result = i2cMasterReceiveTimeout(&I2CD1, addr, &temp, 1, TIME_MS2I(10));
    i2cReleaseBus(&I2CD1);
    if (result == MSG_OK) {
        /* If a device responded, set as valid and activate */
        opd_dev[addr].valid = true;
        max7310Start(&opd_dev[addr].dev, &opd_dev[addr].config);
    } else {
        /* If no response, ensure address is stopped and set as invalid */
        max7310Stop(&opd_dev[addr].dev);
        opd_dev[addr].valid = false;
    }

    /* Return the result of the probe */
    return opd_dev[addr].valid;
}

int opd_enable(opd_addr_t addr)
{
    uint8_t regval;

    /* Ensure device is valid */
    if (opd_dev[addr].valid != true)
        return -1;

    regval = max7310ReadRaw(&opd_dev[addr].dev, MAX7310_AD_ODR);
    regval |= MAX7310_PIN_MASK(OPD_CB_EN);
    max7310WriteRaw(&opd_dev[addr].dev, MAX7310_AD_ODR, regval);
    regval |= MAX7310_PIN_MASK(OPD_EN);
    max7310WriteRaw(&opd_dev[addr].dev, MAX7310_AD_ODR, regval);
    return 0;
}

int opd_disable(opd_addr_t addr)
{
    uint8_t regval;

    /* Ensure device is valid */
    if (opd_dev[addr].valid != true)
        return -1;

    regval = max7310ReadRaw(&opd_dev[addr].dev, MAX7310_AD_ODR);
    regval &= ~MAX7310_PIN_MASK(OPD_EN);
    max7310WriteRaw(&opd_dev[addr].dev, MAX7310_AD_ODR, regval);
    regval &= ~MAX7310_PIN_MASK(OPD_CB_EN);
    max7310WriteRaw(&opd_dev[addr].dev, MAX7310_AD_ODR, regval);
    return 0;
}

int opd_reset(opd_addr_t addr)
{
    uint8_t regval;

    /* Ensure device is valid */
    if (opd_dev[addr].valid != true)
        return -1;

    regval = max7310ReadRaw(&opd_dev[addr].dev, MAX7310_AD_ODR);
    regval |= MAX7310_PIN_MASK(OPD_CB_RESET);
    max7310WriteRaw(&opd_dev[addr].dev, MAX7310_AD_ODR, regval);
    chThdSleepMilliseconds(100);
    regval &= ~MAX7310_PIN_MASK(OPD_CB_RESET);
    max7310WriteRaw(&opd_dev[addr].dev, MAX7310_AD_ODR, regval);
    return 0;
}

int opd_status(opd_addr_t addr, opd_status_t *status)
{
    /* Ensure device is valid */
    if (opd_dev[addr].valid != true)
        return -1;

    status->input = max7310ReadRaw(&opd_dev[addr].dev, MAX7310_AD_INPUT);
    status->odr = max7310ReadRaw(&opd_dev[addr].dev, MAX7310_AD_ODR);
    status->pol = max7310ReadRaw(&opd_dev[addr].dev, MAX7310_AD_POL);
    status->mode = max7310ReadRaw(&opd_dev[addr].dev, MAX7310_AD_MODE);
    status->timeout = max7310ReadRaw(&opd_dev[addr].dev, MAX7310_AD_TIMEOUT);
    return 0;
}
