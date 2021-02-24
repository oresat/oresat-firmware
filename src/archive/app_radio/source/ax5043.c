/**
 * @file    ax5043.c
 * @brief   AX5043 Radio.
 *
 * @addtogroup AX5043
 * @ingrup ORESAT
 * @{
 */

#include <string.h>
#include "ch.h"
#include "hal.h"
#include "ax5043.h"

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/
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

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

#if (AX5043_USE_SPI) || defined(__DOXYGEN__)
/**
 * @brief   Reads AX5043 registers using SPI.
 * @pre     The SPI interface must be initialized and the driver started.
 *
 * @param[in]   spip        SPI Configuration
 * @param[in]   reg         Register address
 * @param[in]   value       Register value
 * @param[out]  rxbuf       Returned data
 * @return                  The value in the register
 * @notapi
 */
uint8_t ax5043SPIReadRegister(SPIDriver *spip, uint16_t reg, uint8_t value, uint8_t rxbuf[]) {
    uint8_t cmd[3];

    /* TODO: Optimize these functions */
    if (reg <  0x0070) {
        cmd[0] = reg;
        cmd[1] = value;
        spiSelect(spip);
        spiExchange(spip, 2, cmd, rxbuf);
        spiUnselect(spip);
        return rxbuf[1];    //return the reg value when reading the register
    } else {
        cmd[0] = 0x70 | (reg >> 8);
        cmd[1] = reg;
        cmd[2] = value;
        spiSelect(spip);
        spiExchange(spip, 3, cmd, rxbuf);
        spiUnselect(spip);
        return rxbuf[2];    //return the reg value when reading the register
    }
}

/**
 * @brief   Writes a value into a register using SPI.
 * @pre     The SPI interface must be initialized and the driver started.
 *
 * @param       spip        SPI Driver
 * @param[in]   reg         Register address
 * @param[in]   value       Register value
 * @param[out]  rxbuf       Returned data
 * @return                  The value in the register
 * @notapi
 */
uint8_t ax5043SPIWriteRegister(SPIDriver *spip, uint16_t reg, uint8_t value, uint8_t rxbuf[]) {
    uint8_t cmd[3];

    /* TODO: Optimize these functions */
    if (reg <  0x0070) {
        cmd[0]=0x80|reg;
        cmd[1]=value;
        spiSelect(spip);
        spiExchange(spip, 2, cmd, rxbuf);
        spiUnselect(spip);
    } else {
        cmd[0]=0xF0|(reg>>8);
        cmd[1]=reg;
        cmd[2]=value;
        spiSelect(spip);
        spiExchange(spip, 3, cmd, rxbuf);
        spiUnselect(spip);
    }
    return rxbuf[0];   //retun status while writting the register
}

/*===========================================================================*/
/* TODO: Organize these functions and clean up comments                      */
/*===========================================================================*/

/**
 * @brief   Sets powermode register of AX5043.
 *
 * @param[in]  devp               pointer to the @p AX5043Driver object.
 * @param[in]  reg_value          powermode register value.
 *
 * @return                        Most significant status bits from last SPI call.
 */
uint8_t ax5043_set_pwrmode(AX5043Driver *devp, uint8_t reg_value){
    uint8_t rxbuf[3]={0,0,0};
    uint8_t value;
    SPIDriver *spip = devp->config->spip;

    value = ax5043SPIReadRegister(spip, AX5043_REG_PWRMODE, (uint8_t)0x00, rxbuf);
    value = value & 0xF0;
    value = value | reg_value;
    ax5043SPIWriteRegister(spip, AX5043_REG_PWRMODE, value, rxbuf);
    devp->status_code = rxbuf[0];
    /*Return last status from Ax5043 while writting the register.
      Normal value is 0x80 0r 0x88*/
    return rxbuf[0];
}

/**
 * @brief   Resets the AX5043.
 *
 * @param[in]  devp               pointer to the @p AX5043Driver object.
 *
 * @return                        Most significant status bits from last SPI call.
 */
uint8_t ax5043_reset(AX5043Driver *devp)
{
    SPIDriver *spip = devp->config->spip;
    uint8_t value = 0;
    uint8_t rxbuf[3]={0,0,0};

    /* TODO: What's this for? */
    spiSelect(spip);
    chThdSleepMicroseconds(5);
    spiUnselect(spip);
    chThdSleepMicroseconds(5);
    spiSelect(spip);
    chThdSleepMicroseconds(5);

    /* Reset the chip through powermode register.*/
    ax5043SPIWriteRegister(spip, AX5043_REG_PWRMODE, AX5043_RESET_BIT, rxbuf);
    chThdSleepMilliseconds(1);

    /* Write to powermode register for enabling XOEN and REFIN and shutdown mode.
       Page 33 in programming manual.*/
    value = ax5043SPIReadRegister(spip, AX5043_REG_PWRMODE, value, rxbuf);
    /* TODO: Why are we grabbing the register value if we overwrite it completely? */
    value = AX5043_OSC_EN_BIT | AX5043_REF_EN_BIT | AX5043_POWERDOWN;
    ax5043SPIWriteRegister(spip, AX5043_REG_PWRMODE, value, rxbuf);

    ax5043SPIWriteRegister(spip, AX5043_REG_SCRATCH, (uint8_t)0xAA, rxbuf);
    value = ax5043SPIReadRegister(spip, AX5043_REG_SCRATCH, (uint8_t)0x00, rxbuf);
    if (value != 0xAA) {
        devp->error_code = AXRADIO_ERR_NOT_CONNECTED;
    }
    ax5043SPIWriteRegister(spip, AX5043_REG_SCRATCH, (uint8_t)0x55, rxbuf);
    value = ax5043SPIReadRegister(spip, AX5043_REG_SCRATCH, (uint8_t)0x00, rxbuf);
    if (value != 0x55) {
        devp->error_code = AXRADIO_ERR_NOT_CONNECTED;
    }
    /*Return last status from Ax5043 while writting the register.*/
    return rxbuf[0];
}

