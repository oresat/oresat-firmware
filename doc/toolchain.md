# Toolchain Setup

This will briefly describe the steps needed to get going on various
types of systems.

## Arch Linux

The build-related tools are acquired through the following packages:

`$ pacman -Sy base-devel arm-none-eabi-binutils arm-none-eabi-gcc
arm-none-eabi-gdb arm-none-eabi-newlib stlink python`

Both `openocd` and `srecord` must be install thru the AUR
(Arch User Repository). Either use a AUR helper like `paru` or `yay` or
built it manually.

### AUR Helper example using paru

- `$ paru -S openocd-git srecord`

### AUR Helper example using yay

- `$ yay -S openocd-git srecord`

### AUR manual build

- Clone AUR openocd-git repo: `$ git clone https://aur.archlinux.org/openocd-git`
- `$ cd openocd-git`
- Build and install Arch Linux package: `$ makepkg -si`

## Debian Linux (and derivatives)

The packages needed for Debian are as follow:

`$ sudo apt install autoconf automake gcc-arm-none-eabi gdb-multiarch
 git libcapstone4 libftdi1-2 libgpiod2 libhidapi-hidraw0 libtool
 libusb-1.0-0 libusb-1.0-0-dev make pkg-config python3 srecord
 stlink-tools tcl xxd`

Make a symbollic link to `arm-none-eabi-gdb`:

`$ sudo ln -s /usr/bin/gdb-multiarch /usr/bin/arm-none-eabi-gdb`

OpenOCD can be built as follow:

- `$ git clone https://git.code.sf.net/p/openocd/code openocd`
- `$ cd openocd`
- `$ ./bootstrap`
- `$ ./configure --prefix=/usr --disable-werror --enable-stlink`
- `$ make`
- `$ sudo make install`
