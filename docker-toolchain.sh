#!/bin/bash

help_msg() {
    echo "OreSat firmware docker toolchain"
    echo "Usage: ./docker-toolchain.sh command path_to_app [options]..."
    echo "Command options:"
    echo "  help                        This message"
    echo "  info                        Get the output of \"st-info --probe\""
    echo "  build                       Build an image"
    echo "  write                       Write an image"
    echo "  gdb                         Run gdb"
    echo "Options:"
    echo "  <serial>                    Specify stlink serial for write/gdb commands."
    echo " "
    echo "Examples:"
    echo "  ./docker-toolchain.sh info"
    echo "  ./docker-toolchain.sh build src/f0/app_blinky"
    echo "  ./docker-toolchain.sh write src/f0/app_blinky"
    echo "  ./docker-toolchain.sh write src/f0/app_blinky 0123456789ABCDEF "
    echo " "
    echo "NOTE: When multiple stlinks are plug into host, use the info command"
    echo "to get serial for the stlinks, and set the optional <serial> arg to"
    echo "to specify to the serial for the stlink wanted."
}

# parse args
if [[ "$1" == "build" ]]; then
    # run as user so build/ and .dep/ dir belong to user, not root
    docker run \
        --rm \
        -u `id -u`:`id -g` \
        -v `pwd`:/oresat-firmware \
        oresat/firmware-toolchain make clean all -C $2
    exit 0
elif [[ "$1" == "write" ]]; then
    CMD="make write -C $2"
elif [[ "$1" == "gdb" ]]; then
    # gdb requires interactive mode
    INTER='-it'
    CMD="make gdb -C $2"
elif [[ "$1" == "help" ]]; then
    help_msg
    exit 0
elif [[ "$1" == "info" ]]; then
    CMD="st-info --probe"
else
    echo -e "\ninvalid command"
    help_msg
    exit 1
fi

# write and gdb have readonly permission, so "make all" won't work
if [[ "$1" == "write" ||  "$1" == "gdb" ]]; then
    if [ ! -d "$2/build" ]; then
        echo "run \"./docker-toolchain.sh build $2\" before \"./docker-toolchain.sh $1 $2\""
        exit 1
    fi
fi

# grab SERIAL arg if given
if [ "$3" != "" ]; then
    CMD="$CMD SERIAL=$3"
fi

# find all the stlink devices
if [[ "$OSTYPE" == "linux-gnu"* ]]; then # Linux
    while read -r line; do
        TEMP=`echo $line | cut -d ':' -f 1`
        if [[ ! "$TEMP" ]]; then
            break # nothing in line
        fi
        BUS=`echo $TEMP | cut -d ' ' -f 2`
        DEV=`echo $TEMP | cut -d ' ' -f 4`
        DEVICES="${DEVICES} --device=/dev/bus/usb/${BUS}/${DEV}"
    done <<< `lsusb | grep -i -e "stlink" -e "st-link"`
else
    echo "docker usb pass-through not support on non Linux hosts"
fi

# make sure there are devices for write and gdb
if [[ ! "$DEVICES" ]]; then
    echo "No STLINK devices found."
    if [[ "$1" == "write" || "$1" == "gdb" ]]; then
        exit 1
    fi
fi

docker run \
    --rm \
    $INTER \
    -v `pwd`:/oresat-firmware:ro \
    $DEVICES \
    oresat/firmware-toolchain $CMD
