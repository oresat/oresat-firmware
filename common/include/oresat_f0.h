#ifndef COMMON_INCLUDE_ORESAT_F0_H_
#define COMMON_INCLUDE_ORESAT_F0_H_

#ifdef __cplusplus
extern "C" {
#endif

// See STM32F091xC-bootloader.ld/STM32F4091xC-app.ld for definitions and
// rules_memory.ld for declarations.
extern uint8_t __flash0_base__[];
extern uint8_t __flash0_end__[];
extern uint8_t __flash1_base__[];
extern uint8_t __flash1_end__[];
extern uint8_t __flash2_base__[];
extern uint8_t __flash2_end__[];
extern uint8_t __ram0_base__[];
extern uint8_t __ram0_end__[];
extern uint8_t __ram1_base__[];
extern uint8_t __ram1_end__[];

// The __*_size__ symbols are weird. The contents aren't relevent, it's the
// address, converted to a number, which is the represented region size.
extern const void __flash0_size__;
extern const void __flash1_size__;
extern const void __flash2_size__;
extern const void __ram0_size__;
extern const void __ram1_size__;
#define FLASH0_SIZE ((const uint32_t)(&__flash0_size__))
#define FLASH1_SIZE ((const uint32_t)(&__flash1_size__))
#define FLASH2_SIZE ((const uint32_t)(&__flash2_size__))
#define RAM0_SIZE ((const uint32_t)(&__ram0_size__))
#define RAM1_SIZE ((const uint32_t)(&__ram1_size__))

#ifdef __cplusplus
}
#endif /*__cplusplus*/



#endif /* COMMON_INCLUDE_ORESAT_F0_H_ */
