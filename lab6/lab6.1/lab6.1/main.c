#include <stdio.h>
#include <stdlib.h>

int checkEnter(int a) {
    while (scanf_s("%d", &a) != 1 || getchar() != '\n') {
        printf("error\n");
        rewind(stdin);
    }
    return a;
}

int main() {
    int size = 0;
    printf("enter size ");
    
    size = checkEnter(size);
    int** arr = calloc(size, sizeof(*arr));
    if (arr == NULL) abort();
    
    for (int i = 0; i < size; i++) {
        arr[i] = calloc(size, sizeof(**arr));
        if (arr[i] == NULL) abort();
            arr[i] = checkEnter(arr[i]);
    }
    
    for (int i = 0; i < size; i++) {
            printf("%3d ", arr[i]);
    }

}