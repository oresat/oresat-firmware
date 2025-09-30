#!/bin/bash

user=`id -u`

if [ $user -ne 0 ]
    then
        echo "Run as root"
        exit
fi

if [ $# -eq 0 ]
    then
        echo "No argument supplied"
        exit
fi

killall -q slcand
slcand -o -c -f -s8 $1 can0
sleep 1
ip link set can0 up
