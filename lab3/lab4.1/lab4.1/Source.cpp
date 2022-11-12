#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
int main() {
    int size = 0, pathNumber = 0,arr[100][100], sum = 0;
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
            printf("%3d", arr[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < size; i++) {
        sum = 0;
        for (int j = 0; j < size; j++) {
            sum = sum + arr[i][j];
            if (arr[i][j] < 0)
                negative = true;
        }
        if (!negative)
            printf("\n%d row sum = %d", (i + 1), sum);
        else {
            negative = false;
            printf("\nRow %d has a negative element", (i + 1));
        }
    }

    int sumDia1 = 0, sumDia2 = 0, sumMin1 = 0, sumMin2 = 0, sumMin;
    for (int n = 1; n < size; n++) {
        for (int i = n, j = 0; i < size; j++, i++) {
            sumDia1 += arr[i][j];
        }
        if (sumMin1 >= sumDia1) {
            sumMin1 = sumDia1;
        }
        for (int j = n, i = 0; j < size; j++, i++) {
            sumDia2 += arr[i][j];
        }
        if (sumMin2 >= sumDia2) {
            sumMin2 = sumDia2;
        }
        sumDia1 -= sumDia1;
        sumDia2 -= sumDia2;
        if (sumMin2 >= sumMin1) {
            sumMin = sumMin1;
        }
        else {
            sumMin = sumMin2;
        }
    }
    printf("\nMin diagonal sum = %d\n", sumMin);
    return 0;
}