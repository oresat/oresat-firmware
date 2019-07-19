#!/bin/bash

killall -q slcand
slcand -o -c -f -s8 $1 can0
ip link set can0 up
