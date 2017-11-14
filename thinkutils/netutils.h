#ifndef _NETUTILS_H_
#define _NETUTILS_H_

#ifdef __cplusplus
extern "C" {
#endif

int get_local_ip(const char* pszName, char* pszIP, int nMaxLenth);

#ifdef __cplusplus
}
#endif

#endif