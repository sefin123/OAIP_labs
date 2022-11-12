#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
int main() {
    int size = 0, pathNumber = 0, arr[100][100], sum = 0;
    bool negative = false;
    printf("Enter size ");
    while (scanf_s("%d", &size) != 1 || size > 100 || size < 1
        || size % 1 != 0 || getchar() != '\n') {
        rewind(stdin);
        printf("Enter size ");
    }
    printf("Press 1 to enter yourself, press 2 to random\n");
    while (scanf_s("%d", &pathNumber) != 1 || pathNumber > 2
        || pathNumber < 1 || size % 1 != 0 || getchar() != '\n') {
        rewind(stdin);
        printf("Press 1 to enter yourself, press 2 to random\n");
    }
    srand(time(0));
    switch (pathNumber) {
    case 1:
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                while (scanf_s("%d", &arr[i][j]) != 1 || getchar() != '\n') {
                    rewind(stdin);
                    printf("enter again\n");
                }
            }
        }
        break;
    case 2:
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                arr[i][j] = (rand() % 100 - 50);
            }
        }
        break;
    default:
        printf("error");
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%3d ", arr[i][j]);
        }
        printf("\n");
    }
    
    for (int i = 0; i < size / 2; i++) {
        for (int j = size / 2; j < size; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    int min = 999999;
    for (int i = 0; i < size / 2; i++) {
        for (int j = size / 2; j < size; j++) {
            if (arr[i][j] < min) {
                min = arr[i][j];
            }
        }
    }
    printf("\nmin = %d", min);
    return 0;
}