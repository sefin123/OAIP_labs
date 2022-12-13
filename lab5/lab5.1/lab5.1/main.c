#include "Header.h"
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

int main() {
    int row = 0, col = 0;

    printf("enter row ");
    row = enterWithValidation(row);
    
    printf("enter col ");
    col = enterWithValidation(col);
   
    int** matrix = fillMatrix(allocateMemoryForArray(row, col), row, col);

    printMatrix(matrix, row ,col);

    checkElement(matrix, row, col);

    freeMatrix(matrix, row);
    
    return 0;
}
