#include "Header.h"
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

int main()
{
    int row = 0, col = 0;
    printf("enter row ");
    row = checkEnter(row);
    printf("enter col ");
    col = checkEnter(col);
    int* arrFirst = calloc(row , sizeof(int));
    for (int i = 0; i < row; i++) arrFirst[i] = col;
    int** arrSecond = calloc(row, sizeof(int*));
    for (int i = 0; i < row; i++) {
        arrSecond[i] = calloc(col, sizeof(int));
        for (int j = 0; j < col; j++) {
            arrSecond[i][j] = checkEnter(arrSecond[i][j]);
        }
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%3d ", arrSecond[i][j]);
        }
        printf("\n");
    }
    checkElement(arrSecond, row, col);
 /*   for (int i = 0; i < row; i++) {
        int sum = 0;
        {
            for (int j = 0; j < col; j++) {
                sum = sum + arrSecond[i][j];
            }
            for (int j = 0; j < col; j++) {
                if (arrSecond[i][j] > sum - arrSecond[i][j]) {
                    printf("array have the element\n");
                }
            }
        }
    }*/

    return 0;
}