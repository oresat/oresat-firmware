/**
 * @file    max17205.h
 * @brief   MAX17205 Power Monitor.
 *
 * @addtogroup MAX17205
 * @ingroup ORESAT
 * @{
 */
#ifndef _MAX17205_H_
#define _MAX17205_H_

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @name    Version Identification
 * @{
 */
/**
 * @brief   MAX17205 Driver version string.
 */
#define MAX17205_VERSION                    "1.0.0"

/**
 * @brief   MAX17205 Driver version major number.
 */
#define MAX17205_MAJOR                      1

/**
 * @brief   MAX17205 Driver version minor number.
 */
#define MAX17205_MINOR                      0

/**
 * @brief   MAX17205 Driver version patch number.
 */
#define MAX17205_PATCH                      0
/** @} */

/**
 * @brief   MAX17205 Slave Addresses
 */
#define MAX17205_SA_MG_M5                   0x6CU
#define MAX17205_SA_SBS_NV                  0x16U
/** @} */

/**
 * @name    MAX17205 Register Addresses
 * TODO: Enumerate remaining register addresses
 * @{
 */
#define MAX17205_AD_STATUS                  0x000U
#define MAX17205_AD_VALRTTH                 0x001U  /* TODO: Define fields */
#define MAX17205_AD_TALRTTH                 0x002U  /* TODO: Define fields */
#define MAX17205_AD_SALRTTH                 0x003U  /* TODO: Define fields */
#define MAX17205_AD_ATRATE                  0x004U
#define MAX17205_AD_REPCAP                  0x005U
#define MAX17205_AD_REPSOC                  0x006U
#define MAX17205_AD_AGE                     0x007U
#define MAX17205_AD_TEMP                    0x008U
#define MAX17205_AD_VCELL                   0x009U
#define MAX17205_AD_CURRENT                 0x00AU
#define MAX17205_AD_AVGCURRENT              0x00BU
#define MAX17205_AD_QRESIDUAL               0x00CU
#define MAX17205_AD_MIXSOC                  0x00DU
#define MAX17205_AD_AVSOC                   0x00EU
#define MAX17205_AD_MIXCAP                  0x00FU
#define MAX17205_AD_FULLCAP                 0x010U
#define MAX17205_AD_TTE                     0x011U
#define MAX17205_AD_QRTABLE00               0x012U
#define MAX17205_AD_FULLSOCTHR              0x013U  /* TODO: Define fields */
#define MAX17205_AD_RCELL                   0x014U
#define MAX17205_AD_RFAST                   0x015U
#define MAX17205_AD_AVGTA                   0x016U
#define MAX17205_AD_CYCLES                  0x017U
#define MAX17205_AD_DESIGNCAP               0x018U
#define MAX17205_AD_AVGVCELL                0x019U
#define MAX17205_AD_MAXMINTEMP              0x01AU  /* TODO: Define fields */
#define MAX17205_AD_MAXMINVOLT              0x01BU  /* TODO: Define fields */
#define MAX17205_AD_MAXMINCURR              0x01CU  /* TODO: Define fields */
#define MAX17205_AD_CONFIG                  0x01DU
#define MAX17205_AD_ICHGTERM                0x01EU
#define MAX17205_AD_AVCAP                   0x01FU
#define MAX17205_AD_TTF                     0x020U
#define MAX17205_AD_DEVNAME                 0x021U  /* TODO: Define fields */
#define MAX17205_AD_QRTABLE10               0x022U
#define MAX17205_AD_FULLCAPNOM              0x023U
#define MAX17205_AD_AIN0                    0x027U
#define MAX17205_AD_LEARNCFG                0x028U
#define MAX17205_AD_FILTERCFG               0x029U  /* TODO: Define fields */
#define MAX17205_AD_RELAXCFG                0x02AU  /* TODO: Define fields */
#define MAX17205_AD_MISCCFG                 0x02BU  /* TODO: Define fields */
#define MAX17205_AD_TGAIN                   0x02CU  /* TODO: Define fields */
#define MAX17205_AD_TOFF                    0x02DU  /* TODO: Define fields */
#define MAX17205_AD_CGAIN                   0x02EU  /* TODO: Define fields */
#define MAX17205_AD_COFF                    0x02FU  /* TODO: Define fields */
#define MAX17205_AD_QRTABLE20               0x032U
#define MAX17205_AD_FULLCAPREP              0x035U
#define MAX17205_AD_IAVGEMPTY               0x036U
#define MAX17205_AD_RCOMP0                  0x038U
#define MAX17205_AD_TEMPCO                  0x039U
#define MAX17205_AD_VEMPTY                  0x03AU  /* TODO: Define fields */
#define MAX17205_AD_FSTAT                   0x03DU  /* TODO: Define fields */
#define MAX17205_AD_TIMER                   0x03EU
#define MAX17205_AD_SHDNTIMER               0x03FU  /* TODO: Define fields */
#define MAX17205_AD_QRTABLE30               0x042U
#define MAX17205_AD_DQACC                   0x045U
#define MAX17205_AD_DPACC                   0x046U
#define MAX17205_AD_VFREMCAP                0x04AU
#define MAX17205_AD_QH                      0x04DU
#define MAX17205_AD_COMMAND                 0x060U  /* TODO: Define commands */
#define MAX17205_AD_COMMSTAT                0x061U  /* TODO: Define fields */
#define MAX17205_AD_LOCK                    0x07FU  /* TODO: Define fields */
#define MAX17205_AD_STATUS2                 0x0B0U
#define MAX17205_AD_IALRTTH                 0x0B4U  /* TODO: Define fields */
#define MAX17205_AD_VSHDNCFG                0x0B8U
#define MAX17205_AD_AGEFORECAST             0x0B9U
#define MAX17205_AD_HIBCFG                  0x0BAU  /* TODO: Define fields */
#define MAX17205_AD_CONFIG2                 0x0BBU
#define MAX17205_AD_VRIPPLE                 0x0BCU
#define MAX17205_AD_PACKCFG                 0x0BDU  /* TODO: Define fields */
#define MAX17205_AD_TIMERH                  0x0BEU
#define MAX17205_AD_ATAVSOC                 0x0CEU
#define MAX17205_AD_AVGCELL4                0x0D1U
#define MAX17205_AD_AVGCELL3                0x0D2U
#define MAX17205_AD_AVGCELL2                0x0D3U
#define MAX17205_AD_AVGCELL1                0x0D4U
#define MAX17205_AD_CELL4                   0x0D5U
#define MAX17205_AD_CELL3                   0x0D6U
#define MAX17205_AD_CELL2                   0x0D7U
#define MAX17205_AD_CELL1                   0x0D8U
#define MAX17205_AD_CELLX                   0x0D9U
#define MAX17205_AD_BATT                    0x0DAU
#define MAX17205_AD_ATQRESIDUAL             0x0DCU
#define MAX17205_AD_ATTTE                   0x0DDU
#define MAX17205_AD_ATAVSOC                 0x0DEU
#define MAX17205_AD_ATAVCAP                 0x0DFU
#define MAX17205_AD_ODSCTH                  0x0F2U  /* TODO: Define fields */
#define MAX17205_AD_ODSCCFG                 0x0F3U  /* TODO: Define fields */
#define MAX17205_AD_VFOCV                   0x0FBU
#define MAX17205_AD_VFSOC                   0x0FFU
#define MAX17205_AD_TEMP1                   0x134U
#define MAX17205_AD_INTTEMP                 0x135U
#define MAX17205_AD_AVGTEMP1                0x137U
#define MAX17205_AD_AVGINTTEMP              0x138U
#define MAX17205_AD_AVGTEMP2                0x139U
#define MAX17205_AD_TEMP2                   0x13BU
#define MAX17205_AD_CGTEMPCO                0x16DU
#define MAX17205_AD_NXTABLE0                0x180U
#define MAX17205_AD_NXTABLE1                0x181U
#define MAX17205_AD_NXTABLE2                0x182U
#define MAX17205_AD_NXTABLE3                0x183U
#define MAX17205_AD_NXTABLE4                0x184U
#define MAX17205_AD_NXTABLE5                0x185U
#define MAX17205_AD_NXTABLE6                0x186U
#define MAX17205_AD_NXTABLE7                0x187U
#define MAX17205_AD_NXTABLE8                0x188U
#define MAX17205_AD_NXTABLE9                0x189U
#define MAX17205_AD_NXTABLE10               0x18AU
#define MAX17205_AD_NXTABLE11               0x18BU
#define MAX17205_AD_NUSER18C                0x18CU
#define MAX17205_AD_NUSER18D                0x18DU
#define MAX17205_AD_NODSCTH                 0x18EU  /* TODO: Define fields */
#define MAX17205_AD_NODSCCFG                0x18FU  /* TODO: Define fields */
#define MAX17205_AD_NOCVTABLE0              0x190U
#define MAX17205_AD_NOCVTABLE1              0x191U
#define MAX17205_AD_NOCVTABLE2              0x192U
#define MAX17205_AD_NOCVTABLE3              0x193U
#define MAX17205_AD_NOCVTABLE4              0x194U
#define MAX17205_AD_NOCVTABLE5              0x195U
#define MAX17205_AD_NOCVTABLE6              0x196U
#define MAX17205_AD_NOCVTABLE7              0x197U
#define MAX17205_AD_NOCVTABLE8              0x198U
#define MAX17205_AD_NOCVTABLE9              0x199U
#define MAX17205_AD_NOCVTABLE10             0x19AU
#define MAX17205_AD_NOCVTABLE11             0x19BU
#define MAX17205_AD_NICHGTERM               0x19CU
#define MAX17205_AD_NFILTERCFG              0x19DU  /* TODO: Define fields */
#define MAX17205_AD_NVEMPTY                 0x19EU  /* TODO: Define fields */
#define MAX17205_AD_NLEARNCFG               0x19FU
#define MAX17205_AD_NQRTABLE00              0x1A0U
#define MAX17205_AD_NQRTABLE10              0x1A1U
#define MAX17205_AD_NQRTABLE20              0x1A2U
#define MAX17205_AD_NQRTABLE30              0x1A3U
#define MAX17205_AD_NCYCLES                 0x1A4U
#define MAX17205_AD_NFULLCAPNOM             0x1A5U
#define MAX17205_AD_NRCOMP0                 0x1A6U
#define MAX17205_AD_NTEMPCO                 0x1A7U
#define MAX17205_AD_NIAVGEMPTY              0x1A8U
#define MAX17205_AD_NFULLCAPREP             0x1A9U
#define MAX17205_AD_NVOLTTEMP               0x1AAU
#define MAX17205_AD_NMAXMINCURR             0x1ABU  /* TODO: Define fields */
#define MAX17205_AD_NMAXMINVOLT             0x1ACU  /* TODO: Define fields */
#define MAX17205_AD_NMAXMINTEMP             0x1ADU  /* TODO: Define fields */
#define MAX17205_AD_NSOC                    0x1AEU
#define MAX17205_AD_NTIMERH                 0x1AFU
#define MAX17205_AD_NCONFIG                 0x1B0U  /* TODO: Define fields */
#define MAX17205_AD_NRIPPLECFGCFG           0x1B1U  /* TODO: Define fields */
#define MAX17205_AD_NMISCCFG                0x1B2U  /* TODO: Define fields */
#define MAX17205_AD_NDESIGNCAP              0x1B3U
#define MAX17205_AD_NHIBCFG                 0x1B4U  /* TODO: Define fields */
#define MAX17205_AD_NPACKCFG                0x1B5U  /* TODO: Define fields */
#define MAX17205_AD_NRELAXCFG               0x1B6U  /* TODO: Define fields */
#define MAX17205_AD_NCONVGCFG               0x1B7U  /* TODO: Define fields */
#define MAX17205_AD_NNVCFG0                 0x1B8U  /* TODO: Define fields */
#define MAX17205_AD_NNVCFG1                 0x1B9U  /* TODO: Define fields */
#define MAX17205_AD_NNVCFG2                 0x1BAU  /* TODO: Define fields */
#define MAX17205_AD_NSBSCFG                 0x1BBU  /* TODO: Define fields */
#define MAX17205_AD_NROMID0                 0x1BCU
#define MAX17205_AD_NROMID1                 0x1BDU
#define MAX17205_AD_NROMID2                 0x1BEU
#define MAX17205_AD_NROMID3                 0x1BFU
#define MAX17205_AD_NVALRTTH                0x1C0U  /* TODO: Define fields */
#define MAX17205_AD_NTALRTTH                0x1C1U  /* TODO: Define fields */
#define MAX17205_AD_NSALRTTH                0x1C2U  /* TODO: Define fields */
#define MAX17205_AD_NIALRTTH                0x1C3U  /* TODO: Define fields */
#define MAX17205_AD_NFULLSOCTHR             0x1C6U  /* TODO: Define fields */
#define MAX17205_AD_NTTFCFG                 0x1C7U  /* TODO: Define fields */
#define MAX17205_AD_NCGAIN                  0x1C8U  /* TODO: Define fields */
#define MAX17205_AD_NTCURVE                 0x1C9U  /* TODO: Define fields */
#define MAX17205_AD_NTGAIN                  0x1CAU  /* TODO: Define fields */
#define MAX17205_AD_NTOFF                   0x1CBU  /* TODO: Define fields */
#define MAX17205_AD_NMANFCTRNAME0           0x1CCU
#define MAX17205_AD_NMANFCTRNAME1           0x1CDU
#define MAX17205_AD_NMANFCTRNAME2           0x1CEU
#define MAX17205_AD_NRSENSE                 0x1CFU
#define MAX17205_AD_NUSER1D0                0x1D0U
#define MAX17205_AD_NUSER1D1                0x1D1U
#define MAX17205_AD_NAGEFCCFG               0x1D2U
#define MAX17205_AD_NDESIGNVOLTAGE          0x1D3U
#define MAX17205_AD_NUSER1D4                0x1D4U
#define MAX17205_AD_NRFASTVSHDN             0x1D5U  /* TODO: Define fields */
#define MAX17205_AD_NMANFCTRDATE            0x1D6U
#define MAX17205_AD_NFIRSTUSED              0x1D7U
#define MAX17205_AD_NSERIALNUMBER0          0x1D8U
#define MAX17205_AD_NSERIALNUMBER1          0x1D9U
#define MAX17205_AD_NSERIALNUMBER2          0x1DAU
#define MAX17205_AD_NDEVICENAME0            0x1DBU
#define MAX17205_AD_NDEVICENAME1            0x1DCU
#define MAX17205_AD_NDEVICENAME2            0x1DDU
#define MAX17205_AD_NDEVICENAME3            0x1DEU
#define MAX17205_AD_NDEVICENAME4            0x1DFU
/** @} */

/**
 * @name    MAX17205 Status register fields
 * @{
 */
#define MAX17205_STATUS_POR_Pos             (1U)
#define MAX17205_STATUS_POR_Msk             (0x1U << MAX17205_STATUS_POR_Pos)
#define MAX17205_STATUS_POR                 MAX17205_STATUS_POR_Msk
#define MAX17205_STATUS_IMN_Pos             (2U)
#define MAX17205_STATUS_IMN_Msk             (0x1U << MAX17205_STATUS_IMN_Pos)
#define MAX17205_STATUS_IMN                 MAX17205_STATUS_IMN_Msk
#define MAX17205_STATUS_BST_Pos             (4U)
#define MAX17205_STATUS_BST_Msk             (0x1U << MAX17205_STATUS_BST_Pos)
#define MAX17205_STATUS_BST                 MAX17205_STATUS_BST_Msk
#define MAX17205_STATUS_IMX_Pos             (6U)
#define MAX17205_STATUS_IMX_Msk             (0x1U << MAX17205_STATUS_IMX_Pos)
#define MAX17205_STATUS_IMX                 MAX17205_STATUS_IMX_Msk
#define MAX17205_STATUS_DSOCI_Pos           (7U)
#define MAX17205_STATUS_DSOCI_Msk           (0x1U << MAX17205_STATUS_DSOCI_Pos)
#define MAX17205_STATUS_DSOCI               MAX17205_STATUS_DSOCI_Msk
#define MAX17205_STATUS_VMN_Pos             (8U)
#define MAX17205_STATUS_VMN_Msk             (0x1U << MAX17205_STATUS_VMN_Pos)
#define MAX17205_STATUS_VMN                 MAX17205_STATUS_VMN_Msk
#define MAX17205_STATUS_TMN_Pos             (9U)
#define MAX17205_STATUS_TMN_Msk             (0x1U << MAX17205_STATUS_TMN_Pos)
#define MAX17205_STATUS_TMN                 MAX17205_STATUS_TMN_Msk
#define MAX17205_STATUS_SMN_Pos             (10U)
#define MAX17205_STATUS_SMN_Msk             (0x1U << MAX17205_STATUS_SMN_Pos)
#define MAX17205_STATUS_SMN                 MAX17205_STATUS_SMN_Msk
#define MAX17205_STATUS_BI_Pos              (11U)
#define MAX17205_STATUS_BI_Msk              (0x1U << MAX17205_STATUS_BI_Pos)
#define MAX17205_STATUS_BI                  MAX17205_STATUS_BI_Msk
#define MAX17205_STATUS_VMX_Pos             (12U)
#define MAX17205_STATUS_VMX_Msk             (0x1U << MAX17205_STATUS_VMX_Pos)
#define MAX17205_STATUS_VMX                 MAX17205_STATUS_VMX_Msk
#define MAX17205_STATUS_TMX_Pos             (13U)
#define MAX17205_STATUS_TMX_Msk             (0x1U << MAX17205_STATUS_TMX_Pos)
#define MAX17205_STATUS_TMX                 MAX17205_STATUS_TMX_Msk
#define MAX17205_STATUS_SMX_Pos             (14U)
#define MAX17205_STATUS_SMX_Msk             (0x1U << MAX17205_STATUS_SMX_Pos)
#define MAX17205_STATUS_SMX                 MAX17205_STATUS_SMX_Msk
#define MAX17205_STATUS_BR_Pos              (15U)
#define MAX17205_STATUS_BR_Msk              (0x1U << MAX17205_STATUS_BR_Pos)
#define MAX17205_STATUS_BR                  MAX17205_STATUS_BR_Msk
/** @} */

/**
 * @name    MAX17205 Command register values
 * TODO: Enumerate remaining commands
 * @{
 */
#define MAX17205_COMMAND_RST                0x000FU
/** @} */

/**
 * @name    MAX17205 Config register fields
 * @{
 */
#define MAX17205_CONFIG_BER_Pos             (0U)
#define MAX17205_CONFIG_BER_Msk             (0x1U << MAX17205_CONFIG_BER_Pos)
#define MAX17205_CONFIG_BER                 MAX17205_CONFIG_BER_Msk
#define MAX17205_CONFIG_BEI_Pos             (1U)
#define MAX17205_CONFIG_BEI_Msk             (0x1U << MAX17205_CONFIG_BEI_Pos)
#define MAX17205_CONFIG_BEI                 MAX17205_CONFIG_BEI_Msk
#define MAX17205_CONFIG_AEN_Pos             (2U)
#define MAX17205_CONFIG_AEN_Msk             (0x1U << MAX17205_CONFIG_AEN_Pos)
#define MAX17205_CONFIG_AEN                 MAX17205_CONFIG_AEN_Msk
#define MAX17205_CONFIG_FTHRM_Pos           (3U)
#define MAX17205_CONFIG_FTHRM_Msk           (0x1U << MAX17205_CONFIG_FTHRM_Pos)
#define MAX17205_CONFIG_FTHRM               MAX17205_CONFIG_FTHRM_Msk
#define MAX17205_CONFIG_ETHRM_Pos           (4U)
#define MAX17205_CONFIG_ETHRM_Msk           (0x1U << MAX17205_CONFIG_ETHRM_Pos)
#define MAX17205_CONFIG_ETHRM               MAX17205_CONFIG_ETHRM_Msk
#define MAX17205_CONFIG_COMMSH_Pos          (6U)
#define MAX17205_CONFIG_COMMSH_Msk          (0x1U << MAX17205_CONFIG_COMMSH_Pos)
#define MAX17205_CONFIG_COMMSH              MAX17205_CONFIG_COMMSH_Msk
#define MAX17205_CONFIG_SHDN_Pos            (7U)
#define MAX17205_CONFIG_SHDN_Msk            (0x1U << MAX17205_CONFIG_SHDN_Pos)
#define MAX17205_CONFIG_SHDN                MAX17205_CONFIG_SHDN_Msk
#define MAX17205_CONFIG_TEX_Pos             (8U)
#define MAX17205_CONFIG_TEX_Msk             (0x1U << MAX17205_CONFIG_TEX_Pos)
#define MAX17205_CONFIG_TEX                 MAX17205_CONFIG_TEX_Msk
#define MAX17205_CONFIG_TEN_Pos             (9U)
#define MAX17205_CONFIG_TEN_Msk             (0x1U << MAX17205_CONFIG_TEN_Pos)
#define MAX17205_CONFIG_TEN                 MAX17205_CONFIG_TEN_Msk
#define MAX17205_CONFIG_AINSH_Pos           (10U)
#define MAX17205_CONFIG_AINSH_Msk           (0x1U << MAX17205_CONFIG_AINSH_Pos)
#define MAX17205_CONFIG_AINSH               MAX17205_CONFIG_AINSH_Msk
#define MAX17205_CONFIG_ALRTP_Pos           (11U)
#define MAX17205_CONFIG_ALRTP_Msk           (0x1U << MAX17205_CONFIG_ALRTP_Pos)
#define MAX17205_CONFIG_ALRTP               MAX17205_CONFIG_ALRTP_Msk
#define MAX17205_CONFIG_VS_Pos              (12U)
#define MAX17205_CONFIG_VS_Msk              (0x1U << MAX17205_CONFIG_VS_Pos)
#define MAX17205_CONFIG_VS                  MAX17205_CONFIG_VS_Msk
#define MAX17205_CONFIG_TS_Pos              (13U)
#define MAX17205_CONFIG_TS_Msk              (0x1U << MAX17205_CONFIG_TS_Pos)
#define MAX17205_CONFIG_TS                  MAX17205_CONFIG_TS_Msk
#define MAX17205_CONFIG_SS_Pos              (14U)
#define MAX17205_CONFIG_SS_Msk              (0x1U << MAX17205_CONFIG_SS_Pos)
#define MAX17205_CONFIG_SS                  MAX17205_CONFIG_SS_Msk
/** @} */

/**
 * @name    MAX17205 Config2 register fields
 * @{
 */
#define MAX17205_CONFIG2_POR_CMD_Pos        (0U)
#define MAX17205_CONFIG2_POR_CMD_Msk        (0x1U << MAX17205_CONFIG2_POR_CMD_Pos)
#define MAX17205_CONFIG2_POR_CMD            MAX17205_CONFIG2_POR_CMD_Msk
#define MAX17205_CONFIG2_TALRTEN_Pos        (6U)
#define MAX17205_CONFIG2_TALRTEN_Msk        (0x1U << MAX17205_CONFIG2_TALRTEN_Pos)
#define MAX17205_CONFIG2_TALRTEN            MAX17205_CONFIG2_TALRTEN_Msk
#define MAX17205_CONFIG2_DSOCEN_Pos         (7U)
#define MAX17205_CONFIG2_DSOCEN_Msk         (0x1U << MAX17205_CONFIG2_DSOCEN_Pos)
#define MAX17205_CONFIG2_DSOCEN             MAX17205_CONFIG2_DSOCEN_Msk
/** @} */

/**
 * @name    MAX17205 nSOC register fields
 * @{
 */
#define MAX17205_NSOC_VFSOC_UPPER_Pos       (0U)
#define MAX17205_NSOC_VFSOC_UPPER_Msk       (0xFFU << MAX17205_NSOC_VFSOC_UPPER_Pos)
#define MAX17205_NSOC_VFSOC_UPPER           MAX17205_NSOC_VFSOC_UPPER_Msk
#define MAX17205_NSOC_MIXSOC_UPPER_Pos      (8U)
#define MAX17205_NSOC_MIXSOC_UPPER_Msk      (0xFFU << MAX17205_NSOC_MIXSOC_UPPER_Pos)
#define MAX17205_NSOC_MIXSOC_UPPER          MAX17205_NSOC_MIXSOC_UPPER_Msk
/** @} */

/**
 * @name    MAX17205 nVoltTemp register fields
 * @{
 */
#define MAX17205_NVOLTTEMP_AVGTA_UPPER_Pos  (0U)
#define MAX17205_NVOLTTEMP_AVGTA_UPPER_Msk  (0x7FU << MAX17205_NVOLTTEMP_AVGTA_UPPER_Pos)
#define MAX17205_NVOLTTEMP_AVGTA_UPPER      MAX17205_NVOLTTEMP_AVGTA_UPPER_Msk
#define MAX17205_NVOLTTEMP_AVGVCELL_UPPER_Pos (7U)
#define MAX17205_NVOLTTEMP_AVGVCELL_UPPER_Msk (0x1FFU << MAX17205_NVOLTTEMP_AVGVCELL_UPPER_Pos)
#define MAX17205_NVOLTTEMP_AVGVCELL_UPPER     MAX17205_NVOLTTEMP_AVGVCELL_UPPER_Msk
/** @} */

/**
 * @name    MAX17205 nAgeFcCfg register fields
 * @{
 */
#define MAX17205_NAGEFCCFG_SETBITS_Pos      (0U)
#define MAX17205_NAGEFCCFG_SETBITS_Msk      (0x1FU << MAX17205_NAGEFCCFG_SETBITS_Pos)
#define MAX17205_NAGEFCCFG_SETBITS          MAX17205_NAGEFCCFG_SETBITS_Msk
#define MAX17205_NAGEFCCFG_SETBITS_VAL      (0x03U)
#define MAX17205_NAGEFCCFG_CYCLESTART_Pos   (5U)
#define MAX17205_NAGEFCCFG_CYCLESTART_Msk   (0x7FU << MAX17205_NAGEFCCFG_CYCLESTART_Pos)
#define MAX17205_NAGEFCCFG_CYCLESTART       MAX17205_NAGEFCCFG_CYCLESTART_Msk
#define MAX17205_NAGEFCCFG_DEADTGTRATIO_Pos (12U)
#define MAX17205_NAGEFCCFG_DEADTGTRATIO_Msk (0xFU << MAX17205_NAGEFCCFG_DEADTGTRATIO_Pos)
#define MAX17205_NAGEFCCFG_DEADTGTRATIO     MAX17205_NAGEFCCFG_DEADTGTRATIO_Msk
/** @} */

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    Configuration options
 * @{
 */
/**
 * @brief   MAX17205 I2C interface switch.
 * @details If set to @p TRUE the support for I2C is included.
 * @note    The default is @p TRUE.
 */
#if !defined(MAX17205_USE_I2C) || defined(__DOXYGEN__)
#define MAX17205_USE_I2C                    TRUE
#endif

/**
 * @brief   MAX17205 shared I2C switch.
 * @details If set to @p TRUE the device acquires I2C bus ownership
 *          on each transaction.
 * @note    The default is @p FALSE. Requires I2C_USE_MUTUAL_EXCLUSION.
 */
#if !defined(MAX17205_SHARED_I2C) || defined(__DOXYGEN__)
#define MAX17205_SHARED_I2C                 FALSE
#endif
/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

#if MAX17205_USE_I2C && !HAL_USE_I2C
#error "MAX17205_USE_I2C requires HAL_USE_I2C"
#endif

#if MAX17205_SHARED_I2C && !I2C_USE_MUTUAL_EXCLUSION
#error "MAX17205_SHARED_I2C requires I2C_USE_MUTUAL_EXCLUSION"
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @name    MAX17205 data structures and types.
 * @{
 */
/**
 * @brief Structure representing a MAX17205 driver.
 */
typedef struct MAX17205Driver MAX17205Driver;

/**
 * @brief   Driver state machine possible states.
 */
typedef enum {
    MAX17205_UNINIT = 0,                /**< Not initialized.                */
    MAX17205_STOP = 1,                  /**< Stopped.                        */
    MAX17205_READY = 2,                 /**< Ready.                          */
} max17205_state_t;

/**
 * @brief   MAX17205 configuration structure.
 */
typedef struct {
#if (MAX17205_USE_I2C) || defined(__DOXYGEN__)
    /**
     * @brief I2C driver associated with this MAX17205.
     */
    I2CDriver                   *i2cp;
    /**
     * @brief I2C configuration associated with this MAX17205.
     */
    const I2CConfig             *i2ccfg;
#endif /* MAX17205_USE_I2C */
} MAX17205Config;

/**
 * @brief   @p MAX17205 specific methods.
 */
#define _max17205_methods_alone

/**
 * @brief   @p MAX17205 specific methods with inherited ones.
 */
#define _max17205_methods                                                   \
    _base_object_methods

/**
 * @extends BaseObjectVMT
 *
 * @brief   @p MAX17205 virtual methods table.
 */
struct MAX17205VMT {
    _max17205_methods
};

/**
 * @brief   @p MAX17205Driver specific data.
 */
#define _max17205_data                                                      \
    _base_object_data                                                       \
    /* Driver state.*/                                                      \
    max17205_state_t              state;                                    \
    /* Current configuration data.*/                                        \
    const MAX17205Config          *config;

/**
 * @brief MAX17205 Power Monitor class.
 */
struct MAX17205Driver {
    /** @brief Virtual Methods Table.*/
    const struct MAX17205VMT     *vmt;
    _max17205_data
};

/** @} */

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
void max17205ObjectInit(MAX17205Driver *devp);
void max17205Start(MAX17205Driver *devp, const MAX17205Config *config);
void max17205Stop(MAX17205Driver *devp);
#ifdef __cplusplus
}
#endif

#endif /* _MAX17205_H_ */

/** @} */
