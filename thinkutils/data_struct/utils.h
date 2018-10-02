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

typedef void (*ThinkDestoryFunc) (void* pData);
typedef void (*ThinkCommonFunc) (void* pData, void* user_data);
typedef int (*ThinkCompareDataFunc) (const void* a, const void* b);

#define max( a , b ) ( (a) > (b) ? (a) : (b) )

#endif //CHELLOWORLD_UTILS_H
