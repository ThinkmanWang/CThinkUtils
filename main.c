#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

#include "log.h"
#include "test.h"
#include "datetime.h"


int main()
{

    log_debug("Hello World!\n");

    char szDate[256];
    log_debug("%s\n", now(szDate));
    func1();

    return 0;
}