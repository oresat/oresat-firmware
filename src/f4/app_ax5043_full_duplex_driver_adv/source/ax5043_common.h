/*! \file ax5043_common.h */


/*!
 * \addtogroup ax5043
 *  * @{
 *
 */
#ifndef _AX5043_COMMON_H
#define _AX5043_COMMON_H

#define DEBUG_SERIAL  SD2
#define DEBUG_CHP     ((BaseSequentialStream *) &DEBUG_SERIAL)

#include <stdbool.h>
#include <stdint.h>



/**
 * The maximum allowed frame size

#define MAX_FRAME_LEN                   1024

#define MIN_RF_FREQ_INT_VCO_RFDIV0      800000000
#define MAX_RF_FREQ_INT_VCO_RFDIV0      1050000000

#define MIN_RF_FREQ_INT_VCO_RFDIV1      (MIN_RF_FREQ_INT_VCO_RFDIV0 / 2)
#define MAX_RF_FREQ_INT_VCO_RFDIV1      (MAX_RF_FREQ_INT_VCO_RFDIV0 / 2)

#define MIN_RF_FREQ_EXT_VCO_RFDIV0      54000000
#define MAX_RF_FREQ_EXT_VCO_RFDIV0      525000000

#define MIN_RF_FREQ_EXT_VCO_RFDIV1      (MIN_RF_FREQ_EXT_VCO_RFDIV0 / 2)
#define MAX_RF_FREQ_EXT_VCO_RFDIV1      (MAX_RF_FREQ_EXT_VCO_RFDIV0 / 2)
 */

/******************************************************************************
 ********************  AX5043 control SPI registers ***************************
 *****************************************************************************/

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

/* MAC parameters */

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

/* Special Functions */

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


/******************************************************************************
 ************************* Register index in config ***************************
 *****************************************************************************/

