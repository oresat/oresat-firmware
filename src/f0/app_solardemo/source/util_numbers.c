
/*! \file util_numbers.c
 *
 * Number utilities
 *
 * @defgroup util_numbers  Numbers Utilities
 * @{
 */


#include "util_numbers.h"

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


//! @}
