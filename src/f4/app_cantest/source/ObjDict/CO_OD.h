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
  #define CO_NO_RPDO                     47   //Associated objects: 14xx, 16xx
  #define CO_NO_TPDO                     16   //Associated objects: 18xx, 1Axx
  #define CO_NO_NMT_MASTER               0
  #define CO_NO_TRACE                    0


/*******************************************************************************
   OBJECT DICTIONARY
*******************************************************************************/
   #define CO_OD_NoOfElements             182


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
/*6001      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               UNSIGNED16     saveInterval;
               UNSIGNED16     EDL_Timeout;
               BOOLEAN        factoryReset;
               }              OD_stateControl_t;
/*6002      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               UNSIGNED32     timeout;
               UNSIGNED32     actuationTime;
               UNSIGNED8      attempts;
               }              OD_deploymentControl_t;
/*6003      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               UNSIGNED32     timeout;
               UNSIGNED32     beaconInterval;
               }              OD_TX_Control_t;
/*6004      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               UNSIGNED64     timestamp;
               UNSIGNED32     alarmA;
               UNSIGNED32     alarmB;
               UNSIGNED32     wakeup;
               UNSIGNED32     lastTX_Enable;
               UNSIGNED32     lastEDL;
               BOOLEAN        deployed;
               }              OD_persistentState_t;
/*7000      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               UNSIGNED32     uptime;
               UNSIGNED8      EMMC_Usage;
               }              OD_C3Telemetry_t;
/*7001      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               UNSIGNED16     vbattBP1;
               UNSIGNED16     vbattBP2;
               UNSIGNED16     VCellMaxBP1;
               UNSIGNED16     VCellMaxBP2;
               UNSIGNED16     VCellMinBP1;
               UNSIGNED16     VCellMinBP2;
               UNSIGNED16     VCellBP1;
               UNSIGNED16     VCellBP2;
               UNSIGNED16     VCell1BP1;
               UNSIGNED16     VCell1BP2;
               UNSIGNED16     VCell2BP1;
               UNSIGNED16     VCell2BP2;
               UNSIGNED16     VCellAvgBP1;
               UNSIGNED16     VCellAvgBP2;
               INTEGER16      currentBP1;
               INTEGER16      currentBP2;
               INTEGER16      currentAvgBP1;
               INTEGER16      currentAvgBP2;
               INTEGER16      currentMaxBP1;
               INTEGER16      currentMaxBP2;
               INTEGER16      currentMinBP1;
               INTEGER16      currentMinBP2;
               UNSIGNED16     fullCapacityBP1;
               UNSIGNED16     fullCapacityBP2;
               UNSIGNED16     reportedCapacityBP1;
               UNSIGNED16     reportedCapacityBP2;
               UNSIGNED16     timeToEmptyBP1;
               UNSIGNED16     timeToEmptyBP2;
               UNSIGNED16     timeToFullBP1;
               UNSIGNED16     timeToFullBP2;
               UNSIGNED16     cyclesBP1;
               UNSIGNED16     cyclesBP2;
               UNSIGNED8      reportedStateOfChargeBP1;
               UNSIGNED8      reportedStateOfChargeBP2;
               INTEGER16      temperatureBP1;
               INTEGER16      temperatureBP2;
               INTEGER16      temperatureAvgBP1;
               INTEGER16      temperatureAvgBP2;
               INTEGER16      temperatureMaxBP1;
               INTEGER16      temperatureMaxBP2;
               INTEGER16      temperatureMinBP1;
               INTEGER16      temperatureMinBP2;
               UNSIGNED8      stateBP1;
               UNSIGNED8      stateBP2;
               }              OD_battery_t;
/*7003      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
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
               INTEGER8       cell1Temp;
               INTEGER8       cell2Temp;
               INTEGER8       cell1TempMin;
               INTEGER8       cell2TempMin;
               INTEGER8       cell1TempMax;
               INTEGER8       cell2TempMax;
               }              OD_solarPanel_t;
/*700B      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               UNSIGNED8      rootParitionPercent;
               UNSIGNED8      RAM_Percent;
               UNSIGNED8      freadCacheLength;
               UNSIGNED8      fwriteCacheLength;
               UNSIGNED8      activeApps;
               UNSIGNED8      failedApps;
               UNSIGNED8      updaterStatus;
               UNSIGNED8      updatesAvailable;
               INTEGER16      rightAscension;
               INTEGER16      declination;
               INTEGER16      roll;
               UNSIGNED64     timestamp;
               }              OD_starTracker_t;
/*700D      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               UNSIGNED8      rootParitionPercent;
               UNSIGNED8      RAM_Percent;
               UNSIGNED8      freadCacheLength;
               UNSIGNED8      fwriteCacheLength;
               UNSIGNED8      activeApps;
               UNSIGNED8      failedApps;
               UNSIGNED8      updaterStatus;
               UNSIGNED8      updatesAvailable;
               UNSIGNED8      GPS_Status;
               UNSIGNED8      satellitesLocked;
               UNSIGNED64     timestamp;
               INTEGER32      positionX;
               INTEGER32      positionY;
               INTEGER32      positionZ;
               INTEGER32      velocityX;
               INTEGER32      velocityY;
               INTEGER32      velocityZ;
               }              OD_GPS_t;
/*700E      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               INTEGER16      gyroPitch;
               INTEGER16      gyroYaw;
               INTEGER16      gyroRoll;
               INTEGER16      accelerationX;
               INTEGER16      accelerationY;
               INTEGER16      accelerationZ;
               UNSIGNED8      IMUTemp;
               INTEGER16      magnetometerPZ1X;
               INTEGER16      magnetometerPZ1Y;
               INTEGER16      magnetometerPZ1Z;
               INTEGER16      magnetometerPZ2X;
               INTEGER16      magnetometerPZ2Y;
               INTEGER16      magnetometerPZ2Z;
               INTEGER16      magnetometerMZ1X;
               INTEGER16      magnetometerMZ1Y;
               INTEGER16      magnetometerMZ1Z;
               INTEGER16      magnetometerMZ2X;
               INTEGER16      magnetometerMZ2Y;
               INTEGER16      magnetometerMZ2Z;
               }              OD_ACS_t;
/*700F      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               UNSIGNED16     subObject1;
               }              OD_RWB_t;
/*7013      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               UNSIGNED8      rootParitionPercent;
               UNSIGNED8      RAM_Percent;
               UNSIGNED8      freadCacheLength;
               UNSIGNED8      fwriteCacheLength;
               UNSIGNED8      activeApps;
               UNSIGNED8      failedApps;
               UNSIGNED8      updaterStatus;
               UNSIGNED8      updatesAvailable;
               BOOLEAN        transmitting;
               }              OD_dxWiFi_t;
/*7014      */ typedef struct {
               UNSIGNED8      highestSubIndexSupported;
               UNSIGNED8      rootParitionPercent;
               UNSIGNED8      RAM_Percent;
               UNSIGNED8      freadCacheLength;
               UNSIGNED8      fwriteCacheLength;
               UNSIGNED8      activeApps;
               UNSIGNED8      failedApps;
               UNSIGNED8      updaterStatus;
               UNSIGNED8      updatesAvailable;
               }              OD_CFC_t;

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
        #define OD_1016_9_consumerHeartbeatTime_consumerHeartbeatTime 9
        #define OD_1016_10_consumerHeartbeatTime_consumerHeartbeatTime 10
        #define OD_1016_11_consumerHeartbeatTime_consumerHeartbeatTime 11
        #define OD_1016_12_consumerHeartbeatTime_consumerHeartbeatTime 12
        #define OD_1016_13_consumerHeartbeatTime_consumerHeartbeatTime 13
        #define OD_1016_14_consumerHeartbeatTime_consumerHeartbeatTime 14
        #define OD_1016_15_consumerHeartbeatTime_consumerHeartbeatTime 15
        #define OD_1016_16_consumerHeartbeatTime_consumerHeartbeatTime 16
        #define OD_1016_17_consumerHeartbeatTime_consumerHeartbeatTime 17
        #define OD_1016_18_consumerHeartbeatTime_consumerHeartbeatTime 18
        #define OD_1016_19_consumerHeartbeatTime_consumerHeartbeatTime 19
        #define OD_1016_20_consumerHeartbeatTime_consumerHeartbeatTime 20
        #define OD_1016_21_consumerHeartbeatTime_consumerHeartbeatTime 21
        #define OD_1016_22_consumerHeartbeatTime_consumerHeartbeatTime 22
        #define OD_1016_23_consumerHeartbeatTime_consumerHeartbeatTime 23
        #define OD_1016_24_consumerHeartbeatTime_consumerHeartbeatTime 24
        #define OD_1016_25_consumerHeartbeatTime_consumerHeartbeatTime 25
        #define OD_1016_26_consumerHeartbeatTime_consumerHeartbeatTime 26
        #define OD_1016_27_consumerHeartbeatTime_consumerHeartbeatTime 27
        #define OD_1016_28_consumerHeartbeatTime_consumerHeartbeatTime 28
        #define OD_1016_29_consumerHeartbeatTime_consumerHeartbeatTime 29
        #define OD_1016_30_consumerHeartbeatTime_consumerHeartbeatTime 30
        #define OD_1016_31_consumerHeartbeatTime_consumerHeartbeatTime 31
        #define OD_1016_32_consumerHeartbeatTime_consumerHeartbeatTime 32

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

