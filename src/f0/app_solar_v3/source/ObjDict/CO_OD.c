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
/*1008*/ {'O', 'r', 'e', 'S', 'a', 't', ' ', 'S', 'o', 'l', 'a', 'r', ' ', 'B', 'o', 'a', 'r', 'd'},
/*1009*/ {'3', '.', '0'},
/*100A*/ {'0', '.', '1', '.', '0'},
/*1014*/ 0x0080L,
/*1015*/ 0x64,
/*1016*/ {0x00000000, 0x00000000, 0x00000000, 0x00000000},
/*1017*/ 0x3E8,
/*1018*/ {0x4L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1019*/ 0x0L,
/*1029*/ {0x00, 0x00, 0x01, 0x00, 0x00, 0x00},
/*1200*/ {{0x2L, 0x0600L, 0x0580L}},
/*1400*/ {{0x2L, 0x0200L, 0xFEL},
/*1401*/ {0x2L, 0x0300L, 0xFEL},
/*1402*/ {0x2L, 0x0400L, 0xFEL},
/*1403*/ {0x2L, 0x0500L, 0xFEL}},
/*1600*/ {{0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1601*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1602*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1603*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L}},
/*1800*/ {{0x6L, 0x0180L, 0xFEL, 0x00, 0x0L, 0x2710, 0x0L},
/*1801*/ {0x6L, 0x0280L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*1802*/ {0x6L, 0x0380L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L},
/*1803*/ {0x6L, 0x0480L, 0xFEL, 0x00, 0x0L, 0x00, 0x0L}},
/*1A00*/ {{0x2L, 0x21080110L, 0x21090110L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1A01*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1A02*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L},
/*1A03*/ {0x0L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L, 0x0000L}},
/*1F80*/ 0x0000L,
/*2101*/ 0x7FL,
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
/*2100*/ {0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L, 0x0L},
/*2103*/ 0x00,
/*2104*/ 0x00,
/*2108*/ {0},
/*2109*/ {0},
/*2130*/ {0x3L, {'-', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, 0x00000000L, 0x0000L},

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

/*0x2130*/ const CO_OD_entryRecord_t OD_record2130[4] = {
           {(void*)&CO_OD_RAM.time.maxSubIndex, 0x06, 0x1 },
           {(void*)&CO_OD_RAM.time.string, 0x06, 0x1E },
           {(void*)&CO_OD_RAM.time.epochTimeBaseMs, 0x8E, 0x8 },
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
{0x1400, 0x02, 0x00,  0, (void*)&OD_record1400},
{0x1401, 0x02, 0x00,  0, (void*)&OD_record1401},
{0x1402, 0x02, 0x00,  0, (void*)&OD_record1402},
{0x1403, 0x02, 0x00,  0, (void*)&OD_record1403},
{0x1600, 0x08, 0x00,  0, (void*)&OD_record1600},
{0x1601, 0x08, 0x00,  0, (void*)&OD_record1601},
{0x1602, 0x08, 0x00,  0, (void*)&OD_record1602},
{0x1603, 0x08, 0x00,  0, (void*)&OD_record1603},
{0x1800, 0x06, 0x00,  0, (void*)&OD_record1800},
{0x1801, 0x06, 0x00,  0, (void*)&OD_record1801},
{0x1802, 0x06, 0x00,  0, (void*)&OD_record1802},
{0x1803, 0x06, 0x00,  0, (void*)&OD_record1803},
{0x1A00, 0x08, 0x00,  0, (void*)&OD_record1A00},
{0x1A01, 0x08, 0x00,  0, (void*)&OD_record1A01},
{0x1A02, 0x08, 0x00,  0, (void*)&OD_record1A02},
{0x1A03, 0x08, 0x00,  0, (void*)&OD_record1A03},
{0x1F80, 0x00, 0x8D,  4, (void*)&CO_OD_ROM.NMTStartup},
{0x2100, 0x00, 0x26, 10, (void*)&CO_OD_RAM.errorStatusBits},
{0x2101, 0x00, 0x0D,  1, (void*)&CO_OD_ROM.CANNodeID},
{0x2102, 0x00, 0x8D,  2, (void*)&CO_OD_ROM.CANBitRate},
{0x2103, 0x00, 0x8E,  2, (void*)&CO_OD_RAM.SYNCCounter},
{0x2104, 0x00, 0x86,  2, (void*)&CO_OD_RAM.SYNCTime},
{0x2108, 0x01, 0xA6,  2, (void*)&CO_OD_RAM.temperature[0]},
{0x2109, 0x01, 0xA6,  2, (void*)&CO_OD_RAM.voltage[0]},
{0x2130, 0x03, 0x00,  0, (void*)&OD_record2130},
};
