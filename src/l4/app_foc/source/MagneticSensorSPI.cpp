#include "MagneticSensorSPI.h"

/** Typical configuration for the 14bit AMS AS5147 magnetic sensor over SPI interface */
MagneticSensorSPIConfig_s AS5147_SPI = {
  .spi_mode = SPI_MODE1,
  .clock_speed = 1000000,
  .bit_resolution = 14,
  .angle_register = 0x3FFF,
  .data_start_bit = 13, 
  .command_rw_bit = 14,
  .command_parity_bit = 15
};

MagneticSensorSPI::MagneticSensorSPI(MagneticSensorSPIConfig_s config, int cs){
  chip_select_pin = cs; 
  // angle read register of the magnetic sensor
  angle_register = config.angle_register ? config.angle_register : DEF_ANGLE_REGISTER;
  // register maximum value (counts per revolution)
  //cpr = pow(2, config.bit_resolution);
  cpr = 1 << config.bit_resolution;

  spi_mode = config.spi_mode;
  clock_speed = config.clock_speed;
  bit_resolution = config.bit_resolution;
  
  command_parity_bit = config.command_parity_bit; // for backwards compatibilty
  command_rw_bit = config.command_rw_bit; // for backwards compatibilty
  data_start_bit = config.data_start_bit; // for backwards compatibilty

}



/* Based on example blinker thread */
THD_WORKING_AREA(sensor_wa, 0x256); // 256 is arbitrary
THD_FUNCTION(sensor, arg)
{
  (void)arg;

  // debug
  palSetLineMode(LINE_LED,PAL_MODE_OUTPUT_PUSHPULL);
  palSetLine(LINE_LED);

  // not sure if this is the appropriate place to put this
  MagneticSensorSPI sensor = MagneticSensorSPI(AS5147_SPI, 10);
  sensor.init();

  while (!chThdShouldTerminateX()) {
    //motor->spi_rxbuf[0] = 0;
    spi_rxbuf[0] = 0;
    spiSelect(&SPID2);                  // Select slave.

    while(SPID2.state != SPI_READY) {}
    //spiReceive(&SPID1,1,motor->spi_rxbuf); // Receive 1 frame (16 bits).
    spiReceive(&SPID2,1,spi_rxbuf); // Receive 1 frame (16 bits).
    spiUnselect(&SPID2);                // Unselect slave.

    // debug
    palToggleLine(LINE_LED);
    chThdSleepMilliseconds(500);
  }

  palClearLine(LINE_LED);
  chThdExit(MSG_OK);
}



void MagneticSensorSPI::init( /* SPIClass* _spi */ ){

    //spi = _spi;

    //ChibiOS
    spiStart(&SPID2,&spicfg);           // Start driver.
    spiAcquireBus(&SPID2);              // Gain ownership of bus.

    /************
	// 1MHz clock (AMS should be able to accept up to 10MHz)
	settings = SPISettings(clock_speed, MSBFIRST, spi_mode);

	//setup pins
	pinMode(chip_select_pin, OUTPUT); //ARDUINO
  
	//SPI has an internal SPI-device counter, it is possible to call "begin()" from different devices
	spi->begin();
#ifndef ESP_H // if not ESP32 board
	spi->setBitOrder(MSBFIRST); // Set the SPI_1 bit order
	spi->setDataMode(spi_mode) ;
	spi->setClockDivider(SPI_CLOCK_DIV8);
#endif

	digitalWrite(chip_select_pin, HIGH);
    //*/

	// velocity calculation init
	angle_prev = 0;
	//velocity_calc_timestamp = micros(); //ARDUINO
    velocity_calc_timestamp = time_usecs_t(); //CHIBIOS_MAYBE


	// full rotations tracking number
	full_rotation_offset = 0;
	angle_data_prev = getRawCount();  
}