/*1410 */
        #define OD_1410_RPDOCommunicationParameter                  0x1410

        #define OD_1410_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1410_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1410_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_1410_5_RPDOCommunicationParameter_eventTimer     5

/*1411 */
        #define OD_1411_RPDOCommunicationParameter                  0x1411

        #define OD_1411_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1411_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1411_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_1411_5_RPDOCommunicationParameter_eventTimer     5

/*1412 */
        #define OD_1412_RPDOCommunicationParameter                  0x1412

        #define OD_1412_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1412_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1412_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_1412_5_RPDOCommunicationParameter_eventTimer     5

/*1413 */
        #define OD_1413_RPDOCommunicationParameter                  0x1413

        #define OD_1413_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1413_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1413_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_1413_5_RPDOCommunicationParameter_eventTimer     5

/*1414 */
        #define OD_1414_RPDOCommunicationParameter                  0x1414

        #define OD_1414_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1414_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1414_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_1414_5_RPDOCommunicationParameter_eventTimer     5

/*1415 */
        #define OD_1415_RPDOCommunicationParameter                  0x1415

        #define OD_1415_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1415_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1415_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_1415_5_RPDOCommunicationParameter_eventTimer     5

/*1416 */
        #define OD_1416_RPDOCommunicationParameter                  0x1416

        #define OD_1416_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1416_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1416_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_1416_5_RPDOCommunicationParameter_eventTimer     5

/*1417 */
        #define OD_1417_RPDOCommunicationParameter                  0x1417

        #define OD_1417_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1417_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1417_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_1417_5_RPDOCommunicationParameter_eventTimer     5

/*1418 */
        #define OD_1418_RPDOCommunicationParameter                  0x1418

        #define OD_1418_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1418_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1418_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_1418_5_RPDOCommunicationParameter_eventTimer     5

/*1419 */
        #define OD_1419_RPDOCommunicationParameter                  0x1419

        #define OD_1419_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1419_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1419_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_1419_5_RPDOCommunicationParameter_eventTimer     5

/*141A */
        #define OD_141A_RPDOCommunicationParameter                  0x141A

        #define OD_141A_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_141A_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_141A_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_141A_5_RPDOCommunicationParameter_eventTimer     5

/*141B */
        #define OD_141B_RPDOCommunicationParameter                  0x141B

        #define OD_141B_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_141B_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_141B_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_141B_5_RPDOCommunicationParameter_eventTimer     5

/*141C */
        #define OD_141C_RPDOCommunicationParameter                  0x141C

        #define OD_141C_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_141C_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_141C_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_141C_5_RPDOCommunicationParameter_eventTimer     5

/*141D */
        #define OD_141D_RPDOCommunicationParameter                  0x141D

        #define OD_141D_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_141D_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_141D_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_141D_5_RPDOCommunicationParameter_eventTimer     5

/*141E */
        #define OD_141E_RPDOCommunicationParameter                  0x141E

        #define OD_141E_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_141E_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_141E_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_141E_5_RPDOCommunicationParameter_eventTimer     5

/*141F */
        #define OD_141F_RPDOCommunicationParameter                  0x141F

        #define OD_141F_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_141F_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_141F_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_141F_5_RPDOCommunicationParameter_eventTimer     5

/*1420 */
        #define OD_1420_RPDOCommunicationParameter                  0x1420

        #define OD_1420_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1420_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1420_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_1420_5_RPDOCommunicationParameter_eventTimer     5

/*1421 */
        #define OD_1421_RPDOCommunicationParameter                  0x1421

        #define OD_1421_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1421_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1421_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_1421_5_RPDOCommunicationParameter_eventTimer     5

/*1422 */
        #define OD_1422_RPDOCommunicationParameter                  0x1422

        #define OD_1422_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1422_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1422_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_1422_5_RPDOCommunicationParameter_eventTimer     5

/*1423 */
        #define OD_1423_RPDOCommunicationParameter                  0x1423

        #define OD_1423_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1423_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1423_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_1423_5_RPDOCommunicationParameter_eventTimer     5

/*1424 */
        #define OD_1424_RPDOCommunicationParameter                  0x1424

        #define OD_1424_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1424_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1424_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_1424_5_RPDOCommunicationParameter_eventTimer     5

/*1425 */
        #define OD_1425_RPDOCommunicationParameter                  0x1425

        #define OD_1425_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1425_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1425_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_1425_5_RPDOCommunicationParameter_eventTimer     5

/*1426 */
        #define OD_1426_RPDOCommunicationParameter                  0x1426

        #define OD_1426_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1426_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1426_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_1426_5_RPDOCommunicationParameter_eventTimer     5

/*1427 */
        #define OD_1427_RPDOCommunicationParameter                  0x1427

        #define OD_1427_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1427_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1427_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_1427_5_RPDOCommunicationParameter_eventTimer     5

/*1428 */
        #define OD_1428_RPDOCommunicationParameter                  0x1428

        #define OD_1428_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1428_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1428_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_1428_5_RPDOCommunicationParameter_eventTimer     5

/*1429 */
        #define OD_1429_RPDOCommunicationParameter                  0x1429

        #define OD_1429_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_1429_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_1429_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_1429_5_RPDOCommunicationParameter_eventTimer     5

/*142A */
        #define OD_142A_RPDOCommunicationParameter                  0x142A

        #define OD_142A_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_142A_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_142A_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_142A_5_RPDOCommunicationParameter_eventTimer     5

/*142B */
        #define OD_142B_RPDOCommunicationParameter                  0x142B

        #define OD_142B_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_142B_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_142B_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_142B_5_RPDOCommunicationParameter_eventTimer     5

/*142C */
        #define OD_142C_RPDOCommunicationParameter                  0x142C

        #define OD_142C_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_142C_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_142C_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_142C_5_RPDOCommunicationParameter_eventTimer     5

/*142D */
        #define OD_142D_RPDOCommunicationParameter                  0x142D

        #define OD_142D_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_142D_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_142D_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_142D_5_RPDOCommunicationParameter_eventTimer     5

/*142E */
        #define OD_142E_RPDOCommunicationParameter                  0x142E

        #define OD_142E_0_RPDOCommunicationParameter_maxSubIndex    0
        #define OD_142E_1_RPDOCommunicationParameter_COB_IDUsedByRPDO 1
        #define OD_142E_2_RPDOCommunicationParameter_transmissionType 2
        #define OD_142E_5_RPDOCommunicationParameter_eventTimer     5

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

/*1610 */
        #define OD_1610_RPDOMappingParameter                        0x1610

        #define OD_1610_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1610_1_RPDOMappingParameter_applicationObject1   1
        #define OD_1610_2_RPDOMappingParameter_applicationObject2   2
        #define OD_1610_3_RPDOMappingParameter_applicationObject3   3
        #define OD_1610_4_RPDOMappingParameter_applicationObject4   4
        #define OD_1610_5_RPDOMappingParameter_applicationObject5   5
        #define OD_1610_6_RPDOMappingParameter_applicationObject6   6
        #define OD_1610_7_RPDOMappingParameter_applicationObject7   7
        #define OD_1610_8_RPDOMappingParameter_applicationObject8   8

