# Raspberry Pi Debug Probe Installation and Usage for the NXP MCXN947

Information about the probe is here: [Raspberry Pi Debug Probe].

## Installation and use

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

2. Install pyocd pack(v19!) to support the mcxn947
   1. download [Device Family Pack 19](https://mcuxpresso.nxp.com/cmsis_pack/repo/NXP.MCXN947_DFP.19.0.0.pack)
      put it somewhere nice

   2. create `pyocd.yaml` in the directory you plan to run `west flash`, containing the line:
   ```
   path: /path/to/NXP.MCXN947_DFP.19.0.0.pack
   ```
    change path to where you placed it.
    ensure you run `west flash`/`pyocd flash` from the directory that contains this file.


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

Or more simply:
```
$ west flash -r pyocd
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

10. To debug:
```
$ west debug -r pyocd
-- west debug: rebuilding
ninja: no work to do.
-- west debug: using runner pyocd
-- runners.pyocd: pyOCD GDB server running on port 3333
GNU gdb (Zephyr SDK 0.17.2) 12.1
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
Reading symbols from ~/src/oresat/firmware/apps/solar/build/zephyr/zephyr.elf...
0000834 I Target type is mcxn947 [board]
0001471 I DP IDR = 0x6ba02477 (v2 rev6) [dap]
0001472 I debugvar 'BootTime' = 0xf4240 (1000000) [pack_target]
0001472 I debugvar 'Dbg_CR' = 0x0 (0) [pack_target]
0001472 I debugvar 'SWO_Pin' = 0x0 (0) [pack_target]
0001974 I AHB-AP#0 IDR = 0x84770001 (AHB-AP var0 rev8) [discovery]
0001976 I AHB-AP#1 IDR = 0x84770001 (AHB-AP var0 rev8) [discovery]
0001976 I AP#2 IDR = 0x002a0000 (AP var0 rev0) [discovery]
0001978 I APB-AP#3 IDR = 0x54770002 (APB-AP var0 rev5) [discovery]
0001981 I AHB-AP#0 Class 0x1 ROM table #0 @ 0xe00fe000 (designer=015 part=000) [rom_table]
0001983 I [0]<e00ff000:ROM class=1 designer=43b:Arm part=4c9> [rom_table]
0001983 I   AHB-AP#0 Class 0x1 ROM table #1 @ 0xe00ff000 (designer=43b:Arm part=4c9) [rom_table]
0001986 I   [0]<e000e000:SCS M33 class=9 designer=43b:Arm part=d21 devtype=00 archid=2a04 devid=0:0:0> [rom_table]
0001988 I   [1]<e0001000:DWT M33 class=9 designer=43b:Arm part=d21 devtype=00 archid=1a02 devid=0:0:0> [rom_table]
0001990 I   [2]<e0002000:BPU M33 class=9 designer=43b:Arm part=d21 devtype=00 archid=1a03 devid=0:0:0> [rom_table]
0001992 I   [3]<e0000000:ITM M33 class=9 designer=43b:Arm part=d21 devtype=43 archid=1a01 devid=0:0:0> [rom_table]
0001994 I   [5]<e0041000:ETM M33 class=9 designer=43b:Arm part=d21 devtype=13 archid=4a13 devid=0:0:0> [rom_table]
0001995 I   [6]<e0042000:CTI M33 class=9 designer=43b:Arm part=d21 devtype=14 archid=1a14 devid=40800:0:0> [rom_table]
0001997 I [1]<e0040000:TPIU M33 class=9 designer=43b:Arm part=d21 devtype=11 archid=0000 devid=ca1:0:0> [rom_table]
0001999 I [2]<e0044000:Trace Funnel CS-400 class=9 designer=43b:Arm part=908 devtype=12 archid=0000 devid=32:0:0> [rom_table]
0002001 I [3]<e0045000:??? class=9 designer=43b:Arm part=961 devtype=21 archid=0000 devid=300:0:0> [rom_table]
0002003 I AHB-AP#1 Class 0x1 ROM table #0 @ 0xe00ff000 (designer=43b:Arm part=4c9) [rom_table]
0002006 I [0]<e000e000:SCS M33 class=9 designer=43b:Arm part=d21 devtype=00 archid=2a04 devid=0:0:0> [rom_table]
0002008 I [1]<e0001000:DWT M33 class=9 designer=43b:Arm part=d21 devtype=00 archid=1a02 devid=0:0:0> [rom_table]
0002010 I [2]<e0002000:BPU M33 class=9 designer=43b:Arm part=d21 devtype=00 archid=1a03 devid=0:0:0> [rom_table]
0002012 I [3]<e0000000:ITM M33 class=9 designer=43b:Arm part=d21 devtype=43 archid=1a01 devid=0:0:0> [rom_table]
0002014 I [6]<e0042000:CTI M33 class=9 designer=43b:Arm part=d21 devtype=14 archid=1a14 devid=40800:0:0> [rom_table]
0002019 I CPU core #0: Cortex-M33 r0p4, v8.0-M architecture [cortex_m]
0002019 I   Extensions: [DSP, FPU, FPU_V5, MPU, SEC] [cortex_m]
0002019 I   FPU present: FPv5-SP-D16-M [cortex_m]
0002027 I CPU core #1: Cortex-M33 r0p4, v8.0-M architecture [cortex_m]
0002028 I Setting core #0 (cm33_core0) default reset sequence to ResetSystem [pack_target]
0002028 W DFP device definition conflict: specified default reset sequence ResetSystem for core #1 (cm33_core1) is disabled by the DFP [pack_target]
0002028 I Setting core #1 (cm33_core1) default reset sequence to ResetProcessor [pack_target]
0002030 I 4 hardware watchpoints [dwt]
0002032 I 8 hardware breakpoints, 1 literal comparators [fpb]
0002040 I 4 hardware watchpoints [dwt]
0002041 I 8 hardware breakpoints, 1 literal comparators [fpb]
0002049 I Semihost server started on port 4444 (core 0) [server]
0002139 I GDB server started on port 3333 (core 0) [gdbserver]
0002141 I Semihost server started on port 4445 (core 1) [server]
0002142 I GDB server started on port 3334 (core 1) [gdbserver]
Remote debugging using :3333
0002398 I Client connected to port 3333! [gdbserver]
__enable_irq () at ~/src/oresat/firmware/modules/hal/cmsis_6/CMSIS/Core/Include/cmsis_gcc.h:800
800	  __ASM volatile ("cpsie i" : : : "memory");
0002497 I Attempting to load RTOS plugins [gdbserver]
0002498 W Zephyr kernel detected. Build your Zephyr application with `CONFIG_DEBUG_THREAD_INFO=y` to enable thread awareness. [zephyr]
Successfully halted device
Resetting target
Loading section rom_start, size 0x2ac lma 0x10000000
Loading section text, size 0xb4e0 lma 0x100002b0
Loading section .ARM.exidx, size 0x8 lma 0x1000b790
Loading section initlevel, size 0xe0 lma 0x1000b798
Loading section device_area, size 0x2ac lma 0x1000b878
Loading section sw_isr_table, size 0x4d8 lma 0x1000bb24
Loading section _static_thread_data_area, size 0x60 lma 0x1000c000
Loading section gpio_driver_api_area, size 0x24 lma 0x1000c060
Loading section i2c_driver_api_area, size 0x18 lma 0x1000c084
Loading section sensor_driver_api_area, size 0x54 lma 0x1000c09c
Loading section clock_control_driver_api_area, size 0x1c lma 0x1000c0f0
Loading section uart_driver_api_area, size 0x14 lma 0x1000c10c
Loading section log_const_area, size 0x98 lma 0x1000c120
Loading section log_backend_area, size 0x10 lma 0x1000c1b8
Loading section rodata, size 0x281c lma 0x1000c1c8
Loading section datas, size 0xa8 lma 0x1000e9e4
Loading section device_states, size 0x28 lma 0x1000ea8c
Loading section log_mpsc_pbuf_area, size 0x3c lma 0x1000eab4
Loading section log_msg_ptr_area, size 0x4 lma 0x1000eaf0
Loading section k_mem_slab_area, size 0x20 lma 0x1000eaf4
Loading section k_heap_area, size 0x18 lma 0x1000eb14
Loading section k_sem_area, size 0x10 lma 0x1000eb2c
Loading section k_queue_area, size 0x14 lma 0x1000eb3c
Loading section .last_section, size 0x4 lma 0x1000eb50
[==================================================] 100%p
0009426 I Erased 65536 bytes (8 sectors), programmed 60416 bytes (118 pages), skipped 0 bytes (0 pages) at 10.00 kB/s [loader]
Start address 0x10003bd0, load size 60236
Transfer rate: 9 KB/sec, 1158 bytes/write.
(gdb) step
122	    msr msp, r0
(gdb) step
137	    bl soc_reset_hook
(gdb) step
...
```

That's it!

[Raspberry Pi Debug Probe]:https://www.raspberrypi.com/documentation/microcontrollers/debug-probe.html

