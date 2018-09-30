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
static void think_btree_node_foreach(ThinkBTreeNode* pRoot, ThinkCommonFunc pFunc, void* pUserData, ForEachMethod method);
void think_btree_insert_node(ThinkBTree* pTree, ThinkBTreeNode* pNodeNew);
static void think_btree_destory_node(ThinkBTree* pTree, ThinkBTreeNode** ppNode);

ThinkBTree* think_btree_new(ThinkCompareDataFunc pCompareFunc, ThinkDestoryFunc pDestoryFunc)
{
    return_val_if_fail(pCompareFunc != NULL, NULL);
    ThinkBTree* pTree = (ThinkBTree*) malloc(sizeof(ThinkBTree));
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

static void think_btree_destory_node(ThinkBTree* pTree, ThinkBTreeNode** ppNode)
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

void think_btree_insert_node(ThinkBTree* pTree, ThinkBTreeNode* pNodeNew) {
    return_if_fail(pTree != NULL);
    return_if_fail(pNodeNew != NULL);

    ThinkBTreeNode* pParent = pTree->m_pNodeRoot;
    ThinkBTreeNode* pCur = pParent;
    while (pCur) {
        int nVal = (pTree->m_pCompareFunc)(pNodeNew->m_pData, pCur->m_pData);
        if (nVal < 0) {
            pParent = pCur;
            pCur = pCur->m_pChildLeft;
        } else {
            pParent = pCur;
            pCur = pCur->m_pChildRight;
        }
    }

    int nVal = (pTree->m_pCompareFunc)(pNodeNew->m_pData, pParent->m_pData);
    if (nVal < 0) {
        pParent->m_pChildLeft = pNodeNew;
    } else {
        pParent->m_pChildRight = pNodeNew;
    }
}

void think_btree_insert(ThinkBTree* pTree, void* pData)
{
    return_if_fail(pTree != NULL);
    return_if_fail(pData != NULL);

    if (NULL == pTree->m_pNodeRoot) {
        pTree->m_pNodeRoot = think_btree_node_new(pData);
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

    ThinkBTreeNode* pNodeNew = think_btree_node_new(pData);
    think_btree_insert_node(pTree, pNodeNew);
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
    return_val_if_fail(pTree != NULL, false);

    ThinkBTreeNode* pParent = pTree->m_pNodeRoot;
    ThinkBTreeNode* pCur = pParent;

    while (pCur != NULL) {
        int nVal = (pTree->m_pCompareFunc)(pData, pCur->m_pData);
        if (nVal < 0) {
            pParent = pCur;
            pCur = pCur->m_pChildLeft;
        } else if (0 == nVal) {
            if (pParent->m_pChildLeft == pCur) {
                pParent->m_pChildLeft = NULL;
            } else {
                pParent->m_pChildRight = NULL;
            }
            ThinkBTreeNode *pLeft = pCur->m_pChildLeft;
            ThinkBTreeNode *pRight = pCur->m_pChildRight;

            think_btree_destory_node(pTree, &pCur);

            ThinkBTreeNode* pParentLeft = pParent->m_pChildLeft;
            pParent->m_pChildLeft = NULL;

            ThinkBTreeNode* pParentRight = pParent->m_pChildRight;
            pParent->m_pChildRight = NULL;

            if (pTree->m_pNodeRoot == pLeft) {
                think_btree_insert_node(pTree, pRight);
            } else {
                think_btree_insert_node(pTree, pLeft);
                think_btree_insert_node(pTree, pRight);

                think_btree_insert_node(pTree, pParentLeft);
                think_btree_insert_node(pTree, pParentRight);
            }

            return true;
        } else { //nVal > 0
            pParent = pCur;
            pCur = pCur->m_pChildRight;
        }
    }


    return false;
}

static ThinkBTreeNode* think_btree_node_exists(ThinkBTree* pTree, const void* pData)
{
    return_val_if_fail(pTree != NULL, NULL);
    return_val_if_fail(pData != NULL, NULL);

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

static unsigned int think_btree_size_real(ThinkBTreeNode* pRoot)
{
    return_val_if_fail(pRoot != NULL, 0);

    unsigned int nChildCount = 0;
    if (pRoot->m_pChildLeft) {
        nChildCount++;
    }

    if (pRoot->m_pChildRight) {
        nChildCount++;
    }

    return (nChildCount += (think_btree_size_real(pRoot->m_pChildLeft) + think_btree_size_real(pRoot->m_pChildRight)));
}

unsigned int think_btree_size(ThinkBTree* pTree)
{
    return_val_if_fail(pTree != NULL, 0);

    return 1 + think_btree_size_real(pTree->m_pNodeRoot);
}
