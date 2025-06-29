# Toolchain Test Application
`app_blinky` is a simple app that blinks a dev board's LED at 1Hz with a 50% duty cycle. it's located in the folder `oresat-firmware/src/f0/app_blinky`.

To ensure you have your toolchain correctly installed and configured:
* Plug in a NUCLEO-F091RC development board using a USB MiniB cable.
* If using WSL make sure your usb devices are being shared with WSL. You may need to use a tool like [usbipd-win](https://github.com/dorssel/usbipd-win).
* `cd` into the `app_blinky` directory
* Run `make` and `make write`

If you see something like the following output for each, your toolchain works. Note that you might get more warning messages than you see below, but if the LED starts to blink, you're good to go!

```
➜ make
Compiler Options
arm-none-eabi-gcc -c -mcpu=cortex-m0 -mthumb -Og -ggdb -fomit-frame-pointer -falign-functions=16 -ffunction-sections -fdata-sections -fno-common -flto -Wall -Wextra -Wundef -Wstrict-prototypes -Wa,-alms=./build/lst/ -DCORTEX_USE_FPU=FALSE -DPORT_IGNORE_GCC_VERSION_CHECK -MD -MP -MF ./.dep/build.d -I. -I./cfg -I../../../ChibiOS/os/license -I../../../ChibiOS/os/common/portability/GCC -I../../../ChibiOS/os/common/startup/ARMCMx/compilers/GCC -I../../../ChibiOS/os/common/startup/ARMCMx/devices/STM32F0xx -I../../../ChibiOS/os/common/ext/ARM/CMSIS/Core/Include -I../../../ChibiOS/os/common/ext/ST/STM32F0xx -I../../../ChibiOS/os/hal/include -I../../../ChibiOS/os/hal/ports/common/ARMCMx -I../../../ChibiOS/os/hal/ports/STM32/STM32F0xx -I../../../ChibiOS/os/hal/ports/STM32/LLD/ADCv1 -I../../../ChibiOS/os/hal/ports/STM32/LLD/CANv1 -I../../../ChibiOS/os/hal/ports/STM32/LLD/DACv1 -I../../../ChibiOS/os/hal/ports/STM32/LLD/DMAv1 -I../../../ChibiOS/os/hal/ports/STM32/LLD/EXTIv1 -I../../../ChibiOS/os/hal/ports/STM32/LLD/GPIOv2 -I../../../ChibiOS/os/hal/ports/STM32/LLD/I2Cv2 -I../../../ChibiOS/os/hal/ports/STM32/LLD/RTCv2 -I../../../ChibiOS/os/hal/ports/STM32/LLD/SPIv2 -I../../../ChibiOS/os/hal/ports/STM32/LLD/TIMv1 -I../../../ChibiOS/os/hal/ports/STM32/LLD/USARTv2 -I../../../ChibiOS/os/hal/ports/STM32/LLD/USBv1 -I../../../ChibiOS/os/hal/ports/STM32/LLD/xWDGv1 -I../../../boards/ST_NUCLEO32_F042K6 -I../../../ChibiOS/os/hal/osal/rt-nil -I../../../ChibiOS/os/rt/include -I../../../ChibiOS/os/oslib/include -I../../../ChibiOS/os/common/ports/ARMCMx -I../../../ChibiOS/os/common/ports/ARMCMx/compilers/GCC -I../../../common/include main.c -o main.o

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
st-flash  --reset --format ihex write ./build/app_blinky.hex
st-flash 1.6.1
2020-07-30T13:29:22 INFO common.c: F09X: 32 KiB SRAM, 256 KiB flash in at least 2 KiB pages.
2020-07-30T13:29:22 INFO common.c: Attempting to write 5192 (0x1448) bytes to stm32 address: 134217728 (0x8000000)
2020-07-30T13:29:22 INFO common.c: Flash page at addr: 0x08000000 erased
2020-07-30T13:29:22 INFO common.c: Flash page at addr: 0x08000800 erased
2020-07-30T13:29:22 INFO common.c: Flash page at addr: 0x08001000 erased
2020-07-30T13:29:22 INFO common.c: Finished erasing 3 pages of 2048 (0x800) bytes
2020-07-30T13:29:22 INFO common.c: Starting Flash write for VL/F0/F3/F1_XL core id
2020-07-30T13:29:22 INFO flash_loader.c: Successfully loaded flash loader in sram
  3/3 pages written
2020-07-30T13:29:22 INFO common.c: Starting verification of write complete
2020-07-30T13:29:22 INFO common.c: Flash written and verified! jolly good!
```
