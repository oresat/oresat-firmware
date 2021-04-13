import sys,os
import struct
import binascii

input_fw_bin_file = sys.argv[1]
output_fw_bin_file = sys.argv[2]
version = sys.argv[3] # 20200101

total_length = 1020 + os.path.getsize(input_fw_bin_file)


f = open(output_fw_bin_file, 'wb')

f.write(struct.pack("I", total_length))
f.write(struct.pack("I", int(version)))
for i in range(0, int((1024 - 4 - 4 - 4) / 4)):
    f.write(struct.pack("I", 0xFFFFFFFF))

f.write(open(input_fw_bin_file, 'rb').read())
f.close()


concated_data = open(output_fw_bin_file, 'rb').read()
crc32 = binascii.crc32(concated_data)

f = open(output_fw_bin_file, 'wb')
f.write(struct.pack("I", crc32))
f.write(concated_data)
f.close()

print("Final Length: " + str(total_length))
print("Final CRC32: 0x" + str(hex(crc32)))