/*1611 */
        #define OD_1611_RPDOMappingParameter                        0x1611

        #define OD_1611_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1611_1_RPDOMappingParameter_applicationObject1   1
        #define OD_1611_2_RPDOMappingParameter_applicationObject2   2
        #define OD_1611_3_RPDOMappingParameter_applicationObject3   3
        #define OD_1611_4_RPDOMappingParameter_applicationObject4   4
        #define OD_1611_5_RPDOMappingParameter_applicationObject5   5
        #define OD_1611_6_RPDOMappingParameter_applicationObject6   6
        #define OD_1611_7_RPDOMappingParameter_applicationObject7   7
        #define OD_1611_8_RPDOMappingParameter_applicationObject8   8

/*1612 */
        #define OD_1612_RPDOMappingParameter                        0x1612

        #define OD_1612_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1612_1_RPDOMappingParameter_applicationObject1   1
        #define OD_1612_2_RPDOMappingParameter_applicationObject2   2
        #define OD_1612_3_RPDOMappingParameter_applicationObject3   3
        #define OD_1612_4_RPDOMappingParameter_applicationObject4   4
        #define OD_1612_5_RPDOMappingParameter_applicationObject5   5
        #define OD_1612_6_RPDOMappingParameter_applicationObject6   6
        #define OD_1612_7_RPDOMappingParameter_applicationObject7   7
        #define OD_1612_8_RPDOMappingParameter_applicationObject8   8

/*1613 */
        #define OD_1613_RPDOMappingParameter                        0x1613

        #define OD_1613_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1613_1_RPDOMappingParameter_applicationObject1   1
        #define OD_1613_2_RPDOMappingParameter_applicationObject2   2
        #define OD_1613_3_RPDOMappingParameter_applicationObject3   3
        #define OD_1613_4_RPDOMappingParameter_applicationObject4   4
        #define OD_1613_5_RPDOMappingParameter_applicationObject5   5
        #define OD_1613_6_RPDOMappingParameter_applicationObject6   6
        #define OD_1613_7_RPDOMappingParameter_applicationObject7   7
        #define OD_1613_8_RPDOMappingParameter_applicationObject8   8

/*1614 */
        #define OD_1614_RPDOMappingParameter                        0x1614

        #define OD_1614_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1614_1_RPDOMappingParameter_applicationObject1   1
        #define OD_1614_2_RPDOMappingParameter_applicationObject2   2
        #define OD_1614_3_RPDOMappingParameter_applicationObject3   3
        #define OD_1614_4_RPDOMappingParameter_applicationObject4   4
        #define OD_1614_5_RPDOMappingParameter_applicationObject5   5
        #define OD_1614_6_RPDOMappingParameter_applicationObject6   6
        #define OD_1614_7_RPDOMappingParameter_applicationObject7   7
        #define OD_1614_8_RPDOMappingParameter_applicationObject8   8

/*1615 */
        #define OD_1615_RPDOMappingParameter                        0x1615

        #define OD_1615_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1615_1_RPDOMappingParameter_applicationObject1   1
        #define OD_1615_2_RPDOMappingParameter_applicationObject2   2
        #define OD_1615_3_RPDOMappingParameter_applicationObject3   3
        #define OD_1615_4_RPDOMappingParameter_applicationObject4   4
        #define OD_1615_5_RPDOMappingParameter_applicationObject5   5
        #define OD_1615_6_RPDOMappingParameter_applicationObject6   6
        #define OD_1615_7_RPDOMappingParameter_applicationObject7   7
        #define OD_1615_8_RPDOMappingParameter_applicationObject8   8

/*1616 */
        #define OD_1616_RPDOMappingParameter                        0x1616

        #define OD_1616_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1616_1_RPDOMappingParameter_applicationObject1   1
        #define OD_1616_2_RPDOMappingParameter_applicationObject2   2
        #define OD_1616_3_RPDOMappingParameter_applicationObject3   3
        #define OD_1616_4_RPDOMappingParameter_applicationObject4   4
        #define OD_1616_5_RPDOMappingParameter_applicationObject5   5
        #define OD_1616_6_RPDOMappingParameter_applicationObject6   6
        #define OD_1616_7_RPDOMappingParameter_applicationObject7   7
        #define OD_1616_8_RPDOMappingParameter_applicationObject8   8

/*1617 */
        #define OD_1617_RPDOMappingParameter                        0x1617

        #define OD_1617_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1617_1_RPDOMappingParameter_applicationObject1   1
        #define OD_1617_2_RPDOMappingParameter_applicationObject2   2
        #define OD_1617_3_RPDOMappingParameter_applicationObject3   3
        #define OD_1617_4_RPDOMappingParameter_applicationObject4   4
        #define OD_1617_5_RPDOMappingParameter_applicationObject5   5
        #define OD_1617_6_RPDOMappingParameter_applicationObject6   6
        #define OD_1617_7_RPDOMappingParameter_applicationObject7   7
        #define OD_1617_8_RPDOMappingParameter_applicationObject8   8

/*1618 */
        #define OD_1618_RPDOMappingParameter                        0x1618

        #define OD_1618_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1618_1_RPDOMappingParameter_applicationObject1   1
        #define OD_1618_2_RPDOMappingParameter_applicationObject2   2
        #define OD_1618_3_RPDOMappingParameter_applicationObject3   3
        #define OD_1618_4_RPDOMappingParameter_applicationObject4   4
        #define OD_1618_5_RPDOMappingParameter_applicationObject5   5
        #define OD_1618_6_RPDOMappingParameter_applicationObject6   6
        #define OD_1618_7_RPDOMappingParameter_applicationObject7   7
        #define OD_1618_8_RPDOMappingParameter_applicationObject8   8

/*1619 */
        #define OD_1619_RPDOMappingParameter                        0x1619

        #define OD_1619_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1619_1_RPDOMappingParameter_applicationObject1   1
        #define OD_1619_2_RPDOMappingParameter_applicationObject2   2
        #define OD_1619_3_RPDOMappingParameter_applicationObject3   3
        #define OD_1619_4_RPDOMappingParameter_applicationObject4   4
        #define OD_1619_5_RPDOMappingParameter_applicationObject5   5
        #define OD_1619_6_RPDOMappingParameter_applicationObject6   6
        #define OD_1619_7_RPDOMappingParameter_applicationObject7   7
        #define OD_1619_8_RPDOMappingParameter_applicationObject8   8

/*161A */
        #define OD_161A_RPDOMappingParameter                        0x161A

        #define OD_161A_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_161A_1_RPDOMappingParameter_applicationObject1   1
        #define OD_161A_2_RPDOMappingParameter_applicationObject2   2
        #define OD_161A_3_RPDOMappingParameter_applicationObject3   3
        #define OD_161A_4_RPDOMappingParameter_applicationObject4   4
        #define OD_161A_5_RPDOMappingParameter_applicationObject5   5
        #define OD_161A_6_RPDOMappingParameter_applicationObject6   6
        #define OD_161A_7_RPDOMappingParameter_applicationObject7   7
        #define OD_161A_8_RPDOMappingParameter_applicationObject8   8

/*161B */
        #define OD_161B_RPDOMappingParameter                        0x161B

        #define OD_161B_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_161B_1_RPDOMappingParameter_applicationObject1   1
        #define OD_161B_2_RPDOMappingParameter_applicationObject2   2
        #define OD_161B_3_RPDOMappingParameter_applicationObject3   3
        #define OD_161B_4_RPDOMappingParameter_applicationObject4   4
        #define OD_161B_5_RPDOMappingParameter_applicationObject5   5
        #define OD_161B_6_RPDOMappingParameter_applicationObject6   6
        #define OD_161B_7_RPDOMappingParameter_applicationObject7   7
        #define OD_161B_8_RPDOMappingParameter_applicationObject8   8

