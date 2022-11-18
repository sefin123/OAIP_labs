#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

int main() {
    int size = 0;
   
    printf("enter size ");
    size = enterWithValidation(size);
    
    int** arrFirst = fillMatrix(size);
    
    printMatrix(arrFirst, size);

    bool sim = false;
    sim = isSymmetric(arrFirst, size);

    newArr(arrFirst, size, sim);
    
    return 0;
}