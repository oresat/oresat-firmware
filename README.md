# Oresat Zephyr Getting Started Guide

# *** ZEPHYR 4.5.0 WORKING BRANCH ***

This documents how to install and use the Oresat firmware for Zephyr.

---

**ATTENTION:**

**The `main` branch in the `oresat-firmware` repository is now the one used for Zephyr, and is now the default branch.
Previous references to a `zephyr` branch are no longer correct, and have been changed below.**

**The old `master` branch containing ChibiOS firmware for STM32-based cards is now called `oresat05-master`.**

---

## Setup

> **NOTE 1:** This mostly rework of the [Zephyr Getting Started Guide].

> **NOTE 2:** Below we use `~/src/oresat/firmware` as the root folder for installing all the source code. Modify as you wish.

> **NOTE 3:** A document explaining the [Oresat Zephyr Repository Organization] is here.

### Select and Update OS

The instructions below apply to Debian-based Linux distributions and Arch Linux. For Windows or MacOS, follow the
related information in the above guide.

Update your OS with its latest packages.

### Install dependencies

- Arch Linux

    ```bash
    sudo pacman -S git cmake ninja gperf ccache dfu-util dtc wget \
      python-dev python-pip python-setuptools python-tk python-wheel \
      xz file make sdl2 stlink
    ```

- Debian or Ubuntu Linux

    ```bash
    sudo apt install --no-install-recommends git cmake ninja-build gperf \
      ccache dfu-util device-tree-compiler wget python3-dev python3-venv python3-tk \
      xz-utils file make libsdl2-dev libmagic1 \
	   python3-pip python3-setuptools python3-wheel stlink-tools
    ```
    For the curious, this is mostly the same list as in the official getting started guide,
    except that we do not require: `gcc gcc-multilib g++-multilib`
	 but instead add: `python3-pip python3-setuptools python3-wheel stlink-tools`

Make sure you have at least the minimum required versions of:

1. CMake: 3.28.0
  `cmake --version`
2. Python: 3.12
  `python3 --version`
3. Devicetree compiler: 1.4.6
  `dtc --version`

**The versions could be higher for later versions of Zephyr than the 4.5.0 referenced here.**

### Get Oresat common code, Zephyr, and Python dependencies

#### Create a new virtual environment:

```bash
python3 -m venv ~/zephyrproject/.venv
```

#### Activate the virtual environment:

```bash
source ~/zephyrproject/.venv/bin/activate
```

Once activated your shell will be prefixed with (.venv). The virtual environment can be deactivated at any time by running deactivate.

**Note**

Remember to activate the virtual environment every time you start working.

#### Install west:

```bash
pip install west
```

Alternatively, your OS's package manager might have a west package. Debian Testing does:
```bash
sudo apt install west
```

**However** it is highly recommended to use the pip (or uv) version as it will be the most up-to-date.

---
#### Get the source code for common firmware repo, all apps, zephyr, and zephyr modules:

> **NOTE:**
>
> **Here are the main deviations from the [Zephyr Getting Started Guide]:**
>
> 1. *We initialize `west` from the main branch of our common firmware repository, not from Zephyr itself.*
> 2. *The common firmware main branch contains a `west.yml` file which intentionally selects a specific Zephyr official release.
> The Zephyr `main` branch is too much in flux to base a real project like Oresat on.*

```bash
mkdir -p ~/src/oresat/firmware
cd ~/src/oresat/firmware
west init -m https://github.com/oresat/oresat-firmware --mr main
west update
```

---
#### Updating to a newer release of oresat-firmware main branch:

> **IMPORTANT: when a newer version of this repository is available, you must do these steps!**

1. If you changed anything in the code (in an app, here in common, or in zephyr), follow the instructions in [Oresat Zephyr Repository Organization-Tasks]
2. Do **west patch clean** -- this undoes any patches applied to the zephyr, modules, or bootloader trees by a previous *west update*; should be no errors
3. Do **cd ~/src/oresat/firmware/common** -- change directory to the `common` folder; this is where the contents of `oresat-firmware` `main` branch are
4. Do **git pull** -- pull in the latest changes to the `oresat-firmware` `main` branch
5. Do **west update** and watch the log output – it will likely switch away from your branch, and tell you this, and give you directions how to switch back;
	  **watch for errors and if any, ask for help in Slack or via github issues before proceeding!**
