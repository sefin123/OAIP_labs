#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include <time.h>

int main() {
    int size = 0;

    printf("enter size ");
    size = enterWithValidation(size);

    int* arrForBubbleSort = allocateMemoryForArray(size);
    fillArr(arrForBubbleSort, size);
    int* arrForMergeSort = arrForBubbleSort;

    printArr(arrForBubbleSort, size);
    
    printf("\n");
    printf("\n");

    bubbleSortTime(arrForBubbleSort, size);
    
    printf("\n");
    printf("\n");

    mergeSortTime(arrForMergeSort,size);    
    
    return 0;
}