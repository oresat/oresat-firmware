// clang-format off
/*******************************************************************************

   File - CO_OD.c/CO_OD.h
   CANopen Object Dictionary.

   This file was automatically generated with libedssharp Object
   Dictionary Editor v0.8-14-gf64b37c   DON'T EDIT THIS FILE MANUALLY !!!!
*******************************************************************************/


#include "CO_driver.h"
#include "CO_OD.h"
#include "CO_SDO.h"

/*******************************************************************************
   DEFINITION AND INITIALIZATION OF OBJECT DICTIONARY VARIABLES
*******************************************************************************/


/***** Definition for ROM variables *******************************************/
struct sCO_OD_ROM CO_OD_ROM = {
           CO_OD_FIRST_LAST_WORD,

/*1000*/ 0x0000L,
/*1005*/ 0x0080L,
/*1006*/ 0x0000L,
/*1007*/ 0x0000L,
/*1008*/ {'O', 'r', 'e', 'S', 'a', 't', ' ', 'C', '3', ' ', 'M', 'a', 's', 't', 'e', 'r', ' ', 'N', 'o', 'd', 'e'},
/*1009*/ {'1', '.', '0'},
/*100A*/ {'0', '.', '1', '.', '0'},
/*1014*/ 0x0080L,
/*1015*/ 0x64,
/*1016*/ {0x00000000, 0x00000000, 0x00000000, 0x00000000},
/*1017*/ 0x3E8,
/*1018*/ {0x4L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1019*/ 0x0L,
/*1029*/ {0x00, 0x00, 0x01, 0x00, 0x00, 0x00},
/*1200*/ {{0x2L, 0x0600L, 0x0580L}},
/*1400*/ {{0x2L, 0x0182L, 0xFEL},
/*1401*/ {0x2L, 0x0183L, 0xFEL},
/*1402*/ {0x2L, 0x0184L, 0xFEL},
/*1403*/ {0x2L, 0x0185L, 0xFEL},
/*1404*/ {0x2L, 0x0186L, 0xFEL},
/*1405*/ {0x2L, 0x0187L, 0xFEL},
/*1406*/ {0x2L, 0x0188L, 0xFEL},
/*1407*/ {0x2L, 0x0189L, 0xFEL},
/*1408*/ {0x2L, 0x018AL, 0xFEL},
/*1409*/ {0x2L, 0x018BL, 0xFEL},
/*140A*/ {0x2L, 0x0193L, 0xFEL},
/*140B*/ {0x2L, 0x0194L, 0xFEL},
/*140C*/ {0x2L, 0x0195L, 0xFEL},
/*140D*/ {0x2L, 0x0196L, 0xFEL},
/*140E*/ {0x2L, 0x0197L, 0xFEL},
/*140F*/ {0x2L, 0x0198L, 0xFEL},
/*1410*/ {0x2L, 0x0199L, 0xFEL},
/*1411*/ {0x2L, 0x01A1L, 0xFEL},
/*1412*/ {0x2L, 0x01A2L, 0xFEL},
/*1413*/ {0x2L, 0x01A3L, 0xFEL}},
/*1600*/ {{0x2L, 0x40020110L, 0x40020210L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1601*/ {0x2L, 0x40030110L, 0x40030210L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1602*/ {0x2L, 0x40040110L, 0x40040210L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1603*/ {0x2L, 0x40050110L, 0x40050210L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1604*/ {0x2L, 0x40060110L, 0x40060210L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1605*/ {0x2L, 0x40070110L, 0x40070210L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1606*/ {0x2L, 0x40080110L, 0x40080210L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1607*/ {0x2L, 0x40090110L, 0x40090210L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1608*/ {0x2L, 0x400A0110L, 0x400A0210L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1609*/ {0x2L, 0x400B0110L, 0x400B0210L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*160A*/ {0x2L, 0x40130110L, 0x40130210L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*160B*/ {0x2L, 0x40140110L, 0x40140210L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*160C*/ {0x2L, 0x40150110L, 0x40150210L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*160D*/ {0x2L, 0x40160110L, 0x40160210L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*160E*/ {0x2L, 0x40170110L, 0x40170210L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*160F*/ {0x2L, 0x40180110L, 0x40180210L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1610*/ {0x2L, 0x40190110L, 0x40190210L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1611*/ {0x2L, 0x40310110L, 0x40310210L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1612*/ {0x2L, 0x40320110L, 0x40320210L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1613*/ {0x2L, 0x40330110L, 0x40330210L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L}},
/*1800*/ {{0x6L, 0x0180L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*1801*/ {0x6L, 0x0280L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*1802*/ {0x6L, 0x0380L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*1803*/ {0x6L, 0x0480L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*1804*/ {0x6L, 0x80000000L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*1805*/ {0x6L, 0x80000000L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*1806*/ {0x6L, 0x80000000L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*1807*/ {0x6L, 0x80000000L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*1808*/ {0x6L, 0x80000000L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*1809*/ {0x6L, 0x80000000L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*180A*/ {0x6L, 0x80000000L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*180B*/ {0x6L, 0x80000000L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*180C*/ {0x6L, 0x80000000L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*180D*/ {0x6L, 0x80000000L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*180E*/ {0x6L, 0x80000000L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*180F*/ {0x6L, 0x80000000L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L}},
/*1A00*/ {{0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
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
/*1F80*/ 0x0001L,
/*2101*/ 0x1L,
/*2102*/ 0x3E8,
/*2106*/ {0x00, 0x00, 0x00},

           CO_OD_FIRST_LAST_WORD,
};


/***** Definition for RAM variables *******************************************/
struct sCO_OD_RAM CO_OD_RAM = {
           CO_OD_FIRST_LAST_WORD,

/*1001*/ 0x0L,
/*1002*/ 0x0000L,
/*1003*/ {0, 0, 0, 0, 0, 0, 0, 0},
/*1010*/ {0x00000003},
/*1011*/ {0x00000001},
/*1280*/ {{0x3L, 0x0000L, 0x0000L, 0x0L}},
/*1F81*/ {0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1F82*/ {0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L},
/*1F89*/ 0x0000L,
/*2010*/ 0x00000000L,
/*2011*/ 0x00000000L,
/*2100*/ {0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L},
/*2103*/ 0x00,
/*2104*/ 0x00,
/*2107*/ {0x00, 0x00, 0x00},
/*2108*/ {0x00},
/*2109*/ {0x00},
/*4002*/ {0x2L, 0x00, 0x00},
/*4003*/ {0x2L, 0x00, 0x00},
/*4004*/ {0x2L, 0x00, 0x00},
/*4005*/ {0x2L, 0x00, 0x00},
/*4006*/ {0x2L, 0x00, 0x00},
/*4007*/ {0x2L, 0x00, 0x00},
/*4008*/ {0x2L, 0x00, 0x00},
/*4009*/ {0x2L, 0x00, 0x00},
/*400A*/ {0x2L, 0x00, 0x00},
/*400B*/ {0x2L, 0x00, 0x00},
/*4011*/ {0x0L},
/*4012*/ {0x0L},
/*4013*/ {0x2L, 0x00, 0x00},
/*4014*/ {0x2L, 0x00, 0x00},
/*4015*/ {0x2L, 0x00, 0x00},
/*4016*/ {0x2L, 0x00, 0x00},
/*4017*/ {0x2L, 0x00, 0x00},
/*4018*/ {0x2L, 0x00, 0x00},
/*4019*/ {0x2L, 0x00, 0x00},
/*4021*/ {0x0L},
/*4022*/ {0x0L},
/*4031*/ {0x2L, 0x00, 0x00},
/*4032*/ {0x2L, 0x00, 0x00},
/*4033*/ {0x2L, 0x00, 0x00},

           CO_OD_FIRST_LAST_WORD,
};


/***** Definition for EEPROM variables *******************************************/
struct sCO_OD_EEPROM CO_OD_EEPROM = {
           CO_OD_FIRST_LAST_WORD,


           CO_OD_FIRST_LAST_WORD,
};




/*******************************************************************************
   STRUCTURES FOR RECORD TYPE OBJECTS
*******************************************************************************/


/*0x1018*/ const CO_OD_entryRecord_t OD_record1018[5] = {
           {(void*)&CO_OD_ROM.identity.maxSubIndex, 0x05, 0x1 },
           {(void*)&CO_OD_ROM.identity.vendorID, 0x85, 0x4 },
           {(void*)&CO_OD_ROM.identity.productCode, 0x85, 0x4 },
           {(void*)&CO_OD_ROM.identity.revisionNumber, 0x85, 0x4 },
           {(void*)&CO_OD_ROM.identity.serialNumber, 0x85, 0x4 },
};

/*0x1200*/ const CO_OD_entryRecord_t OD_record1200[3] = {
           {(void*)&CO_OD_ROM.SDOServerParameter[0].maxSubIndex, 0x05, 0x1 },
           {(void*)&CO_OD_ROM.SDOServerParameter[0].COB_IDClientToServer, 0x85, 0x4 },
           {(void*)&CO_OD_ROM.SDOServerParameter[0].COB_IDServerToClient, 0x85, 0x4 },
};

/*0x1280*/ const CO_OD_entryRecord_t OD_record1280[4] = {
           {(void*)&CO_OD_RAM.SDOClientParameter[0].maxSubIndex, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.SDOClientParameter[0].COB_IDClientToServer, 0xBE, 0x4 },
           {(void*)&CO_OD_RAM.SDOClientParameter[0].COB_IDServerToClient, 0xBE, 0x4 },
           {(void*)&CO_OD_RAM.SDOClientParameter[0].nodeIDOfTheSDOServer, 0x0E, 0x1 },
};

/*0x1400*/ const CO_OD_entryRecord_t OD_record1400[3] = {
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[0].maxSubIndex, 0x05, 0x1 },
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[0].COB_IDUsedByRPDO, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[0].transmissionType, 0x0D, 0x1 },
};

/*0x1401*/ const CO_OD_entryRecord_t OD_record1401[3] = {
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[1].maxSubIndex, 0x05, 0x1 },
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[1].COB_IDUsedByRPDO, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[1].transmissionType, 0x0D, 0x1 },
};

/*0x1402*/ const CO_OD_entryRecord_t OD_record1402[3] = {
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[2].maxSubIndex, 0x05, 0x1 },
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[2].COB_IDUsedByRPDO, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[2].transmissionType, 0x0D, 0x1 },
};

/*0x1403*/ const CO_OD_entryRecord_t OD_record1403[3] = {
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[3].maxSubIndex, 0x05, 0x1 },
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[3].COB_IDUsedByRPDO, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[3].transmissionType, 0x0D, 0x1 },
};

/*0x1404*/ const CO_OD_entryRecord_t OD_record1404[3] = {
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[4].maxSubIndex, 0x05, 0x1 },
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[4].COB_IDUsedByRPDO, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[4].transmissionType, 0x0D, 0x1 },
};

/*0x1405*/ const CO_OD_entryRecord_t OD_record1405[3] = {
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[5].maxSubIndex, 0x05, 0x1 },
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[5].COB_IDUsedByRPDO, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[5].transmissionType, 0x0D, 0x1 },
};

/*0x1406*/ const CO_OD_entryRecord_t OD_record1406[3] = {
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[6].maxSubIndex, 0x05, 0x1 },
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[6].COB_IDUsedByRPDO, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[6].transmissionType, 0x0D, 0x1 },
};

/*0x1407*/ const CO_OD_entryRecord_t OD_record1407[3] = {
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[7].maxSubIndex, 0x05, 0x1 },
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[7].COB_IDUsedByRPDO, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[7].transmissionType, 0x0D, 0x1 },
};

/*0x1408*/ const CO_OD_entryRecord_t OD_record1408[3] = {
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[8].maxSubIndex, 0x05, 0x1 },
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[8].COB_IDUsedByRPDO, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[8].transmissionType, 0x0D, 0x1 },
};

/*0x1409*/ const CO_OD_entryRecord_t OD_record1409[3] = {
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[9].maxSubIndex, 0x05, 0x1 },
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[9].COB_IDUsedByRPDO, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[9].transmissionType, 0x0D, 0x1 },
};

/*0x140A*/ const CO_OD_entryRecord_t OD_record140A[3] = {
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[10].maxSubIndex, 0x05, 0x1 },
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[10].COB_IDUsedByRPDO, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[10].transmissionType, 0x0D, 0x1 },
};

/*0x140B*/ const CO_OD_entryRecord_t OD_record140B[3] = {
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[11].maxSubIndex, 0x05, 0x1 },
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[11].COB_IDUsedByRPDO, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[11].transmissionType, 0x0D, 0x1 },
};

/*0x140C*/ const CO_OD_entryRecord_t OD_record140C[3] = {
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[12].maxSubIndex, 0x05, 0x1 },
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[12].COB_IDUsedByRPDO, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[12].transmissionType, 0x0D, 0x1 },
};

/*0x140D*/ const CO_OD_entryRecord_t OD_record140D[3] = {
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[13].maxSubIndex, 0x05, 0x1 },
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[13].COB_IDUsedByRPDO, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[13].transmissionType, 0x0D, 0x1 },
};

/*0x140E*/ const CO_OD_entryRecord_t OD_record140E[3] = {
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[14].maxSubIndex, 0x05, 0x1 },
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[14].COB_IDUsedByRPDO, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[14].transmissionType, 0x0D, 0x1 },
};

/*0x140F*/ const CO_OD_entryRecord_t OD_record140F[3] = {
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[15].maxSubIndex, 0x05, 0x1 },
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[15].COB_IDUsedByRPDO, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[15].transmissionType, 0x0D, 0x1 },
};

/*0x1410*/ const CO_OD_entryRecord_t OD_record1410[3] = {
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[16].maxSubIndex, 0x05, 0x1 },
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[16].COB_IDUsedByRPDO, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[16].transmissionType, 0x0D, 0x1 },
};

/*0x1411*/ const CO_OD_entryRecord_t OD_record1411[3] = {
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[17].maxSubIndex, 0x05, 0x1 },
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[17].COB_IDUsedByRPDO, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[17].transmissionType, 0x0D, 0x1 },
};

/*0x1412*/ const CO_OD_entryRecord_t OD_record1412[3] = {
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[18].maxSubIndex, 0x05, 0x1 },
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[18].COB_IDUsedByRPDO, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[18].transmissionType, 0x0D, 0x1 },
};

