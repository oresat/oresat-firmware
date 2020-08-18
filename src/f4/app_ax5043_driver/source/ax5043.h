/*! \file ax5043.h */

/**
 * @file    ax5043.h
 * @brief   AX5043 Radio.
 *
 * @addtogroup AX5043
 * @ingroup ORESAT
 * @{
 */
 
#ifndef _AX5043_H
#define _AX5043_H

/**
 * @name    Version Identification
 * @{
 */
/**
 * @brief   AX5043 Driver version string.
 */
#define AX5043_VERSION                      "1.0.0"

/**
 * @brief   AX5043 Driver version major number.
 */
#define AX5043_MAJOR                        1

/**
 * @brief   AX5043 Driver version minor number.
 */
#define AX5043_MINOR                        0

/**
 * @brief   AX5043 Driver version patch number.
 */
#define AX5043_PATCH                        0
/** @} */

/**
 * @name    AX5043 Register Addresses
 * @{
 */

/* Status and test registers */
#define AX5043_REG_REV                  0x0
#define AX5043_REG_SCRATCH              0x1

/* Power and voltage regulator */
#define AX5043_REG_PWRMODE              0x2
#define AX5043_REG_POWSTAT              0x3
#define AX5043_REG_POWSTICKYSTAT        0x4
#define AX5043_REG_POWIRQMASK           0x5

/* Interrupt control */
#define AX5043_REG_IRQMASK1             0x6
#define AX5043_REG_IRQMASK0             0x7
#define AX5043_REG_RADIOEVENTMASK1      0x8
#define AX5043_REG_RADIOEVENTMASK0      0x9

#define AX5043_REG_IRQREQUEST1          0xC
#define AX5043_REG_IRQREQUEST0          0xD
#define AX5043_REG_RADIOEVENTREQ1       0xE
#define AX5043_REG_RADIOEVENTREQ0       0xF

/* Modulation and framing */
#define AX5043_REG_MODULATION           0x010
#define AX5043_REG_ENCODING             0x011
#define AX5043_REG_FRAMING              0x012
#define AX5043_REG_CRCINIT3             0x014
#define AX5043_REG_CRCINIT2             0x015
#define AX5043_REG_CRCINIT1             0x016
#define AX5043_REG_CRCINIT0             0x017

/* FEC */
#define AX5043_REG_FEC                  0x018
#define AX5043_REG_FECSYNC              0x019
#define AX5043_REG_FECSTATUS            0x01A

/* Status */
#define AX5043_REG_RADIOSTATE           0x01C
#define AX5043_REG_XTALSTATUS           0x01D

/* Pin configuration */
#define AX5043_REG_PINSTATE             0x20
#define AX5043_REG_PINFUNCSYSCLK        0x21
#define AX5043_REG_PINFUNCDCLK          0x22
#define AX5043_REG_PINFUNCDATA          0x23
#define AX5043_REG_PINFUNCIRQ           0x24
#define AX5043_REG_PINFUNCANTSEL        0x25
#define AX5043_REG_PINFUNCPWRAMP        0x26
#define AX5043_REG_PWRAMP               0x27

/* FIFO control */
#define AX5043_REG_FIFOSTAT             0x28
#define AX5043_REG_FIFODATA             0x29
#define AX5043_REG_FIFOCOUNT1           0x2A
#define AX5043_REG_FIFOCOUNT0           0x2B
#define AX5043_REG_FIFOFREE1            0x2C
#define AX5043_REG_FIFOFREE0            0x2D
#define AX5043_REG_FIFOTHRESH1          0x2E
#define AX5043_REG_FIFOTHRESH0          0x2F

