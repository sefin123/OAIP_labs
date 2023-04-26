#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"
#include "log.h"

int main() {
    logOpen("test.log");
    
    FILE* in = fopen("test.txt", "r");
    Node* root = deserializeTree(in);
    fclose(in);

    gameAkinator(root);

    serializeTree(root, fopen("test.txt", "w"));

    freeTree(&root);

    return 0;
}