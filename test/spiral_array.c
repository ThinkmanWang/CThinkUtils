#include <stdio.h>
#include <stdlib.h>

typedef enum {
    DIRECTION_RIGHT
    , DIRECTION_BOTTOM
    , DIRECTION_LEFT
    , DIRECTION_TOP
} direction;

int main(int argc,char** argv)
{
    int nRow = 5, nCel = 5;
    if (2 == argc) {
        int _nRow = atoi(argv[1]);
        if (_nRow < 2) {
            printf("row count must >= 2\n");
        } else {
            nRow = nCel = _nRow;
        }
    } else {
        printf("Usage: %s number\n", argv[0]);
    }

    int** ppArray = NULL;
    ppArray = (int**)malloc(sizeof(int*) * nRow);
    for(int i=0; i < nRow; i++ )
    {
        ppArray[i] = (int *)malloc( sizeof(int) * nCel );
    }

    //for init all cell in array to 0
    for (int i = 0; i < nRow; ++i) {
        for (int j = 0; j < nCel; ++j) {
            ppArray[i][j] = 0;
            printf("%d ", ppArray[i][j]);
        }

        printf("\n");
    }

    direction nDirection = DIRECTION_RIGHT;

    int nStartRow = 0, nStartCel = 0;

    //input values
    for (int nStep = 0; nStep < nRow * nCel; ++nStep) {
        ppArray[nStartRow][nStartCel] = nStep + 1;

        switch (nDirection) {
            case DIRECTION_RIGHT:
                if (nStartCel + 1 >= nCel || ppArray[nStartRow][nStartCel + 1] != 0) {
                    nStartRow++;
                    nDirection = DIRECTION_BOTTOM;
                } else {
                    nStartCel++;
                }
                break;
            case DIRECTION_BOTTOM:
                if (nStartRow + 1 >= nRow || ppArray[nStartRow + 1][nStartCel] != 0) {
                    nStartCel--;
                    nDirection = DIRECTION_LEFT;
                } else {
                    nStartRow++;
                }
                break;
            case DIRECTION_LEFT:
                if (nStartCel - 1 < 0 || ppArray[nStartRow][nStartCel - 1] != 0) {
                    nStartRow--;
                    nDirection = DIRECTION_TOP;
                } else {
                    nStartCel--;
                }
                break;
            case DIRECTION_TOP:
                if (nStartRow - 1 < 0 || ppArray[nStartRow - 1][nStartCel] != 0) {
                    nStartCel++;
                    nDirection = DIRECTION_RIGHT;
                } else {
                    nStartRow--;
                }
                break;
            default:
                break;
        }
    }

    printf("\n");
    printf("\n");

    for (int i = 0; i < nRow; ++i) {
        for (int j = 0; j < nCel; ++j) {
            printf("%d ", ppArray[i][j]);
        }

        printf("\n");
    }

    return 0;
}