6. Do **west patch apply** -- this applies any patches in the zepyr-firmware/main branch to the zephyr, modules, or bootloader trees by this *west update*;
	  warnings are ok; **watch for any errors and if any, ask for help before proceeding!**

```bash
west patch clean
cd ~/src/oresat/firmware/common
git pull
west update
west patch apply
```
---

#### Install Python dependencies:

```bash
west packages pip --install
```

#### Export Zephyr CMake package:

```bash
west zephyr-export
```

#### Install the Zephyr SDK:

```bash
cd ~/src/oresat/firmware/zephyr
swest sdk install
```

#### Export Zephyr environment:

```bash
cd ~/src/oresat/firmware/zephyr
source ./zephyr-env.sh
```
**NOTE: it is helpful to also add these to your ~/.bashrc:**
```
export ZEPHYR_SDK_INSTALL_DIR=$HOME/zephyr-sdk-1.0.1
export ZEPHYR_TOOLCHAIN_VARIANT=zephyr
```
For the value of `ZEPHYR_SDK_INSTALL_DIR`, use the SDK version number actually installed. It was `0.17.2` for Zephyr 4.2.0 and `1.0.1` for Zephyr 4.4.1 through 4.5.0.

#### Add udev rule for openocd

This is needed when working with the STM32 version of the battery card. It is not needed for the MCXN947 cards with the Oresat Card Debug Board v3.

```bash
sudo cp $ZEPHYR_SDK_INSTALL_DIR/sysroots/x86_64-pokysdk-linux/usr/share/openocd/contrib/60-openocd.rules /etc/udev/rules.d
sudo udevadm control --reload
```

### Install OreSat Configs

```bash
pip install oresat-configs~=1.2.0
```

### Install Software for Programmer/Debugger Adapters

#### OreSat Card Debug Board v3 (required for Oresat1)

To use with the NXP MCXN947, follow the instructions: [Raspberry Pi Debug Probe].

This debug adapter works very well with probe-rs. Support for this is integrated into all of the Oresat card apps.

#### Segger J-Link (optional)

In order to flash and debug the NXP MCXN947, you will need a compatible debug adapter.
The Segger J-Link debugger, though expensive, works well.

You will need to install the required J-Link software.

Visit [Segger J-Link Downloads], download the latest J-Link software for your OS,
and follow their installation instructions.

#### ST-Link (optional)

Oresat 0.0 and 0.5 used the STM32F091 processor. The Oresat Card Debug Board v2 contains an ST-Link V3 daughter board which
supports this, and also provides a UART interface. The old documentation provides [ST Toolchain Setup] directions.

### Test compile and flash

```bash
cd ~/src/oresat/firmware/apps/template
west build -p always
west flash
```

## Tools

Use [clang-format] to auto format the code. It can be installed with the `clang-format` package.

### CAN Tools

Since the main communication bus on OreSat is a CAN bus, CAN bus monitoring
tools are needed for development and testing.

- [candump]: Useful for monitoring if there is some CAN communication. Can be
  installed with `can-utils` package.
- [SavvyCAN]: A GUI to decode and display/graph signals from CAN messages.
  Use `oresat-configs` to generate the .dbc file used to decode CAN messages
  and their signals with SavvyCAN.

[Zephyr Getting Started Guide]:https://docs.zephyrproject.org/latest/develop/getting_started/index.html
[clang-format]:https://clang.llvm.org/docs/ClangFormat.html
[candump]:https://manpages.debian.org/testing/can-utils/candump.1.en.html
[SavvyCAN]:https://github.com/collin80/SavvyCAN
[Segger J-Link Downloads]:https://www.segger.com/downloads/jlink/
[Raspberry Pi Debug Probe]:README-pyocd-RPDP.md
[ST Toolchain Setup]:https://github.com/oresat/oresat-firmware/blob/oresat05-master/doc/toolchain.md
[Oresat Zephyr Repository Organization]:README-Oresat-Zephyr-Repo-Organization.md
[Oresat Zephyr Repository Organization-Tasks]:README-Oresat-Zephyr-Repo-Organization.md#tasks
