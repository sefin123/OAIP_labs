#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

int main() {
    int row = 0, col = 0, number = 0;

    printf("enter row ");
    row = enterWithValidation(row);
    
    printf("enter col ");
    col = enterWithValidation(col);
    
    printf("enter number ");
    number = enterWithValidation(number);
    
    int** matrix = fillMatrix(allocateMemoryForArray(row, col), row, col);

    printArr(matrix, row, col);

    search(matrix, row, col, number);
    
    freeMatrix(matrix, row);
    return 0;
}
