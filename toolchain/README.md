# Toolchain

OreSat uses either STLink or OpenOCD to program and debug boards. STLink is the preferred method, and `make` commands default to using it.

## Programming

In order to program a board, one must simply build the program in question and then issue a `make write` command as follows (using app_blinky as an example):
```
user@hostname:oresat-firmware/src/f0/app_blinky
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
Compiling chobjcaches.c
Compiling chdelegates.c
Compiling chcore.c
Compiling chcore_v6m.c
Compiling main.c
Linking build/app_blinky.elf
lto-wrapper: warning: Options to Xassembler do not match: -alms=./build/lst/crt1.lst, -alms=./build/lst/hal.lst, dropping all -Xassembler and -Wa options.
Creating build/app_blinky.hex
Creating build/app_blinky.bin
Creating build/app_blinky.dmp

   text	   data	    bss	    dec	    hex	filename
   5192	      0	  32768	  37960	   9448	build/app_blinky.elf
Creating build/app_blinky.list

Done
user@hostname:oresat-firmware/src/f0/app_blinky
➜ make write
st-flash  --reset --format ihex write ./build/app_blinky.hex
st-flash 1.6.1
2020-07-30T13:08:14 INFO common.c: F09X: 32 KiB SRAM, 256 KiB flash in at least 2 KiB pages.
2020-07-30T13:08:14 INFO common.c: Attempting to write 5192 (0x1448) bytes to stm32 address: 134217728 (0x8000000)
2020-07-30T13:08:14 INFO common.c: Flash page at addr: 0x08000000 erased
2020-07-30T13:08:14 INFO common.c: Flash page at addr: 0x08000800 erased
2020-07-30T13:08:14 INFO common.c: Flash page at addr: 0x08001000 erased
2020-07-30T13:08:14 INFO common.c: Finished erasing 3 pages of 2048 (0x800) bytes
2020-07-30T13:08:14 INFO common.c: Starting Flash write for VL/F0/F3/F1_XL core id
2020-07-30T13:08:14 INFO flash_loader.c: Successfully loaded flash loader in sram
  3/3 pages written
2020-07-30T13:08:14 INFO common.c: Starting verification of write complete
2020-07-30T13:08:14 INFO common.c: Flash written and verified! jolly good!
```

## Debugging

Debugging is performed through GDB. Using ST-Link, a GDB server must be started in one terminal, then the `make gdb` command may be issued from the source directory.

Terminal 1:
```
user@hostname:~
➜ st-util
st-util
2020-07-30T13:14:06 INFO common.c: F09X: 32 KiB SRAM, 256 KiB flash in at least 2 KiB pages.
2020-07-30T13:14:06 INFO gdb-server.c: Listening at *:4242...
```

Terminal 2:
```
user@hostname:oresat-firmware/src/f0/app_blinky
➜ make gdb
arm-none-eabi-gdb -q /home/user/Projects/PSAS/oresat-firmware/src/f0/app_blinky/./build/app_blinky.elf -cd ../../../toolchain -x ./gdbstl.cmd
Reading symbols from /home/user/Projects/PSAS/oresat-firmware/src/f0/app_blinky/./build/app_blinky.elf...
_port_thread_start () at ../../../ChibiOS/os/common/ports/ARMCMx/compilers/GCC/chcoreasm_v6m.S:110
110	                bl      chThdExit
Loading section .vectors, size 0xc0 lma 0x8000000
Loading section .text, size 0x11fc lma 0x80000c0
Loading section .rodata, size 0x18c lma 0x80012bc
Start address 0x08000190, load size 5192
Transfer rate: 13 KB/sec, 1730 bytes/write.
(gdb)
```

At this point, the program is loaded and ready to debug.
