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
#define OD_CNT_TPDO 10

#define OD_CNT_ARR_1003 8
#define OD_CNT_ARR_1016 1

typedef struct {
    uint32_t x1000_device_type;
    uint8_t x1001_error_register;
    uint8_t x1003_predefined_error_field_sub0;
    uint32_t x1003_predefined_error_field[OD_CNT_ARR_1003];
    uint32_t x1005_cob_id_sync;
    uint32_t x1006_communication_cycle_period;
    uint32_t x1014_cob_id_emergency_message;
    uint16_t x1015_inhibit_time_emcy;
    uint8_t x1016_consumer_heartbeat_time_sub0;
    uint32_t x1016_consumer_heartbeat_time[OD_CNT_ARR_1016];
    uint16_t x1017_producer_heartbeat_time;
    struct {
        uint8_t highest_index_supported;
        uint32_t vendor_id;
        uint32_t product_code;
        uint32_t revision_number;
        uint32_t serial_number;
    } x1018_identity;
    struct {
        uint8_t highest_index_supported;
        uint32_t cob_id_client_to_server;
        uint32_t cob_id_server_to_client;
        uint32_t node_id_od_sdo_client;
    } x1200_sdo_server_parameter;
    struct {
        uint8_t highest_index_supported;
        uint32_t cob_id;
        uint8_t transmission_type;
        uint16_t inhibit_time;
        uint16_t event_timer;
        uint8_t sync_start_value;
    } x1800_tpdo_1_communication_parameters;
    struct {
        uint8_t highest_index_supported;
        uint32_t cob_id;
        uint8_t transmission_type;
        uint16_t inhibit_time;
        uint16_t event_timer;
        uint8_t sync_start_value;
    } x1801_tpdo_2_communication_parameters;
    struct {
        uint8_t highest_index_supported;
        uint32_t cob_id;
        uint8_t transmission_type;
        uint16_t inhibit_time;
        uint16_t event_timer;
        uint8_t sync_start_value;
    } x1802_tpdo_3_communication_parameters;
    struct {
        uint8_t highest_index_supported;
        uint32_t cob_id;
        uint8_t transmission_type;
        uint16_t inhibit_time;
        uint16_t event_timer;
        uint8_t sync_start_value;
    } x1803_tpdo_4_communication_parameters;
    struct {
        uint8_t highest_index_supported;
        uint32_t cob_id;
        uint8_t transmission_type;
        uint16_t inhibit_time;
        uint16_t event_timer;
        uint8_t sync_start_value;
    } x1804_tpdo_5_communication_parameters;
    struct {
        uint8_t highest_index_supported;
        uint32_t cob_id;
        uint8_t transmission_type;
        uint16_t inhibit_time;
        uint16_t event_timer;
        uint8_t sync_start_value;
    } x1805_tpdo_6_communication_parameters;
    struct {
        uint8_t highest_index_supported;
        uint32_t cob_id;
        uint8_t transmission_type;
        uint16_t inhibit_time;
        uint16_t event_timer;
        uint8_t sync_start_value;
    } x1806_tpdo_7_communication_parameters;
    struct {
        uint8_t highest_index_supported;
        uint32_t cob_id;
        uint8_t transmission_type;
        uint16_t inhibit_time;
        uint16_t event_timer;
        uint8_t sync_start_value;
    } x1807_tpdo_8_communication_parameters;
    struct {
        uint8_t highest_index_supported;
        uint32_t cob_id;
        uint8_t transmission_type;
        uint16_t inhibit_time;
        uint16_t event_timer;
        uint8_t sync_start_value;
    } x1808_tpdo_9_communication_parameters;
    struct {
        uint8_t highest_index_supported;
        uint32_t cob_id;
        uint8_t transmission_type;
        uint16_t inhibit_time;
        uint16_t event_timer;
        uint8_t sync_start_value;
    } x1809_tpdo_10_communication_parameters;
    struct {
        uint8_t highest_index_supported;
        uint32_t mapping_object_1;
        uint32_t mapping_object_2;
        uint32_t mapping_object_3;
    } x1A00_tpdo_1_mapping_parameters;
    struct {
        uint8_t highest_index_supported;
        uint32_t mapping_object_1;
        uint32_t mapping_object_2;
        uint32_t mapping_object_3;
    } x1A01_tpdo_2_mapping_parameters;
    struct {
        uint8_t highest_index_supported;
        uint32_t mapping_object_1;
    } x1A02_tpdo_3_mapping_parameters;
    struct {
        uint8_t highest_index_supported;
        uint32_t mapping_object_1;
        uint32_t mapping_object_2;
        uint32_t mapping_object_3;
    } x1A03_tpdo_4_mapping_parameters;
    struct {
        uint8_t highest_index_supported;
        uint32_t mapping_object_1;
        uint32_t mapping_object_2;
        uint32_t mapping_object_3;
    } x1A04_tpdo_5_mapping_parameters;
    struct {
        uint8_t highest_index_supported;
        uint32_t mapping_object_1;
        uint32_t mapping_object_2;
        uint32_t mapping_object_3;
    } x1A05_tpdo_6_mapping_parameters;
    struct {
        uint8_t highest_index_supported;
        uint32_t mapping_object_1;
        uint32_t mapping_object_2;
        uint32_t mapping_object_3;
    } x1A06_tpdo_7_mapping_parameters;
    struct {
        uint8_t highest_index_supported;
        uint32_t mapping_object_1;
        uint32_t mapping_object_2;
        uint32_t mapping_object_3;
    } x1A07_tpdo_8_mapping_parameters;
    struct {
        uint8_t highest_index_supported;
        uint32_t mapping_object_1;
        uint32_t mapping_object_2;
        uint32_t mapping_object_3;
    } x1A08_tpdo_9_mapping_parameters;
    struct {
        uint8_t highest_index_supported;
        uint32_t mapping_object_1;
        uint32_t mapping_object_2;
        uint32_t mapping_object_3;
    } x1A09_tpdo_10_mapping_parameters;
    uint64_t x2010_scet;
    uint64_t x2011_utc;
    uint8_t x3000_satellite_id;
    bool_t x3001_flight_mode;
    struct {
        uint8_t highest_index_supported;
        char hw_version[4];
        char configs_version[6];
        char fw_version[6];
    } x3002_versions;
    struct {
        uint8_t highest_index_supported;
        int8_t temperature;
        uint8_t vrefint;
    } x3003_system;
    struct {
        uint8_t highest_index_supported;
        int16_t pitch_rate;
        int16_t yaw_rate;
        int16_t roll_rate;
        uint16_t pitch_rate_raw;
        uint16_t yaw_rate_raw;
        uint16_t roll_rate_raw;
    } x4000_gyroscope;
    struct {
        uint8_t highest_index_supported;
        int16_t x;
        int16_t y;
        int16_t z;
        uint16_t x_raw;
        uint16_t y_raw;
        uint16_t z_raw;
    } x4001_accelerometer;
    int8_t x4002_temperature;
    struct {
        uint8_t highest_index_supported;
        int16_t x;
        int16_t y;
        int16_t z;
    } x4003_pos_z_magnetometer_1;
    struct {
        uint8_t highest_index_supported;
        int16_t x;
        int16_t y;
        int16_t z;
    } x4004_pos_z_magnetometer_2;
    struct {
        uint8_t highest_index_supported;
        int16_t x;
        int16_t y;
        int16_t z;
    } x4005_min_z_magnetometer_1;
    struct {
        uint8_t highest_index_supported;
        int16_t x;
        int16_t y;
        int16_t z;
    } x4006_min_z_magnetometer_2;
    struct {
        uint8_t highest_index_supported;
        int32_t x;
        int32_t y;
        int16_t z;
    } x4007_magnetorquer_current;
    struct {
        uint8_t highest_index_supported;
        int32_t x;
        int32_t y;
        int16_t z;
    } x4008_magnetorquer_current_set;
    struct {
        uint8_t highest_index_supported;
        int32_t x;
        int32_t y;
        int16_t z;
    } x4009_magnetorquer_pwm_percent;
} OD_RAM_t;

