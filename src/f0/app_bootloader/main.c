#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "oresat_f0.h"
#include "can_hw.h"
#include "crc.h"
#include <string.h>
// FIXME locking for flash commands
#include "flash_f0.h"
#include "util.h"

#define ARRAY_LEN(x) (sizeof(x)/sizeof(x[0]))
#define MIN(a,b) (((a)<(b))?(a):(b))

#define SERIAL ((BaseSequentialStream*)&SD2)
#ifdef DEBUG_PRINT
#define dbgprintf(...) chprintf(SERIAL, __VA_ARGS__)
#else
#define dbgprintf(...)
#endif

#define BOOTLOADER_VERSION                           0xAC
#define CAN_DRIVER                                   &CAND1

#define CAN_RECEIVE_TIMEOUT                          TIME_MS2I(150)
#define CAN_RECEIVE_TIMEOUT_LONG                     TIME_MS2I(500)
#define CAN_TRANSMIT_TIMEOUT                         TIME_MS2I(150)

#define CAN_ANNOUNCE_MAGIC_NUMBER                    0x04030201
#define UID_LOW                                      (*((const uint32_t *) UID_BASE))
#define BOOTLOADER_ACK                               0x79
#define BOOTLOADER_NACK                              0x1F

struct FirmwareMetadata {
    uint32_t crc;
    uint32_t length;
    uint32_t version;
} __attribute__((packed));

struct FirmwareVectors {
    uint32_t main_stack_addr;
    __attribute__((noreturn)) void (*reset_handler)(void);
} __attribute__((packed));

// The firmware metadata block starts takes up flash page 20, between the
// bootloader and firmware blocks. The relevant metadata lives at the end of the block
#define METADATA (((struct FirmwareMetadata*)(__flash1_end__)) - 1)
#define FIRMWARE_MAX_LENGTH (FLASH1_SIZE + FLASH2_SIZE)
#define FIRMWARE_CRC_START ((void*)&(METADATA->length))
#define VECTORS ((struct FirmwareVectors*)(__flash2_base__))

// The CAN bootloader protocol described in ST Application Note AN3154
// designates CAN IDs for each of the bootloader commands, but there are two
// flaws with the layout for our purposes:
//  - There's no way to distinguish messages from multiple bootloaders on the
//    same CAN network - they all use the same IDs. (See also AN3154 p7 note)
//  - The bootloader is not CANopen aware, so messages intrude into the CANopen
//    address space. Particularly NMT messages which are top priority.
// The previous iteration attempted to solve the first flaw by extending the
// protocol by broadcasting the UID of the MCU as an initial step and then
// looking for the UID as part of the enter wait-for-command stage. The
// downside is that we have no way to associate the UID to CANopen Node ID
// a priori, and we also expect the hardware to change, meaning the UIDs would
// have to be re-associated every time. It also further impinged on the CANopen
// address space.
//
// This new scheme fits the bootloader commands entirely into the CANopen
// reserved address spaces, that are assigned no meaning in CANopen. It also
// remaps the commands based on Node ID, so that each card has a unique set of
// command CAN IDs. This scheme relies on Oresat's convention that Node IDs are
// spaced at least 3, but generally 4 apart. The only downside is that the CAN
// IDs need to be generated at runtime, they are not static.
//
// See CiA301 table 40 (also note typo in decimal representation for 780h) for
// reserved address ranges. See oresat-configs cards.csv for assigned node IDs
#define COMMAND_ANNOUNCE_OFFSET     (0x000)
#define COMMAND_WRITE_MEMORY_OFFSET (0x001)
#define COMMAND_ERASE_OFFSET        (0x002)
#define COMMAND_GET_OFFSET          (0x780)
#define COMMAND_READ_MEMORY_OFFSET  (0x781)
#define COMMAND_GO_OFFSET           (0x782)

#define COMMAND_ANNOUNCE(node_id)     ((node_id) + COMMAND_ANNOUNCE_OFFSET)
#define COMMAND_WRITE_MEMORY(node_id) ((node_id) + COMMAND_WRITE_MEMORY_OFFSET)
#define COMMAND_ERASE(node_id)        ((node_id) + COMMAND_ERASE_OFFSET)
#define COMMAND_GET(node_id)          ((node_id) + COMMAND_GET_OFFSET)
#define COMMAND_READ_MEMORY(node_id)  ((node_id) + COMMAND_READ_MEMORY_OFFSET)
#define COMMAND_GO(node_id)           ((node_id) + COMMAND_GO_OFFSET)