/*0x1413*/ const CO_OD_entryRecord_t OD_record1413[3] = {
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[19].maxSubIndex, 0x05, 0x1 },
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[19].COB_IDUsedByRPDO, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOCommunicationParameter[19].transmissionType, 0x0D, 0x1 },
};

/*0x1600*/ const CO_OD_entryRecord_t OD_record1600[9] = {
           {(void*)&CO_OD_ROM.RPDOMappingParameter[0].numberOfMappedObjects, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[0].mappedObject1, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[0].mappedObject2, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[0].mappedObject3, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[0].mappedObject4, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[0].mappedObject5, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[0].mappedObject6, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[0].mappedObject7, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[0].mappedObject8, 0x8D, 0x4 },
};

/*0x1601*/ const CO_OD_entryRecord_t OD_record1601[9] = {
           {(void*)&CO_OD_ROM.RPDOMappingParameter[1].numberOfMappedObjects, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[1].mappedObject1, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[1].mappedObject2, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[1].mappedObject3, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[1].mappedObject4, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[1].mappedObject5, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[1].mappedObject6, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[1].mappedObject7, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[1].mappedObject8, 0x8D, 0x4 },
};

/*0x1602*/ const CO_OD_entryRecord_t OD_record1602[9] = {
           {(void*)&CO_OD_ROM.RPDOMappingParameter[2].numberOfMappedObjects, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[2].mappedObject1, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[2].mappedObject2, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[2].mappedObject3, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[2].mappedObject4, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[2].mappedObject5, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[2].mappedObject6, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[2].mappedObject7, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[2].mappedObject8, 0x8D, 0x4 },
};

