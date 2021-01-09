#include "blink.h"
#include "chprintf.h"

/*
extern unsigned int __coderam_base__;
extern unsigned int __coderam_init__;
extern unsigned int __coderam_end__;
extern unsigned int __coderam_size__;
unsigned int* coderam_base = (unsigned int*)&__coderam_base__;
unsigned int* coderam_init = (unsigned int*)&__coderam_init__;
unsigned int* coderam_end = (unsigned int*)&__coderam_end__;
unsigned int coderam_size = (unsigned int)&__coderam_size__;
*/

/* Example blinker thread */
THD_WORKING_AREA(blink_wa, 0x200);
THD_FUNCTION(blink, arg)
{
    (void)arg;

    palSetLineMode(LINE_LED, PAL_MODE_OUTPUT_PUSHPULL);

    blinky();
    //blinky_init();


    palClearLine(LINE_LED);
    chThdExit(MSG_OK);
}

/*
#define LOCATE_FUNC  __attribute__((__section__(".coderam")))

void blinky_init() {
    chprintf(&SD2, "BASE: 0x%08x\r\n", coderam_base);
    chprintf(&SD2, "INIT: 0x%08x\r\n", coderam_init);
    chprintf(&SD2, "END: 0x%08x\r\n", coderam_end);
    chprintf(&SD2, "SIZE: 0x%08x\r\n", coderam_size);

    // init the ram function memory region
    memcpy(coderam_base, coderam_init, coderam_size);
    blinky();

}
*/

void blinky()
//void LOCATE_FUNC blinky()
{
    while (!chThdShouldTerminateX())
    {
        palToggleLine(LINE_LED);
        chThdSleepMilliseconds(100);
    }
}