/*161C */
        #define OD_161C_RPDOMappingParameter                        0x161C

        #define OD_161C_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_161C_1_RPDOMappingParameter_applicationObject1   1
        #define OD_161C_2_RPDOMappingParameter_applicationObject2   2
        #define OD_161C_3_RPDOMappingParameter_applicationObject3   3
        #define OD_161C_4_RPDOMappingParameter_applicationObject4   4
        #define OD_161C_5_RPDOMappingParameter_applicationObject5   5
        #define OD_161C_6_RPDOMappingParameter_applicationObject6   6
        #define OD_161C_7_RPDOMappingParameter_applicationObject7   7
        #define OD_161C_8_RPDOMappingParameter_applicationObject8   8

/*161D */
        #define OD_161D_RPDOMappingParameter                        0x161D

        #define OD_161D_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_161D_1_RPDOMappingParameter_applicationObject1   1
        #define OD_161D_2_RPDOMappingParameter_applicationObject2   2
        #define OD_161D_3_RPDOMappingParameter_applicationObject3   3
        #define OD_161D_4_RPDOMappingParameter_applicationObject4   4
        #define OD_161D_5_RPDOMappingParameter_applicationObject5   5
        #define OD_161D_6_RPDOMappingParameter_applicationObject6   6
        #define OD_161D_7_RPDOMappingParameter_applicationObject7   7
        #define OD_161D_8_RPDOMappingParameter_applicationObject8   8

/*161E */
        #define OD_161E_RPDOMappingParameter                        0x161E

        #define OD_161E_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_161E_1_RPDOMappingParameter_applicationObject1   1
        #define OD_161E_2_RPDOMappingParameter_applicationObject2   2
        #define OD_161E_3_RPDOMappingParameter_applicationObject3   3
        #define OD_161E_4_RPDOMappingParameter_applicationObject4   4
        #define OD_161E_5_RPDOMappingParameter_applicationObject5   5
        #define OD_161E_6_RPDOMappingParameter_applicationObject6   6
        #define OD_161E_7_RPDOMappingParameter_applicationObject7   7
        #define OD_161E_8_RPDOMappingParameter_applicationObject8   8

/*161F */
        #define OD_161F_RPDOMappingParameter                        0x161F

        #define OD_161F_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_161F_1_RPDOMappingParameter_applicationObject1   1
        #define OD_161F_2_RPDOMappingParameter_applicationObject2   2
        #define OD_161F_3_RPDOMappingParameter_applicationObject3   3
        #define OD_161F_4_RPDOMappingParameter_applicationObject4   4
        #define OD_161F_5_RPDOMappingParameter_applicationObject5   5
        #define OD_161F_6_RPDOMappingParameter_applicationObject6   6
        #define OD_161F_7_RPDOMappingParameter_applicationObject7   7
        #define OD_161F_8_RPDOMappingParameter_applicationObject8   8

/*1620 */
        #define OD_1620_RPDOMappingParameter                        0x1620

        #define OD_1620_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1620_1_RPDOMappingParameter_applicationObject1   1
        #define OD_1620_2_RPDOMappingParameter_applicationObject2   2
        #define OD_1620_3_RPDOMappingParameter_applicationObject3   3
        #define OD_1620_4_RPDOMappingParameter_applicationObject4   4
        #define OD_1620_5_RPDOMappingParameter_applicationObject5   5
        #define OD_1620_6_RPDOMappingParameter_applicationObject6   6
        #define OD_1620_7_RPDOMappingParameter_applicationObject7   7
        #define OD_1620_8_RPDOMappingParameter_applicationObject8   8

/*1621 */
        #define OD_1621_RPDOMappingParameter                        0x1621

        #define OD_1621_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1621_1_RPDOMappingParameter_applicationObject1   1
        #define OD_1621_2_RPDOMappingParameter_applicationObject2   2
        #define OD_1621_3_RPDOMappingParameter_applicationObject3   3
        #define OD_1621_4_RPDOMappingParameter_applicationObject4   4
        #define OD_1621_5_RPDOMappingParameter_applicationObject5   5
        #define OD_1621_6_RPDOMappingParameter_applicationObject6   6
        #define OD_1621_7_RPDOMappingParameter_applicationObject7   7
        #define OD_1621_8_RPDOMappingParameter_applicationObject8   8

/*1622 */
        #define OD_1622_RPDOMappingParameter                        0x1622

        #define OD_1622_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1622_1_RPDOMappingParameter_applicationObject1   1
        #define OD_1622_2_RPDOMappingParameter_applicationObject2   2
        #define OD_1622_3_RPDOMappingParameter_applicationObject3   3
        #define OD_1622_4_RPDOMappingParameter_applicationObject4   4
        #define OD_1622_5_RPDOMappingParameter_applicationObject5   5
        #define OD_1622_6_RPDOMappingParameter_applicationObject6   6
        #define OD_1622_7_RPDOMappingParameter_applicationObject7   7
        #define OD_1622_8_RPDOMappingParameter_applicationObject8   8

/*1623 */
        #define OD_1623_RPDOMappingParameter                        0x1623

        #define OD_1623_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1623_1_RPDOMappingParameter_applicationObject1   1
        #define OD_1623_2_RPDOMappingParameter_applicationObject2   2
        #define OD_1623_3_RPDOMappingParameter_applicationObject3   3
        #define OD_1623_4_RPDOMappingParameter_applicationObject4   4
        #define OD_1623_5_RPDOMappingParameter_applicationObject5   5
        #define OD_1623_6_RPDOMappingParameter_applicationObject6   6
        #define OD_1623_7_RPDOMappingParameter_applicationObject7   7
        #define OD_1623_8_RPDOMappingParameter_applicationObject8   8

/*1624 */
        #define OD_1624_RPDOMappingParameter                        0x1624

        #define OD_1624_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1624_1_RPDOMappingParameter_applicationObject1   1
        #define OD_1624_2_RPDOMappingParameter_applicationObject2   2
        #define OD_1624_3_RPDOMappingParameter_applicationObject3   3
        #define OD_1624_4_RPDOMappingParameter_applicationObject4   4
        #define OD_1624_5_RPDOMappingParameter_applicationObject5   5
        #define OD_1624_6_RPDOMappingParameter_applicationObject6   6
        #define OD_1624_7_RPDOMappingParameter_applicationObject7   7
        #define OD_1624_8_RPDOMappingParameter_applicationObject8   8

/*1625 */
        #define OD_1625_RPDOMappingParameter                        0x1625

        #define OD_1625_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1625_1_RPDOMappingParameter_applicationObject1   1
        #define OD_1625_2_RPDOMappingParameter_applicationObject2   2
        #define OD_1625_3_RPDOMappingParameter_applicationObject3   3
        #define OD_1625_4_RPDOMappingParameter_applicationObject4   4
        #define OD_1625_5_RPDOMappingParameter_applicationObject5   5
        #define OD_1625_6_RPDOMappingParameter_applicationObject6   6
        #define OD_1625_7_RPDOMappingParameter_applicationObject7   7
        #define OD_1625_8_RPDOMappingParameter_applicationObject8   8

/*1626 */
        #define OD_1626_RPDOMappingParameter                        0x1626

        #define OD_1626_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1626_1_RPDOMappingParameter_applicationObject1   1
        #define OD_1626_2_RPDOMappingParameter_applicationObject2   2
        #define OD_1626_3_RPDOMappingParameter_applicationObject3   3
        #define OD_1626_4_RPDOMappingParameter_applicationObject4   4
        #define OD_1626_5_RPDOMappingParameter_applicationObject5   5
        #define OD_1626_6_RPDOMappingParameter_applicationObject6   6
        #define OD_1626_7_RPDOMappingParameter_applicationObject7   7
        #define OD_1626_8_RPDOMappingParameter_applicationObject8   8

/*1627 */
        #define OD_1627_RPDOMappingParameter                        0x1627

        #define OD_1627_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1627_1_RPDOMappingParameter_applicationObject1   1
        #define OD_1627_2_RPDOMappingParameter_applicationObject2   2
        #define OD_1627_3_RPDOMappingParameter_applicationObject3   3
        #define OD_1627_4_RPDOMappingParameter_applicationObject4   4
        #define OD_1627_5_RPDOMappingParameter_applicationObject5   5
        #define OD_1627_6_RPDOMappingParameter_applicationObject6   6
        #define OD_1627_7_RPDOMappingParameter_applicationObject7   7
        #define OD_1627_8_RPDOMappingParameter_applicationObject8   8

