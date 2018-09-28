#ifndef _THINK_HASHMAP_H_
#define _THINK_HASHMAP_H_

#include <stdio.h>

#include "utils.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HASHMAP_SIZE 1024

typedef struct _hashmap_node{
    char* m_pszKey;
    void* m_pData;
} ThinkHashmapNode;

typedef struct _hashmap_map{
    size_t m_nSize;
    ThinkDestoryFunc m_pDestoryFunc;
    void* m_pArray[HASHMAP_SIZE];
} ThinkHashmap;

typedef void (*ThinkHashFunc) (const char* key
        , void* pData
        , void* user_data);

ThinkHashmap* think_hashmap_new(ThinkDestoryFunc pDestoryFunc);
void think_hashmap_free(ThinkHashmap** ppMap);
size_t think_hashmap_size(ThinkHashmap* pMap);

void think_hashmap_put(ThinkHashmap* pMap, const char* pszKey, void* pData);
void* think_hashmap_get(ThinkHashmap* pMap, const char* pszKey);
void think_hashmap_remove(ThinkHashmap* pMap, const char* pszKey);

void think_hashmao_foreach(ThinkHashmap* pMap, ThinkHashFunc pFunc, void* pUserData);


#ifdef __cplusplus
}
#endif

#endif //_THINK_HASHMAP_H_