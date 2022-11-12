#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

int main() {
    int size = 0;
    printf("enter size ");
    size = checkEnter(size);
    int** arrFirst = calloc(size, sizeof(*arrFirst));
    if (arrFirst == NULL) abort();
    for (int i = 0; i < size; i++) {
        arrFirst[i] = calloc(size, sizeof(**arrFirst));
        if (arrFirst[i] == NULL) abort();
        for (int j = 0; j < size; j++) {
            arrFirst[i][j] = checkEnter(arrFirst[i][j]);
        }
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%3d ", arrFirst[i][j]);
        }
        printf("\n");
    }
    bool sim = 0;
    sim = symmetric(arrFirst, size);
    newArr(arrFirst, size, sim);
    return 0;
}