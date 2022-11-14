#include "Header.h"
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

int main()
{
    int row = 0, col = 0;

    printf("enter row ");
    row = enterWithValidation(row);
    
    printf("enter col ");
    col = enterWithValidation(col);
    
    int** matrix = fillMatrix(row, col);
   /* int** matrix = calloc(row, sizeof(int*));
    for (int i = 0; i < row; i++) {
        if (matrix == NULL) abort();
        matrix[i] = calloc(col, sizeof(int));
        if (matrix[i] == NULL) abort();
        for (int j = 0; j < col; j++) {
            matrix[i][j] = enterWithValidation(matrix[i][j]);
        }
    }*/
    printMatrix(matrix, row ,col);
    checkElement(matrix, row, col);
    return 0;
}