#ifndef _IEEE_H_
#define _IEEE_H_

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SIGN			1
#define EXPONENT		7
#define FRACTION		(32 - SIGN - EXPONENT)
#define EXPONENT_VALUE	( pow( (double)2, (double)EXPONENT )/2.0 - 1.0 )

float ieee2float(const unsigned long from);
unsigned long float2ieee(const float from);
char* itoa_x(int number, char *dest, size_t dest_size);

#ifdef __cplusplus
}
#endif

#endif