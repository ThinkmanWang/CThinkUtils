#ifndef _STRING_UTILS_
#define _STRING_UTILS_

#ifdef __cplusplus
extern "C" {
#endif

char * string_replace(const char* src, char* dst, size_t dst_size, const char* search, const char* replace_with);

#ifdef __cplusplus
}
#endif

#endif