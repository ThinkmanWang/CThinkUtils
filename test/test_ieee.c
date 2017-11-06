#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <string.h>
#include <glib.h>

#include "ieee.h"
#include "log.h"

DEFINE_EA_MOD(MOD_MAIN);

int main(int argc, char* argv[])
{
    ELInit(NULL, log_module);
    ELSetDefaultLogTable(EA_LOG_DEBUG);
    ELSetModuleLogLevel(MOD_MAIN, EA_LOG_DEBUG);
    ELSetModuleLogLevel(MOD_UI, EA_LOG_DEBUG);
    ELSetModuleLogLevel(MOD_DATA, EA_LOG_DEBUG);
    ELSetModuleLogLevel(MOD_NETWORK, EA_LOG_DEBUG);
    ELPrintLogTable();

    if (argc != 3) {
        printf("Usage:\n");
        printf("1. Get ieee754 from float\n");
        printf("  %s -i float\n", argv[0]);
        printf("  Eg:\n");
        printf("    %s -i 3.14159\n", argv[0]);

        printf("\n\n\n");
        printf("2. Get float from ieee754\n");
        printf("%s -f ieee754\n", argv[0]);
        printf("  Eg:\n");
        printf("    %s -f 40490FD0\n", argv[0]);
        return 0;
    }

    if (0 == strcmp("-i", argv[1])) {
        float val;
        if (1 == sscanf(argv[2],"%f", &val)) {
            unsigned long ieee = float2ieee(val);

            char tmp[40] = "";
            char bin[64] = "";
            itoa_x(ieee, tmp, 2); //binary output
//            sprintf(tmp, "%x", ieee);

            //if tmp.length < 32, fill with '0'
            if (strlen(tmp) < 32) {
                int len = 32 - strlen(tmp) + 1;
                char* pBuf = (char*)malloc(len);
                memset(pBuf, '0', len);
                pBuf[len - 1] = '\0';
                strcpy(bin, pBuf);
                free(pBuf);
            }
            strcat(bin, tmp);

            DEBUG("ieee for %f\n", val);
            DEBUG("%s\n", bin);
            DEBUG("0x%X\n", ieee);
        }
    }

    else if (0 == strcmp("-f", argv[1])) {
        unsigned long val;
        if (1 == sscanf(argv[2],"%X", &val)) {
            DEBUG("float for 0x%X : %f\n", val, ieee2float(val));
        }
    }

    else {
        printf("Input Error!");
        return 0;
    }

    return 0;
}
