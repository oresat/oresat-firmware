# Vagrant

Vagrant allows for quickly and easily building and destroying a Virtual
Machines for development. Vagrant basically wraps around VirtualBox and
is configured thru a Vagrantfile.

Vagrant is incredibly useful for quickly spinning up a VM with the
extact same oresat-firmware toolchain used by all developers.

## Setup

- Install dependencies
  - Arch Linux
    - `$ paru -S vagrant virtualbox virtualbox-host-modules-arch virtualbox-ext-oracle`
    - `$ sudo usermod -aG vboxusers $USER`
    - Logout or reboot your system for the usermod to take effect
  - Debian / Ubuntu
    - `$ sudo apt install vagrant`
    - Download VirtualBox from https://www.virtualbox.org/wiki/Linux_Downloads
    - `$ sudo usermod -aG vboxusers $USER`
    - Download the Oracle Extension Pack from https://www.virtualbox.org/wiki/Downloads
    - Install the extension (**change** `PATH_TO_EXT_PACK`): `$ sudo vboxmanage extpack install PATH_TO_EXT_PACK`
    - Logout or reboot your system for the usermod to take effect
  - Windows / MacOS
    - Download and install VirtualBox and download the Oracle Extension Pack
      (it allows for USB passthrough). They can both be downloaded from
      https://www.virtualbox.org/wiki/Downloads
    - Open VirtualBox and goto `File > Tools > Extension Pack Manager` and
      install extension pack.
    - Download and install Vagrant from https://www.vagrantup.com/
- Make the Vagrant box / VM: `$ vagrant up`
- Check USB passthrough is working
  - SSH onto the box: `$ vagrant ssh`
  - Plug in an STLink / Nucleo into your laptop:
  - Run `lsusb` in the VM, you should see a STLink device:
  ```
  vagrant@bullseye:~$ lsusb
  Bus 001 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub
  Bus 002 Device 002: ID 0483:374b STMicroelectronics ST-LINK/V2.1
  Bus 002 Device 001: ID 1d6b:0001 Linux Foundation 1.1 root hub
  ```
- Now you can use favorite GUI or text editor on your host OS, while
  using the VM to compile and flash the firmware.
- When the Vagrant box / VM is no longer needed just do a `$ vagrant destroy`.
