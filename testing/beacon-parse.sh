#!/usr/bin/python3
"""Print parsed C3 beacon"""

import sys
import struct
from serial import Serial, SerialException

def _readline(ser):
    eol = b'\r\n'
    leneol = len(eol)
    line = bytearray()
    while True:
        c = ser.read(1)
        if c:
            line += c
            if line[-leneol:] == eol:
                break
        else:
            break
    return bytes(line)

def main():
    """loop and print data"""
    tty = '/dev/ttyUSB0'

    # open serial
    ser = Serial(tty, 38400, timeout=15.0)

    parts = [
        {'name': 'APRS Data Type', 't': 'B'}, # uint8
        {'name': 'APRS Revision', 't': 'B'}, # uint8
        {'name': 'Oresat0 State', 't': 'c', 'fmt': lambda s : str(s)}, # char # TODO might not need for char
        {'name': 'Uptime', 't': 'I'}, # uint32
        {'name': 'Time', 't': 'I'}, # uint64
        {'name': 'Temperature', 't': 'b'}, # int8
        {'name': 'Ref Voltage', 't': 'B'}, # uint8
        {'name': 'Vbusp Voltage', 't': 'B'}, # uint8
        {'name': 'Vbusp Current', 't': 'B'}, # uint8
        #{'name': 'Num Timeouts', 't': 'H'}, # uint16
        #{'name': 'eMMC % Full', 't': 'B'}, # uint8
        #{'name': 'L Band RX Bytes', 't': '??'},
        #{'name': 'L Band RX Valid Packets', 't': '??'},
        #{'name': 'L Band RX RSSI', 't': 'B'}, # uint8
        #{'name': 'L Band RX PLL Lock', 't': 'c'}, # state
        #{'name': 'UHF TX Temperature', 't': 'b'}, # int8
        #{'name': 'UHF TX FWD PWR', 't': 'H'}, # uint16
        #{'name': 'UHF TX REV PWE', 't': 'H'}, # uint16
        #{'name': 'UHF RX Bytes', 't': '??'},
        #{'name': 'UHF RX Valid Packets', 't': '??'},
        #{'name': 'UHF RX RSSI', 't': 'B'}, # uint8
        #{'name': 'UHF RX PLL Lock', 't': 'c'}, # state
        #{'name': 'Deployer 1', 't': '??'},
        #{'name': 'CAN1', 't': 'c'}, # state
        #{'name': 'CAN2', 't': 'c'}, # state
        #{'name': 'OPD Current', 't': 'B'}, # uint8
        #{'name': 'OPD State', 't': 'c'}, # state

        #{'name': 'Battery Pack 1 Vbatt', 't': 'H'}, # uint16
        #{'name': 'Battery Pack 1 Vcell', 't': 'H'}, # uint16
        #{'name': 'Battery Pack 1 Vcell max', 't': 'H'}, # uint16
        #{'name': 'Battery Pack 1 Vcell min', 't': 'H'}, # uint16
        #{'name': 'Battery Pack 1 Vcell 1', 't': 'H'}, # uint16
        #{'name': 'Battery Pack 1 Vcell 2', 't': 'H'}, # uint16
        #{'name': 'Battery Pack 1 Vcell avg', 't': 'H'}, # uint16
        #{'name': 'Battery Pack 1 temp', 't': 'h'}, # int16
        #{'name': 'Battery Pack 1 temp avg', 't': 'h'}, # int16
        #{'name': 'Battery Pack 1 temp max', 't': 'h'}, # int16
        #{'name': 'Battery Pack 1 temp min', 't': 'h'}, # int16
        #{'name': 'Battery Pack 1 current', 't': 'h'}, # int16
        #{'name': 'Battery Pack 1 current avg', 't': 'h'}, # int16
        #{'name': 'Battery Pack 1 current max', 't': 'h'}, # int16
        #{'name': 'Battery Pack 1 current min', 't': 'h'}, # int16
        #{'name': 'Battery Pack 1 state', 't': 'B'}, # uint8
        #{'name': 'Battery Pack 1 reported state of change', 't': 'B'}, # uint8 
        #{'name': 'Battery Pack 1 full capacity', 't': 'H'}, # uint16
        #{'name': 'Battery Pack 1 reported capacity', 't': 'H'}, # uint16

        #{'name': 'Battery Pack 2 Vbatt', 't': 'H'}, # uint16
        #{'name': 'Battery Pack 2 Vcell', 't': 'H'}, # uint16
        #{'name': 'Battery Pack 2 Vcell max', 't': 'H'}, # uint16
        #{'name': 'Battery Pack 2 Vcell min', 't': 'H'}, # uint16
        #{'name': 'Battery Pack 2 Vcell 1', 't': 'H'}, # uint16
        #{'name': 'Battery Pack 2 Vcell 2', 't': 'H'}, # uint16
        #{'name': 'Battery Pack 2 Vcell avg', 't': 'H'}, # uint16
        #{'name': 'Battery Pack 2 temp', 't': 'h'}, # int16
        #{'name': 'Battery Pack 2 temp avg', 't': 'h'}, # int16
        #{'name': 'Battery Pack 2 temp max', 't': 'h'}, # int16
        #{'name': 'Battery Pack 2 temp min', 't': 'h'}, # int16
        #{'name': 'Battery Pack 2 current', 't': 'h'}, # int16
        #{'name': 'Battery Pack 2 current avg', 't': 'h'}, # int16
        #{'name': 'Battery Pack 2 current max', 't': 'h'}, # int16
        #{'name': 'Battery Pack 2 current min', 't': 'h'}, # int16
        #{'name': 'Battery Pack 2 state', 't': 'B'}, # uint8
        #{'name': 'Battery Pack 2 reported state of change', 't': 'B'}, # uint8 
        #{'name': 'Battery Pack 2 full capacity', 't': 'H'}, # uint16
        #{'name': 'Battery Pack 2 reported capacity', 't': 'H'}, # uint16

        #{'name': 'Solar -X Voltage Avg', 't': 'H'}, # uint16
        #{'name': 'Solar -X Current Avg', 't': 'h'}, # int16
        #{'name': 'Solar -X Power Avg', 't': 'H'}, # uint16
        #{'name': 'Solar -X Voltage Max', 't': 'H'}, # uint16
        #{'name': 'Solar -X Current Max', 't': 'h'}, # int16
        #{'name': 'Solar -X Power Max', 't': 'H'}, # uint16
        #{'name': 'Solar -X Energy', 't': 'H'}, # uint16

        #{'name': 'Solar -Y Voltage Avg', 't': 'H'}, # uint16
        #{'name': 'Solar -Y Current Avg', 't': 'h'}, # int16
        #{'name': 'Solar -Y Power Avg', 't': 'H'}, # uint16
        #{'name': 'Solar -Y Voltage Max', 't': 'H'}, # uint16
        #{'name': 'Solar -Y Current Max', 't': 'h'}, # int16
        #{'name': 'Solar -Y Power Max', 't': 'H'}, # uint16
        #{'name': 'Solar -Y Energy', 't': 'H'}, # uint16

        #{'name': 'Solar +X Voltage Avg', 't': 'H'}, # uint16
        #{'name': 'Solar +X Current Avg', 't': 'h'}, # int16
        #{'name': 'Solar +X Power Avg', 't': 'H'}, # uint16
        #{'name': 'Solar +X Voltage Max', 't': 'H'}, # uint16
        #{'name': 'Solar +X Current Max', 't': 'h'}, # int16
        #{'name': 'Solar +X Power Max', 't': 'H'}, # uint16
        #{'name': 'Solar +X Energy', 't': 'H'}, # uint16

        #{'name': 'Solar +Y Voltage Avg', 't': 'H'}, # uint16
        #{'name': 'Solar +Y Current Avg', 't': 'h'}, # int16
        #{'name': 'Solar +Y Power Avg', 't': 'H'}, # uint16
        #{'name': 'Solar +Y Voltage Max', 't': 'H'}, # uint16
        #{'name': 'Solar +Y Current Max', 't': 'h'}, # int16
        #{'name': 'Solar +Y Power Max', 't': 'H'}, # uint16
        #{'name': 'Solar +Y Energy', 't': 'H'}, # uint16

        #{'name': 'Star Tracker eMMC Capacity', 't': 'B'}, # uint8
        #{'name': 'Star Tracker Readable Files', 't': 'B'}, # uint8
        #{'name': 'Star Tracker Updater Status', 't': 'B'}, # uint8
        #{'name': 'Star Tracker Updates Cached', 't': 'B'}, # uint8
        #{'name': 'Star Tracker Right Ascension', 't': 'h'}, # int16
        #{'name': 'Star Tracker Declination', 't': 'h'}, # int16
        #{'name': 'Star Tracker Roll', 't': 'h'}, # int16
        #{'name': 'Star Tracker Timestamp Last Packet', 't': 'I'}, # uint32

        #{'name': 'GPS eMMC Capacity', 't': 'B'}, # uint8
        #{'name': 'GPS Readable Files', 't': 'B'}, # uint8
        #{'name': 'GPS Updater Status', 't': 'B'}, # uint8
        #{'name': 'GPS Updates Cached', 't': 'B'}, # uint8
        #{'name': 'GPS Status', 't': 'B'}, # uint8
        #{'name': 'GPS Num Sats Locked', 't': 'B'}, # uint8
        #{'name': 'GPS X Pos', 't': 'i'}, # int32
        #{'name': 'GPS Y Pos', 't': 'i'}, # int32
        #{'name': 'GPS Z Pos', 't': 'i'}, # int32
        #{'name': 'GPS X Vel', 't': 'i'}, # int32
        #{'name': 'GPS Y Vel', 't': 'i'}, # int32
        #{'name': 'GPS Z Vel', 't': 'i'}, # int32
        #{'name': 'GPS Timestamp Last Packet', 't': 'I'}, # uint32

        #{'name': 'ADS Gyro Roll Dot', 't': 'h'}, # int16
        #{'name': 'ADS Gyro Pitch Dot', 't': 'h'}, # int16
        #{'name': 'ADS Gyro Yaw Dot', 't': 'h'}, # int16
        #{'name': 'ADS Gyro IMU temp', 't': 'b'}, # int8

        #{'name': 'DxWifi eMMC Capacity', 't': 'B'}, # uint8
        #{'name': 'DxWifi Readable Files', 't': 'B'}, # uint8
        #{'name': 'DxWifi Updater Status', 't': 'B'}, # uint8
        #{'name': 'DxWifi Updates Cached', 't': 'B'}, # uint8
        #{'name': 'DxWifi Transmitting', 't': 'B'}, # bool

        #{'name': 'APRS CRC-32', 't': 'I'}, # uint32
        #{'name': 'APRS Data Type', 't': 'B'}, # uint8

    ]

    # build the struct unpack string
    unpack_str = '<'
    for p in parts:
        #print(p)
        unpack_str += p['t']
        #if 'fmt' in p.keys():
        #    print(p['fmt'])

    while 1:
        try:
            line = _readline(ser)
        except SerialException as exc:
            print('Device error: {}\n'.format(exc))
            break

        # filter out too short lines
        if len(line) < 3:
            continue

        # filter out header
        if 'KJ7SAT' in str(line):
            continue

        try:
            data = struct.unpack_from(unpack_str, line)
            #data = struct.unpack_from('BBBIIbBBB', line)
        except struct.error as exc:
            print('Parse error: {}\n'.format(exc))
            continue

        #print(data)
        #print(line.hex())

        print("===========================")
        print("Beacon Len: ", len(line))
        for i in range(len(data)):
            p = parts[i]
            print(p['name'] + ": " + str(data[i]))
        print("===========================")
        print("")

try:
    main()
except KeyboardInterrupt:
    sys.exit()
