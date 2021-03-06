// clang-format off
/*******************************************************************************
    CANopen Object Dictionary definition for CANopenNode v1 to v2

    This file was automatically generated with
    libedssharp Object Dictionary Editor v0.8-123-g6c02323

    https://github.com/CANopenNode/CANopenNode
    https://github.com/robincornelius/libedssharp

    DON'T EDIT THIS FILE MANUALLY !!!!
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


/*******************************************************************************
   FILE INFO:
      FileName:     app.xdd
      FileVersion:  0
      CreationTime: 2:51PM
      CreationDate: 08-12-2019
      CreatedBy:    Miles Simpson
*******************************************************************************/


/*******************************************************************************
   DEVICE INFO:
      VendorName:     Portland State Aerospace Society
      VendorNumber:   0
      ProductName:    OreSat Template
      ProductNumber:  0
*******************************************************************************/


/*******************************************************************************
   FEATURES
*******************************************************************************/
  #define CO_NO_SYNC                     1   //Associated objects: 1005-1007
  #define CO_NO_EMERGENCY                1   //Associated objects: 1014, 1015
  #define CO_NO_TIME                     0   //Associated objects: 1012, 1013
  #define CO_NO_SDO_SERVER               1   //Associated objects: 1200-127F
  #define CO_NO_SDO_CLIENT               0   //Associated objects: 1280-12FF
  #define CO_NO_GFC                      0   //Associated objects: 1300
  #define CO_NO_SRDO                     0   //Associated objects: 1301-1341, 1381-13C0
  #define CO_NO_LSS_SERVER               0   //LSS Slave
  #define CO_NO_LSS_CLIENT               0   //LSS Master
  #define CO_NO_RPDO                     16   //Associated objects: 14xx, 16xx
  #define CO_NO_TPDO                     16   //Associated objects: 18xx, 1Axx
  #define CO_NO_NMT_MASTER               0
  #define CO_NO_TRACE                    0


/*******************************************************************************
   OBJECT DICTIONARY
*******************************************************************************/
   #define CO_OD_NoOfElements             92


/*******************************************************************************
   TYPE DEFINITIONS FOR RECORDS
*******************************************************************************/
/*1018      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               UNSIGNED32     vendorID;
               UNSIGNED32     productCode;
               UNSIGNED32     revisionNumber;
               UNSIGNED32     serialNumber;
               }              OD_identity_t;
/*1023      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               DOMAIN         command;
               UNSIGNED8      status;
               DOMAIN         reply;
               }              OD_OSCommand_t;
/*1025      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               DOMAIN         command;
               UNSIGNED8      status;
               DOMAIN         reply;
               }              OD_OSDebuggerInterface_t;
/*1200      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               UNSIGNED32     COB_IDClientToServer;
               UNSIGNED32     COB_IDServerToClient;
               UNSIGNED8      nodeIDOfTheSDOClient;
               }              OD_SDOServerParameter_t;
/*1280      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               UNSIGNED32     COB_IDClientToServer;
               UNSIGNED32     COB_IDServerToClient;
               UNSIGNED8      nodeIDOfTheSDOServer;
               }              OD_SDOClientParameter_t;
/*1400      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               UNSIGNED32     COB_IDUsedByRPDO;
               UNSIGNED8      transmissionType;
               UNSIGNED16     eventTimer;
               }              OD_RPDOCommunicationParameter_t;
/*1600      */ typedef struct {
               UNSIGNED8      numberOfMappedApplicationObjectsInPDO;
               UNSIGNED32     applicationObject1;
               UNSIGNED32     applicationObject2;
               UNSIGNED32     applicationObject3;
               UNSIGNED32     applicationObject4;
               UNSIGNED32     applicationObject5;
               UNSIGNED32     applicationObject6;
               UNSIGNED32     applicationObject7;
               UNSIGNED32     applicationObject8;
               }              OD_RPDOMappingParameter_t;
/*1800      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               UNSIGNED32     COB_IDUsedByTPDO;
               UNSIGNED8      transmissionType;
               UNSIGNED16     inhibitTime;
               UNSIGNED8      compatibilityEntry;
               UNSIGNED16     eventTimer;
               UNSIGNED8      SYNCStartValue;
               }              OD_TPDOCommunicationParameter_t;
/*1A00      */ typedef struct {
               UNSIGNED8      numberOfMappedApplicationObjectsInPDO;
               UNSIGNED32     applicationObject1;
               UNSIGNED32     applicationObject2;
               UNSIGNED32     applicationObject3;
               UNSIGNED32     applicationObject4;
               UNSIGNED32     applicationObject5;
               UNSIGNED32     applicationObject6;
               UNSIGNED32     applicationObject7;
               UNSIGNED32     applicationObject8;
               }              OD_TPDOMappingParameter_t;
