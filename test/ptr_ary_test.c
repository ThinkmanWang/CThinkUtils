
#include <stdio.h>
#include <stdlib.h>

#include "ThinkPtrArray.h"
#include "log.h"

void ptr_array_test()
{
    ThinkPtrArray* pArray = think_ptr_array_new(free);
    int* pA = (int*) malloc(sizeof(int));
    *pA = 123;
    think_ptr_array_append(pArray, (void*) pA);

    int* pB = (int*) malloc(sizeof(int));
    *pB = 456;
    think_ptr_array_append(pArray, (void*) pB);

    int* pC = (int*) malloc(sizeof(int));
    *pC = 789;
    think_ptr_array_append(pArray, (void*) pC);

    int* pD = (int*) malloc(sizeof(int));
    *pD = 111;
    think_ptr_array_insert_at(pArray, (void*) pD, 0);

    int* pE = (int*) malloc(sizeof(int));
    *pE = 222;
    think_ptr_array_prepend(pArray, (void*) pE);

    log_debug("Lenth: %d", think_ptr_array_length(pArray));

    for (int i = 0; i < think_ptr_array_length(pArray); ++i) {
        int* pData = think_ptr_array_get_array_index(pArray, i);
        log_debug("%d", *pData);
    }

    log_debug("");

    think_ptr_array_remove_at(pArray, 2, 1);
    for (int i = 0; i < think_ptr_array_length(pArray); ++i) {
        int* pData = think_ptr_array_get_array_index(pArray, i);
        log_debug("%d", *pData);
    }

    log_debug("");
    think_ptr_array_remove(pArray, pC, 1);
    for (int i = 0; i < think_ptr_array_length(pArray); ++i) {
        int* pData = think_ptr_array_get_array_index(pArray, i);
        log_debug("%d", *pData);
    }

    log_debug("");
    int* pData = think_ptr_array_pop(pArray);
    log_debug("%d", *pData);

    log_debug("");
    pData = think_ptr_array_pop_tail(pArray);
    log_debug("%d", *pData);

    log_debug("");
    for (int i = 0; i < think_ptr_array_length(pArray); ++i) {
        pData = think_ptr_array_get_array_index(pArray, i);
        log_debug("%d", *pData);
    }

    think_ptr_array_free(&pArray);

    pArray = think_ptr_array_new(free);
    for (int i = 0; i < 1000; ++i) {
        int* pElement = malloc(sizeof(int));
        *pElement = i;
        think_ptr_array_append(pArray, pElement);
    }

    log_debug("");
    for (int i = 0; i < think_ptr_array_length(pArray); ++i) {
        pData = think_ptr_array_get_array_index(pArray, i);
        log_debug("%d", *pData);
    }
    think_ptr_array_free(&pArray);

}

int my_compare(const void* a, const void* b)
{
    return ((int)a - (int)b);
}

int test1()
{
    ThinkPtrArray* pArray = think_ptr_array_new(NULL);
    
    //57, 68, 59, 52, 72, 28, 96, 33, 24, 24
    think_ptr_array_append(pArray, (void*)57);
    think_ptr_array_append(pArray, (void*)68);
    think_ptr_array_append(pArray, (void*)59);
    think_ptr_array_append(pArray, (void*)52);
    think_ptr_array_append(pArray, (void*)72);

    think_ptr_array_append(pArray, (void*)28);
    think_ptr_array_append(pArray, (void*)96);
    think_ptr_array_append(pArray, (void*)33);
    think_ptr_array_append(pArray, (void*)24);
    think_ptr_array_append(pArray, (void*)24);
    
    think_ptr_array_sort(pArray, my_compare);
    for (unsigned int i = 0; i < think_ptr_array_length(pArray); ++i) {
        void* pData = think_ptr_array_get_array_index(pArray, i);
        log_debug("%d", (int)pData);
    }

    think_ptr_array_free(&pArray);
}

int main(int argc, char** argv)
{
    test1();

    return 0;
}