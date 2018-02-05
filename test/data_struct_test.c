//
// Created by 王晓丰 on 02/02/2018.
//

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <string.h>
#include <glib.h>

#include "log.h"
#include "ThinkPtrArray.h"

int main(int argc, char* argv[])
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

    log_debug("Lenth: %d", think_ptr_array_size(pArray));

    for (int i = 0; i < think_ptr_array_size(pArray); ++i) {
        int* pData = think_ptr_array_get_array_index(pArray, i);
        log_debug("%d", *pData);
    }

    log_debug("");

    think_ptr_array_remove_at(pArray, 2, 1);
    for (int i = 0; i < think_ptr_array_size(pArray); ++i) {
        int* pData = think_ptr_array_get_array_index(pArray, i);
        log_debug("%d", *pData);
    }

    log_debug("");
    think_ptr_array_remove(pArray, pC, 1);
    for (int i = 0; i < think_ptr_array_size(pArray); ++i) {
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
    for (int i = 0; i < think_ptr_array_size(pArray); ++i) {
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
    for (int i = 0; i < think_ptr_array_size(pArray); ++i) {
        pData = think_ptr_array_get_array_index(pArray, i);
        log_debug("%d", *pData);
    }
    think_ptr_array_free(&pArray);

    return 0;
}
