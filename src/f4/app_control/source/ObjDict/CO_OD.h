// clang-format off
/*******************************************************************************

   File - CO_OD.c/CO_OD.h
   CANopen Object Dictionary.

   This file was automatically generated with libedssharp Object
   Dictionary Editor v0.8-78-g7c49b15   DON'T EDIT THIS FILE MANUALLY !!!!
*******************************************************************************/


#ifndef CO_OD_H_
#define CO_OD_H_

/*******************************************************************************
   CANopen DATA TYPES
*******************************************************************************/
   typedef bool_t       BOOLEAN;
   typedef uint8_t      UNSIGNED8;
   typedef uint16_t     UNSIGNED16;
   typedef uint32_t     UNSIGNED32;
   typedef uint64_t     UNSIGNED64;
   typedef int8_t       INTEGER8;
   typedef int16_t      INTEGER16;
   typedef int32_t      INTEGER32;
   typedef int64_t      INTEGER64;
   typedef float32_t    REAL32;
   typedef float64_t    REAL64;
   typedef char_t       VISIBLE_STRING;
   typedef oChar_t      OCTET_STRING;

   #ifdef DOMAIN
   #undef DOMAIN
   #endif

   typedef domain_t     DOMAIN;

#ifndef timeOfDay_t
    typedef union {
        unsigned long long ullValue;
        struct {
            unsigned long ms:28;
            unsigned reserved:4;
            unsigned days:16;
            unsigned reserved2:16;
        };
    }timeOfDay_t;
#endif

    typedef timeOfDay_t TIME_OF_DAY;
    typedef timeOfDay_t TIME_DIFFERENCE;


/*******************************************************************************
   FILE INFO:
      FileName:     app_master.eds
      FileVersion:  0
      CreationTime: 12:18PM
      CreationDate: 08-30-2019
      CreatedBy:    Miles Simpson
*******************************************************************************/


/*******************************************************************************
   DEVICE INFO:
      VendorName:     Portland State Aerospace Society
      VendorNumber:   0
      ProductName:    OreSat C3
      ProductNumber:  0
*******************************************************************************/


/*******************************************************************************
   FEATURES
*******************************************************************************/
  #define CO_NO_SYNC                     1   //Associated objects: 1005-1007
  #define CO_NO_EMERGENCY                1   //Associated objects: 1014, 1015
  #define CO_NO_TIME                     0   //Associated objects: 1012, 1013
  #define CO_NO_SDO_SERVER               1   //Associated objects: 1200-127F
  #define CO_NO_SDO_CLIENT               1   //Associated objects: 1280-12FF
  #define CO_NO_GFC                      0   //Associated objects: 1300
  #define CO_NO_SRDO                     0   //Associated objects: 1301-1341, 1381-13C0
  #define CO_NO_LSS_SERVER               0   //LSS Slave
  #define CO_NO_LSS_CLIENT               0   //LSS Master
  #define CO_NO_RPDO                     28   //Associated objects: 14xx, 16xx
  #define CO_NO_TPDO                     16   //Associated objects: 18xx, 1Axx
  #define CO_NO_NMT_MASTER               1
  #define CO_NO_TRACE                    0


/*******************************************************************************
   OBJECT DICTIONARY
*******************************************************************************/
   #define CO_OD_NoOfElements             148


/*******************************************************************************
   TYPE DEFINITIONS FOR RECORDS
*******************************************************************************/
/*1018      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               UNSIGNED32     vendorID;
               UNSIGNED32     productCode;
               UNSIGNED32     revisionNumber;
               UNSIGNED32     serialNumber;
               }              OD_identity_t;
/*1200      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               UNSIGNED32     COB_IDClientToServer;
               UNSIGNED32     COB_IDServerToClient;
               }              OD_SDOServerParameter_t;
/*1280      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               UNSIGNED32     COB_IDClientToServer;
               UNSIGNED32     COB_IDServerToClient;
               UNSIGNED8      nodeIDOfTheSDOServer;
               }              OD_SDOClientParameter_t;
/*1400      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               UNSIGNED32     COB_IDUsedByRPDO;
               UNSIGNED8      transmissionType;
               }              OD_RPDOCommunicationParameter_t;
/*1600      */ typedef struct {
               UNSIGNED8      numberOfMappedObjects;
               UNSIGNED32     mappedObject1;
               UNSIGNED32     mappedObject2;
               UNSIGNED32     mappedObject3;
               UNSIGNED32     mappedObject4;
               UNSIGNED32     mappedObject5;
               UNSIGNED32     mappedObject6;
               UNSIGNED32     mappedObject7;
               UNSIGNED32     mappedObject8;
               }              OD_RPDOMappingParameter_t;
/*1800      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               UNSIGNED32     COB_IDUsedByTPDO;
               UNSIGNED8      transmissionType;
               UNSIGNED16     inhibitTime;
               UNSIGNED8      compatibilityEntry;
               UNSIGNED16     eventTimer;
               UNSIGNED8      SYNCStartValue;
               }              OD_TPDOCommunicationParameter_t;
/*1A00      */ typedef struct {
               UNSIGNED8      numberOfMappedObjects;
               UNSIGNED32     mappedObject1;
               UNSIGNED32     mappedObject2;
               UNSIGNED32     mappedObject3;
               UNSIGNED32     mappedObject4;
               UNSIGNED32     mappedObject5;
               UNSIGNED32     mappedObject6;
               UNSIGNED32     mappedObject7;
               UNSIGNED32     mappedObject8;
               }              OD_TPDOMappingParameter_t;
/*4002      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               INTEGER16      MCU_Temperature;
               INTEGER16      MCU_Voltage;
               }              OD_battery1_t;
/*4003      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               INTEGER16      MCU_Temperature;
               INTEGER16      MCU_Voltage;
               }              OD_battery2_t;
/*4004      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               INTEGER16      MCU_Temperature;
               INTEGER16      MCU_Voltage;
               UNSIGNED16     PV_Voltage;
               INTEGER16      PV_Current;
               UNSIGNED16     PV_Power;
               }              OD_solarPanel1_t;
/*4005      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               INTEGER16      MCU_Temperature;
               INTEGER16      MCU_Voltage;
               UNSIGNED16     PV_Voltage;
               INTEGER16      PV_Current;
               UNSIGNED16     PV_Power;
               }              OD_solarPanel2_t;
/*4006      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               INTEGER16      MCU_Temperature;
               INTEGER16      MCU_Voltage;
               UNSIGNED16     PV_Voltage;
               INTEGER16      PV_Current;
               UNSIGNED16     PV_Power;
               }              OD_solarPanel3_t;
/*4007      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               INTEGER16      MCU_Temperature;
               INTEGER16      MCU_Voltage;
               UNSIGNED16     PV_Voltage;
               INTEGER16      PV_Current;
               UNSIGNED16     PV_Power;
               }              OD_solarPanel4_t;
/*4008      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               INTEGER16      MCU_Temperature;
               INTEGER16      MCU_Voltage;
               UNSIGNED16     PV_Voltage;
               INTEGER16      PV_Current;
               UNSIGNED16     PV_Power;
               }              OD_solarPanel5_t;
/*4009      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               INTEGER16      MCU_Temperature;
               INTEGER16      MCU_Voltage;
               UNSIGNED16     PV_Voltage;
               INTEGER16      PV_Current;
               UNSIGNED16     PV_Power;
               }              OD_solarPanel6_t;
/*400A      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               INTEGER16      MCU_Temperature;
               INTEGER16      MCU_Voltage;
               UNSIGNED16     PV_Voltage;
               INTEGER16      PV_Current;
               UNSIGNED16     PV_Power;
               }              OD_solarPanel7_t;
/*400B      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               INTEGER16      MCU_Temperature;
               INTEGER16      MCU_Voltage;
               UNSIGNED16     PV_Voltage;
               INTEGER16      PV_Current;
               UNSIGNED16     PV_Power;
               }              OD_solarPanel8_t;
/*4011      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               }              OD_starTracker_t;
/*4012      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               }              OD_GPS_t;
/*4013      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               INTEGER16      MCU_Temperature;
               INTEGER16      MCU_Voltage;
               }              OD_IMU_t;
/*4014      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               INTEGER16      MCU_Temperature;
               INTEGER16      MCU_Voltage;
               }              OD_magnetometer1_t;
/*4015      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               INTEGER16      MCU_Temperature;
               INTEGER16      MCU_Voltage;
               }              OD_magnetometer2_t;
/*4016      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               INTEGER16      MCU_Temperature;
               INTEGER16      MCU_Voltage;
               }              OD_RW_MT1_t;
/*4017      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               INTEGER16      MCU_Temperature;
               INTEGER16      MCU_Voltage;
               }              OD_RW_MT2_t;
/*4018      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               INTEGER16      MCU_Temperature;
               INTEGER16      MCU_Voltage;
               }              OD_RW_MT3_t;
/*4019      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               INTEGER16      MCU_Temperature;
               INTEGER16      MCU_Voltage;
               }              OD_RW4_t;
/*4021      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               }              OD_oreSatLive_t;
/*4022      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               }              OD_CFC_t;
/*4031      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               INTEGER16      MCU_Temperature;
               INTEGER16      MCU_Voltage;
               }              OD_protocard1_t;
/*4032      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               INTEGER16      MCU_Temperature;
               INTEGER16      MCU_Voltage;
               }              OD_protocard2_t;
/*4033      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               INTEGER16      MCU_Temperature;
               INTEGER16      MCU_Voltage;
               }              OD_protocard3_t;

/*******************************************************************************
   TYPE DEFINITIONS FOR OBJECT DICTIONARY INDEXES

   some of those are redundant with CO_SDO.h CO_ObjDicId_t <Common CiA301 object
   dictionary entries>
*******************************************************************************/
/*1000 */
        #define OD_1000_deviceType                                  0x1000

/*1001 */
        #define OD_1001_errorRegister                               0x1001

/*1002 */
        #define OD_1002_manufacturerStatusRegister                  0x1002

/*1003 */
        #define OD_1003_preDefinedErrorField                        0x1003

        #define OD_1003_0_preDefinedErrorField_maxSubIndex          0
        #define OD_1003_1_preDefinedErrorField_standardErrorField   1
        #define OD_1003_2_preDefinedErrorField_standardErrorField   2
        #define OD_1003_3_preDefinedErrorField_standardErrorField   3
        #define OD_1003_4_preDefinedErrorField_standardErrorField   4
        #define OD_1003_5_preDefinedErrorField_standardErrorField   5
        #define OD_1003_6_preDefinedErrorField_standardErrorField   6
        #define OD_1003_7_preDefinedErrorField_standardErrorField   7
        #define OD_1003_8_preDefinedErrorField_standardErrorField   8

/*1005 */
        #define OD_1005_COB_ID_SYNCMessage                          0x1005

/*1006 */
        #define OD_1006_communicationCyclePeriod                    0x1006

/*1007 */
        #define OD_1007_synchronousWindowLength                     0x1007

/*1008 */
        #define OD_1008_manufacturerDeviceName                      0x1008

/*1009 */
        #define OD_1009_manufacturerHardwareVersion                 0x1009

/*100A */
        #define OD_100A_manufacturerSoftwareVersion                 0x100A

/*1010 */
        #define OD_1010_storeParameters                             0x1010

        #define OD_1010_0_storeParameters_maxSubIndex               0
        #define OD_1010_1_storeParameters_saveAllParameters         1

/*1011 */
        #define OD_1011_restoreDefaultParameters                    0x1011

        #define OD_1011_0_restoreDefaultParameters_maxSubIndex      0
        #define OD_1011_1_restoreDefaultParameters_restoreAllDefaultParameters 1

/*1014 */
        #define OD_1014_COB_ID_EMCY                                 0x1014

/*1015 */
        #define OD_1015_inhibitTimeEMCY                             0x1015

/*1016 */
        #define OD_1016_consumerHeartbeatTime                       0x1016

        #define OD_1016_0_consumerHeartbeatTime_maxSubIndex         0
        #define OD_1016_1_consumerHeartbeatTime_consumerHeartbeatTime 1
        #define OD_1016_2_consumerHeartbeatTime_consumerHeartbeatTime 2
        #define OD_1016_3_consumerHeartbeatTime_consumerHeartbeatTime 3
        #define OD_1016_4_consumerHeartbeatTime_consumerHeartbeatTime 4

/*1017 */
        #define OD_1017_producerHeartbeatTime                       0x1017

/*1018 */
        #define OD_1018_identity                                    0x1018

        #define OD_1018_0_identity_maxSubIndex                      0
        #define OD_1018_1_identity_vendorID                         1
        #define OD_1018_2_identity_productCode                      2
        #define OD_1018_3_identity_revisionNumber                   3
        #define OD_1018_4_identity_serialNumber                     4