/* Frequency Synthesizer */
#define AX5043_REG_PLLLOOP              0x30
#define AX5043_REG_PLLCPI               0x31
#define AX5043_REG_PLLVCODIV            0x32
#define AX5043_REG_PLLRANGINGA          0x33
#define AX5043_REG_FREQA3               0x34
#define AX5043_REG_FREQA2               0x35
#define AX5043_REG_FREQA1               0x36
#define AX5043_REG_FREQA0               0x37
#define AX5043_REG_PLLLOOPBOOST         0x38
#define AX5043_REG_PLLCPIBOOST          0x39
#define AX5043_REG_PLLRANGINGB          0x3B
#define AX5043_REG_FREQB3               0x3C
#define AX5043_REG_FREQB2               0x3D
#define AX5043_REG_FREQB1               0x3E
#define AX5043_REG_FREQB0               0x3F

/* RSSI */
#define AX5043_REG_RSSI                 0x40
#define AX5043_REG_BGNDRSSI             0x41
#define AX5043_REG_DIVERSITY            0x42
#define AX5043_REG_AGCCOUNTER           0x43

/* Receiver Tracking */
#define AX5043_REG_TRKDATARATE2         0x45
#define AX5043_REG_TRKDATARATE1         0x46
#define AX5043_REG_TRKDATARATE0         0x47
#define AX5043_REG_TRKAMPL1             0x48
#define AX5043_REG_TRKAMPL0             0x49
#define AX5043_REG_TRKPHASE1            0x4A
#define AX5043_REG_TRKPHASE0            0x4B
#define AX5043_REG_TRKRFFREQ2           0x4D
#define AX5043_REG_TRKRFFREQ1           0x4E
#define AX5043_REG_TRKRFFREQ0           0x4F
#define AX5043_REG_TRKFREQ1             0x50
#define AX5043_REG_TRKFREQ0             0x51
#define AX5043_REG_TRKFSKDEMOD1         0x52
#define AX5043_REG_TRKFSKDEMOD0         0x53

/* Timers */
#define AX5043_REG_TIMER2               0x59
#define AX5043_REG_TIMER1               0x5A
#define AX5043_REG_TIMER0               0x5B

/* Wakeup timer */
#define AX5043_REG_WAKEUPTIMER1         0x68
#define AX5043_REG_WAKEUPTIMER0         0x69
#define AX5043_REG_WAKEUP1              0x6A
#define AX5043_REG_WAKEUP0              0x6B
#define AX5043_REG_WAKEUPFREQ1          0x6C
#define AX5043_REG_WAKEUPFREQ0          0x6D
#define AX5043_REG_WAKEUPXOEARLY        0x6E

/* PHY related registers*/
#define AX5043_REG_IFFREQ1              0x100
#define AX5043_REG_IFFREQ0              0x101
#define AX5043_REG_DECIMATION           0x102
#define AX5043_REG_RXDATARATE2          0x103
#define AX5043_REG_RXDATARATE1          0x104
#define AX5043_REG_RXDATARATE0          0x105
#define AX5043_REG_MAXDROFFSET2         0x106
#define AX5043_REG_MAXDROFFSET1         0x107
#define AX5043_REG_MAXDROFFSET0         0x108
#define AX5043_REG_MAXRFOFFSET2         0x109
#define AX5043_REG_MAXRFOFFSET1         0x10A
#define AX5043_REG_MAXRFOFFSET0         0x10B
#define AX5043_REG_FSKDMAX1             0x10C
#define AX5043_REG_FSKDMAX0             0x10D
#define AX5043_REG_FSKDMIN1             0x10E
#define AX5043_REG_FSKDMIN0             0x10F
#define AX5043_REG_AFSKSPACE1           0x110
#define AX5043_REG_AFSKSPACE0           0x111
#define AX5043_REG_AFSKMARK1            0x112
#define AX5043_REG_AFSKMARK0            0x113
#define AX5043_REG_AFSKCTRL             0x114
#define AX5043_REG_AMPLFILTER           0x115
#define AX5043_REG_FREQUENCYLEAK        0x116
#define AX5043_REG_RXPARAMSETS          0x117
#define AX5043_REG_RXPARAMCURSET        0x118

