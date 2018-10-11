#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    void* pPtr = (void*) malloc(1024);

    printf("%p\n", (pPtr + 0 * sizeof(void*)));
    printf("%p\n", (pPtr + 1 * sizeof(void*)));
    printf("%p\n", (pPtr + 2 * sizeof(void*)));
}