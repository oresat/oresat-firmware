#ifndef OPD_H
#define OPD_H

typedef enum {
    OPD_PROTOCARD1 = 0x18,
    OPD_PROTOCARD2 = 0x19,
    OPD_PROTOCARD3 = 0x1A,
} opd_addr_t;

void opd_init(void);
void opd_start(void);
void opd_stop(void);
void opd_enable(opd_addr_t opd_addr);
void opd_disable(opd_addr_t opd_addr);
#endif
