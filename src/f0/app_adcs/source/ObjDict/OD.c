#define OD_DEFINITION
#include "301/CO_ODinterface.h"
#include "OD.h"

#if CO_VERSION_MAJOR < 4
#error This object dictionary is only comatible with CANopenNode v4 and above
#endif

OD_ATTR_ROM OD_ROM_t OD_ROM = {
    .x1000_deviceType = 0x00000000,
    .x1008_manufacturerDeviceName = "OreSat Node",
    .x1009_manufacturerHardwareVersion = "0.0",
    .x100A_manufacturerSoftwareVersion = "0.0.0",
    .x1018_identity = {
        .highestSubIndexSupported = 0x04,
        .vendorID = 0x00000000,
        .productCode = 0x00000000,
        .revisionNumber = 0x00000000,
        .serialNumber = 0x00000000,
    },
    .x1029_errorBehavior_sub0 = 0x06,
    .x1029_errorBehavior = {0x01, 0x01, 0x01, 0x01, 0x01, 0x01},
};

OD_ATTR_RAM OD_RAM_t OD_RAM = {
    .x1001_errorRegister = 0x00,
    .x1002_manufacturerStatusRegister = 0,
    .x1003_preDefinedErrorField_sub0 = 0x08,
    .x1003_preDefinedErrorField = {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000},
    .x1010_storeParameters_sub0 = 0x04,
    .x1010_storeParameters = {0x00000001, 0x00000001, 0x00000001, 0x00000001},
    .x1011_restoreDefaultParameters_sub0 = 0x04,
    .x1011_restoreDefaultParameters = {0x00000001, 0x00000001, 0x00000001, 0x00000001},
    .x2010_SCET = 0,
    .x2011_UTC = 0,
    .x2020_MCU_UniqueDeviceID_sub0 = 0x03,
    .x2020_MCU_UniqueDeviceID = {0, 0, 0},
    .x2021_MCU_Calibration = {
        .highestSubIndexSupported = 0x03,
        .TS_CAL1 = 0,
        .TS_CAL2 = 0,
        .VREFINT_CAL = 0,
    },
    .x2022_MCU_Sensors = {
        .highestSubIndexSupported = 0x08,
        .temperature = 0,
        .VREFINT = 0,
        .VBAT = 0,
        .VBUSP_Current = 0,
        .temperatureRaw = 0,
        .VREFINT_Raw = 0,
        .VBAT_Raw = 0,
        .VBUSP_CurrentRaw = 0,
    },
    .x2100_errorStatusBits = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    .x6000_gyroscope = {
        .highestSubIndexSupported = 0x06,
        .pitchRate = 0,
        .yawRate = 0,
        .rollRate = 0,
        .pitchRateRaw = 0,
        .yawRateRaw = 0,
        .rollRateRaw = 0,
    },
    .x6001_acceleration = {
        .highestSubIndexSupported = 0x06,
        .accx = 0,
        .accy = 0,
        .accz = 0,
        .accXRaw = 0,
        .accyRaw = 0,
        .acczRaw = 0,
    },
    .x6002_IMU_Temperature = 0,
    .x6003_magnetometerPZ1 = {
        .highestSubIndexSupported = 0x03,
        .magx = 0,
        .magy = 0,
        .magz = 0,
    },
    .x6004_magnetometerPZ2 = {
        .highestSubIndexSupported = 0x03,
        .magx = 0,
        .magy = 0,
        .magz = 0,
    },
    .x6005_magnetometerMZ1 = {
        .highestSubIndexSupported = 0x03,
        .magx = 0,
        .magy = 0,
        .magz = 0,
    },
    .x6006_magnetometerMZ2 = {
        .highestSubIndexSupported = 0x03,
        .magx = 0,
        .magy = 0,
        .magz = 0,
    },
    .x6007_magnetorquer = {
        .highestSubIndexSupported = 0x06,
        .magnetorquerXPWM_DutyCycle = 0,
        .magnetorquerYPWM_DutyCycle = 0,
        .magnetorquerZPWM_DutyCycle = 0,
        .magnetorquerXCurrentUA = 0,
        .magnetorquerYCurrentUA = 0,
        .magnetorquerZCurrentUA = 0,
    },
};

