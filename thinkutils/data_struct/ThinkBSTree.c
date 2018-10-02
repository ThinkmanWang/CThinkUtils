
#include "ThinkBSTree.h"

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    FOREACH_BY_DLR
    , FOREACH_BY_LDR
    , FOREACH_BY_LRD
} ForEachMethod;

static ThinkBSTreeNode* think_bstree_node_new(void* pData);
static void think_bstree_node_destory(ThinkBSTree* pTree, ThinkBSTreeNode** ppNode);
static ThinkBSTreeNode* think_bstree_node_exists(ThinkBSTree* pTree, const void* pData);
static ThinkBSTreeNode* think_bstree_max_node(ThinkBSTree* pTree, ThinkBSTreeNode* pNode);
static ThinkBSTreeNode* think_bstree_min_node(ThinkBSTree* pTree, ThinkBSTreeNode* pNode);
static void think_bstree_insert_node(ThinkBSTree* pTree, ThinkBSTreeNode* pNodeNew);
static void think_bstree_remove_node(ThinkBSTree* pTree, ThinkBSTreeNode* pNodeRemove);
static void think_bstree_update_height(ThinkBSTreeNode* pNode);
static void think_bstree_node_foreach(ThinkBSTreeNode* pRoot, ThinkCommonFunc pFunc, void* pUserData, ForEachMethod method);

static void think_bstree_node_foreach(ThinkBSTreeNode* pRoot, ThinkCommonFunc pFunc, void* pUserData, ForEachMethod method)
{
    return_if_fail(pRoot != NULL);
    return_if_fail(pFunc != NULL);

    if (FOREACH_BY_DLR == method) {
        pFunc(pRoot->m_pData, pUserData);
        think_bstree_node_foreach(pRoot->m_pChildLeft, pFunc, pUserData, method);
        think_bstree_node_foreach(pRoot->m_pChildRight, pFunc, pUserData, method);
    } else if (FOREACH_BY_LDR == method) {
        think_bstree_node_foreach(pRoot->m_pChildLeft, pFunc, pUserData, method);
        pFunc(pRoot->m_pData, pUserData);
        think_bstree_node_foreach(pRoot->m_pChildRight, pFunc, pUserData, method);
    } else {
        think_bstree_node_foreach(pRoot->m_pChildLeft, pFunc, pUserData, method);
        think_bstree_node_foreach(pRoot->m_pChildRight, pFunc, pUserData, method);
        pFunc(pRoot->m_pData, pUserData);
    }
}

static void think_bstree_update_height(ThinkBSTreeNode* pNode)
{
    return_if_fail(pNode != NULL);

    ThinkBSTreeNode* pChild = pNode;

    while (pChild->m_pParent) {
        ThinkBSTreeNode* pParent = pChild->m_pParent;
        if (pParent->m_pChildLeft == pChild) {
            pParent->m_nHeightLeft = max(pChild->m_nHeightLeft, pChild->m_nHeightRight) + 1;
        } else {
            pParent->m_nHeightRight = max(pChild->m_nHeightLeft, pChild->m_nHeightRight) + 1;
        }

        pChild = pChild->m_pParent;
    }
}

static void think_bstree_insert_node(ThinkBSTree* pTree, ThinkBSTreeNode* pNodeNew) {
    return_if_fail(pTree != NULL);
    return_if_fail(pNodeNew != NULL);

    ThinkBSTreeNode* pCur = pTree->m_pNodeRoot;
    if (NULL == pCur) {
        pTree->m_pNodeRoot = pNodeNew;
        goto insert_ret;
    }

    ThinkBSTreeNode* pParent = pCur;
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
        pNodeNew->m_pParent = pParent;
    } else {
        pParent->m_pChildRight = pNodeNew;
        pNodeNew->m_pParent = pParent;
    }

insert_ret:
    think_bstree_update_height(pNodeNew);
    pTree->m_nSize++;
}

