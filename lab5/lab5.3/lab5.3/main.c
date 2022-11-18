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
    
    int* arrFirst = fillArrFirst(row, col);
    
    int** arrSecond = fillArrSecond(row, col);

    printArr(arrSecond, row, col);

    search(arrSecond, row, arrFirst, number);
    
    return 0;
}
