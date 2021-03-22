/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/*
 * This file has been automatically generated using ChibiStudio board
 * generator plugin. Do not edit manually.
 */

#ifndef BOARD_H
#define BOARD_H

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/*
 * OreSat C3 Prototype Board
 * PART: STM32F439VI
 * PACKAGE: LQFP100
 */

/*
 * Board identifier.
 */
#define ORESAT_C3_V4
#define BOARD_NAME                  "OreSat C3 v4"

/*
 * Board oscillators-related settings.
 */
#if !defined(STM32_LSECLK)
#define STM32_LSECLK                32768U
#endif

#if !defined(STM32_HSECLK)
#define STM32_HSECLK                16000000U
#endif

/*
 * Board voltages.
 * Required for performance limits calculation.
 */
#define STM32_VDD                   300U

/*
 * MCU type as defined in the ST header.
 */
#define STM32F439xx

/*
 * IO pins assignments.
 */
#define GPIOA_PIN0                  0U
#define GPIOA_PIN1                  1U
#define GPIOA_PIN2                  2U
#define GPIOA_PIN3                  3U
#define GPIOA_PA_THERM              4U
#define GPIOA_SPI1_SCK              5U
#define GPIOA_SPI1_MISO             6U
#define GPIOA_SPI1_MOSI             7U
#define GPIOA_I2C_PWROFF            8U
#define GPIOA_CAN1_SILENT           9U
#define GPIOA_CAN1_SHDN             10U
#define GPIOA_CAN1_RX               11U
#define GPIOA_CAN1_TX               12U
#define GPIOA_SWDIO                 13U
#define GPIOA_SWCLK                 14U
#define GPIOA_PIN15                 15U

#define GPIOB_PIN0                  0U
#define GPIOB_PIN1                  1U
#define GPIOB_PIN3                  2U
#define GPIOB_SWO                   3U
#define GPIOB_CAN2_SHDN             4U
#define GPIOB_CAN2_RX               5U
#define GPIOB_CAN2_TX               6U
#define GPIOB_CAN2_SILENT           7U
#define GPIOB_I2C1_SCL              8U
#define GPIOB_I2C1_SDA              9U
#define GPIOB_I2C2_SCL              10U
#define GPIOB_I2C2_SDA              11U
#define GPIOB_LO_SEN                12U
#define GPIOB_LO_SCLK               13U
#define GPIOB_LO_SDATA              14U
#define GPIOB_LO_PLL                15U

#define GPIOC_VERIFY_TURN           0U
#define GPIOC_VERIFY_HELI           1U
#define GPIOC_CB_IOUT               2U
#define GPIOC_OPD_ISET              3U
#define GPIOC_PA_FWD                4U
#define GPIOC_PA_REV                5U
#define GPIOC_PIN6                  6U
#define GPIOC_PIN7                  7U
#define GPIOC_SDIO_D0               8U
#define GPIOC_SDIO_D1               9U
#define GPIOC_SDIO_D2               10U
#define GPIOC_SDIO_D3               11U
#define GPIOC_SDIO_CK               12U
#define GPIOC_PIN13                 13U
#define GPIOC_OSC32_IN              14U
#define GPIOC_OSC32_OUT             15U

#define GPIOD_FIRE_HELI_1           0U
#define GPIOD_FIRE_TURN_1           1U
#define GPIOD_SDIO_CMD              2U
#define GPIOD_TEST_HELI             3U
#define GPIOD_UHF_ENABLE            4U
#define GPIOD_OPD_ENABLE            5U
#define GPIOD_TEST_TURN             6U
#define GPIOD_UHF_FLT               7U
#define GPIOD_USART3_TX             8U
#define GPIOD_USART3_RX             9U
#define GPIOD_UHF_IRQ               10U
#define GPIOD_UHF_CS                11U
#define GPIOD_LBAND_IRQ             12U
#define GPIOD_LBAND_CS              13U
#define GPIOD_PIN14                 14U
#define GPIOD_PIN15                 15U

#define GPIOE_OPD_FAULT             0U
#define GPIOE_WDT                   1U
#define GPIOE_FIRE_TURN_2           2U
#define GPIOE_FIRE_HELI_2           3U
#define GPIOE_PIN4                  4U
#define GPIOE_PIN5                  5U
#define GPIOE_PIN6                  6U
#define GPIOE_MMC_PWR               7U
#define GPIOE_PIN8                  8U
#define GPIOE_PIN9                  9U
#define GPIOE_PIN10                 10U
#define GPIOE_TOT_OUT               11U
#define GPIOE_PIN12                 12U
#define GPIOE_LNA_ENABLE            13U
#define GPIOE_PA_ENABLE             14U
#define GPIOE_TOT_CLEAR             15U

#define GPIOF_PIN0                  0U
#define GPIOF_PIN1                  1U
#define GPIOF_PIN2                  2U
#define GPIOF_PIN3                  3U
#define GPIOF_PIN4                  4U
#define GPIOF_PIN5                  5U
#define GPIOF_PIN6                  6U
#define GPIOF_PIN7                  7U
#define GPIOF_PIN8                  8U
#define GPIOF_PIN9                  9U
#define GPIOF_PIN10                 10U
#define GPIOF_PIN11                 11U
#define GPIOF_PIN12                 12U
#define GPIOF_PIN13                 13U
#define GPIOF_PIN14                 14U
#define GPIOF_PIN15                 15U

#define GPIOG_PIN0                  0U
#define GPIOG_PIN1                  1U
#define GPIOG_PIN2                  2U
#define GPIOG_PIN3                  3U
#define GPIOG_PIN4                  4U
#define GPIOG_PIN5                  5U
#define GPIOG_PIN6                  6U
#define GPIOG_PIN7                  7U
#define GPIOG_PIN8                  8U
#define GPIOG_PIN9                  9U
#define GPIOG_PIN10                 10U
#define GPIOG_PIN11                 11U
#define GPIOG_PIN12                 12U
#define GPIOG_PIN13                 13U
#define GPIOG_PIN14                 14U
#define GPIOG_PIN15                 15U

#define GPIOH_OSC_IN                0U
#define GPIOH_OSC_OUT               1U
#define GPIOH_PIN2                  2U
#define GPIOH_PIN3                  3U
#define GPIOH_PIN4                  4U
#define GPIOH_PIN5                  5U
#define GPIOH_PIN6                  6U
#define GPIOH_PIN7                  7U
#define GPIOH_PIN8                  8U
#define GPIOH_PIN9                  9U
#define GPIOH_PIN10                 10U
#define GPIOH_PIN11                 11U
#define GPIOH_PIN12                 12U
#define GPIOH_PIN13                 13U
#define GPIOH_PIN14                 14U
#define GPIOH_PIN15                 15U

#define GPIOI_PIN0                  0U
#define GPIOI_PIN1                  1U
#define GPIOI_PIN2                  2U
#define GPIOI_PIN3                  3U
#define GPIOI_PIN4                  4U
#define GPIOI_PIN5                  5U
#define GPIOI_PIN6                  6U
#define GPIOI_PIN7                  7U
#define GPIOI_PIN8                  8U
#define GPIOI_PIN9                  9U
#define GPIOI_PIN10                 10U
#define GPIOI_PIN11                 11U
#define GPIOI_PIN12                 12U
#define GPIOI_PIN13                 13U
#define GPIOI_PIN14                 14U
#define GPIOI_PIN15                 15U

/*
 * IO lines assignments.
 */
