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

void think_btree_free(ThinkBTree** ppTree)
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
    /*
    1
     \
       3
     /   \
    2     5
         /  \
        4    7
            / \
           6   9
              / \
             8   10

     find node for remove and its parent

     if (parent == nNode)
         means remove root
         if root->left
             root = root->left
             add root->right
             destory node
         else
             root = root->right
     else
         pParentLeft = parent->left
         pParentRight = parent->right
         pLeft = node->left
         pRight = node->Right

         destory node

         add pParentLeft
         add pParentRight
         add pLeft
         add pRight

     */
    return_val_if_fail(pTree != NULL, false);

    ThinkBTreeNode* pParent = pTree->m_pNodeRoot;
    ThinkBTreeNode* pCur = pParent;
    bool bFound = false;

    while (pCur) {
        int nVal = (pTree->m_pCompareFunc)(pData, pCur->m_pData);
        if (nVal < 0) {
            pParent = pCur;
            pCur = pCur->m_pChildLeft;
        } else if (0 == nVal) {
            bFound = true;
            break;
        } else { //nVal > 0
            pParent = pCur;
            pCur = pCur->m_pChildRight;
        }
    }

    return_val_if_fail(bFound != false, false);

    if (pParent == pCur) {
        //remove root
        if (pCur->m_pChildLeft) {
            pTree->m_pNodeRoot = pCur->m_pChildLeft;

            ThinkBTreeNode* pCurRight = pCur->m_pChildRight;
            think_btree_insert_node(pTree, pCurRight);
        } else if (pCur->m_pChildRight) {
            pTree->m_pNodeRoot = pCur->m_pChildRight;

            ThinkBTreeNode* pCurLeft = pCur->m_pChildLeft;
            think_btree_insert_node(pTree, pCurLeft);

        } else {
            pTree->m_pNodeRoot = NULL;
        }

        think_btree_destory_node(pTree, &pCur);
    } else {
        ThinkBTreeNode* pParentLeft = pParent->m_pChildLeft;
        ThinkBTreeNode* pParentRight = pParent->m_pChildRight;
        ThinkBTreeNode* pCurLeft = pCur->m_pChildLeft;
        ThinkBTreeNode* pCurRight = pCur->m_pChildRight;

        if (pParentLeft == pCur) {
            pParentLeft = NULL;
        }

        if (pParentRight == pCur) {
            pParentRight = NULL;
        }
        pParent->m_pChildLeft = NULL;
        pParent->m_pChildRight = NULL;

        think_btree_destory_node(pTree, &pCur);

        think_btree_insert_node(pTree, pParentLeft);
        think_btree_insert_node(pTree, pParentRight);
        think_btree_insert_node(pTree, pCurLeft);
        think_btree_insert_node(pTree, pCurRight);
    }

    return true;
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