/*1019 */
        #define OD_1019_synchronousCounterOverflowValue             0x1019

/*1029 */
        #define OD_1029_errorBehavior                               0x1029

        #define OD_1029_0_errorBehavior_maxSubIndex                 0
        #define OD_1029_1_errorBehavior_communication               1
        #define OD_1029_2_errorBehavior_communicationOther          2
        #define OD_1029_3_errorBehavior_communicationPassive        3
        #define OD_1029_4_errorBehavior_generic                     4
        #define OD_1029_5_errorBehavior_deviceProfile               5
        #define OD_1029_6_errorBehavior_manufacturerSpecific        6

/*1200 */
        #define OD_1200_SDOServerParameter                          0x1200

        #define OD_1200_0_SDOServerParameter_maxSubIndex            0
        #define OD_1200_1_SDOServerParameter_COB_IDClientToServer   1
        #define OD_1200_2_SDOServerParameter_COB_IDServerToClient   2

/*1280 */
        #define OD_1280_SDOClientParameter                          0x1280

        #define OD_1280_0_SDOClientParameter_maxSubIndex            0
        #define OD_1280_1_SDOClientParameter_COB_IDClientToServer   1
        #define OD_1280_2_SDOClientParameter_COB_IDServerToClient   2
        #define OD_1280_3_SDOClientParameter_nodeIDOfTheSDOServer   3

/*1400 */
        #define OD_1400_RPDOCommunicationParameter                  0x1400

        #define OD_1400_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1400_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1400_2_RPDOCommunicationParameter_transmissionType 2

/*1401 */
        #define OD_1401_RPDOCommunicationParameter                  0x1401

        #define OD_1401_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1401_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1401_2_RPDOCommunicationParameter_transmissionType 2

/*1402 */
        #define OD_1402_RPDOCommunicationParameter                  0x1402

        #define OD_1402_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1402_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1402_2_RPDOCommunicationParameter_transmissionType 2

/*1403 */
        #define OD_1403_RPDOCommunicationParameter                  0x1403

        #define OD_1403_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1403_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1403_2_RPDOCommunicationParameter_transmissionType 2

/*1404 */
        #define OD_1404_RPDOCommunicationParameter                  0x1404

        #define OD_1404_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1404_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1404_2_RPDOCommunicationParameter_transmissionType 2

/*1405 */
        #define OD_1405_RPDOCommunicationParameter                  0x1405

        #define OD_1405_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1405_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1405_2_RPDOCommunicationParameter_transmissionType 2

/*1406 */
        #define OD_1406_RPDOCommunicationParameter                  0x1406

        #define OD_1406_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1406_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1406_2_RPDOCommunicationParameter_transmissionType 2

/*1407 */
        #define OD_1407_RPDOCommunicationParameter                  0x1407

        #define OD_1407_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1407_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1407_2_RPDOCommunicationParameter_transmissionType 2

/*1408 */
        #define OD_1408_RPDOCommunicationParameter                  0x1408

        #define OD_1408_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1408_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1408_2_RPDOCommunicationParameter_transmissionType 2

/*1409 */
        #define OD_1409_RPDOCommunicationParameter                  0x1409

        #define OD_1409_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1409_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1409_2_RPDOCommunicationParameter_transmissionType 2

/*140A */
        #define OD_140A_RPDOCommunicationParameter                  0x140A

        #define OD_140A_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_140A_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_140A_2_RPDOCommunicationParameter_transmissionType 2

/*140B */
        #define OD_140B_RPDOCommunicationParameter                  0x140B

        #define OD_140B_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_140B_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_140B_2_RPDOCommunicationParameter_transmissionType 2

/*140C */
        #define OD_140C_RPDOCommunicationParameter                  0x140C

        #define OD_140C_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_140C_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_140C_2_RPDOCommunicationParameter_transmissionType 2

/*140D */
        #define OD_140D_RPDOCommunicationParameter                  0x140D

        #define OD_140D_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_140D_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_140D_2_RPDOCommunicationParameter_transmissionType 2

/*140E */
        #define OD_140E_RPDOCommunicationParameter                  0x140E

        #define OD_140E_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_140E_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_140E_2_RPDOCommunicationParameter_transmissionType 2

/*140F */
        #define OD_140F_RPDOCommunicationParameter                  0x140F

        #define OD_140F_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_140F_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_140F_2_RPDOCommunicationParameter_transmissionType 2

/*1410 */
        #define OD_1410_RPDOCommunicationParameter                  0x1410

        #define OD_1410_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1410_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1410_2_RPDOCommunicationParameter_transmissionType 2

/*1411 */
        #define OD_1411_RPDOCommunicationParameter                  0x1411

        #define OD_1411_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1411_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1411_2_RPDOCommunicationParameter_transmissionType 2

/*1412 */
        #define OD_1412_RPDOCommunicationParameter                  0x1412

        #define OD_1412_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1412_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1412_2_RPDOCommunicationParameter_transmissionType 2

/*1413 */
        #define OD_1413_RPDOCommunicationParameter                  0x1413

        #define OD_1413_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1413_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1413_2_RPDOCommunicationParameter_transmissionType 2

/*1414 */
        #define OD_1414_RPDOCommunicationParameter                  0x1414

        #define OD_1414_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1414_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1414_2_RPDOCommunicationParameter_transmissionType 2

/*1415 */
        #define OD_1415_RPDOCommunicationParameter                  0x1415

        #define OD_1415_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1415_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1415_2_RPDOCommunicationParameter_transmissionType 2

/*1416 */
        #define OD_1416_RPDOCommunicationParameter                  0x1416

        #define OD_1416_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1416_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1416_2_RPDOCommunicationParameter_transmissionType 2

/*1417 */
        #define OD_1417_RPDOCommunicationParameter                  0x1417

        #define OD_1417_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1417_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1417_2_RPDOCommunicationParameter_transmissionType 2

/*1418 */
        #define OD_1418_RPDOCommunicationParameter                  0x1418

        #define OD_1418_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1418_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1418_2_RPDOCommunicationParameter_transmissionType 2

/*1419 */
        #define OD_1419_RPDOCommunicationParameter                  0x1419

        #define OD_1419_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1419_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1419_2_RPDOCommunicationParameter_transmissionType 2

/*141A */
        #define OD_141A_RPDOCommunicationParameter                  0x141A

        #define OD_141A_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_141A_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_141A_2_RPDOCommunicationParameter_transmissionType 2

/*141B */
        #define OD_141B_RPDOCommunicationParameter                  0x141B

        #define OD_141B_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_141B_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_141B_2_RPDOCommunicationParameter_transmissionType 2

/*1600 */
        #define OD_1600_RPDOMappingParameter                        0x1600

        #define OD_1600_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1600_1_RPDOMappingParameter_mappedObject1        1
        #define OD_1600_2_RPDOMappingParameter_mappedObject2        2
        #define OD_1600_3_RPDOMappingParameter_mappedObject3        3
        #define OD_1600_4_RPDOMappingParameter_mappedObject4        4
        #define OD_1600_5_RPDOMappingParameter_mappedObject5        5
        #define OD_1600_6_RPDOMappingParameter_mappedObject6        6
        #define OD_1600_7_RPDOMappingParameter_mappedObject7        7
        #define OD_1600_8_RPDOMappingParameter_mappedObject8        8

/*1601 */
        #define OD_1601_RPDOMappingParameter                        0x1601

        #define OD_1601_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1601_1_RPDOMappingParameter_mappedObject1        1
        #define OD_1601_2_RPDOMappingParameter_mappedObject2        2
        #define OD_1601_3_RPDOMappingParameter_mappedObject3        3
        #define OD_1601_4_RPDOMappingParameter_mappedObject4        4
        #define OD_1601_5_RPDOMappingParameter_mappedObject5        5
        #define OD_1601_6_RPDOMappingParameter_mappedObject6        6
        #define OD_1601_7_RPDOMappingParameter_mappedObject7        7
        #define OD_1601_8_RPDOMappingParameter_mappedObject8        8

/*1602 */
        #define OD_1602_RPDOMappingParameter                        0x1602

        #define OD_1602_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1602_1_RPDOMappingParameter_mappedObject1        1
        #define OD_1602_2_RPDOMappingParameter_mappedObject2        2
        #define OD_1602_3_RPDOMappingParameter_mappedObject3        3
        #define OD_1602_4_RPDOMappingParameter_mappedObject4        4
        #define OD_1602_5_RPDOMappingParameter_mappedObject5        5
        #define OD_1602_6_RPDOMappingParameter_mappedObject6        6
        #define OD_1602_7_RPDOMappingParameter_mappedObject7        7
        #define OD_1602_8_RPDOMappingParameter_mappedObject8        8

/*1603 */
        #define OD_1603_RPDOMappingParameter                        0x1603

        #define OD_1603_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1603_1_RPDOMappingParameter_mappedObject1        1
        #define OD_1603_2_RPDOMappingParameter_mappedObject2        2
        #define OD_1603_3_RPDOMappingParameter_mappedObject3        3
        #define OD_1603_4_RPDOMappingParameter_mappedObject4        4
        #define OD_1603_5_RPDOMappingParameter_mappedObject5        5
        #define OD_1603_6_RPDOMappingParameter_mappedObject6        6
        #define OD_1603_7_RPDOMappingParameter_mappedObject7        7
        #define OD_1603_8_RPDOMappingParameter_mappedObject8        8

/*1604 */
        #define OD_1604_RPDOMappingParameter                        0x1604

        #define OD_1604_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1604_1_RPDOMappingParameter_mappedObject1        1
        #define OD_1604_2_RPDOMappingParameter_mappedObject2        2
        #define OD_1604_3_RPDOMappingParameter_mappedObject3        3
        #define OD_1604_4_RPDOMappingParameter_mappedObject4        4
        #define OD_1604_5_RPDOMappingParameter_mappedObject5        5
        #define OD_1604_6_RPDOMappingParameter_mappedObject6        6
        #define OD_1604_7_RPDOMappingParameter_mappedObject7        7
        #define OD_1604_8_RPDOMappingParameter_mappedObject8        8

/*1605 */
        #define OD_1605_RPDOMappingParameter                        0x1605

        #define OD_1605_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1605_1_RPDOMappingParameter_mappedObject1        1
        #define OD_1605_2_RPDOMappingParameter_mappedObject2        2
        #define OD_1605_3_RPDOMappingParameter_mappedObject3        3
        #define OD_1605_4_RPDOMappingParameter_mappedObject4        4
        #define OD_1605_5_RPDOMappingParameter_mappedObject5        5
        #define OD_1605_6_RPDOMappingParameter_mappedObject6        6
        #define OD_1605_7_RPDOMappingParameter_mappedObject7        7
        #define OD_1605_8_RPDOMappingParameter_mappedObject8        8

/*1606 */
        #define OD_1606_RPDOMappingParameter                        0x1606

        #define OD_1606_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1606_1_RPDOMappingParameter_mappedObject1        1
        #define OD_1606_2_RPDOMappingParameter_mappedObject2        2
        #define OD_1606_3_RPDOMappingParameter_mappedObject3        3
        #define OD_1606_4_RPDOMappingParameter_mappedObject4        4
        #define OD_1606_5_RPDOMappingParameter_mappedObject5        5
        #define OD_1606_6_RPDOMappingParameter_mappedObject6        6
        #define OD_1606_7_RPDOMappingParameter_mappedObject7        7
        #define OD_1606_8_RPDOMappingParameter_mappedObject8        8

/*1607 */
        #define OD_1607_RPDOMappingParameter                        0x1607

        #define OD_1607_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1607_1_RPDOMappingParameter_mappedObject1        1
        #define OD_1607_2_RPDOMappingParameter_mappedObject2        2
        #define OD_1607_3_RPDOMappingParameter_mappedObject3        3
        #define OD_1607_4_RPDOMappingParameter_mappedObject4        4
        #define OD_1607_5_RPDOMappingParameter_mappedObject5        5
        #define OD_1607_6_RPDOMappingParameter_mappedObject6        6
        #define OD_1607_7_RPDOMappingParameter_mappedObject7        7
        #define OD_1607_8_RPDOMappingParameter_mappedObject8        8

/*1608 */
        #define OD_1608_RPDOMappingParameter                        0x1608

        #define OD_1608_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1608_1_RPDOMappingParameter_mappedObject1        1
        #define OD_1608_2_RPDOMappingParameter_mappedObject2        2
        #define OD_1608_3_RPDOMappingParameter_mappedObject3        3
        #define OD_1608_4_RPDOMappingParameter_mappedObject4        4
        #define OD_1608_5_RPDOMappingParameter_mappedObject5        5
        #define OD_1608_6_RPDOMappingParameter_mappedObject6        6
        #define OD_1608_7_RPDOMappingParameter_mappedObject7        7
        #define OD_1608_8_RPDOMappingParameter_mappedObject8        8

