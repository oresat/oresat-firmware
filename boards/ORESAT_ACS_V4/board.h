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
 * ACS V4.x STM32L452CE Board Configuration
 * PART: STM32L452CEU3
 * PACKAGE: UFQFPN48
 */

/*
 * Board identifier.
 */
#define BOARD_ORESAT_ACS_V4
#define BOARD_NAME                  "OreSat ACS V4.x"

/*
 * Board oscillators-related settings.
 * NOTE: LSE not fitted.
 */
#if !defined(STM32_LSECLK)
#define STM32_LSECLK                0U
#endif

#define STM32_LSEDRV                (3U << 3U)

#if !defined(STM32_HSECLK)
#define STM32_HSECLK                16000000U
#endif

/*
 * MCU type as defined in the ST header.
 */
#define STM32L452xx

/*
 * IO pins assignments.
 */
#define GPIOA_MAG_CURR_FDB          0U
#define GPIOA_BLDC_CURR_FDB         1U
#define GPIOA_LPUART1_TX            2U
#define GPIOA_LPUART1_RX            3U
#define GPIOA_SPI1_NSS              4U
#define GPIOA_SPI1_SCK              5U
#define GPIOA_SPI1_MISO             6U
#define GPIOA_PIN7                  7U
#define GPIOA_BLDC_INUL             8U
#define GPIOA_TIM1_CH1              8U
#define GPIOA_BLDC_INVL             9U
#define GPIOA_TIM1_CH2              9U
#define GPIOA_BLDC_INWL             10U
#define GPIOA_TIM1_CH3              10U
#define GPIOA_BLDC_FAULT            11U
#define GPIOA_BLDC_EN               12U
#define GPIOA_SWDIO                 13U
#define GPIOA_SWCLK                 14U
#define GPIOA_MAG_PWM               15U

#define GPIOB_PIN0                  0U
#define GPIOB_DEBUG_2               1U
#define GPIOB_DEBUG_1               2U
#define GPIOB_MAG_DIR               3U
#define GPIOB_CAN_SILENT            4U
#define GPIOB_CAN1_RX               5U
#define GPIOB_CAN1_TX               6U
#define GPIOB_MAG_STBY              7U
#define GPIOB_MAG_FAULT             8U
#define GPIOB_MAG_EN                9U
#define GPIOB_I2C2_SCL              10U
#define GPIOB_I2C2_SDA              11U
#define GPIOB_BLDC_STBY             12U
#define GPIOB_BLDC_INUH             13U
#define GPIOB_TIM1_CH1N             13U
#define GPIOB_BLDC_INVH             14U
#define GPIOB_TIM1_CH2N             14U
#define GPIOB_BLDC_INWH             15U
#define GPIOB_TIM1_CH3N             15U

#define GPIOC_PIN0                  0U
#define GPIOC_PIN1                  1U
#define GPIOC_PIN2                  2U
#define GPIOC_PIN3                  3U
#define GPIOC_PIN4                  4U
#define GPIOC_PIN5                  5U
#define GPIOC_PIN6                  6U
#define GPIOC_PIN7                  7U
#define GPIOC_PIN8                  8U
#define GPIOC_PIN9                  9U
#define GPIOC_PIN10                 10U
#define GPIOC_PIN11                 11U
#define GPIOC_PIN12                 12U
#define GPIOC_PIN13                 13U
#define GPIOC_PIN14                 14U
#define GPIOC_PIN15                 15U

#define GPIOD_PIN0                  0U
#define GPIOD_PIN1                  1U
#define GPIOD_PIN2                  2U
#define GPIOD_PIN3                  3U
#define GPIOD_PIN4                  4U
#define GPIOD_PIN5                  5U
#define GPIOD_PIN6                  6U
#define GPIOD_PIN7                  7U
#define GPIOD_PIN8                  8U
#define GPIOD_PIN9                  9U
#define GPIOD_PIN10                 10U
#define GPIOD_PIN11                 11U
#define GPIOD_PIN12                 12U
#define GPIOD_PIN13                 13U
#define GPIOD_PIN14                 14U
#define GPIOD_PIN15                 15U

#define GPIOE_PIN0                  0U
#define GPIOE_PIN1                  1U
#define GPIOE_PIN2                  2U
#define GPIOE_PIN3                  3U
#define GPIOE_PIN4                  4U
#define GPIOE_PIN5                  5U
#define GPIOE_PIN6                  6U
#define GPIOE_PIN7                  7U
#define GPIOE_PIN8                  8U
#define GPIOE_PIN9                  9U
#define GPIOE_PIN10                 10U
#define GPIOE_PIN11                 11U
#define GPIOE_PIN12                 12U
#define GPIOE_PIN13                 13U
#define GPIOE_PIN14                 14U
#define GPIOE_PIN15                 15U

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
#define GPIOH_BOOT0                 3U
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

/*
 * IO lines assignments.
 */
#define LINE_SPI1_CS                PAL_LINE(GPIOA, 4U)
#define LINE_BLDC_EN                PAL_LINE(GPIOA, 12U)
#define LINE_DEBUG_2                PAL_LINE(GPIOB, 1U)
#define LINE_DEBUG_1                PAL_LINE(GPIOB, 2U)
#define LINE_MAG_DIR                PAL_LINE(GPIOB, 3U)
#define LINE_CAN_SILENT             PAL_LINE(GPIOB, 4U)
#define LINE_MAG_STBY               PAL_LINE(GPIOB, 7U)
#define LINE_MAG_EN                 PAL_LINE(GPIOB, 9U)
#define LINE_BLDC_STBY              PAL_LINE(GPIOB, 12U)

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
#define PIN_ASCR_DISABLED(n)        (0U << (n))
#define PIN_ASCR_ENABLED(n)         (1U << (n))
#define PIN_LOCKR_DISABLED(n)       (0U << (n))
#define PIN_LOCKR_ENABLED(n)        (1U << (n))

/*
 * GPIOA setup:
 *
 * PA0  - MAG_CURR_FDB              (analog).
 * PA1  - BLDC_CURR_FDB             (analog).
 * PA2  - LPUART1_TX                (alternate 8).
 * PA3  - LPUART1_RX                (alternate 8).
 * PA4  - SPI1_CS                   (output pushpull maximum).
 * PA5  - SPI1_SCK                  (alternate 5).
 * PA6  - SPI1_MISO                 (alternate 5).
 * PA7  - PIN7                      (analog).
 * PA8  - BLDC_INUL TIM1_CH1        (alternate 1).
 * PA9  - BLDC_INVL TIM1_CH2        (alternate 1).
 * PA10 - BLDC_INWL TIM1_CH3        (alternate 1).
 * PA11 - BLDC_FAULT                (analog).
 * PA12 - BLDC_EN                   (output pushpull maximum).
 * PA13 - SWDIO                     (alternate 0).
 * PA14 - SWCLK                     (alternate 0).
 * PA15 - MAG_PWM                   (analog).
 */