/**
 * @brief   Writes to AX5043 FIFO
 *
 * @param[in]  spip               pointer to the @p SPIDriver object.
 * @param[in]  ptr                Pointer to array to be written to FIFO.
 * @param[in]  len                length of array to be written to FIFO.
 *
 * @api
 * TODO return a -ve return code if there are any errors
 */
void ax5043_writefifo(SPIDriver * spip, const uint8_t *ptr, uint8_t len){
    uint8_t rxbuf[3]={0,0,0};
    if (!len)
        return;
    do {
        ax5043SPIWriteRegister(spip, AX5043_REG_FIFODATA, *ptr++, rxbuf);
    } while (--len);
}

/**
 * @brief   Reads to AX5043 FIFO
 *
 * @param[in]  devp               pointer to the @p AX5043Driver object.
 * @param[in]  axradio_rxbuffer[] Pointer to array where the packet will be kept.
 * @param[in]  len                Maximum length of array to be read FIFO.
 *
 * @param[out]                    Bytes read from FIFO.
 */
uint8_t ax5043_readfifo(SPIDriver * spip, uint8_t axradio_rxbuffer[], uint8_t len) {
    uint8_t rxbuf[3]={0,0,0};
    uint8_t bytes_read = 0;
    while (len--) {
        axradio_rxbuffer[bytes_read] = ax5043SPIReadRegister(spip, AX5043_REG_FIFODATA, (uint8_t)0x00, rxbuf);
        bytes_read++;
    }
    return bytes_read;
}

/**
 * @brief   Sets AX5043 registers.
 *
 * @param[in]  devp               pointer to the @p AX5043Driver object.
 * @param[in]  group              register group that needs to be written.
 *
 * @return                        Most significant status bits from last SPI call.
 */
uint8_t ax5043_set_regs_group(AX5043Driver *devp, ax5043_reg_group_t group) {
    uint8_t rxbuf[3] = {0, 0, 0};
    int i = 0;
    ax5043_regval_t* entry = devp->config->reg_values;
    while (entry[i].reg != AX5043_REG_END) {
        if (entry[i].group == group){
            ax5043SPIWriteRegister(devp->config->spip, entry[i].reg, entry[i].val, rxbuf);
        }
        i++;
    }
    devp->status_code = rxbuf[0];
    /*Return last status from Ax5043 while writting the register.*/
    return rxbuf[0];
}

/**
 * @brief   Gets AX5043 register values from the AX5043 driver structure.
 *
 * @param[in]  devp               pointer to the @p AX5043Driver object.
 * @param[in]  reg_name           register name.
 *
 * @return                        register value.
 */
uint8_t ax5043_get_reg_val(AX5043Driver *devp, uint16_t reg_name) {
    int i = 0;
    ax5043_regval_t* entry = devp->config->reg_values;
    while (entry[i].reg != AX5043_REG_END) {
        if (entry[i].reg == reg_name){
            return entry[i].val;
        }
        i++;
    }
    devp->error_code = AXRADIO_ERR_REG_NOT_IN_CONF;
    return 0;
}

/**
 * @brief   Gets AX5043 configuration values from the AX5043 driver structure.
 *
 * @param[in]  devp               pointer to the @p AX5043Driver object.
 * @param[in]  conf_name          configuration variable name.
 *
 * @retrun                        value in configuration variable.
 *
 * @api
 * TODO return a -ve return code if there are any errors
 */
uint32_t ax5043_get_conf_val(AX5043Driver *devp, uint8_t conf_name) {
    int i = 0;
    ax5043_confval_t* entry = devp->config->conf_values;
    while (entry[i].conf_name != AXRADIO_PHY_END) {
        if (entry[i].conf_name == conf_name){
            return entry[i].val;
        }
        i++;
    }
    devp->error_code = AXRADIO_ERR_VAL_NOT_IN_CONF;
    return 0;
}

/**
 * @brief   Sets AX5043 configuration values from the AX5043 driver structure.
 *
 * @param[in]  devp               pointer to the @p AX5043Driver object.
 * @param[in]  conf_name          configuration variable name.
 * @param[in]  value              value in configuration variable.
 *
 * @return                        0 if successful, else 0x11.
 */
uint8_t ax5043_set_conf_val(AX5043Driver *devp, uint8_t conf_name, uint32_t value) {
    int i = 0;
    ax5043_confval_t* entry = devp->config->conf_values;
    while (entry[i].conf_name != AXRADIO_PHY_END) {
        if (entry[i].conf_name == conf_name){
            entry[i].val = value;
            return 0;
        }
        i++;
    }
    devp->error_code = AXRADIO_ERR_VAL_NOT_IN_CONF;
    return AXRADIO_ERR_VAL_NOT_IN_CONF;
}

/**
 * @brief   Prepare AX5043 for tx.
 *
 * @param[in]  devp               pointer to the @p AX5043Driver object.
 *
 * @api
 * TODO return a -ve return code if there are any errors
 */
void ax5043_prepare_tx(AX5043Driver *devp){
    uint8_t rxbuf[3]={0,0,0};
    SPIDriver *spip = devp->config->spip;

    ax5043_set_pwrmode(devp, AX5043_STANDBY);
    ax5043_set_pwrmode(devp, AX5043_FIFO_ENABLED);
    ax5043_set_regs_group(devp,tx);
    ax5043_init_registers_common(devp);

    /* Set FIFO threshold and interrupt mask.*/
    ax5043SPIWriteRegister(spip, AX5043_REG_FIFOTHRESH1, (uint8_t)0x00, rxbuf);
    ax5043SPIWriteRegister(spip, AX5043_REG_FIFOTHRESH0, (uint8_t)0x80, rxbuf);
    ax5043SPIWriteRegister(spip, AX5043_REG_IRQMASK0, (uint8_t)0x00, rxbuf);
    ax5043SPIWriteRegister(spip, AX5043_REG_IRQMASK1, (uint8_t)0x01, rxbuf);

    /* Wait for xtal.*/
    while ((ax5043SPIReadRegister(spip, AX5043_REG_XTALSTATUS, (uint8_t)0x00, rxbuf) & 0x01) == 0) {
        chThdSleepMilliseconds(1);
    }
    devp->status_code = rxbuf[0];
    devp->state = AX5043_TX;
}

