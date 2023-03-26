#ifndef OD_H
#define OD_H

#define OD_CNT_NMT 1
#define OD_CNT_EM 1
#define OD_CNT_SYNC 1
#define OD_CNT_SYNC_PROD 1
#define OD_CNT_STORAGE 1
#define OD_CNT_EM_PROD 1
#define OD_CNT_HB_CONS 1
#define OD_CNT_HB_PROD 1
#define OD_CNT_SDO_SRV 1
#define OD_CNT_RPDO 16
#define OD_CNT_TPDO 16

#define OD_CNT_ARR_1003 8
#define OD_CNT_ARR_1010 4
#define OD_CNT_ARR_1011 4
#define OD_CNT_ARR_1016 8
#define OD_CNT_ARR_1029 6
#define OD_CNT_ARR_2020 3

typedef struct {
    uint32_t x1000_deviceType;
    char x1008_manufacturerDeviceName[12];
    char x1009_manufacturerHardwareVersion[4];
    char x100A_manufacturerSoftwareVersion[6];
    struct {
        uint8_t highestSubIndexSupported;
        uint32_t vendorID;
        uint32_t productCode;
        uint32_t revisionNumber;
        uint32_t serialNumber;
    } x1018_identity;
    uint8_t x1029_errorBehavior_sub0;
    uint8_t x1029_errorBehavior[OD_CNT_ARR_1029];
} OD_ROM_t;

typedef struct {
    uint8_t x1001_errorRegister;
    uint32_t x1002_manufacturerStatusRegister;
    uint8_t x1003_preDefinedErrorField_sub0;
    uint32_t x1003_preDefinedErrorField[OD_CNT_ARR_1003];
    uint8_t x1010_storeParameters_sub0;
    uint32_t x1010_storeParameters[OD_CNT_ARR_1010];
    uint8_t x1011_restoreDefaultParameters_sub0;
    uint32_t x1011_restoreDefaultParameters[OD_CNT_ARR_1011];
    uint64_t x2010_SCET;
    uint64_t x2011_UTC;
    uint8_t x2020_MCU_UniqueDeviceID_sub0;
    uint32_t x2020_MCU_UniqueDeviceID[OD_CNT_ARR_2020];
    struct {
        uint8_t highestSubIndexSupported;
        uint16_t TS_CAL1;
        uint16_t TS_CAL2;
        uint16_t VREFINT_CAL;
    } x2021_MCU_Calibration;
    struct {
        uint8_t highestSubIndexSupported;
        int8_t temperature;
        uint8_t VREFINT;
        uint8_t VBAT;
        uint8_t VBUSP_Current;
        uint16_t temperatureRaw;
        uint16_t VREFINT_Raw;
        uint16_t VBAT_Raw;
        uint16_t VBUSP_CurrentRaw;
    } x2022_MCU_Sensors;
    uint8_t x2100_errorStatusBits[10];
    struct {
        uint8_t highestSubIndexSupported;
        int16_t pitchRate;
        int16_t yawRate;
        int16_t rollRate;
        uint16_t pitchRateRaw;
        uint16_t yawRateRaw;
        uint16_t rollRateRaw;
    } x6000_gyroscope;
    struct {
        uint8_t highestSubIndexSupported;
        int16_t accx;
        int16_t accy;
        int16_t accz;
        uint16_t accXRaw;
        uint16_t accyRaw;
        uint16_t acczRaw;
    } x6001_acceleration;
    int8_t x6002_IMU_Temperature;
    struct {
        uint8_t highestSubIndexSupported;
        int16_t magx;
        int16_t magy;
        int16_t magz;
    } x6003_magnetometerPZ1;
    struct {
        uint8_t highestSubIndexSupported;
        int16_t magx;
        int16_t magy;
        int16_t magz;
    } x6004_magnetometerPZ2;
    struct {
        uint8_t highestSubIndexSupported;
        int16_t magx;
        int16_t magy;
        int16_t magz;
    } x6005_magnetometerMZ1;
    struct {
        uint8_t highestSubIndexSupported;
        int16_t magx;
        int16_t magy;
        int16_t magz;
    } x6006_magnetometerMZ2;
    struct {
        uint8_t highestSubIndexSupported;
        int32_t setMagnetorquerXCurrent;
        int32_t setMagnetorquerYCurrent;
        int32_t setMagnetorquerZCurrent;
        int16_t magnetorquerXPWM_DutyCycle;
        int16_t magnetorquerYPWM_DutyCycle;
        int16_t magnetorquerZPWM_DutyCycle;
        int32_t magnetorquerXCurrent;
        int32_t magnetorquerYCurrent;
        int32_t magnetorquerZCurrent;
    } x6007_magnetorquer;
} OD_RAM_t;