/*0x1603*/ const CO_OD_entryRecord_t OD_record1603[9] = {
           {(void*)&CO_OD_ROM.RPDOMappingParameter[3].numberOfMappedObjects, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[3].mappedObject1, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[3].mappedObject2, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[3].mappedObject3, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[3].mappedObject4, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[3].mappedObject5, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[3].mappedObject6, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[3].mappedObject7, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[3].mappedObject8, 0x8D, 0x4 },
};

/*0x1604*/ const CO_OD_entryRecord_t OD_record1604[9] = {
           {(void*)&CO_OD_ROM.RPDOMappingParameter[4].numberOfMappedObjects, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[4].mappedObject1, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[4].mappedObject2, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[4].mappedObject3, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[4].mappedObject4, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[4].mappedObject5, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[4].mappedObject6, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[4].mappedObject7, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[4].mappedObject8, 0x8D, 0x4 },
};

/*0x1605*/ const CO_OD_entryRecord_t OD_record1605[9] = {
           {(void*)&CO_OD_ROM.RPDOMappingParameter[5].numberOfMappedObjects, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[5].mappedObject1, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[5].mappedObject2, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[5].mappedObject3, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[5].mappedObject4, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[5].mappedObject5, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[5].mappedObject6, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[5].mappedObject7, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[5].mappedObject8, 0x8D, 0x4 },
};

/*0x1606*/ const CO_OD_entryRecord_t OD_record1606[9] = {
           {(void*)&CO_OD_ROM.RPDOMappingParameter[6].numberOfMappedObjects, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[6].mappedObject1, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[6].mappedObject2, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[6].mappedObject3, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[6].mappedObject4, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[6].mappedObject5, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[6].mappedObject6, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[6].mappedObject7, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[6].mappedObject8, 0x8D, 0x4 },
};

/*0x1607*/ const CO_OD_entryRecord_t OD_record1607[9] = {
           {(void*)&CO_OD_ROM.RPDOMappingParameter[7].numberOfMappedObjects, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[7].mappedObject1, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[7].mappedObject2, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[7].mappedObject3, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[7].mappedObject4, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[7].mappedObject5, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[7].mappedObject6, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[7].mappedObject7, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[7].mappedObject8, 0x8D, 0x4 },
};

/*0x1608*/ const CO_OD_entryRecord_t OD_record1608[9] = {
           {(void*)&CO_OD_ROM.RPDOMappingParameter[8].numberOfMappedObjects, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[8].mappedObject1, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[8].mappedObject2, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[8].mappedObject3, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[8].mappedObject4, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[8].mappedObject5, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[8].mappedObject6, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[8].mappedObject7, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[8].mappedObject8, 0x8D, 0x4 },
};

/*0x1609*/ const CO_OD_entryRecord_t OD_record1609[9] = {
           {(void*)&CO_OD_ROM.RPDOMappingParameter[9].numberOfMappedObjects, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[9].mappedObject1, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[9].mappedObject2, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[9].mappedObject3, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[9].mappedObject4, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[9].mappedObject5, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[9].mappedObject6, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[9].mappedObject7, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[9].mappedObject8, 0x8D, 0x4 },
};

/*0x160A*/ const CO_OD_entryRecord_t OD_record160A[9] = {
           {(void*)&CO_OD_ROM.RPDOMappingParameter[10].numberOfMappedObjects, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[10].mappedObject1, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[10].mappedObject2, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[10].mappedObject3, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[10].mappedObject4, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[10].mappedObject5, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[10].mappedObject6, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[10].mappedObject7, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[10].mappedObject8, 0x8D, 0x4 },
};

/*0x160B*/ const CO_OD_entryRecord_t OD_record160B[9] = {
           {(void*)&CO_OD_ROM.RPDOMappingParameter[11].numberOfMappedObjects, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[11].mappedObject1, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[11].mappedObject2, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[11].mappedObject3, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[11].mappedObject4, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[11].mappedObject5, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[11].mappedObject6, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[11].mappedObject7, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[11].mappedObject8, 0x8D, 0x4 },
};

