/**
 * @file    ax5043.h
 * @brief   AX5043 Radio.
 *
 * @addtogroup AX5043
 * @ingroup ORESAT
 * @{
 */
#ifndef _AX5043_H_
#define _AX5043_H_

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

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
/* Revision and Interface Probing */
#define AX5043_REG_REVISION                 0x000U
#define AX5043_REG_SCRATCH                  0x001U

/* Operating Mode */
#define AX5043_REG_PWRMODE                  0x002U

/* Voltage Regulator */
#define AX5043_REG_POWSTAT                  0x003U
#define AX5043_REG_POWSTICKYSTAT            0x004U
#define AX5043_REG_POWIRQMASK               0x005U

/* Interrupt Control */
#define AX5043_REG_IRQMASK                  0x006U
#define AX5043_REG_IRQMASK1                 0x006U
#define AX5043_REG_IRQMASK0                 0x007U
#define AX5043_REG_RADIOEVENTMASK           0x008U
#define AX5043_REG_RADIOEVENTMASK1          0x008U
#define AX5043_REG_RADIOEVENTMASK0          0x009U
#define AX5043_REG_IRQINVERSION             0x00AU
#define AX5043_REG_IRQINVERSION1            0x00AU
#define AX5043_REG_IRQINVERSION0            0x00BU
#define AX5043_REG_IRQREQUEST               0x00CU
#define AX5043_REG_IRQREQUEST1              0x00CU
#define AX5043_REG_IRQREQUEST0              0x00DU
#define AX5043_REG_RADIOEVENTREQ            0x00EU
#define AX5043_REG_RADIOEVENTREQ1           0x00EU
#define AX5043_REG_RADIOEVENTREQ0           0x00FU

/* Modulation and Framing */
#define AX5043_REG_MODULATION               0x010U
#define AX5043_REG_ENCODING                 0x011U
#define AX5043_REG_FRAMING                  0x012U
#define AX5043_REG_CRCINIT                  0x014U
#define AX5043_REG_CRCINIT3                 0x014U
#define AX5043_REG_CRCINIT2                 0x015U
#define AX5043_REG_CRCINIT1                 0x016U
#define AX5043_REG_CRCINIT0                 0x017U

/* Forward Error Correction */
#define AX5043_REG_FEC                      0x018U
#define AX5043_REG_FECSYNC                  0x019U
#define AX5043_REG_FECSTATUS                0x01AU

/* Status */
#define AX5043_REG_RADIOSTATE               0x01CU
#define AX5043_REG_XTALSTATUS               0x01DU

/* Pin Configuration */
#define AX5043_REG_PINSTATE                 0x020U
#define AX5043_REG_PINFUNCSYSCLK            0x021U
#define AX5043_REG_PINFUNCDCLK              0x022U
#define AX5043_REG_PINFUNCDATA              0x023U
#define AX5043_REG_PINFUNCIRQ               0x024U
#define AX5043_REG_PINFUNCANTSEL            0x025U
#define AX5043_REG_PINFUNCPWRAMP            0x026U
#define AX5043_REG_PWRAMP                   0x027U

/* FIFO */
#define AX5043_REG_FIFOSTAT                 0x028U
#define AX5043_REG_FIFODATA                 0x029U
#define AX5043_REG_FIFOCOUNT                0x02AU
#define AX5043_REG_FIFOCOUNT1               0x02AU
#define AX5043_REG_FIFOCOUNT0               0x02BU
#define AX5043_REG_FIFOFREE                 0x02CU
#define AX5043_REG_FIFOFREE1                0x02CU
#define AX5043_REG_FIFOFREE0                0x02DU
#define AX5043_REG_FIFOTHRESH               0x02EU
#define AX5043_REG_FIFOTHRESH1              0x02EU
#define AX5043_REG_FIFOTHRESH0              0x02FU

/* Synthesizer */
#define AX5043_REG_PLLLOOP                  0x030U
#define AX5043_REG_PLLCPI                   0x031U
#define AX5043_REG_PLLVCODIV                0x032U
#define AX5043_REG_PLLRANGINGA              0x033U
#define AX5043_REG_FREQA                    0x034U
#define AX5043_REG_FREQA3                   0x034U
#define AX5043_REG_FREQA2                   0x035U
#define AX5043_REG_FREQA1                   0x036U
#define AX5043_REG_FREQA0                   0x037U
#define AX5043_REG_PLLLOOPBOOST             0x038U
#define AX5043_REG_PLLCPIBOOST              0x039U
#define AX5043_REG_PLLRANGINGB              0x03BU
#define AX5043_REG_FREQB                    0x03CU
#define AX5043_REG_FREQB3                   0x03CU
#define AX5043_REG_FREQB2                   0x03DU
#define AX5043_REG_FREQB1                   0x03EU
#define AX5043_REG_FREQB0                   0x03FU

/* Signal Strength */
#define AX5043_REG_RSSI                     0x040U
#define AX5043_REG_BGNDRSSI                 0x041U
#define AX5043_REG_DIVERSITY                0x042U
#define AX5043_REG_AGCCOUNTER               0x043U

/* Receiver Tracking */
#define AX5043_REG_TRKDATARATE              0x045U
#define AX5043_REG_TRKDATARATE2             0x045U
#define AX5043_REG_TRKDATARATE1             0x046U
#define AX5043_REG_TRKDATARATE0             0x047U
#define AX5043_REG_TRKAMPL                  0x048U
#define AX5043_REG_TRKAMPL1                 0x048U
#define AX5043_REG_TRKAMPL0                 0x049U
#define AX5043_REG_TRKPHASE                 0x04AU
#define AX5043_REG_TRKPHASE1                0x04AU
#define AX5043_REG_TRKPHASE0                0x04BU
#define AX5043_REG_TRKRFFREQ                0x04DU
#define AX5043_REG_TRKRFFREQ2               0x04DU
#define AX5043_REG_TRKRFFREQ1               0x04EU
#define AX5043_REG_TRKRFFREQ0               0x04FU
#define AX5043_REG_TRKFREQ                  0x050U
#define AX5043_REG_TRKFREQ1                 0x050U
#define AX5043_REG_TRKFREQ0                 0x051U
#define AX5043_REG_TRKFSKDEMOD              0x052U
#define AX5043_REG_TRKFSKDEMOD1             0x052U
#define AX5043_REG_TRKFSKDEMOD0             0x053U

/* Timers */
#define AX5043_REG_TIMER                    0x059U
#define AX5043_REG_TIMER2                   0x059U
#define AX5043_REG_TIMER1                   0x05AU
#define AX5043_REG_TIMER0                   0x05BU

/* Wakeup Timer */
#define AX5043_REG_WAKEUPTIMER              0x068U
#define AX5043_REG_WAKEUPTIMER1             0x068U
#define AX5043_REG_WAKEUPTIMER0             0x069U
#define AX5043_REG_WAKEUP                   0x06AU
#define AX5043_REG_WAKEUP1                  0x06AU
#define AX5043_REG_WAKEUP0                  0x06BU
#define AX5043_REG_WAKEUPFREQ               0x06CU
#define AX5043_REG_WAKEUPFREQ1              0x06CU
#define AX5043_REG_WAKEUPFREQ0              0x06DU
#define AX5043_REG_WAKEUPXOEARLY            0x06EU

/* PHY Layer Parameters */
/* Receiver Parameters */
#define AX5043_REG_IFFREQ                   0x100U
#define AX5043_REG_IFFREQ1                  0x100U
#define AX5043_REG_IFFREQ0                  0x101U
#define AX5043_REG_DECIMATION               0x102U
#define AX5043_REG_RXDATARATE               0x103U
#define AX5043_REG_RXDATARATE2              0x103U
#define AX5043_REG_RXDATARATE1              0x104U
#define AX5043_REG_RXDATARATE0              0x105U
#define AX5043_REG_MAXDROFFSET              0x106U
#define AX5043_REG_MAXDROFFSET2             0x106U
#define AX5043_REG_MAXDROFFSET1             0x107U
#define AX5043_REG_MAXDROFFSET0             0x108U
#define AX5043_REG_MAXRFOFFSET              0x109U
#define AX5043_REG_MAXRFOFFSET2             0x109U
#define AX5043_REG_MAXRFOFFSET1             0x10AU
#define AX5043_REG_MAXRFOFFSET0             0x10BU
#define AX5043_REG_FSKDMAX                  0x10CU
#define AX5043_REG_FSKDMAX1                 0x10CU
#define AX5043_REG_FSKDMAX0                 0x10DU
#define AX5043_REG_FSKDMIN                  0x10EU
#define AX5043_REG_FSKDMIN1                 0x10EU
#define AX5043_REG_FSKDMIN0                 0x10FU
#define AX5043_REG_AFSKSPACE                0x110U
#define AX5043_REG_AFSKSPACE1               0x110U
#define AX5043_REG_AFSKSPACE0               0x111U
#define AX5043_REG_AFSKMARK                 0x112U
#define AX5043_REG_AFSKMARK1                0x112U
#define AX5043_REG_AFSKMARK0                0x113U
#define AX5043_REG_AFSKCTRL                 0x114U
#define AX5043_REG_AMPLFILTER               0x115U
#define AX5043_REG_FREQUENCYLEAK            0x116U
#define AX5043_REG_RXPARAMSETS              0x117U
#define AX5043_REG_RXPARAMCURSET            0x118U

/* Receiver Parameter Set 0 */
#define AX5043_REG_AGCGAIN0                 0x120U
#define AX5043_REG_AGCTARGET0               0x121U
#define AX5043_REG_AGCAHYST0                0x122U
#define AX5043_REG_AGCMINMAX0               0x123U
#define AX5043_REG_TIMEGAIN0                0x124U
#define AX5043_REG_DRGAIN0                  0x125U
#define AX5043_REG_PHASEGAIN0               0x126U
#define AX5043_REG_FREQGAINA0               0x127U
#define AX5043_REG_FREQGAINB0               0x128U
#define AX5043_REG_FREQGAINC0               0x129U
#define AX5043_REG_FREQGAIND0               0x12AU
#define AX5043_REG_AMPLGAIN0                0x12BU
#define AX5043_REG_FREQDEV0                 0x12CU
#define AX5043_REG_FREQDEV10                0x12CU
#define AX5043_REG_FREQDEV00                0x12DU
#define AX5043_REG_FOURFSK0                 0x12EU
#define AX5043_REG_BBOFFSRES0               0x12FU

/* Receiver Parameter Set 1 */
#define AX5043_REG_AGCGAIN1                 0x130U
#define AX5043_REG_AGCTARGET1               0x131U
#define AX5043_REG_AGCAHYST1                0x132U
#define AX5043_REG_AGCMINMAX1               0x133U
#define AX5043_REG_TIMEGAIN1                0x134U
#define AX5043_REG_DRGAIN1                  0x135U
#define AX5043_REG_PHASEGAIN1               0x136U
#define AX5043_REG_FREQGAINA1               0x137U
#define AX5043_REG_FREQGAINB1               0x138U
#define AX5043_REG_FREQGAINC1               0x139U
#define AX5043_REG_FREQGAIND1               0x13AU
#define AX5043_REG_AMPLGAIN1                0x13BU
#define AX5043_REG_FREQDEV1                 0x13CU
#define AX5043_REG_FREQDEV11                0x13CU
#define AX5043_REG_FREQDEV01                0x13DU
#define AX5043_REG_FOURFSK1                 0x13EU
#define AX5043_REG_BBOFFSRES1               0x13FU

/* Receiver Parameter Set 2 */
#define AX5043_REG_AGCGAIN2                 0x140U
#define AX5043_REG_AGCTARGET2               0x141U
#define AX5043_REG_AGCAHYST2                0x142U
#define AX5043_REG_AGCMINMAX2               0x143U
#define AX5043_REG_TIMEGAIN2                0x144U
#define AX5043_REG_DRGAIN2                  0x145U
#define AX5043_REG_PHASEGAIN2               0x146U
#define AX5043_REG_FREQGAINA2               0x147U
#define AX5043_REG_FREQGAINB2               0x148U
#define AX5043_REG_FREQGAINC2               0x149U
#define AX5043_REG_FREQGAIND2               0x14AU
#define AX5043_REG_AMPLGAIN2                0x14BU
#define AX5043_REG_FREQDEV2                 0x14CU
#define AX5043_REG_FREQDEV12                0x14CU
#define AX5043_REG_FREQDEV02                0x14DU
#define AX5043_REG_FOURFSK2                 0x14EU
#define AX5043_REG_BBOFFSRES2               0x14FU

/* Receiver Parameter Set 3 */
#define AX5043_REG_AGCGAIN3                 0x150U
#define AX5043_REG_AGCTARGET3               0x151U
#define AX5043_REG_AGCAHYST3                0x152U
#define AX5043_REG_AGCMINMAX3               0x153U
#define AX5043_REG_TIMEGAIN3                0x154U
#define AX5043_REG_DRGAIN3                  0x155U
#define AX5043_REG_PHASEGAIN3               0x156U
#define AX5043_REG_FREQGAINA3               0x157U
#define AX5043_REG_FREQGAINB3               0x158U
#define AX5043_REG_FREQGAINC3               0x159U
#define AX5043_REG_FREQGAIND3               0x15AU
#define AX5043_REG_AMPLGAIN3                0x15BU
#define AX5043_REG_FREQDEV3                 0x15CU
#define AX5043_REG_FREQDEV13                0x15CU
#define AX5043_REG_FREQDEV03                0x15DU
#define AX5043_REG_FOURFSK3                 0x15EU
#define AX5043_REG_BBOFFSRES3               0x15FU

/* Transmitter Parameters */
#define AX5043_REG_MODCFGF                  0x160U
#define AX5043_REG_FSKDEV                   0x161U
#define AX5043_REG_FSKDEV2                  0x161U
#define AX5043_REG_FSKDEV1                  0x162U
#define AX5043_REG_FSKDEV0                  0x163U
#define AX5043_REG_MODCFGA                  0x164U
#define AX5043_REG_TXRATE                   0x165U
#define AX5043_REG_TXRATE2                  0x165U
#define AX5043_REG_TXRATE1                  0x166U
#define AX5043_REG_TXRATE0                  0x167U
#define AX5043_REG_TXPWRCOEFFA              0x168U
#define AX5043_REG_TXPWRCOEFFA1             0x168U
#define AX5043_REG_TXPWRCOEFFA0             0x169U
#define AX5043_REG_TXPWRCOEFFB              0x16AU
#define AX5043_REG_TXPWRCOEFFB1             0x16AU
#define AX5043_REG_TXPWRCOEFFB0             0x16BU
#define AX5043_REG_TXPWRCOEFFC              0x16CU
#define AX5043_REG_TXPWRCOEFFC1             0x16CU
#define AX5043_REG_TXPWRCOEFFC0             0x16DU
#define AX5043_REG_TXPWRCOEFFD              0x16EU
#define AX5043_REG_TXPWRCOEFFD1             0x16EU
#define AX5043_REG_TXPWRCOEFFD0             0x16FU
#define AX5043_REG_TXPWRCOEFFE              0x170U
#define AX5043_REG_TXPWRCOEFFE1             0x170U
#define AX5043_REG_TXPWRCOEFFE0             0x171U

/* PLL Parameters */
#define AX5043_REG_PLLVCOI                  0x180U
#define AX5043_REG_PLLVCOIR                 0x181U
#define AX5043_REG_PLLLOCKDET               0x182U
#define AX5043_REG_PLLRNGCLK                0x183U

/* Crystal Oscillator */
#define AX5043_REG_XTALCAP                  0x184U

/* Baseband */
#define AX5043_REG_BBTUNE                   0x188U
#define AX5043_REG_BBOFFSCAP                0x189U

/* MAC Layer Parameters */
/* Packet Format */
#define AX5043_REG_PKTADDRCFG               0x200U
#define AX5043_REG_PKTLENCFG                0x201U
#define AX5043_REG_PKTLENOFFSET             0x202U
#define AX5043_REG_PKTMAXLEN                0x203U
#define AX5043_REG_PKTADDR                  0x204U
#define AX5043_REG_PKTADDR3                 0x204U
#define AX5043_REG_PKTADDR2                 0x205U
#define AX5043_REG_PKTADDR1                 0x206U
#define AX5043_REG_PKTADDR0                 0x207U
#define AX5043_REG_PKTADDRMASK              0x208U
#define AX5043_REG_PKTADDRMASK3             0x208U
#define AX5043_REG_PKTADDRMASK2             0x209U
#define AX5043_REG_PKTADDRMASK1             0x20AU
#define AX5043_REG_PKTADDRMASK0             0x20BU

/* Pattern Match */
#define AX5043_REG_MATCH0PAT                0x210U
#define AX5043_REG_MATCH0PAT3               0x210U
#define AX5043_REG_MATCH0PAT2               0x211U
#define AX5043_REG_MATCH0PAT1               0x212U
#define AX5043_REG_MATCH0PAT0               0x213U
#define AX5043_REG_MATCH0LEN                0x214U
#define AX5043_REG_MATCH0MIN                0x215U
#define AX5043_REG_MATCH0MAX                0x216U
#define AX5043_REG_MATCH1PAT                0x218U
#define AX5043_REG_MATCH1PAT1               0x218U
#define AX5043_REG_MATCH1PAT0               0x219U
#define AX5043_REG_MATCH1LEN                0x21CU
#define AX5043_REG_MATCH1MIN                0x21DU
#define AX5043_REG_MATCH1MAX                0x21EU

/* Packet Controller */
#define AX5043_REG_TMGTXBOOST               0x220U
#define AX5043_REG_TMGTXSETTLE              0x221U
#define AX5043_REG_TMGRXBOOST               0x223U
#define AX5043_REG_TMGRXSETTLE              0x224U
#define AX5043_REG_TMGRXOFFSACQ             0x225U
#define AX5043_REG_TMGRXCOARSEAGC           0x226U
#define AX5043_REG_TMGRXAGC                 0x227U
#define AX5043_REG_TMGRXRSSI                0x228U
#define AX5043_REG_TMGRXPREAMBLE1           0x229U
#define AX5043_REG_TMGRXPREAMBLE2           0x22AU
#define AX5043_REG_TMGRXPREAMBLE3           0x22BU
#define AX5043_REG_RSSIREFERENCE            0x22CU
#define AX5043_REG_RSSIABSTHR               0x22DU
#define AX5043_REG_BGNDRSSIGAIN             0x22EU
#define AX5043_REG_BGNDRSSITHR              0x22FU
#define AX5043_REG_PKTCHUNKSIZE             0x230U
#define AX5043_REG_PKTMISCFLAGS             0x231U
#define AX5043_REG_PKTSTOREFLAGS            0x232U
#define AX5043_REG_PKTACCEPTFLAGS           0x233U

/* General Purpose ADC */
#define AX5043_REG_GPADCCTRL                0x300U
#define AX5043_REG_GPADCPERIOD              0x301U
#define AX5043_REG_GPADC13VALUE             0x308U
#define AX5043_REG_GPADC13VALUE1            0x308U
#define AX5043_REG_GPADC13VALUE0            0x309U

/* Low Power Oscillator Calibration */
#define AX5043_REG_LPOSCCONFIG              0x310U
#define AX5043_REG_LPOSCSTATUS              0x311U
#define AX5043_REG_LPOSCKFILT               0x312U
#define AX5043_REG_LPOSCKFILT1              0x312U
#define AX5043_REG_LPOSCKFILT0              0x313U
#define AX5043_REG_LPOSCREF                 0x314U
#define AX5043_REG_LPOSCREF1                0x314U
#define AX5043_REG_LPOSCREF0                0x315U
#define AX5043_REG_LPOSCFREQ                0x316U
#define AX5043_REG_LPOSCFREQ1               0x316U
#define AX5043_REG_LPOSCFREQ0               0x317U
#define AX5043_REG_LPOSCPER                 0x318U
#define AX5043_REG_LPOSCPER1                0x318U
#define AX5043_REG_LPOSCPER0                0x319U

/* DAC */
#define AX5043_REG_DACVALUE                 0x330U
#define AX5043_REG_DACVALUE1                0x330U
#define AX5043_REG_DACVALUE0                0x331U
#define AX5043_REG_DACCONFIG                0x332U

/* Performance Tuning Registers */
#define AX5043_REG_0xF00                    0xF00U
#define AX5043_REG_0xF0C                    0xF0CU
#define AX5043_REG_0xF0D                    0xF0DU
#define AX5043_REG_0xF10                    0xF10U
#define AX5043_REG_XTALOSC                  0xF10U
#define AX5043_REG_0xF11                    0xF11U
#define AX5043_REG_XTALAMPL                 0xF11U
#define AX5043_REG_0xF18                    0xF18U
#define AX5043_REG_0xF1C                    0xF1CU
#define AX5043_REG_0xF21                    0xF21U
#define AX5043_REG_0xF22                    0xF22U
#define AX5043_REG_0xF23                    0xF23U
#define AX5043_REG_0xF26                    0xF26U
#define AX5043_REG_0xF30                    0xF30U
#define AX5043_REG_0xF31                    0xF31U
#define AX5043_REG_0xF32                    0xF32U
#define AX5043_REG_0xF33                    0xF33U
#define AX5043_REG_0xF34                    0xF34U
#define AX5043_REG_0xF35                    0xF35U
#define AX5043_REG_XTALDIV                  0xF35U
#define AX5043_REG_0xF44                    0xF44U
#define AX5043_REG_0xF72                    0xF72U
/** @} */

