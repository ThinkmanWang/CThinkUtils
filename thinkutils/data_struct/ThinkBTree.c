#include "ThinkBTree.h"

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    FOREACH_BY_DLR
    , FOREACH_BY_LDR
    , FOREACH_BY_LRD
} ForEachMethod;

static ThinkBTreeNode* think_btree_node_new(void* pData);
static ThinkBTreeNode* think_btree_node_exists(ThinkBTree* pTree, const void* pData);
static void think_btree_node_destory(ThinkBTree* pTree, ThinkBTreeNode** ppNode);
static void think_btree_node_foreach(ThinkBTreeNode* pRoot, ThinkCommonFunc pFunc, void* pUserData, ForEachMethod method);

ThinkBTree* think_btree_new(ThinkCompareDataFunc pCompareFunc, ThinkDestoryFunc pDestoryFunc)
{
    return_val_if_fail(pCompareFunc != NULL, NULL);
    ThinkBTree* pTree = (ThinkBTree*) malloc(sizeof(ThinkBTree));
    pTree->m_nSize = 0;
    pTree->m_pNodeRoot = NULL;
    pTree->m_pCompareFunc = pCompareFunc;
    pTree->m_pDestoryFunc = pDestoryFunc;

    return pTree;
}

static ThinkBTreeNode* think_btree_node_new(void* pData)
{
    ThinkBTreeNode* pNode = (ThinkBTreeNode*) malloc(sizeof(ThinkBTreeNode));
    pNode->m_pData = pData;
    pNode->m_pChildLeft = NULL;
    pNode->m_pChildRight = NULL;

    return pNode;
}

static void think_btree_node_destory(ThinkBTree* pTree, ThinkBTreeNode** ppNode)
{
    if (pTree->m_pDestoryFunc) {
        (pTree->m_pDestoryFunc)((*ppNode)->m_pData);
    }

    free(*ppNode);
    *ppNode = NULL;
}

void think_btree_destory(ThinkBTree** ppTree)
{

}


void think_btree_insert(ThinkBTree* pTree, void* pData)
{
    return_if_fail(pTree != NULL);
    return_if_fail(pData != NULL);

    if (NULL == pTree->m_pNodeRoot) {
        pTree->m_pNodeRoot = think_btree_node_new(pData);
        pTree->m_nSize++;
        return;
    }

    ThinkBTreeNode* pOldNode = think_btree_node_exists(pTree, pData);
    if (NULL != pOldNode) {
        if (pTree->m_pDestoryFunc) {
            (pTree->m_pDestoryFunc)(pOldNode->m_pData);
            pOldNode->m_pData = NULL;
        }

        pOldNode->m_pData = pData;

        return;
    }

    ThinkBTreeNode* pParent = pTree->m_pNodeRoot;
    ThinkBTreeNode* pCur = pParent;
    while (pCur) {
        int nVal = (pTree->m_pCompareFunc)(pData, pCur->m_pData);
        if (nVal < 0) {
            pParent = pCur;
            pCur = pCur->m_pChildLeft;
        } else {
            pParent = pCur;
            pCur = pCur->m_pChildRight;
        }
    }

    ThinkBTreeNode* pNodeNew = think_btree_node_new(pData);
    int nVal = (pTree->m_pCompareFunc)(pData, pParent->m_pData);
    if (nVal < 0) {
        pParent->m_pChildLeft = pNodeNew;
    } else {
        pParent->m_pChildRight = pNodeNew;
    }
    pTree->m_nSize++;
}

static void think_btree_node_foreach(ThinkBTreeNode* pRoot, ThinkCommonFunc pFunc, void* pUserData, ForEachMethod method)
{
    return_if_fail(pRoot != NULL);
    return_if_fail(pFunc != NULL);

    if (FOREACH_BY_DLR == method) {
        pFunc(pRoot->m_pData, pUserData);
        think_btree_node_foreach(pRoot->m_pChildLeft, pFunc, pUserData, method);
        think_btree_node_foreach(pRoot->m_pChildRight, pFunc, pUserData, method);
    } else if (FOREACH_BY_LDR == method) {
        think_btree_node_foreach(pRoot->m_pChildLeft, pFunc, pUserData, method);
        pFunc(pRoot->m_pData, pUserData);
        think_btree_node_foreach(pRoot->m_pChildRight, pFunc, pUserData, method);
    } else {
        think_btree_node_foreach(pRoot->m_pChildLeft, pFunc, pUserData, method);
        think_btree_node_foreach(pRoot->m_pChildRight, pFunc, pUserData, method);
        pFunc(pRoot->m_pData, pUserData);
    }
}

void think_btree_foreach_ldr(ThinkBTree* pTree, ThinkCommonFunc pFunc, void* pUserData)
{
    return_if_fail(pTree != NULL);
    return_if_fail(pFunc != NULL);

    think_btree_node_foreach(pTree->m_pNodeRoot, pFunc, pUserData, FOREACH_BY_LDR);
}

void think_btree_foreach_lrd(ThinkBTree* pTree, ThinkCommonFunc pFunc, void* pUserData)
{
    return_if_fail(pTree != NULL);
    return_if_fail(pFunc != NULL);

    think_btree_node_foreach(pTree->m_pNodeRoot, pFunc, pUserData, FOREACH_BY_LRD);
}

void think_btree_foreach_dlr(ThinkBTree* pTree, ThinkCommonFunc pFunc, void* pUserData)
{
    return_if_fail(pTree != NULL);
    return_if_fail(pFunc != NULL);

    think_btree_node_foreach(pTree->m_pNodeRoot, pFunc, pUserData, FOREACH_BY_DLR);
}

bool think_btree_remove(ThinkBTree* pTree, const void* pData)
{
    return false;
}

static ThinkBTreeNode* think_btree_node_exists(ThinkBTree* pTree, const void* pData)
{
    return_val_if_fail(pTree != NULL, NULL);
    return_val_if_fail(pData != NULL, NULL);

    if (0 == pTree->m_nSize) {
        return NULL;
    }

    ThinkBTreeNode* pNode = pTree->m_pNodeRoot;
    while (pNode != NULL) {
        int nVal = (pTree->m_pCompareFunc)(pData, pNode->m_pData);
        if (nVal < 0) {
            pNode = pNode->m_pChildLeft;
        } else if (0 == nVal) {
            return pNode;
        } else { //nVal > 0
            pNode = pNode->m_pChildRight;
        }
    }

    return NULL;
}

bool think_btree_exists(ThinkBTree* pTree, const void* pData)
{
    return_val_if_fail(pTree != NULL, false);
    return_val_if_fail(pData != NULL, false);

    ThinkBTreeNode* pNode = think_btree_node_exists(pTree, pData);
    return NULL != pNode;
}

unsigned int think_btree_size(ThinkBTree* pTree)
{
    return_val_if_fail(pTree != NULL, 0);

    return pTree->m_nSize;
}