/*0x160C*/ const CO_OD_entryRecord_t OD_record160C[9] = {
           {(void*)&CO_OD_ROM.RPDOMappingParameter[12].numberOfMappedObjects, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[12].mappedObject1, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[12].mappedObject2, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[12].mappedObject3, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[12].mappedObject4, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[12].mappedObject5, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[12].mappedObject6, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[12].mappedObject7, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[12].mappedObject8, 0x8D, 0x4 },
};

/*0x160D*/ const CO_OD_entryRecord_t OD_record160D[9] = {
           {(void*)&CO_OD_ROM.RPDOMappingParameter[13].numberOfMappedObjects, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[13].mappedObject1, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[13].mappedObject2, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[13].mappedObject3, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[13].mappedObject4, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[13].mappedObject5, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[13].mappedObject6, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[13].mappedObject7, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[13].mappedObject8, 0x8D, 0x4 },
};

/*0x160E*/ const CO_OD_entryRecord_t OD_record160E[9] = {
           {(void*)&CO_OD_ROM.RPDOMappingParameter[14].numberOfMappedObjects, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[14].mappedObject1, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[14].mappedObject2, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[14].mappedObject3, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[14].mappedObject4, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[14].mappedObject5, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[14].mappedObject6, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[14].mappedObject7, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[14].mappedObject8, 0x8D, 0x4 },
};

/*0x160F*/ const CO_OD_entryRecord_t OD_record160F[9] = {
           {(void*)&CO_OD_ROM.RPDOMappingParameter[15].numberOfMappedObjects, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[15].mappedObject1, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[15].mappedObject2, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[15].mappedObject3, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[15].mappedObject4, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[15].mappedObject5, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[15].mappedObject6, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[15].mappedObject7, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[15].mappedObject8, 0x8D, 0x4 },
};

/*0x1610*/ const CO_OD_entryRecord_t OD_record1610[9] = {
           {(void*)&CO_OD_ROM.RPDOMappingParameter[16].numberOfMappedObjects, 0x05, 0x1 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[16].mappedObject1, 0x85, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[16].mappedObject2, 0x85, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[16].mappedObject3, 0x85, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[16].mappedObject4, 0x85, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[16].mappedObject5, 0x85, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[16].mappedObject6, 0x85, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[16].mappedObject7, 0x85, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[16].mappedObject8, 0x85, 0x4 },
};

/*0x1611*/ const CO_OD_entryRecord_t OD_record1611[9] = {
           {(void*)&CO_OD_ROM.RPDOMappingParameter[17].numberOfMappedObjects, 0x05, 0x1 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[17].mappedObject1, 0x85, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[17].mappedObject2, 0x85, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[17].mappedObject3, 0x85, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[17].mappedObject4, 0x85, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[17].mappedObject5, 0x85, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[17].mappedObject6, 0x85, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[17].mappedObject7, 0x85, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[17].mappedObject8, 0x85, 0x4 },
};

/*0x1612*/ const CO_OD_entryRecord_t OD_record1612[9] = {
           {(void*)&CO_OD_ROM.RPDOMappingParameter[18].numberOfMappedObjects, 0x05, 0x1 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[18].mappedObject1, 0x85, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[18].mappedObject2, 0x85, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[18].mappedObject3, 0x85, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[18].mappedObject4, 0x85, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[18].mappedObject5, 0x85, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[18].mappedObject6, 0x85, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[18].mappedObject7, 0x85, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[18].mappedObject8, 0x85, 0x4 },
};

/*0x1613*/ const CO_OD_entryRecord_t OD_record1613[9] = {
           {(void*)&CO_OD_ROM.RPDOMappingParameter[19].numberOfMappedObjects, 0x05, 0x1 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[19].mappedObject1, 0x85, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[19].mappedObject2, 0x85, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[19].mappedObject3, 0x85, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[19].mappedObject4, 0x85, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[19].mappedObject5, 0x85, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[19].mappedObject6, 0x85, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[19].mappedObject7, 0x85, 0x4 },
           {(void*)&CO_OD_ROM.RPDOMappingParameter[19].mappedObject8, 0x85, 0x4 },
};

/*0x1800*/ const CO_OD_entryRecord_t OD_record1800[7] = {
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[0].maxSubIndex, 0x05, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[0].COB_IDUsedByTPDO, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[0].transmissionType, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[0].inhibitTime, 0x8D, 0x2 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[0].compatibilityEntry, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[0].eventTimer, 0x8D, 0x2 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[0].SYNCStartValue, 0x0D, 0x1 },
};

/*0x1801*/ const CO_OD_entryRecord_t OD_record1801[7] = {
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[1].maxSubIndex, 0x05, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[1].COB_IDUsedByTPDO, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[1].transmissionType, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[1].inhibitTime, 0x8D, 0x2 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[1].compatibilityEntry, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[1].eventTimer, 0x8D, 0x2 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[1].SYNCStartValue, 0x0D, 0x1 },
};

/*0x1802*/ const CO_OD_entryRecord_t OD_record1802[7] = {
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[2].maxSubIndex, 0x05, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[2].COB_IDUsedByTPDO, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[2].transmissionType, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[2].inhibitTime, 0x8D, 0x2 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[2].compatibilityEntry, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[2].eventTimer, 0x8D, 0x2 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[2].SYNCStartValue, 0x0D, 0x1 },
};

/*0x1803*/ const CO_OD_entryRecord_t OD_record1803[7] = {
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[3].maxSubIndex, 0x05, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[3].COB_IDUsedByTPDO, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[3].transmissionType, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[3].inhibitTime, 0x8D, 0x2 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[3].compatibilityEntry, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[3].eventTimer, 0x8D, 0x2 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[3].SYNCStartValue, 0x0D, 0x1 },
};

/*0x1804*/ const CO_OD_entryRecord_t OD_record1804[7] = {
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[4].maxSubIndex, 0x05, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[4].COB_IDUsedByTPDO, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[4].transmissionType, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[4].inhibitTime, 0x8D, 0x2 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[4].compatibilityEntry, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[4].eventTimer, 0x8D, 0x2 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[4].SYNCStartValue, 0x0D, 0x1 },
};

/*0x1805*/ const CO_OD_entryRecord_t OD_record1805[7] = {
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[5].maxSubIndex, 0x05, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[5].COB_IDUsedByTPDO, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[5].transmissionType, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[5].inhibitTime, 0x8D, 0x2 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[5].compatibilityEntry, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[5].eventTimer, 0x8D, 0x2 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[5].SYNCStartValue, 0x0D, 0x1 },
};