#define OPTION_DATA0 ((FLASH->OBR & FLASH_OBR_DATA0_Msk) >> FLASH_OBR_DATA0_Pos)

static uint8_t node_id(void) {
    const uint8_t id = OPTION_DATA0;
    if(id == 0 || id == 0xFF || id % 4) {
        return 0x7C; // prevents commands from intruding into CANopen ID space
    }
    return id;
}

static const char* command_offset_to_str(const uint32_t v) {
    switch (v) {
    case COMMAND_GET_OFFSET:
        return "COMMAND_GET";
    case COMMAND_READ_MEMORY_OFFSET:
        return "COMMAND_READ_MEMORY";
    case COMMAND_GO_OFFSET:
        return "COMMAND_GO";
    case COMMAND_WRITE_MEMORY_OFFSET:
        return "COMMAND_WRITE_MEMORY";
    case COMMAND_ERASE_OFFSET:
        return "COMMAND_ERASE";
    }
    return "Invalid command";
}

// Duplicated because different TX and RX types
static void dbgprint_frame_tx(const CANTxFrame * const msg) {
    dbgprintf("TX Frame - SID = 0x%03X DLC = %u RTR = %u IDE = %u [ ",
        msg->SID, msg->DLC, msg->RTR, msg->IDE);
    for(int i = 0; i < msg->DLC; i++) {
        dbgprintf("%02X ", msg->data8[i]);
    }
    dbgprintf("] ");
}

static void dbgprint_frame_rx(const CANRxFrame * const msg) {
    dbgprintf("RX Frame - SID = 0x%03X DLC = %u RTR = %u IDE = %u [ ",
        msg->SID, msg->DLC, msg->RTR, msg->IDE);
    for(int i = 0; i < msg->DLC; i++) {
        dbgprintf("%02X ", msg->data8[i]);
    }
    dbgprintf("] ");
}

static msg_t can_transmit(const CANTxFrame * const msg) {
    dbgprint_frame_tx(msg);
    const msg_t r = canTransmitTimeout(CAN_DRIVER, CAN_ANY_MAILBOX, msg, CAN_TRANSMIT_TIMEOUT);
    if(r == MSG_OK) {
        // FIXME: if we send messages too fast the can driver seems to silently drop them instead
        // of returning an error??? Having these print statements here seems slow things down
        // enough that it works. This is particularly noticeable in command_read_memory because
        // it does a lot of sending
        chprintf(SERIAL,"- SUCCESS\r\n");
        //dbgprintf("- SUCCESS\r\n");
    } else {
        chprintf(SERIAL, " - FAIL\r\n");
        //dbgprintf(" - FAIL\r\n");
    }
    return r;
}

__attribute__((warn_unused_result)) static msg_t can_receive(CANRxFrame * const msg, const sysinterval_t timeout) {
    const msg_t r = canReceiveTimeout(CAN_DRIVER, CAN_ANY_MAILBOX, msg, timeout);
    switch(r) {
    case MSG_OK:
        dbgprint_frame_rx(msg);
        dbgprintf("\r\n");
        break;
    case MSG_TIMEOUT:
        dbgprintf(".");
        break;
    default:
        dbgprintf("Error receiving CAN frame: %s\r\n", msg_t_to_str(r));
    }
    return r;
}

static msg_t send_ack(const CANRxFrame * const cmd) {
    dbgprintf("Transmitting CAN bootloader ACK\r\n");
    return can_transmit(&(CANTxFrame){
        .SID = cmd->SID,
        .DLC = 1,
        .data8 = { BOOTLOADER_ACK },
    });
}

static msg_t send_nack(const CANRxFrame * const cmd) {
    dbgprintf("Transmitting CAN bootloader NACK\r\n");
    return can_transmit(&(CANTxFrame){
        .SID = cmd->SID,
        .DLC = 1,
        .data8 = { BOOTLOADER_NACK },
    });
}

static msg_t announce_presence_on_bus(const uint16_t node_id) {
    dbgprintf("\r\nBootloader announcing presence on bus...\r\n");
    return can_transmit(&(CANTxFrame){
        .SID = COMMAND_ANNOUNCE(node_id),
        .DLC = 8,
        .data32 = { 0x04030201, UID_LOW },
    });
}

__attribute__((noreturn)) static void soft_reset_cortex_m0(void) {
    // FIXME: flush/wait for completion of CAN/Serial instead of sleep
    chThdSleepMilliseconds(100);
    sdStop(&SD2);
    chSysDisable();

    NVIC_SystemReset();
}