/**
 * @name    AX5043 REVISION register
 * @{
 */
#define AX5043_REVISION_Pos                 (0U)
#define AX5043_REVISION_Msk                 (0xFFU << AX5043_REVISION_Pos)
#define AX5043_REVISION                     AX5043_REVISION_Msk
/** @} */

/**
 * @name    AX5043 SCRATCH register
 * @{
 */
#define AX5043_SCRATCH_Pos                  (0U)
#define AX5043_SCRATCH_Msk                  (0xFFU << AX5043_SCRATCH_Pos)
#define AX5043_SCRATCH                      AX5043_SCRATCH_Msk
/** @} */

/**
 * @name    AX5043 PWRMODE register fields
 * @{
 */
#define AX5043_PWRMODE_Pos                  (0U)
#define AX5043_PWRMODE_Msk                  (0xFU << AX5043_PWRMODE_Pos)
#define AX5043_PWRMODE                      AX5043_PWRMODE_Msk
#define AX5043_PWRMODE_POWERDOWN            (0x0U)
#define AX5043_PWRMODE_DEEPSLEEP            (0x1U)
#define AX5043_PWRMODE_STANDBY              (0x5U)
#define AX5043_PWRMODE_FIFO_EN              (0x7U)
#define AX5043_PWRMODE_RX_SYNTH             (0x8U)
#define AX5043_PWRMODE_RX_FULL              (0x9U)
#define AX5043_PWRMODE_RX_WOR               (0xBU)
#define AX5043_PWRMODE_TX_SYNTH             (0xCU)
#define AX5043_PWRMODE_TX_FULL              (0xDU)
#define AX5043_PWRMODE_WDS_Pos              (4U)
#define AX5043_PWRMODE_WDS_Msk              (0x1U << AX5043_PWRMODE_WDS_Pos)
#define AX5043_PWRMODE_WDS                  AX5043_PWRMODE_WDS_Msk
#define AX5043_PWRMODE_REFEN_Pos            (5U)
#define AX5043_PWRMODE_REFEN_Msk            (0x1U << AX5043_PWRMODE_REFEN_Pos)
#define AX5043_PWRMODE_REFEN                AX5043_PWRMODE_REFEN_Msk
#define AX5043_PWRMODE_XOEN_Pos             (6U)
#define AX5043_PWRMODE_XOEN_Msk             (0x1U << AX5043_PWRMODE_XOEN_Pos)
#define AX5043_PWRMODE_XOEN                 AX5043_PWRMODE_XOEN_Msk
#define AX5043_PWRMODE_RESET_Pos            (7U)
#define AX5043_PWRMODE_RESET_Msk            (0x1U << AX5043_PWRMODE_RESET_Pos)
#define AX5043_PWRMODE_RESET                AX5043_PWRMODE_RESET_Msk
/** @} */

/**
 * @name    AX5043 POWSTAT/POWSTICKYSTAT/POWIRQMASK register fields
 * @{
 */
#define AX5043_POWIRQ_SVIO_Pos              (0U)
#define AX5043_POWIRQ_SVIOgsk               (0x1U << AX5043_POWIRQ_MSVIO_Pos)
#define AX5043_POWIRQ_SVIO                  AX5043_POWIRQgSVIO_Msk
#define AX5043_POWIRQ_SBEVMODEM_Pos         (1U)
#define AX5043_POWIRQ_SBEVMODEMgsk          (0x1U << AX5043_POWIRQ_MSBEVMODEM_Pos)
#define AX5043_POWIRQ_SBEVMODEM             AX5043_POWIRQgSBEVMODEM_Msk
#define AX5043_POWIRQ_SBEVANA_Pos           (2U)
#define AX5043_POWIRQ_SBEVANAgsk            (0x1U << AX5043_POWIRQ_MSBEVANA_Pos)
#define AX5043_POWIRQ_SBEVANA               AX5043_POWIRQgSBEVANA_Msk
#define AX5043_POWIRQ_SVMODEM_Pos           (3U)
#define AX5043_POWIRQ_SVMODEMgsk            (0x1U << AX5043_POWIRQ_MSVMODEM_Pos)
#define AX5043_POWIRQ_SVMODEM               AX5043_POWIRQgSVMODEM_Msk
#define AX5043_POWIRQ_SVANA_Pos             (4U)
#define AX5043_POWIRQ_SVANAgsk              (0x1U << AX5043_POWIRQ_MSVANA_Pos)
#define AX5043_POWIRQ_SVANA                 AX5043_POWIRQgSVANA_Msk
#define AX5043_POWIRQ_SVREF_Pos             (5U)
#define AX5043_POWIRQ_SVREFgsk              (0x1U << AX5043_POWIRQ_MSVREF_Pos)
#define AX5043_POWIRQ_SVREF                 AX5043_POWIRQ_SMVREFgsk
#define AX5043_POWIRQ_SREF_Pos              (6U)
#define AX5043_POWIRQ_SREFgsk               (0x1U << AX5043_POWIRQ_MSREF_Pos)
#define AX5043_POWIRQ_SREF                  AX5043_POWIRQgSREF_Msk
#define AX5043_POWIRQ_PWRGOOD_Pos           (7U)
#define AX5043_POWIRQ_PWRGOODgsk            (0x1U << AX5043_POWIRQ_MPWRGOOD_Pos)
#define AX5043_POWIRQ_PWRGOOD               AX5043_POWIRQgPWRGOOD_Msk
/** @} */

/**
 * @name    AX5043 IRQMASK/IRQINVERSION/IRQREQUEST register fields
 * @{
 */
#define AX5043_IRQ_FIFONOTEMPTY_Pos         (0U)
#define AX5043_IRQ_FIFONOTEMPTY_Msk         (0x1U << AX5043_IRQ_FIFONOTEMPTY_Pos)
#define AX5043_IRQ_FIFONOTEMPTY             AX5043_IRQ_FIFONOTEMPTY_Msk
#define AX5043_IRQ_FIFONOTFULL_Pos          (1U)
#define AX5043_IRQ_FIFONOTFULL_Msk          (0x1U << AX5043_IRQ_FIFONOTFULL_Pos)
#define AX5043_IRQ_FIFONOTFULL              AX5043_IRQ_FIFONOTFULL_Msk
#define AX5043_IRQ_FIFOTHRCNT_Pos           (2U)
#define AX5043_IRQ_FIFOTHRCNT_Msk           (0x1U << AX5043_IRQ_FIFOTHRCNT_Pos)
#define AX5043_IRQ_FIFOTHRCNT               AX5043_IRQ_FIFOTHRCNT_Msk
#define AX5043_IRQ_FIFOTHRFREE_Pos          (3U)
#define AX5043_IRQ_FIFOTHRFREE_Msk          (0x1U << AX5043_IRQ_FIFOTHRFREE_Pos)
#define AX5043_IRQ_FIFOTHRFREE              AX5043_IRQ_FIFOTHRFREE_Msk
#define AX5043_IRQ_FIFOERROR_Pos            (4U)
#define AX5043_IRQ_FIFOERROR_Msk            (0x1U << AX5043_IRQ_FIFOERROR_Pos)
#define AX5043_IRQ_FIFOERROR                AX5043_IRQ_FIFOERROR_Msk
#define AX5043_IRQ_PLLUNLOCK_Pos            (5U)
#define AX5043_IRQ_PLLUNLOCK_Msk            (0x1U << AX5043_IRQ_PLLUNLOCK_Pos)
#define AX5043_IRQ_PLLUNLOCK                AX5043_IRQ_PLLUNLOCK_Msk
#define AX5043_IRQ_RADIOCTRL_Pos            (6U)
#define AX5043_IRQ_RADIOCTRL_Msk            (0x1U << AX5043_IRQ_RADIOCTRL_Pos)
#define AX5043_IRQ_RADIOCTRL                AX5043_IRQ_RADIOCTRL_Msk
#define AX5043_IRQ_POWER_Pos                (7U)
#define AX5043_IRQ_POWER_Msk                (0x1U << AX5043_IRQ_POWER_Pos)
#define AX5043_IRQ_POWER                    AX5043_IRQ_POWER_Msk
#define AX5043_IRQ_XTALREADY_Pos            (8U)
#define AX5043_IRQ_XTALREADY_Msk            (0x1U << AX5043_IRQ_XTALREADY_Pos)
#define AX5043_IRQ_XTALREADY                AX5043_IRQ_XTALREADY_Msk
#define AX5043_IRQ_WAKEUPTIMER_Pos          (9U)
#define AX5043_IRQ_WAKEUPTIMER_Msk          (0x1U << AX5043_IRQ_WAKEUPTIMER_Pos)
#define AX5043_IRQ_WAKEUPTIMER              AX5043_IRQ_WAKEUPTIMER_Msk
#define AX5043_IRQ_LPOSC_Pos                (10U)
#define AX5043_IRQ_LPOSC_Msk                (0x1U << AX5043_IRQ_LPOSC_Pos)
#define AX5043_IRQ_LPOSC                    AX5043_IRQ_LPOSC_Msk
#define AX5043_IRQ_GPADC_Pos                (11U)
#define AX5043_IRQ_GPADC_Msk                (0x1U << AX5043_IRQ_GPADC_Pos)
#define AX5043_IRQ_GPADC                    AX5043_IRQ_GPADC_Msk
#define AX5043_IRQ_PLLRNGDONE_Pos           (12U)
#define AX5043_IRQ_PLLRNGDONE_Msk           (0x1U << AX5043_IRQ_PLLRNGDONE_Pos)
#define AX5043_IRQ_PLLRNGDONE               AX5043_IRQ_PLLRNGDONE_Msk
/** @} */

/**
 * @name    AX5043 RADIOEVENTMASK/RADIOEVENTREQ register fields
 * @{
 */
#define AX5043_RADIOEVENT_DONE_Pos          (0U)
#define AX5043_RADIOEVENT_DONE_Msk          (0x1U << AX5043_RADIOEVENT_DONE_Pos)
#define AX5043_RADIOEVENT_DONE              AX5043_RADIOEVENT_DONE_Msk
#define AX5043_RADIOEVENT_SETTLED_Pos       (1U)
#define AX5043_RADIOEVENT_SETTLED_Msk       (0x1U << AX5043_RADIOEVENT_SETTLED_Pos)
#define AX5043_RADIOEVENT_SETTLED           AX5043_RADIOEVENT_SETTLED_Msk
#define AX5043_RADIOEVENT_RADIOSTATECHG_Pos (2U)
#define AX5043_RADIOEVENT_RADIOSTATECHG_Msk (0x1U << AX5043_RADIOEVENT_RADIOSTATECHG_Pos)
#define AX5043_RADIOEVENT_RADIOSTATECHG     AX5043_RADIOEVENT_RADIOSTATECHG_Msk
#define AX5043_RADIOEVENT_RXPARAMSETCHG_Pos (3U)
#define AX5043_RADIOEVENT_RXPARAMSETCHG_Msk (0x1U << AX5043_RADIOEVENT_RXPARAMSETCHG_Pos)
#define AX5043_RADIOEVENT_RXPARAMSETCHG     AX5043_RADIOEVENT_RXPARAMSETCHG_Msk
#define AX5043_RADIOEVENT_FRAMECLK_Pos      (4U)
#define AX5043_RADIOEVENT_FRAMECLK_Msk      (0x1U << AX5043_RADIOEVENT_FRAMECLK_Pos)
#define AX5043_RADIOEVENT_FRAMECLK          AX5043_RADIOEVENT_FRAMECLK_Msk
/** @} */

/**
 * @name    AX5043 MODULATION register fields
 * @{
 */
#define AX5043_MODULATION_Pos               (0U)
#define AX5043_MODULATION_Msk               (0xFU << AX5043_MODULATION_Pos)
#define AX5043_MODULATION                   AX5043_MODULATION_Msk
#define AX5043_MODULATION_ASK               (0x0U)
#define AX5043_MODULATION_ASK_COHERENT      (0x1U)
#define AX5043_MODULATION_PSK               (0x4U)
#define AX5043_MODULATION_OQSK              (0x6U)
#define AX5043_MODULATION_MSK               (0x7U)
#define AX5043_MODULATION_FSK               (0x8U)
#define AX5043_MODULATION_4FSK              (0x9U)
#define AX5043_MODULATION_AFSK              (0xAU)
#define AX5043_MODULATION_FM                (0xBU)
#define AX5043_MODULATION_RXHALFSPEED_Pos   (4U)
#define AX5043_MODULATION_RXHALFSPEED_Msk   (0x1U << AX5043_MODULATION_RXHALFSPEED_Pos)
#define AX5043_MODULATION_RXHALFSPEED       AX5043_MODULATION_RXHALFSPEED_Msk
/** @} */

/**
 * @name    AX5043 ENCODING register fields
 * @{
 */
#define AX5043_ENCODING_Pos                 (0U)
#define AX5043_ENCODING_Msk                 (0xFU << AX5043_ENCODING_Pos)
#define AX5043_ENCODING                     AX5043_ENCODING_Msk
#define AX5043_ENCODING_INV_Pos             (0U)
#define AX5043_ENCODING_INV_Msk             (0x1U << AX5043_ENCODING_INV_Pos)
#define AX5043_ENCODING_INV                 AX5043_ENCODING_INV_Msk
#define AX5043_ENCODING_DIFF_Pos            (1U)
#define AX5043_ENCODING_DIFF_Msk            (0x1U << AX5043_ENCODING_DIFF_Pos)
#define AX5043_ENCODING_DIFF                AX5043_ENCODING_DIFF_Msk
#define AX5043_ENCODING_SCRAM_Pos           (2U)
#define AX5043_ENCODING_SCRAM_Msk           (0x1U << AX5043_ENCODING_SCRAM_Pos)
#define AX5043_ENCODING_SCRAM               AX5043_ENCODING_SCRAM_Msk
#define AX5043_ENCODING_MANCH_Pos           (3U)
#define AX5043_ENCODING_MANCH_Msk           (0x1U << AX5043_ENCODING_MANCH_Pos)
#define AX5043_ENCODING_MANCH               AX5043_ENCODING_MANCH_Msk
#define AX5043_ENCODING_NOSYNC_Pos          (4U)
#define AX5043_ENCODING_NOSYNC_Msk          (0x1U << AX5043_ENCODING_NOSYNC_Pos)
#define AX5043_ENCODING_NOSYNC              AX5043_ENCODING_NOSYNC_Msk
/* Customary Encodings */
#define AX5043_ENCODING_NRZ                 (0x0U)  /* MANCH=0 SCRAM=0 DIFF=0 INV=0 */
#define AX5043_ENCODING_NRZI                (0x3U)  /* MANCH=0 SCRAM=0 DIFF=1 INV=1 */
#define AX5043_ENCODING_NRZ_SCRAM           (0x4U)  /* MANCH=0 SCRAM=1 DIFF=0 INV=0 */
#define AX5043_ENCODING_NRZI_SCRAM          (0x7U)  /* MANCH=0 SCRAM=1 DIFF=1 INV=1 */
#define AX5043_ENCODING_MANCHESTER          (0x8U)  /* MANCH=1 SCRAM=0 DIFF=0 INV=0 */
#define AX5043_ENCODING_FM0                 (0xAU)  /* MANCH=1 SCRAM=0 DIFF=1 INV=0 */
#define AX5043_ENCODING_FM1                 (0xBU)  /* MANCH=1 SCRAM=0 DIFF=1 INV=1 */
/** @} */

/**
 * @name    AX5043 FRAMING register fields
 * @{
 */
#define AX5043_FRAMING_FABORT_Pos           (0U)
#define AX5043_FRAMING_FABORT_Msk           (0x1U << AX5043_FRAMING_FABORT_Pos)
#define AX5043_FRAMING_FABORT               AX5043_FRAMING_FABORT_Msk
#define AX5043_FRAMING_FRMMODE_Pos          (1U)
#define AX5043_FRAMING_FRMMODE_Msk          (0x7U << AX5043_FRAMING_FRMMODE_Pos)
#define AX5043_FRAMING_FRMMODE              AX5043_FRAMING_FRMMODE_Msk
#define AX5043_FRMMODE_RAW                  (0x0U)
#define AX5043_FRMMODE_RAW_SOFTBITS         (0x1U)
#define AX5043_FRMMODE_HDLC                 (0x2U)
#define AX5043_FRMMODE_RAW_PATMATCH         (0x3U)
#define AX5043_FRMMODE_WMBUS                (0x4U)
#define AX5043_FRMMODE_WMBUS_4TO6           (0x5U)
#define AX5043_FRAMING_CRCMODE_Pos          (4U)
#define AX5043_FRAMING_CRCMODE_Msk          (0x7U << AX5043_FRAMING_CRCMODE_Pos)
#define AX5043_FRAMING_CRCMODE              AX5043_FRAMING_CRCMODE_Msk
#define AX5043_CRCMODE_OFF                  (0x0U)
#define AX5043_CRCMODE_CCITT                (0x1U)
#define AX5043_CRCMODE_CRC16                (0x2U)
#define AX5043_CRCMODE_DNP                  (0x3U)
#define AX5043_CRCMODE_CRC32                (0x6U)
#define AX5043_FRAMING_FRMRX_Pos            (7U)
#define AX5043_FRAMING_FRMRX_Msk            (0x1U << AX5043_FRAMING_FRMRX_Pos)
#define AX5043_FRAMING_FRMRX                AX5043_FRAMING_FRMRX_Msk
/** @} */

/**
 * @name    AX5043 CRCINIT register fields
 * @{
 */
#define AX5043_CRCINIT_Pos                  (0U)
#define AX5043_CRCINIT_Msk                  (0xFFFFFFFFU << AX5043_CRCINIT_Pos)
#define AX5043_CRCINIT                      AX5043_CRCINIT_Msk
/** @} */

/**
 * @name    AX5043 FEC register fields
 * @{
 */
#define AX5043_FEC_FECENA_Pos               (0U)
#define AX5043_FEC_FECENA_Msk               (0x1U << AX5043_FEC_FECENA_Pos)
#define AX5043_FEC_FECENA                   AX5043_FEC_FECENA_Msk
#define AX5043_FEC_FECINPSHIFT_Pos          (1U)
#define AX5043_FEC_FECINPSHIFT_Msk          (0x7U << AX5043_FEC_FECINPSHIFT_Pos)
#define AX5043_FEC_FECINPSHIFT              AX5043_FEC_FECINPSHIFT_Msk
#define AX5043_FEC_FECPOS_Pos               (4U)
#define AX5043_FEC_FECPOS_Msk               (0x1U << AX5043_FEC_FECPOS_Pos)
#define AX5043_FEC_FECPOS                   AX5043_FEC_FECPOS_Msk
#define AX5043_FEC_FECNEG_Pos               (5U)
#define AX5043_FEC_FECNEG_Msk               (0x1U << AX5043_FEC_FECNEG_Pos)
#define AX5043_FEC_FECNEG                   AX5043_FEC_FECNEG_Msk
#define AX5043_FEC_RSTVITERBI_Pos           (6U)
#define AX5043_FEC_RSTVITERBI_Msk           (0x1U << AX5043_FEC_RSTVITERBI_Pos)
#define AX5043_FEC_RSTVITERBI               AX5043_FEC_RSTVITERBI_Msk
#define AX5043_FEC_SHORTMEM_Pos             (7U)
#define AX5043_FEC_SHORTMEM_Msk             (0x1U << AX5043_FEC_SHORTMEM_Pos)
#define AX5043_FEC_SHORTMEM                 AX5043_FEC_SHORTMEM_Msk
/** @} */

/**
 * @name    AX5043 FECSYNC register fields
 * @{
 */
#define AX5043_FECSYNC_Pos                  (0U)
#define AX5043_FECSYNC_Msk                  (0xFFU << AX5043_FECSYNC_Pos)
#define AX5043_FECSYNC                      AX5043_FECSYNC_Msk
/** @} */

/**
 * @name    AX5043 FECSTATUS register fields
 * @{
 */
#define AX5043_FECSTATUS_MAXMETRIC_Pos      (0U)
#define AX5043_FECSTATUS_MAXMETRIC_Msk      (0x7FU << AX5043_FECSTATUS_MAXMETRIC_Pos)
#define AX5043_FECSTATUS_MAXMETRIC          AX5043_FECSTATUS_MAXMETRIC_Msk
#define AX5043_FECSTATUS_FECINV_Pos         (7U)
#define AX5043_FECSTATUS_FECINV_Msk         (0x1U << AX5043_FECSTATUS_FECINV_Pos)
#define AX5043_FECSTATUS_FECINV             AX5043_FECSTATUS_FECINV_Msk
/** @} */

/**
 * @name    AX5043 RADIOSTATE register fields
 * @{
 */
