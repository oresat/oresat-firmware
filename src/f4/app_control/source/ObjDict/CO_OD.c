// clang-format off
/*******************************************************************************
    CANopen Object Dictionary definition for CANopenNode v1 to v2

    This file was automatically generated with
    libedssharp Object Dictionary Editor v0.8-123-g6c02323

    https://github.com/CANopenNode/CANopenNode
    https://github.com/robincornelius/libedssharp

    DON'T EDIT THIS FILE MANUALLY !!!!
*******************************************************************************/
// For CANopenNode V2 users, C macro `CO_VERSION_MAJOR=2` has to be added to project options
#ifndef CO_VERSION_MAJOR
 #include "CO_driver.h"
 #include "CO_OD.h"
 #include "CO_SDO.h"
#elif CO_VERSION_MAJOR < 4
 #include "301/CO_driver.h"
 #include "CO_OD.h"
 #include "301/CO_SDOserver.h"
#else
 #error This Object dictionary is not compatible with CANopenNode v4.0 and up!
#endif

/*******************************************************************************
   DEFINITION AND INITIALIZATION OF OBJECT DICTIONARY VARIABLES
*******************************************************************************/


/***** Definition for RAM variables *******************************************/
struct sCO_OD_RAM CO_OD_RAM = {
           CO_OD_FIRST_LAST_WORD,

/*1001*/ 0x0L,
/*1002*/ 0x0000L,
/*1003*/ {0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1010*/ {0x0001L, 0x0001L, 0x0001L, 0x0001L},
/*1011*/ {0x0001L, 0x0001L, 0x0001L, 0x0001L},
/*1F89*/ 0x0000L,
/*2010*/ 0x00000000L,
/*2011*/ 0x00000000L,
/*2020*/ {0x0000L, 0x0000L, 0x0000L},
/*2021*/ {0x3L, 0x00, 0x00, 0x00},
/*2022*/ {0x8L, 0x0, 0x0L, 0x0L, 0x0L, 0x00, 0x00, 0x00, 0x00},
/*2100*/ {0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L},
/*6000*/ {'B'},
/*7000*/ {0x5L, 0x0000L, 0x0L, 0x0, 0x00, 0x00},
/*7001*/ {{0x2CL, 0x1C20, 0x1C20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0L, 0x0L, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0L, 0x0L},
/*7002*/ {0x2CL, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0L, 0x0L, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0L, 0x0L}},
/*7003*/ {{0x10L, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0, 0x0, 0x7F, 0x7F, 0x80, 0x80},
/*7004*/ {0x10L, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0, 0x0, 0x7F, 0x7F, 0x80, 0x80},
/*7005*/ {0x10L, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0, 0x0, 0x7F, 0x7F, 0x80, 0x80},
/*7006*/ {0x10L, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0, 0x0, 0x7F, 0x7F, 0x80, 0x80},
/*7007*/ {0x10L, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0, 0x0, 0x7F, 0x7F, 0x80, 0x80},
/*7008*/ {0x10L, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0, 0x0, 0x7F, 0x7F, 0x80, 0x80},
/*7009*/ {0x10L, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0, 0x0, 0x7F, 0x7F, 0x80, 0x80},
/*700A*/ {0x10L, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0, 0x0, 0x7F, 0x7F, 0x80, 0x80}},
/*700B*/ {{0xCL, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x00, 0x00, 0x00, 0x00000000L},
/*700C*/ {0xCL, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x00, 0x00, 0x00, 0x00000000L}},
/*700D*/ {0x11L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x00000000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*700E*/ {0x13L, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0L, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
/*700F*/ {0x1L, 0x00},
/*7013*/ {0x9L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0},
/*7014*/ {0x8L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L},

           CO_OD_FIRST_LAST_WORD,
};


/***** Definition for ROM variables *******************************************/
struct sCO_OD_ROM CO_OD_ROM = {
           CO_OD_FIRST_LAST_WORD,

/*1000*/ 0x0000L,
/*1008*/ {'O', 'r', 'e', 'S', 'a', 't', ' ', 'N', 'o', 'd', 'e'},
/*1009*/ {'0', '.', '0'},
/*100A*/ {'0', '.', '0', '.', '0'},
/*1018*/ {0x4L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1029*/ {0x1L, 0x1L, 0x1L, 0x1L, 0x1L, 0x1L},

           CO_OD_FIRST_LAST_WORD,
};


/***** Definition for EEPROM variables *******************************************/
struct sCO_OD_EEPROM CO_OD_EEPROM = {
           CO_OD_FIRST_LAST_WORD,


           CO_OD_FIRST_LAST_WORD,
};


/***** Definition for PERSIST_COMM variables *******************************************/
struct sCO_OD_PERSIST_COMM CO_OD_PERSIST_COMM = {
           CO_OD_FIRST_LAST_WORD,

/*1005*/ 0x0080L,
/*1006*/ 0x0000L,
/*1007*/ 0x0000L,
/*1014*/ 0x0080L,
/*1015*/ 0x00,
/*1016*/ {0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1017*/ 0x3E8,
/*1019*/ 0x0L,
/*1028*/ {0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1200*/ {{0x3L, 0x80000000L, 0x80000000L, 0x1L}},
/*1280*/ {{0x3L, 0x80000000L, 0x80000000L, 0x1L}},
/*1400*/ {{0x5L, 0x0181L, 0xFEL, 0x00},
/*1401*/ {0x5L, 0x0184L, 0xFEL, 0x00},
/*1402*/ {0x5L, 0x0284L, 0xFEL, 0x00},
/*1403*/ {0x5L, 0x0384L, 0xFEL, 0x00},
/*1404*/ {0x5L, 0x0484L, 0xFEL, 0x00},
/*1405*/ {0x5L, 0x0185L, 0xFEL, 0x00},
/*1406*/ {0x5L, 0x0285L, 0xFEL, 0x00},
/*1407*/ {0x5L, 0x0385L, 0xFEL, 0x00},
/*1408*/ {0x5L, 0x0485L, 0xFEL, 0x00},
/*1409*/ {0x5L, 0x0186L, 0xFEL, 0x00},
/*140A*/ {0x5L, 0x0286L, 0xFEL, 0x00},
/*140B*/ {0x5L, 0x018CL, 0xFEL, 0x00},
/*140C*/ {0x5L, 0x028CL, 0xFEL, 0x00},
/*140D*/ {0x5L, 0x038CL, 0xFEL, 0x00},
/*140E*/ {0x5L, 0x048CL, 0xFEL, 0x00},
/*140F*/ {0x5L, 0x0190L, 0xFEL, 0x00},
/*1410*/ {0x5L, 0x0290L, 0xFEL, 0x00},
/*1411*/ {0x5L, 0x0390L, 0xFEL, 0x00},
/*1412*/ {0x5L, 0x0490L, 0xFEL, 0x00},
/*1413*/ {0x5L, 0x0194L, 0xFEL, 0x00},
/*1414*/ {0x5L, 0x0294L, 0xFEL, 0x00},
/*1415*/ {0x5L, 0x0394L, 0xFEL, 0x00},
/*1416*/ {0x5L, 0x0494L, 0xFEL, 0x00},
/*1417*/ {0x5L, 0x0198L, 0xFEL, 0x00},
/*1418*/ {0x5L, 0x0298L, 0xFEL, 0x00},
/*1419*/ {0x5L, 0x0398L, 0xFEL, 0x00},
/*141A*/ {0x5L, 0x0498L, 0xFEL, 0x00},
/*141B*/ {0x5L, 0x01ACL, 0xFEL, 0x00},
/*141C*/ {0x5L, 0x02ACL, 0xFEL, 0x00},
/*141D*/ {0x5L, 0x03ACL, 0xFEL, 0x00},
/*141E*/ {0x5L, 0x04ACL, 0xFEL, 0x00},
/*141F*/ {0x5L, 0x01B4L, 0xFEL, 0x00},
/*1420*/ {0x5L, 0x02B4L, 0xFEL, 0x00},
/*1421*/ {0x5L, 0x03B4L, 0xFEL, 0x00},
/*1422*/ {0x5L, 0x04B4L, 0xFEL, 0x00},
/*1423*/ {0x5L, 0x01B5L, 0xFEL, 0x00},
/*1424*/ {0x5L, 0x02B5L, 0xFEL, 0x00},
/*1425*/ {0x5L, 0x03B5L, 0xFEL, 0x00},
/*1426*/ {0x5L, 0x01B8L, 0xFEL, 0x00},
/*1427*/ {0x5L, 0x02B8L, 0xFEL, 0x00},
/*1428*/ {0x5L, 0x03B8L, 0xFEL, 0x00},
/*1429*/ {0x5L, 0x04B8L, 0xFEL, 0x00},
/*142A*/ {0x5L, 0x01B9L, 0xFEL, 0x00},
/*142B*/ {0x5L, 0x02B9L, 0xFEL, 0x00},
/*142C*/ {0x5L, 0x01CCL, 0xFEL, 0x00},
/*142D*/ {0x5L, 0x02CCL, 0xFEL, 0x00},
/*142E*/ {0x5L, 0x03CCL, 0xFEL, 0x00}},
/*1600*/ {{0x1L, 0x20100040L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1601*/ {0x4L, 0x70010110L, 0x70010310L, 0x70010510L, 0x70010710L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1602*/ {0x3L, 0x70010910L, 0x70010B10L, 0x70010D10L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1603*/ {0x4L, 0x70010F10L, 0x70011110L, 0x70011310L, 0x70011510L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1604*/ {0x4L, 0x70012310L, 0x70012510L, 0x70012710L, 0x70012910L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1605*/ {0x4L, 0x70011710L, 0x70011910L, 0x70012108L, 0x70012B08L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1606*/ {0x4L, 0x70010210L, 0x70010410L, 0x70010610L, 0x70010810L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1607*/ {0x3L, 0x70010A10L, 0x70010C10L, 0x70010E10L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1608*/ {0x4L, 0x70011010L, 0x70011210L, 0x70011410L, 0x70011610L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1609*/ {0x4L, 0x70012410L, 0x70012610L, 0x70012810L, 0x70012A10L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*160A*/ {0x4L, 0x70011810L, 0x70011A10L, 0x70012208L, 0x70012C08L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*160B*/ {0x4L, 0x70030110L, 0x70030210L, 0x70030310L, 0x70030410L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*160C*/ {0x4L, 0x70030510L, 0x70030610L, 0x70030710L, 0x70030810L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*160D*/ {0x2L, 0x70030910L, 0x70030A10L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*160E*/ {0x6L, 0x70030B08L, 0x70030C08L, 0x70030D08L, 0x70030E08L, 0x70030F08L, 0x70031008L, 0x0000L, 0x0000L},
/*160F*/ {0x4L, 0x70040110L, 0x70040210L, 0x70040310L, 0x70040410L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1610*/ {0x4L, 0x70040510L, 0x70040610L, 0x70040710L, 0x70040810L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1611*/ {0x2L, 0x70040910L, 0x70040A10L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1612*/ {0x6L, 0x70040B08L, 0x70040C08L, 0x70040D08L, 0x70040E08L, 0x70040F08L, 0x70041008L, 0x0000L, 0x0000L},
/*1613*/ {0x4L, 0x70050110L, 0x70050210L, 0x70050310L, 0x70050410L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1614*/ {0x4L, 0x70050510L, 0x70050610L, 0x70050710L, 0x70050810L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1615*/ {0x2L, 0x70050910L, 0x70050A10L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1616*/ {0x6L, 0x70050B08L, 0x70050C08L, 0x70050D08L, 0x70050E08L, 0x70050F08L, 0x70051008L, 0x0000L, 0x0000L},
/*1617*/ {0x4L, 0x70060110L, 0x70060210L, 0x70060310L, 0x70060410L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1618*/ {0x4L, 0x70060510L, 0x70060610L, 0x70060710L, 0x70060810L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1619*/ {0x2L, 0x70060910L, 0x70060A10L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*161A*/ {0x6L, 0x70060B08L, 0x70060C08L, 0x70060D08L, 0x70060E08L, 0x70060F08L, 0x70061008L, 0x0000L, 0x0000L},
/*161B*/ {0x6L, 0x700B0108L, 0x700B0208L, 0x700B0308L, 0x700B0408L, 0x700B0508L, 0x700B0608L, 0x0000L, 0x0000L},
/*161C*/ {0x2L, 0x700B0708L, 0x700B0808L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*161D*/ {0x3L, 0x700B0910L, 0x700B0A10L, 0x700B0B10L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*161E*/ {0x1L, 0x700B0C40L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*161F*/ {0x6L, 0x700D0108L, 0x700D0208L, 0x700D0308L, 0x700D0408L, 0x700D0508L, 0x700D0608L, 0x0000L, 0x0000L},
/*1620*/ {0x2L, 0x700D0708L, 0x700D0808L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1621*/ {0x1L, 0x700D0940L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1622*/ {0x2L, 0x700D0C20L, 0x700D0D20L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1623*/ {0x2L, 0x700D0E20L, 0x700D0F20L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1624*/ {0x2L, 0x700D0908L, 0x700D0A08L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1625*/ {0x2L, 0x700D0E20L, 0x700D0F20L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1626*/ {0x3L, 0x700E0110L, 0x700E0210L, 0x700E0310L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1627*/ {0x3L, 0x700E0410L, 0x700E0510L, 0x700E0610L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1628*/ {0x1L, 0x700E0708L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1629*/ {0x4L, 0x700E0820L, 0x700E0920L, 0x700E0A20L, 0x700E0B20L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*162A*/ {0x4L, 0x700E0C20L, 0x700E0D20L, 0x700E0E20L, 0x700E0F20L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*162B*/ {0x4L, 0x700E1020L, 0x700E1120L, 0x700E1220L, 0x700E1320L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*162C*/ {0x6L, 0x70130108L, 0x70130208L, 0x70130308L, 0x70130408L, 0x70130508L, 0x70130608L, 0x0000L, 0x0000L},
/*162D*/ {0x2L, 0x70130708L, 0x70130808L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*162E*/ {0x1L, 0x70130908L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L}},
/*1800*/ {{0x6L, 0xC0000180L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*1801*/ {0x6L, 0xC0000280L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*1802*/ {0x6L, 0xC0000380L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*1803*/ {0x6L, 0xC0000480L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*1804*/ {0x6L, 0xC0000180L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*1805*/ {0x6L, 0xC0000280L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*1806*/ {0x6L, 0xC0000380L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*1807*/ {0x6L, 0xC0000480L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*1808*/ {0x6L, 0xC0000180L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*1809*/ {0x6L, 0xC0000280L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*180A*/ {0x6L, 0xC0000380L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*180B*/ {0x6L, 0xC0000480L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*180C*/ {0x6L, 0xC0000180L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*180D*/ {0x6L, 0xC0000280L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*180E*/ {0x6L, 0xC0000380L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*180F*/ {0x6L, 0xC0000480L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L}},
/*1A00*/ {{0x1L, 0x20100040L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1A01*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1A02*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1A03*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1A04*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1A05*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1A06*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1A07*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1A08*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1A09*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1A0A*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1A0B*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1A0C*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1A0D*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1A0E*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1A0F*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L}},
/*1F80*/ 0x0008L,
/*1F81*/ {0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1F82*/ {0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L},

           CO_OD_FIRST_LAST_WORD,
};


/***** Definition for PERSIST_MFR variables *******************************************/
struct sCO_OD_PERSIST_MFR CO_OD_PERSIST_MFR = {
           CO_OD_FIRST_LAST_WORD,

/*2000*/ {0x4L, 0x0L, 0x0L, 0x0L, 0x0L},

           CO_OD_FIRST_LAST_WORD,
};


/***** Definition for PERSIST_APP variables *******************************************/
struct sCO_OD_PERSIST_APP CO_OD_PERSIST_APP = {
           CO_OD_FIRST_LAST_WORD,

/*6001*/ {0x3L, 0x0A, 0x3C, 0},
/*6002*/ {0x3L, 0x012CL, 0x3A98L, 0x3L},
/*6003*/ {0x2L, 0x127500L, 0x2710L},

           CO_OD_FIRST_LAST_WORD,
};


/***** Definition for PERSIST_STATE variables *******************************************/
struct sCO_OD_PERSIST_STATE CO_OD_PERSIST_STATE = {
           CO_OD_FIRST_LAST_WORD,

/*6004*/ {0xEL, 0x00000000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0, 0x00, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x00000000L, 0x00000000L},

           CO_OD_FIRST_LAST_WORD,
};




/*******************************************************************************
   STRUCTURES FOR RECORD TYPE OBJECTS
*******************************************************************************/


/*0x1018*/ const CO_OD_entryRecord_t OD_record1018[5] = {
           {(void*)&CO_OD_ROM.identity.highestSubIndexSupported, 0x05, 0x1 },
           {(void*)&CO_OD_ROM.identity.vendorID, 0x85, 0x4 },
           {(void*)&CO_OD_ROM.identity.productCode, 0x85, 0x4 },
           {(void*)&CO_OD_ROM.identity.revisionNumber, 0x85, 0x4 },
           {(void*)&CO_OD_ROM.identity.serialNumber, 0x85, 0x4 },
};

/*0x1200*/ const CO_OD_entryRecord_t OD_record1200[4] = {
           {(void*)&CO_OD_PERSIST_COMM.SDOServerParameter[0].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.SDOServerParameter[0].COB_IDClientToServer, 0xBF, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.SDOServerParameter[0].COB_IDServerToClient, 0xBF, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.SDOServerParameter[0].nodeIDOfTheSDOClient, 0x0F, 0x1 },
};

/*0x1280*/ const CO_OD_entryRecord_t OD_record1280[4] = {
           {(void*)&CO_OD_PERSIST_COMM.SDOClientParameter[0].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.SDOClientParameter[0].COB_IDClientToServer, 0xBF, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.SDOClientParameter[0].COB_IDServerToClient, 0xBF, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.SDOClientParameter[0].nodeIDOfTheSDOServer, 0x0F, 0x1 },
};

/*0x1400*/ const CO_OD_entryRecord_t OD_record1400[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[0].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[0].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[0].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[0].eventTimer, 0x8F, 0x2 },
};

/*0x1401*/ const CO_OD_entryRecord_t OD_record1401[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[1].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[1].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[1].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[1].eventTimer, 0x8F, 0x2 },
};

/*0x1402*/ const CO_OD_entryRecord_t OD_record1402[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[2].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[2].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[2].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[2].eventTimer, 0x8F, 0x2 },
};

/*0x1403*/ const CO_OD_entryRecord_t OD_record1403[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[3].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[3].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[3].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[3].eventTimer, 0x8F, 0x2 },
};

/*0x1404*/ const CO_OD_entryRecord_t OD_record1404[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[4].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[4].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[4].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[4].eventTimer, 0x8F, 0x2 },
};

/*0x1405*/ const CO_OD_entryRecord_t OD_record1405[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[5].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[5].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[5].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[5].eventTimer, 0x8F, 0x2 },
};

/*0x1406*/ const CO_OD_entryRecord_t OD_record1406[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[6].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[6].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[6].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[6].eventTimer, 0x8F, 0x2 },
};

/*0x1407*/ const CO_OD_entryRecord_t OD_record1407[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[7].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[7].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[7].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[7].eventTimer, 0x8F, 0x2 },
};

/*0x1408*/ const CO_OD_entryRecord_t OD_record1408[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[8].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[8].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[8].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[8].eventTimer, 0x8F, 0x2 },
};

/*0x1409*/ const CO_OD_entryRecord_t OD_record1409[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[9].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[9].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[9].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[9].eventTimer, 0x8F, 0x2 },
};

/*0x140A*/ const CO_OD_entryRecord_t OD_record140A[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[10].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[10].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[10].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[10].eventTimer, 0x8F, 0x2 },
};

/*0x140B*/ const CO_OD_entryRecord_t OD_record140B[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[11].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[11].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[11].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[11].eventTimer, 0x8F, 0x2 },
};

/*0x140C*/ const CO_OD_entryRecord_t OD_record140C[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[12].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[12].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[12].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[12].eventTimer, 0x8F, 0x2 },
};

/*0x140D*/ const CO_OD_entryRecord_t OD_record140D[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[13].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[13].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[13].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[13].eventTimer, 0x8F, 0x2 },
};

/*0x140E*/ const CO_OD_entryRecord_t OD_record140E[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[14].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[14].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[14].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[14].eventTimer, 0x8F, 0x2 },
};

/*0x140F*/ const CO_OD_entryRecord_t OD_record140F[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[15].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[15].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[15].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[15].eventTimer, 0x8F, 0x2 },
};

/*0x1410*/ const CO_OD_entryRecord_t OD_record1410[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[16].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[16].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[16].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[16].eventTimer, 0x8F, 0x2 },
};

/*0x1411*/ const CO_OD_entryRecord_t OD_record1411[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[17].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[17].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[17].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[17].eventTimer, 0x8F, 0x2 },
};

/*0x1412*/ const CO_OD_entryRecord_t OD_record1412[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[18].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[18].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[18].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[18].eventTimer, 0x8F, 0x2 },
};

/*0x1413*/ const CO_OD_entryRecord_t OD_record1413[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[19].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[19].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[19].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[19].eventTimer, 0x8F, 0x2 },
};

/*0x1414*/ const CO_OD_entryRecord_t OD_record1414[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[20].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[20].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[20].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[20].eventTimer, 0x8F, 0x2 },
};

/*0x1415*/ const CO_OD_entryRecord_t OD_record1415[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[21].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[21].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[21].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[21].eventTimer, 0x8F, 0x2 },
};

/*0x1416*/ const CO_OD_entryRecord_t OD_record1416[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[22].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[22].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[22].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[22].eventTimer, 0x8F, 0x2 },
};

/*0x1417*/ const CO_OD_entryRecord_t OD_record1417[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[23].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[23].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[23].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[23].eventTimer, 0x8F, 0x2 },
};

/*0x1418*/ const CO_OD_entryRecord_t OD_record1418[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[24].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[24].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[24].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[24].eventTimer, 0x8F, 0x2 },
};

/*0x1419*/ const CO_OD_entryRecord_t OD_record1419[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[25].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[25].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[25].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[25].eventTimer, 0x8F, 0x2 },
};

/*0x141A*/ const CO_OD_entryRecord_t OD_record141A[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[26].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[26].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[26].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[26].eventTimer, 0x8F, 0x2 },
};

/*0x141B*/ const CO_OD_entryRecord_t OD_record141B[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[27].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[27].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[27].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[27].eventTimer, 0x8F, 0x2 },
};

/*0x141C*/ const CO_OD_entryRecord_t OD_record141C[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[28].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[28].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[28].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[28].eventTimer, 0x8F, 0x2 },
};

/*0x141D*/ const CO_OD_entryRecord_t OD_record141D[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[29].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[29].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[29].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[29].eventTimer, 0x8F, 0x2 },
};

/*0x141E*/ const CO_OD_entryRecord_t OD_record141E[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[30].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[30].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[30].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[30].eventTimer, 0x8F, 0x2 },
};

/*0x141F*/ const CO_OD_entryRecord_t OD_record141F[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[31].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[31].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[31].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[31].eventTimer, 0x8F, 0x2 },
};

/*0x1420*/ const CO_OD_entryRecord_t OD_record1420[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[32].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[32].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[32].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[32].eventTimer, 0x8F, 0x2 },
};

/*0x1421*/ const CO_OD_entryRecord_t OD_record1421[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[33].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[33].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[33].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[33].eventTimer, 0x8F, 0x2 },
};

/*0x1422*/ const CO_OD_entryRecord_t OD_record1422[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[34].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[34].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[34].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[34].eventTimer, 0x8F, 0x2 },
};

/*0x1423*/ const CO_OD_entryRecord_t OD_record1423[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[35].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[35].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[35].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[35].eventTimer, 0x8F, 0x2 },
};

/*0x1424*/ const CO_OD_entryRecord_t OD_record1424[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[36].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[36].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[36].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[36].eventTimer, 0x8F, 0x2 },
};

/*0x1425*/ const CO_OD_entryRecord_t OD_record1425[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[37].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[37].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[37].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[37].eventTimer, 0x8F, 0x2 },
};

/*0x1426*/ const CO_OD_entryRecord_t OD_record1426[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[38].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[38].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[38].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[38].eventTimer, 0x8F, 0x2 },
};

/*0x1427*/ const CO_OD_entryRecord_t OD_record1427[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[39].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[39].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[39].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[39].eventTimer, 0x8F, 0x2 },
};

/*0x1428*/ const CO_OD_entryRecord_t OD_record1428[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[40].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[40].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[40].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[40].eventTimer, 0x8F, 0x2 },
};

/*0x1429*/ const CO_OD_entryRecord_t OD_record1429[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[41].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[41].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[41].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[41].eventTimer, 0x8F, 0x2 },
};

/*0x142A*/ const CO_OD_entryRecord_t OD_record142A[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[42].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[42].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[42].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[42].eventTimer, 0x8F, 0x2 },
};

/*0x142B*/ const CO_OD_entryRecord_t OD_record142B[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[43].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[43].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[43].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[43].eventTimer, 0x8F, 0x2 },
};

/*0x142C*/ const CO_OD_entryRecord_t OD_record142C[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[44].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[44].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[44].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[44].eventTimer, 0x8F, 0x2 },
};

/*0x142D*/ const CO_OD_entryRecord_t OD_record142D[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[45].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[45].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[45].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[45].eventTimer, 0x8F, 0x2 },
};

/*0x142E*/ const CO_OD_entryRecord_t OD_record142E[4] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[46].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[46].COB_IDUsedByRPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[46].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOCommunicationParameter[46].eventTimer, 0x8F, 0x2 },
};

/*0x1600*/ const CO_OD_entryRecord_t OD_record1600[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[0].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[0].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[0].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[0].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[0].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[0].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[0].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[0].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[0].applicationObject8, 0x8F, 0x4 },
};

/*0x1601*/ const CO_OD_entryRecord_t OD_record1601[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[1].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[1].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[1].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[1].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[1].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[1].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[1].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[1].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[1].applicationObject8, 0x8F, 0x4 },
};

/*0x1602*/ const CO_OD_entryRecord_t OD_record1602[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[2].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[2].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[2].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[2].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[2].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[2].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[2].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[2].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[2].applicationObject8, 0x8F, 0x4 },
};

/*0x1603*/ const CO_OD_entryRecord_t OD_record1603[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[3].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[3].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[3].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[3].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[3].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[3].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[3].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[3].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[3].applicationObject8, 0x8F, 0x4 },
};

/*0x1604*/ const CO_OD_entryRecord_t OD_record1604[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[4].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[4].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[4].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[4].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[4].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[4].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[4].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[4].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[4].applicationObject8, 0x8F, 0x4 },
};

/*0x1605*/ const CO_OD_entryRecord_t OD_record1605[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[5].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[5].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[5].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[5].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[5].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[5].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[5].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[5].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[5].applicationObject8, 0x8F, 0x4 },
};

/*0x1606*/ const CO_OD_entryRecord_t OD_record1606[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[6].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[6].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[6].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[6].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[6].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[6].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[6].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[6].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[6].applicationObject8, 0x8F, 0x4 },
};

/*0x1607*/ const CO_OD_entryRecord_t OD_record1607[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[7].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[7].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[7].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[7].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[7].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[7].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[7].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[7].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[7].applicationObject8, 0x8F, 0x4 },
};

/*0x1608*/ const CO_OD_entryRecord_t OD_record1608[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[8].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[8].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[8].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[8].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[8].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[8].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[8].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[8].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[8].applicationObject8, 0x8F, 0x4 },
};

/*0x1609*/ const CO_OD_entryRecord_t OD_record1609[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[9].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[9].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[9].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[9].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[9].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[9].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[9].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[9].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[9].applicationObject8, 0x8F, 0x4 },
};

/*0x160A*/ const CO_OD_entryRecord_t OD_record160A[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[10].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[10].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[10].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[10].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[10].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[10].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[10].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[10].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[10].applicationObject8, 0x8F, 0x4 },
};

/*0x160B*/ const CO_OD_entryRecord_t OD_record160B[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[11].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[11].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[11].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[11].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[11].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[11].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[11].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[11].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[11].applicationObject8, 0x8F, 0x4 },
};

/*0x160C*/ const CO_OD_entryRecord_t OD_record160C[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[12].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[12].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[12].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[12].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[12].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[12].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[12].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[12].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[12].applicationObject8, 0x8F, 0x4 },
};

