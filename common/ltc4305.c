#include "hal.h"
#include "ltc4305.h"


bool ltc4305_set_connections(I2CDriver *i2cp, const uint8_t i2c_addr, const bool enable_i2c_bus_1, const bool enable_i2c_bus_2) {


	uint8_t tx[2];
	tx[0] = 0x03;

	uint8_t reg_3_value = 0;
	if( enable_i2c_bus_1 ) {
		reg_3_value |= (1<<7);
	}

	if( enable_i2c_bus_2 ) {
		reg_3_value |= (1<<6);
	}

	tx[1] = reg_3_value;

    if( i2cMasterTransmitTimeout(i2cp, i2c_addr, tx, 2, NULL, 0, 50) == MSG_OK ) {
    	return(true);
    }
    return(false);

}
