
#include "datetime.h"

#include <glib.h>
#include <string.h>
#include <stdio.h>
#include <ntsid.h>
#include <sys/time.h>

#include "common.h"

char* now(char* currTime, size_t nMax)
{
    g_return_val_if_fail(currTime != NULL, NULL);

    struct tm* ptm = NULL;
    time_t tme;
    tme = time(NULL);
    ptm = localtime(&tme);
    char szTime[256];

    memset(szTime, 0, 256);
    snprintf(szTime, MIN(nMax, 256), "%d-%02d-%02d %02d:%02d:%02d", (ptm->tm_year + 1900),
            ptm->tm_mon + 1, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec);

//    g_free(ptm);
    strcpy(currTime, szTime);
    return currTime;
}

int hour()
{
    struct tm* ptm = NULL;
    time_t tme;
    tme = time(NULL);
    ptm = localtime(&tme);

//    g_free(ptm);

    return ptm->tm_hour;
}

char* today(char* currTime, size_t nMax)
{
    g_return_val_if_fail(currTime != NULL, NULL);

    struct tm* ptm = NULL;
    time_t tme;
    tme = time(NULL);
    ptm = localtime(&tme);
    char szTime[256];

    memset(szTime, 0, 256);
    snprintf(szTime, MIN(nMax, 256), "%d-%02d-%02d", (ptm->tm_year + 1900), ptm->tm_mon + 1, ptm->tm_mday);
//    g_free(ptm);

    strcpy(currTime, szTime);
    return currTime;
}

char* diffday(char* szDate, int nDiffDay)
{
    g_return_val_if_fail(szDate != NULL, NULL);

    struct tm* ptm = NULL;
    time_t tme;
    tme = time(NULL) + (long) ((long) nDiffDay * 3600L * 24L);
    ptm = localtime(&tme);
    char szTime[256];

    memset(szTime, 0, 256);
    sprintf(szTime, "%d-%02d-%02d", (ptm->tm_year + 1900), ptm->tm_mon + 1, ptm->tm_mday);
//    g_free(ptm);

    strcpy(szDate, szTime);
    return szDate;
}