OD_ATTR_PERSIST_COMM OD_PERSIST_COMM_t OD_PERSIST_COMM = {
    .x1005_COB_ID_SYNC_Message = 0x00000080,
    .x1006_communicationCyclePeriod = 0,
    .x1007_synchronousWindowLength = 0,
    .x1014_COB_ID_EMCY = 0x80,
    .x1015_inhibitTimeEMCY = 0,
    .x1016_consumerHeartbeatTime_sub0 = 0x08,
    .x1016_consumerHeartbeatTime = {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000},
    .x1017_producerHeartbeatTime = 1000,
    .x1019_synchronousCounterOverflowValue = 0,
    .x1200_SDO_ServerParameter = {
        .highestSubIndexSupported = 0x03,
        .COB_ID_ClientToServer = 0x80000000,
        .COB_ID_ServerToClient = 0x80000000,
        .nodeID_OfTheSDO_Client = 0x01,
    },
    .x1400_RPDO_CommunicationParameter = {
        .highestSubIndexSupported = 0x03,
        .COB_ID_UsedByRPDO = 0x80000200,
        .transmissionType = 254,
        .eventTimer = 0,
    },
    .x1401_RPDO_CommunicationParameter = {
        .highestSubIndexSupported = 0x03,
        .COB_ID_UsedByRPDO = 0x80000300,
        .transmissionType = 254,
        .eventTimer = 0,
    },
    .x1402_RPDO_CommunicationParameter = {
        .highestSubIndexSupported = 0x03,
        .COB_ID_UsedByRPDO = 0x80000400,
        .transmissionType = 254,
        .eventTimer = 0,
    },
    .x1403_RPDO_CommunicationParameter = {
        .highestSubIndexSupported = 0x03,
        .COB_ID_UsedByRPDO = 0x80000500,
        .transmissionType = 254,
        .eventTimer = 0,
    },
    .x1404_RPDO_CommunicationParameter = {
        .highestSubIndexSupported = 0x03,
        .COB_ID_UsedByRPDO = 0x80000200,
        .transmissionType = 254,
        .eventTimer = 0,
    },
    .x1405_RPDO_CommunicationParameter = {
        .highestSubIndexSupported = 0x03,
        .COB_ID_UsedByRPDO = 0x80000300,
        .transmissionType = 254,
        .eventTimer = 0,
    },
    .x1406_RPDO_CommunicationParameter = {
        .highestSubIndexSupported = 0x03,
        .COB_ID_UsedByRPDO = 0x80000400,
        .transmissionType = 254,
        .eventTimer = 0,
    },
    .x1407_RPDO_CommunicationParameter = {
        .highestSubIndexSupported = 0x03,
        .COB_ID_UsedByRPDO = 0x80000500,
        .transmissionType = 254,
        .eventTimer = 0,
    },
    .x1408_RPDO_CommunicationParameter = {
        .highestSubIndexSupported = 0x03,
        .COB_ID_UsedByRPDO = 0x80000200,
        .transmissionType = 254,
        .eventTimer = 0,
    },
    .x1409_RPDO_CommunicationParameter = {
        .highestSubIndexSupported = 0x03,
        .COB_ID_UsedByRPDO = 0x80000300,
        .transmissionType = 254,
        .eventTimer = 0,
    },
    .x140A_RPDO_CommunicationParameter = {
        .highestSubIndexSupported = 0x03,
        .COB_ID_UsedByRPDO = 0x80000400,
        .transmissionType = 254,
        .eventTimer = 0,
    },
    .x140B_RPDO_CommunicationParameter = {
        .highestSubIndexSupported = 0x03,
        .COB_ID_UsedByRPDO = 0x80000500,
        .transmissionType = 254,
        .eventTimer = 0,
    },
    .x140C_RPDO_CommunicationParameter = {
        .highestSubIndexSupported = 0x03,
        .COB_ID_UsedByRPDO = 0x80000200,
        .transmissionType = 254,
        .eventTimer = 0,
    },
    .x140D_RPDO_CommunicationParameter = {
        .highestSubIndexSupported = 0x03,
        .COB_ID_UsedByRPDO = 0x80000300,
        .transmissionType = 254,
        .eventTimer = 0,
    },
    .x140E_RPDO_CommunicationParameter = {
        .highestSubIndexSupported = 0x03,
        .COB_ID_UsedByRPDO = 0x80000400,
        .transmissionType = 254,
        .eventTimer = 0,
    },
    .x140F_RPDO_CommunicationParameter = {
        .highestSubIndexSupported = 0x03,
        .COB_ID_UsedByRPDO = 0x80000500,
        .transmissionType = 254,
        .eventTimer = 0,
    },
    .x1600_RPDO_MappingParameter = {
        .numberOfMappedApplicationObjectsInPDO = 0x08,
        .applicationObject_1 = 0x00000000,
        .applicationObject_2 = 0x00000000,
        .applicationObject_3 = 0x00000000,
        .applicationObject_4 = 0x00000000,
        .applicationObject_5 = 0x00000000,
        .applicationObject_6 = 0x00000000,
        .applicationObject_7 = 0x00000000,
        .applicationObject_8 = 0x00000000,
    },
    .x1601_RPDO_MappingParameter = {
        .numberOfMappedApplicationObjectsInPDO = 0x08,
        .applicationObject_1 = 0x00000000,
        .applicationObject_2 = 0x00000000,
        .applicationObject_3 = 0x00000000,
        .applicationObject_4 = 0x00000000,
        .applicationObject_5 = 0x00000000,
        .applicationObject_6 = 0x00000000,
        .applicationObject_7 = 0x00000000,
        .applicationObject_8 = 0x00000000,
    },
    .x1602_RPDO_MappingParameter = {
        .numberOfMappedApplicationObjectsInPDO = 0x08,
        .applicationObject_1 = 0x00000000,
        .applicationObject_2 = 0x00000000,
        .applicationObject_3 = 0x00000000,
        .applicationObject_4 = 0x00000000,
        .applicationObject_5 = 0x00000000,
        .applicationObject_6 = 0x00000000,
        .applicationObject_7 = 0x00000000,
        .applicationObject_8 = 0x00000000,
    },
    .x1603_RPDO_MappingParameter = {
        .numberOfMappedApplicationObjectsInPDO = 0x08,
        .applicationObject_1 = 0x00000000,
        .applicationObject_2 = 0x00000000,
        .applicationObject_3 = 0x00000000,
        .applicationObject_4 = 0x00000000,
        .applicationObject_5 = 0x00000000,
        .applicationObject_6 = 0x00000000,
        .applicationObject_7 = 0x00000000,
        .applicationObject_8 = 0x00000000,
    },
    .x1604_RPDO_MappingParameter = {
        .numberOfMappedApplicationObjectsInPDO = 0x08,
        .applicationObject_1 = 0x00000000,
        .applicationObject_2 = 0x00000000,
        .applicationObject_3 = 0x00000000,
        .applicationObject_4 = 0x00000000,
        .applicationObject_5 = 0x00000000,
        .applicationObject_6 = 0x00000000,
        .applicationObject_7 = 0x00000000,
        .applicationObject_8 = 0x00000000,
    },
    .x1605_RPDO_MappingParameter = {
        .numberOfMappedApplicationObjectsInPDO = 0x08,
        .applicationObject_1 = 0x00000000,
        .applicationObject_2 = 0x00000000,
        .applicationObject_3 = 0x00000000,
        .applicationObject_4 = 0x00000000,
        .applicationObject_5 = 0x00000000,
        .applicationObject_6 = 0x00000000,
        .applicationObject_7 = 0x00000000,
        .applicationObject_8 = 0x00000000,
    },
    .x1606_RPDO_MappingParameter = {
        .numberOfMappedApplicationObjectsInPDO = 0x08,
        .applicationObject_1 = 0x00000000,
        .applicationObject_2 = 0x00000000,
        .applicationObject_3 = 0x00000000,
        .applicationObject_4 = 0x00000000,
        .applicationObject_5 = 0x00000000,
        .applicationObject_6 = 0x00000000,
        .applicationObject_7 = 0x00000000,
        .applicationObject_8 = 0x00000000,
    },
    .x1607_RPDO_MappingParameter = {
        .numberOfMappedApplicationObjectsInPDO = 0x08,
        .applicationObject_1 = 0x00000000,
        .applicationObject_2 = 0x00000000,
        .applicationObject_3 = 0x00000000,
        .applicationObject_4 = 0x00000000,
        .applicationObject_5 = 0x00000000,
        .applicationObject_6 = 0x00000000,
        .applicationObject_7 = 0x00000000,
        .applicationObject_8 = 0x00000000,
    },
    .x1608_RPDO_MappingParameter = {
        .numberOfMappedApplicationObjectsInPDO = 0x08,
        .applicationObject_1 = 0x00000000,
        .applicationObject_2 = 0x00000000,
        .applicationObject_3 = 0x00000000,
        .applicationObject_4 = 0x00000000,
        .applicationObject_5 = 0x00000000,
        .applicationObject_6 = 0x00000000,
        .applicationObject_7 = 0x00000000,
        .applicationObject_8 = 0x00000000,
    },
    .x1609_RPDO_MappingParameter = {
        .numberOfMappedApplicationObjectsInPDO = 0x08,
        .applicationObject_1 = 0x00000000,
        .applicationObject_2 = 0x00000000,
        .applicationObject_3 = 0x00000000,
        .applicationObject_4 = 0x00000000,
        .applicationObject_5 = 0x00000000,
        .applicationObject_6 = 0x00000000,
        .applicationObject_7 = 0x00000000,
        .applicationObject_8 = 0x00000000,
    },
    .x160A_RPDO_MappingParameter = {
        .numberOfMappedApplicationObjectsInPDO = 0x08,
        .applicationObject_1 = 0x00000000,
        .applicationObject_2 = 0x00000000,
        .applicationObject_3 = 0x00000000,
        .applicationObject_4 = 0x00000000,
        .applicationObject_5 = 0x00000000,
        .applicationObject_6 = 0x00000000,
        .applicationObject_7 = 0x00000000,
        .applicationObject_8 = 0x00000000,
    },
    .x160B_RPDO_MappingParameter = {
        .numberOfMappedApplicationObjectsInPDO = 0x08,
        .applicationObject_1 = 0x00000000,
        .applicationObject_2 = 0x00000000,
        .applicationObject_3 = 0x00000000,
        .applicationObject_4 = 0x00000000,
        .applicationObject_5 = 0x00000000,
        .applicationObject_6 = 0x00000000,
        .applicationObject_7 = 0x00000000,
        .applicationObject_8 = 0x00000000,
    },
    .x160C_RPDO_MappingParameter = {
        .numberOfMappedApplicationObjectsInPDO = 0x08,
        .applicationObject_1 = 0x00000000,
        .applicationObject_2 = 0x00000000,
        .applicationObject_3 = 0x00000000,
        .applicationObject_4 = 0x00000000,
        .applicationObject_5 = 0x00000000,
        .applicationObject_6 = 0x00000000,
        .applicationObject_7 = 0x00000000,
        .applicationObject_8 = 0x00000000,
    },
    .x160D_RPDO_MappingParameter = {
        .numberOfMappedApplicationObjectsInPDO = 0x08,
        .applicationObject_1 = 0x00000000,
        .applicationObject_2 = 0x00000000,
        .applicationObject_3 = 0x00000000,
        .applicationObject_4 = 0x00000000,
        .applicationObject_5 = 0x00000000,
        .applicationObject_6 = 0x00000000,
        .applicationObject_7 = 0x00000000,
        .applicationObject_8 = 0x00000000,
    },
    .x160E_RPDO_MappingParameter = {
        .numberOfMappedApplicationObjectsInPDO = 0x08,
        .applicationObject_1 = 0x00000000,
        .applicationObject_2 = 0x00000000,
        .applicationObject_3 = 0x00000000,
        .applicationObject_4 = 0x00000000,
        .applicationObject_5 = 0x00000000,
        .applicationObject_6 = 0x00000000,
        .applicationObject_7 = 0x00000000,
        .applicationObject_8 = 0x00000000,
    },
    .x160F_RPDO_MappingParameter = {
        .numberOfMappedApplicationObjectsInPDO = 0x08,
        .applicationObject_1 = 0x00000000,
        .applicationObject_2 = 0x00000000,
        .applicationObject_3 = 0x00000000,
        .applicationObject_4 = 0x00000000,
        .applicationObject_5 = 0x00000000,
        .applicationObject_6 = 0x00000000,
        .applicationObject_7 = 0x00000000,
        .applicationObject_8 = 0x00000000,
    },
    .x1800_TPDO_CommunicationParameter = {
        .highestSubIndexSupported = 0x06,
        .COB_ID_UsedByTPDO = 0x40000180,
        .transmissionType = 254,
        .inhibitTime = 0,
        .compatibilityEntry = 0,
        .eventTimer = 10000,
        .SYNC_StartValue = 0,
    },
    .x1801_TPDO_CommunicationParameter = {
        .highestSubIndexSupported = 0x06,
        .COB_ID_UsedByTPDO = 0x40000280,
        .transmissionType = 254,
        .inhibitTime = 0,
        .compatibilityEntry = 0,
        .eventTimer = 10000,
        .SYNC_StartValue = 0,
    },
    .x1802_TPDO_CommunicationParameter = {
        .highestSubIndexSupported = 0x06,
        .COB_ID_UsedByTPDO = 0x40000380,
        .transmissionType = 254,
        .inhibitTime = 0,
        .compatibilityEntry = 0,
        .eventTimer = 10000,
        .SYNC_StartValue = 0,
    },
    .x1803_TPDO_CommunicationParameter = {
        .highestSubIndexSupported = 0x06,
        .COB_ID_UsedByTPDO = 0x40000480,
        .transmissionType = 254,
        .inhibitTime = 0,
        .compatibilityEntry = 0,
        .eventTimer = 0,
        .SYNC_StartValue = 0,
    },
    .x1804_TPDO_CommunicationParameter = {
        .highestSubIndexSupported = 0x06,
        .COB_ID_UsedByTPDO = 0x40000180,
        .transmissionType = 254,
        .inhibitTime = 0,
        .compatibilityEntry = 0,
        .eventTimer = 0,
        .SYNC_StartValue = 0,
    },
    .x1805_TPDO_CommunicationParameter = {
        .highestSubIndexSupported = 0x06,
        .COB_ID_UsedByTPDO = 0x40000280,
        .transmissionType = 254,
        .inhibitTime = 0,
        .compatibilityEntry = 0,
        .eventTimer = 0,
        .SYNC_StartValue = 0,
    },
    .x1806_TPDO_CommunicationParameter = {
        .highestSubIndexSupported = 0x06,
        .COB_ID_UsedByTPDO = 0xC0000380,
        .transmissionType = 254,
        .inhibitTime = 0,
        .compatibilityEntry = 0,
        .eventTimer = 0,
        .SYNC_StartValue = 0,
    },
    .x1807_TPDO_CommunicationParameter = {
        .highestSubIndexSupported = 0x06,
        .COB_ID_UsedByTPDO = 0xC0000480,
        .transmissionType = 254,
        .inhibitTime = 0,
        .compatibilityEntry = 0,
        .eventTimer = 0,
        .SYNC_StartValue = 0,
    },
    .x1808_TPDO_CommunicationParameter = {
        .highestSubIndexSupported = 0x06,
        .COB_ID_UsedByTPDO = 0xC0000180,
        .transmissionType = 254,
        .inhibitTime = 0,
        .compatibilityEntry = 0,
        .eventTimer = 0,
        .SYNC_StartValue = 0,
    },
    .x1809_TPDO_CommunicationParameter = {
        .highestSubIndexSupported = 0x06,
        .COB_ID_UsedByTPDO = 0xC0000280,
        .transmissionType = 254,
        .inhibitTime = 0,
        .compatibilityEntry = 0,
        .eventTimer = 0,
        .SYNC_StartValue = 0,
    },
    .x180A_TPDO_CommunicationParameter = {
        .highestSubIndexSupported = 0x06,
        .COB_ID_UsedByTPDO = 0xC0000380,
        .transmissionType = 254,
        .inhibitTime = 0,
        .compatibilityEntry = 0,
        .eventTimer = 0,
        .SYNC_StartValue = 0,
    },
    .x180B_TPDO_CommunicationParameter = {
        .highestSubIndexSupported = 0x06,
        .COB_ID_UsedByTPDO = 0xC0000480,
        .transmissionType = 254,
        .inhibitTime = 0,
        .compatibilityEntry = 0,
        .eventTimer = 0,
        .SYNC_StartValue = 0,
    },
    .x180C_TPDO_CommunicationParameter = {
        .highestSubIndexSupported = 0x06,
        .COB_ID_UsedByTPDO = 0xC0000180,
        .transmissionType = 254,
        .inhibitTime = 0,
        .compatibilityEntry = 0,
        .eventTimer = 0,
        .SYNC_StartValue = 0,
    },
    .x180D_TPDO_CommunicationParameter = {
        .highestSubIndexSupported = 0x06,
        .COB_ID_UsedByTPDO = 0xC0000280,
        .transmissionType = 254,
        .inhibitTime = 0,
        .compatibilityEntry = 0,
        .eventTimer = 0,
        .SYNC_StartValue = 0,
    },
    .x180E_TPDO_CommunicationParameter = {
        .highestSubIndexSupported = 0x06,
        .COB_ID_UsedByTPDO = 0xC0000380,
        .transmissionType = 254,
        .inhibitTime = 0,
        .compatibilityEntry = 0,
        .eventTimer = 0,
        .SYNC_StartValue = 0,
    },
    .x180F_TPDO_CommunicationParameter = {
        .highestSubIndexSupported = 0x06,
        .COB_ID_UsedByTPDO = 0xC0000480,
        .transmissionType = 254,
        .inhibitTime = 0,
        .compatibilityEntry = 0,
        .eventTimer = 0,
        .SYNC_StartValue = 0,
    },
    .x1A00_TPDO_MappingParameter = {
        .numberOfMappedApplicationObjectsInPDO = 0x08,
        .applicationObject_1 = 0x60000110,
        .applicationObject_2 = 0x60000210,
        .applicationObject_3 = 0x60000310,
        .applicationObject_4 = 0x00000000,
        .applicationObject_5 = 0x00000000,
        .applicationObject_6 = 0x00000000,
        .applicationObject_7 = 0x00000000,
        .applicationObject_8 = 0x00000000,
    },
    .x1A01_TPDO_MappingParameter = {
        .numberOfMappedApplicationObjectsInPDO = 0x08,
        .applicationObject_1 = 0x60010110,
        .applicationObject_2 = 0x60010210,
        .applicationObject_3 = 0x60010310,
        .applicationObject_4 = 0x00000000,
        .applicationObject_5 = 0x00000000,
        .applicationObject_6 = 0x00000000,
        .applicationObject_7 = 0x00000000,
        .applicationObject_8 = 0x00000000,
    },
    .x1A02_TPDO_MappingParameter = {
        .numberOfMappedApplicationObjectsInPDO = 0x08,
        .applicationObject_1 = 0x60020008,
        .applicationObject_2 = 0x00000000,
        .applicationObject_3 = 0x00000000,
        .applicationObject_4 = 0x00000000,
        .applicationObject_5 = 0x00000000,
        .applicationObject_6 = 0x00000000,
        .applicationObject_7 = 0x00000000,
        .applicationObject_8 = 0x00000000,
    },
    .x1A03_TPDO_MappingParameter = {
        .numberOfMappedApplicationObjectsInPDO = 0x08,
        .applicationObject_1 = 0x60030110,
        .applicationObject_2 = 0x60030210,
        .applicationObject_3 = 0x60030310,
        .applicationObject_4 = 0x60040110,
        .applicationObject_5 = 0x00000000,
        .applicationObject_6 = 0x00000000,
        .applicationObject_7 = 0x00000000,
        .applicationObject_8 = 0x00000000,
    },
    .x1A04_TPDO_MappingParameter = {
        .numberOfMappedApplicationObjectsInPDO = 0x08,
        .applicationObject_1 = 0x60040210,
        .applicationObject_2 = 0x60040310,
        .applicationObject_3 = 0x60050110,
        .applicationObject_4 = 0x60050210,
        .applicationObject_5 = 0x00000000,
        .applicationObject_6 = 0x00000000,
        .applicationObject_7 = 0x00000000,
        .applicationObject_8 = 0x00000000,
    },
    .x1A05_TPDO_MappingParameter = {
        .numberOfMappedApplicationObjectsInPDO = 0x08,
        .applicationObject_1 = 0x60050310,
        .applicationObject_2 = 0x60060110,
        .applicationObject_3 = 0x60060210,
        .applicationObject_4 = 0x60060310,
        .applicationObject_5 = 0x00000000,
        .applicationObject_6 = 0x00000000,
        .applicationObject_7 = 0x00000000,
        .applicationObject_8 = 0x00000000,
    },
    .x1A06_TPDO_MappingParameter = {
        .numberOfMappedApplicationObjectsInPDO = 0x08,
        .applicationObject_1 = 0x00000000,
        .applicationObject_2 = 0x00000000,
        .applicationObject_3 = 0x00000000,
        .applicationObject_4 = 0x00000000,
        .applicationObject_5 = 0x00000000,
        .applicationObject_6 = 0x00000000,
        .applicationObject_7 = 0x00000000,
        .applicationObject_8 = 0x00000000,
    },
    .x1A07_TPDO_MappingParameter = {
        .numberOfMappedApplicationObjectsInPDO = 0x08,
        .applicationObject_1 = 0x00000000,
        .applicationObject_2 = 0x00000000,
        .applicationObject_3 = 0x00000000,
        .applicationObject_4 = 0x00000000,
        .applicationObject_5 = 0x00000000,
        .applicationObject_6 = 0x00000000,
        .applicationObject_7 = 0x00000000,
        .applicationObject_8 = 0x00000000,
    },
    .x1A08_TPDO_MappingParameter = {
        .numberOfMappedApplicationObjectsInPDO = 0x08,
        .applicationObject_1 = 0x00000000,
        .applicationObject_2 = 0x00000000,
        .applicationObject_3 = 0x00000000,
        .applicationObject_4 = 0x00000000,
        .applicationObject_5 = 0x00000000,
        .applicationObject_6 = 0x00000000,
        .applicationObject_7 = 0x00000000,
        .applicationObject_8 = 0x00000000,
    },
    .x1A09_TPDO_MappingParameter = {
        .numberOfMappedApplicationObjectsInPDO = 0x08,
        .applicationObject_1 = 0x00000000,
        .applicationObject_2 = 0x00000000,
        .applicationObject_3 = 0x00000000,
        .applicationObject_4 = 0x00000000,
        .applicationObject_5 = 0x00000000,
        .applicationObject_6 = 0x00000000,
        .applicationObject_7 = 0x00000000,
        .applicationObject_8 = 0x00000000,
    },
    .x1A0A_TPDO_MappingParameter = {
        .numberOfMappedApplicationObjectsInPDO = 0x08,
        .applicationObject_1 = 0x00000000,
        .applicationObject_2 = 0x00000000,
        .applicationObject_3 = 0x00000000,
        .applicationObject_4 = 0x00000000,
        .applicationObject_5 = 0x00000000,
        .applicationObject_6 = 0x00000000,
        .applicationObject_7 = 0x00000000,
        .applicationObject_8 = 0x00000000,
    },
    .x1A0B_TPDO_MappingParameter = {
        .numberOfMappedApplicationObjectsInPDO = 0x08,
        .applicationObject_1 = 0x00000000,
        .applicationObject_2 = 0x00000000,
        .applicationObject_3 = 0x00000000,
        .applicationObject_4 = 0x00000000,
        .applicationObject_5 = 0x00000000,
        .applicationObject_6 = 0x00000000,
        .applicationObject_7 = 0x00000000,
        .applicationObject_8 = 0x00000000,
    },
    .x1A0C_TPDO_MappingParameter = {
        .numberOfMappedApplicationObjectsInPDO = 0x08,
        .applicationObject_1 = 0x00000000,
        .applicationObject_2 = 0x00000000,
        .applicationObject_3 = 0x00000000,
        .applicationObject_4 = 0x00000000,
        .applicationObject_5 = 0x00000000,
        .applicationObject_6 = 0x00000000,
        .applicationObject_7 = 0x00000000,
        .applicationObject_8 = 0x00000000,
    },
    .x1A0D_TPDO_MappingParameter = {
        .numberOfMappedApplicationObjectsInPDO = 0x08,
        .applicationObject_1 = 0x00000000,
        .applicationObject_2 = 0x00000000,
        .applicationObject_3 = 0x00000000,
        .applicationObject_4 = 0x00000000,
        .applicationObject_5 = 0x00000000,
        .applicationObject_6 = 0x00000000,
        .applicationObject_7 = 0x00000000,
        .applicationObject_8 = 0x00000000,
    },
    .x1A0E_TPDO_MappingParameter = {
        .numberOfMappedApplicationObjectsInPDO = 0x08,
        .applicationObject_1 = 0x00000000,
        .applicationObject_2 = 0x00000000,
        .applicationObject_3 = 0x00000000,
        .applicationObject_4 = 0x00000000,
        .applicationObject_5 = 0x00000000,
        .applicationObject_6 = 0x00000000,
        .applicationObject_7 = 0x00000000,
        .applicationObject_8 = 0x00000000,
    },
    .x1A0F_TPDO_MappingParameter = {
        .numberOfMappedApplicationObjectsInPDO = 0x08,
        .applicationObject_1 = 0x00000000,
        .applicationObject_2 = 0x00000000,
        .applicationObject_3 = 0x00000000,
        .applicationObject_4 = 0x00000000,
        .applicationObject_5 = 0x00000000,
        .applicationObject_6 = 0x00000000,
        .applicationObject_7 = 0x00000000,
        .applicationObject_8 = 0x00000000,
    },
    .x1F80_nmtstartup = 0x00000008,
};