#ifndef OD_ATTR_RAM
#define OD_ATTR_RAM
#endif
extern OD_ATTR_RAM OD_RAM_t OD_RAM;

#ifndef OD_ATTR_OD
#define OD_ATTR_OD
#endif
extern OD_ATTR_OD OD_t *OD;

#define OD_ENTRY_H1000 &OD->list[0]
#define OD_ENTRY_H1001 &OD->list[1]
#define OD_ENTRY_H1003 &OD->list[2]
#define OD_ENTRY_H1005 &OD->list[3]
#define OD_ENTRY_H1006 &OD->list[4]
#define OD_ENTRY_H1014 &OD->list[5]
#define OD_ENTRY_H1015 &OD->list[6]
#define OD_ENTRY_H1016 &OD->list[7]
#define OD_ENTRY_H1017 &OD->list[8]
#define OD_ENTRY_H1018 &OD->list[9]
#define OD_ENTRY_H1200 &OD->list[10]
#define OD_ENTRY_H1800 &OD->list[11]
#define OD_ENTRY_H1801 &OD->list[12]
#define OD_ENTRY_H1802 &OD->list[13]
#define OD_ENTRY_H1803 &OD->list[14]
#define OD_ENTRY_H1804 &OD->list[15]
#define OD_ENTRY_H1805 &OD->list[16]
#define OD_ENTRY_H1806 &OD->list[17]
#define OD_ENTRY_H1807 &OD->list[18]
#define OD_ENTRY_H1808 &OD->list[19]
#define OD_ENTRY_H1809 &OD->list[20]
#define OD_ENTRY_H1A00 &OD->list[21]
#define OD_ENTRY_H1A01 &OD->list[22]
#define OD_ENTRY_H1A02 &OD->list[23]
#define OD_ENTRY_H1A03 &OD->list[24]
#define OD_ENTRY_H1A04 &OD->list[25]
#define OD_ENTRY_H1A05 &OD->list[26]
#define OD_ENTRY_H1A06 &OD->list[27]
#define OD_ENTRY_H1A07 &OD->list[28]
#define OD_ENTRY_H1A08 &OD->list[29]
#define OD_ENTRY_H1A09 &OD->list[30]
#define OD_ENTRY_H2010 &OD->list[31]
#define OD_ENTRY_H2011 &OD->list[32]
#define OD_ENTRY_H3000 &OD->list[33]
#define OD_ENTRY_H3001 &OD->list[34]
#define OD_ENTRY_H3002 &OD->list[35]
#define OD_ENTRY_H3003 &OD->list[36]
#define OD_ENTRY_H4000 &OD->list[37]
#define OD_ENTRY_H4001 &OD->list[38]
#define OD_ENTRY_H4002 &OD->list[39]
#define OD_ENTRY_H4003 &OD->list[40]
#define OD_ENTRY_H4004 &OD->list[41]
#define OD_ENTRY_H4005 &OD->list[42]
#define OD_ENTRY_H4006 &OD->list[43]
#define OD_ENTRY_H4007 &OD->list[44]
#define OD_ENTRY_H4008 &OD->list[45]
#define OD_ENTRY_H4009 &OD->list[46]