/*2000      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               UNSIGNED8      bdefault;
               UNSIGNED8      ttoggle;
               UNSIGNED8      ntoggle;
               UNSIGNED8      ctoggle;
               }              OD_BUS_Management_t;
/*2021      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               UNSIGNED16     TS_CAL1;
               UNSIGNED16     TS_CAL2;
               UNSIGNED16     VREFINT_CAL;
               }              OD_MCU_Calibration_t;
/*2022      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               INTEGER8       temperature;
               UNSIGNED8      VREFINT;
               UNSIGNED8      VBAT;
               UNSIGNED8      VBUSP_Current;
               UNSIGNED16     temperatureRaw;
               UNSIGNED16     VREFINT_Raw;
               UNSIGNED16     VBAT_Raw;
               UNSIGNED16     VBUSP_CurrentRaw;
               }              OD_MCU_Sensors_t;

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
        #define OD_1010_2_storeParameters_saveCommunicationParameters 2
        #define OD_1010_3_storeParameters_saveApplicationParameters 3
        #define OD_1010_4_storeParameters_saveManufacturerDefinedParameters 4

/*1011 */
        #define OD_1011_restoreDefaultParameters                    0x1011

        #define OD_1011_0_restoreDefaultParameters_maxSubIndex      0
        #define OD_1011_1_restoreDefaultParameters_restoreAllDefaultParameters 1
        #define OD_1011_2_restoreDefaultParameters_restoreCommunicationDefaultParameters 2
        #define OD_1011_3_restoreDefaultParameters_restoreApplicationDefaultParameters 3
        #define OD_1011_4_restoreDefaultParameters_restoreManufacturerDefinedDefaultParameters 4

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
        #define OD_1016_5_consumerHeartbeatTime_consumerHeartbeatTime 5
        #define OD_1016_6_consumerHeartbeatTime_consumerHeartbeatTime 6
        #define OD_1016_7_consumerHeartbeatTime_consumerHeartbeatTime 7
        #define OD_1016_8_consumerHeartbeatTime_consumerHeartbeatTime 8

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
        #define OD_1200_3_SDOServerParameter_nodeIDOfTheSDOClient   3

/*1400 */
        #define OD_1400_RPDOCommunicationParameter                  0x1400

        #define OD_1400_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1400_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1400_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_1400_5_RPDOCommunicationParameter_eventTimer     5

/*1401 */
        #define OD_1401_RPDOCommunicationParameter                  0x1401

        #define OD_1401_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1401_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1401_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_1401_5_RPDOCommunicationParameter_eventTimer     5

/*1402 */
        #define OD_1402_RPDOCommunicationParameter                  0x1402

        #define OD_1402_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1402_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1402_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_1402_5_RPDOCommunicationParameter_eventTimer     5

/*1403 */
        #define OD_1403_RPDOCommunicationParameter                  0x1403

        #define OD_1403_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1403_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1403_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_1403_5_RPDOCommunicationParameter_eventTimer     5

/*1404 */
        #define OD_1404_RPDOCommunicationParameter                  0x1404

        #define OD_1404_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1404_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1404_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_1404_5_RPDOCommunicationParameter_eventTimer     5

/*1405 */
        #define OD_1405_RPDOCommunicationParameter                  0x1405

        #define OD_1405_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1405_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1405_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_1405_5_RPDOCommunicationParameter_eventTimer     5

/*1406 */
        #define OD_1406_RPDOCommunicationParameter                  0x1406

        #define OD_1406_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1406_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1406_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_1406_5_RPDOCommunicationParameter_eventTimer     5

/*1407 */
        #define OD_1407_RPDOCommunicationParameter                  0x1407

        #define OD_1407_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1407_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1407_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_1407_5_RPDOCommunicationParameter_eventTimer     5

/*1408 */
        #define OD_1408_RPDOCommunicationParameter                  0x1408

        #define OD_1408_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1408_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1408_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_1408_5_RPDOCommunicationParameter_eventTimer     5

/*1409 */
        #define OD_1409_RPDOCommunicationParameter                  0x1409

        #define OD_1409_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1409_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1409_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_1409_5_RPDOCommunicationParameter_eventTimer     5

/*140A */
        #define OD_140A_RPDOCommunicationParameter                  0x140A

        #define OD_140A_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_140A_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_140A_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_140A_5_RPDOCommunicationParameter_eventTimer     5

/*140B */
        #define OD_140B_RPDOCommunicationParameter                  0x140B

        #define OD_140B_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_140B_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_140B_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_140B_5_RPDOCommunicationParameter_eventTimer     5

/*140C */
        #define OD_140C_RPDOCommunicationParameter                  0x140C

        #define OD_140C_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_140C_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_140C_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_140C_5_RPDOCommunicationParameter_eventTimer     5

/*140D */
        #define OD_140D_RPDOCommunicationParameter                  0x140D

        #define OD_140D_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_140D_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_140D_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_140D_5_RPDOCommunicationParameter_eventTimer     5

/*140E */
        #define OD_140E_RPDOCommunicationParameter                  0x140E

        #define OD_140E_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_140E_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_140E_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_140E_5_RPDOCommunicationParameter_eventTimer     5

/*140F */
        #define OD_140F_RPDOCommunicationParameter                  0x140F

        #define OD_140F_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_140F_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_140F_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_140F_5_RPDOCommunicationParameter_eventTimer     5

/*1600 */
        #define OD_1600_RPDOMappingParameter                        0x1600

        #define OD_1600_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1600_1_RPDOMappingParameter_applicationObject1   1
        #define OD_1600_2_RPDOMappingParameter_applicationObject2   2
        #define OD_1600_3_RPDOMappingParameter_applicationObject3   3
        #define OD_1600_4_RPDOMappingParameter_applicationObject4   4
        #define OD_1600_5_RPDOMappingParameter_applicationObject5   5
        #define OD_1600_6_RPDOMappingParameter_applicationObject6   6
        #define OD_1600_7_RPDOMappingParameter_applicationObject7   7
        #define OD_1600_8_RPDOMappingParameter_applicationObject8   8

/*1601 */
        #define OD_1601_RPDOMappingParameter                        0x1601

        #define OD_1601_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1601_1_RPDOMappingParameter_applicationObject1   1
        #define OD_1601_2_RPDOMappingParameter_applicationObject2   2
        #define OD_1601_3_RPDOMappingParameter_applicationObject3   3
        #define OD_1601_4_RPDOMappingParameter_applicationObject4   4
        #define OD_1601_5_RPDOMappingParameter_applicationObject5   5
        #define OD_1601_6_RPDOMappingParameter_applicationObject6   6
        #define OD_1601_7_RPDOMappingParameter_applicationObject7   7
        #define OD_1601_8_RPDOMappingParameter_applicationObject8   8