#define LINE_SPI1_MISO              PAL_LINE(GPIOA, 6U)
#define LINE_I2C_PWROFF             PAL_LINE(GPIOA, 8U)
#define LINE_CAN1_SILENT            PAL_LINE(GPIOA, 9U)
#define LINE_CAN1_SHDN              PAL_LINE(GPIOA, 10U)
#define LINE_CAN2_SHDN              PAL_LINE(GPIOB, 4U)
#define LINE_CAN2_SILENT            PAL_LINE(GPIOB, 7U)
#define LINE_LO_SEN                 PAL_LINE(GPIOB, 12U)
#define LINE_LO_SCLK                PAL_LINE(GPIOB, 13U)
#define LINE_LO_SDATA               PAL_LINE(GPIOB, 14U)
#define LINE_LO_PLL                 PAL_LINE(GPIOB, 15U)
#define LINE_FIRE_HELI_1            PAL_LINE(GPIOD, 0U)
#define LINE_FIRE_TURN_1            PAL_LINE(GPIOD, 1U)
#define LINE_UHF_ENABLE             PAL_LINE(GPIOD, 4U)
#define LINE_OPD_ENABLE             PAL_LINE(GPIOD, 5U)
#define LINE_UHF_IRQ                PAL_LINE(GPIOD, 10U)
#define LINE_UHF_CS                 PAL_LINE(GPIOD, 11U)
#define LINE_LBAND_IRQ              PAL_LINE(GPIOD, 12U)
#define LINE_LBAND_CS               PAL_LINE(GPIOD, 13U)
#define LINE_OPD_FAULT              PAL_LINE(GPIOE, 0U)
#define LINE_WDT                    PAL_LINE(GPIOE, 1U)
#define LINE_FIRE_TURN_2            PAL_LINE(GPIOE, 2U)
#define LINE_FIRE_HELI_2            PAL_LINE(GPIOE, 3U)
#define LINE_MMC_PWR                PAL_LINE(GPIOE, 7U)
#define LINE_TOT_OUT                PAL_LINE(GPIOE, 11U)
#define LINE_LNA_ENABLE             PAL_LINE(GPIOE, 13U)
#define LINE_PA_ENABLE              PAL_LINE(GPIOE, 14U)
#define LINE_TOT_CLEAR              PAL_LINE(GPIOE, 15U)

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 * Please refer to the STM32 Reference Manual for details.
 */
#define PIN_MODE_INPUT(n)           (0U << ((n) * 2U))
#define PIN_MODE_OUTPUT(n)          (1U << ((n) * 2U))
#define PIN_MODE_ALTERNATE(n)       (2U << ((n) * 2U))
#define PIN_MODE_ANALOG(n)          (3U << ((n) * 2U))
#define PIN_ODR_LOW(n)              (0U << (n))
#define PIN_ODR_HIGH(n)             (1U << (n))
#define PIN_OTYPE_PUSHPULL(n)       (0U << (n))
#define PIN_OTYPE_OPENDRAIN(n)      (1U << (n))
#define PIN_OSPEED_VERYLOW(n)       (0U << ((n) * 2U))
#define PIN_OSPEED_LOW(n)           (1U << ((n) * 2U))
#define PIN_OSPEED_MEDIUM(n)        (2U << ((n) * 2U))
#define PIN_OSPEED_HIGH(n)          (3U << ((n) * 2U))
#define PIN_PUPDR_FLOATING(n)       (0U << ((n) * 2U))
#define PIN_PUPDR_PULLUP(n)         (1U << ((n) * 2U))
#define PIN_PUPDR_PULLDOWN(n)       (2U << ((n) * 2U))
#define PIN_AFIO_AF(n, v)           ((v) << (((n) % 8U) * 4U))

/*
 * GPIOA setup:
 *
 * PA0  - PIN0                      (analog).
 * PA1  - PIN1                      (analog).
 * PA2  - PIN2                      (analog).
 * PA3  - PIN3                      (analog).
 * PA4  - PA_THERM                  (analog).
 * PA5  - SPI1_SCK                  (alternate 5).
 * PA6  - SPI1_MISO                 (alternate 5).
 * PA7  - SPI1_MOSI                 (alternate 5).
 * PA8  - I2C_PWROFF                (output pushpull).
 * PA9  - CAN1_SILENT               (output pushpull).
 * PA10 - CAN1_SHDN                 (output pushpull).
 * PA11 - CAN1_RX                   (alternate 9).
 * PA12 - CAN1_TX                   (alternate 9).
 * PA13 - SWDIO                     (alternate 0).
 * PA14 - SWCLK                     (alternate 0).
 * PA15 - PIN15                     (analog).
 */
#define VAL_GPIOA_MODER             (PIN_MODE_ANALOG(GPIOA_PIN0) |          \
                                     PIN_MODE_ANALOG(GPIOA_PIN1) |          \
                                     PIN_MODE_ANALOG(GPIOA_PIN2) |          \
                                     PIN_MODE_ANALOG(GPIOA_PIN3) |          \
                                     PIN_MODE_ANALOG(GPIOA_PA_THERM) |      \
                                     PIN_MODE_ALTERNATE(GPIOA_SPI1_SCK) |   \
                                     PIN_MODE_ALTERNATE(GPIOA_SPI1_MISO) |  \
                                     PIN_MODE_ALTERNATE(GPIOA_SPI1_MOSI) |  \
                                     PIN_MODE_OUTPUT(GPIOA_I2C_PWROFF) |    \
                                     PIN_MODE_OUTPUT(GPIOA_CAN1_SILENT) |   \
                                     PIN_MODE_OUTPUT(GPIOA_CAN1_SHDN) |     \
                                     PIN_MODE_ALTERNATE(GPIOA_CAN1_RX) |    \
                                     PIN_MODE_ALTERNATE(GPIOA_CAN1_TX) |    \
                                     PIN_MODE_ALTERNATE(GPIOA_SWDIO) |      \
                                     PIN_MODE_ALTERNATE(GPIOA_SWCLK) |      \
                                     PIN_MODE_ANALOG(GPIOA_PIN15))
#define VAL_GPIOA_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOA_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PA_THERM) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SPI1_SCK) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SPI1_MISO) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SPI1_MOSI) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_I2C_PWROFF) | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_CAN1_SILENT) |\
                                     PIN_OTYPE_PUSHPULL(GPIOA_CAN1_SHDN) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_CAN1_RX) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOA_CAN1_TX) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWDIO) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWCLK) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN15))
#define VAL_GPIOA_OSPEEDR           (PIN_OSPEED_HIGH(GPIOA_PIN0) |          \
                                     PIN_OSPEED_HIGH(GPIOA_PIN1) |          \
                                     PIN_OSPEED_HIGH(GPIOA_PIN2) |          \
                                     PIN_OSPEED_HIGH(GPIOA_PIN3) |          \
                                     PIN_OSPEED_HIGH(GPIOA_PA_THERM) |      \
                                     PIN_OSPEED_HIGH(GPIOA_SPI1_SCK) |      \
                                     PIN_OSPEED_HIGH(GPIOA_SPI1_MISO) |     \
                                     PIN_OSPEED_HIGH(GPIOA_SPI1_MOSI) |     \
                                     PIN_OSPEED_HIGH(GPIOA_I2C_PWROFF) |    \
                                     PIN_OSPEED_HIGH(GPIOA_CAN1_SILENT) |   \
                                     PIN_OSPEED_HIGH(GPIOA_CAN1_SHDN) |     \
                                     PIN_OSPEED_HIGH(GPIOA_CAN1_RX) |       \
                                     PIN_OSPEED_HIGH(GPIOA_CAN1_TX) |       \
                                     PIN_OSPEED_HIGH(GPIOA_SWDIO) |         \
                                     PIN_OSPEED_HIGH(GPIOA_SWCLK) |         \
                                     PIN_OSPEED_HIGH(GPIOA_PIN15))
#define VAL_GPIOA_PUPDR             (PIN_PUPDR_FLOATING(GPIOA_PIN0) |       \
                                     PIN_PUPDR_FLOATING(GPIOA_PIN1) |       \
                                     PIN_PUPDR_FLOATING(GPIOA_PIN2) |       \
                                     PIN_PUPDR_FLOATING(GPIOA_PIN3) |       \
                                     PIN_PUPDR_FLOATING(GPIOA_PA_THERM) |   \
                                     PIN_PUPDR_FLOATING(GPIOA_SPI1_SCK) |   \
                                     PIN_PUPDR_FLOATING(GPIOA_SPI1_MISO) |  \
                                     PIN_PUPDR_FLOATING(GPIOA_SPI1_MOSI) |  \
                                     PIN_PUPDR_FLOATING(GPIOA_I2C_PWROFF) | \
                                     PIN_PUPDR_FLOATING(GPIOA_CAN1_SILENT) |\
                                     PIN_PUPDR_FLOATING(GPIOA_CAN1_SHDN) |  \
                                     PIN_PUPDR_FLOATING(GPIOA_CAN1_RX) |    \
                                     PIN_PUPDR_FLOATING(GPIOA_CAN1_TX) |    \
                                     PIN_PUPDR_PULLUP(GPIOA_SWDIO) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOA_SWCLK) |      \
                                     PIN_PUPDR_FLOATING(GPIOA_PIN15))
