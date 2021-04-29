#!/usr/bin/python3
"""Print parsed C3 beacon"""

import sys
import struct
from serial import Serial, SerialException
from tabulate import tabulate
from datetime import datetime

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

def to_hex(x):
    if type(x) is bytes:
        return x.hex()
    elif type(x) is int:
        return hex(x)
    else:
        raise Exception("unhandled type " + str(type(x)))

def t_to_type(t):
    if t == uint8:
        return 'uint8'
    elif t == int8:
        return 'int8'
    elif t == uint16:
        return 'uint16'
    elif t == int16:
        return 'int16'
    elif t == uint32:
        return 'uint32'
    elif t == int32:
        return 'int32'
    elif t == state:
        return 'state'
    else:
        return 'other: ' + str(t)

def main():
    # open serial
    tty = '/dev/serial/by-id/usb-SCS_SCS_Tracker___DSP_TNC_PT2HJ743-if00-port0'
    ser = Serial(tty, 38400, timeout=15.0)

    while 1:
        try:
            line = _readline(ser)
        except SerialException as exc:
            print('Device error: {}\n'.format(exc))
            break

        # filter out too short lines
        if len(line) < 3:
            continue
        print("LINE:", line)
        # filter out header
        if 'KJ7SAT' in str(line):
            continue

        # generate the header
        beacon_len = len(line)
        ts = datetime.now().isoformat('T')
        print("========= " + ts + " Beacon: " + str(beacon_len) + " bytes =========")
        print("RAW: ", line.hex())

        # initialize the print table
        disp = []
        disp.append(["NAME", "VAL", "TYPE", "RAW"])

        # iterate through all the known parts and parse each individually. I 
        # know this sorta defeats the purpose of using 'unpack', but I am doing 
        # it this way so we can extract the raw source bytes easily for 
        # inspection. Also this allows us to parse as many data points as are 
        # included in the beacon as we expand it
        b = 0
        next = 0
        for i in range(len(parts)):

            # get the current data part to parse
            p = parts[i]

            # find the index 1 past the end of the current prt
            next = b+struct.calcsize(p['t'])

            # extract the raw bytes for the current part
            chunk = line[b:next]

            # unpack the raw bytes into the expected type. If there are not
            # enough bytes for the field, just just break out of the loop
            try:
                d = struct.unpack(p['t'], chunk)
            except struct.error:
                break

            # increment the byte counter
            b += struct.calcsize(p['t'])

            # append the parsed data to the table for printing
            disp.append([p['name'], str(d[0]), t_to_type(p['t']), '0x'+chunk.hex()] )

        # print the table
        print(tabulate(disp))
        print("")

    
uint8 = 'B'
int8 = 'b'
uint16 = 'H'
int16 = 'h'
uint32 = 'I'
int32 = 'i'
state = 'c' # state represented as char