/*1609 */
        #define OD_1609_RPDOMappingParameter                        0x1609

        #define OD_1609_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1609_1_RPDOMappingParameter_mappedObject1        1
        #define OD_1609_2_RPDOMappingParameter_mappedObject2        2
        #define OD_1609_3_RPDOMappingParameter_mappedObject3        3
        #define OD_1609_4_RPDOMappingParameter_mappedObject4        4
        #define OD_1609_5_RPDOMappingParameter_mappedObject5        5
        #define OD_1609_6_RPDOMappingParameter_mappedObject6        6
        #define OD_1609_7_RPDOMappingParameter_mappedObject7        7
        #define OD_1609_8_RPDOMappingParameter_mappedObject8        8

/*160A */
        #define OD_160A_RPDOMappingParameter                        0x160A

        #define OD_160A_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_160A_1_RPDOMappingParameter_mappedObject1        1
        #define OD_160A_2_RPDOMappingParameter_mappedObject2        2
        #define OD_160A_3_RPDOMappingParameter_mappedObject3        3
        #define OD_160A_4_RPDOMappingParameter_mappedObject4        4
        #define OD_160A_5_RPDOMappingParameter_mappedObject5        5
        #define OD_160A_6_RPDOMappingParameter_mappedObject6        6
        #define OD_160A_7_RPDOMappingParameter_mappedObject7        7
        #define OD_160A_8_RPDOMappingParameter_mappedObject8        8

/*160B */
        #define OD_160B_RPDOMappingParameter                        0x160B

        #define OD_160B_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_160B_1_RPDOMappingParameter_mappedObject1        1
        #define OD_160B_2_RPDOMappingParameter_mappedObject2        2
        #define OD_160B_3_RPDOMappingParameter_mappedObject3        3
        #define OD_160B_4_RPDOMappingParameter_mappedObject4        4
        #define OD_160B_5_RPDOMappingParameter_mappedObject5        5
        #define OD_160B_6_RPDOMappingParameter_mappedObject6        6
        #define OD_160B_7_RPDOMappingParameter_mappedObject7        7
        #define OD_160B_8_RPDOMappingParameter_mappedObject8        8

/*160C */
        #define OD_160C_RPDOMappingParameter                        0x160C

        #define OD_160C_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_160C_1_RPDOMappingParameter_mappedObject1        1
        #define OD_160C_2_RPDOMappingParameter_mappedObject2        2
        #define OD_160C_3_RPDOMappingParameter_mappedObject3        3
        #define OD_160C_4_RPDOMappingParameter_mappedObject4        4
        #define OD_160C_5_RPDOMappingParameter_mappedObject5        5
        #define OD_160C_6_RPDOMappingParameter_mappedObject6        6
        #define OD_160C_7_RPDOMappingParameter_mappedObject7        7
        #define OD_160C_8_RPDOMappingParameter_mappedObject8        8

/*160D */
        #define OD_160D_RPDOMappingParameter                        0x160D

        #define OD_160D_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_160D_1_RPDOMappingParameter_mappedObject1        1
        #define OD_160D_2_RPDOMappingParameter_mappedObject2        2
        #define OD_160D_3_RPDOMappingParameter_mappedObject3        3
        #define OD_160D_4_RPDOMappingParameter_mappedObject4        4
        #define OD_160D_5_RPDOMappingParameter_mappedObject5        5
        #define OD_160D_6_RPDOMappingParameter_mappedObject6        6
        #define OD_160D_7_RPDOMappingParameter_mappedObject7        7
        #define OD_160D_8_RPDOMappingParameter_mappedObject8        8

/*160E */
        #define OD_160E_RPDOMappingParameter                        0x160E

        #define OD_160E_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_160E_1_RPDOMappingParameter_mappedObject1        1
        #define OD_160E_2_RPDOMappingParameter_mappedObject2        2
        #define OD_160E_3_RPDOMappingParameter_mappedObject3        3
        #define OD_160E_4_RPDOMappingParameter_mappedObject4        4
        #define OD_160E_5_RPDOMappingParameter_mappedObject5        5
        #define OD_160E_6_RPDOMappingParameter_mappedObject6        6
        #define OD_160E_7_RPDOMappingParameter_mappedObject7        7
        #define OD_160E_8_RPDOMappingParameter_mappedObject8        8

/*160F */
        #define OD_160F_RPDOMappingParameter                        0x160F

        #define OD_160F_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_160F_1_RPDOMappingParameter_mappedObject1        1
        #define OD_160F_2_RPDOMappingParameter_mappedObject2        2
        #define OD_160F_3_RPDOMappingParameter_mappedObject3        3
        #define OD_160F_4_RPDOMappingParameter_mappedObject4        4
        #define OD_160F_5_RPDOMappingParameter_mappedObject5        5
        #define OD_160F_6_RPDOMappingParameter_mappedObject6        6
        #define OD_160F_7_RPDOMappingParameter_mappedObject7        7
        #define OD_160F_8_RPDOMappingParameter_mappedObject8        8

/*1610 */
        #define OD_1610_RPDOMappingParameter                        0x1610

        #define OD_1610_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1610_1_RPDOMappingParameter_mappedObject1        1
        #define OD_1610_2_RPDOMappingParameter_mappedObject2        2
        #define OD_1610_3_RPDOMappingParameter_mappedObject3        3
        #define OD_1610_4_RPDOMappingParameter_mappedObject4        4
        #define OD_1610_5_RPDOMappingParameter_mappedObject5        5
        #define OD_1610_6_RPDOMappingParameter_mappedObject6        6
        #define OD_1610_7_RPDOMappingParameter_mappedObject7        7
        #define OD_1610_8_RPDOMappingParameter_mappedObject8        8

/*1611 */
        #define OD_1611_RPDOMappingParameter                        0x1611

        #define OD_1611_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1611_1_RPDOMappingParameter_mappedObject1        1
        #define OD_1611_2_RPDOMappingParameter_mappedObject2        2
        #define OD_1611_3_RPDOMappingParameter_mappedObject3        3
        #define OD_1611_4_RPDOMappingParameter_mappedObject4        4
        #define OD_1611_5_RPDOMappingParameter_mappedObject5        5
        #define OD_1611_6_RPDOMappingParameter_mappedObject6        6
        #define OD_1611_7_RPDOMappingParameter_mappedObject7        7
        #define OD_1611_8_RPDOMappingParameter_mappedObject8        8

/*1612 */
        #define OD_1612_RPDOMappingParameter                        0x1612

        #define OD_1612_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1612_1_RPDOMappingParameter_mappedObject1        1
        #define OD_1612_2_RPDOMappingParameter_mappedObject2        2
        #define OD_1612_3_RPDOMappingParameter_mappedObject3        3
        #define OD_1612_4_RPDOMappingParameter_mappedObject4        4
        #define OD_1612_5_RPDOMappingParameter_mappedObject5        5
        #define OD_1612_6_RPDOMappingParameter_mappedObject6        6
        #define OD_1612_7_RPDOMappingParameter_mappedObject7        7
        #define OD_1612_8_RPDOMappingParameter_mappedObject8        8

/*1613 */
        #define OD_1613_RPDOMappingParameter                        0x1613

        #define OD_1613_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1613_1_RPDOMappingParameter_mappedObject1        1
        #define OD_1613_2_RPDOMappingParameter_mappedObject2        2
        #define OD_1613_3_RPDOMappingParameter_mappedObject3        3
        #define OD_1613_4_RPDOMappingParameter_mappedObject4        4
        #define OD_1613_5_RPDOMappingParameter_mappedObject5        5
        #define OD_1613_6_RPDOMappingParameter_mappedObject6        6
        #define OD_1613_7_RPDOMappingParameter_mappedObject7        7
        #define OD_1613_8_RPDOMappingParameter_mappedObject8        8

/*1614 */
        #define OD_1614_RPDOMappingParameter                        0x1614

        #define OD_1614_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1614_1_RPDOMappingParameter_mappedObject1        1
        #define OD_1614_2_RPDOMappingParameter_mappedObject2        2
        #define OD_1614_3_RPDOMappingParameter_mappedObject3        3
        #define OD_1614_4_RPDOMappingParameter_mappedObject4        4
        #define OD_1614_5_RPDOMappingParameter_mappedObject5        5
        #define OD_1614_6_RPDOMappingParameter_mappedObject6        6
        #define OD_1614_7_RPDOMappingParameter_mappedObject7        7
        #define OD_1614_8_RPDOMappingParameter_mappedObject8        8

/*1615 */
        #define OD_1615_RPDOMappingParameter                        0x1615

        #define OD_1615_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1615_1_RPDOMappingParameter_mappedObject1        1
        #define OD_1615_2_RPDOMappingParameter_mappedObject2        2
        #define OD_1615_3_RPDOMappingParameter_mappedObject3        3
        #define OD_1615_4_RPDOMappingParameter_mappedObject4        4
        #define OD_1615_5_RPDOMappingParameter_mappedObject5        5
        #define OD_1615_6_RPDOMappingParameter_mappedObject6        6
        #define OD_1615_7_RPDOMappingParameter_mappedObject7        7
        #define OD_1615_8_RPDOMappingParameter_mappedObject8        8

/*1616 */
        #define OD_1616_RPDOMappingParameter                        0x1616

        #define OD_1616_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1616_1_RPDOMappingParameter_mappedObject1        1
        #define OD_1616_2_RPDOMappingParameter_mappedObject2        2
        #define OD_1616_3_RPDOMappingParameter_mappedObject3        3
        #define OD_1616_4_RPDOMappingParameter_mappedObject4        4
        #define OD_1616_5_RPDOMappingParameter_mappedObject5        5
        #define OD_1616_6_RPDOMappingParameter_mappedObject6        6
        #define OD_1616_7_RPDOMappingParameter_mappedObject7        7
        #define OD_1616_8_RPDOMappingParameter_mappedObject8        8

/*1617 */
        #define OD_1617_RPDOMappingParameter                        0x1617

        #define OD_1617_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1617_1_RPDOMappingParameter_mappedObject1        1
        #define OD_1617_2_RPDOMappingParameter_mappedObject2        2
        #define OD_1617_3_RPDOMappingParameter_mappedObject3        3
        #define OD_1617_4_RPDOMappingParameter_mappedObject4        4
        #define OD_1617_5_RPDOMappingParameter_mappedObject5        5
        #define OD_1617_6_RPDOMappingParameter_mappedObject6        6
        #define OD_1617_7_RPDOMappingParameter_mappedObject7        7
        #define OD_1617_8_RPDOMappingParameter_mappedObject8        8

/*1618 */
        #define OD_1618_RPDOMappingParameter                        0x1618

        #define OD_1618_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1618_1_RPDOMappingParameter_mappedObject1        1
        #define OD_1618_2_RPDOMappingParameter_mappedObject2        2
        #define OD_1618_3_RPDOMappingParameter_mappedObject3        3
        #define OD_1618_4_RPDOMappingParameter_mappedObject4        4
        #define OD_1618_5_RPDOMappingParameter_mappedObject5        5
        #define OD_1618_6_RPDOMappingParameter_mappedObject6        6
        #define OD_1618_7_RPDOMappingParameter_mappedObject7        7
        #define OD_1618_8_RPDOMappingParameter_mappedObject8        8

/*1619 */
        #define OD_1619_RPDOMappingParameter                        0x1619

        #define OD_1619_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1619_1_RPDOMappingParameter_mappedObject1        1
        #define OD_1619_2_RPDOMappingParameter_mappedObject2        2
        #define OD_1619_3_RPDOMappingParameter_mappedObject3        3
        #define OD_1619_4_RPDOMappingParameter_mappedObject4        4
        #define OD_1619_5_RPDOMappingParameter_mappedObject5        5
        #define OD_1619_6_RPDOMappingParameter_mappedObject6        6
        #define OD_1619_7_RPDOMappingParameter_mappedObject7        7
        #define OD_1619_8_RPDOMappingParameter_mappedObject8        8

/*161A */
        #define OD_161A_RPDOMappingParameter                        0x161A

        #define OD_161A_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_161A_1_RPDOMappingParameter_mappedObject1        1
        #define OD_161A_2_RPDOMappingParameter_mappedObject2        2
        #define OD_161A_3_RPDOMappingParameter_mappedObject3        3
        #define OD_161A_4_RPDOMappingParameter_mappedObject4        4
        #define OD_161A_5_RPDOMappingParameter_mappedObject5        5
        #define OD_161A_6_RPDOMappingParameter_mappedObject6        6
        #define OD_161A_7_RPDOMappingParameter_mappedObject7        7
        #define OD_161A_8_RPDOMappingParameter_mappedObject8        8

