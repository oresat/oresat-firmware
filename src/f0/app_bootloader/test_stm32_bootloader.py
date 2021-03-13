import can
import time,math
#This does testing of the CAN bootloader from python using a CANable attached to the host PC

BOOTLOADER_EXPECTED_FIRST_FRAME_ID = 0x79

CAN_COMMAND_GET = 0x00
CAN_COMMAND_READ_MEMORY = 0x11
CAN_COMMAND_GO = 0x21
CAN_COMMAND_WRITE_MEMORY = 0x31
CAN_COMMAND_ERASE = 0x43


def rx_ack_nack(bus, sid, timeout=0.25):
    msg = bus.recv(timeout)
    print("RX msg: " + str(msg))

    if( msg is not None and msg.arbitration_id == sid and msg.dlc == 1 ):
        if( msg.data[0] == 0x79 ):
            print("Got ACK from device")
            return(True)
        elif( msg.data[0] == 0x1F ):
            print("Got NACK from device")
            return(False)

    raise Exception("Got unexpected CAN frame type: " + str(msg))


def purge_rx_buff(bus):
    countdown = 3
    while( countdown > 0 ):
        if( bus.recv(0.05) ):
             countdown = 3
        else:
            countdown -= 1
            
    return


def read_memory(bus, read_address, num_bytes_to_read):
    print("Reading " + str(num_bytes_to_read) + " bytes of data at address 0x" + hex(read_address))
    msg = can.Message(arbitration_id=CAN_COMMAND_READ_MEMORY,
            data=[(read_address >> 24) & 0xFF, (read_address >> 16) & 0xFF, (read_address >> 8) & 0xFF, (read_address >> 0) & 0xFF, num_bytes_to_read - 1],
            is_extended_id=False)
    bus.send(msg)
    rx_ack_nack(bus, CAN_COMMAND_READ_MEMORY)

    expected_frame_count = int(math.ceil((num_bytes_to_read) / 8.0))
    print("expected_frame_count = " + str(expected_frame_count))

    #total_bytes_read = 0
    for idx in range(0, expected_frame_count):
        # read data
        msg = bus.recv(0.25)
        print("Data readback is " + str(msg))
        #total_bytes_read += msg.dlc

    rx_ack_nack(bus, CAN_COMMAND_READ_MEMORY)

    purge_rx_buff(bus)

    return


def erase_all_pages(bus):
    print("Eraseing all pages")
    msg = can.Message(arbitration_id=CAN_COMMAND_ERASE, data=[0xFF], is_extended_id=False)
    print("Sending " + str(msg))
    bus.send(msg)
    rx_ack_nack(bus, CAN_COMMAND_ERASE)

    return


def erase_page(bus, list_of_page_numbers):
    print("Erasing page numbers " + str(list_of_page_numbers))
    purge_rx_buff(bus)

    num_pages_to_erase = len(list_of_page_numbers)
    data = [num_pages_to_erase - 1]
    data.extend(list_of_page_numbers)
    msg = can.Message(arbitration_id=CAN_COMMAND_ERASE, data=data, is_extended_id=False)
    print("Sending " + str(msg))
    
    bus.send(msg)
    rx_ack_nack(bus, CAN_COMMAND_ERASE)

    for i in range(0, len(list_of_page_numbers)):
        rx_ack_nack(bus, CAN_COMMAND_ERASE, timeout=5.0)

    purge_rx_buff(bus)

    return


def write_memory(bus, base_address, byte_list):
    print("Writing " + str(len(byte_list)) + " bytes at address 0x" + hex(base_address))

    msg = can.Message(arbitration_id=CAN_COMMAND_WRITE_MEMORY,
            data=[(base_address >> 24) & 0xFF, (base_address >> 16) & 0xFF, (base_address >> 8) & 0xFF, (base_address >> 0) & 0xFF, len(byte_list)],
            is_extended_id=False)
    bus.send(msg)
    rx_ack_nack(bus, msg.arbitration_id)

    idx = 0
    while(True):
        temp_data = []
        while( idx < len(byte_list) and len(temp_data) < 8 ):
            temp_data.append(byte_list[idx])
            idx += 1
            
        if( len(temp_data) > 0 ):
            msg = can.Message(arbitration_id=0x04, data=temp_data, is_extended_id=False)
            print("Sending: " + str(msg))
            bus.send(msg)
            rx_ack_nack(bus, CAN_COMMAND_WRITE_MEMORY)
        else:
            break

    rx_ack_nack(bus, CAN_COMMAND_WRITE_MEMORY)

    return