/*0x160D*/ const CO_OD_entryRecord_t OD_record160D[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[13].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[13].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[13].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[13].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[13].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[13].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[13].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[13].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[13].applicationObject8, 0x8F, 0x4 },
};

/*0x160E*/ const CO_OD_entryRecord_t OD_record160E[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[14].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[14].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[14].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[14].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[14].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[14].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[14].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[14].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[14].applicationObject8, 0x8F, 0x4 },
};

/*0x160F*/ const CO_OD_entryRecord_t OD_record160F[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[15].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[15].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[15].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[15].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[15].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[15].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[15].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[15].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[15].applicationObject8, 0x8F, 0x4 },
};

/*0x1610*/ const CO_OD_entryRecord_t OD_record1610[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[16].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[16].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[16].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[16].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[16].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[16].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[16].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[16].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[16].applicationObject8, 0x8F, 0x4 },
};

/*0x1611*/ const CO_OD_entryRecord_t OD_record1611[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[17].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[17].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[17].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[17].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[17].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[17].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[17].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[17].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[17].applicationObject8, 0x8F, 0x4 },
};

/*0x1612*/ const CO_OD_entryRecord_t OD_record1612[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[18].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[18].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[18].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[18].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[18].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[18].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[18].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[18].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[18].applicationObject8, 0x8F, 0x4 },
};

