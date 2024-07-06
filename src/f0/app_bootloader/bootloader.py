#!/usr/bin/env python3
'''This does testing of the CAN bootloader from python using a CANable attached to the host PC'''

import argparse
import math
import struct
import time
from abc import ABC, abstractmethod
from copy import deepcopy
from dataclasses import dataclass
from itertools import islice

import can

# Implements some of ST-AN3154


def batched(iterable, n):
    '''batched('ABCDEFG', 3) → ABC DEF G'''
    # FIXME: Replace with itertools.batched when 3.12 is standard. Copied from
    # https://docs.python.org/3/library/itertools.html#itertools.batched
    if n < 1:
        raise ValueError('n must be at least one')
    it = iter(iterable)
    while batch := tuple(islice(it, n)):
        yield batch


class ExpectMessage(can.Message):
    '''Extends can.Message with a mask to compare only the unmasked bytes in .equals()

    Each bit in mask corresponds to a byte in data to compare or ignore
    '''

    def __init__(self, arbitration_id=0, dlc=None, data=None, is_rx=True, mask=0xFF):
        assert 0x00 <= mask <= 0xFF
        self.mask = [bool(int(b)) for b in reversed(f"{mask:08b}")]
        super().__init__(
            arbitration_id=arbitration_id,
            dlc=dlc,
            data=data,
            is_rx=is_rx,
            is_extended_id=False,
            check=True,
        )

    def equals(self, other, *_):
        if other is None:
            return False
        copy = deepcopy(other)
        data = []
        for mask, theirs, ours in zip(self.mask, copy.data, self.data):
            if mask:
                data.append(theirs)
            else:
                data.append(ours)
        copy.data = bytearray(data)
        return super().equals(copy, timestamp_delta=None, check_channel=False)


class UnexpectedNack(ValueError):
    pass


class Command(ABC):
    ACK = 0x79
    NACK = 0x1F
    offset = 0

    def __init__(self, node_id):
        self.canid = node_id + self.offset

    @abstractmethod
    def run(self, reader):
        pass

    def expect_ack(self, reader):
        ack = ExpectMessage(arbitration_id=self.canid, data=[self.ACK])
        nak = ExpectMessage(arbitration_id=self.canid, data=[self.NACK])
        got = reader.get_message(timeout=10)
        if not ack.equals(got):
            if nak.equals(got):
                raise UnexpectedNack("was expecting ACK")
            raise ValueError(f"unexpected message in bagging area: {got}")

    def expect_nack(self, reader):
        nak = ExpectMessage(arbitration_id=self.canid, data=[self.NACK])
        got = reader.get_message(timeout=10)
        if not nak.equals(got):
            raise ValueError(f"unexpected message in bagging area: {got}")


class Announce(Command):
    '''The boootloader announces its presence on the CAN bus and then will wait 100ms for a response

    If the bootloader receives the response it will then enter and stay in command mode, where the
    remaining commands become available. It will remain in that mode until a 'Go' is issued.
    '''

    offset = 0

    def __init__(self, node_id):
        super().__init__(node_id)
        self.expect = ExpectMessage(
            arbitration_id=self.canid,
            data=[0x01, 0x02, 0x03, 0x04, 0, 0, 0, 0],
            mask=0x0F,
        )

    def run(self, reader):
        got = reader.get_message(timeout=100)
        if not self.expect.equals(got):
            raise ValueError(f"unexpected message in bagging area: {got}")

        yield can.Message(
            arbitration_id=got.arbitration_id,
            data=got.data[4:8] + b'\x01\x02\x03\x04',
            is_extended_id=False,
        )


class Go(Command):
    '''Commands bootloader to restart.

    The bootloader will revalidate the firmware and perform the standard bus announce message
    '''

    offset = 0x782

    def __init__(self, node_id):
        super().__init__(node_id)
        self.command = can.Message(arbitration_id=self.canid, is_extended_id=False)

    def run(self, reader):
        yield self.command
        self.expect_ack(reader)


@dataclass
class GetResponse:
    version: int
    get: int
    read: int
    go: int
    write: int
    erase: int


class Get(Command):
    '''Gets the version and list of command can IDs

    Can be used to verify which features the bootloader has avaliable.
    '''

    offset = 0x780

    def __init__(self, node_id):
        super().__init__(node_id)
        self.msg = can.Message(arbitration_id=self.canid, is_extended_id=False)

    def run(self, reader):
        yield self.msg
        self.expect_ack(reader)

        count = reader.get_message(0.25)
        frames = count.data[0] + 1

        data = []
        for _ in range(frames):
            r = reader.get_message(0.25)
            data.append(int.from_bytes(r.data, byteorder='big', signed=False))

        self.expect_ack(reader)
        self.result = GetResponse(*data)