#define VAL_GPIOA_MODER             (PIN_MODE_ANALOG(GPIOA_MAG_CURR_FDB) |  \
                                     PIN_MODE_ANALOG(GPIOA_BLDC_CURR_FDB) | \
                                     PIN_MODE_ALTERNATE(GPIOA_LPUART1_TX) | \
                                     PIN_MODE_ALTERNATE(GPIOA_LPUART1_RX) | \
                                     PIN_MODE_OUTPUT(GPIOA_SPI1_NSS) |       \
                                     PIN_MODE_ALTERNATE(GPIOA_SPI1_SCK) |   \
                                     PIN_MODE_ALTERNATE(GPIOA_SPI1_MISO) |  \
                                     PIN_MODE_ANALOG(GPIOA_PIN7) |          \
                                     PIN_MODE_ALTERNATE(GPIOA_BLDC_INUL) |  \
                                     PIN_MODE_ALTERNATE(GPIOA_BLDC_INVL) |  \
                                     PIN_MODE_ALTERNATE(GPIOA_BLDC_INWL) |  \
                                     PIN_MODE_ANALOG(GPIOA_BLDC_FAULT) |    \
                                     PIN_MODE_OUTPUT(GPIOA_BLDC_EN) |       \
                                     PIN_MODE_ALTERNATE(GPIOA_SWDIO) |      \
                                     PIN_MODE_ALTERNATE(GPIOA_SWCLK) |      \
                                     PIN_MODE_ANALOG(GPIOA_MAG_PWM))
#define VAL_GPIOA_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOA_MAG_CURR_FDB) | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_BLDC_CURR_FDB) | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_LPUART1_TX) | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_LPUART1_RX) | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SPI1_NSS) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SPI1_SCK) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SPI1_MISO) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_BLDC_INUL) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_BLDC_INVL) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_BLDC_INWL) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_BLDC_FAULT) | \
                                     PIN_OTYPE_PUSHPULL(GPIOA_BLDC_EN) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWDIO) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWCLK) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_MAG_PWM))
#define VAL_GPIOA_OSPEEDR           (PIN_OSPEED_HIGH(GPIOA_MAG_CURR_FDB) |  \
                                     PIN_OSPEED_HIGH(GPIOA_BLDC_CURR_FDB) | \
                                     PIN_OSPEED_HIGH(GPIOA_LPUART1_TX) |    \
                                     PIN_OSPEED_HIGH(GPIOA_LPUART1_RX) |    \
                                     PIN_OSPEED_HIGH(GPIOA_SPI1_NSS) |       \
                                     PIN_OSPEED_HIGH(GPIOA_SPI1_SCK) |      \
                                     PIN_OSPEED_HIGH(GPIOA_SPI1_MISO) |     \
                                     PIN_OSPEED_HIGH(GPIOA_PIN7) |          \
                                     PIN_OSPEED_HIGH(GPIOA_BLDC_INUL) |     \
                                     PIN_OSPEED_HIGH(GPIOA_BLDC_INVL) |     \
                                     PIN_OSPEED_HIGH(GPIOA_BLDC_INWL) |     \
                                     PIN_OSPEED_HIGH(GPIOA_BLDC_FAULT) |    \
                                     PIN_OSPEED_HIGH(GPIOA_BLDC_EN) |       \
                                     PIN_OSPEED_HIGH(GPIOA_SWDIO) |         \
                                     PIN_OSPEED_HIGH(GPIOA_SWCLK) |         \
                                     PIN_OSPEED_HIGH(GPIOA_MAG_PWM))
#define VAL_GPIOA_PUPDR             (PIN_PUPDR_FLOATING(GPIOA_MAG_CURR_FDB) | \
                                     PIN_PUPDR_FLOATING(GPIOA_BLDC_CURR_FDB) | \
                                     PIN_PUPDR_FLOATING(GPIOA_LPUART1_TX) | \
                                     PIN_PUPDR_FLOATING(GPIOA_LPUART1_RX) | \
                                     PIN_PUPDR_PULLUP(GPIOA_SPI1_NSS) |    \
                                     PIN_PUPDR_PULLUP(GPIOA_SPI1_SCK) |   \
                                     PIN_PUPDR_PULLUP(GPIOA_SPI1_MISO) |  \
                                     PIN_PUPDR_FLOATING(GPIOA_PIN7) |       \
                                     PIN_PUPDR_FLOATING(GPIOA_BLDC_INUL) |  \
                                     PIN_PUPDR_FLOATING(GPIOA_BLDC_INVL) |  \
                                     PIN_PUPDR_FLOATING(GPIOA_BLDC_INWL) |  \
                                     PIN_PUPDR_FLOATING(GPIOA_BLDC_FAULT) | \
                                     PIN_PUPDR_PULLUP(GPIOA_BLDC_EN) |    \
                                     PIN_PUPDR_FLOATING(GPIOA_SWDIO) |      \
                                     PIN_PUPDR_FLOATING(GPIOA_SWCLK) |      \
                                     PIN_PUPDR_FLOATING(GPIOA_MAG_PWM))
#define VAL_GPIOA_ODR               (PIN_ODR_HIGH(GPIOA_MAG_CURR_FDB) |     \
                                     PIN_ODR_HIGH(GPIOA_BLDC_CURR_FDB) |    \
                                     PIN_ODR_HIGH(GPIOA_LPUART1_TX) |       \
                                     PIN_ODR_HIGH(GPIOA_LPUART1_RX) |       \
                                     PIN_ODR_HIGH(GPIOA_SPI1_NSS) |           \
                                     PIN_ODR_HIGH(GPIOA_SPI1_SCK) |         \
                                     PIN_ODR_HIGH(GPIOA_SPI1_MISO) |        \
                                     PIN_ODR_HIGH(GPIOA_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOA_BLDC_INUL) |        \
                                     PIN_ODR_HIGH(GPIOA_BLDC_INVL) |        \
                                     PIN_ODR_HIGH(GPIOA_BLDC_INWL) |        \
                                     PIN_ODR_HIGH(GPIOA_BLDC_FAULT) |       \
                                     PIN_ODR_HIGH(GPIOA_BLDC_EN) |           \
                                     PIN_ODR_HIGH(GPIOA_SWDIO) |            \
                                     PIN_ODR_HIGH(GPIOA_SWCLK) |            \
                                     PIN_ODR_HIGH(GPIOA_MAG_PWM))
#define VAL_GPIOA_AFRL              (PIN_AFIO_AF(GPIOA_MAG_CURR_FDB, 0U) |  \
                                     PIN_AFIO_AF(GPIOA_BLDC_CURR_FDB, 0U) | \
                                     PIN_AFIO_AF(GPIOA_LPUART1_TX, 8U) |    \
                                     PIN_AFIO_AF(GPIOA_LPUART1_RX, 8U) |    \
                                     PIN_AFIO_AF(GPIOA_SPI1_NSS, 5U) |       \
                                     PIN_AFIO_AF(GPIOA_SPI1_SCK, 5U) |      \
                                     PIN_AFIO_AF(GPIOA_SPI1_MISO, 5U) |     \
                                     PIN_AFIO_AF(GPIOA_PIN7, 0U))
#define VAL_GPIOA_AFRH              (PIN_AFIO_AF(GPIOA_BLDC_INUL, 1U) |     \
                                     PIN_AFIO_AF(GPIOA_BLDC_INVL, 1U) |     \
                                     PIN_AFIO_AF(GPIOA_BLDC_INWL, 1U) |     \
                                     PIN_AFIO_AF(GPIOA_BLDC_FAULT, 0U) |    \
                                     PIN_AFIO_AF(GPIOA_BLDC_EN, 0U) |       \
                                     PIN_AFIO_AF(GPIOA_SWDIO, 0U) |         \
                                     PIN_AFIO_AF(GPIOA_SWCLK, 0U) |         \
                                     PIN_AFIO_AF(GPIOA_MAG_PWM, 0U))
