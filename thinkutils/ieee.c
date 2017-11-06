#include "ieee.h"

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <string.h>

#include "log.h"

DEFINE_EA_MOD(MOD_TOOLS);

float ieee2float(const unsigned long from)
{
    unsigned long sign, //sign
            exp,  //exponent
            fr;   //fraction

    unsigned long val = from;
    DEBUG("from : 0x%X\n", val);

    sign = val >> (EXPONENT + FRACTION); //save sign 31
    DEBUG("sign : 0x%X\n", sign);
    val <<= SIGN; //1

    exp = val >> (SIGN + FRACTION);  //save exponent 25
    DEBUG("val : 0x%X\n", val);
    DEBUG("exp : 0x%X\n", exp);
    val <<= EXPONENT;

    fr = val; //save fraction

    if (0 == exp && 0 == fr) {
        return 0.0f;
    }

    double S = pow((double)-1, (double)sign);
    double E = pow((double)2, (double)(exp - EXPONENT_VALUE));
    double M = 1.0 + (double)((double)fr/(double)((unsigned long)0x80000000));

    return (float)(S * E * M);
}

unsigned long float2ieee(const float from)
{
    float val = from;

    unsigned long sign = 0; //sign
    int exp = 0;  //exponent

    if (0.0f == val) {
        return 0x00000000;
    }

    if (val < 0) { // save sian
        sign = 1;
        val *= -1;
    }

    /**
     * format value and get exponent
     * value must be 1.X * 2^e
     */
    while (val >= 2.0f) {
        val /= 2.0f;
        exp ++;
    }

    while (val < 1.0f) {
        val *= 2.0f;
        exp --;
    }

    unsigned long S = sign;
    unsigned long E = (unsigned long)(exp + EXPONENT_VALUE);
    unsigned long M = (unsigned long)( ((double)val - (double)1) * ((double)0x80000000) );

    return ( S << (EXPONENT + FRACTION) ) | ( E << FRACTION ) | ( M >> (SIGN + EXPONENT));
}

#define SIGNED_PRINT_SIZE(object)  ((sizeof(object) * CHAR_BIT - 1)* 28 / 93 + 3)

char* itoa_x(int number, char *dest, size_t dest_size)
{
    if (dest == NULL) {
        return NULL;
    }

    char buf[SIGNED_PRINT_SIZE(number)];
    char *p = &buf[sizeof buf - 1];

    // Work with negative absolute value
    int neg_num = number < 0 ? number : -number;

    // Form string
    *p = '\0';
    do {
        *--p = (char) ('0' - neg_num % 10);
        neg_num /= 10;
    } while (neg_num);
    if (number < 0) {
        *--p = '-';
    }

    // Copy string
    size_t src_size = (size_t) (&buf[sizeof buf] - p);
    if (src_size > dest_size) {
        // Not enough room
        return NULL;
    }
    return memcpy(dest, p, src_size);
}