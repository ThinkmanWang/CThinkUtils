//
// Created by 王晓丰 on 2018/10/19.
//

#include <stdio.h>
#include <stdlib.h>

void test1(int a)
{
    printf("%p\n", &a);
}

void test2(int* pA)
{
    printf("%p\n", pA);
}

void test3(int& a)
{
    printf("%p\n", &a);
}

int main(int argc, char** argv)
{
    int a = 1;
    printf("%p\n", &a);
    test1(a);
    test2(&a);
    test3(a);
    return 0;
}