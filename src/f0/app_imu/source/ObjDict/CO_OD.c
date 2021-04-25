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
/*2010*/ 0x00000000L,
/*2011*/ 0x00000000L,
/*2020*/ {0x0000L, 0x0000L, 0x0000L},
/*2021*/ {0x3L, 0x00, 0x00, 0x00},
/*2022*/ {0x8L, 0x0, 0x0L, 0x0L, 0x0L, 0x00, 0x00, 0x00, 0x00},
/*2100*/ {0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L},
/*6000*/ {0x6L, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
/*6001*/ {0x6L, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
/*6002*/ 0x0,
/*6003*/ {0x3L, 0x00, 0x00, 0x00},
/*6004*/ {0x3L, 0x00, 0x00, 0x00},
/*6005*/ {0x3L, 0x00, 0x00, 0x00},
/*6006*/ {0x3L, 0x00, 0x00, 0x00},

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
/*1016*/ {0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1017*/ 0x3E8,
/*1019*/ 0x0L,
/*1200*/ {{0x3L, 0x80000000L, 0x80000000L, 0x1L}},
/*1400*/ {{0x5L, 0x80000200L, 0xFEL, 0x00},
/*1401*/ {0x5L, 0x80000300L, 0xFEL, 0x00},
/*1402*/ {0x5L, 0x80000400L, 0xFEL, 0x00},
/*1403*/ {0x5L, 0x80000500L, 0xFEL, 0x00},
/*1404*/ {0x5L, 0x80000200L, 0xFEL, 0x00},
/*1405*/ {0x5L, 0x80000300L, 0xFEL, 0x00},
/*1406*/ {0x5L, 0x80000400L, 0xFEL, 0x00},
/*1407*/ {0x5L, 0x80000500L, 0xFEL, 0x00},
/*1408*/ {0x5L, 0x80000200L, 0xFEL, 0x00},
/*1409*/ {0x5L, 0x80000300L, 0xFEL, 0x00},
/*140A*/ {0x5L, 0x80000400L, 0xFEL, 0x00},
/*140B*/ {0x5L, 0x80000500L, 0xFEL, 0x00},
/*140C*/ {0x5L, 0x80000200L, 0xFEL, 0x00},
/*140D*/ {0x5L, 0x80000300L, 0xFEL, 0x00},
/*140E*/ {0x5L, 0x80000400L, 0xFEL, 0x00},
/*140F*/ {0x5L, 0x80000500L, 0xFEL, 0x00}},
/*1600*/ {{0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1601*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1602*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1603*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1604*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1605*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1606*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1607*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1608*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1609*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*160A*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*160B*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*160C*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*160D*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*160E*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*160F*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L}},
/*1800*/ {{0x6L, 0x40000180L, 0xFEL, 0x00, 0x0L, 0x2710, 0x0L},
/*1801*/ {0x6L, 0x40000280L, 0xFEL, 0x00, 0x0L, 0x2710, 0x0L},
/*1802*/ {0x6L, 0x40000380L, 0xFEL, 0x00, 0x0L, 0x2710, 0x0L},
/*1803*/ {0x6L, 0x40000480L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*1804*/ {0x6L, 0x40000180L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*1805*/ {0x6L, 0x40000280L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
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
/*1A00*/ {{0x3L, 0x60000110L, 0x60000210L, 0x60000310L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1A01*/ {0x3L, 0x60010110L, 0x60010210L, 0x60010310L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1A02*/ {0x1L, 0x60020008L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1A03*/ {0x4L, 0x60030110L, 0x60030210L, 0x60030310L, 0x60040110L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1A04*/ {0x4L, 0x60040210L, 0x60040310L, 0x60050110L, 0x60050210L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1A05*/ {0x4L, 0x60050310L, 0x60060110L, 0x60060210L, 0x60060310L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
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

           CO_OD_FIRST_LAST_WORD,
};


/***** Definition for PERSIST_MFR variables *******************************************/
struct sCO_OD_PERSIST_MFR CO_OD_PERSIST_MFR = {
           CO_OD_FIRST_LAST_WORD,

/*2000*/ {0x4L, 0x0L, 0x0L, 0x0L, 0x0L},

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

/*0x6000*/ const CO_OD_entryRecord_t OD_record6000[7] = {
           {(void*)&CO_OD_RAM.gyroscope.highestSubIndexSupported, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.gyroscope.pitchRate, 0xA6, 0x2 },
           {(void*)&CO_OD_RAM.gyroscope.yawRate, 0xA6, 0x2 },
           {(void*)&CO_OD_RAM.gyroscope.rollRate, 0xA6, 0x2 },
           {(void*)&CO_OD_RAM.gyroscope.pitchRateRaw, 0xA6, 0x2 },
           {(void*)&CO_OD_RAM.gyroscope.yawRateRaw, 0xA6, 0x2 },
           {(void*)&CO_OD_RAM.gyroscope.rollRateRaw, 0xA6, 0x2 },
};

/*0x6001*/ const CO_OD_entryRecord_t OD_record6001[7] = {
           {(void*)&CO_OD_RAM.acceleration.highestSubIndexSupported, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.acceleration.x, 0xA6, 0x2 },
           {(void*)&CO_OD_RAM.acceleration.y, 0xA6, 0x2 },
           {(void*)&CO_OD_RAM.acceleration.z, 0xA6, 0x2 },
           {(void*)&CO_OD_RAM.acceleration.XRaw, 0xA6, 0x2 },
           {(void*)&CO_OD_RAM.acceleration.YRaw, 0xA6, 0x2 },
           {(void*)&CO_OD_RAM.acceleration.ZRaw, 0xA6, 0x2 },
};

/*0x6003*/ const CO_OD_entryRecord_t OD_record6003[4] = {
           {(void*)&CO_OD_RAM.magnetometerPZ1.highestSubIndexSupported, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.magnetometerPZ1.x, 0xA6, 0x2 },
           {(void*)&CO_OD_RAM.magnetometerPZ1.y, 0xA6, 0x2 },
           {(void*)&CO_OD_RAM.magnetometerPZ1.z, 0xA6, 0x2 },
};

/*0x6004*/ const CO_OD_entryRecord_t OD_record6004[4] = {
           {(void*)&CO_OD_RAM.magnetometerPZ2.highestSubIndexSupported, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.magnetometerPZ2.x, 0xA6, 0x2 },
           {(void*)&CO_OD_RAM.magnetometerPZ2.y, 0xA6, 0x2 },
           {(void*)&CO_OD_RAM.magnetometerPZ2.z, 0xA6, 0x2 },
};

/*0x6005*/ const CO_OD_entryRecord_t OD_record6005[4] = {
           {(void*)&CO_OD_RAM.magnetometerMZ1.highestSubIndexSupported, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.magnetometerMZ1.x, 0xA6, 0x2 },
           {(void*)&CO_OD_RAM.magnetometerMZ1.y, 0xA6, 0x2 },
           {(void*)&CO_OD_RAM.magnetometerMZ1.z, 0xA6, 0x2 },
};

/*0x6006*/ const CO_OD_entryRecord_t OD_record6006[4] = {
           {(void*)&CO_OD_RAM.magnetometerMZ2.highestSubIndexSupported, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.magnetometerMZ2.x, 0xA6, 0x2 },
           {(void*)&CO_OD_RAM.magnetometerMZ2.y, 0xA6, 0x2 },
           {(void*)&CO_OD_RAM.magnetometerMZ2.z, 0xA6, 0x2 },
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
{0x1016, 0x08, 0x8F,  4, (void*)&CO_OD_PERSIST_COMM.consumerHeartbeatTime[0]},
{0x1017, 0x00, 0x8F,  2, (void*)&CO_OD_PERSIST_COMM.producerHeartbeatTime},
{0x1018, 0x04, 0x00,  0, (void*)&OD_record1018},
{0x1019, 0x00, 0x0F,  1, (void*)&CO_OD_PERSIST_COMM.synchronousCounterOverflowValue},
{0x1029, 0x06, 0x0D,  1, (void*)&CO_OD_ROM.errorBehavior[0]},
{0x1200, 0x03, 0x00,  0, (void*)&OD_record1200},
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
{0x2000, 0x04, 0x00,  0, (void*)&OD_record2000},
{0x2010, 0x00, 0xBE,  8, (void*)&CO_OD_RAM.SCET},
{0x2011, 0x00, 0xBE,  8, (void*)&CO_OD_RAM.UTC},
{0x2020, 0x03, 0x86,  4, (void*)&CO_OD_RAM.MCU_UniqueDeviceID[0]},
{0x2021, 0x03, 0x00,  0, (void*)&OD_record2021},
{0x2022, 0x08, 0x00,  0, (void*)&OD_record2022},
{0x2100, 0x00, 0x06, 10, (void*)&CO_OD_RAM.errorStatusBits},
{0x6000, 0x06, 0x00,  0, (void*)&OD_record6000},
{0x6001, 0x06, 0x00,  0, (void*)&OD_record6001},
{0x6002, 0x00, 0x26,  1, (void*)&CO_OD_RAM.IMU_Temperature},
{0x6003, 0x03, 0x00,  0, (void*)&OD_record6003},
{0x6004, 0x03, 0x00,  0, (void*)&OD_record6004},
{0x6005, 0x03, 0x00,  0, (void*)&OD_record6005},
{0x6006, 0x03, 0x00,  0, (void*)&OD_record6006},
};
// clang-format on
