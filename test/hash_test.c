#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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


int main(){
    printf("%d\n", hash("abcd"));
    printf("%d\n", hash("dcba"));
    printf("%d\n", hash("abcd"));
    printf("%d\n", hash("efgh"));
    printf("%d\n", hash("asdfasf"));
    printf("%d\n", hash("asdfasfasdfagagdfgsdfgerwgrgwrgrtwgrtgrwtskadjfaksfhalkfadfadfadfafafadhasfhaskfhg"));
}