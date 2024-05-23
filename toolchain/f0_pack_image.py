'''Prepends metadata (crc, length, version) to F0 firmware images'''
import binascii
import os
import struct
import sys

input_fw_bin_file = sys.argv[1]
output_fw_bin_file = sys.argv[2]
version = sys.argv[3]  # e.g. 20200101

# See app_bootloader struct FirmwareMetadata for definition. Metadata consists
# of 3 uint32_t at the end of the metadata block (which is just before the
# firmware block, see ld/STM32F091xC-bootloader.ld)
LENGTH_LEN = 4
VERSION_LEN = 4

# The length that gets CRC'd. Doesn't include the CRC space itself, but
# does include everything else
total_length = LENGTH_LEN + VERSION_LEN + os.path.getsize(input_fw_bin_file)

with open(input_fw_bin_file, 'rb') as f:
    metadata = struct.pack("II", total_length, int(version))
    firmware = f.read()
    crc32 = binascii.crc32(metadata + firmware)

with open(output_fw_bin_file, 'wb') as f:
    f.write(struct.pack("I", crc32))
    f.write(metadata)
    f.write(firmware)

print(f"Final Length: {total_length}")
print(f"Final CRC32: 0x{hex(crc32)}")
