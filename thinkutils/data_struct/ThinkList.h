//
// Created by 王晓丰 on 05/02/2018.
//

#ifndef _THINKLIST_H_
#define _THINKLIST_H_

#include "utils.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _ThinkList ThinkList;

struct _ThinkList{
    void* m_pData;
    ThinkList* m_pPre;
    ThinkList* m_pNext;
};

ThinkList* think_list_append(ThinkList* pList, void* pData);
ThinkList* think_list_prepend(ThinkList* pList, void* pData);
ThinkList* think_list_insert(ThinkList* pList, void* pData, unsigned int nIndex);
ThinkList* think_list_concat(ThinkList* pList1, ThinkList* pList2);

ThinkList* think_list_remove(ThinkList* pList, void* pData, ThinkDestoryFunc pFunc);
ThinkList* think_list_remove_at(ThinkList* pList, unsigned int nIndex, ThinkDestoryFunc pFunc);

void* think_list_get(ThinkList* pList, unsigned int nIndex);
void* think_list_pop(ThinkList** ppList);
void* think_list_pop_tail(ThinkList** ppList);

unsigned int think_list_length(ThinkList* pList);

void think_list_free(ThinkList** pList, ThinkDestoryFunc pFunc);

void think_list_sort(ThinkList* pList, ThinkCompareDataFunc pFunc);


#ifdef __cplusplus
}
#endif

#endif //CHELLOWORLD_THINKLIST_H
