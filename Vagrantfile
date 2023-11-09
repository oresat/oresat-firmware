# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure("2") do |config|
  config.vm.box = "debian/bullseye64"

  # sync oresat-firmware directory
  config.vm.synced_folder "../oresat-firmware", "/home/vagrant/oresat-firmware"
 
  # install everything!
  config.vm.provision "shell", inline: <<-SHELL
    apt-get update
    apt-get install -y \
      autoconf \
      automake \
      bear \
      can-utils \
      curl \
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
      python3-pip \
      srecord \
      stlink-tools \
      tcl \
      usbutils \
      vim \
      xxd
    pip3 install \
      eds-utils \
      oresat-olaf
    ln -s /usr/bin/gdb-multiarch /usr/bin/arm-none-eabi-gdb
    git clone --recurse-submodules https://github.com/openocd-org/openocd && \
      cd openocd && \
      ./bootstrap && \
      ./configure --prefix=/usr --disable-werror --enable-stlink && \
      make && \
      make install && \
      cd .. && \
      rm -rf openocd
    curl -Lo gcc-arm-none-eabi.tar.xz "https://developer.arm.com/-/media/Files/downloads/gnu/12.2.mpacbti-rel1/binrel/arm-gnu-toolchain-12.2.mpacbti-rel1-x86_64-arm-none-eabi.tar.xz"    
    mkdir /opt/gcc-arm-none-eabi
    tar xf gcc-arm-none-eabi.tar.xz --strip-components=1 -C /opt/gcc-arm-none-eabi
    echo 'export PATH=$PATH:/opt/gcc-arm-none-eabi/bin' | sudo tee -a /etc/profile.d/gcc-arm-none-eabi.sh
    source /etc/profile
    rm -rf gcc-arm-none-eabi.tar.xz
  SHELL

  # enable USB Controller on VirtualBox and filter for STLink and CANable
  config.vm.provider "virtualbox" do |vb|
    vb.customize ["modifyvm", :id, "--usb", "on"]
    vb.customize ["modifyvm", :id, "--usbehci", "on"]
    vb.customize ["usbfilter", "add", "0", "--target", :id,
      "--name", "Any STM32 STLink",
      "--manufacturer", "STMicroelectronics",
      "--remote", "no"
    ]
    vb.customize ["usbfilter", "add", "1", "--target", :id,
      "--name", "Any CANable",
      "--manufacturer", "Protofusion Labs",
      "--remote", "no"
    ]
  end
end