#define VAL_GPIOA_ODR               (PIN_ODR_HIGH(GPIOA_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOA_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOA_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOA_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOA_PA_THERM) |         \
                                     PIN_ODR_HIGH(GPIOA_SPI1_SCK) |         \
                                     PIN_ODR_HIGH(GPIOA_SPI1_MISO) |        \
                                     PIN_ODR_HIGH(GPIOA_SPI1_MOSI) |        \
                                     PIN_ODR_HIGH(GPIOA_I2C_PWROFF) |       \
                                     PIN_ODR_LOW(GPIOA_CAN1_SILENT) |       \
                                     PIN_ODR_LOW(GPIOA_CAN1_SHDN) |         \
                                     PIN_ODR_HIGH(GPIOA_CAN1_RX) |          \
                                     PIN_ODR_HIGH(GPIOA_CAN1_TX) |          \
                                     PIN_ODR_HIGH(GPIOA_SWDIO) |            \
                                     PIN_ODR_HIGH(GPIOA_SWCLK) |            \
                                     PIN_ODR_HIGH(GPIOA_PIN15))
#define VAL_GPIOA_AFRL              (PIN_AFIO_AF(GPIOA_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOA_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOA_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOA_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOA_PA_THERM, 0U) |      \
                                     PIN_AFIO_AF(GPIOA_SPI1_SCK, 5U) |      \
                                     PIN_AFIO_AF(GPIOA_SPI1_MISO, 5U) |     \
                                     PIN_AFIO_AF(GPIOA_SPI1_MOSI, 5U))
#define VAL_GPIOA_AFRH              (PIN_AFIO_AF(GPIOA_I2C_PWROFF, 0U) |    \
                                     PIN_AFIO_AF(GPIOA_CAN1_SILENT, 0U) |   \
                                     PIN_AFIO_AF(GPIOA_CAN1_SHDN, 0U) |     \
                                     PIN_AFIO_AF(GPIOA_CAN1_RX, 9U) |       \
                                     PIN_AFIO_AF(GPIOA_CAN1_TX, 9U) |       \
                                     PIN_AFIO_AF(GPIOA_SWDIO, 0U) |         \
                                     PIN_AFIO_AF(GPIOA_SWCLK, 0U) |         \
                                     PIN_AFIO_AF(GPIOA_PIN15, 0U))

/*
 * GPIOB setup:
 *
 * PB0  - PIN0                      (analog).
 * PB1  - PIN1                      (analog).
 * PB2  - PIN3                      (analog).
 * PB3  - SWO                       (alternate 0).
 * PB4  - CAN2_SHDN                 (output pushpull).
 * PB5  - CAN2_RX                   (alternate 9).
 * PB6  - CAN2_TX                   (alternate 9).
 * PB7  - CAN2_SILENT               (output pushpull).
 * PB8  - I2C1_SCL                  (alternate 4).
 * PB9  - I2C1_SDA                  (alternate 4).
 * PB10 - I2C2_SCL                  (alternate 4).
 * PB11 - I2C2_SDA                  (alternate 4).
 * PB12 - LO_SEN                    (output pushpull).
 * PB13 - LO_SCLK                   (output pushpull).
 * PB14 - LO_SDATA                  (output pushpull).
 * PB15 - LO_PLL                    (input).
 */
#define VAL_GPIOB_MODER             (PIN_MODE_ANALOG(GPIOB_PIN0) |          \
                                     PIN_MODE_ANALOG(GPIOB_PIN1) |          \
                                     PIN_MODE_ANALOG(GPIOB_PIN3) |          \
                                     PIN_MODE_ALTERNATE(GPIOB_SWO) |        \
                                     PIN_MODE_ANALOG(GPIOB_CAN2_SHDN) |     \
                                     PIN_MODE_ALTERNATE(GPIOB_CAN2_RX) |    \
                                     PIN_MODE_ALTERNATE(GPIOB_CAN2_TX) |    \
                                     PIN_MODE_ANALOG(GPIOB_CAN2_SILENT) |   \
                                     PIN_MODE_ALTERNATE(GPIOB_I2C1_SCL) |   \
                                     PIN_MODE_ALTERNATE(GPIOB_I2C1_SDA) |   \
                                     PIN_MODE_ALTERNATE(GPIOB_I2C2_SCL) |   \
                                     PIN_MODE_ALTERNATE(GPIOB_I2C2_SDA) |   \
                                     PIN_MODE_OUTPUT(GPIOB_LO_SEN) |        \
                                     PIN_MODE_OUTPUT(GPIOB_LO_SCLK) |       \
                                     PIN_MODE_OUTPUT(GPIOB_LO_SDATA) |      \
                                     PIN_MODE_INPUT(GPIOB_LO_PLL))
#define VAL_GPIOB_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOB_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_SWO) |        \
                                     PIN_OTYPE_PUSHPULL(GPIOB_CAN2_SHDN) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOB_CAN2_RX) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOB_CAN2_TX) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOB_CAN2_SILENT) |\
                                     PIN_OTYPE_OPENDRAIN(GPIOB_I2C1_SCL) |  \
                                     PIN_OTYPE_OPENDRAIN(GPIOB_I2C1_SDA) |  \
                                     PIN_OTYPE_OPENDRAIN(GPIOB_I2C2_SCL) |  \
                                     PIN_OTYPE_OPENDRAIN(GPIOB_I2C2_SDA) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOB_LO_SEN) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOB_LO_SCLK) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOB_LO_SDATA) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOB_LO_PLL))
#define VAL_GPIOB_OSPEEDR           (PIN_OSPEED_HIGH(GPIOB_PIN0) |          \
                                     PIN_OSPEED_HIGH(GPIOB_PIN1) |          \
                                     PIN_OSPEED_HIGH(GPIOB_PIN3) |          \
                                     PIN_OSPEED_HIGH(GPIOB_SWO) |           \
                                     PIN_OSPEED_HIGH(GPIOB_CAN2_SHDN) |     \
                                     PIN_OSPEED_HIGH(GPIOB_CAN2_RX) |       \
                                     PIN_OSPEED_HIGH(GPIOB_CAN2_TX) |       \
                                     PIN_OSPEED_HIGH(GPIOB_CAN2_SILENT) |   \
                                     PIN_OSPEED_HIGH(GPIOB_I2C1_SCL) |      \
                                     PIN_OSPEED_HIGH(GPIOB_I2C1_SDA) |      \
                                     PIN_OSPEED_HIGH(GPIOB_I2C2_SCL) |      \
                                     PIN_OSPEED_HIGH(GPIOB_I2C2_SDA) |      \
                                     PIN_OSPEED_HIGH(GPIOB_LO_SEN) |        \
                                     PIN_OSPEED_HIGH(GPIOB_LO_SCLK) |       \
                                     PIN_OSPEED_HIGH(GPIOB_LO_SDATA) |      \
                                     PIN_OSPEED_HIGH(GPIOB_LO_PLL))
#define VAL_GPIOB_PUPDR             (PIN_PUPDR_FLOATING(GPIOB_PIN0) |       \
                                     PIN_PUPDR_FLOATING(GPIOB_PIN1) |       \
                                     PIN_PUPDR_FLOATING(GPIOB_PIN3) |       \
                                     PIN_PUPDR_FLOATING(GPIOB_SWO) |        \
                                     PIN_PUPDR_FLOATING(GPIOB_CAN2_SHDN) |  \
                                     PIN_PUPDR_FLOATING(GPIOB_CAN2_RX) |    \
                                     PIN_PUPDR_FLOATING(GPIOB_CAN2_TX) |    \
                                     PIN_PUPDR_FLOATING(GPIOB_CAN2_SILENT) |\
                                     PIN_PUPDR_FLOATING(GPIOB_I2C1_SCL) |   \
                                     PIN_PUPDR_FLOATING(GPIOB_I2C1_SDA) |   \
                                     PIN_PUPDR_FLOATING(GPIOB_I2C2_SCL) |   \
                                     PIN_PUPDR_FLOATING(GPIOB_I2C2_SDA) |   \
                                     PIN_PUPDR_FLOATING(GPIOB_LO_SEN) |     \
                                     PIN_PUPDR_FLOATING(GPIOB_LO_SCLK) |    \
                                     PIN_PUPDR_FLOATING(GPIOB_LO_SDATA) |   \
                                     PIN_PUPDR_PULLUP(GPIOB_LO_PLL))
