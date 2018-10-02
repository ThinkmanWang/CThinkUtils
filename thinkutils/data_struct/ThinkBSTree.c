
#include "ThinkBSTree.h"

#include <stdio.h>
#include <stdlib.h>

static ThinkBSTreeNode* think_bstree_node_new(void* pData);
static void think_bstree_node_destory(ThinkBSTree* pTree, ThinkBSTreeNode** ppNode);
static ThinkBSTreeNode* think_bstree_node_exists(ThinkBSTree* pTree, const void* pData);
static ThinkBSTreeNode* think_bstree_max_node(ThinkBSTree* pTree, ThinkBSTreeNode* pNode);
void think_btree_insert_node(ThinkBSTree* pTree, ThinkBSTreeNode* pNodeNew) {

static void think_btree_insert_node(ThinkBSTree* pTree, ThinkBSTreeNode* pNodeNew) {
    return_if_fail(pTree != NULL);
    return_if_fail(pNodeNew != NULL);

    ThinkBSTreeNode* pCur = pTree->m_pNodeRoot;
    if (NULL == pCur) {
        pTree->m_pNodeRoot = pNodeNew;
        return;
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

}

void think_bstree_foreach_dlr(ThinkBSTree* pTree, ThinkCommonFunc func, void* pUserData)
{

}

void think_bstree_foreach_ldr(ThinkBSTree* pTree, ThinkCommonFunc func, void* pUserData)
{

}

void think_bstree_foreach_lrd(ThinkBSTree* pTree, ThinkCommonFunc func, void* pUserData)
{

}

bool think_bstree_remove(ThinkBSTree* pTree, const void* pData)
{
    return false;
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
