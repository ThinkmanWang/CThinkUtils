#ifndef _DATETIME_H_
#define _DATETIME_H_

#ifdef __cplusplus
extern "C" {
#endif
char* now(char* currTime);
char* today(char* currTime);
int hour();
char* diffday(char* szDate, int nDiffDay);
#ifdef __cplusplus
}
#endif

#endif