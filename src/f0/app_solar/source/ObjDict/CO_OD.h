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
      CreationTime: 2:51PM
      CreationDate: 08-12-2019
      CreatedBy:    Miles Simpson
*******************************************************************************/


/*******************************************************************************
   DEVICE INFO:
      VendorName:     Portland State Aerospace Society
      VendorNumber:   0
      ProductName:    OreSat Solar Board
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
  #define CO_NO_RPDO                     4   //Associated objects: 14xx, 16xx
  #define CO_NO_TPDO                     4   //Associated objects: 18xx, 1Axx
  #define CO_NO_NMT_MASTER               0
  #define CO_NO_TRACE                    0


/*******************************************************************************
   OBJECT DICTIONARY
*******************************************************************************/
   #define CO_OD_NoOfElements             46


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
/*6000      */ typedef struct {
               UNSIGNED8      maxSubIndex;
               UNSIGNED16     voltage;
               INTEGER16      current;
               UNSIGNED16     power;
               UNSIGNED16     voltageAvg;
               INTEGER16      currentAvg;
               UNSIGNED16     powerAvg;
               UNSIGNED16     voltageMax;
               INTEGER16      currentMax;
               UNSIGNED16     powerMax;
               UNSIGNED16     energy;
               }              OD_PV_Power_t;
/*6001      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               INTEGER8       cell1Temp;
               INTEGER8       cell2Temp;
               INTEGER8       cell1TempMin;
               INTEGER8       cell2TempMin;
               INTEGER8       cell1TempMax;
               INTEGER8       cell2TempMax;
               }              OD_PV_Temp_t;
/*6002      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               UNSIGNED8      algorithm;
               UNSIGNED8      LT1618IADJ;
               }              OD_MPPT_t;

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
        #define OD_1029_1_errorBehavior_communicationError          1
        #define OD_1029_2_errorBehavior_profileOrManufacturerSpecificError 2

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
        #define OD_6000_PV_Power                                    0x6000

        #define OD_6000_0_PV_Power_maxSubIndex                      0
        #define OD_6000_1_PV_Power_voltage                          1
        #define OD_6000_2_PV_Power_current                          2
        #define OD_6000_3_PV_Power_power                            3
        #define OD_6000_4_PV_Power_voltageAvg                       4
        #define OD_6000_5_PV_Power_currentAvg                       5
        #define OD_6000_6_PV_Power_powerAvg                         6
        #define OD_6000_7_PV_Power_voltageMax                       7
        #define OD_6000_8_PV_Power_currentMax                       8
        #define OD_6000_9_PV_Power_powerMax                         9
        #define OD_6000_10_PV_Power_energy                          10

/*6001 */
        #define OD_6001_PV_Temp                                     0x6001

        #define OD_6001_0_PV_Temp_maxSubIndex                       0
        #define OD_6001_1_PV_Temp_cell1Temp                         1
        #define OD_6001_2_PV_Temp_cell2Temp                         2
        #define OD_6001_3_PV_Temp_cell1TempMin                      3
        #define OD_6001_4_PV_Temp_cell2TempMin                      4
        #define OD_6001_5_PV_Temp_cell1TempMax                      5
        #define OD_6001_6_PV_Temp_cell2TempMax                      6

/*6002 */
        #define OD_6002_MPPT                                        0x6002

        #define OD_6002_0_MPPT_maxSubIndex                          0
        #define OD_6002_1_MPPT_algorithm                            1
        #define OD_6002_2_MPPT_LT1618IADJ                           2

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
/*2020      */ OD_MCU_Calibration_t MCU_Calibration;
/*2021      */ OD_MCU_Sensors_t MCU_Sensors;
/*2100      */ OCTET_STRING   errorStatusBits[10];
/*6000      */ OD_PV_Power_t   PV_Power;
/*6001      */ OD_PV_Temp_t    PV_Temp;
/*6002      */ OD_MPPT_t       MPPT;

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
/*1029      */ UNSIGNED8       errorBehavior[2];
/*1200      */ OD_SDOServerParameter_t SDOServerParameter[1];
/*1400      */ OD_RPDOCommunicationParameter_t RPDOCommunicationParameter[4];
/*1600      */ OD_RPDOMappingParameter_t RPDOMappingParameter[4];
/*1800      */ OD_TPDOCommunicationParameter_t TPDOCommunicationParameter[4];
/*1A00      */ OD_TPDOMappingParameter_t TPDOMappingParameter[4];
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

/*1029, Data Type: UNSIGNED8, Array[2] */
        #define OD_errorBehavior                                    CO_OD_PERSIST_COMM.errorBehavior
        #define ODL_errorBehavior_arrayLength                       2
        #define ODA_errorBehavior_communicationError                0
        #define ODA_errorBehavior_profileOrManufacturerSpecificError 1

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

/*2020, Data Type: MCU_Calibration_t */
        #define OD_MCU_Calibration                                  CO_OD_RAM.MCU_Calibration

/*2021, Data Type: MCU_Sensors_t */
        #define OD_MCU_Sensors                                      CO_OD_RAM.MCU_Sensors

/*2100, Data Type: OCTET_STRING */
        #define OD_errorStatusBits                                  CO_OD_RAM.errorStatusBits
        #define ODL_errorStatusBits_stringLength                    10

/*6000, Data Type: PV_Power_t */
        #define OD_PV_Power                                         CO_OD_RAM.PV_Power

/*6001, Data Type: PV_Temp_t */
        #define OD_PV_Temp                                          CO_OD_RAM.PV_Temp

/*6002, Data Type: MPPT_t */
        #define OD_MPPT                                             CO_OD_RAM.MPPT

#endif
// clang-format on