/*0x1806*/ const CO_OD_entryRecord_t OD_record1806[7] = {
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[6].maxSubIndex, 0x05, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[6].COB_IDUsedByTPDO, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[6].transmissionType, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[6].inhibitTime, 0x8D, 0x2 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[6].compatibilityEntry, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[6].eventTimer, 0x8D, 0x2 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[6].SYNCStartValue, 0x0D, 0x1 },
};

/*0x1807*/ const CO_OD_entryRecord_t OD_record1807[7] = {
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[7].maxSubIndex, 0x05, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[7].COB_IDUsedByTPDO, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[7].transmissionType, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[7].inhibitTime, 0x8D, 0x2 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[7].compatibilityEntry, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[7].eventTimer, 0x8D, 0x2 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[7].SYNCStartValue, 0x0D, 0x1 },
};

/*0x1808*/ const CO_OD_entryRecord_t OD_record1808[7] = {
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[8].maxSubIndex, 0x05, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[8].COB_IDUsedByTPDO, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[8].transmissionType, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[8].inhibitTime, 0x8D, 0x2 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[8].compatibilityEntry, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[8].eventTimer, 0x8D, 0x2 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[8].SYNCStartValue, 0x0D, 0x1 },
};

/*0x1809*/ const CO_OD_entryRecord_t OD_record1809[7] = {
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[9].maxSubIndex, 0x05, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[9].COB_IDUsedByTPDO, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[9].transmissionType, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[9].inhibitTime, 0x8D, 0x2 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[9].compatibilityEntry, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[9].eventTimer, 0x8D, 0x2 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[9].SYNCStartValue, 0x0D, 0x1 },
};

/*0x180A*/ const CO_OD_entryRecord_t OD_record180A[7] = {
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[10].maxSubIndex, 0x05, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[10].COB_IDUsedByTPDO, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[10].transmissionType, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[10].inhibitTime, 0x8D, 0x2 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[10].compatibilityEntry, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[10].eventTimer, 0x8D, 0x2 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[10].SYNCStartValue, 0x0D, 0x1 },
};

/*0x180B*/ const CO_OD_entryRecord_t OD_record180B[7] = {
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[11].maxSubIndex, 0x05, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[11].COB_IDUsedByTPDO, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[11].transmissionType, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[11].inhibitTime, 0x8D, 0x2 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[11].compatibilityEntry, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[11].eventTimer, 0x8D, 0x2 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[11].SYNCStartValue, 0x0D, 0x1 },
};

/*0x180C*/ const CO_OD_entryRecord_t OD_record180C[7] = {
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[12].maxSubIndex, 0x05, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[12].COB_IDUsedByTPDO, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[12].transmissionType, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[12].inhibitTime, 0x8D, 0x2 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[12].compatibilityEntry, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[12].eventTimer, 0x8D, 0x2 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[12].SYNCStartValue, 0x0D, 0x1 },
};

/*0x180D*/ const CO_OD_entryRecord_t OD_record180D[7] = {
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[13].maxSubIndex, 0x05, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[13].COB_IDUsedByTPDO, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[13].transmissionType, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[13].inhibitTime, 0x8D, 0x2 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[13].compatibilityEntry, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[13].eventTimer, 0x8D, 0x2 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[13].SYNCStartValue, 0x0D, 0x1 },
};

/*0x180E*/ const CO_OD_entryRecord_t OD_record180E[7] = {
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[14].maxSubIndex, 0x05, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[14].COB_IDUsedByTPDO, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[14].transmissionType, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[14].inhibitTime, 0x8D, 0x2 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[14].compatibilityEntry, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[14].eventTimer, 0x8D, 0x2 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[14].SYNCStartValue, 0x0D, 0x1 },
};

/*0x180F*/ const CO_OD_entryRecord_t OD_record180F[7] = {
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[15].maxSubIndex, 0x05, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[15].COB_IDUsedByTPDO, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[15].transmissionType, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[15].inhibitTime, 0x8D, 0x2 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[15].compatibilityEntry, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[15].eventTimer, 0x8D, 0x2 },
           {(void*)&CO_OD_ROM.TPDOCommunicationParameter[15].SYNCStartValue, 0x0D, 0x1 },
};

/*0x1A00*/ const CO_OD_entryRecord_t OD_record1A00[9] = {
           {(void*)&CO_OD_ROM.TPDOMappingParameter[0].numberOfMappedObjects, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[0].mappedObject1, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[0].mappedObject2, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[0].mappedObject3, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[0].mappedObject4, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[0].mappedObject5, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[0].mappedObject6, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[0].mappedObject7, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[0].mappedObject8, 0x8D, 0x4 },
};

/*0x1A01*/ const CO_OD_entryRecord_t OD_record1A01[9] = {
           {(void*)&CO_OD_ROM.TPDOMappingParameter[1].numberOfMappedObjects, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[1].mappedObject1, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[1].mappedObject2, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[1].mappedObject3, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[1].mappedObject4, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[1].mappedObject5, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[1].mappedObject6, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[1].mappedObject7, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[1].mappedObject8, 0x8D, 0x4 },
};

/*0x1A02*/ const CO_OD_entryRecord_t OD_record1A02[9] = {
           {(void*)&CO_OD_ROM.TPDOMappingParameter[2].numberOfMappedObjects, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[2].mappedObject1, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[2].mappedObject2, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[2].mappedObject3, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[2].mappedObject4, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[2].mappedObject5, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[2].mappedObject6, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[2].mappedObject7, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[2].mappedObject8, 0x8D, 0x4 },
};

/*0x1A03*/ const CO_OD_entryRecord_t OD_record1A03[9] = {
           {(void*)&CO_OD_ROM.TPDOMappingParameter[3].numberOfMappedObjects, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[3].mappedObject1, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[3].mappedObject2, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[3].mappedObject3, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[3].mappedObject4, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[3].mappedObject5, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[3].mappedObject6, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[3].mappedObject7, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[3].mappedObject8, 0x8D, 0x4 },
};

/*0x1A04*/ const CO_OD_entryRecord_t OD_record1A04[9] = {
           {(void*)&CO_OD_ROM.TPDOMappingParameter[4].numberOfMappedObjects, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[4].mappedObject1, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[4].mappedObject2, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[4].mappedObject3, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[4].mappedObject4, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[4].mappedObject5, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[4].mappedObject6, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[4].mappedObject7, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[4].mappedObject8, 0x8D, 0x4 },
};