static void command_get(const CANRxFrame * const cmd, const uint16_t id) {
    send_ack(cmd);

    // We implement only a subset of AN3154, omitting all ReadOutProtect
    // handling, write [un]protect, speed, and ID.
    const uint16_t cmd_list[] = {
        BOOTLOADER_VERSION,
        COMMAND_GET(id),
        COMMAND_READ_MEMORY(id),
        COMMAND_GO(id),
        COMMAND_WRITE_MEMORY(id),
        COMMAND_ERASE(id),
    };

    can_transmit(&(CANTxFrame) {
        .SID = cmd->SID,
        .DLC = 1,
        .data8 = { ARRAY_LEN(cmd_list) - 1 },
    });

    for(size_t i = 0; i < ARRAY_LEN(cmd_list); i++) {
        can_transmit(&(CANTxFrame){
            .SID = cmd->SID,
            .DLC = 2,
            // We're little endian but data gets sent big endian
            .data16 = { __builtin_bswap16(cmd_list[i]) },
        });
    }
    send_ack(cmd);
}

static bool valid_read_region(const uint8_t * const start, const uint16_t length) {
    const uint8_t * const end = start + length - 1;
    if(start >= __flash0_base__ && end < __flash2_end__)
        return true;
    if(start >= __ram0_base__ && end < __ram1_end__)
        return true;
    // TODO: AN3154 specifies that the system and option memory regions  are
    // valid for reading, but they've been omitted here because of time
    // constraints.
    return false;
}

static void command_read_memory(const CANRxFrame * const cmd) {
    if(cmd->DLC != 5) {
        send_nack(cmd);
        return;
    }
    // Address is sent in big endian, we're little endian
    uint8_t *read_address = (uint8_t *)__builtin_bswap32(cmd->data32[0]);
    uint16_t bytes_to_read = cmd->data8[4] + 1;

    dbgprintf("Address to read from: 0x%X\r\n", read_address);
    dbgprintf("Number of bytes to read: %u\r\n", bytes_to_read);

    if(bytes_to_read > 256) {
        send_nack(cmd);
        return;
    }
    if(!valid_read_region(read_address, bytes_to_read)) {
        send_nack(cmd);
        return;
    }
    // TODO: AN3154 says nack if ReadOutProtection is enabled and I think this
    // is something in the option bytes? But we don't use it and I'm too lazy to
    // check right now.
    send_ack(cmd);

    while(bytes_to_read > 0) {
        CANTxFrame reply = {
            .SID = cmd->SID,
            .DLC = MIN(bytes_to_read, 8),
        };
        memcpy(reply.data8, read_address, reply.DLC);
        bytes_to_read -= reply.DLC;
        read_address += reply.DLC;

        dbgprintf("Transmitting %u bytes in response to read request.\r\n", reply.DLC);
        if(can_transmit(&reply)) {
            break;
        }
    }

    send_ack(cmd);
}

static void command_go(const CANRxFrame * const cmd) {
    // TODO: AN3154 says nack if ReadOutProtection is enabled and I think this
    // is something in the option bytes? But we don't use it and I'm too lazy to
    // check right now.
    //
    // We also omit the the address argument, only allowing jumps to the linker
    // specified start of firmware. This has the nice property of allowing GO
    // to be unable to fail.
    send_ack(cmd);
}


static bool valid_write_range(const uint8_t * const start, const uint32_t length) {
    // TODO: While the general spec allows for writes to SRAM, option, and the
    // whole flash range, we limit this to application flash for safety. SRAM
    // and option might be worthwhile in the future?
    const uint8_t * const end = start + length - 1;
    return start >= __flash0_end__ && end < __flash2_end__;
}


