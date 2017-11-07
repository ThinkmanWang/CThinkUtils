#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <string.h>
#include <glib.h>

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



    return 0;
}
