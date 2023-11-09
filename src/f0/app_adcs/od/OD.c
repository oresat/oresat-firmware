#define OD_DEFINITION
#include "301/CO_ODinterface.h"
#include "OD.h"

#if CO_VERSION_MAJOR < 4
#error This file is only comatible with CANopenNode v4 and above
#endif

OD_ATTR_RAM OD_RAM_t OD_RAM = {
    .x1000_device_type = 0x0,
    .x1001_error_register = 0x0,
    .x1003_predefined_error_field_sub0 = 8,
    .x1003_predefined_error_field = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    .x1005_cob_id_sync = 0x80,
    .x1006_communication_cycle_period = 0x0,
    .x1014_cob_id_emergency_message = 0xB8,
    .x1015_inhibit_time_emcy = 0x0,
    .x1016_consumer_heartbeat_time_sub0 = 1,
    .x1016_consumer_heartbeat_time = {0x3E8},
    .x1017_producer_heartbeat_time = 0x3E8,
    .x1018_identity = {
        .highest_index_supported = 0x4,
        .vendor_id = 0x0,
        .product_code = 0x0,
        .revision_number = 0x0,
        .serial_number = 0x0,
    },
    .x1200_sdo_server_parameter = {
        .highest_index_supported = 0x3,
        .cob_id_client_to_server = 0x80000000,
        .cob_id_server_to_client = 0x80000000,
        .node_id_od_sdo_client = 0x1,
    },
    .x1800_tpdo_1_communication_parameters = {
        .highest_index_supported = 0x6,
        .cob_id = 0x180,
        .transmission_type = 0xFE,
        .inhibit_time = 0x0,
        .event_timer = 0x3E8,
        .sync_start_value = 0x0,
    },
    .x1801_tpdo_2_communication_parameters = {
        .highest_index_supported = 0x6,
        .cob_id = 0x280,
        .transmission_type = 0xFE,
        .inhibit_time = 0x0,
        .event_timer = 0x3E8,
        .sync_start_value = 0x0,
    },
    .x1802_tpdo_3_communication_parameters = {
        .highest_index_supported = 0x6,
        .cob_id = 0x380,
        .transmission_type = 0xFE,
        .inhibit_time = 0x0,
        .event_timer = 0x3E8,
        .sync_start_value = 0x0,
    },
    .x1803_tpdo_4_communication_parameters = {
        .highest_index_supported = 0x6,
        .cob_id = 0x480,
        .transmission_type = 0xFE,
        .inhibit_time = 0x0,
        .event_timer = 0x3E8,
        .sync_start_value = 0x0,
    },
    .x1804_tpdo_5_communication_parameters = {
        .highest_index_supported = 0x6,
        .cob_id = 0x180,
        .transmission_type = 0xFE,
        .inhibit_time = 0x0,
        .event_timer = 0x3E8,
        .sync_start_value = 0x0,
    },
    .x1805_tpdo_6_communication_parameters = {
        .highest_index_supported = 0x6,
        .cob_id = 0x280,
        .transmission_type = 0xFE,
        .inhibit_time = 0x0,
        .event_timer = 0x3E8,
        .sync_start_value = 0x0,
    },
    .x1806_tpdo_7_communication_parameters = {
        .highest_index_supported = 0x6,
        .cob_id = 0x380,
        .transmission_type = 0xFE,
        .inhibit_time = 0x0,
        .event_timer = 0x3E8,
        .sync_start_value = 0x0,
    },
    .x1807_tpdo_8_communication_parameters = {
        .highest_index_supported = 0x6,
        .cob_id = 0x480,
        .transmission_type = 0xFE,
        .inhibit_time = 0x0,
        .event_timer = 0x3E8,
        .sync_start_value = 0x0,
    },
    .x1808_tpdo_9_communication_parameters = {
        .highest_index_supported = 0x6,
        .cob_id = 0x180,
        .transmission_type = 0xFE,
        .inhibit_time = 0x0,
        .event_timer = 0x0,
        .sync_start_value = 0x0,
    },
    .x1809_tpdo_10_communication_parameters = {
        .highest_index_supported = 0x6,
        .cob_id = 0x280,
        .transmission_type = 0xFE,
        .inhibit_time = 0x0,
        .event_timer = 0x3E8,
        .sync_start_value = 0x0,
    },
    .x1A00_tpdo_1_mapping_parameters = {
        .highest_index_supported = 0x3,
        .mapping_object_1 = 0x40000110,
        .mapping_object_2 = 0x40000210,
        .mapping_object_3 = 0x40000310,
    },
    .x1A01_tpdo_2_mapping_parameters = {
        .highest_index_supported = 0x3,
        .mapping_object_1 = 0x40010110,
        .mapping_object_2 = 0x40010210,
        .mapping_object_3 = 0x40010310,
    },
    .x1A02_tpdo_3_mapping_parameters = {
        .highest_index_supported = 0x1,
        .mapping_object_1 = 0x40020008,
    },
    .x1A03_tpdo_4_mapping_parameters = {
        .highest_index_supported = 0x3,
        .mapping_object_1 = 0x40030110,
        .mapping_object_2 = 0x40030210,
        .mapping_object_3 = 0x40030310,
    },
    .x1A04_tpdo_5_mapping_parameters = {
        .highest_index_supported = 0x3,
        .mapping_object_1 = 0x40040110,
        .mapping_object_2 = 0x40040210,
        .mapping_object_3 = 0x40040310,
    },
    .x1A05_tpdo_6_mapping_parameters = {
        .highest_index_supported = 0x3,
        .mapping_object_1 = 0x40050110,
        .mapping_object_2 = 0x40050210,
        .mapping_object_3 = 0x40050310,
    },
    .x1A06_tpdo_7_mapping_parameters = {
        .highest_index_supported = 0x3,
        .mapping_object_1 = 0x40060110,
        .mapping_object_2 = 0x40060210,
        .mapping_object_3 = 0x40060310,
    },
    .x1A07_tpdo_8_mapping_parameters = {
        .highest_index_supported = 0x3,
        .mapping_object_1 = 0x40070120,
        .mapping_object_2 = 0x40070220,
        .mapping_object_3 = 0x40070310,
    },
    .x1A08_tpdo_9_mapping_parameters = {
        .highest_index_supported = 0x3,
        .mapping_object_1 = 0x40080120,
        .mapping_object_2 = 0x40080220,
        .mapping_object_3 = 0x40080310,
    },
    .x1A09_tpdo_10_mapping_parameters = {
        .highest_index_supported = 0x3,
        .mapping_object_1 = 0x40090120,
        .mapping_object_2 = 0x40090220,
        .mapping_object_3 = 0x40090310,
    },
    .x2010_scet = 0x0,
    .x2011_utc = 0x0,
    .x3000_satellite_id = 0x2,
    .x3001_flight_mode = 1,
    .x3002_versions = {
        .highest_index_supported = 0x4,
        .hw_version = {'0', '.', '0', 0}, 
        .configs_version = {'0', '.', '1', '.', '0', 0}, 
        .fw_version = {'0', '.', '0', '.', '0', 0}, 
    },
    .x3003_system = {
        .highest_index_supported = 0x8,
        .temperature = 0x0,
        .vrefint = 0x0,
    },
    .x4000_gyroscope = {
        .highest_index_supported = 0x6,
        .pitch_rate = 0x0,
        .yaw_rate = 0x0,
        .roll_rate = 0x0,
        .pitch_rate_raw = 0x0,
        .yaw_rate_raw = 0x0,
        .roll_rate_raw = 0x0,
    },
    .x4001_accelerometer = {
        .highest_index_supported = 0x6,
        .x = 0x0,
        .y = 0x0,
        .z = 0x0,
        .x_raw = 0x0,
        .y_raw = 0x0,
        .z_raw = 0x0,
    },
    .x4002_temperature = 0x0,
    .x4003_pos_z_magnetometer_1 = {
        .highest_index_supported = 0x3,
        .x = 0x0,
        .y = 0x0,
        .z = 0x0,
    },
    .x4004_pos_z_magnetometer_2 = {
        .highest_index_supported = 0x3,
        .x = 0x0,
        .y = 0x0,
        .z = 0x0,
    },
    .x4005_min_z_magnetometer_1 = {
        .highest_index_supported = 0x3,
        .x = 0x0,
        .y = 0x0,
        .z = 0x0,
    },
    .x4006_min_z_magnetometer_2 = {
        .highest_index_supported = 0x3,
        .x = 0x0,
        .y = 0x0,
        .z = 0x0,
    },
    .x4007_magnetorquer_current = {
        .highest_index_supported = 0x3,
        .x = 0x0,
        .y = 0x0,
        .z = 0x0,
    },
    .x4008_magnetorquer_current_set = {
        .highest_index_supported = 0x3,
        .x = 0x0,
        .y = 0x0,
        .z = 0x0,
    },
    .x4009_magnetorquer_pwm_percent = {
        .highest_index_supported = 0x3,
        .x = 0x0,
        .y = 0x0,
        .z = 0x0,
    },
};

