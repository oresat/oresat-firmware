#!/usr/bin/env python3
'''
SDO transfer script

This scipt act as CANopen master node, allowing it to read and write other
node's Object Dictionaries.
'''

import sys
from argparse import ArgumentParser
from struct import pack, unpack
from enum import Enum, auto

import canopen


class CANopenTypes(Enum):
    '''All valid canopen types supported'''
    b = auto()
    i8 = auto()
    u8 = auto()
    i16 = auto()
    u16 = auto()
    i32 = auto()
    u32 = auto()
    i64 = auto()
    u64 = auto()
    f32 = auto()
    f64 = auto()
    s = auto()
    o = auto()
    d = auto()  # DOMAIN type


DECODE_KEYS = {
    CANopenTypes.b: '?',
    CANopenTypes.i8: 'b',
    CANopenTypes.i16: 'h',
    CANopenTypes.i32: 'i',
    CANopenTypes.i64: 'q',
    CANopenTypes.u8: 'B',
    CANopenTypes.u16: 'H',
    CANopenTypes.u32: 'I',
    CANopenTypes.u64: 'Q',
    CANopenTypes.f32: 'f',
    CANopenTypes.f64: 'd',
}


def main():
    parser = ArgumentParser(description='Read or write value to a node\'s object dictionary')
    parser.add_argument('bus', help='CAN bus to use')
    parser.add_argument('node', help='device node name in hex')
    parser.add_argument('mode', help='read or write')
    parser.add_argument('index', help='object dictionary index in hex')
    parser.add_argument('subindex', help='object dictionary subindex in hex')
    parser.add_argument('type', help='data type (i8, u8, f32, s, etc)')
    parser.add_argument('value', nargs='?', default=0, help='data to write')
    args = parser.parse_args()

    # make sure valid type
    co_type = CANopenTypes[args.type]

    # convert hex str to int
    index = int(args.index, 16)
    subindex = int(args.subindex, 16)

    # connect to network and add a fake node to make pythonic canopen happy
    network = canopen.Network()
    node = canopen.RemoteNode(int(args.node, 16), canopen.ObjectDictionary())
    network.add_node(node)
    network.connect(bustype='socketcan', channel=args.bus)

    if args.mode == 'r' or args.mode == 'read':
        try:
            raw_data = node.sdo.upload(index, subindex)
            network.disconnect()
        except Exception as exc:
            print(exc)
            network.disconnect()
            sys.exit(1)

        if co_type in DECODE_KEYS.keys():
            data = unpack(DECODE_KEYS[co_type], raw_data)[0]
            print(data)
            sys.exit(0)
        elif co_type == CANopenTypes.s:
            data = raw_data.decode('utf-8')
            print(data)
            sys.exit(0)
        elif co_type in [CANopenTypes.o, CANopenTypes.d]:
            print(raw_data)
            sys.exit(0)
        else:
            print(f'invalid data type {co_type}')
            sys.exit(1)

        print(data[0])
    elif args.mode == 'w' or args.mode == 'write':
        if co_type == CANopenTypes.f32:
            raw_data = pack('f', float(args.value))
        elif co_type == CANopenTypes.f64:
            raw_data = pack('d', float(args.value))
        elif co_type in DECODE_KEYS.keys():
            raw_data = pack(DECODE_KEYS[co_type], int(args.value))
        elif co_type in [CANopenTypes.s, CANopenTypes.o, CANopenTypes.d]:
            if args.value.startswith('file:'):
                with open(args.value[5:], 'rb') as f:
                    raw_data = f.read()
            else:
                raw_data = args.value
        else:
            print(f'invalid data type {co_type}')
            sys.exit(1)

        try:
            node.sdo.download(index, subindex, raw_data)
            network.disconnect()
        except Exception as exc:
            print(exc)
            network.disconnect()
            sys.exit(1)
    else:
        print('Invalid mode')
        print('Must be read or write')
        sys.exit(1)


if __name__ == '__main__':
    main()
