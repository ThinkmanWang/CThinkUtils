#include "ThinkTree.h"

#include <stdlib.h>

static void think_tree_size_real(ThinkTree* pTree, unsigned int* pCount);

ThinkTree* think_tree_new(void* pData)
{
    ThinkTree* pTree = (ThinkTree*) malloc(sizeof(ThinkTree));

    pTree->m_pData = pData;
    pTree->m_pParent = NULL;
    pTree->m_pPre = NULL;
    pTree->m_pNext = NULL;
    pTree->m_pChildren = NULL;

    return pTree;
}

void think_tree_unlink(ThinkTree* pTree)
{
    return_if_fail(pTree != NULL);

    if (pTree->m_pPre) {
        pTree->m_pPre->m_pNext = pTree->m_pNext;
    }

    if (pTree->m_pNext) {
        pTree->m_pNext->m_pPre = pTree->m_pPre;
    }

    if (pTree->m_pParent
        && pTree->m_pParent->m_pChildren == pTree) {
        pTree->m_pParent->m_pChildren = pTree->m_pNext;
    }

    pTree->m_pParent = NULL;
    pTree->m_pPre = NULL;
    pTree->m_pNext = NULL;
}

void think_tree_free(ThinkTree** ppTree, ThinkDestoryFunc pDestoryFunc)
{
    return_if_fail(ppTree != NULL);
    return_if_fail((*ppTree) != NULL);

    ThinkTree* pCur = *ppTree;
    while (pCur) {
        ThinkTree* pNext = pCur->m_pNext;

        if (pCur->m_pChildren) {
            think_tree_free(&pCur->m_pChildren, pDestoryFunc);
        }

        if (pDestoryFunc) {
            (pDestoryFunc)((*ppTree)->m_pData);
        }
        free(pCur);
        pCur = NULL;

        pCur = pNext;
    }

    *ppTree = NULL;
}

ThinkTree* think_tree_get_child(ThinkTree* pTree, unsigned int nPos)
{
    return_val_if_fail(pTree != NULL, NULL);
    return_val_if_fail(pTree->m_pChildren != NULL, NULL);

    ThinkTree* pCur = pTree->m_pChildren;
    for (unsigned int i = 0; i < nPos; ++i) {
        if (pCur->m_pNext) {
            pCur = pCur->m_pNext;
        } else {
            return NULL;
        }
    }

    return pCur;
}

ThinkTree* think_tree_insert(ThinkTree* pParent, unsigned int nPos, void* pData)
{
    return_val_if_fail(pParent != NULL, NULL);

    ThinkTree* pNode = think_tree_get_child(pParent, nPos);
    if (NULL == pNode) {
        return think_tree_append(pParent, pData);
    } else {
        return think_tree_insert_before(pParent, pNode, pData);
    }
}

ThinkTree* think_tree_insert_before(ThinkTree* pParent, ThinkTree* pNode, void* pData)
{
    return_val_if_fail(pParent != NULL, NULL);
    return_val_if_fail(pNode != NULL, NULL);

    if (NULL == pNode->m_pPre) {
        return think_tree_prepend(pParent, pData);
    }

    ThinkTree* pNewNode = think_tree_new(pData);
    pNewNode->m_pParent = pParent;

    pNewNode->m_pPre = pNode->m_pPre;
    pNewNode->m_pNext = pNode;

    pNewNode->m_pPre->m_pNext = pNewNode;
    pNewNode->m_pNext->m_pPre = pNewNode;

    return pNewNode;
}

ThinkTree* think_tree_insert_after(ThinkTree* pParent, ThinkTree* pNode, void* pData)
{
    return_val_if_fail(pParent != NULL, NULL);
    return_val_if_fail(pNode != NULL, NULL);

    if (NULL == pNode->m_pNext) {
        think_tree_append(pParent, pData);
    }

    ThinkTree* pNewNode = think_tree_new(pData);
    pNewNode->m_pParent = pParent;

    pNewNode->m_pPre = pNode;
    pNewNode->m_pNext = pNode->m_pNext;

    pNewNode->m_pPre->m_pNext = pNewNode;
    pNewNode->m_pNext->m_pPre = pNewNode;

    return pNewNode;
}