parts = [
    {'name': 'APRS Data Type 1', 't': uint8 + uint8 + uint8}, 
    {'name': 'APRS Revision', 't': uint8}, 
    {'name': 'Oresat0 State', 't': state},
    {'name': 'Uptime', 't': uint32}, 
    {'name': 'Time', 't': uint32}, 
    {'name': 'Temperature', 't': int8}, 
    {'name': 'Ref Voltage', 't': uint8}, 
    {'name': 'Vbusp Voltage', 't': uint8},
    {'name': 'Vbusp Current', 't': uint8},
    {'name': 'Num Timeouts', 't': uint16}, 
    {'name': 'eMMC % Full', 't': uint8}, 
    {'name': 'L Band RX Bytes', 't': uint32},
    {'name': 'L Band RX Valid Packets', 't': uint32},
    {'name': 'L Band RX RSSI', 't': uint8}, 
    {'name': 'L Band RX PLL Lock', 't': state},
    {'name': 'UHF TX Temperature', 't': int8},
    {'name': 'UHF TX FWD PWR', 't': uint16},
    {'name': 'UHF TX REV PWE', 't': uint16},
    {'name': 'UHF RX Bytes', 't': uint32},
    {'name': 'UHF RX Valid Packets', 't': uint32},
    {'name': 'UHF RX RSSI', 't': uint8},
    {'name': 'UHF RX PLL Lock', 't': state},
    {'name': 'Deployer 1', 't': uint8}, # TODO Type???
    {'name': 'CAN1', 't': state}, 
    {'name': 'CAN2', 't': state}, 
    {'name': 'OPD Current', 't': uint8}, 
    {'name': 'OPD State', 't': state}, 

    {'name': 'Battery Pack 1 Vbatt', 't': uint16}, 
    {'name': 'Battery Pack 1 Vcell', 't': uint16}, 
    {'name': 'Battery Pack 1 Vcell max', 't': uint16},
    {'name': 'Battery Pack 1 Vcell min', 't': uint16}, 
    {'name': 'Battery Pack 1 Vcell 1', 't': uint16}, 
    {'name': 'Battery Pack 1 Vcell 2', 't': uint16}, 
    {'name': 'Battery Pack 1 Vcell avg', 't': uint16}, 
    {'name': 'Battery Pack 1 temp', 't': int16}, 
    {'name': 'Battery Pack 1 temp avg', 't': int16}, 
    {'name': 'Battery Pack 1 temp max', 't': int16}, 
    {'name': 'Battery Pack 1 temp min', 't': int16}, 
    {'name': 'Battery Pack 1 current', 't': int16}, 
    {'name': 'Battery Pack 1 current avg', 't': int16},
    {'name': 'Battery Pack 1 current max', 't': int16},
    {'name': 'Battery Pack 1 current min', 't': int16},
    {'name': 'Battery Pack 1 state', 't': uint8}, 
    {'name': 'Battery Pack 1 reported state of change', 't': uint8},
    {'name': 'Battery Pack 1 full capacity', 't': uint16},
    {'name': 'Battery Pack 1 reported capacity', 't': uint16},

    {'name': 'Battery Pack 2 Vbatt', 't': uint16},
    {'name': 'Battery Pack 2 Vcell', 't': uint16},
    {'name': 'Battery Pack 2 Vcell max', 't': uint16},
    {'name': 'Battery Pack 2 Vcell min', 't': uint16}, 
    {'name': 'Battery Pack 2 Vcell 1', 't': uint16}, 
    {'name': 'Battery Pack 2 Vcell 2', 't': uint16}, 
    {'name': 'Battery Pack 2 Vcell avg', 't': uint16}, 
    {'name': 'Battery Pack 2 temp', 't': int16}, 
    {'name': 'Battery Pack 2 temp avg', 't': int16}, 
    {'name': 'Battery Pack 2 temp max', 't': int16}, 
    {'name': 'Battery Pack 2 temp min', 't': int16}, 
    {'name': 'Battery Pack 2 current', 't': int16}, 
    {'name': 'Battery Pack 2 current avg', 't': int16}, 
    {'name': 'Battery Pack 2 current max', 't': int16}, 
    {'name': 'Battery Pack 2 current min', 't': int16}, 
    {'name': 'Battery Pack 2 state', 't': uint8}, 
    {'name': 'Battery Pack 2 reported state of change', 't': uint8}, 
    {'name': 'Battery Pack 2 full capacity', 't': uint16}, 
    {'name': 'Battery Pack 2 reported capacity', 't': uint16}, 

    {'name': 'Solar -X Voltage Avg', 't': uint16}, 
    {'name': 'Solar -X Current Avg', 't': int16}, 
    {'name': 'Solar -X Power Avg', 't': uint16}, 
    {'name': 'Solar -X Voltage Max', 't': uint16}, 
    {'name': 'Solar -X Current Max', 't': int16}, 
    {'name': 'Solar -X Power Max', 't': uint16}, 
    {'name': 'Solar -X Energy', 't': uint16}, 

    {'name': 'Solar -Y Voltage Avg', 't': uint16}, 
    {'name': 'Solar -Y Current Avg', 't': int16}, 
    {'name': 'Solar -Y Power Avg', 't': uint16}, 
    {'name': 'Solar -Y Voltage Max', 't': uint16}, 
    {'name': 'Solar -Y Current Max', 't': int16}, 
    {'name': 'Solar -Y Power Max', 't': uint16}, 
    {'name': 'Solar -Y Energy', 't': uint16}, 

    {'name': 'Solar +X Voltage Avg', 't': uint16},
    {'name': 'Solar +X Current Avg', 't': int16},
    {'name': 'Solar +X Power Avg', 't': uint16}, 
    {'name': 'Solar +X Voltage Max', 't': uint16}, 
    {'name': 'Solar +X Current Max', 't': int16}, 
    {'name': 'Solar +X Power Max', 't': uint16}, 
    {'name': 'Solar +X Energy', 't': uint16}, 

    {'name': 'Solar +Y Voltage Avg', 't': uint16}, 
    {'name': 'Solar +Y Current Avg', 't': int16}, 
    {'name': 'Solar +Y Power Avg', 't': uint16}, 
    {'name': 'Solar +Y Voltage Max', 't': uint16},
    {'name': 'Solar +Y Current Max', 't': int16},
    {'name': 'Solar +Y Power Max', 't': uint16},
    {'name': 'Solar +Y Energy', 't': uint16},

    {'name': 'Star Tracker eMMC Capacity', 't': uint8},
    {'name': 'Star Tracker Readable Files', 't': uint8},
    {'name': 'Star Tracker Updater Status', 't': uint8},
    {'name': 'Star Tracker Updates Cached', 't': uint8},
    {'name': 'Star Tracker Right Ascension', 't': int16},
    {'name': 'Star Tracker Declination', 't': int16},
    {'name': 'Star Tracker Roll', 't': int16},
    {'name': 'Star Tracker Timestamp Last Packet', 't': uint32},

    {'name': 'GPS eMMC Capacity', 't': uint8},
    {'name': 'GPS Readable Files', 't': uint8},
    {'name': 'GPS Updater Status', 't': uint8}, 
    {'name': 'GPS Updates Cached', 't': uint8}, 
    {'name': 'GPS Status', 't': uint8}, 
    {'name': 'GPS Num Sats Locked', 't': uint8}, 
    {'name': 'GPS X Pos', 't': int32}, 
    {'name': 'GPS Y Pos', 't': int32}, 
    {'name': 'GPS Z Pos', 't': int32},
    {'name': 'GPS X Vel', 't': int32},
    {'name': 'GPS Y Vel', 't': int32},
    {'name': 'GPS Z Vel', 't': int32}, 
    {'name': 'GPS Timestamp Last Packet', 't': uint32},

    {'name': 'ADS Gyro Roll Dot', 't': int16},
    {'name': 'ADS Gyro Pitch Dot', 't': int16},
    {'name': 'ADS Gyro Yaw Dot', 't': int16},
    {'name': 'ADS Gyro IMU temp', 't': int8},

    {'name': 'DxWifi eMMC Capacity', 't': uint8},
    {'name': 'DxWifi Readable Files', 't': uint8},
    {'name': 'DxWifi Updater Status', 't': uint8}, 
    {'name': 'DxWifi Updates Cached', 't': uint8}, 
    {'name': 'DxWifi Transmitting', 't': uint8}, # bool

    {'name': 'APRS CRC-32', 't': uint32},
]

try:
    main()
except KeyboardInterrupt:
    sys.exit()