typedef struct {
    uint32_t x1005_COB_ID_SYNC_Message;
    uint32_t x1006_communicationCyclePeriod;
    uint32_t x1007_synchronousWindowLength;
    uint32_t x1014_COB_ID_EMCY;
    uint16_t x1015_inhibitTimeEMCY;
    uint8_t x1016_consumerHeartbeatTime_sub0;
    uint32_t x1016_consumerHeartbeatTime[OD_CNT_ARR_1016];
    uint16_t x1017_producerHeartbeatTime;
    uint8_t x1019_synchronousCounterOverflowValue;
    struct {
        uint8_t highestSubIndexSupported;
        uint32_t COB_ID_ClientToServer;
        uint32_t COB_ID_ServerToClient;
        uint8_t nodeID_OfTheSDO_Client;
    } x1200_SDO_ServerParameter;
    struct {
        uint8_t highestSubIndexSupported;
        uint32_t COB_ID_UsedByRPDO;
        uint8_t transmissionType;
        uint16_t eventTimer;
    } x1400_RPDO_CommunicationParameter;
    struct {
        uint8_t highestSubIndexSupported;
        uint32_t COB_ID_UsedByRPDO;
        uint8_t transmissionType;
        uint16_t eventTimer;
    } x1401_RPDO_CommunicationParameter;
    struct {
        uint8_t highestSubIndexSupported;
        uint32_t COB_ID_UsedByRPDO;
        uint8_t transmissionType;
        uint16_t eventTimer;
    } x1402_RPDO_CommunicationParameter;
    struct {
        uint8_t highestSubIndexSupported;
        uint32_t COB_ID_UsedByRPDO;
        uint8_t transmissionType;
        uint16_t eventTimer;
    } x1403_RPDO_CommunicationParameter;
    struct {
        uint8_t highestSubIndexSupported;
        uint32_t COB_ID_UsedByRPDO;
        uint8_t transmissionType;
        uint16_t eventTimer;
    } x1404_RPDO_CommunicationParameter;
    struct {
        uint8_t highestSubIndexSupported;
        uint32_t COB_ID_UsedByRPDO;
        uint8_t transmissionType;
        uint16_t eventTimer;
    } x1405_RPDO_CommunicationParameter;
    struct {
        uint8_t highestSubIndexSupported;
        uint32_t COB_ID_UsedByRPDO;
        uint8_t transmissionType;
        uint16_t eventTimer;
    } x1406_RPDO_CommunicationParameter;
    struct {
        uint8_t highestSubIndexSupported;
        uint32_t COB_ID_UsedByRPDO;
        uint8_t transmissionType;
        uint16_t eventTimer;
    } x1407_RPDO_CommunicationParameter;
    struct {
        uint8_t highestSubIndexSupported;
        uint32_t COB_ID_UsedByRPDO;
        uint8_t transmissionType;
        uint16_t eventTimer;
    } x1408_RPDO_CommunicationParameter;
    struct {
        uint8_t highestSubIndexSupported;
        uint32_t COB_ID_UsedByRPDO;
        uint8_t transmissionType;
        uint16_t eventTimer;
    } x1409_RPDO_CommunicationParameter;
    struct {
        uint8_t highestSubIndexSupported;
        uint32_t COB_ID_UsedByRPDO;
        uint8_t transmissionType;
        uint16_t eventTimer;
    } x140A_RPDO_CommunicationParameter;
    struct {
        uint8_t highestSubIndexSupported;
        uint32_t COB_ID_UsedByRPDO;
        uint8_t transmissionType;
        uint16_t eventTimer;
    } x140B_RPDO_CommunicationParameter;
    struct {
        uint8_t highestSubIndexSupported;
        uint32_t COB_ID_UsedByRPDO;
        uint8_t transmissionType;
        uint16_t eventTimer;
    } x140C_RPDO_CommunicationParameter;
    struct {
        uint8_t highestSubIndexSupported;
        uint32_t COB_ID_UsedByRPDO;
        uint8_t transmissionType;
        uint16_t eventTimer;
    } x140D_RPDO_CommunicationParameter;
    struct {
        uint8_t highestSubIndexSupported;
        uint32_t COB_ID_UsedByRPDO;
        uint8_t transmissionType;
        uint16_t eventTimer;
    } x140E_RPDO_CommunicationParameter;
    struct {
        uint8_t highestSubIndexSupported;
        uint32_t COB_ID_UsedByRPDO;
        uint8_t transmissionType;
        uint16_t eventTimer;
    } x140F_RPDO_CommunicationParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject_1;
        uint32_t applicationObject_2;
        uint32_t applicationObject_3;
        uint32_t applicationObject_4;
        uint32_t applicationObject_5;
        uint32_t applicationObject_6;
        uint32_t applicationObject_7;
        uint32_t applicationObject_8;
    } x1600_RPDO_MappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject_1;
        uint32_t applicationObject_2;
        uint32_t applicationObject_3;
        uint32_t applicationObject_4;
        uint32_t applicationObject_5;
        uint32_t applicationObject_6;
        uint32_t applicationObject_7;
        uint32_t applicationObject_8;
    } x1601_RPDO_MappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject_1;
        uint32_t applicationObject_2;
        uint32_t applicationObject_3;
        uint32_t applicationObject_4;
        uint32_t applicationObject_5;
        uint32_t applicationObject_6;
        uint32_t applicationObject_7;
        uint32_t applicationObject_8;
    } x1602_RPDO_MappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject_1;
        uint32_t applicationObject_2;
        uint32_t applicationObject_3;
        uint32_t applicationObject_4;
        uint32_t applicationObject_5;
        uint32_t applicationObject_6;
        uint32_t applicationObject_7;
        uint32_t applicationObject_8;
    } x1603_RPDO_MappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject_1;
        uint32_t applicationObject_2;
        uint32_t applicationObject_3;
        uint32_t applicationObject_4;
        uint32_t applicationObject_5;
        uint32_t applicationObject_6;
        uint32_t applicationObject_7;
        uint32_t applicationObject_8;
    } x1604_RPDO_MappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject_1;
        uint32_t applicationObject_2;
        uint32_t applicationObject_3;
        uint32_t applicationObject_4;
        uint32_t applicationObject_5;
        uint32_t applicationObject_6;
        uint32_t applicationObject_7;
        uint32_t applicationObject_8;
    } x1605_RPDO_MappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject_1;
        uint32_t applicationObject_2;
        uint32_t applicationObject_3;
        uint32_t applicationObject_4;
        uint32_t applicationObject_5;
        uint32_t applicationObject_6;
        uint32_t applicationObject_7;
        uint32_t applicationObject_8;
    } x1606_RPDO_MappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject_1;
        uint32_t applicationObject_2;
        uint32_t applicationObject_3;
        uint32_t applicationObject_4;
        uint32_t applicationObject_5;
        uint32_t applicationObject_6;
        uint32_t applicationObject_7;
        uint32_t applicationObject_8;
    } x1607_RPDO_MappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject_1;
        uint32_t applicationObject_2;
        uint32_t applicationObject_3;
        uint32_t applicationObject_4;
        uint32_t applicationObject_5;
        uint32_t applicationObject_6;
        uint32_t applicationObject_7;
        uint32_t applicationObject_8;
    } x1608_RPDO_MappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject_1;
        uint32_t applicationObject_2;
        uint32_t applicationObject_3;
        uint32_t applicationObject_4;
        uint32_t applicationObject_5;
        uint32_t applicationObject_6;
        uint32_t applicationObject_7;
        uint32_t applicationObject_8;
    } x1609_RPDO_MappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject_1;
        uint32_t applicationObject_2;
        uint32_t applicationObject_3;
        uint32_t applicationObject_4;
        uint32_t applicationObject_5;
        uint32_t applicationObject_6;
        uint32_t applicationObject_7;
        uint32_t applicationObject_8;
    } x160A_RPDO_MappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject_1;
        uint32_t applicationObject_2;
        uint32_t applicationObject_3;
        uint32_t applicationObject_4;
        uint32_t applicationObject_5;
        uint32_t applicationObject_6;
        uint32_t applicationObject_7;
        uint32_t applicationObject_8;
    } x160B_RPDO_MappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject_1;
        uint32_t applicationObject_2;
        uint32_t applicationObject_3;
        uint32_t applicationObject_4;
        uint32_t applicationObject_5;
        uint32_t applicationObject_6;
        uint32_t applicationObject_7;
        uint32_t applicationObject_8;
    } x160C_RPDO_MappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject_1;
        uint32_t applicationObject_2;
        uint32_t applicationObject_3;
        uint32_t applicationObject_4;
        uint32_t applicationObject_5;
        uint32_t applicationObject_6;
        uint32_t applicationObject_7;
        uint32_t applicationObject_8;
    } x160D_RPDO_MappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject_1;
        uint32_t applicationObject_2;
        uint32_t applicationObject_3;
        uint32_t applicationObject_4;
        uint32_t applicationObject_5;
        uint32_t applicationObject_6;
        uint32_t applicationObject_7;
        uint32_t applicationObject_8;
    } x160E_RPDO_MappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject_1;
        uint32_t applicationObject_2;
        uint32_t applicationObject_3;
        uint32_t applicationObject_4;
        uint32_t applicationObject_5;
        uint32_t applicationObject_6;
        uint32_t applicationObject_7;
        uint32_t applicationObject_8;
    } x160F_RPDO_MappingParameter;
    struct {
        uint8_t highestSubIndexSupported;
        uint32_t COB_ID_UsedByTPDO;
        uint8_t transmissionType;
        uint16_t inhibitTime;
        uint8_t compatibilityEntry;
        uint16_t eventTimer;
        uint8_t SYNC_StartValue;
    } x1800_TPDO_CommunicationParameter;
    struct {
        uint8_t highestSubIndexSupported;
        uint32_t COB_ID_UsedByTPDO;
        uint8_t transmissionType;
        uint16_t inhibitTime;
        uint8_t compatibilityEntry;
        uint16_t eventTimer;
        uint8_t SYNC_StartValue;
    } x1801_TPDO_CommunicationParameter;
    struct {
        uint8_t highestSubIndexSupported;
        uint32_t COB_ID_UsedByTPDO;
        uint8_t transmissionType;
        uint16_t inhibitTime;
        uint8_t compatibilityEntry;
        uint16_t eventTimer;
        uint8_t SYNC_StartValue;
    } x1802_TPDO_CommunicationParameter;
    struct {
        uint8_t highestSubIndexSupported;
        uint32_t COB_ID_UsedByTPDO;
        uint8_t transmissionType;
        uint16_t inhibitTime;
        uint8_t compatibilityEntry;
        uint16_t eventTimer;
        uint8_t SYNC_StartValue;
    } x1803_TPDO_CommunicationParameter;
    struct {
        uint8_t highestSubIndexSupported;
        uint32_t COB_ID_UsedByTPDO;
        uint8_t transmissionType;
        uint16_t inhibitTime;
        uint8_t compatibilityEntry;
        uint16_t eventTimer;
        uint8_t SYNC_StartValue;
    } x1804_TPDO_CommunicationParameter;
    struct {
        uint8_t highestSubIndexSupported;
        uint32_t COB_ID_UsedByTPDO;
        uint8_t transmissionType;
        uint16_t inhibitTime;
        uint8_t compatibilityEntry;
        uint16_t eventTimer;
        uint8_t SYNC_StartValue;
    } x1805_TPDO_CommunicationParameter;
    struct {
        uint8_t highestSubIndexSupported;
        uint32_t COB_ID_UsedByTPDO;
        uint8_t transmissionType;
        uint16_t inhibitTime;
        uint8_t compatibilityEntry;
        uint16_t eventTimer;
        uint8_t SYNC_StartValue;
    } x1806_TPDO_CommunicationParameter;
    struct {
        uint8_t highestSubIndexSupported;
        uint32_t COB_ID_UsedByTPDO;
        uint8_t transmissionType;
        uint16_t inhibitTime;
        uint8_t compatibilityEntry;
        uint16_t eventTimer;
        uint8_t SYNC_StartValue;
    } x1807_TPDO_CommunicationParameter;
    struct {
        uint8_t highestSubIndexSupported;
        uint32_t COB_ID_UsedByTPDO;
        uint8_t transmissionType;
        uint16_t inhibitTime;
        uint8_t compatibilityEntry;
        uint16_t eventTimer;
        uint8_t SYNC_StartValue;
    } x1808_TPDO_CommunicationParameter;
    struct {
        uint8_t highestSubIndexSupported;
        uint32_t COB_ID_UsedByTPDO;
        uint8_t transmissionType;
        uint16_t inhibitTime;
        uint8_t compatibilityEntry;
        uint16_t eventTimer;
        uint8_t SYNC_StartValue;
    } x1809_TPDO_CommunicationParameter;
    struct {
        uint8_t highestSubIndexSupported;
        uint32_t COB_ID_UsedByTPDO;
        uint8_t transmissionType;
        uint16_t inhibitTime;
        uint8_t compatibilityEntry;
        uint16_t eventTimer;
        uint8_t SYNC_StartValue;
    } x180A_TPDO_CommunicationParameter;
    struct {
        uint8_t highestSubIndexSupported;
        uint32_t COB_ID_UsedByTPDO;
        uint8_t transmissionType;
        uint16_t inhibitTime;
        uint8_t compatibilityEntry;
        uint16_t eventTimer;
        uint8_t SYNC_StartValue;
    } x180B_TPDO_CommunicationParameter;
    struct {
        uint8_t highestSubIndexSupported;
        uint32_t COB_ID_UsedByTPDO;
        uint8_t transmissionType;
        uint16_t inhibitTime;
        uint8_t compatibilityEntry;
        uint16_t eventTimer;
        uint8_t SYNC_StartValue;
    } x180C_TPDO_CommunicationParameter;
    struct {
        uint8_t highestSubIndexSupported;
        uint32_t COB_ID_UsedByTPDO;
        uint8_t transmissionType;
        uint16_t inhibitTime;
        uint8_t compatibilityEntry;
        uint16_t eventTimer;
        uint8_t SYNC_StartValue;
    } x180D_TPDO_CommunicationParameter;
    struct {
        uint8_t highestSubIndexSupported;
        uint32_t COB_ID_UsedByTPDO;
        uint8_t transmissionType;
        uint16_t inhibitTime;
        uint8_t compatibilityEntry;
        uint16_t eventTimer;
        uint8_t SYNC_StartValue;
    } x180E_TPDO_CommunicationParameter;
    struct {
        uint8_t highestSubIndexSupported;
        uint32_t COB_ID_UsedByTPDO;
        uint8_t transmissionType;
        uint16_t inhibitTime;
        uint8_t compatibilityEntry;
        uint16_t eventTimer;
        uint8_t SYNC_StartValue;
    } x180F_TPDO_CommunicationParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject_1;
        uint32_t applicationObject_2;
        uint32_t applicationObject_3;
        uint32_t applicationObject_4;
        uint32_t applicationObject_5;
        uint32_t applicationObject_6;
        uint32_t applicationObject_7;
        uint32_t applicationObject_8;
    } x1A00_TPDO_MappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject_1;
        uint32_t applicationObject_2;
        uint32_t applicationObject_3;
        uint32_t applicationObject_4;
        uint32_t applicationObject_5;
        uint32_t applicationObject_6;
        uint32_t applicationObject_7;
        uint32_t applicationObject_8;
    } x1A01_TPDO_MappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject_1;
        uint32_t applicationObject_2;
        uint32_t applicationObject_3;
        uint32_t applicationObject_4;
        uint32_t applicationObject_5;
        uint32_t applicationObject_6;
        uint32_t applicationObject_7;
        uint32_t applicationObject_8;
    } x1A02_TPDO_MappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject_1;
        uint32_t applicationObject_2;
        uint32_t applicationObject_3;
        uint32_t applicationObject_4;
        uint32_t applicationObject_5;
        uint32_t applicationObject_6;
        uint32_t applicationObject_7;
        uint32_t applicationObject_8;
    } x1A03_TPDO_MappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject_1;
        uint32_t applicationObject_2;
        uint32_t applicationObject_3;
        uint32_t applicationObject_4;
        uint32_t applicationObject_5;
        uint32_t applicationObject_6;
        uint32_t applicationObject_7;
        uint32_t applicationObject_8;
    } x1A04_TPDO_MappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject_1;
        uint32_t applicationObject_2;
        uint32_t applicationObject_3;
        uint32_t applicationObject_4;
        uint32_t applicationObject_5;
        uint32_t applicationObject_6;
        uint32_t applicationObject_7;
        uint32_t applicationObject_8;
    } x1A05_TPDO_MappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject_1;
        uint32_t applicationObject_2;
        uint32_t applicationObject_3;
        uint32_t applicationObject_4;
        uint32_t applicationObject_5;
        uint32_t applicationObject_6;
        uint32_t applicationObject_7;
        uint32_t applicationObject_8;
    } x1A06_TPDO_MappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject_1;
        uint32_t applicationObject_2;
        uint32_t applicationObject_3;
        uint32_t applicationObject_4;
        uint32_t applicationObject_5;
        uint32_t applicationObject_6;
        uint32_t applicationObject_7;
        uint32_t applicationObject_8;
    } x1A07_TPDO_MappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject_1;
        uint32_t applicationObject_2;
        uint32_t applicationObject_3;
        uint32_t applicationObject_4;
        uint32_t applicationObject_5;
        uint32_t applicationObject_6;
        uint32_t applicationObject_7;
        uint32_t applicationObject_8;
    } x1A08_TPDO_MappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject_1;
        uint32_t applicationObject_2;
        uint32_t applicationObject_3;
        uint32_t applicationObject_4;
        uint32_t applicationObject_5;
        uint32_t applicationObject_6;
        uint32_t applicationObject_7;
        uint32_t applicationObject_8;
    } x1A09_TPDO_MappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject_1;
        uint32_t applicationObject_2;
        uint32_t applicationObject_3;
        uint32_t applicationObject_4;
        uint32_t applicationObject_5;
        uint32_t applicationObject_6;
        uint32_t applicationObject_7;
        uint32_t applicationObject_8;
    } x1A0A_TPDO_MappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject_1;
        uint32_t applicationObject_2;
        uint32_t applicationObject_3;
        uint32_t applicationObject_4;
        uint32_t applicationObject_5;
        uint32_t applicationObject_6;
        uint32_t applicationObject_7;
        uint32_t applicationObject_8;
    } x1A0B_TPDO_MappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject_1;
        uint32_t applicationObject_2;
        uint32_t applicationObject_3;
        uint32_t applicationObject_4;
        uint32_t applicationObject_5;
        uint32_t applicationObject_6;
        uint32_t applicationObject_7;
        uint32_t applicationObject_8;
    } x1A0C_TPDO_MappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject_1;
        uint32_t applicationObject_2;
        uint32_t applicationObject_3;
        uint32_t applicationObject_4;
        uint32_t applicationObject_5;
        uint32_t applicationObject_6;
        uint32_t applicationObject_7;
        uint32_t applicationObject_8;
    } x1A0D_TPDO_MappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject_1;
        uint32_t applicationObject_2;
        uint32_t applicationObject_3;
        uint32_t applicationObject_4;
        uint32_t applicationObject_5;
        uint32_t applicationObject_6;
        uint32_t applicationObject_7;
        uint32_t applicationObject_8;
    } x1A0E_TPDO_MappingParameter;
    struct {
        uint8_t numberOfMappedApplicationObjectsInPDO;
        uint32_t applicationObject_1;
        uint32_t applicationObject_2;
        uint32_t applicationObject_3;
        uint32_t applicationObject_4;
        uint32_t applicationObject_5;
        uint32_t applicationObject_6;
        uint32_t applicationObject_7;
        uint32_t applicationObject_8;
    } x1A0F_TPDO_MappingParameter;
    uint32_t x1F80_nmtstartup;
} OD_PERSIST_COMM_t;

