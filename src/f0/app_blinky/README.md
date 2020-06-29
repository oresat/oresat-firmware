# Toolchain Test Application
`app_blinky` is a simple app that blinks a dev board's LED at 1Hz with a 50% duty cycle.

To ensure you have your toolchain correctly installed and configured,
you simply need to run the following sequence of commands:

```
make
make write
```

If you see something like the following output for each, your
toolchain works:

```
➜ make
Compiler Options
arm-none-eabi-gcc -c -mcpu=cortex-m0 -mthumb -Og -ggdb -fomit-frame-pointer -falign-functions=16 -ffunction-sections -fdata-sections -fno-common -flto -Wall -Wextra -Wundef -Wstrict-prototypes -Wa,-alms=./build/lst/ -DCORTEX_USE_FPU=FALSE -DPORT_IGNORE_GCC_VERSION_CHECK -MD -MP -MF ./.dep/build.d -I. -I./cfg -I../../../ChibiOS/os/license -I../../../ChibiOS/os/common/portability/GCC -I../../../ChibiOS/os/common/startup/ARMCMx/compilers/GCC -I../../../ChibiOS/os/common/startup/ARMCMx/devices/STM32F0xx -I../../../ChibiOS/os/common/ext/ARM/CMSIS/Core/Include -I../../../ChibiOS/os/common/ext/ST/STM32F0xx -I../../../ChibiOS/os/hal/include -I../../../ChibiOS/os/hal/ports/common/ARMCMx -I../../../ChibiOS/os/hal/ports/STM32/STM32F0xx -I../../../ChibiOS/os/hal/ports/STM32/LLD/ADCv1 -I../../../ChibiOS/os/hal/ports/STM32/LLD/CANv1 -I../../../ChibiOS/os/hal/ports/STM32/LLD/DACv1 -I../../../ChibiOS/os/hal/ports/STM32/LLD/DMAv1 -I../../../ChibiOS/os/hal/ports/STM32/LLD/EXTIv1 -I../../../ChibiOS/os/hal/ports/STM32/LLD/GPIOv2 -I../../../ChibiOS/os/hal/ports/STM32/LLD/I2Cv2 -I../../../ChibiOS/os/hal/ports/STM32/LLD/RTCv2 -I../../../ChibiOS/os/hal/ports/STM32/LLD/SPIv2 -I../../../ChibiOS/os/hal/ports/STM32/LLD/TIMv1 -I../../../ChibiOS/os/hal/ports/STM32/LLD/USARTv2 -I../../../ChibiOS/os/hal/ports/STM32/LLD/USBv1 -I../../../ChibiOS/os/hal/ports/STM32/LLD/xWDGv1 -I../../../boards/ST_NUCLEO64_F091RC -I../../../ChibiOS/os/hal/osal/rt-nil -I../../../ChibiOS/os/rt/include -I../../../ChibiOS/os/oslib/include -I../../../ChibiOS/os/common/ports/ARMCMx -I../../../ChibiOS/os/common/ports/ARMCMx/compilers/GCC -I../../../common/include main.c -o main.o

Compiling crt0_v6m.S
Compiling vectors.S
Compiling chcoreasm_v6m.S
Compiling crt1.c
Compiling hal.c
Compiling hal_st.c
Compiling hal_buffers.c
Compiling hal_queues.c
Compiling hal_flash.c
Compiling hal_mmcsd.c
Compiling hal_pal.c
Compiling hal_serial.c
Compiling nvic.c
Compiling stm32_isr.c
Compiling hal_lld.c
Compiling stm32_dma.c
Compiling stm32_exti.c
Compiling hal_pal_lld.c
Compiling hal_st_lld.c
Compiling hal_serial_lld.c
Compiling board.c
Compiling osal.c
Compiling chsys.c
Compiling chdebug.c
Compiling chtrace.c
Compiling chvt.c
Compiling chschd.c
Compiling chthreads.c
Compiling chregistry.c
Compiling chsem.c
Compiling chmtx.c
Compiling chcond.c
Compiling chevents.c
Compiling chmsg.c
Compiling chdynamic.c
Compiling chmboxes.c
Compiling chmemcore.c
Compiling chmempools.c
Compiling chpipes.c
Compiling chcore.c
Compiling chcore_v6m.c
Compiling main.c
Linking build/app_blinky.elf
Creating build/app_blinky.hex
Creating build/app_blinky.bin
Creating build/app_blinky.dmp

   text	   data	    bss	    dec	    hex	filename
   4952	      0	   6144	  11096	   2b58	build/app_blinky.elf
Creating build/app_blinky.list

Done

➜ make write
openocd -s ../../../boards/ST_NUCLEO64_F091RC -f oocd.cfg -c "program ./build/app_blinky.hex verify reset exit"
Open On-Chip Debugger 0.10.0+dev-00924-g16496488d (2019-08-08-08:23)
Licensed under GNU GPL v2
For bug reports, read
	http://openocd.org/doc/doxygen/bugs.html
Info : The selected transport took over low-level target control. The results might differ compared to plain JTAG/SWD
Info : clock speed 1000 kHz
Info : STLINK V2J25M14 (API v2) VID:PID 0483:374B
Info : Target voltage: 3.238896
Info : stm32f0x.cpu: hardware has 4 breakpoints, 2 watchpoints
Info : Listening on port 3333 for gdb connections
Info : Unable to match requested speed 1000 kHz, using 950 kHz
Info : Unable to match requested speed 1000 kHz, using 950 kHz
target halted due to debug-request, current mode: Thread 
xPSR: 0xc1000000 pc: 0x08000190 msp: 0x20000100
Info : Unable to match requested speed 8000 kHz, using 4000 kHz
Info : Unable to match requested speed 8000 kHz, using 4000 kHz
** Programming Started **
Info : device id = 0x10006445
Info : flash size = 32kbytes
** Programming Finished **
** Verify Started **
** Verified OK **
** Resetting Target **
Info : Unable to match requested speed 1000 kHz, using 950 kHz
Info : Unable to match requested speed 1000 kHz, using 950 kHz
shutdown command invoked
```