/**
 * @brief   prepare AX5043 for rx.
 *
 * @param[in]  devp               pointer to the @p AX5043Driver object.
 *
 * @api
 * TODO return a -ve return code if there are any errors
 */
void ax5043_prepare_rx(AX5043Driver *devp){
    uint8_t rxbuf[3]={0,0,0};
    SPIDriver *spip = devp->config->spip;

    ax5043_set_regs_group(devp,rx);
    ax5043_init_registers_common(devp);

    /* Updates RSSI reference value, Sets a group of RX registers.*/
    uint8_t rssireference = ax5043_get_conf_val(devp, AXRADIO_PHY_RSSIREFERENCE) ;
    ax5043SPIWriteRegister(spip, AX5043_REG_RSSIREFERENCE, rssireference, rxbuf);
    ax5043_set_regs_group(devp,rx_cont);
    /* Resets FIFO, changes powermode to FULL RX.*/
    ax5043SPIWriteRegister(spip, AX5043_REG_FIFOSTAT, (uint8_t)0x03, rxbuf);
    ax5043_set_pwrmode(devp, AX5043_FULL_RX);
    /* Sets FIFO threshold and interrupt mask.*/
    ax5043SPIWriteRegister(spip, AX5043_REG_FIFOTHRESH1, (uint8_t)0x00, rxbuf);
    ax5043SPIWriteRegister(spip, AX5043_REG_FIFOTHRESH0, (uint8_t)0x80, rxbuf);
    ax5043SPIWriteRegister(spip, AX5043_REG_IRQMASK0, (uint8_t)0x01, rxbuf);
    ax5043SPIWriteRegister(spip, AX5043_REG_IRQMASK1, (uint8_t)0x00, rxbuf);
    devp->status_code = rxbuf[0];
    devp->state = AX5043_RX;
}

/**
 * @brief   Does PLL ranging.
 *
 * @param[in]  devp               pointer to the @p AX5043Driver object.
 *
 * @returns                       PLLVCOI Register content.
 * @api
 * TODO return a -ve return code if there are any errors
 */
uint8_t axradio_get_pllvcoi(AX5043Driver *devp){
    uint8_t rxbuf[3]={0,0,0};
    SPIDriver *spip = devp->config->spip;

    uint8_t x = ax5043_get_conf_val(devp, AXRADIO_PHY_CHANVCOIINIT) ;
    uint8_t pll_init_val = ax5043_get_conf_val(devp, AXRADIO_PHY_CHANPLLRNGINIT);
    uint8_t pll_val = ax5043_get_conf_val(devp, AXRADIO_PHY_CHANPLLRNG);
    if (x & 0x80) {
        if (!(pll_init_val & 0xF0)) {
            x += (pll_val & 0x0F) - (pll_init_val & 0x0F);
            x &= 0x3f;
            x |= 0x80;
        }
        return x;
    }
    return ax5043SPIReadRegister(spip, AX5043_REG_PLLVCOI, (uint8_t)0x00, rxbuf);
}

/**
 * @brief   Initialized AX5043 registers common to RX and TX.
 *
 * @param[in]  devp               pointer to the @p AX5043Driver object.
 *
 * @api
 * TODO return a -ve return code if there are any errors
 */
void ax5043_init_registers_common(AX5043Driver *devp){
    uint8_t rxbuf[3]={0,0,0};
    SPIDriver *spip = devp->config->spip;

    uint8_t rng = ax5043_get_conf_val(devp, AXRADIO_PHY_CHANPLLRNG);
    if (rng & 0x20)
        devp->status_code = AXRADIO_ERR_PLLRNG_VAL;
    if ( ax5043SPIReadRegister(spip, AX5043_REG_PLLLOOP, (uint8_t)0x00, rxbuf) & 0x80) {
        ax5043SPIWriteRegister(spip, AX5043_REG_PLLRANGINGB, (uint8_t)(rng & 0x0F), rxbuf);
    }
    else {
        ax5043SPIWriteRegister(spip, AX5043_REG_PLLRANGINGA, (uint8_t)(rng & 0x0F), rxbuf);
    }
    rng = axradio_get_pllvcoi(devp);
    if (rng & 0x80)
        ax5043SPIWriteRegister(spip, AX5043_REG_PLLVCOI, (uint8_t)(rng), rxbuf);
}

/**
 * @brief   Initializes AX5043. This is written based on easyax5043.c generated from AX Radiolab.
 *
 * @param[in]  devp               pointer to the @p AX5043Driver object.
 *
 * @api
 * TODO Standardize the error handling.
 */
