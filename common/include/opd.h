#ifndef OPD_H
#define OPD_H

/* IO Pin Assignments */
#define OPD_SCL             0U
#define OPD_SDA             1U
#define OPD_FAULT           2U
#define OPD_EN              3U
#define OPD_CB_RESET        4U
#define OPD_BOOT0           5U
#define OPD_PIN6            6U
#define OPD_PIN7            7U

/* IO Pin Configurations */
#define OPD_ODR_VAL        (MAX7310_PIN_ODR_LOW(OPD_SCL)            |   \
                            MAX7310_PIN_ODR_LOW(OPD_SDA)            |   \
                            MAX7310_PIN_ODR_LOW(OPD_FAULT)          |   \
                            MAX7310_PIN_ODR_LOW(OPD_EN)             |   \
                            MAX7310_PIN_ODR_LOW(OPD_CB_RESET)       |   \
                            MAX7310_PIN_ODR_LOW(OPD_BOOT0)          |   \
                            MAX7310_PIN_ODR_LOW(OPD_PIN6)           |   \
                            MAX7310_PIN_ODR_LOW(OPD_PIN7))
#define OPD_POL_VAL        (MAX7310_PIN_POL_STD(OPD_SCL)            |   \
                            MAX7310_PIN_POL_STD(OPD_SDA)            |   \
                            MAX7310_PIN_POL_INV(OPD_FAULT)          |   \
                            MAX7310_PIN_POL_STD(OPD_EN)             |   \
                            MAX7310_PIN_POL_STD(OPD_CB_RESET)       |   \
                            MAX7310_PIN_POL_STD(OPD_BOOT0)          |   \
                            MAX7310_PIN_POL_STD(OPD_PIN6)           |   \
                            MAX7310_PIN_POL_STD(OPD_PIN7))
#define OPD_MODE_VAL       (MAX7310_PIN_MODE_INPUT(OPD_SCL)         |   \
                            MAX7310_PIN_MODE_INPUT(OPD_SDA)         |   \
                            MAX7310_PIN_MODE_INPUT(OPD_FAULT)       |   \
                            MAX7310_PIN_MODE_OUTPUT(OPD_EN)         |   \
                            MAX7310_PIN_MODE_OUTPUT(OPD_CB_RESET)   |   \
                            MAX7310_PIN_MODE_OUTPUT(OPD_BOOT0)      |   \
                            MAX7310_PIN_MODE_OUTPUT(OPD_PIN6)       |   \
                            MAX7310_PIN_MODE_OUTPUT(OPD_PIN7))

typedef struct {
    uint8_t input;
    uint8_t odr;
    uint8_t pol;
    uint8_t mode;
    uint8_t timeout;
} opd_status_t;

void opd_init(void);
void opd_start(void);
void opd_stop(void);
bool opd_probe(i2caddr_t addr);
int opd_enable(i2caddr_t addr);
int opd_disable(i2caddr_t addr);
int opd_reset(i2caddr_t addr);
int opd_status(i2caddr_t addr, opd_status_t *status);

int opd_boot(i2caddr_t addr);
#endif
