/*! \file util_numbers.h
 * \addtogroup util_numbers
 * @{
 */

#ifndef UTIL_NUMBERS_H_
#define UTIL_NUMBERS_H_

#ifdef __cplusplus
extern "C" {
#endif

static inline int round_nearest(float f)
{
    return((f < 0) ? ((int)(f - 0.5f)) : ((int)(f + 0.5f)));
    //if(f<0) {
    //return((int)(f-0.5f));
    //}
    //return (int)(f + 0.5f);
}


double incr_rnd(double d, double m) ;
signed int sign_extend_13bit(signed int);

uint8_t bits_get_bit_n(uint8_t byte, uint8_t n) ;

#ifdef __cplusplus
}
#endif

#endif

//! @}

