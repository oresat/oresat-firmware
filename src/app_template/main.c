/*! \file main.c
 *  app_template
 *
 */

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

/*!
 * \defgroup main app_template main
 *
 * @{
 */

/*
 * ChibiOS header files
 */
#include "ch.h"
#include "hal.h"

/*
 * Project header files
 */
#include "can.h"

/*
 * Serial configuration
 */
static SerialConfig ser_cfg =
{
    115200,     //Baud rate
    0,          //
    0,          //
    0,          //
};

/*
 * CAN Register configuration
 * See section 22.7.7 on the STM32 reference manual.
 * Timing calculator:
 * http://www.bittiming.can-wiki.info/
 */
static const CANConfig cancfg = {
    // MCR (Master Control Register)
    CAN_MCR_ABOM      |     //Automatic Bus-Off Management
    CAN_MCR_AWUM      |     //Automatic Wakeup Mode
    CAN_MCR_TXFP      ,     //Transmit FIFO Priority
    // BTR (Bit Timing Register)
    // Note: Convert to zero based values here when using the calculator
    // CAN_BTR_LBKM     |     //Loopback Mode (Debug)
    CAN_BTR_SJW(0)    |     //Synchronization Jump Width
    CAN_BTR_TS1(12)   |     //Time Segment 1
    CAN_BTR_TS2(1)    |     //Time Segment 2
    CAN_BTR_BRP(5)          //Bit Rate Prescaler
};

/*
 * Receiver thread.
 */
static THD_WORKING_AREA(can_rx_wa, 256);
static THD_FUNCTION(can_rx, p)
{
    event_listener_t        el;
    CANRxFrame              rxmsg;

    (void)p;
    // Set thread name
    chRegSetThreadName("receiver");
    // Register RX event
    chEvtRegister(&CAND1.rxfull_event, &el, 0);

    // Configure Status LED (Green)
    palSetLineMode(LINE_LED_GREEN, PAL_MODE_OUTPUT_PUSHPULL);
    palClearLine(LINE_LED_GREEN);

    // Start RX Loop
    while (!chThdShouldTerminateX())
    {
        if (chEvtWaitAnyTimeout(ALL_EVENTS, TIME_MS2I(100)) == 0)
        {
            continue;
        }
        while (canReceive(&CAND1, CAN_ANY_MAILBOX, &rxmsg, TIME_IMMEDIATE) == MSG_OK)
        {
            /* Process message.*/
            palToggleLine(LINE_LED_GREEN);
        }
    }

    //Unregister RX event before terminating thread
    chEvtUnregister(&CAND1.rxfull_event, &el);
}

/*
 * Transmitter thread.
 */
static THD_WORKING_AREA(can_tx_wa, 256);
static THD_FUNCTION(can_tx, p)
{
    CANTxFrame txmsg;

    (void)p;
    chRegSetThreadName("transmitter");
    txmsg.IDE = CAN_IDE_STD;
    txmsg.SID = 0x000;
    txmsg.RTR = CAN_RTR_DATA;
    txmsg.DLC = 8;
    txmsg.data8[0] = 0x00;
    txmsg.data8[1] = 0x01;
    txmsg.data8[2] = 0x02;
    txmsg.data8[3] = 0x03;
    txmsg.data8[4] = 0x04;
    txmsg.data8[5] = 0x05;
    txmsg.data8[6] = 0x06;
    txmsg.data8[7] = 0x07;

    // Start TX Loop
    while (!chThdShouldTerminateX())
    {
        canTransmit(&CAND1, CAN_ANY_MAILBOX, &txmsg, TIME_MS2I(100));
        chThdSleepMilliseconds(500);
    }
}

static void app_init(void)
{
    // Start up debug output
    sdStart(&SD2, &ser_cfg);


    /*
     * Activates CAN driver 1.
     */
    canStart(&CAND1, &cancfg);


}

static void main_app(void)
{
    /*
     * Starting the transmitter and receiver threads.
     */
    chThdCreateStatic(can_rx_wa, sizeof(can_rx_wa), NORMALPRIO + 7, can_rx, NULL);
    chThdCreateStatic(can_tx_wa, sizeof(can_tx_wa), NORMALPRIO + 7, can_tx, NULL);

    /*
     * Begin main loop
     */
    while (true)
    {
        chThdSleepMilliseconds(1000);
    }
}

int main(void)
{
    /*
     * System initializations.
     * - HAL initialization, this also initializes the configured device drivers
     *   and performs the board-specific initializations.
     * - Kernel initialization, the main() function becomes a thread and the
     *   RTOS is active.
     */
    halInit();
    chSysInit();
    app_init();

    main_app();

    return 0;
}

//! @}

