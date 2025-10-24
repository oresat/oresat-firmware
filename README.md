# Oresat Zephyr Getting Started Guide

This documents how to install and use the Oresat firmware for Zephyr.

## Setup

**NOTE 1:** This mostly rework of the [Zephyr Getting Started Guide].

**NOTE 2:** Below we use `~/src/oresat/firmware` as the root folder for installing all the source code. Modify as you wish.

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

- Debian Linux

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

1. CMake: 3.20.5
  `cmake --version`
2. Python: 3.10
  `python3 --version`
3. Devicetree compiler: 1.4.6
  `dtc --version`

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

#### Get the source code for common firmware repo, all apps, zephyr, and zephyr modules:

> **NOTE:**
>
> **Here are the main deviations from the [Zephyr Getting Started Guide]:**
>
> 1. *We initialize `west` from the zephyr branch of our common firmware repository, not from Zephyr itself.*
> 2. *The common firmware zephyr branch contains a `west.yml` file which intentionally selects a specific Zephyr official release.
> The Zephyr `main` branch is too much in flux to base a real project like Oresat on.*

```bash
mkdir -p ~/src/oresat/firmware
cd ~/src/oresat/firmware
west init -m https://github.com/oresat/oresat-firmware --mr zephyr
west update
```

#### Export Zephyr CMake package:

```bash
west zephyr-export
```

#### Install Python dependencies:

```bash
west packages pip --install
```

#### Install the Zephyr SDK:

```bash
cd ~/src/oresat/firmware/zephyr
west sdk install
```

#### Export Zephyr environment:

```bash
cd ~/src/oresat/firmware/zephyr
source ./zephyr-env.sh
```
**NOTE: it is helpful to also add these to your ~/.bashrc:**
```
export ZEPHYR_SDK_INSTALL_DIR=$HOME/zephyr-sdk-0.17.2
export ZEPHYR_TOOLCHAIN_VARIANT=zephyr
```
Obviously use the SDK version number actually installed.

#### Add udev rule:

```bash
sudo cp $ZEPHYR_SDK_INSTALL_DIR/sysroots/x86_64-pokysdk-linux/usr/share/openocd/contrib/60-openocd.rules /etc/udev/rules.d
sudo udevadm control --reload
```

### Install OreSat Configs

```bash
pip install oresat-configs~=1.0.0
```

### ST-Link

Oresat 0.0 and 0.5 used the STM32F091 processor. The Oresat Card Debug Board contains an ST-Link V3 daughter board which
supports this, and also provides a UART interface. The old documentation provides [ST Toolchain Setup] directions.

### Segger J-Link

In order to flash and debug the NXP MCXN947, you will need a compatible debug adapter.
The Segger J-Link debugger, though expensive, works well.

You will need to install the required J-Link software.

Visit [Segger J-Link Downloads], download the latest J-Link software for your OS,
and follow their installation instructions.

### Raspberry Pi Debug Probe

To use the Raspi debug probe with the NXP MCXN947, follow the instructions: [Raspberry Pi Debug Probe].

### Test compile and flash

```bash
cd ~/src/oresat/firmware/apps/template
west build -p always -b nucleo_f091rc .
west flash --runner openocd
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
[ST Toolchain Setup]:https://github.com/oresat/oresat-firmware/blob/master/doc/toolchain.md
