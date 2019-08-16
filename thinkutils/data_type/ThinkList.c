//
// Created by 王晓丰 on 05/02/2018.
//

#include "ThinkList.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

static ThinkList* think_list_get_node(ThinkList* pList, unsigned int nIndex);
static void think_list_sort_real(ThinkList* pList, ThinkCompareDataFunc pCompareFunc, unsigned int nStart, unsigned int nEnd);

static ThinkList* think_list_create_node(void* pData)
{
    ThinkList* pNode = malloc(sizeof(ThinkList));
    pNode->m_pData = pData;
    pNode->m_pNext = NULL;
    pNode->m_pPre = NULL;

    return pNode;
}

static void think_list_free_node(ThinkList** pNode)
{
    free(*pNode);
    *pNode = NULL;
}

static ThinkList* think_list_first_node(ThinkList* pList)
{
    return_val_if_fail(pList != NULL, NULL);

    ThinkList* pNode = pList;
    while (pNode->m_pPre) {
        pNode = pNode->m_pPre;
    }

    return pNode;
}

static ThinkList* think_list_last_node(ThinkList* pList)
{
    return_val_if_fail(pList != NULL, NULL);

    ThinkList* pNode = pList;
    while (pNode->m_pNext) {
        pNode = pNode->m_pNext;
    }

    return pNode;
}

ThinkList* think_list_append(ThinkList* pList, void* pData)
{
    ThinkList* pNode = think_list_create_node(pData);
    ThinkList* pLastNode = think_list_last_node(pList);

    if (NULL == pLastNode) {
        return pNode;
    }

    pLastNode->m_pNext = pNode;
    pNode->m_pPre = pLastNode;

    return think_list_first_node(pList);
}

ThinkList* think_list_prepend(ThinkList* pList, void* pData)
{
    return_val_if_fail(pData != NULL, pList);

    ThinkList* pNode = think_list_create_node(pData);
    if (NULL == pList) {
        return pNode;
    }

    pNode->m_pNext = pList;
    pList->m_pPre = pNode;

    return think_list_first_node(pList);
}

ThinkList* think_list_insert(ThinkList* pList, void* pData, unsigned int nIndex)
{
    return_val_if_fail(pData != NULL, pList);

    if (NULL == pList && nIndex != 0) {
        return pList;
    }

    if (pList != NULL && nIndex > think_list_length(pList)) {
        return pList;
    }

    if (NULL == pList || 0 == nIndex) {
        return think_list_prepend(pList, pData);
    }

    if (pList != NULL && nIndex == think_list_length(pList)) {
        return think_list_append(pList, pData);
    }

    int i = 0;
    ThinkList* pHead = pList;
    ThinkList* pNode = pList;
    ThinkList* pNewNode = think_list_create_node(pData);
    while (pNode && i < nIndex) {
        i += 1;
        pNode = pNode->m_pNext;
    }

    pNewNode->m_pNext = pNode;
    pNewNode->m_pPre = pNode->m_pPre;

    pNode->m_pPre->m_pNext = pNewNode;
    pNode->m_pPre = pNewNode;

    return think_list_first_node(pList);
}

ThinkList* think_list_concat(ThinkList* pList1, ThinkList* pList2)
{
    if (NULL == pList1) {
        return pList2;
    }

    if (NULL == pList2) {
        return pList1;
    }

    ThinkList* pLastNode = think_list_last_node(pList1);
    pLastNode->m_pNext = pList2;
    pList2->m_pPre = pLastNode;

    return think_list_first_node(pList1);
}

ThinkList* think_list_remove(ThinkList* pList, void* pData, ThinkDestoryFunc pFunc)
{
    if (NULL == pData) {
        return pList;
    }

    if (pData == pList->m_pData) {
        ThinkList* pHead = pList->m_pNext;

        if (pFunc) {
            (*pFunc)(pList->m_pData);
        }
        think_list_free_node(&pList);

        if (pHead) {
            pHead->m_pPre = NULL;
        }

        return think_list_first_node(pHead);
    }

    int bFound = 0;
    ThinkList* pNode = pList;
    while (pNode) {
        if (pData == pNode->m_pData) {
            bFound = 1;
            break;
        }
        pNode = pNode->m_pNext;
    }

    if (bFound) {
        if (NULL == pNode->m_pNext) {
            pNode->m_pPre->m_pNext = NULL;

            if (pFunc) {
                (*pFunc)(pList->m_pData);
            }
            think_list_free_node(&pNode);
        } else {
            pNode->m_pNext->m_pPre = pNode->m_pPre;
            pNode->m_pPre->m_pNext = pNode->m_pNext;

            if (pFunc) {
                (*pFunc)(pList->m_pData);
            }
            think_list_free_node(&pNode);
        }
    }

    return think_list_first_node(pList);
}

