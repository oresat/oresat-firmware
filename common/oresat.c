#include "oresat.h"

void oresat_init(uint8_t node_id) {
    if (node_id == 0) {
        //TODO: Check if the user data bytes are set and set Node ID from that if so
        node_id == 0x7F;
    }
    //Initialize CAN Subsystem
    can_init(node_id, 500);
    //Start CAN Subsystem
    can_start();

    return;
}
