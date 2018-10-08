
#include "ThinkBSTree.h"

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    FOREACH_BY_DLR
    , FOREACH_BY_LDR
    , FOREACH_BY_LRD
} ForEachMethod;

typedef enum {
    NODE_ADD
    , NODE_DEL
} NodeOperation;

typedef enum {
    NODE_ROTETE_CW
    , NODE_ROTETE_ACW
} NodeRotate;

static ThinkBSTreeNode* think_bstree_node_new(void* pData);
static void think_bstree_node_destory(ThinkBSTree* pTree, ThinkBSTreeNode** ppNode, bool bFree);
static ThinkBSTreeNode* think_bstree_node_exists(ThinkBSTree* pTree, const void* pData);
static ThinkBSTreeNode* think_bstree_max_node(ThinkBSTree* pTree, ThinkBSTreeNode* pNode);
static ThinkBSTreeNode* think_bstree_min_node(ThinkBSTree* pTree, ThinkBSTreeNode* pNode);
static void think_bstree_insert_node(ThinkBSTree* pTree, ThinkBSTreeNode* pNodeNew);
static void think_bstree_remove_node(ThinkBSTree* pTree, ThinkBSTreeNode* pNodeRemove, bool bFree);
static void think_bstree_update_height(ThinkBSTreeNode* pNode, NodeOperation nOperation);
static void think_bstree_node_foreach(ThinkBSTreeNode* pRoot, ThinkCommonFunc pFunc, void* pUserData, ForEachMethod method);
static void think_bstree_node_rotate(ThinkBSTree* pTree, ThinkBSTreeNode* pNodeRoot, NodeRotate nRotate);

static void think_bstree_node_rotate(ThinkBSTree* pTree, ThinkBSTreeNode* pNodeRoot, NodeRotate nRotate)
{
    /**
     * remove root
     *     update root
     * insert root
     */

    return_if_fail(pTree != NULL);
    return_if_fail(pNodeRoot != NULL);

    ThinkBSTreeNode* pNewRoot = NULL;
    if (NODE_ROTETE_CW == nRotate) {
        pNewRoot = pNodeRoot->m_pChildLeft;
        pNewRoot->m_pParent = pNodeRoot->m_pParent;

        if (pNewRoot->m_pParent) {
            pNewRoot->m_pParent->m_pChildLeft = pNewRoot;
        }

        pNodeRoot->m_pParent = NULL;
        pNodeRoot->m_pChildLeft = NULL;
        pNodeRoot->m_nHeightLeft = 0;
    } else {
        pNewRoot = pNodeRoot->m_pChildRight;
        pNewRoot->m_pParent = pNodeRoot->m_pParent;

        if (pNewRoot->m_pParent) {
            pNewRoot->m_pParent->m_pChildRight = pNewRoot;
        }

        pNodeRoot->m_pParent = NULL;
        pNodeRoot->m_pChildRight = NULL;
        pNodeRoot->m_nHeightRight = 0;

    }

    if (pTree->m_pNodeRoot == pNodeRoot) {
        pTree->m_pNodeRoot = pNewRoot;
    }

    ThinkBSTreeNode* pCur = pNewRoot;
    ThinkBSTreeNode* pParent = pCur;
    while (pCur) {
        int nVal = (pTree->m_pCompareFunc)(pNodeRoot->m_pData, pCur->m_pData);
        if (nVal < 0) {
            pParent = pCur;
            pCur = pCur->m_pChildLeft;
        } else {
            pParent = pCur;
            pCur = pCur->m_pChildRight;
        }
    }

    int nVal = (pTree->m_pCompareFunc)(pNodeRoot->m_pData, pParent->m_pData);
    if (nVal < 0) {
        pParent->m_pChildLeft = pNodeRoot;
        pNodeRoot->m_pParent = pParent;
    } else {
        pParent->m_pChildRight = pNodeRoot;
        pNodeRoot->m_pParent = pParent;
    }

    think_bstree_update_height(pNodeRoot, NODE_ADD);
}

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

