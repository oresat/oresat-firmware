#ifndef OPD_H
#define OPD_H

/* IO Pin Assignments */
#define OPD_SCL             3U /* TODO: Revert this when the time comes */
#define OPD_SDA             4U /* TODO: Revert this when the time comes */
#define OPD_FAULT           2U
#define OPD_EN              0U /* TODO: Revert this when the time comes */
#define OPD_CB_RESET        1U /* TODO: Revert this when the time comes */
#define OPD_BOOT0           5U
#define OPD_PULLUP          6U
#define OPD_LED             7U

/* IO Pin Configurations */
#define OPD_ODR_VAL        (MAX7310_PIN_ODR_LOW(OPD_SCL)            |   \
                            MAX7310_PIN_ODR_LOW(OPD_SDA)            |   \
                            MAX7310_PIN_ODR_LOW(OPD_FAULT)          |   \
                            MAX7310_PIN_ODR_LOW(OPD_EN)             |   \
                            MAX7310_PIN_ODR_LOW(OPD_CB_RESET)       |   \
                            MAX7310_PIN_ODR_LOW(OPD_BOOT0)          |   \
                            MAX7310_PIN_ODR_LOW(OPD_PULLUP)         |   \
                            MAX7310_PIN_ODR_LOW(OPD_LED))
#define OPD_POL_VAL        (MAX7310_PIN_POL_INV(OPD_SCL)            |   \
                            MAX7310_PIN_POL_INV(OPD_SDA)            |   \
                            MAX7310_PIN_POL_INV(OPD_FAULT)          |   \
                            MAX7310_PIN_POL_STD(OPD_EN)             |   \
                            MAX7310_PIN_POL_STD(OPD_CB_RESET)       |   \
                            MAX7310_PIN_POL_STD(OPD_BOOT0)          |   \
                            MAX7310_PIN_POL_STD(OPD_PULLUP)         |   \
                            MAX7310_PIN_POL_STD(OPD_LED))
#define OPD_MODE_VAL       (MAX7310_PIN_MODE_INPUT(OPD_SCL)         |   \
                            MAX7310_PIN_MODE_INPUT(OPD_SDA)         |   \
                            MAX7310_PIN_MODE_INPUT(OPD_FAULT)       |   \
                            MAX7310_PIN_MODE_INPUT(OPD_EN)          |   \
                            MAX7310_PIN_MODE_INPUT(OPD_CB_RESET)    |   \
                            MAX7310_PIN_MODE_INPUT(OPD_BOOT0)       |   \
                            MAX7310_PIN_MODE_INPUT(OPD_PULLUP)      |   \
                            MAX7310_PIN_MODE_OUTPUT(OPD_LED))

typedef enum {
    OPD_PROTOCARD1 = 0x18,
    OPD_PROTOCARD2 = 0x19,
    OPD_PROTOCARD3 = 0x1A,
} opd_addr_t;

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
void opd_enable(opd_addr_t opd_addr);
void opd_disable(opd_addr_t opd_addr);
void opd_reset(opd_addr_t opd_addr);
int  opd_status(opd_addr_t opd_addr, opd_status_t *status);
#endif