#define OD_ENTRY_H1000_DEVICE_TYPE &OD->list[0]
#define OD_ENTRY_H1001_ERROR_REGISTER &OD->list[1]
#define OD_ENTRY_H1003_PREDEFINED_ERROR_FIELD &OD->list[2]
#define OD_ENTRY_H1005_COB_ID_SYNC &OD->list[3]
#define OD_ENTRY_H1006_COMMUNICATION_CYCLE_PERIOD &OD->list[4]
#define OD_ENTRY_H1014_COB_ID_EMERGENCY_MESSAGE &OD->list[5]
#define OD_ENTRY_H1015_INHIBIT_TIME_EMCY &OD->list[6]
#define OD_ENTRY_H1016_CONSUMER_HEARTBEAT_TIME &OD->list[7]
#define OD_ENTRY_H1017_PRODUCER_HEARTBEAT_TIME &OD->list[8]
#define OD_ENTRY_H1018_IDENTITY &OD->list[9]
#define OD_ENTRY_H1200_SDO_SERVER_PARAMETER &OD->list[10]
#define OD_ENTRY_H1800_TPDO_1_COMMUNICATION_PARAMETERS &OD->list[11]
#define OD_ENTRY_H1801_TPDO_2_COMMUNICATION_PARAMETERS &OD->list[12]
#define OD_ENTRY_H1802_TPDO_3_COMMUNICATION_PARAMETERS &OD->list[13]
#define OD_ENTRY_H1803_TPDO_4_COMMUNICATION_PARAMETERS &OD->list[14]
#define OD_ENTRY_H1804_TPDO_5_COMMUNICATION_PARAMETERS &OD->list[15]
#define OD_ENTRY_H1805_TPDO_6_COMMUNICATION_PARAMETERS &OD->list[16]
#define OD_ENTRY_H1806_TPDO_7_COMMUNICATION_PARAMETERS &OD->list[17]
#define OD_ENTRY_H1807_TPDO_8_COMMUNICATION_PARAMETERS &OD->list[18]
#define OD_ENTRY_H1808_TPDO_9_COMMUNICATION_PARAMETERS &OD->list[19]
#define OD_ENTRY_H1809_TPDO_10_COMMUNICATION_PARAMETERS &OD->list[20]
#define OD_ENTRY_H1A00_TPDO_1_MAPPING_PARAMETERS &OD->list[21]
#define OD_ENTRY_H1A01_TPDO_2_MAPPING_PARAMETERS &OD->list[22]
#define OD_ENTRY_H1A02_TPDO_3_MAPPING_PARAMETERS &OD->list[23]
#define OD_ENTRY_H1A03_TPDO_4_MAPPING_PARAMETERS &OD->list[24]
#define OD_ENTRY_H1A04_TPDO_5_MAPPING_PARAMETERS &OD->list[25]
#define OD_ENTRY_H1A05_TPDO_6_MAPPING_PARAMETERS &OD->list[26]
#define OD_ENTRY_H1A06_TPDO_7_MAPPING_PARAMETERS &OD->list[27]
#define OD_ENTRY_H1A07_TPDO_8_MAPPING_PARAMETERS &OD->list[28]
#define OD_ENTRY_H1A08_TPDO_9_MAPPING_PARAMETERS &OD->list[29]
#define OD_ENTRY_H1A09_TPDO_10_MAPPING_PARAMETERS &OD->list[30]
#define OD_ENTRY_H2010_SCET &OD->list[31]
#define OD_ENTRY_H2011_UTC &OD->list[32]
#define OD_ENTRY_H3000_SATELLITE_ID &OD->list[33]
#define OD_ENTRY_H3001_FLIGHT_MODE &OD->list[34]
#define OD_ENTRY_H3002_VERSIONS &OD->list[35]
#define OD_ENTRY_H3003_SYSTEM &OD->list[36]
#define OD_ENTRY_H4000_GYROSCOPE &OD->list[37]
#define OD_ENTRY_H4001_ACCELEROMETER &OD->list[38]
#define OD_ENTRY_H4002_TEMPERATURE &OD->list[39]
#define OD_ENTRY_H4003_POS_Z_MAGNETOMETER_1 &OD->list[40]
#define OD_ENTRY_H4004_POS_Z_MAGNETOMETER_2 &OD->list[41]
#define OD_ENTRY_H4005_MIN_Z_MAGNETOMETER_1 &OD->list[42]
#define OD_ENTRY_H4006_MIN_Z_MAGNETOMETER_2 &OD->list[43]
#define OD_ENTRY_H4007_MAGNETORQUER_CURRENT &OD->list[44]
#define OD_ENTRY_H4008_MAGNETORQUER_CURRENT_SET &OD->list[45]
#define OD_ENTRY_H4009_MAGNETORQUER_PWM_PERCENT &OD->list[46]