void ax5043_init(AX5043Driver *devp){
    SPIDriver *spip = devp->config->spip;
    uint8_t rxbuf[3]={0,0,0};

    ax5043_reset(devp);

    ax5043_set_regs_group(devp,common);
    ax5043_set_regs_group(devp,tx);

    ax5043SPIWriteRegister(spip, AX5043_REG_PLLLOOP, (uint8_t)0x09, rxbuf);
    ax5043SPIWriteRegister(spip, AX5043_REG_PLLCPI, (uint8_t)0x08, rxbuf);

    ax5043_set_pwrmode(devp, AX5043_STANDBY);
    ax5043SPIWriteRegister(spip, AX5043_REG_MODULATION, (uint8_t)0x08, rxbuf);
    ax5043SPIWriteRegister(spip, AX5043_REG_FSKDEV2, (uint8_t)0x00, rxbuf);
    ax5043SPIWriteRegister(spip, AX5043_REG_FSKDEV1, (uint8_t)0x00, rxbuf);
    ax5043SPIWriteRegister(spip, AX5043_REG_FSKDEV0, (uint8_t)0x00, rxbuf);

    /* Wait for Xtal.*/
    while ((ax5043SPIReadRegister(spip, AX5043_REG_XTALSTATUS, (uint8_t)0x00, rxbuf) & 0x01) == 0){
        chThdSleepMilliseconds(1);
    }

    /* Set frequency.*/
    uint32_t f = ax5043_get_conf_val(devp, AXRADIO_PHY_CHANFREQ);
    ax5043SPIWriteRegister(spip, AX5043_REG_FREQA0, (uint8_t)f, rxbuf);
    ax5043SPIWriteRegister(spip, AX5043_REG_FREQA1, (uint8_t)(f >> 8), rxbuf);
    ax5043SPIWriteRegister(spip, AX5043_REG_FREQA2, (uint8_t)(f >> 16), rxbuf);
    ax5043SPIWriteRegister(spip, AX5043_REG_FREQA3, (uint8_t)(f >> 24), rxbuf);

    /* PLL autoranging.*/
    uint8_t r;
    uint8_t pll_init_val = ax5043_get_conf_val(devp, AXRADIO_PHY_CHANPLLRNGINIT);
    if( !(pll_init_val & 0xF0) ) { // start values for ranging available
        r = pll_init_val | 0x10;
    }
    else {
        r = 0x18;
    }
    ax5043SPIWriteRegister(spip, AX5043_REG_PLLRANGINGA, (uint8_t)r, rxbuf);
    chThdSleepMilliseconds(1);
    while ((ax5043SPIReadRegister(spip, AX5043_REG_PLLRANGINGA, (uint8_t)0x00, rxbuf) & 0x10) != 0)
    {
        chThdSleepMilliseconds(1);
    }
    int8_t value = ax5043SPIReadRegister(spip, AX5043_REG_PLLRANGINGA, (uint8_t)0x00, rxbuf);
    ax5043_set_conf_val(devp, AXRADIO_PHY_CHANPLLRNG, value);
    devp->state = AX5043_PLL_RANGE_DONE;

    ax5043_set_pwrmode(devp, AX5043_POWERDOWN);
    ax5043_set_regs_group(devp,common);
    ax5043_set_regs_group(devp,rx);

    uint8_t pll_val = ax5043_get_conf_val(devp, AXRADIO_PHY_CHANPLLRNG);
    ax5043SPIReadRegister(spip, AX5043_REG_PLLRANGINGA, (pll_val & 0x0F), rxbuf);
    f = ax5043_get_conf_val(devp, AXRADIO_PHY_CHANFREQ);
    ax5043SPIWriteRegister(spip, AX5043_REG_FREQA0, (uint8_t)f, rxbuf);
    ax5043SPIWriteRegister(spip, AX5043_REG_FREQA1, (uint8_t)(f >> 8), rxbuf);
    ax5043SPIWriteRegister(spip, AX5043_REG_FREQA2, (uint8_t)(f >> 16), rxbuf);
    ax5043SPIWriteRegister(spip, AX5043_REG_FREQA3, (uint8_t)(f >> 24), rxbuf);

    ax5043_set_regs_group(devp,local_address);
}

/**
 * @brief   Transmit loop to transmit bytes of a packet.
 *
 * @param[in]  devp               pointer to the @p AX5043Driver object.
 * @param[in]  packet_len         Complete packet length including mac.
 * @param[in]  axradio_txbuffer   pointer to packet.
 * @param[in]  packet_bytes_sent length before the packet.
 *
 * @api
 * TODO Standardize the error handling, remove packet_bytes_sent, simplify the code.
 */