/* Receiver Parameter Set 0 */
#define AX5043_REG_AGCGAIN0             0x120
#define AX5043_REG_AGCTARGET0           0x121
#define AX5043_REG_AGCAHYST0            0x122
#define AX5043_REG_AGCMINMAX0           0x123
#define AX5043_REG_TIMEGAIN0            0x124
#define AX5043_REG_DRGAIN0              0x125
#define AX5043_REG_PHASEGAIN0           0x126
#define AX5043_REG_FREQUENCYGAINA0      0x127
#define AX5043_REG_FREQUENCYGAINB0      0x128
#define AX5043_REG_FREQUENCYGAINC0      0x129
#define AX5043_REG_FREQUENCYGAIND0      0x12A
#define AX5043_REG_AMPLITUDEGAIN0       0x12B
#define AX5043_REG_FREQDEV10            0x12C
#define AX5043_REG_FREQDEV00            0x12D
#define AX5043_REG_FOURFSK0             0x12E
#define AX5043_REG_BBOFFSRES0           0x12F

/* Receiver Parameter Set 1 */
#define AX5043_REG_AGCGAIN1             0x130
#define AX5043_REG_AGCTARGET1           0x131
#define AX5043_REG_AGCAHYST1            0x132
#define AX5043_REG_AGCMINMAX1           0x133
#define AX5043_REG_TIMEGAIN1            0x134
#define AX5043_REG_DRGAIN1              0x135
#define AX5043_REG_PHASEGAIN1           0x136
#define AX5043_REG_FREQUENCYGAINA1      0x137
#define AX5043_REG_FREQUENCYGAINB1      0x138
#define AX5043_REG_FREQUENCYGAINC1      0x139
#define AX5043_REG_FREQUENCYGAIND1      0x13A
#define AX5043_REG_AMPLITUDEGAIN1       0x13B
#define AX5043_REG_FREQDEV11            0x13C
#define AX5043_REG_FREQDEV01            0x13D
#define AX5043_REG_FOURFSK1             0x13E
#define AX5043_REG_BBOFFSRES1           0x13F

/* Receiver Parameter Set 2 */
#define AX5043_REG_AGCGAIN2             0x140
#define AX5043_REG_AGCTARGET2           0x141
#define AX5043_REG_AGCAHYST2            0x142
#define AX5043_REG_AGCMINMAX2           0x143
#define AX5043_REG_TIMEGAIN2            0x144
#define AX5043_REG_DRGAIN2              0x145
#define AX5043_REG_PHASEGAIN2           0x146
#define AX5043_REG_FREQGAINA2           0x147
#define AX5043_REG_FREQGAINB2           0x148
#define AX5043_REG_FREQGAINC2           0x149
#define AX5043_REG_FREQGAIND2           0x14A
#define AX5043_REG_AMPLGAIN2            0x14B
#define AX5043_REG_FREQDEV12            0x14C
#define AX5043_REG_FREQDEV02            0x14D
#define AX5043_REG_FOURFSK2             0x14E
#define AX5043_REG_BBOFFSRES2           0x14F

/* Receiver Parameter Set 3 */
#define AX5043_REG_AGCGAIN3             0x150
#define AX5043_REG_AGCTARGET3           0x151
#define AX5043_REG_AGCAHYST3            0x152
#define AX5043_REG_AGCMINMAX3           0x153
#define AX5043_REG_TIMEGAIN3            0x154
#define AX5043_REG_DRGAIN3              0x155
#define AX5043_REG_PHASEGAIN3           0x156
#define AX5043_REG_FREQUENCYGAINA3      0x157
#define AX5043_REG_FREQUENCYGAINB3      0x158
#define AX5043_REG_FREQUENCYGAINC3      0x159
#define AX5043_REG_FREQUENCYGAIND3      0x15A
#define AX5043_REG_AMPLITUDEGAIN3       0x15B
#define AX5043_REG_FREQDEV13            0x15C
#define AX5043_REG_FREQDEV03            0x15D
#define AX5043_REG_FOURFSK3             0x15E
#define AX5043_REG_BBOFFSRES3           0x15F

