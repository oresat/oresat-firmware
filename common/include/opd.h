#ifndef OPD_H
#define OPD_H

#define OPD_MIN_ADDR                0x8
#define OPD_MAX_ADDR                0x3F

/* IO Pin Assignments */
#define OPD_SCL                     0U
#define OPD_SDA                     1U
#define OPD_FAULT                   2U
#define OPD_EN                      3U
#define OPD_CB_RESET                4U
#define OPD_BOOT0                   5U
#define OPD_LINUX_BOOT                    6U
#define OPD_PIN7                    7U

#define OPD_PIN_MASK(n)             (1U << (n))

#define OPD_PIN_ODR_LOW(n)          (0U << (n))
#define OPD_PIN_ODR_HIGH(n)         (1U << (n))
#define OPD_PIN_POL_STD(n)          (0U << (n))
#define OPD_PIN_POL_INV(n)          (1U << (n))
#define OPD_PIN_MODE_OUTPUT(n)      (0U << (n))
#define OPD_PIN_MODE_INPUT(n)       (1U << (n))

/* IO Pin Configurations */
#define OPD_ODR_VAL                 (OPD_PIN_ODR_LOW(OPD_SCL)           |   \
                                     OPD_PIN_ODR_LOW(OPD_SDA)           |   \
                                     OPD_PIN_ODR_LOW(OPD_FAULT)         |   \
                                     OPD_PIN_ODR_LOW(OPD_EN)            |   \
                                     OPD_PIN_ODR_LOW(OPD_CB_RESET)      |   \
                                     OPD_PIN_ODR_LOW(OPD_BOOT0)         |   \
                                     OPD_PIN_ODR_HIGH(OPD_LINUX_BOOT)   |   \
                                     OPD_PIN_ODR_LOW(OPD_PIN7))
#define OPD_POL_VAL                 (OPD_PIN_POL_STD(OPD_SCL)           |   \
                                     OPD_PIN_POL_STD(OPD_SDA)           |   \
                                     OPD_PIN_POL_INV(OPD_FAULT)         |   \
                                     OPD_PIN_POL_STD(OPD_EN)            |   \
                                     OPD_PIN_POL_STD(OPD_CB_RESET)      |   \
                                     OPD_PIN_POL_STD(OPD_BOOT0)         |   \
                                     OPD_PIN_POL_STD(OPD_LINUX_BOOT)    |   \
                                     OPD_PIN_POL_STD(OPD_PIN7))
#define OPD_MODE_VAL                (OPD_PIN_MODE_INPUT(OPD_SCL)        |   \
                                     OPD_PIN_MODE_INPUT(OPD_SDA)        |   \
                                     OPD_PIN_MODE_INPUT(OPD_FAULT)      |   \
                                     OPD_PIN_MODE_OUTPUT(OPD_EN)        |   \
                                     OPD_PIN_MODE_OUTPUT(OPD_CB_RESET)  |   \
                                     OPD_PIN_MODE_OUTPUT(OPD_BOOT0)     |   \
                                     OPD_PIN_MODE_OUTPUT(OPD_LINUX_BOOT)|   \
                                     OPD_PIN_MODE_OUTPUT(OPD_PIN7))

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
void opd_scan(bool restart);
bool opd_probe(i2caddr_t addr, bool restart);
int opd_enable(i2caddr_t addr, bool enable);
int opd_disable(i2caddr_t addr);
int opd_reset(i2caddr_t addr);
int opd_status(i2caddr_t addr, opd_status_t *status);

int opd_boot(i2caddr_t addr);
int opd_linux_recover(i2caddr_t addr, bool enable);
#endif
