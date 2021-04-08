#ifndef APP_FOC_H
#define APP_FOC_H

// ChibiOS headers
#include "ch.h"
#include "hal.h"
#include "chprintf.h"

// C++ headers
#include <cstdlib>
#include <algorithm>
#include <stdio.h>
#include <string.h>

// SimpleFOC headers
#include "BLDCMotor.h"
#include "MagneticSensorSPI.h"
#include "drivers/BLDCDriver6PWM.h"
//#include "current_sense/InlineCurrentSense.h"
//#include "communication/Commander.h"
//#include "communication/StepDirListener.h"

/* This pointer to a sequential stream actually points to our serial driver.
   To use the serial driver in chprintf we need to cast it and we are using
   this variable to perform a cast only once. 
   from https://www.playembedded.org/blog/vcp-stm32-chibios/ */
static BaseSequentialStream* chp = (BaseSequentialStream*) &LPSD1;

#endif