#define AX5043_RADIOSTATE_Pos               (0U)
#define AX5043_RADIOSTATE_Msk               (0xFU << AX5043_RADIOSTATE_Pos)
#define AX5043_RADIOSTATE                   AX5043_RADIOSTATE_Msk
#define AX5043_RADIOSTATE_IDLE              (0x0U)
#define AX5043_RADIOSTATE_POWERDOWN         (0x1U)
#define AX5043_RADIOSTATE_TX_PLL_SET        (0x4U)
#define AX5043_RADIOSTATE_TX                (0x6U)
#define AX5043_RADIOSTATE_TX_TAIL           (0x7U)
#define AX5043_RADIOSTATE_RX_PLL_SET        (0x8U)
#define AX5043_RADIOSTATE_RX_ANTSEL         (0x9U)
#define AX5043_RADIOSTATE_RX_PREAMBLE1      (0xCU)
#define AX5043_RADIOSTATE_RX_PREAMBLE2      (0xDU)
#define AX5043_RADIOSTATE_RX_PREAMBLE3      (0xEU)
#define AX5043_RADIOSTATE_RX                (0xFU)
/** @} */

/**
 * @name    AX5043 XTALSTATUS register fields
 * @{
 */
#define AX5043_XTALSTATUS_XTALRUN_Pos       (0U)
#define AX5043_XTALSTATUS_XTALRUN_Msk       (0x1U << AX5043_XTALSTATUS_XTALRUN_Pos)
#define AX5043_XTALSTATUS_XTALRUN           AX5043_XTALSTATUS_XTALRUN_Msk

/**
 * @name    AX5043 PINSTATE register fields
 * @{
 */
#define AX5043_PINSTATE_PSSYSCLK_Pos        (0U)
#define AX5043_PINSTATE_PSSYSCLK_Msk        (0x1U << AX5043_PINSTATE_PSSYSCLK_Pos)
#define AX5043_PINSTATE_PSSYSCLK            AX5043_PINSTATE_PSSYSCLK_Msk
#define AX5043_PINSTATE_PSDCLK_Pos          (1U)
#define AX5043_PINSTATE_PSDCLK_Msk          (0x1U << AX5043_PINSTATE_PSDCLK_Pos)
#define AX5043_PINSTATE_PSDCLK              AX5043_PINSTATE_PSDCLK_Msk
#define AX5043_PINSTATE_PSDATA_Pos          (2U)
#define AX5043_PINSTATE_PSDATA_Msk          (0x1U << AX5043_PINSTATE_PSDATA_Pos)
#define AX5043_PINSTATE_PSDATA              AX5043_PINSTATE_PSDATA_Msk
#define AX5043_PINSTATE_PSIRQ_Pos           (3U)
#define AX5043_PINSTATE_PSIRQ_Msk           (0x1U << AX5043_PINSTATE_PSIRQ_Pos)
#define AX5043_PINSTATE_PSIRQ               AX5043_PINSTATE_PSIRQ_Msk
#define AX5043_PINSTATE_PSANTSEL_Pos        (4U)
#define AX5043_PINSTATE_PSANTSEL_Msk        (0x1U << AX5043_PINSTATE_PSANTSEL_Pos)
#define AX5043_PINSTATE_PSANTSEL            AX5043_PINSTATE_PSANTSEL_Msk
#define AX5043_PINSTATE_PSPWRAMP_Pos        (5U)
#define AX5043_PINSTATE_PSPWRAMP_Msk        (0x1U << AX5043_PINSTATE_PSPWRAMP_Pos)
#define AX5043_PINSTATE_PSPWRAMP            AX5043_PINSTATE_PSPWRAMP_Msk
/** @} */

/**
 * @name    AX5043 PINFUNCSYSCLK register fields
 * @{
 */
#define AX5043_PINFUNCSYSCLK_Pos            (0U)
#define AX5043_PINFUNCSYSCLK_Msk            (0x1FU << AX5043_PINFUNCSYSCLK_Pos)
#define AX5043_PINFUNCSYSCLK                AX5043_PINFUNCSYSCLK_Msk
#define AX5043_PFSYSCLK_OUT_0               (0x00U)
#define AX5043_PFSYSCLK_OUT_1               (0x01U)
#define AX5043_PFSYSCLK_OUT_Z               (0x02U)
#define AX5043_PFSYSCLK_OUT_XTAL_INV        (0x03U)
#define AX5043_PFSYSCLK_OUT_XTAL_DIV1       (0x04U)
#define AX5043_PFSYSCLK_OUT_XTAL_DIV2       (0x05U)
#define AX5043_PFSYSCLK_OUT_XTAL_DIV4       (0x06U)
#define AX5043_PFSYSCLK_OUT_XTAL_DIV8       (0x07U)
#define AX5043_PFSYSCLK_OUT_XTAL_DIV16      (0x08U)
#define AX5043_PFSYSCLK_OUT_XTAL_DIV32      (0x09U)
#define AX5043_PFSYSCLK_OUT_XTAL_DIV64      (0x0AU)
#define AX5043_PFSYSCLK_OUT_XTAL_DIV128     (0x0BU)
#define AX5043_PFSYSCLK_OUT_XTAL_DIV256     (0x0CU)
#define AX5043_PFSYSCLK_OUT_XTAL_DIV512     (0x0DU)
#define AX5043_PFSYSCLK_OUT_XTAL_DIV1024    (0x0EU)
#define AX5043_PFSYSCLK_OUT_LPOSC           (0x0FU)
#define AX5043_PFSYSCLK_OUT_TEST_OBS        (0x1FU)
#define AX5043_PINFUNCSYSCLK_PUSYSCLK_Pos   (7U)
#define AX5043_PINFUNCSYSCLK_PUSYSCLK_Msk   (0x1U << AX5043_PINFUNCSYSCLK_PUSYSCLK_Pos)
#define AX5043_PINFUNCSYSCLK_PUSYSCLK       AX5043_PINFUNCSYSCLK_PUSYSCLK_Msk
/** @} */

/**
 * @name    AX5043 PINFUNCDCLK register fields
 * @{
 */
#define AX5043_PINFUNCDCLK_Pos              (0U)
#define AX5043_PINFUNCDCLK_Msk              (0x7U << AX5043_PINFUNCDCLK_Pos)
#define AX5043_PINFUNCDCLK                  AX5043_PINFUNCDCLK_Msk
#define AX5043_PFDCLK_OUT_0                 (0x0U)
#define AX5043_PFDCLK_OUT_1                 (0x1U)
#define AX5043_PFDCLK_OUT_Z                 (0x2U)
#define AX5043_PFDCLK_IN_MODEM_IO           (0x3U)
#define AX5043_PFDCLK_OUT_MODEM             (0x4U)
#define AX5043_PFDCLK_OUT_MODEM_IO          (0x5U)
#define AX5043_PFDCLK_OUT_TEST_OBS          (0x7U)
#define AX5043_PINFUNCDCLK_PIDCLK_Pos       (6U)
#define AX5043_PINFUNCDCLK_PIDCLK_Msk       (0x1U << AX5043_PINFUNCDCLK_PIDCLK_Pos)
#define AX5043_PINFUNCDCLK_PIDCLK           AX5043_PINFUNCDCLK_PIDCLK_Msk
#define AX5043_PINFUNCDCLK_PUDCLK_Pos       (7U)
#define AX5043_PINFUNCDCLK_PUDCLK_Msk       (0x1U << AX5043_PINFUNCDCLK_PUDCLK_Pos)
#define AX5043_PINFUNCDCLK_PUDCLK           AX5043_PINFUNCDCLK_PUDCLK_Msk
/** @} */

/**
 * @name    AX5043 PINFUNCDATA register fields
 * @{
 */
#define AX5043_PINFUNCDATA_Pos              (0U)
#define AX5043_PINFUNCDATA_Msk              (0xFU << AX5043_PINFUNCDATA_Pos)
#define AX5043_PINFUNCDATA                  AX5043_PINFUNCDATA_Msk
#define AX5043_PFDATA_OUT_0                 (0x0U)
#define AX5043_PFDATA_OUT_1                 (0x1U)
#define AX5043_PFDATA_OUT_Z                 (0x2U)
#define AX5043_PFDATA_IO_FRAME              (0x3U)
#define AX5043_PFDATA_IO_MODEM              (0x4U)
#define AX5043_PFDATA_IO_MODEM_ASYNC        (0x5U)
#define AX5043_PFDATA_OUT_MODEM             (0x7U)
#define AX5043_PFDATA_OUT_TEST_OBS          (0xFU)
#define AX5043_PINFUNCDATA_PIDATA_Pos       (6U)
#define AX5043_PINFUNCDATA_PIDATA_Msk       (0x1U << AX5043_PINFUNCDATA_PIDATA_Pos)
#define AX5043_PINFUNCDATA_PIDATA           AX5043_PINFUNCDATA_PIDATA_Msk
#define AX5043_PINFUNCDATA_PUDATA_Pos       (7U)
#define AX5043_PINFUNCDATA_PUDATA_Msk       (0x1U << AX5043_PINFUNCDATA_PUDATA_Pos)
#define AX5043_PINFUNCDATA_PUDATA           AX5043_PINFUNCDATA_PUDATA_Msk
/** @} */

/**
 * @name    AX5043 PINFUNCIRQ register fields
 * @{
 */
#define AX5043_PINFUNCIRQ_Pos               (0U)
#define AX5043_PINFUNCIRQ_Msk               (0x7U << AX5043_PINFUNCIRQ_Pos)
#define AX5043_PINFUNCIRQ                   AX5043_PINFUNCIRQ_Msk
#define AX5043_PFIRQ_OUT_0                  (0x0U)
#define AX5043_PFIRQ_OUT_1                  (0x1U)
#define AX5043_PFIRQ_OUT_Z                  (0x2U)
#define AX5043_PFIRQ_OUT_IRQ                (0x3U)
#define AX5043_PFIRQ_OUT_TEST_OBS           (0x7U)
#define AX5043_PINFUNCIRQ_PIIRQ_Pos         (6U)
#define AX5043_PINFUNCIRQ_PIIRQ_Msk         (0x1U << AX5043_PINFUNCIRQ_PIIRQ_Pos)
#define AX5043_PINFUNCIRQ_PIIRQ             AX5043_PINFUNCIRQ_PIIRQ_Msk
#define AX5043_PINFUNCIRQ_PUIRQ_Pos         (7U)
#define AX5043_PINFUNCIRQ_PUIRQ_Msk         (0x1U << AX5043_PINFUNCIRQ_PUIRQ_Pos)
#define AX5043_PINFUNCIRQ_PUIRQ             AX5043_PINFUNCIRQ_PUIRQ_Msk
/** @} */

/**
 * @name    AX5043 PINFUNCANTSEL register fields
 * @{
 */
#define AX5043_PINFUNCANTSEL_Pos            (0U)
#define AX5043_PINFUNCANTSEL_Msk            (0x7U << AX5043_PINFUNCANTSEL_Pos)
#define AX5043_PINFUNCANTSEL                AX5043_PINFUNCANTSEL_Msk
#define AX5043_PFANTSEL_OUT_0               (0x0U)
#define AX5043_PFANTSEL_OUT_1               (0x1U)
#define AX5043_PFANTSEL_OUT_Z               (0x2U)
#define AX5043_PFANTSEL_OUT_BB_TUNE_CLK     (0x3U)
#define AX5043_PFANTSEL_OUT_TCXO_EN         (0x4U)
#define AX5043_PFANTSEL_OUT_DAC             (0x5U)
#define AX5043_PFANTSEL_OUT_DIVERSE_ANTSEL  (0x6U)
#define AX5043_PFANTSEL_OUT_TEST_OBS        (0x7U)
#define AX5043_PINFUNCANTSEL_PIANTSEL_Pos   (6U)
#define AX5043_PINFUNCANTSEL_PIANTSEL_Msk   (0x1U << AX5043_PINFUNCANTSEL_PIANTSEL_Pos)
#define AX5043_PINFUNCANTSEL_PIANTSEL       AX5043_PINFUNCANTSEL_PIANTSEL_Msk
#define AX5043_PINFUNCANTSEL_PUANTSEL_Pos   (7U)
#define AX5043_PINFUNCANTSEL_PUANTSEL_Msk   (0x1U << AX5043_PINFUNCANTSEL_PUANTSEL_Pos)
#define AX5043_PINFUNCANTSEL_PUANTSEL       AX5043_PINFUNCANTSEL_PUANTSEL_Msk
/** @} */

/**
 * @name    AX5043 PINFUNCPWRAMP register fields
 * @{
 */
#define AX5043_PINFUNCPWRAMP_Pos            (0U)
#define AX5043_PINFUNCPWRAMP_Msk            (0xFU << AX5043_PINFUNCPWRAMP_Pos)
#define AX5043_PINFUNCPWRAMP                AX5043_PINFUNCPWRAMP_Msk
#define AX5043_PFPWRAMP_OUT_0               (0x0U)
#define AX5043_PFPWRAMP_OUT_1               (0x1U)
#define AX5043_PFPWRAMP_OUT_Z               (0x2U)
#define AX5043_PFPWRAMP_IN_DIBIT_SYNC       (0x3U)
#define AX5043_PFPWRAMP_OUT_DIBIT_SYNC      (0x4U)
#define AX5043_PFPWRAMP_OUT_DAC             (0x5U)
#define AX5043_PFPWRAMP_OUT_PWRAMP_CTRL     (0x6U)
#define AX5043_PFPWRAMP_OUT_TXCO_EN         (0x7U)
#define AX5043_PFPWRAMP_OUT_TEST_OBS        (0xFU)
#define AX5043_PINFUNCPWRAMP_PIPWRAMP_Pos   (6U)
#define AX5043_PINFUNCPWRAMP_PIPWRAMP_Msk   (0x1U << AX5043_PINFUNCPWRAMP_PIPWRAMP_Pos)
#define AX5043_PINFUNCPWRAMP_PIPWRAMP       AX5043_PINFUNCPWRAMP_PIPWRAMP_Msk
#define AX5043_PINFUNCPWRAMP_PUPWRAMP_Pos   (7U)
#define AX5043_PINFUNCPWRAMP_PUPWRAMP_Msk   (0x1U << AX5043_PINFUNCPWRAMP_PUPWRAMP_Pos)
#define AX5043_PINFUNCPWRAMP_PUPWRAMP       AX5043_PINFUNCPWRAMP_PUPWRAMP_Msk
/** @} */

/**
 * @name    AX5043 PWRAMP register fields
 * @{
 */
#define AX5043_PWRAMP_Pos                   (0U)
#define AX5043_PWRAMP_Msk                   (0x1U << AX5043_PWRAMP_Pos)
#define AX5043_PWRAMP                       AX5043_PWRAMP_Msk
/** @} */

/**
 * @name    AX5043 FIFOSTAT register fields
 * @{
 */
#define AX5043_FIFOSTAT_FIFOCMD_Pos         (0U)
#define AX5043_FIFOSTAT_FIFOCMD_Msk         (0x3FU << AX5043_FIFOSTAT_FIFOCMD_Pos)
#define AX5043_FIFOSTAT_FIFOCMD             AX5043_FIFOSTAT_FIFOCMD_Msk
#define AX5043_FIFOCMD_NOP                  (0x00U)
#define AX5043_FIFOCMD_ASK_COHERENT         (0x01U)
#define AX5043_FIFOCMD_CLEAR_FIFOERR        (0x02U)
#define AX5043_FIFOCMD_CLEAR_FIFODAT        (0x03U)
#define AX5043_FIFOCMD_COMMIT               (0x04U)
#define AX5043_FIFOCMD_ROLLBACK             (0x05U)
#define AX5043_FIFOSTAT_FIFOEMPTY_Pos       (0U)
#define AX5043_FIFOSTAT_FIFOEMPTY_Msk       (0x1U << AX5043_FIFOSTAT_FIFOEMPTY_Pos)
#define AX5043_FIFOSTAT_FIFOEMPTY           AX5043_FIFOSTAT_FIFOEMPTY_Msk
#define AX5043_FIFOSTAT_FIFOFULL_Pos        (1U)
#define AX5043_FIFOSTAT_FIFOFULL_Msk        (0x1U << AX5043_FIFOSTAT_FIFOFULL_Pos)
#define AX5043_FIFOSTAT_FIFOFULL            AX5043_FIFOSTAT_FIFOFULL_Msk
#define AX5043_FIFOSTAT_FIFOUNDER_Pos       (2U)
#define AX5043_FIFOSTAT_FIFOUNDER_Msk       (0x1U << AX5043_FIFOSTAT_FIFOUNDER_Pos)
#define AX5043_FIFOSTAT_FIFOUNDER           AX5043_FIFOSTAT_FIFOUNDER_Msk
#define AX5043_FIFOSTAT_FIFOOVER_Pos        (3U)
#define AX5043_FIFOSTAT_FIFOOVER_Msk        (0x1U << AX5043_FIFOSTAT_FIFOOVER_Pos)
#define AX5043_FIFOSTAT_FIFOOVER            AX5043_FIFOSTAT_FIFOOVER_Msk
#define AX5043_FIFOSTAT_FIFOCNTTHR_Pos      (4U)
#define AX5043_FIFOSTAT_FIFOCNTTHR_Msk      (0x1U << AX5043_FIFOSTAT_FIFOCNTTHR_Pos)
#define AX5043_FIFOSTAT_FIFOCNTTHR          AX5043_FIFOSTAT_FIFOCNTTHR_Msk
#define AX5043_FIFOSTAT_FIFOFREETHR_Pos     (5U)
#define AX5043_FIFOSTAT_FIFOFREETHR_Msk     (0x1U << AX5043_FIFOSTAT_FIFOFREETHR_Pos)
#define AX5043_FIFOSTAT_FIFOFREETHR         AX5043_FIFOSTAT_FIFOFREETHR_Msk
#define AX5043_FIFOSTAT_FIFOAUTOCOMMIT_Pos  (7U)
#define AX5043_FIFOSTAT_FIFOAUTOCOMMIT_Msk  (0x1U << AX5043_FIFOSTAT_FIFOAUTOCOMMIT_Pos)
#define AX5043_FIFOSTAT_FIFOAUTOCOMMIT      AX5043_FIFOSTAT_FIFOAUTOCOMMIT_Msk
/** @} */

/**
 * @name    AX5043 FIFODATA register fields
 * @{
 */
#define AX5043_FIFODATA_Pos                 (0U)
#define AX5043_FIFODATA_Msk                 (0xFFU << AX5043_FIFODATA_Pos)
#define AX5043_FIFODATA                     AX5043_FIFODATA_Msk
/** @} */

/**
 * @name    AX5043 FIFOCOUNT register fields
 * @{
 */
#define AX5043_FIFOCOUNT_Pos                (0U)
#define AX5043_FIFOCOUNT_Msk                (0x1FFU << AX5043_FIFOCOUNT_Pos)
#define AX5043_FIFOCOUNT                    AX5043_FIFOCOUNT_Msk
/** @} */

/**
 * @name    AX5043 FIFOFREE register fields
 * @{
 */
#define AX5043_FIFOFREE_Pos                 (0U)
#define AX5043_FIFOFREE_Msk                 (0x1FFU << AX5043_FIFOFREE_Pos)
#define AX5043_FIFOFREE                     AX5043_FIFOFREE_Msk
/** @} */

/**
 * @name    AX5043 FIFOTHRESH register fields
 * @{
 */
#define AX5043_FIFOTHRESH_Pos               (0U)
#define AX5043_FIFOTHRESH_Msk               (0x1FFU << AX5043_FIFOTHRESH_Pos)
#define AX5043_FIFOTHRESH                   AX5043_FIFOTHRESH_Msk
/** @} */

/**
 * @name    AX5043 PLLLOOP/PLLLOOPBOOST register fields
 * @{
 */
#define AX5043_PLLLOOP_FLT_Pos              (0U)
#define AX5043_PLLLOOP_FLT_Msk              (0x3U << AX5043_PLLLOOP_FLT_Pos)
#define AX5043_PLLLOOP_FLT                  AX5043_PLLLOOP_FLT_Msk
#define AX5043_FLT_EXTERN                   (0x0U)
#define AX5043_FLT_INTERN_100KHZ            (0x1U)
#define AX5043_FLT_INTERN_200KHZ            (0x2U)
#define AX5043_FLT_INTERN_300KHZ            (0x3U)
#define AX5043_PLLLOOP_FLTEN_Pos            (2U)
#define AX5043_PLLLOOP_FLTEN_Msk            (0x1U << AX5043_PLLLOOP_FLTEN_Pos)
#define AX5043_PLLLOOP_FLTEN                AX5043_PLLLOOP_FLTEN_Msk
#define AX5043_PLLLOOP_DIRECT_Pos           (3U)
#define AX5043_PLLLOOP_DIRECT_Msk           (0x1U << AX5043_PLLLOOP_DIRECT_Pos)
#define AX5043_PLLLOOP_DIRECT               AX5043_PLLLOOP_DIRECT_Msk
#define AX5043_PLLLOOP_FREQSEL_Pos          (7U)
#define AX5043_PLLLOOP_FREQSEL_Msk          (0x1U << AX5043_PLLLOOP_FREQSEL_Pos)
#define AX5043_PLLLOOP_FREQSEL              AX5043_PLLLOOP_FREQSEL_Msk
/** @} */

/**
 * @name    AX5043 PLLCPI/PLLCPIBOOST register fields
 * @{
 */
#define AX5043_PLLCPI_Pos                   (0U)
#define AX5043_PLLCPI_Msk                   (0xFFU << AX5043_PLLCPI_Pos)
#define AX5043_PLLCPI                       AX5043_PLLCPI_Msk
/** @} */