/* Transmitter Parameters */
#define AX5043_REG_MODCFGF              0x160
#define AX5043_REG_FSKDEV2              0x161
#define AX5043_REG_FSKDEV1              0x162
#define AX5043_REG_FSKDEV0              0x163
#define AX5043_REG_MODCFGA              0x164
#define AX5043_REG_TXRATE2              0x165
#define AX5043_REG_TXRATE1              0x166
#define AX5043_REG_TXRATE0              0x167
#define AX5043_REG_TXPWRCOEFFA1         0x168
#define AX5043_REG_TXPWRCOEFFA0         0x169
#define AX5043_REG_TXPWRCOEFFB1         0x16A
#define AX5043_REG_TXPWRCOEFFB0         0x16B
#define AX5043_REG_TXPWRCOEFFC1         0x16C
#define AX5043_REG_TXPWRCOEFFC0         0x16D
#define AX5043_REG_TXPWRCOEFFD1         0x16E
#define AX5043_REG_TXPWRCOEFFD0         0x16F
#define AX5043_REG_TXPWRCOEFFE1         0x170
#define AX5043_REG_TXPWRCOEFFE0         0x171

/* PLL parameters */
#define AX5043_REG_PLLVCOI              0x180
#define AX5043_REG_PLLVCOIR             0x181
#define AX5043_REG_PLLLOCKDET           0x182
#define AX5043_REG_PLLRNGCLK            0x183

/* Crystal Oscillator */
#define AX5043_REG_XTALCAP              0x184

/* Baseband */
#define AX5043_REG_BBTUNE               0x188
#define AX5043_REG_BBOFFSCAP            0x189

/* Packet Format */
#define AX5043_REG_PKTADDRCFG           0x200
#define AX5043_REG_PKTLENCFG            0x201
#define AX5043_REG_PKTLENOFFSET         0x202
#define AX5043_REG_PKTMAXLEN            0x203
#define AX5043_REG_PKTADDR3             0x204
#define AX5043_REG_PKTADDR2             0x205
#define AX5043_REG_PKTADDR1             0x206
#define AX5043_REG_PKTADDR0             0x207
#define AX5043_REG_PKTADDRMASK3         0x208
#define AX5043_REG_PKTADDRMASK2         0x209
#define AX5043_REG_PKTADDRMASK1         0x20A
#define AX5043_REG_PKTADDRMASK0         0x20B

/* Pattern Match */
#define AX5043_REG_MATCH0PAT3           0x210
#define AX5043_REG_MATCH0PAT2           0x211
#define AX5043_REG_MATCH0PAT1           0x212
#define AX5043_REG_MATCH0PAT0           0x213
#define AX5043_REG_MATCH0LEN            0x214
#define AX5043_REG_MATCH0MIN            0x215
#define AX5043_REG_MATCH0MAX            0x216
#define AX5043_REG_MATCH1PAT1           0x218
#define AX5043_REG_MATCH1PAT0           0x219
#define AX5043_REG_MATCH1LEN            0x21C
#define AX5043_REG_MATCH1MIN            0x21D
#define AX5043_REG_MATCH1MAX            0x21E

/* Packet Controller */
#define AX5043_REG_TMGTXBOOST           0x220
#define AX5043_REG_TMGTXSETTLE          0x221
#define AX5043_REG_TMGRXBOOST           0x223
#define AX5043_REG_TMGRXSETTLE          0x224
#define AX5043_REG_TMGRXOFFSACQ         0x225
#define AX5043_REG_TMGRXCOARSEAGC       0x226
#define AX5043_REG_TMGRXAGC             0x227
#define AX5043_REG_TMGRXRSSI            0x228
#define AX5043_REG_TMGRXPREAMBLE1       0x229
#define AX5043_REG_TMGRXPREAMBLE2       0x22A
#define AX5043_REG_TMGRXPREAMBLE3       0x22B
#define AX5043_REG_RSSIREFERENCE        0x22C
#define AX5043_REG_RSSIABSTHR           0x22D
#define AX5043_REG_BGNDRSSIGAIN         0x22E
#define AX5043_REG_BGNDRSSITHR          0x22F
#define AX5043_REG_PKTCHUNKSIZE         0x230
#define AX5043_REG_PKTMISCFLAGS         0x231
#define AX5043_REG_PKTSTOREFLAGS        0x232
#define AX5043_REG_PKTACCEPTFLAGS       0x233

