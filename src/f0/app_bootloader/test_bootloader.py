#!/usr/bin/env python3
'''Tests primarly the firmware bootloader implementation, testing of bootloader.py is accessory'''
import argparse
import sys
import time
import unittest

import can

from bootloader import (Announce, ErasePages, Get, GetResponse, Go, ReadMemory,
                        UnexpectedNack, WriteMemory)

if __name__ == '__main__':
    # NOTE: this co-opts -b, -c, and -h from unittest. Don't need them now but deconflict in
    # the future?
    parser = argparse.ArgumentParser()
    parser.add_argument('-b', '--bustype', default='socketcan', help="default: %(default)s")
    parser.add_argument('-c', '--channel', default='can0', help="default: %(default)s")
    parser.add_argument('-r', '--bitrate', default=1000000, help="default: %(default)s", type=int)
    parser.add_argument('-n', '--node-id', default=0x7C, help="default: %(default)s", type=int)

    args, remaining = parser.parse_known_args()

    bus = can.Bus(bustype=args.bustype, channel=args.channel, bitrate=args.bitrate)
    reader = can.BufferedReader()
    notifier = can.Notifier(bus, [reader])


class TestCommand(unittest.TestCase):
    def setUp(self):
        self.do_cmds([Announce(args.node_id)])

    def tearDown(self):
        self.do_cmds([Go(args.node_id)])

    def do_cmds(self, commands):
        for command in commands:
            for message in command.run(reader):
                bus.send(message)
                # FIXME: send() timeout option doesn't seem to work for socketcan. Get
                # CanOperationError: Failed to transmit: No buffer space available [Error Code 105]
                # if long writes are transmitted too quickly
                time.sleep(0.01)


class TestGet(TestCommand):
    def test_get(self):
        get = Get(args.node_id)
        self.do_cmds([get])
        self.assertEqual(
            get.result,
            GetResponse(
                version=0xAC,
                get=Get.offset + args.node_id,
                read=ReadMemory.offset + args.node_id,
                go=Go.offset + args.node_id,
                write=WriteMemory.offset + args.node_id,
                erase=ErasePages.offset + args.node_id,
            ),
        )


class TestReadMemory(TestCommand):
    def test_good_address_short(self):
        length = 1
        read = ReadMemory(args.node_id, 0x08000000, length)
        self.do_cmds([read])
        self.assertEqual(len(read.result), length)

    def test_bad_address_short(self):
        length = 1
        read = ReadMemory(args.node_id, 0x88000000, length)
        with self.assertRaises(UnexpectedNack):
            self.do_cmds([read])

    def test_good_address_long(self):
        length = 256
        read = ReadMemory(args.node_id, 0x08000000, length)
        self.do_cmds([read])
        self.assertEqual(len(read.result), length)

    def test_bad_address_long(self):
        length = 256
        read = ReadMemory(args.node_id, 0x88000000, length)
        with self.assertRaises(UnexpectedNack):
            self.do_cmds([read])

    def test_last_address(self):
        # Address is at the top of flash memory space
        length = 1
        read = ReadMemory(args.node_id, 0x0803FFFF, length)
        self.do_cmds([read])
        self.assertEqual(len(read.result), length)

    def test_last_address_too_long(self):
        # Address is at the top of flash memory space
        length = 2
        read = ReadMemory(args.node_id, 0x0803FFFF, length)
        with self.assertRaises(UnexpectedNack):
            self.do_cmds([read])


class TestErasePages(TestCommand):
    def test_good_page_short(self):
        erase = ErasePages(args.node_id, [20])
        self.do_cmds([erase])

    def test_bad_page_short(self):
        erase = ErasePages(args.node_id, [19])
        with self.assertRaises(UnexpectedNack):
            self.do_cmds([erase])

    def test_good_page_long(self):
        erase = ErasePages(args.node_id, range(20, 27))
        self.do_cmds([erase])

    def test_bad_page_long(self):
        erase = ErasePages(args.node_id, range(19, 26))
        with self.assertRaises(UnexpectedNack):
            self.do_cmds([erase])

    def test_last_good_page(self):
        erase = ErasePages(args.node_id, [127])
        self.do_cmds([erase])

    def test_last_bad_page_short(self):
        erase = ErasePages(args.node_id, [128])
        with self.assertRaises(UnexpectedNack):
            self.do_cmds([erase])

    def test_last_bad_page_long(self):
        erase = ErasePages(args.node_id, range(125, 132))
        with self.assertRaises(UnexpectedNack):
            self.do_cmds([erase])

    def test_mix_n_match(self):
        erase = ErasePages(args.node_id, [20, 127, 33, 94, 33, 33])
        self.do_cmds([erase])

    def test_too_long_range(self):
        erase = ErasePages(args.node_id, [20])
        erase.msg.data[0] = 8
        with self.assertRaises(UnexpectedNack):
            self.do_cmds([erase])


class TestWriteMemory(TestCommand):
    def test_good_address_short(self):
        address = 0x0800A000
        data = bytearray([2])
        erase = ErasePages(args.node_id, [20])
        write = WriteMemory(args.node_id, address, data)
        read = ReadMemory(args.node_id, address, len(data))
        self.do_cmds([erase, write, read])
        self.assertEqual(data, read.result)

    def test_bad_address_short(self):
        address = 0x08000000
        data = bytearray([2])
        erase = ErasePages(args.node_id, [20])
        write = WriteMemory(args.node_id, address, data)
        self.do_cmds([erase])
        with self.assertRaises(UnexpectedNack):
            self.do_cmds([write])

    def test_good_address_long(self):
        address = 0x0800A000
        data = bytearray([2] * 256)
        erase = ErasePages(args.node_id, [20])
        write = WriteMemory(args.node_id, address, data)
        read = ReadMemory(args.node_id, address, len(data))
        self.do_cmds([erase, write, read])
        self.assertEqual(data, read.result)

    def test_bad_address_long(self):
        address = 0x08000000
        data = bytearray([2] * 256)
        erase = ErasePages(args.node_id, [20])
        write = WriteMemory(args.node_id, address, data)
        self.do_cmds([erase])
        with self.assertRaises(UnexpectedNack):
            self.do_cmds([write])


# TODO: class TestMetadata which tests valid and invalid firmware metadata


def tearDownModule():
    bus.shutdown()


if __name__ == '__main__':
    unittest.main(argv=[sys.argv[0]] + remaining)