/**
 * @name    AX5043 PLLVCODIV register fields
 * @{
 */
#define AX5043_PLLVCODIV_REFDIV_Pos         (0U)
#define AX5043_PLLVCODIV_REFDIV_Msk         (0x3U << AX5043_PLLVCODIV_REFDIV_Pos)
#define AX5043_PLLVCODIV_REFDIV             AX5043_PLLVCODIV_REFDIV_Msk
#define AX5043_REFDIV_XTAL_DIV1             (0x0U)
#define AX5043_REFDIV_XTAL_DIV2             (0x1U)
#define AX5043_REFDIV_XTAL_DIV4             (0x2U)
#define AX5043_REFDIV_XTAL_DIV8             (0x3U)
#define AX5043_PLLVCODIV_RFDIV_Pos          (2U)
#define AX5043_PLLVCODIV_RFDIV_Msk          (0x1U << AX5043_PLLVCODIV_RFDIV_Pos)
#define AX5043_PLLVCODIV_RFDIV              AX5043_PLLVCODIV_RFDIV_Msk
#define AX5043_PLLVCODIV_VCOSEL_Pos         (4U)
#define AX5043_PLLVCODIV_VCOSEL_Msk         (0x1U << AX5043_PLLVCODIV_VCOSEL_Pos)
#define AX5043_PLLVCODIV_VCOSEL             AX5043_PLLVCODIV_VCOSEL_Msk
#define AX5043_PLLVCODIV_VCO2INT_Pos        (5U)
#define AX5043_PLLVCODIV_VCO2INT_Msk        (0x1U << AX5043_PLLVCODIV_VCO2INT_Pos)
#define AX5043_PLLVCODIV_VCO2INT            AX5043_PLLVCODIV_VCO2INT_Msk
#define AX5043_PLLVCODIV_VCOIMAN_Pos        (6U)
#define AX5043_PLLVCODIV_VCOIMAN_Msk        (0x1U << AX5043_PLLVCODIV_VCOIMAN_Pos)
#define AX5043_PLLVCODIV_VCOIMAN            AX5043_PLLVCODIV_VCOIMAN_Msk
/** @} */

/**
 * @name    AX5043 PLLRANGINGA/PLLRANGINGB register fields
 * @{
 */
#define AX5043_PLLRANGING_VCOR_Pos          (0U)
#define AX5043_PLLRANGING_VCOR_Msk          (0xFU << AX5043_PLLRANGING_VCOR_Pos)
#define AX5043_PLLRANGING_VCOR              AX5043_PLLRANGING_VCOR_Msk
#define AX5043_PLLRANGING_RNGSTART_Pos      (4U)
#define AX5043_PLLRANGING_RNGSTART_Msk      (0x1U << AX5043_PLLRANGING_RNGSTART_Pos)
#define AX5043_PLLRANGING_RNGSTART          AX5043_PLLRANGING_RNGSTART_Msk
#define AX5043_PLLRANGING_RNGERR_Pos        (5U)
#define AX5043_PLLRANGING_RNGERR_Msk        (0x1U << AX5043_PLLRANGING_RNGERR_Pos)
#define AX5043_PLLRANGING_RNGERR            AX5043_PLLRANGING_RNGERR_Msk
#define AX5043_PLLRANGING_PLLLOCK_Pos       (6U)
#define AX5043_PLLRANGING_PLLLOCK_Msk       (0x1U << AX5043_PLLRANGING_PLLLOCK_Pos)
#define AX5043_PLLRANGING_PLLLOCK           AX5043_PLLRANGING_PLLLOCK_Msk
#define AX5043_PLLRANGING_STICKYLOCK_Pos    (7U)
#define AX5043_PLLRANGING_STICKYLOCK_Msk    (0x1U << AX5043_PLLRANGING_STICKYLOCK_Pos)
#define AX5043_PLLRANGING_STICKYLOCK        AX5043_PLLRANGING_STICKYLOCK_Msk
/** @} */

/**
 * @name    AX5043 FREQA/FREQB register fields
 * @{
 */
#define AX5043_FREQ_Pos                     (0U)
#define AX5043_FREQ_Msk                     (0xFFFFFFFFU << AX5043_FREQ_Pos)
#define AX5043_FREQ                         AX5043_FREQ_Msk
/** @} */

/**
 * @name    AX5043 RSSI register fields
 * @{
 */
#define AX5043_RSSI_Pos                     (0U)
#define AX5043_RSSI_Msk                     (0xFFU << AX5043_RSSI_Pos)
#define AX5043_RSSI                         AX5043_RSSI_Msk
/** @} */

/**
 * @name    AX5043 BGNDRSSI register fields
 * @{
 */
#define AX5043_BGNDRSSI_Pos                 (0U)
#define AX5043_BGNDRSSI_Msk                 (0xFFU << AX5043_BGNDRSSI_Pos)
#define AX5043_BGNDRSSI                     AX5043_BGNDRSSI_Msk
/** @} */

/**
 * @name    AX5043 DIVERSITY register fields
 * @{
 */
#define AX5043_DIVERSITY_DIVENA_Pos         (0U)
#define AX5043_DIVERSITY_DIVENA_Msk         (0x1U << AX5043_DIVERSITY_DIVENA_Pos)
#define AX5043_DIVERSITY_DIVENA             AX5043_DIVERSITY_DIVENA_Msk
#define AX5043_DIVERSITY_ANTSEL_Pos         (1U)
#define AX5043_DIVERSITY_ANTSEL_Msk         (0x1U << AX5043_DIVERSITY_ANTSEL_Pos)
#define AX5043_DIVERSITY_ANTSEL             AX5043_DIVERSITY_ANTSEL_Msk
/** @} */

/**
 * @name    AX5043 AGCCOUNTER register fields
 * @{
 */
#define AX5043_AGCCOUNTER_Pos               (0U)
#define AX5043_AGCCOUNTER_Msk               (0xFFU << AX5043_AGCCOUNTER_Pos)
#define AX5043_AGCCOUNTER                   AX5043_AGCCOUNTER_Msk
/** @} */

/**
 * @name    AX5043 TRKDATARATE register fields
 * @{
 */
#define AX5043_TRKDATARATE_Pos              (0U)
#define AX5043_TRKDATARATE_Msk              (0xFFFFFFU << AX5043_TRKDATARATE_Pos)
#define AX5043_TRKDATARATE                  AX5043_TRKDATARATE_Msk
/** @} */

/**
 * @name    AX5043 TRKAMPL register fields
 * @{
 */
#define AX5043_TRKAMPL_Pos                  (0U)
#define AX5043_TRKAMPL_Msk                  (0xFFFFU << AX5043_TRKAMPL_Pos)
#define AX5043_TRKAMPL                      AX5043_TRKAMPL_Msk
/** @} */

/**
 * @name    AX5043 TRKPHASE register fields
 * @{
 */
#define AX5043_TRKPHASE_Pos                 (0U)
#define AX5043_TRKPHASE_Msk                 (0xFFFU << AX5043_TRKPHASE_Pos)
#define AX5043_TRKPHASE                     AX5043_TRKPHASE_Msk
/** @} */

/**
 * @name    AX5043 TRKRFFREQ register fields
 * @{
 */
#define AX5043_TRKRFFREQ_Pos                (0U)
#define AX5043_TRKRFFREQ_Msk                (0xFFFFFU << AX5043_TRKRFFREQ_Pos)
#define AX5043_TRKRFFREQ                    AX5043_TRKRFFREQ_Msk
/** @} */

/**
 * @name    AX5043 TRKFREQ register fields
 * @{
 */
#define AX5043_TRKFREQ_Pos                  (0U)
#define AX5043_TRKFREQ_Msk                  (0xFFFFU << AX5043_TRKFREQ_Pos)
#define AX5043_TRKFREQ                      AX5043_TRKFREQ_Msk
/** @} */

/**
 * @name    AX5043 TRKFSKDEMOD register fields
 * @{
 */
#define AX5043_TRKFSKDEMOD_Pos              (0U)
#define AX5043_TRKFSKDEMOD_Msk              (0x3FFFU << AX5043_TRKFSKDEMOD_Pos)
#define AX5043_TRKFSKDEMOD                  AX5043_TRKFSKDEMOD_Msk
/** @} */

/**
 * @name    AX5043 TRKAFSKDEMOD register fields
 * @{
 */
#define AX5043_TRKAFSKDEMOD_Pos             (0U)
#define AX5043_TRKAFSKDEMOD_Msk             (0xFFFFU << AX5043_TRKAFSKDEMOD_Pos)
#define AX5043_TRKAFSKDEMOD                 AX5043_TRKAFSKDEMOD_Msk
/** @} */

/**
 * @name    AX5043 Tracking register reset fields
 *
 * @note    For writes to TRKDATARATE, TRKAMPL, TRKPHASE registers
 * TODO:    Verify these are correct?
 * @{
 */
#define AX5043_TRACKING_DTRKRESET_Pos       (3U)
#define AX5043_TRACKING_DTRKRESET_Msk       (0x1U << AX5043_TRACKING_DTRKRESET_Pos)
#define AX5043_TRACKING_DTRKRESET           AX5043_TRACKING_DTRKRESET_Msk
#define AX5043_TRACKING_ATRKRESET_Pos       (4U)
#define AX5043_TRACKING_ATRKRESET_Msk       (0x1U << AX5043_TRACKING_ATRKRESET_Pos)
#define AX5043_TRACKING_ATRKRESET           AX5043_TRACKING_ATRKRESET_Msk
#define AX5043_TRACKING_PTRKRESET_Pos       (5U)
#define AX5043_TRACKING_PTRKRESET_Msk       (0x1U << AX5043_TRACKING_PTRKRESET_Pos)
#define AX5043_TRACKING_PTRKRESET           AX5043_TRACKING_PTRKRESET_Msk
#define AX5043_TRACKING_RTRKRESET_Pos       (6U)
#define AX5043_TRACKING_RTRKRESET_Msk       (0x1U << AX5043_TRACKING_RTRKRESET_Pos)
#define AX5043_TRACKING_RTRKRESET           AX5043_TRACKING_RTRKRESET_Msk
#define AX5043_TRACKING_FTRKRESET_Pos       (7U)
#define AX5043_TRACKING_FTRKRESET_Msk       (0x1U << AX5043_TRACKING_FTRKRESET_Pos)
#define AX5043_TRACKING_FTRKRESET           AX5043_TRACKING_FTRKRESET_Msk
/** @} */

/**
 * @name    AX5043 TIMER register fields
 * @{
 */
#define AX5043_TIMER_Pos                    (0U)
#define AX5043_TIMER_Msk                    (0xFFFFFFU << AX5043_TIMER_Pos)
#define AX5043_TIMER                        AX5043_TIMER_Msk
/** @} */

/**
 * @name    AX5043 WAKEUPTIMER register fields
 * @{
 */
#define AX5043_WAKEUPTIMER_Pos              (0U)
#define AX5043_WAKEUPTIMER_Msk              (0xFFFFU << AX5043_WAKEUPTIMER_Pos)
#define AX5043_WAKEUPTIMER                  AX5043_WAKEUPTIMER_Msk
/** @} */

/**
 * @name    AX5043 WAKEUP register fields
 * @{
 */
#define AX5043_WAKEUP_Pos                   (0U)
#define AX5043_WAKEUP_Msk                   (0xFFFFU << AX5043_WAKEUP_Pos)
#define AX5043_WAKEUP                       AX5043_WAKEUP_Msk
/** @} */

/**
 * @name    AX5043 WAKEUPFREQ register fields
 * @{
 */
#define AX5043_WAKEUPFREQ_Pos               (0U)
#define AX5043_WAKEUPFREQ_Msk               (0xFFFFU << AX5043_WAKEUPFREQ_Pos)
#define AX5043_WAKEUPFREQ                   AX5043_WAKEUPFREQ_Msk
/** @} */

/**
 * @name    AX5043 WAKEUPXOEARLY register fields
 * @{
 */
#define AX5043_WAKEUPXOEARLY_Pos            (0U)
#define AX5043_WAKEUPXOEARLY_Msk            (0xFFU << AX5043_WAKEUPXOEARLY_Pos)
#define AX5043_WAKEUPXOEARLY                AX5043_WAKEUPXOEARLY_Msk
/** @} */

/**
 * @name    AX5043 IFFREQ register fields
 * @{
 */
#define AX5043_IFFREQ_Pos                   (0U)
#define AX5043_IFFREQ_Msk                   (0xFFFFU << AX5043_IFFREQ_Pos)
#define AX5043_IFFREQ                       AX5043_IFFREQ_Msk
/** @} */

/**
 * @name    AX5043 DECIMATION register fields
 * @{
 */
#define AX5043_DECIMATION_Pos               (0U)
#define AX5043_DECIMATION_Msk               (0x7F << AX5043_DECIMATION_Pos)
#define AX5043_DECIMATION                   AX5043_DECIMATION_Msk
/** @} */

/**
 * @name    AX5043 RXDATARATE register fields
 * @{
 */
#define AX5043_RXDATARATE_Pos               (0U)
#define AX5043_RXDATARATE_Msk               (0xFFFFFFU << AX5043_RXDATARATE_Pos)
#define AX5043_RXDATARATE                   AX5043_RXDATARATE_Msk
/** @} */

/**
 * @name    AX5043 MAXDROFFSET register fields
 * @{
 */
#define AX5043_MAXDROFFSET_Pos              (0U)
#define AX5043_MAXDROFFSET_Msk              (0xFFFFFFU << AX5043_MAXDROFFSET_Pos)
#define AX5043_MAXDROFFSET                  AX5043_MAXDROFFSET_Msk
/** @} */

/**
 * @name    AX5043 MAXRFOFFSET register fields
 * @{
 */
#define AX5043_MAXRFOFFSET_Pos              (0U)
#define AX5043_MAXRFOFFSET_Msk              (0xFFFFFU << AX5043_MAXRFOFFSET_Pos)
#define AX5043_MAXRFOFFSET                  AX5043_MAXRFOFFSET_Msk
#define AX5043_MAXRFOFFSET_FREQOFFSCORR_Pos (23U)
#define AX5043_MAXRFOFFSET_FREQOFFSCORR_Msk (0x1U << AX5043_MAXRFOFFSET_FREQOFFSCORR_Pos)
#define AX5043_MAXRFOFFSET_FREQOFFSCORR     AX5043_MAXRFOFFSET_FREQOFFSCORR_Msk
/** @} */

/**
 * @name    AX5043 FSKDMAX register fields
 * @{
 */
#define AX5043_FSKDMAX_Pos                  (0U)
#define AX5043_FSKDMAX_Msk                  (0xFFFFU << AX5043_FSKDMAX_Pos)
#define AX5043_FSKDMAX                      AX5043_FSKDMAX_Msk
/** @} */

/**
 * @name    AX5043 FSKDMIN register fields
 * @{
 */
#define AX5043_FSKDMIN_Pos                  (0U)
#define AX5043_FSKDMIN_Msk                  (0xFFFFU << AX5043_FSKDMIN_Pos)
#define AX5043_FSKDMIN                      AX5043_FSKDMIN_Msk
/** @} */

/**
 * @name    AX5043 AFSKSPACE register fields
 * TODO:    Verify the field width here
 * @{
 */
#define AX5043_AFSKSPACE_Pos                (0U)
#define AX5043_AFSKSPACE_Msk                (0xFFFFU << AX5043_AFSKSPACE_Pos)
#define AX5043_AFSKSPACE                    AX5043_AFSKSPACE_Msk
/** @} */

/**
 * @name    AX5043 AFSKMARK register fields
 * TODO:    Verify the field width here
 * @{
 */
#define AX5043_AFSKMARK_Pos                 (0U)
#define AX5043_AFSKMARK_Msk                 (0xFFFFU << AX5043_AFSKMARK_Pos)
#define AX5043_AFSKMARK                     AX5043_AFSKMARK_Msk
/** @} */

/**
 * @name    AX5043 AFSKCTRL register fields
 * @{
 */
#define AX5043_AFSKCTRL_AFSKSHIFT_Pos       (0U)
#define AX5043_AFSKCTRL_AFSKSHIFT_Msk       (0x1FU << AX5043_AFSKCTRL_AFSKSHIFT_Pos)
#define AX5043_AFSKCTRL_AFSKSHIFT           AX5043_AFSKCTRL_AFSKSHIFT_Msk
/** @} */

/**
 * @name    AX5043 AMPLFILTER register fields
 * @{
 */
#define AX5043_AMPLFILTER_Pos               (0U)
#define AX5043_AMPLFILTER_Msk               (0xFU << AX5043_AMPLFILTER_Pos)
#define AX5043_AMPLFILTER                   AX5043_AMPLFILTER_Msk
/** @} */

/**
 * @name    AX5043 FREQUENCYLEAK register fields
 * @{
 */
#define AX5043_FREQUENCYLEAK_Pos            (0U)
#define AX5043_FREQUENCYLEAK_Msk            (0xFU << AX5043_FREQUENCYLEAK_Pos)
#define AX5043_FREQUENCYLEAK                AX5043_FREQUENCYLEAK_Msk
/** @} */

/**
 * @name    AX5043 RXPARAMSETS register fields
 * @{
 */
#define AX5043_RXPARAMSETS_RXPS0_Pos        (0U)
#define AX5043_RXPARAMSETS_RXPS0_Msk        (0x3U << AX5043_RXPARAMSETS_RXPS0_Pos)
#define AX5043_RXPARAMSETS_RXPS0            AX5043_RXPARAMSETS_RXPS0_Msk
#define AX5043_RXPARAMSETS_RXPS1_Pos        (2U)
#define AX5043_RXPARAMSETS_RXPS1_Msk        (0x3U << AX5043_RXPARAMSETS_RXPS1_Pos)
#define AX5043_RXPARAMSETS_RXPS1            AX5043_RXPARAMSETS_RXPS1_Msk
#define AX5043_RXPARAMSETS_RXPS2_Pos        (4U)
#define AX5043_RXPARAMSETS_RXPS2_Msk        (0x3U << AX5043_RXPARAMSETS_RXPS2_Pos)
#define AX5043_RXPARAMSETS_RXPS2            AX5043_RXPARAMSETS_RXPS2_Msk
#define AX5043_RXPARAMSETS_RXPS3_Pos        (6U)
#define AX5043_RXPARAMSETS_RXPS3_Msk        (0x3U << AX5043_RXPARAMSETS_RXPS3_Pos)
#define AX5043_RXPARAMSETS_RXPS3            AX5043_RXPARAMSETS_RXPS3_Msk
/** @} */

/**
 * @name    AX5043 RXPARAMCURSET register fields
 * @{
 */
#define AX5043_RXPARAMCURSET_RXSI_Pos       (0U)
#define AX5043_RXPARAMCURSET_RXSI_Msk       (0x3U << AX5043_RXPARAMCURSET_RXSI_Pos)
#define AX5043_RXPARAMCURSET_RXSI           AX5043_RXPARAMCURSET_RXSI_Msk
#define AX5043_RXPARAMCURSET_RXSN_Pos       (2U)
#define AX5043_RXPARAMCURSET_RXSN_Msk       (0x3U << AX5043_RXPARAMCURSET_RXSN_Pos)
#define AX5043_RXPARAMCURSET_RXSN           AX5043_RXPARAMCURSET_RXSN_Msk
#define AX5043_RXPARAMCURSET_RXSI_FUNC_Pos  (4U)
#define AX5043_RXPARAMCURSET_RXSI_FUNC_Msk  (0x1U << AX5043_RXPARAMCURSET_RXSI_FUNC_Pos)
#define AX5043_RXPARAMCURSET_RXSI_FUNC      AX5043_RXPARAMCURSET_RXSI_FUNC_Msk
/** @} */

/**
 * @name    AX5043 AGCGAIN 0/1/2/3 register fields
 * @{
 */
#define AX5043_AGCGAIN_AGCATTACK_Pos        (0U)
#define AX5043_AGCGAIN_AGCATTACK_Msk        (0xFU << AX5043_AGCGAIN_AGCATTACK_Pos)
#define AX5043_AGCGAIN_AGCATTACK            AX5043_AGCGAIN_AGCATTACK_Msk
#define AX5043_AGCGAIN_AGCDECAY_Pos         (4U)
#define AX5043_AGCGAIN_AGCDECAY_Msk         (0xFU << AX5043_AGCGAIN_AGCDECAY_Pos)
#define AX5043_AGCGAIN_AGCDECAY             AX5043_AGCGAIN_AGCDECAY_Msk
/** @} */

/**
 * @name    AX5043 AGCTARGET 0/1/2/3 register fields
 * @{
 */
#define AX5043_AGCTARGET_Pos                (0U)
#define AX5043_AGCTARGET_Msk                (0xFFU << AX5043_AGCTARGET_Pos)
#define AX5043_AGCTARGET                    AX5043_AGCTARGET_Msk
/** @} */

/**
 * @name    AX5043 AGCAHYST 0/1/2/3 register fields
 * @{
 */
#define AX5043_AGCAHYST_Pos                 (0U)
#define AX5043_AGCAHYST_Msk                 (0x7U << AX5043_AGCAHYST_Pos)
#define AX5043_AGCAHYST                     AX5043_AGCAHYST_Msk
/** @} */

