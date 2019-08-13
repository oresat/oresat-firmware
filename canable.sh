#!/bin/bash

killall -q slcand
slcand -o -c -f -s8 $1 can0
sleep 1
ip link set can0 up