OD_ATTR_PERSIST_MFR OD_PERSIST_MFR_t OD_PERSIST_MFR = {
    .x2000_BUS_Management = {
        .highestSubIndexSupported = 0x04,
        .bdefault = 0,
        .ttoggle = 0,
        .ntoggle = 0,
        .ctoggle = 0,
    },
};

typedef struct {
    OD_obj_var_t o_1000_deviceType;
    OD_obj_var_t o_1001_errorRegister;
    OD_obj_var_t o_1002_manufacturerStatusRegister;
    OD_obj_array_t o_1003_preDefinedErrorField;
    OD_obj_var_t o_1005_COB_ID_SYNC_Message;
    OD_obj_var_t o_1006_communicationCyclePeriod;
    OD_obj_var_t o_1007_synchronousWindowLength;
    OD_obj_var_t o_1008_manufacturerDeviceName;
    OD_obj_var_t o_1009_manufacturerHardwareVersion;
    OD_obj_var_t o_100A_manufacturerSoftwareVersion;
    OD_obj_array_t o_1010_storeParameters;
    OD_obj_array_t o_1011_restoreDefaultParameters;
    OD_obj_var_t o_1014_COB_ID_EMCY;
    OD_obj_var_t o_1015_inhibitTimeEMCY;
    OD_obj_array_t o_1016_consumerHeartbeatTime;
    OD_obj_var_t o_1017_producerHeartbeatTime;
    OD_obj_record_t o_1018_identity[5];
    OD_obj_var_t o_1019_synchronousCounterOverflowValue;
    OD_obj_array_t o_1029_errorBehavior;
    OD_obj_record_t o_1200_SDO_ServerParameter[4];
    OD_obj_record_t o_1400_RPDO_CommunicationParameter[4];
    OD_obj_record_t o_1401_RPDO_CommunicationParameter[4];
    OD_obj_record_t o_1402_RPDO_CommunicationParameter[4];
    OD_obj_record_t o_1403_RPDO_CommunicationParameter[4];
    OD_obj_record_t o_1404_RPDO_CommunicationParameter[4];
    OD_obj_record_t o_1405_RPDO_CommunicationParameter[4];
    OD_obj_record_t o_1406_RPDO_CommunicationParameter[4];
    OD_obj_record_t o_1407_RPDO_CommunicationParameter[4];
    OD_obj_record_t o_1408_RPDO_CommunicationParameter[4];
    OD_obj_record_t o_1409_RPDO_CommunicationParameter[4];
    OD_obj_record_t o_140A_RPDO_CommunicationParameter[4];
    OD_obj_record_t o_140B_RPDO_CommunicationParameter[4];
    OD_obj_record_t o_140C_RPDO_CommunicationParameter[4];
    OD_obj_record_t o_140D_RPDO_CommunicationParameter[4];
    OD_obj_record_t o_140E_RPDO_CommunicationParameter[4];
    OD_obj_record_t o_140F_RPDO_CommunicationParameter[4];
    OD_obj_record_t o_1600_RPDO_MappingParameter[9];
    OD_obj_record_t o_1601_RPDO_MappingParameter[9];
    OD_obj_record_t o_1602_RPDO_MappingParameter[9];
    OD_obj_record_t o_1603_RPDO_MappingParameter[9];
    OD_obj_record_t o_1604_RPDO_MappingParameter[9];
    OD_obj_record_t o_1605_RPDO_MappingParameter[9];
    OD_obj_record_t o_1606_RPDO_MappingParameter[9];
    OD_obj_record_t o_1607_RPDO_MappingParameter[9];
    OD_obj_record_t o_1608_RPDO_MappingParameter[9];
    OD_obj_record_t o_1609_RPDO_MappingParameter[9];
    OD_obj_record_t o_160A_RPDO_MappingParameter[9];
    OD_obj_record_t o_160B_RPDO_MappingParameter[9];
    OD_obj_record_t o_160C_RPDO_MappingParameter[9];
    OD_obj_record_t o_160D_RPDO_MappingParameter[9];
    OD_obj_record_t o_160E_RPDO_MappingParameter[9];
    OD_obj_record_t o_160F_RPDO_MappingParameter[9];
    OD_obj_record_t o_1800_TPDO_CommunicationParameter[7];
    OD_obj_record_t o_1801_TPDO_CommunicationParameter[7];
    OD_obj_record_t o_1802_TPDO_CommunicationParameter[7];
    OD_obj_record_t o_1803_TPDO_CommunicationParameter[7];
    OD_obj_record_t o_1804_TPDO_CommunicationParameter[7];
    OD_obj_record_t o_1805_TPDO_CommunicationParameter[7];
    OD_obj_record_t o_1806_TPDO_CommunicationParameter[7];
    OD_obj_record_t o_1807_TPDO_CommunicationParameter[7];
    OD_obj_record_t o_1808_TPDO_CommunicationParameter[7];
    OD_obj_record_t o_1809_TPDO_CommunicationParameter[7];
    OD_obj_record_t o_180A_TPDO_CommunicationParameter[7];
    OD_obj_record_t o_180B_TPDO_CommunicationParameter[7];
    OD_obj_record_t o_180C_TPDO_CommunicationParameter[7];
    OD_obj_record_t o_180D_TPDO_CommunicationParameter[7];
    OD_obj_record_t o_180E_TPDO_CommunicationParameter[7];
    OD_obj_record_t o_180F_TPDO_CommunicationParameter[7];
    OD_obj_record_t o_1A00_TPDO_MappingParameter[9];
    OD_obj_record_t o_1A01_TPDO_MappingParameter[9];
    OD_obj_record_t o_1A02_TPDO_MappingParameter[9];
    OD_obj_record_t o_1A03_TPDO_MappingParameter[9];
    OD_obj_record_t o_1A04_TPDO_MappingParameter[9];
    OD_obj_record_t o_1A05_TPDO_MappingParameter[9];
    OD_obj_record_t o_1A06_TPDO_MappingParameter[9];
    OD_obj_record_t o_1A07_TPDO_MappingParameter[9];
    OD_obj_record_t o_1A08_TPDO_MappingParameter[9];
    OD_obj_record_t o_1A09_TPDO_MappingParameter[9];
    OD_obj_record_t o_1A0A_TPDO_MappingParameter[9];
    OD_obj_record_t o_1A0B_TPDO_MappingParameter[9];
    OD_obj_record_t o_1A0C_TPDO_MappingParameter[9];
    OD_obj_record_t o_1A0D_TPDO_MappingParameter[9];
    OD_obj_record_t o_1A0E_TPDO_MappingParameter[9];
    OD_obj_record_t o_1A0F_TPDO_MappingParameter[9];
    OD_obj_var_t o_1F80_nmtstartup;
    OD_obj_record_t o_2000_BUS_Management[5];
    OD_obj_var_t o_2010_SCET;
    OD_obj_var_t o_2011_UTC;
    OD_obj_array_t o_2020_MCU_UniqueDeviceID;
    OD_obj_record_t o_2021_MCU_Calibration[4];
    OD_obj_record_t o_2022_MCU_Sensors[9];
    OD_obj_var_t o_2100_errorStatusBits;
    OD_obj_record_t o_6000_gyroscope[7];
    OD_obj_record_t o_6001_acceleration[7];
    OD_obj_var_t o_6002_IMU_Temperature;
    OD_obj_record_t o_6003_magnetometerPZ1[4];
    OD_obj_record_t o_6004_magnetometerPZ2[4];
    OD_obj_record_t o_6005_magnetometerMZ1[4];
    OD_obj_record_t o_6006_magnetometerMZ2[4];
    OD_obj_record_t o_6007_magnetorquer[7];
} ODObjs_t;

