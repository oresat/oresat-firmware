/*  MAX17205 Power Monitor  */
#ifndef _MAX17205_H_
#define _MAX17205_H_

#define MAX17205_T_RECAL_MS      5
//tBlock(max) is specified as 7360ms in the data sheet, page 16
#define MAX17205_T_BLOCK_MS      8000
#define MAX17205_T_POR_MS        10

/**
 * @name    MAX17205 Register Addresses
 * @{
 */
#define MAX17205_AD_STATUS                  0x000U
#define MAX17205_AD_VALRTTH                 0x001U
#define MAX17205_AD_TALRTTH                 0x002U
#define MAX17205_AD_SALRTTH                 0x003U
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
#define MAX17205_AD_FULLSOCTHR              0x013U
#define MAX17205_AD_RCELL                   0x014U
#define MAX17205_AD_RFAST                   0x015U
#define MAX17205_AD_AVGTA                   0x016U
#define MAX17205_AD_CYCLES                  0x017U
#define MAX17205_AD_DESIGNCAP               0x018U
#define MAX17205_AD_AVGVCELL                0x019U
#define MAX17205_AD_MAXMINTEMP              0x01AU
#define MAX17205_AD_MAXMINVOLT              0x01BU
#define MAX17205_AD_MAXMINCURR              0x01CU
#define MAX17205_AD_CONFIG                  0x01DU
#define MAX17205_AD_ICHGTERM                0x01EU
#define MAX17205_AD_AVCAP                   0x01FU
#define MAX17205_AD_TTF                     0x020U
#define MAX17205_AD_DEVNAME                 0x021U
#define MAX17205_AD_QRTABLE10               0x022U
#define MAX17205_AD_FULLCAPNOM              0x023U
#define MAX17205_AD_AIN0                    0x027U
#define MAX17205_AD_LEARNCFG                0x028U
#define MAX17205_AD_FILTERCFG               0x029U
#define MAX17205_AD_RELAXCFG                0x02AU
#define MAX17205_AD_MISCCFG                 0x02BU
#define MAX17205_AD_TGAIN                   0x02CU
#define MAX17205_AD_TOFF                    0x02DU
#define MAX17205_AD_CGAIN                   0x02EU
#define MAX17205_AD_COFF                    0x02FU
#define MAX17205_AD_QRTABLE20               0x032U
#define MAX17205_AD_FULLCAPREP              0x035U
#define MAX17205_AD_IAVGEMPTY               0x036U
#define MAX17205_AD_RCOMP0                  0x038U
#define MAX17205_AD_TEMPCO                  0x039U
#define MAX17205_AD_VEMPTY                  0x03AU
#define MAX17205_AD_FSTAT                   0x03DU
#define MAX17205_AD_TIMER                   0x03EU
#define MAX17205_AD_SHDNTIMER               0x03FU
#define MAX17205_AD_QRTABLE30               0x042U
#define MAX17205_AD_DQACC                   0x045U
#define MAX17205_AD_DPACC                   0x046U
#define MAX17205_AD_VFREMCAP                0x04AU
#define MAX17205_AD_QH                      0x04DU
#define MAX17205_AD_COMMAND                 0x060U
#define MAX17205_AD_COMMSTAT                0x061U
#define MAX17205_AD_LOCK                    0x07FU
#define MAX17205_AD_STATUS2                 0x0B0U
#define MAX17205_AD_IALRTTH                 0x0B4U
#define MAX17205_AD_VSHDNCFG                0x0B8U
#define MAX17205_AD_AGEFORECAST             0x0B9U
#define MAX17205_AD_HIBCFG                  0x0BAU
#define MAX17205_AD_CONFIG2                 0x0BBU
#define MAX17205_AD_VRIPPLE                 0x0BCU
#define MAX17205_AD_PACKCFG                 0x0BDU
#define MAX17205_AD_TIMERH                  0x0BEU
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
#define MAX17205_AD_ODSCTH                  0x0F2U
#define MAX17205_AD_ODSCCFG                 0x0F3U
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
#define MAX17205_AD_NODSCTH                 0x18EU
#define MAX17205_AD_NODSCCFG                0x18FU
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
#define MAX17205_AD_NFILTERCFG              0x19DU
#define MAX17205_AD_NVEMPTY                 0x19EU
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
#define MAX17205_AD_NMAXMINCURR             0x1ABU
#define MAX17205_AD_NMAXMINVOLT             0x1ACU
#define MAX17205_AD_NMAXMINTEMP             0x1ADU
#define MAX17205_AD_NSOC                    0x1AEU
#define MAX17205_AD_NTIMERH                 0x1AFU
#define MAX17205_AD_NCONFIG                 0x1B0U
#define MAX17205_AD_NRIPPLECFGCFG           0x1B1U
#define MAX17205_AD_NMISCCFG                0x1B2U
#define MAX17205_AD_NDESIGNCAP              0x1B3U
#define MAX17205_AD_NHIBCFG                 0x1B4U
#define MAX17205_AD_NPACKCFG                0x1B5U
#define MAX17205_AD_NRELAXCFG               0x1B6U
#define MAX17205_AD_NCONVGCFG               0x1B7U
#define MAX17205_AD_NNVCFG0                 0x1B8U
#define MAX17205_AD_NNVCFG1                 0x1B9U
#define MAX17205_AD_NNVCFG2                 0x1BAU
#define MAX17205_AD_NSBSCFG                 0x1BBU
#define MAX17205_AD_NROMID0                 0x1BCU
#define MAX17205_AD_NROMID1                 0x1BDU
#define MAX17205_AD_NROMID2                 0x1BEU
#define MAX17205_AD_NROMID3                 0x1BFU
#define MAX17205_AD_NVALRTTH                0x1C0U
#define MAX17205_AD_NTALRTTH                0x1C1U
#define MAX17205_AD_NSALRTTH                0x1C2U
#define MAX17205_AD_NIALRTTH                0x1C3U
#define MAX17205_AD_NFULLSOCTHR             0x1C6U
#define MAX17205_AD_NTTFCFG                 0x1C7U
#define MAX17205_AD_NCGAIN                  0x1C8U
#define MAX17205_AD_NTCURVE                 0x1C9U
#define MAX17205_AD_NTGAIN                  0x1CAU
#define MAX17205_AD_NTOFF                   0x1CBU
#define MAX17205_AD_NMANFCTRNAME0           0x1CCU
#define MAX17205_AD_NMANFCTRNAME1           0x1CDU
#define MAX17205_AD_NMANFCTRNAME2           0x1CEU
#define MAX17205_AD_NRSENSE                 0x1CFU
#define MAX17205_AD_NUSER1D0                0x1D0U
#define MAX17205_AD_NUSER1D1                0x1D1U
#define MAX17205_AD_NAGEFCCFG               0x1D2U
#define MAX17205_AD_NDESIGNVOLTAGE          0x1D3U
#define MAX17205_AD_NUSER1D4                0x1D4U
#define MAX17205_AD_NRFASTVSHDN             0x1D5U
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
 * @name    MAX17205 Status register (000h) fields
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
 * @name    MAX17205 (n)VAlrtTh register (001h/1C0h) fields
 * @{
 */
#define MAX17205_VALRTTH_VMIN_Pos           (0U)
#define MAX17205_VALRTTH_VMIN_Msk           (0xFFU << MAX17205_VALRTTH_VMIN_Pos)
#define MAX17205_VALRTTH_VMIN               MAX17205_VALRTTH_VMIN_Msk
#define MAX17205_VALRTTH_VMAX_Pos           (8U)
#define MAX17205_VALRTTH_VMAX_Msk           (0xFFU << MAX17205_VALRTTH_VMAX_Pos)
#define MAX17205_VALRTTH_VMAX               MAX17205_VALRTTH_VMAX_Msk
/** @} */

/**
 * @name    MAX17205 (n)TAlrtTh register (002h/1C1h) fields
 * @{
 */
#define MAX17205_TALRTTH_TMIN_Pos           (0U)
#define MAX17205_TALRTTH_TMIN_Msk           (0xFFU << MAX17205_TALRTTH_TMIN_Pos)
#define MAX17205_TALRTTH_TMIN               MAX17205_TALRTTH_TMIN_Msk
#define MAX17205_TALRTTH_TMAX_Pos           (8U)
#define MAX17205_TALRTTH_TMAX_Msk           (0xFFU << MAX17205_TALRTTH_TMAX_Pos)
#define MAX17205_TALRTTH_TMAX               MAX17205_TALRTTH_TMAX_Msk
/** @} */

/**
 * @name    MAX17205 (n)SAlrtTh register (003h/1C2h) fields
 * @{
 */
#define MAX17205_SALRTTH_SMIN_Pos           (0U)
#define MAX17205_SALRTTH_SMIN_Msk           (0xFFU << MAX17205_SALRTTH_SMIN_Pos)
#define MAX17205_SALRTTH_SMIN               MAX17205_SALRTTH_SMIN_Msk
#define MAX17205_SALRTTH_SMAX_Pos           (8U)
#define MAX17205_SALRTTH_SMAX_Msk           (0xFFU << MAX17205_SALRTTH_SMAX_Pos)
#define MAX17205_SALRTTH_SMAX               MAX17205_SALRTTH_SMAX_Msk
/** @} */

/**
 * @name    MAX17205 (n)FullSocThr register (013h/1C6h) fields
 * @{
 */
#define MAX17205_AD_FULLSOCTHR_PermMsk      (0x7U)
#define MAX17205_AD_FULLSOCTHR_PermSet      (0x5U)
#define MAX17205_FULLSOCTHR_NFULLSOCTHR_Pos (3U)
#define MAX17205_FULLSOCTHR_NFULLSOCTHR_Msk (0x1FFFU << MAX17205_FULLSOCTHR_NFULLSOCTHR_Pos)
#define MAX17205_FULLSOCTHR_NFULLSOCTHR     MAX17205_FULLSOCTHR_NFULLSOCTHR_Msk
/** @} */

/**
 * @name    MAX17205 (n)MaxMinTemp register (01Ah/1ADh) fields
 * @{
 */
#define MAX17205_MAXMINTEMP_MIN_Pos         (0U)
#define MAX17205_MAXMINTEMP_MIN_Msk         (0xFFU << MAX17205_MAXMINTEMP_MIN_Pos)
#define MAX17205_MAXMINTEMP_MIN             MAX17205_MAXMINTEMP_MIN_Msk
#define MAX17205_MAXMINTEMP_MAX_Pos         (8U)
#define MAX17205_MAXMINTEMP_MAX_Msk         (0xFFU << MAX17205_MAXMINTEMP_MAX_Pos)
#define MAX17205_MAXMINTEMP_MAX             MAX17205_MAXMINTEMP_MAX_Msk
/** @} */

/**
 * @name    MAX17205 (n)MaxMinVolt register (01Bh/1ACh) fields
 * @{
 */
#define MAX17205_MAXMINVOLT_MIN_Pos         (0U)
#define MAX17205_MAXMINVOLT_MIN_Msk         (0xFFU << MAX17205_MAXMINVOLT_MIN_Pos)
#define MAX17205_MAXMINVOLT_MIN             MAX17205_MAXMINVOLT_MIN_Msk
#define MAX17205_MAXMINVOLT_MAX_Pos         (8U)
#define MAX17205_MAXMINVOLT_MAX_Msk         (0xFFU << MAX17205_MAXMINVOLT_MAX_Pos)
#define MAX17205_MAXMINVOLT_MAX             MAX17205_MAXMINVOLT_MAX_Msk
/** @} */

/**
 * @name    MAX17205 (n)MaxMinCurr register (01Ch/1ABh) fields
 * @{
 */
#define MAX17205_MAXMINCURR_MIN_Pos         (0U)
#define MAX17205_MAXMINCURR_MIN_Msk         (0xFFU << MAX17205_MAXMINCURR_MIN_Pos)
#define MAX17205_MAXMINCURR_MIN             MAX17205_MAXMINCURR_MIN_Msk
#define MAX17205_MAXMINCURR_MAX_Pos         (8U)
#define MAX17205_MAXMINCURR_MAX_Msk         (0xFFU << MAX17205_MAXMINCURR_MAX_Pos)
#define MAX17205_MAXMINCURR_MAX             MAX17205_MAXMINCURR_MAX_Msk
/** @} */

/**
 * @name    MAX17205 Config register (01Dh) fields
 * @{
 */
#define MAX17205_AD_CONFIG_PermMsk          (0x8020U)
#define MAX17205_AD_CONFIG_PermSet          (0x0000U)
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
 * @name    MAX17205 DevName register (021h) fields
 * @{
 */
#define MAX17205_DEVNAME_DEV_Pos            (0U)
#define MAX17205_DEVNAME_DEV_Msk            (0xFU << MAX17205_DEVNAME_DEV_Pos)
#define MAX17205_DEVNAME_DEV                MAX17205_DEVNAME_DEV_Msk
#define MAX17205_DEVNAME_REV_Pos            (4U)
#define MAX17205_DEVNAME_REV_Msk            (0xFFFU << MAX17205_DEVNAME_REV_Pos)
#define MAX17205_DEVNAME_REV                MAX17205_DEVNAME_REV_Msk
/** @} */

/**
 * @name    MAX17205 (n)LearnCfg register (028h/19Fh) fields
 * @{
 */
#define MAX17205_AD_NLEARNCFG_PermMsk        (0xFF8BU)
#define MAX17205_AD_NLEARNCFG_PermSet        (0x2602U)
#define MAX17205_LEARNCFG_FILT_EMPTY_Pos    (2U)
#define MAX17205_LEARNCFG_FILT_EMPTY_Msk    (0x1U << MAX17205_LEARNCFG_FILT_EMPTY_Pos)
#define MAX17205_LEARNCFG_FILT_EMPTY        MAX17205_LEARNCFG_FILT_EMPTY_Msk
#define MAX17205_LEARNCFG_LS_Pos            (4U)
#define MAX17205_LEARNCFG_LS_Msk            (0x7U << MAX17205_LEARNCFG_LS_Pos)
#define MAX17205_LEARNCFG_LS                MAX17205_LEARNCFG_LS_Msk
#define MAX17205_LEARN_COMPLETE             7
/** @} */

/**
 * @name    MAX17205 (n)FilterCfg register (029h/19Dh) fields
 * @{
 */
#define MAX17205_AD_FILTERCFG_PermMsk       (0xC000U)
#define MAX17205_AD_FILTERCFG_PermSet       (0x0000U)
#define MAX17205_FILTERCFG_CURR_Pos         (0U)
#define MAX17205_FILTERCFG_CURR_Msk         (0xFU << MAX17205_FILTERCFG_CURR_Pos)
#define MAX17205_FILTERCFG_CURR             MAX17205_FILTERCFG_CURR_Msk
#define MAX17205_FILTERCFG_VOLT_Pos         (4U)
#define MAX17205_FILTERCFG_VOLT_Msk         (0x7U << MAX17205_FILTERCFG_VOLT_Pos)
#define MAX17205_FILTERCFG_VOLT             MAX17205_FILTERCFG_VOLT_Msk
#define MAX17205_FILTERCFG_MIX_Pos          (7U)
#define MAX17205_FILTERCFG_MIX_Msk          (0xFU << MAX17205_FILTERCFG_MIX_Pos)
#define MAX17205_FILTERCFG_MIX              MAX17205_FILTERCFG_MIX_Msk
#define MAX17205_FILTERCFG_TEMP_Pos         (11U)
#define MAX17205_FILTERCFG_TEMP_Msk         (0x7U << MAX17205_FILTERCFG_TEMP_Pos)
#define MAX17205_FILTERCFG_TEMP             MAX17205_FILTERCFG_TEMP_Msk
/** @} */

/**
 * @name    MAX17205 (n)RelaxCfg register (02Ah/1B6h) fields
 * @{
 */
#define MAX17205_RELAXCFG_DT_Pos            (0U)
#define MAX17205_RELAXCFG_DT_Msk            (0xFU << MAX17205_RELAXCFG_DT_Pos)
#define MAX17205_RELAXCFG_DT                MAX17205_RELAXCFG_DT_Msk
#define MAX17205_RELAXCFG_DV_Pos            (4U)
#define MAX17205_RELAXCFG_DV_Msk            (0x1FU << MAX17205_RELAXCFG_DV_Pos)
#define MAX17205_RELAXCFG_DV                MAX17205_RELAXCFG_DV_Msk
#define MAX17205_RELAXCFG_LOAD_Pos          (9U)
#define MAX17205_RELAXCFG_LOAD_Msk          (0xFEU << MAX17205_RELAXCFG_LOAD_Pos)
#define MAX17205_RELAXCFG_LOAD              MAX17205_RELAXCFG_LOAD_Msk
/** @} */

/**
 * @name    MAX17205 (n)MiscCfg register (02Bh/1B2h) fields
 * @{
 */
#define MAX17205_AD_MISCCFG_PermMsk         (0x0C1CU)
#define MAX17205_AD_MISCCFG_PermSet         (0x0810U)
#define MAX17205_MISCCFG_SACFG_Pos          (0U)
#define MAX17205_MISCCFG_SACFG_Msk          (0x3U << MAX17205_MISCCFG_SACFG_Pos)
#define MAX17205_MISCCFG_SACFG              MAX17205_MISCCFG_SACFG_Msk
#define MAX17205_MISCCFG_MR_Pos             (5U)
#define MAX17205_MISCCFG_MR_Msk             (0x1FU << MAX17205_MISCCFG_MR_Pos)
#define MAX17205_MISCCFG_MR                 MAX17205_MISCCFG_MR_Msk
#define MAX17205_MISCCFG_FUS_Pos            (12U)
#define MAX17205_MISCCFG_FUS_Msk            (0xFU << MAX17205_MISCCFG_FUS_Pos)
#define MAX17205_MISCCFG_FUS                MAX17205_MISCCFG_FUS_Msk
/** @} */

/**
 * @name    MAX17205 VEmpty register (03Ah/19Eh) fields
 * @{
 */
#define MAX17205_VEMPTY_VR_Pos              (0U)
#define MAX17205_VEMPTY_VR_Msk              (0x7FU << MAX17205_VEMPTY_VR_Pos)
#define MAX17205_VEMPTY_VR                  MAX17205_VEMPTY_VR_Msk
#define MAX17205_VEMPTY_VE_Pos              (7U)
#define MAX17205_VEMPTY_VE_Msk              (0x1FFU << MAX17205_VEMPTY_VE_Pos)
#define MAX17205_VEMPTY_VE                  MAX17205_VEMPTY_VE_Msk
/** @} */

/**
 * @name    MAX17205 FStat register (03Dh) fields
 * @{
 */
#define MAX17205_FSTAT_DNR_Pos              (0U)
#define MAX17205_FSTAT_DNR_Msk              (0x1U << MAX17205_FSTAT_DNR_Pos)
#define MAX17205_FSTAT_DNR                  MAX17205_FSTAT_DNR_Msk
#define MAX17205_FSTAT_RELDT2_Pos           (6U)
#define MAX17205_FSTAT_RELDT2_Msk           (0x1U << MAX17205_FSTAT_RELDT2_Pos)
#define MAX17205_FSTAT_RELDT2               MAX17205_FSTAT_RELDT2_Msk
#define MAX17205_FSTAT_FQ_Pos               (7U)
#define MAX17205_FSTAT_FQ_Msk               (0x1U << MAX17205_FSTAT_FQ_Pos)
#define MAX17205_FSTAT_FQ                   MAX17205_FSTAT_FQ_Msk
#define MAX17205_FSTAT_EDET_Pos             (8U)
#define MAX17205_FSTAT_EDET_Msk             (0x1U << MAX17205_FSTAT_EDET_Pos)
#define MAX17205_FSTAT_EDET                 MAX17205_FSTAT_EDET_Msk
#define MAX17205_FSTAT_RELDT_Pos            (9U)
#define MAX17205_FSTAT_RELDT_Msk            (0x1U << MAX17205_FSTAT_RELDT_Pos)
#define MAX17205_FSTAT_RELDT                MAX17205_FSTAT_RELDT_Msk
/** @} */

/**
 * @name    MAX17205 ShdnTimer register (03Fh) fields
 * @{
 */
#define MAX17205_SHDNTIMER_CTR_Pos          (0U)
#define MAX17205_SHDNTIMER_CTR_Msk          (0x1FFFU << MAX17205_SHDNTIMER_CTR_Pos)
#define MAX17205_SHDNTIMER_CTR              MAX17205_SHDNTIMER_CTR_Msk
#define MAX17205_SHDNTIMER_THR_Pos          (13U)
#define MAX17205_SHDNTIMER_THR_Msk          (0xEU << MAX17205_SHDNTIMER_THR_Pos)
#define MAX17205_SHDNTIMER_THR              MAX17205_SHDNTIMER_THR_Msk
/** @} */

/**
 * @name    MAX17205 Command register (060h) values
 * @{
 */
#define MAX17205_COMMAND_COMPUTE_WITHOUT_ROM_ID 0x3600U
#define MAX17205_COMMAND_COMPUTE_WITH_ROM_ID    0x3500U
#define MAX17205_COMMAND_COMPUTE_SECRET_WITHOUT_ROM_ID  0x3000U
#define MAX17205_COMMAND_COMPUTE_SECRET_WITH_ROM_ID     0x3300U
#define MAX17205_COMMAND_CLEAR_SECRET       0x5A00U
#define MAX17205_COMMAND_LOCK_SECRET        0x6000U
#define MAX17205_COMMAND_COPY_NV_BLOCK      0xE904U
#define MAX17205_COMMAND_NV_RECALL          0xE001U
#define MAX17205_COMMAND_HISTORY_RECALL     0xE200U
#define MAX17205_COMMAND_NV_LOCK            0x6A00U
#define MAX17205_COMMAND_HARDWARE_RESET     0x000FU
/** @} */

/**
 * @name    MAX17205 CommStat register (061h) fields
 * @{
 */
#define MAX17205_COMMSTAT_NVBUSY_Pos        (1U)
#define MAX17205_COMMSTAT_NVBUSY_Msk        (0x1U << MAX17205_COMMSTAT_NVBUSY_Pos)
#define MAX17205_COMMSTAT_NVBUSY            MAX17205_COMMSTAT_NVBUSY_Msk
#define MAX17205_COMMSTAT_NVERROR_Pos       (2U)
#define MAX17205_COMMSTAT_NVERROR_Msk       (0x1U << MAX17205_COMMSTAT_NVERROR_Pos)
#define MAX17205_COMMSTAT_NVERROR           MAX17205_COMMSTAT_NVERROR_Msk
/** @} */

/**
 * @name    MAX17205 Lock register (07Fh) fields
 * @{
 */
#define MAX17205_LOCK_LOCK1_CMD_Pos        (0U)
#define MAX17205_LOCK_LOCK1_CMD_Msk        (0x1U << MAX17205_LOCK_LOCK1_CMD_Pos)
#define MAX17205_LOCK_LOCK1_CMD            MAX17205_LOCK_LOCK1_CMD_Msk
#define MAX17205_LOCK_LOCK2_CMD_Pos        (1U)
#define MAX17205_LOCK_LOCK2_CMD_Msk        (0x1U << MAX17205_LOCK_LOCK2_CMD_Pos)
#define MAX17205_LOCK_LOCK2_CMD            MAX17205_LOCK_LOCK2_CMD_Msk
#define MAX17205_LOCK_LOCK3_CMD_Pos        (2U)
#define MAX17205_LOCK_LOCK3_CMD_Msk        (0x1U << MAX17205_LOCK_LOCK3_CMD_Pos)
#define MAX17205_LOCK_LOCK3_CMD            MAX17205_LOCK_LOCK3_CMD_Msk
#define MAX17205_LOCK_LOCK4_CMD_Pos        (3U)
#define MAX17205_LOCK_LOCK4_CMD_Msk        (0x1U << MAX17205_LOCK_LOCK4_CMD_Pos)
#define MAX17205_LOCK_LOCK4_CMD            MAX17205_LOCK_LOCK4_CMD_Msk
#define MAX17205_LOCK_LOCK5_CMD_Pos        (4U)
#define MAX17205_LOCK_LOCK5_CMD_Msk        (0x1U << MAX17205_LOCK_LOCK5_CMD_Pos)
#define MAX17205_LOCK_LOCK5_CMD            MAX17205_LOCK_LOCK5_CMD_Msk
/** @} */

/**
 * @name    MAX17205 (n)IArtlTh (0B4h/1C3h) register fields
 * @{
 */
#define MAX17205_IALRTTH_IMIN_CMD_Pos       (0U)
#define MAX17205_IALRTTH_IMIN_CMD_Msk       (0xFFU << MAX17205_IALRTTH_IMIN_CMD_Pos)
#define MAX17205_IALRTTH_IMIN_CMD           MAX17205_IALRTTH_IMIN_CMD_Msk
#define MAX17205_IALRTTH_IMAX_Pos           (8U)
#define MAX17205_IALRTTH_IMAX_Msk           (0xFFU << MAX17205_IALRTTH_IMAX_Pos)
#define MAX17205_IALRTTH_IMAX               MAX17205_IALRTTH_IMAX_Msk
/** @} */

/**
 * @name    MAX17205 (n)HibCfg (0BAh/1B4h) register fields
 * @{
 */
#define MAX17205_AD_HIBCFG_PermMsk          (0x00E0U)
#define MAX17205_AD_HIBCFG_PermSet          (0x0000U)
#define MAX17205_HIBCFG_HIBSCALAR_CMD_Pos   (0U)
#define MAX17205_HIBCFG_HIBSCALAR_CMD_Msk   (0x7U << MAX17205_HIBCFG_HIBSCALAR_CMD_Pos)
#define MAX17205_HIBCFG_HIBSCALAR_CMD       MAX17205_HIBCFG_HIBSCALAR_CMD_Msk
#define MAX17205_HIBCFG_HIBEXITTIME_Pos     (3U)
#define MAX17205_HIBCFG_HIBEXITTIME_Msk     (0x3U << MAX17205_HIBCFG_HIBEXITTIME_Pos)
#define MAX17205_HIBCFG_HIBEXITTIME         MAX17205_HIBCFG_HIBEXITTIME_Msk
#define MAX17205_HIBCFG_HIBTHRESHOLD_Pos    (8U)
#define MAX17205_HIBCFG_HIBTHRESHOLD_Msk    (0xFU << MAX17205_HIBCFG_HIBTHRESHOLD_Pos)
#define MAX17205_HIBCFG_HIBTHRESHOLD        MAX17205_HIBCFG_HIBTHRESHOLD_Msk
#define MAX17205_HIBCFG_HIBENTERTIME_Pos    (12U)
#define MAX17205_HIBCFG_HIBENTERTIME_Msk    (0x7U << MAX17205_HIBCFG_HIBENTERTIME_Pos)
#define MAX17205_HIBCFG_HIBENTERTIME        MAX17205_HIBCFG_HIBENTERTIME_Msk
#define MAX17205_HIBCFG_ENHIB_Pos           (15U)
#define MAX17205_HIBCFG_ENHIB_Msk           (0x1U << MAX17205_HIBCFG_ENHIB_Pos)
#define MAX17205_HIBCFG_ENHIB               MAX17205_HIBCFG_ENHIB_Msk

/**
 * @name    MAX17205 Config2 (0BBh) register fields
 * @{
 */
#define MAX17205_AD_CONFIG2_PermMsk         (0xFF3EU)
#define MAX17205_AD_CONFIG2_PermSet         (0x0010U)
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
 * @name    MAX17205 Config2 register (0BBh) values
 * @{
 */
#define MAX17205_COMMAND_FUEL_GAUAGE_RESET  0x0001U
/** @} */

/**
 * @name    MAX17205 (n)PackCfg (0BDh/1B5h) register fields
 * @{
 */
#define MAX17205_AD_PACKCFG_PermMsk         (0x4010U)
#define MAX17205_AD_PACKCFG_PermSet         (0x0000U)
#define MAX17205_PACKCFG_NCELLS_Pos         (0U)
#define MAX17205_PACKCFG_NCELLS_Msk         (0xFU << MAX17205_PACKCFG_NCELLS_Pos)
#define MAX17205_PACKCFG_NCELLS             MAX17205_PACKCFG_NCELLS_Msk
#define MAX17205_PACKCFG_BALCFG_Pos         (5U)
#define MAX17205_PACKCFG_BALCFG_Msk         (0x7U << MAX17205_PACKCFG_BALCFG_Pos)
#define MAX17205_PACKCFG_BALCFG             MAX17205_PACKCFG_BALCFG_Msk
#define MAX17205_PACKCFG_BALCFG_2_5         (0x1U << MAX17205_PACKCFG_BALCFG_Pos)
#define MAX17205_PACKCFG_BALCFG_5           (0x2U << MAX17205_PACKCFG_BALCFG_Pos)
#define MAX17205_PACKCFG_BALCFG_10          (0x3U << MAX17205_PACKCFG_BALCFG_Pos)
#define MAX17205_PACKCFG_BALCFG_20          (0x4U << MAX17205_PACKCFG_BALCFG_Pos)
#define MAX17205_PACKCFG_BALCFG_40          (0x5U << MAX17205_PACKCFG_BALCFG_Pos)
#define MAX17205_PACKCFG_BALCFG_80          (0x6U << MAX17205_PACKCFG_BALCFG_Pos)
#define MAX17205_PACKCFG_BALCFG_160         (0x7U << MAX17205_PACKCFG_BALCFG_Pos)
#define MAX17205_PACKCFG_CXEN_Pos           (8U)
#define MAX17205_PACKCFG_CXEN_Msk           (0x1U << MAX17205_PACKCFG_CXEN_Pos)
#define MAX17205_PACKCFG_CXEN               MAX17205_PACKCFG_CXEN_Msk
#define MAX17205_PACKCFG_BTEN_Pos           (9U)
#define MAX17205_PACKCFG_BTEN_Msk           (0x1U << MAX17205_PACKCFG_BTEN_Pos)
#define MAX17205_PACKCFG_BTEN               MAX17205_PACKCFG_BTEN_Msk
#define MAX17205_PACKCFG_CHEN_Pos           (10U)
#define MAX17205_PACKCFG_CHEN_Msk           (0x1U << MAX17205_PACKCFG_CHEN_Pos)
#define MAX17205_PACKCFG_CHEN               MAX17205_PACKCFG_CHEN_Msk
#define MAX17205_PACKCFG_TDEN_Pos           (11U)
#define MAX17205_PACKCFG_TDEN_Msk           (0x1U << MAX17205_PACKCFG_TDEN_Pos)
#define MAX17205_PACKCFG_TDEN               MAX17205_PACKCFG_TDEN_Msk
#define MAX17205_PACKCFG_A1EN_Pos           (12U)
#define MAX17205_PACKCFG_A1EN_Msk           (0x1U << MAX17205_PACKCFG_A1EN_Pos)
#define MAX17205_PACKCFG_A1EN               MAX17205_PACKCFG_A1EN_Msk
#define MAX17205_PACKCFG_A2EN_Pos           (13U)
#define MAX17205_PACKCFG_A2EN_Msk           (0x1U << MAX17205_PACKCFG_A2EN_Pos)
#define MAX17205_PACKCFG_A2EN               MAX17205_PACKCFG_A2EN_Msk
#define MAX17205_PACKCFG_FGT_Pos            (15U)
#define MAX17205_PACKCFG_FGT_Msk            (0x1U << MAX17205_PACKCFG_FGT_Pos)
#define MAX17205_PACKCFG_FGT                MAX17205_PACKCFG_FGT_Msk
/** @} */

/**
 * @name    MAX17205 (n)ODSCTh (0F2h/18Eh) register fields
 * @{
 */
#define MAX17205_ODSCTH_ODTH_Pos            (0U)
#define MAX17205_ODSCTH_ODTH_Msk            (0x1FU << MAX17205_ODSCTH_ODTH_Pos)
#define MAX17205_ODSCTH_ODTH                MAX17205_ODSCTH_ODTH_Msk
#define MAX17205_ODSCTH_SCTH_Pos            (8U)
#define MAX17205_ODSCTH_SCTH_Msk            (0x1FU << MAX17205_ODSCTH_SCTH_Pos)
#define MAX17205_ODSCTH_SCTH                MAX17205_ODSCTH_SCTH_Msk
/** @} */

/**
 * @name    MAX17205 (n)ODSCCFG (0F3h/18Fh) register fields
 * @{
 */
#define MAX17205_ODSCCFG_ODDLY_Pos          (0U)
#define MAX17205_ODSCCFG_ODDLY_Msk          (0xFU << MAX17205_ODSCCFG_ODDLY_Pos)
#define MAX17205_ODSCCFG_ODDLY              MAX17205_ODSCCFG_ODDLY_Msk
#define MAX17205_ODSCCFG_ODEN_Pos           (6U)
#define MAX17205_ODSCCFG_ODEN_Msk           (0x1U << MAX17205_ODSCCFG_ODEN_Pos)
#define MAX17205_ODSCCFG_ODEN               MAX17205_ODSCCFG_ODEN_Msk
#define MAX17205_ODSCCFG_ODI_Pos            (7U)
#define MAX17205_ODSCCFG_ODI_Msk            (0x1U << MAX17205_ODSCCFG_ODI_Pos)
#define MAX17205_ODSCCFG_ODI                MAX17205_ODSCCFG_ODI_Msk
#define MAX17205_ODSCCFG_SCDLY_Pos          (8U)
#define MAX17205_ODSCCFG_SCDLY_Msk          (0xFU << MAX17205_ODSCCFG_SCDLY_Pos)
#define MAX17205_ODSCCFG_SCDLY              MAX17205_ODSCCFG_SCDLY_Msk
#define MAX17205_ODSCCFG_SCEN_Pos           (14U)
#define MAX17205_ODSCCFG_SCEN_Msk           (0x1U << MAX17205_ODSCCFG_SCEN_Pos)
#define MAX17205_ODSCCFG_SCEN               MAX17205_ODSCCFG_SCEN_Msk
#define MAX17205_ODSCCFG_SCI_Pos            (15U)
#define MAX17205_ODSCCFG_SCI_Msk            (0x1U << MAX17205_ODSCCFG_SCI_Pos)
#define MAX17205_ODSCCFG_SCI                MAX17205_ODSCCFG_SCI_Msk
/** @} */

/**
 * @name    MAX17205 nVoltTemp (1AAh) register fields
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
 * @name    MAX17205 nSOC (1AEh) register fields
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
 * @name    MAX17205 nConfig (1B0h) register fields
 * @{
 */
#define MAX17205_AD_NCONFIG_PermMsk         (0x8010U)
#define MAX17205_AD_NCONFIG_PermSet         (0x0010U)
#define MAX17205_NCONFIG_TALRTEN_Pos        (0U)
#define MAX17205_NCONFIG_TALRTEN_Msk        (0x1U << MAX17205_NCONFIG_TALRTEN_Pos)
#define MAX17205_NCONFIG_TALRTEN            MAX17205_NCONFIG_TALRTEN_Msk
#define MAX17205_NCONFIG_DSOCEN_Pos         (1U)
#define MAX17205_NCONFIG_DSOCEN_Msk         (0x1U << MAX17205_NCONFIG_DSOCEN_Pos)
#define MAX17205_NCONFIG_DSOCEN             MAX17205_NCONFIG_DSOCEN_Msk
#define MAX17205_NCONFIG_AEN_Pos            (2U)
#define MAX17205_NCONFIG_AEN_Msk            (0x1U << MAX17205_NCONFIG_AEN_Pos)
#define MAX17205_NCONFIG_AEN                MAX17205_NCONFIG_AEN_Msk
#define MAX17205_NCONFIG_FTHRM_Pos          (3U)
#define MAX17205_NCONFIG_FTHRM_Msk          (0x1U << MAX17205_NCONFIG_FTHRM_Pos)
#define MAX17205_NCONFIG_FTHRM              MAX17205_NCONFIG_FTHRM_Msk
#define MAX17205_NCONFIG_ALSH_Pos           (5U)
#define MAX17205_NCONFIG_ALSH_Msk           (0x1U << MAX17205_NCONFIG_ALSH_Pos)
#define MAX17205_NCONFIG_ALSH               MAX17205_NCONFIG_ALSH_Msk
#define MAX17205_NCONFIG_COMMSH_Pos         (6U)
#define MAX17205_NCONFIG_COMMSH_Msk         (0x1U << MAX17205_NCONFIG_COMMSH_Pos)
#define MAX17205_NCONFIG_COMMSH             MAX17205_NCONFIG_COMMSH_Msk
#define MAX17205_NCONFIG_SHDN_Pos           (7U)
#define MAX17205_NCONFIG_SHDN_Msk           (0x1U << MAX17205_NCONFIG_SHDN_Pos)
#define MAX17205_NCONFIG_SHDN               MAX17205_NCONFIG_SHDN_Msk
#define MAX17205_NCONFIG_TEX_Pos            (8U)
#define MAX17205_NCONFIG_TEX_Msk            (0x1U << MAX17205_NCONFIG_TEX_Pos)
#define MAX17205_NCONFIG_TEX                MAX17205_NCONFIG_TEX_Msk
#define MAX17205_NCONFIG_TEN_Pos            (9U)
#define MAX17205_NCONFIG_TEN_Msk            (0x1U << MAX17205_NCONFIG_TEN_Pos)
#define MAX17205_NCONFIG_TEN                MAX17205_NCONFIG_TEN_Msk
#define MAX17205_NCONFIG_AINSH_Pos          (10U)
#define MAX17205_NCONFIG_AINSH_Msk          (0x1U << MAX17205_NCONFIG_AINSH_Pos)
#define MAX17205_NCONFIG_AINSH              MAX17205_NCONFIG_AINSH_Msk
#define MAX17205_NCONFIG_ALRTP_Pos          (11U)
#define MAX17205_NCONFIG_ALRTP_Msk          (0x1U << MAX17205_NCONFIG_ALRTP_Pos)
#define MAX17205_NCONFIG_ALRTP              MAX17205_NCONFIG_ALRTP_Msk
#define MAX17205_NCONFIG_VS_Pos             (12U)
#define MAX17205_NCONFIG_VS_Msk             (0x1U << MAX17205_NCONFIG_VS_Pos)
#define MAX17205_NCONFIG_VS                 MAX17205_NCONFIG_VS_Msk
#define MAX17205_NCONFIG_TS_Pos             (13U)
#define MAX17205_NCONFIG_TS_Msk             (0x1U << MAX17205_NCONFIG_TS_Pos)
#define MAX17205_NCONFIG_TS                 MAX17205_NCONFIG_TS_Msk
#define MAX17205_NCONFIG_SS_Pos             (14U)
#define MAX17205_NCONFIG_SS_Msk             (0x1U << MAX17205_NCONFIG_SS_Pos)
#define MAX17205_NCONFIG_SS                 MAX17205_NCONFIG_SS_Msk
/** @} */

/**
 * @name    MAX17205 nRippleCfg (1B1h) register fields
 * @{
 */
#define MAX17205_NRIPPLECFG_NR_Pos          (0U)
#define MAX17205_NRIPPLECFG_NR_Msk          (0x7U << MAX17205_NRIPPLECFG_NR_Pos)
#define MAX17205_NRIPPLECFG_NR              MAX17205_NRIPPLECFG_NR_Msk
#define MAX17205_NRIPPLECFG_KDV_Pos         (3U)
#define MAX17205_NRIPPLECFG_KDV_Msk         (0x1FFFU << MAX17205_NNVCFG0_ENSBS_Pos)
#define MAX17205_NRIPPLECFG_KDV             MAX17205_NNVCFG0_ENSBS_Msk
/** @} */

/**
 * @name    MAX17205 nConvgCfg (1B7h) register fields
 * @{
 */
#define MAX17205_NCONVGCFG_REPL_PER_STAGE_Pos   (0U)
#define MAX17205_NCONVGCFG_REPL_PER_STAGE_Msk   (0x7U << MAX17205_NCONVGCFG_REPL_PER_STAGE_Pos)
#define MAX17205_NCONVGCFG_REPL_PER_STAGE       MAX17205_NCONVGCFG_REPL_PER_STAGE_Msk
#define MAX17205_NCONVGCFG_MINSLOPEX_Pos        (3U)
#define MAX17205_NCONVGCFG_MINSLOPEX_Msk        (0xFU << MAX17205_NCONVGCFG_MINSLOPEX_Pos)
#define MAX17205_NCONVGCFG_MINSLOPEX            MAX17205_NCONVGCFG_MINSLOPEX_Msk
#define MAX17205_NCONVGCFG_VOLTLOWOFF_Pos       (7U)
#define MAX17205_NCONVGCFG_VOLTLOWOFF_Msk       (0x1FU << MAX17205_NCONVGCFG_VOLTLOWOFF_Pos)
#define MAX17205_NCONVGCFG_VOLTLOWOFF           MAX17205_NCONVGCFG_VOLTLOWOFF_Msk
#define MAX17205_NCONVGCFG_REPLOW_Pos           (12U)
#define MAX17205_NCONVGCFG_REPLOW_Msk           (0xFU << MAX17205_NCONVGCFG_REPLOW_Pos)
#define MAX17205_NCONVGCFG_REPLOW               MAX17205_NCONVGCFG_REPLOW_Msk
/** @} */

/**
 * @name    MAX17205 nNVCfg0 (1B8h) register fields
 * @{
 */
#define MAX17205_AD_NNVCFG0_PermMsk         (0x3000U)
#define MAX17205_AD_NNVCFG0_PermSet         (0x0000U)
#define MAX17205_NNVCFG0_ENSBS_Pos          (0U)
#define MAX17205_NNVCFG0_ENSBS_Msk          (0x1U << MAX17205_NNVCFG0_ENSBS_Pos)
#define MAX17205_NNVCFG0_ENSBS              MAX17205_NNVCFG0_ENSBS_Msk
#define MAX17205_NNVCFG0_ENHCFG_Pos         (1U)
#define MAX17205_NNVCFG0_ENHCFG_Msk         (0x1U << MAX17205_NNVCFG0_ENHCFG_Pos)
#define MAX17205_NNVCFG0_ENHCFG             MAX17205_NNVCFG0_ENHCFG_Msk
#define MAX17205_NNVCFG0_ENAF_Pos           (2U)
#define MAX17205_NNVCFG0_ENAF_Msk           (0x1U << MAX17205_NNVCFG0_ENAF_Pos)
#define MAX17205_NNVCFG0_ENAF               MAX17205_NNVCFG0_ENAF_Msk
#define MAX17205_NNVCFG0_ENMC_Pos           (3U)
#define MAX17205_NNVCFG0_ENMC_Msk           (0x1U << MAX17205_NNVCFG0_ENMC_Pos)
#define MAX17205_NNVCFG0_ENMC               MAX17205_NNVCFG0_ENMC_Msk
#define MAX17205_NNVCFG0_ENDC_Pos           (4U)
#define MAX17205_NNVCFG0_ENDC_Msk           (0x1U << MAX17205_NNVCFG0_ENDC_Pos)
#define MAX17205_NNVCFG0_ENDC               MAX17205_NNVCFG0_ENDC_Msk
#define MAX17205_NNVCFG0_ENVE_Pos           (5U)
#define MAX17205_NNVCFG0_ENVE_Msk           (0x1U << MAX17205_NNVCFG0_ENVE_Pos)
#define MAX17205_NNVCFG0_ENVE               MAX17205_NNVCFG0_ENVE_Msk
#define MAX17205_NNVCFG0_ENCG_Pos           (6U)
#define MAX17205_NNVCFG0_ENCG_Msk           (0x1U << MAX17205_NNVCFG0_ENCG_Pos)
#define MAX17205_NNVCFG0_ENCG               MAX17205_NNVCFG0_ENCG_Msk
#define MAX17205_NNVCFG0_ENICT_Pos          (7U)
#define MAX17205_NNVCFG0_ENICT_Msk          (0x1U << MAX17205_NNVCFG0_ENICT_Pos)
#define MAX17205_NNVCFG0_ENICT              MAX17205_NNVCFG0_ENICT_Msk
#define MAX17205_NNVCFG0_ENLCFG_Pos         (8U)
#define MAX17205_NNVCFG0_ENLCFG_Msk         (0x1U << MAX17205_NNVCFG0_ENLCFG_Pos)
#define MAX17205_NNVCFG0_ENLCFG             MAX17205_NNVCFG0_ENLCFG_Msk
#define MAX17205_NNVCFG0_ENRCFG_Pos         (9U)
#define MAX17205_NNVCFG0_ENRCFG_Msk         (0x1U << MAX17205_NNVCFG0_ENRCFG_Pos)
#define MAX17205_NNVCFG0_ENRCFG             MAX17205_NNVCFG0_ENRCFG_Msk
#define MAX17205_NNVCFG0_ENFCFG_Pos         (10U)
#define MAX17205_NNVCFG0_ENFCFG_Msk         (0x1U << MAX17205_NNVCFG0_ENFCFG_Pos)
#define MAX17205_NNVCFG0_ENFCFG             MAX17205_NNVCFG0_ENFCFG_Msk
#define MAX17205_NNVCFG0_ENCFG_Pos          (11U)
#define MAX17205_NNVCFG0_ENCFG_Msk          (0x1U << MAX17205_NNVCFG0_ENCFG_Pos)
#define MAX17205_NNVCFG0_ENCFG              MAX17205_NNVCFG0_ENCFG_Msk
#define MAX17205_NNVCFG0_ENX_Pos            (14U)
#define MAX17205_NNVCFG0_ENX_Msk            (0x1U << MAX17205_NNVCFG0_ENX_Pos)
#define MAX17205_NNVCFG0_ENX                MAX17205_NNVCFG0_ENX_Msk
#define MAX17205_NNVCFG0_ENOCV_Pos          (15U)
#define MAX17205_NNVCFG0_ENOCV_Msk          (0x1U << MAX17205_NNVCFG0_ENOCV_Pos)
#define MAX17205_NNVCFG0_ENOCV              MAX17205_NNVCFG0_ENOCV_Msk
/** @} */

/**
 * @name    MAX17205 nNVCfg1 (1B9h) register fields
 * @{
 */
#define MAX17205_AD_NNVCFG1_PermMsk         (0x07E1U)
#define MAX17205_AD_NNVCFG1_PermSet         (0x0000U)
#define MAX17205_NNVCFG1_ENCTE_Pos          (1U)
#define MAX17205_NNVCFG1_ENCTE_Msk          (0x1U << MAX17205_NNVCFG1_ENCTE_Pos)
#define MAX17205_NNVCFG1_ENCTE              MAX17205_NNVCFG1_ENCTE_Msk
#define MAX17205_NNVCFG1_ENCRV_Pos          (2U)
#define MAX17205_NNVCFG1_ENCRV_Msk          (0x1U << MAX17205_NNVCFG1_ENCRV_Pos)
#define MAX17205_NNVCFG1_ENCRV              MAX17205_NNVCFG1_ENCRV_Msk
#define MAX17205_NNVCFG1_ENAT_Pos           (3U)
#define MAX17205_NNVCFG1_ENAT_Msk           (0x1U << MAX17205_NNVCFG1_ENAT_Pos)
#define MAX17205_NNVCFG1_ENAT               MAX17205_NNVCFG1_ENAT_Msk
#define MAX17205_NNVCFG1_ENTTF_Pos          (4U)
#define MAX17205_NNVCFG1_ENTTF_Msk          (0x1U << MAX17205_NNVCFG1_ENTTF_Pos)
#define MAX17205_NNVCFG1_ENTTF              MAX17205_NNVCFG1_ENTTF_Msk
#define MAX17205_NNVCFG1_ENODSC_Pos         (11U)
#define MAX17205_NNVCFG1_ENODSC_Msk         (0x1U << MAX17205_NNVCFG1_ENODSC_Pos)
#define MAX17205_NNVCFG1_ENODSC             MAX17205_NNVCFG1_ENODSC_Msk
#define MAX17205_NNVCFG1_ENRFVSH_Pos        (12U)
#define MAX17205_NNVCFG1_ENRFVSH_Msk        (0x1U << MAX17205_NNVCFG1_ENRFVSH_Pos)
#define MAX17205_NNVCFG1_ENRFVSH            MAX17205_NNVCFG1_ENRFVSH_Msk
#define MAX17205_NNVCFG1_ENFTH_Pos          (13U)
#define MAX17205_NNVCFG1_ENFTH_Msk          (0x1U << MAX17205_NNVCFG1_ENFTH_Pos)
#define MAX17205_NNVCFG1_ENFTH              MAX17205_NNVCFG1_ENFTH_Msk
#define MAX17205_NNVCFG1_ENMTL_Pos          (14U)
#define MAX17205_NNVCFG1_ENMTL_Msk          (0x1U << MAX17205_NNVCFG1_ENMTL_Pos)
#define MAX17205_NNVCFG1_ENMTL              MAX17205_NNVCFG1_ENMTL_Msk
#define MAX17205_NNVCFG1_ENTGO_Pos          (15U)
#define MAX17205_NNVCFG1_ENTGO_Msk          (0x1U << MAX17205_NNVCFG1_ENTGO_Pos)
#define MAX17205_NNVCFG1_ENTGO              MAX17205_NNVCFG1_ENTGO_Msk
/** @} */

/**
 * @name    MAX17205 nNVCfg2 (1BAh) register fields
 * @{
 */
#define MAX17205_NNVCFG2_CYCLESPSAVE_Pos    (0U)
#define MAX17205_NNVCFG2_CYCLESPSAVE_Msk    (0x3FU << MAX17205_NNVCFG2_CYCLESPSAVE_Pos)
#define MAX17205_NNVCFG2_CYCLESPSAVE        MAX17205_NNVCFG2_CYCLESPSAVE_Msk
#define MAX17205_NNVCFG2_ENMET_Pos          (7U)
#define MAX17205_NNVCFG2_ENMET_Msk          (0x1U << MAX17205_NNVCFG2_ENMET_Pos)
#define MAX17205_NNVCFG2_ENMET              MAX17205_NNVCFG2_ENMET_Msk
#define MAX17205_NNVCFG2_ENIAVG_Pos         (8U)
#define MAX17205_NNVCFG2_ENIAVG_Msk         (0x1U << MAX17205_NNVCFG2_ENIAVG_Pos)
#define MAX17205_NNVCFG2_ENIAVG             MAX17205_NNVCFG2_ENIAVG_Msk
#define MAX17205_NNVCFG2_ENFC_Pos           (9U)
#define MAX17205_NNVCFG2_ENFC_Msk           (0x1U << MAX17205_NNVCFG2_ENFC_Pos)
#define MAX17205_NNVCFG2_ENFC               MAX17205_NNVCFG2_ENFC_Msk
#define MAX17205_NNVCFG2_ENVT_Pos           (10U)
#define MAX17205_NNVCFG2_ENVT_Msk           (0x1U << MAX17205_NNVCFG2_ENVT_Pos)
#define MAX17205_NNVCFG2_ENVT               MAX17205_NNVCFG2_ENVT_Msk
#define MAX17205_NNVCFG2_ENMMC_Pos          (11U)
#define MAX17205_NNVCFG2_ENMMC_Msk          (0x1U << MAX17205_NNVCFG2_ENMMC_Pos)
#define MAX17205_NNVCFG2_ENMMC              MAX17205_NNVCFG2_ENMMC_Msk
#define MAX17205_NNVCFG2_ENMMV_Pos          (12U)
#define MAX17205_NNVCFG2_ENMMV_Msk          (0x1U << MAX17205_NNVCFG2_ENMMV_Pos)
#define MAX17205_NNVCFG2_ENMMV              MAX17205_NNVCFG2_ENMMV_Msk
#define MAX17205_NNVCFG2_ENMMT_Pos          (13U)
#define MAX17205_NNVCFG2_ENMMT_Msk          (0x1U << MAX17205_NNVCFG2_ENMMT_Pos)
#define MAX17205_NNVCFG2_ENMMT              MAX17205_NNVCFG2_ENMMT_Msk
#define MAX17205_NNVCFG2_ENSOC_Pos          (14U)
#define MAX17205_NNVCFG2_ENSOC_Msk          (0x1U << MAX17205_NNVCFG2_ENSOC_Pos)
#define MAX17205_NNVCFG2_ENSOC              MAX17205_NNVCFG2_ENSOC_Msk
#define MAX17205_NNVCFG2_ENT_Pos            (15U)
#define MAX17205_NNVCFG2_ENT_Msk            (0x1U << MAX17205_NNVCFG2_ENT_Pos)
#define MAX17205_NNVCFG2_ENT                MAX17205_NNVCFG2_ENT_Msk
/** @} */

/**
 * @name    MAX17205 nSBSCfg (1BBh) register fields
 * @{
 */
#define MAX17205_NSBSCFG_MECFG_Pos          (1U)
#define MAX17205_NSBSCFG_MECFG_Msk          (0x3U << MAX17205_NSBSCFG_MECFG_Pos)
#define MAX17205_NSBSCFG_MECFG              MAX17205_NSBSCFG_MECFG_Msk
#define MAX17205_NSBSCFG_CAPMD_Pos          (15U)
#define MAX17205_NSBSCFG_CAPMD_Msk          (0x1U << MAX17205_NSBSCFG_CAPMD_Pos)
#define MAX17205_NSBSCFG_CAPMD              MAX17205_NSBSCFG_CAPMD_Msk
/** @} */

/**
 * @name    MAX17205 nTTFCfg register (1C7h) fields
 * @{
 */
#define MAX17205_NTTFCFG_NCV_MIXCAPRATIO_Pos    (0U)
#define MAX17205_NTTFCFG_NCV_MIXCAPRATIO_Msk    (0xFFU << MAX17205_NTTFCFG_NCV_MIXCAPRATIO_Pos)
#define MAX17205_NTTFCFG_NCV_MIXCAPRATIO        MAX17205_NTTFCFG_NCV_MIXCAPRATIO_Msk
#define MAX17205_NTTFCFG_NCV_HALFTIME_Pos   (8U)
#define MAX17205_NTTFCFG_NCV_HALFTIME_Msk   (0xFFU << MAX17205_NTTFCFG_NCV_HALFTIME_Pos)
#define MAX17205_NTTFCFG_NCV_HALFTIME       MAX17205_NTTFCFG_NCV_HALFTIME_Msk
/** @} */

/**
 * @name    MAX17205 nCGain register (1C8h) fields
 * @{
 */
#define MAX17205_NCGAIN_NCOFF_Pos           (0U)
#define MAX17205_NCGAIN_NCOFF_Msk           (0x3FU << MAX17205_NCGAIN_NCOFF_Pos)
#define MAX17205_NCGAIN_NCOFF               MAX17205_NCGAIN_NCOFF_Msk
#define MAX17205_NCGAIN_NCGAIN_Pos          (6U)
#define MAX17205_NCGAIN_NCGAIN_Msk          (0x3FFU << MAX17205_NCGAIN_NCGAIN_Pos)
#define MAX17205_NCGAIN_NCGAIN              MAX17205_NCGAIN_NCGAIN_Msk
/** @} */


/**
 * @name    MAX17205 nAgeFcCfg (1D2h) register fields
 * @{
 */
#define MAX17205_AD_NAGEFCCFG_PermMsk       (0x001FU)
#define MAX17205_AD_NAGEFCCFG_PermSet       (0x0003U)
#define MAX17205_NAGEFCCFG_CYCLESTART_Pos   (5U)
#define MAX17205_NAGEFCCFG_CYCLESTART_Msk   (0x7FU << MAX17205_NAGEFCCFG_CYCLESTART_Pos)
#define MAX17205_NAGEFCCFG_CYCLESTART       MAX17205_NAGEFCCFG_CYCLESTART_Msk
#define MAX17205_NAGEFCCFG_DEADTGTRATIO_Pos (12U)
#define MAX17205_NAGEFCCFG_DEADTGTRATIO_Msk (0xFU << MAX17205_NAGEFCCFG_DEADTGTRATIO_Pos)
#define MAX17205_NAGEFCCFG_DEADTGTRATIO     MAX17205_NAGEFCCFG_DEADTGTRATIO_Msk
/** @} */

/**
 * @name    MAX17205 nRFastVshdn register (1D5h) fields
 * @{
 */
#define MAX17205_NRFASTVSHDN_NVSHDN_Pos     (0U)
#define MAX17205_NRFASTVSHDN_NVSHDN_Msk     (0xFFU << MAX17205_NRFASTVSHDN_NVSHDN_Pos)
#define MAX17205_NRFASTVSHDN_NVSHDN         MAX17205_NRFASTVSHDN_NVSHDN_Msk
#define MAX17205_NRFASTVSHDN_NRFAST_Pos     (8U)
#define MAX17205_NRFASTVSHDN_NRFAST_Msk     (0xFFU << MAX17205_NRFASTVSHDN_NRFAST_Pos)
#define MAX17205_NRFASTVSHDN_NRFAST         MAX17205_NRFASTVSHDN_NRFAST_Msk
/** @} */

#if !HAL_USE_I2C
#error "MAX17205 requires HAL_USE_I2C"
#endif

#if !I2C_USE_MUTUAL_EXCLUSION
#error "MAX17205 requires I2C_USE_MUTUAL_EXCLUSION"
#endif

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
 * @brief   Structure to store register:value pairs for configuration
 */
typedef struct {
    uint16_t reg;
    uint16_t value;
} max17205_regval_t;

/**
 * @brief   MAX17205 configuration structure.
 */
typedef struct {
    /**
     * @brief I2C driver associated with this MAX17205.
     */
    I2CDriver                   *i2cp;
    /**
     * @brief Array of reg:value pairs used to configure the IC.
     */
    const max17205_regval_t     *regcfg;
    /**
     * @brief The value of the physical RSENSE resistor in microohms.
     */
    uint16_t rsense_uOhm;
} MAX17205Config;

/**
 * @brief MAX17205 Power Monitor class.
 */
struct MAX17205Driver {
    /* Current configuration data. */
    const MAX17205Config          *config;

    /* Driver state. */
    max17205_state_t state;

    /* Runtime value of RSENSE. If not set in config it's read from nRSense */
    uint16_t rsense_uOhm;
};

/** @} */

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/**
 * @brief   MAX17205 Register Value Verification
 */
#define MAX17205_SETVAL(reg, val)           (((uint16_t)(val) & ~ (reg ## _PermMsk)) | reg ## _PermSet)
#define MAX17205_RSENSE2REG(val)            ((uint16_t)(val / 10U))
#define MAX17205_REG2RSENSE(val)            ((uint16_t)(val * 10U))

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
/* Driver state machine */
void max17205ObjectInit(MAX17205Driver *devp);
bool max17205Start(MAX17205Driver *devp, const MAX17205Config *config);
void max17205Stop(MAX17205Driver *devp);

/* Reference datasheet table 1, generic register reads */
msg_t max17205ReadCapacity(MAX17205Driver *devp, const uint16_t reg, uint32_t *dest_mAh);
msg_t max17205WriteCapacity(MAX17205Driver *devp, const uint16_t reg, uint32_t dest_mAh);
msg_t max17205ReadPercentage(MAX17205Driver *devp, uint16_t reg, uint8_t *dest_pct);
msg_t max17205ReadVoltage(MAX17205Driver *devp, uint16_t reg, uint16_t *dest_mV);
msg_t max17205ReadCurrent(MAX17205Driver *devp, uint16_t reg, int32_t *dest_mA);
msg_t max17205ReadTemperature(MAX17205Driver *devp, uint16_t reg, int32_t *dest_mC);
msg_t max17205ReadResistance(MAX17205Driver *devp, uint16_t reg, uint16_t *dest_mOhm);
msg_t max17205ReadTime(MAX17205Driver *devp, uint16_t reg, uint32_t *dest_S);

/* Register reads that require a specific conversion not covered by table 1 */
msg_t max17205ReadAverageTemperature(MAX17205Driver *devp, uint16_t reg, int16_t *dest_C);
msg_t max17205ReadBatt(MAX17205Driver *devp, uint32_t *dest_mV);
msg_t max17205ReadCycles(MAX17205Driver *devp, uint16_t *dest_count);
msg_t max17205ReadMaxMinVoltage(MAX17205Driver *devp, uint16_t * max_mV, uint16_t * min_mV);
msg_t max17205ReadMaxMinCurrent(MAX17205Driver *devp, int32_t * max_mA, int32_t * min_mA);
msg_t max17205ReadMaxMinTemperature(MAX17205Driver *devp, int8_t * max_C, int8_t * min_C);

/* Misc */
msg_t max17205ReadLearnState(MAX17205Driver *devp, uint8_t *dest);
msg_t max17205WriteLearnState(MAX17205Driver *devp, uint8_t state);
msg_t max17205ReadHistory(MAX17205Driver *devp);

msg_t max17205ValidateRegisters(MAX17205Driver *devp, const max17205_regval_t * list, size_t len, bool * valid);
msg_t max17205WriteRegisters(MAX17205Driver *devp, const max17205_regval_t * list, size_t len);
msg_t max17205FirmwareReset(MAX17205Driver * devp);
msg_t max17205HardwareReset(MAX17205Driver *devp);

msg_t max17205ReadNVWriteCountMaskingRegister(MAX17205Driver *devp, uint16_t *reg_dest, uint8_t *number_of_writes_left);
msg_t max17205NonvolatileBlockProgram(MAX17205Driver *devp);
msg_t max17205PrintVolatileMemory(MAX17205Driver *devp);
msg_t max17205PrintNonvolatileMemory(MAX17205Driver *devp);

const char* max17205RegToStr(const uint16_t reg);

#ifdef __cplusplus
}
#endif

#endif /* _MAX17205_H_ */

/** @} */