/*1628 */
        #define OD_1628_RPDOMappingParameter                        0x1628

        #define OD_1628_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1628_1_RPDOMappingParameter_applicationObject1   1
        #define OD_1628_2_RPDOMappingParameter_applicationObject2   2
        #define OD_1628_3_RPDOMappingParameter_applicationObject3   3
        #define OD_1628_4_RPDOMappingParameter_applicationObject4   4
        #define OD_1628_5_RPDOMappingParameter_applicationObject5   5
        #define OD_1628_6_RPDOMappingParameter_applicationObject6   6
        #define OD_1628_7_RPDOMappingParameter_applicationObject7   7
        #define OD_1628_8_RPDOMappingParameter_applicationObject8   8

/*1629 */
        #define OD_1629_RPDOMappingParameter                        0x1629

        #define OD_1629_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_1629_1_RPDOMappingParameter_applicationObject1   1
        #define OD_1629_2_RPDOMappingParameter_applicationObject2   2
        #define OD_1629_3_RPDOMappingParameter_applicationObject3   3
        #define OD_1629_4_RPDOMappingParameter_applicationObject4   4
        #define OD_1629_5_RPDOMappingParameter_applicationObject5   5
        #define OD_1629_6_RPDOMappingParameter_applicationObject6   6
        #define OD_1629_7_RPDOMappingParameter_applicationObject7   7
        #define OD_1629_8_RPDOMappingParameter_applicationObject8   8

/*162A */
        #define OD_162A_RPDOMappingParameter                        0x162A

        #define OD_162A_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_162A_1_RPDOMappingParameter_applicationObject1   1
        #define OD_162A_2_RPDOMappingParameter_applicationObject2   2
        #define OD_162A_3_RPDOMappingParameter_applicationObject3   3
        #define OD_162A_4_RPDOMappingParameter_applicationObject4   4
        #define OD_162A_5_RPDOMappingParameter_applicationObject5   5
        #define OD_162A_6_RPDOMappingParameter_applicationObject6   6
        #define OD_162A_7_RPDOMappingParameter_applicationObject7   7
        #define OD_162A_8_RPDOMappingParameter_applicationObject8   8

/*162B */
        #define OD_162B_RPDOMappingParameter                        0x162B

        #define OD_162B_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_162B_1_RPDOMappingParameter_applicationObject1   1
        #define OD_162B_2_RPDOMappingParameter_applicationObject2   2
        #define OD_162B_3_RPDOMappingParameter_applicationObject3   3
        #define OD_162B_4_RPDOMappingParameter_applicationObject4   4
        #define OD_162B_5_RPDOMappingParameter_applicationObject5   5
        #define OD_162B_6_RPDOMappingParameter_applicationObject6   6
        #define OD_162B_7_RPDOMappingParameter_applicationObject7   7
        #define OD_162B_8_RPDOMappingParameter_applicationObject8   8

/*162C */
        #define OD_162C_RPDOMappingParameter                        0x162C

        #define OD_162C_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_162C_1_RPDOMappingParameter_applicationObject1   1
        #define OD_162C_2_RPDOMappingParameter_applicationObject2   2
        #define OD_162C_3_RPDOMappingParameter_applicationObject3   3
        #define OD_162C_4_RPDOMappingParameter_applicationObject4   4
        #define OD_162C_5_RPDOMappingParameter_applicationObject5   5
        #define OD_162C_6_RPDOMappingParameter_applicationObject6   6
        #define OD_162C_7_RPDOMappingParameter_applicationObject7   7
        #define OD_162C_8_RPDOMappingParameter_applicationObject8   8

/*162D */
        #define OD_162D_RPDOMappingParameter                        0x162D

        #define OD_162D_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_162D_1_RPDOMappingParameter_applicationObject1   1
        #define OD_162D_2_RPDOMappingParameter_applicationObject2   2
        #define OD_162D_3_RPDOMappingParameter_applicationObject3   3
        #define OD_162D_4_RPDOMappingParameter_applicationObject4   4
        #define OD_162D_5_RPDOMappingParameter_applicationObject5   5
        #define OD_162D_6_RPDOMappingParameter_applicationObject6   6
        #define OD_162D_7_RPDOMappingParameter_applicationObject7   7
        #define OD_162D_8_RPDOMappingParameter_applicationObject8   8

/*162E */
        #define OD_162E_RPDOMappingParameter                        0x162E

        #define OD_162E_0_RPDOMappingParameter_maxSubIndex          0
        #define OD_162E_1_RPDOMappingParameter_applicationObject1   1
        #define OD_162E_2_RPDOMappingParameter_applicationObject2   2
        #define OD_162E_3_RPDOMappingParameter_applicationObject3   3
        #define OD_162E_4_RPDOMappingParameter_applicationObject4   4
        #define OD_162E_5_RPDOMappingParameter_applicationObject5   5
        #define OD_162E_6_RPDOMappingParameter_applicationObject6   6
        #define OD_162E_7_RPDOMappingParameter_applicationObject7   7
        #define OD_162E_8_RPDOMappingParameter_applicationObject8   8

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

/*6000 */
        #define OD_6000_C3State                                     0x6000

/*6001 */
        #define OD_6001_stateControl                                0x6001

        #define OD_6001_0_stateControl_maxSubIndex                  0
        #define OD_6001_1_stateControl_saveInterval                 1
        #define OD_6001_2_stateControl_EDL_Timeout                  2
        #define OD_6001_3_stateControl_factoryReset                 3

/*6002 */
        #define OD_6002_deploymentControl                           0x6002

        #define OD_6002_0_deploymentControl_maxSubIndex             0
        #define OD_6002_1_deploymentControl_timeout                 1
        #define OD_6002_2_deploymentControl_actuationTime           2
        #define OD_6002_3_deploymentControl_attempts                3

/*6003 */
        #define OD_6003_TX_Control                                  0x6003

        #define OD_6003_0_TX_Control_maxSubIndex                    0
        #define OD_6003_1_TX_Control_timeout                        1
        #define OD_6003_2_TX_Control_beaconInterval                 2

/*6004 */
        #define OD_6004_persistentState                             0x6004

        #define OD_6004_0_persistentState_maxSubIndex               0
        #define OD_6004_1_persistentState_timestamp                 1
        #define OD_6004_2_persistentState_alarmA                    2
        #define OD_6004_3_persistentState_alarmB                    3
        #define OD_6004_4_persistentState_wakeup                    4
        #define OD_6004_5_persistentState_lastTX_Enable             5
        #define OD_6004_6_persistentState_lastEDL                   6
        #define OD_6004_7_persistentState_deployed                  7

/*7000 */
        #define OD_7000_C3Telemetry                                 0x7000

        #define OD_7000_0_C3Telemetry_maxSubIndex                   0
        #define OD_7000_1_C3Telemetry_uptime                        1
        #define OD_7000_2_C3Telemetry_EMMC_Usage                    2

