#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_utils.h"
#include <stdbool.h>

char* string_replace(const char* src, char* dst, size_t dst_size, const char* search, const char* replace_with) {
    char * replace_buf = (char *)malloc(dst_size);
    if (replace_buf) {
        replace_buf[0] = 0;
        char * p = (char *)src;
        char * pos = NULL;
        while ( (pos = strstr(p, search)) != NULL ) {
            size_t n = (size_t)(pos-p);
            strncat(replace_buf, p, n > dst_size ? dst_size : n);
            strncat(replace_buf, replace_with, dst_size-strlen(replace_buf)-1);
            p = pos + strlen(search);
        }
        snprintf(dst, dst_size, "%s%s", replace_buf, p);
        free(replace_buf);
    }
    return dst;
}

gboolean is_empty_string(const gchar* pszTxt)
{
    g_return_val_if_fail(pszTxt != NULL, true);
    g_return_val_if_fail(strlen(pszTxt) > 0, true);

    return FALSE;
}