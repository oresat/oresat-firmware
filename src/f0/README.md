# STM32F091xC

This is the source directory for all STM32F091xC applications.
This device contains an ARM Cortex-M0, and is also known as an M0 or F0.

This MCU typically implements low power OreSat subsystems,
such as solar panels, batteries, and some sensors.

Note that the development boards use an STM32F091RC, but that OreSat boards
use the STM32F091CC. The only difference between these two packages is the
number of available pins.

[STM32F091 Reference Manual](https://www.st.com/resource/en/reference_manual/dm00031936-stm32f0x1stm32f0x2stm32f0x8-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)

[STM32F091 Datasheet](https://www.st.com/resource/en/datasheet/stm32f091cc.pdf)


## Testing the toolchain
After having installed the required toolchain components as described in
the Prerequesites section of the main README, it is good to test that
they all function as expected. This can be done by building and flashing
the `app_blinky` application that simply blinks an LED.

In order to accomplish this, from this directory simply execute the
following:

```
cd app_blinky
make
make write
```
This should result in a clean no-error build, followed by a successful
write to the board and a flashing green LED. If this all works,
congratulations! Your toolchain is working and you can begin developing.

## Creating an app
The template to copy for new applications is [app_protocard](app_protocard) or
[app_devboard](app_devboard). To create a new app, simply make a copy of the
directory and name it whatever you like. From this directory:

```
cp -R app_protocard app_<name>
```

Then, open the Makefile `app_<name>/Makefile` and edit the line `PROJECT =` to whatever name
you've chosen:

If building for a specific board, also update the `BOARD =` line to the
board defined in the `boards` directory.
```
PROJECT   = app_<name>
```

At this point, you simply write code in source files under the `sources`
directory, include the appropriate header file in the main.c file,
and finally register your worker with the main OreSat application.

See the doc folder for further documentation.



## Flash Memory Layout
The STM32F091 has 64 flash sectors of 4kbytes each. These are layed out to allow for a bootloader.


Firmware Image Layout. Total of ???k in length. The first 1k is metadata, the remaining ??k is executable code.
Relative Address 0-0x400: Image meta data. crc32, length, version
- 0x0000: 4 byte CRC32
- 0x0004: 4 byte firmware image data length
- 0x0008: 4 byte firmware version
- 0x000C to 0x0400: padding
Relative Address 0x0400-0xC800: Compiled firmware