#define VAL_GPIOA_ASCR              (PIN_ASCR_DISABLED(GPIOA_MAG_CURR_FDB) | \
                                     PIN_ASCR_DISABLED(GPIOA_BLDC_CURR_FDB) |  \
                                     PIN_ASCR_DISABLED(GPIOA_LPUART1_TX) |  \
                                     PIN_ASCR_DISABLED(GPIOA_LPUART1_RX) |  \
                                     PIN_ASCR_DISABLED(GPIOA_SPI1_NSS) |     \
                                     PIN_ASCR_DISABLED(GPIOA_SPI1_SCK) |    \
                                     PIN_ASCR_DISABLED(GPIOA_SPI1_MISO) |   \
                                     PIN_ASCR_DISABLED(GPIOA_PIN7) |        \
                                     PIN_ASCR_DISABLED(GPIOA_BLDC_INUL) |   \
                                     PIN_ASCR_DISABLED(GPIOA_BLDC_INVL) |   \
                                     PIN_ASCR_DISABLED(GPIOA_BLDC_INWL) |   \
                                     PIN_ASCR_DISABLED(GPIOA_BLDC_FAULT) |  \
                                     PIN_ASCR_DISABLED(GPIOA_BLDC_EN) |     \
                                     PIN_ASCR_DISABLED(GPIOA_SWDIO) |       \
                                     PIN_ASCR_DISABLED(GPIOA_SWCLK) |       \
                                     PIN_ASCR_DISABLED(GPIOA_MAG_PWM))
#define VAL_GPIOA_LOCKR             (PIN_LOCKR_DISABLED(GPIOA_MAG_CURR_FDB) | \
                                     PIN_LOCKR_DISABLED(GPIOA_BLDC_CURR_FDB) | \
                                     PIN_LOCKR_DISABLED(GPIOA_LPUART1_TX) | \
                                     PIN_LOCKR_DISABLED(GPIOA_LPUART1_RX) | \
                                     PIN_LOCKR_DISABLED(GPIOA_SPI1_NSS) |    \
                                     PIN_LOCKR_DISABLED(GPIOA_SPI1_SCK) |   \
                                     PIN_LOCKR_DISABLED(GPIOA_SPI1_MISO) |  \
                                     PIN_LOCKR_DISABLED(GPIOA_PIN7) |       \
                                     PIN_LOCKR_DISABLED(GPIOA_BLDC_INUL) |  \
                                     PIN_LOCKR_DISABLED(GPIOA_BLDC_INVL) |  \
                                     PIN_LOCKR_DISABLED(GPIOA_BLDC_INWL) |  \
                                     PIN_LOCKR_DISABLED(GPIOA_BLDC_FAULT) | \
                                     PIN_LOCKR_DISABLED(GPIOA_BLDC_EN) |    \
                                     PIN_LOCKR_DISABLED(GPIOA_SWDIO) |      \
                                     PIN_LOCKR_DISABLED(GPIOA_SWCLK) |      \
                                     PIN_LOCKR_DISABLED(GPIOA_MAG_PWM))

/*
 * GPIOB setup:
 *
 * PB0  - PIN0                      (analog).
 * PB1  - DEBUG_2                   (output pushpull maximum).
 * PB2  - DEBUG_1                   (output pushpull maximum).
 * PB3  - MAG_DIR                   (output pushpull maximum).
 * PB4  - CAN_SILENT                (output pushpull maximum).
 * PB5  - CAN1_RX                   (alternate 3).
 * PB6  - CAN1_TX                   (alternate 8).
 * PB7  - MAG_STBY                  (output pushpull maximum).
 * PB8  - MAG_FAULT                 (analog).
 * PB9  - MAG_EN                    (output pushpull maximum).
 * PB10 - I2C2_SCL                  (altenrate 4).
 * PB11 - I2C2_SDA                  (altenrate 4).
 * PB12 - BLDC_STBY                 (output pushpull maximum).
 * PB13 - BLDC_INUH TIM1_CH1N       (alternate 1).
 * PB14 - BLDC_INVH TIM1_CH2N       (alternate 1).
 * PB15 - BLDC_INWH TIM1_CH3N       (alternate 1).
 */
#define VAL_GPIOB_MODER             (PIN_MODE_ANALOG(GPIOB_PIN0) |          \
                                     PIN_MODE_OUTPUT(GPIOB_DEBUG_2) |       \
                                     PIN_MODE_OUTPUT(GPIOB_DEBUG_1) |       \
                                     PIN_MODE_OUTPUT(GPIOB_MAG_DIR) |       \
                                     PIN_MODE_OUTPUT(GPIOB_CAN_SILENT) |    \
                                     PIN_MODE_ALTERNATE(GPIOB_CAN1_RX) |    \
                                     PIN_MODE_ALTERNATE(GPIOB_CAN1_TX) |    \
                                     PIN_MODE_OUTPUT(GPIOB_MAG_STBY) |      \
                                     PIN_MODE_ANALOG(GPIOB_MAG_FAULT) |     \
                                     PIN_MODE_OUTPUT(GPIOB_MAG_EN) |        \
                                     PIN_MODE_ALTERNATE(GPIOB_I2C2_SCL) |   \
                                     PIN_MODE_ALTERNATE(GPIOB_I2C2_SDA) |   \
                                     PIN_MODE_OUTPUT(GPIOB_BLDC_STBY) |     \
                                     PIN_MODE_ALTERNATE(GPIOB_BLDC_INUH) |  \
                                     PIN_MODE_ALTERNATE(GPIOB_BLDC_INVH) |  \
                                     PIN_MODE_ALTERNATE(GPIOB_BLDC_INWH))
#define VAL_GPIOB_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOB_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_DEBUG_2) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOB_DEBUG_1) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOB_MAG_DIR) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOB_CAN_SILENT) | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_CAN1_RX) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOB_CAN1_TX) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOB_MAG_STBY) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOB_MAG_FAULT) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOB_MAG_EN) |     \
                                     PIN_OTYPE_OPENDRAIN(GPIOB_I2C2_SCL) |  \
                                     PIN_OTYPE_OPENDRAIN(GPIOB_I2C2_SDA) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOB_BLDC_INUH) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOB_BLDC_STBY) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOB_BLDC_INVH) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOB_BLDC_INWH))
#define VAL_GPIOB_OSPEEDR           (PIN_OSPEED_HIGH(GPIOB_PIN0) |          \
                                     PIN_OSPEED_HIGH(GPIOB_DEBUG_2) |       \
                                     PIN_OSPEED_HIGH(GPIOB_DEBUG_1) |       \
                                     PIN_OSPEED_HIGH(GPIOB_MAG_DIR) |       \
                                     PIN_OSPEED_HIGH(GPIOB_CAN_SILENT) |    \
                                     PIN_OSPEED_HIGH(GPIOB_CAN1_RX) |       \
                                     PIN_OSPEED_HIGH(GPIOB_CAN1_TX) |       \
                                     PIN_OSPEED_HIGH(GPIOB_MAG_STBY) |      \
                                     PIN_OSPEED_HIGH(GPIOB_MAG_FAULT) |     \
                                     PIN_OSPEED_HIGH(GPIOB_MAG_EN) |        \
                                     PIN_OSPEED_HIGH(GPIOB_I2C2_SCL) |      \
                                     PIN_OSPEED_HIGH(GPIOB_I2C2_SDA) |      \
                                     PIN_OSPEED_HIGH(GPIOB_BLDC_STBY) |     \
                                     PIN_OSPEED_HIGH(GPIOB_BLDC_INUH) |     \
                                     PIN_OSPEED_HIGH(GPIOB_BLDC_INVH) |     \
                                     PIN_OSPEED_HIGH(GPIOB_BLDC_INWH))