#define VAL_GPIOB_ODR               (PIN_ODR_HIGH(GPIOB_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOB_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOB_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOB_SWO) |              \
                                     PIN_ODR_LOW(GPIOB_CAN2_SHDN) |         \
                                     PIN_ODR_HIGH(GPIOB_CAN2_RX) |          \
                                     PIN_ODR_HIGH(GPIOB_CAN2_TX) |          \
                                     PIN_ODR_LOW(GPIOB_CAN2_SILENT) |       \
                                     PIN_ODR_HIGH(GPIOB_I2C1_SCL) |         \
                                     PIN_ODR_HIGH(GPIOB_I2C1_SDA) |         \
                                     PIN_ODR_HIGH(GPIOB_I2C2_SCL) |         \
                                     PIN_ODR_HIGH(GPIOB_I2C2_SDA) |         \
                                     PIN_ODR_HIGH(GPIOB_LO_SEN) |           \
                                     PIN_ODR_HIGH(GPIOB_LO_SCLK) |          \
                                     PIN_ODR_HIGH(GPIOB_LO_SDATA) |         \
                                     PIN_ODR_HIGH(GPIOB_LO_PLL))
#define VAL_GPIOB_AFRL              (PIN_AFIO_AF(GPIOB_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOB_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOB_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOB_SWO, 0U) |           \
                                     PIN_AFIO_AF(GPIOB_CAN2_SHDN, 0U) |     \
                                     PIN_AFIO_AF(GPIOB_CAN2_RX, 9U) |       \
                                     PIN_AFIO_AF(GPIOB_CAN2_TX, 9U) |       \
                                     PIN_AFIO_AF(GPIOB_CAN2_SILENT, 0U))
#define VAL_GPIOB_AFRH              (PIN_AFIO_AF(GPIOB_I2C1_SCL, 4U) |      \
                                     PIN_AFIO_AF(GPIOB_I2C1_SDA, 4U) |      \
                                     PIN_AFIO_AF(GPIOB_I2C2_SCL, 4U) |      \
                                     PIN_AFIO_AF(GPIOB_I2C2_SDA, 4U) |      \
                                     PIN_AFIO_AF(GPIOB_LO_SEN, 5U) |        \
                                     PIN_AFIO_AF(GPIOB_LO_SCLK, 5U) |       \
                                     PIN_AFIO_AF(GPIOB_LO_SDATA, 5U) |      \
                                     PIN_AFIO_AF(GPIOB_LO_PLL, 5U))

/*
 * GPIOC setup:
 *
 * PC0  - VERIFY_TURN               (analog).
 * PC1  - VERIFY_HELI               (analog).
 * PC2  - CB_IOUT                   (analog).
 * PC3  - OPD_ISET                  (analog).
 * PC4  - PA_FWD                    (analog).
 * PC5  - PA_REV                    (analog).
 * PC6  - PIN6                      (analog).
 * PC7  - PIN7                      (analog).
 * PC8  - SDIO_D0                   (alternate 12).
 * PC9  - SDIO_D1                   (alternate 12).
 * PC10 - SDIO_D2                   (alternate 12).
 * PC11 - SDIO_D3                   (alternate 12).
 * PC12 - SDIO_CK                   (alternate 12).
 * PC13 - PIN13                     (analog).
 * PC14 - OSC32_IN                  (analog).
 * PC15 - OSC32_OUT                 (analog).
 */
#define VAL_GPIOC_MODER             (PIN_MODE_ANALOG(GPIOC_VERIFY_TURN) |   \
                                     PIN_MODE_ANALOG(GPIOC_VERIFY_HELI) |   \
                                     PIN_MODE_ANALOG(GPIOC_CB_IOUT) |       \
                                     PIN_MODE_ANALOG(GPIOC_OPD_ISET) |      \
                                     PIN_MODE_ANALOG(GPIOC_PA_FWD) |        \
                                     PIN_MODE_ANALOG(GPIOC_PA_REV) |        \
                                     PIN_MODE_ANALOG(GPIOC_PIN6) |          \
                                     PIN_MODE_ANALOG(GPIOC_PIN7) |          \
                                     PIN_MODE_ALTERNATE(GPIOC_SDIO_D0) |    \
                                     PIN_MODE_ALTERNATE(GPIOC_SDIO_D1) |    \
                                     PIN_MODE_ALTERNATE(GPIOC_SDIO_D2) |    \
                                     PIN_MODE_ALTERNATE(GPIOC_SDIO_D3) |    \
                                     PIN_MODE_ALTERNATE(GPIOC_SDIO_CK) |    \
                                     PIN_MODE_ANALOG(GPIOC_PIN13) |         \
                                     PIN_MODE_ANALOG(GPIOC_OSC32_IN) |      \
                                     PIN_MODE_ANALOG(GPIOC_OSC32_OUT))
#define VAL_GPIOC_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOC_VERIFY_TURN) |\
                                     PIN_OTYPE_PUSHPULL(GPIOC_VERIFY_HELI) |\
                                     PIN_OTYPE_PUSHPULL(GPIOC_CB_IOUT) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOC_OPD_ISET) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PA_FWD) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PA_REV) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SDIO_D0) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SDIO_D1) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SDIO_D2) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SDIO_D3) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SDIO_CK) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_OSC32_IN) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOC_OSC32_OUT))
#define VAL_GPIOC_OSPEEDR           (PIN_OSPEED_HIGH(GPIOC_VERIFY_TURN) |   \
                                     PIN_OSPEED_HIGH(GPIOC_VERIFY_HELI) |   \
                                     PIN_OSPEED_HIGH(GPIOC_CB_IOUT) |       \
                                     PIN_OSPEED_HIGH(GPIOC_OPD_ISET) |      \
                                     PIN_OSPEED_HIGH(GPIOC_PA_FWD) |        \
                                     PIN_OSPEED_HIGH(GPIOC_PA_REV) |        \
                                     PIN_OSPEED_HIGH(GPIOC_PIN6) |          \
                                     PIN_OSPEED_HIGH(GPIOC_PIN7) |          \
                                     PIN_OSPEED_HIGH(GPIOC_SDIO_D0) |       \
                                     PIN_OSPEED_HIGH(GPIOC_SDIO_D1) |       \
                                     PIN_OSPEED_HIGH(GPIOC_SDIO_D2) |       \
                                     PIN_OSPEED_HIGH(GPIOC_SDIO_D3) |       \
                                     PIN_OSPEED_HIGH(GPIOC_SDIO_CK) |       \
                                     PIN_OSPEED_HIGH(GPIOC_PIN13) |         \
                                     PIN_OSPEED_HIGH(GPIOC_OSC32_IN) |      \
                                     PIN_OSPEED_HIGH(GPIOC_OSC32_OUT))
#define VAL_GPIOC_PUPDR             (PIN_PUPDR_FLOATING(GPIOC_VERIFY_TURN) |\
                                     PIN_PUPDR_FLOATING(GPIOC_VERIFY_HELI) |\
                                     PIN_PUPDR_FLOATING(GPIOC_CB_IOUT) |    \
                                     PIN_PUPDR_FLOATING(GPIOC_OPD_ISET) |   \
                                     PIN_PUPDR_FLOATING(GPIOC_PA_FWD) |     \
                                     PIN_PUPDR_FLOATING(GPIOC_PA_REV) |     \
                                     PIN_PUPDR_FLOATING(GPIOC_PIN6) |       \
                                     PIN_PUPDR_FLOATING(GPIOC_PIN7) |       \
                                     PIN_PUPDR_FLOATING(GPIOC_SDIO_D0) |    \
                                     PIN_PUPDR_FLOATING(GPIOC_SDIO_D1) |    \
                                     PIN_PUPDR_FLOATING(GPIOC_SDIO_D2) |    \
                                     PIN_PUPDR_FLOATING(GPIOC_SDIO_D3) |    \
                                     PIN_PUPDR_FLOATING(GPIOC_SDIO_CK) |    \
                                     PIN_PUPDR_FLOATING(GPIOC_PIN13) |      \
                                     PIN_PUPDR_FLOATING(GPIOC_OSC32_IN) |   \
                                     PIN_PUPDR_FLOATING(GPIOC_OSC32_OUT))