/*0x1A05*/ const CO_OD_entryRecord_t OD_record1A05[9] = {
           {(void*)&CO_OD_ROM.TPDOMappingParameter[5].numberOfMappedObjects, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[5].mappedObject1, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[5].mappedObject2, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[5].mappedObject3, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[5].mappedObject4, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[5].mappedObject5, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[5].mappedObject6, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[5].mappedObject7, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[5].mappedObject8, 0x8D, 0x4 },
};

/*0x1A06*/ const CO_OD_entryRecord_t OD_record1A06[9] = {
           {(void*)&CO_OD_ROM.TPDOMappingParameter[6].numberOfMappedObjects, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[6].mappedObject1, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[6].mappedObject2, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[6].mappedObject3, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[6].mappedObject4, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[6].mappedObject5, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[6].mappedObject6, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[6].mappedObject7, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[6].mappedObject8, 0x8D, 0x4 },
};

/*0x1A07*/ const CO_OD_entryRecord_t OD_record1A07[9] = {
           {(void*)&CO_OD_ROM.TPDOMappingParameter[7].numberOfMappedObjects, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[7].mappedObject1, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[7].mappedObject2, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[7].mappedObject3, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[7].mappedObject4, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[7].mappedObject5, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[7].mappedObject6, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[7].mappedObject7, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[7].mappedObject8, 0x8D, 0x4 },
};

/*0x1A08*/ const CO_OD_entryRecord_t OD_record1A08[9] = {
           {(void*)&CO_OD_ROM.TPDOMappingParameter[8].numberOfMappedObjects, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[8].mappedObject1, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[8].mappedObject2, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[8].mappedObject3, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[8].mappedObject4, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[8].mappedObject5, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[8].mappedObject6, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[8].mappedObject7, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[8].mappedObject8, 0x8D, 0x4 },
};

/*0x1A09*/ const CO_OD_entryRecord_t OD_record1A09[9] = {
           {(void*)&CO_OD_ROM.TPDOMappingParameter[9].numberOfMappedObjects, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[9].mappedObject1, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[9].mappedObject2, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[9].mappedObject3, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[9].mappedObject4, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[9].mappedObject5, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[9].mappedObject6, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[9].mappedObject7, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[9].mappedObject8, 0x8D, 0x4 },
};

/*0x1A0A*/ const CO_OD_entryRecord_t OD_record1A0A[9] = {
           {(void*)&CO_OD_ROM.TPDOMappingParameter[10].numberOfMappedObjects, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[10].mappedObject1, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[10].mappedObject2, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[10].mappedObject3, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[10].mappedObject4, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[10].mappedObject5, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[10].mappedObject6, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[10].mappedObject7, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[10].mappedObject8, 0x8D, 0x4 },
};

/*0x1A0B*/ const CO_OD_entryRecord_t OD_record1A0B[9] = {
           {(void*)&CO_OD_ROM.TPDOMappingParameter[11].numberOfMappedObjects, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[11].mappedObject1, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[11].mappedObject2, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[11].mappedObject3, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[11].mappedObject4, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[11].mappedObject5, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[11].mappedObject6, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[11].mappedObject7, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[11].mappedObject8, 0x8D, 0x4 },
};

/*0x1A0C*/ const CO_OD_entryRecord_t OD_record1A0C[9] = {
           {(void*)&CO_OD_ROM.TPDOMappingParameter[12].numberOfMappedObjects, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[12].mappedObject1, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[12].mappedObject2, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[12].mappedObject3, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[12].mappedObject4, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[12].mappedObject5, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[12].mappedObject6, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[12].mappedObject7, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[12].mappedObject8, 0x8D, 0x4 },
};

/*0x1A0D*/ const CO_OD_entryRecord_t OD_record1A0D[9] = {
           {(void*)&CO_OD_ROM.TPDOMappingParameter[13].numberOfMappedObjects, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[13].mappedObject1, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[13].mappedObject2, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[13].mappedObject3, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[13].mappedObject4, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[13].mappedObject5, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[13].mappedObject6, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[13].mappedObject7, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[13].mappedObject8, 0x8D, 0x4 },
};

/*0x1A0E*/ const CO_OD_entryRecord_t OD_record1A0E[9] = {
           {(void*)&CO_OD_ROM.TPDOMappingParameter[14].numberOfMappedObjects, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[14].mappedObject1, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[14].mappedObject2, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[14].mappedObject3, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[14].mappedObject4, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[14].mappedObject5, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[14].mappedObject6, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[14].mappedObject7, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[14].mappedObject8, 0x8D, 0x4 },
};

/*0x1A0F*/ const CO_OD_entryRecord_t OD_record1A0F[9] = {
           {(void*)&CO_OD_ROM.TPDOMappingParameter[15].numberOfMappedObjects, 0x0D, 0x1 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[15].mappedObject1, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[15].mappedObject2, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[15].mappedObject3, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[15].mappedObject4, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[15].mappedObject5, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[15].mappedObject6, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[15].mappedObject7, 0x8D, 0x4 },
           {(void*)&CO_OD_ROM.TPDOMappingParameter[15].mappedObject8, 0x8D, 0x4 },
};

/*0x4002*/ const CO_OD_entryRecord_t OD_record4002[3] = {
           {(void*)&CO_OD_RAM.battery1.maxSubIndex, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.battery1.MCU_Temperature, 0xA6, 0x2 },
           {(void*)&CO_OD_RAM.battery1.MCU_Voltage, 0xA6, 0x2 },
};

/*0x4003*/ const CO_OD_entryRecord_t OD_record4003[3] = {
           {(void*)&CO_OD_RAM.battery2.maxSubIndex, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.battery2.MCU_Temperature, 0xA6, 0x2 },
           {(void*)&CO_OD_RAM.battery2.MCU_Voltage, 0xA6, 0x2 },
};

/*0x4004*/ const CO_OD_entryRecord_t OD_record4004[3] = {
           {(void*)&CO_OD_RAM.solarPanel1.maxSubIndex, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel1.MCU_Temperature, 0xA6, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel1.MCU_Voltage, 0xA6, 0x2 },
};

/*0x4005*/ const CO_OD_entryRecord_t OD_record4005[3] = {
           {(void*)&CO_OD_RAM.solarPanel2.maxSubIndex, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel2.MCU_Temperature, 0xA6, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel2.MCU_Voltage, 0xA6, 0x2 },
};

/*0x4006*/ const CO_OD_entryRecord_t OD_record4006[3] = {
           {(void*)&CO_OD_RAM.solarPanel3.maxSubIndex, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel3.MCU_Temperature, 0xA6, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel3.MCU_Voltage, 0xA6, 0x2 },
};

/*0x4007*/ const CO_OD_entryRecord_t OD_record4007[3] = {
           {(void*)&CO_OD_RAM.solarPanel4.maxSubIndex, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel4.MCU_Temperature, 0xA6, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel4.MCU_Voltage, 0xA6, 0x2 },
};

