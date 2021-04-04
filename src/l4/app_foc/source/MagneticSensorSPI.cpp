#include "MagneticSensorSPI.h"

/* This pointer to a sequential stream actually points to our serial driver.
   To use the serial driver in chprintf we need to cast it and we are using
   this variable to perform a cast only once. 
   from https://www.playembedded.org/blog/vcp-stm32-chibios/ */
static BaseSequentialStream* chp = (BaseSequentialStream*) &LPSD1;


/** Typical configuration for the 14bit AMS AS5147 magnetic sensor over SPI interface */
MagneticSensorSPIConfig_s AS5147_SPI = {
  .spi_mode = SPI_MODE1,        // unused?
  .clock_speed = 1000000,       // unused?
  .bit_resolution = 14,         // used for cpr, data_mask, register_value
  .angle_register = 0x3FFF,     // unused (Instead, tie MOSI to +3.3V)
  .data_start_bit = 13,         // used for register_value
  .command_rw_bit = 14,         // unused?
  .command_parity_bit = 15      // unused?
};

MagneticSensorSPI::MagneticSensorSPI(MagneticSensorSPIConfig_s config, int cs){
  chip_select_pin = cs; 
  // angle read register of the magnetic sensor
  //angle_register = config.angle_register ? config.angle_register : DEF_ANGLE_REGISTER;
  // register maximum value (counts per revolution)
  //cpr = pow(2, config.bit_resolution);
  cpr = 1 << config.bit_resolution;

  //spi_mode = config.spi_mode;
  //clock_speed = config.clock_speed;
  bit_resolution = config.bit_resolution;
  
  //command_parity_bit = config.command_parity_bit; // for backwards compatibilty
  //command_rw_bit = config.command_rw_bit; // for backwards compatibilty
  data_start_bit = config.data_start_bit; // for backwards compatibilty

  data_mask = 0xFFFF >> (16 - bit_resolution);
}



/* Based on example blinker thread */
THD_WORKING_AREA(sensor_wa, 0x256); // 256 is arbitrary
THD_FUNCTION(sensor, arg)
{
  (void)arg;

  // debug
  palSetLineMode(LINE_LED,PAL_MODE_OUTPUT_PUSHPULL);
  palSetLine(LINE_LED);

  chprintf(chp, "made it into THD_FUNCTION\n\r");
  chThdSleepMilliseconds(500);
  // not sure if this is the appropriate place to put this
  MagneticSensorSPI sensor = MagneticSensorSPI(AS5147_SPI, 10);
  sensor.init();

  while (!chThdShouldTerminateX()) {

      chprintf(chp, "Angle: %f\n\r", sensor.getAngle() );
      chprintf(chp, "Velocity: %f\n\r", sensor.getVelocity() );

    // debug
    palToggleLine(LINE_LED);
    chThdSleepMilliseconds(500);
  }

  // does close get called automatically in some way?
  //sensor.close();

  palClearLine(LINE_LED);
  chThdExit(MSG_OK);
}



void MagneticSensorSPI::init( /* SPIClass* _spi */ ){

  //spi = _spi;

  chprintf(chp, "made it into sensor.init()\n\r");
  chThdSleepMilliseconds(500);

  /*
   * SPI2 I/O pins setup.
   */

  /*
  palSetLineMode(GPIOB_PIN12,
                 PAL_MODE_ALTERNATE(5) |
                 PAL_STM32_OSPEED_HIGH);         // NSS.                
  palSetLineMode(GPIOB_SPI2_SCK,
                 PAL_MODE_ALTERNATE(5) |
                 PAL_STM32_OSPEED_HIGH);         // SPI SCK.            
  palSetLineMode(GPIOB_SPI2_MISO,
                 PAL_MODE_ALTERNATE(5) |
                 PAL_STM32_OSPEED_HIGH);         // MISO.
  //*/           

  palSetPadMode(GPIOB, GPIOB_SPI2_SCK,
              PAL_MODE_ALTERNATE(5) | PAL_STM32_OSPEED_HIGH);    /* New SCK */
  palSetPadMode(GPIOB, GPIOB_SPI2_MISO,
              PAL_MODE_ALTERNATE(5) | PAL_STM32_OSPEED_HIGH);    /* New MISO*/
  palSetPadMode(GPIOB, GPIOB_PIN12,
              PAL_MODE_OUTPUT_PUSHPULL | PAL_STM32_OSPEED_HIGH); /* New CS*/


  //ChibiOS
  spiStart(&SPID2,&spicfg);           // Start driver.
  spiAcquireBus(&SPID2);              // Gain ownership of bus.

  chprintf(chp, "made it past spiStart() and spiAcquireBus\n\r");
  chThdSleepMilliseconds(500);

	// 1MHz clock (AMS should be able to accept up to 10MHz)
	//spi->setClockDivider(SPI_CLOCK_DIV8);

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
  // in order to expand angle range from [0,2PI] 
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
	return (int)MagneticSensorSPI::read( /* angle_register */ );
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
word MagneticSensorSPI::read( /* word angle_register */ ){

  chprintf(chp, "made it into sensor.read()\n\r");
  chThdSleepMilliseconds(500);

  //from ACS project
  spiSelect(&SPID2);                  // Select SPI device.
  while(SPID2.state != SPI_READY) {}

  chprintf(chp, "made it past while(SPID2.state != SPI_READY)\n\r");
  chThdSleepMilliseconds(500);

  spiReceive(&SPID2,1,spi_rxbuf);     // Receive 1 frame (16 bits).

  chprintf(chp, "made it past spiReceieve (SPID2.state != SPI_READY)\n\r");
  chThdSleepMilliseconds(500);

  spiUnselect(&SPID2);                // Unselect SPI device.
  
  //this should shift data to the rightmost bits of the word
  register_value = (word)spi_rxbuf >> (1 + data_start_bit - bit_resolution);  

  return register_value & data_mask;  // Return the data, stripping the non data (e.g parity) bits
}

/**
 * Closes the SPI connection
 */
void MagneticSensorSPI::close(){
	//spi->end();  //ARDUINO

  spiReleaseBus(&SPID2);              // Release ownership of bus.

}
