
#include "datetime.h"

#include <glib.h>
#include <string.h>
#include <stdio.h>


char* now(char* currTime)
{
    g_return_val_if_fail(currTime != NULL, NULL);

    struct tm* ptm = NULL;
    time_t tme;
    tme = time(NULL);
    ptm = localtime(&tme);
    char szTime[256];

    memset(szTime, 0, 256);
    sprintf(szTime, "%d-%02d-%02d %02d:%02d:%02d", (ptm->tm_year + 1900),
            ptm->tm_mon + 1, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec);

    strcpy(currTime, szTime);
    return currTime;
}