/* General Purpose ADC */
#define AX5043_REG_GPADCCTRL            0x300
#define AX5043_REG_GPADCPERIOD          0x301
#define AX5043_REG_GPADC13VALUE1        0x308
#define AX5043_REG_GPADC13VALUE0        0x309

/* Low Power Oscillator Calibration */
#define AX5043_REG_LPOSCCONFIG          0x310
#define AX5043_REG_LPOSCSTATUS          0x311
#define AX5043_REG_LPOSCKFILT1          0x312
#define AX5043_REG_LPOSCKFILT0          0x313
#define AX5043_REG_LPOSCREF1            0x314
#define AX5043_REG_LPOSCREF0            0x315
#define AX5043_REG_LPOSCFREQ1           0x316
#define AX5043_REG_LPOSCFREQ0           0x317
#define AX5043_REG_LPOSCPER1            0x318
#define AX5043_REG_LPOSCPER0            0x319

/* DAC */
#define AX5043_REG_DACVALUE1            0x330
#define AX5043_REG_DACVALUE0            0x331
#define AX5043_REG_DACCONFIG            0x332

/* Performance Tuning Registers */
#define AX5043_REG_REF                  0xF00
#define AX5043_REG_0xF00                0xF00
#define AX5043_REG_0xF0C                0xF0C
#define AX5043_REG_0xF0D                0xF0D
#define AX5043_REG_XTALOSC              0xF10
#define AX5043_REG_XTALAMPL             0xF11
#define AX5043_REG_0xF1C                0xF1C
#define AX5043_REG_0xF18                0xF18
#define AX5043_REG_0xF21                0xF21
#define AX5043_REG_0xF22                0xF22
#define AX5043_REG_0xF23                0xF23
#define AX5043_REG_0xF26                0xF26
#define AX5043_REG_0xF30                0xF30
#define AX5043_REG_0xF31                0xF31
#define AX5043_REG_0xF32                0xF32
#define AX5043_REG_0xF33                0xF33
#define AX5043_REG_0xF34                0xF34
#define AX5043_REG_0xF35                0xF35
#define AX5043_REG_0xF44                0xF44
#define AX5043_REG_0xF72                0xF72
#define AX5043_REG_XTALDIV              0xF35

/* Not a real register. Indicator of end of registers.*/
#define AX5043_REG_END                  0xFFF
/** @} */

/**
 * @name    AX5043 Register and bit values
 * 
 */
/* Power modes */
#define AX5043_RESET_BIT                (1 << 7)
#define AX5043_OSC_EN_BIT               (1 << 6)
#define AX5043_REF_EN_BIT               (1 << 5)

#define AX5043_POWERDOWN                0x0
#define AX5043_DEEPSLEEP                0x1
#define AX5043_STANDBY                  0x5
#define AX5043_FIFO_ENABLED             0x7
#define AX5043_SYNTH_RX                 0x8
#define AX5043_FULL_RX                  0x9
#define AX5043_WOR_RX                   0xB
#define AX5043_SYNTH_TX                 0xC
#define AX5043_FULL_TX                  0xD

/**
 * @name    AX5043 FIFO Commands
 * 
 */
#define AX5043_FIFOCMD_NOP      0x00
#define AX5043_FIFOCMD_DATA     0x01
#define AX5043_FIFOCMD_REPEATDATA 0x02
#define AX5043_FIFOCMD_TIMER    0x10
#define AX5043_FIFOCMD_RSSI     0x11
#define AX5043_FIFOCMD_FREQOFFS   0x12
#define AX5043_FIFOCMD_RFFREQOFFS 0x13
#define AX5043_FIFOCMD_DATARATE   0x14
#define AX5043_FIFOCMD_ANTRSSI    0x15
#define AX5043_FIFOCMD_TXCTRL   0x1C
#define AX5043_FIFOCMD_TXPWR    0x1D

