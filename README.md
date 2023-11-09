# oresat-firmware
## General Information
This is the central repository for OreSat firmware development.

OreSat uses ChibiOS, a Real Time Operating System (RTOS), for Command, Communication, and Control (C<sup>3</sup>), as well as for its various subsystems. All subsystems communicate via the ECSS CANbus Extension Protocol which is itself based on the CANopen protocol stack and implements the CCSDS Spacecraft Onboard Interface Services recommendations. The C<sup>3</sup> system controller manages the overall satellite, as well as critical communications with ground stations. Subsystems handle specific aspects of satellite operation. The various subsystems are listed below.

Further general documentation can be found [here](doc)

## Getting Started
### Prerequisites
In order to get started developing for OreSat, you must clone this repository and initialize the ChibiOS and CANopenNode submodules after cloning this respository. In addition, you must have the necessary toolchain components to build, interface, and debug a board.

#### Cloning
Cloning requires `git` or some GUI variant of it to clone the
repository. An example of cloning via the command line is shown below.

```
username@hostname:~
➜ cd Projects
username@hostname:~/Projects
➜ git clone git@github.com:oresat/oresat-firmware.git
Cloning into 'oresat-firmware'...
remote: Enumerating objects: 314, done.
remote: Counting objects: 100% (314/314), done.
remote: Compressing objects: 100% (203/203), done.
remote: Total 7257 (delta 217), reused 194 (delta 110), pack-reused 6943
Receiving objects: 100% (7257/7257), 5.55 MiB | 32.28 MiB/s, done.
Resolving deltas: 100% (4838/4838), done.
username@hostname:~/Projects
➜ cd oresat-firmware
username@hostname:oresat-firmware on  master
➜
```

#### Submodules
Once the repository is cloned, you need to initialize the submodules.
Additionally, this step needs to be done any time submodule references
are updated. This is accomplished by the following command.

```
git submodule update --init
```

An example of this is shown below

```
username@hostname:oresat-firmware on  master
➜ git submodule update --init
Submodule 'ChibiOS' (https://github.com/ChibiOS/ChibiOS.git) registered
for path 'ChibiOS'
Submodule 'common/CANopenNode'
(https://github.com/heliochronix/CANopenNode.git) registered for path
'common/CANopenNode'
Cloning into '/home/username/Projects/oresat-firmware/ChibiOS'...
Cloning into
'/home/username/Projects/oresat-firmware/common/CANopenNode'...
Submodule path 'ChibiOS': checked out
'81e586a948125ef1d885f7ddbdcf6591883ff594'
remote: Enumerating objects: 70, done.
remote: Counting objects: 100% (70/70), done.
remote: Total 92 (delta 70), reused 70 (delta 70), pack-reused 22
Unpacking objects: 100% (92/92), 17.81 KiB | 588.00 KiB/s, done.
From https://github.com/heliochronix/CANopenNode
 * branch            58836f4083b3607368471f48711d7c1b03576ce8 ->
   FETCH_HEAD
Submodule path 'common/CANopenNode': checked out
'58836f4083b3607368471f48711d7c1b03576ce8'
username@hostname:oresat-firmware on  master
➜
```

#### Building and Debugging
This project requires the following set of tools to build/write/debug firmware.
Please refer to your OS documentation or package installation tool to determine
how to install these tools, as it varies between systems.

Tools required:
* make
* arm-none-eabi-gcc
* arm-none-eabi-gdb   (may require a symlink to gdb-multiarch on Debian systems)
* openocd             (Required, this is how we program and debug things)
* stlink              (Gets udev rules up and running, may be helpful)
* srecord
* oresat-configs

To install oresat-configs: 
* `$ git clone https://github.com/oresat/oresat-configs`
* `$ cd oresat-configs`
* `$ pip install -r requirements.txt`
* `$ ./build_and_install.sh`

PLEASE NOTE: If you use OpenOCD, the latest "official" release of OpenOCD in
package managers is several years old. You MUST build it from source for it
to work with our boards, as there have been over 1000 commits since the
last official release and several of our boards were added since then.

Please refer to [Platform Specific Installation Instructions](doc/toolchain.md)
for details on how to do this on a per-system basis.

#### Test your toolchain
To test that your build system works correctly, it's recommended that you build one of the `app_blinky` applications and write it to a dev board successfully. Here are the links for the various versions of the app with further documentation:
* [NUCLEO64_STM32F091RC](src/f0/app_blinky)
* [NUCLEO144 STM32F439ZI](src/f4/app_blinky)
* [NUCLEO64 STM32L452RE](src/l4/app_blinky)

### Creating an app
Once you have a working toolchain in place, the next step is to copy an existing
app_template for your microcontroller to a new app_projectname. The currently
supported MCUs for OreSat are listed below, and link to the relevant folders and READMEs.

#### Supported MCUs
* [STM32F091xC](src/f0)
* [STM32F439Zx](src/f4)
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