typedef struct {
    struct {
        uint8_t highestSubIndexSupported;
        uint8_t bdefault;
        uint8_t ttoggle;
        uint8_t ntoggle;
        uint8_t ctoggle;
    } x2000_BUS_Management;
} OD_PERSIST_MFR_t;

#ifndef OD_ATTR_ROM
#define OD_ATTR_ROM
#endif
extern OD_ATTR_ROM OD_ROM_t OD_ROM;

#ifndef OD_ATTR_RAM
#define OD_ATTR_RAM
#endif
extern OD_ATTR_RAM OD_RAM_t OD_RAM;

#ifndef OD_ATTR_PERSIST_COMM
#define OD_ATTR_PERSIST_COMM
#endif
extern OD_ATTR_PERSIST_COMM OD_PERSIST_COMM_t OD_PERSIST_COMM;

#ifndef OD_ATTR_PERSIST_MFR
#define OD_ATTR_PERSIST_MFR
#endif
extern OD_ATTR_PERSIST_MFR OD_PERSIST_MFR_t OD_PERSIST_MFR;

#ifndef OD_ATTR_OD
#define OD_ATTR_OD
#endif
extern OD_ATTR_OD OD_t *OD;

#define OD_ENTRY_H1000 &OD->list[0]
#define OD_ENTRY_H1001 &OD->list[1]
#define OD_ENTRY_H1002 &OD->list[2]
#define OD_ENTRY_H1003 &OD->list[3]
#define OD_ENTRY_H1005 &OD->list[4]
#define OD_ENTRY_H1006 &OD->list[5]
#define OD_ENTRY_H1007 &OD->list[6]
#define OD_ENTRY_H1008 &OD->list[7]
#define OD_ENTRY_H1009 &OD->list[8]
#define OD_ENTRY_H100A &OD->list[9]
#define OD_ENTRY_H1010 &OD->list[10]
#define OD_ENTRY_H1011 &OD->list[11]
#define OD_ENTRY_H1014 &OD->list[12]
#define OD_ENTRY_H1015 &OD->list[13]
#define OD_ENTRY_H1016 &OD->list[14]
#define OD_ENTRY_H1017 &OD->list[15]
#define OD_ENTRY_H1018 &OD->list[16]
#define OD_ENTRY_H1019 &OD->list[17]
#define OD_ENTRY_H1029 &OD->list[18]
#define OD_ENTRY_H1200 &OD->list[19]
#define OD_ENTRY_H1400 &OD->list[20]
#define OD_ENTRY_H1401 &OD->list[21]
#define OD_ENTRY_H1402 &OD->list[22]
#define OD_ENTRY_H1403 &OD->list[23]
#define OD_ENTRY_H1404 &OD->list[24]
#define OD_ENTRY_H1405 &OD->list[25]
#define OD_ENTRY_H1406 &OD->list[26]
#define OD_ENTRY_H1407 &OD->list[27]
#define OD_ENTRY_H1408 &OD->list[28]
#define OD_ENTRY_H1409 &OD->list[29]
#define OD_ENTRY_H140A &OD->list[30]
#define OD_ENTRY_H140B &OD->list[31]
#define OD_ENTRY_H140C &OD->list[32]
#define OD_ENTRY_H140D &OD->list[33]
#define OD_ENTRY_H140E &OD->list[34]
#define OD_ENTRY_H140F &OD->list[35]
#define OD_ENTRY_H1600 &OD->list[36]
#define OD_ENTRY_H1601 &OD->list[37]
#define OD_ENTRY_H1602 &OD->list[38]
#define OD_ENTRY_H1603 &OD->list[39]
#define OD_ENTRY_H1604 &OD->list[40]
#define OD_ENTRY_H1605 &OD->list[41]
#define OD_ENTRY_H1606 &OD->list[42]
#define OD_ENTRY_H1607 &OD->list[43]
#define OD_ENTRY_H1608 &OD->list[44]
#define OD_ENTRY_H1609 &OD->list[45]
#define OD_ENTRY_H160A &OD->list[46]
#define OD_ENTRY_H160B &OD->list[47]
#define OD_ENTRY_H160C &OD->list[48]
#define OD_ENTRY_H160D &OD->list[49]
#define OD_ENTRY_H160E &OD->list[50]
#define OD_ENTRY_H160F &OD->list[51]
#define OD_ENTRY_H1800 &OD->list[52]
#define OD_ENTRY_H1801 &OD->list[53]
#define OD_ENTRY_H1802 &OD->list[54]
#define OD_ENTRY_H1803 &OD->list[55]
#define OD_ENTRY_H1804 &OD->list[56]
#define OD_ENTRY_H1805 &OD->list[57]
#define OD_ENTRY_H1806 &OD->list[58]
#define OD_ENTRY_H1807 &OD->list[59]
#define OD_ENTRY_H1808 &OD->list[60]
#define OD_ENTRY_H1809 &OD->list[61]
#define OD_ENTRY_H180A &OD->list[62]
#define OD_ENTRY_H180B &OD->list[63]
#define OD_ENTRY_H180C &OD->list[64]
#define OD_ENTRY_H180D &OD->list[65]
#define OD_ENTRY_H180E &OD->list[66]
#define OD_ENTRY_H180F &OD->list[67]
#define OD_ENTRY_H1A00 &OD->list[68]
#define OD_ENTRY_H1A01 &OD->list[69]
#define OD_ENTRY_H1A02 &OD->list[70]
#define OD_ENTRY_H1A03 &OD->list[71]
#define OD_ENTRY_H1A04 &OD->list[72]
#define OD_ENTRY_H1A05 &OD->list[73]
#define OD_ENTRY_H1A06 &OD->list[74]
#define OD_ENTRY_H1A07 &OD->list[75]
#define OD_ENTRY_H1A08 &OD->list[76]
#define OD_ENTRY_H1A09 &OD->list[77]
#define OD_ENTRY_H1A0A &OD->list[78]
#define OD_ENTRY_H1A0B &OD->list[79]
#define OD_ENTRY_H1A0C &OD->list[80]
#define OD_ENTRY_H1A0D &OD->list[81]
#define OD_ENTRY_H1A0E &OD->list[82]
#define OD_ENTRY_H1A0F &OD->list[83]
#define OD_ENTRY_H1F80 &OD->list[84]
#define OD_ENTRY_H2000 &OD->list[85]
#define OD_ENTRY_H2010 &OD->list[86]
#define OD_ENTRY_H2011 &OD->list[87]
#define OD_ENTRY_H2020 &OD->list[88]
#define OD_ENTRY_H2021 &OD->list[89]
#define OD_ENTRY_H2022 &OD->list[90]
#define OD_ENTRY_H2100 &OD->list[91]
#define OD_ENTRY_H6000 &OD->list[92]
#define OD_ENTRY_H6001 &OD->list[93]
#define OD_ENTRY_H6002 &OD->list[94]
#define OD_ENTRY_H6003 &OD->list[95]
#define OD_ENTRY_H6004 &OD->list[96]
#define OD_ENTRY_H6005 &OD->list[97]
#define OD_ENTRY_H6006 &OD->list[98]
#define OD_ENTRY_H6007 &OD->list[99]