#define AX5043_IND_REV                  1
#define AX5043_IND_SCRATCH              2
#define AX5043_IND_PWRMODE              3
#define AX5043_IND_POWSTAT              4
#define AX5043_IND_POWSTICKYSTAT        5
#define AX5043_IND_POWIRQMASK           6
#define AX5043_IND_IRQMASK1             7
#define AX5043_IND_IRQMASK0             8
#define AX5043_IND_RADIOEVENTMASK1      9
#define AX5043_IND_RADIOEVENTMASK0      10
#define AX5043_IND_IRQREQUEST1          11
#define AX5043_IND_IRQREQUEST0          12
#define AX5043_IND_RADIOEVENTREQ1       13
#define AX5043_IND_RADIOEVENTREQ0       14
#define AX5043_IND_MODULATION           15
#define AX5043_IND_ENCODING             16
#define AX5043_IND_FRAMING              17
#define AX5043_IND_CRCINIT3             18
#define AX5043_IND_CRCINIT2             19
#define AX5043_IND_CRCINIT1             20
#define AX5043_IND_CRCINIT0             21
#define AX5043_IND_FEC                  22
#define AX5043_IND_FECSYNC              23
#define AX5043_IND_FECSTATUS            24
#define AX5043_IND_RADIOSTATE           25
#define AX5043_IND_XTALSTATUS           26
#define AX5043_IND_PINSTATE             27
#define AX5043_IND_PINFUNCSYSCLK        28
#define AX5043_IND_PINFUNCDCLK          29
#define AX5043_IND_PINFUNCDATA          30
#define AX5043_IND_PINFUNCIRQ           31
#define AX5043_IND_PINFUNCANTSEL        32
#define AX5043_IND_PINFUNCPWRAMP        33
#define AX5043_IND_PWRAMP               34
#define AX5043_IND_FIFOSTAT             35
#define AX5043_IND_FIFODATA             36
#define AX5043_IND_FIFOCOUNT1           37
#define AX5043_IND_FIFOCOUNT0           38
#define AX5043_IND_FIFOFREE1            39
#define AX5043_IND_FIFOFREE0            40
#define AX5043_IND_FIFOTHRESH1          41
#define AX5043_IND_FIFOTHRESH0          42
#define AX5043_IND_PLLLOOP              43
#define AX5043_IND_PLLCPI               44
#define AX5043_IND_PLLVCODIV            45
#define AX5043_IND_PLLRANGINGA          46
#define AX5043_IND_FREQA3               47
#define AX5043_IND_FREQA2               48
#define AX5043_IND_FREQA1               49
#define AX5043_IND_FREQA0               50
#define AX5043_IND_PLLLOOPBOOST         51
#define AX5043_IND_PLLCPIBOOST          52
#define AX5043_IND_PLLRANGINGB          53
#define AX5043_IND_FREQB3               54
#define AX5043_IND_FREQB2               55
#define AX5043_IND_FREQB1               56
#define AX5043_IND_FREQB0               57
#define AX5043_IND_RSSI                 58
#define AX5043_IND_BGNDRSSI             59
#define AX5043_IND_DIVERSITY            60
#define AX5043_IND_AGCCOUNTER           61
#define AX5043_IND_TRKDATARATE2         62
#define AX5043_IND_TRKDATARATE1         63
#define AX5043_IND_TRKDATARATE0         64
#define AX5043_IND_TRKAMPL1             65
#define AX5043_IND_TRKAMPL0             66
#define AX5043_IND_TRKPHASE1            67
#define AX5043_IND_TRKPHASE0            68
#define AX5043_IND_TRKRFFREQ2           69
#define AX5043_IND_TRKRFFREQ1           70
#define AX5043_IND_TRKRFFREQ0           71
#define AX5043_IND_TRKFREQ1             72
#define AX5043_IND_TRKFREQ0             73
#define AX5043_IND_TRKFSKDEMOD1         74
#define AX5043_IND_TRKFSKDEMOD0         75
#define AX5043_IND_TIMER2               76
#define AX5043_IND_TIMER1               77
#define AX5043_IND_TIMER0               78
#define AX5043_IND_WAKEUPTIMER1         79
#define AX5043_IND_WAKEUPTIMER0         80
#define AX5043_IND_WAKEUP1              81
#define AX5043_IND_WAKEUP0              82
#define AX5043_IND_WAKEUPFREQ1          83
#define AX5043_IND_WAKEUPFREQ0          84
#define AX5043_IND_WAKEUPXOEARLY        85
#define AX5043_IND_IFFREQ1              86
#define AX5043_IND_IFFREQ0              87
#define AX5043_IND_DECIMATION           88
#define AX5043_IND_RXDATARATE2          89
#define AX5043_IND_RXDATARATE1          90
#define AX5043_IND_RXDATARATE0          91
#define AX5043_IND_MAXDROFFSET2         92
#define AX5043_IND_MAXDROFFSET1         93
#define AX5043_IND_MAXDROFFSET0         94
#define AX5043_IND_MAXRFOFFSET2         95
#define AX5043_IND_MAXRFOFFSET1         96
#define AX5043_IND_MAXRFOFFSET0         97
#define AX5043_IND_FSKDMAX1             98
#define AX5043_IND_FSKDMAX0             99
#define AX5043_IND_FSKDMIN1             100
#define AX5043_IND_FSKDMIN0             101
#define AX5043_IND_AFSKSPACE1           102
#define AX5043_IND_AFSKSPACE0           103
#define AX5043_IND_AFSKMARK1            104
#define AX5043_IND_AFSKMARK0            105
#define AX5043_IND_AFSKCTRL             106
#define AX5043_IND_AMPLFILTER           107
#define AX5043_IND_FREQUENCYLEAK        108
#define AX5043_IND_RXPARAMSETS          109
#define AX5043_IND_RXPARAMCURSET        110
#define AX5043_IND_AGCGAIN0             111
#define AX5043_IND_AGCTARGET0           112
#define AX5043_IND_AGCAHYST0            113
#define AX5043_IND_AGCMINMAX0           114
#define AX5043_IND_TIMEGAIN0            115
#define AX5043_IND_DRGAIN0              116
#define AX5043_IND_PHASEGAIN0           117
#define AX5043_IND_FREQUENCYGAINA0      118
#define AX5043_IND_FREQUENCYGAINB0      119
#define AX5043_IND_FREQUENCYGAINC0      120
#define AX5043_IND_FREQUENCYGAIND0      121
#define AX5043_IND_AMPLITUDEGAIN0       122
#define AX5043_IND_FREQDEV10            123
#define AX5043_IND_FREQDEV00            124
#define AX5043_IND_FOURFSK0             125
#define AX5043_IND_BBOFFSRES0           126
#define AX5043_IND_AGCGAIN1             127
#define AX5043_IND_AGCTARGET1           128
#define AX5043_IND_AGCAHYST1            129
#define AX5043_IND_AGCMINMAX1           130
#define AX5043_IND_TIMEGAIN1            131
#define AX5043_IND_DRGAIN1              132
#define AX5043_IND_PHASEGAIN1           133
#define AX5043_IND_FREQUENCYGAINA1      134
#define AX5043_IND_FREQUENCYGAINB1      135
#define AX5043_IND_FREQUENCYGAINC1      136
#define AX5043_IND_FREQUENCYGAIND1      137
#define AX5043_IND_AMPLITUDEGAIN1       138
#define AX5043_IND_FREQDEV11            139
#define AX5043_IND_FREQDEV01            140
#define AX5043_IND_FOURFSK1             141
#define AX5043_IND_BBOFFSRES1           142
#define AX5043_IND_AGCGAIN2             143
#define AX5043_IND_AGCTARGET2           144
#define AX5043_IND_AGCAHYST2            145
#define AX5043_IND_AGCMINMAX2           146
#define AX5043_IND_TIMEGAIN2            147
#define AX5043_IND_DRGAIN2              148
#define AX5043_IND_PHASEGAIN2           149
#define AX5043_IND_FREQGAINA2           150
#define AX5043_IND_FREQGAINB2           151
#define AX5043_IND_FREQGAINC2           152
#define AX5043_IND_FREQGAIND2           153
#define AX5043_IND_AMPLGAIN2            154
#define AX5043_IND_FREQDEV12            155
#define AX5043_IND_FREQDEV02            156
#define AX5043_IND_FOURFSK2             157
#define AX5043_IND_BBOFFSRES2           158
#define AX5043_IND_AGCGAIN3             159
#define AX5043_IND_AGCTARGET3           160
#define AX5043_IND_AGCAHYST3            161
#define AX5043_IND_AGCMINMAX3           162
#define AX5043_IND_TIMEGAIN3            163
#define AX5043_IND_DRGAIN3              164
#define AX5043_IND_PHASEGAIN3           165
#define AX5043_IND_FREQUENCYGAINA3      166
#define AX5043_IND_FREQUENCYGAINB3      167
#define AX5043_IND_FREQUENCYGAINC3      168
#define AX5043_IND_FREQUENCYGAIND3      169
#define AX5043_IND_AMPLITUDEGAIN3       170
#define AX5043_IND_FREQDEV13            171
#define AX5043_IND_FREQDEV03            172
#define AX5043_IND_FOURFSK3             173
#define AX5043_IND_BBOFFSRES3           174
#define AX5043_IND_MODCFGF              175
#define AX5043_IND_FSKDEV2              176
#define AX5043_IND_FSKDEV1              177
#define AX5043_IND_FSKDEV0              178
#define AX5043_IND_MODCFGA              179
#define AX5043_IND_TXRATE2              180
#define AX5043_IND_TXRATE1              181
#define AX5043_IND_TXRATE0              182
#define AX5043_IND_TXPWRCOEFFA1         183
#define AX5043_IND_TXPWRCOEFFA0         184
#define AX5043_IND_TXPWRCOEFFB1         185
#define AX5043_IND_TXPWRCOEFFB0         186
#define AX5043_IND_TXPWRCOEFFC1         187
#define AX5043_IND_TXPWRCOEFFC0         188
#define AX5043_IND_TXPWRCOEFFD1         189
#define AX5043_IND_TXPWRCOEFFD0         190
#define AX5043_IND_TXPWRCOEFFE1         191
#define AX5043_IND_TXPWRCOEFFE0         192
#define AX5043_IND_PLLVCOI              193
#define AX5043_IND_PLLVCOIR             194
#define AX5043_IND_PLLLOCKDET           195
#define AX5043_IND_PLLRNGCLK            196
#define AX5043_IND_XTALCAP              197
#define AX5043_IND_BBTUNE               198
#define AX5043_IND_BBOFFSCAP            199
#define AX5043_IND_PKTADDRCFG           200
#define AX5043_IND_PKTLENCFG            201
#define AX5043_IND_PKTLENOFFSET         202
#define AX5043_IND_PKTMAXLEN            203
#define AX5043_IND_PKTADDR3             204
#define AX5043_IND_PKTADDR2             205
#define AX5043_IND_PKTADDR1             206
#define AX5043_IND_PKTADDR0             207
#define AX5043_IND_PKTADDRMASK3         208
#define AX5043_IND_PKTADDRMASK2         209
#define AX5043_IND_PKTADDRMASK1         210
#define AX5043_IND_PKTADDRMASK0         211
#define AX5043_IND_MATCH0PAT3           212
#define AX5043_IND_MATCH0PAT2           213
#define AX5043_IND_MATCH0PAT1           214
#define AX5043_IND_MATCH0PAT0           215
#define AX5043_IND_MATCH0LEN            216
#define AX5043_IND_MATCH0MIN            217
#define AX5043_IND_MATCH0MAX            218
#define AX5043_IND_MATCH1PAT1           219
#define AX5043_IND_MATCH1PAT0           220
#define AX5043_IND_MATCH1LEN            221
#define AX5043_IND_MATCH1MIN            222
#define AX5043_IND_MATCH1MAX            223
#define AX5043_IND_TMGTXBOOST           224
#define AX5043_IND_TMGTXSETTLE          225
#define AX5043_IND_TMGRXBOOST           226
#define AX5043_IND_TMGRXSETTLE          227
#define AX5043_IND_TMGRXOFFSACQ         228
#define AX5043_IND_TMGRXCOARSEAGC       229
#define AX5043_IND_TMGRXAGC             230
#define AX5043_IND_TMGRXRSSI            231
#define AX5043_IND_TMGRXPREAMBLE1       232
#define AX5043_IND_TMGRXPREAMBLE2       233
#define AX5043_IND_TMGRXPREAMBLE3       234
#define AX5043_IND_RSSIREFERENCE        235
#define AX5043_IND_RSSIABSTHR           236
#define AX5043_IND_BGNDRSSIGAIN         237
#define AX5043_IND_BGNDRSSITHR          238
#define AX5043_IND_PKTCHUNKSIZE         239
#define AX5043_IND_PKTMISCFLAGS         240
#define AX5043_IND_PKTSTOREFLAGS        241
#define AX5043_IND_PKTACCEPTFLAGS       242
#define AX5043_IND_GPADCCTRL            243
#define AX5043_IND_GPADCPERIOD          244
#define AX5043_IND_GPADC13VALUE1        245
#define AX5043_IND_GPADC13VALUE0        246
#define AX5043_IND_LPOSCCONFIG          247
#define AX5043_IND_LPOSCSTATUS          248
#define AX5043_IND_LPOSCKFILT1          249
#define AX5043_IND_LPOSCKFILT0          250
#define AX5043_IND_LPOSCREF1            251
#define AX5043_IND_LPOSCREF0            252
#define AX5043_IND_LPOSCFREQ1           253
#define AX5043_IND_LPOSCFREQ0           254
#define AX5043_IND_LPOSCPER1            255
#define AX5043_IND_LPOSCPER0            256
#define AX5043_IND_DACVALUE1            257
#define AX5043_IND_DACVALUE0            258
#define AX5043_IND_DACCONFIG            259
#define AX5043_IND_REF                  260
#define AX5043_IND_0xF00                261
#define AX5043_IND_0xF0C                262
#define AX5043_IND_0xF0D                263
#define AX5043_IND_XTALOSC              264
#define AX5043_IND_XTALAMPL             265
#define AX5043_IND_0xF1C                266
#define AX5043_IND_0xF18                267
#define AX5043_IND_0xF21                268
#define AX5043_IND_0xF22                269
#define AX5043_IND_0xF23                270
#define AX5043_IND_0xF26                271
#define AX5043_IND_0xF30                272
#define AX5043_IND_0xF31                273
#define AX5043_IND_0xF32                274
#define AX5043_IND_0xF33                275
#define AX5043_IND_0xF34                276
#define AX5043_IND_0xF35                277
#define AX5043_IND_0xF44                278
#define AX5043_IND_0xF72                279
#define AX5043_IND_XTALDIV              280


