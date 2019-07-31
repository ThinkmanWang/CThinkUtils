#ifndef _DATETIME_H_
#define _DATETIME_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif
char* now(char* currTime, size_t nMax);
char* today(char* currTime, size_t nMax);
int hour();
char* diffday(char* szDate, int nDiffDay);
#ifdef __cplusplus
}
#endif

#endif