#define VAL_GPIOB_PUPDR             (PIN_PUPDR_FLOATING(GPIOB_PIN0) |       \
                                     PIN_PUPDR_FLOATING(GPIOB_DEBUG_2) |    \
                                     PIN_PUPDR_FLOATING(GPIOB_DEBUG_1) |    \
                                     PIN_PUPDR_FLOATING(GPIOB_MAG_DIR) |    \
                                     PIN_PUPDR_FLOATING(GPIOB_CAN_SILENT) | \
                                     PIN_PUPDR_FLOATING(GPIOB_CAN1_RX) |    \
                                     PIN_PUPDR_FLOATING(GPIOB_CAN1_TX) |    \
                                     PIN_PUPDR_FLOATING(GPIOB_MAG_STBY) |   \
                                     PIN_PUPDR_FLOATING(GPIOB_MAG_FAULT) |  \
                                     PIN_PUPDR_FLOATING(GPIOB_MAG_EN) |     \
                                     PIN_PUPDR_PULLUP(GPIOB_I2C2_SCL) |     \
                                     PIN_PUPDR_PULLUP(GPIOB_I2C2_SDA) |     \
                                     PIN_PUPDR_FLOATING(GPIOB_BLDC_STBY) |  \
                                     PIN_PUPDR_FLOATING(GPIOB_BLDC_INUH) |  \
                                     PIN_PUPDR_FLOATING(GPIOB_BLDC_INVH) |  \
                                     PIN_PUPDR_FLOATING(GPIOB_BLDC_INWH))
#define VAL_GPIOB_ODR               (PIN_ODR_HIGH(GPIOB_PIN0) |             \
                                     PIN_ODR_LOW(GPIOB_DEBUG_2) |           \
                                     PIN_ODR_LOW(GPIOB_DEBUG_1) |           \
                                     PIN_ODR_LOW(GPIOB_MAG_DIR) |           \
                                     PIN_ODR_LOW(GPIOB_CAN_SILENT) |        \
                                     PIN_ODR_HIGH(GPIOB_CAN1_RX) |          \
                                     PIN_ODR_HIGH(GPIOB_CAN1_TX) |          \
                                     PIN_ODR_LOW(GPIOB_MAG_STBY) |          \
                                     PIN_ODR_HIGH(GPIOB_MAG_FAULT) |        \
                                     PIN_ODR_LOW(GPIOB_MAG_EN) |            \
                                     PIN_ODR_HIGH(GPIOB_I2C2_SCL) |         \
                                     PIN_ODR_HIGH(GPIOB_I2C2_SDA) |         \
                                     PIN_ODR_LOW(GPIOB_BLDC_STBY) |         \
                                     PIN_ODR_HIGH(GPIOB_BLDC_INUH) |        \
                                     PIN_ODR_HIGH(GPIOB_BLDC_INVH) |        \
                                     PIN_ODR_HIGH(GPIOB_BLDC_INWH))
#define VAL_GPIOB_AFRL              (PIN_AFIO_AF(GPIOB_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOB_DEBUG_2, 0U) |       \
                                     PIN_AFIO_AF(GPIOB_DEBUG_2, 0U) |       \
                                     PIN_AFIO_AF(GPIOB_MAG_DIR, 0U) |       \
                                     PIN_AFIO_AF(GPIOB_CAN_SILENT, 0U) |    \
                                     PIN_AFIO_AF(GPIOB_CAN1_RX, 0U) |       \
                                     PIN_AFIO_AF(GPIOB_CAN1_TX, 0U) |       \
                                     PIN_AFIO_AF(GPIOB_MAG_STBY, 0U))
#define VAL_GPIOB_AFRH              (PIN_AFIO_AF(GPIOB_MAG_FAULT, 0U) |     \
                                     PIN_AFIO_AF(GPIOB_MAG_EN, 0U) |        \
                                     PIN_AFIO_AF(GPIOB_I2C2_SCL, 4U) |      \
                                     PIN_AFIO_AF(GPIOB_I2C2_SDA, 4U) |      \
                                     PIN_AFIO_AF(GPIOB_BLDC_STBY, 0U) |     \
                                     PIN_AFIO_AF(GPIOB_BLDC_INUH, 1U) |     \
                                     PIN_AFIO_AF(GPIOB_BLDC_INVH, 1U) |     \
                                     PIN_AFIO_AF(GPIOB_BLDC_INWH, 1U))
#define VAL_GPIOB_ASCR              (PIN_ASCR_DISABLED(GPIOB_PIN0) |        \
                                     PIN_ASCR_DISABLED(GPIOB_DEBUG_2) |     \
                                     PIN_ASCR_DISABLED(GPIOB_DEBUG_1) |     \
                                     PIN_ASCR_DISABLED(GPIOB_MAG_DIR) |     \
                                     PIN_ASCR_DISABLED(GPIOB_CAN_SILENT) |  \
                                     PIN_ASCR_DISABLED(GPIOB_CAN1_RX) |     \
                                     PIN_ASCR_DISABLED(GPIOB_CAN1_TX) |     \
                                     PIN_ASCR_DISABLED(GPIOB_MAG_STBY) |    \
                                     PIN_ASCR_DISABLED(GPIOB_MAG_FAULT) |   \
                                     PIN_ASCR_DISABLED(GPIOB_MAG_EN) |      \
                                     PIN_ASCR_DISABLED(GPIOB_I2C2_SCL) |    \
                                     PIN_ASCR_DISABLED(GPIOB_I2C2_SDA) |    \
                                     PIN_ASCR_DISABLED(GPIOB_BLDC_STBY) |   \
                                     PIN_ASCR_DISABLED(GPIOB_BLDC_INUH) |   \
                                     PIN_ASCR_DISABLED(GPIOB_BLDC_INVH) |   \
                                     PIN_ASCR_DISABLED(GPIOB_BLDC_INWH))
#define VAL_GPIOB_LOCKR             (PIN_LOCKR_DISABLED(GPIOB_PIN0) |       \
                                     PIN_LOCKR_DISABLED(GPIOB_DEBUG_2) |    \
                                     PIN_LOCKR_DISABLED(GPIOB_DEBUG_1) |    \
                                     PIN_LOCKR_DISABLED(GPIOB_MAG_DIR) |    \
                                     PIN_LOCKR_DISABLED(GPIOB_CAN_SILENT) | \
                                     PIN_LOCKR_DISABLED(GPIOB_CAN1_RX) |    \
                                     PIN_LOCKR_DISABLED(GPIOB_CAN1_TX) |    \
                                     PIN_LOCKR_DISABLED(GPIOB_MAG_STBY) |   \
                                     PIN_LOCKR_DISABLED(GPIOB_MAG_FAULT) |  \
                                     PIN_LOCKR_DISABLED(GPIOB_MAG_EN) |     \
                                     PIN_LOCKR_DISABLED(GPIOB_I2C2_SCL) |   \
                                     PIN_LOCKR_DISABLED(GPIOB_I2C2_SDA) |   \
                                     PIN_LOCKR_DISABLED(GPIOB_BLDC_STBY) |  \
                                     PIN_LOCKR_DISABLED(GPIOB_BLDC_INUH) |  \
                                     PIN_LOCKR_DISABLED(GPIOB_BLDC_INVH) |  \
                                     PIN_LOCKR_DISABLED(GPIOB_BLDC_INWH))

