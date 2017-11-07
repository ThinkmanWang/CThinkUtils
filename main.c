#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <unistd.h>

#include "log.h"
#include "test.h"
#include "datetime.h"
#include "ini.h"

void test_ini()
{
    ini_t *config = ini_load("config.ini");
    const char *name = ini_get(config, "owner", "name");
    if (name) {
        log_debug("name: %s\n", name);
    }

    const char *server = "default";
    int port = 80;

    ini_sget(config, "database", "server", NULL, &server);
    ini_sget(config, "database", "port", "%d", &port);

    log_debug("server: %s:%d\n", server, port);
}

int main()
{

    log_debug("Hello World!\n");

    char szDate[256];
    log_debug("%s\n", now(szDate));
    func1();

    char buf[256];
    getcwd(buf,sizeof(buf));
    log_debug("current working directory: %s\n", buf);

    test_ini();

    return 0;
}