/*1602 */
        #define OD_1602_RPDOMappingParameter                        0x1602

        #define OD_1602_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1602_1_RPDOMappingParameter_applicationObject1   1
        #define OD_1602_2_RPDOMappingParameter_applicationObject2   2
        #define OD_1602_3_RPDOMappingParameter_applicationObject3   3
        #define OD_1602_4_RPDOMappingParameter_applicationObject4   4
        #define OD_1602_5_RPDOMappingParameter_applicationObject5   5
        #define OD_1602_6_RPDOMappingParameter_applicationObject6   6
        #define OD_1602_7_RPDOMappingParameter_applicationObject7   7
        #define OD_1602_8_RPDOMappingParameter_applicationObject8   8

/*1603 */
        #define OD_1603_RPDOMappingParameter                        0x1603

        #define OD_1603_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1603_1_RPDOMappingParameter_applicationObject1   1
        #define OD_1603_2_RPDOMappingParameter_applicationObject2   2
        #define OD_1603_3_RPDOMappingParameter_applicationObject3   3
        #define OD_1603_4_RPDOMappingParameter_applicationObject4   4
        #define OD_1603_5_RPDOMappingParameter_applicationObject5   5
        #define OD_1603_6_RPDOMappingParameter_applicationObject6   6
        #define OD_1603_7_RPDOMappingParameter_applicationObject7   7
        #define OD_1603_8_RPDOMappingParameter_applicationObject8   8

/*1604 */
        #define OD_1604_RPDOMappingParameter                        0x1604

        #define OD_1604_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1604_1_RPDOMappingParameter_applicationObject1   1
        #define OD_1604_2_RPDOMappingParameter_applicationObject2   2
        #define OD_1604_3_RPDOMappingParameter_applicationObject3   3
        #define OD_1604_4_RPDOMappingParameter_applicationObject4   4
        #define OD_1604_5_RPDOMappingParameter_applicationObject5   5
        #define OD_1604_6_RPDOMappingParameter_applicationObject6   6
        #define OD_1604_7_RPDOMappingParameter_applicationObject7   7
        #define OD_1604_8_RPDOMappingParameter_applicationObject8   8

/*1605 */
        #define OD_1605_RPDOMappingParameter                        0x1605

        #define OD_1605_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1605_1_RPDOMappingParameter_applicationObject1   1
        #define OD_1605_2_RPDOMappingParameter_applicationObject2   2
        #define OD_1605_3_RPDOMappingParameter_applicationObject3   3
        #define OD_1605_4_RPDOMappingParameter_applicationObject4   4
        #define OD_1605_5_RPDOMappingParameter_applicationObject5   5
        #define OD_1605_6_RPDOMappingParameter_applicationObject6   6
        #define OD_1605_7_RPDOMappingParameter_applicationObject7   7
        #define OD_1605_8_RPDOMappingParameter_applicationObject8   8

/*1606 */
        #define OD_1606_RPDOMappingParameter                        0x1606

        #define OD_1606_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1606_1_RPDOMappingParameter_applicationObject1   1
        #define OD_1606_2_RPDOMappingParameter_applicationObject2   2
        #define OD_1606_3_RPDOMappingParameter_applicationObject3   3
        #define OD_1606_4_RPDOMappingParameter_applicationObject4   4
        #define OD_1606_5_RPDOMappingParameter_applicationObject5   5
        #define OD_1606_6_RPDOMappingParameter_applicationObject6   6
        #define OD_1606_7_RPDOMappingParameter_applicationObject7   7
        #define OD_1606_8_RPDOMappingParameter_applicationObject8   8

/*1607 */
        #define OD_1607_RPDOMappingParameter                        0x1607

        #define OD_1607_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1607_1_RPDOMappingParameter_applicationObject1   1
        #define OD_1607_2_RPDOMappingParameter_applicationObject2   2
        #define OD_1607_3_RPDOMappingParameter_applicationObject3   3
        #define OD_1607_4_RPDOMappingParameter_applicationObject4   4
        #define OD_1607_5_RPDOMappingParameter_applicationObject5   5
        #define OD_1607_6_RPDOMappingParameter_applicationObject6   6
        #define OD_1607_7_RPDOMappingParameter_applicationObject7   7
        #define OD_1607_8_RPDOMappingParameter_applicationObject8   8

/*1608 */
        #define OD_1608_RPDOMappingParameter                        0x1608

        #define OD_1608_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1608_1_RPDOMappingParameter_applicationObject1   1
        #define OD_1608_2_RPDOMappingParameter_applicationObject2   2
        #define OD_1608_3_RPDOMappingParameter_applicationObject3   3
        #define OD_1608_4_RPDOMappingParameter_applicationObject4   4
        #define OD_1608_5_RPDOMappingParameter_applicationObject5   5
        #define OD_1608_6_RPDOMappingParameter_applicationObject6   6
        #define OD_1608_7_RPDOMappingParameter_applicationObject7   7
        #define OD_1608_8_RPDOMappingParameter_applicationObject8   8

/*1609 */
        #define OD_1609_RPDOMappingParameter                        0x1609

        #define OD_1609_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1609_1_RPDOMappingParameter_applicationObject1   1
        #define OD_1609_2_RPDOMappingParameter_applicationObject2   2
        #define OD_1609_3_RPDOMappingParameter_applicationObject3   3
        #define OD_1609_4_RPDOMappingParameter_applicationObject4   4
        #define OD_1609_5_RPDOMappingParameter_applicationObject5   5
        #define OD_1609_6_RPDOMappingParameter_applicationObject6   6
        #define OD_1609_7_RPDOMappingParameter_applicationObject7   7
        #define OD_1609_8_RPDOMappingParameter_applicationObject8   8

