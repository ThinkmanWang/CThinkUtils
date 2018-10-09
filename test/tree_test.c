#include <stdio.h>
#include <stdlib.h>

#include "ThinkTree.h"
#include "log.h"

void test1()
{
    ThinkTree* pTree = think_tree_new((void*)1);
    ThinkTree* pNode2 = think_tree_append(pTree, (void*)2);
    think_tree_append(pNode2, (void*)5);
    think_tree_append(pNode2, (void*)6);
//
//    ThinkTree* pNode3 = think_tree_append(pTree, (void*)3);
//    think_tree_append(pNode3, (void*)7);
//    think_tree_append(pNode3, (void*)8);
//    think_tree_append(pNode3, (void*)9);
//
//    ThinkTree* pNode4 = think_tree_append(pTree, (void*)4);
//    think_tree_append(pNode4, (void*)10);
//    think_tree_append(pNode4, (void*)11);
//    think_tree_append(pNode4, (void*)12);

    log_debug("Size: %d", think_tree_size(pTree));
}

int main()
{
    test1();

    return 0;
}