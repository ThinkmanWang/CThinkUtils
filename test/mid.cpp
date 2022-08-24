//
// Created by thinkman on 2022/8/24.
//

#include <stdio.h>
#include <stdlib.h>

void bubble_sort(int arr[], int size)
{
    int j,i,tem;
    for (i = 0; i < size-1;i ++)//size-1是因为不用与自己比较，所以比的数就少一个
    {
        int count = 0;
        for (j = 0; j < size-1 - i; j++)    //size-1-i是因为每一趟就会少一个数比较
        {
            if (arr[j] > arr[j+1])//这是升序排法，前一个数和后一个数比较，如果前数大则与后一个数换位置
            {
                tem = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tem;
                count = 1;

            }
        }
        if (count == 0)         //如果某一趟没有交换位置，则说明已经排好序，直接退出循环
            break;
    }

}

int main(int argc, char** argv)
{
    int nNum = 0;
    printf("请输入个数(奇数): ");
    if (1 != scanf("%d", &nNum)) {
        printf("scan number failed\n");
    }

    int* pAryNum = (int*)malloc(sizeof(int) * nNum);
    printf("请输入%d个数, 以空格隔开", nNum);
    for (int i = 0; i < nNum; i++) {
        scanf("%d", &pAryNum[i]);
    }

    bubble_sort(pAryNum, nNum);

    printf("%d\n", pAryNum[nNum / 2]);

    free(pAryNum);
    pAryNum = NULL;
}


