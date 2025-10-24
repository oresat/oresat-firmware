# Raspberry Pi Debug Probe Installation and Usage for the NXP MCXN947

Information about the probe is here: [Raspberry Pi Debug Probe].

## Installation and use

### On terminal 1

1. Check pyocd version
```
~/src/oresat/firmware/apps/solar/build/zephyr$ pyocd --version
0.37.0
```
Version 0.38.0 is the latest as of 10/23/2025, though 0.37.0 works fine.

2. Install pyocd pack to support the mcxn947
```
$ pyocd pack install mcxn947
0000465 I No pack index present, downloading now... [pack_cmd]
Downloading packs (press Control-C to cancel):
    NXP.MCXN947_DFP.25.09.00
Downloading descriptors (001/001)
```

3. Connect the probe and verify we can see it
```
~/src/oresat/firmware/apps/solar/build/zephyr$ pyocd list
  #   Probe/Board                            Unique ID          Target  
------------------------------------------------------------------------
  0   Raspberry Pi Debug Probe (CMSIS-DAP)   E663AC91D38F7439   n/a      <-- found probe
```

4. Check the firmware version:
```
~/src/oresat/firmware/apps/solar/build/zephyr$ lsusb -v -d 2e8a:000c | grep bcdDevice
  bcdDevice            1.01
```
This is too old -- latest is 2.23.

5. Update the firmware version:
    1. Take off the lid
    2. Unplug the cable to the PC
    3. Press the button while plugging in cable
    4. Browse to https://github.com/raspberrypi/debugprobe
    5. Click on latest "Releases" link and download debugprobe.uf2
    6. Copy that to the USB drive the debug probe created to update to latest firmware
    7. Debug probe will automatically update and reboot

6. After upgrade, check the version:
```
~/src/oresat/firmware/apps/solar/build/zephyr$ lsusb -v -d 2e8a:000c | grep bcdDevice
  bcdDevice            2.23
```

7. Open a serial terminal (e.g., PuTTY) on the serial device (Ubuntu 24.04 shows /dev/ttyACM0), 115200 baud, 8n1

8. Verify we can flash (assumes you built the firmware at some point):
```
~/src/oresat/firmware/apps/solar$ pyocd flash build/zephyr/zephyr.elf -t mcxn947
0002082 W DFP device definition conflict: specified default reset sequence ResetSystem for core #1 (cm33_core1) is disabled by the DFP [pack_target]
0002096 I Loading ~/src/oresat/firmware/apps/solar/build/zephyr/zephyr.elf [load_cmd]
[==================================================] 100%
0008081 I Erased 65536 bytes (8 sectors), programmed 60416 bytes (118 pages), skipped 0 bytes (0 pages) at 9.86 kB/s [loader]
```

9. You should see output on the serial terminal:
```
*** Booting Zephyr OS build v4.2.0 ***

[00:00:00.003,000] <inf> oresat_mcxn947_solar: Oresat MCXN947 Solar Board App

[00:00:00.003,000] <inf> oresat_blink: Starting blink demo
[00:00:00.003,000] <dbg> oresat_blink: handle_blink: The light is blinking!
[00:00:00.003,000] <inf> oresat_i2c_sensors: Starting INA226 reading
[00:00:00.003,000] <inf> oresat_i2c_sensors: Starting TMP108 reading
Bus: 0.000000 [V] -- Power: 0.000000 [W] -- Current: 0.000000 [A]
temperature from tmp108@48 (tmp101_cell1) is 19.5C
temperature from tmp108@4a (tmp101_cell2) is 19.5C
[00:00:01.003,000] <dbg> oresat_blink: handle_blink: The light is blinking!
[00:00:02.003,000] <dbg> oresat_blink: handle_blink: The light is blinking!
Bus: 0.000000 [V] -- Power: 0.000000 [W] -- Current: 0.000000 [A]
temperature from tmp108@48 (tmp101_cell1) is 19.5C
temperature from tmp108@4a (tmp101_cell2) is 19.5C

```

