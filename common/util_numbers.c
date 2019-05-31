
/*! \file util_numbers.c
 *
 * Number utilities
 *
 * @defgroup util_numbers  Numbers Utilities
 * @{
 */


#include <stdint.h>

#include "util_numbers.h"

/* ===================================  NUMBERS ======================== */
/*
 * Given a number d
 * An increment m
 * 1. create y = x/m
 * 2. q = int(Round y)
 * 3. z = q * m
 *
 */
double incr_rnd(double d, double m)
{

    int    q;
    double y = 0;
    double z = 0;

    y = d / m;

    q = round_nearest(y);

    z = q * m;

    return z;

}

/*!
 * Reference
 * https://graphics.stanford.edu/~seander/bithacks.html#FixedSignExtend
 *
 * Note: Clear bits 14->31 prior to calling.
 * Warning: Untested on 64 bit integers.
 *
 * example
 *          //clear dv bit
 *          tint_msb = ((~(1 << 7)) & tint_msb);
 *          tint = sign_extend_12bit((tint_msb << 8) | tint_lsb);
 *
 */
signed int sign_extend_13bit(signed int x)
{
    signed int r = 0;
    struct
    {
        signed int x: 13;
    } s;

    r = s.x = x;

    return r;
}

/* ===================================  BITS ======================== */
/*
 * input 8 bit unsigned byte
 * output bit at position n
 */
uint8_t bits_get_bit_n(uint8_t byte, uint8_t n) {
    return( (byte>>n) & 0b1 );
}

/*
void test_bits_get_bit_n(void) {
    uint8_t testnum;

    srand (time (0));
    for(int i=0; i<10; ++i) {
        testnum = (uint8_t)(rand() % 256);

        printf("num=0x%x:\r\n\t0b", testnum);
        for(int i=7; i>=0; --i) {
            printf("%d ",bits_get_bit_n(testnum, i));
        }
        printf("\r\n");
    }
}
*/



//! @}
