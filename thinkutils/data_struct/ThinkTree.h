#ifndef _THINK_TREE_H_
#define _THINK_TREE_H_

#include <stdio.h>
#include <stdbool.h>

#include "utils.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _ThinkTree ThinkTree;

struct _ThinkTree{
    void* m_pData;
    ThinkTree* m_pNext;
    ThinkTree* m_pPre;
    ThinkTree* m_pParent;
    ThinkTree* m_pChildren;
} ;

ThinkTree* think_tree_new(void* pData);
void think_tree_unlink(ThinkTree* pTree);
void think_tree_destory(ThinkTree** ppTree, ThinkDestoryFunc m_pDestoryFunc);

ThinkTree* think_tree_insert(ThinkTree* pParent, int position, void* pData);
ThinkTree* think_tree_insert_before(ThinkTree* pParent, ThinkTree* pNode, void* pData);
ThinkTree* think_tree_insert_after(ThinkTree* pParent, ThinkTree* pNode, void* pData);
ThinkTree* think_tree_append(ThinkTree* pParent, void* pData);
ThinkTree* think_tree_prepend(ThinkTree* pParent, void* pData);

ThinkTree* think_tree_find(ThinkTree* pTree, void* pData);
ThinkTree* think_tree_find_children(ThinkTree* pTree, void* pData);

void think_tree_foreach(ThinkTree* pTree, ThinkCommonFunc func);
void think_tree_foreach_children(ThinkTree* pTree, ThinkCommonFunc func);

ThinkTree* think_tree_first_child(ThinkTree* pTree);
ThinkTree* think_tree_last_child(ThinkTree* pTree);

unsigned int think_tree_depth(ThinkTree* pTree);
unsigned int think_tree_height(ThinkTree* pTree);

#ifdef __cplusplus
}
#endif

#endif //_THINK_TREE_H_