void transmit_loop(AX5043Driver *devp, uint16_t packet_len,uint8_t axradio_txbuffer[]){
    uint8_t rxbuf[3]={0,0,0};
    SPIDriver *spip = devp->config->spip;

    uint8_t free_fifo_bytes;
    uint8_t packet_end_indicator = 0;
    uint16_t packet_bytes_sent = 0;
    uint8_t flags = 0;
    uint16_t packet_len_to_be_sent = 0;
    uint8_t synclen = ax5043_get_conf_val(devp, AXRADIO_FRAMING_SYNCLEN);

    while (packet_end_indicator == 0) {
        if (ax5043SPIReadRegister(spip,AX5043_REG_FIFOFREE1, (uint8_t)0x00, rxbuf))
            free_fifo_bytes = 0xff;
        else
            free_fifo_bytes = ax5043SPIReadRegister(spip,AX5043_REG_FIFOFREE0, (uint8_t)0x00, rxbuf);
        /* Make sure sixteen bytes in FIFO are free. We can do with minimum 4 bytes free but taking in 16 here.*/
        if (free_fifo_bytes < 19) {
            /* FIFO commit.*/
            ax5043SPIWriteRegister(spip,AX5043_REG_FIFOSTAT, 4, rxbuf);
            continue;
        }

        switch (devp->state) {
        case AX5043_TX_LONGPREAMBLE:
            if (!packet_bytes_sent) {
                devp->state = AX5043_TX_SHORTPREAMBLE;
                packet_bytes_sent = ax5043_get_conf_val(devp, AXRADIO_PHY_PREAMBLE_LEN);
                break;
            }

            free_fifo_bytes = 7;
            if (packet_bytes_sent < 7)
                free_fifo_bytes = packet_bytes_sent;
            packet_bytes_sent -= free_fifo_bytes;
            free_fifo_bytes <<= 5;
            ax5043SPIWriteRegister(spip,AX5043_REG_FIFODATA, AX5043_FIFOCMD_REPEATDATA | (3 << 5), rxbuf);
            ax5043SPIWriteRegister(spip,AX5043_REG_FIFODATA, (uint8_t)ax5043_get_conf_val(devp, AXRADIO_PHY_PREAMBLE_FLAGS), rxbuf);
            ax5043SPIWriteRegister(spip,AX5043_REG_FIFODATA, free_fifo_bytes, rxbuf);
            ax5043SPIWriteRegister(spip,AX5043_REG_FIFODATA, (uint8_t)ax5043_get_conf_val(devp, AXRADIO_PHY_PREAMBLE_BYTE), rxbuf);
            break;

        case AX5043_TX_SHORTPREAMBLE:
            if (!packet_bytes_sent) {
                uint8_t preamble_appendbits = ax5043_get_conf_val(devp, AXRADIO_PHY_PREAMBLE_APPENDBITS);
                if (preamble_appendbits) {
                    uint8_t byte;
                    ax5043SPIWriteRegister(spip,AX5043_REG_FIFODATA, AX5043_FIFOCMD_DATA | (2 << 5), rxbuf);
                    ax5043SPIWriteRegister(spip,AX5043_REG_FIFODATA, 0x1C, rxbuf);
                    byte = ax5043_get_conf_val(devp, AXRADIO_PHY_PREAMBLE_APPENDPATTERN);
                    if (ax5043SPIReadRegister(spip,AX5043_REG_PKTADDRCFG, (uint8_t)0x00, rxbuf) & 0x80) {
                        // msb first -> stop bit below
                        byte &= 0xFF << (8-preamble_appendbits);
                        byte |= 0x80 >> preamble_appendbits;
                    } else {
                        // lsb first -> stop bit above
                        byte &= 0xFF >> (8-preamble_appendbits);
                        byte |= 0x01 << preamble_appendbits;
                    }
                    ax5043SPIWriteRegister(spip,AX5043_REG_FIFODATA, byte, rxbuf);
                }
                if ((ax5043SPIReadRegister(spip,AX5043_REG_FRAMING, (uint8_t)0x00, rxbuf) & 0x0E) == 0x06 && synclen) {
                    /* Write SYNC word if framing mode is raw_patternmatch, might use SYNCLEN > 0 as a criterion, but need to make sure SYNCLEN=0 for WMBUS.
                       Chip automatically sends SYNCWORD but matching in RX works via MATCH0PAT).*/
                    int8_t len_byte = synclen;
                    uint8_t i = (len_byte & 0x07) ? 0x04 : 0;
                    /* SYNCLEN in bytes, rather than bits. Ceiled to next integer e.g. fractional bits are counted as full bits.*/
                    len_byte += 7;
                    len_byte >>= 3;
                    ax5043SPIWriteRegister(spip,AX5043_REG_FIFODATA, AX5043_FIFOCMD_DATA | ((len_byte + 1) << 5), rxbuf);
                    ax5043SPIWriteRegister(spip,AX5043_REG_FIFODATA, (uint8_t)ax5043_get_conf_val(devp, AXRADIO_FRAMING_SYNCFLAGS) | i, rxbuf);

                    uint8_t syncword[4] = {ax5043_get_conf_val(devp, AXRADIO_FRAMING_SYNCWORD0),
                        ax5043_get_conf_val(devp, AXRADIO_FRAMING_SYNCWORD1),
                        ax5043_get_conf_val(devp, AXRADIO_FRAMING_SYNCWORD2),
                        ax5043_get_conf_val(devp, AXRADIO_FRAMING_SYNCWORD3)};
                    for (i = 0; i < len_byte; ++i) {
                        ax5043SPIWriteRegister(spip,AX5043_REG_FIFODATA, syncword[i], rxbuf);
                    }
                }
                devp->state = AX5043_TX_PACKET;
                continue;
            }
            free_fifo_bytes = 255;
            if (packet_bytes_sent < 255*8)
                free_fifo_bytes = packet_bytes_sent >> 3;
            if (free_fifo_bytes) {
                packet_bytes_sent -= ((uint16_t)free_fifo_bytes) << 3;
                ax5043SPIWriteRegister(spip,AX5043_REG_FIFODATA, AX5043_FIFOCMD_REPEATDATA | (3 << 5), rxbuf);
                ax5043SPIWriteRegister(spip,AX5043_REG_FIFODATA, (uint8_t)ax5043_get_conf_val(devp, AXRADIO_PHY_PREAMBLE_FLAGS), rxbuf);
                ax5043SPIWriteRegister(spip,AX5043_REG_FIFODATA, free_fifo_bytes, rxbuf);
                ax5043SPIWriteRegister(spip,AX5043_REG_FIFODATA, (uint8_t)ax5043_get_conf_val(devp, AXRADIO_PHY_PREAMBLE_BYTE), rxbuf);
                continue;
            }
            {
                uint8_t byte = ax5043_get_conf_val(devp, AXRADIO_PHY_PREAMBLE_BYTE) ;
                free_fifo_bytes = packet_bytes_sent;
                packet_bytes_sent = 0;
                ax5043SPIWriteRegister(spip,AX5043_REG_FIFODATA, AX5043_FIFOCMD_DATA | (2 << 5), rxbuf);
                ax5043SPIWriteRegister(spip,AX5043_REG_FIFODATA, 0x1C, rxbuf);
                if (ax5043SPIReadRegister(spip,AX5043_REG_PKTADDRCFG, (uint8_t)0x00, rxbuf) & 0x80) {
                    /* MSB first -> stop bit below.*/
                    byte &= 0xFF << (8-free_fifo_bytes);
                    byte |= 0x80 >> free_fifo_bytes;
                } else {
                    // lsb first -> stop bit above
                    byte &= 0xFF >> (8-free_fifo_bytes);
                    byte |= 0x01 << free_fifo_bytes;
                }
                ax5043SPIWriteRegister(spip,AX5043_REG_FIFODATA, byte, rxbuf);
            }
            continue;

        case AX5043_TX_PACKET:
            flags = 0;
            packet_len_to_be_sent = 0;
            if (!packet_bytes_sent)
                /* Flag byte indicates packetstart.*/
                flags |= 0x01;

            packet_len_to_be_sent = packet_len - packet_bytes_sent;
            /* 3 bytes of FIFO commands are written before payload can be written to FIFO.*/
            if (free_fifo_bytes >= packet_len_to_be_sent + 3) {
                /* Flag byte indicates packet end.*/
                flags |= 0x02;
            }
            else{
                packet_len_to_be_sent = free_fifo_bytes - 3;
            }


            ax5043SPIWriteRegister(spip,AX5043_REG_FIFODATA, AX5043_FIFOCMD_DATA | (7 << 5), rxbuf);
            /* Write FIFO chunk length byte. Length includes the flag byte, thus the +1.*/
            ax5043SPIWriteRegister(spip,AX5043_REG_FIFODATA, packet_len_to_be_sent + 1, rxbuf);
            ax5043SPIWriteRegister(spip,AX5043_REG_FIFODATA, flags, rxbuf);
            ax5043_writefifo(spip,&axradio_txbuffer[packet_bytes_sent], packet_len_to_be_sent);
            packet_bytes_sent += packet_len_to_be_sent;
            if (flags & 0x02){
                packet_end_indicator = 1;
                /* Enable radio event done (REVRDONE) event.*/
                ax5043SPIWriteRegister(spip,AX5043_REG_RADIOEVENTMASK0, 0x01, rxbuf);
                ax5043SPIWriteRegister(spip,AX5043_REG_FIFOSTAT, 4, rxbuf); // commit
            }
            break;

        default:
            packet_end_indicator = 1;
            devp->error_code = AXRADIO_ERR_UNEXPECTED_STATE;
        }
    }
    devp->state = AX5043_TX;
}

