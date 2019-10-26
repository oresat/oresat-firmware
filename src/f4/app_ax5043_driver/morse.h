
#ifndef _MORSE_H_
#define _MORSE_H_

#define DEBUG_SERIAL  SD2
#define DEBUG_CHP     ((BaseSequentialStream *) &DEBUG_SERIAL)

#define SPACE " "



#include "ax5043.h"

void ax5043_morse_dot_dash(AX5043Driver *devp, uint16_t dot_dash_time);
const char *ax5043_ascii_to_morse(char letter);
void ax5043_send_cw(AX5043Driver *devp, int wpm, char beaconMessage[], uint16_t pktlen );

#endif
