# oresat-firmware

OreSat firmware for Zephyr common code and main manifest repository.

Initialize a new west workspace from this repository --it contains the top level west.yml file for all Oresat card applications.

## Setup

**NOTE:** This mostly rework of https://docs.zephyrproject.org/latest/develop/getting_started/index.html

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
    For the curious, this is mostly the same list as in the official Zephyr getting started,
    except that we do not require: `gcc gcc-multilib g++-multilib`
	 but instead add: `python3-pip python3-setuptools python3-wheel stlink-tools`

### Install Zephyr SDK

- Arch Linux (from AUR)

    ```bash
    paru -S zephyr-sdk-bin
    ```

- Everything else

    ```bash
    sudo cd /opt
    sudo wget https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v0.16.8/zephyr-sdk-0.16.8_linux-x86_64.tar.xz
    sudo tar xvf zephyr-sdk-0.16.8_linux-x86_64.tar.xz
    sudo cd zephyr-sdk-0.16.8
    sudo ./setup.sh
    ```

### Add udev rule:

```bash
sudo cp /opt/zephyr-sdk-0.16.8/sysroots/x86_64-pokysdk-linux/usr/share/openocd/contrib/60-openocd.rules /etc/udev/rules.d
sudo udevadm control --reload
```

### Create a new virtual environment:

```bash
python3 -m venv ~/zephyrproject/.venv
```

### Activate the virtual environment:

```bash
source ~/zephyrproject/.venv/bin/activate
```

Once activated your shell will be prefixed with (.venv). The virtual environment can be deactivated at any time by running deactivate.

**Note**

Remember to activate the virtual environment every time you start working.

### Install west

```bash
pip install west
```

Alternatively, your OS's package manager might have a west package. Debian Testing does:
```bash
sudo apt install west
```

**However** it is highly recommended to use the pip (or uv) version as it will be the most up-to-date.

### Get the source code for common firmware repo, all apps, zephyr, and zephyr modules

```bash
mkdir -p ~/src/oresat/firmware
cd ~/src/oresat/firmware
west init -m https://github.com/oresat/oresat-firmware --mr zephyr
west update
```

### Export Zephyr CMake package:

```bash
west zephyr-export
```

### Export zephyr environment

```bash
cd ~/src/oresat/firmware/zephyr
source ./zephyr-env.sh
```
NOTE: it is helpful to also add these to your ~/.bashrc:
```
export ZEPHYR_SDK_INSTALL_DIR=/opt/zephyr-sdk-0.16.8
export ZEPHYR_TOOLCHAIN_VARIANT=zephyr
```

### Install the rest of Zephyr's Python dependencies

```bash
pip install -r ~/src/oresat/firmware/zephyr/scripts/requirements.txt
```

### Install OreSat Configs

```bash
pip install --user oresat-configs~=1.0.0
```

### Test compile and flash

```bash
cd ~/src/oresat/firmware/apps/template
west build -p always -b nucleo_f091rc .
west flash --runner openocd
```

### Segger J-Link

In order to flash and debug the NXP MCXN947, you will need a Segger J-Link debugger
and install the required J-Link software.

Visit [Segger J-Link Downloads], download the latest J-Link software for your OS,
and follow their installation instructions.

## Tools

- [clang-format]: Used to auto format the code. Can be installed with
  the `clang-format` package.

### CAN Tools

Since the main communication bus on OreSat is a CAN bus, CAN bus monitoring
tools are needed for development and testing.

- [candump]: Useful for monitoring if there is some CAN communication. Can be
  installed with `can-utils` package.
- [SavvyCAN]: A GUI to decode and display/graph signals from CAN messages.
  Use `oresat-configs` to generate the .dbc file used to decode CAN messages
  and their signals with SavvyCAN.

[clang-format]:https://clang.llvm.org/docs/ClangFormat.html
[candump]:https://manpages.debian.org/testing/can-utils/candump.1.en.html
[SavvyCAN]:https://github.com/collin80/SavvyCAN
[Segger J-Link Downloads]:https://www.segger.com/downloads/jlink/
