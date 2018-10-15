#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ThinkHashmap.h"
//#include "ThinkList.h"

static unsigned int hash(const char* pszKey)
{
    unsigned int hash = 0;
    while (*pszKey) {
        hash = (*pszKey++) + (hash << 6) + (hash << 16) - hash;
    }

    return (hash & 0x7FFFFFFF);
}

static ThinkHashmapNode* think_hashmap_node_new(const char* pszKey, void* pData)
{
    return_val_if_fail(pszKey != NULL, NULL);
    return_val_if_fail(pData != NULL, NULL);

    ThinkHashmapNode* pNode = (ThinkHashmapNode*) malloc(sizeof(ThinkHashmapNode));
    pNode->m_pszKey = strdup(pszKey);
    pNode->m_pData = pData;
    pNode->m_pNext = NULL;

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

    (*ppNode)->m_pNext = NULL;

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
        ThinkHashmapNode* pNode = (*ppMap)->m_pArray[i];
        if (NULL == pNode) {
            continue;
        }

        while (pNode) {
            ThinkHashmapNode* pNext = pNode->m_pNext;

            think_hashmap_node_free((*ppMap), &pNode);
            (*ppMap)->m_nSize -= 1;

            pNode = pNext;
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

    ThinkHashmapNode* pNewNode = think_hashmap_node_new(pszKey, pData);
    ThinkHashmapNode* pCur = pMap->m_pArray[nIndex];
    if (NULL == pCur) {
        pMap->m_pArray[nIndex] = pNewNode;
    } else {
        while (pNode->m_pNext) {
            pCur = pCur->m_pNext;
        }

        pCur->m_pNext = pNewNode;
    }

    pMap->m_nSize++;

}

void* think_hashmap_get(ThinkHashmap* pMap, const char* pszKey)
{
    return_val_if_fail(pMap != NULL, NULL);
    return_val_if_fail(pszKey != NULL, NULL);

    int nIndex = hash(pszKey) % HASHMAP_SIZE;

    ThinkHashmapNode* pCur = pMap->m_pArray[nIndex];
    while (pCur) {
        if (0 == strcmp(pCur->m_pszKey, pszKey)) {
            return pCur->m_pData;
        }
        pCur = pCur->m_pNext;
    }

    return NULL;
}

void think_hashmap_remove(ThinkHashmap* pMap, const char* pszKey)
{
    return_if_fail(pMap != NULL);
    return_if_fail(pszKey != NULL);

    int nIndex = hash(pszKey) % HASHMAP_SIZE;
    ThinkHashmapNode* pCur = pMap->m_pArray[nIndex];
    ThinkHashmapNode* pParent = NULL;
    while (pCur) {

        if (0 == strcmp(pCur->m_pszKey, pszKey)) {

            if (NULL == pParent) {
                pMap->m_pArray[nIndex] = pCur->m_pNext;
            } else {
                pParent->m_pNext = pCur->m_pNext;
            }

            think_hashmap_node_free(pMap, &pCur);

            break;
        }

        pParent = pCur;
        pCur = pCur->m_pNext;
    }

    pMap->m_nSize--;

}


void think_hashmap_foreach(ThinkHashmap* pMap, ThinkHashFunc pFunc, void* pUserData)
{
    return_if_fail(pMap != NULL);
    return_if_fail(pFunc != NULL);

    for (int i = 0; i < HASHMAP_SIZE; ++i) {
        ThinkHashmapNode* pNode = pMap->m_pArray[i];

        while (pNode) {

            pFunc(pNode->m_pszKey, pNode->m_pData, pUserData);

            pNode = pNode->m_pNext;
        }
    }
}
