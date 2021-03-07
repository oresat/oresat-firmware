import can
#This does testing of the CAN bootloader from python using a CANable attached to the host PC

# Stock slcan firmware on Linux
bus = can.interface.Bus(bustype='slcan', channel='/dev/ttyACM1', bitrate=1000000)



rx_msg = bus.recv()
print("rx_msg.arbitration_id = " + str(rx_msg.arbitration_id))
print("rx_msg.dlc = " + str(rx_msg.dlc))
print("rx_msg.data = " + str(rx_msg.data))

def rx_ack_nack(bus, sid):
    msg = bus.recv(0.25)
    print("RX msg: " + str(msg))

    if( msg.arbitration_id == sid and msg.dlc == 1 ):
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
            
         
CAN_COMMAND_GET = 0x00
CAN_COMMAND_READ_MEMORY = 0x11
CAN_COMMAND_GO = 0x21
CAN_COMMAND_WRITE_MEMORY = 0x31
CAN_COMMAND_ERASE = 0x43


def read_memory(bus, read_address, num_bytes_to_read):
    print("Reading data at address...")
    msg = can.Message(arbitration_id=CAN_COMMAND_READ_MEMORY,
            data=[(read_address >> 24) & 0xFF, (read_address >> 16) & 0xFF, (read_address >> 8) & 0xFF, (read_address >> 0) & 0xFF, num_bytes_to_read],
            is_extended_id=True)
    bus.send(msg)
    rx_ack_nack(bus, CAN_COMMAND_READ_MEMORY)

    total_bytes_read = 0
    while(total_bytes_read < num_bytes_to_read):
        # read data
        msg = bus.recv(0.25)
        print("Data readback is " + str(msg))
        total_bytes_read += msg.dlc

    rx_ack_nack(bus, CAN_COMMAND_READ_MEMORY)

    purge_rx_buff(bus)

    return


def erase_page(bus, list_of_page_numbers):
    print("Erasing page numbers " + str(list_of_page_numbers))
    purge_rx_buff(bus)

    msg = can.Message(arbitration_id=CAN_COMMAND_ERASE,
                   data=list_of_page_numbers,
                   is_extended_id=True)
    
    bus.send(msg)
    rx_ack_nack(bus, CAN_COMMAND_ERASE)
    for i in range(0, len(list_of_page_numbers)):
        rx_ack_nack(bus, CAN_COMMAND_ERASE)

    purge_rx_buff(bus)

    return


def write_memory(bus, base_address, byte_list):
    print("Writing " + str(len(byte_list)) + " bytes at address 0x" + hex(base_address))

    msg = can.Message(arbitration_id=CAN_COMMAND_WRITE_MEMORY,
            data=[(base_address >> 24) & 0xFF, (base_address >> 16) & 0xFF, (base_address >> 8) & 0xFF, (base_address >> 0) & 0xFF, len(byte_list)],
            is_extended_id=True)
    bus.send(msg)
    rx_ack_nack(bus, msg.arbitration_id)

    idx = 0
    while(True):
        temp_data = []
        while( idx < len(byte_list) and len(temp_data) < 8 ):
            temp_data.append(byte_list[idx])
            idx += 1
            
        if( len(temp_data) > 0 ):
            msg = can.Message(arbitration_id=0x04, data=temp_data, is_extended_id=True)
            bus.send(msg)
            rx_ack_nack(bus, CAN_COMMAND_WRITE_MEMORY)
        else:
            break

    rx_ack_nack(bus, CAN_COMMAND_WRITE_MEMORY)

    return


def firmware_update(bus, address, firmware_image):
    for i in range(20, 126):
        erase_page(bus, [i])
    
    buff = []
    with open(firmware_image, 'rb') as f:
        byte = f.read(1)
        while byte != b"":
            buff.append(byte)
            byte = f.read(1)


    #address = 0x0800A000
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
    msg = can.Message(arbitration_id=CAN_COMMAND_GO, data=[], is_extended_id=True)
    bus.send(msg)

    rx_ack_nack(bus, CAN_COMMAND_GO)

    return

if( rx_msg.arbitration_id == CAN_COMMAND_GET and rx_msg.dlc == 8 ):
    if(rx_msg.data[0] == 0x01 and rx_msg.data[1] == 0x02 and rx_msg.data[2] == 0x03 and rx_msg.data[3] == 0x04 ):
        msg = can.Message(arbitration_id=rx_msg.arbitration_id,
                   data=[rx_msg.data[4], rx_msg.data[5], rx_msg.data[6], rx_msg.data[7], 0x01, 0x02, 0x03, 0x04],
                   is_extended_id=True)

        bus.send(msg)
        rx_ack_nack(bus, msg.arbitration_id)
        print("Reading number of bytes")
        msg_number_of_bytes = bus.recv(0.25)
        number_of_frames = msg_number_of_bytes.data[0]
        print("number_of_frames = " + str(number_of_frames))

        for i in range(0, number_of_frames):
            msg_command_type = bus.recv(0.25)
            print(str(msg_command_type))

        rx_ack_nack(bus, msg.arbitration_id)

        purge_rx_buff(bus)



        firmware_update(bus, 0x0800A000, '../app_protocard2/build/app_protocard2.crc32.bin')
        # read_memory(bus, 0x0800A000, 32)
        
        # #erase_page(bus, [128])
        # erase_page(bus, [126, 20])

        # read_memory(bus, 0x0800A000, 32)

        # write_memory(bus, 0x0800A000, [0x0A, 0x0B, 0x0C, 0x0D, 0x01, 0x02, 0x03, 0x04, 0x05])

        # read_memory(bus, 0x0800A000, 32)

        # can_go(bus)
        



        


        
        

        
        

