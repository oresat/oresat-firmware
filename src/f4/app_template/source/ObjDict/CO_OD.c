/*
 * CANopen Object Dictionary.
 *
 * This file was automatically generated with CANopenNode Object
 * Dictionary Editor. DON'T EDIT THIS FILE MANUALLY !!!!
 * Object Dictionary Editor is currently an older, but functional web
 * application. For more info see See 'Object_Dictionary_Editor/about.html' in
 * <http://sourceforge.net/p/canopennode/code_complete/ci/master/tree/>
 * For more information on CANopen Object Dictionary see <CO_SDO.h>.
 *
 * @file        CO_OD.c/CO_OD.h
 * @author      Janez Paternoster
 * @copyright   2010 - 2016 Janez Paternoster
 *
 * This file is part of CANopenNode, an opensource CANopen Stack.
 * Project home page is <https://github.com/CANopenNode/CANopenNode>.
 * For more information on CANopen see <http://www.can-cia.org/>.
 *
 * CANopenNode is free and open source software: you can redistribute
 * it and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Following clarification and special exception to the GNU General Public
 * License is included to the distribution terms of CANopenNode:
 *
 * Linking this library statically or dynamically with other modules is
 * making a combined work based on this library. Thus, the terms and
 * conditions of the GNU General Public License cover the whole combination.
 *
 * As a special exception, the copyright holders of this library give
 * you permission to link this library with independent modules to
 * produce an executable, regardless of the license terms of these
 * independent modules, and to copy and distribute the resulting
 * executable under terms of your choice, provided that you also meet,
 * for each linked independent module, the terms and conditions of the
 * license of that module. An independent module is a module which is
 * not derived from or based on this library. If you modify this
 * library, you may extend this exception to your version of the
 * library, but you are not obliged to do so. If you do not wish
 * to do so, delete this exception statement from your version.
 * Dictionary Editor v0.7-12-g6a8ebda * DON'T EDIT THIS FILE MANUALLY !!!!
 */


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
/*1008*/ {'O', 'r', 'e', 's', 'a', 't', ' ', 'M', 'a', 's', 't', 'e', 'r', ' ', 'N', 'o', 'd', 'e'},
/*1009*/ {'3', '.', '0', '0'},
/*100A*/ {'3', '.', '0', '0'},
/*1014*/ 0x0080L,
/*1015*/ 0x64,
/*1016*/ {0x00000000, 0x00000000, 0x00000000, 0x00000000},
/*1017*/ 0x3E8,
/*1018*/ {0x4L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1019*/ 0x0L,
/*1029*/ {0x00, 0x00, 0x01, 0x00, 0x00, 0x00},
/*1200*/ {{0x2L, 0x0600L, 0x0580L}},
/*1400*/ {{0x2L, 0x0200L, 0xFFL},
/*1401*/ {0x2L, 0x0300L, 0xFEL},
/*1402*/ {0x2L, 0x0400L, 0xFEL},
/*1403*/ {0x2L, 0x0500L, 0xFEL},
/*1404*/ {0x2L, 0x80000000L, 0xFEL},
/*1405*/ {0x2L, 0x80000000L, 0xFEL},
/*1406*/ {0x2L, 0x80000000L, 0xFEL},
/*1407*/ {0x2L, 0x80000000L, 0xFEL},
/*1408*/ {0x2L, 0x80000000L, 0xFEL},
/*1409*/ {0x2L, 0x80000000L, 0xFEL},
/*140A*/ {0x2L, 0x80000000L, 0xFEL},
/*140B*/ {0x2L, 0x80000000L, 0xFEL},
/*140C*/ {0x2L, 0x80000000L, 0xFEL},
/*140D*/ {0x2L, 0x80000000L, 0xFEL},
/*140E*/ {0x2L, 0x80000000L, 0xFEL},
/*140F*/ {0x2L, 0x80000000L, 0xFEL}},
/*1600*/ {{0x2L, 0x62000108L, 0x62000208L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
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
/*1A00*/ {{0x2L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
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
/*2101*/ 0x70L,
/*2102*/ 0x3E8,

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
/*2100*/ {0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L},
/*2103*/ 0x00,
/*2104*/ 0x00,
/*2107*/ {1000, 0, 0, 0, 0},
/*2108*/ {0},
/*2109*/ {0},
/*2130*/ {0x3L, {'-', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, 0x00000000L, 0x0000L},

           CO_OD_FIRST_LAST_WORD,
};


/***** Definition for EEPROM variables *******************************************/
struct sCO_OD_EEPROM CO_OD_EEPROM = {
           CO_OD_FIRST_LAST_WORD,

/*2106*/ 0x0000L,

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

/*0x2130*/ const CO_OD_entryRecord_t OD_record2130[4] = {
           {(void*)&CO_OD_RAM.time.maxSubIndex, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.time.string, 0x06, 0x1E },
           {(void*)&CO_OD_RAM.time.epochTimeBaseMs, 0x86, 0x8 },
           {(void*)&CO_OD_RAM.time.epochTimeOffsetMs, 0xBE, 0x4 },
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
{0x1008, 0x00, 0x05, 18, (void*)&CO_OD_ROM.manufacturerDeviceName},
{0x1009, 0x00, 0x05,  4, (void*)&CO_OD_ROM.manufacturerHardwareVersion},
{0x100A, 0x00, 0x05,  4, (void*)&CO_OD_ROM.manufacturerSoftwareVersion},
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
{0x1F80, 0x00, 0x8D,  4, (void*)&CO_OD_ROM.NMTStartup},
{0x1F81, 0x7F, 0x8E,  4, (void*)&CO_OD_RAM.slaveAssignment[0]},
{0x1F82, 0x7F, 0x0E,  1, (void*)&CO_OD_RAM.requestNMT[0]},
{0x1F89, 0x00, 0x8E,  4, (void*)&CO_OD_RAM.bootTime},
{0x2100, 0x00, 0x26, 10, (void*)&CO_OD_RAM.errorStatusBits},
{0x2101, 0x00, 0x0D,  1, (void*)&CO_OD_ROM.CANNodeID},
{0x2102, 0x00, 0x8D,  2, (void*)&CO_OD_ROM.CANBitRate},
{0x2103, 0x00, 0x8E,  2, (void*)&CO_OD_RAM.SYNCCounter},
{0x2104, 0x00, 0x86,  2, (void*)&CO_OD_RAM.SYNCTime},
{0x2106, 0x00, 0x87,  4, (void*)&CO_OD_EEPROM.powerOnCounter},
{0x2107, 0x05, 0xBE,  2, (void*)&CO_OD_RAM.performance[0]},
{0x2108, 0x01, 0xA6,  2, (void*)&CO_OD_RAM.temperature[0]},
{0x2109, 0x01, 0xA6,  2, (void*)&CO_OD_RAM.voltage[0]},
{0x2130, 0x03, 0x00,  0, (void*)&OD_record2130},
};