def firmware_update(bus, address, firmware_image):
    page_list = range(20, 126)

    while( len(page_list) > 0 ):
        page_list_2 = []
        while( len(page_list_2) < 7 and len(page_list) > 0 ):
            page_list_2.append(page_list.pop(0))
        if( len(page_list) > 0 ):
            erase_page(bus, page_list_2)

    # for i in range(20, 126):
    #     erase_page(bus, [i])
    
    buff = []
    with open(firmware_image, 'rb') as f:
        byte = f.read(1)
        while byte != b"":
            buff.append(byte)
            byte = f.read(1)


    while(len(buff) > 0):
        data = []
        for i in range(0, 64):
            if( len(buff) == 0 ):
                break

            data.append(int.from_bytes(buff.pop(0), 'big'))
        
        write_memory(bus, address, data)
        address += len(data)

    can_go(bus)

    return


def can_go(bus):
    msg = can.Message(arbitration_id=CAN_COMMAND_GO, data=[], is_extended_id=False)
    bus.send(msg)

    rx_ack_nack(bus, CAN_COMMAND_GO)

    return


def can_get(bus):
    msg = can.Message(arbitration_id=CAN_COMMAND_GET, data=[], is_extended_id=False)

    bus.send(msg)
    rx_ack_nack(bus, msg.arbitration_id)

    print("Reading number of bytes")
    msg_number_of_bytes = bus.recv(0.25)
    print(str(msg_number_of_bytes))

    number_of_frames = msg_number_of_bytes.data[0] + 1
    print("number_of_frames = " + str(number_of_frames))

    for i in range(0, number_of_frames):
        msg_command_type = bus.recv(0.25)
        print(str(msg_command_type))

    rx_ack_nack(bus, msg.arbitration_id)

    print("Done with can_get()")

    purge_rx_buff(bus)

    return


def test_can_bootloader_client(bus, is_407_cpu=True):
    #purge_rx_buff(bus)
    can_get(bus)

    # read_memory(bus, 0x08000000, 31)
    # read_memory(bus, 0x08000000, 32)
    # read_memory(bus, 0x08000000, 33)

    # read_memory(bus, 0x0800A000, 32)
    # write_memory(bus, 0x0800A000, [0x0A, 0x0B, 0x0C, 0x0D, 0x01, 0x02, 0x03, 0x04, 0x05])
    # read_memory(bus, 0x0800A000, 32)
    
    # erase_page_list = [20, 21, 22, 23]
    # if( is_407_cpu ):
    #     erase_page_list = [0, 1, 2, 3]
    #     erase_page_list = [3]

    # erase_page(bus, erase_page_list)
    # read_memory(bus, 0x0800A000, 32)

    # write_memory(bus, 0x0800A000, [0x0A, 0x0B, 0x0C, 0x0D, 0x01, 0x02, 0x03, 0x04, 0x05])
    # read_memory(bus, 0x0800A000, 32)

    if( not is_407_cpu ):
        firmware_update(bus, 0x0800A000, '../app_protocard2/build/app_protocard2.crc32.bin')
    
    return




if( True ):
    rx_msg = None
    bitrate = 1000000

    bus = can.interface.Bus(bustype='slcan', channel='/dev/ttyACM1', bitrate=bitrate)
    while( rx_msg is None ):
        rx_msg = bus.recv(1)
        if( rx_msg is None ):
            print("No RX message yet")

    if( rx_msg.arbitration_id == CAN_COMMAND_GET and rx_msg.dlc == 8 ):
        if(rx_msg.data[0] == 0x01 and rx_msg.data[1] == 0x02 and rx_msg.data[2] == 0x03 and rx_msg.data[3] == 0x04 ):
            msg = can.Message(arbitration_id=BOOTLOADER_EXPECTED_FIRST_FRAME_ID,
                    data=[rx_msg.data[4], rx_msg.data[5], rx_msg.data[6], rx_msg.data[7], 0x01, 0x02, 0x03, 0x04],
                    is_extended_id=False)

            print("Sending " + str(msg))
            bus.send(msg)
            #rx_ack_nack(bus, msg.arbitration_id)

            test_can_bootloader_client(bus, False)
else:
    bitrate = 125000
    bus = can.interface.Bus(bustype='slcan', channel='/dev/ttyACM0', bitrate=bitrate)

    for i in range(0, 99999):
        msg = can.Message(arbitration_id=BOOTLOADER_EXPECTED_FIRST_FRAME_ID, data=[0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA], is_extended_id=False)

        bus.send(msg)
        print(str(time.time()) + " Sent Initialization frame: " + str(msg))

        rx_msg = bus.recv(0.05)
        if( rx_msg is not None ):
            print("RX: " + str(rx_msg))
            test_can_bootloader_client(bus, True)
            break
        
        time.sleep(0.2)

        

        
        

