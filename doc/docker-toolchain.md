# Docker Toolchain

OreSat fimware toolchain in a docker container.

This allows a developer to modify any source code with their favorite IDE or
text editor and then compile the code in the docker container without needing
to build the toolchain for their specific systems and allows all oresat fimware
developers to have the exact same toolchain reguardless of their developing
system's OS.

The container only contains the toolchain no `oresat-fimware` source code, so
the source needs to be add as volume to the container when the container is used.

The [docker-toolchain.sh] script is for convience rather than having to type a
long docker command every time the source code needs to be compiled. The script
will add the `oresat-fimware` directory to the container allow the fimware to
be compiled in the container. For Linux host **only**, it also can automatically
detect any STLINK programmers and add them to the container, allowing the docker
container to flash images to hardware. Docker for Windows and Mac host does not
support USB pass-though, so the [docker-toolchain.sh] cannot flash images when
used on a Windows or Mac host.

## Setup

- **Linux users only**:
  - Make sure `usbutils` is install on your system, install it if not.
  - Install `docker` for your system
  - Enable and start docker daemon:
    - `$ sudo systemctl enable docker`
    - `$ sudo systemctl start docker`
  - Add your user to the `docker` group, so `sudo` will not be require for all
    `docker` commands. Replace `USERNAME` with your username:
    `$ sudo usermod -aG docker USERNAME`
  - Log out or reboot your system for the new group to take effect
- **Mac users only**:
  - Install `docker`, see https://docs.docker.com/desktop/mac/install/
- **Windows users only**:
  - Install `docker`, see https://docs.docker.com/desktop/windows/install/
- Clone oresat-fimware repo:
  `$ git clone --recurse-submodules git:https://github.com:oresat/oresat-fimware.git`
- Swap to oresat-fimware directory: `$ cd oresat-fimware`
- Pull and test docker toolchain by building an app:
  `$ ./docker-toolchain.sh build src/f0/app_blinky`
  - **NOTE:** This will automatically pull the docker image on first run

## Usage

- Must be in the root directory of the `oresat-fimware` repo.
- Use the Docker toolchain: `$ ./docker-toolchain.sh COMMAND APP SERIAL`.
  - **NOTE:** `SERIAL` is an optional arg for `write` and `gdb` commands to specify
    which stlink to use in case of multiple stlinks.
- Examples:
  - `$ ./docker-toolchain.sh info`
  - `$ ./docker-toolchain.sh build src/f0/app_solar`
  - `$ ./docker-toolchain.sh write src/f0/app_solar`
  - `$ ./docker-toolchain.sh write src/f0/app_solar 0123456789ABCDEF`
  - `$ ./docker-toolchain.sh gdb src/f0/app_solar`
  - `$ ./docker-toolchain.sh gdb src/f0/app_solar 0123456789ABCDEF`

[docker-toolchain.sh]: ../docker-toolchain.sh
