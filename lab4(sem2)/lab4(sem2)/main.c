#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

int main() {
    binaryTree* tree = NULL;
    tree = insert(tree, 50);
    tree = insert(tree, 30);
    tree = insert(tree, 20);
    tree = insert(tree, 40);
    tree = insert(tree, 70);
    tree = insert(tree, 60);
    tree = insert(tree, 80);
    Print(tree);
    return 0;
}