#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"
#include "ThinkHashmap.h"


static unsigned int hash(const char* pszKey)
{
    unsigned int hash = 0;
    while (*pszKey) {
        hash = (*pszKey++) + (hash << 6) + (hash << 16) - hash;
    }

    return (hash & 0x7FFFFFFF);
}

void foreach_map(char* pszKey, void* pData, void* pUserData)
{
    log_debug("Hashmap size: %s->%s %p", pszKey, pData, pUserData);
}

int main()
{
    log_debug("%d", hash("1"));
    log_debug("%d", hash("2"));
    log_debug("%d", hash("3"));
//    for (int i = 0; i < 1024; ++i) {
//        char szTxt[8] = "";
//        sprintf(szTxt, "%d", i);
//        log_debug("%d->%d", i, hash(szTxt));
//    }
    log_debug("%d\n", hash("efgh"));
    log_debug("%d\n", hash("asdfasf"));
    log_debug("%d\n", hash("asdfasfasdfagagdfgsdfgerwgrgwrgrtwgrtgrwtskadjfaksfhalkfadfadfadfafafadhasfhaskfhg"));

    ThinkHashMap* pMap = think_hashmap_new(NULL);

    think_hashmap_put(pMap, "1", "华鹏");
    think_hashmap_put(pMap, "2", "老王");
    think_hashmap_put(pMap, "3", "test str");
    think_hashmap_put(pMap, "中文key", "中文value");

    log_debug("Hashmap size: %d", think_hashmap_size(pMap));
    log_debug("Hashmap : %s->%s", "1", think_hashmap_get(pMap, "1"));
    log_debug("Hashmap : %s->%s", "2", think_hashmap_get(pMap, "2"));
    log_debug("Hashmap : %s->%s", "3", think_hashmap_get(pMap, "3"));

    think_hashmap_foreach(pMap, (ThinkHashFunc) foreach_map, NULL);
    log_debug("");
    think_hashmap_remove(pMap, "2");
    think_hashmap_foreach(pMap, (ThinkHashFunc) foreach_map, NULL);

    log_debug("Hashmap %p", pMap);
    think_hashmap_free(&pMap);
    log_debug("Hashmap %p", pMap);
}
