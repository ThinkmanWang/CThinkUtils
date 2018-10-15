//
// Created by 王晓丰 on 02/02/2018.
//

#ifndef _THINKPTRARRAY_H_
#define _THINKPTRARRAY_H_

#include "utils.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    void** m_pData;
    unsigned int m_nLength;
    unsigned int m_nArySize;
    ThinkDestoryFunc m_pDestoryFunc;
} ThinkPtrArray;

#define ARRAY_LEN(ary) = (sizeof(ary->m_pData) / sizeof(void*))

ThinkPtrArray* think_ptr_array_new(ThinkDestoryFunc pDestroyFunc);
void think_ptr_array_free(ThinkPtrArray** pArray);

unsigned int think_ptr_array_length(ThinkPtrArray *pArray);

void think_ptr_array_append(ThinkPtrArray* pArray, void* pData);
void think_ptr_array_insert_at(ThinkPtrArray* pArray, void* pData, unsigned int nIndex);

void think_ptr_array_prepend(ThinkPtrArray* pArray, void* pData);

void think_ptr_array_remove(ThinkPtrArray* pArray, void* pData, int bFree);
void think_ptr_array_remove_at(ThinkPtrArray* pArray, unsigned int nIndex, int bFree);

void* think_ptr_array_get_array_index(ThinkPtrArray* pArray, unsigned int nIndex);
void* think_ptr_array_pop(ThinkPtrArray* pArray);
void* think_ptr_array_pop_tail(ThinkPtrArray* pArray);

void think_ptr_array_sort(ThinkPtrArray* pArray, ThinkCompareDataFunc pCompareFunc);

#ifdef __cplusplus
}
#endif

#endif