/**
 * @brief   Transmits a packet.
 *
 * @param[in]  devp               pointer to the @p AX5043Driver object.
 * @param[in]  addr               remote destination address of packet.
 * @param[in]  pkt                pointer to packet.
 * @param[in]  pktlen             packet length.
 *
 * @param[out] AXRADIO_ERR        Error code.
 *
 * @api
 * TODO Standardize the error handling, Maybe move address to a driver config structure
 */
uint8_t transmit_packet(AX5043Driver *devp, const struct axradio_address *addr, const uint8_t *pkt, uint16_t pktlen) {
    uint8_t rxbuf[3]={0,0,0};
    SPIDriver *spip = devp->config->spip;
    uint16_t packet_len;
    uint8_t axradio_txbuffer[PKTDATA_BUFLEN];
    uint8_t axradio_localaddr[4];

    uint8_t maclen = ax5043_get_conf_val(devp, AXRADIO_FRAMING_MACLEN);
    uint8_t destaddrpos = ax5043_get_conf_val(devp, AXRADIO_FRAMING_DESTADDRPOS);
    uint8_t addrlen = ax5043_get_conf_val(devp, AXRADIO_FRAMING_ADDRLEN);
    uint8_t sourceaddrpos = ax5043_get_conf_val(devp, AXRADIO_FRAMING_SOURCEADDRPOS);
    uint8_t lenmask = ax5043_get_conf_val(devp, AXRADIO_FRAMING_LENMASK);
    uint8_t lenoffs = ax5043_get_conf_val(devp, AXRADIO_FRAMING_LENOFFS);
    uint8_t lenpos = ax5043_get_conf_val(devp, AXRADIO_FRAMING_LENPOS);

    axradio_localaddr[0] = ax5043_get_reg_val(devp, AX5043_REG_PKTADDR0);
    axradio_localaddr[1] = ax5043_get_reg_val(devp, AX5043_REG_PKTADDR1);
    axradio_localaddr[2] = ax5043_get_reg_val(devp, AX5043_REG_PKTADDR2);
    axradio_localaddr[3] = ax5043_get_reg_val(devp, AX5043_REG_PKTADDR3);

    packet_len = pktlen + maclen;
    if (packet_len > sizeof(axradio_txbuffer))
        return AXRADIO_ERR_INVALID;

    /* Prepare the MAC segment of the packet.*/
    memset(axradio_txbuffer, 0, maclen);
    memcpy(&axradio_txbuffer[maclen], pkt, pktlen);
    if (destaddrpos != 0xff)
        memcpy(&axradio_txbuffer[destaddrpos], &addr->addr, addrlen);
    if (sourceaddrpos != 0xff)
        memcpy(&axradio_txbuffer[sourceaddrpos], axradio_localaddr, addrlen);
    if (lenmask) {
        /* Calculate payload length and update the MAC of payload.*/
        uint8_t len_byte = (uint8_t)(packet_len - lenoffs) & lenmask;
        axradio_txbuffer[lenpos] = (axradio_txbuffer[lenpos] & (uint8_t)~lenmask) | len_byte;
    }
    /*Clear radioevent flag. This indicator is set when packet is out.*/
    ax5043SPIReadRegister(spip,AX5043_REG_RADIOEVENTREQ0, (uint8_t)0x00, rxbuf);
    /* Clear leftover FIFO data & flags.*/
    ax5043SPIWriteRegister(spip, AX5043_REG_FIFOSTAT, 3, rxbuf);
    devp->state = AX5043_TX_LONGPREAMBLE;

    /*Code for 4-FSK mode.*/
    if ((ax5043SPIReadRegister(spip,AX5043_REG_MODULATION, (uint8_t)0x00, rxbuf) & 0x0F) == 9) {
        ax5043SPIWriteRegister(spip,AX5043_REG_FIFODATA, AX5043_FIFOCMD_DATA | (7 << 5), rxbuf);
        /* Length including flags.*/
        ax5043SPIWriteRegister(spip,AX5043_REG_FIFODATA, 2, rxbuf);
        /* Flag PKTSTART -> dibit sync.*/
        ax5043SPIWriteRegister(spip,AX5043_REG_FIFODATA, 0x01, rxbuf);
        /* Dummy byte for forcing dibit sync.*/
        ax5043SPIWriteRegister(spip,AX5043_REG_FIFODATA, 0x11, rxbuf);
    }
    transmit_loop(devp, packet_len, axradio_txbuffer);
    ax5043_set_pwrmode(devp, AX5043_FULL_TX);

    ax5043SPIReadRegister(spip,AX5043_REG_RADIOEVENTREQ0, (uint8_t)0x00, rxbuf);
    while (ax5043SPIReadRegister(spip,AX5043_REG_RADIOSTATE, (uint8_t)0x00, rxbuf) != 0) {
        chThdSleepMilliseconds(1);
    }

    ax5043SPIWriteRegister(spip,AX5043_REG_RADIOEVENTMASK0, 0x00, rxbuf);
    devp->error_code = AXRADIO_ERR_NOERROR;
    return AXRADIO_ERR_NOERROR;
}