/*160A */
        #define OD_160A_RPDOMappingParameter                        0x160A

        #define OD_160A_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_160A_1_RPDOMappingParameter_applicationObject1   1
        #define OD_160A_2_RPDOMappingParameter_applicationObject2   2
        #define OD_160A_3_RPDOMappingParameter_applicationObject3   3
        #define OD_160A_4_RPDOMappingParameter_applicationObject4   4
        #define OD_160A_5_RPDOMappingParameter_applicationObject5   5
        #define OD_160A_6_RPDOMappingParameter_applicationObject6   6
        #define OD_160A_7_RPDOMappingParameter_applicationObject7   7
        #define OD_160A_8_RPDOMappingParameter_applicationObject8   8

/*160B */
        #define OD_160B_RPDOMappingParameter                        0x160B

        #define OD_160B_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_160B_1_RPDOMappingParameter_applicationObject1   1
        #define OD_160B_2_RPDOMappingParameter_applicationObject2   2
        #define OD_160B_3_RPDOMappingParameter_applicationObject3   3
        #define OD_160B_4_RPDOMappingParameter_applicationObject4   4
        #define OD_160B_5_RPDOMappingParameter_applicationObject5   5
        #define OD_160B_6_RPDOMappingParameter_applicationObject6   6
        #define OD_160B_7_RPDOMappingParameter_applicationObject7   7
        #define OD_160B_8_RPDOMappingParameter_applicationObject8   8

/*160C */
        #define OD_160C_RPDOMappingParameter                        0x160C

        #define OD_160C_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_160C_1_RPDOMappingParameter_applicationObject1   1
        #define OD_160C_2_RPDOMappingParameter_applicationObject2   2
        #define OD_160C_3_RPDOMappingParameter_applicationObject3   3
        #define OD_160C_4_RPDOMappingParameter_applicationObject4   4
        #define OD_160C_5_RPDOMappingParameter_applicationObject5   5
        #define OD_160C_6_RPDOMappingParameter_applicationObject6   6
        #define OD_160C_7_RPDOMappingParameter_applicationObject7   7
        #define OD_160C_8_RPDOMappingParameter_applicationObject8   8

/*160D */
        #define OD_160D_RPDOMappingParameter                        0x160D

        #define OD_160D_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_160D_1_RPDOMappingParameter_applicationObject1   1
        #define OD_160D_2_RPDOMappingParameter_applicationObject2   2
        #define OD_160D_3_RPDOMappingParameter_applicationObject3   3
        #define OD_160D_4_RPDOMappingParameter_applicationObject4   4
        #define OD_160D_5_RPDOMappingParameter_applicationObject5   5
        #define OD_160D_6_RPDOMappingParameter_applicationObject6   6
        #define OD_160D_7_RPDOMappingParameter_applicationObject7   7
        #define OD_160D_8_RPDOMappingParameter_applicationObject8   8

/*160E */
        #define OD_160E_RPDOMappingParameter                        0x160E

        #define OD_160E_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_160E_1_RPDOMappingParameter_applicationObject1   1
        #define OD_160E_2_RPDOMappingParameter_applicationObject2   2
        #define OD_160E_3_RPDOMappingParameter_applicationObject3   3
        #define OD_160E_4_RPDOMappingParameter_applicationObject4   4
        #define OD_160E_5_RPDOMappingParameter_applicationObject5   5
        #define OD_160E_6_RPDOMappingParameter_applicationObject6   6
        #define OD_160E_7_RPDOMappingParameter_applicationObject7   7
        #define OD_160E_8_RPDOMappingParameter_applicationObject8   8

/*160F */
        #define OD_160F_RPDOMappingParameter                        0x160F

        #define OD_160F_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_160F_1_RPDOMappingParameter_applicationObject1   1
        #define OD_160F_2_RPDOMappingParameter_applicationObject2   2
        #define OD_160F_3_RPDOMappingParameter_applicationObject3   3
        #define OD_160F_4_RPDOMappingParameter_applicationObject4   4
        #define OD_160F_5_RPDOMappingParameter_applicationObject5   5
        #define OD_160F_6_RPDOMappingParameter_applicationObject6   6
        #define OD_160F_7_RPDOMappingParameter_applicationObject7   7
        #define OD_160F_8_RPDOMappingParameter_applicationObject8   8

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
        #define OD_1A00_1_TPDOMappingParameter_applicationObject1   1
        #define OD_1A00_2_TPDOMappingParameter_applicationObject2   2
        #define OD_1A00_3_TPDOMappingParameter_applicationObject3   3
        #define OD_1A00_4_TPDOMappingParameter_applicationObject4   4
        #define OD_1A00_5_TPDOMappingParameter_applicationObject5   5
        #define OD_1A00_6_TPDOMappingParameter_applicationObject6   6
        #define OD_1A00_7_TPDOMappingParameter_applicationObject7   7
        #define OD_1A00_8_TPDOMappingParameter_applicationObject8   8

/*1A01 */
        #define OD_1A01_TPDOMappingParameter                        0x1A01

        #define OD_1A01_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A01_1_TPDOMappingParameter_applicationObject1   1
        #define OD_1A01_2_TPDOMappingParameter_applicationObject2   2
        #define OD_1A01_3_TPDOMappingParameter_applicationObject3   3
        #define OD_1A01_4_TPDOMappingParameter_applicationObject4   4
        #define OD_1A01_5_TPDOMappingParameter_applicationObject5   5
        #define OD_1A01_6_TPDOMappingParameter_applicationObject6   6
        #define OD_1A01_7_TPDOMappingParameter_applicationObject7   7
        #define OD_1A01_8_TPDOMappingParameter_applicationObject8   8

