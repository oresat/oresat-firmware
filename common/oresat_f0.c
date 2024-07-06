#include "hal.h"
#include "oresat_f0.h"
#include "string.h"


/**
 * This function is called by applications using the STM32F091xC-app.ld
 * linker script and using the bootloader to run them. It overwrites a weak
 * symbol from ChibiOS's CRT0 and so will be called late in the init sequence.
 */
void __late_init(void) {
    // Relocate by software the vector table to the internal SRAM at 0x20000000.
    // The vector table comes from flash, mapped at the base of the application
    // region, load address __flash2_base__ (0x0800A800).
    //
    // The SRAM then gets remapped to 0x00000000 to function as the real vector
    // table

    memcpy(__ram0_base__, __flash2_base__, 0xC0);
    __DSB();
    /* Remap SRAM at 0x00000000 */
    SYSCFG->CFGR1 |= SYSCFG_CFGR1_MEM_MODE;
    __DSB();
    __ISB();
}
