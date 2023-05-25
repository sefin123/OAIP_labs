#include "header.h"
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

int* allocateMemoryForArray(int size) {
    int* arr = calloc(size, sizeof(int));
    return arr;
}



void fillArr(int* arr, int size) {
    int p;
    int n = 1000;
    printf("press 1 to normal fill or 2 to bad fill\n");
    scanf_s("%d", &p);
    switch (p) {
    case 1:
        srand(time(0));
        for (int i = 0; i < size - 5; i++)
            arr[i] = (rand() % 10);
        for (int i = size - 5; i < size; i++)
            arr[i] = (rand() % 1 - 100);
    case 2:
        for (int i = 0; i < size; i++) {
            arr[i] = n;
            n--;
        }
    }
}

void printArr(int* arr, int size) {
    for (int i = 0; i < size; i++)
        printf("%5d", arr[i]);
}

int findNegativeElement(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] < 0) {
            int negativeElement = i;
            return i;
        }
    }
}

void bubbleSort(int* arr, int size) {
    int row = findNegativeElement(arr, size);
    bool flag = true;
    do {
        flag = false;
        for (int i = 0; i < row - 1; i++) {
            if (arr[i] > arr[i + 1]) {
                int swap = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = swap;
                flag = true;
            }
        }
    } while (flag);
}

void bubbleSortTime(int* arr,int size) {
    clock_t begin = clock();
    bubbleSort(arr, size);
    clock_t end = clock();

    printf("Bubble sort:\n");
    //printArr(arr, size);

    float seconds = (float)(end - begin) / CLOCKS_PER_SEC;

    printf("Bubble sort takes %f seconds", seconds);
}

void mergeSort(int* mas, int l, int r) {
    int p1 = 0, p2 = 0, mid = (l + r) / 2, pos = 0;
    int* b = NULL;
    b = (int*)malloc(r * sizeof(int));
    int i = 0;
    while (p1 + l <= mid && mid + p2 + 1 <= r) {
        if (p1 > mid || mid + 1 + p2 > r) break;

        if (mas[p1 + l] < mas[mid + 1 + p2]) {
            b[i] = (mas[p1 + l]);
            i++;
            p1++;
        }
        else {
            b[i] = (mas[mid + 1 + p2]);
            i++;
            p2++;
        }
    }
    while (p1 + l <= mid) {
        if (mas[p1 + l] < 0) {
            break;
        }
        p1++;
    }
    while (mid + 1 + p2 <= r) {
        if (mas[mid + 1 + p2] < 0) {
            break;
        }
        p2++;
    }
    pos = 0;
    for (int i = l; i <= r; i++) {
        if (mas[i] < 0) {
            break;
        }
    }
    free(b);
}


void merge(int* mas, int left, int right) {
    if (left == right)return;
    int mid = (left + right) / 2;
    merge(mas, left, mid);
    merge(mas, mid + 1, right);
    mergeSort(mas, left, right);
}

void mergeSortTime(int* arrForMergeSort, int size) {
    clock_t start = clock();
    merge(arrForMergeSort, 0, size - 1);
    clock_t end = clock();

    printf("Merge sort:\n");
  //  printArr(arrForMergeSort, size);

    float seconds = (float)(end - start) / CLOCKS_PER_SEC;
    
    printf("Merge sort takes %f seconds", seconds);
}