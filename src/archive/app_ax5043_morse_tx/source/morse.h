
#ifndef _MORSE_H_
#define _MORSE_H_

#define DEBUG_SERIAL  SD2
#define DEBUG_CHP     ((BaseSequentialStream *) &DEBUG_SERIAL)

#define SPACE " "


#define LETTER_SPACE_MS (ditLength*3)
#define WORD_SPACE_MS (ditLength*7)
#define DIT_MS (ditLength)
#define DASH_MS (ditLength*3)



void SendDot(SPIDriver * spip);
void SendDash(SPIDriver * spip);
void LetterSleep(void);
void WordSleep(void);
void ElementSleep(void);
void SetWpm(int wpm);
void SetMessage(char *message);
void SendMessage(SPIDriver * spip);

#endif
