#ifndef _THINK_BTREE_H_
#define _THINK_BTREE_H_

#include <stdio.h>
#include <stdbool.h>

#include "utils.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _ThinkBTreeNode {
    void* m_pData;
    struct _ThinkBTreeNode* m_pChildLeft;
    struct _ThinkBTreeNode* m_pChildRight;
}ThinkBTreeNode;

typedef struct _ThinkBTree {
    ThinkBTreeNode* m_pNodeRoot;

    ThinkDestoryFunc m_pDestoryFunc;
    ThinkCompareDataFunc m_pCompareFunc;
}ThinkBTree;

ThinkBTree* think_btree_new(ThinkCompareDataFunc pCompareFunc, ThinkDestoryFunc pDestoryFunc);
void think_btree_free(ThinkBTree** ppTree);

void think_btree_insert(ThinkBTree* pTree, void* pData);

void think_btree_foreach_dlr(ThinkBTree* pTree, ThinkCommonFunc func, void* pUserData);
void think_btree_foreach_ldr(ThinkBTree* pTree, ThinkCommonFunc func, void* pUserData);
void think_btree_foreach_lrd(ThinkBTree* pTree, ThinkCommonFunc func, void* pUserData);

bool think_btree_remove(ThinkBTree* pTree, const void* pData);
bool think_btree_exists(ThinkBTree* pTree, const void* pData);
unsigned int think_btree_size(ThinkBTree* pTree);


#ifdef __cplusplus
}
#endif

#endif //_THINK_HASHMAP_H_