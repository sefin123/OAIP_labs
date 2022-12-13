#include <stdio.h>
#include <stdlib.h>
#include "Header.h"
#include <stdbool.h>

int main() {
    int row = 0, col = 0, number = 0;

    printf("enter row ");
    row = enterWithValidation(row);

    printf("enter col ");
    col = enterWithValidation(col);

    int** matrix = fillMatrix(allocateMemoryForArray(col, row), col, row);

    printMatrix(matrix, row, col);
    printf("\n");
    
    quickSort(matrix, 0, col - 1, row);

    printMatrix(matrix, row, col);
    
    return 0;
}