static CO_PROGMEM ODObjs_t ODObjs = {
    .o_1000_deviceType = {
        .dataOrig = &OD_ROM.x1000_deviceType,
        .attribute = ODA_SDO_R | ODA_MB,
        .dataLength = 4
    },
    .o_1001_errorRegister = {
        .dataOrig = &OD_RAM.x1001_errorRegister,
        .attribute = ODA_SDO_R | ODA_TPDO,
        .dataLength = 1
    },
    .o_1002_manufacturerStatusRegister = {
        .dataOrig = &OD_RAM.x1002_manufacturerStatusRegister,
        .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
        .dataLength = 4
    },
    .o_1003_preDefinedErrorField = {
        .dataOrig0 = &OD_RAM.x1003_preDefinedErrorField_sub0,
        .dataOrig = &OD_RAM.x1003_preDefinedErrorField[0],
        .attribute0 = ODA_SDO_R,
        .attribute = ODA_SDO_R | ODA_MB,
        .dataElementLength = 4,
        .dataElementSizeof = sizeof(uint32_t)
    },
    .o_1005_COB_ID_SYNC_Message = {
        .dataOrig = &OD_PERSIST_COMM.x1005_COB_ID_SYNC_Message,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataLength = 4
    },
    .o_1006_communicationCyclePeriod = {
        .dataOrig = &OD_PERSIST_COMM.x1006_communicationCyclePeriod,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataLength = 4
    },
    .o_1007_synchronousWindowLength = {
        .dataOrig = &OD_PERSIST_COMM.x1007_synchronousWindowLength,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataLength = 4
    },
    .o_1008_manufacturerDeviceName = {
        .dataOrig = &OD_ROM.x1008_manufacturerDeviceName[0],
        .attribute = ODA_SDO_R | ODA_STR,
        .dataLength = 11
    },
    .o_1009_manufacturerHardwareVersion = {
        .dataOrig = &OD_ROM.x1009_manufacturerHardwareVersion[0],
        .attribute = ODA_SDO_R | ODA_STR,
        .dataLength = 3
    },
    .o_100A_manufacturerSoftwareVersion = {
        .dataOrig = &OD_ROM.x100A_manufacturerSoftwareVersion[0],
        .attribute = ODA_SDO_R | ODA_STR,
        .dataLength = 5
    },
    .o_1010_storeParameters = {
        .dataOrig0 = &OD_RAM.x1010_storeParameters_sub0,
        .dataOrig = &OD_RAM.x1010_storeParameters[0],
        .attribute0 = ODA_SDO_R,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataElementLength = 4,
        .dataElementSizeof = sizeof(uint32_t)
    },
    .o_1011_restoreDefaultParameters = {
        .dataOrig0 = &OD_RAM.x1011_restoreDefaultParameters_sub0,
        .dataOrig = &OD_RAM.x1011_restoreDefaultParameters[0],
        .attribute0 = ODA_SDO_R,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataElementLength = 4,
        .dataElementSizeof = sizeof(uint32_t)
    },
    .o_1014_COB_ID_EMCY = {
        .dataOrig = &OD_PERSIST_COMM.x1014_COB_ID_EMCY,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataLength = 4
    },
    .o_1015_inhibitTimeEMCY = {
        .dataOrig = &OD_PERSIST_COMM.x1015_inhibitTimeEMCY,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataLength = 2
    },
    .o_1016_consumerHeartbeatTime = {
        .dataOrig0 = &OD_PERSIST_COMM.x1016_consumerHeartbeatTime_sub0,
        .dataOrig = &OD_PERSIST_COMM.x1016_consumerHeartbeatTime[0],
        .attribute0 = ODA_SDO_R,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataElementLength = 4,
        .dataElementSizeof = sizeof(uint32_t)
    },
    .o_1017_producerHeartbeatTime = {
        .dataOrig = &OD_PERSIST_COMM.x1017_producerHeartbeatTime,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataLength = 2
    },
    .o_1018_identity = {
        {
            .dataOrig = &OD_ROM.x1018_identity.highestSubIndexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_ROM.x1018_identity.vendorID,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_ROM.x1018_identity.productCode,
            .subIndex = 2,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_ROM.x1018_identity.revisionNumber,
            .subIndex = 3,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_ROM.x1018_identity.serialNumber,
            .subIndex = 4,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
    },
    .o_1019_synchronousCounterOverflowValue = {
        .dataOrig = &OD_PERSIST_COMM.x1019_synchronousCounterOverflowValue,
        .attribute = ODA_SDO_RW,
        .dataLength = 1
    },
    .o_1029_errorBehavior = {
        .dataOrig0 = &OD_ROM.x1029_errorBehavior_sub0,
        .dataOrig = &OD_ROM.x1029_errorBehavior[0],
        .attribute0 = ODA_SDO_R,
        .attribute = ODA_SDO_RW,
        .dataElementLength = 1,
        .dataElementSizeof = sizeof(uint8_t)
    },
    .o_1200_SDO_ServerParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1200_SDO_ServerParameter.highestSubIndexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1200_SDO_ServerParameter.COB_ID_ClientToServer,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_TRPDO | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1200_SDO_ServerParameter.COB_ID_ServerToClient,
            .subIndex = 2,
            .attribute = ODA_SDO_RW | ODA_TRPDO | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1200_SDO_ServerParameter.nodeID_OfTheSDO_Client,
            .subIndex = 3,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
    },
    .o_1400_RPDO_CommunicationParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1400_RPDO_CommunicationParameter.highestSubIndexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1400_RPDO_CommunicationParameter.COB_ID_UsedByRPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1400_RPDO_CommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1400_RPDO_CommunicationParameter.eventTimer,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
    },
    .o_1401_RPDO_CommunicationParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1401_RPDO_CommunicationParameter.highestSubIndexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1401_RPDO_CommunicationParameter.COB_ID_UsedByRPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1401_RPDO_CommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1401_RPDO_CommunicationParameter.eventTimer,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
    },
    .o_1402_RPDO_CommunicationParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1402_RPDO_CommunicationParameter.highestSubIndexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1402_RPDO_CommunicationParameter.COB_ID_UsedByRPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1402_RPDO_CommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1402_RPDO_CommunicationParameter.eventTimer,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
    },
    .o_1403_RPDO_CommunicationParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1403_RPDO_CommunicationParameter.highestSubIndexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1403_RPDO_CommunicationParameter.COB_ID_UsedByRPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1403_RPDO_CommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1403_RPDO_CommunicationParameter.eventTimer,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
    },
    .o_1404_RPDO_CommunicationParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1404_RPDO_CommunicationParameter.highestSubIndexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1404_RPDO_CommunicationParameter.COB_ID_UsedByRPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1404_RPDO_CommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1404_RPDO_CommunicationParameter.eventTimer,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
    },
    .o_1405_RPDO_CommunicationParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1405_RPDO_CommunicationParameter.highestSubIndexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1405_RPDO_CommunicationParameter.COB_ID_UsedByRPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1405_RPDO_CommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1405_RPDO_CommunicationParameter.eventTimer,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
    },
    .o_1406_RPDO_CommunicationParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1406_RPDO_CommunicationParameter.highestSubIndexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1406_RPDO_CommunicationParameter.COB_ID_UsedByRPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1406_RPDO_CommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1406_RPDO_CommunicationParameter.eventTimer,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
    },
    .o_1407_RPDO_CommunicationParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1407_RPDO_CommunicationParameter.highestSubIndexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1407_RPDO_CommunicationParameter.COB_ID_UsedByRPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1407_RPDO_CommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1407_RPDO_CommunicationParameter.eventTimer,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
    },
    .o_1408_RPDO_CommunicationParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1408_RPDO_CommunicationParameter.highestSubIndexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1408_RPDO_CommunicationParameter.COB_ID_UsedByRPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1408_RPDO_CommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1408_RPDO_CommunicationParameter.eventTimer,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
    },
    .o_1409_RPDO_CommunicationParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1409_RPDO_CommunicationParameter.highestSubIndexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1409_RPDO_CommunicationParameter.COB_ID_UsedByRPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1409_RPDO_CommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1409_RPDO_CommunicationParameter.eventTimer,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
    },
    .o_140A_RPDO_CommunicationParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x140A_RPDO_CommunicationParameter.highestSubIndexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x140A_RPDO_CommunicationParameter.COB_ID_UsedByRPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x140A_RPDO_CommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x140A_RPDO_CommunicationParameter.eventTimer,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
    },
    .o_140B_RPDO_CommunicationParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x140B_RPDO_CommunicationParameter.highestSubIndexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x140B_RPDO_CommunicationParameter.COB_ID_UsedByRPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x140B_RPDO_CommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x140B_RPDO_CommunicationParameter.eventTimer,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
    },
    .o_140C_RPDO_CommunicationParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x140C_RPDO_CommunicationParameter.highestSubIndexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x140C_RPDO_CommunicationParameter.COB_ID_UsedByRPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x140C_RPDO_CommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x140C_RPDO_CommunicationParameter.eventTimer,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
    },
    .o_140D_RPDO_CommunicationParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x140D_RPDO_CommunicationParameter.highestSubIndexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x140D_RPDO_CommunicationParameter.COB_ID_UsedByRPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x140D_RPDO_CommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x140D_RPDO_CommunicationParameter.eventTimer,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
    },
    .o_140E_RPDO_CommunicationParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x140E_RPDO_CommunicationParameter.highestSubIndexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x140E_RPDO_CommunicationParameter.COB_ID_UsedByRPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x140E_RPDO_CommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x140E_RPDO_CommunicationParameter.eventTimer,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
    },
    .o_140F_RPDO_CommunicationParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x140F_RPDO_CommunicationParameter.highestSubIndexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x140F_RPDO_CommunicationParameter.COB_ID_UsedByRPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x140F_RPDO_CommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x140F_RPDO_CommunicationParameter.eventTimer,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
    },
    .o_1600_RPDO_MappingParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1600_RPDO_MappingParameter.numberOfMappedApplicationObjectsInPDO,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1600_RPDO_MappingParameter.applicationObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1600_RPDO_MappingParameter.applicationObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1600_RPDO_MappingParameter.applicationObject_3,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1600_RPDO_MappingParameter.applicationObject_4,
            .subIndex = 4,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1600_RPDO_MappingParameter.applicationObject_5,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1600_RPDO_MappingParameter.applicationObject_6,
            .subIndex = 6,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1600_RPDO_MappingParameter.applicationObject_7,
            .subIndex = 7,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1600_RPDO_MappingParameter.applicationObject_8,
            .subIndex = 8,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
    },
    .o_1601_RPDO_MappingParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1601_RPDO_MappingParameter.numberOfMappedApplicationObjectsInPDO,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1601_RPDO_MappingParameter.applicationObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1601_RPDO_MappingParameter.applicationObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1601_RPDO_MappingParameter.applicationObject_3,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1601_RPDO_MappingParameter.applicationObject_4,
            .subIndex = 4,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1601_RPDO_MappingParameter.applicationObject_5,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1601_RPDO_MappingParameter.applicationObject_6,
            .subIndex = 6,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1601_RPDO_MappingParameter.applicationObject_7,
            .subIndex = 7,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1601_RPDO_MappingParameter.applicationObject_8,
            .subIndex = 8,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
    },
    .o_1602_RPDO_MappingParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1602_RPDO_MappingParameter.numberOfMappedApplicationObjectsInPDO,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1602_RPDO_MappingParameter.applicationObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1602_RPDO_MappingParameter.applicationObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1602_RPDO_MappingParameter.applicationObject_3,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1602_RPDO_MappingParameter.applicationObject_4,
            .subIndex = 4,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1602_RPDO_MappingParameter.applicationObject_5,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1602_RPDO_MappingParameter.applicationObject_6,
            .subIndex = 6,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1602_RPDO_MappingParameter.applicationObject_7,
            .subIndex = 7,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1602_RPDO_MappingParameter.applicationObject_8,
            .subIndex = 8,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
    },
    .o_1603_RPDO_MappingParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1603_RPDO_MappingParameter.numberOfMappedApplicationObjectsInPDO,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1603_RPDO_MappingParameter.applicationObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1603_RPDO_MappingParameter.applicationObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1603_RPDO_MappingParameter.applicationObject_3,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1603_RPDO_MappingParameter.applicationObject_4,
            .subIndex = 4,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1603_RPDO_MappingParameter.applicationObject_5,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1603_RPDO_MappingParameter.applicationObject_6,
            .subIndex = 6,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1603_RPDO_MappingParameter.applicationObject_7,
            .subIndex = 7,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1603_RPDO_MappingParameter.applicationObject_8,
            .subIndex = 8,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
    },
    .o_1604_RPDO_MappingParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1604_RPDO_MappingParameter.numberOfMappedApplicationObjectsInPDO,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1604_RPDO_MappingParameter.applicationObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1604_RPDO_MappingParameter.applicationObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1604_RPDO_MappingParameter.applicationObject_3,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1604_RPDO_MappingParameter.applicationObject_4,
            .subIndex = 4,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1604_RPDO_MappingParameter.applicationObject_5,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1604_RPDO_MappingParameter.applicationObject_6,
            .subIndex = 6,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1604_RPDO_MappingParameter.applicationObject_7,
            .subIndex = 7,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1604_RPDO_MappingParameter.applicationObject_8,
            .subIndex = 8,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
    },
    .o_1605_RPDO_MappingParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1605_RPDO_MappingParameter.numberOfMappedApplicationObjectsInPDO,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1605_RPDO_MappingParameter.applicationObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1605_RPDO_MappingParameter.applicationObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1605_RPDO_MappingParameter.applicationObject_3,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1605_RPDO_MappingParameter.applicationObject_4,
            .subIndex = 4,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1605_RPDO_MappingParameter.applicationObject_5,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1605_RPDO_MappingParameter.applicationObject_6,
            .subIndex = 6,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1605_RPDO_MappingParameter.applicationObject_7,
            .subIndex = 7,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1605_RPDO_MappingParameter.applicationObject_8,
            .subIndex = 8,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
    },
    .o_1606_RPDO_MappingParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1606_RPDO_MappingParameter.numberOfMappedApplicationObjectsInPDO,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1606_RPDO_MappingParameter.applicationObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1606_RPDO_MappingParameter.applicationObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1606_RPDO_MappingParameter.applicationObject_3,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1606_RPDO_MappingParameter.applicationObject_4,
            .subIndex = 4,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1606_RPDO_MappingParameter.applicationObject_5,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1606_RPDO_MappingParameter.applicationObject_6,
            .subIndex = 6,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1606_RPDO_MappingParameter.applicationObject_7,
            .subIndex = 7,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1606_RPDO_MappingParameter.applicationObject_8,
            .subIndex = 8,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
    },
    .o_1607_RPDO_MappingParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1607_RPDO_MappingParameter.numberOfMappedApplicationObjectsInPDO,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1607_RPDO_MappingParameter.applicationObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1607_RPDO_MappingParameter.applicationObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1607_RPDO_MappingParameter.applicationObject_3,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1607_RPDO_MappingParameter.applicationObject_4,
            .subIndex = 4,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1607_RPDO_MappingParameter.applicationObject_5,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1607_RPDO_MappingParameter.applicationObject_6,
            .subIndex = 6,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1607_RPDO_MappingParameter.applicationObject_7,
            .subIndex = 7,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1607_RPDO_MappingParameter.applicationObject_8,
            .subIndex = 8,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
    },
    .o_1608_RPDO_MappingParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1608_RPDO_MappingParameter.numberOfMappedApplicationObjectsInPDO,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1608_RPDO_MappingParameter.applicationObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1608_RPDO_MappingParameter.applicationObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1608_RPDO_MappingParameter.applicationObject_3,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1608_RPDO_MappingParameter.applicationObject_4,
            .subIndex = 4,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1608_RPDO_MappingParameter.applicationObject_5,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1608_RPDO_MappingParameter.applicationObject_6,
            .subIndex = 6,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1608_RPDO_MappingParameter.applicationObject_7,
            .subIndex = 7,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1608_RPDO_MappingParameter.applicationObject_8,
            .subIndex = 8,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
    },
    .o_1609_RPDO_MappingParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1609_RPDO_MappingParameter.numberOfMappedApplicationObjectsInPDO,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1609_RPDO_MappingParameter.applicationObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1609_RPDO_MappingParameter.applicationObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1609_RPDO_MappingParameter.applicationObject_3,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1609_RPDO_MappingParameter.applicationObject_4,
            .subIndex = 4,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1609_RPDO_MappingParameter.applicationObject_5,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1609_RPDO_MappingParameter.applicationObject_6,
            .subIndex = 6,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1609_RPDO_MappingParameter.applicationObject_7,
            .subIndex = 7,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1609_RPDO_MappingParameter.applicationObject_8,
            .subIndex = 8,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
    },
    .o_160A_RPDO_MappingParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x160A_RPDO_MappingParameter.numberOfMappedApplicationObjectsInPDO,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160A_RPDO_MappingParameter.applicationObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160A_RPDO_MappingParameter.applicationObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160A_RPDO_MappingParameter.applicationObject_3,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160A_RPDO_MappingParameter.applicationObject_4,
            .subIndex = 4,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160A_RPDO_MappingParameter.applicationObject_5,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160A_RPDO_MappingParameter.applicationObject_6,
            .subIndex = 6,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160A_RPDO_MappingParameter.applicationObject_7,
            .subIndex = 7,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160A_RPDO_MappingParameter.applicationObject_8,
            .subIndex = 8,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
    },
    .o_160B_RPDO_MappingParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x160B_RPDO_MappingParameter.numberOfMappedApplicationObjectsInPDO,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160B_RPDO_MappingParameter.applicationObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160B_RPDO_MappingParameter.applicationObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160B_RPDO_MappingParameter.applicationObject_3,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160B_RPDO_MappingParameter.applicationObject_4,
            .subIndex = 4,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160B_RPDO_MappingParameter.applicationObject_5,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160B_RPDO_MappingParameter.applicationObject_6,
            .subIndex = 6,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160B_RPDO_MappingParameter.applicationObject_7,
            .subIndex = 7,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160B_RPDO_MappingParameter.applicationObject_8,
            .subIndex = 8,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
    },
    .o_160C_RPDO_MappingParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x160C_RPDO_MappingParameter.numberOfMappedApplicationObjectsInPDO,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160C_RPDO_MappingParameter.applicationObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160C_RPDO_MappingParameter.applicationObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160C_RPDO_MappingParameter.applicationObject_3,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160C_RPDO_MappingParameter.applicationObject_4,
            .subIndex = 4,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160C_RPDO_MappingParameter.applicationObject_5,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160C_RPDO_MappingParameter.applicationObject_6,
            .subIndex = 6,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160C_RPDO_MappingParameter.applicationObject_7,
            .subIndex = 7,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160C_RPDO_MappingParameter.applicationObject_8,
            .subIndex = 8,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
    },
    .o_160D_RPDO_MappingParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x160D_RPDO_MappingParameter.numberOfMappedApplicationObjectsInPDO,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160D_RPDO_MappingParameter.applicationObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160D_RPDO_MappingParameter.applicationObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160D_RPDO_MappingParameter.applicationObject_3,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160D_RPDO_MappingParameter.applicationObject_4,
            .subIndex = 4,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160D_RPDO_MappingParameter.applicationObject_5,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160D_RPDO_MappingParameter.applicationObject_6,
            .subIndex = 6,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160D_RPDO_MappingParameter.applicationObject_7,
            .subIndex = 7,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160D_RPDO_MappingParameter.applicationObject_8,
            .subIndex = 8,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
    },
    .o_160E_RPDO_MappingParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x160E_RPDO_MappingParameter.numberOfMappedApplicationObjectsInPDO,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160E_RPDO_MappingParameter.applicationObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160E_RPDO_MappingParameter.applicationObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160E_RPDO_MappingParameter.applicationObject_3,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160E_RPDO_MappingParameter.applicationObject_4,
            .subIndex = 4,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160E_RPDO_MappingParameter.applicationObject_5,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160E_RPDO_MappingParameter.applicationObject_6,
            .subIndex = 6,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160E_RPDO_MappingParameter.applicationObject_7,
            .subIndex = 7,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160E_RPDO_MappingParameter.applicationObject_8,
            .subIndex = 8,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
    },
    .o_160F_RPDO_MappingParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x160F_RPDO_MappingParameter.numberOfMappedApplicationObjectsInPDO,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160F_RPDO_MappingParameter.applicationObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160F_RPDO_MappingParameter.applicationObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160F_RPDO_MappingParameter.applicationObject_3,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160F_RPDO_MappingParameter.applicationObject_4,
            .subIndex = 4,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160F_RPDO_MappingParameter.applicationObject_5,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160F_RPDO_MappingParameter.applicationObject_6,
            .subIndex = 6,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160F_RPDO_MappingParameter.applicationObject_7,
            .subIndex = 7,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x160F_RPDO_MappingParameter.applicationObject_8,
            .subIndex = 8,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
    },
    .o_1800_TPDO_CommunicationParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1800_TPDO_CommunicationParameter.highestSubIndexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1800_TPDO_CommunicationParameter.COB_ID_UsedByTPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1800_TPDO_CommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1800_TPDO_CommunicationParameter.inhibitTime,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1800_TPDO_CommunicationParameter.compatibilityEntry,
            .subIndex = 4,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1800_TPDO_CommunicationParameter.eventTimer,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1800_TPDO_CommunicationParameter.SYNC_StartValue,
            .subIndex = 6,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
    },
    .o_1801_TPDO_CommunicationParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1801_TPDO_CommunicationParameter.highestSubIndexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1801_TPDO_CommunicationParameter.COB_ID_UsedByTPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1801_TPDO_CommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1801_TPDO_CommunicationParameter.inhibitTime,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1801_TPDO_CommunicationParameter.compatibilityEntry,
            .subIndex = 4,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1801_TPDO_CommunicationParameter.eventTimer,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1801_TPDO_CommunicationParameter.SYNC_StartValue,
            .subIndex = 6,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
    },
    .o_1802_TPDO_CommunicationParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1802_TPDO_CommunicationParameter.highestSubIndexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1802_TPDO_CommunicationParameter.COB_ID_UsedByTPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1802_TPDO_CommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1802_TPDO_CommunicationParameter.inhibitTime,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1802_TPDO_CommunicationParameter.compatibilityEntry,
            .subIndex = 4,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1802_TPDO_CommunicationParameter.eventTimer,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1802_TPDO_CommunicationParameter.SYNC_StartValue,
            .subIndex = 6,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
    },
    .o_1803_TPDO_CommunicationParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1803_TPDO_CommunicationParameter.highestSubIndexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1803_TPDO_CommunicationParameter.COB_ID_UsedByTPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1803_TPDO_CommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1803_TPDO_CommunicationParameter.inhibitTime,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1803_TPDO_CommunicationParameter.compatibilityEntry,
            .subIndex = 4,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1803_TPDO_CommunicationParameter.eventTimer,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1803_TPDO_CommunicationParameter.SYNC_StartValue,
            .subIndex = 6,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
    },
    .o_1804_TPDO_CommunicationParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1804_TPDO_CommunicationParameter.highestSubIndexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1804_TPDO_CommunicationParameter.COB_ID_UsedByTPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1804_TPDO_CommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1804_TPDO_CommunicationParameter.inhibitTime,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1804_TPDO_CommunicationParameter.compatibilityEntry,
            .subIndex = 4,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1804_TPDO_CommunicationParameter.eventTimer,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1804_TPDO_CommunicationParameter.SYNC_StartValue,
            .subIndex = 6,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
    },
    .o_1805_TPDO_CommunicationParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1805_TPDO_CommunicationParameter.highestSubIndexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1805_TPDO_CommunicationParameter.COB_ID_UsedByTPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1805_TPDO_CommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1805_TPDO_CommunicationParameter.inhibitTime,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1805_TPDO_CommunicationParameter.compatibilityEntry,
            .subIndex = 4,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1805_TPDO_CommunicationParameter.eventTimer,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1805_TPDO_CommunicationParameter.SYNC_StartValue,
            .subIndex = 6,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
    },
    .o_1806_TPDO_CommunicationParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1806_TPDO_CommunicationParameter.highestSubIndexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1806_TPDO_CommunicationParameter.COB_ID_UsedByTPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1806_TPDO_CommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1806_TPDO_CommunicationParameter.inhibitTime,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1806_TPDO_CommunicationParameter.compatibilityEntry,
            .subIndex = 4,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1806_TPDO_CommunicationParameter.eventTimer,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1806_TPDO_CommunicationParameter.SYNC_StartValue,
            .subIndex = 6,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
    },
    .o_1807_TPDO_CommunicationParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1807_TPDO_CommunicationParameter.highestSubIndexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1807_TPDO_CommunicationParameter.COB_ID_UsedByTPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1807_TPDO_CommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1807_TPDO_CommunicationParameter.inhibitTime,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1807_TPDO_CommunicationParameter.compatibilityEntry,
            .subIndex = 4,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1807_TPDO_CommunicationParameter.eventTimer,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1807_TPDO_CommunicationParameter.SYNC_StartValue,
            .subIndex = 6,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
    },
    .o_1808_TPDO_CommunicationParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1808_TPDO_CommunicationParameter.highestSubIndexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1808_TPDO_CommunicationParameter.COB_ID_UsedByTPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1808_TPDO_CommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1808_TPDO_CommunicationParameter.inhibitTime,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1808_TPDO_CommunicationParameter.compatibilityEntry,
            .subIndex = 4,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1808_TPDO_CommunicationParameter.eventTimer,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1808_TPDO_CommunicationParameter.SYNC_StartValue,
            .subIndex = 6,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
    },
    .o_1809_TPDO_CommunicationParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1809_TPDO_CommunicationParameter.highestSubIndexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1809_TPDO_CommunicationParameter.COB_ID_UsedByTPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1809_TPDO_CommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1809_TPDO_CommunicationParameter.inhibitTime,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1809_TPDO_CommunicationParameter.compatibilityEntry,
            .subIndex = 4,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1809_TPDO_CommunicationParameter.eventTimer,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1809_TPDO_CommunicationParameter.SYNC_StartValue,
            .subIndex = 6,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
    },
    .o_180A_TPDO_CommunicationParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x180A_TPDO_CommunicationParameter.highestSubIndexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x180A_TPDO_CommunicationParameter.COB_ID_UsedByTPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x180A_TPDO_CommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x180A_TPDO_CommunicationParameter.inhibitTime,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x180A_TPDO_CommunicationParameter.compatibilityEntry,
            .subIndex = 4,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x180A_TPDO_CommunicationParameter.eventTimer,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x180A_TPDO_CommunicationParameter.SYNC_StartValue,
            .subIndex = 6,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
    },
    .o_180B_TPDO_CommunicationParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x180B_TPDO_CommunicationParameter.highestSubIndexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x180B_TPDO_CommunicationParameter.COB_ID_UsedByTPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x180B_TPDO_CommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x180B_TPDO_CommunicationParameter.inhibitTime,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x180B_TPDO_CommunicationParameter.compatibilityEntry,
            .subIndex = 4,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x180B_TPDO_CommunicationParameter.eventTimer,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x180B_TPDO_CommunicationParameter.SYNC_StartValue,
            .subIndex = 6,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
    },
    .o_180C_TPDO_CommunicationParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x180C_TPDO_CommunicationParameter.highestSubIndexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x180C_TPDO_CommunicationParameter.COB_ID_UsedByTPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x180C_TPDO_CommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x180C_TPDO_CommunicationParameter.inhibitTime,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x180C_TPDO_CommunicationParameter.compatibilityEntry,
            .subIndex = 4,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x180C_TPDO_CommunicationParameter.eventTimer,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x180C_TPDO_CommunicationParameter.SYNC_StartValue,
            .subIndex = 6,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
    },
    .o_180D_TPDO_CommunicationParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x180D_TPDO_CommunicationParameter.highestSubIndexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x180D_TPDO_CommunicationParameter.COB_ID_UsedByTPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x180D_TPDO_CommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x180D_TPDO_CommunicationParameter.inhibitTime,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x180D_TPDO_CommunicationParameter.compatibilityEntry,
            .subIndex = 4,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x180D_TPDO_CommunicationParameter.eventTimer,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x180D_TPDO_CommunicationParameter.SYNC_StartValue,
            .subIndex = 6,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
    },
    .o_180E_TPDO_CommunicationParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x180E_TPDO_CommunicationParameter.highestSubIndexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x180E_TPDO_CommunicationParameter.COB_ID_UsedByTPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x180E_TPDO_CommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x180E_TPDO_CommunicationParameter.inhibitTime,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x180E_TPDO_CommunicationParameter.compatibilityEntry,
            .subIndex = 4,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x180E_TPDO_CommunicationParameter.eventTimer,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x180E_TPDO_CommunicationParameter.SYNC_StartValue,
            .subIndex = 6,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
    },
    .o_180F_TPDO_CommunicationParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x180F_TPDO_CommunicationParameter.highestSubIndexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x180F_TPDO_CommunicationParameter.COB_ID_UsedByTPDO,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x180F_TPDO_CommunicationParameter.transmissionType,
            .subIndex = 2,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x180F_TPDO_CommunicationParameter.inhibitTime,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x180F_TPDO_CommunicationParameter.compatibilityEntry,
            .subIndex = 4,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x180F_TPDO_CommunicationParameter.eventTimer,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x180F_TPDO_CommunicationParameter.SYNC_StartValue,
            .subIndex = 6,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
    },
    .o_1A00_TPDO_MappingParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1A00_TPDO_MappingParameter.numberOfMappedApplicationObjectsInPDO,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A00_TPDO_MappingParameter.applicationObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A00_TPDO_MappingParameter.applicationObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A00_TPDO_MappingParameter.applicationObject_3,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A00_TPDO_MappingParameter.applicationObject_4,
            .subIndex = 4,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A00_TPDO_MappingParameter.applicationObject_5,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A00_TPDO_MappingParameter.applicationObject_6,
            .subIndex = 6,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A00_TPDO_MappingParameter.applicationObject_7,
            .subIndex = 7,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A00_TPDO_MappingParameter.applicationObject_8,
            .subIndex = 8,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
    },
    .o_1A01_TPDO_MappingParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1A01_TPDO_MappingParameter.numberOfMappedApplicationObjectsInPDO,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A01_TPDO_MappingParameter.applicationObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A01_TPDO_MappingParameter.applicationObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A01_TPDO_MappingParameter.applicationObject_3,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A01_TPDO_MappingParameter.applicationObject_4,
            .subIndex = 4,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A01_TPDO_MappingParameter.applicationObject_5,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A01_TPDO_MappingParameter.applicationObject_6,
            .subIndex = 6,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A01_TPDO_MappingParameter.applicationObject_7,
            .subIndex = 7,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A01_TPDO_MappingParameter.applicationObject_8,
            .subIndex = 8,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
    },
    .o_1A02_TPDO_MappingParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1A02_TPDO_MappingParameter.numberOfMappedApplicationObjectsInPDO,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A02_TPDO_MappingParameter.applicationObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A02_TPDO_MappingParameter.applicationObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A02_TPDO_MappingParameter.applicationObject_3,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A02_TPDO_MappingParameter.applicationObject_4,
            .subIndex = 4,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A02_TPDO_MappingParameter.applicationObject_5,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A02_TPDO_MappingParameter.applicationObject_6,
            .subIndex = 6,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A02_TPDO_MappingParameter.applicationObject_7,
            .subIndex = 7,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A02_TPDO_MappingParameter.applicationObject_8,
            .subIndex = 8,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
    },
    .o_1A03_TPDO_MappingParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1A03_TPDO_MappingParameter.numberOfMappedApplicationObjectsInPDO,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A03_TPDO_MappingParameter.applicationObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A03_TPDO_MappingParameter.applicationObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A03_TPDO_MappingParameter.applicationObject_3,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A03_TPDO_MappingParameter.applicationObject_4,
            .subIndex = 4,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A03_TPDO_MappingParameter.applicationObject_5,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A03_TPDO_MappingParameter.applicationObject_6,
            .subIndex = 6,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A03_TPDO_MappingParameter.applicationObject_7,
            .subIndex = 7,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A03_TPDO_MappingParameter.applicationObject_8,
            .subIndex = 8,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
    },
    .o_1A04_TPDO_MappingParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1A04_TPDO_MappingParameter.numberOfMappedApplicationObjectsInPDO,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A04_TPDO_MappingParameter.applicationObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A04_TPDO_MappingParameter.applicationObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A04_TPDO_MappingParameter.applicationObject_3,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A04_TPDO_MappingParameter.applicationObject_4,
            .subIndex = 4,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A04_TPDO_MappingParameter.applicationObject_5,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A04_TPDO_MappingParameter.applicationObject_6,
            .subIndex = 6,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A04_TPDO_MappingParameter.applicationObject_7,
            .subIndex = 7,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A04_TPDO_MappingParameter.applicationObject_8,
            .subIndex = 8,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
    },
    .o_1A05_TPDO_MappingParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1A05_TPDO_MappingParameter.numberOfMappedApplicationObjectsInPDO,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A05_TPDO_MappingParameter.applicationObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A05_TPDO_MappingParameter.applicationObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A05_TPDO_MappingParameter.applicationObject_3,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A05_TPDO_MappingParameter.applicationObject_4,
            .subIndex = 4,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A05_TPDO_MappingParameter.applicationObject_5,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A05_TPDO_MappingParameter.applicationObject_6,
            .subIndex = 6,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A05_TPDO_MappingParameter.applicationObject_7,
            .subIndex = 7,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A05_TPDO_MappingParameter.applicationObject_8,
            .subIndex = 8,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
    },
    .o_1A06_TPDO_MappingParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1A06_TPDO_MappingParameter.numberOfMappedApplicationObjectsInPDO,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A06_TPDO_MappingParameter.applicationObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A06_TPDO_MappingParameter.applicationObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A06_TPDO_MappingParameter.applicationObject_3,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A06_TPDO_MappingParameter.applicationObject_4,
            .subIndex = 4,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A06_TPDO_MappingParameter.applicationObject_5,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A06_TPDO_MappingParameter.applicationObject_6,
            .subIndex = 6,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A06_TPDO_MappingParameter.applicationObject_7,
            .subIndex = 7,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A06_TPDO_MappingParameter.applicationObject_8,
            .subIndex = 8,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
    },
    .o_1A07_TPDO_MappingParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1A07_TPDO_MappingParameter.numberOfMappedApplicationObjectsInPDO,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A07_TPDO_MappingParameter.applicationObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A07_TPDO_MappingParameter.applicationObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A07_TPDO_MappingParameter.applicationObject_3,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A07_TPDO_MappingParameter.applicationObject_4,
            .subIndex = 4,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A07_TPDO_MappingParameter.applicationObject_5,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A07_TPDO_MappingParameter.applicationObject_6,
            .subIndex = 6,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A07_TPDO_MappingParameter.applicationObject_7,
            .subIndex = 7,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A07_TPDO_MappingParameter.applicationObject_8,
            .subIndex = 8,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
    },
    .o_1A08_TPDO_MappingParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1A08_TPDO_MappingParameter.numberOfMappedApplicationObjectsInPDO,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A08_TPDO_MappingParameter.applicationObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A08_TPDO_MappingParameter.applicationObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A08_TPDO_MappingParameter.applicationObject_3,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A08_TPDO_MappingParameter.applicationObject_4,
            .subIndex = 4,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A08_TPDO_MappingParameter.applicationObject_5,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A08_TPDO_MappingParameter.applicationObject_6,
            .subIndex = 6,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A08_TPDO_MappingParameter.applicationObject_7,
            .subIndex = 7,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A08_TPDO_MappingParameter.applicationObject_8,
            .subIndex = 8,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
    },
    .o_1A09_TPDO_MappingParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1A09_TPDO_MappingParameter.numberOfMappedApplicationObjectsInPDO,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A09_TPDO_MappingParameter.applicationObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A09_TPDO_MappingParameter.applicationObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A09_TPDO_MappingParameter.applicationObject_3,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A09_TPDO_MappingParameter.applicationObject_4,
            .subIndex = 4,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A09_TPDO_MappingParameter.applicationObject_5,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A09_TPDO_MappingParameter.applicationObject_6,
            .subIndex = 6,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A09_TPDO_MappingParameter.applicationObject_7,
            .subIndex = 7,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A09_TPDO_MappingParameter.applicationObject_8,
            .subIndex = 8,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
    },
    .o_1A0A_TPDO_MappingParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0A_TPDO_MappingParameter.numberOfMappedApplicationObjectsInPDO,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0A_TPDO_MappingParameter.applicationObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0A_TPDO_MappingParameter.applicationObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0A_TPDO_MappingParameter.applicationObject_3,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0A_TPDO_MappingParameter.applicationObject_4,
            .subIndex = 4,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0A_TPDO_MappingParameter.applicationObject_5,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0A_TPDO_MappingParameter.applicationObject_6,
            .subIndex = 6,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0A_TPDO_MappingParameter.applicationObject_7,
            .subIndex = 7,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0A_TPDO_MappingParameter.applicationObject_8,
            .subIndex = 8,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
    },
    .o_1A0B_TPDO_MappingParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0B_TPDO_MappingParameter.numberOfMappedApplicationObjectsInPDO,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0B_TPDO_MappingParameter.applicationObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0B_TPDO_MappingParameter.applicationObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0B_TPDO_MappingParameter.applicationObject_3,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0B_TPDO_MappingParameter.applicationObject_4,
            .subIndex = 4,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0B_TPDO_MappingParameter.applicationObject_5,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0B_TPDO_MappingParameter.applicationObject_6,
            .subIndex = 6,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0B_TPDO_MappingParameter.applicationObject_7,
            .subIndex = 7,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0B_TPDO_MappingParameter.applicationObject_8,
            .subIndex = 8,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
    },
    .o_1A0C_TPDO_MappingParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0C_TPDO_MappingParameter.numberOfMappedApplicationObjectsInPDO,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0C_TPDO_MappingParameter.applicationObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0C_TPDO_MappingParameter.applicationObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0C_TPDO_MappingParameter.applicationObject_3,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0C_TPDO_MappingParameter.applicationObject_4,
            .subIndex = 4,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0C_TPDO_MappingParameter.applicationObject_5,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0C_TPDO_MappingParameter.applicationObject_6,
            .subIndex = 6,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0C_TPDO_MappingParameter.applicationObject_7,
            .subIndex = 7,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0C_TPDO_MappingParameter.applicationObject_8,
            .subIndex = 8,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
    },
    .o_1A0D_TPDO_MappingParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0D_TPDO_MappingParameter.numberOfMappedApplicationObjectsInPDO,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0D_TPDO_MappingParameter.applicationObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0D_TPDO_MappingParameter.applicationObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0D_TPDO_MappingParameter.applicationObject_3,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0D_TPDO_MappingParameter.applicationObject_4,
            .subIndex = 4,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0D_TPDO_MappingParameter.applicationObject_5,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0D_TPDO_MappingParameter.applicationObject_6,
            .subIndex = 6,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0D_TPDO_MappingParameter.applicationObject_7,
            .subIndex = 7,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0D_TPDO_MappingParameter.applicationObject_8,
            .subIndex = 8,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
    },
    .o_1A0E_TPDO_MappingParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0E_TPDO_MappingParameter.numberOfMappedApplicationObjectsInPDO,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0E_TPDO_MappingParameter.applicationObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0E_TPDO_MappingParameter.applicationObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0E_TPDO_MappingParameter.applicationObject_3,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0E_TPDO_MappingParameter.applicationObject_4,
            .subIndex = 4,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0E_TPDO_MappingParameter.applicationObject_5,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0E_TPDO_MappingParameter.applicationObject_6,
            .subIndex = 6,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0E_TPDO_MappingParameter.applicationObject_7,
            .subIndex = 7,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0E_TPDO_MappingParameter.applicationObject_8,
            .subIndex = 8,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
    },
    .o_1A0F_TPDO_MappingParameter = {
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0F_TPDO_MappingParameter.numberOfMappedApplicationObjectsInPDO,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0F_TPDO_MappingParameter.applicationObject_1,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0F_TPDO_MappingParameter.applicationObject_2,
            .subIndex = 2,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0F_TPDO_MappingParameter.applicationObject_3,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0F_TPDO_MappingParameter.applicationObject_4,
            .subIndex = 4,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0F_TPDO_MappingParameter.applicationObject_5,
            .subIndex = 5,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0F_TPDO_MappingParameter.applicationObject_6,
            .subIndex = 6,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0F_TPDO_MappingParameter.applicationObject_7,
            .subIndex = 7,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_PERSIST_COMM.x1A0F_TPDO_MappingParameter.applicationObject_8,
            .subIndex = 8,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
    },
    .o_1F80_nmtstartup = {
        .dataOrig = &OD_PERSIST_COMM.x1F80_nmtstartup,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataLength = 4
    },
    .o_2000_BUS_Management = {
        {
            .dataOrig = &OD_PERSIST_MFR.x2000_BUS_Management.highestSubIndexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_MFR.x2000_BUS_Management.bdefault,
            .subIndex = 1,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_MFR.x2000_BUS_Management.ttoggle,
            .subIndex = 2,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_MFR.x2000_BUS_Management.ntoggle,
            .subIndex = 3,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_PERSIST_MFR.x2000_BUS_Management.ctoggle,
            .subIndex = 4,
            .attribute = ODA_SDO_RW,
            .dataLength = 1
        },
    },
    .o_2010_SCET = {
        .dataOrig = &OD_RAM.x2010_SCET,
        .attribute = ODA_SDO_RW | ODA_TRPDO | ODA_MB,
        .dataLength = 8
    },
    .o_2011_UTC = {
        .dataOrig = &OD_RAM.x2011_UTC,
        .attribute = ODA_SDO_RW | ODA_TRPDO | ODA_MB,
        .dataLength = 8
    },
    .o_2020_MCU_UniqueDeviceID = {
        .dataOrig0 = &OD_RAM.x2020_MCU_UniqueDeviceID_sub0,
        .dataOrig = &OD_RAM.x2020_MCU_UniqueDeviceID[0],
        .attribute0 = ODA_SDO_R,
        .attribute = ODA_SDO_R | ODA_MB,
        .dataElementLength = 4,
        .dataElementSizeof = sizeof(uint32_t)
    },
    .o_2021_MCU_Calibration = {
        {
            .dataOrig = &OD_RAM.x2021_MCU_Calibration.highestSubIndexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x2021_MCU_Calibration.TS_CAL1,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x2021_MCU_Calibration.TS_CAL2,
            .subIndex = 2,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x2021_MCU_Calibration.VREFINT_CAL,
            .subIndex = 3,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 2
        },
    },
    .o_2022_MCU_Sensors = {
        {
            .dataOrig = &OD_RAM.x2022_MCU_Sensors.highestSubIndexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x2022_MCU_Sensors.temperature,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_TPDO,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x2022_MCU_Sensors.VREFINT,
            .subIndex = 2,
            .attribute = ODA_SDO_R | ODA_TPDO,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x2022_MCU_Sensors.VBAT,
            .subIndex = 3,
            .attribute = ODA_SDO_R | ODA_TPDO,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x2022_MCU_Sensors.VBUSP_Current,
            .subIndex = 4,
            .attribute = ODA_SDO_R | ODA_TPDO,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x2022_MCU_Sensors.temperatureRaw,
            .subIndex = 5,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x2022_MCU_Sensors.VREFINT_Raw,
            .subIndex = 6,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x2022_MCU_Sensors.VBAT_Raw,
            .subIndex = 7,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x2022_MCU_Sensors.VBUSP_CurrentRaw,
            .subIndex = 8,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
    },
    .o_2100_errorStatusBits = {
        .dataOrig = &OD_RAM.x2100_errorStatusBits[0],
        .attribute = ODA_SDO_R,
        .dataLength = 0
    },
    .o_6000_gyroscope = {
        {
            .dataOrig = &OD_RAM.x6000_gyroscope.highestSubIndexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x6000_gyroscope.pitchRate,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x6000_gyroscope.yawRate,
            .subIndex = 2,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x6000_gyroscope.rollRate,
            .subIndex = 3,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x6000_gyroscope.pitchRateRaw,
            .subIndex = 4,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x6000_gyroscope.yawRateRaw,
            .subIndex = 5,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x6000_gyroscope.rollRateRaw,
            .subIndex = 6,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
    },
    .o_6001_acceleration = {
        {
            .dataOrig = &OD_RAM.x6001_acceleration.highestSubIndexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x6001_acceleration.accx,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x6001_acceleration.accy,
            .subIndex = 2,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x6001_acceleration.accz,
            .subIndex = 3,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x6001_acceleration.accXRaw,
            .subIndex = 4,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x6001_acceleration.accyRaw,
            .subIndex = 5,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x6001_acceleration.acczRaw,
            .subIndex = 6,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
    },
    .o_6002_IMU_Temperature = {
        .dataOrig = &OD_RAM.x6002_IMU_Temperature,
        .attribute = ODA_SDO_R | ODA_TPDO,
        .dataLength = 1
    },
    .o_6003_magnetometerPZ1 = {
        {
            .dataOrig = &OD_RAM.x6003_magnetometerPZ1.highestSubIndexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x6003_magnetometerPZ1.magx,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x6003_magnetometerPZ1.magy,
            .subIndex = 2,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x6003_magnetometerPZ1.magz,
            .subIndex = 3,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
    },
    .o_6004_magnetometerPZ2 = {
        {
            .dataOrig = &OD_RAM.x6004_magnetometerPZ2.highestSubIndexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x6004_magnetometerPZ2.magx,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x6004_magnetometerPZ2.magy,
            .subIndex = 2,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x6004_magnetometerPZ2.magz,
            .subIndex = 3,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
    },
    .o_6005_magnetometerMZ1 = {
        {
            .dataOrig = &OD_RAM.x6005_magnetometerMZ1.highestSubIndexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x6005_magnetometerMZ1.magx,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x6005_magnetometerMZ1.magy,
            .subIndex = 2,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x6005_magnetometerMZ1.magz,
            .subIndex = 3,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
    },
    .o_6006_magnetometerMZ2 = {
        {
            .dataOrig = &OD_RAM.x6006_magnetometerMZ2.highestSubIndexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x6006_magnetometerMZ2.magx,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x6006_magnetometerMZ2.magy,
            .subIndex = 2,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x6006_magnetometerMZ2.magz,
            .subIndex = 3,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
    },
    .o_6007_magnetorquer = {
        {
            .dataOrig = &OD_RAM.x6007_magnetorquer.highestSubIndexSupported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x6007_magnetorquer.magnetorquerXPWM_DutyCycle,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_TRPDO | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x6007_magnetorquer.magnetorquerYPWM_DutyCycle,
            .subIndex = 2,
            .attribute = ODA_SDO_RW | ODA_TRPDO | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x6007_magnetorquer.magnetorquerZPWM_DutyCycle,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_TRPDO | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x6007_magnetorquer.magnetorquerXCurrentUA,
            .subIndex = 4,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x6007_magnetorquer.magnetorquerYCurrentUA,
            .subIndex = 5,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x6007_magnetorquer.magnetorquerZCurrentUA,
            .subIndex = 6,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
    },
};

static OD_ATTR_OD OD_entry_t ODList[] = {
    {0x1000, 0x01, ODT_VAR, &ODObjs.o_1000_deviceType, NULL},
    {0x1001, 0x01, ODT_VAR, &ODObjs.o_1001_errorRegister, NULL},
    {0x1002, 0x01, ODT_VAR, &ODObjs.o_1002_manufacturerStatusRegister, NULL},
    {0x1003, 0x09, ODT_ARR, &ODObjs.o_1003_preDefinedErrorField, NULL},
    {0x1005, 0x01, ODT_VAR, &ODObjs.o_1005_COB_ID_SYNC_Message, NULL},
    {0x1006, 0x01, ODT_VAR, &ODObjs.o_1006_communicationCyclePeriod, NULL},
    {0x1007, 0x01, ODT_VAR, &ODObjs.o_1007_synchronousWindowLength, NULL},
    {0x1008, 0x01, ODT_VAR, &ODObjs.o_1008_manufacturerDeviceName, NULL},
    {0x1009, 0x01, ODT_VAR, &ODObjs.o_1009_manufacturerHardwareVersion, NULL},
    {0x100A, 0x01, ODT_VAR, &ODObjs.o_100A_manufacturerSoftwareVersion, NULL},
    {0x1010, 0x05, ODT_ARR, &ODObjs.o_1010_storeParameters, NULL},
    {0x1011, 0x05, ODT_ARR, &ODObjs.o_1011_restoreDefaultParameters, NULL},
    {0x1014, 0x01, ODT_VAR, &ODObjs.o_1014_COB_ID_EMCY, NULL},
    {0x1015, 0x01, ODT_VAR, &ODObjs.o_1015_inhibitTimeEMCY, NULL},
    {0x1016, 0x09, ODT_ARR, &ODObjs.o_1016_consumerHeartbeatTime, NULL},
    {0x1017, 0x01, ODT_VAR, &ODObjs.o_1017_producerHeartbeatTime, NULL},
    {0x1018, 0x05, ODT_REC, &ODObjs.o_1018_identity, NULL},
    {0x1019, 0x01, ODT_VAR, &ODObjs.o_1019_synchronousCounterOverflowValue, NULL},
    {0x1029, 0x07, ODT_ARR, &ODObjs.o_1029_errorBehavior, NULL},
    {0x1200, 0x04, ODT_REC, &ODObjs.o_1200_SDO_ServerParameter, NULL},
    {0x1400, 0x04, ODT_REC, &ODObjs.o_1400_RPDO_CommunicationParameter, NULL},
    {0x1401, 0x04, ODT_REC, &ODObjs.o_1401_RPDO_CommunicationParameter, NULL},
    {0x1402, 0x04, ODT_REC, &ODObjs.o_1402_RPDO_CommunicationParameter, NULL},
    {0x1403, 0x04, ODT_REC, &ODObjs.o_1403_RPDO_CommunicationParameter, NULL},
    {0x1404, 0x04, ODT_REC, &ODObjs.o_1404_RPDO_CommunicationParameter, NULL},
    {0x1405, 0x04, ODT_REC, &ODObjs.o_1405_RPDO_CommunicationParameter, NULL},
    {0x1406, 0x04, ODT_REC, &ODObjs.o_1406_RPDO_CommunicationParameter, NULL},
    {0x1407, 0x04, ODT_REC, &ODObjs.o_1407_RPDO_CommunicationParameter, NULL},
    {0x1408, 0x04, ODT_REC, &ODObjs.o_1408_RPDO_CommunicationParameter, NULL},
    {0x1409, 0x04, ODT_REC, &ODObjs.o_1409_RPDO_CommunicationParameter, NULL},
    {0x140A, 0x04, ODT_REC, &ODObjs.o_140A_RPDO_CommunicationParameter, NULL},
    {0x140B, 0x04, ODT_REC, &ODObjs.o_140B_RPDO_CommunicationParameter, NULL},
    {0x140C, 0x04, ODT_REC, &ODObjs.o_140C_RPDO_CommunicationParameter, NULL},
    {0x140D, 0x04, ODT_REC, &ODObjs.o_140D_RPDO_CommunicationParameter, NULL},
    {0x140E, 0x04, ODT_REC, &ODObjs.o_140E_RPDO_CommunicationParameter, NULL},
    {0x140F, 0x04, ODT_REC, &ODObjs.o_140F_RPDO_CommunicationParameter, NULL},
    {0x1600, 0x09, ODT_REC, &ODObjs.o_1600_RPDO_MappingParameter, NULL},
    {0x1601, 0x09, ODT_REC, &ODObjs.o_1601_RPDO_MappingParameter, NULL},
    {0x1602, 0x09, ODT_REC, &ODObjs.o_1602_RPDO_MappingParameter, NULL},
    {0x1603, 0x09, ODT_REC, &ODObjs.o_1603_RPDO_MappingParameter, NULL},
    {0x1604, 0x09, ODT_REC, &ODObjs.o_1604_RPDO_MappingParameter, NULL},
    {0x1605, 0x09, ODT_REC, &ODObjs.o_1605_RPDO_MappingParameter, NULL},
    {0x1606, 0x09, ODT_REC, &ODObjs.o_1606_RPDO_MappingParameter, NULL},
    {0x1607, 0x09, ODT_REC, &ODObjs.o_1607_RPDO_MappingParameter, NULL},
    {0x1608, 0x09, ODT_REC, &ODObjs.o_1608_RPDO_MappingParameter, NULL},
    {0x1609, 0x09, ODT_REC, &ODObjs.o_1609_RPDO_MappingParameter, NULL},
    {0x160A, 0x09, ODT_REC, &ODObjs.o_160A_RPDO_MappingParameter, NULL},
    {0x160B, 0x09, ODT_REC, &ODObjs.o_160B_RPDO_MappingParameter, NULL},
    {0x160C, 0x09, ODT_REC, &ODObjs.o_160C_RPDO_MappingParameter, NULL},
    {0x160D, 0x09, ODT_REC, &ODObjs.o_160D_RPDO_MappingParameter, NULL},
    {0x160E, 0x09, ODT_REC, &ODObjs.o_160E_RPDO_MappingParameter, NULL},
    {0x160F, 0x09, ODT_REC, &ODObjs.o_160F_RPDO_MappingParameter, NULL},
    {0x1800, 0x07, ODT_REC, &ODObjs.o_1800_TPDO_CommunicationParameter, NULL},
    {0x1801, 0x07, ODT_REC, &ODObjs.o_1801_TPDO_CommunicationParameter, NULL},
    {0x1802, 0x07, ODT_REC, &ODObjs.o_1802_TPDO_CommunicationParameter, NULL},
    {0x1803, 0x07, ODT_REC, &ODObjs.o_1803_TPDO_CommunicationParameter, NULL},
    {0x1804, 0x07, ODT_REC, &ODObjs.o_1804_TPDO_CommunicationParameter, NULL},
    {0x1805, 0x07, ODT_REC, &ODObjs.o_1805_TPDO_CommunicationParameter, NULL},
    {0x1806, 0x07, ODT_REC, &ODObjs.o_1806_TPDO_CommunicationParameter, NULL},
    {0x1807, 0x07, ODT_REC, &ODObjs.o_1807_TPDO_CommunicationParameter, NULL},
    {0x1808, 0x07, ODT_REC, &ODObjs.o_1808_TPDO_CommunicationParameter, NULL},
    {0x1809, 0x07, ODT_REC, &ODObjs.o_1809_TPDO_CommunicationParameter, NULL},
    {0x180A, 0x07, ODT_REC, &ODObjs.o_180A_TPDO_CommunicationParameter, NULL},
    {0x180B, 0x07, ODT_REC, &ODObjs.o_180B_TPDO_CommunicationParameter, NULL},
    {0x180C, 0x07, ODT_REC, &ODObjs.o_180C_TPDO_CommunicationParameter, NULL},
    {0x180D, 0x07, ODT_REC, &ODObjs.o_180D_TPDO_CommunicationParameter, NULL},
    {0x180E, 0x07, ODT_REC, &ODObjs.o_180E_TPDO_CommunicationParameter, NULL},
    {0x180F, 0x07, ODT_REC, &ODObjs.o_180F_TPDO_CommunicationParameter, NULL},
    {0x1A00, 0x09, ODT_REC, &ODObjs.o_1A00_TPDO_MappingParameter, NULL},
    {0x1A01, 0x09, ODT_REC, &ODObjs.o_1A01_TPDO_MappingParameter, NULL},
    {0x1A02, 0x09, ODT_REC, &ODObjs.o_1A02_TPDO_MappingParameter, NULL},
    {0x1A03, 0x09, ODT_REC, &ODObjs.o_1A03_TPDO_MappingParameter, NULL},
    {0x1A04, 0x09, ODT_REC, &ODObjs.o_1A04_TPDO_MappingParameter, NULL},
    {0x1A05, 0x09, ODT_REC, &ODObjs.o_1A05_TPDO_MappingParameter, NULL},
    {0x1A06, 0x09, ODT_REC, &ODObjs.o_1A06_TPDO_MappingParameter, NULL},
    {0x1A07, 0x09, ODT_REC, &ODObjs.o_1A07_TPDO_MappingParameter, NULL},
    {0x1A08, 0x09, ODT_REC, &ODObjs.o_1A08_TPDO_MappingParameter, NULL},
    {0x1A09, 0x09, ODT_REC, &ODObjs.o_1A09_TPDO_MappingParameter, NULL},
    {0x1A0A, 0x09, ODT_REC, &ODObjs.o_1A0A_TPDO_MappingParameter, NULL},
    {0x1A0B, 0x09, ODT_REC, &ODObjs.o_1A0B_TPDO_MappingParameter, NULL},
    {0x1A0C, 0x09, ODT_REC, &ODObjs.o_1A0C_TPDO_MappingParameter, NULL},
    {0x1A0D, 0x09, ODT_REC, &ODObjs.o_1A0D_TPDO_MappingParameter, NULL},
    {0x1A0E, 0x09, ODT_REC, &ODObjs.o_1A0E_TPDO_MappingParameter, NULL},
    {0x1A0F, 0x09, ODT_REC, &ODObjs.o_1A0F_TPDO_MappingParameter, NULL},
    {0x1F80, 0x01, ODT_VAR, &ODObjs.o_1F80_nmtstartup, NULL},
    {0x2000, 0x05, ODT_REC, &ODObjs.o_2000_BUS_Management, NULL},
    {0x2010, 0x01, ODT_VAR, &ODObjs.o_2010_SCET, NULL},
    {0x2011, 0x01, ODT_VAR, &ODObjs.o_2011_UTC, NULL},
    {0x2020, 0x04, ODT_ARR, &ODObjs.o_2020_MCU_UniqueDeviceID, NULL},
    {0x2021, 0x04, ODT_REC, &ODObjs.o_2021_MCU_Calibration, NULL},
    {0x2022, 0x09, ODT_REC, &ODObjs.o_2022_MCU_Sensors, NULL},
    {0x2100, 0x01, ODT_VAR, &ODObjs.o_2100_errorStatusBits, NULL},
    {0x6000, 0x07, ODT_REC, &ODObjs.o_6000_gyroscope, NULL},
    {0x6001, 0x07, ODT_REC, &ODObjs.o_6001_acceleration, NULL},
    {0x6002, 0x01, ODT_VAR, &ODObjs.o_6002_IMU_Temperature, NULL},
    {0x6003, 0x04, ODT_REC, &ODObjs.o_6003_magnetometerPZ1, NULL},
    {0x6004, 0x04, ODT_REC, &ODObjs.o_6004_magnetometerPZ2, NULL},
    {0x6005, 0x04, ODT_REC, &ODObjs.o_6005_magnetometerMZ1, NULL},
    {0x6006, 0x04, ODT_REC, &ODObjs.o_6006_magnetometerMZ2, NULL},
    {0x6007, 0x07, ODT_REC, &ODObjs.o_6007_magnetorquer, NULL},
    {0x0000, 0x00, 0, NULL, NULL}
};

static OD_t _OD = {
    (sizeof(ODList) / sizeof(ODList[0])) - 1,
    &ODList[0]
};

OD_t *OD = &_OD;
