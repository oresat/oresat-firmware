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


#define MAX_MESSAGE_SIZE 512
char beaconMessage[MAX_MESSAGE_SIZE];
uint16_t ditLength;

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

void SendDot(SPIDriver * spip)
{

  uint8_t ret_value[3]={0,0,0};

  ax5043_full_tx(spip);
  chprintf(DEBUG_CHP, "Dot\r\n");
  ax5043_write_reg(&SPID2, AX5043_REG_FIFODATA, (uint8_t)(AX5043_REPEATDATA_CMD|0x00), ret_value);
  ax5043_write_reg(&SPID2, AX5043_REG_FIFODATA, (uint8_t)0x38, ret_value);//preamble flag
  ax5043_write_reg(&SPID2, AX5043_REG_FIFODATA, (uint8_t)0xFF, ret_value);
  ax5043_write_reg(&SPID2, AX5043_REG_FIFODATA, (uint8_t)0xF0, ret_value);//preamble
  ax5043_write_reg(&SPID2, AX5043_REG_FIFOSTAT, (uint8_t)0x04, ret_value);//FIFO Commit 
  chThdSleepMilliseconds(DIT_MS);
  ax5043_standby(spip);

}

void SendDash(SPIDriver * spip)
{

  uint8_t ret_value[3]={0,0,0};

  ax5043_full_tx(spip);
  chprintf(DEBUG_CHP, "Dash\r\n");
  ax5043_write_reg(&SPID2, AX5043_REG_FIFODATA, (uint8_t)(AX5043_REPEATDATA_CMD|0x00), ret_value);
  ax5043_write_reg(&SPID2, AX5043_REG_FIFODATA, (uint8_t)0x38, ret_value);//preamble flag
  ax5043_write_reg(&SPID2, AX5043_REG_FIFODATA, (uint8_t)0xFF, ret_value);
  ax5043_write_reg(&SPID2, AX5043_REG_FIFODATA, (uint8_t)0xF0, ret_value);//preamble
  ax5043_write_reg(&SPID2, AX5043_REG_FIFOSTAT, (uint8_t)0x04, ret_value);//FIFO Commit 
  chThdSleepMilliseconds(DASH_MS);
  ax5043_standby(spip);
}

void LetterSleep(void)
{
    chThdSleepMilliseconds(LETTER_SPACE_MS);
}

void WordSleep(void)
{
    chThdSleepMilliseconds(WORD_SPACE_MS);
}

void ElementSleep(void)
{
    chThdSleepMilliseconds(DIT_MS);
}

//sets ditLength in ms
void SetWpm(int wpm)
{
    ditLength = 1200/wpm;
}

void SetMessage(char *message)
{
    memset(beaconMessage, 0, MAX_MESSAGE_SIZE);
    int len = strlen(message);
    if (strlen(message) >= MAX_MESSAGE_SIZE)
        len = MAX_MESSAGE_SIZE-1;
    memcpy(beaconMessage, message, len);
}

const char *AsciiToMorse(char letter)
{
    letter = tolower(letter);

    if (isalpha(letter))
    {
        return alpha[letter-'a'];
    }
    else if (isdigit(letter))
    {
        return num[letter-'0'];
    }

    return SPACE;
}

void SendMessage(SPIDriver * spip)
{
    int element;
    int index = 0;
    const char *morse;
    while (beaconMessage[index] != '\0')
    {
        morse = AsciiToMorse(beaconMessage[index]);

        element = 0;
        while (morse[element] != '\0')
        {
            switch(morse[element])
            {
            case '-':
                SendDash(spip);
                break;
            case '.':
                SendDot(spip);
            }

            if (morse[element] == ' ')
            {
                WordSleep();
            }
            else if (morse[element+1] != '\0')
            {
                ElementSleep();
            }
            else if (morse[element+1] == '\0')
            {
                LetterSleep();
            }
            element++;
        }

        index++;
    }
}

