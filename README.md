# oresat-firmware
## General Information
This is the central repository for OreSat firmware development.

OreSat uses ChibiOS, a Real Time Operating System (RTOS), for Command, Control, and Communication, as well as for its various subsystems. All subsystems communicate via CAN bus, with the C<sup>3</sup> system controller managing the overall satellite, as well as critical communications with ground stations. Subsystems handle specific aspects of satellite operation. The various subsystems are listed below.

Further general documentation can be found [here](doc/README.md)

### Prerequisites
In order to have a working environment, you must initialize the ChibiOS submodule after cloning this respository. In addition, you must have the necessary toolchain components to build, interface, and debug a board.

To initialize the ChibiOS submodule, run:
```git submodule update --init```

Requires `make`, `arm-none-eabi-gcc`, `arm-none-eabi-gdb`, and `openocd` to build/write/debug.

### Subsystems
* C<sup>3</sup> (Command, Control, Communication) system controller
* ACS (Attitude Control System)

## ACS (Attitude Control System)
### Firmware
* [General information and overview](https://github.com/oresat/oresat-firmware/wiki/ACS-Firmware).
* [Code Documentation](http://oresat.org/ACS-Capstone-2018/firmware-doc/files.html)

### Hardware
[General Information and Overview](https://github.com/oresat/oresat-acs-board) (start with the README.)