/*0x1613*/ const CO_OD_entryRecord_t OD_record1613[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[19].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[19].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[19].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[19].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[19].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[19].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[19].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[19].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[19].applicationObject8, 0x8F, 0x4 },
};

/*0x1614*/ const CO_OD_entryRecord_t OD_record1614[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[20].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[20].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[20].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[20].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[20].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[20].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[20].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[20].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[20].applicationObject8, 0x8F, 0x4 },
};

/*0x1615*/ const CO_OD_entryRecord_t OD_record1615[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[21].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[21].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[21].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[21].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[21].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[21].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[21].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[21].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[21].applicationObject8, 0x8F, 0x4 },
};

/*0x1616*/ const CO_OD_entryRecord_t OD_record1616[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[22].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[22].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[22].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[22].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[22].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[22].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[22].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[22].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[22].applicationObject8, 0x8F, 0x4 },
};

/*0x1617*/ const CO_OD_entryRecord_t OD_record1617[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[23].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[23].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[23].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[23].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[23].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[23].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[23].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[23].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[23].applicationObject8, 0x8F, 0x4 },
};

/*0x1618*/ const CO_OD_entryRecord_t OD_record1618[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[24].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[24].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[24].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[24].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[24].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[24].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[24].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[24].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[24].applicationObject8, 0x8F, 0x4 },
};