static void think_bstree_update_height(ThinkBSTreeNode* pNode, NodeOperation nOperation)
{
    return_if_fail(pNode != NULL);

    ThinkBSTreeNode* pChild = pNode;

    while (pChild->m_pParent) {
        ThinkBSTreeNode* pParent = pChild->m_pParent;
        if (pParent->m_pChildLeft == pChild) {
            if (NODE_ADD == nOperation) {
                pParent->m_nHeightLeft = max(pChild->m_nHeightLeft, pChild->m_nHeightRight) + 1;
            } else {
                if (pChild == pNode) {
                    pParent->m_nHeightLeft -= 1;
                } else {
                    pParent->m_nHeightLeft = max(pChild->m_nHeightLeft, pChild->m_nHeightRight) + 1;
                }
            }
        } else {
            if (NODE_ADD == nOperation) {
                pParent->m_nHeightRight = max(pChild->m_nHeightLeft, pChild->m_nHeightRight) + 1;
            } else {
                if (pChild == pNode) {
                    pParent->m_nHeightRight -= 1;
                } else {
                    pParent->m_nHeightRight = max(pChild->m_nHeightLeft, pChild->m_nHeightRight) + 1;
                }
            }
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
    think_bstree_update_height(pNodeNew, NODE_ADD);
    pTree->m_nSize++;
}

static void think_bstree_remove_node(ThinkBSTree* pTree, ThinkBSTreeNode* pNodeRemove, bool bFree)
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
            think_bstree_remove_node(pTree, pMaxSubNode, false);
        } else if (pTree->m_pNodeRoot->m_pChildRight) {
            ThinkBSTreeNode* pMinSubNode = think_bstree_min_node(pTree, pTree->m_pNodeRoot->m_pChildRight);
            pNodeRemove->m_pData = pMinSubNode->m_pData;
            think_bstree_remove_node(pTree, pMinSubNode, false);
        } else {
            think_bstree_node_destory(pTree, &pNodeRemove, false);
            pTree->m_pNodeRoot = NULL;
        }
    } else {
        if (pNodeRemove->m_pChildLeft) {
            ThinkBSTreeNode* pMaxSubNode = think_bstree_max_node(pTree, pNodeRemove->m_pChildLeft);
            pNodeRemove->m_pData = pMaxSubNode->m_pData;
            if (pTree->m_pDestoryFunc) {
                (pTree->m_pDestoryFunc)(pNodeRemove->m_pData);
            }

            think_bstree_remove_node(pTree, pMaxSubNode, false);
        } else if (pNodeRemove->m_pChildRight) {
            ThinkBSTreeNode* pMinSubNode = think_bstree_min_node(pTree, pNodeRemove->m_pChildRight);
            pNodeRemove->m_pData = pMinSubNode->m_pData;
            think_bstree_remove_node(pTree, pMinSubNode, false);
        } else {
            think_bstree_update_height(pNodeRemove, NODE_DEL);
            think_bstree_node_destory(pTree, &pNodeRemove, false);
        }
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

static void think_bstree_node_destory(ThinkBSTree* pTree, ThinkBSTreeNode** ppNode, bool bFree)
{
    if (pTree->m_pDestoryFunc && bFree) {
        (pTree->m_pDestoryFunc)((*ppNode)->m_pData);
    }

    if ((*ppNode)->m_pParent) {
        if ((*ppNode)->m_pParent->m_pChildLeft == (*ppNode)) {
            (*ppNode)->m_pParent->m_pChildLeft = NULL;
        } else {
            (*ppNode)->m_pParent->m_pChildRight = NULL;
        }

        (*ppNode)->m_pParent = NULL;
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

    ThinkBSTreeNode* pCur = pNode;
    while (pCur) {
        int nVal = ((int)pCur->m_nHeightLeft - (int)pCur->m_nHeightRight);
        if (nVal < -1) {
            think_bstree_node_rotate(pTree, pCur, NODE_ROTETE_ACW);
        } else if (nVal > 1) {
            think_bstree_node_rotate(pTree, pCur, NODE_ROTETE_CW);
        } else {

        }

        pCur = pCur->m_pParent;
    }
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

    think_bstree_remove_node(pTree, pNode, true);
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
