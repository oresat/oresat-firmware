#include "hal.h"
#include "oresat_f0.h"
#include "string.h"


/**
 * This function should be called on applications using the STM32F091xC-app.ld linker script and using the bootloader to run them.
 */
void __late_init(void) {
    /* Relocate by software the vector table to the internal SRAM at 0x20000000 ***/
    /* Copy the vector table from the Flash (mapped at the base of the application
    load address 0x08003000) to the base address of the SRAM at 0x20000000. */

    memcpy((void *)0x20000000, (void *)ORESAT_F0_FIRMWARE_CODE_ADDRESS, 0xC0);
    __DSB();
    /* Remap SRAM at 0x00000000 */
    SYSCFG->CFGR1 |= SYSCFG_CFGR1_MEM_MODE;
    __DSB();
    __ISB();
}