typedef struct {
    OD_obj_var_t o_1000_device_type;
    OD_obj_var_t o_1001_error_register;
    OD_obj_array_t o_1003_predefined_error_field;
    OD_obj_var_t o_1005_cob_id_sync;
    OD_obj_var_t o_1006_communication_cycle_period;
    OD_obj_var_t o_1014_cob_id_emergency_message;
    OD_obj_var_t o_1015_inhibit_time_emcy;
    OD_obj_array_t o_1016_consumer_heartbeat_time;
    OD_obj_var_t o_1017_producer_heartbeat_time;
    OD_obj_record_t o_1018_identity[5];
    OD_obj_record_t o_1200_sdo_server_parameter[4];
    OD_obj_record_t o_1800_tpdo_1_communication_parameters[6];
    OD_obj_record_t o_1801_tpdo_2_communication_parameters[6];
    OD_obj_record_t o_1802_tpdo_3_communication_parameters[6];
    OD_obj_record_t o_1803_tpdo_4_communication_parameters[6];
    OD_obj_record_t o_1804_tpdo_5_communication_parameters[6];
    OD_obj_record_t o_1805_tpdo_6_communication_parameters[6];
    OD_obj_record_t o_1806_tpdo_7_communication_parameters[6];
    OD_obj_record_t o_1807_tpdo_8_communication_parameters[6];
    OD_obj_record_t o_1808_tpdo_9_communication_parameters[6];
    OD_obj_record_t o_1809_tpdo_10_communication_parameters[6];
    OD_obj_record_t o_1A00_tpdo_1_mapping_parameters[4];
    OD_obj_record_t o_1A01_tpdo_2_mapping_parameters[4];
    OD_obj_record_t o_1A02_tpdo_3_mapping_parameters[2];
    OD_obj_record_t o_1A03_tpdo_4_mapping_parameters[4];
    OD_obj_record_t o_1A04_tpdo_5_mapping_parameters[4];
    OD_obj_record_t o_1A05_tpdo_6_mapping_parameters[4];
    OD_obj_record_t o_1A06_tpdo_7_mapping_parameters[4];
    OD_obj_record_t o_1A07_tpdo_8_mapping_parameters[4];
    OD_obj_record_t o_1A08_tpdo_9_mapping_parameters[4];
    OD_obj_record_t o_1A09_tpdo_10_mapping_parameters[4];
    OD_obj_var_t o_2010_scet;
    OD_obj_var_t o_2011_utc;
    OD_obj_var_t o_3000_satellite_id;
    OD_obj_var_t o_3001_flight_mode;
    OD_obj_record_t o_3002_versions[4];
    OD_obj_record_t o_3003_system[3];
    OD_obj_record_t o_4000_gyroscope[7];
    OD_obj_record_t o_4001_accelerometer[7];
    OD_obj_var_t o_4002_temperature;
    OD_obj_record_t o_4003_pos_z_magnetometer_1[4];
    OD_obj_record_t o_4004_pos_z_magnetometer_2[4];
    OD_obj_record_t o_4005_min_z_magnetometer_1[4];
    OD_obj_record_t o_4006_min_z_magnetometer_2[4];
    OD_obj_record_t o_4007_magnetorquer_current[4];
    OD_obj_record_t o_4008_magnetorquer_current_set[4];
    OD_obj_record_t o_4009_magnetorquer_pwm_percent[4];
} ODObjs_t;