ThinkList* think_list_remove_at(ThinkList* pList, unsigned int nIndex, ThinkDestoryFunc pFunc)
{
    return_val_if_fail(pList != NULL, pList);
    return_val_if_fail(nIndex < think_list_length(pList), pList);

    void* pData = think_list_get(pList, nIndex);

    return think_list_remove(pList, pData, pFunc);
}

void* think_list_get(ThinkList* pList, unsigned int nIndex)
{
    return_val_if_fail(pList != NULL, NULL);
    return_val_if_fail(nIndex < think_list_length(pList), NULL);

    ThinkList* pNode = pList;
    for (int i = 0; i < nIndex; ++i) {
        pNode = pNode->m_pNext;
    }

    return pNode->m_pData;
}

static ThinkList* think_list_get_node(ThinkList* pList, unsigned int nIndex)
{
    return_val_if_fail(pList != NULL, NULL);
    return_val_if_fail(nIndex < think_list_length(pList), NULL);

    ThinkList* pNode = pList;
    for (int i = 0; i < nIndex; ++i) {
        pNode = pNode->m_pNext;
    }

    return pNode;
}

void* think_list_pop(ThinkList** ppList)
{
    return_val_if_fail(ppList != NULL, NULL);
    return_val_if_fail(*ppList != NULL, NULL);

    ThinkList* pNode = *ppList;
    void* pRet = pNode->m_pData;

    *ppList = think_list_remove_at(*ppList, 0, NULL);

    return pRet;
}

void* think_list_pop_tail(ThinkList** ppList)
{
    return_val_if_fail(ppList != NULL, NULL);
    return_val_if_fail(*ppList != NULL, NULL);

    void* pData = think_list_get(*ppList, think_list_length(*ppList) - 1);
    *ppList = think_list_remove_at(*ppList, think_list_length(*ppList) - 1, NULL);

    return pData;
}

unsigned int think_list_length(ThinkList* pList)
{
    return_val_if_fail(pList != NULL, 0);

    ThinkList* pNode = pList;

    unsigned int nLength = 0;
    while (pNode) {
        nLength++;
        pNode = pNode->m_pNext;
    }

    return nLength;
}

void think_list_free(ThinkList** pList, ThinkDestoryFunc pFunc)
{
    return_if_fail(pList != NULL);
    return_if_fail(*pList != NULL);

    while (*pList != NULL) {
        *pList = think_list_remove_at(*pList, 0, pFunc);
    }
}

static void think_list_sort_real(ThinkList* pList, ThinkCompareDataFunc pCompareFunc, unsigned int nStart, unsigned int nEnd)
{
    return_if_fail(pList != NULL);
    return_if_fail(pCompareFunc != NULL);
    return_if_fail(nStart < nEnd);

    unsigned int nFirst = nStart;
    unsigned int nLast = nEnd;
    void* pKey = think_list_get(pList, nFirst);

    while(nFirst < nLast)
    {
        while(nFirst < nLast && pCompareFunc(think_list_get(pList, nLast), pKey) >= 0) {
            --nLast;
        }

        ThinkList* pNode1 = think_list_get_node(pList, nFirst);
        ThinkList* pNode2 = think_list_get_node(pList, nLast);
        pNode1->m_pData = pNode2->m_pData;

        while(nFirst < nLast && pCompareFunc(think_list_get(pList, nFirst), pKey) <= 0) {
            ++nFirst;
        }

        pNode1 = think_list_get_node(pList, nLast);
        pNode2 = think_list_get_node(pList, nFirst);
        pNode1->m_pData = pNode2->m_pData;
    }

    ThinkList* pNode1 = think_list_get_node(pList, nFirst);
    pNode1->m_pData = pKey;
    if (nFirst > 0) {
        think_list_sort_real(pList, pCompareFunc, nStart, nFirst - 1);
    }
    think_list_sort_real(pList, pCompareFunc, nFirst + 1, nEnd);
}

void think_list_sort(ThinkList* pList, ThinkCompareDataFunc pFunc)
{
    return_if_fail(pList != NULL);
    return_if_fail(pFunc != NULL);
    return_if_fail(think_list_length(pList) > 1);

    think_list_sort_real(pList, pFunc, 0, think_list_length(pList) - 1);
}
