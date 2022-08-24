
#include <stdio.h>
#include <stdlib.h>

#include "ThinkList.h"
#include "log.h"

int my_compare(const void* a, const void* b)
{
    return ((int)a - (int)b);
}

void test1()
{
    ThinkList* pList = NULL;
    
    //57, 68, 59, 52, 72, 28, 96, 33, 24, 24
    pList = think_list_append(pList, (void*)57);
    pList = think_list_append(pList, (void*)68);
    pList = think_list_append(pList, (void*)59);
    pList = think_list_append(pList, (void*)52);
    pList = think_list_append(pList, (void*)72);

    pList = think_list_append(pList, (void*)28);
    pList = think_list_append(pList, (void*)96);
    pList = think_list_append(pList, (void*)33);
    pList = think_list_append(pList, (void*)24);
    pList = think_list_append(pList, (void*)24);
    
    think_list_sort(pList, my_compare);
    for (unsigned int i = 0; i < think_list_length(pList); ++i) {
        void* pData = think_list_get(pList, i);
        log_debug("%p", pData);
    }

    think_list_free(&pList, NULL);
}

int main(int argc, char** argv)
{
    test1();

    return 0;
}