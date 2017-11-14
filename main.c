#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <unistd.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "log.h"
#include "test.h"
#include "datetime.h"
#include "ini.h"
#include "md5.h"
#include "netutils.h"

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

void datetime_test()
{
    char szDate[256];
    log_debug("%s\n", now(szDate));
    func1();

    char buf[256];
    getcwd(buf,sizeof(buf));
    log_debug("current working directory: %s\n", buf);
}

void test_md5()
{
    int ret;
    const char *file_path = "config.ini";
    char md5_str[MD5_STR_LEN + 1];
    const char *test_str = "gchinaran@gmail.com";

    // test file md5
    ret = Compute_file_md5(file_path, md5_str);
    if (0 == ret)
    {
        log_debug("[file - %s] md5 value ==> %s\n", file_path, md5_str);
    }

    // test string md5
    Compute_string_md5((unsigned char *)test_str, strlen(test_str), md5_str);
    log_debug("[string - %s] md5 value ==> %s\n", test_str, md5_str);
}

void test_ip_address()
{
    char szIP[256];
    int nRet = get_local_ip("en0", szIP, 256);
    log_debug("%s\n", szIP);
}

int main()
{

    log_debug("Hello World!\n");

    datetime_test();
    test_ini();
    test_md5();
    test_ip_address();

    return 0;
}