/**
 * @name    AX5043 AGCMINMAX 0/1/2/3 register fields
 * @{
 */
#define AX5043_AGCMINMAX_AGCMINDA_Pos       (0U)
#define AX5043_AGCMINMAX_AGCMINDA_Msk       (0x7U << AX5043_AGCMINMAX_AGCMINDA_Pos)
#define AX5043_AGCMINMAX_AGCMINDA           AX5043_AGCMINMAX_AGCMINDA_Msk
#define AX5043_AGCMINMAX_AGCMAXDA_Pos       (4U)
#define AX5043_AGCMINMAX_AGCMAXDA_Msk       (0x7U << AX5043_AGCMINMAX_AGCMAXDA_Pos)
#define AX5043_AGCMINMAX_AGCMAXDA           AX5043_AGCMINMAX_AGCMAXDA_Msk
/** @} */

/**
 * @name    AX5043 TIMEGAIN 0/1/2/3 register fields
 * @{
 */
#define AX5043_TIMEGAIN_E_Pos               (0U)
#define AX5043_TIMEGAIN_E_Msk               (0xFU << AX5043_TIMEGAIN_E_Pos)
#define AX5043_TIMEGAIN_E                   AX5043_TIMEGAIN_E_Msk
#define AX5043_TIMEGAIN_M_Pos               (4U)
#define AX5043_TIMEGAIN_M_Msk               (0xFU << AX5043_TIMEGAIN_M_Pos)
#define AX5043_TIMEGAIN_M                   AX5043_TIMEGAIN_M_Msk
/** @} */

/**
 * @name    AX5043 DRGAIN 0/1/2/3 register fields
 * @{
 */
#define AX5043_DRGAIN_E_Pos                 (0U)
#define AX5043_DRGAIN_E_Msk                 (0xFU << AX5043_DRGAIN_E_Pos)
#define AX5043_DRGAIN_E                     AX5043_DRGAIN_E_Msk
#define AX5043_DRGAIN_M_Pos                 (4U)
#define AX5043_DRGAIN_M_Msk                 (0xFU << AX5043_DRGAIN_M_Pos)
#define AX5043_DRGAIN_M                     AX5043_DRGAIN_M_Msk
/** @} */

/**
 * @name    AX5043 PHASEGAIN 0/1/2/3 register fields
 * @{
 */
#define AX5043_PHASEGAIN_Pos                (0U)
#define AX5043_PHASEGAIN_Msk                (0xFU << AX5043_PHASEGAIN_Pos)
#define AX5043_PHASEGAIN                    AX5043_PHASEGAIN_Msk
#define AX5043_PHASEGAIN_FILTERIDX_Pos      (6U)
#define AX5043_PHASEGAIN_FILTERIDX_Msk      (0x3U << AX5043_PHASEGAIN_FILTERIDX_Pos)
#define AX5043_PHASEGAIN_FILTERIDX          AX5043_PHASEGAIN_FILTERIDX_Msk
/** @} */

/**
 * @name    AX5043 FREQGAINA 0/1/2/3 register fields
 * @{
 */
#define AX5043_FREQGAINA_Pos                (0U)
#define AX5043_FREQGAINA_Msk                (0xFU << AX5043_FREQGAINA_Pos)
#define AX5043_FREQGAINA                    AX5043_FREQGAINA_Msk
#define AX5043_FREQGAINA_FREQAMPLGATE_Pos   (4U)
#define AX5043_FREQGAINA_FREQAMPLGATE_Msk   (0x1U << AX5043_FREQGAINA_FREQAMPLGATE_Pos)
#define AX5043_FREQGAINA_FREQAMPLGATE       AX5043_FREQGAINA_FREQAMPLGATE_Msk
#define AX5043_FREQGAINA_FREQHALFMOD_Pos    (5U)
#define AX5043_FREQGAINA_FREQHALFMOD_Msk    (0x1U << AX5043_FREQGAINA_FREQHALFMOD_Pos)
#define AX5043_FREQGAINA_FREQHALFMOD        AX5043_FREQGAINA_FREQHALFMOD_Msk
#define AX5043_FREQGAINA_FREQMODULO_Pos     (6U)
#define AX5043_FREQGAINA_FREQMODULO_Msk     (0x1U << AX5043_FREQGAINA_FREQMODULO_Pos)
#define AX5043_FREQGAINA_FREQMODULO         AX5043_FREQGAINA_FREQMODULO_Msk
#define AX5043_FREQGAINA_FREQLIM_Pos        (7U)
#define AX5043_FREQGAINA_FREQLIM_Msk        (0x1U << AX5043_FREQGAINA_FREQLIM_Pos)
#define AX5043_FREQGAINA_FREQLIM            AX5043_FREQGAINA_FREQLIM_Msk
/** @} */

/**
 * @name    AX5043 FREQGAINB 0/1/2/3 register fields
 * @{
 */
#define AX5043_FREQGAINB_Pos                (0U)
#define AX5043_FREQGAINB_Msk                (0x1FU << AX5043_FREQGAINB_Pos)
#define AX5043_FREQGAINB                    AX5043_FREQGAINB_Msk
#define AX5043_FREQGAINB_FREQAVG_Pos        (6U)
#define AX5043_FREQGAINB_FREQAVG_Msk        (0x1U << AX5043_FREQGAINB_FREQAVG_Pos)
#define AX5043_FREQGAINB_FREQAVG            AX5043_FREQGAINB_FREQAVG_Msk
#define AX5043_FREQGAINB_FREQFREEZE_Pos     (7U)
#define AX5043_FREQGAINB_FREQFREEZE_Msk     (0x1U << AX5043_FREQGAINB_FREQFREEZE_Pos)
#define AX5043_FREQGAINB_FREQFREEZE         AX5043_FREQGAINB_FREQFREEZE_Msk
/** @} */

/**
 * @name    AX5043 FREQGAINC 0/1/2/3 register fields
 * @{
 */
#define AX5043_FREQGAINC_Pos                (0U)
#define AX5043_FREQGAINC_Msk                (0x1FU << AX5043_FREQGAINC_Pos)
#define AX5043_FREQGAINC                    AX5043_FREQGAINC_Msk
/** @} */

/**
 * @name    AX5043 FREQGAIND 0/1/2/3 register fields
 * @{
 */
#define AX5043_FREQGAIND_Pos                (0U)
#define AX5043_FREQGAIND_Msk                (0x1FU << AX5043_FREQGAIND_Pos)
#define AX5043_FREQGAIND                    AX5043_FREQGAIND_Msk
#define AX5043_FREQGAIND_RFFREQFREEZE_Pos   (7U)
#define AX5043_FREQGAIND_RFFREQFREEZE_Msk   (0x1U << AX5043_FREQGAIND_RFFREQFREEZE_Pos)
#define AX5043_FREQGAIND_RFFREQFREEZE       AX5043_FREQGAIND_RFFREQFREEZE_Msk
/** @} */

/**
 * @name    AX5043 AMPLGAIN 0/1/2/3 register fields
 * @{
 */
#define AX5043_AMPLGAIN_Pos                 (0U)
#define AX5043_AMPLGAIN_Msk                 (0xFU << AX5043_AMPLGAIN_Pos)
#define AX5043_AMPLGAIN                     AX5043_AMPLGAIN_Msk
#define AX5043_AMPLGAIN_AMPLAGC_Pos         (6U)
#define AX5043_AMPLGAIN_AMPLAGC_Msk         (0x1U << AX5043_AMPLGAIN_AMPLAGC_Pos)
#define AX5043_AMPLGAIN_AMPLAGC             AX5043_AMPLGAIN_AMPLAGC_Msk
#define AX5043_AMPLGAIN_AMPLAVG_Pos         (7U)
#define AX5043_AMPLGAIN_AMPLAVG_Msk         (0x1U << AX5043_AMPLGAIN_AMPLAVG_Pos)
#define AX5043_AMPLGAIN_AMPLAVG             AX5043_AMPLGAIN_AMPLAVG_Msk
/** @} */

/**
 * @name    AX5043 FREQDEV 0/1/2/3 register fields
 * @{
 */
#define AX5043_FREQDEV_Pos                  (0U)
#define AX5043_FREQDEV_Msk                  (0xFFFU << AX5043_FREQDEV_Pos)
#define AX5043_FREQDEV                      AX5043_FREQDEV_Msk
/** @} */

/**
 * @name    AX5043 FOURFSK register fields
 * @{
 */
#define AX5043_FOURFSK_DEVDECAY_Pos         (0U)
#define AX5043_FOURFSK_DEVDECAY_Msk         (0xFU << AX5043_FOURFSK_DEVDECAY_Pos)
#define AX5043_FOURFSK_DEVDECAY             AX5043_FOURFSK_DEVDECAY_Msk
#define AX5043_FOURFSK_DEVUPDATE_Pos        (4U)
#define AX5043_FOURFSK_DEVUPDATE_Msk        (0x1U << AX5043_FOURFSK_DEVUPDATE_Pos)
#define AX5043_FOURFSK_DEVUPDATE            AX5043_FOURFSK_DEVUPDATE_Msk
/** @} */

/**
 * @name    AX5043 BBOFFSRES 0/1/2/3 register fields
 * @{
 */
#define AX5043_BBOFFSRES_RESINTA_Pos        (0U)
#define AX5043_BBOFFSRES_RESINTA_Msk        (0xFU << AX5043_BBOFFSRES_RESINTA_Pos)
#define AX5043_BBOFFSRES_RESINTA            AX5043_BBOFFSRES_RESINTA_Msk
#define AX5043_BBOFFSRES_RESINTB_Pos        (4U)
#define AX5043_BBOFFSRES_RESINTB_Msk        (0xFU << AX5043_BBOFFSRES_RESINTB_Pos)
#define AX5043_BBOFFSRES_RESINTB            AX5043_BBOFFSRES_RESINTB_Msk
/** @} */

/**
 * @name    AX5043 MODCFGF register fields
 * @{
 */
#define AX5043_MODCFGF_FREQSHAPE_Pos        (0U)
#define AX5043_MODCFGF_FREQSHAPE_Msk        (0x3U << AX5043_MODCFGF_FREQSHAPE_Pos)
#define AX5043_MODCFGF_FREQSHAPE            AX5043_MODCFGF_FREQSHAPE_Msk
#define AX5043_FREQSHAPE_EXTERN_LOOP_FILT   (0x0U)
#define AX5043_FREQSHAPE_GAUSS_BT_0_3       (0x2U)
#define AX5043_FREQSHAPE_GAUSS_BT_0_5       (0x3U)
/** @} */

/**
 * @name    AX5043 FSKDEV register fields
 * @{
 */
#define AX5043_FSKDEV_Pos                   (0U)
#define AX5043_FSKDEV_Msk                   (0xFFFFFFU << AX5043_FSKDEV_Pos)
#define AX5043_FSKDEV                       AX5043_FSKDEV_Msk
#define AX5043_FSKDEV_FMSHIFT_Pos           (0U)
#define AX5043_FSKDEV_FMSHIFT_Msk           (0x3U << AX5043_FSKDEV_FMSHIFT_Pos)
#define AX5043_FSKDEV_FMSHIFT               AX5043_FSKDEV_FMSHIFT_Msk
#define AX5043_FSKDEV_FMINPUT_Pos           (8U)
#define AX5043_FSKDEV_FMINPUT_Msk           (0x3U << AX5043_FSKDEV_FMINPUT_Pos)
#define AX5043_FSKDEV_FMINPUT               AX5043_FSKDEV_FMINPUT_Msk
#define AX5043_FSKDEV_FMSEXT_Pos            (14U)
#define AX5043_FSKDEV_FMSEXT_Msk            (0x1U << AX5043_FSKDEV_FMSEXT_Pos)
#define AX5043_FSKDEV_FMSEXT                AX5043_FSKDEV_FMSEXT_Msk
#define AX5043_FSKDEV_FMOFFS_Pos            (15U)
#define AX5043_FSKDEV_FMOFFS_Msk            (0x1U << AX5043_FSKDEV_FMOFFS_Pos)
#define AX5043_FSKDEV_FMOFFS                AX5043_FSKDEV_FMOFFS_Msk
/** @} */

/**
 * @name    AX5043 MODCFGA register fields
 * @{
 */
#define AX5043_MODCFGA_TXDIFF_Pos           (0U)
#define AX5043_MODCFGA_TXDIFF_Msk           (0x1U << AX5043_MODCFGA_TXDIFF_Pos)
#define AX5043_MODCFGA_TXDIFF               AX5043_MODCFGA_TXDIFF_Msk
#define AX5043_MODCFGA_TXSE_Pos             (1U)
#define AX5043_MODCFGA_TXSE_Msk             (0x1U << AX5043_MODCFGA_TXSE_Pos)
#define AX5043_MODCFGA_TXSE                 AX5043_MODCFGA_TXSE_Msk
#define AX5043_MODCFGA_AMPLSHAPE_Pos        (2U)
#define AX5043_MODCFGA_AMPLSHAPE_Msk        (0x1U << AX5043_MODCFGA_AMPLSHAPE_Pos)
#define AX5043_MODCFGA_AMPLSHAPE            AX5043_MODCFGA_AMPLSHAPE_Msk
#define AX5043_AMPLSHAPE_UNSHAPED           (0x0U)
#define AX5043_AMPLSHAPE_RAISEDCOS          (0x1U)
#define AX5043_MODCFGA_SLOWRAMP_Pos         (4U)
#define AX5043_MODCFGA_SLOWRAMP_Msk         (0x3U << AX5043_MODCFGA_SLOWRAMP_Pos)
#define AX5043_MODCFGA_SLOWRAMP             AX5043_MODCFGA_SLOWRAMP_Msk
#define AX5043_SLOWRAMP_1BIT                (0x0U)
#define AX5043_SLOWRAMP_2BIT                (0x1U)
#define AX5043_SLOWRAMP_4BIT                (0x2U)
#define AX5043_SLOWRAMP_8BIT                (0x3U)
#define AX5043_MODCFGA_PTTLCKGATE_Pos       (6U)
#define AX5043_MODCFGA_PTTLCKGATE_Msk       (0x1U << AX5043_MODCFGA_PTTLCKGATE_Pos)
#define AX5043_MODCFGA_PTTLCKGATE           AX5043_MODCFGA_PTTLCKGATE_Msk
#define AX5043_MODCFGA_BROWNGATE_Pos        (7U)
#define AX5043_MODCFGA_BROWNGATE_Msk        (0x1U << AX5043_MODCFGA_BROWNGATE_Pos)
#define AX5043_MODCFGA_BROWNGATE            AX5043_MODCFGA_BROWNGATE_Msk
/** @} */

/**
 * @name    AX5043 TXRATE register fields
 * @{
 */
#define AX5043_TXRATE_Pos                   (0U)
#define AX5043_TXRATE_Msk                   (0xFFFFFFU << AX5043_TXRATE_Pos)
#define AX5043_TXRATE                       AX5043_TXRATE_Msk
/** @} */

/**
 * @name    AX5043 TXPWRCOEFF A/B/C/D/E register fields
 * @{
 */
#define AX5043_TXPWRCOEFF_Pos               (0U)
#define AX5043_TXPWRCOEFF_Msk               (0xFFFFU << AX5043_TXPWRCOEFF_Pos)
#define AX5043_TXPWRCOEFF                   AX5043_TXPWRCOEFF_Msk
/** @} */

/**
 * @name    AX5043 PLLVCOI register fields
 * @{
 */
#define AX5043_PLLVCOI_VCOI_Pos             (0U)
#define AX5043_PLLVCOI_VCOI_Msk             (0x3FU << AX5043_PLLVCOI_VCOI_Pos)
#define AX5043_PLLVCOI_VCOI                 AX5043_PLLVCOI_VCOI_Msk
#define AX5043_PLLVCOI_VCOIE_Pos            (7U)
#define AX5043_PLLVCOI_VCOIE_Msk            (0x1U << AX5043_PLLVCOI_VCOIE_Pos)
#define AX5043_PLLVCOI_VCOIE                AX5043_PLLVCOI_VCOIE_Msk
/** @} */

/**
 * @name    AX5043 PLLVCOIR register fields
 * @{
 */
#define AX5043_PLLVCOIR_Pos                 (0U)
#define AX5043_PLLVCOIR_Msk                 (0x3FU << AX5043_PLLVCOIR_Pos)
#define AX5043_PLLVCOIR                     AX5043_PLLVCOIR_Msk
/** @} */

/**
 * @name    AX5043 PLLLOCKDET register fields
 * @{
 */
#define AX5043_PLLLOCKDET_LOCKDETDLY_Pos    (0U)
#define AX5043_PLLLOCKDET_LOCKDETDLY_Msk    (0x3U << AX5043_PLLLOCKDET_LOCKDETDLY_Pos)
#define AX5043_PLLLOCKDET_LOCKDETDLY        AX5043_PLLLOCKDET_LOCKDETDLY_Msk
#define AX5043_LOCKDETDLY_6NS               (0x0U)
#define AX5043_LOCKDETDLY_9NS               (0x1U)
#define AX5043_LOCKDETDLY_12NS              (0x2U)
#define AX5043_LOCKDETDLY_14NS              (0x3U)
#define AX5043_PLLLOCKDET_LOCKDETDLYM_Pos   (2U)
#define AX5043_PLLLOCKDET_LOCKDETDLYM_Msk   (0x1U << AX5043_PLLLOCKDET_LOCKDETDLYM_Pos)
#define AX5043_PLLLOCKDET_LOCKDETDLYM       AX5043_PLLLOCKDET_LOCKDETDLYM_Msk
#define AX5043_PLLLOCKDET_LOCKDETDLYR_Pos   (6U)
#define AX5043_PLLLOCKDET_LOCKDETDLYR_Msk   (0x3U << AX5043_PLLLOCKDET_LOCKDETDLYR_Pos)
#define AX5043_PLLLOCKDET_LOCKDETDLYR       AX5043_PLLLOCKDET_LOCKDETDLYR_Msk
/** @} */

/**
 * @name    AX5043 PLLRNGCLK register fields
 * @{
 */
#define AX5043_PLLRNGCLK_Pos                (0U)
#define AX5043_PLLRNGCLK_Msk                (0x7U << AX5043_PLLRNGCLK_Pos)
#define AX5043_PLLRNGCLK                    AX5043_PLLRNGCLK_Msk
/** @} */

/**
 * @name    AX5043 XTALCAP register fields
 * @{
 */
#define AX5043_XTALCAP_Pos                  (0U)
#define AX5043_XTALCAP_Msk                  (0xFFU << AX5043_XTALCAP_Pos)
#define AX5043_XTALCAP                      AX5043_XTALCAP_Msk
/** @} */

/**
 * @name    AX5043 BBTUNE register fields
 * @{
 */
#define AX5043_BBTUNE_Pos                   (0U)
#define AX5043_BBTUNE_Msk                   (0xFU << AX5043_BBTUNE_Pos)
#define AX5043_BBTUNE                       AX5043_BBTUNE_Msk
#define AX5043_BBTUNE_BBTUNERUN_Pos         (4U)
#define AX5043_BBTUNE_BBTUNERUN_Msk         (0x1U << AX5043_BBTUNE_BBTUNERUN_Pos)
#define AX5043_BBTUNE_BBTUNERUN             AX5043_BBTUNE_BBTUNERUN_Msk
/** @} */

/**
 * @name    AX5043 BBOFFSCAP register fields
 * @{
 */
#define AX5043_BBOFFSCAP_CAPINTA_Pos        (0U)
#define AX5043_BBOFFSCAP_CAPINTA_Msk        (0x7U << AX5043_BBOFFSCAP_CAPINTA_Pos)
#define AX5043_BBOFFSCAP_CAPINTA            AX5043_BBOFFSCAP_CAPINTA_Msk
#define AX5043_BBOFFSCAP_CAPINTB_Pos        (4U)
#define AX5043_BBOFFSCAP_CAPINTB_Msk        (0x7U << AX5043_BBOFFSCAP_CAPINTB_Pos)
#define AX5043_BBOFFSCAP_CAPINTB            AX5043_BBOFFSCAP_CAPINTB_Msk
/** @} */

/**
 * @name    AX5043 PKTADDRCFG register fields
 * @{
 */
#define AX5043_PKTADDRCFG_ADDRPOS_Pos       (0U)
#define AX5043_PKTADDRCFG_ADDRPOS_Msk       (0xFU << AX5043_PKTADDRCFG_ADDRPOS_Pos)
#define AX5043_PKTADDRCFG_ADDRPOS           AX5043_PKTADDRCFG_ADDRPOS_Msk
#define AX5043_PKTADDRCFG_FECSYNCDIS_Pos    (5U)
#define AX5043_PKTADDRCFG_FECSYNCDIS_Msk    (0x1U << AX5043_PKTADDRCFG_FECSYNCDIS_Pos)
#define AX5043_PKTADDRCFG_FECSYNCDIS        AX5043_PKTADDRCFG_FECSYNCDIS_Msk
#define AX5043_PKTADDRCFG_CRCSKIPFIRST_Pos  (6U)
#define AX5043_PKTADDRCFG_CRCSKIPFIRST_Msk  (0x1U << AX5043_PKTADDRCFG_CRCSKIPFIRST_Pos)
#define AX5043_PKTADDRCFG_CRCSKIPFIRST      AX5043_PKTADDRCFG_CRCSKIPFIRST_Msk
#define AX5043_PKTADDRCFG_MSBFIRST_Pos      (7U)
#define AX5043_PKTADDRCFG_MSBFIRST_Msk      (0x1U << AX5043_PKTADDRCFG_MSBFIRST_Pos)
#define AX5043_PKTADDRCFG_MSBFIRST          AX5043_PKTADDRCFG_MSBFIRST_Msk
/** @} */

