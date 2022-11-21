#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

int main() {
    int row = 0, col = 0, number = 0;

    printf("enter row ");
    row = checkEnter(row);
    
    printf("enter col ");
    col = checkEnter(col);
    
    printf("enter number ");
    number = checkEnter(number);
    
    int** matrix = fillMatrix(allocateMemoryForArray(row, col), row, col);

    printArr(matrix, row, col);

    search(matrix, row, col, number);
    
    return 0;
}
