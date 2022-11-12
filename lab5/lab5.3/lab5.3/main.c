#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

int main()
{
    int row = 0, col = 0, number = 0, c = 0;

    printf("enter row ");
    row = checkEnter(row);
    printf("enter col ");
    col = checkEnter(col);
    printf("enter number ");
    number = checkEnter(number);

    int *arrFirst = calloc(row , sizeof(int));
    for (int i = 0; i < row; i++) arrFirst[i] = col;
    int** arrSecond = calloc(row, sizeof(int*));
    for (int i = 0; i < row; i++) {
        arrSecond[i] = calloc(col, sizeof(int));
        for (int j = 0; j < col - 1; j++) {
            arrSecond[i][j] = checkEnter(arrSecond[i][j]);
        }
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%3d ", arrSecond[i][j]);
        }
        printf("\n");
    }
    search(arrSecond, row, arrFirst, number);
    return 0;
}