10. To debug, start GDB server:
```
~/zephyr-sdk-0.16.8/arm-zephyr-eabi/bin/arm-zephyr-eabi-gdb zephyr.elf
```

## On terminal 2
```
~/src/oresat/firmware/apps/solar/build/zephyr$ ~/zephyr-sdk-0.16.8/arm-zephyr-eabi/bin/arm-zephyr-eabi-gdb zephyr.elf
GNU gdb (Zephyr SDK 0.16.8) 12.1
Copyright (C) 2022 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "--host=x86_64-build_pc-linux-gnu --target=arm-zephyr-eabi".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://github.com/zephyrproject-rtos/sdk-ng/issues>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from zephyr.elf...
(gdb)
(gdb) target remote localhost:3333
Remote debugging using localhost:3333
__enable_irq () at ~src/oresat/firmware/modules/hal/cmsis_6/CMSIS/Core/Include/cmsis_gcc.h:800
800	  __ASM volatile ("cpsie i" : : : "memory");
(gdb) step
arch_cpu_idle () at ~src/oresat/firmware/zephyr/arch/arm/core/cortex_m/cpu_idle.c:105
105		__ISB();
(gdb) continue
Continuing.
^C
Program received signal SIGINT, Interrupt.
0x10005b00 in LPUART_GetStatusFlags (base=<optimized out>) at ~src/oresat/firmware/modules/hal/nxp/mcux/mcux-sdk-ng/drivers/lpflexcomm/lpuart/fsl_lpuart.c:952
952	    temp |= ((base->TOSR & 0xF00UL) << 2U);
(gdb) bt
#0  0x10005b00 in LPUART_GetStatusFlags (base=<optimized out>) at ~src/oresat/firmware/modules/hal/nxp/mcux/mcux-sdk-ng/drivers/lpflexcomm/lpuart/fsl_lpuart.c:952
#1  0x1000a936 in mcux_lpuart_poll_out (dev=<optimized out>, c=<optimized out>) at ~src/oresat/firmware/zephyr/drivers/serial/uart_mcux_lpuart.c:182
#2  0x10003446 in z_impl_uart_poll_out (dev=<optimized out>, out_char=<optimized out>) at ~src/oresat/firmware/zephyr/include/zephyr/drivers/uart/uart_internal.h:186
#3  uart_poll_out (dev=<optimized out>, out_char=<optimized out>) at ~src/oresat/firmware/apps/solar/build/zephyr/include/generated/zephyr/syscalls/uart.h:108
#4  char_out (data=<optimized out>, length=1, ctx=<optimized out>) at ~src/oresat/firmware/zephyr/subsys/logging/backends/log_backend_uart.c:104
#5  0x1000a160 in log_output_write (outf=0x10003429 <char_out>, buf=0x300057aa <lbu_buffer> "5", len=1, ctx=0x1000c54c <lbu_cb_ctx>)
    at ~src/oresat/firmware/zephyr/include/zephyr/logging/log_output.h:205
#6  0x1000a178 in log_output_flush (output=output@entry=0x1000c554 <lbu_output>) at ~src/oresat/firmware/zephyr/include/zephyr/logging/log_output.h:217
#7  0x10003046 in out_func (c=67, ctx=0x1000c554 <lbu_output>) at ~src/oresat/firmware/zephyr/subsys/logging/log_output.c:108
#8  0x1000a198 in cr_out_func (c=67, ctx=0x1000c554 <lbu_output>) at ~src/oresat/firmware/zephyr/subsys/logging/log_output.c:124
#9  0x1000a2c2 in cbputc (c=<optimized out>, _s=<optimized out>) at ~src/oresat/firmware/zephyr/lib/libc/picolibc/cbprintf.c:19
```

That's it!

[Raspberry Pi Debug Probe]:https://www.raspberrypi.com/documentation/microcontrollers/debug-probe.html