/*161B */
        #define OD_161B_RPDOMappingParameter                        0x161B

        #define OD_161B_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_161B_1_RPDOMappingParameter_mappedObject1        1
        #define OD_161B_2_RPDOMappingParameter_mappedObject2        2
        #define OD_161B_3_RPDOMappingParameter_mappedObject3        3
        #define OD_161B_4_RPDOMappingParameter_mappedObject4        4
        #define OD_161B_5_RPDOMappingParameter_mappedObject5        5
        #define OD_161B_6_RPDOMappingParameter_mappedObject6        6
        #define OD_161B_7_RPDOMappingParameter_mappedObject7        7
        #define OD_161B_8_RPDOMappingParameter_mappedObject8        8

/*1800 */
        #define OD_1800_TPDOCommunicationParameter                  0x1800

        #define OD_1800_0_TPDOCommunicationParameter_maxSubIndex    0
        #define OD_1800_1_TPDOCommunicationParameter_COB_IDUsedByTPDO 1
        #define OD_1800_2_TPDOCommunicationParameter_transmissionType 2
        #define OD_1800_3_TPDOCommunicationParameter_inhibitTime    3
        #define OD_1800_4_TPDOCommunicationParameter_compatibilityEntry 4
        #define OD_1800_5_TPDOCommunicationParameter_eventTimer     5
        #define OD_1800_6_TPDOCommunicationParameter_SYNCStartValue 6

/*1801 */
        #define OD_1801_TPDOCommunicationParameter                  0x1801

        #define OD_1801_0_TPDOCommunicationParameter_maxSubIndex    0
        #define OD_1801_1_TPDOCommunicationParameter_COB_IDUsedByTPDO 1
        #define OD_1801_2_TPDOCommunicationParameter_transmissionType 2
        #define OD_1801_3_TPDOCommunicationParameter_inhibitTime    3
        #define OD_1801_4_TPDOCommunicationParameter_compatibilityEntry 4
        #define OD_1801_5_TPDOCommunicationParameter_eventTimer     5
        #define OD_1801_6_TPDOCommunicationParameter_SYNCStartValue 6

/*1802 */
        #define OD_1802_TPDOCommunicationParameter                  0x1802

        #define OD_1802_0_TPDOCommunicationParameter_maxSubIndex    0
        #define OD_1802_1_TPDOCommunicationParameter_COB_IDUsedByTPDO 1
        #define OD_1802_2_TPDOCommunicationParameter_transmissionType 2
        #define OD_1802_3_TPDOCommunicationParameter_inhibitTime    3
        #define OD_1802_4_TPDOCommunicationParameter_compatibilityEntry 4
        #define OD_1802_5_TPDOCommunicationParameter_eventTimer     5
        #define OD_1802_6_TPDOCommunicationParameter_SYNCStartValue 6

/*1803 */
        #define OD_1803_TPDOCommunicationParameter                  0x1803

        #define OD_1803_0_TPDOCommunicationParameter_maxSubIndex    0
        #define OD_1803_1_TPDOCommunicationParameter_COB_IDUsedByTPDO 1
        #define OD_1803_2_TPDOCommunicationParameter_transmissionType 2
        #define OD_1803_3_TPDOCommunicationParameter_inhibitTime    3
        #define OD_1803_4_TPDOCommunicationParameter_compatibilityEntry 4
        #define OD_1803_5_TPDOCommunicationParameter_eventTimer     5
        #define OD_1803_6_TPDOCommunicationParameter_SYNCStartValue 6

/*1804 */
        #define OD_1804_TPDOCommunicationParameter                  0x1804

        #define OD_1804_0_TPDOCommunicationParameter_maxSubIndex    0
        #define OD_1804_1_TPDOCommunicationParameter_COB_IDUsedByTPDO 1
        #define OD_1804_2_TPDOCommunicationParameter_transmissionType 2
        #define OD_1804_3_TPDOCommunicationParameter_inhibitTime    3
        #define OD_1804_4_TPDOCommunicationParameter_compatibilityEntry 4
        #define OD_1804_5_TPDOCommunicationParameter_eventTimer     5
        #define OD_1804_6_TPDOCommunicationParameter_SYNCStartValue 6

/*1805 */
        #define OD_1805_TPDOCommunicationParameter                  0x1805

        #define OD_1805_0_TPDOCommunicationParameter_maxSubIndex    0
        #define OD_1805_1_TPDOCommunicationParameter_COB_IDUsedByTPDO 1
        #define OD_1805_2_TPDOCommunicationParameter_transmissionType 2
        #define OD_1805_3_TPDOCommunicationParameter_inhibitTime    3
        #define OD_1805_4_TPDOCommunicationParameter_compatibilityEntry 4
        #define OD_1805_5_TPDOCommunicationParameter_eventTimer     5
        #define OD_1805_6_TPDOCommunicationParameter_SYNCStartValue 6

/*1806 */
        #define OD_1806_TPDOCommunicationParameter                  0x1806

        #define OD_1806_0_TPDOCommunicationParameter_maxSubIndex    0
        #define OD_1806_1_TPDOCommunicationParameter_COB_IDUsedByTPDO 1
        #define OD_1806_2_TPDOCommunicationParameter_transmissionType 2
        #define OD_1806_3_TPDOCommunicationParameter_inhibitTime    3
        #define OD_1806_4_TPDOCommunicationParameter_compatibilityEntry 4
        #define OD_1806_5_TPDOCommunicationParameter_eventTimer     5
        #define OD_1806_6_TPDOCommunicationParameter_SYNCStartValue 6

/*1807 */
        #define OD_1807_TPDOCommunicationParameter                  0x1807

        #define OD_1807_0_TPDOCommunicationParameter_maxSubIndex    0
        #define OD_1807_1_TPDOCommunicationParameter_COB_IDUsedByTPDO 1
        #define OD_1807_2_TPDOCommunicationParameter_transmissionType 2
        #define OD_1807_3_TPDOCommunicationParameter_inhibitTime    3
        #define OD_1807_4_TPDOCommunicationParameter_compatibilityEntry 4
        #define OD_1807_5_TPDOCommunicationParameter_eventTimer     5
        #define OD_1807_6_TPDOCommunicationParameter_SYNCStartValue 6

/*1808 */
        #define OD_1808_TPDOCommunicationParameter                  0x1808

        #define OD_1808_0_TPDOCommunicationParameter_maxSubIndex    0
        #define OD_1808_1_TPDOCommunicationParameter_COB_IDUsedByTPDO 1
        #define OD_1808_2_TPDOCommunicationParameter_transmissionType 2
        #define OD_1808_3_TPDOCommunicationParameter_inhibitTime    3
        #define OD_1808_4_TPDOCommunicationParameter_compatibilityEntry 4
        #define OD_1808_5_TPDOCommunicationParameter_eventTimer     5
        #define OD_1808_6_TPDOCommunicationParameter_SYNCStartValue 6

/*1809 */
        #define OD_1809_TPDOCommunicationParameter                  0x1809

        #define OD_1809_0_TPDOCommunicationParameter_maxSubIndex    0
        #define OD_1809_1_TPDOCommunicationParameter_COB_IDUsedByTPDO 1
        #define OD_1809_2_TPDOCommunicationParameter_transmissionType 2
        #define OD_1809_3_TPDOCommunicationParameter_inhibitTime    3
        #define OD_1809_4_TPDOCommunicationParameter_compatibilityEntry 4
        #define OD_1809_5_TPDOCommunicationParameter_eventTimer     5
        #define OD_1809_6_TPDOCommunicationParameter_SYNCStartValue 6

/*180A */
        #define OD_180A_TPDOCommunicationParameter                  0x180A

        #define OD_180A_0_TPDOCommunicationParameter_maxSubIndex    0
        #define OD_180A_1_TPDOCommunicationParameter_COB_IDUsedByTPDO 1
        #define OD_180A_2_TPDOCommunicationParameter_transmissionType 2
        #define OD_180A_3_TPDOCommunicationParameter_inhibitTime    3
        #define OD_180A_4_TPDOCommunicationParameter_compatibilityEntry 4
        #define OD_180A_5_TPDOCommunicationParameter_eventTimer     5
        #define OD_180A_6_TPDOCommunicationParameter_SYNCStartValue 6

/*180B */
        #define OD_180B_TPDOCommunicationParameter                  0x180B

        #define OD_180B_0_TPDOCommunicationParameter_maxSubIndex    0
        #define OD_180B_1_TPDOCommunicationParameter_COB_IDUsedByTPDO 1
        #define OD_180B_2_TPDOCommunicationParameter_transmissionType 2
        #define OD_180B_3_TPDOCommunicationParameter_inhibitTime    3
        #define OD_180B_4_TPDOCommunicationParameter_compatibilityEntry 4
        #define OD_180B_5_TPDOCommunicationParameter_eventTimer     5
        #define OD_180B_6_TPDOCommunicationParameter_SYNCStartValue 6

/*180C */
        #define OD_180C_TPDOCommunicationParameter                  0x180C

        #define OD_180C_0_TPDOCommunicationParameter_maxSubIndex    0
        #define OD_180C_1_TPDOCommunicationParameter_COB_IDUsedByTPDO 1
        #define OD_180C_2_TPDOCommunicationParameter_transmissionType 2
        #define OD_180C_3_TPDOCommunicationParameter_inhibitTime    3
        #define OD_180C_4_TPDOCommunicationParameter_compatibilityEntry 4
        #define OD_180C_5_TPDOCommunicationParameter_eventTimer     5
        #define OD_180C_6_TPDOCommunicationParameter_SYNCStartValue 6

/*180D */
        #define OD_180D_TPDOCommunicationParameter                  0x180D

        #define OD_180D_0_TPDOCommunicationParameter_maxSubIndex    0
        #define OD_180D_1_TPDOCommunicationParameter_COB_IDUsedByTPDO 1
        #define OD_180D_2_TPDOCommunicationParameter_transmissionType 2
        #define OD_180D_3_TPDOCommunicationParameter_inhibitTime    3
        #define OD_180D_4_TPDOCommunicationParameter_compatibilityEntry 4
        #define OD_180D_5_TPDOCommunicationParameter_eventTimer     5
        #define OD_180D_6_TPDOCommunicationParameter_SYNCStartValue 6

/*180E */
        #define OD_180E_TPDOCommunicationParameter                  0x180E

        #define OD_180E_0_TPDOCommunicationParameter_maxSubIndex    0
        #define OD_180E_1_TPDOCommunicationParameter_COB_IDUsedByTPDO 1
        #define OD_180E_2_TPDOCommunicationParameter_transmissionType 2
        #define OD_180E_3_TPDOCommunicationParameter_inhibitTime    3
        #define OD_180E_4_TPDOCommunicationParameter_compatibilityEntry 4
        #define OD_180E_5_TPDOCommunicationParameter_eventTimer     5
        #define OD_180E_6_TPDOCommunicationParameter_SYNCStartValue 6

/*180F */
        #define OD_180F_TPDOCommunicationParameter                  0x180F

        #define OD_180F_0_TPDOCommunicationParameter_maxSubIndex    0
        #define OD_180F_1_TPDOCommunicationParameter_COB_IDUsedByTPDO 1
        #define OD_180F_2_TPDOCommunicationParameter_transmissionType 2
        #define OD_180F_3_TPDOCommunicationParameter_inhibitTime    3
        #define OD_180F_4_TPDOCommunicationParameter_compatibilityEntry 4
        #define OD_180F_5_TPDOCommunicationParameter_eventTimer     5
        #define OD_180F_6_TPDOCommunicationParameter_SYNCStartValue 6

/*1A00 */
        #define OD_1A00_TPDOMappingParameter                        0x1A00

        #define OD_1A00_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A00_1_TPDOMappingParameter_mappedObject1        1
        #define OD_1A00_2_TPDOMappingParameter_mappedObject2        2
        #define OD_1A00_3_TPDOMappingParameter_mappedObject3        3
        #define OD_1A00_4_TPDOMappingParameter_mappedObject4        4
        #define OD_1A00_5_TPDOMappingParameter_mappedObject5        5
        #define OD_1A00_6_TPDOMappingParameter_mappedObject6        6
        #define OD_1A00_7_TPDOMappingParameter_mappedObject7        7
        #define OD_1A00_8_TPDOMappingParameter_mappedObject8        8

/*1A01 */
        #define OD_1A01_TPDOMappingParameter                        0x1A01

        #define OD_1A01_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A01_1_TPDOMappingParameter_mappedObject1        1
        #define OD_1A01_2_TPDOMappingParameter_mappedObject2        2
        #define OD_1A01_3_TPDOMappingParameter_mappedObject3        3
        #define OD_1A01_4_TPDOMappingParameter_mappedObject4        4
        #define OD_1A01_5_TPDOMappingParameter_mappedObject5        5
        #define OD_1A01_6_TPDOMappingParameter_mappedObject6        6
        #define OD_1A01_7_TPDOMappingParameter_mappedObject7        7
        #define OD_1A01_8_TPDOMappingParameter_mappedObject8        8

