#ifndef _SIN_LUT_H_
#define _SIN_LUT_H_

#include <unistd.h>

#define LUT_SIZE 512 

static const int kLUTSize = LUT_SIZE;

typedef float sin_t;

extern const sin_t sin_lut[LUT_SIZE];

#endif
