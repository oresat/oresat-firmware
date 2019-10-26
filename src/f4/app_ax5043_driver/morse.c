/*
The code here refers to logic and snippets from Adam Parker - KD5OOL
*/

#include <string.h>
#include <ctype.h>


#include "ch.h"
#include "hal.h"
#include "chprintf.h"

#include "morse.h"
#include "ax5043.h"



static const char *alpha[] = {
    ".-",   //A
    "-...", //B
    "-.-.", //C
    "-..",  //D
    ".",    //E
    "..-.", //F
    "--.",  //G
    "....", //H
    "..",   //I
    ".---", //J
    "-.-",  //K
    ".-..", //L
    "--",   //M
    "-.",   //N
    "---",  //O
    ".--.", //P
    "--.-", //Q
    ".-.",  //R
    "...",  //S
    "-",    //T
    "..-",  //U
    "...-", //V
    ".--",  //W
    "-..-", //X
    "-.--", //Y
    "--..", //Z
};

static const char *num[] = {
    "-----", //0
    ".----", //1
    "..---", //2
    "...--", //3
    "....-", //4
    ".....", //5
    "-....", //6
    "--...", //7
    "---..", //8
    "----.", //9
};




void ax5043_morse_dot_dash(AX5043Driver *devp, uint16_t dot_dash_time){

  uint8_t ret_value[3]={0,0,0};
  SPIDriver *spip = devp->config->spip;

  ax5043_set_pwrmode(devp, AX5043_FULL_TX);
  ax5043_write_reg(spip, AX5043_REG_FIFODATA, (uint8_t)(AX5043_FIFOCMD_REPEATDATA|0x60), ret_value);
  ax5043_write_reg(spip, AX5043_REG_FIFODATA, (uint8_t)0x38, ret_value);//preamble flag
  ax5043_write_reg(spip, AX5043_REG_FIFODATA, (uint8_t)0xFF, ret_value);
  ax5043_write_reg(spip, AX5043_REG_FIFODATA, (uint8_t)0x00, ret_value);//preamble
  ax5043_write_reg(spip, AX5043_REG_FIFOSTAT, (uint8_t)0x04, ret_value);//FIFO Commit 
  chThdSleepMilliseconds(dot_dash_time);
  ax5043_set_pwrmode(devp, AX5043_STANDBY);

}


const char *ax5043_ascii_to_morse(char letter){
  letter = tolower(letter);

  if (isalpha(letter)){
    return alpha[letter-'a'];
  }
  else if (isdigit(letter)){
    return num[letter-'0'];
  }

  return SPACE;
}


void ax5043_send_cw(AX5043Driver *devp, int wpm, char beaconMessage[], uint16_t pktlen ){
  int element;
  int index = 0;
  const char *morse;
    
  uint16_t ditLength = 1200/wpm;
  uint16_t letter_space = ditLength*3;
  uint16_t word_space = ditLength*7;
  uint16_t element_space = ditLength;
  uint16_t dash = ditLength*3;
    
  while (index < pktlen){
    morse = ax5043_ascii_to_morse(beaconMessage[index]);

    element = 0;
    while (morse[element] != '\0'){
      switch(morse[element]){
      case '-':
        ax5043_morse_dot_dash(devp, dash);
        break;
      case '.':
        ax5043_morse_dot_dash(devp, ditLength);
        break;
      }

      if (morse[element] == ' '){
        chThdSleepMilliseconds(word_space);
      }
      else if (morse[element+1] != '\0'){
        chThdSleepMilliseconds(element_space);
      }
      else if (morse[element+1] == '\0'){
        chThdSleepMilliseconds(letter_space);
      }
      element++;
    }

    index++;
  }
}