/*1A02 */
        #define OD_1A02_TPDOMappingParameter                        0x1A02

        #define OD_1A02_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A02_1_TPDOMappingParameter_applicationObject1   1
        #define OD_1A02_2_TPDOMappingParameter_applicationObject2   2
        #define OD_1A02_3_TPDOMappingParameter_applicationObject3   3
        #define OD_1A02_4_TPDOMappingParameter_applicationObject4   4
        #define OD_1A02_5_TPDOMappingParameter_applicationObject5   5
        #define OD_1A02_6_TPDOMappingParameter_applicationObject6   6
        #define OD_1A02_7_TPDOMappingParameter_applicationObject7   7
        #define OD_1A02_8_TPDOMappingParameter_applicationObject8   8

/*1A03 */
        #define OD_1A03_TPDOMappingParameter                        0x1A03

        #define OD_1A03_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A03_1_TPDOMappingParameter_applicationObject1   1
        #define OD_1A03_2_TPDOMappingParameter_applicationObject2   2
        #define OD_1A03_3_TPDOMappingParameter_applicationObject3   3
        #define OD_1A03_4_TPDOMappingParameter_applicationObject4   4
        #define OD_1A03_5_TPDOMappingParameter_applicationObject5   5
        #define OD_1A03_6_TPDOMappingParameter_applicationObject6   6
        #define OD_1A03_7_TPDOMappingParameter_applicationObject7   7
        #define OD_1A03_8_TPDOMappingParameter_applicationObject8   8

/*1A04 */
        #define OD_1A04_TPDOMappingParameter                        0x1A04

        #define OD_1A04_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A04_1_TPDOMappingParameter_applicationObject1   1
        #define OD_1A04_2_TPDOMappingParameter_applicationObject2   2
        #define OD_1A04_3_TPDOMappingParameter_applicationObject3   3
        #define OD_1A04_4_TPDOMappingParameter_applicationObject4   4
        #define OD_1A04_5_TPDOMappingParameter_applicationObject5   5
        #define OD_1A04_6_TPDOMappingParameter_applicationObject6   6
        #define OD_1A04_7_TPDOMappingParameter_applicationObject7   7
        #define OD_1A04_8_TPDOMappingParameter_applicationObject8   8

/*1A05 */
        #define OD_1A05_TPDOMappingParameter                        0x1A05

        #define OD_1A05_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A05_1_TPDOMappingParameter_applicationObject1   1
        #define OD_1A05_2_TPDOMappingParameter_applicationObject2   2
        #define OD_1A05_3_TPDOMappingParameter_applicationObject3   3
        #define OD_1A05_4_TPDOMappingParameter_applicationObject4   4
        #define OD_1A05_5_TPDOMappingParameter_applicationObject5   5
        #define OD_1A05_6_TPDOMappingParameter_applicationObject6   6
        #define OD_1A05_7_TPDOMappingParameter_applicationObject7   7
        #define OD_1A05_8_TPDOMappingParameter_applicationObject8   8

/*1A06 */
        #define OD_1A06_TPDOMappingParameter                        0x1A06

        #define OD_1A06_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A06_1_TPDOMappingParameter_applicationObject1   1
        #define OD_1A06_2_TPDOMappingParameter_applicationObject2   2
        #define OD_1A06_3_TPDOMappingParameter_applicationObject3   3
        #define OD_1A06_4_TPDOMappingParameter_applicationObject4   4
        #define OD_1A06_5_TPDOMappingParameter_applicationObject5   5
        #define OD_1A06_6_TPDOMappingParameter_applicationObject6   6
        #define OD_1A06_7_TPDOMappingParameter_applicationObject7   7
        #define OD_1A06_8_TPDOMappingParameter_applicationObject8   8

/*1A07 */
        #define OD_1A07_TPDOMappingParameter                        0x1A07

        #define OD_1A07_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A07_1_TPDOMappingParameter_applicationObject1   1
        #define OD_1A07_2_TPDOMappingParameter_applicationObject2   2
        #define OD_1A07_3_TPDOMappingParameter_applicationObject3   3
        #define OD_1A07_4_TPDOMappingParameter_applicationObject4   4
        #define OD_1A07_5_TPDOMappingParameter_applicationObject5   5
        #define OD_1A07_6_TPDOMappingParameter_applicationObject6   6
        #define OD_1A07_7_TPDOMappingParameter_applicationObject7   7
        #define OD_1A07_8_TPDOMappingParameter_applicationObject8   8

/*1A08 */
        #define OD_1A08_TPDOMappingParameter                        0x1A08

        #define OD_1A08_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A08_1_TPDOMappingParameter_applicationObject1   1
        #define OD_1A08_2_TPDOMappingParameter_applicationObject2   2
        #define OD_1A08_3_TPDOMappingParameter_applicationObject3   3
        #define OD_1A08_4_TPDOMappingParameter_applicationObject4   4
        #define OD_1A08_5_TPDOMappingParameter_applicationObject5   5
        #define OD_1A08_6_TPDOMappingParameter_applicationObject6   6
        #define OD_1A08_7_TPDOMappingParameter_applicationObject7   7
        #define OD_1A08_8_TPDOMappingParameter_applicationObject8   8