/*
 * GPIOC setup:
 *
 * PC0  - PIN0                      (analog).
 * PC1  - PIN1                      (analog).
 * PC2  - PIN2                      (analog).
 * PC3  - PIN3                      (analog).
 * PC4  - PIN4                      (analog).
 * PC5  - PIN5                      (analog).
 * PC6  - PIN6                      (analog).
 * PC7  - PIN7                      (analog).
 * PC8  - PIN8                      (analog).
 * PC9  - PIN9                      (analog).
 * PC10 - PIN10                     (analog).
 * PC11 - PIN11                     (analog).
 * PC12 - PIN12                     (analog).
 * PC13 - PIN13                     (analog).
 * PC14 - PIN14                     (analog).
 * PC15 - PIN15                     (analog).
 */
#define VAL_GPIOC_MODER             (PIN_MODE_ANALOG(GPIOC_PIN0) |          \
                                     PIN_MODE_ANALOG(GPIOC_PIN1) |          \
                                     PIN_MODE_ANALOG(GPIOC_PIN2) |          \
                                     PIN_MODE_ANALOG(GPIOC_PIN3) |          \
                                     PIN_MODE_ANALOG(GPIOC_PIN4) |          \
                                     PIN_MODE_ANALOG(GPIOC_PIN5) |          \
                                     PIN_MODE_ANALOG(GPIOC_PIN6) |          \
                                     PIN_MODE_ANALOG(GPIOC_PIN7) |          \
                                     PIN_MODE_ANALOG(GPIOC_PIN8) |          \
                                     PIN_MODE_ANALOG(GPIOC_PIN9) |          \
                                     PIN_MODE_ANALOG(GPIOC_PIN10) |         \
                                     PIN_MODE_ANALOG(GPIOC_PIN11) |         \
                                     PIN_MODE_ANALOG(GPIOC_PIN12) |         \
                                     PIN_MODE_ANALOG(GPIOC_PIN13) |         \
                                     PIN_MODE_ANALOG(GPIOC_PIN14) |         \
                                     PIN_MODE_ANALOG(GPIOC_PIN15))
#define VAL_GPIOC_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOC_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN15))
#define VAL_GPIOC_OSPEEDR           (PIN_OSPEED_HIGH(GPIOC_PIN0) |          \
                                     PIN_OSPEED_HIGH(GPIOC_PIN1) |          \
                                     PIN_OSPEED_HIGH(GPIOC_PIN2) |          \
                                     PIN_OSPEED_HIGH(GPIOC_PIN3) |          \
                                     PIN_OSPEED_HIGH(GPIOC_PIN4) |          \
                                     PIN_OSPEED_HIGH(GPIOC_PIN5) |          \
                                     PIN_OSPEED_HIGH(GPIOC_PIN6) |          \
                                     PIN_OSPEED_HIGH(GPIOC_PIN7) |          \
                                     PIN_OSPEED_HIGH(GPIOC_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOC_PIN9) |          \
                                     PIN_OSPEED_HIGH(GPIOC_PIN10) |         \
                                     PIN_OSPEED_HIGH(GPIOC_PIN11) |         \
                                     PIN_OSPEED_HIGH(GPIOC_PIN12) |         \
                                     PIN_OSPEED_HIGH(GPIOC_PIN13) |         \
                                     PIN_OSPEED_HIGH(GPIOC_PIN14) |         \
                                     PIN_OSPEED_HIGH(GPIOC_PIN15))
#define VAL_GPIOC_PUPDR             (PIN_PUPDR_FLOATING(GPIOC_PIN0) |       \
                                     PIN_PUPDR_FLOATING(GPIOC_PIN1) |       \
                                     PIN_PUPDR_FLOATING(GPIOC_PIN2) |       \
                                     PIN_PUPDR_FLOATING(GPIOC_PIN3) |       \
                                     PIN_PUPDR_FLOATING(GPIOC_PIN4) |       \
                                     PIN_PUPDR_FLOATING(GPIOC_PIN5) |       \
                                     PIN_PUPDR_FLOATING(GPIOC_PIN6) |       \
                                     PIN_PUPDR_FLOATING(GPIOC_PIN7) |       \
                                     PIN_PUPDR_FLOATING(GPIOC_PIN8) |       \
                                     PIN_PUPDR_FLOATING(GPIOC_PIN9) |       \
                                     PIN_PUPDR_FLOATING(GPIOC_PIN10) |      \
                                     PIN_PUPDR_FLOATING(GPIOC_PIN11) |      \
                                     PIN_PUPDR_FLOATING(GPIOC_PIN12) |      \
                                     PIN_PUPDR_FLOATING(GPIOC_PIN13) |      \
                                     PIN_PUPDR_FLOATING(GPIOC_PIN14) |      \
                                     PIN_PUPDR_FLOATING(GPIOC_PIN15))
#define VAL_GPIOC_ODR               (PIN_ODR_HIGH(GPIOC_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOC_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOC_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOC_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOC_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOC_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOC_PIN15))
#define VAL_GPIOC_AFRL              (PIN_AFIO_AF(GPIOC_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_PIN7, 0U))
#define VAL_GPIOC_AFRH              (PIN_AFIO_AF(GPIOC_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOC_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOC_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOC_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOC_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOC_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOC_PIN15, 0U))
#define VAL_GPIOC_ASCR              (PIN_ASCR_DISABLED(GPIOC_PIN0) |        \
                                     PIN_ASCR_DISABLED(GPIOC_PIN1) |        \
                                     PIN_ASCR_DISABLED(GPIOC_PIN2) |        \
                                     PIN_ASCR_DISABLED(GPIOC_PIN3) |        \
                                     PIN_ASCR_DISABLED(GPIOC_PIN4) |        \
                                     PIN_ASCR_DISABLED(GPIOC_PIN5) |        \
                                     PIN_ASCR_DISABLED(GPIOC_PIN6) |        \
                                     PIN_ASCR_DISABLED(GPIOC_PIN7) |        \
                                     PIN_ASCR_DISABLED(GPIOC_PIN8) |        \
                                     PIN_ASCR_DISABLED(GPIOC_PIN9) |        \
                                     PIN_ASCR_DISABLED(GPIOC_PIN10) |       \
                                     PIN_ASCR_DISABLED(GPIOC_PIN11) |       \
                                     PIN_ASCR_DISABLED(GPIOC_PIN12) |       \
                                     PIN_ASCR_DISABLED(GPIOC_PIN13) |       \
                                     PIN_ASCR_DISABLED(GPIOC_PIN14) |       \
                                     PIN_ASCR_DISABLED(GPIOC_PIN15))
#define VAL_GPIOC_LOCKR             (PIN_LOCKR_DISABLED(GPIOC_PIN0) |       \
                                     PIN_LOCKR_DISABLED(GPIOC_PIN1) |       \
                                     PIN_LOCKR_DISABLED(GPIOC_PIN2) |       \
                                     PIN_LOCKR_DISABLED(GPIOC_PIN3) |       \
                                     PIN_LOCKR_DISABLED(GPIOC_PIN4) |       \
                                     PIN_LOCKR_DISABLED(GPIOC_PIN5) |       \
                                     PIN_LOCKR_DISABLED(GPIOC_PIN6) |       \
                                     PIN_LOCKR_DISABLED(GPIOC_PIN7) |       \
                                     PIN_LOCKR_DISABLED(GPIOC_PIN8) |       \
                                     PIN_LOCKR_DISABLED(GPIOC_PIN9) |       \
                                     PIN_LOCKR_DISABLED(GPIOC_PIN10) |      \
                                     PIN_LOCKR_DISABLED(GPIOC_PIN11) |      \
                                     PIN_LOCKR_DISABLED(GPIOC_PIN12) |      \
                                     PIN_LOCKR_DISABLED(GPIOC_PIN13) |      \
                                     PIN_LOCKR_DISABLED(GPIOC_PIN14) |      \
                                     PIN_LOCKR_DISABLED(GPIOC_PIN15))