/*0x1619*/ const CO_OD_entryRecord_t OD_record1619[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[25].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[25].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[25].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[25].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[25].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[25].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[25].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[25].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[25].applicationObject8, 0x8F, 0x4 },
};

/*0x161A*/ const CO_OD_entryRecord_t OD_record161A[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[26].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[26].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[26].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[26].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[26].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[26].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[26].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[26].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[26].applicationObject8, 0x8F, 0x4 },
};

/*0x161B*/ const CO_OD_entryRecord_t OD_record161B[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[27].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[27].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[27].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[27].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[27].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[27].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[27].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[27].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[27].applicationObject8, 0x8F, 0x4 },
};

/*0x161C*/ const CO_OD_entryRecord_t OD_record161C[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[28].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[28].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[28].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[28].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[28].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[28].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[28].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[28].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[28].applicationObject8, 0x8F, 0x4 },
};

/*0x161D*/ const CO_OD_entryRecord_t OD_record161D[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[29].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[29].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[29].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[29].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[29].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[29].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[29].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[29].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[29].applicationObject8, 0x8F, 0x4 },
};

/*0x161E*/ const CO_OD_entryRecord_t OD_record161E[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[30].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[30].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[30].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[30].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[30].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[30].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[30].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[30].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[30].applicationObject8, 0x8F, 0x4 },
};

/*0x161F*/ const CO_OD_entryRecord_t OD_record161F[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[31].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[31].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[31].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[31].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[31].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[31].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[31].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[31].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[31].applicationObject8, 0x8F, 0x4 },
};

/*0x1620*/ const CO_OD_entryRecord_t OD_record1620[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[32].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[32].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[32].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[32].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[32].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[32].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[32].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[32].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[32].applicationObject8, 0x8F, 0x4 },
};

/*0x1621*/ const CO_OD_entryRecord_t OD_record1621[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[33].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[33].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[33].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[33].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[33].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[33].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[33].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[33].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[33].applicationObject8, 0x8F, 0x4 },
};

/*0x1622*/ const CO_OD_entryRecord_t OD_record1622[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[34].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[34].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[34].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[34].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[34].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[34].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[34].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[34].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[34].applicationObject8, 0x8F, 0x4 },
};

/*0x1623*/ const CO_OD_entryRecord_t OD_record1623[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[35].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[35].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[35].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[35].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[35].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[35].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[35].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[35].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[35].applicationObject8, 0x8F, 0x4 },
};

/*0x1624*/ const CO_OD_entryRecord_t OD_record1624[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[36].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[36].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[36].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[36].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[36].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[36].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[36].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[36].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[36].applicationObject8, 0x8F, 0x4 },
};

/*0x1625*/ const CO_OD_entryRecord_t OD_record1625[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[37].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[37].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[37].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[37].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[37].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[37].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[37].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[37].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[37].applicationObject8, 0x8F, 0x4 },
};

/*0x1626*/ const CO_OD_entryRecord_t OD_record1626[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[38].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[38].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[38].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[38].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[38].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[38].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[38].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[38].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[38].applicationObject8, 0x8F, 0x4 },
};

/*0x1627*/ const CO_OD_entryRecord_t OD_record1627[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[39].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[39].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[39].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[39].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[39].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[39].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[39].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[39].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[39].applicationObject8, 0x8F, 0x4 },
};

/*0x1628*/ const CO_OD_entryRecord_t OD_record1628[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[40].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[40].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[40].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[40].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[40].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[40].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[40].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[40].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[40].applicationObject8, 0x8F, 0x4 },
};

/*0x1629*/ const CO_OD_entryRecord_t OD_record1629[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[41].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[41].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[41].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[41].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[41].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[41].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[41].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[41].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[41].applicationObject8, 0x8F, 0x4 },
};

/*0x162A*/ const CO_OD_entryRecord_t OD_record162A[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[42].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[42].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[42].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[42].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[42].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[42].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[42].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[42].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[42].applicationObject8, 0x8F, 0x4 },
};

/*0x162B*/ const CO_OD_entryRecord_t OD_record162B[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[43].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[43].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[43].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[43].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[43].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[43].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[43].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[43].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[43].applicationObject8, 0x8F, 0x4 },
};

/*0x162C*/ const CO_OD_entryRecord_t OD_record162C[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[44].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[44].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[44].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[44].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[44].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[44].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[44].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[44].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[44].applicationObject8, 0x8F, 0x4 },
};

/*0x162D*/ const CO_OD_entryRecord_t OD_record162D[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[45].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[45].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[45].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[45].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[45].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[45].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[45].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[45].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[45].applicationObject8, 0x8F, 0x4 },
};

/*0x162E*/ const CO_OD_entryRecord_t OD_record162E[9] = {
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[46].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[46].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[46].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[46].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[46].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[46].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[46].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[46].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.RPDOMappingParameter[46].applicationObject8, 0x8F, 0x4 },
};

/*0x1800*/ const CO_OD_entryRecord_t OD_record1800[7] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[0].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[0].COB_IDUsedByTPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[0].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[0].inhibitTime, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[0].compatibilityEntry, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[0].eventTimer, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[0].SYNCStartValue, 0x0F, 0x1 },
};

/*0x1801*/ const CO_OD_entryRecord_t OD_record1801[7] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[1].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[1].COB_IDUsedByTPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[1].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[1].inhibitTime, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[1].compatibilityEntry, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[1].eventTimer, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[1].SYNCStartValue, 0x0F, 0x1 },
};

/*0x1802*/ const CO_OD_entryRecord_t OD_record1802[7] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[2].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[2].COB_IDUsedByTPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[2].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[2].inhibitTime, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[2].compatibilityEntry, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[2].eventTimer, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[2].SYNCStartValue, 0x0F, 0x1 },
};

/*0x1803*/ const CO_OD_entryRecord_t OD_record1803[7] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[3].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[3].COB_IDUsedByTPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[3].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[3].inhibitTime, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[3].compatibilityEntry, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[3].eventTimer, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[3].SYNCStartValue, 0x0F, 0x1 },
};

/*0x1804*/ const CO_OD_entryRecord_t OD_record1804[7] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[4].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[4].COB_IDUsedByTPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[4].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[4].inhibitTime, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[4].compatibilityEntry, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[4].eventTimer, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[4].SYNCStartValue, 0x0F, 0x1 },
};

/*0x1805*/ const CO_OD_entryRecord_t OD_record1805[7] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[5].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[5].COB_IDUsedByTPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[5].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[5].inhibitTime, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[5].compatibilityEntry, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[5].eventTimer, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[5].SYNCStartValue, 0x0F, 0x1 },
};

/*0x1806*/ const CO_OD_entryRecord_t OD_record1806[7] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[6].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[6].COB_IDUsedByTPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[6].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[6].inhibitTime, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[6].compatibilityEntry, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[6].eventTimer, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[6].SYNCStartValue, 0x0F, 0x1 },
};

/*0x1807*/ const CO_OD_entryRecord_t OD_record1807[7] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[7].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[7].COB_IDUsedByTPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[7].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[7].inhibitTime, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[7].compatibilityEntry, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[7].eventTimer, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[7].SYNCStartValue, 0x0F, 0x1 },
};

/*0x1808*/ const CO_OD_entryRecord_t OD_record1808[7] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[8].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[8].COB_IDUsedByTPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[8].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[8].inhibitTime, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[8].compatibilityEntry, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[8].eventTimer, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[8].SYNCStartValue, 0x0F, 0x1 },
};

/*0x1809*/ const CO_OD_entryRecord_t OD_record1809[7] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[9].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[9].COB_IDUsedByTPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[9].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[9].inhibitTime, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[9].compatibilityEntry, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[9].eventTimer, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[9].SYNCStartValue, 0x0F, 0x1 },
};

