#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>
#include "Header.h"

int main() {
    
    printf("choose task\n");
    int task = enterWithValidation();

    if (task == 1) {
        taskFirst();
    }
    else {
        taskSecond();
    }

    return 0;
}