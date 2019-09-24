# oresat-firmware
## General Information
This is the central repository for OreSat firmware development.

OreSat uses ChibiOS, a Real Time Operating System (RTOS), for Command, Communication, and Control (C<sup>3</sup>), as well as for its various subsystems. All subsystems communicate via the ECSS CANbus Extension Protocol which is itself based on the CANopen protocol stack and implements the CCSDS Spacecraft Onboard Interface Services recommendations. The C<sup>3</sup> system controller manages the overall satellite, as well as critical communications with ground stations. Subsystems handle specific aspects of satellite operation. The various subsystems are listed below.

Further general documentation can be found [here](doc)

## Getting Started
### Prerequisites
In order to have a working environment, you must initialize the ChibiOS and CANopenNode submodules after cloning this respository. In addition, you must have the necessary toolchain components to build, interface, and debug a board.

To initialize the submodules, or to resync after submodule references are updated, run:
```git submodule update --init```

This project requires `make`, `arm-none-eabi-gcc`, `arm-none-eabi-gdb`, and `openocd` to build/write/debug. Refer to your OS documentation or package installation tool to determine how to install these tools.

### Creating an app
Once you have a working toolchain in place, the next step is to copy an existing app_template for your microcontroller to a new app_projectname. The currently supported MCUs for OreSat are listed below, and link to the relevant folders and READMEs.

#### Supported MCUs
* [STM32F042K6](src/f0)
* [STM32F446RE](src/f4)
* [STM32L452RE](src/l4)

## Subsystems
### ACS (Attitude Control System)
#### Firmware
* [General information and overview](https://github.com/oresat/oresat-firmware/wiki/ACS-Firmware).
* [Code Documentation](http://oresat.org/ACS-Capstone-2018/firmware-doc/files.html)

#### Hardware
[General Information and Overview](https://github.com/oresat/oresat-acs-board) (start with the README.)

## Notes
### Troubleshooting
If the a submodule reference gets updated in oresat-firmware, run the following command again to sync to the proper reference and checkout a working copy:
```git submodule update --init```
