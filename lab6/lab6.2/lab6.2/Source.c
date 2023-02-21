#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

int enterWithValidation() {
    int a;
    while (scanf_s("%d", &a) != 1 || a < 1 || getchar() != '\n') {
        printf("error\n");
        rewind(stdin);
    }
    return a;
}

int** allocateMemoryForArray(int row, int col) {
    int** matrix = (int**)calloc(row, sizeof(int*));
    for (int i = 0; i < row; i++) {
        matrix[i] = (int*)calloc(col, sizeof(int));
    }
    return matrix;

}

int** fillMatrix(int** matrix, int row, int col) {
    srand(time(0));
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            matrix[i][j] = (rand() % 10 - 5);
        }
    }
    return matrix;
}

void printMatrix(int** matrix, int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%3d", matrix[j][i]);
        }
        printf("\n");
    }

}

int sum(const int* arr, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++)
        sum += arr[i];
    return sum;
}

void swap(int** a, int** b) {
    int* temp = *a;
    *a = *b;
    *b = temp;
}

bool lessThen(const int* left, const int* right, int size) {
    return sum(left, size) < sum(right, size);
}

void quickSort(int** matrix, int left, int right, int size) {
    int i = left;
    int j = right;
    int* x = matrix[(i + j) / 2];
    do {

        while (lessThen(matrix[i], x, size) && i < right) {
            i++;
        }
        while (lessThen(x, matrix[j], size) && j > left) {
            j--;
        }
        if (i <= j) {
            if (i % 2 == 0 || j % 2 == 0) swap(&matrix[i], &matrix[j]);
            i++;
            j--;
        }
    } while (i <= j);
    if (j > left) {
        quickSort(matrix, left, j, size);
    }
    if (i < right) {
        quickSort(matrix, i, right, size);
    }
}

void freeMatrix() {

}