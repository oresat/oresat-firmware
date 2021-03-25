// clang-format off
/*******************************************************************************
    CANopen Object Dictionary definition for CANopenNode v1 to v2

    This file was automatically generated with
    libedssharp Object Dictionary Editor v0.8-121-g3349c4d

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
      CreationTime: 11:18AM
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
  #define CO_NO_RPDO                     4   //Associated objects: 14xx, 16xx
  #define CO_NO_TPDO                     4   //Associated objects: 18xx, 1Axx
  #define CO_NO_NMT_MASTER               0
  #define CO_NO_TRACE                    0


/*******************************************************************************
   OBJECT DICTIONARY
*******************************************************************************/
   #define CO_OD_NoOfElements             50


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
/*2020      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               UNSIGNED16     TS_CAL1;
               UNSIGNED16     TS_CAL2;
               UNSIGNED16     VREFINT_CAL;
               }              OD_MCU_Calibration_t;
/*2021      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               INTEGER8       temperature;
               INTEGER16      VREFINT;
               INTEGER16      VBAT;
               UNSIGNED16     temperatureRaw;
               UNSIGNED16     VREFINT_Raw;
               UNSIGNED16     VBAT_Raw;
               }              OD_MCU_Sensors_t;
/*6001      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               BOOLEAN        enabled;
               UNSIGNED32     TX_Timeout;
               UNSIGNED32     beaconInterval;
               }              OD_TX_Control_t;

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

/*1028 */
        #define OD_1028_emergencyConsumerObject                     0x1028

        #define OD_1028_0_emergencyConsumerObject_maxSubIndex       0
        #define OD_1028_1_emergencyConsumerObject_emergencyConsumer1 1
        #define OD_1028_2_emergencyConsumerObject_emergencyConsumer2 2
        #define OD_1028_3_emergencyConsumerObject_emergencyConsumer3 3
        #define OD_1028_4_emergencyConsumerObject_emergencyConsumer4 4
        #define OD_1028_5_emergencyConsumerObject_emergencyConsumer5 5
        #define OD_1028_6_emergencyConsumerObject_emergencyConsumer6 6
        #define OD_1028_7_emergencyConsumerObject_emergencyConsumer7 7
        #define OD_1028_8_emergencyConsumerObject_emergencyConsumer8 8

/*1029 */
        #define OD_1029_errorBehavior                               0x1029

        #define OD_1029_0_errorBehavior_maxSubIndex                 0
        #define OD_1029_1_errorBehavior_communicationError          1
        #define OD_1029_2_errorBehavior_profileOrManufacturerSpecificError 2

/*1200 */
        #define OD_1200_SDOServerParameter                          0x1200

        #define OD_1200_0_SDOServerParameter_maxSubIndex            0
        #define OD_1200_1_SDOServerParameter_COB_IDClientToServer   1
        #define OD_1200_2_SDOServerParameter_COB_IDServerToClient   2
        #define OD_1200_3_SDOServerParameter_nodeIDOfTheSDOClient   3

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
        #define OD_2020_MCU_Calibration                             0x2020

        #define OD_2020_0_MCU_Calibration_maxSubIndex               0
        #define OD_2020_1_MCU_Calibration_TS_CAL1                   1
        #define OD_2020_2_MCU_Calibration_TS_CAL2                   2
        #define OD_2020_3_MCU_Calibration_VREFINT_CAL               3

/*2021 */
        #define OD_2021_MCU_Sensors                                 0x2021

        #define OD_2021_0_MCU_Sensors_maxSubIndex                   0
        #define OD_2021_1_MCU_Sensors_temperature                   1
        #define OD_2021_2_MCU_Sensors_VREFINT                       2
        #define OD_2021_3_MCU_Sensors_VBAT                          3
        #define OD_2021_4_MCU_Sensors_temperatureRaw                4
        #define OD_2021_5_MCU_Sensors_VREFINT_Raw                   5
        #define OD_2021_6_MCU_Sensors_VBAT_Raw                      6

/*2100 */
        #define OD_2100_errorStatusBits                             0x2100

/*6000 */
        #define OD_6000_C3State                                     0x6000

/*6001 */
        #define OD_6001_TX_Control                                  0x6001

        #define OD_6001_0_TX_Control_maxSubIndex                    0
        #define OD_6001_1_TX_Control_enabled                        1
        #define OD_6001_2_TX_Control_TX_Timeout                     2
        #define OD_6001_3_TX_Control_beaconInterval                 3

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
/*1F89      */ UNSIGNED32     bootTime;
/*2010      */ UNSIGNED64     SCET;
/*2011      */ UNSIGNED64     UTC;
/*2020      */ OD_MCU_Calibration_t MCU_Calibration;
/*2021      */ OD_MCU_Sensors_t MCU_Sensors;
/*2100      */ OCTET_STRING   errorStatusBits[10];
/*6000      */ VISIBLE_STRING C3State[1];

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
/*1028      */ UNSIGNED32      emergencyConsumerObject[8];
/*1029      */ UNSIGNED8       errorBehavior[2];
/*1200      */ OD_SDOServerParameter_t SDOServerParameter[1];
/*1280      */ OD_SDOClientParameter_t SDOClientParameter[1];
/*1400      */ OD_RPDOCommunicationParameter_t RPDOCommunicationParameter[4];
/*1600      */ OD_RPDOMappingParameter_t RPDOMappingParameter[4];
/*1800      */ OD_TPDOCommunicationParameter_t TPDOCommunicationParameter[4];
/*1A00      */ OD_TPDOMappingParameter_t TPDOMappingParameter[4];
/*1F80      */ UNSIGNED32     NMTStartup;
/*1F81      */ UNSIGNED32      slaveAssignment[127];
/*1F82      */ UNSIGNED8       requestNMT[127];

               UNSIGNED32     LastWord;
};