/******************************************************************************
 ************ Variable index for variables in config.c file in radiolab********
 *****************************************************************************/

#define AXRADIO_IND_PHY_PN9                            1 
#define AXRADIO_IND_PHY_NRCHANNELS                     2                        
#define AXRADIO_IND_PHY_CHANFREQ                       3               
#define AXRADIO_IND_PHY_CHANPLLRNGINIT                 4           
#define AXRADIO_IND_PHY_CHANVCOIINIT                   5         
#define AXRADIO_IND_PHY_CHANPLLRNG                     6       
#define AXRADIO_IND_PHY_CHANVCOI                       7     
#define AXRADIO_IND_PHY_VCOCALIB                       8     
#define AXRADIO_IND_PHY_MAXFREQOFFSET                  9          
#define AXRADIO_IND_PHY_RSSIOFFSET                     10       
#define AXRADIO_IND_PHY_RSSIREFERENCE                  11          
#define AXRADIOPHY_CHANNELBUSY                         12   
#define AXRADIO_IND_PHY_CS_PERIOD                      13      
#define AXRADIO_IND_PHY_CS_ENABLED                     14       
#define AXRADIO_IND_PHY_LBT_RETRIES                    15        
#define AXRADIO_IND_PHY_LBT_FORCETX                    16        
#define AXRADIO_IND_PHY_PREAMBLE_WOR_LONGLEN           17                 
#define AXRADIO_IND_PHY_PREAMBLE_WOR_LEN               18             
#define AXRADIO_IND_PHY_PREAMBLE_LONGLEN               19             
#define AXRADIO_IND_PHY_PREAMBLE_LEN                   20         
#define AXRADIO_IND_PHY_PREAMBLE_BYTE                  21          
#define AXRADIO_IND_PHY_PREAMBLE_FLAGS                 22           
#define AXRADIO_IND_PHY_PREAMBLE_APPENDBITS            23                
#define AXRADIO_IND_PHY_PREAMBLE_APPENDPATTERN         24                   
#define AXRADIO_IND_FRAMING_MACLEN                     25       
#define AXRADIO_IND_FRAMING_ADDRLEN                    26        
#define AXRADIO_IND_FRAMING_DESTADDRPOS                27            
#define AXRADIO_IND_FRAMING_SOURCEADDRPOS              28              
#define AXRADIO_IND_FRAMING_LENPOS                     29       
#define AXRADIO_IND_FRAMING_LENOFFS                    30        
#define AXRADIO_IND_FRAMING_LENMASK                    31        
#define AXRADIO_IND_FRAMING_SWCRCLEN                   32         
#define AXRADIO_IND_FRAMING_SYNCLEN                    33        
#define AXRADIO_IND_FRAMING_SYNCWORD                   34         
#define AXRADIO_IND_FRAMING_SYNCFLAGS                  35          
#define AXRADIO_IND_FRAMING_ENABLE_SFDCALLBACK         36                   
#define AXRADIO_IND_FRAMING_ACK_TIMEOUT                37            
#define AXRADIO_IND_FRAMING_ACK_DELAY                  38          
#define AXRADIO_IND_FRAMING_ACK_RETRANSMISSIONS        39                    
#define AXRADIO_IND_FRAMING_ACK_SEQNRPOS               40             
#define AXRADIO_IND_FRAMING_MINPAYLOADLEN              41              
#define AXRADIO_IND_PHY_INNERFREQLOOP                  42 

