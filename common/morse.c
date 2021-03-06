#include "morse.h"
#include "ax5043.h"

/**
 * @brief   Morse code for alphabets and numbers.
 */
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

/**
 * @brief   Prepare for CW mode
 *
 * @param[in]  devp               pointer to the @p AX5043Driver object.
 *
 * @api
 */
uint8_t ax5043_prepare_cw(AX5043Driver *devp){
    ax5043WriteU24(devp, AX5043_REG_FSKDEV, 0x000000U);
    ax5043WriteU24(devp, AX5043_REG_TXRATE, 0x000001U);

    ax5043SetPWRMode(devp, AX5043_PWRMODE_TX_FULL);

    /* This is not mentioned in datasheet or programming manual but is required.
     * Removing this will make the transmission to transmit in low power for a few seconds
     * before it reaches peak power */
    /* FIFO reset */
    ax5043WriteU8(devp, AX5043_REG_FIFOSTAT, AX5043_FIFOCMD_CLEAR_FIFODAT);
    ax5043WriteU8(devp, AX5043_REG_FIFODATA, (AX5043_CHUNKCMD_REPEATDATA | _VAL2FLD(AX5043_FIFOCHUNK_SIZE, 3)));
    /* Preamble flag */
    ax5043WriteU8(devp, AX5043_REG_FIFODATA, AX5043_CHUNK_DATATX_UNENC | AX5043_CHUNK_DATATX_NOCRC);
    ax5043WriteU8(devp, AX5043_REG_FIFODATA, 0xFF);
    /* Preamble */
    ax5043WriteU8(devp, AX5043_REG_FIFODATA, 0x55);
    /* FIFO Commit */
    ax5043WriteU8(devp, AX5043_REG_FIFOSTAT, 0x04);

    ax5043SetPWRMode(devp, AX5043_PWRMODE_STANDBY);
    devp->state = AX5043_CW;
    return 0;
}

/**
 * @brief   Send Morse dot and dash over the air
 *
 * @param[in]  devp               pointer to the @p AX5043Driver object.
 * @param[in]  dot_dash_time      time in milliseconds for transmiter to be on.
 */
void ax5043_morse_dot_dash(AX5043Driver *devp, uint16_t dot_dash_time){
    ax5043SetPWRMode(devp, AX5043_PWRMODE_TX_FULL);
    ax5043WriteU8(devp, AX5043_REG_FIFODATA, (AX5043_CHUNKCMD_REPEATDATA | _VAL2FLD(AX5043_FIFOCHUNK_SIZE, 3)));
    /* Preamble flag */
    ax5043WriteU8(devp, AX5043_REG_FIFODATA, AX5043_CHUNK_DATATX_UNENC | AX5043_CHUNK_DATATX_NOCRC);
    ax5043WriteU8(devp, AX5043_REG_FIFODATA, 0xFF);
    /* Preamble */
    ax5043WriteU8(devp, AX5043_REG_FIFODATA, 0x00);
    /* FIFO Commit */
    ax5043WriteU8(devp, AX5043_REG_FIFOSTAT, 0x04);
    chThdSleepMilliseconds(dot_dash_time);
    ax5043SetPWRMode(devp, AX5043_PWRMODE_STANDBY);

}

/**
 * @brief   Convert an alphabet or number to morse dot and dash
 *
 * @param[in]  letter             An alphabet or number.
 *
 * @return                        Length of packet received.
 */
const char *ax5043_ascii_to_morse(char letter){
    letter = tolower(letter);

    if (isalpha(letter)){
        return alpha[letter-'a'];
    }
    else if (isdigit(letter)){
        return num[letter-'0'];
    }

    return " ";
}

/**
 * @brief   Convert a message to morse code and transmit it.
 *
 * @param[in]  devp               pointer to the @p AX5043Driver object.
 * @param[in]  wpm                words per minute.
 * @param[in]  beaconMessage      Message to be transmitted.
 * @param[in]  pktlen             Length of packet/beacon message.
 */
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
