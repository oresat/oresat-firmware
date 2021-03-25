#!/bin/bash
`sudo slcand -o -c -f -s6 /dev/serial/by-id/*CANtact*-if00`
`sudo ip link set slcan0 up`