static void command_write_memory(const CANRxFrame * const cmd) {
    if(cmd->DLC != 5) {
        send_nack(cmd);
        return;
    }
    // Address is sent in big endian, we're little endian
    const void * const write_address = (void *)__builtin_bswap32(cmd->data32[0]);
    const uint16_t bytes_to_write = cmd->data8[4] + 1;

    if(!valid_write_range(write_address, bytes_to_write)) {
        dbgprintf("Address 0x%X outside of valid write range...\r\n", write_address);
        send_nack(cmd);
        return;
    }

    send_ack(cmd);

    // Based on the protocol spec, the host will send a maximum of 256 bytes
    uint8_t buf[256];
    uint32_t received_bytes = 0;
    const uint16_t id = node_id();
    while(received_bytes < bytes_to_write) {
        CANRxFrame frame;
        if(can_receive(&frame, CAN_RECEIVE_TIMEOUT)) {
            //Failed to receive an expected frame of data to be written
            send_nack(cmd);
            return;
        }
        // AN3154 recommends 0x04 but says any SID is valid. We choose the
        // command SID to reduce unique SIDs.
        if(frame.SID != COMMAND_WRITE_MEMORY(id)) {
            // Wrong SID, protocol misalignment?
            send_nack(&frame);
            return;
        }
        if(frame.DLC + received_bytes > bytes_to_write) {
            dbgprintf("Incorrect number of bytes: have %u out of %u, given %u\r\n",
                received_bytes, bytes_to_write, frame.DLC);
            send_nack(&frame);
            return;
        }
        memcpy(buf + received_bytes, frame.data8, frame.DLC);
        received_bytes += frame.DLC;
    }

    dbgprintf("bytes_to_write = %u\r\n", bytes_to_write);
    dbgprintf("received_bytes = %u\r\n", received_bytes);

    dbgprintf("Writing data to flash...\r\n");

    // FIXME: uintptr_t is almost certainly not the right type
    int fw_r = flashWriteF091((uintptr_t) write_address, buf, bytes_to_write);

    if(fw_r == FLASH_RETURN_SUCCESS) {
        dbgprintf("Successfully wrote data to flash...\r\n");
        send_ack(cmd);
    } else {
        dbgprintf("Failed to write data to flash...\r\n");
        send_nack(cmd);
    }
}

static bool is_page_valid(const uint8_t page) {
    const uint32_t metadata_page = ((uint32_t)METADATA - 0x08000000)
        / STM32F093_FLASH_PAGE_SIZE;

    return page >= metadata_page && page <= FLASH_PAGE_COUNT;
}

static void command_erase(const CANRxFrame * const cmd) {
    if(cmd->DLC < 1) {
        send_nack(cmd);
        return;
    }

    const uint16_t page_count = cmd->data8[0] + 1;
    dbgprintf("erase page_count = %u\r\n", page_count);

    if(page_count <= 7 && cmd->DLC == page_count + 1) {
        send_ack(cmd);
    } else {
        // Mass erase not implemented. Additionally the documentation is
        // contradictory on how many pages can be erased in a single run so
        // here we only accept a single can frame (the strictest interpretation)
        // The other alternative is to accept up to 255/8 = 31 additional can
        // frames which contain more page numbers.
        send_nack(cmd);
        return;
    }

    for(size_t i = 1; i <= page_count && i < 8; i++) {
        const uint8_t page = cmd->data8[i];
        if(!is_page_valid(page) ) {
            dbgprintf("Page %u cannot be erased.\r\n", page);
            send_nack(cmd);
            return;
        }

        dbgprintf("Erasing page number = %u\r\n", page);
        if(flashPageEraseF091(page) == FLASH_RETURN_SUCCESS ) {
            dbgprintf("Successfully erased page\r\n");
            send_ack(cmd);
        } else {
            dbgprintf("Failed to erase page\r\n");
            send_nack(cmd);
            return;
        }
    }
    dbgprintf("Done with erase command\r\n");
}