/**
 * @brief   Receive loop to recieve bytes from FIFO.
 *
 * @param[in]  devp               pointer to the @p AX5043Driver object.
 * @param[out] axradio_rxbuffer[] Pointer to array where the packet will be kept.
 *
 * @return                        Length of packet received.
 *
 * @api
 * TODO return a -ve return code if there are any errors
 */
uint8_t receive_loop(AX5043Driver *devp, uint8_t axradio_rxbuffer[]) {
    uint8_t rxbuf[3]={0,0,0};
    SPIDriver *spip = devp->config->spip;
    uint8_t fifo_cmd;
    uint8_t i;
    uint8_t chunk_len;
    uint8_t bytesRead = 0;

    /* Clear interrupt.*/
    ax5043SPIReadRegister(spip, AX5043_REG_RADIOEVENTREQ0, (uint8_t)0x00, rxbuf);
    devp->state = AX5043_RX_LOOP;
    /* Loop until FIFO not empty.*/
    while ((ax5043SPIReadRegister(spip, AX5043_REG_FIFOSTAT, (uint8_t)0x00, rxbuf) & 0x01) != 1) {
        /* FIFO read comman.*/
        fifo_cmd = ax5043SPIReadRegister(spip, AX5043_REG_FIFODATA, (uint8_t)0x00, rxbuf);
        /* Top 3 bits encode payload length.*/
        chunk_len = (fifo_cmd & 0xE0) >> 5;
        /* 7 means variable length, get length byte from next read.*/
        if (chunk_len == 7)
            chunk_len = ax5043SPIReadRegister(spip, AX5043_REG_FIFODATA, (uint8_t)0x00, rxbuf);
        fifo_cmd &= 0x1F;
        switch (fifo_cmd) {
        case AX5043_FIFOCMD_DATA:
            if (chunk_len!=0){
                /* Discard the flag.*/
                ax5043SPIReadRegister(spip, AX5043_REG_FIFODATA, (uint8_t)0x00, rxbuf);
                chunk_len = chunk_len - 1;
                bytesRead = ax5043_readfifo(spip, axradio_rxbuffer, chunk_len);
            }
            break;

        case AX5043_FIFOCMD_RFFREQOFFS:
            if (chunk_len == 3){
                devp->rf_freq_off3 = ax5043SPIReadRegister(spip, AX5043_REG_FIFODATA, (uint8_t)0x00, rxbuf);
                devp->rf_freq_off2 = ax5043SPIReadRegister(spip, AX5043_REG_FIFODATA, (uint8_t)0x00, rxbuf);
                devp->rf_freq_off1 = ax5043SPIReadRegister(spip, AX5043_REG_FIFODATA, (uint8_t)0x00, rxbuf);
            }
            else{
                for(i=0;i<chunk_len;i++){
                    devp->dropped[i] = ax5043SPIReadRegister(spip, AX5043_REG_FIFODATA, (uint8_t)0x00, rxbuf);
                    devp->error_code = AXRADIO_ERR_FIFO_CHUNK;
                }
            }
            break;

        case AX5043_FIFOCMD_FREQOFFS:
            if (chunk_len == 2){
                devp->rf_freq_off3 = 0;
                devp->rf_freq_off2 = ax5043SPIReadRegister(spip, AX5043_REG_FIFODATA, (uint8_t)0x00, rxbuf);
                devp->rf_freq_off1 = ax5043SPIReadRegister(spip, AX5043_REG_FIFODATA, (uint8_t)0x00, rxbuf);
            }
            else{
                for(i=0;i<chunk_len;i++){
                    devp->dropped[i] = ax5043SPIReadRegister(spip, AX5043_REG_FIFODATA, (uint8_t)0x00, rxbuf);
                    devp->error_code = AXRADIO_ERR_FIFO_CHUNK;
                }
            }
            break;

        case AX5043_FIFOCMD_RSSI:
            if (chunk_len == 1){
                devp->rssi = ax5043SPIReadRegister(spip, AX5043_REG_FIFODATA, (uint8_t)0x00, rxbuf);
            }
            else{
                for(i=0;i<chunk_len;i++){
                    devp->dropped[i] = ax5043SPIReadRegister(spip, AX5043_REG_FIFODATA, (uint8_t)0x00, rxbuf);
                    devp->error_code = AXRADIO_ERR_FIFO_CHUNK;
                }
            }
            break;

        default:
            devp->error_code = AXRADIO_ERR_FIFO_CMD;
            for(i=0;i<chunk_len;i++){
                devp->dropped[i] = ax5043SPIReadRegister(spip, AX5043_REG_FIFODATA, (uint8_t)0x00, rxbuf);
            }
        }
        devp->state = AX5043_RX;
    }
    return bytesRead;
}

/**
 * @brief   Prepare for CW mode
 *
 * @param[in]  devp               pointer to the @p AX5043Driver object.
 *
 * @return                        Length of packet received.
 *
 * @api
 * TODO return a -ve return code if there are any errors
 */