/***** Structure for PERSIST_MFR variables ********************************************/
struct sCO_OD_PERSIST_MFR{
               UNSIGNED32     FirstWord;

/*2000      */ OD_BUS_Management_t BUS_Management;

               UNSIGNED32     LastWord;
};

/***** Structure for PERSIST_APP variables ********************************************/
struct sCO_OD_PERSIST_APP{
               UNSIGNED32     FirstWord;

/*6001      */ OD_TX_Control_t TX_Control;

               UNSIGNED32     LastWord;
};

/***** Declaration of Object Dictionary variables *****************************/
extern struct sCO_OD_RAM CO_OD_RAM;

extern struct sCO_OD_ROM CO_OD_ROM;

extern struct sCO_OD_EEPROM CO_OD_EEPROM;

extern struct sCO_OD_PERSIST_COMM CO_OD_PERSIST_COMM;

extern struct sCO_OD_PERSIST_MFR CO_OD_PERSIST_MFR;

extern struct sCO_OD_PERSIST_APP CO_OD_PERSIST_APP;

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

/*1028, Data Type: UNSIGNED32, Array[8] */
        #define OD_emergencyConsumerObject                          CO_OD_PERSIST_COMM.emergencyConsumerObject
        #define ODL_emergencyConsumerObject_arrayLength             8
        #define ODA_emergencyConsumerObject_emergencyConsumer1      0
        #define ODA_emergencyConsumerObject_emergencyConsumer2      1
        #define ODA_emergencyConsumerObject_emergencyConsumer3      2
        #define ODA_emergencyConsumerObject_emergencyConsumer4      3
        #define ODA_emergencyConsumerObject_emergencyConsumer5      4
        #define ODA_emergencyConsumerObject_emergencyConsumer6      5
        #define ODA_emergencyConsumerObject_emergencyConsumer7      6
        #define ODA_emergencyConsumerObject_emergencyConsumer8      7

/*1029, Data Type: UNSIGNED8, Array[2] */
        #define OD_errorBehavior                                    CO_OD_PERSIST_COMM.errorBehavior
        #define ODL_errorBehavior_arrayLength                       2
        #define ODA_errorBehavior_communicationError                0
        #define ODA_errorBehavior_profileOrManufacturerSpecificError 1

/*1200, Data Type: SDOServerParameter_t */
        #define OD_SDOServerParameter                               CO_OD_PERSIST_COMM.SDOServerParameter

/*1280, Data Type: SDOClientParameter_t */
        #define OD_SDOClientParameter                               CO_OD_PERSIST_COMM.SDOClientParameter

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

/*1F81, Data Type: UNSIGNED32, Array[127] */
        #define OD_slaveAssignment                                  CO_OD_PERSIST_COMM.slaveAssignment
        #define ODL_slaveAssignment_arrayLength                     127
        #define ODA_slaveAssignment_                                0

/*1F82, Data Type: UNSIGNED8, Array[127] */
        #define OD_requestNMT                                       CO_OD_PERSIST_COMM.requestNMT
        #define ODL_requestNMT_arrayLength                          127
        #define ODA_requestNMT_                                     0

/*1F89, Data Type: UNSIGNED32 */
        #define OD_bootTime                                         CO_OD_RAM.bootTime

/*2000, Data Type: BUS_Management_t */
        #define OD_BUS_Management                                   CO_OD_PERSIST_MFR.BUS_Management

/*2010, Data Type: UNSIGNED64 */
        #define OD_SCET                                             CO_OD_RAM.SCET

/*2011, Data Type: UNSIGNED64 */
        #define OD_UTC                                              CO_OD_RAM.UTC

/*2020, Data Type: MCU_Calibration_t */
        #define OD_MCU_Calibration                                  CO_OD_RAM.MCU_Calibration

/*2021, Data Type: MCU_Sensors_t */
        #define OD_MCU_Sensors                                      CO_OD_RAM.MCU_Sensors

/*2100, Data Type: OCTET_STRING */
        #define OD_errorStatusBits                                  CO_OD_RAM.errorStatusBits
        #define ODL_errorStatusBits_stringLength                    10

/*6000, Data Type: VISIBLE_STRING */
        #define OD_C3State                                          CO_OD_RAM.C3State
        #define ODL_C3State_stringLength                            1

/*6001, Data Type: TX_Control_t */
        #define OD_TX_Control                                       CO_OD_PERSIST_APP.TX_Control

#endif
// clang-format on