/*0x180A*/ const CO_OD_entryRecord_t OD_record180A[7] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[10].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[10].COB_IDUsedByTPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[10].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[10].inhibitTime, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[10].compatibilityEntry, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[10].eventTimer, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[10].SYNCStartValue, 0x0F, 0x1 },
};

/*0x180B*/ const CO_OD_entryRecord_t OD_record180B[7] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[11].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[11].COB_IDUsedByTPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[11].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[11].inhibitTime, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[11].compatibilityEntry, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[11].eventTimer, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[11].SYNCStartValue, 0x0F, 0x1 },
};

/*0x180C*/ const CO_OD_entryRecord_t OD_record180C[7] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[12].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[12].COB_IDUsedByTPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[12].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[12].inhibitTime, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[12].compatibilityEntry, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[12].eventTimer, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[12].SYNCStartValue, 0x0F, 0x1 },
};

/*0x180D*/ const CO_OD_entryRecord_t OD_record180D[7] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[13].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[13].COB_IDUsedByTPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[13].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[13].inhibitTime, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[13].compatibilityEntry, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[13].eventTimer, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[13].SYNCStartValue, 0x0F, 0x1 },
};

/*0x180E*/ const CO_OD_entryRecord_t OD_record180E[7] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[14].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[14].COB_IDUsedByTPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[14].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[14].inhibitTime, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[14].compatibilityEntry, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[14].eventTimer, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[14].SYNCStartValue, 0x0F, 0x1 },
};

/*0x180F*/ const CO_OD_entryRecord_t OD_record180F[7] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[15].highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[15].COB_IDUsedByTPDO, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[15].transmissionType, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[15].inhibitTime, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[15].compatibilityEntry, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[15].eventTimer, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOCommunicationParameter[15].SYNCStartValue, 0x0F, 0x1 },
};

/*0x1A00*/ const CO_OD_entryRecord_t OD_record1A00[9] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[0].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[0].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[0].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[0].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[0].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[0].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[0].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[0].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[0].applicationObject8, 0x8F, 0x4 },
};

/*0x1A01*/ const CO_OD_entryRecord_t OD_record1A01[9] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[1].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[1].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[1].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[1].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[1].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[1].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[1].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[1].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[1].applicationObject8, 0x8F, 0x4 },
};

/*0x1A02*/ const CO_OD_entryRecord_t OD_record1A02[9] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[2].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[2].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[2].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[2].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[2].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[2].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[2].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[2].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[2].applicationObject8, 0x8F, 0x4 },
};

/*0x1A03*/ const CO_OD_entryRecord_t OD_record1A03[9] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[3].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[3].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[3].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[3].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[3].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[3].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[3].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[3].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[3].applicationObject8, 0x8F, 0x4 },
};

/*0x1A04*/ const CO_OD_entryRecord_t OD_record1A04[9] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[4].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[4].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[4].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[4].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[4].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[4].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[4].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[4].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[4].applicationObject8, 0x8F, 0x4 },
};

/*0x1A05*/ const CO_OD_entryRecord_t OD_record1A05[9] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[5].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[5].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[5].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[5].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[5].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[5].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[5].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[5].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[5].applicationObject8, 0x8F, 0x4 },
};

/*0x1A06*/ const CO_OD_entryRecord_t OD_record1A06[9] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[6].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[6].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[6].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[6].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[6].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[6].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[6].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[6].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[6].applicationObject8, 0x8F, 0x4 },
};

/*0x1A07*/ const CO_OD_entryRecord_t OD_record1A07[9] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[7].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[7].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[7].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[7].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[7].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[7].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[7].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[7].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[7].applicationObject8, 0x8F, 0x4 },
};

/*0x1A08*/ const CO_OD_entryRecord_t OD_record1A08[9] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[8].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[8].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[8].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[8].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[8].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[8].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[8].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[8].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[8].applicationObject8, 0x8F, 0x4 },
};

/*0x1A09*/ const CO_OD_entryRecord_t OD_record1A09[9] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[9].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[9].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[9].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[9].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[9].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[9].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[9].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[9].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[9].applicationObject8, 0x8F, 0x4 },
};

/*0x1A0A*/ const CO_OD_entryRecord_t OD_record1A0A[9] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[10].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[10].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[10].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[10].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[10].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[10].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[10].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[10].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[10].applicationObject8, 0x8F, 0x4 },
};

/*0x1A0B*/ const CO_OD_entryRecord_t OD_record1A0B[9] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[11].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[11].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[11].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[11].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[11].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[11].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[11].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[11].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[11].applicationObject8, 0x8F, 0x4 },
};

/*0x1A0C*/ const CO_OD_entryRecord_t OD_record1A0C[9] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[12].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[12].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[12].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[12].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[12].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[12].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[12].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[12].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[12].applicationObject8, 0x8F, 0x4 },
};

/*0x1A0D*/ const CO_OD_entryRecord_t OD_record1A0D[9] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[13].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[13].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[13].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[13].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[13].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[13].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[13].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[13].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[13].applicationObject8, 0x8F, 0x4 },
};

/*0x1A0E*/ const CO_OD_entryRecord_t OD_record1A0E[9] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[14].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[14].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[14].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[14].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[14].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[14].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[14].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[14].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[14].applicationObject8, 0x8F, 0x4 },
};

/*0x1A0F*/ const CO_OD_entryRecord_t OD_record1A0F[9] = {
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[15].numberOfMappedApplicationObjectsInPDO, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[15].applicationObject1, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[15].applicationObject2, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[15].applicationObject3, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[15].applicationObject4, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[15].applicationObject5, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[15].applicationObject6, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[15].applicationObject7, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_COMM.TPDOMappingParameter[15].applicationObject8, 0x8F, 0x4 },
};

/*0x2000*/ const CO_OD_entryRecord_t OD_record2000[5] = {
           {(void*)&CO_OD_PERSIST_MFR.BUS_Management.highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_MFR.BUS_Management.bdefault, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_MFR.BUS_Management.ttoggle, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_MFR.BUS_Management.ntoggle, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_MFR.BUS_Management.ctoggle, 0x0F, 0x1 },
};

/*0x2021*/ const CO_OD_entryRecord_t OD_record2021[4] = {
           {(void*)&CO_OD_RAM.MCU_Calibration.highestSubIndexSupported, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.MCU_Calibration.TS_CAL1, 0x86, 0x2 },
           {(void*)&CO_OD_RAM.MCU_Calibration.TS_CAL2, 0x86, 0x2 },
           {(void*)&CO_OD_RAM.MCU_Calibration.VREFINT_CAL, 0x86, 0x2 },
};

/*0x2022*/ const CO_OD_entryRecord_t OD_record2022[9] = {
           {(void*)&CO_OD_RAM.MCU_Sensors.highestSubIndexSupported, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.MCU_Sensors.temperature, 0x26, 0x1 },
           {(void*)&CO_OD_RAM.MCU_Sensors.VREFINT, 0x26, 0x1 },
           {(void*)&CO_OD_RAM.MCU_Sensors.VBAT, 0x26, 0x1 },
           {(void*)&CO_OD_RAM.MCU_Sensors.VBUSP_Current, 0x26, 0x1 },
           {(void*)&CO_OD_RAM.MCU_Sensors.temperatureRaw, 0xA6, 0x2 },
           {(void*)&CO_OD_RAM.MCU_Sensors.VREFINT_Raw, 0xA6, 0x2 },
           {(void*)&CO_OD_RAM.MCU_Sensors.VBAT_Raw, 0xA6, 0x2 },
           {(void*)&CO_OD_RAM.MCU_Sensors.VBUSP_CurrentRaw, 0xA6, 0x2 },
};

/*0x6001*/ const CO_OD_entryRecord_t OD_record6001[4] = {
           {(void*)&CO_OD_PERSIST_APP.stateControl.highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_APP.stateControl.saveInterval, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_APP.stateControl.EDL_Timeout, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_APP.stateControl.factoryReset, 0x0F, 0x1 },
};

/*0x6002*/ const CO_OD_entryRecord_t OD_record6002[4] = {
           {(void*)&CO_OD_PERSIST_APP.deploymentControl.highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_APP.deploymentControl.timeout, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_APP.deploymentControl.actuationTime, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_APP.deploymentControl.attempts, 0x0F, 0x1 },
};

/*0x6003*/ const CO_OD_entryRecord_t OD_record6003[3] = {
           {(void*)&CO_OD_PERSIST_APP.TX_Control.highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_APP.TX_Control.timeout, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_APP.TX_Control.beaconInterval, 0x8F, 0x4 },
};

/*0x6004*/ const CO_OD_entryRecord_t OD_record6004[15] = {
           {(void*)&CO_OD_PERSIST_STATE.persistentState.highestSubIndexSupported, 0x07, 0x1 },
           {(void*)&CO_OD_PERSIST_STATE.persistentState.timestamp, 0x8F, 0x8 },
           {(void*)&CO_OD_PERSIST_STATE.persistentState.alarmA, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_STATE.persistentState.alarmB, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_STATE.persistentState.wakeup, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_STATE.persistentState.lastTX_Enable, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_STATE.persistentState.lastEDL, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_STATE.persistentState.deployed, 0x0F, 0x1 },
           {(void*)&CO_OD_PERSIST_STATE.persistentState.powerCycles, 0x8F, 0x2 },
           {(void*)&CO_OD_PERSIST_STATE.persistentState.LBandRX_Bytes, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_STATE.persistentState.LBandRX_Packets, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_STATE.persistentState.UHF_RX_Bytes, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_STATE.persistentState.UHF_RX_Packets, 0x8F, 0x4 },
           {(void*)&CO_OD_PERSIST_STATE.persistentState.VC1SequenceCount, 0x8F, 0x8 },
           {(void*)&CO_OD_PERSIST_STATE.persistentState.VC1ExpediteCount, 0x8F, 0x8 },
};

