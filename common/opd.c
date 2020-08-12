#include "hal.h"
#include "max7310.h"
#include "opd.h"

#define OPD_ADDR_MAX        (MAX7310_MAX_ADDR + 1)
#define OPD_I2C_TRIES       3

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

/**
 * OPD Control Functions
 */

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

bool opd_probe(uint8_t addr)
{
    msg_t result;
    uint8_t temp;

    /* Probe the device */
    i2cAcquireBus(&I2CD1);
    i2cStart(&I2CD1, &i2cconfig);
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

int opd_enable(uint8_t addr)
{
    /* Ensure device is valid */
    if (opd_dev[addr].valid != true)
        return -1;

    max7310SetPin(&opd_dev[addr].dev, OPD_EN);
    return 0;
}

int opd_disable(uint8_t addr)
{
    /* Ensure device is valid */
    if (opd_dev[addr].valid != true)
        return -1;

    max7310ClearPin(&opd_dev[addr].dev, OPD_EN);
    return 0;
}

int opd_reset(uint8_t addr)
{
    /* Ensure device is valid */
    if (opd_dev[addr].valid != true)
        return -1;

    max7310SetPin(&opd_dev[addr].dev, OPD_CB_RESET);
    chThdSleepMilliseconds(100);
    max7310ClearPin(&opd_dev[addr].dev, OPD_CB_RESET);
    return 0;
}

int opd_status(uint8_t addr, opd_status_t *status)
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

/**
 * I2C over OPD support functions
 */
void opd_i2c_start(MAX7310Driver *devp)
{
    uint8_t reg;

    reg = max7310ReadRaw(devp, MAX7310_AD_MODE);
    reg &= ~MAX7310_PIN_MASK(OPD_SDA);
    max7310WriteRaw(devp, MAX7310_AD_MODE, reg);
    reg &= ~MAX7310_PIN_MASK(OPD_SCL);
    max7310WriteRaw(devp, MAX7310_AD_MODE, reg);
}

void opd_i2c_stop(MAX7310Driver *devp)
{
    uint8_t reg;

    reg = max7310ReadRaw(devp, MAX7310_AD_MODE);
    reg |= MAX7310_PIN_MASK(OPD_SCL);
    max7310WriteRaw(devp, MAX7310_AD_MODE, reg);
    reg |= MAX7310_PIN_MASK(OPD_SDA);
    max7310WriteRaw(devp, MAX7310_AD_MODE, reg);
}

void opd_i2c_transmit(uint8_t addr, uint8_t *txbuf, size_t txsize, uint8_t *rxbuf, size_t rxsize)
{
    MAX7310Driver *devp;
    uint8_t tries;
    uint8_t reg;

    if (opd_dev[addr].valid != true)
        return;

    devp = &opd_dev[addr].dev;

    /* Assert start condition on I2C */
    opd_i2c_start(devp);

    /* Transmit all bytes */
    for (size_t i = 0; i < txsize; i++) {
        uint8_t byte = txbuf[i];

        /* Transmit 8 bits per byte */
        for (int j = 0; j < 8; j++) {
            reg = max7310ReadRaw(devp, MAX7310_AD_MODE);

            /* Set SDA based on MSB of byte */
            reg = (reg & ~MAX7310_PIN_MASK(OPD_SDA)) | ((byte & 0x8) ? MAX7310_PIN_MASK(OPD_SDA) : 0);
            max7310WriteRaw(devp, MAX7310_AD_MODE, reg);

            /* Cycle SCL */
            reg |= MAX7310_PIN_MASK(OPD_SCL);
            max7310WriteRaw(devp, MAX7310_AD_MODE, reg);
            reg &= ~MAX7310_PIN_MASK(OPD_SCL);
            max7310WriteRaw(devp, MAX7310_AD_MODE, reg);

            /* Shift next bit into MSB */
            byte <<= 1;
        }

        /* Wait for ACK after all bits sent */
        tries = OPD_I2C_TRIES;
        reg |= MAX7310_PIN_MASK(OPD_SDA);
        max7310WriteRaw(devp, MAX7310_AD_MODE, reg);
        reg |= MAX7310_PIN_MASK(OPD_SCL);
        max7310WriteRaw(devp, MAX7310_AD_MODE, reg);
        while (!(max7310ReadRaw(devp, MAX7310_AD_INPUT) & MAX7310_PIN_MASK(OPD_SDA)) && tries)
            tries--;
        reg &= ~MAX7310_PIN_MASK(OPD_SCL);
        max7310WriteRaw(devp, MAX7310_AD_MODE, reg);
        if (tries == 0)
            goto opd_i2c_fail;
    }

    for (size_t i = 0; i < rxsize; i++) {
        uint8_t byte = 0;

        for (int j = 0; j < 8; j++) {

            /* Cycle SCL while reading pin */
            reg |= MAX7310_PIN_MASK(OPD_SCL);
            max7310WriteRaw(devp, MAX7310_AD_MODE, reg);
            byte |= !!(max7310ReadRaw(devp, MAX7310_AD_INPUT) & MAX7310_PIN_MASK(OPD_SDA));
            reg &= ~MAX7310_PIN_MASK(OPD_SCL);
            max7310WriteRaw(devp, MAX7310_AD_MODE, reg);
            byte <<= 1;
        }

        reg |= MAX7310_PIN_MASK(OPD_SCL);
        max7310WriteRaw(devp, MAX7310_AD_MODE, reg);
        reg &= ~MAX7310_PIN_MASK(OPD_SDA);
        max7310WriteRaw(devp, MAX7310_AD_MODE, reg);
        reg &= ~MAX7310_PIN_MASK(OPD_SCL);
        max7310WriteRaw(devp, MAX7310_AD_MODE, reg);
        reg |= MAX7310_PIN_MASK(OPD_SDA);
        max7310WriteRaw(devp, MAX7310_AD_MODE, reg);

        rxbuf[i] = byte;
    }

opd_i2c_fail:
    opd_i2c_stop(devp);
    return;
}

int opd_boot(uint8_t addr)
{
    MAX7310Driver *devp;
    uint8_t txbuf[10];
    uint8_t rxbuf[10];
    int retval;

    if (opd_dev[addr].valid != true)
        return -1;
    devp = &opd_dev[addr].dev;

    max7310ClearPin(devp, OPD_EN);
    max7310SetPin(devp, OPD_BOOT0);
    max7310SetPin(devp, OPD_EN);

    txbuf[0] = 0x82U;
    txbuf[1] = 0x01U;
    txbuf[2] = 0xFEU;
    opd_i2c_transmit(addr, txbuf, 3, NULL, 0);

    txbuf[0] = 0x83U;
    opd_i2c_transmit(addr, txbuf, 1, rxbuf, 1);
    if (rxbuf[0] != 0x79)
        return -2;

    opd_i2c_transmit(addr, txbuf, 1, rxbuf, 1);
    retval = rxbuf[0];

    opd_i2c_transmit(addr, txbuf, 1, rxbuf, 1);
    if (rxbuf[0] != 0x79)
        return -2;

    max7310ClearPin(devp, OPD_BOOT0);

    return retval;
}
