#ifndef CO_DRIVER_CUSTOM_H
#define CO_DRIVER_CUSTOM_H

#ifdef __cplusplus
extern "C" {
#endif

// See CANopenNode/CANopen.c lines 181 - 192. I'm 80% sure that it's a bug in
// the library that it doesn't handle the case where OD_CNT_{T,R}PDO is defined
// but zero; as written it only compiles when they're either undefined or
// greater than zero. None of the firmware projects use RPDOs so they've been
// disabled in CO_CONFIG_PDO (common/include/CO_driver_target.h) but this is
// one of the few project that also doesn't do TPDOs. Our generated object
// dictionaries (od/OD.h) always define OD_CNT_{T,R}PDO. The two defines below
// are what CANopen does when OD_CNT_TPDO is undefined and should probably do
// also when they are defined but zero.
#define OD_ENTRY_H1800 NULL
#define OD_ENTRY_H1A00 NULL

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CO_DRIVER_CUSTOM_H */
