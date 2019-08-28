#include "hal.h"
#include "max7310.h"
#include "opd.h"

/* IO Pin Assignments */
#define OPD_SCL             0U
#define OPD_SDA             1U
#define OPD_FAULT           2U
#define OPD_EN              3U
#define OPD_CB_RESET        4U
#define OPD_BOOT0           5U
#define OPD_PULLUP          6U
#define OPD_LED             7U

/* IO Pin Configurations */
#define OPD_ODR_VAL        (MAX7310_PIN_ODR_HIGH(OPD_SCL)           |   \
                            MAX7310_PIN_ODR_HIGH(OPD_SDA)           |   \
                            MAX7310_PIN_ODR_LOW(OPD_FAULT)          |   \
                            MAX7310_PIN_ODR_LOW(OPD_EN)             |   \
                            MAX7310_PIN_ODR_LOW(OPD_CB_RESET)       |   \
                            MAX7310_PIN_ODR_LOW(OPD_BOOT0)          |   \
                            MAX7310_PIN_ODR_LOW(OPD_PULLUP)         |   \
                            MAX7310_PIN_ODR_HIGH(OPD_LED))
#define OPD_POL_VAL        (MAX7310_PIN_POL_INV(OPD_SCL)            |   \
                            MAX7310_PIN_POL_INV(OPD_SDA)            |   \
                            MAX7310_PIN_POL_INV(OPD_FAULT)          |   \
                            MAX7310_PIN_POL_STD(OPD_EN)             |   \
                            MAX7310_PIN_POL_STD(OPD_CB_RESET)       |   \
                            MAX7310_PIN_POL_STD(OPD_BOOT0)          |   \
                            MAX7310_PIN_POL_STD(OPD_PULLUP)         |   \
                            MAX7310_PIN_POL_STD(OPD_LED))
#define OPD_MODE_VAL       (MAX7310_PIN_MODE_OUTPUT(OPD_SCL)        |   \
                            MAX7310_PIN_MODE_OUTPUT(OPD_SDA)        |   \
                            MAX7310_PIN_MODE_INPUT(OPD_FAULT)       |   \
                            MAX7310_PIN_MODE_OUTPUT(OPD_EN)         |   \
                            MAX7310_PIN_MODE_OUTPUT(OPD_CB_RESET)   |   \
                            MAX7310_PIN_MODE_OUTPUT(OPD_BOOT0)      |   \
                            MAX7310_PIN_MODE_OUTPUT(OPD_PULLUP)     |   \
                            MAX7310_PIN_MODE_OUTPUT(OPD_LED))

static MAX7310Driver MAX7310D1;

static const I2CConfig i2cconfig = {
    OPMODE_I2C,
    400000,
    FAST_DUTY_CYCLE_2,
};

static MAX7310Config devconfig = {
    &I2CD1,
    &i2cconfig,
    OPD_PROTOCARD1,
    OPD_ODR_VAL,
    OPD_POL_VAL,
    OPD_MODE_VAL,
    MAX7310_TIMEOUT_ENABLED
};

void opd_init(void)
{
    max7310ObjectInit(&MAX7310D1);
}

void opd_start(opd_addr_t opd_addr)
{
    devconfig.saddr = opd_addr;
    max7310Start(&MAX7310D1, &devconfig);
}

void opd_stop(void)
{
    max7310Stop(&MAX7310D1);
}

void opd_enable(opd_addr_t opd_addr)
{

}

void opd_disable(opd_addr_t opd_addr)
{

}