static void think_bstree_remove_node(ThinkBSTree* pTree, ThinkBSTreeNode* pNodeRemove)
{
    /*
     if remove root node
         if left child
             make max node in left sub tree as root
         else right tree
             make child right as root
         else
            means only one node in this bstree
            free node and set pTree->root as NULL
     else
         if left child
             make max node in left for replace
         else right tree
             make min node in right for replace
         else
            means only one node in this sub bstree
            free node

     update tree height for pNode
     update tree height for maxNode in subtree
     */

    if (pTree->m_pNodeRoot == pNodeRemove) {
        if (pTree->m_pNodeRoot->m_pChildLeft) {
            ThinkBSTreeNode* pMaxSubNode = think_bstree_max_node(pTree, pTree->m_pNodeRoot->m_pChildLeft);
            pNodeRemove->m_pData = pMaxSubNode->m_pData;

            if (pMaxSubNode == pMaxSubNode->m_pParent->m_pChildLeft) {
                pMaxSubNode->m_pParent->m_nHeightLeft -= 1;
                pMaxSubNode->m_pParent->m_pChildLeft = NULL;
            } else {
                pMaxSubNode->m_pParent->m_nHeightRight -= 1;
                pMaxSubNode->m_pParent->m_pChildRight = NULL;
            }

            think_bstree_update_height(pMaxSubNode->m_pParent);
            think_bstree_node_destory(pTree, &pMaxSubNode);
        } else if (pTree->m_pNodeRoot->m_nHeightRight) {
            pTree->m_pNodeRoot = pNodeRemove->m_pChildRight;
            pNodeRemove->m_pChildRight->m_pParent = NULL;

            think_bstree_node_destory(pTree, &pNodeRemove);
        } else {
            pTree->m_pNodeRoot = NULL;
            think_bstree_node_destory(pTree, &pNodeRemove);
        }

    } else {
        if (pNodeRemove->m_pChildLeft) {
            ThinkBSTreeNode* pMaxSubNode = think_bstree_max_node(pTree, pNodeRemove->m_pChildLeft);
            pNodeRemove->m_pData = pMaxSubNode->m_pData;

            if (pMaxSubNode == pMaxSubNode->m_pParent->m_pChildLeft) {
                pMaxSubNode->m_pParent->m_nHeightLeft -= 1;
                pMaxSubNode->m_pParent->m_pChildLeft = NULL;
            } else {
                pMaxSubNode->m_pParent->m_nHeightRight -= 1;
                pMaxSubNode->m_pParent->m_pChildRight = NULL;
            }

            think_bstree_update_height(pMaxSubNode->m_pParent);
            think_bstree_node_destory(pTree, &pMaxSubNode);
        } else if (pNodeRemove->m_pChildRight) {
            ThinkBSTreeNode* pMinSubNode = think_bstree_min_node(pTree, pNodeRemove->m_pChildRight);

            pNodeRemove->m_pData = pMinSubNode->m_pData;

            if (pMinSubNode == pMinSubNode->m_pParent->m_pChildLeft) {
                pMinSubNode->m_pParent->m_nHeightLeft -= 1;
                pMinSubNode->m_pParent->m_pChildLeft = NULL;
            } else {
                pMinSubNode->m_pParent->m_nHeightRight -= 1;
                pMinSubNode->m_pParent->m_pChildRight = NULL;
            }

            think_bstree_update_height(pMinSubNode->m_pParent);
            think_bstree_node_destory(pTree, &pMinSubNode);
        } else {
            if (pNodeRemove == pNodeRemove->m_pParent->m_pChildLeft) {
                pNodeRemove->m_pParent->m_nHeightLeft -= 1;
                pNodeRemove->m_pParent->m_pChildLeft = NULL;
            } else {
                pNodeRemove->m_pParent->m_nHeightRight -= 1;
                pNodeRemove->m_pParent->m_pChildRight = NULL;
            }

            think_bstree_update_height(pNodeRemove->m_pParent);
            think_bstree_node_destory(pTree, &pNodeRemove);

        }
    }

    think_bstree_update_height(pNodeRemove);

}

static ThinkBSTreeNode* think_bstree_node_new(void* pData)
{
    return_val_if_fail(pData != NULL, NULL);

    /*
    void* m_pData;

    unsigned int m_nSize;

    unsigned int m_nLeftHeight;
    unsigned int m_nRightHeight;

    struct _ThinkBSTreeNode* m_pParent;
    struct _ThinkBSTreeNode* m_pChildLeft;
    struct _ThinkBSTreeNode* m_pChildRight;
     */

    ThinkBSTreeNode* pNode = (ThinkBSTreeNode*) malloc(sizeof(ThinkBSTreeNode));
    pNode->m_pData = pData;

    pNode->m_nHeightLeft = 0;
    pNode->m_nHeightRight = 0;

    pNode->m_pParent = NULL;
    pNode->m_pChildLeft = NULL;
    pNode->m_pChildRight = NULL;

    return pNode;
}

static void think_bstree_node_destory(ThinkBSTree* pTree, ThinkBSTreeNode** ppNode)
{
    if (pTree->m_pDestoryFunc) {
        (pTree->m_pDestoryFunc)((*ppNode)->m_pData);
    }

    free(*ppNode);
    *ppNode = NULL;
}