/**
 * @name    AX5043 PKTLENCFG register fields
 * @{
 */
#define AX5043_PKTLENCFG_LENPOS_Pos         (0U)
#define AX5043_PKTLENCFG_LENPOS_Msk         (0xFU << AX5043_PKTLENCFG_LENPOS_Pos)
#define AX5043_PKTLENCFG_LENPOS             AX5043_PKTLENCFG_LENPOS_Msk
#define AX5043_PKTLENCFG_LENBITS_Pos        (4U)
#define AX5043_PKTLENCFG_LENBITS_Msk        (0xFU << AX5043_PKTLENCFG_LENBITS_Pos)
#define AX5043_PKTLENCFG_LENBITS            AX5043_PKTLENCFG_LENBITS_Msk
/** @} */

/**
 * @name    AX5043 PKTLENOFFSET register fields
 * @{
 */
#define AX5043_PKTLENOFFSET_Pos             (0U)
#define AX5043_PKTLENOFFSET_Msk             (0xFFU << AX5043_PKTLENOFFSET_Pos)
#define AX5043_PKTLENOFFSET                 AX5043_PKTLENOFFSET_Msk
/** @} */

/**
 * @name    AX5043 PKTMAXLEN register fields
 * @{
 */
#define AX5043_PKTMAXLEN_Pos                (0U)
#define AX5043_PKTMAXLEN_Msk                (0xFFU << AX5043_PKTMAXLEN_Pos)
#define AX5043_PKTMAXLEN                    AX5043_PKTMAXLEN_Msk
/** @} */

/**
 * @name    AX5043 PKTADDR register fields
 * @{
 */
#define AX5043_PKTADDR_Pos                  (0U)
#define AX5043_PKTADDR_Msk                  (0xFFFFFFFFU << AX5043_PKTADDR_Pos)
#define AX5043_PKTADDR                      AX5043_PKTADDR_Msk
/** @} */

/**
 * @name    AX5043 PKTADDRMASK register fields
 * @{
 */
#define AX5043_PKTADDRMASK_Pos              (0U)
#define AX5043_PKTADDRMASK_Msk              (0xFFFFFFFFU << AX5043_PKTADDRMASK_Pos)
#define AX5043_PKTADDRMASK                  AX5043_PKTADDRMASK_Msk
/** @} */

/**
 * @name    AX5043 MATCH0PAT register fields
 * @{
 */
#define AX5043_MATCH0PAT_Pos                (0U)
#define AX5043_MATCH0PAT_Msk                (0xFFFFFFFFU << AX5043_MATCH0PAT_Pos)
#define AX5043_MATCH0PAT                    AX5043_MATCH0PAT_Msk
/** @} */

/**
 * @name    AX5043 MATCH0LEN register fields
 * @{
 */
#define AX5043_MATCH0LEN_Pos                (0U)
#define AX5043_MATCH0LEN_Msk                (0x1FU << AX5043_MATCH0LEN_Pos)
#define AX5043_MATCH0LEN                    AX5043_MATCH0LEN_Msk
#define AX5043_MATCH0LEN_MATCH0RAW_Pos      (7U)
#define AX5043_MATCH0LEN_MATCH0RAW_Msk      (0x1U << AX5043_MATCH0LEN_MATCH0RAW_Pos)
#define AX5043_MATCH0LEN_MATCH0RAW          AX5043_MATCH0LEN_MATCH0RAW_Msk
/** @} */

/**
 * @name    AX5043 MATCH0MIN register fields
 * @{
 */
#define AX5043_MATCH0MIN_Pos                (0U)
#define AX5043_MATCH0MIN_Msk                (0x1FU << AX5043_MATCH0MIN_Pos)
#define AX5043_MATCH0MIN                    AX5043_MATCH0MIN_Msk
/** @} */

/**
 * @name    AX5043 MATCH0MAX register fields
 * @{
 */
#define AX5043_MATCH0MAX_Pos                (0U)
#define AX5043_MATCH0MAX_Msk                (0x1FU << AX5043_MATCH0MAX_Pos)
#define AX5043_MATCH0MAX                    AX5043_MATCH0MAX_Msk
/** @} */

/**
 * @name    AX5043 MATCH1PAT register fields
 * @{
 */
#define AX5043_MATCH1PAT_Pos                (0U)
#define AX5043_MATCH1PAT_Msk                (0xFFFFU << AX5043_MATCH1PAT_Pos)
#define AX5043_MATCH1PAT                    AX5043_MATCH1PAT_Msk
/** @} */

/**
 * @name    AX5043 MATCH1LEN register fields
 * @{
 */
#define AX5043_MATCH1LEN_Pos                (0U)
#define AX5043_MATCH1LEN_Msk                (0xFU << AX5043_MATCH1LEN_Pos)
#define AX5043_MATCH1LEN                    AX5043_MATCH1LEN_Msk
#define AX5043_MATCH1LEN_MATCH1RAW_Pos      (7U)
#define AX5043_MATCH1LEN_MATCH1RAW_Msk      (0x1U << AX5043_MATCH1LEN_MATCH1RAW_Pos)
#define AX5043_MATCH1LEN_MATCH1RAW          AX5043_MATCH1LEN_MATCH1RAW_Msk
/** @} */

/**
 * @name    AX5043 MATCH1MIN register fields
 * @{
 */
#define AX5043_MATCH1MIN_Pos                (0U)
#define AX5043_MATCH1MIN_Msk                (0xFU << AX5043_MATCH1MIN_Pos)
#define AX5043_MATCH1MIN                    AX5043_MATCH1MIN_Msk
/** @} */

/**
 * @name    AX5043 MATCH1MAX register fields
 * @{
 */
#define AX5043_MATCH1MAX_Pos                (0U)
#define AX5043_MATCH1MAX_Msk                (0xFU << AX5043_MATCH1MAX_Pos)
#define AX5043_MATCH1MAX                    AX5043_MATCH1MAX_Msk
/** @} */

/**
 * @name    AX5043 TMGTXBOOST register fields
 * @{
 */
#define AX5043_TMGTXBOOST_M_Pos             (0U)
#define AX5043_TMGTXBOOST_M_Msk             (0x1FU << AX5043_TMGTXBOOST_M_Pos)
#define AX5043_TMGTXBOOST_M                 AX5043_TMGTXBOOST_M_Msk
#define AX5043_TMGTXBOOST_E_Pos             (5U)
#define AX5043_TMGTXBOOST_E_Msk             (0x7U << AX5043_TMGTXBOOST_E_Pos)
#define AX5043_TMGTXBOOST_E                 AX5043_TMGTXBOOST_E_Msk
/** @} */

/**
 * @name    AX5043 TMGTXSETTLE register fields
 * @{
 */
#define AX5043_TMGTXSETTLE_M_Pos            (0U)
#define AX5043_TMGTXSETTLE_M_Msk            (0x1FU << AX5043_TMGTXSETTLE_M_Pos)
#define AX5043_TMGTXSETTLE_M                AX5043_TMGTXSETTLE_M_Msk
#define AX5043_TMGTXSETTLE_E_Pos            (5U)
#define AX5043_TMGTXSETTLE_E_Msk            (0x7U << AX5043_TMGTXSETTLE_E_Pos)
#define AX5043_TMGTXSETTLE_E                AX5043_TMGTXSETTLE_E_Msk
/** @} */

/**
 * @name    AX5043 TMGRXBOOST register fields
 * @{
 */
#define AX5043_TMGRXBOOST_M_Pos             (0U)
#define AX5043_TMGRXBOOST_M_Msk             (0x1FU << AX5043_TMGRXBOOST_M_Pos)
#define AX5043_TMGRXBOOST_M                 AX5043_TMGRXBOOST_M_Msk
#define AX5043_TMGRXBOOST_E_Pos             (5U)
#define AX5043_TMGRXBOOST_E_Msk             (0x7U << AX5043_TMGRXBOOST_E_Pos)
#define AX5043_TMGRXBOOST_E                 AX5043_TMGRXBOOST_E_Msk
/** @} */

/**
 * @name    AX5043 TMGRXSETTLE register fields
 * @{
 */
#define AX5043_TMGRXSETTLE_M_Pos            (0U)
#define AX5043_TMGRXSETTLE_M_Msk            (0x1FU << AX5043_TMGRXSETTLE_M_Pos)
#define AX5043_TMGRXSETTLE_M                AX5043_TMGRXSETTLE_M_Msk
#define AX5043_TMGRXSETTLE_E_Pos            (5U)
#define AX5043_TMGRXSETTLE_E_Msk            (0x7U << AX5043_TMGRXSETTLE_E_Pos)
#define AX5043_TMGRXSETTLE_E                AX5043_TMGRXSETTLE_E_Msk
/** @} */

/**
 * @name    AX5043 TMGRXOFFSACQ register fields
 * @{
 */
#define AX5043_TMGRXOFFSACQ_M_Pos           (0U)
#define AX5043_TMGRXOFFSACQ_M_Msk           (0x1FU << AX5043_TMGRXOFFSACQ_M_Pos)
#define AX5043_TMGRXOFFSACQ_M               AX5043_TMGRXOFFSACQ_M_Msk
#define AX5043_TMGRXOFFSACQ_E_Pos           (5U)
#define AX5043_TMGRXOFFSACQ_E_Msk           (0x7U << AX5043_TMGRXOFFSACQ_E_Pos)
#define AX5043_TMGRXOFFSACQ_E               AX5043_TMGRXOFFSACQ_E_Msk
/** @} */

/**
 * @name    AX5043 TMGRXCOARSEAGC register fields
 * @{
 */
#define AX5043_TMGRXCOARSEAGC_M_Pos         (0U)
#define AX5043_TMGRXCOARSEAGC_M_Msk         (0x1FU << AX5043_TMGRXCOARSEAGC_M_Pos)
#define AX5043_TMGRXCOARSEAGC_M             AX5043_TMGRXCOARSEAGC_M_Msk
#define AX5043_TMGRXCOARSEAGC_E_Pos         (0U)
#define AX5043_TMGRXCOARSEAGC_E_Msk         (0x7U << AX5043_TMGRXCOARSEAGC_E_Pos)
#define AX5043_TMGRXCOARSEAGC_E             AX5043_TMGRXCOARSEAGC_E_Msk
/** @} */

/**
 * @name    AX5043 TMGRXAGC register fields
 * @{
 */
#define AX5043_TMGRXAGC_M_Pos               (0U)
#define AX5043_TMGRXAGC_M_Msk               (0x1FU << AX5043_TMGRXAGC_M_Pos)
#define AX5043_TMGRXAGC_M                   AX5043_TMGRXAGC_M_Msk
#define AX5043_TMGRXAGC_E_Pos               (5U)
#define AX5043_TMGRXAGC_E_Msk               (0x7U << AX5043_TMGRXAGC_E_Pos)
#define AX5043_TMGRXAGC_E                   AX5043_TMGRXAGC_E_Msk
/** @} */

/**
 * @name    AX5043 TMGRXRSSI register fields
 * @{
 */
#define AX5043_TMGRXRSSI_M_Pos              (0U)
#define AX5043_TMGRXRSSI_M_Msk              (0x1FU << AX5043_TMGRXRSSI_M_Pos)
#define AX5043_TMGRXRSSI_M                  AX5043_TMGRXRSSI_M_Msk
#define AX5043_TMGRXRSSI_E_Pos              (5U)
#define AX5043_TMGRXRSSI_E_Msk              (0x7U << AX5043_TMGRXRSSI_E_Pos)
#define AX5043_TMGRXRSSI_E                  AX5043_TMGRXRSSI_E_Msk
/** @} */

/**
 * @name    AX5043 TMGRXPREAMBLE 1/2/3 register fields
 * @{
 */
#define AX5043_TMGRXPREAMBLE_M_Pos          (0U)
#define AX5043_TMGRXPREAMBLE_M_Msk          (0x1FU << AX5043_TMGRXPREAMBLE_M_Pos)
#define AX5043_TMGRXPREAMBLE_M              AX5043_TMGRXPREAMBLE_M_Msk
#define AX5043_TMGRXPREAMBLE_E_Pos          (5U)
#define AX5043_TMGRXPREAMBLE_E_Msk          (0x7U << AX5043_TMGRXPREAMBLE_E_Pos)
#define AX5043_TMGRXPREAMBLE_E              AX5043_TMGRXPREAMBLE_E_Msk
/** @} */

/**
 * @name    AX5043 RSSIREFERENCE register fields
 * @{
 */
#define AX5043_RSSIREFERENCE_Pos            (0U)
#define AX5043_RSSIREFERENCE_Msk            (0xFFU << AX5043_RSSIREFERENCE_Pos)
#define AX5043_RSSIREFERENCE                AX5043_RSSIREFERENCE_Msk
/** @} */

/**
 * @name    AX5043 RSSIABSTHR register fields
 * @{
 */
#define AX5043_RSSIABSTHR_Pos               (0U)
#define AX5043_RSSIABSTHR_Msk               (0xFFU << AX5043_RSSIABSTHR_Pos)
#define AX5043_RSSIABSTHR                   AX5043_RSSIABSTHR_Msk
/** @} */

/**
 * @name    AX5043 BGNDRSSIGAIN register fields
 * @{
 */
#define AX5043_BGNDRSSIGAIN_Pos             (0U)
#define AX5043_BGNDRSSIGAIN_Msk             (0xFU << AX5043_BGNDRSSIGAIN_Pos)
#define AX5043_BGNDRSSIGAIN                 AX5043_BGNDRSSIGAIN_Msk
/** @} */

/**
 * @name    AX5043 BGNDRSSITHR register fields
 * @{
 */
#define AX5043_BGNDRSSITHR_Pos              (0U)
#define AX5043_BGNDRSSITHR_Msk              (0x3FU << AX5043_BGNDRSSITHR_Pos)
#define AX5043_BGNDRSSITHR                  AX5043_BGNDRSSITHR_Msk
/** @} */

/**
 * @name    AX5043 PKTCHUNKSIZE register fields
 * @{
 */
#define AX5043_PKTCHUNKSIZE_Pos             (0U)
#define AX5043_PKTCHUNKSIZE_Msk             (0xFU << AX5043_PKTCHUNKSIZE_Pos)
#define AX5043_PKTCHUNKSIZE                 AX5043_PKTCHUNKSIZE_Msk
#define AX5043_PKTCHUNKSIZE_1               (0x1U)
#define AX5043_PKTCHUNKSIZE_2               (0x2U)
#define AX5043_PKTCHUNKSIZE_4               (0x3U)
#define AX5043_PKTCHUNKSIZE_8               (0x4U)
#define AX5043_PKTCHUNKSIZE_16              (0x5U)
#define AX5043_PKTCHUNKSIZE_32              (0x6U)
#define AX5043_PKTCHUNKSIZE_64              (0x7U)
#define AX5043_PKTCHUNKSIZE_96              (0x8U)
#define AX5043_PKTCHUNKSIZE_128             (0x9U)
#define AX5043_PKTCHUNKSIZE_160             (0xAU)
#define AX5043_PKTCHUNKSIZE_192             (0xBU)
#define AX5043_PKTCHUNKSIZE_224             (0xCU)
#define AX5043_PKTCHUNKSIZE_240             (0xDU)
/** @} */

/**
 * @name    AX5043 PKTMISCFLAGS register fields
 * @{
 */
#define AX5043_PKTMISCFLAGS_RXRSSICLK_Pos   (0U)
#define AX5043_PKTMISCFLAGS_RXRSSICLK_Msk   (0x1U << AX5043_PKTMISCFLAGS_RXRSSICLK_Pos)
#define AX5043_PKTMISCFLAGS_RXRSSICLK       AX5043_PKTMISCFLAGS_RXRSSICLK_Msk
#define AX5043_PKTMISCFLAGS_RXAGCCLK_Pos    (1U)
#define AX5043_PKTMISCFLAGS_RXAGCCLK_Msk    (0x1U << AX5043_PKTMISCFLAGS_RXAGCCLK_Pos)
#define AX5043_PKTMISCFLAGS_RXAGCCLK        AX5043_PKTMISCFLAGS_RXAGCCLK_Msk
#define AX5043_PKTMISCFLAGS_BGNDRSSI_Pos    (2U)
#define AX5043_PKTMISCFLAGS_BGNDRSSI_Msk    (0x1U << AX5043_PKTMISCFLAGS_BGNDRSSI_Pos)
#define AX5043_PKTMISCFLAGS_BGNDRSSI        AX5043_PKTMISCFLAGS_BGNDRSSI_Msk
#define AX5043_PKTMISCFLAGS_AGCSETTLDET_Pos (3U)
#define AX5043_PKTMISCFLAGS_AGCSETTLDET_Msk (0x1U << AX5043_PKTMISCFLAGS_AGCSETTLDET_Pos)
#define AX5043_PKTMISCFLAGS_AGCSETTLDET     AX5043_PKTMISCFLAGS_AGCSETTLDET_Msk
#define AX5043_PKTMISCFLAGS_WORMULTIPKT_Pos (4U)
#define AX5043_PKTMISCFLAGS_WORMULTIPKT_Msk (0x1U << AX5043_PKTMISCFLAGS_WORMULTIPKT_Pos)
#define AX5043_PKTMISCFLAGS_WORMULTIPKT     AX5043_PKTMISCFLAGS_WORMULTIPKT_Msk
/** @} */

/**
 * @name    AX5043 PKTSTOREFLAGS register fields
 * @{
 */
#define AX5043_PKTSTOREFLAGS_TIMER_Pos      (0U)
#define AX5043_PKTSTOREFLAGS_TIMER_Msk      (0x1U << AX5043_PKTSTOREFLAGS_TIMER_Pos)
#define AX5043_PKTSTOREFLAGS_TIMER          AX5043_PKTSTOREFLAGS_TIMER_Msk
#define AX5043_PKTSTOREFLAGS_FOFFS_Pos      (1U)
#define AX5043_PKTSTOREFLAGS_FOFFS_Msk      (0x1U << AX5043_PKTSTOREFLAGS_FOFFS_Pos)
#define AX5043_PKTSTOREFLAGS_FOFFS          AX5043_PKTSTOREFLAGS_FOFFS_Msk
#define AX5043_PKTSTOREFLAGS_RFOFFS_Pos     (2U)
#define AX5043_PKTSTOREFLAGS_RFOFFS_Msk     (0x1U << AX5043_PKTSTOREFLAGS_RFOFFS_Pos)
#define AX5043_PKTSTOREFLAGS_RFOFFS         AX5043_PKTSTOREFLAGS_RFOFFS_Msk
#define AX5043_PKTSTOREFLAGS_DR_Pos         (3U)
#define AX5043_PKTSTOREFLAGS_DR_Msk         (0x1U << AX5043_PKTSTOREFLAGS_DR_Pos)
#define AX5043_PKTSTOREFLAGS_DR             AX5043_PKTSTOREFLAGS_DR_Msk
#define AX5043_PKTSTOREFLAGS_RSSI_Pos       (4U)
#define AX5043_PKTSTOREFLAGS_RSSI_Msk       (0x1U << AX5043_PKTSTOREFLAGS_RSSI_Pos)
#define AX5043_PKTSTOREFLAGS_RSSI           AX5043_PKTSTOREFLAGS_RSSI_Msk
#define AX5043_PKTSTOREFLAGS_CRCB_Pos       (5U)
#define AX5043_PKTSTOREFLAGS_CRCB_Msk       (0x1U << AX5043_PKTSTOREFLAGS_CRCB_Pos)
#define AX5043_PKTSTOREFLAGS_CRCB           AX5043_PKTSTOREFLAGS_CRCB_Msk
#define AX5043_PKTSTOREFLAGS_ANTRSSI_Pos    (6U)
#define AX5043_PKTSTOREFLAGS_ANTRSSI_Msk    (0x1U << AX5043_PKTSTOREFLAGS_ANTRSSI_Pos)
#define AX5043_PKTSTOREFLAGS_ANTRSSI        AX5043_PKTSTOREFLAGS_ANTRSSI_Msk
/** @} */

/**
 * @name    AX5043 PKTACCEPTFLAGS register fields
 * @{
 */