ThinkTree* think_tree_append(ThinkTree* pParent, void* pData)
{
    return_val_if_fail(pParent != NULL, NULL);

    ThinkTree* pNode = think_tree_new(pData);
    pNode->m_pParent = pParent;

    if (NULL == pParent->m_pChildren) {
        pParent->m_pChildren = pNode;
    } else {
        ThinkTree* pCur = pParent->m_pChildren;

        while (pCur->m_pNext) {
            pCur = pCur->m_pNext;
        }

        pCur->m_pNext = pNode;
        pNode->m_pPre = pCur;
    }

    return pNode;
}

ThinkTree* think_tree_prepend(ThinkTree* pParent, void* pData)
{
    return_val_if_fail(pParent != NULL, NULL);

    ThinkTree* pNode = think_tree_new(pData);
    pNode->m_pParent = pParent;

    if (NULL == pParent->m_pChildren) {
        pParent->m_pChildren = pNode;
    } else {
        ThinkTree* pCur = pParent->m_pChildren;

        pNode->m_pNext = pCur;
        pCur->m_pPre = pNode;

        pParent->m_pChildren = pNode;
    }

    return pNode;
}


ThinkTree* think_tree_find(ThinkTree* pTree, void* pData)
{
    return_val_if_fail(pTree != NULL, NULL);
    return_val_if_fail(pData != NULL, NULL);

    if (pTree->m_pData == pData) {
        return pTree;
    }

    if (pTree->m_pChildren) {
        ThinkTree* pChild = pTree->m_pChildren;
        while (pChild) {
            ThinkTree* pRet = think_tree_find(pChild, pData);
            if (pRet) {
                return pRet;
            }
            pChild = pChild->m_pNext;
        }
    }

    return NULL;
}

ThinkTree* think_tree_find_children(ThinkTree* pTree, void* pData)
{
    return_val_if_fail(pTree != NULL, NULL);
    return_val_if_fail(pData != NULL, NULL);
    return_val_if_fail(pTree->m_pChildren != NULL, NULL);

    ThinkTree* pCur = pTree->m_pChildren;
    while (pCur) {
        if (pData == pCur->m_pData) {
            return pCur;
        }

        pCur = pCur->m_pNext;
    }

    return NULL;
}


void think_tree_foreach(ThinkTree* pTree, ThinkCommonFunc pFunc, void* pUserData)
{
    return_if_fail(pTree != NULL);
    return_if_fail(pFunc != NULL);

    pFunc(pTree->m_pData, pUserData);

    if (pTree->m_pChildren) {
        ThinkTree* pChild = pTree->m_pChildren;
        while (pChild) {
            think_tree_foreach(pChild, pFunc, pUserData);
            pChild = pChild->m_pNext;
        }
    }
}

bool think_tree_is_leaf(ThinkTree* pTree)
{
    return_val_if_fail(pTree != NULL, false);
    return (NULL == pTree->m_pChildren);
}

static void think_tree_size_real(ThinkTree* pTree, unsigned int* pCount)
{
    if (pTree->m_pChildren) {
        ThinkTree* pChild;
        (*pCount)++;

        pChild = pTree->m_pChildren;
        while (pChild) {
            think_tree_size_real(pChild, pCount);
            pChild = pChild->m_pNext;
        }
    } else {
        (*pCount)++;
    }
}

unsigned int think_tree_size(ThinkTree* pTree)
{
    return_val_if_fail(pTree != NULL, 0);

    unsigned int nCount = 0;
    think_tree_size_real(pTree, &nCount);

    return nCount;
}

unsigned int think_tree_children_size(ThinkTree* pTree)
{
    return_val_if_fail(pTree != NULL, 0);

    if (NULL == pTree->m_pChildren) {
        return 0;
    }

    ThinkTree* pCur = pTree->m_pChildren;
    unsigned int nSize = 0;

    while (pCur) {
        nSize++;

        pCur = pCur->m_pNext;
    }

    return nSize;
}

unsigned int think_tree_depth(ThinkTree* pTree)
{
    unsigned int nDepth = 0;
    while (pTree) {
        nDepth++;
        pTree = pTree->m_pParent;
    }

    return nDepth;
}

unsigned int think_tree_height(ThinkTree* pTree)
{
    ThinkTree* pChild;
    unsigned int nMaxHeight = 0;

    if (NULL == pTree) {
        return 0;
    }

    pChild = pTree->m_pChildren;
    while (pChild) {
        unsigned int nTmpHeight;

        nTmpHeight = think_tree_height(pChild);
        if (nTmpHeight > nMaxHeight) {
            nMaxHeight = nTmpHeight;
        }

        pChild = pChild->m_pNext;
    }

    return nMaxHeight + 1;
}
