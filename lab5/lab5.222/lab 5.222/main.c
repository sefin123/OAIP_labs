#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

int main() {
    int size = 0;
   
    printf("enter size ");
    size = enterWithValidation(size);
    
    int** matrix = allocateMemoryForArray(size);
    matrix = fillMatrix(matrix, size);
    
    printMatrix(matrix, size);

    bool sim = false;
    sim = isSymmetric(matrix, size);

    newArr(matrix, size, sim);

    freeMatrix(matrix, size);
    return 0;
}