/**
 * @brief  FIFO commit command
 */
#define AX5043_FIFO_COMMIT_CMD          (1 << 2)
#define AX5043_FIFO_PKTSTART            1
#define AX5043_FIFO_PKTEND              (1 << 1)
#define AX5043_FIFO_NOCRC               (1 << 3)
#define AX5043_FIFO_RAW                 (1 << 4)

#define PKTDATA_BUFLEN 260

/**
 * @brief  Error codes
 */
#define AXRADIO_ERR_NOERROR                     0x00
#define AXRADIO_ERR_NOTSUPPORTED                0x01
#define AXRADIO_ERR_BUSY                        0x02
#define AXRADIO_ERR_TIMEOUT                     0x03
#define AXRADIO_ERR_INVALID                     0x04
#define AXRADIO_ERR_NOCHIP                      0x05
#define AXRADIO_ERR_RANGING                     0x06
#define AXRADIO_ERR_LOCKLOST                    0x07
#define AXRADIO_ERR_RETRANSMISSION              0x08
#define AXRADIO_ERR_RESYNC                      0x09
#define AXRADIO_ERR_RESYNCTIMEOUT               0x0a
#define AXRADIO_ERR_RECEIVESTART                0x0b
#define AXRADIO_ERR_FIFO_CHUNK                  0x0c
#define AXRADIO_ERR_FIFO_CMD                    0x0d
#define AXRADIO_ERR_UNEXPECTED_STATE            0x0e
#define AXRADIO_ERR_NOT_CONNECTED               0x0f
#define AXRADIO_ERR_REG_NOT_IN_CONF             0x10
#define AXRADIO_ERR_VAL_NOT_IN_CONF             0x11
#define AXRADIO_ERR_PLLRNG_VAL                  0x12

/**
 * @brief  PHY and Framing details
 */
#define AXRADIO_PHY_PN9                     0
#define AXRADIO_PHY_NRCHANNELS              1
#define AXRADIO_PHY_CHANFREQ                2
#define AXRADIO_PHY_CHANPLLRNGINIT          3
#define AXRADIO_PHY_CHANVCOIINIT            4
#define AXRADIO_PHY_CHANPLLRNG              5
#define AXRADIO_PHY_CHANVCOI                6
#define AXRADIO_PHY_VCOCALIB                7
#define AXRADIO_PHY_MAXFREQOFFSET           8
#define AXRADIO_PHY_RSSIOFFSET              9
#define AXRADIO_PHY_RSSIREFERENCE           10
#define AXRADIO_PHY_CHANNELBUSY             11
#define AXRADIO_PHY_CS_PERIOD               12
#define AXRADIO_PHY_CS_ENABLED              13
#define AXRADIO_PHY_LBT_RETRIES             14
#define AXRADIO_PHY_LBT_FORCETX             15
#define AXRADIO_PHY_PREAMBLE_WOR_LONGLEN    16
#define AXRADIO_PHY_PREAMBLE_WOR_LEN        17
#define AXRADIO_PHY_PREAMBLE_LONGLEN        18
#define AXRADIO_PHY_PREAMBLE_LEN            19
#define AXRADIO_PHY_PREAMBLE_BYTE           20
#define AXRADIO_PHY_PREAMBLE_FLAGS          21
#define AXRADIO_PHY_PREAMBLE_APPENDBITS     22
#define AXRADIO_PHY_PREAMBLE_APPENDPATTERN  23
#define AXRADIO_FRAMING_MACLEN              24
#define AXRADIO_FRAMING_ADDRLEN             25
#define AXRADIO_FRAMING_DESTADDRPOS         26
#define AXRADIO_FRAMING_SOURCEADDRPOS       27
#define AXRADIO_FRAMING_LENPOS              28
#define AXRADIO_FRAMING_LENOFFS             29
#define AXRADIO_FRAMING_LENMASK             30
#define AXRADIO_FRAMING_SWCRCLEN            31
#define AXRADIO_FRAMING_SYNCLEN             32
#define AXRADIO_FRAMING_SYNCWORD0           33
#define AXRADIO_FRAMING_SYNCWORD1           34
#define AXRADIO_FRAMING_SYNCWORD2           35
#define AXRADIO_FRAMING_SYNCWORD3           36
#define AXRADIO_FRAMING_SYNCFLAGS           37
#define AXRADIO_FRAMING_ENABLE_SFDCALLBACK  38
#define AXRADIO_FRAMING_ACK_TIMEOUT         39
#define AXRADIO_FRAMING_ACK_DELAY           40
#define AXRADIO_FRAMING_ACK_RETRANSMISSIONS 41
#define AXRADIO_FRAMING_ACK_SEQNRPOS        42
#define AXRADIO_FRAMING_MINPAYLOADLEN       43
#define AXRADIO_WOR_PERIOD                  44
#define AXRADIO_PHY_INNERFREQLOOP           45
#define AXRADIO_PHY_END                     200

