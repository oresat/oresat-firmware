#ifndef MAGNETICSENSORSPI_LIB_H
#define MAGNETICSENSORSPI_LIB_H

#include <cstdlib>
#include <stdio.h>
#include <string.h>

#include "ch.h"
#include "hal.h"
#include "chprintf.h"


//#include "Arduino.h"
//#include <SPI.h>
#include "common/base_classes/Sensor.h"
#include "common/foc_utils.h"
//#include "common/time_utils.h"

#define DEF_ANGLE_REGISTER 0x3FFF


// Copied from Arduino libraries
#define SPI_MODE1 0x01
typedef unsigned int word;
typedef uint8_t byte;


/* Example blinker thread prototypes */
extern THD_WORKING_AREA(sensor_wa, 0x256);  // 256 is arbitrary
extern THD_FUNCTION(sensor, arg);

/**
 * @brief Control structure used to configure the SPI driver
 * 
 * from ACS project
 *
 * GPIOA_SPI1_NSS is the pin used to initially select the SPI slave.
 * The mask for SPI Control Register 1 sets the frequency of data transfers
 * and sets the clock polarity.
 * The mask for SPI control Register 2 sets the size of the transfer buffer, 16 bits.
 *
 */
static const SPIConfig spicfg = {
	false,                                                  // Not using circular buffer.
	NULL,                                                   // Not using operation complete callback.
	GPIOA,                                                  // Chip select line.
	//GPIOB_SPI2_NSS,                                       // Chip select port.
  GPIOA_PIN8,
	SPI_CR1_BR_0|SPI_CR1_BR_1|SPI_CR1_BR_2|SPI_CR1_CPHA,    // SPI Control Register 1 mask.
  //SPI_CR1_BR_0|SPI_CR1_BR_1|SPI_CR1_CPHA,
                                                          // BR[2:0] = 111: Baud rate is fPCLK/256
                                                          // CPHA = 1: Clock Phase is: second clock
                                                          // transition is the first data capture edge
	SPI_CR2_DS_0|SPI_CR2_DS_1|SPI_CR2_DS_2|SPI_CR2_DS_3,    // SPI Control Register 2 mask.
                                                          // DS[3:0] = 1111: data size 16 bits
};

struct MagneticSensorSPIConfig_s  {
  int spi_mode;
  long clock_speed;
  int bit_resolution;
  int angle_register;
  int data_start_bit;
  int command_rw_bit;
  int command_parity_bit;
};
// typical configuration structures
extern MagneticSensorSPIConfig_s AS5147_SPI;

class MagneticSensorSPI: public Sensor{
 public:
    /**
     *  MagneticSensorSPI class constructor
     * @param config   SPI config
     * @param cs  SPI chip select pin
     */
    MagneticSensorSPI(MagneticSensorSPIConfig_s config, int cs);

    /** sensor initialise pins */
    void init( /* SPIClass* _spi = &SPI */ ); //ARDUINO

    // implementation of abstract functions of the Sensor class
    /** get current angle (rad) */
    float getAngle() override;
    /** get current angular velocity (rad/s) **/
    float getVelocity() override;

    // returns the spi mode (phase/polarity of read/writes) i.e one of SPI_MODE0 | SPI_MODE1 | SPI_MODE2 | SPI_MODE3
    int spi_mode;
    
    /* returns the speed of the SPI clock signal */
    long clock_speed;
    

  private:
    float cpr; //!< Maximum range of the magnetic sensor
    // spi variables
    int angle_register; //!< SPI angle register to read
    int chip_select_pin; //!< SPI chip select pin
	  //SPISettings settings; //!< SPI settings variable  //ARDUINO
    // spi functions
    /** Stop SPI communication */
    void close(); 
    /** Read one SPI register value */
    word read( /* word angle_register */ );
    /** Calculate parity value  */
    byte spiCalcEvenParity(word value);

    /**
     * Function getting current angle register value
     * it uses angle_register variable
     */
    int getRawCount();

    // total angle tracking variables
    float full_rotation_offset; //!<number of full rotations made
    float angle_data_prev; //!< angle in previous position calculation step

    // velocity calculation variables
    float angle_prev; //!< angle in previous velocity calculation step
    long velocity_calc_timestamp; //!< last velocity calculation timestamp
    
    int bit_resolution; //!< the number of bites of angle data
    int command_parity_bit; //!< the bit where parity flag is stored in command
    int command_rw_bit; //!< the bit where read/write flag is stored in command
    int data_start_bit; //!< the the position of first bit

    //from ACS project
    uint16_t spi_rxbuf[2];  //receive buffer
    word register_value;  // (word)spi_rxbuf;

    word data_mask;  //0xFFFF >> (16 - bit_resolution);





    //SPIClass* spi;  //ARDUINO
};


#endif