/*1A02 */
        #define OD_1A02_TPDOMappingParameter                        0x1A02

        #define OD_1A02_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A02_1_TPDOMappingParameter_mappedObject1        1
        #define OD_1A02_2_TPDOMappingParameter_mappedObject2        2
        #define OD_1A02_3_TPDOMappingParameter_mappedObject3        3
        #define OD_1A02_4_TPDOMappingParameter_mappedObject4        4
        #define OD_1A02_5_TPDOMappingParameter_mappedObject5        5
        #define OD_1A02_6_TPDOMappingParameter_mappedObject6        6
        #define OD_1A02_7_TPDOMappingParameter_mappedObject7        7
        #define OD_1A02_8_TPDOMappingParameter_mappedObject8        8

/*1A03 */
        #define OD_1A03_TPDOMappingParameter                        0x1A03

        #define OD_1A03_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A03_1_TPDOMappingParameter_mappedObject1        1
        #define OD_1A03_2_TPDOMappingParameter_mappedObject2        2
        #define OD_1A03_3_TPDOMappingParameter_mappedObject3        3
        #define OD_1A03_4_TPDOMappingParameter_mappedObject4        4
        #define OD_1A03_5_TPDOMappingParameter_mappedObject5        5
        #define OD_1A03_6_TPDOMappingParameter_mappedObject6        6
        #define OD_1A03_7_TPDOMappingParameter_mappedObject7        7
        #define OD_1A03_8_TPDOMappingParameter_mappedObject8        8

/*1A04 */
        #define OD_1A04_TPDOMappingParameter                        0x1A04

        #define OD_1A04_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A04_1_TPDOMappingParameter_mappedObject1        1
        #define OD_1A04_2_TPDOMappingParameter_mappedObject2        2
        #define OD_1A04_3_TPDOMappingParameter_mappedObject3        3
        #define OD_1A04_4_TPDOMappingParameter_mappedObject4        4
        #define OD_1A04_5_TPDOMappingParameter_mappedObject5        5
        #define OD_1A04_6_TPDOMappingParameter_mappedObject6        6
        #define OD_1A04_7_TPDOMappingParameter_mappedObject7        7
        #define OD_1A04_8_TPDOMappingParameter_mappedObject8        8

/*1A05 */
        #define OD_1A05_TPDOMappingParameter                        0x1A05

        #define OD_1A05_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A05_1_TPDOMappingParameter_mappedObject1        1
        #define OD_1A05_2_TPDOMappingParameter_mappedObject2        2
        #define OD_1A05_3_TPDOMappingParameter_mappedObject3        3
        #define OD_1A05_4_TPDOMappingParameter_mappedObject4        4
        #define OD_1A05_5_TPDOMappingParameter_mappedObject5        5
        #define OD_1A05_6_TPDOMappingParameter_mappedObject6        6
        #define OD_1A05_7_TPDOMappingParameter_mappedObject7        7
        #define OD_1A05_8_TPDOMappingParameter_mappedObject8        8

/*1A06 */
        #define OD_1A06_TPDOMappingParameter                        0x1A06

        #define OD_1A06_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A06_1_TPDOMappingParameter_mappedObject1        1
        #define OD_1A06_2_TPDOMappingParameter_mappedObject2        2
        #define OD_1A06_3_TPDOMappingParameter_mappedObject3        3
        #define OD_1A06_4_TPDOMappingParameter_mappedObject4        4
        #define OD_1A06_5_TPDOMappingParameter_mappedObject5        5
        #define OD_1A06_6_TPDOMappingParameter_mappedObject6        6
        #define OD_1A06_7_TPDOMappingParameter_mappedObject7        7
        #define OD_1A06_8_TPDOMappingParameter_mappedObject8        8

/*1A07 */
        #define OD_1A07_TPDOMappingParameter                        0x1A07

        #define OD_1A07_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A07_1_TPDOMappingParameter_mappedObject1        1
        #define OD_1A07_2_TPDOMappingParameter_mappedObject2        2
        #define OD_1A07_3_TPDOMappingParameter_mappedObject3        3
        #define OD_1A07_4_TPDOMappingParameter_mappedObject4        4
        #define OD_1A07_5_TPDOMappingParameter_mappedObject5        5
        #define OD_1A07_6_TPDOMappingParameter_mappedObject6        6
        #define OD_1A07_7_TPDOMappingParameter_mappedObject7        7
        #define OD_1A07_8_TPDOMappingParameter_mappedObject8        8

/*1A08 */
        #define OD_1A08_TPDOMappingParameter                        0x1A08

        #define OD_1A08_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A08_1_TPDOMappingParameter_mappedObject1        1
        #define OD_1A08_2_TPDOMappingParameter_mappedObject2        2
        #define OD_1A08_3_TPDOMappingParameter_mappedObject3        3
        #define OD_1A08_4_TPDOMappingParameter_mappedObject4        4
        #define OD_1A08_5_TPDOMappingParameter_mappedObject5        5
        #define OD_1A08_6_TPDOMappingParameter_mappedObject6        6
        #define OD_1A08_7_TPDOMappingParameter_mappedObject7        7
        #define OD_1A08_8_TPDOMappingParameter_mappedObject8        8

/*1A09 */
        #define OD_1A09_TPDOMappingParameter                        0x1A09

        #define OD_1A09_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A09_1_TPDOMappingParameter_mappedObject1        1
        #define OD_1A09_2_TPDOMappingParameter_mappedObject2        2
        #define OD_1A09_3_TPDOMappingParameter_mappedObject3        3
        #define OD_1A09_4_TPDOMappingParameter_mappedObject4        4
        #define OD_1A09_5_TPDOMappingParameter_mappedObject5        5
        #define OD_1A09_6_TPDOMappingParameter_mappedObject6        6
        #define OD_1A09_7_TPDOMappingParameter_mappedObject7        7
        #define OD_1A09_8_TPDOMappingParameter_mappedObject8        8

/*1A0A */
        #define OD_1A0A_TPDOMappingParameter                        0x1A0A

        #define OD_1A0A_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A0A_1_TPDOMappingParameter_mappedObject1        1
        #define OD_1A0A_2_TPDOMappingParameter_mappedObject2        2
        #define OD_1A0A_3_TPDOMappingParameter_mappedObject3        3
        #define OD_1A0A_4_TPDOMappingParameter_mappedObject4        4
        #define OD_1A0A_5_TPDOMappingParameter_mappedObject5        5
        #define OD_1A0A_6_TPDOMappingParameter_mappedObject6        6
        #define OD_1A0A_7_TPDOMappingParameter_mappedObject7        7
        #define OD_1A0A_8_TPDOMappingParameter_mappedObject8        8

/*1A0B */
        #define OD_1A0B_TPDOMappingParameter                        0x1A0B

        #define OD_1A0B_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A0B_1_TPDOMappingParameter_mappedObject1        1
        #define OD_1A0B_2_TPDOMappingParameter_mappedObject2        2
        #define OD_1A0B_3_TPDOMappingParameter_mappedObject3        3
        #define OD_1A0B_4_TPDOMappingParameter_mappedObject4        4
        #define OD_1A0B_5_TPDOMappingParameter_mappedObject5        5
        #define OD_1A0B_6_TPDOMappingParameter_mappedObject6        6
        #define OD_1A0B_7_TPDOMappingParameter_mappedObject7        7
        #define OD_1A0B_8_TPDOMappingParameter_mappedObject8        8

/*1A0C */
        #define OD_1A0C_TPDOMappingParameter                        0x1A0C

        #define OD_1A0C_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A0C_1_TPDOMappingParameter_mappedObject1        1
        #define OD_1A0C_2_TPDOMappingParameter_mappedObject2        2
        #define OD_1A0C_3_TPDOMappingParameter_mappedObject3        3
        #define OD_1A0C_4_TPDOMappingParameter_mappedObject4        4
        #define OD_1A0C_5_TPDOMappingParameter_mappedObject5        5
        #define OD_1A0C_6_TPDOMappingParameter_mappedObject6        6
        #define OD_1A0C_7_TPDOMappingParameter_mappedObject7        7
        #define OD_1A0C_8_TPDOMappingParameter_mappedObject8        8

/*1A0D */
        #define OD_1A0D_TPDOMappingParameter                        0x1A0D

        #define OD_1A0D_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A0D_1_TPDOMappingParameter_mappedObject1        1
        #define OD_1A0D_2_TPDOMappingParameter_mappedObject2        2
        #define OD_1A0D_3_TPDOMappingParameter_mappedObject3        3
        #define OD_1A0D_4_TPDOMappingParameter_mappedObject4        4
        #define OD_1A0D_5_TPDOMappingParameter_mappedObject5        5
        #define OD_1A0D_6_TPDOMappingParameter_mappedObject6        6
        #define OD_1A0D_7_TPDOMappingParameter_mappedObject7        7
        #define OD_1A0D_8_TPDOMappingParameter_mappedObject8        8

/*1A0E */
        #define OD_1A0E_TPDOMappingParameter                        0x1A0E

        #define OD_1A0E_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A0E_1_TPDOMappingParameter_mappedObject1        1
        #define OD_1A0E_2_TPDOMappingParameter_mappedObject2        2
        #define OD_1A0E_3_TPDOMappingParameter_mappedObject3        3
        #define OD_1A0E_4_TPDOMappingParameter_mappedObject4        4
        #define OD_1A0E_5_TPDOMappingParameter_mappedObject5        5
        #define OD_1A0E_6_TPDOMappingParameter_mappedObject6        6
        #define OD_1A0E_7_TPDOMappingParameter_mappedObject7        7
        #define OD_1A0E_8_TPDOMappingParameter_mappedObject8        8

/*1A0F */
        #define OD_1A0F_TPDOMappingParameter                        0x1A0F

        #define OD_1A0F_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A0F_1_TPDOMappingParameter_mappedObject1        1
        #define OD_1A0F_2_TPDOMappingParameter_mappedObject2        2
        #define OD_1A0F_3_TPDOMappingParameter_mappedObject3        3
        #define OD_1A0F_4_TPDOMappingParameter_mappedObject4        4
        #define OD_1A0F_5_TPDOMappingParameter_mappedObject5        5
        #define OD_1A0F_6_TPDOMappingParameter_mappedObject6        6
        #define OD_1A0F_7_TPDOMappingParameter_mappedObject7        7
        #define OD_1A0F_8_TPDOMappingParameter_mappedObject8        8

/*1F80 */
        #define OD_1F80_NMTStartup                                  0x1F80