class ReadMemory(Command):
    '''Reads up to a 256 byte region of memory.

    Valid regions are between addresses 0x0800000 and 0x0803FFFF (flash) and between addresses
    0x02000000 and 0x02007FFF for SRAM. System and Option regions are not currently implemented.
    '''

    offset = 0x781

    def __init__(self, node_id, address, length):
        super().__init__(node_id)
        self.length = length
        self.address = address
        self.expected_frames = int(math.ceil((length) / 8.0))
        self.msg = can.Message(
            arbitration_id=self.canid,
            data=struct.pack('>IB', address, length - 1),
            is_extended_id=False,
        )

    def run(self, reader):
        yield self.msg
        self.expect_ack(reader)

        data = bytearray()
        for _ in range(self.expected_frames):
            r = reader.get_message(0.25)
            data.extend(r.data)

        self.expect_ack(reader)
        self.result = data


class ErasePages(Command):
    '''Erase a list of up to 7 2kb pages.

    Valid pages are 20 (metadata) and 21-127 (application firmware)
    '''

    offset = 0x02

    def __init__(self, node_id, pages):
        super().__init__(node_id)
        self.count = len(pages)
        assert 0 <= self.count <= 7
        if self.count == 0:
            self.count = 256  # no pages given == erase all pages
        data = [self.count - 1]
        data.extend(pages)
        self.msg = can.Message(arbitration_id=self.canid, data=data, is_extended_id=False)

    @classmethod
    def all(cls, node_id):  # FIXME: Not implemented in bootloader
        return cls(node_id, [])

    def run(self, reader):
        yield self.msg
        # command ack
        self.expect_ack(reader)
        # effect ack
        for _ in range(self.count):
            self.expect_ack(reader)


class WriteMemory(Command):
    '''Writes up to 256 bytes to flash.

    The page where writes take place must have been erased first. Valid addresses are between
    0x0800A000 and 0x0800A7FF (metadata) and between 0x0800A800 and 0x0803FFFF (application
    firmware). It's recommended for alignment reasons to only start writes at even number addresses.

    To write a standard OreSat application image (e.g. foo.crc32.bin), start writing at 0x0800A7F4.
    The image is prefixed with 12 bytes of metadata and then the actual application will start at
    0x0800A800.
    '''

    offset = 0x01

    def __init__(self, node_id, base_address, byte_list):
        super().__init__(node_id)
        self.byte_list = byte_list
        self.msg = can.Message(
            arbitration_id=self.canid,
            data=struct.pack(">IB", base_address, len(byte_list) - 1),
            is_extended_id=False,
        )

    def run(self, reader):
        yield self.msg
        self.expect_ack(reader)

        for chunk in batched(self.byte_list, 8):
            yield can.Message(arbitration_id=self.canid, data=chunk, is_extended_id=False)

        self.expect_ack(reader)


def firmware_update(node_id, address, firmware_image):
    commands = []
    page_list = range(20, 127)
    for chunk in batched(page_list, 7):
        commands.append(ErasePages(node_id, chunk))

    with open(firmware_image, 'rb') as f:
        while chunk := f.read(256):
            commands.append(WriteMemory(node_id, address, chunk))
            address += len(chunk)
    return commands


def write_firmware(bus, node_id, filename):
    reader = can.BufferedReader()
    can.Notifier(bus, [can.Printer(), reader])

    commands = [Announce(node_id), Get(node_id)]
    commands.extend(firmware_update(node_id, 0x0800A7F4, filename))
    commands.append(Go(node_id))
    for command in commands:
        print("~~~ Starting", command.__class__.__name__)
        for message in command.run(reader):
            print("TX msg:", message)
            bus.send(message)
            # FIXME: send() timeout option doesn't seem to work for socketcan. Get
            # CanOperationError: Failed to transmit: No buffer space available [Error Code 105]
            # if long writes are transmitted too quickly
            time.sleep(0.01)
        if isinstance(command, (Get, ReadMemory)):
            print("Result:", command.result)


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('-b', '--bustype', default='socketcan', help="default: %(default)s")
    parser.add_argument('-c', '--channel', default='can0', help="default: %(default)s")
    parser.add_argument('-r', '--bitrate', default=1000000, help="default: %(default)s", type=int)
    parser.add_argument('-n', '--node-id', default=0x7C, help="default: %(default)s", type=int)
    parser.add_argument('-p', '--program', help="The image to write (usually foo.crc32.bin")

    args = parser.parse_args()

    filters = [
        {'can_id': Announce.offset + args.node_id, 'can_mask': 0x7FF, 'extende': False},
        {'can_id': Go.offset + args.node_id, 'can_mask': 0x7FF, 'extended': False},
        {'can_id': Get.offset + args.node_id, 'can_mask': 0x7FF, "extended": False},
        {'can_id': ReadMemory.offset + args.node_id, 'can_mask': 0x7FF, 'extended': False},
        {'can_id': WriteMemory.offset + args.node_id, 'can_mask': 0x7FF, 'extended': False},
        {'can_id': ErasePages.offset + args.node_id, 'can_mask': 0x7FF, 'extended': False},
    ]

    with can.Bus(
        bustype=args.bustype,
        channel=args.channel,
        bitrate=args.bitrate,
        can_filters=filters,
    ) as b:
        write_firmware(b, args.node_id, args.program)
