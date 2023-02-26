#!/usr/bin/env python3
'''
Send C3 crypto key

This script will set the C3 crypto key from a file. File must contain a 128 byte value.
'''

import sys
from argparse import ArgumentParser

import canopen


def main():
    parser = ArgumentParser(description='Set the C3\'s crypto key')
    parser.add_argument('-b', '--bus', default='can0', help='CAN bus to use')
    parser.add_argument('-s', '--store', action='store_true', help='store the key (save it)')
    parser.add_argument('key_file', help='key binary file')
    args = parser.parse_args()

    # connect to network and add a fake node to make pythonic canopen happy
    network = canopen.Network()
    node = canopen.RemoteNode(0x1, canopen.ObjectDictionary())
    network.add_node(node)
    network.connect(bustype='socketcan', channel=args.bus)

    with open(args.key_file, 'rb') as f:
        data = f.read()

    if len(data) != 128:
        print('invalid key length')
        sys.exit(1)

    for i in range(4):
        start = i * 32
        stop = (i + 1) * 32
        raw_data = data[start: stop]
        node.sdo.download(0x6005, i + 1, raw_data)

    if args.store:
        raw = 1
        raw = raw.to_bytes(4, 'little', signed=False)
        node.sdo.download(0x1010, 0x6, raw)

    network.disconnect()


if __name__ == '__main__':
    main()
