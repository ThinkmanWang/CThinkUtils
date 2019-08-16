#ifndef _THINK_HASHMAP_H_
#define _THINK_HASHMAP_H_

#include <stdio.h>

#include "utils.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HASHMAP_SIZE 1024

typedef struct _ThinkHashMapNode{
    char* m_pszKey;
    void* m_pData;
    struct _ThinkHashMapNode* m_pNext;
} ThinkHashMapNode;

typedef struct _ThinkHashMap{
    size_t m_nSize;
    ThinkDestoryFunc m_pDestoryFunc;
    ThinkHashMapNode* m_pArray[HASHMAP_SIZE];
} ThinkHashMap;

typedef void (*ThinkHashFunc) (const char* key
        , void* pData
        , void* user_data);

ThinkHashMap* think_hashmap_new(ThinkDestoryFunc pDestoryFunc);
void think_hashmap_free(ThinkHashMap** ppMap);
size_t think_hashmap_size(ThinkHashMap* pMap);

void think_hashmap_put(ThinkHashMap* pMap, const char* pszKey, void* pData);
void* think_hashmap_get(ThinkHashMap* pMap, const char* pszKey);
void think_hashmap_remove(ThinkHashMap* pMap, const char* pszKey);

void think_hashmap_foreach(ThinkHashMap* pMap, ThinkHashFunc pFunc, void* pUserData);


#ifdef __cplusplus
}
#endif

#endif //_THINK_HASHMAP_H_