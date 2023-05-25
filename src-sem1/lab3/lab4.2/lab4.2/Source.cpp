#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
int main() {
    int col = 0, pathNumber = 0, arr[100][100],row, sum = 0;
    bool negative = false;
    printf("Enter row ");
    while (scanf_s("%d", &row) != 1 || row > 100 || row < 1
        || row % 1 != 0 || getchar() != '\n') {
        rewind(stdin);
        printf("Enter row ");
    }
    printf("\nEnter col ");
    while (scanf_s("%d", &col) != 1 || col > 100 || col < 1
        || col % 1 != 0 || getchar() != '\n') {
        rewind(stdin);
        printf("Enter col ");
    }
    printf("Press 1 to enter yourself, press 2 to random\n");
    while (scanf_s("%d", &pathNumber) != 1 || pathNumber > 2
        || pathNumber < 1 || pathNumber % 1 != 0 || getchar() != '\n') {
        rewind(stdin);
        printf("Press 1 to enter yourself, press 2 to random\n");
    }
    srand(time(0));
    switch (pathNumber) {
    case 1:
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                while (scanf_s("%d", &arr[i][j]) != 1 || getchar() != '\n') {
                    rewind(stdin);
                    printf("enter again\n");
                }
            }
        }
        break;
    case 2:
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                arr[i][j] = (rand() % 10 - 5);
            }
        }
        break;
    default:
        printf("error");
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%3d", arr[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < row; i++) {
        negative = true;
        sum = 0;
        for (int j = 0; j < col; j++) {
            if (arr[j][i] >= 0) {
                negative = false;
                break;
            }
        }
        if (negative) {
            for (int j = 0; j < row; j++) {
                sum = sum + arr[j][i];
            }
            sum = sum / row ;
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    arr[i][j] -= sum;
                }
            }
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    printf("%5d", arr[i][j]);
                }
                printf("\n");
            }
            break;
        }
        else if (i == row - 1) {
            printf("no negative elements");
        }

    }
	return 0;
}