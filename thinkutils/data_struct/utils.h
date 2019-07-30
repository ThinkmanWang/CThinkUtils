//
// Created by 王晓丰 on 02/02/2018.
//

#ifndef CHELLOWORLD_UTILS_H
#define CHELLOWORLD_UTILS_H

#define return_if_fail(args) \
    if (!(args)) { \
        return; \
    }

#define return_val_if_fail(args, val) \
    if (!(args)) { \
        return val; \
    }

#define think_free(pVal) \
    if (pVal) { \
        free(pVal); \
        pVal = NULL; \
    }

typedef enum {
    SORT_ASC
    , SORT_DESC
} SortBy;

typedef void (*ThinkDestoryFunc) (void* pData);
typedef void (*ThinkCommonFunc) (void* pData, void* user_data);
typedef int (*ThinkCompareDataFunc) (const void* a, const void* b);
typedef char* (*ThinkToStringFunc) (void* pData, char* pStr, unsigned int nMax);

#define max( a , b ) ( (a) > (b) ? (a) : (b) )

#endif //CHELLOWORLD_UTILS_H