#define SPACE                               " "

/**
 * @brief   AX5043 states.
 */
typedef enum {
  AX5043_UNINIT,                  /**< Not initialized.                  */
  AX5043_STOP,                    /**< Stopped.                          */
  AX5043_READY,                   /**< Ready.                            */
  AX5043_BUSY,                    /**< Busy.                             */
  AX5043_IDLE,                    /**< Idle.                             */
  AX5043_RX,
  AX5043_RX_LOOP,                 /**< In the middle of receiving packet.*/    
  AX5043_TX,
  AX5043_PLL_RANGE_DONE,
  AX5043_OFF,
  AX5043_TX_LONGPREAMBLE,
  AX5043_TX_SHORTPREAMBLE,
  AX5043_TX_PACKET,
  AX5043_CW
} ax5043_state_t;

/**
 * @brief   AX5043 registers are gouped together based on this
 */
typedef enum {
  common,
  tx,
  rx,
  rx_cont,
  local_address
} ax5043_reg_group_t;

/**
 * @brief   Structure containing a four byte sender X.25 address
 */
struct axradio_address {
  uint8_t addr[4]; 
};

/**
 * @brief  Ax5043 Register values
 */
typedef struct {
  uint16_t reg;
  uint8_t val;
  ax5043_reg_group_t group;
} ax5043_regval_t;

/**
 * @brief   Other configuration values
 */
typedef struct {
  uint8_t conf_name;
  uint32_t val;
} ax5043_confval_t;

/**
 * @brief   Other configuration values
 */
