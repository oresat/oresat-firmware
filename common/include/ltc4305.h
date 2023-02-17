#ifndef COMMON_INCLUDE_LTC4305_H_
#define COMMON_INCLUDE_LTC4305_H_

#define LTC_4035_MINUSZ_CARD_I2C_ADDRESS_WRITE   (0xA8 >> 1)
#define LTC_4035_PLUSZ_CARD_I2C_ADDRESS_WRITE    (0x88 >> 1)

bool ltc4305_set_connections(I2CDriver *i2cp, const uint8_t i2c_addr, const bool enable_i2c_bus_1, const bool enable_i2c_bus_2);


#endif /* COMMON_INCLUDE_LTC4305_H_ */
