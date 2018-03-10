#include "oresat.h"

void oresat_init(void) {
    //Initialize CAN Subsystem
    can_init(0x01, 500);
    //Start CAN Subsystem
    can_start();

    return;
}