/*0x7000*/ const CO_OD_entryRecord_t OD_record7000[6] = {
           {(void*)&CO_OD_RAM.C3Telemetry.highestSubIndexSupported, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.C3Telemetry.uptime, 0x86, 0x4 },
           {(void*)&CO_OD_RAM.C3Telemetry.EMMC_Usage, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.C3Telemetry.UHF_Temperature, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.C3Telemetry.UHF_FWD_Pwr, 0x86, 0x2 },
           {(void*)&CO_OD_RAM.C3Telemetry.UHF_REV_Pwr, 0x86, 0x2 },
};

/*0x7001*/ const CO_OD_entryRecord_t OD_record7001[45] = {
           {(void*)&CO_OD_RAM.battery[0].highestSubIndexSupported, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.battery[0].vbattBP1, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[0].vbattBP2, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[0].VCellMaxBP1, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[0].VCellMaxBP2, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[0].VCellMinBP1, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[0].VCellMinBP2, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[0].VCellBP1, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[0].VCellBP2, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[0].VCell1BP1, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[0].VCell1BP2, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[0].VCell2BP1, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[0].VCell2BP2, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[0].VCellAvgBP1, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[0].VCellAvgBP2, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[0].currentBP1, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[0].currentBP2, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[0].currentAvgBP1, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[0].currentAvgBP2, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[0].currentMaxBP1, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[0].currentMaxBP2, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[0].currentMinBP1, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[0].currentMinBP2, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[0].fullCapacityBP1, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[0].fullCapacityBP2, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[0].reportedCapacityBP1, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[0].reportedCapacityBP2, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[0].timeToEmptyBP1, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[0].timeToEmptyBP2, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[0].timeToFullBP1, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[0].timeToFullBP2, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[0].cyclesBP1, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[0].cyclesBP2, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[0].reportedStateOfChargeBP1, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.battery[0].reportedStateOfChargeBP2, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.battery[0].temperatureBP1, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[0].temperatureBP2, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[0].temperatureAvgBP1, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[0].temperatureAvgBP2, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[0].temperatureMaxBP1, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[0].temperatureMaxBP2, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[0].temperatureMinBP1, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[0].temperatureMinBP2, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[0].stateBP1, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.battery[0].stateBP2, 0x3E, 0x1 },
};

/*0x7002*/ const CO_OD_entryRecord_t OD_record7002[45] = {
           {(void*)&CO_OD_RAM.battery[1].highestSubIndexSupported, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.battery[1].vbattBP1, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[1].vbattBP2, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[1].VCellMaxBP1, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[1].VCellMaxBP2, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[1].VCellMinBP1, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[1].VCellMinBP2, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[1].VCellBP1, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[1].VCellBP2, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[1].VCell1BP1, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[1].VCell1BP2, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[1].VCell2BP1, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[1].VCell2BP2, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[1].VCellAvgBP1, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[1].VCellAvgBP2, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[1].currentBP1, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[1].currentBP2, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[1].currentAvgBP1, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[1].currentAvgBP2, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[1].currentMaxBP1, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[1].currentMaxBP2, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[1].currentMinBP1, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[1].currentMinBP2, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[1].fullCapacityBP1, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[1].fullCapacityBP2, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[1].reportedCapacityBP1, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[1].reportedCapacityBP2, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[1].timeToEmptyBP1, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[1].timeToEmptyBP2, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[1].timeToFullBP1, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[1].timeToFullBP2, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[1].cyclesBP1, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[1].cyclesBP2, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[1].reportedStateOfChargeBP1, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.battery[1].reportedStateOfChargeBP2, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.battery[1].temperatureBP1, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[1].temperatureBP2, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[1].temperatureAvgBP1, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[1].temperatureAvgBP2, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[1].temperatureMaxBP1, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[1].temperatureMaxBP2, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[1].temperatureMinBP1, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[1].temperatureMinBP2, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.battery[1].stateBP1, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.battery[1].stateBP2, 0x3E, 0x1 },
};

/*0x7003*/ const CO_OD_entryRecord_t OD_record7003[17] = {
           {(void*)&CO_OD_RAM.solarPanel[0].highestSubIndexSupported, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[0].voltage, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[0].current, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[0].power, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[0].voltageAvg, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[0].currentAvg, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[0].powerAvg, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[0].voltageMax, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[0].currentMax, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[0].powerMax, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[0].energy, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[0].cell1Temp, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[0].cell2Temp, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[0].cell1TempMin, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[0].cell2TempMin, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[0].cell1TempMax, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[0].cell2TempMax, 0x3E, 0x1 },
};

/*0x7004*/ const CO_OD_entryRecord_t OD_record7004[17] = {
           {(void*)&CO_OD_RAM.solarPanel[1].highestSubIndexSupported, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[1].voltage, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[1].current, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[1].power, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[1].voltageAvg, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[1].currentAvg, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[1].powerAvg, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[1].voltageMax, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[1].currentMax, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[1].powerMax, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[1].energy, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[1].cell1Temp, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[1].cell2Temp, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[1].cell1TempMin, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[1].cell2TempMin, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[1].cell1TempMax, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[1].cell2TempMax, 0x3E, 0x1 },
};

/*0x7005*/ const CO_OD_entryRecord_t OD_record7005[17] = {
           {(void*)&CO_OD_RAM.solarPanel[2].highestSubIndexSupported, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[2].voltage, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[2].current, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[2].power, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[2].voltageAvg, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[2].currentAvg, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[2].powerAvg, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[2].voltageMax, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[2].currentMax, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[2].powerMax, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[2].energy, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[2].cell1Temp, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[2].cell2Temp, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[2].cell1TempMin, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[2].cell2TempMin, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[2].cell1TempMax, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[2].cell2TempMax, 0x3E, 0x1 },
};

/*0x7006*/ const CO_OD_entryRecord_t OD_record7006[17] = {
           {(void*)&CO_OD_RAM.solarPanel[3].highestSubIndexSupported, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[3].voltage, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[3].current, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[3].power, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[3].voltageAvg, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[3].currentAvg, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[3].powerAvg, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[3].voltageMax, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[3].currentMax, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[3].powerMax, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[3].energy, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[3].cell1Temp, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[3].cell2Temp, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[3].cell1TempMin, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[3].cell2TempMin, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[3].cell1TempMax, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[3].cell2TempMax, 0x3E, 0x1 },
};

/*0x7007*/ const CO_OD_entryRecord_t OD_record7007[17] = {
           {(void*)&CO_OD_RAM.solarPanel[4].highestSubIndexSupported, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[4].voltage, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[4].current, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[4].power, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[4].voltageAvg, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[4].currentAvg, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[4].powerAvg, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[4].voltageMax, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[4].currentMax, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[4].powerMax, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[4].energy, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[4].cell1Temp, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[4].cell2Temp, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[4].cell1TempMin, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[4].cell2TempMin, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[4].cell1TempMax, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[4].cell2TempMax, 0x3E, 0x1 },
};

/*0x7008*/ const CO_OD_entryRecord_t OD_record7008[17] = {
           {(void*)&CO_OD_RAM.solarPanel[5].highestSubIndexSupported, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[5].voltage, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[5].current, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[5].power, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[5].voltageAvg, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[5].currentAvg, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[5].powerAvg, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[5].voltageMax, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[5].currentMax, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[5].powerMax, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[5].energy, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[5].cell1Temp, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[5].cell2Temp, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[5].cell1TempMin, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[5].cell2TempMin, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[5].cell1TempMax, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[5].cell2TempMax, 0x3E, 0x1 },
};

/*0x7009*/ const CO_OD_entryRecord_t OD_record7009[17] = {
           {(void*)&CO_OD_RAM.solarPanel[6].highestSubIndexSupported, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[6].voltage, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[6].current, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[6].power, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[6].voltageAvg, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[6].currentAvg, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[6].powerAvg, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[6].voltageMax, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[6].currentMax, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[6].powerMax, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[6].energy, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[6].cell1Temp, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[6].cell2Temp, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[6].cell1TempMin, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[6].cell2TempMin, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[6].cell1TempMax, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[6].cell2TempMax, 0x3E, 0x1 },
};

/*0x700A*/ const CO_OD_entryRecord_t OD_record700A[17] = {
           {(void*)&CO_OD_RAM.solarPanel[7].highestSubIndexSupported, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[7].voltage, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[7].current, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[7].power, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[7].voltageAvg, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[7].currentAvg, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[7].powerAvg, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[7].voltageMax, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[7].currentMax, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[7].powerMax, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[7].energy, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel[7].cell1Temp, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[7].cell2Temp, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[7].cell1TempMin, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[7].cell2TempMin, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[7].cell1TempMax, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel[7].cell2TempMax, 0x3E, 0x1 },
};

/*0x700B*/ const CO_OD_entryRecord_t OD_record700B[13] = {
           {(void*)&CO_OD_RAM.starTracker[0].highestSubIndexSupported, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.starTracker[0].rootParitionPercent, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.starTracker[0].RAM_Percent, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.starTracker[0].freadCacheLength, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.starTracker[0].fwriteCacheLength, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.starTracker[0].activeApps, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.starTracker[0].failedApps, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.starTracker[0].updaterStatus, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.starTracker[0].updatesAvailable, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.starTracker[0].rightAscension, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.starTracker[0].declination, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.starTracker[0].roll, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.starTracker[0].timestamp, 0xBE, 0x8 },
};

/*0x700C*/ const CO_OD_entryRecord_t OD_record700C[13] = {
           {(void*)&CO_OD_RAM.starTracker[1].highestSubIndexSupported, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.starTracker[1].rootParitionPercent, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.starTracker[1].RAM_Percent, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.starTracker[1].freadCacheLength, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.starTracker[1].fwriteCacheLength, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.starTracker[1].activeApps, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.starTracker[1].failedApps, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.starTracker[1].updaterStatus, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.starTracker[1].updatesAvailable, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.starTracker[1].rightAscension, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.starTracker[1].declination, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.starTracker[1].roll, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.starTracker[1].timestamp, 0xBE, 0x8 },
};