static void handle_can_comms(bool * firmware_valid, const uint16_t id) {
    systime_t last_announce = chVTGetSystemTime();
    announce_presence_on_bus(id);

    const uint32_t timeout_ms = 100;
    const systime_t timeout = TIME_MS2I(timeout_ms) + chVTGetSystemTime();

    while(true) {
        const systime_t now = chVTGetSystemTime();
        if(*firmware_valid) {
            if(now >= timeout) {
                dbgprintf("No CAN frame after %u ms, resetting and running main firmware...\r\n",
                    timeout_ms);
                return;
            }
        } else {
            // Re-announce presence on the bus every 5 seconds if the firmware
            // image is specifically invalid
            if((now - last_announce) > TIME_MS2I(5000)) {
                last_announce = now;
                announce_presence_on_bus(id);
            }
        }

        CANRxFrame msg = {};
        if(can_receive(&msg, CAN_RECEIVE_TIMEOUT_LONG)) {
            continue;
        }

        dbgprintf("0: %08X 1: %08X\r\n", msg.data32[0], msg.data32[1]);
        dbgprintf("0: %08X 1: %08X\r\n", UID_LOW, CAN_ANNOUNCE_MAGIC_NUMBER);
        if(msg.SID == COMMAND_ANNOUNCE(id)
            && msg.DLC == 8
            && msg.data32[0] == UID_LOW
            && msg.data32[1] == CAN_ANNOUNCE_MAGIC_NUMBER
        ) {
            // Host will TX a reply frame with the magic number and
            // CPU unique ID values swapped to indicaet this node
            // should stay in bootloader mode
            dbgprintf("RXed frame to stay in bootloader mode...\r\n");
            break;
        }
    }

    while(true) {
        CANRxFrame msg = {};
        if(can_receive(&msg, CAN_RECEIVE_TIMEOUT_LONG)) {
            continue;
        }

        const uint16_t command_offset = msg.SID - id;
        chprintf(SERIAL, "Handling frame SID 0x%X %s\r\n",
            msg.SID, command_offset_to_str(command_offset));
        switch(command_offset) {
        case COMMAND_GET_OFFSET:
            command_get(&msg, id);
            break;
        case COMMAND_READ_MEMORY_OFFSET:
            command_read_memory(&msg);
            break;
        case COMMAND_GO_OFFSET:
            command_go(&msg);
            // because GO can't fail, we can just return
            return;
        case COMMAND_WRITE_MEMORY_OFFSET:
            *firmware_valid = false;
            command_write_memory(&msg);
            break;
        case COMMAND_ERASE_OFFSET:
            *firmware_valid = false;
            command_erase(&msg);
            break;
        }
    }
}

#define filter4(index, c1, c2, c3, c4) ((CANFilter) { \
        .filter = index,  /* Bank index */ \
        .mode = 1,        /* List mode */ \
        .scale = 0,       /* 16 bits mode */ \
        .assignment = 0,  /* Must be set to zero - see docs */ \
        .register1 = (c1) << 21 | (c2) << 5, \
        .register2 = (c3) << 21 | (c4) << 5, \
})

#define filter2(index, c1, c2) ((CANFilter) { \
        .filter = index,  /* Bank index */ \
        .mode = 1,        /* List mode */ \
        .scale = 1,       /* 32 bits mode */ \
        .assignment = 0,  /* Must be set to zero - see docs */ \
        .register1 = (c1) << 21, \
        .register2 = (c2) << 21, \
})

#define filter1(index, c1) ((CANFilter) { \
        .filter = index,  /* Bank index */ \
        .mode = 0,        /* Mask mode */ \
        .scale = 1,       /* 32 bits mode */ \
        .assignment = 0,  /* Must be set to zero - see docs */ \
        .register1 = (c1) << 21, \
        .register2 = 0x7FF << 21, \
})

static void can_bootloader_run(bool * firmware_valid) {
    const CANConfig cancfg = {
        // Tool for calculating STM32 bit timing: http://www.bittiming.can-wiki.info/
        .btr = CAN_BTR(1000),
        .mcr = CAN_MCR_ABOM //Automatic Bus-Off Management
            | CAN_MCR_AWUM  //Automatic Wakeup Mode
            | CAN_MCR_TXFP  //Transmit FIFO Priority
            | 0,            //Automatic Retransmission (no -> CAN_MCR_NART)
    };

    dbgprintf("Initializing CAN peripheral with MCR = 0x%X\r\n", cancfg.mcr);
    dbgprintf("Initializing CAN peripheral with BTR = 0x%X\r\n", cancfg.btr);

    const uint16_t id = node_id();
    chprintf(SERIAL, "Node ID: %u\r\n", id);

    const CANFilter filters[] = {
        filter4(0,
            COMMAND_ANNOUNCE(id),
            COMMAND_GET(id),
            COMMAND_READ_MEMORY(id),
            COMMAND_GO(id)
        ),
        filter2(1, COMMAND_WRITE_MEMORY(id), COMMAND_ERASE(id)),
    };
    canSTM32SetFilters(CAN_DRIVER, 0, ARRAY_LEN(filters), filters);

    canStart(CAN_DRIVER, &cancfg);
    dbgprintf("Done starting CAN peripheral\r\n");

    handle_can_comms(firmware_valid, id);

    canStop(CAN_DRIVER);
}

static bool is_metadata_valid(void) {
    if(METADATA->length == 0 || METADATA->length >= FIRMWARE_MAX_LENGTH) {
        return false;
    }
    return METADATA->crc != 0 && METADATA->crc != UINT32_MAX;
}