/*1F81 */
        #define OD_1F81_slaveAssignment                             0x1F81

        #define OD_1F81_0_slaveAssignment_maxSubIndex               0
        #define OD_1F81_1_slaveAssignment_                          1
        #define OD_1F81_2_slaveAssignment_                          2
        #define OD_1F81_3_slaveAssignment_                          3
        #define OD_1F81_4_slaveAssignment_                          4
        #define OD_1F81_5_slaveAssignment_                          5
        #define OD_1F81_6_slaveAssignment_                          6
        #define OD_1F81_7_slaveAssignment_                          7
        #define OD_1F81_8_slaveAssignment_                          8
        #define OD_1F81_9_slaveAssignment_                          9
        #define OD_1F81_10_slaveAssignment_                         10
        #define OD_1F81_11_slaveAssignment_                         11
        #define OD_1F81_12_slaveAssignment_                         12
        #define OD_1F81_13_slaveAssignment_                         13
        #define OD_1F81_14_slaveAssignment_                         14
        #define OD_1F81_15_slaveAssignment_                         15
        #define OD_1F81_16_slaveAssignment_                         16
        #define OD_1F81_17_slaveAssignment_                         17
        #define OD_1F81_18_slaveAssignment_                         18
        #define OD_1F81_19_slaveAssignment_                         19
        #define OD_1F81_20_slaveAssignment_                         20
        #define OD_1F81_21_slaveAssignment_                         21
        #define OD_1F81_22_slaveAssignment_                         22
        #define OD_1F81_23_slaveAssignment_                         23
        #define OD_1F81_24_slaveAssignment_                         24
        #define OD_1F81_25_slaveAssignment_                         25
        #define OD_1F81_26_slaveAssignment_                         26
        #define OD_1F81_27_slaveAssignment_                         27
        #define OD_1F81_28_slaveAssignment_                         28
        #define OD_1F81_29_slaveAssignment_                         29
        #define OD_1F81_30_slaveAssignment_                         30
        #define OD_1F81_31_slaveAssignment_                         31
        #define OD_1F81_32_slaveAssignment_                         32
        #define OD_1F81_33_slaveAssignment_                         33
        #define OD_1F81_34_slaveAssignment_                         34
        #define OD_1F81_35_slaveAssignment_                         35
        #define OD_1F81_36_slaveAssignment_                         36
        #define OD_1F81_37_slaveAssignment_                         37
        #define OD_1F81_38_slaveAssignment_                         38
        #define OD_1F81_39_slaveAssignment_                         39
        #define OD_1F81_40_slaveAssignment_                         40
        #define OD_1F81_41_slaveAssignment_                         41
        #define OD_1F81_42_slaveAssignment_                         42
        #define OD_1F81_43_slaveAssignment_                         43
        #define OD_1F81_44_slaveAssignment_                         44
        #define OD_1F81_45_slaveAssignment_                         45
        #define OD_1F81_46_slaveAssignment_                         46
        #define OD_1F81_47_slaveAssignment_                         47
        #define OD_1F81_48_slaveAssignment_                         48
        #define OD_1F81_49_slaveAssignment_                         49
        #define OD_1F81_50_slaveAssignment_                         50
        #define OD_1F81_51_slaveAssignment_                         51
        #define OD_1F81_52_slaveAssignment_                         52
        #define OD_1F81_53_slaveAssignment_                         53
        #define OD_1F81_54_slaveAssignment_                         54
        #define OD_1F81_55_slaveAssignment_                         55
        #define OD_1F81_56_slaveAssignment_                         56
        #define OD_1F81_57_slaveAssignment_                         57
        #define OD_1F81_58_slaveAssignment_                         58
        #define OD_1F81_59_slaveAssignment_                         59
        #define OD_1F81_60_slaveAssignment_                         60
        #define OD_1F81_61_slaveAssignment_                         61
        #define OD_1F81_62_slaveAssignment_                         62
        #define OD_1F81_63_slaveAssignment_                         63
        #define OD_1F81_64_slaveAssignment_                         64
        #define OD_1F81_65_slaveAssignment_                         65
        #define OD_1F81_66_slaveAssignment_                         66
        #define OD_1F81_67_slaveAssignment_                         67
        #define OD_1F81_68_slaveAssignment_                         68
        #define OD_1F81_69_slaveAssignment_                         69
        #define OD_1F81_70_slaveAssignment_                         70
        #define OD_1F81_71_slaveAssignment_                         71
        #define OD_1F81_72_slaveAssignment_                         72
        #define OD_1F81_73_slaveAssignment_                         73
        #define OD_1F81_74_slaveAssignment_                         74
        #define OD_1F81_75_slaveAssignment_                         75
        #define OD_1F81_76_slaveAssignment_                         76
        #define OD_1F81_77_slaveAssignment_                         77
        #define OD_1F81_78_slaveAssignment_                         78
        #define OD_1F81_79_slaveAssignment_                         79
        #define OD_1F81_80_slaveAssignment_                         80
        #define OD_1F81_81_slaveAssignment_                         81
        #define OD_1F81_82_slaveAssignment_                         82
        #define OD_1F81_83_slaveAssignment_                         83
        #define OD_1F81_84_slaveAssignment_                         84
        #define OD_1F81_85_slaveAssignment_                         85
        #define OD_1F81_86_slaveAssignment_                         86
        #define OD_1F81_87_slaveAssignment_                         87
        #define OD_1F81_88_slaveAssignment_                         88
        #define OD_1F81_89_slaveAssignment_                         89
        #define OD_1F81_90_slaveAssignment_                         90
        #define OD_1F81_91_slaveAssignment_                         91
        #define OD_1F81_92_slaveAssignment_                         92
        #define OD_1F81_93_slaveAssignment_                         93
        #define OD_1F81_94_slaveAssignment_                         94
        #define OD_1F81_95_slaveAssignment_                         95
        #define OD_1F81_96_slaveAssignment_                         96
        #define OD_1F81_97_slaveAssignment_                         97
        #define OD_1F81_98_slaveAssignment_                         98
        #define OD_1F81_99_slaveAssignment_                         99
        #define OD_1F81_100_slaveAssignment_                        100
        #define OD_1F81_101_slaveAssignment_                        101
        #define OD_1F81_102_slaveAssignment_                        102
        #define OD_1F81_103_slaveAssignment_                        103
        #define OD_1F81_104_slaveAssignment_                        104
        #define OD_1F81_105_slaveAssignment_                        105
        #define OD_1F81_106_slaveAssignment_                        106
        #define OD_1F81_107_slaveAssignment_                        107
        #define OD_1F81_108_slaveAssignment_                        108
        #define OD_1F81_109_slaveAssignment_                        109
        #define OD_1F81_110_slaveAssignment_                        110
        #define OD_1F81_111_slaveAssignment_                        111
        #define OD_1F81_112_slaveAssignment_                        112
        #define OD_1F81_113_slaveAssignment_                        113
        #define OD_1F81_114_slaveAssignment_                        114
        #define OD_1F81_115_slaveAssignment_                        115
        #define OD_1F81_116_slaveAssignment_                        116
        #define OD_1F81_117_slaveAssignment_                        117
        #define OD_1F81_118_slaveAssignment_                        118
        #define OD_1F81_119_slaveAssignment_                        119
        #define OD_1F81_120_slaveAssignment_                        120
        #define OD_1F81_121_slaveAssignment_                        121
        #define OD_1F81_122_slaveAssignment_                        122
        #define OD_1F81_123_slaveAssignment_                        123
        #define OD_1F81_124_slaveAssignment_                        124
        #define OD_1F81_125_slaveAssignment_                        125
        #define OD_1F81_126_slaveAssignment_                        126
        #define OD_1F81_127_slaveAssignment_                        127

/*1F82 */
        #define OD_1F82_requestNMT                                  0x1F82

        #define OD_1F82_0_requestNMT_maxSubIndex                    0
        #define OD_1F82_1_requestNMT_                               1
        #define OD_1F82_2_requestNMT_                               2
        #define OD_1F82_3_requestNMT_                               3
        #define OD_1F82_4_requestNMT_                               4
        #define OD_1F82_5_requestNMT_                               5
        #define OD_1F82_6_requestNMT_                               6
        #define OD_1F82_7_requestNMT_                               7
        #define OD_1F82_8_requestNMT_                               8
        #define OD_1F82_9_requestNMT_                               9
        #define OD_1F82_10_requestNMT_                              10
        #define OD_1F82_11_requestNMT_                              11
        #define OD_1F82_12_requestNMT_                              12
        #define OD_1F82_13_requestNMT_                              13
        #define OD_1F82_14_requestNMT_                              14
        #define OD_1F82_15_requestNMT_                              15
        #define OD_1F82_16_requestNMT_                              16
        #define OD_1F82_17_requestNMT_                              17
        #define OD_1F82_18_requestNMT_                              18
        #define OD_1F82_19_requestNMT_                              19
        #define OD_1F82_20_requestNMT_                              20
        #define OD_1F82_21_requestNMT_                              21
        #define OD_1F82_22_requestNMT_                              22
        #define OD_1F82_23_requestNMT_                              23
        #define OD_1F82_24_requestNMT_                              24
        #define OD_1F82_25_requestNMT_                              25
        #define OD_1F82_26_requestNMT_                              26
        #define OD_1F82_27_requestNMT_                              27
        #define OD_1F82_28_requestNMT_                              28
        #define OD_1F82_29_requestNMT_                              29
        #define OD_1F82_30_requestNMT_                              30
        #define OD_1F82_31_requestNMT_                              31
        #define OD_1F82_32_requestNMT_                              32
        #define OD_1F82_33_requestNMT_                              33
        #define OD_1F82_34_requestNMT_                              34
        #define OD_1F82_35_requestNMT_                              35
        #define OD_1F82_36_requestNMT_                              36
        #define OD_1F82_37_requestNMT_                              37
        #define OD_1F82_38_requestNMT_                              38
        #define OD_1F82_39_requestNMT_                              39
        #define OD_1F82_40_requestNMT_                              40
        #define OD_1F82_41_requestNMT_                              41
        #define OD_1F82_42_requestNMT_                              42
        #define OD_1F82_43_requestNMT_                              43
        #define OD_1F82_44_requestNMT_                              44
        #define OD_1F82_45_requestNMT_                              45
        #define OD_1F82_46_requestNMT_                              46
        #define OD_1F82_47_requestNMT_                              47
        #define OD_1F82_48_requestNMT_                              48
        #define OD_1F82_49_requestNMT_                              49
        #define OD_1F82_50_requestNMT_                              50
        #define OD_1F82_51_requestNMT_                              51
        #define OD_1F82_52_requestNMT_                              52
        #define OD_1F82_53_requestNMT_                              53
        #define OD_1F82_54_requestNMT_                              54
        #define OD_1F82_55_requestNMT_                              55
        #define OD_1F82_56_requestNMT_                              56
        #define OD_1F82_57_requestNMT_                              57
        #define OD_1F82_58_requestNMT_                              58
        #define OD_1F82_59_requestNMT_                              59
        #define OD_1F82_60_requestNMT_                              60
        #define OD_1F82_61_requestNMT_                              61
        #define OD_1F82_62_requestNMT_                              62
        #define OD_1F82_63_requestNMT_                              63
        #define OD_1F82_64_requestNMT_                              64
        #define OD_1F82_65_requestNMT_                              65
        #define OD_1F82_66_requestNMT_                              66
        #define OD_1F82_67_requestNMT_                              67
        #define OD_1F82_68_requestNMT_                              68
        #define OD_1F82_69_requestNMT_                              69
        #define OD_1F82_70_requestNMT_                              70
        #define OD_1F82_71_requestNMT_                              71
        #define OD_1F82_72_requestNMT_                              72
        #define OD_1F82_73_requestNMT_                              73
        #define OD_1F82_74_requestNMT_                              74
        #define OD_1F82_75_requestNMT_                              75
        #define OD_1F82_76_requestNMT_                              76
        #define OD_1F82_77_requestNMT_                              77
        #define OD_1F82_78_requestNMT_                              78
        #define OD_1F82_79_requestNMT_                              79
        #define OD_1F82_80_requestNMT_                              80
        #define OD_1F82_81_requestNMT_                              81
        #define OD_1F82_82_requestNMT_                              82
        #define OD_1F82_83_requestNMT_                              83
        #define OD_1F82_84_requestNMT_                              84
        #define OD_1F82_85_requestNMT_                              85
        #define OD_1F82_86_requestNMT_                              86
        #define OD_1F82_87_requestNMT_                              87
        #define OD_1F82_88_requestNMT_                              88
        #define OD_1F82_89_requestNMT_                              89
        #define OD_1F82_90_requestNMT_                              90
        #define OD_1F82_91_requestNMT_                              91
        #define OD_1F82_92_requestNMT_                              92
        #define OD_1F82_93_requestNMT_                              93
        #define OD_1F82_94_requestNMT_                              94
        #define OD_1F82_95_requestNMT_                              95
        #define OD_1F82_96_requestNMT_                              96
        #define OD_1F82_97_requestNMT_                              97
        #define OD_1F82_98_requestNMT_                              98
        #define OD_1F82_99_requestNMT_                              99
        #define OD_1F82_100_requestNMT_                             100
        #define OD_1F82_101_requestNMT_                             101
        #define OD_1F82_102_requestNMT_                             102
        #define OD_1F82_103_requestNMT_                             103
        #define OD_1F82_104_requestNMT_                             104
        #define OD_1F82_105_requestNMT_                             105
        #define OD_1F82_106_requestNMT_                             106
        #define OD_1F82_107_requestNMT_                             107
        #define OD_1F82_108_requestNMT_                             108
        #define OD_1F82_109_requestNMT_                             109
        #define OD_1F82_110_requestNMT_                             110
        #define OD_1F82_111_requestNMT_                             111
        #define OD_1F82_112_requestNMT_                             112
        #define OD_1F82_113_requestNMT_                             113
        #define OD_1F82_114_requestNMT_                             114
        #define OD_1F82_115_requestNMT_                             115
        #define OD_1F82_116_requestNMT_                             116
        #define OD_1F82_117_requestNMT_                             117
        #define OD_1F82_118_requestNMT_                             118
        #define OD_1F82_119_requestNMT_                             119
        #define OD_1F82_120_requestNMT_                             120
        #define OD_1F82_121_requestNMT_                             121
        #define OD_1F82_122_requestNMT_                             122
        #define OD_1F82_123_requestNMT_                             123
        #define OD_1F82_124_requestNMT_                             124
        #define OD_1F82_125_requestNMT_                             125
        #define OD_1F82_126_requestNMT_                             126
        #define OD_1F82_127_requestNMT_                             127

