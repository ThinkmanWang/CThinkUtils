//
// Created by Thinkman on 02/02/2018.
//

#include <stdio.h>
#include <stdlib.h>

#include "ThinkPtrArray.h"

ThinkPtrArray* think_ptr_array_new()
{
    ThinkPtrArray* pArray = (ThinkPtrArray*) malloc(sizeof(ThinkPtrArray));
    if (NULL == pArray) {
        return NULL;
    }

    pArray->m_nLen = 0;
    pArray->m_pData = malloc(sizeof(void*) * 16);

    if (NULL == pArray->m_pData) {
        goto err_ret;
    }

    return pArray;

err_ret:
    free(pArray);
    pArray = NULL;

    return NULL;
}

unsigned int think_ptr_array_size(ThinkPtrArray* pArray)
{
    return pArray->m_nLen;
}

void think_ptr_array_append(ThinkPtrArray* pArray, void* pData)
{

}

void think_ptr_array_insert_at(ThinkPtrArray* pArray, void* pData, unsigned int nIndex)
{

}

void think_ptr_array_prepend(ThinkPtrArray* pArray, void* pData)
{

}

void think_ptr_array_remove(ThinkPtrArray* pArray, void* pData)
{

}

void think_ptr_array_remove_at(ThinkPtrArray* pArray, unsigned int nIndex)
{

}

void* think_ptr_array_get_array_index(ThinkPtrArray* pArray, unsigned int nIndex)
{
    return NULL;
}

void* think_ptr_array_pop(ThinkPtrArray* pArray)
{
    return NULL;
}

void* think_ptr_array_pop_tail(ThinkPtrArray* pArray)
{
    return NULL;
}