/*1A09 */
        #define OD_1A09_TPDOMappingParameter                        0x1A09

        #define OD_1A09_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A09_1_TPDOMappingParameter_applicationObject1   1
        #define OD_1A09_2_TPDOMappingParameter_applicationObject2   2
        #define OD_1A09_3_TPDOMappingParameter_applicationObject3   3
        #define OD_1A09_4_TPDOMappingParameter_applicationObject4   4
        #define OD_1A09_5_TPDOMappingParameter_applicationObject5   5
        #define OD_1A09_6_TPDOMappingParameter_applicationObject6   6
        #define OD_1A09_7_TPDOMappingParameter_applicationObject7   7
        #define OD_1A09_8_TPDOMappingParameter_applicationObject8   8

/*1A0A */
        #define OD_1A0A_TPDOMappingParameter                        0x1A0A

        #define OD_1A0A_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A0A_1_TPDOMappingParameter_applicationObject1   1
        #define OD_1A0A_2_TPDOMappingParameter_applicationObject2   2
        #define OD_1A0A_3_TPDOMappingParameter_applicationObject3   3
        #define OD_1A0A_4_TPDOMappingParameter_applicationObject4   4
        #define OD_1A0A_5_TPDOMappingParameter_applicationObject5   5
        #define OD_1A0A_6_TPDOMappingParameter_applicationObject6   6
        #define OD_1A0A_7_TPDOMappingParameter_applicationObject7   7
        #define OD_1A0A_8_TPDOMappingParameter_applicationObject8   8

/*1A0B */
        #define OD_1A0B_TPDOMappingParameter                        0x1A0B

        #define OD_1A0B_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A0B_1_TPDOMappingParameter_applicationObject1   1
        #define OD_1A0B_2_TPDOMappingParameter_applicationObject2   2
        #define OD_1A0B_3_TPDOMappingParameter_applicationObject3   3
        #define OD_1A0B_4_TPDOMappingParameter_applicationObject4   4
        #define OD_1A0B_5_TPDOMappingParameter_applicationObject5   5
        #define OD_1A0B_6_TPDOMappingParameter_applicationObject6   6
        #define OD_1A0B_7_TPDOMappingParameter_applicationObject7   7
        #define OD_1A0B_8_TPDOMappingParameter_applicationObject8   8

/*1A0C */
        #define OD_1A0C_TPDOMappingParameter                        0x1A0C

        #define OD_1A0C_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A0C_1_TPDOMappingParameter_applicationObject1   1
        #define OD_1A0C_2_TPDOMappingParameter_applicationObject2   2
        #define OD_1A0C_3_TPDOMappingParameter_applicationObject3   3
        #define OD_1A0C_4_TPDOMappingParameter_applicationObject4   4
        #define OD_1A0C_5_TPDOMappingParameter_applicationObject5   5
        #define OD_1A0C_6_TPDOMappingParameter_applicationObject6   6
        #define OD_1A0C_7_TPDOMappingParameter_applicationObject7   7
        #define OD_1A0C_8_TPDOMappingParameter_applicationObject8   8

/*1A0D */
        #define OD_1A0D_TPDOMappingParameter                        0x1A0D

        #define OD_1A0D_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A0D_1_TPDOMappingParameter_applicationObject1   1
        #define OD_1A0D_2_TPDOMappingParameter_applicationObject2   2
        #define OD_1A0D_3_TPDOMappingParameter_applicationObject3   3
        #define OD_1A0D_4_TPDOMappingParameter_applicationObject4   4
        #define OD_1A0D_5_TPDOMappingParameter_applicationObject5   5
        #define OD_1A0D_6_TPDOMappingParameter_applicationObject6   6
        #define OD_1A0D_7_TPDOMappingParameter_applicationObject7   7
        #define OD_1A0D_8_TPDOMappingParameter_applicationObject8   8

/*1A0E */
        #define OD_1A0E_TPDOMappingParameter                        0x1A0E

        #define OD_1A0E_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A0E_1_TPDOMappingParameter_applicationObject1   1
        #define OD_1A0E_2_TPDOMappingParameter_applicationObject2   2
        #define OD_1A0E_3_TPDOMappingParameter_applicationObject3   3
        #define OD_1A0E_4_TPDOMappingParameter_applicationObject4   4
        #define OD_1A0E_5_TPDOMappingParameter_applicationObject5   5
        #define OD_1A0E_6_TPDOMappingParameter_applicationObject6   6
        #define OD_1A0E_7_TPDOMappingParameter_applicationObject7   7
        #define OD_1A0E_8_TPDOMappingParameter_applicationObject8   8

/*1A0F */
        #define OD_1A0F_TPDOMappingParameter                        0x1A0F

        #define OD_1A0F_0_TPDOMappingParameter_maxSubIndex          0
        #define OD_1A0F_1_TPDOMappingParameter_applicationObject1   1
        #define OD_1A0F_2_TPDOMappingParameter_applicationObject2   2
        #define OD_1A0F_3_TPDOMappingParameter_applicationObject3   3
        #define OD_1A0F_4_TPDOMappingParameter_applicationObject4   4
        #define OD_1A0F_5_TPDOMappingParameter_applicationObject5   5
        #define OD_1A0F_6_TPDOMappingParameter_applicationObject6   6
        #define OD_1A0F_7_TPDOMappingParameter_applicationObject7   7
        #define OD_1A0F_8_TPDOMappingParameter_applicationObject8   8

/*1F80 */
        #define OD_1F80_NMTStartup                                  0x1F80

/*2000 */
        #define OD_2000_BUS_Management                              0x2000

        #define OD_2000_0_BUS_Management_maxSubIndex                0
        #define OD_2000_1_BUS_Management_bdefault                   1
        #define OD_2000_2_BUS_Management_ttoggle                    2
        #define OD_2000_3_BUS_Management_ntoggle                    3
        #define OD_2000_4_BUS_Management_ctoggle                    4

