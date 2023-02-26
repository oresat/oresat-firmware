#!/usr/bin/env python3
'''
Send Time Sync TPDO

This script will send the Time Sync TPDO for OreSat, all node that care about time should sync to
it.
'''

from argparse import ArgumentParser
from time import time

import canopen


def main():
    parser = ArgumentParser(description='Send the OreSat Time Sync TPDO')
    parser.add_argument('-b', '--bus', default='can0', help='CAN bus to use')
    args = parser.parse_args()

    # connect to network and add a fake node to make pythonic canopen happy
    network = canopen.Network()
    network.connect(bustype='socketcan', channel=args.bus)

    # get current time as SCET
    unix_time = time()
    coarse = int(unix_time)
    coarse_bytes = coarse.to_bytes(4, 'little')
    fine = int(unix_time % 1 * 1000000)
    fine_bytes = fine.to_bytes(4, 'little')
    scet_raw = coarse_bytes + fine_bytes[:3] + b'\x00'

    # send Time Sync TPDO
    network.send_message(0x181, scet_raw, False)

    network.disconnect()


if __name__ == '__main__':
    main()