#define VAL_GPIOC_ODR               (PIN_ODR_HIGH(GPIOC_VERIFY_TURN) |      \
                                     PIN_ODR_HIGH(GPIOC_VERIFY_HELI) |      \
                                     PIN_ODR_HIGH(GPIOC_CB_IOUT) |          \
                                     PIN_ODR_HIGH(GPIOC_OPD_ISET) |         \
                                     PIN_ODR_HIGH(GPIOC_PA_FWD) |           \
                                     PIN_ODR_HIGH(GPIOC_PA_REV) |           \
                                     PIN_ODR_HIGH(GPIOC_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOC_SDIO_D0) |          \
                                     PIN_ODR_HIGH(GPIOC_SDIO_D1) |          \
                                     PIN_ODR_HIGH(GPIOC_SDIO_D2) |          \
                                     PIN_ODR_HIGH(GPIOC_SDIO_D3) |          \
                                     PIN_ODR_HIGH(GPIOC_SDIO_CK) |          \
                                     PIN_ODR_HIGH(GPIOC_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOC_OSC32_IN) |         \
                                     PIN_ODR_HIGH(GPIOC_OSC32_OUT))
#define VAL_GPIOC_AFRL              (PIN_AFIO_AF(GPIOC_VERIFY_TURN, 0U) |   \
                                     PIN_AFIO_AF(GPIOC_VERIFY_HELI, 0U) |   \
                                     PIN_AFIO_AF(GPIOC_CB_IOUT, 0U) |       \
                                     PIN_AFIO_AF(GPIOC_OPD_ISET, 0U) |      \
                                     PIN_AFIO_AF(GPIOC_PA_FWD, 0U) |        \
                                     PIN_AFIO_AF(GPIOC_PA_REV, 0U) |        \
                                     PIN_AFIO_AF(GPIOC_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_PIN7, 0U))
#define VAL_GPIOC_AFRH              (PIN_AFIO_AF(GPIOC_SDIO_D0, 12U) |      \
                                     PIN_AFIO_AF(GPIOC_SDIO_D1, 12U) |      \
                                     PIN_AFIO_AF(GPIOC_SDIO_D2, 12U) |      \
                                     PIN_AFIO_AF(GPIOC_SDIO_D3, 12U) |      \
                                     PIN_AFIO_AF(GPIOC_SDIO_CK, 12U) |      \
                                     PIN_AFIO_AF(GPIOC_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOC_OSC32_IN, 0U) |      \
                                     PIN_AFIO_AF(GPIOC_OSC32_OUT, 0U))

/*
 * GPIOD setup:
 *
 * PD0  - FIRE_HELI_1               (output pushpull).
 * PD1  - FIRE_TURN_1               (output pushpull).
 * PD2  - SDIO_CMD                  (alternate 12).
 * PD3  - TEST_HELI                 (analog).
 * PD4  - UHF_ENABLE                (output pushpull).
 * PD5  - OPD_ENABLE                (output pushpull).
 * PD6  - TEST_TURN                 (analog).
 * PD7  - UHF_FLT                   (analog).
 * PD8  - USART3_TX                 (alternate 7).
 * PD9  - USART3_RX                 (alternate 7).
 * PD10 - UHF_IRQ                   (input).
 * PD11 - UHF_CS                    (output).
 * PD12 - LBAND_IRQ                 (input).
 * PD13 - LBAND_CS                  (output).
 * PD14 - PIN14                     (analog).
 * PD15 - PIN15                     (analog).
 */
#define VAL_GPIOD_MODER             (PIN_MODE_OUTPUT(GPIOD_FIRE_HELI_1) |   \
                                     PIN_MODE_OUTPUT(GPIOD_FIRE_TURN_1) |   \
                                     PIN_MODE_ALTERNATE(GPIOD_SDIO_CMD) |   \
                                     PIN_MODE_ANALOG(GPIOD_TEST_HELI) |     \
                                     PIN_MODE_OUTPUT(GPIOD_UHF_ENABLE) |    \
                                     PIN_MODE_OUTPUT(GPIOD_OPD_ENABLE) |    \
                                     PIN_MODE_ANALOG(GPIOD_TEST_TURN) |     \
                                     PIN_MODE_ANALOG(GPIOD_UHF_FLT) |       \
                                     PIN_MODE_ALTERNATE(GPIOD_USART3_TX) |  \
                                     PIN_MODE_ALTERNATE(GPIOD_USART3_RX) |  \
                                     PIN_MODE_INPUT(GPIOD_UHF_IRQ) |        \
                                     PIN_MODE_OUTPUT(GPIOD_UHF_CS) |        \
                                     PIN_MODE_INPUT(GPIOD_LBAND_IRQ) |      \
                                     PIN_MODE_OUTPUT(GPIOD_LBAND_CS) |      \
                                     PIN_MODE_ANALOG(GPIOD_PIN14) |         \
                                     PIN_MODE_ANALOG(GPIOD_PIN15))
#define VAL_GPIOD_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOD_FIRE_HELI_1) |\
                                     PIN_OTYPE_PUSHPULL(GPIOD_FIRE_TURN_1) |\
                                     PIN_OTYPE_PUSHPULL(GPIOD_SDIO_CMD) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOD_TEST_HELI) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOD_UHF_ENABLE) | \
                                     PIN_OTYPE_PUSHPULL(GPIOD_OPD_ENABLE) | \
                                     PIN_OTYPE_PUSHPULL(GPIOD_TEST_TURN) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOD_UHF_FLT) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOD_USART3_TX) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOD_USART3_RX) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOD_UHF_IRQ) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOD_UHF_CS) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOD_LBAND_IRQ) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOD_LBAND_CS) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN15))
#define VAL_GPIOD_OSPEEDR           (PIN_OSPEED_HIGH(GPIOD_FIRE_HELI_1) |   \
                                     PIN_OSPEED_HIGH(GPIOD_FIRE_TURN_1) |   \
                                     PIN_OSPEED_HIGH(GPIOD_SDIO_CMD) |      \
                                     PIN_OSPEED_HIGH(GPIOD_TEST_HELI) |     \
                                     PIN_OSPEED_HIGH(GPIOD_UHF_ENABLE) |    \
                                     PIN_OSPEED_HIGH(GPIOD_OPD_ENABLE) |    \
                                     PIN_OSPEED_HIGH(GPIOD_TEST_TURN) |     \
                                     PIN_OSPEED_HIGH(GPIOD_UHF_FLT) |       \
                                     PIN_OSPEED_HIGH(GPIOD_USART3_TX) |     \
                                     PIN_OSPEED_HIGH(GPIOD_USART3_RX) |     \
                                     PIN_OSPEED_HIGH(GPIOD_UHF_IRQ) |       \
                                     PIN_OSPEED_HIGH(GPIOD_UHF_CS) |        \
                                     PIN_OSPEED_HIGH(GPIOD_LBAND_IRQ) |     \
                                     PIN_OSPEED_HIGH(GPIOD_LBAND_CS) |      \
                                     PIN_OSPEED_HIGH(GPIOD_PIN14) |         \
                                     PIN_OSPEED_HIGH(GPIOD_PIN15))
#define VAL_GPIOD_PUPDR             (PIN_PUPDR_FLOATING(GPIOD_FIRE_HELI_1) |\
                                     PIN_PUPDR_FLOATING(GPIOD_FIRE_TURN_1) |\
                                     PIN_PUPDR_FLOATING(GPIOD_SDIO_CMD) |   \
                                     PIN_PUPDR_FLOATING(GPIOD_TEST_HELI) |  \
                                     PIN_PUPDR_FLOATING(GPIOD_UHF_ENABLE) | \
                                     PIN_PUPDR_FLOATING(GPIOD_OPD_ENABLE) | \
                                     PIN_PUPDR_FLOATING(GPIOD_TEST_TURN) |  \
                                     PIN_PUPDR_FLOATING(GPIOD_UHF_FLT) |    \
                                     PIN_PUPDR_FLOATING(GPIOD_USART3_TX) |  \
                                     PIN_PUPDR_FLOATING(GPIOD_USART3_RX) |  \
                                     PIN_PUPDR_FLOATING(GPIOD_UHF_IRQ) |    \
                                     PIN_PUPDR_FLOATING(GPIOD_UHF_CS) |     \
                                     PIN_PUPDR_FLOATING(GPIOD_LBAND_IRQ) |  \
                                     PIN_PUPDR_FLOATING(GPIOD_LBAND_CS) |   \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN14) |      \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN15))
