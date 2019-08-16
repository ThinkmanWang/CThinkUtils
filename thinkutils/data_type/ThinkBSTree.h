#ifndef _THINK_BSTREE_H_
#define _THINK_BSTREE_H_

#include <stdio.h>
#include <stdbool.h>

#include "utils.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct _ThinkBSTreeNode {
    void* m_pData;

    unsigned int m_nHeightLeft;
    unsigned int m_nHeightRight;

    struct _ThinkBSTreeNode* m_pParent;
    struct _ThinkBSTreeNode* m_pChildLeft;
    struct _ThinkBSTreeNode* m_pChildRight;
}ThinkBSTreeNode;

typedef struct _ThinkBSTree {
    ThinkBSTreeNode* m_pNodeRoot;
    unsigned int m_nSize;

    ThinkDestoryFunc m_pDestoryFunc;
    ThinkCompareDataFunc m_pCompareFunc;

}ThinkBSTree;

ThinkBSTree* think_bstree_new(ThinkCompareDataFunc pCompareFunc, ThinkDestoryFunc pDestoryFunc);
void think_bstree_free(ThinkBSTree** ppTree);

void think_bstree_insert(ThinkBSTree* pTree, void* pData);

void think_bstree_foreach_dlr(ThinkBSTree* pTree, ThinkCommonFunc func, void* pUserData);
void think_bstree_foreach_ldr(ThinkBSTree* pTree, ThinkCommonFunc func, void* pUserData);
void think_bstree_foreach_lrd(ThinkBSTree* pTree, ThinkCommonFunc func, void* pUserData);

bool think_bstree_remove(ThinkBSTree* pTree, const void* pData);
bool think_bstree_exists(ThinkBSTree* pTree, const void* pData);

unsigned int think_bstree_size(ThinkBSTree* pTree);
unsigned int think_bstree_height(ThinkBSTree* pTree);

char* think_bstree_to_string(ThinkBSTree* pTree, ThinkToStringFunc pToStringFunc);


#ifdef __cplusplus
}
#endif

#endif //_THINK_HASHMAP_H_