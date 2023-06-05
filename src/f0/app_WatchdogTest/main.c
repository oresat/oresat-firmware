/*
    This is the Watchdog Firmware testing environment where the internal Watchdog for STM32F091
    will be interfacing with ChibiOS threads, flags, and voting. 
*/

/* ChibiOS header files */
#include "hal.h"
#include "math.h"
#include "stdarg.h"
#include "stdlib.h"
#include "stdio.h"
#include "halconf.h"
#include "stm32f0xx_tim.h"
#include "mcuconf.h"
#include "stm32f0xx.h"
#include "stm32f0xx_iwdg.h" //needed to activate library for internal watchdog timer








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
   
    
   

    while (true)
    {
        palClearLine(LINE_LED);
        chThdSleepMilliseconds(500);
        palSetLine(LINE_LED);
        chThdSleepMilliseconds(500);
        
        
    }

//TEST RUNNING ACTIVATING IWDG (according to reference manual)

/* (1) Activate IWDG (not needed if done in option bytes) */
/* (2) Enable write access to IWDG registers */
/* (3) Set prescaler by 8 */
/* (4) Set reload value to have a rollover each 100ms */
/* (5) Check if flags are reset */
/* (6) Refresh counter */
IWDG->KR = 0xCCCC; /* (1) */
IWDG->KR = 0x5555; /* (2) */
IWDG->PR = IWDG_Prescaler_8; /* (3) */
IWDG->RLR = 0x0FFF; /* (4) */
printf("Hello\n");
while (IWDG->SR) /* (5) */
{
/* add time out here for a robust application */

}
IWDG->KR = 0x0000; /* (6) */


 




    return 0;
}
