FROM debian:bookworm-slim

RUN apt update && apt -y install \
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
  pkg-config \
  python3 \
  srecord \
  stlink-tools \
  tcl \
  xxd \
  && rm -rf /var/lib/apt/lists/*

RUN git clone --recurse-submodules https://github.com/openocd-org/openocd && \
    cd openocd && \
    ./bootstrap && \
    ./configure --prefix=/usr --disable-werror --enable-stlink && \
    make && \
    make install && \
    cd .. && \
    rm openocd -rf

RUN mkdir /oresat-firmware
WORKDIR /oresat-firmware

RUN ln -s /usr/bin/gdb-multiarch /usr/bin/arm-none-eabi-gdb
