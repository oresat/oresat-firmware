/*
    This is the Watchdog Firmware testing environment where the internal Watchdog for STM32F091
    will be interfacing with ChibiOS threads, flags, and voting. 
*/

/* ChibiOS header files */
#include "ch.h"
#include "hal.h"
#include "math.h"
#include <stdlib.h>
#include "halconf.h"
#include "stm32f0xx_iwdg.h" //needed to activate library for internal watchdog timer

//Enabling internal Watchdog Timer
void IWDG_Enable(void){
    IWDG -> KR = 0x0000; //Activate IWDG
    IWDG -> KR = IWDG_WriteAccess_Enable;
    IWDG_SetPrescaler(8); //set prescaler to 8
    IWDG_SetReload(40000);
    while (IWDG -> SR) {}
    div_t result = div((int)IWDG_ReloadCounter, 2);
    IWDG -> WINR = result.quot; //IWDG_ReloadCounter / 2
}

//Setting SysTick Timer to show IWDG is working
void SysTick_Init(void) {
    //set SysTick to generate an interrupt every 1 ms
    div_t result = div(SystemCoreClock, 1000);
    SysTick_Config(result.quot);
}

volatile uint32_t tick_counter = 0;

void SysTick_Handler(void){
    tick_counter++;
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
    SysTick_Init();
    IWDG_Enable();

    while (true)
    {
        palClearLine(LINE_LED);
        chThdSleepMilliseconds(500);
        palSetLine(LINE_LED);
        chThdSleepMilliseconds(500);
    }

    while (1) {
        //check if IWDG has reset MCU
        if (RCC -> CSR & RCC_CSR_IWDGRSTF) {
            //clear reset flag
            RCC -> CSR |= RCC_CSR_RMVF;
            //blink the LED to indicate a reset occurred
        }

        //check if it's time to refresh the IWDG
        if (tick_counter >= 1000) { //refresh every second
            //reload the IWDG
            IWDG_ReloadCounter();
            //reset the tick counter
            tick_counter = 0;
        }
    }

    return 0;
}