#define AX5043_PKTACCEPTFLAGS_RESIDUE_Pos   (0U)
#define AX5043_PKTACCEPTFLAGS_RESIDUE_Msk   (0x1U << AX5043_PKTACCEPTFLAGS_RESIDUE_Pos)
#define AX5043_PKTACCEPTFLAGS_RESIDUE       AX5043_PKTACCEPTFLAGS_RESIDUE_Msk
#define AX5043_PKTACCEPTFLAGS_ABRT_Pos      (1U)
#define AX5043_PKTACCEPTFLAGS_ABRT_Msk      (0x1U << AX5043_PKTACCEPTFLAGS_ABRT_Pos)
#define AX5043_PKTACCEPTFLAGS_ABRT          AX5043_PKTACCEPTFLAGS_ABRT_Msk
#define AX5043_PKTACCEPTFLAGS_CRCF_Pos      (2U)
#define AX5043_PKTACCEPTFLAGS_CRCF_Msk      (0x1U << AX5043_PKTACCEPTFLAGS_CRCF_Pos)
#define AX5043_PKTACCEPTFLAGS_CRCF          AX5043_PKTACCEPTFLAGS_CRCF_Msk
#define AX5043_PKTACCEPTFLAGS_ADDRF_Pos     (3U)
#define AX5043_PKTACCEPTFLAGS_ADDRF_Msk     (0x1U << AX5043_PKTACCEPTFLAGS_ADDRF_Pos)
#define AX5043_PKTACCEPTFLAGS_ADDRF         AX5043_PKTACCEPTFLAGS_ADDRF_Msk
#define AX5043_PKTACCEPTFLAGS_SZF_Pos       (4U)
#define AX5043_PKTACCEPTFLAGS_SZF_Msk       (0x1U << AX5043_PKTACCEPTFLAGS_SZF_Pos)
#define AX5043_PKTACCEPTFLAGS_SZF           AX5043_PKTACCEPTFLAGS_SZF_Msk
#define AX5043_PKTACCEPTFLAGS_LRGP_Pos      (5U)
#define AX5043_PKTACCEPTFLAGS_LRGP_Msk      (0x1U << AX5043_PKTACCEPTFLAGS_LRGP_Pos)
#define AX5043_PKTACCEPTFLAGS_LRGP          AX5043_PKTACCEPTFLAGS_LRGP_Msk
/** @} */

/**
 * @name    AX5043 GPADCCTRL register fields
 * @{
 */
#define AX5043_GPADCCTRL_CHISOL_Pos         (0U)
#define AX5043_GPADCCTRL_CHISOL_Msk         (0x1U << AX5043_GPADCCTRL_CHISOL_Pos)
#define AX5043_GPADCCTRL_CHISOL             AX5043_GPADCCTRL_CHISOL_Msk
#define AX5043_GPADCCTRL_CONT_Pos           (1U)
#define AX5043_GPADCCTRL_CONT_Msk           (0x1U << AX5043_GPADCCTRL_CONT_Pos)
#define AX5043_GPADCCTRL_CONT               AX5043_GPADCCTRL_CONT_Msk
#define AX5043_GPADCCTRL_GPADC13_Pos        (2U)
#define AX5043_GPADCCTRL_GPADC13_Msk        (0x1U << AX5043_GPADCCTRL_GPADC13_Pos)
#define AX5043_GPADCCTRL_GPADC13            AX5043_GPADCCTRL_GPADC13_Msk
#define AX5043_GPADCCTRL_BUSY_Pos           (7U)
#define AX5043_GPADCCTRL_BUSY_Msk           (0x1U << AX5043_GPADCCTRL_BUSY_Pos)
#define AX5043_GPADCCTRL_BUSY               AX5043_GPADCCTRL_BUSY_Msk
/** @} */

/**
 * @name    AX5043 GPADCPERIOD register fields
 * @{
 */
#define AX5043_GPADCPERIOD_Pos              (0U)
#define AX5043_GPADCPERIOD_Msk              (0xFFU << AX5043_GPADCPERIOD_Pos)
#define AX5043_GPADCPERIOD                  AX5043_GPADCPERIOD_Msk
/** @} */

/**
 * @name    AX5043 GPADC13VALUE register fields
 * @{
 */
#define AX5043_GPADC13VALUE_Pos             (0U)
#define AX5043_GPADC13VALUE_Msk             (0x3FFU << AX5043_GPADC13VALUE_Pos)
#define AX5043_GPADC13VALUE                 AX5043_GPADC13VALUE_Msk
/** @} */

/**
 * @name    AX5043 LPOSCCONFIG register fields
 * @{
 */
#define AX5043_LPOSCCONFIG_ENA_Pos          (0U)
#define AX5043_LPOSCCONFIG_ENA_Msk          (0x1U << AX5043_LPOSCCONFIG_ENA_Pos)
#define AX5043_LPOSCCONFIG_ENA              AX5043_LPOSCCONFIG_ENA_Msk
#define AX5043_LPOSCCONFIG_FAST_Pos         (1U)
#define AX5043_LPOSCCONFIG_FAST_Msk         (0x1U << AX5043_LPOSCCONFIG_FAST_Pos)
#define AX5043_LPOSCCONFIG_FAST             AX5043_LPOSCCONFIG_FAST_Msk
/* TODO: Verify which bit is IRQF/IRQR, manual is inconsistent */
#define AX5043_LPOSCCONFIG_IRQF_Pos         (2U)
#define AX5043_LPOSCCONFIG_IRQF_Msk         (0x1U << AX5043_LPOSCCONFIG_IRQF_Pos)
#define AX5043_LPOSCCONFIG_IRQF             AX5043_LPOSCCONFIG_IRQF_Msk
#define AX5043_LPOSCCONFIG_IRQR_Pos         (3U)
#define AX5043_LPOSCCONFIG_IRQR_Msk         (0x1U << AX5043_LPOSCCONFIG_IRQR_Pos)
#define AX5043_LPOSCCONFIG_IRQR             AX5043_LPOSCCONFIG_IRQR_Msk
#define AX5043_LPOSCCONFIG_CALIBF_Pos       (4U)
#define AX5043_LPOSCCONFIG_CALIBF_Msk       (0x1U << AX5043_LPOSCCONFIG_CALIBF_Pos)
#define AX5043_LPOSCCONFIG_CALIBF           AX5043_LPOSCCONFIG_CALIBF_Msk
#define AX5043_LPOSCCONFIG_CALIBR_Pos       (5U)
#define AX5043_LPOSCCONFIG_CALIBR_Msk       (0x1U << AX5043_LPOSCCONFIG_CALIBR_Pos)
#define AX5043_LPOSCCONFIG_CALIBR           AX5043_LPOSCCONFIG_CALIBR_Msk
#define AX5043_LPOSCCONFIG_OSCDOUBLE_Pos    (6U)
#define AX5043_LPOSCCONFIG_OSCDOUBLE_Msk    (0x1U << AX5043_LPOSCCONFIG_OSCDOUBLE_Pos)
#define AX5043_LPOSCCONFIG_OSCDOUBLE        AX5043_LPOSCCONFIG_OSCDOUBLE_Msk
#define AX5043_LPOSCCONFIG_OSCINVERT_Pos    (7U)
#define AX5043_LPOSCCONFIG_OSCINVERT_Msk    (0x1U << AX5043_LPOSCCONFIG_OSCINVERT_Pos)
#define AX5043_LPOSCCONFIG_OSCINVERT        AX5043_LPOSCCONFIG_OSCINVERT_Msk
/** @} */

/**
 * @name    AX5043 LPOSCSTATUS register fields
 * @{
 */
#define AX5043_LPOSCSTATUS_EDGE_Pos         (0U)
#define AX5043_LPOSCSTATUS_EDGE_Msk         (0x1U << AX5043_LPOSCSTATUS_EDGE_Pos)
#define AX5043_LPOSCSTATUS_EDGE             AX5043_LPOSCSTATUS_EDGE_Msk
#define AX5043_LPOSCSTATUS_IRQ_Pos          (1U)
#define AX5043_LPOSCSTATUS_IRQ_Msk          (0x1U << AX5043_LPOSCSTATUS_IRQ_Pos)
#define AX5043_LPOSCSTATUS_IRQ              AX5043_LPOSCSTATUS_IRQ_Msk
/** @} */

/**
 * @name    AX5043 LPOSCFILT register fields
 * @{
 */
#define AX5043_LPOSCFILT_Pos                (0U)
#define AX5043_LPOSCFILT_Msk                (0xFFFFU << AX5043_LPOSCFILT_Pos)
#define AX5043_LPOSCFILT                    AX5043_LPOSCFILT_Msk
/** @} */

/**
 * @name    AX5043 LPOSCREF register fields
 * @{
 */
#define AX5043_LPOSCREF_Pos                 (0U)
#define AX5043_LPOSCREF_Msk                 (0xFFFFU << AX5043_LPOSCREF_Pos)
#define AX5043_LPOSCREF                     AX5043_LPOSCREF_Msk
/** @} */

/**
 * @name    AX5043 LPOSCFREQ register fields
 * TODO:    Verify the field width here
 * @{
 */
#define AX5043_LPOSCFREQ_Pos                (0U)
#define AX5043_LPOSCFREQ_Msk                (0x3FFU << AX5043_LPOSCFREQ_Pos)
#define AX5043_LPOSCFREQ                    AX5043_LPOSCFREQ_Msk
/** @} */

/**
 * @name    AX5043 LPOSCPER register fields
 * @{
 */
#define AX5043_LPOSCPER_Pos                 (0U)
#define AX5043_LPOSCPER_Msk                 (0xFFFFU << AX5043_LPOSCPER_Pos)
#define AX5043_LPOSCPER                     AX5043_LPOSCPER_Msk
/** @} */

/**
 * @name    AX5043 DACVALUE register fields
 * @{
 */
#define AX5043_DACVALUE_Pos                 (0U)
#define AX5043_DACVALUE_Msk                 (0xFFFU << AX5043_DACVALUE_Pos)
#define AX5043_DACVALUE                     AX5043_DACVALUE_Msk
#define AX5043_DACVALUE_DACSHIFT_Pos        (0U)
#define AX5043_DACVALUE_DACSHIFT_Msk        (0xFU << AX5043_DACVALUE_DACSHIFT_Pos)
#define AX5043_DACVALUE_DACSHIFT            AX5043_DACVALUE_DACSHIFT_Msk
/** @} */

/**
 * @name    AX5043 DACCONFIG register fields
 * @{
 */
#define AX5043_DACCONFIG_DACINPUT_Pos       (0U)
#define AX5043_DACCONFIG_DACINPUT_Msk       (0xFU << AX5043_DACCONFIG_DACINPUT_Pos)
#define AX5043_DACCONFIG_DACINPUT           AX5043_DACCONFIG_DACINPUT_Msk
#define AX5043_DACINPUT_DACVALUER           (0x0U)
#define AX5043_DACINPUT_TRKAMPLITUDE        (0x1U)
#define AX5043_DACINPUT_TRKRFFREQUENCY      (0x2U)
#define AX5043_DACINPUT_TRKFREQUENCY        (0x3U)
#define AX5043_DACINPUT_FSKDEMOD            (0x4U)
#define AX5043_DACINPUT_AFSKDEMOD           (0x5U)
#define AX5043_DACINPUT_RXSOFTDATA          (0x6U)
#define AX5043_DACINPUT_RSSI                (0x7U)
#define AX5043_DACINPUT_SAMPLE_ROT_I        (0x8U)
#define AX5043_DACINPUT_SAMPLE_ROT_Q        (0x9U)
#define AX5043_DACINPUT_GPADC13             (0xCU)
#define AX5043_DACCONFIG_DACCLKX2_Pos       (6U)
#define AX5043_DACCONFIG_DACCLKX2_Msk       (0x1U << AX5043_DACCONFIG_DACCLKX2_Pos)
#define AX5043_DACCONFIG_DACCLKX2           AX5043_DACCONFIG_DACCLKX2_Msk
#define AX5043_DACCONFIG_DACPWM_Pos         (7U)
#define AX5043_DACCONFIG_DACPWM_Msk         (0x1U << AX5043_DACCONFIG_DACPWM_Pos)
#define AX5043_DACCONFIG_DACPWM             AX5043_DACCONFIG_DACPWM_Msk
/** @} */

/**
 * @name    AX5043 PERFTUNE registers
 * @{
 */
#define AX5043_0xF00_DEFVAL                 (0x0FU)
#define AX5043_0xF0C_DEFVAL                 (0x00U)
#define AX5043_0xF0D_DEFVAL                 (0x03U)
#define AX5043_0xF10_CRYSTAL                (0x03U)
#define AX5043_0xF10_TCXO                   (0x04U)
#define AX5043_0xF10_GT_43MHZ               (0x0DU)
#define AX5043_0xF11_TCXO                   (0x00U)
#define AX5043_0xF11_CRYSTAL                (0x07U)
/* TODO: Try to figure out 0xF18 values */
#define AX5043_0xF1C_DEFVAL                 (0x07U)
#define AX5043_0xF21_DEFVAL                 (0x5CU)
#define AX5043_0xF22_DEFVAL                 (0x53U)
#define AX5043_0xF23_DEFVAL                 (0x76U)
#define AX5043_0xF26_DEFVAL                 (0x92U)
#define AX5043_0xF30_DEFVAL                 (0x3FU)
#define AX5043_0xF31_DEFVAL                 (0xF0U)
#define AX5043_0xF32_DEFVAL                 (0x3FU)
#define AX5043_0xF33_DEFVAL                 (0xF0U)
#define AX5043_0xF34_NORFDIV                (0x08U)
#define AX5043_0xF34_RFDIV                  (0x28U)
#define AX5043_0xF35_XTALDIV1               (0x10U)
#define AX5043_0xF35_XTALDIV2               (0x11U)
#define AX5043_0xF44_DEFVAL                 (0x24U)
#define AX5043_0xF72_NORAWSOFTBITS          (0x00U)
#define AX5043_0xF72_RAWSOFTBITS            (0x06U)
/** @} */

/**
 * @name    AX5043 SPI Status Bits
 * @{
 */
#define AX5043_STATUS_PLL_LOCK              (1 << 1)
#define AX5043_STATUS_FIFO_OVER             (1 << 2)
#define AX5043_STATUS_FIFO_UNDER            (1 << 3)
#define AX5043_STATUS_FIFO_THR_FREE         (1 << 4)
#define AX5043_STATUS_FIFO_THR_COUNT        (1 << 5)
#define AX5043_STATUS_FIFO_FULL             (1 << 6)
#define AX5043_STATUS_FIFO_EMPTY            (1 << 7)
#define AX5043_STATUS_PWRGOOD               (1 << 8)
#define AX5043_STATUS_PWR_INT_PENDING       (1 << 9)
#define AX5043_STATUS_RADIO_EVENT_PENDING   (1 << 10)
#define AX5043_STATUS_XTAL_OSC_RUNNING      (1 << 11)
#define AX5043_STATUS_WAKEUP_INT_PENDING    (1 << 12)
#define AX5043_STATUS_LPOSC_INT_PENDING     (1 << 13)
#define AX5043_STATUS_GPADC_INT_PENDING     (1 << 14)
/** @} */

/**
 * @name    AX5043 FIFO chunk header fields and encodings
 * @{
 */
#define AX5043_FIFOCHUNK_CMD_Pos            (0U)
#define AX5043_FIFOCHUNK_CMD_Msk            (0x1FU << AX5043_FIFOCHUNK_CMD_Pos)
#define AX5043_FIFOCHUNK_CMD                AX5043_FIFOCHUNK_CMD_Msk
#define AX5043_CHUNKCMD_NOP                 (0x00U)
#define AX5043_CHUNKCMD_DATA                (0x01U)
#define AX5043_CHUNKCMD_REPEATDATA          (0x02U)
#define AX5043_CHUNKCMD_TIMER               (0x10U)
#define AX5043_CHUNKCMD_RSSI                (0x11U)
#define AX5043_CHUNKCMD_FREQOFFS            (0x12U)
#define AX5043_CHUNKCMD_RFFREQOFFS          (0x13U)
#define AX5043_CHUNKCMD_DATARATE            (0x14U)
#define AX5043_CHUNKCMD_ANTRSSI             (0x15U)
#define AX5043_CHUNKCMD_TXCTRL              (0x1CU)
#define AX5043_CHUNKCMD_TXPWR               (0x1DU)
#define AX5043_FIFOCHUNK_SIZE_Pos           (5U)
#define AX5043_FIFOCHUNK_SIZE_Msk           (0x7U << AX5043_FIFOCHUNK_SIZE_Pos)
#define AX5043_FIFOCHUNK_SIZE               AX5043_FIFOCHUNK_SIZE_Msk
#define AX5043_CHUNKSIZE_VAR                (0x7U)
/** @} */

/**
 * @name    AX5043 FIFO TXCTRL Command flags
 * @{
 */
#define AX5043_CHUNK_TXCTRL_PASTATE_Pos     (0U)
#define AX5043_CHUNK_TXCTRL_PASTATE_Msk     (0x1U << AX5043_CHUNK_TXCTRL_PASTATE_Pos)
#define AX5043_CHUNK_TXCTRL_PASTATE         AX5043_CHUNK_TXCTRL_PASTATE_Msk
#define AX5043_CHUNK_TXCTRL_SETPA_Pos       (1U)
#define AX5043_CHUNK_TXCTRL_SETPA_Msk       (0x1U << AX5043_CHUNK_TXCTRL_SETPA_Pos)
#define AX5043_CHUNK_TXCTRL_SETPA           AX5043_CHUNK_TXCTRL_SETPA_Msk
#define AX5043_CHUNK_TXCTRL_ANTSTATE_Pos    (2U)
#define AX5043_CHUNK_TXCTRL_ANTSTATE_Msk    (0x1U << AX5043_CHUNK_TXCTRL_ANTSTATE_Pos)
#define AX5043_CHUNK_TXCTRL_ANTSTATE        AX5043_CHUNK_TXCTRL_ANTSTATE_Msk
#define AX5043_CHUNK_TXCTRL_SETANT_Pos      (3U)
#define AX5043_CHUNK_TXCTRL_SETANT_Msk      (0x1U << AX5043_CHUNK_TXCTRL_SETANT_Pos)
#define AX5043_CHUNK_TXCTRL_SETANT          AX5043_CHUNK_TXCTRL_SETANT_Msk
#define AX5043_CHUNK_TXCTRL_TXDIFF_Pos      (4U)
#define AX5043_CHUNK_TXCTRL_TXDIFF_Msk      (0x1U << AX5043_CHUNK_TXCTRL_TXDIFF_Pos)
#define AX5043_CHUNK_TXCTRL_TXDIFF          AX5043_CHUNK_TXCTRL_TXDIFF_Msk
#define AX5043_CHUNK_TXCTRL_TXSE_Pos        (5U)
#define AX5043_CHUNK_TXCTRL_TXSE_Msk        (0x1U << AX5043_CHUNK_TXCTRL_TXSE_Pos)
#define AX5043_CHUNK_TXCTRL_TXSE            AX5043_CHUNK_TXCTRL_TXSE_Msk
#define AX5043_CHUNK_TXCTRL_SETTX_Pos       (6U)
#define AX5043_CHUNK_TXCTRL_SETTX_Msk       (0x1U << AX5043_CHUNK_TXCTRL_SETTX_Pos)
#define AX5043_CHUNK_TXCTRL_SETTX           AX5043_CHUNK_TXCTRL_SETTX_Msk
/** @} */

/**
 * @name    AX5043 FIFO REPEATDATA Command flags
 * @{
 */
#define AX5043_CHUNK_REPEATDATA_PKTSTART_Pos (0U)
#define AX5043_CHUNK_REPEATDATA_PKTSTART_Msk (0x1U << AX5043_CHUNK_REPEATDATA_PKTSTART_Pos)
#define AX5043_CHUNK_REPEATDATA_PKTSTART     AX5043_CHUNK_REPEATDATA_PKTSTART_Msk
#define AX5043_CHUNK_REPEATDATA_PKTEND_Pos  (1U)
#define AX5043_CHUNK_REPEATDATA_PKTEND_Msk  (0x1U << AX5043_CHUNK_REPEATDATA_PKTEND_Pos)
#define AX5043_CHUNK_REPEATDATA_PKTEND      AX5043_CHUNK_REPEATDATA_PKTEND_Msk
#define AX5043_CHUNK_REPEATDATA_RESIDUE_Pos (2U)
#define AX5043_CHUNK_REPEATDATA_RESIDUE_Msk (0x1U << AX5043_CHUNK_REPEATDATA_RESIDUE_Pos)
#define AX5043_CHUNK_REPEATDATA_RESIDUE     AX5043_CHUNK_REPEATDATA_RESIDUE_Msk
#define AX5043_CHUNK_REPEATDATA_NOCRC_Pos   (3U)
#define AX5043_CHUNK_REPEATDATA_NOCRC_Msk   (0x1U << AX5043_CHUNK_REPEATDATA_NOCRC_Pos)
#define AX5043_CHUNK_REPEATDATA_NOCRC       AX5043_CHUNK_REPEATDATA_NOCRC_Msk
#define AX5043_CHUNK_REPEATDATA_RAW_Pos     (4U)
#define AX5043_CHUNK_REPEATDATA_RAW_Msk     (0x1U << AX5043_CHUNK_REPEATDATA_RAW_Pos)
#define AX5043_CHUNK_REPEATDATA_RAW         AX5043_CHUNK_REPEATDATA_RAW_Msk
#define AX5043_CHUNK_REPEATDATA_UNENC_Pos   (5U)
#define AX5043_CHUNK_REPEATDATA_UNENC_Msk   (0x1U << AX5043_CHUNK_REPEATDATA_UNENC_Pos)
#define AX5043_CHUNK_REPEATDATA_UNENC       AX5043_CHUNK_REPEATDATA_UNENC_Msk
/** @} */

/**
 * @name    AX5043 FIFO DATA TX flags
 * @{
 */
