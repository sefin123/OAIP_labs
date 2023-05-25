#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>
#include "Header.h"

int main() {
    
    void (*task1) (void) = &taskFirst;
    void (*task2) (void) = &taskSecond;

    printf("choose task\n");
    int task = enterWithValidation();

    if (task == 1) {
        task1();
    }
    else {
        task2();
    }

    return 0;
}