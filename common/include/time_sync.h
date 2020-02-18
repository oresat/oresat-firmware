#ifndef TIME_H
#define TIME_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ch.h"
#include "hal.h"
#include "CANopen.h"

#define TIME_UNIX_EPOCH     1970U   /* UNIX Time Epoch */
#define TIME_TAI_EPOCH      1958U   /* CCSDS Level 1 Time Code Epoch (TAI) */
#define TIME_CUC_PREAMBLE   0x1E    /* CCSDS Unsegmented Time Code (CUC) Preamble */
#define TIME_CDS_PREAMBLE   0x41    /* CCSDS Day Segmented Time Code (CDS) Preamble */

/* CCSDS Unsegmented Time Code (CUC) data type */
typedef union {
    uint64_t raw;
    struct {
        uint32_t coarse:32;
        uint32_t fine:24;
    };
} time_scet_t;

/* CCSDS Day Segmented Time Code (CDS) data type */
typedef union {
    uint64_t raw;
    struct {
        uint16_t day:16;
        uint32_t ms:32;
        uint16_t us:16;
    };
} time_utc_t;

time_t get_time_unix(uint32_t *msec);
void set_time_unix(time_t unix_time, uint32_t msec);
void get_time_scet(time_scet_t *scet);
void set_time_scet(const time_scet_t *scet);
void get_time_utc(time_utc_t *utc);
void set_time_utc(const time_utc_t *utc);

CO_SDO_abortCode_t OD_SCET_Func(CO_ODF_arg_t *ODF_arg);
CO_SDO_abortCode_t OD_UTC_Func(CO_ODF_arg_t *ODF_arg);

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif
