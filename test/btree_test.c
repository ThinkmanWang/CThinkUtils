#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"
#include "ThinkBTree.h"

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
    ThinkBTree* pTree = think_btree_new(my_compare, NULL);
//    for (int i = 0; i < 100; ++i) {
//        int nRand = rand() % MY_RAND_MAX;
//        think_btree_insert(pTree, (void*)nRand);
//    }
    think_btree_insert(pTree, (void*)1);
    think_btree_insert(pTree, (void*)3);
    think_btree_insert(pTree, (void*)5);
    think_btree_insert(pTree, (void*)7);
    think_btree_insert(pTree, (void*)9);

    think_btree_insert(pTree, (void*)2);
    think_btree_insert(pTree, (void*)4);
    think_btree_insert(pTree, (void*)6);
    think_btree_insert(pTree, (void*)8);
    think_btree_insert(pTree, (void*)10);

    think_btree_remove(pTree, (void*)6);

    log_debug("Set size: %d", think_btree_size(pTree));

//    log_debug("");
//    think_btree_foreach_dlr(pTree, foreach_set, NULL);

    log_debug("");
    think_btree_foreach_ldr(pTree, foreach_set, NULL);

//    log_debug("");
//    think_btree_foreach_lrd(pTree, foreach_set, NULL);
}