/*0x700D*/ const CO_OD_entryRecord_t OD_record700D[18] = {
           {(void*)&CO_OD_RAM.GPS.highestSubIndexSupported, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.GPS.rootParitionPercent, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.GPS.RAM_Percent, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.GPS.freadCacheLength, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.GPS.fwriteCacheLength, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.GPS.activeApps, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.GPS.failedApps, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.GPS.updaterStatus, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.GPS.updatesAvailable, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.GPS.GPS_Status, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.GPS.satellitesLocked, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.GPS.timestamp, 0xBE, 0x8 },
           {(void*)&CO_OD_RAM.GPS.positionX, 0xBE, 0x4 },
           {(void*)&CO_OD_RAM.GPS.positionY, 0xBE, 0x4 },
           {(void*)&CO_OD_RAM.GPS.positionZ, 0xBE, 0x4 },
           {(void*)&CO_OD_RAM.GPS.velocityX, 0xBE, 0x4 },
           {(void*)&CO_OD_RAM.GPS.velocityY, 0xBE, 0x4 },
           {(void*)&CO_OD_RAM.GPS.velocityZ, 0xBE, 0x4 },
};

/*0x700E*/ const CO_OD_entryRecord_t OD_record700E[20] = {
           {(void*)&CO_OD_RAM.ACS.highestSubIndexSupported, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.ACS.gyroPitch, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.ACS.gyroYaw, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.ACS.gyroRoll, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.ACS.accelerationX, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.ACS.accelerationY, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.ACS.accelerationZ, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.ACS.IMUTemp, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.ACS.magnetometerPZ1X, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.ACS.magnetometerPZ1Y, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.ACS.magnetometerPZ1Z, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.ACS.magnetometerPZ2X, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.ACS.magnetometerPZ2Y, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.ACS.magnetometerPZ2Z, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.ACS.magnetometerMZ1X, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.ACS.magnetometerMZ1Y, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.ACS.magnetometerMZ1Z, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.ACS.magnetometerMZ2X, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.ACS.magnetometerMZ2Y, 0xBE, 0x2 },
           {(void*)&CO_OD_RAM.ACS.magnetometerMZ2Z, 0xBE, 0x2 },
};

/*0x700F*/ const CO_OD_entryRecord_t OD_record700F[2] = {
           {(void*)&CO_OD_RAM.RWB.highestSubIndexSupported, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.RWB.subObject1, 0xB6, 0x2 },
};

/*0x7013*/ const CO_OD_entryRecord_t OD_record7013[10] = {
           {(void*)&CO_OD_RAM.dxWiFi.highestSubIndexSupported, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.dxWiFi.rootParitionPercent, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.dxWiFi.RAM_Percent, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.dxWiFi.freadCacheLength, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.dxWiFi.fwriteCacheLength, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.dxWiFi.activeApps, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.dxWiFi.failedApps, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.dxWiFi.updaterStatus, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.dxWiFi.updatesAvailable, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.dxWiFi.transmitting, 0x3E, 0x1 },
};

/*0x7014*/ const CO_OD_entryRecord_t OD_record7014[9] = {
           {(void*)&CO_OD_RAM.CFC.highestSubIndexSupported, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.CFC.rootParitionPercent, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.CFC.RAM_Percent, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.CFC.freadCacheLength, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.CFC.fwriteCacheLength, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.CFC.activeApps, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.CFC.failedApps, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.CFC.updaterStatus, 0x3E, 0x1 },
           {(void*)&CO_OD_RAM.CFC.updatesAvailable, 0x3E, 0x1 },
};

