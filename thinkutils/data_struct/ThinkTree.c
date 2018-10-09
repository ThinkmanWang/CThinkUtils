#include "ThinkTree.h"

ThinkTree* think_tree_new(void* pData)
{
    return NULL;
}

void think_tree_unlink(ThinkTree* pTree)
{

}

void think_tree_destory(ThinkTree** ppTree, ThinkDestoryFunc m_pDestoryFunc)
{

}


ThinkTree* think_tree_insert(ThinkTree* pParent, int position, void* pData)
{
    return NULL;
}

ThinkTree* think_tree_insert_before(ThinkTree* pParent, ThinkTree* pNode, void* pData)
{
    return NULL;
}

ThinkTree* think_tree_insert_after(ThinkTree* pParent, ThinkTree* pNode, void* pData)
{
    return NULL;
}

ThinkTree* think_tree_append(ThinkTree* pParent, void* pData)
{
    return NULL;
}

ThinkTree* think_tree_prepend(ThinkTree* pParent, void* pData)
{
    return NULL;
}


ThinkTree* think_tree_find(ThinkTree* pTree, void* pData)
{
    return NULL;
}

ThinkTree* think_tree_find_children(ThinkTree* pTree, void* pData)
{
    return NULL;
}


void think_tree_foreach(ThinkTree* pTree, ThinkCommonFunc func)
{

}

void think_tree_foreach_children(ThinkTree* pTree, ThinkCommonFunc func)
{

}


ThinkTree* think_tree_first_child(ThinkTree* pTree)
{
    return NULL;
}

ThinkTree* think_tree_last_child(ThinkTree* pTree)
{
    return NULL;
}


unsigned int think_tree_depth(ThinkTree* pTree)
{
    return 0;
}

unsigned int think_tree_height(ThinkTree* pTree)
{
    return 0;
}