/******************************************************************************
 ************************* Register values ************************************
 *****************************************************************************/
#define AX5043_REV                      0x51
#define AX5043_SCRATCH_TEST             0xAA

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

#define AX5043_RADIO_STATE_IDLE         0x0

#define AX5043_PLLVCOI_MANUAL           (1 << 7)

/**
 * Modem Domain Voltage Regulator Ready
 */
#define AX5043_SVMODEM                  (1 << 3)

/**
 * Init value for the VCO prior starting an autoranging
 */
#define AX5043_VCOR_INIT                8

#define AX5043_RFDIV0                   0x0
#define AX5043_RFDIV1                   (1 << 2)

#define AX5043_FREQSHAPE_EXT_FILTER     0x0
#define AX5043_FREQSHAPE_INVALID        0x1
#define AX5043_FREQSHAPE_GAUSSIAN_BT_03 0x2
#define AX5043_FREQSHAPE_GAUSSIAN_BT_05 0x3

/**
 *  FSK modulation mode
 */
#define AX5043_MODULATION_FSK           (1 << 3)

#define AX5043_ENC_INV                  1
#define AX5043_ENC_DIFF                 (1 << 1)
#define AX5043_ENC_SCRAM                (1 << 2)

/**
 * HDLC Framing mode
 */
