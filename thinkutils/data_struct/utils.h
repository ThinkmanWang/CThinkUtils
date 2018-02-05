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

#endif //CHELLOWORLD_UTILS_H
