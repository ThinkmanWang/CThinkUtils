#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"
#include "ThinkHashmap.h"


int hash(const char* key)
{
    if (key == NULL) {
        return 0;
    }

    size_t len = strlen(key);
    int index = (int) key[0];
    for (int i = 1; i<len; ++i) {
        index *= 1103515245 + (int)key[i];
    }
    index >>= 27;

    return (abs(index));
}

void foreach_map(char* pszKey, void* pData, void* pUserData) {
    log_debug("Hashmap size: %s->%d %p", pszKey, pData, pUserData);
}

int main(){
    log_debug("%d", hash("1"));
    log_debug("%d", hash("2"));
    log_debug("%d", hash("3"));
//    printf("%d\n", hash("efgh"));
//    printf("%d\n", hash("asdfasf"));
//    printf("%d\n", hash("asdfasfasdfagagdfgsdfgerwgrgwrgrtwgrtgrwtskadjfaksfhalkfadfadfadfafafadhasfhaskfhg"));

    ThinkHashmap* pMap = think_hashmap_new(NULL);

    think_hashmap_put(pMap, "1", (void*)1);
    think_hashmap_put(pMap, "2", (void*)2);
    think_hashmap_put(pMap, "3", (void*)3);

    log_debug("Hashmap size: %d", think_hashmap_size(pMap));
    log_debug("Hashmap size: %s->%d", "1", think_hashmap_get(pMap, "1"));
    log_debug("Hashmap size: %s->%d", "2", think_hashmap_get(pMap, "2"));
    log_debug("Hashmap size: %s->%d", "3", think_hashmap_get(pMap, "3"));

    think_hashmap_foreach(pMap, (ThinkHashFunc) foreach_map, NULL);
    log_debug("");
    think_hashmap_remove(pMap, "2");
    think_hashmap_foreach(pMap, (ThinkHashFunc) foreach_map, NULL);

    log_debug("Hashmap %p", pMap);
    think_hashmap_free(&pMap);
    log_debug("Hashmap %p", pMap);
}