/*1F89 */
        #define OD_1F89_bootTime                                    0x1F89

/*2010 */
        #define OD_2010_SCET                                        0x2010

/*2011 */
        #define OD_2011_UTC                                         0x2011

/*2100 */
        #define OD_2100_errorStatusBits                             0x2100

/*2101 */
        #define OD_2101_CANNodeID                                   0x2101

/*2102 */
        #define OD_2102_CANBitRate                                  0x2102

/*2103 */
        #define OD_2103_SYNCCounter                                 0x2103

/*2104 */
        #define OD_2104_SYNCTime                                    0x2104

/*2106 */
        #define OD_2106_calibration                                 0x2106

        #define OD_2106_0_calibration_maxSubIndex                   0
        #define OD_2106_1_calibration_TS_CAL1                       1
        #define OD_2106_2_calibration_TS_CAL2                       2
        #define OD_2106_3_calibration_VREFINT_CAL                   3

/*2107 */
        #define OD_2107_sensors                                     0x2107

        #define OD_2107_0_sensors_maxSubIndex                       0
        #define OD_2107_1_sensors_MCU_Temperature                   1
        #define OD_2107_2_sensors_MCU_VREFINT                       2
        #define OD_2107_3_sensors_MCU_VBAT                          3

/*2108 */
        #define OD_2108_temperature                                 0x2108

        #define OD_2108_0_temperature_maxSubIndex                   0
        #define OD_2108_1_temperature_MCU_Junction                  1

/*2109 */
        #define OD_2109_voltage                                     0x2109

        #define OD_2109_0_voltage_maxSubIndex                       0
        #define OD_2109_1_voltage_MCU_VDDA                          1

/*4002 */
        #define OD_4002_battery1                                    0x4002

        #define OD_4002_0_battery1_maxSubIndex                      0
        #define OD_4002_1_battery1_MCU_Temperature                  1
        #define OD_4002_2_battery1_MCU_Voltage                      2

/*4003 */
        #define OD_4003_battery2                                    0x4003

        #define OD_4003_0_battery2_maxSubIndex                      0
        #define OD_4003_1_battery2_MCU_Temperature                  1
        #define OD_4003_2_battery2_MCU_Voltage                      2

/*4004 */
        #define OD_4004_solarPanel1                                 0x4004

        #define OD_4004_0_solarPanel1_maxSubIndex                   0
        #define OD_4004_1_solarPanel1_MCU_Temperature               1
        #define OD_4004_2_solarPanel1_MCU_Voltage                   2
        #define OD_4004_3_solarPanel1_PV_Voltage                    3
        #define OD_4004_4_solarPanel1_PV_Current                    4
        #define OD_4004_5_solarPanel1_PV_Power                      5

/*4005 */
        #define OD_4005_solarPanel2                                 0x4005

        #define OD_4005_0_solarPanel2_maxSubIndex                   0
        #define OD_4005_1_solarPanel2_MCU_Temperature               1
        #define OD_4005_2_solarPanel2_MCU_Voltage                   2
        #define OD_4005_3_solarPanel2_PV_Voltage                    3
        #define OD_4005_4_solarPanel2_PV_Current                    4
        #define OD_4005_5_solarPanel2_PV_Power                      5

/*4006 */
        #define OD_4006_solarPanel3                                 0x4006

        #define OD_4006_0_solarPanel3_maxSubIndex                   0
        #define OD_4006_1_solarPanel3_MCU_Temperature               1
        #define OD_4006_2_solarPanel3_MCU_Voltage                   2
        #define OD_4006_3_solarPanel3_PV_Voltage                    3
        #define OD_4006_4_solarPanel3_PV_Current                    4
        #define OD_4006_5_solarPanel3_PV_Power                      5

/*4007 */
        #define OD_4007_solarPanel4                                 0x4007

        #define OD_4007_0_solarPanel4_maxSubIndex                   0
        #define OD_4007_1_solarPanel4_MCU_Temperature               1
        #define OD_4007_2_solarPanel4_MCU_Voltage                   2
        #define OD_4007_3_solarPanel4_PV_Voltage                    3
        #define OD_4007_4_solarPanel4_PV_Current                    4
        #define OD_4007_5_solarPanel4_PV_Power                      5

/*4008 */
        #define OD_4008_solarPanel5                                 0x4008

        #define OD_4008_0_solarPanel5_maxSubIndex                   0
        #define OD_4008_1_solarPanel5_MCU_Temperature               1
        #define OD_4008_2_solarPanel5_MCU_Voltage                   2
        #define OD_4008_3_solarPanel5_PV_Voltage                    3
        #define OD_4008_4_solarPanel5_PV_Current                    4
        #define OD_4008_5_solarPanel5_PV_Power                      5

/*4009 */
        #define OD_4009_solarPanel6                                 0x4009

        #define OD_4009_0_solarPanel6_maxSubIndex                   0
        #define OD_4009_1_solarPanel6_MCU_Temperature               1
        #define OD_4009_2_solarPanel6_MCU_Voltage                   2
        #define OD_4009_3_solarPanel6_PV_Voltage                    3
        #define OD_4009_4_solarPanel6_PV_Current                    4
        #define OD_4009_5_solarPanel6_PV_Power                      5

/*400A */
        #define OD_400A_solarPanel7                                 0x400A

        #define OD_400A_0_solarPanel7_maxSubIndex                   0
        #define OD_400A_1_solarPanel7_MCU_Temperature               1
        #define OD_400A_2_solarPanel7_MCU_Voltage                   2
        #define OD_400A_3_solarPanel7_PV_Voltage                    3
        #define OD_400A_4_solarPanel7_PV_Current                    4
        #define OD_400A_5_solarPanel7_PV_Power                      5

/*400B */
        #define OD_400B_solarPanel8                                 0x400B

        #define OD_400B_0_solarPanel8_maxSubIndex                   0
        #define OD_400B_1_solarPanel8_MCU_Temperature               1
        #define OD_400B_2_solarPanel8_MCU_Voltage                   2
        #define OD_400B_3_solarPanel8_PV_Voltage                    3
        #define OD_400B_4_solarPanel8_PV_Current                    4
        #define OD_400B_5_solarPanel8_PV_Power                      5

/*4011 */
        #define OD_4011_starTracker                                 0x4011

        #define OD_4011_0_starTracker_maxSubIndex                   0

/*4012 */
        #define OD_4012_GPS                                         0x4012

        #define OD_4012_0_GPS_maxSubIndex                           0

/*4013 */
        #define OD_4013_IMU                                         0x4013

        #define OD_4013_0_IMU_maxSubIndex                           0
        #define OD_4013_1_IMU_MCU_Temperature                       1
        #define OD_4013_2_IMU_MCU_Voltage                           2

/*4014 */
        #define OD_4014_magnetometer1                               0x4014

        #define OD_4014_0_magnetometer1_maxSubIndex                 0
        #define OD_4014_1_magnetometer1_MCU_Temperature             1
        #define OD_4014_2_magnetometer1_MCU_Voltage                 2

/*4015 */
        #define OD_4015_magnetometer2                               0x4015

        #define OD_4015_0_magnetometer2_maxSubIndex                 0
        #define OD_4015_1_magnetometer2_MCU_Temperature             1
        #define OD_4015_2_magnetometer2_MCU_Voltage                 2

/*4016 */
        #define OD_4016_RW_MT1                                      0x4016

        #define OD_4016_0_RW_MT1_maxSubIndex                        0
        #define OD_4016_1_RW_MT1_MCU_Temperature                    1
        #define OD_4016_2_RW_MT1_MCU_Voltage                        2

/*4017 */
        #define OD_4017_RW_MT2                                      0x4017

        #define OD_4017_0_RW_MT2_maxSubIndex                        0
        #define OD_4017_1_RW_MT2_MCU_Temperature                    1
        #define OD_4017_2_RW_MT2_MCU_Voltage                        2

/*4018 */
        #define OD_4018_RW_MT3                                      0x4018

        #define OD_4018_0_RW_MT3_maxSubIndex                        0
        #define OD_4018_1_RW_MT3_MCU_Temperature                    1
        #define OD_4018_2_RW_MT3_MCU_Voltage                        2

/*4019 */
        #define OD_4019_RW4                                         0x4019

        #define OD_4019_0_RW4_maxSubIndex                           0
        #define OD_4019_1_RW4_MCU_Temperature                       1
        #define OD_4019_2_RW4_MCU_Voltage                           2

/*4021 */
        #define OD_4021_oreSatLive                                  0x4021

        #define OD_4021_0_oreSatLive_maxSubIndex                    0

/*4022 */
        #define OD_4022_CFC                                         0x4022

        #define OD_4022_0_CFC_maxSubIndex                           0

/*4031 */
        #define OD_4031_protocard1                                  0x4031

        #define OD_4031_0_protocard1_maxSubIndex                    0
        #define OD_4031_1_protocard1_MCU_Temperature                1
        #define OD_4031_2_protocard1_MCU_Voltage                    2

/*4032 */
        #define OD_4032_protocard2                                  0x4032

        #define OD_4032_0_protocard2_maxSubIndex                    0
        #define OD_4032_1_protocard2_MCU_Temperature                1
        #define OD_4032_2_protocard2_MCU_Voltage                    2

/*4033 */
        #define OD_4033_protocard3                                  0x4033

        #define OD_4033_0_protocard3_maxSubIndex                    0
        #define OD_4033_1_protocard3_MCU_Temperature                1
        #define OD_4033_2_protocard3_MCU_Voltage                    2

/*******************************************************************************
   STRUCTURES FOR VARIABLES IN DIFFERENT MEMORY LOCATIONS
*******************************************************************************/
#define  CO_OD_FIRST_LAST_WORD     0x55 //Any value from 0x01 to 0xFE. If changed, EEPROM will be reinitialized.

/***** Structure for ROM variables ********************************************/
struct sCO_OD_ROM{
               UNSIGNED32     FirstWord;

/*1000      */ UNSIGNED32     deviceType;
/*1005      */ UNSIGNED32     COB_ID_SYNCMessage;
/*1006      */ UNSIGNED32     communicationCyclePeriod;
/*1007      */ UNSIGNED32     synchronousWindowLength;
/*1008      */ VISIBLE_STRING manufacturerDeviceName[21];
/*1009      */ VISIBLE_STRING manufacturerHardwareVersion[3];
/*100A      */ VISIBLE_STRING manufacturerSoftwareVersion[5];
/*1014      */ UNSIGNED32     COB_ID_EMCY;
/*1015      */ UNSIGNED16     inhibitTimeEMCY;
/*1016      */ UNSIGNED32      consumerHeartbeatTime[4];
/*1017      */ UNSIGNED16     producerHeartbeatTime;
/*1018      */ OD_identity_t   identity;
/*1019      */ UNSIGNED8      synchronousCounterOverflowValue;
/*1029      */ UNSIGNED8       errorBehavior[6];
/*1200      */ OD_SDOServerParameter_t SDOServerParameter[1];
/*1400      */ OD_RPDOCommunicationParameter_t RPDOCommunicationParameter[28];
/*1600      */ OD_RPDOMappingParameter_t RPDOMappingParameter[28];
/*1800      */ OD_TPDOCommunicationParameter_t TPDOCommunicationParameter[16];
/*1A00      */ OD_TPDOMappingParameter_t TPDOMappingParameter[16];
/*1F80      */ UNSIGNED32     NMTStartup;
/*2101      */ UNSIGNED8      CANNodeID;
/*2102      */ UNSIGNED16     CANBitRate;
/*2106      */ UNSIGNED16      calibration[3];

               UNSIGNED32     LastWord;
};

