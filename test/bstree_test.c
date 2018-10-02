#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"
#include "ThinkBSTree.h"

#define MY_RAND_MAX 100

int my_compare(const void* a, const void* b)
{
    return ((int)a - (int)b);
}

void foreach_set(void* pData, void* pUserData)
{
    log_debug("%d %p", (int) pData, pUserData);
}

int main()
{
    ThinkBSTree* pTree = think_bstree_new(my_compare, NULL);
//    for (int i = 0; i < 100; ++i) {
//        int nRand = rand() % MY_RAND_MAX;
//        think_btree_insert(pTree, (void*)nRand);
//    }
    think_bstree_insert(pTree, (void*)6);
    think_bstree_insert(pTree, (void*)4);
    think_bstree_insert(pTree, (void*)10);
    think_bstree_insert(pTree, (void*)2);
    think_bstree_insert(pTree, (void*)5);

    think_bstree_insert(pTree, (void*)8);
    think_bstree_insert(pTree, (void*)12);
    think_bstree_insert(pTree, (void*)1);
    think_bstree_insert(pTree, (void*)3);
    think_bstree_insert(pTree, (void*)7);

    think_bstree_insert(pTree, (void*)9);
    think_bstree_insert(pTree, (void*)11);
    think_bstree_insert(pTree, (void*)13);
    think_bstree_insert(pTree, (void*)14);
    think_bstree_insert(pTree, (void*)15);

    log_debug("Set size: %d", think_bstree_size(pTree));
    log_debug("Set size: %d", think_bstree_height(pTree));

//    log_debug("");
//    think_btree_foreach_dlr(pTree, foreach_set, NULL);

    log_debug("");
    think_bstree_foreach_ldr(pTree, foreach_set, NULL);

//    log_debug("");
//    think_btree_foreach_lrd(pTree, foreach_set, NULL);
}