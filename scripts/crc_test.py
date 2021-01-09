#!/usr/bin/python3
import crcmod
import time
from serial import Serial
import random
import threading
import sys

print(sys.argv)

# open serial port
ser = Serial("/dev/ttyACM0", 115200)

# the FW image program section file is the first arg, 
fw_img = open(sys.argv[1], 'rb').read()

# thread_exit flags that the thread should exit
thread_exit = 0

# function to be run in thread, that reads serial
# and writes it to a file
def ser_read():
    ser = Serial("/dev/ttyACM0", 115200, timeout=1)
    f = open("crc_out", "w+")
    f.write("==========================================\n")
    f.write("==========================================\n")
    while 1:
        # read a line from the file
        line = ser.readline()

        # write the line to the file and flush to 
        # it is written immediately
        f.write(line.decode('utf-8'))
        f.flush()

        if thread_exit:
            print("exitting read thread...")
            return

# read serial in thread
t = threading.Thread(target=ser_read)
t.start()
  
# create CRC func with:
# - polynomial 0x4C11DB7 (1 is MSB is usually implicit, just not in python)
# - initial value of 0xffffffff
# - no bit reversal
# - xorOut of 0x00000000
# These settings match the default settings on the STM32 CRC unit
crc_func = crcmod.mkCrcFun(0x104C11DB7, initCrc=0xffffffff, rev=False, xorOut=0x00000000)

# large buffer size with odd number of bytes
#buffer_size = (1<<15) + 1223
#data = bytearray(buffer_size)

fw_img_len = len(fw_img)

# CRC the fw image
fw_crc = crc_func(fw_img)

print("FW Image Program Size: ", fw_img_len)
print("FW CRC: ", hex(fw_crc)) 

# get the image CRC, length, and flags as bytes
fw_crc_b = fw_crc.to_bytes(4, 'little')
fw_len_b = fw_img_len.to_bytes(4, 'little')
flags_b = int(0).to_bytes(4, 'little')

# package the bytes into a struct
fw_header = bytearray(fw_crc_b + fw_len_b + flags_b)

# write the FW header struct bytes
n = ser.write(fw_header)

# wait a sec for the uC to parse and CRC it
time.sleep(0.2)

sent = 0
while sent < len(fw_img):
    # buffer length is 2048, unless there are less than
    # that many bytes left in the buffer
    buf_len = 2048
    if (fw_img_len - sent) < 2048:
        buf_len = fw_img_len - sent

    # send the byte array
    n = ser.write(fw_img[sent:sent+buf_len])
    print("wrote {} bytes of program".format(n))

    sent += n
    
    # wait a sec for block to be written to flash
    time.sleep(0.2)

print("Sent {} bytes total".format(sent))

# give the thread a sec to finish, then tell it to exit
time.sleep(1)
thread_exit = 1
t.join()
print("exit")