#define AX5043_HDLC_FRAMING             (1 << 2)

/**
 * HDLC compliant CRC16
 */
#define AX5043_CRC16_CCITT              (1 << 4)

/**
 * FIFO commands
 */

#define AX5043_NOP_CMD                  0x0
#define AX5043_RSSI_CMD                 0x31
#define AX5043_TXCTRL_CMD               0x3C
#define AX5043_FREQOFFS_CMD             0x52
#define AX5043_ANTRSSI2_CMD             0x55
#define AX5043_REPEATDATA_CMD           0x62
#define AX5043_TIMER_CMD                0x70
#define AX5043_RFREQOFFS_CMD            0x73
#define AX5043_DATARATE_CMD             0x74
#define AX5043_ANTRSSI3_CMD             0x75
#define AX5043_DATA_CMD                 0xE1
#define AX5043_TXPWR_CMD                0xFD


//fifo commands
#define AX5043_FIFOCMD_NOP			0x00
#define AX5043_FIFOCMD_DATA			0x01
#define AX5043_FIFOCMD_REPEATDATA	0x02
#define AX5043_FIFOCMD_TIMER		0x10
#define AX5043_FIFOCMD_RSSI			0x11
#define AX5043_FIFOCMD_FREQOFFS		0x12
#define AX5043_FIFOCMD_RFFREQOFFS	0x13
#define AX5043_FIFOCMD_DATARATE		0x14
#define AX5043_FIFOCMD_ANTRSSI		0x15
#define AX5043_FIFOCMD_TXCTRL		0x1C
#define AX5043_FIFOCMD_TXPWR		0x1D



