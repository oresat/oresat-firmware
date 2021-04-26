#!/usr/bin/python3
"""Print parsed C3 beacon"""

import sys
import struct
from serial import Serial, SerialException
from tabulate import tabulate

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
    # open serial
    tty = '/dev/serial/by-id/usb-SCS_SCS_Tracker___DSP_TNC_PT2HJ743-if00-port0'
    ser = Serial(tty, 38400, timeout=15.0)

    # build the struct unpack string
    unpack_str = '<'
    for p in parts:
        #print(p)
        unpack_str += p['t']
        #if 'fmt' in p.keys():
        #    print(p['fmt'])
        
    print("Min Beacon Size: ", struct.calcsize(unpack_str))

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

        # generate the header
        header = "========= Beacon: " + str(len(line))  + " bytes ========="
        print(header)

        print("RAW: ", line.hex())

        try:
            data = struct.unpack_from(unpack_str, line)
            #data = struct.unpack_from('BBBIIbBBB', line)
        except struct.error as exc:
            print('Parse error: {}\n'.format(exc))
            continue

        # add the parsed values to the table
        disp = []
        for i in range(len(data)):
            p = parts[i]
            disp.append([p['name'], str(data[i]), p['t']])

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
    {'name': 'APRS Data Type', 't': uint8}, 
    {'name': 'APRS Revision', 't': uint8}, 
    {'name': 'Oresat0 State', 't': state, 'fmt': lambda s : str(s)}, # TODO might not need for char
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
    #{'name': 'OPD Current', 't': uint8}, 
    #{'name': 'OPD State', 't': state}, 

    #{'name': 'Battery Pack 1 Vbatt', 't': uint16}, 
    #{'name': 'Battery Pack 1 Vcell', 't': uint16}, 
    #{'name': 'Battery Pack 1 Vcell max', 't': uint16},
    #{'name': 'Battery Pack 1 Vcell min', 't': uint16}, 
    #{'name': 'Battery Pack 1 Vcell 1', 't': uint16}, 
    #{'name': 'Battery Pack 1 Vcell 2', 't': uint16}, 
    #{'name': 'Battery Pack 1 Vcell avg', 't': uint16}, 
    #{'name': 'Battery Pack 1 temp', 't': int16}, 
    #{'name': 'Battery Pack 1 temp avg', 't': int16}, 
    #{'name': 'Battery Pack 1 temp max', 't': int16}, 
    #{'name': 'Battery Pack 1 temp min', 't': int16}, 
    #{'name': 'Battery Pack 1 current', 't': int16}, 
    #{'name': 'Battery Pack 1 current avg', 't': int16},
    #{'name': 'Battery Pack 1 current max', 't': int16},
    #{'name': 'Battery Pack 1 current min', 't': int16},
    #{'name': 'Battery Pack 1 state', 't': uint8}, 
    #{'name': 'Battery Pack 1 reported state of change', 't': uint8},
    #{'name': 'Battery Pack 1 full capacity', 't': uint16},
    #{'name': 'Battery Pack 1 reported capacity', 't': uint16},

    #{'name': 'Battery Pack 2 Vbatt', 't': uint16},
    #{'name': 'Battery Pack 2 Vcell', 't': uint16},
    #{'name': 'Battery Pack 2 Vcell max', 't': uint16},
    #{'name': 'Battery Pack 2 Vcell min', 't': uint16}, 
    #{'name': 'Battery Pack 2 Vcell 1', 't': uint16}, 
    #{'name': 'Battery Pack 2 Vcell 2', 't': uint16}, 
    #{'name': 'Battery Pack 2 Vcell avg', 't': uint16}, 
    #{'name': 'Battery Pack 2 temp', 't': int16}, 
    #{'name': 'Battery Pack 2 temp avg', 't': int16}, 
    #{'name': 'Battery Pack 2 temp max', 't': int16}, 
    #{'name': 'Battery Pack 2 temp min', 't': int16}, 
    #{'name': 'Battery Pack 2 current', 't': int16}, 
    #{'name': 'Battery Pack 2 current avg', 't': int16}, 
    #{'name': 'Battery Pack 2 current max', 't': int16}, 
    #{'name': 'Battery Pack 2 current min', 't': int16}, 
    #{'name': 'Battery Pack 2 state', 't': uint8}, 
    #{'name': 'Battery Pack 2 reported state of change', 't': uint8}, 
    #{'name': 'Battery Pack 2 full capacity', 't': uint16}, 
    #{'name': 'Battery Pack 2 reported capacity', 't': uint16}, 

    #{'name': 'Solar -X Voltage Avg', 't': uint16}, 
    #{'name': 'Solar -X Current Avg', 't': int16}, 
    #{'name': 'Solar -X Power Avg', 't': uint16}, 
    #{'name': 'Solar -X Voltage Max', 't': uint16}, 
    #{'name': 'Solar -X Current Max', 't': int16}, 
    #{'name': 'Solar -X Power Max', 't': uint16}, 
    #{'name': 'Solar -X Energy', 't': uint16}, 

    #{'name': 'Solar -Y Voltage Avg', 't': uint16}, 
    #{'name': 'Solar -Y Current Avg', 't': int16}, 
    #{'name': 'Solar -Y Power Avg', 't': uint16}, 
    #{'name': 'Solar -Y Voltage Max', 't': uint16}, 
    #{'name': 'Solar -Y Current Max', 't': int16}, 
    #{'name': 'Solar -Y Power Max', 't': uint16}, 
    #{'name': 'Solar -Y Energy', 't': uint16}, 

    #{'name': 'Solar +X Voltage Avg', 't': uint16},
    #{'name': 'Solar +X Current Avg', 't': int16},
    #{'name': 'Solar +X Power Avg', 't': uint16}, 
    #{'name': 'Solar +X Voltage Max', 't': uint16}, 
    #{'name': 'Solar +X Current Max', 't': int16}, 
    #{'name': 'Solar +X Power Max', 't': uint16}, 
    #{'name': 'Solar +X Energy', 't': uint16}, 

    #{'name': 'Solar +Y Voltage Avg', 't': uint16}, 
    #{'name': 'Solar +Y Current Avg', 't': int16}, 
    #{'name': 'Solar +Y Power Avg', 't': uint16}, 
    #{'name': 'Solar +Y Voltage Max', 't': uint16},
    #{'name': 'Solar +Y Current Max', 't': int16},
    #{'name': 'Solar +Y Power Max', 't': uint16},
    #{'name': 'Solar +Y Energy', 't': uint16},

    #{'name': 'Star Tracker eMMC Capacity', 't': uint8},
    #{'name': 'Star Tracker Readable Files', 't': uint8},
    #{'name': 'Star Tracker Updater Status', 't': uint8},
    #{'name': 'Star Tracker Updates Cached', 't': uint8},
    #{'name': 'Star Tracker Right Ascension', 't': int16},
    #{'name': 'Star Tracker Declination', 't': int16},
    #{'name': 'Star Tracker Roll', 't': int16},
    #{'name': 'Star Tracker Timestamp Last Packet', 't': uint32},

    #{'name': 'GPS eMMC Capacity', 't': uint8},
    #{'name': 'GPS Readable Files', 't': uint8},
    #{'name': 'GPS Updater Status', 't': uint8}, 
    #{'name': 'GPS Updates Cached', 't': uint8}, 
    #{'name': 'GPS Status', 't': uint8}, 
    #{'name': 'GPS Num Sats Locked', 't': uint8}, 
    #{'name': 'GPS X Pos', 't': int32}, 
    #{'name': 'GPS Y Pos', 't': int32}, 
    #{'name': 'GPS Z Pos', 't': int32},
    #{'name': 'GPS X Vel', 't': int32},
    #{'name': 'GPS Y Vel', 't': int32},
    #{'name': 'GPS Z Vel', 't': int32}, 
    #{'name': 'GPS Timestamp Last Packet', 't': uint32},

    #{'name': 'ADS Gyro Roll Dot', 't': int16},
    #{'name': 'ADS Gyro Pitch Dot', 't': int16},
    #{'name': 'ADS Gyro Yaw Dot', 't': int16},
    #{'name': 'ADS Gyro IMU temp', 't': int8},

    #{'name': 'DxWifi eMMC Capacity', 't': uint8},
    #{'name': 'DxWifi Readable Files', 't': uint8},
    #{'name': 'DxWifi Updater Status', 't': uint8}, 
    #{'name': 'DxWifi Updates Cached', 't': uint8}, 
    #{'name': 'DxWifi Transmitting', 't': uint8}, # bool

    #{'name': 'APRS CRC-32', 't': uint32},
    #{'name': 'APRS Data Type', 't': uint8},
]
try:
    main()
except KeyboardInterrupt:
    sys.exit()