/*7001 */
        #define OD_7001_battery                                     0x7001

        #define OD_7001_0_battery_maxSubIndex                       0
        #define OD_7001_1_battery_vbattBP1                          1
        #define OD_7001_2_battery_vbattBP2                          2
        #define OD_7001_3_battery_VCellMaxBP1                       3
        #define OD_7001_4_battery_VCellMaxBP2                       4
        #define OD_7001_5_battery_VCellMinBP1                       5
        #define OD_7001_6_battery_VCellMinBP2                       6
        #define OD_7001_7_battery_VCellBP1                          7
        #define OD_7001_8_battery_VCellBP2                          8
        #define OD_7001_9_battery_VCell1BP1                         9
        #define OD_7001_10_battery_VCell1BP2                        10
        #define OD_7001_11_battery_VCell2BP1                        11
        #define OD_7001_12_battery_VCell2BP2                        12
        #define OD_7001_13_battery_VCellAvgBP1                      13
        #define OD_7001_14_battery_VCellAvgBP2                      14
        #define OD_7001_15_battery_currentBP1                       15
        #define OD_7001_16_battery_currentBP2                       16
        #define OD_7001_17_battery_currentAvgBP1                    17
        #define OD_7001_18_battery_currentAvgBP2                    18
        #define OD_7001_19_battery_currentMaxBP1                    19
        #define OD_7001_20_battery_currentMaxBP2                    20
        #define OD_7001_21_battery_currentMinBP1                    21
        #define OD_7001_22_battery_currentMinBP2                    22
        #define OD_7001_23_battery_fullCapacityBP1                  23
        #define OD_7001_24_battery_fullCapacityBP2                  24
        #define OD_7001_25_battery_reportedCapacityBP1              25
        #define OD_7001_26_battery_reportedCapacityBP2              26
        #define OD_7001_27_battery_timeToEmptyBP1                   27
        #define OD_7001_28_battery_timeToEmptyBP2                   28
        #define OD_7001_29_battery_timeToFullBP1                    29
        #define OD_7001_30_battery_timeToFullBP2                    30
        #define OD_7001_31_battery_cyclesBP1                        31
        #define OD_7001_32_battery_cyclesBP2                        32
        #define OD_7001_33_battery_reportedStateOfChargeBP1         33
        #define OD_7001_34_battery_reportedStateOfChargeBP2         34
        #define OD_7001_35_battery_temperatureBP1                   35
        #define OD_7001_36_battery_temperatureBP2                   36
        #define OD_7001_37_battery_temperatureAvgBP1                37
        #define OD_7001_38_battery_temperatureAvgBP2                38
        #define OD_7001_39_battery_temperatureMaxBP1                39
        #define OD_7001_40_battery_temperatureMaxBP2                40
        #define OD_7001_41_battery_temperatureMinBP1                41
        #define OD_7001_42_battery_temperatureMinBP2                42
        #define OD_7001_43_battery_stateBP1                         43
        #define OD_7001_44_battery_stateBP2                         44

/*7002 */
        #define OD_7002_battery                                     0x7002

        #define OD_7002_0_battery_maxSubIndex                       0
        #define OD_7002_1_battery_vbattBP1                          1
        #define OD_7002_2_battery_vbattBP2                          2
        #define OD_7002_3_battery_VCellMaxBP1                       3
        #define OD_7002_4_battery_VCellMaxBP2                       4
        #define OD_7002_5_battery_VCellMinBP1                       5
        #define OD_7002_6_battery_VCellMinBP2                       6
        #define OD_7002_7_battery_VCellBP1                          7
        #define OD_7002_8_battery_VCellBP2                          8
        #define OD_7002_9_battery_VCell1BP1                         9
        #define OD_7002_10_battery_VCell1BP2                        10
        #define OD_7002_11_battery_VCell2BP1                        11
        #define OD_7002_12_battery_VCell2BP2                        12
        #define OD_7002_13_battery_VCellAvgBP1                      13
        #define OD_7002_14_battery_VCellAvgBP2                      14
        #define OD_7002_15_battery_currentBP1                       15
        #define OD_7002_16_battery_currentBP2                       16
        #define OD_7002_17_battery_currentAvgBP1                    17
        #define OD_7002_18_battery_currentAvgBP2                    18
        #define OD_7002_19_battery_currentMaxBP1                    19
        #define OD_7002_20_battery_currentMaxBP2                    20
        #define OD_7002_21_battery_currentMinBP1                    21
        #define OD_7002_22_battery_currentMinBP2                    22
        #define OD_7002_23_battery_fullCapacityBP1                  23
        #define OD_7002_24_battery_fullCapacityBP2                  24
        #define OD_7002_25_battery_reportedCapacityBP1              25
        #define OD_7002_26_battery_reportedCapacityBP2              26
        #define OD_7002_27_battery_timeToEmptyBP1                   27
        #define OD_7002_28_battery_timeToEmptyBP2                   28
        #define OD_7002_29_battery_timeToFullBP1                    29
        #define OD_7002_30_battery_timeToFullBP2                    30
        #define OD_7002_31_battery_cyclesBP1                        31
        #define OD_7002_32_battery_cyclesBP2                        32
        #define OD_7002_33_battery_reportedStateOfChargeBP1         33
        #define OD_7002_34_battery_reportedStateOfChargeBP2         34
        #define OD_7002_35_battery_temperatureBP1                   35
        #define OD_7002_36_battery_temperatureBP2                   36
        #define OD_7002_37_battery_temperatureAvgBP1                37
        #define OD_7002_38_battery_temperatureAvgBP2                38
        #define OD_7002_39_battery_temperatureMaxBP1                39
        #define OD_7002_40_battery_temperatureMaxBP2                40
        #define OD_7002_41_battery_temperatureMinBP1                41
        #define OD_7002_42_battery_temperatureMinBP2                42
        #define OD_7002_43_battery_stateBP1                         43
        #define OD_7002_44_battery_stateBP2                         44

/*7003 */
        #define OD_7003_solarPanel                                  0x7003

        #define OD_7003_0_solarPanel_maxSubIndex                    0
        #define OD_7003_1_solarPanel_voltage                        1
        #define OD_7003_2_solarPanel_current                        2
        #define OD_7003_3_solarPanel_power                          3
        #define OD_7003_4_solarPanel_voltageAvg                     4
        #define OD_7003_5_solarPanel_currentAvg                     5
        #define OD_7003_6_solarPanel_powerAvg                       6
        #define OD_7003_7_solarPanel_voltageMax                     7
        #define OD_7003_8_solarPanel_currentMax                     8
        #define OD_7003_9_solarPanel_powerMax                       9
        #define OD_7003_10_solarPanel_energy                        10
        #define OD_7003_11_solarPanel_cell1Temp                     11
        #define OD_7003_12_solarPanel_cell2Temp                     12
        #define OD_7003_13_solarPanel_cell1TempMin                  13
        #define OD_7003_14_solarPanel_cell2TempMin                  14
        #define OD_7003_15_solarPanel_cell1TempMax                  15
        #define OD_7003_16_solarPanel_cell2TempMax                  16

/*7004 */
        #define OD_7004_solarPanel                                  0x7004

        #define OD_7004_0_solarPanel_maxSubIndex                    0
        #define OD_7004_1_solarPanel_voltage                        1
        #define OD_7004_2_solarPanel_current                        2
        #define OD_7004_3_solarPanel_power                          3
        #define OD_7004_4_solarPanel_voltageAvg                     4
        #define OD_7004_5_solarPanel_currentAvg                     5
        #define OD_7004_6_solarPanel_powerAvg                       6
        #define OD_7004_7_solarPanel_voltageMax                     7
        #define OD_7004_8_solarPanel_currentMax                     8
        #define OD_7004_9_solarPanel_powerMax                       9
        #define OD_7004_10_solarPanel_energy                        10
        #define OD_7004_11_solarPanel_cell1Temp                     11
        #define OD_7004_12_solarPanel_cell2Temp                     12
        #define OD_7004_13_solarPanel_cell1TempMin                  13
        #define OD_7004_14_solarPanel_cell2TempMin                  14
        #define OD_7004_15_solarPanel_cell1TempMax                  15
        #define OD_7004_16_solarPanel_cell2TempMax                  16

/*7005 */
        #define OD_7005_solarPanel                                  0x7005

        #define OD_7005_0_solarPanel_maxSubIndex                    0
        #define OD_7005_1_solarPanel_voltage                        1
        #define OD_7005_2_solarPanel_current                        2
        #define OD_7005_3_solarPanel_power                          3
        #define OD_7005_4_solarPanel_voltageAvg                     4
        #define OD_7005_5_solarPanel_currentAvg                     5
        #define OD_7005_6_solarPanel_powerAvg                       6
        #define OD_7005_7_solarPanel_voltageMax                     7
        #define OD_7005_8_solarPanel_currentMax                     8
        #define OD_7005_9_solarPanel_powerMax                       9
        #define OD_7005_10_solarPanel_energy                        10
        #define OD_7005_11_solarPanel_cell1Temp                     11
        #define OD_7005_12_solarPanel_cell2Temp                     12
        #define OD_7005_13_solarPanel_cell1TempMin                  13
        #define OD_7005_14_solarPanel_cell2TempMin                  14
        #define OD_7005_15_solarPanel_cell1TempMax                  15
        #define OD_7005_16_solarPanel_cell2TempMax                  16