/*******************************************************************************
   OBJECT DICTIONARY
*******************************************************************************/
const CO_OD_entry_t CO_OD[CO_OD_NoOfElements] = {
{0x1000, 0x00, 0x85,  4, (void*)&CO_OD_ROM.deviceType},
{0x1001, 0x00, 0x36,  1, (void*)&CO_OD_RAM.errorRegister},
{0x1002, 0x00, 0xB6,  4, (void*)&CO_OD_RAM.manufacturerStatusRegister},
{0x1003, 0x08, 0x8E,  4, (void*)&CO_OD_RAM.preDefinedErrorField[0]},
{0x1005, 0x00, 0x8F,  4, (void*)&CO_OD_PERSIST_COMM.COB_ID_SYNCMessage},
{0x1006, 0x00, 0x8F,  4, (void*)&CO_OD_PERSIST_COMM.communicationCyclePeriod},
{0x1007, 0x00, 0x8F,  4, (void*)&CO_OD_PERSIST_COMM.synchronousWindowLength},
{0x1008, 0x00, 0x05, 11, (void*)&CO_OD_ROM.manufacturerDeviceName},
{0x1009, 0x00, 0x05,  3, (void*)&CO_OD_ROM.manufacturerHardwareVersion},
{0x100A, 0x00, 0x05,  5, (void*)&CO_OD_ROM.manufacturerSoftwareVersion},
{0x1010, 0x04, 0x8E,  4, (void*)&CO_OD_RAM.storeParameters[0]},
{0x1011, 0x04, 0x8E,  4, (void*)&CO_OD_RAM.restoreDefaultParameters[0]},
{0x1014, 0x00, 0x8F,  4, (void*)&CO_OD_PERSIST_COMM.COB_ID_EMCY},
{0x1015, 0x00, 0x8F,  2, (void*)&CO_OD_PERSIST_COMM.inhibitTimeEMCY},
{0x1016, 0x20, 0x8F,  4, (void*)&CO_OD_PERSIST_COMM.consumerHeartbeatTime[0]},
{0x1017, 0x00, 0x8F,  2, (void*)&CO_OD_PERSIST_COMM.producerHeartbeatTime},
{0x1018, 0x04, 0x00,  0, (void*)&OD_record1018},
{0x1019, 0x00, 0x0F,  1, (void*)&CO_OD_PERSIST_COMM.synchronousCounterOverflowValue},
{0x1028, 0x08, 0x8F,  4, (void*)&CO_OD_PERSIST_COMM.emergencyConsumerObject[0]},
{0x1029, 0x06, 0x0D,  1, (void*)&CO_OD_ROM.errorBehavior[0]},
{0x1200, 0x03, 0x00,  0, (void*)&OD_record1200},
{0x1280, 0x03, 0x00,  0, (void*)&OD_record1280},
{0x1400, 0x03, 0x00,  0, (void*)&OD_record1400},
{0x1401, 0x03, 0x00,  0, (void*)&OD_record1401},
{0x1402, 0x03, 0x00,  0, (void*)&OD_record1402},
{0x1403, 0x03, 0x00,  0, (void*)&OD_record1403},
{0x1404, 0x03, 0x00,  0, (void*)&OD_record1404},
{0x1405, 0x03, 0x00,  0, (void*)&OD_record1405},
{0x1406, 0x03, 0x00,  0, (void*)&OD_record1406},
{0x1407, 0x03, 0x00,  0, (void*)&OD_record1407},
{0x1408, 0x03, 0x00,  0, (void*)&OD_record1408},
{0x1409, 0x03, 0x00,  0, (void*)&OD_record1409},
{0x140A, 0x03, 0x00,  0, (void*)&OD_record140A},
{0x140B, 0x03, 0x00,  0, (void*)&OD_record140B},
{0x140C, 0x03, 0x00,  0, (void*)&OD_record140C},
{0x140D, 0x03, 0x00,  0, (void*)&OD_record140D},
{0x140E, 0x03, 0x00,  0, (void*)&OD_record140E},
{0x140F, 0x03, 0x00,  0, (void*)&OD_record140F},
{0x1410, 0x03, 0x00,  0, (void*)&OD_record1410},
{0x1411, 0x03, 0x00,  0, (void*)&OD_record1411},
{0x1412, 0x03, 0x00,  0, (void*)&OD_record1412},
{0x1413, 0x03, 0x00,  0, (void*)&OD_record1413},
{0x1414, 0x03, 0x00,  0, (void*)&OD_record1414},
{0x1415, 0x03, 0x00,  0, (void*)&OD_record1415},
{0x1416, 0x03, 0x00,  0, (void*)&OD_record1416},
{0x1417, 0x03, 0x00,  0, (void*)&OD_record1417},
{0x1418, 0x03, 0x00,  0, (void*)&OD_record1418},
{0x1419, 0x03, 0x00,  0, (void*)&OD_record1419},
{0x141A, 0x03, 0x00,  0, (void*)&OD_record141A},
{0x141B, 0x03, 0x00,  0, (void*)&OD_record141B},
{0x141C, 0x03, 0x00,  0, (void*)&OD_record141C},
{0x141D, 0x03, 0x00,  0, (void*)&OD_record141D},
{0x141E, 0x03, 0x00,  0, (void*)&OD_record141E},
{0x141F, 0x03, 0x00,  0, (void*)&OD_record141F},
{0x1420, 0x03, 0x00,  0, (void*)&OD_record1420},
{0x1421, 0x03, 0x00,  0, (void*)&OD_record1421},
{0x1422, 0x03, 0x00,  0, (void*)&OD_record1422},
{0x1423, 0x03, 0x00,  0, (void*)&OD_record1423},
{0x1424, 0x03, 0x00,  0, (void*)&OD_record1424},
{0x1425, 0x03, 0x00,  0, (void*)&OD_record1425},
{0x1426, 0x03, 0x00,  0, (void*)&OD_record1426},
{0x1427, 0x03, 0x00,  0, (void*)&OD_record1427},
{0x1428, 0x03, 0x00,  0, (void*)&OD_record1428},
{0x1429, 0x03, 0x00,  0, (void*)&OD_record1429},
{0x142A, 0x03, 0x00,  0, (void*)&OD_record142A},
{0x142B, 0x03, 0x00,  0, (void*)&OD_record142B},
{0x142C, 0x03, 0x00,  0, (void*)&OD_record142C},
{0x142D, 0x03, 0x00,  0, (void*)&OD_record142D},
{0x142E, 0x03, 0x00,  0, (void*)&OD_record142E},
{0x1600, 0x08, 0x00,  0, (void*)&OD_record1600},
{0x1601, 0x08, 0x00,  0, (void*)&OD_record1601},
{0x1602, 0x08, 0x00,  0, (void*)&OD_record1602},
{0x1603, 0x08, 0x00,  0, (void*)&OD_record1603},
{0x1604, 0x08, 0x00,  0, (void*)&OD_record1604},
{0x1605, 0x08, 0x00,  0, (void*)&OD_record1605},
{0x1606, 0x08, 0x00,  0, (void*)&OD_record1606},
{0x1607, 0x08, 0x00,  0, (void*)&OD_record1607},
{0x1608, 0x08, 0x00,  0, (void*)&OD_record1608},
{0x1609, 0x08, 0x00,  0, (void*)&OD_record1609},
{0x160A, 0x08, 0x00,  0, (void*)&OD_record160A},
{0x160B, 0x08, 0x00,  0, (void*)&OD_record160B},
{0x160C, 0x08, 0x00,  0, (void*)&OD_record160C},
{0x160D, 0x08, 0x00,  0, (void*)&OD_record160D},
{0x160E, 0x08, 0x00,  0, (void*)&OD_record160E},
{0x160F, 0x08, 0x00,  0, (void*)&OD_record160F},
{0x1610, 0x08, 0x00,  0, (void*)&OD_record1610},
{0x1611, 0x08, 0x00,  0, (void*)&OD_record1611},
{0x1612, 0x08, 0x00,  0, (void*)&OD_record1612},
{0x1613, 0x08, 0x00,  0, (void*)&OD_record1613},
{0x1614, 0x08, 0x00,  0, (void*)&OD_record1614},
{0x1615, 0x08, 0x00,  0, (void*)&OD_record1615},
{0x1616, 0x08, 0x00,  0, (void*)&OD_record1616},
{0x1617, 0x08, 0x00,  0, (void*)&OD_record1617},
{0x1618, 0x08, 0x00,  0, (void*)&OD_record1618},
{0x1619, 0x08, 0x00,  0, (void*)&OD_record1619},
{0x161A, 0x08, 0x00,  0, (void*)&OD_record161A},
{0x161B, 0x08, 0x00,  0, (void*)&OD_record161B},
{0x161C, 0x08, 0x00,  0, (void*)&OD_record161C},
{0x161D, 0x08, 0x00,  0, (void*)&OD_record161D},
{0x161E, 0x08, 0x00,  0, (void*)&OD_record161E},
{0x161F, 0x08, 0x00,  0, (void*)&OD_record161F},
{0x1620, 0x08, 0x00,  0, (void*)&OD_record1620},
{0x1621, 0x08, 0x00,  0, (void*)&OD_record1621},
{0x1622, 0x08, 0x00,  0, (void*)&OD_record1622},
{0x1623, 0x08, 0x00,  0, (void*)&OD_record1623},
{0x1624, 0x08, 0x00,  0, (void*)&OD_record1624},
{0x1625, 0x08, 0x00,  0, (void*)&OD_record1625},
{0x1626, 0x08, 0x00,  0, (void*)&OD_record1626},
{0x1627, 0x08, 0x00,  0, (void*)&OD_record1627},
{0x1628, 0x08, 0x00,  0, (void*)&OD_record1628},
{0x1629, 0x08, 0x00,  0, (void*)&OD_record1629},
{0x162A, 0x08, 0x00,  0, (void*)&OD_record162A},
{0x162B, 0x08, 0x00,  0, (void*)&OD_record162B},
{0x162C, 0x08, 0x00,  0, (void*)&OD_record162C},
{0x162D, 0x08, 0x00,  0, (void*)&OD_record162D},
{0x162E, 0x08, 0x00,  0, (void*)&OD_record162E},
{0x1800, 0x06, 0x00,  0, (void*)&OD_record1800},
{0x1801, 0x06, 0x00,  0, (void*)&OD_record1801},
{0x1802, 0x06, 0x00,  0, (void*)&OD_record1802},
{0x1803, 0x06, 0x00,  0, (void*)&OD_record1803},
{0x1804, 0x06, 0x00,  0, (void*)&OD_record1804},
{0x1805, 0x06, 0x00,  0, (void*)&OD_record1805},
{0x1806, 0x06, 0x00,  0, (void*)&OD_record1806},
{0x1807, 0x06, 0x00,  0, (void*)&OD_record1807},
{0x1808, 0x06, 0x00,  0, (void*)&OD_record1808},
{0x1809, 0x06, 0x00,  0, (void*)&OD_record1809},
{0x180A, 0x06, 0x00,  0, (void*)&OD_record180A},
{0x180B, 0x06, 0x00,  0, (void*)&OD_record180B},
{0x180C, 0x06, 0x00,  0, (void*)&OD_record180C},
{0x180D, 0x06, 0x00,  0, (void*)&OD_record180D},
{0x180E, 0x06, 0x00,  0, (void*)&OD_record180E},
{0x180F, 0x06, 0x00,  0, (void*)&OD_record180F},
{0x1A00, 0x08, 0x00,  0, (void*)&OD_record1A00},
{0x1A01, 0x08, 0x00,  0, (void*)&OD_record1A01},
{0x1A02, 0x08, 0x00,  0, (void*)&OD_record1A02},
{0x1A03, 0x08, 0x00,  0, (void*)&OD_record1A03},
{0x1A04, 0x08, 0x00,  0, (void*)&OD_record1A04},
{0x1A05, 0x08, 0x00,  0, (void*)&OD_record1A05},
{0x1A06, 0x08, 0x00,  0, (void*)&OD_record1A06},
{0x1A07, 0x08, 0x00,  0, (void*)&OD_record1A07},
{0x1A08, 0x08, 0x00,  0, (void*)&OD_record1A08},
{0x1A09, 0x08, 0x00,  0, (void*)&OD_record1A09},
{0x1A0A, 0x08, 0x00,  0, (void*)&OD_record1A0A},
{0x1A0B, 0x08, 0x00,  0, (void*)&OD_record1A0B},
{0x1A0C, 0x08, 0x00,  0, (void*)&OD_record1A0C},
{0x1A0D, 0x08, 0x00,  0, (void*)&OD_record1A0D},
{0x1A0E, 0x08, 0x00,  0, (void*)&OD_record1A0E},
{0x1A0F, 0x08, 0x00,  0, (void*)&OD_record1A0F},
{0x1F80, 0x00, 0x8F,  4, (void*)&CO_OD_PERSIST_COMM.NMTStartup},
{0x1F81, 0x7F, 0x8F,  4, (void*)&CO_OD_PERSIST_COMM.slaveAssignment[0]},
{0x1F82, 0x7F, 0x0F,  1, (void*)&CO_OD_PERSIST_COMM.requestNMT[0]},
{0x1F89, 0x00, 0x8E,  4, (void*)&CO_OD_RAM.bootTime},
{0x2000, 0x04, 0x00,  0, (void*)&OD_record2000},
{0x2010, 0x00, 0xBE,  8, (void*)&CO_OD_RAM.SCET},
{0x2011, 0x00, 0xBE,  8, (void*)&CO_OD_RAM.UTC},
{0x2020, 0x03, 0x86,  4, (void*)&CO_OD_RAM.MCU_UniqueDeviceID[0]},
{0x2021, 0x03, 0x00,  0, (void*)&OD_record2021},
{0x2022, 0x08, 0x00,  0, (void*)&OD_record2022},
{0x2100, 0x00, 0x06, 10, (void*)&CO_OD_RAM.errorStatusBits},
{0x6000, 0x00, 0x06,  1, (void*)&CO_OD_RAM.C3State},
{0x6001, 0x03, 0x00,  0, (void*)&OD_record6001},
{0x6002, 0x03, 0x00,  0, (void*)&OD_record6002},
{0x6003, 0x02, 0x00,  0, (void*)&OD_record6003},
{0x6004, 0x0E, 0x00,  0, (void*)&OD_record6004},
{0x7000, 0x05, 0x00,  0, (void*)&OD_record7000},
{0x7001, 0x2C, 0x00,  0, (void*)&OD_record7001},
{0x7002, 0x2C, 0x00,  0, (void*)&OD_record7002},
{0x7003, 0x10, 0x00,  0, (void*)&OD_record7003},
{0x7004, 0x10, 0x00,  0, (void*)&OD_record7004},
{0x7005, 0x10, 0x00,  0, (void*)&OD_record7005},
{0x7006, 0x10, 0x00,  0, (void*)&OD_record7006},
{0x7007, 0x10, 0x00,  0, (void*)&OD_record7007},
{0x7008, 0x10, 0x00,  0, (void*)&OD_record7008},
{0x7009, 0x10, 0x00,  0, (void*)&OD_record7009},
{0x700A, 0x10, 0x00,  0, (void*)&OD_record700A},
{0x700B, 0x0C, 0x00,  0, (void*)&OD_record700B},
{0x700C, 0x0C, 0x00,  0, (void*)&OD_record700C},
{0x700D, 0x11, 0x00,  0, (void*)&OD_record700D},
{0x700E, 0x13, 0x00,  0, (void*)&OD_record700E},
{0x700F, 0x01, 0x00,  0, (void*)&OD_record700F},
{0x7013, 0x09, 0x00,  0, (void*)&OD_record7013},
{0x7014, 0x08, 0x00,  0, (void*)&OD_record7014},
};
// clang-format on
