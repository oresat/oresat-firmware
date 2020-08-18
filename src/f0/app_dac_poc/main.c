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

/* ChibiOS header files */
#include "ch.h"
#include "hal.h"

/* Project header files */
#include "oresat.h"
#include "blink.h"

static worker_t dac_thr;

static oresat_config_t oresat_conf = {
    &CAND1,
    ORESAT_DEFAULT_ID,
    ORESAT_DEFAULT_BITRATE
};

/* 
TODO DAC
    - ref manual says that GPIO should be set to analog input before enabling
    DAC, check that chibios doing this under the hood
    - There is an output buffer, do we want it? Or is it enabled by default?
*/

// DAC1 config
static const DACConfig dac1cfg1 = {
  .init         = 0U,                   // initialize DAC to 0 
  .datamode     = DAC_DHRM_12BIT_RIGHT, // 12 bit, right aligned
  .cr           = 0                     // no control reg options
};

// DAC test thread
THD_WORKING_AREA(dac_da, 0x40);
THD_FUNCTION(dac_test, arg)
{
    (void)arg;

    /*
    * System initializations.
    * - HAL initialization, this also initializes the configured device drivers
    *   and performs the board-specific initializations.
    * - Kernel initialization, the main() function becomes a thread and the
    *   RTOS is active.
    */
    halInit();
    chSysInit();

    // start the DAC driver
    dacStart(&DACD1, &dac1cfg1);

    while(1){
        dacPutMillivolts(&DACD1, 0, 2222);
        chThdSleepMicroseconds(1);
    }
}

#define DAC_BITS 12

// VDDA (vref) is 3.333V on nucleo64 board
#define DAC_VDDA_V 3.333                // volts
#define DAC_VDDA_MV (DAC_VDDA_V * 1000) // millivolts

void dacPutMillivolts(DACDriver *dacp, dacchannel_t chan, uint32_t mv) {
    // per section 14.5.3 of the STM32F0x1 ref manual,  
    // Vout(mV) = VDDA(mV) * (reg_val / 4096)
    // so, reg_val = (Vout * 4096) / VDDA 
    dacsample_t val = (mv * 1<<DAC_BITS) / DAC_VDDA_MV;
    dacPutChannelX(dacp, chan, val);
}

/**
 * @brief App Initialization
 */
static void app_init(void)
{
    // init the DAC worker
    init_worker(&dac_thr, "DAC test", dac_da, sizeof(dac_da), NORMALPRIO, dac_test, NULL);
    reg_worker(&dac_thr);

    start_workers();

    /* Start up debug output */
    sdStart(&SD2, NULL);
}

/**
 * @brief Main Application
 */
int main(void)
{
    // Initialize and start
    oresat_init();
    app_init();
    oresat_start(&oresat_conf);
    return 0;
}