/*0x4008*/ const CO_OD_entryRecord_t OD_record4008[3] = {
           {(void*)&CO_OD_RAM.solarPanel5.maxSubIndex, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel5.MCU_Temperature, 0xA6, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel5.MCU_Voltage, 0xA6, 0x2 },
};

/*0x4009*/ const CO_OD_entryRecord_t OD_record4009[3] = {
           {(void*)&CO_OD_RAM.solarPanel6.maxSubIndex, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel6.MCU_Temperature, 0xA6, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel6.MCU_Voltage, 0xA6, 0x2 },
};

/*0x400A*/ const CO_OD_entryRecord_t OD_record400A[3] = {
           {(void*)&CO_OD_RAM.solarPanel7.maxSubIndex, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel7.MCU_Temperature, 0xA6, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel7.MCU_Voltage, 0xA6, 0x2 },
};

/*0x400B*/ const CO_OD_entryRecord_t OD_record400B[3] = {
           {(void*)&CO_OD_RAM.solarPanel8.maxSubIndex, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.solarPanel8.MCU_Temperature, 0xA6, 0x2 },
           {(void*)&CO_OD_RAM.solarPanel8.MCU_Voltage, 0xA6, 0x2 },
};

/*0x4011*/ const CO_OD_entryRecord_t OD_record4011[1] = {
           {(void*)&CO_OD_RAM.starTracker.maxSubIndex, 0x06, 0x1 },
};

/*0x4012*/ const CO_OD_entryRecord_t OD_record4012[1] = {
           {(void*)&CO_OD_RAM.GPS.maxSubIndex, 0x06, 0x1 },
};

/*0x4013*/ const CO_OD_entryRecord_t OD_record4013[3] = {
           {(void*)&CO_OD_RAM.IMU.maxSubIndex, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.IMU.MCU_Temperature, 0xA6, 0x2 },
           {(void*)&CO_OD_RAM.IMU.MCU_Voltage, 0xA6, 0x2 },
};

/*0x4014*/ const CO_OD_entryRecord_t OD_record4014[3] = {
           {(void*)&CO_OD_RAM.magnetometer1.maxSubIndex, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.magnetometer1.MCU_Temperature, 0xA6, 0x2 },
           {(void*)&CO_OD_RAM.magnetometer1.MCU_Voltage, 0xA6, 0x2 },
};

/*0x4015*/ const CO_OD_entryRecord_t OD_record4015[3] = {
           {(void*)&CO_OD_RAM.magnetometer2.maxSubIndex, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.magnetometer2.MCU_Temperature, 0xA6, 0x2 },
           {(void*)&CO_OD_RAM.magnetometer2.MCU_Voltage, 0xA6, 0x2 },
};

/*0x4016*/ const CO_OD_entryRecord_t OD_record4016[3] = {
           {(void*)&CO_OD_RAM.RW_MT1.maxSubIndex, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.RW_MT1.MCU_Temperature, 0xA6, 0x2 },
           {(void*)&CO_OD_RAM.RW_MT1.MCU_Voltage, 0xA6, 0x2 },
};

/*0x4017*/ const CO_OD_entryRecord_t OD_record4017[3] = {
           {(void*)&CO_OD_RAM.RW_MT2.maxSubIndex, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.RW_MT2.MCU_Temperature, 0xA6, 0x2 },
           {(void*)&CO_OD_RAM.RW_MT2.MCU_Voltage, 0xA6, 0x2 },
};

/*0x4018*/ const CO_OD_entryRecord_t OD_record4018[3] = {
           {(void*)&CO_OD_RAM.RW_MT3.maxSubIndex, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.RW_MT3.MCU_Temperature, 0xA6, 0x2 },
           {(void*)&CO_OD_RAM.RW_MT3.MCU_Voltage, 0xA6, 0x2 },
};

/*0x4019*/ const CO_OD_entryRecord_t OD_record4019[3] = {
           {(void*)&CO_OD_RAM.RW4.maxSubIndex, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.RW4.MCU_Temperature, 0xA6, 0x2 },
           {(void*)&CO_OD_RAM.RW4.MCU_Voltage, 0xA6, 0x2 },
};

/*0x4021*/ const CO_OD_entryRecord_t OD_record4021[1] = {
           {(void*)&CO_OD_RAM.oreSatLive.maxSubIndex, 0x06, 0x1 },
};

/*0x4022*/ const CO_OD_entryRecord_t OD_record4022[1] = {
           {(void*)&CO_OD_RAM.CFC.maxSubIndex, 0x06, 0x1 },
};

/*0x4031*/ const CO_OD_entryRecord_t OD_record4031[3] = {
           {(void*)&CO_OD_RAM.protocard1.maxSubIndex, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.protocard1.MCU_Temperature, 0xA6, 0x2 },
           {(void*)&CO_OD_RAM.protocard1.MCU_Voltage, 0xA6, 0x2 },
};

/*0x4032*/ const CO_OD_entryRecord_t OD_record4032[3] = {
           {(void*)&CO_OD_RAM.protocard2.maxSubIndex, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.protocard2.MCU_Temperature, 0xA6, 0x2 },
           {(void*)&CO_OD_RAM.protocard2.MCU_Voltage, 0xA6, 0x2 },
};

/*0x4033*/ const CO_OD_entryRecord_t OD_record4033[3] = {
           {(void*)&CO_OD_RAM.protocard3.maxSubIndex, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.protocard3.MCU_Temperature, 0xA6, 0x2 },
           {(void*)&CO_OD_RAM.protocard3.MCU_Voltage, 0xA6, 0x2 },
};