/**
 * Poweramp pin function, output/Z pull up for board 0.9 with diodes for 1.4V
 */
#define AX5043_POWERAMP_MODE_OUTPUT     (1 << 2) | 1)
#define AX5043_POWERAMP_MODE_PULLUP     ((1 << 7) | 1)
#define AX5043_POWERAMP_MODE_DAC        ((1 << 2) | 1)
/**
 * FIFO commit command
 */
#define AX5043_FIFO_COMMIT_CMD          (1 << 2)
#define AX5043_FIFO_PKTSTART            1
#define AX5043_FIFO_PKTEND              (1 << 1)
#define AX5043_FIFO_NOCRC               (1 << 3)
#define AX5043_FIFO_RAW                 (1 << 4)

/**
 * Maximum chuck that can be committed on the FIFO
 */
#define AX5043_PKTCHUNKSIZE_240         0xd

#define AX5043_FIFO_MAX_SIZE            240

/**
 * When this threshold of free bytes in the TX FIFO is reached,
 * an IRQ is raised
 */
#define AX5043_FIFO_FREE_THR            128

#define AX5043_IRQMFIFOTHRFREE          (1 << 3)
#define AX5043_IRQRFIFOTHRFREE          (1 << 3)
#define AX5043_IRQMRADIOCTRL            (1 << 6)
#define AX5043_REVMDONE                 0x1