/*
 * GPIOD setup:
 *
 * PD0  - PIN0                      (analog).
 * PD1  - PIN1                      (analog).
 * PD2  - PIN2                      (analog).
 * PD3  - PIN3                      (analog).
 * PD4  - PIN4                      (analog).
 * PD5  - PIN5                      (analog).
 * PD6  - PIN6                      (analog).
 * PD7  - PIN7                      (analog).
 * PD8  - PIN8                      (analog).
 * PD9  - PIN9                      (analog).
 * PD10 - PIN10                     (analog).
 * PD11 - PIN11                     (analog).
 * PD12 - PIN12                     (analog).
 * PD13 - PIN13                     (analog).
 * PD14 - PIN14                     (analog).
 * PD15 - PIN15                     (analog).
 */
#define VAL_GPIOD_MODER             (PIN_MODE_ANALOG(GPIOD_PIN0) |          \
                                     PIN_MODE_ANALOG(GPIOD_PIN1) |          \
                                     PIN_MODE_ANALOG(GPIOD_PIN2) |          \
                                     PIN_MODE_ANALOG(GPIOD_PIN3) |          \
                                     PIN_MODE_ANALOG(GPIOD_PIN4) |          \
                                     PIN_MODE_ANALOG(GPIOD_PIN5) |          \
                                     PIN_MODE_ANALOG(GPIOD_PIN6) |          \
                                     PIN_MODE_ANALOG(GPIOD_PIN7) |          \
                                     PIN_MODE_ANALOG(GPIOD_PIN8) |          \
                                     PIN_MODE_ANALOG(GPIOD_PIN9) |          \
                                     PIN_MODE_ANALOG(GPIOD_PIN10) |         \
                                     PIN_MODE_ANALOG(GPIOD_PIN11) |         \
                                     PIN_MODE_ANALOG(GPIOD_PIN12) |         \
                                     PIN_MODE_ANALOG(GPIOD_PIN13) |         \
                                     PIN_MODE_ANALOG(GPIOD_PIN14) |         \
                                     PIN_MODE_ANALOG(GPIOD_PIN15))
#define VAL_GPIOD_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOD_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN15))
#define VAL_GPIOD_OSPEEDR           (PIN_OSPEED_HIGH(GPIOD_PIN0) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN1) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN2) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN3) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN4) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN5) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN6) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN7) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN9) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN10) |         \
                                     PIN_OSPEED_HIGH(GPIOD_PIN11) |         \
                                     PIN_OSPEED_HIGH(GPIOD_PIN12) |         \
                                     PIN_OSPEED_HIGH(GPIOD_PIN13) |         \
                                     PIN_OSPEED_HIGH(GPIOD_PIN14) |         \
                                     PIN_OSPEED_HIGH(GPIOD_PIN15))
#define VAL_GPIOD_PUPDR             (PIN_PUPDR_FLOATING(GPIOD_PIN0) |       \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN1) |       \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN2) |       \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN3) |       \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN4) |       \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN5) |       \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN6) |       \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN7) |       \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN8) |       \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN9) |       \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN10) |      \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN11) |      \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN12) |      \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN13) |      \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN14) |      \
                                     PIN_PUPDR_FLOATING(GPIOD_PIN15))
#define VAL_GPIOD_ODR               (PIN_ODR_HIGH(GPIOD_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOD_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOD_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOD_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOD_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOD_PIN15))
#define VAL_GPIOD_AFRL              (PIN_AFIO_AF(GPIOD_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN7, 0U))
#define VAL_GPIOD_AFRH              (PIN_AFIO_AF(GPIOD_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOD_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOD_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOD_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOD_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOD_PIN15, 0U))
#define VAL_GPIOD_ASCR              (PIN_ASCR_DISABLED(GPIOD_PIN0) |        \
                                     PIN_ASCR_DISABLED(GPIOD_PIN1) |        \
                                     PIN_ASCR_DISABLED(GPIOD_PIN2) |        \
                                     PIN_ASCR_DISABLED(GPIOD_PIN3) |        \
                                     PIN_ASCR_DISABLED(GPIOD_PIN4) |        \
                                     PIN_ASCR_DISABLED(GPIOD_PIN5) |        \
                                     PIN_ASCR_DISABLED(GPIOD_PIN6) |        \
                                     PIN_ASCR_DISABLED(GPIOD_PIN7) |        \
                                     PIN_ASCR_DISABLED(GPIOD_PIN8) |        \
                                     PIN_ASCR_DISABLED(GPIOD_PIN9) |        \
                                     PIN_ASCR_DISABLED(GPIOD_PIN10) |       \
                                     PIN_ASCR_DISABLED(GPIOD_PIN11) |       \
                                     PIN_ASCR_DISABLED(GPIOD_PIN12) |       \
                                     PIN_ASCR_DISABLED(GPIOD_PIN13) |       \
                                     PIN_ASCR_DISABLED(GPIOD_PIN14) |       \
                                     PIN_ASCR_DISABLED(GPIOD_PIN15))
#define VAL_GPIOD_LOCKR             (PIN_LOCKR_DISABLED(GPIOD_PIN0) |       \
                                     PIN_LOCKR_DISABLED(GPIOD_PIN1) |       \
                                     PIN_LOCKR_DISABLED(GPIOD_PIN2) |       \
                                     PIN_LOCKR_DISABLED(GPIOD_PIN3) |       \
                                     PIN_LOCKR_DISABLED(GPIOD_PIN4) |       \
                                     PIN_LOCKR_DISABLED(GPIOD_PIN5) |       \
                                     PIN_LOCKR_DISABLED(GPIOD_PIN6) |       \
                                     PIN_LOCKR_DISABLED(GPIOD_PIN7) |       \
                                     PIN_LOCKR_DISABLED(GPIOD_PIN8) |       \
                                     PIN_LOCKR_DISABLED(GPIOD_PIN9) |       \
                                     PIN_LOCKR_DISABLED(GPIOD_PIN10) |      \
                                     PIN_LOCKR_DISABLED(GPIOD_PIN11) |      \
                                     PIN_LOCKR_DISABLED(GPIOD_PIN12) |      \
                                     PIN_LOCKR_DISABLED(GPIOD_PIN13) |      \
                                     PIN_LOCKR_DISABLED(GPIOD_PIN14) |      \
                                     PIN_LOCKR_DISABLED(GPIOD_PIN15))

/*
 * GPIOE setup:
 *
 * PE0  - PIN0                      (analog).
 * PE1  - PIN1                      (analog).
 * PE2  - PIN2                      (analog).
 * PE3  - PIN3                      (analog).
 * PE4  - PIN4                      (analog).
 * PE5  - PIN5                      (analog).
 * PE6  - PIN6                      (analog).
 * PE7  - PIN7                      (analog).
 * PE8  - PIN8                      (analog).
 * PE9  - PIN9                      (analog).
 * PE10 - PIN10                     (analog).
 * PE11 - PIN11                     (analog).
 * PE12 - PIN12                     (analog).
 * PE13 - PIN13                     (analog).
 * PE14 - PIN14                     (analog).
 * PE15 - PIN15                     (analog).
 */