#define OD_INDEX_SCET 0x2010

#define OD_INDEX_UTC 0x2011

#define OD_INDEX_SATELLITE_ID 0x3000

#define OD_INDEX_FLIGHT_MODE 0x3001

#define OD_INDEX_VERSIONS 0x3002
#define OD_SUBINDEX_VERSIONS_HW_VERSION 0x1
#define OD_SUBINDEX_VERSIONS_CONFIGS_VERSION 0x2
#define OD_SUBINDEX_VERSIONS_FW_VERSION 0x4

#define OD_INDEX_SYSTEM 0x3003
#define OD_SUBINDEX_SYSTEM_TEMPERATURE 0x7
#define OD_SUBINDEX_SYSTEM_VREFINT 0x8

#define OD_INDEX_GYROSCOPE 0x4000
#define OD_SUBINDEX_GYROSCOPE_PITCH_RATE 0x1
#define OD_SUBINDEX_GYROSCOPE_YAW_RATE 0x2
#define OD_SUBINDEX_GYROSCOPE_ROLL_RATE 0x3
#define OD_SUBINDEX_GYROSCOPE_PITCH_RATE_RAW 0x4
#define OD_SUBINDEX_GYROSCOPE_YAW_RATE_RAW 0x5
#define OD_SUBINDEX_GYROSCOPE_ROLL_RATE_RAW 0x6