/**
 * TX antenna transmission mode
 */
#define AX5043_TX_SINGLE_ENDED          0x2

/**
 * Radio confguration information
 */
#define CALLSIGN_STATION                (uint8_t*) "KG7ZVV"
#define CALLSIGN_DESTINATION            (uint8_t*) ""

#define APRS_UHF                        433800000
#define APRS_UHF_ALT                    432500000

/******************************************************************************
 ************************* RF Configuration ***********************************
 *****************************************************************************/
#define RX_FREQ_HZ                      433000000
#define TX_FREQ_HZ                      APRS_UHF

/**
 * Enables/Disables the appropriate setup for deployment on the devboards or
 * the
 */
#define PQWS_DEV_BOARD 0

/* Reference Oscillator frequency */
#if PQWS_DEV_BOARD
#define XTAL_FREQ_HZ                    48000000
#else
#define XTAL_FREQ_HZ                    26000000
#endif

/**
 * External PA Control
 */

#define AX5043_EXT_PA_ENABLE            0
#define AX5043_EXT_PA_DISABLE           1

/**
 * Ramp up/Ramp down period of the power amplifier in microseconds
 */
#define PWRAMP_RAMP_PERIOD_US           200

#define AX5043_RF_SWITCH_ENABLE         ANTSEL_OUTPUT_1
#define AX5043_RF_SWITCH_DISABLE        ANTSEL_OUTPUT_0


#define PKTDATA_BUFLEN 260


/**
 * Define error codes
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

#define	EXIT_FAILURE	1	// Failing exit status.  
#define	EXIT_SUCCESS	0	// Successful exit status. 

/**
 * Frequency mode A or B actually selects at which registers
 * the frequency configuration should be written.
 *
 * This is quite handy for different RX/TX frequencies, to avoid
 * writing every time the two different frequency configurations.
 */
typedef enum {
  FREQA_MODE = 0,               //!< FREQA_MODE
  FREQB_MODE = 1                //!< FREQB_MODE
} freq_mode_t;

typedef enum {
  VCO_INTERNAL = 0,
  VCO_EXTERNAL = 1
} vco_mode_t;

typedef enum
{
  POWERDOWN,
  DEEPSLEEP,
  STANDBY,
  FIFO_ENABLED,
  RECEIVE_MODE,
  RECEIVER_RUNNING,
  RECEIVER_WOR,
  TRANSMIT_MODE,
  FULLTX
} power_mode_t;

typedef enum
{
  ANTSEL_OUTPUT_0 = 0,
  ANTSEL_OUTPUT_1,
  ANTSEL_OUTPUT_Z,
  ANTSEL_OUTPUT_BB_TUBE_CLK,
  ANTSEL_OUTPUT_EXT_TCXO_EN,
  ANTSEL_OUTPUT_DAC,
  ANTSEL_OUTPUT_DIVERSITY,
  ANTSEL_OUTPUT_TEST_OBS
} pfantsel_t;