#define VAL_GPIOE_MODER             (PIN_MODE_ANALOG(GPIOE_PIN0) |          \
                                     PIN_MODE_ANALOG(GPIOE_PIN1) |          \
                                     PIN_MODE_ANALOG(GPIOE_PIN2) |          \
                                     PIN_MODE_ANALOG(GPIOE_PIN3) |          \
                                     PIN_MODE_ANALOG(GPIOE_PIN4) |          \
                                     PIN_MODE_ANALOG(GPIOE_PIN5) |          \
                                     PIN_MODE_ANALOG(GPIOE_PIN6) |          \
                                     PIN_MODE_ANALOG(GPIOE_PIN7) |          \
                                     PIN_MODE_ANALOG(GPIOE_PIN8) |          \
                                     PIN_MODE_ANALOG(GPIOE_PIN9) |          \
                                     PIN_MODE_ANALOG(GPIOE_PIN10) |         \
                                     PIN_MODE_ANALOG(GPIOE_PIN11) |         \
                                     PIN_MODE_ANALOG(GPIOE_PIN12) |         \
                                     PIN_MODE_ANALOG(GPIOE_PIN13) |         \
                                     PIN_MODE_ANALOG(GPIOE_PIN14) |         \
                                     PIN_MODE_ANALOG(GPIOE_PIN15))
#define VAL_GPIOE_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOE_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN15))
#define VAL_GPIOE_OSPEEDR           (PIN_OSPEED_HIGH(GPIOE_PIN0) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN1) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN2) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN3) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN4) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN5) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN6) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN7) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN9) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN10) |         \
                                     PIN_OSPEED_HIGH(GPIOE_PIN11) |         \
                                     PIN_OSPEED_HIGH(GPIOE_PIN12) |         \
                                     PIN_OSPEED_HIGH(GPIOE_PIN13) |         \
                                     PIN_OSPEED_HIGH(GPIOE_PIN14) |         \
                                     PIN_OSPEED_HIGH(GPIOE_PIN15))
#define VAL_GPIOE_PUPDR             (PIN_PUPDR_FLOATING(GPIOE_PIN0) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN1) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN2) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN3) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN4) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN5) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN6) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN7) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN8) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN9) |       \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN10) |      \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN11) |      \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN12) |      \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN13) |      \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN14) |      \
                                     PIN_PUPDR_FLOATING(GPIOE_PIN15))
#define VAL_GPIOE_ODR               (PIN_ODR_HIGH(GPIOE_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOE_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOE_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOE_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOE_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOE_PIN15))
#define VAL_GPIOE_AFRL              (PIN_AFIO_AF(GPIOE_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN7, 0U))
#define VAL_GPIOE_AFRH              (PIN_AFIO_AF(GPIOE_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOE_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOE_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOE_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOE_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOE_PIN15, 0U))
#define VAL_GPIOE_ASCR              (PIN_ASCR_DISABLED(GPIOE_PIN0) |        \
                                     PIN_ASCR_DISABLED(GPIOE_PIN1) |        \
                                     PIN_ASCR_DISABLED(GPIOE_PIN2) |        \
                                     PIN_ASCR_DISABLED(GPIOE_PIN3) |        \
                                     PIN_ASCR_DISABLED(GPIOE_PIN4) |        \
                                     PIN_ASCR_DISABLED(GPIOE_PIN5) |        \
                                     PIN_ASCR_DISABLED(GPIOE_PIN6) |        \
                                     PIN_ASCR_DISABLED(GPIOE_PIN7) |        \
                                     PIN_ASCR_DISABLED(GPIOE_PIN8) |        \
                                     PIN_ASCR_DISABLED(GPIOE_PIN9) |        \
                                     PIN_ASCR_DISABLED(GPIOE_PIN10) |       \
                                     PIN_ASCR_DISABLED(GPIOE_PIN11) |       \
                                     PIN_ASCR_DISABLED(GPIOE_PIN12) |       \
                                     PIN_ASCR_DISABLED(GPIOE_PIN13) |       \
                                     PIN_ASCR_DISABLED(GPIOE_PIN14) |       \
                                     PIN_ASCR_DISABLED(GPIOE_PIN15))
#define VAL_GPIOE_LOCKR             (PIN_LOCKR_DISABLED(GPIOE_PIN0) |       \
                                     PIN_LOCKR_DISABLED(GPIOE_PIN1) |       \
                                     PIN_LOCKR_DISABLED(GPIOE_PIN2) |       \
                                     PIN_LOCKR_DISABLED(GPIOE_PIN3) |       \
                                     PIN_LOCKR_DISABLED(GPIOE_PIN4) |       \
                                     PIN_LOCKR_DISABLED(GPIOE_PIN5) |       \
                                     PIN_LOCKR_DISABLED(GPIOE_PIN6) |       \
                                     PIN_LOCKR_DISABLED(GPIOE_PIN7) |       \
                                     PIN_LOCKR_DISABLED(GPIOE_PIN8) |       \
                                     PIN_LOCKR_DISABLED(GPIOE_PIN9) |       \
                                     PIN_LOCKR_DISABLED(GPIOE_PIN10) |      \
                                     PIN_LOCKR_DISABLED(GPIOE_PIN11) |      \
                                     PIN_LOCKR_DISABLED(GPIOE_PIN12) |      \
                                     PIN_LOCKR_DISABLED(GPIOE_PIN13) |      \
                                     PIN_LOCKR_DISABLED(GPIOE_PIN14) |      \
                                     PIN_LOCKR_DISABLED(GPIOE_PIN15))

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
#define VAL_GPIOF_ASCR              (PIN_ASCR_DISABLED(GPIOF_PIN0) |        \
                                     PIN_ASCR_DISABLED(GPIOF_PIN1) |        \
                                     PIN_ASCR_DISABLED(GPIOF_PIN2) |        \
                                     PIN_ASCR_DISABLED(GPIOF_PIN3) |        \
                                     PIN_ASCR_DISABLED(GPIOF_PIN4) |        \
                                     PIN_ASCR_DISABLED(GPIOF_PIN5) |        \
                                     PIN_ASCR_DISABLED(GPIOF_PIN6) |        \
                                     PIN_ASCR_DISABLED(GPIOF_PIN7) |        \
                                     PIN_ASCR_DISABLED(GPIOF_PIN8) |        \
                                     PIN_ASCR_DISABLED(GPIOF_PIN9) |        \
                                     PIN_ASCR_DISABLED(GPIOF_PIN10) |       \
                                     PIN_ASCR_DISABLED(GPIOF_PIN11) |       \
                                     PIN_ASCR_DISABLED(GPIOF_PIN12) |       \
                                     PIN_ASCR_DISABLED(GPIOF_PIN13) |       \
                                     PIN_ASCR_DISABLED(GPIOF_PIN14) |       \
                                     PIN_ASCR_DISABLED(GPIOF_PIN15))