typedef enum {
  AX5043_MODE_RX,
  AX5043_MODE_TX,
  AX5043_MODE_CW,
  AX5043_MODE_OFF,
} ax5043_mode_t;

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    Configuration options
 * @{
 */
/**
 * @brief   AX5043 SPI interface switch.
 * @details If set to @p TRUE the support for SPI is included.
 * @note    The default is @p TRUE.
 */
#if !defined(AX5043_USE_SPI) || defined(__DOXYGEN__)
#define AX5043_USE_SPI                      TRUE
#endif

/**
 * @brief   AX5043 shared SPI switch.
 * @details If set to @p TRUE the device acquires SPI bus ownership
 *          on each transaction.
 * @note    The default is @p FALSE. Requires SPI_USE_MUTUAL_EXCLUSION.
 */
#if !defined(AX5043_SHARED_SPI) || defined(__DOXYGEN__)
#define AX5043_SHARED_SPI                   FALSE
#endif
/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

#if AX5043_USE_SPI && !HAL_USE_SPI
#error "AX5043_USE_SPI requires HAL_USE_SPI"
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @name    AX5043 data structures and types.
 * @{
 */
/**
 * @brief Structure representing a AX5043 driver.
 */
typedef struct AX5043Driver AX5043Driver;

/**
 * @brief   AX5043 configuration structure.
 */
typedef struct{
#if (AX5043_USE_SPI) || defined(__DOXYGEN__)
  /**
   * @brief SPI driver associated with this AX5043.
   */
  SPIDriver *spip;

#endif /* AX5043_USE_SPI */
  ioline_t irq;
  ax5043_regval_t *reg_values;
  ax5043_confval_t *conf_values;
  ax5043_mode_t ax5043_mode;
  /* TODO: probably move these to an implementation of the driver */
  mailbox_t *mb;
} AX5043Config;

/**
 * @brief   @p AX5043 specific methods.
 */
#define _ax5043_methods_alone

/**
 * @brief   @p AX5043 specific methods with inherited ones.
 */
#define _ax5043_methods                                                     \
  _base_object_methods

/**
 * @extends BaseObjectVMT
 *
 * @brief   @p AX5043 virtual methods table.
 */
struct AX5043VMT {
  _ax5043_methods
};

/**
 * @brief   @p AX5043Driver specific data.
 */
#define _ax5043_data                                                        \
  _base_object_data                                                       \
  /* Driver state.*/                                                      \
  ax5043_state_t     state;                                               \
  /* Current configuration data.*/                                        \
  const AX5043Config          *config;                                    \
  /* Ax5043 returned values.*/                                            \
  uint8_t rf_freq_off1;                                                   \
  uint8_t rf_freq_off2;                                                   \
  uint8_t rf_freq_off3;                                                   \
  uint8_t rssi;                                                           \
  uint8_t dropped[250];                                                   \
  uint8_t error_code;                                                     \
  uint8_t status_code;                                                    \

/**
 * @brief AX5043 Radio class.
 */
struct AX5043Driver {
  /** @brief Virtual Methods Table.*/
  const struct AX5043VMT     *vmt;
  _ax5043_data
};

/*===========================================================================*/
/* Function declarations. These are not to be exposed except debugging       */
/*===========================================================================*/
uint8_t ax5043_write_reg(SPIDriver * spip, uint16_t reg, uint8_t value, uint8_t ret_value[]);
uint8_t ax5043_read_reg(SPIDriver * spip, uint16_t reg, uint8_t value, uint8_t ret_value[]);
uint8_t ax5043_set_pwrmode(AX5043Driver *devp, uint8_t reg_value);
uint8_t ax5043_reset(AX5043Driver *devp);
void ax5043_writefifo(SPIDriver * spip,const uint8_t *ptr, uint8_t len);
uint8_t ax5043_readfifo(SPIDriver * spip, uint8_t axradio_rxbuffer[], uint8_t len) ;

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
void ax5043ObjectInit(AX5043Driver *devp);
void ax5043Start(AX5043Driver *devp, const AX5043Config *config);
void ax5043Stop(AX5043Driver *devp);

uint8_t ax5043_set_regs_group(AX5043Driver *devp, ax5043_reg_group_t group);
uint8_t ax5043_get_reg_val(AX5043Driver *devp, uint16_t reg_name);
uint32_t ax5043_get_conf_val(AX5043Driver *devp, uint8_t conf_name);
uint8_t ax5043_set_conf_val(AX5043Driver *devp, uint8_t conf_name, uint32_t value);
void ax5043_prepare_tx(AX5043Driver *devp);
void ax5043_prepare_rx(AX5043Driver *devp);
void ax5043_init_registers_common(AX5043Driver *devp);
uint8_t axradio_get_pllvcoi(AX5043Driver *devp);
void ax5043_init(AX5043Driver *devp);
void transmit_loop(AX5043Driver *devp, uint16_t axradio_txbuffer_len,uint8_t axradio_txbuffer[]);
uint8_t transmit_packet(AX5043Driver *devp, const struct axradio_address *addr, const uint8_t *pkt, uint16_t pktlen);
uint8_t receive_loop(AX5043Driver *devp, uint8_t axradio_rxbuffer[]);

void ax5043_morse_dot_dash(AX5043Driver *devp, uint16_t dot_dash_time);
const char *ax5043_ascii_to_morse(char letter);
void ax5043_send_cw(AX5043Driver *devp, int wpm, char beaconMessage[], uint16_t pktlen );

#ifdef __cplusplus
}
#endif

#endif /*_AX5043_H_ */
//! @}