static CO_PROGMEM ODObjs_t ODObjs = {
    .o_1000_device_type = {
        .dataOrig = &OD_RAM.x1000_device_type,
        .attribute = ODA_SDO_R | ODA_MB,
        .dataLength = 4
    },
    .o_1001_error_register = {
        .dataOrig = &OD_RAM.x1001_error_register,
        .attribute = ODA_SDO_R,
        .dataLength = 1
    },
    .o_1003_predefined_error_field = {
        .dataOrig0 = &OD_RAM.x1003_predefined_error_field_sub0,
        .dataOrig = &OD_RAM.x1003_predefined_error_field[0],
        .attribute0 = ODA_SDO_R,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataElementLength = 4,
        .dataElementSizeof = sizeof(uint32_t),
    },
    .o_1005_cob_id_sync = {
        .dataOrig = &OD_RAM.x1005_cob_id_sync,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataLength = 4
    },
    .o_1006_communication_cycle_period = {
        .dataOrig = &OD_RAM.x1006_communication_cycle_period,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataLength = 4
    },
    .o_1014_cob_id_emergency_message = {
        .dataOrig = &OD_RAM.x1014_cob_id_emergency_message,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataLength = 4
    },
    .o_1015_inhibit_time_emcy = {
        .dataOrig = &OD_RAM.x1015_inhibit_time_emcy,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataLength = 2
    },
    .o_1016_consumer_heartbeat_time = {
        .dataOrig0 = &OD_RAM.x1016_consumer_heartbeat_time_sub0,
        .dataOrig = &OD_RAM.x1016_consumer_heartbeat_time[0],
        .attribute0 = ODA_SDO_R,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataElementLength = 4,
        .dataElementSizeof = sizeof(uint32_t),
    },
    .o_1017_producer_heartbeat_time = {
        .dataOrig = &OD_RAM.x1017_producer_heartbeat_time,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataLength = 2
    },
    .o_1018_identity = {
        {
            .dataOrig = &OD_RAM.x1018_identity.highest_index_supported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x1018_identity.vendor_id,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x1018_identity.product_code,
            .subIndex = 2,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x1018_identity.revision_number,
            .subIndex = 3,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x1018_identity.serial_number,
            .subIndex = 4,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
    },
    .o_1200_sdo_server_parameter = {
        {
            .dataOrig = &OD_RAM.x1200_sdo_server_parameter.highest_index_supported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x1200_sdo_server_parameter.cob_id_client_to_server,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x1200_sdo_server_parameter.cob_id_server_to_client,
            .subIndex = 2,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x1200_sdo_server_parameter.node_id_od_sdo_client,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_MB,
            .dataLength = 4
        },
    },
    .o_1800_tpdo_1_communication_parameters = {
        {
            .dataOrig = &OD_RAM.x1800_tpdo_1_communication_parameters.highest_index_supported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x1800_tpdo_1_communication_parameters.cob_id,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x1800_tpdo_1_communication_parameters.transmission_type,
            .subIndex = 2,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x1800_tpdo_1_communication_parameters.inhibit_time,
            .subIndex = 3,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x1800_tpdo_1_communication_parameters.event_timer,
            .subIndex = 5,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x1800_tpdo_1_communication_parameters.sync_start_value,
            .subIndex = 6,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
    },
    .o_1801_tpdo_2_communication_parameters = {
        {
            .dataOrig = &OD_RAM.x1801_tpdo_2_communication_parameters.highest_index_supported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x1801_tpdo_2_communication_parameters.cob_id,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x1801_tpdo_2_communication_parameters.transmission_type,
            .subIndex = 2,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x1801_tpdo_2_communication_parameters.inhibit_time,
            .subIndex = 3,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x1801_tpdo_2_communication_parameters.event_timer,
            .subIndex = 5,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x1801_tpdo_2_communication_parameters.sync_start_value,
            .subIndex = 6,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
    },
    .o_1802_tpdo_3_communication_parameters = {
        {
            .dataOrig = &OD_RAM.x1802_tpdo_3_communication_parameters.highest_index_supported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x1802_tpdo_3_communication_parameters.cob_id,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x1802_tpdo_3_communication_parameters.transmission_type,
            .subIndex = 2,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x1802_tpdo_3_communication_parameters.inhibit_time,
            .subIndex = 3,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x1802_tpdo_3_communication_parameters.event_timer,
            .subIndex = 5,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x1802_tpdo_3_communication_parameters.sync_start_value,
            .subIndex = 6,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
    },
    .o_1803_tpdo_4_communication_parameters = {
        {
            .dataOrig = &OD_RAM.x1803_tpdo_4_communication_parameters.highest_index_supported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x1803_tpdo_4_communication_parameters.cob_id,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x1803_tpdo_4_communication_parameters.transmission_type,
            .subIndex = 2,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x1803_tpdo_4_communication_parameters.inhibit_time,
            .subIndex = 3,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x1803_tpdo_4_communication_parameters.event_timer,
            .subIndex = 5,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x1803_tpdo_4_communication_parameters.sync_start_value,
            .subIndex = 6,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
    },
    .o_1804_tpdo_5_communication_parameters = {
        {
            .dataOrig = &OD_RAM.x1804_tpdo_5_communication_parameters.highest_index_supported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x1804_tpdo_5_communication_parameters.cob_id,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x1804_tpdo_5_communication_parameters.transmission_type,
            .subIndex = 2,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x1804_tpdo_5_communication_parameters.inhibit_time,
            .subIndex = 3,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x1804_tpdo_5_communication_parameters.event_timer,
            .subIndex = 5,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x1804_tpdo_5_communication_parameters.sync_start_value,
            .subIndex = 6,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
    },
    .o_1805_tpdo_6_communication_parameters = {
        {
            .dataOrig = &OD_RAM.x1805_tpdo_6_communication_parameters.highest_index_supported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x1805_tpdo_6_communication_parameters.cob_id,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x1805_tpdo_6_communication_parameters.transmission_type,
            .subIndex = 2,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x1805_tpdo_6_communication_parameters.inhibit_time,
            .subIndex = 3,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x1805_tpdo_6_communication_parameters.event_timer,
            .subIndex = 5,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x1805_tpdo_6_communication_parameters.sync_start_value,
            .subIndex = 6,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
    },
    .o_1806_tpdo_7_communication_parameters = {
        {
            .dataOrig = &OD_RAM.x1806_tpdo_7_communication_parameters.highest_index_supported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x1806_tpdo_7_communication_parameters.cob_id,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x1806_tpdo_7_communication_parameters.transmission_type,
            .subIndex = 2,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x1806_tpdo_7_communication_parameters.inhibit_time,
            .subIndex = 3,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x1806_tpdo_7_communication_parameters.event_timer,
            .subIndex = 5,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x1806_tpdo_7_communication_parameters.sync_start_value,
            .subIndex = 6,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
    },
    .o_1807_tpdo_8_communication_parameters = {
        {
            .dataOrig = &OD_RAM.x1807_tpdo_8_communication_parameters.highest_index_supported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x1807_tpdo_8_communication_parameters.cob_id,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x1807_tpdo_8_communication_parameters.transmission_type,
            .subIndex = 2,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x1807_tpdo_8_communication_parameters.inhibit_time,
            .subIndex = 3,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x1807_tpdo_8_communication_parameters.event_timer,
            .subIndex = 5,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x1807_tpdo_8_communication_parameters.sync_start_value,
            .subIndex = 6,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
    },
    .o_1808_tpdo_9_communication_parameters = {
        {
            .dataOrig = &OD_RAM.x1808_tpdo_9_communication_parameters.highest_index_supported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x1808_tpdo_9_communication_parameters.cob_id,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x1808_tpdo_9_communication_parameters.transmission_type,
            .subIndex = 2,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x1808_tpdo_9_communication_parameters.inhibit_time,
            .subIndex = 3,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x1808_tpdo_9_communication_parameters.event_timer,
            .subIndex = 5,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x1808_tpdo_9_communication_parameters.sync_start_value,
            .subIndex = 6,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
    },
    .o_1809_tpdo_10_communication_parameters = {
        {
            .dataOrig = &OD_RAM.x1809_tpdo_10_communication_parameters.highest_index_supported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x1809_tpdo_10_communication_parameters.cob_id,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x1809_tpdo_10_communication_parameters.transmission_type,
            .subIndex = 2,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x1809_tpdo_10_communication_parameters.inhibit_time,
            .subIndex = 3,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x1809_tpdo_10_communication_parameters.event_timer,
            .subIndex = 5,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x1809_tpdo_10_communication_parameters.sync_start_value,
            .subIndex = 6,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
    },
    .o_1A00_tpdo_1_mapping_parameters = {
        {
            .dataOrig = &OD_RAM.x1A00_tpdo_1_mapping_parameters.highest_index_supported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x1A00_tpdo_1_mapping_parameters.mapping_object_1,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x1A00_tpdo_1_mapping_parameters.mapping_object_2,
            .subIndex = 2,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x1A00_tpdo_1_mapping_parameters.mapping_object_3,
            .subIndex = 3,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
    },
    .o_1A01_tpdo_2_mapping_parameters = {
        {
            .dataOrig = &OD_RAM.x1A01_tpdo_2_mapping_parameters.highest_index_supported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x1A01_tpdo_2_mapping_parameters.mapping_object_1,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x1A01_tpdo_2_mapping_parameters.mapping_object_2,
            .subIndex = 2,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x1A01_tpdo_2_mapping_parameters.mapping_object_3,
            .subIndex = 3,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
    },
    .o_1A02_tpdo_3_mapping_parameters = {
        {
            .dataOrig = &OD_RAM.x1A02_tpdo_3_mapping_parameters.highest_index_supported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x1A02_tpdo_3_mapping_parameters.mapping_object_1,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
    },
    .o_1A03_tpdo_4_mapping_parameters = {
        {
            .dataOrig = &OD_RAM.x1A03_tpdo_4_mapping_parameters.highest_index_supported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x1A03_tpdo_4_mapping_parameters.mapping_object_1,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x1A03_tpdo_4_mapping_parameters.mapping_object_2,
            .subIndex = 2,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x1A03_tpdo_4_mapping_parameters.mapping_object_3,
            .subIndex = 3,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
    },
    .o_1A04_tpdo_5_mapping_parameters = {
        {
            .dataOrig = &OD_RAM.x1A04_tpdo_5_mapping_parameters.highest_index_supported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x1A04_tpdo_5_mapping_parameters.mapping_object_1,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x1A04_tpdo_5_mapping_parameters.mapping_object_2,
            .subIndex = 2,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x1A04_tpdo_5_mapping_parameters.mapping_object_3,
            .subIndex = 3,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
    },
    .o_1A05_tpdo_6_mapping_parameters = {
        {
            .dataOrig = &OD_RAM.x1A05_tpdo_6_mapping_parameters.highest_index_supported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x1A05_tpdo_6_mapping_parameters.mapping_object_1,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x1A05_tpdo_6_mapping_parameters.mapping_object_2,
            .subIndex = 2,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x1A05_tpdo_6_mapping_parameters.mapping_object_3,
            .subIndex = 3,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
    },
    .o_1A06_tpdo_7_mapping_parameters = {
        {
            .dataOrig = &OD_RAM.x1A06_tpdo_7_mapping_parameters.highest_index_supported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x1A06_tpdo_7_mapping_parameters.mapping_object_1,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x1A06_tpdo_7_mapping_parameters.mapping_object_2,
            .subIndex = 2,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x1A06_tpdo_7_mapping_parameters.mapping_object_3,
            .subIndex = 3,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
    },
    .o_1A07_tpdo_8_mapping_parameters = {
        {
            .dataOrig = &OD_RAM.x1A07_tpdo_8_mapping_parameters.highest_index_supported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x1A07_tpdo_8_mapping_parameters.mapping_object_1,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x1A07_tpdo_8_mapping_parameters.mapping_object_2,
            .subIndex = 2,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x1A07_tpdo_8_mapping_parameters.mapping_object_3,
            .subIndex = 3,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
    },
    .o_1A08_tpdo_9_mapping_parameters = {
        {
            .dataOrig = &OD_RAM.x1A08_tpdo_9_mapping_parameters.highest_index_supported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x1A08_tpdo_9_mapping_parameters.mapping_object_1,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x1A08_tpdo_9_mapping_parameters.mapping_object_2,
            .subIndex = 2,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x1A08_tpdo_9_mapping_parameters.mapping_object_3,
            .subIndex = 3,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
    },
    .o_1A09_tpdo_10_mapping_parameters = {
        {
            .dataOrig = &OD_RAM.x1A09_tpdo_10_mapping_parameters.highest_index_supported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x1A09_tpdo_10_mapping_parameters.mapping_object_1,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x1A09_tpdo_10_mapping_parameters.mapping_object_2,
            .subIndex = 2,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x1A09_tpdo_10_mapping_parameters.mapping_object_3,
            .subIndex = 3,
            .attribute = ODA_SDO_R | ODA_MB,
            .dataLength = 4
        },
    },
    .o_2010_scet = {
        .dataOrig = &OD_RAM.x2010_scet,
        .attribute = ODA_SDO_RW | ODA_TRPDO | ODA_MB,
        .dataLength = 8
    },
    .o_2011_utc = {
        .dataOrig = &OD_RAM.x2011_utc,
        .attribute = ODA_SDO_RW | ODA_MB,
        .dataLength = 8
    },
    .o_3000_satellite_id = {
        .dataOrig = &OD_RAM.x3000_satellite_id,
        .attribute = ODA_SDO_R | ODA_TPDO,
        .dataLength = 1
    },
    .o_3001_flight_mode = {
        .dataOrig = &OD_RAM.x3001_flight_mode,
        .attribute = ODA_SDO_R | ODA_TPDO,
        .dataLength = 1
    },
    .o_3002_versions = {
        {
            .dataOrig = &OD_RAM.x3002_versions.highest_index_supported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x3002_versions.hw_version[0],
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_STR,
            .dataLength = 3
        },
        {
            .dataOrig = &OD_RAM.x3002_versions.configs_version[0],
            .subIndex = 2,
            .attribute = ODA_SDO_R | ODA_STR,
            .dataLength = 5
        },
        {
            .dataOrig = &OD_RAM.x3002_versions.fw_version[0],
            .subIndex = 4,
            .attribute = ODA_SDO_R | ODA_STR,
            .dataLength = 5
        },
    },
    .o_3003_system = {
        {
            .dataOrig = &OD_RAM.x3003_system.highest_index_supported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x3003_system.temperature,
            .subIndex = 7,
            .attribute = ODA_SDO_R | ODA_TPDO,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x3003_system.vrefint,
            .subIndex = 8,
            .attribute = ODA_SDO_R | ODA_TPDO,
            .dataLength = 1
        },
    },
    .o_4000_gyroscope = {
        {
            .dataOrig = &OD_RAM.x4000_gyroscope.highest_index_supported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x4000_gyroscope.pitch_rate,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x4000_gyroscope.yaw_rate,
            .subIndex = 2,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x4000_gyroscope.roll_rate,
            .subIndex = 3,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x4000_gyroscope.pitch_rate_raw,
            .subIndex = 4,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x4000_gyroscope.yaw_rate_raw,
            .subIndex = 5,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x4000_gyroscope.roll_rate_raw,
            .subIndex = 6,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
    },
    .o_4001_accelerometer = {
        {
            .dataOrig = &OD_RAM.x4001_accelerometer.highest_index_supported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x4001_accelerometer.x,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x4001_accelerometer.y,
            .subIndex = 2,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x4001_accelerometer.z,
            .subIndex = 3,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x4001_accelerometer.x_raw,
            .subIndex = 4,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x4001_accelerometer.y_raw,
            .subIndex = 5,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x4001_accelerometer.z_raw,
            .subIndex = 6,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
    },
    .o_4002_temperature = {
        .dataOrig = &OD_RAM.x4002_temperature,
        .attribute = ODA_SDO_R | ODA_TPDO,
        .dataLength = 1
    },
    .o_4003_pos_z_magnetometer_1 = {
        {
            .dataOrig = &OD_RAM.x4003_pos_z_magnetometer_1.highest_index_supported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x4003_pos_z_magnetometer_1.x,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x4003_pos_z_magnetometer_1.y,
            .subIndex = 2,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x4003_pos_z_magnetometer_1.z,
            .subIndex = 3,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
    },
    .o_4004_pos_z_magnetometer_2 = {
        {
            .dataOrig = &OD_RAM.x4004_pos_z_magnetometer_2.highest_index_supported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x4004_pos_z_magnetometer_2.x,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x4004_pos_z_magnetometer_2.y,
            .subIndex = 2,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x4004_pos_z_magnetometer_2.z,
            .subIndex = 3,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
    },
    .o_4005_min_z_magnetometer_1 = {
        {
            .dataOrig = &OD_RAM.x4005_min_z_magnetometer_1.highest_index_supported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x4005_min_z_magnetometer_1.x,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x4005_min_z_magnetometer_1.y,
            .subIndex = 2,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x4005_min_z_magnetometer_1.z,
            .subIndex = 3,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
    },
    .o_4006_min_z_magnetometer_2 = {
        {
            .dataOrig = &OD_RAM.x4006_min_z_magnetometer_2.highest_index_supported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x4006_min_z_magnetometer_2.x,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x4006_min_z_magnetometer_2.y,
            .subIndex = 2,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
        {
            .dataOrig = &OD_RAM.x4006_min_z_magnetometer_2.z,
            .subIndex = 3,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
    },
    .o_4007_magnetorquer_current = {
        {
            .dataOrig = &OD_RAM.x4007_magnetorquer_current.highest_index_supported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x4007_magnetorquer_current.x,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x4007_magnetorquer_current.y,
            .subIndex = 2,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x4007_magnetorquer_current.z,
            .subIndex = 3,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
    },
    .o_4008_magnetorquer_current_set = {
        {
            .dataOrig = &OD_RAM.x4008_magnetorquer_current_set.highest_index_supported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x4008_magnetorquer_current_set.x,
            .subIndex = 1,
            .attribute = ODA_SDO_RW | ODA_TRPDO | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x4008_magnetorquer_current_set.y,
            .subIndex = 2,
            .attribute = ODA_SDO_RW | ODA_TRPDO | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x4008_magnetorquer_current_set.z,
            .subIndex = 3,
            .attribute = ODA_SDO_RW | ODA_TRPDO | ODA_MB,
            .dataLength = 2
        },
    },
    .o_4009_magnetorquer_pwm_percent = {
        {
            .dataOrig = &OD_RAM.x4009_magnetorquer_pwm_percent.highest_index_supported,
            .subIndex = 0,
            .attribute = ODA_SDO_R,
            .dataLength = 1
        },
        {
            .dataOrig = &OD_RAM.x4009_magnetorquer_pwm_percent.x,
            .subIndex = 1,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x4009_magnetorquer_pwm_percent.y,
            .subIndex = 2,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 4
        },
        {
            .dataOrig = &OD_RAM.x4009_magnetorquer_pwm_percent.z,
            .subIndex = 3,
            .attribute = ODA_SDO_R | ODA_TPDO | ODA_MB,
            .dataLength = 2
        },
    },
};

static OD_ATTR_OD OD_entry_t ODList[] = {
    {0x1000, 0x01, ODT_VAR, &ODObjs.o_1000_device_type, NULL},
    {0x1001, 0x01, ODT_VAR, &ODObjs.o_1001_error_register, NULL},
    {0x1003, 0x09, ODT_ARR, &ODObjs.o_1003_predefined_error_field, NULL},
    {0x1005, 0x01, ODT_VAR, &ODObjs.o_1005_cob_id_sync, NULL},
    {0x1006, 0x01, ODT_VAR, &ODObjs.o_1006_communication_cycle_period, NULL},
    {0x1014, 0x01, ODT_VAR, &ODObjs.o_1014_cob_id_emergency_message, NULL},
    {0x1015, 0x01, ODT_VAR, &ODObjs.o_1015_inhibit_time_emcy, NULL},
    {0x1016, 0x02, ODT_ARR, &ODObjs.o_1016_consumer_heartbeat_time, NULL},
    {0x1017, 0x01, ODT_VAR, &ODObjs.o_1017_producer_heartbeat_time, NULL},
    {0x1018, 0x05, ODT_REC, &ODObjs.o_1018_identity, NULL},
    {0x1200, 0x04, ODT_REC, &ODObjs.o_1200_sdo_server_parameter, NULL},
    {0x1800, 0x06, ODT_REC, &ODObjs.o_1800_tpdo_1_communication_parameters, NULL},
    {0x1801, 0x06, ODT_REC, &ODObjs.o_1801_tpdo_2_communication_parameters, NULL},
    {0x1802, 0x06, ODT_REC, &ODObjs.o_1802_tpdo_3_communication_parameters, NULL},
    {0x1803, 0x06, ODT_REC, &ODObjs.o_1803_tpdo_4_communication_parameters, NULL},
    {0x1804, 0x06, ODT_REC, &ODObjs.o_1804_tpdo_5_communication_parameters, NULL},
    {0x1805, 0x06, ODT_REC, &ODObjs.o_1805_tpdo_6_communication_parameters, NULL},
    {0x1806, 0x06, ODT_REC, &ODObjs.o_1806_tpdo_7_communication_parameters, NULL},
    {0x1807, 0x06, ODT_REC, &ODObjs.o_1807_tpdo_8_communication_parameters, NULL},
    {0x1808, 0x06, ODT_REC, &ODObjs.o_1808_tpdo_9_communication_parameters, NULL},
    {0x1809, 0x06, ODT_REC, &ODObjs.o_1809_tpdo_10_communication_parameters, NULL},
    {0x1A00, 0x04, ODT_REC, &ODObjs.o_1A00_tpdo_1_mapping_parameters, NULL},
    {0x1A01, 0x04, ODT_REC, &ODObjs.o_1A01_tpdo_2_mapping_parameters, NULL},
    {0x1A02, 0x02, ODT_REC, &ODObjs.o_1A02_tpdo_3_mapping_parameters, NULL},
    {0x1A03, 0x04, ODT_REC, &ODObjs.o_1A03_tpdo_4_mapping_parameters, NULL},
    {0x1A04, 0x04, ODT_REC, &ODObjs.o_1A04_tpdo_5_mapping_parameters, NULL},
    {0x1A05, 0x04, ODT_REC, &ODObjs.o_1A05_tpdo_6_mapping_parameters, NULL},
    {0x1A06, 0x04, ODT_REC, &ODObjs.o_1A06_tpdo_7_mapping_parameters, NULL},
    {0x1A07, 0x04, ODT_REC, &ODObjs.o_1A07_tpdo_8_mapping_parameters, NULL},
    {0x1A08, 0x04, ODT_REC, &ODObjs.o_1A08_tpdo_9_mapping_parameters, NULL},
    {0x1A09, 0x04, ODT_REC, &ODObjs.o_1A09_tpdo_10_mapping_parameters, NULL},
    {0x2010, 0x01, ODT_VAR, &ODObjs.o_2010_scet, NULL},
    {0x2011, 0x01, ODT_VAR, &ODObjs.o_2011_utc, NULL},
    {0x3000, 0x01, ODT_VAR, &ODObjs.o_3000_satellite_id, NULL},
    {0x3001, 0x01, ODT_VAR, &ODObjs.o_3001_flight_mode, NULL},
    {0x3002, 0x04, ODT_REC, &ODObjs.o_3002_versions, NULL},
    {0x3003, 0x03, ODT_REC, &ODObjs.o_3003_system, NULL},
    {0x4000, 0x07, ODT_REC, &ODObjs.o_4000_gyroscope, NULL},
    {0x4001, 0x07, ODT_REC, &ODObjs.o_4001_accelerometer, NULL},
    {0x4002, 0x01, ODT_VAR, &ODObjs.o_4002_temperature, NULL},
    {0x4003, 0x04, ODT_REC, &ODObjs.o_4003_pos_z_magnetometer_1, NULL},
    {0x4004, 0x04, ODT_REC, &ODObjs.o_4004_pos_z_magnetometer_2, NULL},
    {0x4005, 0x04, ODT_REC, &ODObjs.o_4005_min_z_magnetometer_1, NULL},
    {0x4006, 0x04, ODT_REC, &ODObjs.o_4006_min_z_magnetometer_2, NULL},
    {0x4007, 0x04, ODT_REC, &ODObjs.o_4007_magnetorquer_current, NULL},
    {0x4008, 0x04, ODT_REC, &ODObjs.o_4008_magnetorquer_current_set, NULL},
    {0x4009, 0x04, ODT_REC, &ODObjs.o_4009_magnetorquer_pwm_percent, NULL},
    {0x0000, 0x00, 0, NULL, NULL}
};

static OD_t _OD = {
    (sizeof(ODList) / sizeof(ODList[0])) - 1,
    &ODList[0]
};

OD_t *OD = &_OD;
