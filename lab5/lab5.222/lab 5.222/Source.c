#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int enterWithValidation() {
    int a;
    while (scanf_s("%d", &a) != 1 || a < 1 || a % 1 != 0 || getchar() != '\n') {
        printf("error\n");
        rewind(stdin);
    }
    return a;
}

int** fillMatrix(int size) {
    int** arrFirst = (int**)calloc(size, sizeof(int*));
    for (int i = 0; i < size; i++) {
        arrFirst[i] = (int*)calloc(size, sizeof(int));
        for (int j = 0; j < size; j++) {
            arrFirst[i][j] = enterWithValidation(arrFirst);
        }
    }
    return arrFirst;
}

void printMatrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
}

bool isSymmetric(int** arrFirst, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (arrFirst[i][j] != arrFirst[size - 1 - j][size - 1 - i]) {
                return false;
            }
        }
    }
    return true;
}

void newArr(int** arrFirst, int size, bool sim) {
    int** arrSecond = calloc(size, sizeof(*arrSecond));
    if (arrSecond == NULL) abort();
    for (int i = 0; i < size; i++) {
        arrSecond[i] = calloc(size, sizeof(**arrSecond));
        if (arrSecond == NULL) abort();
    }
    if (sim == true) {
        printf("the matrix is symmetric with respect to the secondary diagonal\n");
        for (int i = 0; i < size; i++) {
            int count = 0;
            for (int j = 0; j < size; j++) {
                if (i == size - j - 1) {
                    count++;
                    continue;
                }
                arrSecond[i][j - count] = arrFirst[i][j];
            }
        }
    }
    else {
        printf("the matrix is not symmetric with respect to the secondary diagonal\n");
        for (int i = 0; i < size; i++) {
            int count = 0;
            for (int j = 0; j < size; j++) {
                if (i == j) {
                    count++;
                    continue;
                }
                arrSecond[i][j - count] = arrFirst[i][j];
            }
        }
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - 1; j++) {
            printf("%5d ", arrSecond[i][j]);
        }
        printf("\n");
    }
}