/*******************************************************************************
   OBJECT DICTIONARY
*******************************************************************************/
const CO_OD_entry_t CO_OD[CO_OD_NoOfElements] = {
{0x1000, 0x00, 0x85,  4, (void*)&CO_OD_ROM.deviceType},
{0x1001, 0x00, 0x26,  1, (void*)&CO_OD_RAM.errorRegister},
{0x1002, 0x00, 0xA6,  4, (void*)&CO_OD_RAM.manufacturerStatusRegister},
{0x1003, 0x08, 0x86,  4, (void*)&CO_OD_RAM.preDefinedErrorField[0]},
{0x1005, 0x00, 0x8D,  4, (void*)&CO_OD_ROM.COB_ID_SYNCMessage},
{0x1006, 0x00, 0x8D,  4, (void*)&CO_OD_ROM.communicationCyclePeriod},
{0x1007, 0x00, 0x8D,  4, (void*)&CO_OD_ROM.synchronousWindowLength},
{0x1008, 0x00, 0x05, 21, (void*)&CO_OD_ROM.manufacturerDeviceName},
{0x1009, 0x00, 0x05,  3, (void*)&CO_OD_ROM.manufacturerHardwareVersion},
{0x100A, 0x00, 0x05,  5, (void*)&CO_OD_ROM.manufacturerSoftwareVersion},
{0x1010, 0x01, 0x8E,  4, (void*)&CO_OD_RAM.storeParameters[0]},
{0x1011, 0x01, 0x8E,  4, (void*)&CO_OD_RAM.restoreDefaultParameters[0]},
{0x1014, 0x00, 0x85,  4, (void*)&CO_OD_ROM.COB_ID_EMCY},
{0x1015, 0x00, 0x8D,  2, (void*)&CO_OD_ROM.inhibitTimeEMCY},
{0x1016, 0x04, 0x8D,  4, (void*)&CO_OD_ROM.consumerHeartbeatTime[0]},
{0x1017, 0x00, 0x8D,  2, (void*)&CO_OD_ROM.producerHeartbeatTime},
{0x1018, 0x04, 0x00,  0, (void*)&OD_record1018},
{0x1019, 0x00, 0x0D,  1, (void*)&CO_OD_ROM.synchronousCounterOverflowValue},
{0x1029, 0x06, 0x0D,  1, (void*)&CO_OD_ROM.errorBehavior[0]},
{0x1200, 0x02, 0x00,  0, (void*)&OD_record1200},
{0x1280, 0x03, 0x00,  0, (void*)&OD_record1280},
{0x1400, 0x02, 0x00,  0, (void*)&OD_record1400},
{0x1401, 0x02, 0x00,  0, (void*)&OD_record1401},
{0x1402, 0x02, 0x00,  0, (void*)&OD_record1402},
{0x1403, 0x02, 0x00,  0, (void*)&OD_record1403},
{0x1404, 0x02, 0x00,  0, (void*)&OD_record1404},
{0x1405, 0x02, 0x00,  0, (void*)&OD_record1405},
{0x1406, 0x02, 0x00,  0, (void*)&OD_record1406},
{0x1407, 0x02, 0x00,  0, (void*)&OD_record1407},
{0x1408, 0x02, 0x00,  0, (void*)&OD_record1408},
{0x1409, 0x02, 0x00,  0, (void*)&OD_record1409},
{0x140A, 0x02, 0x00,  0, (void*)&OD_record140A},
{0x140B, 0x02, 0x00,  0, (void*)&OD_record140B},
{0x140C, 0x02, 0x00,  0, (void*)&OD_record140C},
{0x140D, 0x02, 0x00,  0, (void*)&OD_record140D},
{0x140E, 0x02, 0x00,  0, (void*)&OD_record140E},
{0x140F, 0x02, 0x00,  0, (void*)&OD_record140F},
{0x1410, 0x02, 0x00,  0, (void*)&OD_record1410},
{0x1411, 0x02, 0x00,  0, (void*)&OD_record1411},
{0x1412, 0x02, 0x00,  0, (void*)&OD_record1412},
{0x1413, 0x02, 0x00,  0, (void*)&OD_record1413},
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
{0x1F80, 0x00, 0x8D,  4, (void*)&CO_OD_ROM.NMTStartup},
{0x1F81, 0x7F, 0x8E,  4, (void*)&CO_OD_RAM.slaveAssignment[0]},
{0x1F82, 0x7F, 0x0E,  1, (void*)&CO_OD_RAM.requestNMT[0]},
{0x1F89, 0x00, 0x8E,  4, (void*)&CO_OD_RAM.bootTime},
{0x2010, 0x00, 0xBE,  8, (void*)&CO_OD_RAM.SCET},
{0x2011, 0x00, 0xBE,  8, (void*)&CO_OD_RAM.UTC},
{0x2100, 0x00, 0x26, 10, (void*)&CO_OD_RAM.errorStatusBits},
{0x2101, 0x00, 0x0D,  1, (void*)&CO_OD_ROM.CANNodeID},
{0x2102, 0x00, 0x8D,  2, (void*)&CO_OD_ROM.CANBitRate},
{0x2103, 0x00, 0x8E,  2, (void*)&CO_OD_RAM.SYNCCounter},
{0x2104, 0x00, 0x86,  2, (void*)&CO_OD_RAM.SYNCTime},
{0x2106, 0x03, 0x85,  2, (void*)&CO_OD_ROM.calibration[0]},
{0x2107, 0x03, 0xA6,  2, (void*)&CO_OD_RAM.sensors[0]},
{0x2108, 0x01, 0xA6,  2, (void*)&CO_OD_RAM.temperature[0]},
{0x2109, 0x01, 0xA6,  2, (void*)&CO_OD_RAM.voltage[0]},
{0x4002, 0x02, 0x00,  1, (void*)&OD_record4002},
{0x4003, 0x02, 0x00,  1, (void*)&OD_record4003},
{0x4004, 0x02, 0x00,  1, (void*)&OD_record4004},
{0x4005, 0x02, 0x00,  1, (void*)&OD_record4005},
{0x4006, 0x02, 0x00,  1, (void*)&OD_record4006},
{0x4007, 0x02, 0x00,  1, (void*)&OD_record4007},
{0x4008, 0x02, 0x00,  1, (void*)&OD_record4008},
{0x4009, 0x02, 0x00,  1, (void*)&OD_record4009},
{0x400A, 0x02, 0x00,  1, (void*)&OD_record400A},
{0x400B, 0x02, 0x00,  1, (void*)&OD_record400B},
{0x4011, 0x00, 0x00,  1, (void*)&OD_record4011},
{0x4012, 0x00, 0x00,  1, (void*)&OD_record4012},
{0x4013, 0x02, 0x00,  1, (void*)&OD_record4013},
{0x4014, 0x02, 0x00,  1, (void*)&OD_record4014},
{0x4015, 0x02, 0x00,  1, (void*)&OD_record4015},
{0x4016, 0x02, 0x00,  1, (void*)&OD_record4016},
{0x4017, 0x02, 0x00,  1, (void*)&OD_record4017},
{0x4018, 0x02, 0x00,  1, (void*)&OD_record4018},
{0x4019, 0x02, 0x00,  1, (void*)&OD_record4019},
{0x4021, 0x00, 0x00,  1, (void*)&OD_record4021},
{0x4022, 0x00, 0x00,  1, (void*)&OD_record4022},
{0x4031, 0x02, 0x00,  1, (void*)&OD_record4031},
{0x4032, 0x02, 0x00,  1, (void*)&OD_record4032},
{0x4033, 0x02, 0x00,  1, (void*)&OD_record4033},
};
// clang-format on