uint8_t ax5043_prepare_cw(AX5043Driver *devp){
    uint8_t rxbuf[3]={0,0,0};
    SPIDriver *spip = devp->config->spip;

    ax5043SPIWriteRegister(spip, AX5043_REG_FSKDEV2, (uint8_t)0x00, rxbuf);
    ax5043SPIWriteRegister(spip, AX5043_REG_FSKDEV1, (uint8_t)0x00, rxbuf);
    ax5043SPIWriteRegister(spip, AX5043_REG_FSKDEV0, (uint8_t)0x00, rxbuf);
    ax5043SPIWriteRegister(spip, AX5043_REG_TXRATE2, (uint8_t)0x00, rxbuf);
    ax5043SPIWriteRegister(spip, AX5043_REG_TXRATE1, (uint8_t)0x00, rxbuf);
    ax5043SPIWriteRegister(spip, AX5043_REG_TXRATE0, (uint8_t)0x01, rxbuf);

    ax5043_set_pwrmode(devp, AX5043_FULL_TX);

    /* This is not mentioned in datasheet or programming manual but is required.
     * Removing this will make the transmission to transmit in low power for a few seconds
     * before it reaches peak power.*/
    /* FIFO reset.*/
    ax5043SPIWriteRegister(spip, AX5043_REG_FIFOSTAT, (uint8_t)0x03, rxbuf);
    ax5043SPIWriteRegister(spip, AX5043_REG_FIFODATA, (uint8_t)(AX5043_FIFOCMD_REPEATDATA|0x60), rxbuf);
    /* Preamble flag.*/
    ax5043SPIWriteRegister(spip, AX5043_REG_FIFODATA, (uint8_t)0x38, rxbuf);
    ax5043SPIWriteRegister(spip, AX5043_REG_FIFODATA, (uint8_t)0xff, rxbuf);
    /* Preamble.*/
    ax5043SPIWriteRegister(spip, AX5043_REG_FIFODATA, (uint8_t)0x55, rxbuf);
    /* FIFO Commit.*/
    ax5043SPIWriteRegister(spip, AX5043_REG_FIFOSTAT, (uint8_t)0x04, rxbuf);

    ax5043_set_pwrmode(devp, AX5043_STANDBY);
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

    uint8_t rxbuf[3]={0,0,0};
    SPIDriver *spip = devp->config->spip;

    ax5043_set_pwrmode(devp, AX5043_FULL_TX);
    ax5043SPIWriteRegister(spip, AX5043_REG_FIFODATA, (uint8_t)(AX5043_FIFOCMD_REPEATDATA|0x60), rxbuf);
    /* Preamble flag.*/
    ax5043SPIWriteRegister(spip, AX5043_REG_FIFODATA, (uint8_t)0x38, rxbuf);
    ax5043SPIWriteRegister(spip, AX5043_REG_FIFODATA, (uint8_t)0xFF, rxbuf);
    /* Preamble.*/
    ax5043SPIWriteRegister(spip, AX5043_REG_FIFODATA, (uint8_t)0x00, rxbuf);
    /* FIFO Commit.*/
    ax5043SPIWriteRegister(spip, AX5043_REG_FIFOSTAT, (uint8_t)0x04, rxbuf);
    chThdSleepMilliseconds(dot_dash_time);
    ax5043_set_pwrmode(devp, AX5043_STANDBY);

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

    return SPACE;
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
/*===========================================================================*/
/* TODO END CLEANUP                                                          */
/*===========================================================================*/

#endif /* AX5043_USE_SPI */

/*==========================================================================*/
/* Interface implementation.                                                */
/*==========================================================================*/

static const struct AX5043VMT vmt_device = {
    (size_t)0,
};

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Initializes an instance of AX5043Driver object.
 *
 * @param[out] devp     pointer to the @p AX5043Driver object
 *
 * @init
 */
void ax5043ObjectInit(AX5043Driver *devp) {
    devp->vmt = &vmt_device;

    devp->config = NULL;

    devp->state = AX5043_STOP;
}

/**
 * @brief   Configures and activates the AX5043 Radio Driver.
 *
 * @param[in] devp      pointer to the @p AX5043Driver object
 * @param[in] config    pointer to the @p AX5043Config object
 *
 * @api
 */
void ax5043Start(AX5043Driver *devp, const AX5043Config *config) {
    osalDbgCheck((devp != NULL) && (config != NULL));
    osalDbgAssert((devp->state == AX5043_STOP) ||
            (devp->state == AX5043_READY),
            "ax5043Start(), invalid state");

    devp->config = config;
    devp->rf_freq_off3 = 0;
    devp->rf_freq_off2 = 0;
    devp->rf_freq_off1 = 0;
    devp->rssi = 0;
    devp->error_code = 0;
    devp->status_code = 0;

    ax5043_init(devp);
    switch(config->ax5043_mode) {
    case AX5043_MODE_RX:
        ax5043_prepare_rx(devp);
        break;
    case AX5043_MODE_TX:
        ax5043_prepare_tx(devp);
        break;
    case AX5043_MODE_CW:
        ax5043_prepare_cw(devp);
        break;
    case AX5043_MODE_OFF:
        ax5043_set_pwrmode(devp, AX5043_POWERDOWN);
        break;
    default:
        ax5043_prepare_rx(devp);
    }
}

/**
 * @brief   Deactivates the AX5043 Radio Driver.
 *
 * @param[in] devp      pointer to the @p AX5043Driver object
 *
 * @api
 */
void ax5043Stop(AX5043Driver *devp) {
    ax5043_set_pwrmode(devp, AX5043_POWERDOWN);
    devp->state = AX5043_OFF;
    /* TODO: verify if additional driver things needs to be done.*/
    devp->state = AX5043_STOP;
}

/** @} */