#define OD_INDEX_ACCELEROMETER 0x4001
#define OD_SUBINDEX_ACCELEROMETER_X 0x1
#define OD_SUBINDEX_ACCELEROMETER_Y 0x2
#define OD_SUBINDEX_ACCELEROMETER_Z 0x3
#define OD_SUBINDEX_ACCELEROMETER_X_RAW 0x4
#define OD_SUBINDEX_ACCELEROMETER_Y_RAW 0x5
#define OD_SUBINDEX_ACCELEROMETER_Z_RAW 0x6

#define OD_INDEX_TEMPERATURE 0x4002

#define OD_INDEX_POS_Z_MAGNETOMETER_1 0x4003
#define OD_SUBINDEX_POS_Z_MAGNETOMETER_1_X 0x1
#define OD_SUBINDEX_POS_Z_MAGNETOMETER_1_Y 0x2
#define OD_SUBINDEX_POS_Z_MAGNETOMETER_1_Z 0x3

#define OD_INDEX_POS_Z_MAGNETOMETER_2 0x4004
#define OD_SUBINDEX_POS_Z_MAGNETOMETER_2_X 0x1
#define OD_SUBINDEX_POS_Z_MAGNETOMETER_2_Y 0x2
#define OD_SUBINDEX_POS_Z_MAGNETOMETER_2_Z 0x3

#define OD_INDEX_MIN_Z_MAGNETOMETER_1 0x4005
#define OD_SUBINDEX_MIN_Z_MAGNETOMETER_1_X 0x1
#define OD_SUBINDEX_MIN_Z_MAGNETOMETER_1_Y 0x2
#define OD_SUBINDEX_MIN_Z_MAGNETOMETER_1_Z 0x3

#define OD_INDEX_MIN_Z_MAGNETOMETER_2 0x4006
#define OD_SUBINDEX_MIN_Z_MAGNETOMETER_2_X 0x1
#define OD_SUBINDEX_MIN_Z_MAGNETOMETER_2_Y 0x2
#define OD_SUBINDEX_MIN_Z_MAGNETOMETER_2_Z 0x3

#define OD_INDEX_MAGNETORQUER_CURRENT 0x4007
#define OD_SUBINDEX_MAGNETORQUER_CURRENT_X 0x1
#define OD_SUBINDEX_MAGNETORQUER_CURRENT_Y 0x2
#define OD_SUBINDEX_MAGNETORQUER_CURRENT_Z 0x3

#define OD_INDEX_MAGNETORQUER_CURRENT_SET 0x4008
#define OD_SUBINDEX_MAGNETORQUER_CURRENT_SET_X 0x1
#define OD_SUBINDEX_MAGNETORQUER_CURRENT_SET_Y 0x2
#define OD_SUBINDEX_MAGNETORQUER_CURRENT_SET_Z 0x3

#define OD_INDEX_MAGNETORQUER_PWM_PERCENT 0x4009
#define OD_SUBINDEX_MAGNETORQUER_PWM_PERCENT_X 0x1
#define OD_SUBINDEX_MAGNETORQUER_PWM_PERCENT_Y 0x2
#define OD_SUBINDEX_MAGNETORQUER_PWM_PERCENT_Z 0x3

#endif /* OD_H */
