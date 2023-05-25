#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int enterWithValidation() {
    int a;
    while (scanf_s("%d", &a) != 1 || a < 1 || getchar() != '\n') {
        printf("error\n");
        rewind(stdin);
    }
    return a;
}

int enterMatrixWithValidation() {
    int a;
    while (scanf_s("%d", &a) != 1 || getchar() != '\n') {
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
            matrix[i][j] = enterMatrixWithValidation();
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

void simmetricMatrix(int** matrix, int size) {
    printf("the matrix is symmetric with respect to the secondary diagonal\n");
    for (int i = 0; i < size; i++) {
        int count = 0;
        for (int j = 0; j < size; j++) {
            if (i == size - j - 1) {
                count++;
                continue;
            }
            matrix[i][j - count] = matrix[i][j];
        }
        matrix[i] = realloc(matrix[i], size * 4);
    }
}

void nesimmetricMatrix(int** matrix, int size) {
    printf("the matrix is not symmetric with respect to the secondary diagonal\n");
    for (int i = 0; i < size; i++) {
        int count = 0;
        for (int j = 0; j < size; j++) {
            if (i == j) {
                count++;
                continue;
            }
            matrix[i][j - count] = matrix[i][j];
        }
        matrix[i] = realloc(matrix[i], size * 4);
    }
}



void newArr(int** matrix, int size, bool sim) {

    sim == true ? simmetricMatrix(matrix, size) : nesimmetricMatrix(matrix, size);
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - 1; j++) {
            printf("%5d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void freeMatrix(int** matrix, int size) {
    for (int i = 0; i < size ; i++)
        free(matrix[i]);
    free(matrix);
}