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

int** allocateMemoryForArray(int size) {
    int** matrix = (int**)calloc(size, sizeof(int*));
    for (int i = 0; i < size; i++) {
        matrix[i] = (int*)calloc(size, sizeof(int));
        
    }
    return matrix;

}

int** fillMatrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = enterWithValidation(matrix);
        }
    }
    return matrix;
}

void printMatrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
}

bool isSymmetric(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (matrix[i][j] != matrix[size - 1 - j][size - 1 - i]) {
                return false;
            }
        }
    }
    return true;
}

void newArr(int** arrFirst, int size, bool sim) {

    
    if (sim == true) {
        printf("the matrix is symmetric with respect to the secondary diagonal\n");
        for (int i = 0; i < size; i++) {
            int count = 0;
            for (int j = 0; j < size; j++) {
                if (i == size - j - 1) {
                    count++;
                    continue;
                }
                arrFirst[i][j - count] = arrFirst[i][j];
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
                arrFirst[i][j - count] = arrFirst[i][j];
            }
        }
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - 1; j++) {
            printf("%5d ", arrFirst[i][j]);
        }
        printf("\n");
    }
}