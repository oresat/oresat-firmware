# Toolchain Setup

This documentation describes the steps needed to configure a local development
toolchain on various system platforms (Linux, macOS, etc).

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

```sh
sudo apt install -y \
    autoconf \
    automake \
    gcc-arm-none-eabi \
    gdb-multiarch \
    git \
    libcapstone4 \
    libftdi1-2 \
    libgpiod2 \
    libhidapi-hidraw0 \
    libtool \
    libusb-1.0-0 \
    libusb-1.0-0-dev \
    make \
    openocd \
    pkg-config \
    srecord \
    stlink-tools \
    tcl \
    xxd
```

## macOS

These instructions assume the use of the [Homebrew](https://brew.sh/) package
manager.

1.  Install Python and pip (if they aren't already installed).

    There are several ways to do this. To ensure you're using the latest
    (or a specific) Python version, consider using a Python version manager.
    The following instructions describe how to use
    [pyenv](https://github.com/pyenv/pyenv).

    ```sh
    brew install pyenv
    ```

    Now, install latest python (replace `<version>`, e.g. `3.13.3`):

    ```sh
    pyenv install <version>
    pyenv global <version>
    ```

2.  Using Homebrew, add the required "taps" (package repositories).

    ```sh
    brew tap RetroReversing/gdb-multiarch
    brew install --cask gcc-arm-embedded
    ```

3.  Now, use Homebrew to install the required system tools and dependencies.

    ```sh
    brew install \
        arm-none-eabi-newlib \
        gdb-multiarch \
        make \
        openocd \
        srecord \
        stlink
    ```

4.  Add `arm-none-eabi` to your PATH.

    ```sh
    export PATH="/Applications/ArmGNUToolchain/14.2.rel1/arm-none-eabi/bin:$PATH"
    ```

    If you want to persist this change in future terminal sessions, add it to
    whichever `.rc` file you are using. Since macOS uses
    [zsh](https://www.zsh.org/) by default, here's how it's done:

    ```sh
    echo 'export PATH="/Applications/ArmGNUToolchain/14.2.rel1/arm-none-eabi/bin:$PATH"' >> ~/.zshrc
    source ~/.zshrc
    ```

Your toolchain is now configured.