static ThinkBSTreeNode* think_bstree_node_exists(ThinkBSTree* pTree, const void* pData)
{
    return_val_if_fail(pTree != NULL, NULL);
    return_val_if_fail(pData != NULL, NULL);

    ThinkBSTreeNode* pNode = pTree->m_pNodeRoot;
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

static ThinkBSTreeNode* think_bstree_max_node(ThinkBSTree* pTree, ThinkBSTreeNode* pNode)
{
    return_val_if_fail(pTree != NULL, NULL);
    return_val_if_fail(pNode != NULL, NULL);

    ThinkBSTreeNode* pCur = pNode;
    while (pCur->m_pChildRight) {
        pCur = pCur->m_pChildRight;
    }

    return pCur;
}

static ThinkBSTreeNode* think_bstree_min_node(ThinkBSTree* pTree, ThinkBSTreeNode* pNode)
{
    return_val_if_fail(pTree != NULL, NULL);
    return_val_if_fail(pNode != NULL, NULL);

    ThinkBSTreeNode* pCur = pNode;
    while (pCur->m_pChildLeft) {
        pCur = pCur->m_pChildLeft;
    }

    return pCur;
}

ThinkBSTree* think_bstree_new(ThinkCompareDataFunc pCompareFunc, ThinkDestoryFunc pDestoryFunc)
{
    return_val_if_fail(pCompareFunc != NULL, NULL);

    /*
    ThinkBSTreeNode* m_pNodeRoot;
    unsigned int m_nSize;

    ThinkDestoryFunc m_pDestoryFunc;
    ThinkCompareDataFunc m_pCompareFunc;
     */

    ThinkBSTree* pTree = (ThinkBSTree*) malloc(sizeof(ThinkBSTree));

    pTree->m_pNodeRoot = NULL;
    pTree->m_nSize = 0;
    pTree->m_pCompareFunc = pCompareFunc;
    pTree->m_pDestoryFunc = pDestoryFunc;

    return pTree;
}

void think_bstree_destory(ThinkBSTree** ppTree)
{

}

void think_bstree_insert(ThinkBSTree* pTree, void* pData)
{
    return_if_fail(pTree != NULL);
    return_if_fail(pData != NULL);

    ThinkBSTreeNode* pNode = think_bstree_node_exists(pTree, pData);
    if (pNode) {
        if (pTree->m_pDestoryFunc) {
            (pTree->m_pDestoryFunc)(pNode->m_pData);
            pNode->m_pData = NULL;
        }

        pNode->m_pData = pData;

        return;
    }

    pNode = think_bstree_node_new(pData);
    think_bstree_insert_node(pTree, pNode);
}

void think_bstree_foreach_dlr(ThinkBSTree* pTree, ThinkCommonFunc pFunc, void* pUserData)
{
    return_if_fail(pTree != NULL);
    return_if_fail(pFunc != NULL);

    think_bstree_node_foreach(pTree->m_pNodeRoot, pFunc, pUserData, FOREACH_BY_DLR);
}

void think_bstree_foreach_ldr(ThinkBSTree* pTree, ThinkCommonFunc pFunc, void* pUserData)
{
    return_if_fail(pTree != NULL);
    return_if_fail(pFunc != NULL);

    think_bstree_node_foreach(pTree->m_pNodeRoot, pFunc, pUserData, FOREACH_BY_LDR);
}

void think_bstree_foreach_lrd(ThinkBSTree* pTree, ThinkCommonFunc pFunc, void* pUserData)
{
    return_if_fail(pTree != NULL);
    return_if_fail(pFunc != NULL);

    think_bstree_node_foreach(pTree->m_pNodeRoot, pFunc, pUserData, FOREACH_BY_LRD);
}

bool think_bstree_remove(ThinkBSTree* pTree, const void* pData)
{
    ThinkBSTreeNode* pNode = think_bstree_node_exists(pTree, pData);
    if (NULL == pNode) {
        return false;
    }

    think_bstree_remove_node(pTree, pNode);
    pTree->m_nSize--;

    return true;
}

bool think_bstree_exists(ThinkBSTree* pTree, const void* pData)
{
    ThinkBSTreeNode* pNode = think_bstree_node_exists(pTree, pData);

    return (pNode != NULL);
}

unsigned int think_bstree_size(ThinkBSTree* pTree)
{
    return pTree->m_nSize;
}

unsigned int think_bstree_height(ThinkBSTree* pTree)
{
    return_val_if_fail(pTree != NULL, 0);

    return max(pTree->m_pNodeRoot->m_nHeightLeft, pTree->m_pNodeRoot->m_nHeightRight) + 1;
}