/*2010 */
        #define OD_2010_SCET                                        0x2010

/*2011 */
        #define OD_2011_UTC                                         0x2011

/*2020 */
        #define OD_2020_MCU_UniqueDeviceID                          0x2020

        #define OD_2020_0_MCU_UniqueDeviceID_maxSubIndex            0
        #define OD_2020_1_MCU_UniqueDeviceID_UID                    1
        #define OD_2020_2_MCU_UniqueDeviceID_UID                    2
        #define OD_2020_3_MCU_UniqueDeviceID_UID                    3

/*2021 */
        #define OD_2021_MCU_Calibration                             0x2021

        #define OD_2021_0_MCU_Calibration_maxSubIndex               0
        #define OD_2021_1_MCU_Calibration_TS_CAL1                   1
        #define OD_2021_2_MCU_Calibration_TS_CAL2                   2
        #define OD_2021_3_MCU_Calibration_VREFINT_CAL               3

/*2022 */
        #define OD_2022_MCU_Sensors                                 0x2022

        #define OD_2022_0_MCU_Sensors_maxSubIndex                   0
        #define OD_2022_1_MCU_Sensors_temperature                   1
        #define OD_2022_2_MCU_Sensors_VREFINT                       2
        #define OD_2022_3_MCU_Sensors_VBAT                          3
        #define OD_2022_4_MCU_Sensors_VBUSP_Current                 4
        #define OD_2022_5_MCU_Sensors_temperatureRaw                5
        #define OD_2022_6_MCU_Sensors_VREFINT_Raw                   6
        #define OD_2022_7_MCU_Sensors_VBAT_Raw                      7
        #define OD_2022_8_MCU_Sensors_VBUSP_CurrentRaw              8

/*2100 */
        #define OD_2100_errorStatusBits                             0x2100

/*******************************************************************************
   STRUCTURES FOR VARIABLES IN DIFFERENT MEMORY LOCATIONS
*******************************************************************************/
#define  CO_OD_FIRST_LAST_WORD     0x55 //Any value from 0x01 to 0xFE. If changed, EEPROM will be reinitialized.

/***** Structure for RAM variables ********************************************/
struct sCO_OD_RAM{
               UNSIGNED32     FirstWord;

/*1001      */ UNSIGNED8      errorRegister;
/*1002      */ UNSIGNED32     manufacturerStatusRegister;
/*1003      */ UNSIGNED32      preDefinedErrorField[8];
/*1010      */ UNSIGNED32      storeParameters[4];
/*1011      */ UNSIGNED32      restoreDefaultParameters[4];
/*2010      */ UNSIGNED64     SCET;
/*2011      */ UNSIGNED64     UTC;
/*2020      */ UNSIGNED32      MCU_UniqueDeviceID[3];
/*2021      */ OD_MCU_Calibration_t MCU_Calibration;
/*2022      */ OD_MCU_Sensors_t MCU_Sensors;
/*2100      */ OCTET_STRING   errorStatusBits[10];

               UNSIGNED32     LastWord;
};

/***** Structure for ROM variables ********************************************/
struct sCO_OD_ROM{
               UNSIGNED32     FirstWord;

/*1000      */ UNSIGNED32     deviceType;
/*1008      */ VISIBLE_STRING manufacturerDeviceName[11];
/*1009      */ VISIBLE_STRING manufacturerHardwareVersion[3];
/*100A      */ VISIBLE_STRING manufacturerSoftwareVersion[5];
/*1018      */ OD_identity_t   identity;
/*1029      */ UNSIGNED8       errorBehavior[6];

               UNSIGNED32     LastWord;
};

/***** Structure for EEPROM variables ********************************************/
struct sCO_OD_EEPROM{
               UNSIGNED32     FirstWord;


               UNSIGNED32     LastWord;
};

/***** Structure for PERSIST_COMM variables ********************************************/
struct sCO_OD_PERSIST_COMM{
               UNSIGNED32     FirstWord;

/*1005      */ UNSIGNED32     COB_ID_SYNCMessage;
/*1006      */ UNSIGNED32     communicationCyclePeriod;
/*1007      */ UNSIGNED32     synchronousWindowLength;
/*1014      */ UNSIGNED32     COB_ID_EMCY;
/*1015      */ UNSIGNED16     inhibitTimeEMCY;
/*1016      */ UNSIGNED32      consumerHeartbeatTime[8];
/*1017      */ UNSIGNED16     producerHeartbeatTime;
/*1019      */ UNSIGNED8      synchronousCounterOverflowValue;
/*1200      */ OD_SDOServerParameter_t SDOServerParameter[1];
/*1400      */ OD_RPDOCommunicationParameter_t RPDOCommunicationParameter[16];
/*1600      */ OD_RPDOMappingParameter_t RPDOMappingParameter[16];
/*1800      */ OD_TPDOCommunicationParameter_t TPDOCommunicationParameter[16];
/*1A00      */ OD_TPDOMappingParameter_t TPDOMappingParameter[16];
/*1F80      */ UNSIGNED32     NMTStartup;

               UNSIGNED32     LastWord;
};

/***** Structure for PERSIST_MFR variables ********************************************/
struct sCO_OD_PERSIST_MFR{
               UNSIGNED32     FirstWord;

/*2000      */ OD_BUS_Management_t BUS_Management;

               UNSIGNED32     LastWord;
};

/***** Declaration of Object Dictionary variables *****************************/
extern struct sCO_OD_RAM CO_OD_RAM;

extern struct sCO_OD_ROM CO_OD_ROM;

extern struct sCO_OD_EEPROM CO_OD_EEPROM;