#define AX5043_CHUNK_DATATX_PKTSTART_Pos    (0U)
#define AX5043_CHUNK_DATATX_PKTSTART_Msk    (0x1U << AX5043_CHUNK_DATATX_PKTSTART_Pos)
#define AX5043_CHUNK_DATATX_PKTSTART        AX5043_CHUNK_DATATX_PKTSTART_Msk
#define AX5043_CHUNK_DATATX_PKTEND_Pos      (0U)
#define AX5043_CHUNK_DATATX_PKTEND_Msk      (0x1U << AX5043_CHUNK_DATATX_PKTEND_Pos)
#define AX5043_CHUNK_DATATX_PKTEND          AX5043_CHUNK_DATATX_PKTEND_Msk
#define AX5043_CHUNK_DATATX_RESIDUE_Pos     (0U)
#define AX5043_CHUNK_DATATX_RESIDUE_Msk     (0x1U << AX5043_CHUNK_DATATX_RESIDUE_Pos)
#define AX5043_CHUNK_DATATX_RESIDUE         AX5043_CHUNK_DATATX_RESIDUE_Msk
#define AX5043_CHUNK_DATATX_NOCRC_Pos       (0U)
#define AX5043_CHUNK_DATATX_NOCRC_Msk       (0x1U << AX5043_CHUNK_DATATX_NOCRC_Pos)
#define AX5043_CHUNK_DATATX_NOCRC           AX5043_CHUNK_DATATX_NOCRC_Msk
#define AX5043_CHUNK_DATATX_RAW_Pos         (0U)
#define AX5043_CHUNK_DATATX_RAW_Msk         (0x1U << AX5043_CHUNK_DATATX_RAW_Pos)
#define AX5043_CHUNK_DATATX_RAW             AX5043_CHUNK_DATATX_RAW_Msk
#define AX5043_CHUNK_DATATX_UNENC_Pos       (0U)
#define AX5043_CHUNK_DATATX_UNENC_Msk       (0x1U << AX5043_CHUNK_DATATX_UNENC_Pos)
#define AX5043_CHUNK_DATATX_UNENC           AX5043_CHUNK_DATATX_UNENC_Msk
/** @} */

/**
 * @name    AX5043 FIFO DATA RX flags
 * @{
 */
#define AX5043_CHUNK_DATARX_PKTSTART_Pos    (0U)
#define AX5043_CHUNK_DATARX_PKTSTART_Msk    (0x1U << AX5043_CHUNK_DATARX_PKTSTART_Pos)
#define AX5043_CHUNK_DATARX_PKTSTART        AX5043_CHUNK_DATARX_PKTSTART_Msk
#define AX5043_CHUNK_DATARX_PKTEND_Pos      (0U)
#define AX5043_CHUNK_DATARX_PKTEND_Msk      (0x1U << AX5043_CHUNK_DATARX_PKTEND_Pos)
#define AX5043_CHUNK_DATARX_PKTEND          AX5043_CHUNK_DATARX_PKTEND_Msk
#define AX5043_CHUNK_DATARX_RESIDUE_Pos     (0U)
#define AX5043_CHUNK_DATARX_RESIDUE_Msk     (0x1U << AX5043_CHUNK_DATARX_RESIDUE_Pos)
#define AX5043_CHUNK_DATARX_RESIDUE         AX5043_CHUNK_DATARX_RESIDUE_Msk
#define AX5043_CHUNK_DATARX_CRCFAIL_Pos     (0U)
#define AX5043_CHUNK_DATARX_CRCFAIL_Msk     (0x1U << AX5043_CHUNK_DATARX_CRCFAIL_Pos)
#define AX5043_CHUNK_DATARX_CRCFAIL         AX5043_CHUNK_DATARX_CRCFAIL_Msk
#define AX5043_CHUNK_DATARX_ADDRFAIL_Pos    (0U)
#define AX5043_CHUNK_DATARX_ADDRFAIL_Msk    (0x1U << AX5043_CHUNK_DATARX_ADDRFAIL_Pos)
#define AX5043_CHUNK_DATARX_ADDRFAIL        AX5043_CHUNK_DATARX_ADDRFAIL_Msk
#define AX5043_CHUNK_DATARX_SIZEFAIL_Pos    (0U)
#define AX5043_CHUNK_DATARX_SIZEFAIL_Msk    (0x1U << AX5043_CHUNK_DATARX_SIZEFAIL_Pos)
#define AX5043_CHUNK_DATARX_SIZEFAIL        AX5043_CHUNK_DATARX_SIZEFAIL_Msk
#define AX5043_CHUNK_DATARX_ABORT_Pos       (0U)
#define AX5043_CHUNK_DATARX_ABORT_Msk       (0x1U << AX5043_CHUNK_DATARX_ABORT_Pos)
#define AX5043_CHUNK_DATARX_ABORT           AX5043_CHUNK_DATARX_ABORT_Msk
/** @} */

/**
 * @name    AX5043 Frequency ranges
 * @{
 */
/** @} */

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

/**
 * @brief   Maximum frequency for RFDIV = 0 (DIV 1)
 */
#ifndef AX5043_RFDIV_DIV1_MAX
#define AX5043_RFDIV_DIV1_MAX               (1050000000U)
#endif

/**
 * @brief   Minimum frequency for RFDIV = 0 (DIV 1)
 */
#ifndef AX5043_RFDIV_DIV1_MIN
#define AX5043_RFDIV_DIV1_MIN               (800000000U)
#endif

/**
 * @brief   Maximum frequency for RFDIV = 1 (DIV 2)
 */
#ifndef AX5043_RFDIV_DIV2_MAX
#define AX5043_RFDIV_DIV2_MAX               (525000000U)
#endif

/**
 * @brief   Maximum frequency for RFDIV = 1 (DIV 2)
 */
#ifndef AX5043_RFDIV_DIV2_MIN
#define AX5043_RFDIV_DIV2_MIN               (400000000U)
#endif

/**
 * @brief   Number of mailboxes
 * @note    The default is 8 mailboxes.
 */
#ifndef AX5043_MAILBOX_COUNT
#define AX5043_MAILBOX_COUNT                (8U)
#endif

/**
 * @brief   Size of mailboxes
 * @note    The default size of a mailbox is 512 bytes.
 */
#ifndef AX5043_MAILBOX_SIZE
#define AX5043_MAILBOX_SIZE                 (512U)
#endif

/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

#if AX5043_USE_SPI && !HAL_USE_SPI
#error "AX5043_USE_SPI requires HAL_USE_SPI"
#endif

#if AX5043_SHARED_SPI && !SPI_USE_MUTUAL_EXCLUSION
#error "AX5043_SHARED_SPI requires SPI_USE_MUTUAL_EXCLUSION"
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
 * @brief   AX5043 status bits.
 */
typedef uint16_t ax5043_status_t;

/**
 * @brief   AX5043 TX buffer fill callback type.
 * @details Callback used to fill the buffer driver TX buffer.
 *
 * @param   buf     The buffer to copy data into
 * @param   max_len The maximum number of bytes to copy
 *
 * @return          The actual number of bytes copied.
 *                  If 0, TX terminates.
 */
typedef size_t (*ax5043_tx_cb_t)(uint8_t *buf, size_t max_len);

/**
 * @name    AX5043 chunk structures.
 * @{
 */
/**
 * @brief   RSSI
 */
typedef struct __attribute__((packed)) {
    uint8_t                     header;
    uint8_t                     rssi;
} ax5043_chunk_rssi_t;

/**
 * @brief   TXCTRL
 */
typedef struct __attribute__((packed)) {
    uint8_t                     header;
    uint8_t                     flags;
} ax5043_chunk_txctrl_t;

/**
 * @brief   FREQOFFS
 */
typedef struct __attribute__((packed)) {
    uint8_t                     header;
    uint16_t                    freqoffs;
} ax5043_chunk_freqoffs_t;

/**
 * @brief   ANTRSSI2
 */
typedef struct __attribute__((packed)) {
    uint8_t                     header;
    uint8_t                     rssi;
    uint8_t                     bgndnoise;
} ax5043_chunk_antrssi2_t;

/**
 * @brief   REPEATDATA
 */
typedef struct __attribute__((packed)) {
    uint8_t                     header;
    uint8_t                     flags;
    uint8_t                     repeatcnt;
    uint8_t                     data;
} ax5043_chunk_repeatdata_t;

/**
 * @brief   TIMER
 */
typedef struct __attribute__((packed)) {
    uint8_t                     header;
    uint32_t                    timer;
} ax5043_chunk_timer_t;

/**
 * @brief   RFFREQOFFS
 */
typedef struct __attribute__((packed)) {
    uint8_t                     header;
    uint32_t                    rffreqoffs;
} ax5043_chunk_rffreqoffs_t;

/**
 * @brief   DATARATE
 */
typedef struct __attribute__((packed)) {
    uint8_t                     header;
    uint32_t                    datarate;
} ax5043_chunk_datarate_t;

/**
 * @brief   ANTRSSI3
 */
typedef struct __attribute__((packed)) {
    uint8_t                     header;
    uint8_t                     ant0rssi;
    uint8_t                     ant1rssi;
    uint8_t                     bgndnoise;
} ax5043_chunk_antrssi3_t;

/**
 * @brief   DATA
 */
typedef struct __attribute__((packed)) {
    uint8_t                     header;
    uint8_t                     length;
    uint8_t                     flags;
    uint8_t                     data[];
} ax5043_chunk_data_t;

/**
 * @brief   TXPWR
 */
typedef struct __attribute__((packed)) {
    uint8_t                     header;
    uint8_t                     length;
    uint16_t                    txpwrcoeffa;
    uint16_t                    txpwrcoeffb;
    uint16_t                    txpwrcoeffc;
    uint16_t                    txpwrcoeffd;
    uint16_t                    txpwrcoeffe;
} ax5043_chunk_txpwr_t;

/**
 * @brief   FIFO Chunk union type
 */
typedef union __attribute__((packed)) {
    struct {
        uint8_t                 header;
        uint8_t                 length;
    };
    ax5043_chunk_rssi_t         rssi;
    ax5043_chunk_txctrl_t       txctrl;
    ax5043_chunk_freqoffs_t     freqoffs;
    ax5043_chunk_antrssi2_t     antrssi2;
    ax5043_chunk_timer_t        timer;
    ax5043_chunk_rffreqoffs_t   rffreqoffs;
    ax5043_chunk_datarate_t     datarate;
    ax5043_chunk_antrssi3_t     antrssi3;
    ax5043_chunk_data_t         data;
    ax5043_chunk_txpwr_t        txpwr;
} ax5043_chunk_t;
/** @} */

/**
 * @brief   Mailbox structure for TX/RX
 */
typedef struct {
    size_t                      index;
    uint8_t                     data[AX5043_MAILBOX_SIZE];
} ax5043_mailbox_t;

/**
 * @brief   Structure containing a four byte sender X.25 address
 */
struct axradio_address {
    uint8_t addr[4];
};

/**
 * @brief  Ax5043 Register value pair type
 */
typedef struct {
    uint16_t reg;
    uint32_t val;
    size_t   len;
} ax5043_profile_t;

/**
 * TODO: Update brief to describe this
 * @brief   Other configuration values
 */
typedef struct {
    uint8_t conf_name;
    uint32_t val;
} ax5043_confval_t;

/**
 * @brief   Error codes
 */
typedef enum {
    AX5043_ERR_NOERROR,
    AX5043_ERR_NOTSUPPORTED,
    AX5043_ERR_BUSY,
    AX5043_ERR_TIMEOUT,
    AX5043_ERR_INVALID,
    AX5043_ERR_NOCHIP,
    AX5043_ERR_RANGING,
    AX5043_ERR_LOCKLOST,
    AX5043_ERR_RETRANSMISSION,
    AX5043_ERR_RESYNC,
    AX5043_ERR_RESYNCTIMEOUT,
    AX5043_ERR_RECEIVESTART,
    AX5043_ERR_FIFO_CHUNK,
    AX5043_ERR_FIFO_CMD,
    AX5043_ERR_UNEXPECTED_STATE,
    AX5043_ERR_NOT_CONNECTED,
    AX5043_ERR_REG_NOT_IN_CONF,
    AX5043_ERR_VAL_NOT_IN_CONF,
    AX5043_ERR_PLLRNG_VAL
} ax5043_err_t;

/**
 * @brief   Driver state machine possible states.
 */
typedef enum {
    AX5043_UNINIT,              /**< Not initialized.                   */
    AX5043_STOP,                /**< Stopped.                           */
    AX5043_RESET,               /**< Reset.                             */
    AX5043_READY,               /**< Ready.                             */
    AX5043_RX,
    AX5043_WOR,
    AX5043_RX_LOOP,             /**< In the middle of receiving packet. */
    AX5043_TX,
    AX5043_TX_LONGPREAMBLE,
    AX5043_TX_SHORTPREAMBLE,
    AX5043_TX_PACKET,
    AX5043_CW
} ax5043_state_t;

/**
 * @brief   AX5043 configuration structure.
 */
typedef struct{
#if (AX5043_USE_SPI) || defined(__DOXYGEN__)
    /**
     * @brief SPI driver associated with this AX5043.
     */
    SPIDriver                   *spip;
    /**
     * @brief SPI configuration associated with this AX5043.
     */
    const SPIConfig             *spicfg;
    /**
     * @brief PAL Line for MISO, to detect status of device
     */
    ioline_t                    miso;
#endif /* AX5043_USE_SPI */
    /**
     * @brief PAL Line for IRQ signal from radio
     */
    ioline_t                    irq;
    /**
     * @brief XTAL Frequency in Hz
     */
    uint32_t                    xtal_freq;
    /**
     * @brief Radio Address
     */
    uint32_t                    addr;
    /**
     * @brief Profile register values table
     * @note  This is for initial configuration and performance tuning.
     *        Certain registers may be overwritten later, either by
     *        the driver or a future call to @p ax5043SetProfile.
     */
    const ax5043_profile_t      *profile;

    ax5043_confval_t *conf_values;
} AX5043Config;

/**
 * @brief AX5043 Radio class.
 */
struct AX5043Driver {
    /* Driver state */
    ax5043_state_t              state;
    /* Current configuration data */
    const AX5043Config          *config;
    /* Status as of last exchange */
    ax5043_status_t             status;
    /* Error state of device */
    ax5043_err_t                error;
    /* IRQ worker thread */
    thread_t                    *irq_worker;
    /* IRQ event Source */
    event_source_t              irq_event;
    /* FIFO worker thread */
    thread_t                    *fifo_worker;
    /* TX buffer fill callback */
    ax5043_tx_cb_t              tx_cb;
    /* RX Mailbox buffer */
    ax5043_mailbox_t            mb_buf[AX5043_MAILBOX_COUNT];
    /* Filled Mailboxes */
    mailbox_t                   mb_filled;
    msg_t                       mb_filled_queue[AX5043_MAILBOX_COUNT];
    /* Free Mailboxes */
    mailbox_t                   mb_free;
    msg_t                       mb_free_queue[AX5043_MAILBOX_COUNT];

    /* Last VCOR returned from ranging */
    uint8_t                     vcora;
    uint8_t                     vcorb;

    /* RX information */
    uint32_t                    timer;
    uint32_t                    datarate;
    uint32_t                    freq_off;
    uint32_t                    rf_freq_off;
    uint8_t                     rssi;
    uint8_t                     ant0rssi;
    uint8_t                     ant1rssi;
    uint8_t                     bgndnoise;
    uint8_t                     dropped[250];
};
/** @} */

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

#define AX5043_FREQ_TO_REG(freq, ref)       (((freq * UINT64_C(0x2000000) + ref) / (ref * 2)) | 0x01U)
#define AX5043_REG_TO_FREQ(reg, ref)        (((reg & ~UINT64_C(1)) * ref) / UINT64_C(0x1000000))

/**
 * @brief  PHY and Framing details
 * TODO: Overhaul this stuff
 */
#define AX5043_PHY_PN9                     0
#define AX5043_PHY_NRCHANNELS              1
#define AX5043_PHY_CHANFREQ                2
#define AX5043_PHY_CHANPLLRNGINIT          3
#define AX5043_PHY_CHANVCOIINIT            4
#define AX5043_PHY_CHANPLLRNG              5
#define AX5043_PHY_CHANVCOI                6
#define AX5043_PHY_VCOCALIB                7
#define AX5043_PHY_MAXFREQOFFSET           8
#define AX5043_PHY_RSSIOFFSET              9
#define AX5043_PHY_RSSIREFERENCE           10
#define AX5043_PHY_CHANNELBUSY             11
#define AX5043_PHY_CS_PERIOD               12
#define AX5043_PHY_CS_ENABLED              13
#define AX5043_PHY_LBT_RETRIES             14
#define AX5043_PHY_LBT_FORCETX             15
#define AX5043_PHY_PREAMBLE_WOR_LONGLEN    16
#define AX5043_PHY_PREAMBLE_WOR_LEN        17
#define AX5043_PHY_PREAMBLE_LONGLEN        18
#define AX5043_PHY_PREAMBLE_LEN            19
#define AX5043_PHY_PREAMBLE_BYTE           20
#define AX5043_PHY_PREAMBLE_FLAGS          21
#define AX5043_PHY_PREAMBLE_APPENDBITS     22
#define AX5043_PHY_PREAMBLE_APPENDPATTERN  23
#define AX5043_FRAMING_MACLEN              24
#define AX5043_FRAMING_ADDRLEN             25
#define AX5043_FRAMING_DESTADDRPOS         26
#define AX5043_FRAMING_SOURCEADDRPOS       27
#define AX5043_FRAMING_LENPOS              28
#define AX5043_FRAMING_LENOFFS             29
#define AX5043_FRAMING_LENMASK             30
#define AX5043_FRAMING_SWCRCLEN            31
#define AX5043_FRAMING_SYNCLEN             32
#define AX5043_FRAMING_SYNCWORD0           33
#define AX5043_FRAMING_SYNCWORD1           34
#define AX5043_FRAMING_SYNCWORD2           35
#define AX5043_FRAMING_SYNCWORD3           36
#define AX5043_FRAMING_SYNCFLAGS           37
#define AX5043_FRAMING_ENABLE_SFDCALLBACK  38
#define AX5043_FRAMING_ACK_TIMEOUT         39
#define AX5043_FRAMING_ACK_DELAY           40
#define AX5043_FRAMING_ACK_RETRANSMISSIONS 41
#define AX5043_FRAMING_ACK_SEQNRPOS        42
#define AX5043_FRAMING_MINPAYLOADLEN       43
#define AX5043_WOR_PERIOD                  44
#define AX5043_PHY_INNERFREQLOOP           45
#define AX5043_PHY_END                     200

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
void ax5043ObjectInit(AX5043Driver *devp);
void ax5043Start(AX5043Driver *devp, const AX5043Config *config);
void ax5043Stop(AX5043Driver *devp);

void ax5043Idle(AX5043Driver *devp);
void ax5043RX(AX5043Driver *devp);
void ax5043WOR(AX5043Driver *devp);
void ax5043TX(AX5043Driver *devp, ax5043_tx_cb_t tx_cb);

void ax5043SetProfile(AX5043Driver *devp, const ax5043_profile_t *profile);
uint8_t ax5043SetFreq(AX5043Driver *devp, uint32_t freq, uint8_t vcor, bool chan_b);

ax5043_status_t ax5043Exchange(AX5043Driver *devp, uint16_t reg, bool write, const uint8_t *txbuf, uint8_t *rxbuf, size_t n);
ax5043_status_t ax5043GetStatus(AX5043Driver *devp);
uint8_t ax5043ReadU8(AX5043Driver *devp, uint16_t reg);
uint16_t ax5043ReadU16(AX5043Driver *devp, uint16_t reg);
uint32_t ax5043ReadU24(AX5043Driver *devp, uint16_t reg);
uint32_t ax5043ReadU32(AX5043Driver *devp, uint16_t reg);
void ax5043WriteU8(AX5043Driver *devp, uint16_t reg, uint8_t value);
void ax5043WriteU16(AX5043Driver *devp, uint16_t reg, uint16_t value);
void ax5043WriteU24(AX5043Driver *devp, uint16_t reg, uint32_t value);
void ax5043WriteU32(AX5043Driver *devp, uint16_t reg, uint32_t value);

/*===========================*/
/* TODO: START OVERHAUL HERE */
/*===========================*/

uint32_t ax5043_get_conf_val(AX5043Driver *devp, uint8_t conf_name);
uint8_t ax5043_set_conf_val(AX5043Driver *devp, uint8_t conf_name, uint32_t value);
void transmit_loop(AX5043Driver *devp, uint16_t axradio_txbuffer_len,uint8_t axradio_txbuffer[]);
uint8_t transmit_packet(AX5043Driver *devp, const struct axradio_address *addr, const uint8_t *pkt, uint16_t pktlen);
uint8_t receive_loop(AX5043Driver *devp, uint8_t axradio_rxbuffer[]);

void ax5043_morse_dot_dash(AX5043Driver *devp, uint16_t dot_dash_time);
const char *ax5043_ascii_to_morse(char letter);
void ax5043_send_cw(AX5043Driver *devp, int wpm, char beaconMessage[], uint16_t pktlen );
#ifdef __cplusplus
}
#endif

#endif /* _AX5043_H_ */

/** @} */
