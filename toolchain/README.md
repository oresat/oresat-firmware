# Toolchain

OreSat uses either STLink or OpenOCD to program and debug boards. OpenOCD is the
preferred method, and `make` commands default to using it.

## Programming

In order to program a board, the firmware must be built and then programmed on
to the device. `make` on it's own will just build the firmware but `make write`
will both build and program in a single step. This is an example of using `make
write` in `app_blinky`:

```
$ make write
Compiler Options
arm-none-eabi-gcc -c -mcpu=cortex-m0 -mthumb -Og -ggdb -fomit-frame-pointer -falign-functions=16 -ffunction-sections -fdata-sections -fno-common -flto -Wall -Wextra -Wundef -Wstrict-prototypes -Wa,-alms=./build/lst/ -DCORTEX_USE_FPU=FALSE -MD -MP -MF ./.dep/build.d -I. -I./cfg -I../../../ext/ChibiOS/os/license -I../../../ext/ChibiOS/os/common/portability/GCC -I../../../ext/ChibiOS/os/common/startup/ARMCMx/compilers/GCC -I../../../ext/ChibiOS/os/common/startup/ARMCMx/devices/STM32F0xx -I../../../ext/ChibiOS/os/common/ext/ARM/CMSIS/Core/Include -I../../../ext/ChibiOS/os/common/ext/ST/STM32F0xx -I../../../ext/ChibiOS/os/hal/include -I../../../ext/ChibiOS/os/hal/ports/common/ARMCMx -I../../../ext/ChibiOS/os/hal/ports/STM32/STM32F0xx -I../../../ext/ChibiOS/os/hal/ports/STM32/LLD/ADCv1 -I../../../ext/ChibiOS/os/hal/ports/STM32/LLD/CANv1 -I../../../ext/ChibiOS/os/hal/ports/STM32/LLD/DACv1 -I../../../ext/ChibiOS/os/hal/ports/STM32/LLD/DMAv1 -I../../../ext/ChibiOS/os/hal/ports/STM32/LLD/EXTIv1 -I../../../ext/ChibiOS/os/hal/ports/STM32/LLD/GPIOv2 -I../../../ext/ChibiOS/os/hal/ports/STM32/LLD/I2Cv2 -I../../../ext/ChibiOS/os/hal/ports/STM32/LLD/RTCv2 -I../../../ext/ChibiOS/os/hal/ports/STM32/LLD/SPIv2 -I../../../ext/ChibiOS/os/hal/ports/STM32/LLD/TIMv1 -I../../../ext/ChibiOS/os/hal/ports/STM32/LLD/USARTv2 -I../../../ext/ChibiOS/os/hal/ports/STM32/LLD/USBv1 -I../../../ext/ChibiOS/os/hal/ports/STM32/LLD/xWDGv1 -I../../../boards/ST_NUCLEO64_F091RC -I../../../ext/ChibiOS/os/hal/osal/rt-nil -I../../../ext/ChibiOS/os/rt/include -I../../../ext/ChibiOS/os/oslib/include -I../../../ext/ChibiOS/os/common/ports/ARMCMx -I../../../ext/ChibiOS/os/common/ports/ARMCMx/compilers/GCC -I../../../common/include main.c -o main.o

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
   5236	      0	  32768	  38004	   9474	build/app_blinky.elf
Creating build/app_blinky.list

Done
openocd -s ../../../boards/ST_NUCLEO64_F091RC -s ../../../toolchain -f oocd-interface.cfg -f oocd-target.cfg -c " program ./build/app_blinky.hex verify reset exit"
Open On-Chip Debugger 0.11.0
Licensed under GNU GPL v2
For bug reports, read
	http://openocd.org/doc/doxygen/bugs.html
dapdirect_swd
Info : STLINK V2J25M14 (API v2) VID:PID 0483:374B
Info : Target voltage: 3.255680
Info : Unable to match requested speed 1000 kHz, using 950 kHz
Info : Unable to match requested speed 1000 kHz, using 950 kHz
Info : clock speed 950 kHz
Info : stlink_dap_op_connect(connect)
Info : SWD DPIDR 0x0bb11477
Info : stm32f0x.cpu: hardware has 4 breakpoints, 2 watchpoints
Info : starting gdb server for stm32f0x.cpu on 3333
Info : Listening on port 3333 for gdb connections
Info : Unable to match requested speed 1000 kHz, using 950 kHz
Info : Unable to match requested speed 1000 kHz, using 950 kHz
target halted due to debug-request, current mode: Thread
xPSR: 0xc1000000 pc: 0x08001dac msp: 0x200005e0
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
The message `** Verified OK **` shows that programming was ultimately
successful.

## Debugging

Debugging is performed through GDB. The `make gdb` command may be issued from
any application source directory and it will automatically start both openocd
and gdb for you.

Terminal:
```

make gdb
gdb-multiarch -q ./build/app_blinky.elf -ex "target extended-remote | openocd -s ../../../boards/ST_NUCLEO64_F091RC -s ../../../toolchain -f oocd-interface.cfg -f oocd-target.cfg -c ' gdb_port pipe'" -x ../../../toolchain/gdboocd.cmd
Reading symbols from ./build/app_blinky.elf...
Remote debugging using | openocd -s ../../../boards/ST_NUCLEO64_F091RC -s ../../../toolchain -f oocd-interface.cfg -f oocd-target.cfg -c ' gdb_port pipe'
Open On-Chip Debugger 0.11.0
Licensed under GNU GPL v2
For bug reports, read
	http://openocd.org/doc/doxygen/bugs.html
dapdirect_swd
Info : Listening on port 6666 for tcl connections
Info : Listening on port 4444 for telnet connections
Info : STLINK V2J33M25 (API v2) VID:PID 0483:374B
Info : Target voltage: 3.257482
Info : Unable to match requested speed 1000 kHz, using 950 kHz
Info : Unable to match requested speed 1000 kHz, using 950 kHz
Info : clock speed 950 kHz
Info : stlink_dap_op_connect(connect)
Info : SWD DPIDR 0x0bb11477
Info : stm32f0x.cpu: hardware has 4 breakpoints, 2 watchpoints
Info : starting gdb server for stm32f0x.cpu on pipe
Info : accepting 'gdb' connection from pipe
target halted due to debug-request, current mode: Thread
xPSR: 0x41000000 pc: 0x080006c2 psp: 0x20000368
Info : device id = 0x10006442
Info : flash size = 256kbytes
0x080006c2 in port_wait_for_interrupt () at ../../../ext/ChibiOS/os/common/ports/ARMCMx/chcore_v6m.h:458
458	  __WFI();
Info : Unable to match requested speed 1000 kHz, using 950 kHz
Unable to match requested speed 1000 kHz, using 950 kHz
Info : Unable to match requested speed 1000 kHz, using 950 kHz
Unable to match requested speed 1000 kHz, using 950 kHz
target halted due to debug-request, current mode: Thread
xPSR: 0xc1000000 pc: 0x08000190 msp: 0x20000100
target halted due to debug-request, current mode: Thread
xPSR: 0xc1000000 pc: 0x08000190 msp: 0x20000100
Info : Unable to match requested speed 8000 kHz, using 4000 kHz
Info : Unable to match requested speed 8000 kHz, using 4000 kHz
Unable to match requested speed 8000 kHz, using 4000 kHz
Unable to match requested speed 8000 kHz, using 4000 kHz
(gdb)
```

At this point, the program is loaded and ready to debug. To quit gdb press
ctrl+d.
