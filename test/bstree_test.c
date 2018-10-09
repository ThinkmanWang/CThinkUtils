#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

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

void test1()
{
    ThinkBSTree* pTree = think_bstree_new(my_compare, NULL);

    think_bstree_insert(pTree, (void*)6);
    think_bstree_insert(pTree, (void*)4);
    think_bstree_insert(pTree, (void*)10);

    assert(3 == think_bstree_size(pTree));
    assert(2 == think_bstree_height(pTree));

    think_bstree_remove(pTree, (void*)4);

    assert(2 == think_bstree_size(pTree));
    assert(2 == think_bstree_height(pTree));

    think_bstree_remove(pTree, (void*)10);
    assert(1 == think_bstree_size(pTree));
    assert(1 == think_bstree_height(pTree));

    log_debug("SUCCESS");
}

void test2()
{
    ThinkBSTree* pTree = think_bstree_new(my_compare, NULL);

    think_bstree_insert(pTree, (void*)6);
    think_bstree_insert(pTree, (void*)4);
    think_bstree_insert(pTree, (void*)10);
    think_bstree_insert(pTree, (void*)2);

    assert(4 == think_bstree_size(pTree));
    assert(3 == think_bstree_height(pTree));

    think_bstree_remove(pTree, (void*)4);

    assert(3 == think_bstree_size(pTree));
    assert(2 == think_bstree_height(pTree));

    think_bstree_remove(pTree, (void*)10);
    assert(2 == think_bstree_size(pTree));
    assert(2 == think_bstree_height(pTree));

    log_debug("SUCCESS");
}

void test3()
{
    ThinkBSTree* pTree = think_bstree_new(my_compare, NULL);

    think_bstree_insert(pTree, (void*)6);
    think_bstree_insert(pTree, (void*)4);
    think_bstree_insert(pTree, (void*)10);
    think_bstree_insert(pTree, (void*)2);
    think_bstree_insert(pTree, (void*)8);
    think_bstree_insert(pTree, (void*)11);
    think_bstree_insert(pTree, (void*)7);
    think_bstree_insert(pTree, (void*)9);

    assert(8 == think_bstree_size(pTree));
    assert(4 == think_bstree_height(pTree));

    think_bstree_remove(pTree, (void*)10);

    assert(7 == think_bstree_size(pTree));
    assert(4 == think_bstree_height(pTree));

    log_debug("SUCCESS");
}

void test4()
{
    ThinkBSTree* pTree = think_bstree_new(my_compare, NULL);

    think_bstree_insert(pTree, (void*)6);
    think_bstree_insert(pTree, (void*)4);
    think_bstree_insert(pTree, (void*)10);

    think_bstree_remove(pTree, (void*)6);

    assert(2 == think_bstree_size(pTree));
    assert(2 == think_bstree_height(pTree));

    log_debug("SUCCESS");
}

void test_foreach() {
    ThinkBSTree* pTree = think_bstree_new(my_compare, NULL);

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

    log_debug("");
    think_bstree_foreach_dlr(pTree, foreach_set, NULL);

    log_debug("");
    think_bstree_foreach_ldr(pTree, foreach_set, NULL);

    log_debug("");
    think_bstree_foreach_lrd(pTree, foreach_set, NULL);
}

void test6()
{
    ThinkBSTree* pTree = think_bstree_new(my_compare, NULL);

    think_bstree_insert(pTree, (void*)4);
    think_bstree_insert(pTree, (void*)3);
    think_bstree_insert(pTree, (void*)5);
    think_bstree_insert(pTree, (void*)7);
    think_bstree_insert(pTree, (void*)6);
    think_bstree_insert(pTree, (void*)8);

    think_bstree_remove(pTree, (void*)5);

    assert(5 == think_bstree_size(pTree));
    assert(4 == think_bstree_height(pTree));

    log_debug("");
    think_bstree_foreach_ldr(pTree, foreach_set, NULL);

    log_debug("SUCCESS");
}

void test7()
{
    ThinkBSTree* pTree = think_bstree_new(my_compare, NULL);

    think_bstree_insert(pTree, (void*)4);
    think_bstree_insert(pTree, (void*)4);

    assert(1 == think_bstree_size(pTree));
    assert(1 == think_bstree_height(pTree));
    log_debug("SUCCESS");
}

void test8()
{
    ThinkBSTree* pTree = think_bstree_new(my_compare, NULL);

    think_bstree_insert(pTree, (void*)5);
    think_bstree_insert(pTree, (void*)4);
    think_bstree_insert(pTree, (void*)3);
    think_bstree_insert(pTree, (void*)2);

    think_bstree_insert(pTree, (void*)6);
    think_bstree_insert(pTree, (void*)7);
    think_bstree_insert(pTree, (void*)8);

    think_bstree_remove(pTree, (void*)4);

    assert(6 == think_bstree_size(pTree));
    assert(4 == think_bstree_height(pTree));

    log_debug("");
    think_bstree_foreach_ldr(pTree, foreach_set, NULL);

    log_debug("SUCCESS");
}

void test9()
{
    ThinkBSTree* pTree = think_bstree_new(my_compare, NULL);
    think_bstree_insert(pTree, (void*)10);
    think_bstree_insert(pTree, (void*)5);
    think_bstree_insert(pTree, (void*)15);
    think_bstree_insert(pTree, (void*)2);
    think_bstree_insert(pTree, (void*)8);
    think_bstree_insert(pTree, (void*)1);
    think_bstree_insert(pTree, (void*)7);


    think_bstree_remove(pTree, (void*)5);

    assert(6 == think_bstree_size(pTree));
    assert(4 == think_bstree_height(pTree));

    think_bstree_foreach_ldr(pTree, foreach_set, NULL);
    log_debug("SUCCESS");
}

void test10()
{
    ThinkBSTree* pTree = think_bstree_new(my_compare, NULL);
    think_bstree_insert(pTree, (void*)10);
    think_bstree_insert(pTree, (void*)5);
    think_bstree_insert(pTree, (void*)15);
//    think_bstree_insert(pTree, (void*)2);
    think_bstree_insert(pTree, (void*)9);
//    think_bstree_insert(pTree, (void*)1);
    think_bstree_insert(pTree, (void*)7);
    think_bstree_insert(pTree, (void*)8);


    think_bstree_remove(pTree, (void*)5);

    assert(5 == think_bstree_size(pTree));
    assert(4 == think_bstree_height(pTree));

    think_bstree_foreach_ldr(pTree, foreach_set, NULL);
    log_debug("SUCCESS");
}

void test11()
{
    ThinkBSTree* pTree = think_bstree_new(my_compare, NULL);
    for (int i = 1; i <= 255; ++i) {
        think_bstree_insert(pTree, (void*)i);
    }

    log_debug("Size: %d", think_bstree_size(pTree));
    log_debug("Height: %d", think_bstree_height(pTree));

    think_bstree_foreach_ldr(pTree, foreach_set, NULL);

    think_bstree_destory(&pTree);
    log_debug("%p", pTree);

    log_debug("SUCCESS");
}

int main()
{
//    test1();
//    test2();
//    test3();
//    test4();
//    test6();
//    test7();
//
//    test_foreach();
//    test8();
//    test9();
//
//    test10();

    test11();
}