/***** Structure for RAM variables ********************************************/
struct sCO_OD_RAM{
               UNSIGNED32     FirstWord;

/*1001      */ UNSIGNED8      errorRegister;
/*1002      */ UNSIGNED32     manufacturerStatusRegister;
/*1003      */ UNSIGNED32      preDefinedErrorField[8];
/*1010      */ UNSIGNED32      storeParameters[1];
/*1011      */ UNSIGNED32      restoreDefaultParameters[1];
/*1280      */ OD_SDOClientParameter_t SDOClientParameter[1];
/*1F81      */ UNSIGNED32      slaveAssignment[127];
/*1F82      */ UNSIGNED8       requestNMT[127];
/*1F89      */ UNSIGNED32     bootTime;
/*2010      */ UNSIGNED64     SCET;
/*2011      */ UNSIGNED64     UTC;
/*2100      */ OCTET_STRING   errorStatusBits[10];
/*2103      */ UNSIGNED16     SYNCCounter;
/*2104      */ UNSIGNED16     SYNCTime;
/*2107      */ UNSIGNED16      sensors[3];
/*2108      */ INTEGER16       temperature[1];
/*2109      */ INTEGER16       voltage[1];
/*4002      */ OD_battery1_t   battery1;
/*4003      */ OD_battery2_t   battery2;
/*4004      */ OD_solarPanel1_t solarPanel1;
/*4005      */ OD_solarPanel2_t solarPanel2;
/*4006      */ OD_solarPanel3_t solarPanel3;
/*4007      */ OD_solarPanel4_t solarPanel4;
/*4008      */ OD_solarPanel5_t solarPanel5;
/*4009      */ OD_solarPanel6_t solarPanel6;
/*400A      */ OD_solarPanel7_t solarPanel7;
/*400B      */ OD_solarPanel8_t solarPanel8;
/*4011      */ OD_starTracker_t starTracker;
/*4012      */ OD_GPS_t        GPS;
/*4013      */ OD_IMU_t        IMU;
/*4014      */ OD_magnetometer1_t magnetometer1;
/*4015      */ OD_magnetometer2_t magnetometer2;
/*4016      */ OD_RW_MT1_t     RW_MT1;
/*4017      */ OD_RW_MT2_t     RW_MT2;
/*4018      */ OD_RW_MT3_t     RW_MT3;
/*4019      */ OD_RW4_t        RW4;
/*4021      */ OD_oreSatLive_t oreSatLive;
/*4022      */ OD_CFC_t        CFC;
/*4031      */ OD_protocard1_t protocard1;
/*4032      */ OD_protocard2_t protocard2;
/*4033      */ OD_protocard3_t protocard3;

               UNSIGNED32     LastWord;
};

/***** Structure for EEPROM variables ********************************************/
struct sCO_OD_EEPROM{
               UNSIGNED32     FirstWord;


               UNSIGNED32     LastWord;
};

/***** Declaration of Object Dictionary variables *****************************/
extern struct sCO_OD_ROM CO_OD_ROM;

extern struct sCO_OD_RAM CO_OD_RAM;

extern struct sCO_OD_EEPROM CO_OD_EEPROM;

/*******************************************************************************
   ALIASES FOR OBJECT DICTIONARY VARIABLES
*******************************************************************************/
/*1000, Data Type: UNSIGNED32 */
        #define OD_deviceType                                       CO_OD_ROM.deviceType

/*1001, Data Type: UNSIGNED8 */
        #define OD_errorRegister                                    CO_OD_RAM.errorRegister

/*1002, Data Type: UNSIGNED32 */
        #define OD_manufacturerStatusRegister                       CO_OD_RAM.manufacturerStatusRegister

/*1003, Data Type: UNSIGNED32, Array[8] */
        #define OD_preDefinedErrorField                             CO_OD_RAM.preDefinedErrorField
        #define ODL_preDefinedErrorField_arrayLength                8
        #define ODA_preDefinedErrorField_standardErrorField         0

/*1005, Data Type: UNSIGNED32 */
        #define OD_COB_ID_SYNCMessage                               CO_OD_ROM.COB_ID_SYNCMessage

/*1006, Data Type: UNSIGNED32 */
        #define OD_communicationCyclePeriod                         CO_OD_ROM.communicationCyclePeriod

/*1007, Data Type: UNSIGNED32 */
        #define OD_synchronousWindowLength                          CO_OD_ROM.synchronousWindowLength

/*1008, Data Type: VISIBLE_STRING */
        #define OD_manufacturerDeviceName                           CO_OD_ROM.manufacturerDeviceName
        #define ODL_manufacturerDeviceName_stringLength             21

/*1009, Data Type: VISIBLE_STRING */
        #define OD_manufacturerHardwareVersion                      CO_OD_ROM.manufacturerHardwareVersion
        #define ODL_manufacturerHardwareVersion_stringLength        3

/*100A, Data Type: VISIBLE_STRING */
        #define OD_manufacturerSoftwareVersion                      CO_OD_ROM.manufacturerSoftwareVersion
        #define ODL_manufacturerSoftwareVersion_stringLength        5

/*1010, Data Type: UNSIGNED32, Array[1] */
        #define OD_storeParameters                                  CO_OD_RAM.storeParameters
        #define ODL_storeParameters_arrayLength                     1
        #define ODA_storeParameters_saveAllParameters               0

/*1011, Data Type: UNSIGNED32, Array[1] */
        #define OD_restoreDefaultParameters                         CO_OD_RAM.restoreDefaultParameters
        #define ODL_restoreDefaultParameters_arrayLength            1
        #define ODA_restoreDefaultParameters_restoreAllDefaultParameters 0

/*1014, Data Type: UNSIGNED32 */
        #define OD_COB_ID_EMCY                                      CO_OD_ROM.COB_ID_EMCY

/*1015, Data Type: UNSIGNED16 */
        #define OD_inhibitTimeEMCY                                  CO_OD_ROM.inhibitTimeEMCY

/*1016, Data Type: UNSIGNED32, Array[4] */
        #define OD_consumerHeartbeatTime                            CO_OD_ROM.consumerHeartbeatTime
        #define ODL_consumerHeartbeatTime_arrayLength               4
        #define ODA_consumerHeartbeatTime_consumerHeartbeatTime     0

/*1017, Data Type: UNSIGNED16 */
        #define OD_producerHeartbeatTime                            CO_OD_ROM.producerHeartbeatTime

/*1018, Data Type: identity_t */
        #define OD_identity                                         CO_OD_ROM.identity

/*1019, Data Type: UNSIGNED8 */
        #define OD_synchronousCounterOverflowValue                  CO_OD_ROM.synchronousCounterOverflowValue

/*1029, Data Type: UNSIGNED8, Array[6] */
        #define OD_errorBehavior                                    CO_OD_ROM.errorBehavior
        #define ODL_errorBehavior_arrayLength                       6
        #define ODA_errorBehavior_communication                     0
        #define ODA_errorBehavior_communicationOther                1
        #define ODA_errorBehavior_communicationPassive              2
        #define ODA_errorBehavior_generic                           3
        #define ODA_errorBehavior_deviceProfile                     4
        #define ODA_errorBehavior_manufacturerSpecific              5

/*1200, Data Type: SDOServerParameter_t */
        #define OD_SDOServerParameter                               CO_OD_ROM.SDOServerParameter

/*1280, Data Type: SDOClientParameter_t */
        #define OD_SDOClientParameter                               CO_OD_RAM.SDOClientParameter

/*1400, Data Type: RPDOCommunicationParameter_t */
        #define OD_RPDOCommunicationParameter                       CO_OD_ROM.RPDOCommunicationParameter

/*1600, Data Type: RPDOMappingParameter_t */
        #define OD_RPDOMappingParameter                             CO_OD_ROM.RPDOMappingParameter

/*1800, Data Type: TPDOCommunicationParameter_t */
        #define OD_TPDOCommunicationParameter                       CO_OD_ROM.TPDOCommunicationParameter

/*1A00, Data Type: TPDOMappingParameter_t */
        #define OD_TPDOMappingParameter                             CO_OD_ROM.TPDOMappingParameter

/*1F80, Data Type: UNSIGNED32 */
        #define OD_NMTStartup                                       CO_OD_ROM.NMTStartup

/*1F81, Data Type: UNSIGNED32, Array[127] */
        #define OD_slaveAssignment                                  CO_OD_RAM.slaveAssignment
        #define ODL_slaveAssignment_arrayLength                     127
        #define ODA_slaveAssignment_                                0

/*1F82, Data Type: UNSIGNED8, Array[127] */
        #define OD_requestNMT                                       CO_OD_RAM.requestNMT
        #define ODL_requestNMT_arrayLength                          127
        #define ODA_requestNMT_                                     0

/*1F89, Data Type: UNSIGNED32 */
        #define OD_bootTime                                         CO_OD_RAM.bootTime

/*2010, Data Type: UNSIGNED64 */
        #define OD_SCET                                             CO_OD_RAM.SCET

/*2011, Data Type: UNSIGNED64 */
        #define OD_UTC                                              CO_OD_RAM.UTC

/*2100, Data Type: OCTET_STRING */
        #define OD_errorStatusBits                                  CO_OD_RAM.errorStatusBits
        #define ODL_errorStatusBits_stringLength                    10

/*2101, Data Type: UNSIGNED8 */
        #define OD_CANNodeID                                        CO_OD_ROM.CANNodeID

/*2102, Data Type: UNSIGNED16 */
        #define OD_CANBitRate                                       CO_OD_ROM.CANBitRate

/*2103, Data Type: UNSIGNED16 */
        #define OD_SYNCCounter                                      CO_OD_RAM.SYNCCounter

/*2104, Data Type: UNSIGNED16 */
        #define OD_SYNCTime                                         CO_OD_RAM.SYNCTime

/*2106, Data Type: UNSIGNED16, Array[3] */
        #define OD_calibration                                      CO_OD_ROM.calibration
        #define ODL_calibration_arrayLength                         3
        #define ODA_calibration_TS_CAL1                             0
        #define ODA_calibration_TS_CAL2                             1
        #define ODA_calibration_VREFINT_CAL                         2

/*2107, Data Type: UNSIGNED16, Array[3] */
        #define OD_sensors                                          CO_OD_RAM.sensors
        #define ODL_sensors_arrayLength                             3
        #define ODA_sensors_MCU_Temperature                         0
        #define ODA_sensors_MCU_VREFINT                             1
        #define ODA_sensors_MCU_VBAT                                2

/*2108, Data Type: INTEGER16, Array[1] */
        #define OD_temperature                                      CO_OD_RAM.temperature
        #define ODL_temperature_arrayLength                         1
        #define ODA_temperature_MCU_Junction                        0

/*2109, Data Type: INTEGER16, Array[1] */
        #define OD_voltage                                          CO_OD_RAM.voltage
        #define ODL_voltage_arrayLength                             1
        #define ODA_voltage_MCU_VDDA                                0

/*4002, Data Type: battery1_t */
        #define OD_battery1                                         CO_OD_RAM.battery1

/*4003, Data Type: battery2_t */
        #define OD_battery2                                         CO_OD_RAM.battery2

/*4004, Data Type: solarPanel1_t */
        #define OD_solarPanel1                                      CO_OD_RAM.solarPanel1

/*4005, Data Type: solarPanel2_t */
        #define OD_solarPanel2                                      CO_OD_RAM.solarPanel2

/*4006, Data Type: solarPanel3_t */
        #define OD_solarPanel3                                      CO_OD_RAM.solarPanel3

/*4007, Data Type: solarPanel4_t */
        #define OD_solarPanel4                                      CO_OD_RAM.solarPanel4

/*4008, Data Type: solarPanel5_t */
        #define OD_solarPanel5                                      CO_OD_RAM.solarPanel5

/*4009, Data Type: solarPanel6_t */
        #define OD_solarPanel6                                      CO_OD_RAM.solarPanel6

/*400A, Data Type: solarPanel7_t */
        #define OD_solarPanel7                                      CO_OD_RAM.solarPanel7

/*400B, Data Type: solarPanel8_t */
        #define OD_solarPanel8                                      CO_OD_RAM.solarPanel8

/*4011, Data Type: starTracker_t */
        #define OD_starTracker                                      CO_OD_RAM.starTracker

/*4012, Data Type: GPS_t */
        #define OD_GPS                                              CO_OD_RAM.GPS

/*4013, Data Type: IMU_t */
        #define OD_IMU                                              CO_OD_RAM.IMU

/*4014, Data Type: magnetometer1_t */
        #define OD_magnetometer1                                    CO_OD_RAM.magnetometer1

/*4015, Data Type: magnetometer2_t */
        #define OD_magnetometer2                                    CO_OD_RAM.magnetometer2

/*4016, Data Type: RW_MT1_t */
        #define OD_RW_MT1                                           CO_OD_RAM.RW_MT1

/*4017, Data Type: RW_MT2_t */
        #define OD_RW_MT2                                           CO_OD_RAM.RW_MT2

/*4018, Data Type: RW_MT3_t */
        #define OD_RW_MT3                                           CO_OD_RAM.RW_MT3

/*4019, Data Type: RW4_t */
        #define OD_RW4                                              CO_OD_RAM.RW4

/*4021, Data Type: oreSatLive_t */
        #define OD_oreSatLive                                       CO_OD_RAM.oreSatLive

/*4022, Data Type: CFC_t */
        #define OD_CFC                                              CO_OD_RAM.CFC

/*4031, Data Type: protocard1_t */
        #define OD_protocard1                                       CO_OD_RAM.protocard1

/*4032, Data Type: protocard2_t */
        #define OD_protocard2                                       CO_OD_RAM.protocard2

/*4033, Data Type: protocard3_t */
        #define OD_protocard3                                       CO_OD_RAM.protocard3

#endif
// clang-format on