#define VAL_GPIOD_ODR               (PIN_ODR_LOW(GPIOD_FIRE_HELI_1) |       \
                                     PIN_ODR_LOW(GPIOD_FIRE_TURN_1) |       \
                                     PIN_ODR_HIGH(GPIOD_SDIO_CMD) |         \
                                     PIN_ODR_HIGH(GPIOD_TEST_HELI) |        \
                                     PIN_ODR_HIGH(GPIOD_UHF_ENABLE) |       \
                                     PIN_ODR_HIGH(GPIOD_OPD_ENABLE) |       \
                                     PIN_ODR_HIGH(GPIOD_TEST_TURN) |        \
                                     PIN_ODR_HIGH(GPIOD_UHF_FLT) |          \
                                     PIN_ODR_HIGH(GPIOD_USART3_TX) |        \
                                     PIN_ODR_HIGH(GPIOD_USART3_RX) |        \
                                     PIN_ODR_HIGH(GPIOD_UHF_IRQ) |          \
                                     PIN_ODR_HIGH(GPIOD_UHF_CS) |           \
                                     PIN_ODR_HIGH(GPIOD_LBAND_IRQ) |        \
                                     PIN_ODR_HIGH(GPIOD_LBAND_CS) |         \
                                     PIN_ODR_HIGH(GPIOD_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOD_PIN15))
#define VAL_GPIOD_AFRL              (PIN_AFIO_AF(GPIOD_FIRE_HELI_1, 0U) |   \
                                     PIN_AFIO_AF(GPIOD_FIRE_TURN_1, 0U) |   \
                                     PIN_AFIO_AF(GPIOD_SDIO_CMD, 12U) |     \
                                     PIN_AFIO_AF(GPIOD_TEST_HELI, 0U) |     \
                                     PIN_AFIO_AF(GPIOD_UHF_ENABLE, 0U) |    \
                                     PIN_AFIO_AF(GPIOD_OPD_ENABLE, 0U) |    \
                                     PIN_AFIO_AF(GPIOD_TEST_TURN, 0U) |     \
                                     PIN_AFIO_AF(GPIOD_UHF_FLT, 0U))
#define VAL_GPIOD_AFRH              (PIN_AFIO_AF(GPIOD_USART3_TX, 7U) |     \
                                     PIN_AFIO_AF(GPIOD_USART3_RX, 7U) |     \
                                     PIN_AFIO_AF(GPIOD_UHF_IRQ, 0U) |       \
                                     PIN_AFIO_AF(GPIOD_UHF_CS, 0U) |        \
                                     PIN_AFIO_AF(GPIOD_LBAND_IRQ, 0U) |     \
                                     PIN_AFIO_AF(GPIOD_LBAND_CS, 0U) |      \
                                     PIN_AFIO_AF(GPIOD_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOD_PIN15, 0U))

/*
 * GPIOE setup:
 *
 * PE0  - OPD_FAULT                 (input).
 * PE1  - WDT                       (output pushpull).
 * PE2  - FIRE_TURN_2               (output pushpull).
 * PE3  - FIRE_HELI_2               (output pushpull).
 * PE4  - PIN4                      (analog).
 * PE5  - PIN5                      (analog).
 * PE6  - PIN6                      (analog).
 * PE7  - MMC_PWR                   (output pushpull).
 * PE8  - PIN8                      (analog).
 * PE9  - PIN9                      (analog).
 * PE10 - PIN10                     (analog).
 * PE11 - TOT_OUT                   (input).
 * PE12 - PIN12                     (analog).
 * PE13 - LNA_ENABLE                (output pushpull).
 * PE14 - PA_ENABLE                 (output pushpull).
 * PE15 - TOT_CLEAR                 (output pushpull).
 */
#define VAL_GPIOE_MODER             (PIN_MODE_INPUT(GPIOE_OPD_FAULT) |      \
                                     PIN_MODE_OUTPUT(GPIOE_WDT) |           \
                                     PIN_MODE_OUTPUT(GPIOE_FIRE_TURN_2) |   \
                                     PIN_MODE_OUTPUT(GPIOE_FIRE_HELI_2) |   \
                                     PIN_MODE_ANALOG(GPIOE_PIN4) |          \
                                     PIN_MODE_ANALOG(GPIOE_PIN5) |          \
                                     PIN_MODE_ANALOG(GPIOE_PIN6) |          \
                                     PIN_MODE_OUTPUT(GPIOE_MMC_PWR) |       \
                                     PIN_MODE_ANALOG(GPIOE_PIN8) |          \
                                     PIN_MODE_ANALOG(GPIOE_PIN9) |          \
                                     PIN_MODE_ANALOG(GPIOE_PIN10) |         \
                                     PIN_MODE_INPUT(GPIOE_TOT_OUT) |        \
                                     PIN_MODE_ANALOG(GPIOE_PIN12) |         \
                                     PIN_MODE_OUTPUT(GPIOE_LNA_ENABLE) |    \
                                     PIN_MODE_OUTPUT(GPIOE_PA_ENABLE) |     \
                                     PIN_MODE_OUTPUT(GPIOE_TOT_CLEAR))
#define VAL_GPIOE_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOE_OPD_FAULT) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOE_WDT) |        \
                                     PIN_OTYPE_PUSHPULL(GPIOE_FIRE_TURN_2) |\
                                     PIN_OTYPE_PUSHPULL(GPIOE_FIRE_HELI_2) |\
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_MMC_PWR) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_TOT_OUT) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_LNA_ENABLE) | \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PA_ENABLE) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOE_TOT_CLEAR))
#define VAL_GPIOE_OSPEEDR           (PIN_OSPEED_HIGH(GPIOE_OPD_FAULT) |     \
                                     PIN_OSPEED_HIGH(GPIOE_WDT) |           \
                                     PIN_OSPEED_HIGH(GPIOE_FIRE_TURN_2) |   \
                                     PIN_OSPEED_HIGH(GPIOE_FIRE_HELI_2) |   \
                                     PIN_OSPEED_HIGH(GPIOE_PIN4) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN5) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN6) |          \
                                     PIN_OSPEED_HIGH(GPIOE_MMC_PWR) |       \
                                     PIN_OSPEED_HIGH(GPIOE_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN9) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN10) |         \
                                     PIN_OSPEED_HIGH(GPIOE_TOT_OUT) |       \
                                     PIN_OSPEED_HIGH(GPIOE_PIN12) |         \
                                     PIN_OSPEED_HIGH(GPIOE_LNA_ENABLE) |    \
                                     PIN_OSPEED_HIGH(GPIOE_PA_ENABLE) |     \
                                     PIN_OSPEED_HIGH(GPIOE_TOT_CLEAR))
#define VAL_GPIOE_PUPDR             (PIN_PUPDR_FLOATING(GPIOE_OPD_FAULT) |  \
                                     PIN_PUPDR_FLOATING(GPIOE_WDT) |        \
                                     PIN_PUPDR_FLOATING(GPIOE_FIRE_TURN_2) |\
                                     PIN_PUPDR_FLOATING(GPIOE_FIRE_HELI_2) |\
                                     PIN_PUPDR_FLOATING(GPIOE_PIN4) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN5) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN6) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_MMC_PWR) |    \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN8) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN9) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN10) |      \
                                     PIN_PUPDR_FLOATING(GPIOE_TOT_OUT) |    \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN12) |      \
                                     PIN_PUPDR_FLOATING(GPIOE_LNA_ENABLE) | \
                                     PIN_PUPDR_FLOATING(GPIOE_PA_ENABLE) |  \
                                     PIN_PUPDR_FLOATING(GPIOE_TOT_CLEAR))
#define VAL_GPIOE_ODR               (PIN_ODR_HIGH(GPIOE_OPD_FAULT) |        \
                                     PIN_ODR_LOW(GPIOE_WDT) |               \
                                     PIN_ODR_LOW(GPIOE_FIRE_TURN_2) |       \
                                     PIN_ODR_LOW(GPIOE_FIRE_HELI_2) |       \
                                     PIN_ODR_HIGH(GPIOE_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOE_MMC_PWR) |          \
                                     PIN_ODR_HIGH(GPIOE_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOE_TOT_OUT) |          \
                                     PIN_ODR_HIGH(GPIOE_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOE_LNA_ENABLE) |       \
                                     PIN_ODR_LOW(GPIOE_PA_ENABLE) |         \
                                     PIN_ODR_LOW(GPIOE_TOT_CLEAR))