// The word at the very end of SRAM is not allocated or cleared by CRT of the
// bootloader OS due to linker script specifying RAM as 31k - 4 instead of
// the full 32k
#define VALIDATED_FIRMWARE (*((volatile uint32_t *) __ram0_end__))
#define BOOTLOADER_VALIDATED_FIRMWARE_MAGIC_NUMBER   0x12345678

int main(void) {
    if(VALIDATED_FIRMWARE == BOOTLOADER_VALIDATED_FIRMWARE_MAGIC_NUMBER) {
        // Previous power cycle validated the firmware, just run the firmware
        // without bootstraping the OS. We specifically want to branch to the
        // firmware image with the CPU as close to out of reset mode as possible.
        VALIDATED_FIRMWARE = 0;
        __DSB();
        // The application firmware will eventually remap its vector table to
        // SRAM in __late_init().
        __set_MSP(VECTORS->main_stack_addr);
        VECTORS->reset_handler();
    }

    // Note: none of this gets run when VALIDATED_FIRMWARE is set to the magic
    // number because branch_to_firmware_image() branches to the firmware image
    // and does not return.
    halInit();
    chSysInit();
    palSetLine(LINE_LED);

    sdStart(&SD2, NULL);
    chprintf(SERIAL, "\r\n=======================================\r\n");
    chprintf(SERIAL, "Bootloader started...\r\n");

#ifdef DEBUG_PRINT
    dbgprintf("Bootloader __flash0_base__ = 0x%08X\r\n", __flash0_base__);
    dbgprintf("Bootloader __flash0_end__ = 0x%08X\r\n", __flash0_end__);
    dbgprintf("Bootloader __flash0_size__ = 0x%08X\r\n", FLASH0_SIZE);
    dbgprintf("Bootloader metadata = 0x%08X\r\n", METADATA);
    dbgprintf("Firmware __flash2_base__ = 0x%08X\r\n", __flash2_base__);
    dbgprintf("Firmware __flash2_end__ = 0x%08X\r\n", __flash2_end__);
    dbgprintf("Firmware __flash2_size__ = 0x%08X\r\n", FLASH2_SIZE);
    dbgprintf("SRAM __ram0_base__ = 0x%08X\r\n", __ram0_base__);
    dbgprintf("SRAM __ram0_end = 0x%08X\r\n", __ram0_end__);
    dbgprintf("SRAM __ram1_base__ = 0x%08X\r\n", __ram1_base__);
    dbgprintf("SRAM __ram1_end = 0x%08X\r\n", __ram1_end__);
    dbgprintf("FLASH->OBR = 0x%08X\r\n", FLASH->OBR);
    dbgprintf("Option bytes0 = 0x%08X\r\n", *((uint32_t *)0x1ffff800));
    dbgprintf("Option bytes1 = 0x%08X\r\n", *((uint32_t *)0x1ffff804));

    extern stkalign_t __main_thread_stack_base__;
    extern stkalign_t __main_thread_stack_end__;
    dbgprintf("Stack size: %u\r\n", ((uint8_t *) &__main_thread_stack_end__)
        - ((uint8_t *) &__main_thread_stack_base__));

    dbgprintf("Checking firmware validity...\r\n");
#endif

    const bool metadata_valid = is_metadata_valid();
    uint32_t crc = -1;
    if(metadata_valid) {
        // FIXME: verify that this is using the HW crc implementation
        crc = crc32(FIRMWARE_CRC_START, METADATA->length, 0);
    }
    bool firmware_valid = metadata_valid && crc == METADATA->crc;

    dbgprintf("firmware expected crc = 0x%X\r\n", METADATA->crc);
    dbgprintf("firmware expected length = %u\r\n", METADATA->length);
    dbgprintf("firmware version = %u\r\n", METADATA->version);
    chprintf(SERIAL, "firmware metadata_valid = %u\r\n", metadata_valid);
    chprintf(SERIAL, "firmware actual CRC = 0x%X\r\n", crc);
    chprintf(SERIAL, "Current firmware_valid = %u\r\n", firmware_valid);

    // bootloader commands could invalidate the firmware
    can_bootloader_run(&firmware_valid);

    if(firmware_valid) {
        VALIDATED_FIRMWARE = BOOTLOADER_VALIDATED_FIRMWARE_MAGIC_NUMBER;
    } else {
        VALIDATED_FIRMWARE = 0;
    }

    dbgprintf("set VALIDATED_FIRMWARE = 0x%X\r\n", VALIDATED_FIRMWARE);
    dbgprintf("reseting MCU\r\n");

    soft_reset_cortex_m0();

    return 0;
}