extern struct sCO_OD_PERSIST_COMM CO_OD_PERSIST_COMM;

extern struct sCO_OD_PERSIST_MFR CO_OD_PERSIST_MFR;

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
        #define OD_COB_ID_SYNCMessage                               CO_OD_PERSIST_COMM.COB_ID_SYNCMessage

/*1006, Data Type: UNSIGNED32 */
        #define OD_communicationCyclePeriod                         CO_OD_PERSIST_COMM.communicationCyclePeriod

/*1007, Data Type: UNSIGNED32 */
        #define OD_synchronousWindowLength                          CO_OD_PERSIST_COMM.synchronousWindowLength

/*1008, Data Type: VISIBLE_STRING */
        #define OD_manufacturerDeviceName                           CO_OD_ROM.manufacturerDeviceName
        #define ODL_manufacturerDeviceName_stringLength             11

/*1009, Data Type: VISIBLE_STRING */
        #define OD_manufacturerHardwareVersion                      CO_OD_ROM.manufacturerHardwareVersion
        #define ODL_manufacturerHardwareVersion_stringLength        3

/*100A, Data Type: VISIBLE_STRING */
        #define OD_manufacturerSoftwareVersion                      CO_OD_ROM.manufacturerSoftwareVersion
        #define ODL_manufacturerSoftwareVersion_stringLength        5

/*1010, Data Type: UNSIGNED32, Array[4] */
        #define OD_storeParameters                                  CO_OD_RAM.storeParameters
        #define ODL_storeParameters_arrayLength                     4
        #define ODA_storeParameters_saveAllParameters               0
        #define ODA_storeParameters_saveCommunicationParameters     1
        #define ODA_storeParameters_saveApplicationParameters       2
        #define ODA_storeParameters_saveManufacturerDefinedParameters 3

/*1011, Data Type: UNSIGNED32, Array[4] */
        #define OD_restoreDefaultParameters                         CO_OD_RAM.restoreDefaultParameters
        #define ODL_restoreDefaultParameters_arrayLength            4
        #define ODA_restoreDefaultParameters_restoreAllDefaultParameters 0
        #define ODA_restoreDefaultParameters_restoreCommunicationDefaultParameters 1
        #define ODA_restoreDefaultParameters_restoreApplicationDefaultParameters 2
        #define ODA_restoreDefaultParameters_restoreManufacturerDefinedDefaultParameters 3

/*1014, Data Type: UNSIGNED32 */
        #define OD_COB_ID_EMCY                                      CO_OD_PERSIST_COMM.COB_ID_EMCY

/*1015, Data Type: UNSIGNED16 */
        #define OD_inhibitTimeEMCY                                  CO_OD_PERSIST_COMM.inhibitTimeEMCY

/*1016, Data Type: UNSIGNED32, Array[8] */
        #define OD_consumerHeartbeatTime                            CO_OD_PERSIST_COMM.consumerHeartbeatTime
        #define ODL_consumerHeartbeatTime_arrayLength               8
        #define ODA_consumerHeartbeatTime_consumerHeartbeatTime     0

/*1017, Data Type: UNSIGNED16 */
        #define OD_producerHeartbeatTime                            CO_OD_PERSIST_COMM.producerHeartbeatTime

/*1018, Data Type: identity_t */
        #define OD_identity                                         CO_OD_ROM.identity

/*1019, Data Type: UNSIGNED8 */
        #define OD_synchronousCounterOverflowValue                  CO_OD_PERSIST_COMM.synchronousCounterOverflowValue

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
        #define OD_SDOServerParameter                               CO_OD_PERSIST_COMM.SDOServerParameter

/*1400, Data Type: RPDOCommunicationParameter_t */
        #define OD_RPDOCommunicationParameter                       CO_OD_PERSIST_COMM.RPDOCommunicationParameter

/*1600, Data Type: RPDOMappingParameter_t */
        #define OD_RPDOMappingParameter                             CO_OD_PERSIST_COMM.RPDOMappingParameter

/*1800, Data Type: TPDOCommunicationParameter_t */
        #define OD_TPDOCommunicationParameter                       CO_OD_PERSIST_COMM.TPDOCommunicationParameter

/*1A00, Data Type: TPDOMappingParameter_t */
        #define OD_TPDOMappingParameter                             CO_OD_PERSIST_COMM.TPDOMappingParameter

/*1F80, Data Type: UNSIGNED32 */
        #define OD_NMTStartup                                       CO_OD_PERSIST_COMM.NMTStartup

/*2000, Data Type: BUS_Management_t */
        #define OD_BUS_Management                                   CO_OD_PERSIST_MFR.BUS_Management

/*2010, Data Type: UNSIGNED64 */
        #define OD_SCET                                             CO_OD_RAM.SCET

/*2011, Data Type: UNSIGNED64 */
        #define OD_UTC                                              CO_OD_RAM.UTC

/*2020, Data Type: UNSIGNED32, Array[3] */
        #define OD_MCU_UniqueDeviceID                               CO_OD_RAM.MCU_UniqueDeviceID
        #define ODL_MCU_UniqueDeviceID_arrayLength                  3
        #define ODA_MCU_UniqueDeviceID_UID                          0

/*2021, Data Type: MCU_Calibration_t */
        #define OD_MCU_Calibration                                  CO_OD_RAM.MCU_Calibration

/*2022, Data Type: MCU_Sensors_t */
        #define OD_MCU_Sensors                                      CO_OD_RAM.MCU_Sensors

/*2100, Data Type: OCTET_STRING */
        #define OD_errorStatusBits                                  CO_OD_RAM.errorStatusBits
        #define ODL_errorStatusBits_stringLength                    10

#endif
// clang-format on
