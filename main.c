#include <stdio.h>

#include <stdlib.h>
#include <glib.h>
#include <unistd.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <glib-object.h>
#include <json-glib/json-glib.h>
#include <json-glib/json-gobject.h>

#include "log.h"
#include "test.h"
#include "datetime.h"
#include "ini.h"
#include "md5.h"
#include "netutils.h"
#include "string_utils.h"

void test_ini()
{
    ini_t *config = ini_load("config.ini");
    const char *name = ini_get(config, "owner", "name");
    if (name) {
        log_debug("name: %s", name);
    }

    const char *server = "default";
    int port = 80;

    ini_sget(config, "database", "server", NULL, &server);
    ini_sget(config, "database", "port", "%d", &port);

    log_debug("server: %s:%d", server, port);
}

void datetime_test()
{
    char szDate[256];
    log_debug("%s", now(szDate));
    func1();

    char buf[256];
    getcwd(buf,sizeof(buf));
    log_debug("current working directory: %s", buf);

    int nDiffDay = -3;
    log_debug("diffday %d ==> %s", nDiffDay, diffday(szDate, nDiffDay));

    nDiffDay = -2;
    log_debug("diffday %d ==> %s", nDiffDay, diffday(szDate, nDiffDay));

    nDiffDay = -1;
    log_debug("diffday %d ==> %s", nDiffDay, diffday(szDate, nDiffDay));

    nDiffDay = 0;
    log_debug("diffday %d ==> %s", nDiffDay, diffday(szDate, nDiffDay));

    nDiffDay = 1;
    log_debug("diffday %d ==> %s", nDiffDay, diffday(szDate, nDiffDay));

    nDiffDay = 2;
    log_debug("diffday %d ==> %s", nDiffDay, diffday(szDate, nDiffDay));

    nDiffDay = 3;
    log_debug("diffday %d ==> %s", nDiffDay, diffday(szDate, nDiffDay));
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
        log_debug("[file - %s] md5 value ==> %s", file_path, md5_str);
    }

    // test string md5
    Compute_string_md5((unsigned char *)test_str, strlen(test_str), md5_str);
    log_debug("[string - %s] md5 value ==> %s", test_str, md5_str);
}

void test_ip_address()
{
    char szIP[256];
    int nRet = get_local_ip("en0", szIP, 256);
    log_debug("%s", szIP);
}

void uuid_test()
{
    gchar* pszUuid = g_uuid_string_random();
    log_debug("uuid ==> %s", pszUuid);


    g_free(pszUuid);
}

void string_test()
{
    gchar szSrc[] = "870b5a59-c840-4164-9b5f-69003f034b50";
    gchar szDst[MAX_INPUT];

    log_debug("%s", string_replace(szSrc, szDst, MAX_INPUT, "-", ""));

    log_debug("%d", is_empty_string(NULL));
    log_debug("%d", is_empty_string(""));
    log_debug("%d", is_empty_string("123"));
}

void test_json()
{
    JsonParser* parser;
    JsonNode* root;
    GError* error;

    parser = json_parser_new ();
    error = NULL;

    const gchar* test_base_object_data = "{ \"text\" : \"hello, world!\", \"foo\" : null, \"blah\" : 47, \"double\" : 42.47 }";
    json_parser_load_from_data(parser, test_base_object_data, -1, &error);
    root = json_parser_get_root(parser);

    log_debug("%s", test_base_object_data);
//    const gchar* pszText = json_node_get_string(root);

    JsonReader *reader = json_reader_new (json_parser_get_root(parser));
    json_reader_read_member (reader, "text");
    const char* pszText = json_reader_get_string_value (reader);

    log_debug("%s", pszText);

    g_free(pszText);
    json_node_free(root);
}

int main()
{

    log_debug("Hello World!");

    datetime_test();
    test_ini();
    test_md5();
    test_ip_address();
    uuid_test();
    string_test();
    test_json();

    return 0;
}