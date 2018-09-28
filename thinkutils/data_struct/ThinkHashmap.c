#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ThinkHashmap.h"
#include "ThinkList.h"

static int hash(const char* key)
{
    if (key == NULL) {
        return 0;
    }

    size_t len = strlen(key);
    int index = (int) key[0];
    for (int i = 1; i<len; ++i) {
        index *= 1103515245 + (int)key[i];
    }
    index >>= 27;

    return (abs(index));
}

static ThinkHashmapNode* think_hashmap_node_new(const char* pszKey, void* pData)
{
    return_val_if_fail(pszKey != NULL, NULL);
    return_val_if_fail(pData != NULL, NULL);

    ThinkHashmapNode* pNode = (ThinkHashmapNode*) malloc(sizeof(ThinkHashmapNode));
    pNode->m_pszKey = strdup(pszKey);
    pNode->m_pData = pData;

    return pNode;
}

static void think_hashmap_node_free(ThinkHashmap* pMap, ThinkHashmapNode** ppNode) {
    return_if_fail(ppNode != NULL);
    return_if_fail(*ppNode != NULL);

    if ((*ppNode)->m_pData && *pMap->m_pDestoryFunc != NULL) {
        (*pMap->m_pDestoryFunc)((*ppNode)->m_pData);
        (*ppNode)->m_pData = NULL;
    }

    if ((*ppNode)->m_pszKey) {
        free((void *) (*ppNode)->m_pszKey);
        (*ppNode)->m_pszKey = NULL;
    }

    free((*ppNode));

    *ppNode = NULL;
}

ThinkHashmap* think_hashmap_new(ThinkDestoryFunc pDestoryFunc)
{
    ThinkHashmap* pMap = (ThinkHashmap*) malloc(sizeof(ThinkHashmap));
    pMap->m_nSize = 0;
    pMap->m_pDestoryFunc = pDestoryFunc;
    for (int i = 0; i < HASHMAP_SIZE; ++i) {
        pMap->m_pArray[i] = NULL;
    }

    return pMap;
}

void think_hashmap_free(ThinkHashmap** ppMap)
{
    return_if_fail(ppMap != NULL);
    return_if_fail(*ppMap != NULL);

    for (int i = 0; i < HASHMAP_SIZE; ++i) {
        ThinkList* pList = (*ppMap)->m_pArray[i];
        if (NULL == pList) {
            continue;
        }

        ThinkHashmapNode* pNode = think_list_pop(&pList);
        while (pNode != NULL) {
            think_hashmap_node_free((*ppMap), &pNode);
            (*ppMap)->m_nSize -= 1;

            pNode = think_list_pop(&pList);
        }
    }

    free((*ppMap));
    *ppMap = NULL;
}

size_t think_hashmap_size(ThinkHashmap* pMap)
{
    return pMap->m_nSize;
}


void think_hashmap_put(ThinkHashmap* pMap, const char* pszKey, void* pData)
{
    return_if_fail(pMap != NULL);
    return_if_fail(pszKey != NULL);

    void* pOldData = think_hashmap_get(pMap, pszKey);
    if (NULL != pOldData) {
        think_hashmap_remove(pMap, pszKey);
    }

    ThinkHashmapNode* pNode = think_hashmap_node_new(pszKey, pData);
    return_if_fail(pNode != NULL);

    int nIndex = hash(pszKey) % HASHMAP_SIZE;
    ThinkList* pListNode = pMap->m_pArray[nIndex];

    pMap->m_pArray[nIndex] = think_list_append(pListNode, pNode);
    pMap->m_nSize++;
}

void* think_hashmap_get(ThinkHashmap* pMap, const char* pszKey)
{
    return_val_if_fail(pMap != NULL, NULL);
    return_val_if_fail(pszKey != NULL, NULL);

    int nIndex = hash(pszKey) % HASHMAP_SIZE;
    ThinkList* pListNode = pMap->m_pArray[nIndex];

    return_val_if_fail(pListNode != NULL, NULL);

    while (pListNode != NULL) {
        ThinkHashmapNode* pHashmapNode = pListNode->m_pData;
        if (pHashmapNode != NULL && 0 == strcmp(pHashmapNode->m_pszKey, pszKey)) {
            return pHashmapNode->m_pData;
        }

        pListNode = pListNode->m_pNext;
    }

    return NULL;
}

void think_hashmap_remove(ThinkHashmap* pMap, const char* pszKey)
{

}


void think_hashmap_foreach(ThinkHashmap* pMap, ThinkHashFunc pFunc, void* pUserData)
{
    return_if_fail(pMap != NULL);

    for (int i = 0; i < HASHMAP_SIZE; ++i) {
        ThinkList *pList = pMap->m_pArray[i];
        if (NULL == pList) {
            continue;
        }

        size_t nSize = think_list_length(pList);
        for (int nIndex = 0; nIndex < nSize; ++nIndex) {
            ThinkHashmapNode *pNode = think_list_get(pList, nIndex);
            if (NULL == pNode) {
                continue;
            }

            if (NULL == pFunc) {
                continue;
            }

            pFunc(pNode->m_pszKey, pNode->m_pData, pUserData);
        }
    }

}