/*7006 */
        #define OD_7006_solarPanel                                  0x7006

        #define OD_7006_0_solarPanel_maxSubIndex                    0
        #define OD_7006_1_solarPanel_voltage                        1
        #define OD_7006_2_solarPanel_current                        2
        #define OD_7006_3_solarPanel_power                          3
        #define OD_7006_4_solarPanel_voltageAvg                     4
        #define OD_7006_5_solarPanel_currentAvg                     5
        #define OD_7006_6_solarPanel_powerAvg                       6
        #define OD_7006_7_solarPanel_voltageMax                     7
        #define OD_7006_8_solarPanel_currentMax                     8
        #define OD_7006_9_solarPanel_powerMax                       9
        #define OD_7006_10_solarPanel_energy                        10
        #define OD_7006_11_solarPanel_cell1Temp                     11
        #define OD_7006_12_solarPanel_cell2Temp                     12
        #define OD_7006_13_solarPanel_cell1TempMin                  13
        #define OD_7006_14_solarPanel_cell2TempMin                  14
        #define OD_7006_15_solarPanel_cell1TempMax                  15
        #define OD_7006_16_solarPanel_cell2TempMax                  16

/*7007 */
        #define OD_7007_solarPanel                                  0x7007

        #define OD_7007_0_solarPanel_maxSubIndex                    0
        #define OD_7007_1_solarPanel_voltage                        1
        #define OD_7007_2_solarPanel_current                        2
        #define OD_7007_3_solarPanel_power                          3
        #define OD_7007_4_solarPanel_voltageAvg                     4
        #define OD_7007_5_solarPanel_currentAvg                     5
        #define OD_7007_6_solarPanel_powerAvg                       6
        #define OD_7007_7_solarPanel_voltageMax                     7
        #define OD_7007_8_solarPanel_currentMax                     8
        #define OD_7007_9_solarPanel_powerMax                       9
        #define OD_7007_10_solarPanel_energy                        10
        #define OD_7007_11_solarPanel_cell1Temp                     11
        #define OD_7007_12_solarPanel_cell2Temp                     12
        #define OD_7007_13_solarPanel_cell1TempMin                  13
        #define OD_7007_14_solarPanel_cell2TempMin                  14
        #define OD_7007_15_solarPanel_cell1TempMax                  15
        #define OD_7007_16_solarPanel_cell2TempMax                  16

/*7008 */
        #define OD_7008_solarPanel                                  0x7008

        #define OD_7008_0_solarPanel_maxSubIndex                    0
        #define OD_7008_1_solarPanel_voltage                        1
        #define OD_7008_2_solarPanel_current                        2
        #define OD_7008_3_solarPanel_power                          3
        #define OD_7008_4_solarPanel_voltageAvg                     4
        #define OD_7008_5_solarPanel_currentAvg                     5
        #define OD_7008_6_solarPanel_powerAvg                       6
        #define OD_7008_7_solarPanel_voltageMax                     7
        #define OD_7008_8_solarPanel_currentMax                     8
        #define OD_7008_9_solarPanel_powerMax                       9
        #define OD_7008_10_solarPanel_energy                        10
        #define OD_7008_11_solarPanel_cell1Temp                     11
        #define OD_7008_12_solarPanel_cell2Temp                     12
        #define OD_7008_13_solarPanel_cell1TempMin                  13
        #define OD_7008_14_solarPanel_cell2TempMin                  14
        #define OD_7008_15_solarPanel_cell1TempMax                  15
        #define OD_7008_16_solarPanel_cell2TempMax                  16

/*7009 */
        #define OD_7009_solarPanel                                  0x7009

        #define OD_7009_0_solarPanel_maxSubIndex                    0
        #define OD_7009_1_solarPanel_voltage                        1
        #define OD_7009_2_solarPanel_current                        2
        #define OD_7009_3_solarPanel_power                          3
        #define OD_7009_4_solarPanel_voltageAvg                     4
        #define OD_7009_5_solarPanel_currentAvg                     5
        #define OD_7009_6_solarPanel_powerAvg                       6
        #define OD_7009_7_solarPanel_voltageMax                     7
        #define OD_7009_8_solarPanel_currentMax                     8
        #define OD_7009_9_solarPanel_powerMax                       9
        #define OD_7009_10_solarPanel_energy                        10
        #define OD_7009_11_solarPanel_cell1Temp                     11
        #define OD_7009_12_solarPanel_cell2Temp                     12
        #define OD_7009_13_solarPanel_cell1TempMin                  13
        #define OD_7009_14_solarPanel_cell2TempMin                  14
        #define OD_7009_15_solarPanel_cell1TempMax                  15
        #define OD_7009_16_solarPanel_cell2TempMax                  16

/*700A */
        #define OD_700A_solarPanel                                  0x700A

        #define OD_700A_0_solarPanel_maxSubIndex                    0
        #define OD_700A_1_solarPanel_voltage                        1
        #define OD_700A_2_solarPanel_current                        2
        #define OD_700A_3_solarPanel_power                          3
        #define OD_700A_4_solarPanel_voltageAvg                     4
        #define OD_700A_5_solarPanel_currentAvg                     5
        #define OD_700A_6_solarPanel_powerAvg                       6
        #define OD_700A_7_solarPanel_voltageMax                     7
        #define OD_700A_8_solarPanel_currentMax                     8
        #define OD_700A_9_solarPanel_powerMax                       9
        #define OD_700A_10_solarPanel_energy                        10
        #define OD_700A_11_solarPanel_cell1Temp                     11
        #define OD_700A_12_solarPanel_cell2Temp                     12
        #define OD_700A_13_solarPanel_cell1TempMin                  13
        #define OD_700A_14_solarPanel_cell2TempMin                  14
        #define OD_700A_15_solarPanel_cell1TempMax                  15
        #define OD_700A_16_solarPanel_cell2TempMax                  16

/*700B */
        #define OD_700B_starTracker                                 0x700B

        #define OD_700B_0_starTracker_maxSubIndex                   0
        #define OD_700B_1_starTracker_rootParitionPercent           1
        #define OD_700B_2_starTracker_RAM_Percent                   2
        #define OD_700B_3_starTracker_freadCacheLength              3
        #define OD_700B_4_starTracker_fwriteCacheLength             4
        #define OD_700B_5_starTracker_activeApps                    5
        #define OD_700B_6_starTracker_failedApps                    6
        #define OD_700B_7_starTracker_updaterStatus                 7
        #define OD_700B_8_starTracker_updatesAvailable              8
        #define OD_700B_9_starTracker_rightAscension                9
        #define OD_700B_10_starTracker_declination                  10
        #define OD_700B_11_starTracker_roll                         11
        #define OD_700B_12_starTracker_timestamp                    12

/*700C */
        #define OD_700C_starTracker                                 0x700C

        #define OD_700C_0_starTracker_maxSubIndex                   0
        #define OD_700C_1_starTracker_rootParitionPercent           1
        #define OD_700C_2_starTracker_RAM_Percent                   2
        #define OD_700C_3_starTracker_freadCacheLength              3
        #define OD_700C_4_starTracker_fwriteCacheLength             4
        #define OD_700C_5_starTracker_activeApps                    5
        #define OD_700C_6_starTracker_failedApps                    6
        #define OD_700C_7_starTracker_updaterStatus                 7
        #define OD_700C_8_starTracker_updatesAvailable              8
        #define OD_700C_9_starTracker_rightAscension                9
        #define OD_700C_10_starTracker_declination                  10
        #define OD_700C_11_starTracker_roll                         11
        #define OD_700C_12_starTracker_timestamp                    12

/*700D */
        #define OD_700D_GPS                                         0x700D

        #define OD_700D_0_GPS_maxSubIndex                           0
        #define OD_700D_1_GPS_rootParitionPercent                   1
        #define OD_700D_2_GPS_RAM_Percent                           2
        #define OD_700D_3_GPS_freadCacheLength                      3
        #define OD_700D_4_GPS_fwriteCacheLength                     4
        #define OD_700D_5_GPS_activeApps                            5
        #define OD_700D_6_GPS_failedApps                            6
        #define OD_700D_7_GPS_updaterStatus                         7
        #define OD_700D_8_GPS_updatesAvailable                      8
        #define OD_700D_9_GPS_GPS_Status                            9
        #define OD_700D_10_GPS_satellitesLocked                     10
        #define OD_700D_11_GPS_timestamp                            11
        #define OD_700D_12_GPS_positionX                            12
        #define OD_700D_13_GPS_positionY                            13
        #define OD_700D_14_GPS_positionZ                            14
        #define OD_700D_15_GPS_velocityX                            15
        #define OD_700D_16_GPS_velocityY                            16
        #define OD_700D_17_GPS_velocityZ                            17

