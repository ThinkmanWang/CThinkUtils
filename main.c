#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

#include "log.h"
#include "test.h"

DEFINE_EA_MOD(MOD_MAIN);

int main()
{
    ELInit(NULL, log_module);
    ELSetDefaultLogTable(EA_LOG_DEBUG);
    ELSetModuleLogLevel(MOD_MAIN, EA_LOG_DEBUG);
    ELSetModuleLogLevel(MOD_UI, EA_LOG_DEBUG);
    ELSetModuleLogLevel(MOD_DATA, EA_LOG_DEBUG);
    ELSetModuleLogLevel(MOD_NETWORK, EA_LOG_DEBUG);
    ELPrintLogTable();

    DEBUG("Hello World!\n");
    func1();

    return 0;
}