#define VAL_GPIOF_LOCKR             (PIN_LOCKR_DISABLED(GPIOF_PIN0) |       \
                                     PIN_LOCKR_DISABLED(GPIOF_PIN1) |       \
                                     PIN_LOCKR_DISABLED(GPIOF_PIN2) |       \
                                     PIN_LOCKR_DISABLED(GPIOF_PIN3) |       \
                                     PIN_LOCKR_DISABLED(GPIOF_PIN4) |       \
                                     PIN_LOCKR_DISABLED(GPIOF_PIN5) |       \
                                     PIN_LOCKR_DISABLED(GPIOF_PIN6) |       \
                                     PIN_LOCKR_DISABLED(GPIOF_PIN7) |       \
                                     PIN_LOCKR_DISABLED(GPIOF_PIN8) |       \
                                     PIN_LOCKR_DISABLED(GPIOF_PIN9) |       \
                                     PIN_LOCKR_DISABLED(GPIOF_PIN10) |      \
                                     PIN_LOCKR_DISABLED(GPIOF_PIN11) |      \
                                     PIN_LOCKR_DISABLED(GPIOF_PIN12) |      \
                                     PIN_LOCKR_DISABLED(GPIOF_PIN13) |      \
                                     PIN_LOCKR_DISABLED(GPIOF_PIN14) |      \
                                     PIN_LOCKR_DISABLED(GPIOF_PIN15))

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
#define VAL_GPIOG_ASCR              (PIN_ASCR_DISABLED(GPIOG_PIN0) |        \
                                     PIN_ASCR_DISABLED(GPIOG_PIN1) |        \
                                     PIN_ASCR_DISABLED(GPIOG_PIN2) |        \
                                     PIN_ASCR_DISABLED(GPIOG_PIN3) |        \
                                     PIN_ASCR_DISABLED(GPIOG_PIN4) |        \
                                     PIN_ASCR_DISABLED(GPIOG_PIN5) |        \
                                     PIN_ASCR_DISABLED(GPIOG_PIN6) |        \
                                     PIN_ASCR_DISABLED(GPIOG_PIN7) |        \
                                     PIN_ASCR_DISABLED(GPIOG_PIN8) |        \
                                     PIN_ASCR_DISABLED(GPIOG_PIN9) |        \
                                     PIN_ASCR_DISABLED(GPIOG_PIN10) |       \
                                     PIN_ASCR_DISABLED(GPIOG_PIN11) |       \
                                     PIN_ASCR_DISABLED(GPIOG_PIN12) |       \
                                     PIN_ASCR_DISABLED(GPIOG_PIN13) |       \
                                     PIN_ASCR_DISABLED(GPIOG_PIN14) |       \
                                     PIN_ASCR_DISABLED(GPIOG_PIN15))
#define VAL_GPIOG_LOCKR             (PIN_LOCKR_DISABLED(GPIOG_PIN0) |       \
                                     PIN_LOCKR_DISABLED(GPIOG_PIN1) |       \
                                     PIN_LOCKR_DISABLED(GPIOG_PIN2) |       \
                                     PIN_LOCKR_DISABLED(GPIOG_PIN3) |       \
                                     PIN_LOCKR_DISABLED(GPIOG_PIN4) |       \
                                     PIN_LOCKR_DISABLED(GPIOG_PIN5) |       \
                                     PIN_LOCKR_DISABLED(GPIOG_PIN6) |       \
                                     PIN_LOCKR_DISABLED(GPIOG_PIN7) |       \
                                     PIN_LOCKR_DISABLED(GPIOG_PIN8) |       \
                                     PIN_LOCKR_DISABLED(GPIOG_PIN9) |       \
                                     PIN_LOCKR_DISABLED(GPIOG_PIN10) |      \
                                     PIN_LOCKR_DISABLED(GPIOG_PIN11) |      \
                                     PIN_LOCKR_DISABLED(GPIOG_PIN12) |      \
                                     PIN_LOCKR_DISABLED(GPIOG_PIN13) |      \
                                     PIN_LOCKR_DISABLED(GPIOG_PIN14) |      \
                                     PIN_LOCKR_DISABLED(GPIOG_PIN15))

/*
 * GPIOH setup:
 *
 * PH0  - OSC_IN                    (analog).
 * PH1  - OSC_OUT                   (analog).
 * PH2  - PIN2                      (analog).
 * PH3  - BOOT0                     (analog).
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
                                     PIN_MODE_ANALOG(GPIOH_BOOT0) |         \
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
                                     PIN_OTYPE_PUSHPULL(GPIOH_BOOT0) |      \
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
                                     PIN_OSPEED_HIGH(GPIOH_BOOT0) |         \
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
                                     PIN_PUPDR_FLOATING(GPIOH_BOOT0) |      \
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
                                     PIN_ODR_HIGH(GPIOH_BOOT0) |            \
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
                                     PIN_AFIO_AF(GPIOH_BOOT0, 0U) |         \
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
#define VAL_GPIOH_ASCR              (PIN_ASCR_DISABLED(GPIOH_OSC_IN) |      \
                                     PIN_ASCR_DISABLED(GPIOH_OSC_OUT) |     \
                                     PIN_ASCR_DISABLED(GPIOH_PIN2) |        \
                                     PIN_ASCR_DISABLED(GPIOH_BOOT0) |       \
                                     PIN_ASCR_DISABLED(GPIOH_PIN4) |        \
                                     PIN_ASCR_DISABLED(GPIOH_PIN5) |        \
                                     PIN_ASCR_DISABLED(GPIOH_PIN6) |        \
                                     PIN_ASCR_DISABLED(GPIOH_PIN7) |        \
                                     PIN_ASCR_DISABLED(GPIOH_PIN8) |        \
                                     PIN_ASCR_DISABLED(GPIOH_PIN9) |        \
                                     PIN_ASCR_DISABLED(GPIOH_PIN10) |       \
                                     PIN_ASCR_DISABLED(GPIOH_PIN11) |       \
                                     PIN_ASCR_DISABLED(GPIOH_PIN12) |       \
                                     PIN_ASCR_DISABLED(GPIOH_PIN13) |       \
                                     PIN_ASCR_DISABLED(GPIOH_PIN14) |       \
                                     PIN_ASCR_DISABLED(GPIOH_PIN15))
#define VAL_GPIOH_LOCKR             (PIN_LOCKR_DISABLED(GPIOH_OSC_IN) |     \
                                     PIN_LOCKR_DISABLED(GPIOH_OSC_OUT) |    \
                                     PIN_LOCKR_DISABLED(GPIOH_PIN2) |       \
                                     PIN_LOCKR_DISABLED(GPIOH_BOOT0) |      \
                                     PIN_LOCKR_DISABLED(GPIOH_PIN4) |       \
                                     PIN_LOCKR_DISABLED(GPIOH_PIN5) |       \
                                     PIN_LOCKR_DISABLED(GPIOH_PIN6) |       \
                                     PIN_LOCKR_DISABLED(GPIOH_PIN7) |       \
                                     PIN_LOCKR_DISABLED(GPIOH_PIN8) |       \
                                     PIN_LOCKR_DISABLED(GPIOH_PIN9) |       \
                                     PIN_LOCKR_DISABLED(GPIOH_PIN10) |      \
                                     PIN_LOCKR_DISABLED(GPIOH_PIN11) |      \
                                     PIN_LOCKR_DISABLED(GPIOH_PIN12) |      \
                                     PIN_LOCKR_DISABLED(GPIOH_PIN13) |      \
                                     PIN_LOCKR_DISABLED(GPIOH_PIN14) |      \
                                     PIN_LOCKR_DISABLED(GPIOH_PIN15))

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