/*700E */
        #define OD_700E_ACS                                         0x700E

        #define OD_700E_0_ACS_maxSubIndex                           0
        #define OD_700E_1_ACS_gyroPitch                             1
        #define OD_700E_2_ACS_gyroYaw                               2
        #define OD_700E_3_ACS_gyroRoll                              3
        #define OD_700E_4_ACS_accelerationX                         4
        #define OD_700E_5_ACS_accelerationY                         5
        #define OD_700E_6_ACS_accelerationZ                         6
        #define OD_700E_7_ACS_IMUTemp                               7
        #define OD_700E_8_ACS_magnetometerPZ1X                      8
        #define OD_700E_9_ACS_magnetometerPZ1Y                      9
        #define OD_700E_10_ACS_magnetometerPZ1Z                     10
        #define OD_700E_11_ACS_magnetometerPZ2X                     11
        #define OD_700E_12_ACS_magnetometerPZ2Y                     12
        #define OD_700E_13_ACS_magnetometerPZ2Z                     13
        #define OD_700E_14_ACS_magnetometerMZ1X                     14
        #define OD_700E_15_ACS_magnetometerMZ1Y                     15
        #define OD_700E_16_ACS_magnetometerMZ1Z                     16
        #define OD_700E_17_ACS_magnetometerMZ2X                     17
        #define OD_700E_18_ACS_magnetometerMZ2Y                     18
        #define OD_700E_19_ACS_magnetometerMZ2Z                     19

/*700F */
        #define OD_700F_RWB                                         0x700F

        #define OD_700F_0_RWB_maxSubIndex                           0
        #define OD_700F_1_RWB_subObject1                            1

/*7013 */
        #define OD_7013_dxWiFi                                      0x7013

        #define OD_7013_0_dxWiFi_maxSubIndex                        0
        #define OD_7013_1_dxWiFi_rootParitionPercent                1
        #define OD_7013_2_dxWiFi_RAM_Percent                        2
        #define OD_7013_3_dxWiFi_freadCacheLength                   3
        #define OD_7013_4_dxWiFi_fwriteCacheLength                  4
        #define OD_7013_5_dxWiFi_activeApps                         5
        #define OD_7013_6_dxWiFi_failedApps                         6
        #define OD_7013_7_dxWiFi_updaterStatus                      7
        #define OD_7013_8_dxWiFi_updatesAvailable                   8
        #define OD_7013_9_dxWiFi_transmitting                       9

/*7014 */
        #define OD_7014_CFC                                         0x7014

        #define OD_7014_0_CFC_maxSubIndex                           0
        #define OD_7014_1_CFC_rootParitionPercent                   1
        #define OD_7014_2_CFC_RAM_Percent                           2
        #define OD_7014_3_CFC_freadCacheLength                      3
        #define OD_7014_4_CFC_fwriteCacheLength                     4
        #define OD_7014_5_CFC_activeApps                            5
        #define OD_7014_6_CFC_failedApps                            6
        #define OD_7014_7_CFC_updaterStatus                         7
        #define OD_7014_8_CFC_updatesAvailable                      8

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
/*2020      */ UNSIGNED32      MCU_UniqueDeviceID[3];
/*2021      */ OD_MCU_Calibration_t MCU_Calibration;
/*2022      */ OD_MCU_Sensors_t MCU_Sensors;
/*2100      */ OCTET_STRING   errorStatusBits[10];
/*6000      */ VISIBLE_STRING C3State[1];
/*7000      */ OD_C3Telemetry_t C3Telemetry;
/*7001      */ OD_battery_t    battery[2];
/*7003      */ OD_solarPanel_t solarPanel[8];
/*700B      */ OD_starTracker_t starTracker[2];
/*700D      */ OD_GPS_t        GPS;
/*700E      */ OD_ACS_t        ACS;
/*700F      */ OD_RWB_t        RWB;
/*7013      */ OD_dxWiFi_t     dxWiFi;
/*7014      */ OD_CFC_t        CFC;

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
/*1016      */ UNSIGNED32      consumerHeartbeatTime[32];
/*1017      */ UNSIGNED16     producerHeartbeatTime;
/*1019      */ UNSIGNED8      synchronousCounterOverflowValue;
/*1028      */ UNSIGNED32      emergencyConsumerObject[8];
/*1200      */ OD_SDOServerParameter_t SDOServerParameter[1];
/*1280      */ OD_SDOClientParameter_t SDOClientParameter[1];
/*1400      */ OD_RPDOCommunicationParameter_t RPDOCommunicationParameter[47];
/*1600      */ OD_RPDOMappingParameter_t RPDOMappingParameter[47];
/*1800      */ OD_TPDOCommunicationParameter_t TPDOCommunicationParameter[16];
/*1A00      */ OD_TPDOMappingParameter_t TPDOMappingParameter[16];
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

/*6001      */ OD_stateControl_t stateControl;
/*6002      */ OD_deploymentControl_t deploymentControl;
/*6003      */ OD_TX_Control_t TX_Control;

               UNSIGNED32     LastWord;
};

/***** Structure for PERSIST_STATE variables ********************************************/
struct sCO_OD_PERSIST_STATE{
               UNSIGNED32     FirstWord;

/*6004      */ OD_persistentState_t persistentState;

               UNSIGNED32     LastWord;
};

/***** Declaration of Object Dictionary variables *****************************/
extern struct sCO_OD_RAM CO_OD_RAM;

extern struct sCO_OD_ROM CO_OD_ROM;

extern struct sCO_OD_EEPROM CO_OD_EEPROM;

extern struct sCO_OD_PERSIST_COMM CO_OD_PERSIST_COMM;

extern struct sCO_OD_PERSIST_MFR CO_OD_PERSIST_MFR;

extern struct sCO_OD_PERSIST_APP CO_OD_PERSIST_APP;

extern struct sCO_OD_PERSIST_STATE CO_OD_PERSIST_STATE;

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

/*1016, Data Type: UNSIGNED32, Array[32] */
        #define OD_consumerHeartbeatTime                            CO_OD_PERSIST_COMM.consumerHeartbeatTime
        #define ODL_consumerHeartbeatTime_arrayLength               32
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

/*6000, Data Type: VISIBLE_STRING */
        #define OD_C3State                                          CO_OD_RAM.C3State
        #define ODL_C3State_stringLength                            1

/*6001, Data Type: stateControl_t */
        #define OD_stateControl                                     CO_OD_PERSIST_APP.stateControl

/*6002, Data Type: deploymentControl_t */
        #define OD_deploymentControl                                CO_OD_PERSIST_APP.deploymentControl

/*6003, Data Type: TX_Control_t */
        #define OD_TX_Control                                       CO_OD_PERSIST_APP.TX_Control

/*6004, Data Type: persistentState_t */
        #define OD_persistentState                                  CO_OD_PERSIST_STATE.persistentState

/*7000, Data Type: C3Telemetry_t */
        #define OD_C3Telemetry                                      CO_OD_RAM.C3Telemetry

/*7001, Data Type: battery_t */
        #define OD_battery                                          CO_OD_RAM.battery

/*7003, Data Type: solarPanel_t */
        #define OD_solarPanel                                       CO_OD_RAM.solarPanel

/*700B, Data Type: starTracker_t */
        #define OD_starTracker                                      CO_OD_RAM.starTracker

/*700D, Data Type: GPS_t */
        #define OD_GPS                                              CO_OD_RAM.GPS

/*700E, Data Type: ACS_t */
        #define OD_ACS                                              CO_OD_RAM.ACS

/*700F, Data Type: RWB_t */
        #define OD_RWB                                              CO_OD_RAM.RWB

/*7013, Data Type: dxWiFi_t */
        #define OD_dxWiFi                                           CO_OD_RAM.dxWiFi

/*7014, Data Type: CFC_t */
        #define OD_CFC                                              CO_OD_RAM.CFC

#endif
// clang-format on