#define OD_ENTRY_H1000_deviceType &OD->list[0]
#define OD_ENTRY_H1001_errorRegister &OD->list[1]
#define OD_ENTRY_H1002_manufacturerStatusRegister &OD->list[2]
#define OD_ENTRY_H1003_preDefinedErrorField &OD->list[3]
#define OD_ENTRY_H1005_COB_ID_SYNC_Message &OD->list[4]
#define OD_ENTRY_H1006_communicationCyclePeriod &OD->list[5]
#define OD_ENTRY_H1007_synchronousWindowLength &OD->list[6]
#define OD_ENTRY_H1008_manufacturerDeviceName &OD->list[7]
#define OD_ENTRY_H1009_manufacturerHardwareVersion &OD->list[8]
#define OD_ENTRY_H100A_manufacturerSoftwareVersion &OD->list[9]
#define OD_ENTRY_H1010_storeParameters &OD->list[10]
#define OD_ENTRY_H1011_restoreDefaultParameters &OD->list[11]
#define OD_ENTRY_H1014_COB_ID_EMCY &OD->list[12]
#define OD_ENTRY_H1015_inhibitTimeEMCY &OD->list[13]
#define OD_ENTRY_H1016_consumerHeartbeatTime &OD->list[14]
#define OD_ENTRY_H1017_producerHeartbeatTime &OD->list[15]
#define OD_ENTRY_H1018_identity &OD->list[16]
#define OD_ENTRY_H1019_synchronousCounterOverflowValue &OD->list[17]
#define OD_ENTRY_H1029_errorBehavior &OD->list[18]
#define OD_ENTRY_H1200_SDO_ServerParameter &OD->list[19]
#define OD_ENTRY_H1400_RPDO_CommunicationParameter &OD->list[20]
#define OD_ENTRY_H1401_RPDO_CommunicationParameter &OD->list[21]
#define OD_ENTRY_H1402_RPDO_CommunicationParameter &OD->list[22]
#define OD_ENTRY_H1403_RPDO_CommunicationParameter &OD->list[23]
#define OD_ENTRY_H1404_RPDO_CommunicationParameter &OD->list[24]
#define OD_ENTRY_H1405_RPDO_CommunicationParameter &OD->list[25]
#define OD_ENTRY_H1406_RPDO_CommunicationParameter &OD->list[26]
#define OD_ENTRY_H1407_RPDO_CommunicationParameter &OD->list[27]
#define OD_ENTRY_H1408_RPDO_CommunicationParameter &OD->list[28]
#define OD_ENTRY_H1409_RPDO_CommunicationParameter &OD->list[29]
#define OD_ENTRY_H140A_RPDO_CommunicationParameter &OD->list[30]
#define OD_ENTRY_H140B_RPDO_CommunicationParameter &OD->list[31]
#define OD_ENTRY_H140C_RPDO_CommunicationParameter &OD->list[32]
#define OD_ENTRY_H140D_RPDO_CommunicationParameter &OD->list[33]
#define OD_ENTRY_H140E_RPDO_CommunicationParameter &OD->list[34]
#define OD_ENTRY_H140F_RPDO_CommunicationParameter &OD->list[35]
#define OD_ENTRY_H1600_RPDO_MappingParameter &OD->list[36]
#define OD_ENTRY_H1601_RPDO_MappingParameter &OD->list[37]
#define OD_ENTRY_H1602_RPDO_MappingParameter &OD->list[38]
#define OD_ENTRY_H1603_RPDO_MappingParameter &OD->list[39]
#define OD_ENTRY_H1604_RPDO_MappingParameter &OD->list[40]
#define OD_ENTRY_H1605_RPDO_MappingParameter &OD->list[41]
#define OD_ENTRY_H1606_RPDO_MappingParameter &OD->list[42]
#define OD_ENTRY_H1607_RPDO_MappingParameter &OD->list[43]
#define OD_ENTRY_H1608_RPDO_MappingParameter &OD->list[44]
#define OD_ENTRY_H1609_RPDO_MappingParameter &OD->list[45]
#define OD_ENTRY_H160A_RPDO_MappingParameter &OD->list[46]
#define OD_ENTRY_H160B_RPDO_MappingParameter &OD->list[47]
#define OD_ENTRY_H160C_RPDO_MappingParameter &OD->list[48]
#define OD_ENTRY_H160D_RPDO_MappingParameter &OD->list[49]
#define OD_ENTRY_H160E_RPDO_MappingParameter &OD->list[50]
#define OD_ENTRY_H160F_RPDO_MappingParameter &OD->list[51]
#define OD_ENTRY_H1800_TPDO_CommunicationParameter &OD->list[52]
#define OD_ENTRY_H1801_TPDO_CommunicationParameter &OD->list[53]
#define OD_ENTRY_H1802_TPDO_CommunicationParameter &OD->list[54]
#define OD_ENTRY_H1803_TPDO_CommunicationParameter &OD->list[55]
#define OD_ENTRY_H1804_TPDO_CommunicationParameter &OD->list[56]
#define OD_ENTRY_H1805_TPDO_CommunicationParameter &OD->list[57]
#define OD_ENTRY_H1806_TPDO_CommunicationParameter &OD->list[58]
#define OD_ENTRY_H1807_TPDO_CommunicationParameter &OD->list[59]
#define OD_ENTRY_H1808_TPDO_CommunicationParameter &OD->list[60]
#define OD_ENTRY_H1809_TPDO_CommunicationParameter &OD->list[61]
#define OD_ENTRY_H180A_TPDO_CommunicationParameter &OD->list[62]
#define OD_ENTRY_H180B_TPDO_CommunicationParameter &OD->list[63]
#define OD_ENTRY_H180C_TPDO_CommunicationParameter &OD->list[64]
#define OD_ENTRY_H180D_TPDO_CommunicationParameter &OD->list[65]
#define OD_ENTRY_H180E_TPDO_CommunicationParameter &OD->list[66]
#define OD_ENTRY_H180F_TPDO_CommunicationParameter &OD->list[67]
#define OD_ENTRY_H1A00_TPDO_MappingParameter &OD->list[68]
#define OD_ENTRY_H1A01_TPDO_MappingParameter &OD->list[69]
#define OD_ENTRY_H1A02_TPDO_MappingParameter &OD->list[70]
#define OD_ENTRY_H1A03_TPDO_MappingParameter &OD->list[71]
#define OD_ENTRY_H1A04_TPDO_MappingParameter &OD->list[72]
#define OD_ENTRY_H1A05_TPDO_MappingParameter &OD->list[73]
#define OD_ENTRY_H1A06_TPDO_MappingParameter &OD->list[74]
#define OD_ENTRY_H1A07_TPDO_MappingParameter &OD->list[75]
#define OD_ENTRY_H1A08_TPDO_MappingParameter &OD->list[76]
#define OD_ENTRY_H1A09_TPDO_MappingParameter &OD->list[77]
#define OD_ENTRY_H1A0A_TPDO_MappingParameter &OD->list[78]
#define OD_ENTRY_H1A0B_TPDO_MappingParameter &OD->list[79]
#define OD_ENTRY_H1A0C_TPDO_MappingParameter &OD->list[80]
#define OD_ENTRY_H1A0D_TPDO_MappingParameter &OD->list[81]
#define OD_ENTRY_H1A0E_TPDO_MappingParameter &OD->list[82]
#define OD_ENTRY_H1A0F_TPDO_MappingParameter &OD->list[83]
#define OD_ENTRY_H1F80_nmtstartup &OD->list[84]
#define OD_ENTRY_H2000_BUS_Management &OD->list[85]
#define OD_ENTRY_H2010_SCET &OD->list[86]
#define OD_ENTRY_H2011_UTC &OD->list[87]
#define OD_ENTRY_H2020_MCU_UniqueDeviceID &OD->list[88]
#define OD_ENTRY_H2021_MCU_Calibration &OD->list[89]
#define OD_ENTRY_H2022_MCU_Sensors &OD->list[90]
#define OD_ENTRY_H2100_errorStatusBits &OD->list[91]
#define OD_ENTRY_H6000_gyroscope &OD->list[92]
#define OD_ENTRY_H6001_acceleration &OD->list[93]
#define OD_ENTRY_H6002_IMU_Temperature &OD->list[94]
#define OD_ENTRY_H6003_magnetometerPZ1 &OD->list[95]
#define OD_ENTRY_H6004_magnetometerPZ2 &OD->list[96]
#define OD_ENTRY_H6005_magnetometerMZ1 &OD->list[97]
#define OD_ENTRY_H6006_magnetometerMZ2 &OD->list[98]
#define OD_ENTRY_H6007_magnetorquer &OD->list[99]

#endif /* OD_H */