//  Shaft angle calculation
//  angle is in radians [rad]
float MagneticSensorSPI::getAngle(){
  // raw data from the sensor
  float angle_data = getRawCount(); 

  // tracking the number of rotations 
  // in order to expand angle range form [0,2PI] 
  // to basically infinity
  float d_angle = angle_data - angle_data_prev;
  // if overflow happened track it as full rotation
  if(abs(d_angle) > (0.8*cpr) ) full_rotation_offset += d_angle > 0 ? -_2PI : _2PI; 
  // save the current angle value for the next steps
  // in order to know if overflow happened
  angle_data_prev = angle_data;

  // return the full angle 
  // (number of full rotations)*2PI + current sensor angle 
  return full_rotation_offset + ( angle_data / (float)cpr) * _2PI;
}

// Shaft velocity calculation
float MagneticSensorSPI::getVelocity(){
  // calculate sample time
  //unsigned long now_us = micros();
  unsigned long now_us = time_usecs_t(); //CHIBIOS_MAYBE
  float Ts = (now_us - velocity_calc_timestamp)*1e-6;
  // quick fix for strange cases (micros overflow)
  if(Ts <= 0 || Ts > 0.5) Ts = 1e-3; 

  // current angle
  float angle_c = getAngle();
  // velocity calculation
  float vel = (angle_c - angle_prev)/Ts;

  // save variables for future pass
  angle_prev = angle_c;
  velocity_calc_timestamp = now_us;
  return vel;
}


// function reading the raw counter of the magnetic sensor
int MagneticSensorSPI::getRawCount(){
	return (int)MagneticSensorSPI::read(angle_register);
}

// SPI functions 
/**
 * Utility function used to calculate even parity of word
 */
byte MagneticSensorSPI::spiCalcEvenParity(word value){
	byte cnt = 0;
	byte i;

	for (i = 0; i < 16; i++)
	{
		if (value & 0x1) cnt++;
		value >>= 1;
	}
	return cnt & 0x1;
}

  /*
  * Read a register from the sensor
  * Takes the address of the register as a 16 bit word
  * Returns the value of the register
  */
word MagneticSensorSPI::read(word angle_register){

  /**********
  word command = angle_register;

  if (command_rw_bit > 0) {
    command = angle_register | (1 << command_rw_bit);
  }
  if (command_parity_bit > 0) {
   	//Add a parity bit on the the MSB
  	command |= ((word)spiCalcEvenParity(command) << command_parity_bit);
  }

  //Send the command
  digitalWrite(chip_select_pin, LOW);
  digitalWrite(chip_select_pin, LOW);
  spi->transfer16(command);
  digitalWrite(chip_select_pin,HIGH);
  digitalWrite(chip_select_pin,HIGH);
  
  delayMicroseconds(10);
  

  //Now read the response
  digitalWrite(chip_select_pin, LOW); //ARDUINO
  digitalWrite(chip_select_pin, LOW);
  word register_value = spi->transfer16(0x00);
  digitalWrite(chip_select_pin, HIGH);
  digitalWrite(chip_select_pin,HIGH);
  //*/

  word register_value;

  //from ACS project
  spiSelect(&SPID2);                       // Select SPI device.
  while(SPID2.state != SPI_READY) {}
  //spiReceive(&SPID2,1,register_value);     // Receive 1 frame (16 bits).
  spiReceive(&SPID2,1,spi_rxbuf);     // Receive 1 frame (16 bits).
  spiUnselect(&SPID2);                     // Unselect SPI device.

  //memcpy(dest, src, length in bytes);
  //memcpy(&register_value, spi_rxbuf, 2);

  
  register_value = (word)spi_rxbuf >> (1 + data_start_bit - bit_resolution);  //this should shift data to the rightmost bits of the word

  const static word data_mask = 0xFFFF >> (16 - bit_resolution);

  return register_value & data_mask;  // Return the data, stripping the non data (e.g parity) bits
}

/**
 * Closes the SPI connection
 * SPI has an internal SPI-device counter, for each init()-call the close() function must be called exactly 1 time
 */
void MagneticSensorSPI::close(){
	//spi->end();  //ARDUINO
}