#define VAL_GPIOE_AFRL              (PIN_AFIO_AF(GPIOE_OPD_FAULT, 0U) |     \
                                     PIN_AFIO_AF(GPIOE_WDT, 0U) |           \
                                     PIN_AFIO_AF(GPIOE_FIRE_TURN_2, 0U) |   \
                                     PIN_AFIO_AF(GPIOE_FIRE_HELI_2, 0U) |   \
                                     PIN_AFIO_AF(GPIOE_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_MMC_PWR, 0U))
#define VAL_GPIOE_AFRH              (PIN_AFIO_AF(GPIOE_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOE_TOT_OUT, 0U) |       \
                                     PIN_AFIO_AF(GPIOE_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOE_LNA_ENABLE, 0U) |    \
                                     PIN_AFIO_AF(GPIOE_PA_ENABLE, 0U) |     \
                                     PIN_AFIO_AF(GPIOE_TOT_CLEAR, 0U))

/*
 * GPIOF setup:
 *
 * PF0  - PIN0                      (analog).
 * PF1  - PIN1                      (analog).
 * PF2  - PIN2                      (analog).
 * PF3  - PIN3                      (analog).
 * PF4  - PIN4                      (analog).
 * PF5  - PIN5                      (analog).
 * PF6  - PIN6                      (analog).
 * PF7  - PIN7                      (analog).
 * PF8  - PIN8                      (analog).
 * PF9  - PIN9                      (analog).
 * PF10 - PIN10                     (analog).
 * PF11 - PIN11                     (analog).
 * PF12 - PIN12                     (analog).
 * PF13 - PIN13                     (analog).
 * PF14 - PIN14                     (analog).
 * PF15 - PIN15                     (analog).
 */
#define VAL_GPIOF_MODER             (PIN_MODE_ANALOG(GPIOF_PIN0) |          \
                                     PIN_MODE_ANALOG(GPIOF_PIN1) |          \
                                     PIN_MODE_ANALOG(GPIOF_PIN2) |          \
                                     PIN_MODE_ANALOG(GPIOF_PIN3) |          \
                                     PIN_MODE_ANALOG(GPIOF_PIN4) |          \
                                     PIN_MODE_ANALOG(GPIOF_PIN5) |          \
                                     PIN_MODE_ANALOG(GPIOF_PIN6) |          \
                                     PIN_MODE_ANALOG(GPIOF_PIN7) |          \
                                     PIN_MODE_ANALOG(GPIOF_PIN8) |          \
                                     PIN_MODE_ANALOG(GPIOF_PIN9) |          \
                                     PIN_MODE_ANALOG(GPIOF_PIN10) |         \
                                     PIN_MODE_ANALOG(GPIOF_PIN11) |         \
                                     PIN_MODE_ANALOG(GPIOF_PIN12) |         \
                                     PIN_MODE_ANALOG(GPIOF_PIN13) |         \
                                     PIN_MODE_ANALOG(GPIOF_PIN14) |         \
                                     PIN_MODE_ANALOG(GPIOF_PIN15))
#define VAL_GPIOF_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOF_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN15))
#define VAL_GPIOF_OSPEEDR           (PIN_OSPEED_HIGH(GPIOF_PIN0) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN1) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN2) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN3) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN4) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN5) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN6) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN7) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN9) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN10) |         \
                                     PIN_OSPEED_HIGH(GPIOF_PIN11) |         \
                                     PIN_OSPEED_HIGH(GPIOF_PIN12) |         \
                                     PIN_OSPEED_HIGH(GPIOF_PIN13) |         \
                                     PIN_OSPEED_HIGH(GPIOF_PIN14) |         \
                                     PIN_OSPEED_HIGH(GPIOF_PIN15))
#define VAL_GPIOF_PUPDR             (PIN_PUPDR_FLOATING(GPIOF_PIN0) |       \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN1) |       \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN2) |       \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN3) |       \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN4) |       \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN5) |       \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN6) |       \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN7) |       \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN8) |       \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN9) |       \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN10) |      \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN11) |      \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN12) |      \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN13) |      \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN14) |      \
                                     PIN_PUPDR_FLOATING(GPIOF_PIN15))
#define VAL_GPIOF_ODR               (PIN_ODR_HIGH(GPIOF_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN15))
#define VAL_GPIOF_AFRL              (PIN_AFIO_AF(GPIOF_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN7, 0U))
#define VAL_GPIOF_AFRH              (PIN_AFIO_AF(GPIOF_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOF_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOF_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOF_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOF_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOF_PIN15, 0U))

/*
 * GPIOG setup:
 *
 * PG0  - PIN0                      (analog).
 * PG1  - PIN1                      (analog).
 * PG2  - PIN2                      (analog).
 * PG3  - PIN3                      (analog).
 * PG4  - PIN4                      (analog).
 * PG5  - PIN5                      (analog).
 * PG6  - PIN6                      (analog).
 * PG7  - PIN7                      (analog).
 * PG8  - PIN8                      (analog).
 * PG9  - PIN9                      (analog).
 * PG10 - PIN10                     (analog).
 * PG11 - PIN11                     (analog).
 * PG12 - PIN12                     (analog).
 * PG13 - PIN13                     (analog).
 * PG14 - PIN14                     (analog).
 * PG15 - PIN15                     (analog).
 */
#define VAL_GPIOG_MODER             (PIN_MODE_ANALOG(GPIOG_PIN0) |          \
                                     PIN_MODE_ANALOG(GPIOG_PIN1) |          \
                                     PIN_MODE_ANALOG(GPIOG_PIN2) |          \
                                     PIN_MODE_ANALOG(GPIOG_PIN3) |          \
                                     PIN_MODE_ANALOG(GPIOG_PIN4) |          \
                                     PIN_MODE_ANALOG(GPIOG_PIN5) |          \
                                     PIN_MODE_ANALOG(GPIOG_PIN6) |          \
                                     PIN_MODE_ANALOG(GPIOG_PIN7) |          \
                                     PIN_MODE_ANALOG(GPIOG_PIN8) |          \
                                     PIN_MODE_ANALOG(GPIOG_PIN9) |          \
                                     PIN_MODE_ANALOG(GPIOG_PIN10) |         \
                                     PIN_MODE_ANALOG(GPIOG_PIN11) |         \
                                     PIN_MODE_ANALOG(GPIOG_PIN12) |         \
                                     PIN_MODE_ANALOG(GPIOG_PIN13) |         \
                                     PIN_MODE_ANALOG(GPIOG_PIN14) |         \
                                     PIN_MODE_ANALOG(GPIOG_PIN15))
#define VAL_GPIOG_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOG_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN15))
#define VAL_GPIOG_OSPEEDR           (PIN_OSPEED_HIGH(GPIOG_PIN0) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN1) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN2) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN3) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN4) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN5) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN6) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN7) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN9) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN10) |         \
                                     PIN_OSPEED_HIGH(GPIOG_PIN11) |         \
                                     PIN_OSPEED_HIGH(GPIOG_PIN12) |         \
                                     PIN_OSPEED_HIGH(GPIOG_PIN13) |         \
                                     PIN_OSPEED_HIGH(GPIOG_PIN14) |         \
                                     PIN_OSPEED_HIGH(GPIOG_PIN15))
#define VAL_GPIOG_PUPDR             (PIN_PUPDR_FLOATING(GPIOG_PIN0) |       \
                                     PIN_PUPDR_FLOATING(GPIOG_PIN1) |       \
                                     PIN_PUPDR_FLOATING(GPIOG_PIN2) |       \
                                     PIN_PUPDR_FLOATING(GPIOG_PIN3) |       \
                                     PIN_PUPDR_FLOATING(GPIOG_PIN4) |       \
                                     PIN_PUPDR_FLOATING(GPIOG_PIN5) |       \
                                     PIN_PUPDR_FLOATING(GPIOG_PIN6) |       \
                                     PIN_PUPDR_FLOATING(GPIOG_PIN7) |       \
                                     PIN_PUPDR_FLOATING(GPIOG_PIN8) |       \
                                     PIN_PUPDR_FLOATING(GPIOG_PIN9) |       \
                                     PIN_PUPDR_FLOATING(GPIOG_PIN10) |      \
                                     PIN_PUPDR_FLOATING(GPIOG_PIN11) |      \
                                     PIN_PUPDR_FLOATING(GPIOG_PIN12) |      \
                                     PIN_PUPDR_FLOATING(GPIOG_PIN13) |      \
                                     PIN_PUPDR_FLOATING(GPIOG_PIN14) |      \
                                     PIN_PUPDR_FLOATING(GPIOG_PIN15))