typedef enum
{
  PWRAMP_OUTPUT_0 = 0,
  PWRAMP_OUTPUT_1,
  PWRAMP_OUTPUT_Z,
  PWRAMP_INPUT_DiBit_SYNC,
  PWRAMP_OUTPUT_DiBit_SYNC,
  PWRAMP_OUTPUT_DAC,
  PWRAMP_OUTPUT_PA_CTRL,
  PWRAMP_OUTPUT_EXT_TCXO_EN,
  PWRAMP_OUTPUT_TEST_OBS,
} pfpwramp_t;

typedef enum
{
  AX5043_OK = 0,
  AX5043_INVALID_PARAM = 11,
  AX5043_TIMEOUT = 12,
  AX5043_NOT_FOUND = 13,
  AX5043_AUTORANGING_ERROR = 14
} ax5043_code_t;

typedef struct
{
  uint32_t tx_freq;
  uint32_t rx_freq;
  uint32_t f_xtal;
  uint8_t f_xtaldiv;
  uint32_t tx_baudrate;
  uint32_t rx_baudrate;
  SPIDriver *spi;
  uint8_t rf_init;
  freq_mode_t freqsel;
  vco_mode_t vco;
} ax5043_conf_t;


typedef enum {
    trxstate_off,
    trxstate_rx,
    trxstate_rxwor,
    trxstate_wait_xtal,
    trxstate_xtal_ready,
    trxstate_pll_ranging,
    trxstate_pll_ranging_done,
    trxstate_pll_settling,
    trxstate_pll_settled,
    trxstate_tx_xtalwait,
    trxstate_tx_longpreamble,
    trxstate_tx_shortpreamble,
    trxstate_tx_packet,
    trxstate_tx_waitdone,
    trxstate_txcw_xtalwait,
    trxstate_txstream_xtalwait,
    trxstate_txstream
} axradio_trxstate_t;


//! Structure containing a four byte X.25 address
typedef struct{
    uint8_t addr[4]; //!< Four byte X.25 address
}axradio_address_t;

typedef struct{
    uint8_t addr[4];
    uint8_t mask[4];
}axradio_address_mask_t;


//Structure for storing registers and other configuration details.
typedef struct{
    uint8_t reg_values[280];
    uint8_t config[43];
    uint8_t remoteaddr[4];
    uint8_t localaddr[4];
    uint8_t localadr_mask[4];
}axradio_config_t;

//function declaration starts here
uint8_t ax5043_write_reg(SPIDriver * spip, uint16_t reg, uint8_t value, uint8_t ret_value[]);
uint8_t ax5043_read_reg(SPIDriver * spip, uint16_t reg, uint8_t value, uint8_t ret_value[]);
void ax5043_shutdown(SPIDriver * spip);
void ax5043_standby(SPIDriver * spip);
void ax5043_fifo_en(SPIDriver * spip);
void ax5043_full_rx(SPIDriver * spip);
void ax5043_synth_tx(SPIDriver * spip);
void ax5043_full_tx(SPIDriver * spip);
void ax5043_set_addr(SPIDriver * spip, axradio_address_mask_t *local_addr);
void ax5043_reset(SPIDriver * spip);
void ax5043_writefifo(SPIDriver * spip,const uint8_t *ptr, uint8_t len);
uint8_t ax5043_readfifo(SPIDriver * spip, uint8_t axradio_rxbuffer[], uint8_t len);
void ax5043_writefifo(SPIDriver * spip,const uint8_t *ptr, uint8_t len);
uint8_t ax5043_readfifo(SPIDriver * spip, uint8_t axradio_rxbuffer[], uint8_t len) ;

#endif
//! @}