#define VAL_GPIOG_ODR               (PIN_ODR_HIGH(GPIOG_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOG_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOG_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOG_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOG_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOG_PIN15))
#define VAL_GPIOG_AFRL              (PIN_AFIO_AF(GPIOG_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN7, 0U))
#define VAL_GPIOG_AFRH              (PIN_AFIO_AF(GPIOG_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOG_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOG_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOG_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOG_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOG_PIN15, 0U))

/*
 * GPIOH setup:
 *
 * PH0  - OSC_IN                    (analog).
 * PH1  - OSC_OUT                   (analog).
 * PH2  - PIN2                      (analog).
 * PH3  - PIN3                      (analog).
 * PH4  - PIN4                      (analog).
 * PH5  - PIN5                      (analog).
 * PH6  - PIN6                      (analog).
 * PH7  - PIN7                      (analog).
 * PH8  - PIN8                      (analog).
 * PH9  - PIN9                      (analog).
 * PH10 - PIN10                     (analog).
 * PH11 - PIN11                     (analog).
 * PH12 - PIN12                     (analog).
 * PH13 - PIN13                     (analog).
 * PH14 - PIN14                     (analog).
 * PH15 - PIN15                     (analog).
 */
#define VAL_GPIOH_MODER             (PIN_MODE_ANALOG(GPIOH_OSC_IN) |        \
                                     PIN_MODE_ANALOG(GPIOH_OSC_OUT) |       \
                                     PIN_MODE_ANALOG(GPIOH_PIN2) |          \
                                     PIN_MODE_ANALOG(GPIOH_PIN3) |          \
                                     PIN_MODE_ANALOG(GPIOH_PIN4) |          \
                                     PIN_MODE_ANALOG(GPIOH_PIN5) |          \
                                     PIN_MODE_ANALOG(GPIOH_PIN6) |          \
                                     PIN_MODE_ANALOG(GPIOH_PIN7) |          \
                                     PIN_MODE_ANALOG(GPIOH_PIN8) |          \
                                     PIN_MODE_ANALOG(GPIOH_PIN9) |          \
                                     PIN_MODE_ANALOG(GPIOH_PIN10) |         \
                                     PIN_MODE_ANALOG(GPIOH_PIN11) |         \
                                     PIN_MODE_ANALOG(GPIOH_PIN12) |         \
                                     PIN_MODE_ANALOG(GPIOH_PIN13) |         \
                                     PIN_MODE_ANALOG(GPIOH_PIN14) |         \
                                     PIN_MODE_ANALOG(GPIOH_PIN15))
#define VAL_GPIOH_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOH_OSC_IN) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOH_OSC_OUT) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN15))
#define VAL_GPIOH_OSPEEDR           (PIN_OSPEED_HIGH(GPIOH_OSC_IN) |        \
                                     PIN_OSPEED_HIGH(GPIOH_OSC_OUT) |       \
                                     PIN_OSPEED_HIGH(GPIOH_PIN2) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN3) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN4) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN5) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN6) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN7) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN9) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN10) |         \
                                     PIN_OSPEED_HIGH(GPIOH_PIN11) |         \
                                     PIN_OSPEED_HIGH(GPIOH_PIN12) |         \
                                     PIN_OSPEED_HIGH(GPIOH_PIN13) |         \
                                     PIN_OSPEED_HIGH(GPIOH_PIN14) |         \
                                     PIN_OSPEED_HIGH(GPIOH_PIN15))
#define VAL_GPIOH_PUPDR             (PIN_PUPDR_FLOATING(GPIOH_OSC_IN) |     \
                                     PIN_PUPDR_FLOATING(GPIOH_OSC_OUT) |    \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN2) |       \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN3) |       \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN4) |       \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN5) |       \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN6) |       \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN7) |       \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN8) |       \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN9) |       \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN10) |      \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN11) |      \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN12) |      \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN13) |      \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN14) |      \
                                     PIN_PUPDR_FLOATING(GPIOH_PIN15))
#define VAL_GPIOH_ODR               (PIN_ODR_HIGH(GPIOH_OSC_IN) |           \
                                     PIN_ODR_HIGH(GPIOH_OSC_OUT) |          \
                                     PIN_ODR_HIGH(GPIOH_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN15))
#define VAL_GPIOH_AFRL              (PIN_AFIO_AF(GPIOH_OSC_IN, 0U) |        \
                                     PIN_AFIO_AF(GPIOH_OSC_OUT, 0U) |       \
                                     PIN_AFIO_AF(GPIOH_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN7, 0U))
#define VAL_GPIOH_AFRH              (PIN_AFIO_AF(GPIOH_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN15, 0U))

/*
 * GPIOI setup:
 *
 * PG0  - PIN0                      (analog).
 * PG1  - PIN1                      (analog).
 * PG2  - PIN2                      (analog).
 * PG3  - PIN3                      (analog).
 * PG4  - PIN4                      (analog).
 * PG5  - PIN5                      (analog).
 * PG6  - PIN6                      (analog).
 * PG7  - PIN7                      (analog).
 * PG8  - PIN8                      (analog).
 * PG9  - PIN9                      (analog).
 * PG10 - PIN10                     (analog).
 * PG11 - PIN11                     (analog).
 * PG12 - PIN12                     (analog).
 * PG13 - PIN13                     (analog).
 * PG14 - PIN14                     (analog).
 * PG15 - PIN15                     (analog).
 */
#define VAL_GPIOI_MODER             (PIN_MODE_ANALOG(GPIOI_PIN0) |          \
                                     PIN_MODE_ANALOG(GPIOI_PIN1) |          \
                                     PIN_MODE_ANALOG(GPIOI_PIN2) |          \
                                     PIN_MODE_ANALOG(GPIOI_PIN3) |          \
                                     PIN_MODE_ANALOG(GPIOI_PIN4) |          \
                                     PIN_MODE_ANALOG(GPIOI_PIN5) |          \
                                     PIN_MODE_ANALOG(GPIOI_PIN6) |          \
                                     PIN_MODE_ANALOG(GPIOI_PIN7) |          \
                                     PIN_MODE_ANALOG(GPIOI_PIN8) |          \
                                     PIN_MODE_ANALOG(GPIOI_PIN9) |          \
                                     PIN_MODE_ANALOG(GPIOI_PIN10) |         \
                                     PIN_MODE_ANALOG(GPIOI_PIN11) |         \
                                     PIN_MODE_ANALOG(GPIOI_PIN12) |         \
                                     PIN_MODE_ANALOG(GPIOI_PIN13) |         \
                                     PIN_MODE_ANALOG(GPIOI_PIN14) |         \
                                     PIN_MODE_ANALOG(GPIOI_PIN15))
#define VAL_GPIOI_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOI_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN15))
#define VAL_GPIOI_OSPEEDR           (PIN_OSPEED_HIGH(GPIOI_PIN0) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN1) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN2) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN3) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN4) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN5) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN6) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN7) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN9) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN10) |         \
                                     PIN_OSPEED_HIGH(GPIOI_PIN11) |         \
                                     PIN_OSPEED_HIGH(GPIOI_PIN12) |         \
                                     PIN_OSPEED_HIGH(GPIOI_PIN13) |         \
                                     PIN_OSPEED_HIGH(GPIOI_PIN14) |         \
                                     PIN_OSPEED_HIGH(GPIOI_PIN15))
#define VAL_GPIOI_PUPDR             (PIN_PUPDR_FLOATING(GPIOI_PIN0) |       \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN1) |       \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN2) |       \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN3) |       \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN4) |       \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN5) |       \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN6) |       \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN7) |       \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN8) |       \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN9) |       \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN10) |      \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN11) |      \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN12) |      \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN13) |      \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN14) |      \
                                     PIN_PUPDR_FLOATING(GPIOI_PIN15))
#define VAL_GPIOI_ODR               (PIN_ODR_HIGH(GPIOI_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN15))
#define VAL_GPIOI_AFRL              (PIN_AFIO_AF(GPIOI_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN7, 0U))
#define VAL_GPIOI_AFRH              (PIN_AFIO_AF(GPIOI_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN15, 0U))

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* BOARD_H */
