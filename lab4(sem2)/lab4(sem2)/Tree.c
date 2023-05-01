#include <stdio.h>
#include "Header.h"
#include "Tree.h"
#include "log.h"

Node* createNode(const char* word, Node* left, Node* right) {
    Node* node = malloc(sizeof(*node));
    if (node == NULL) abort();

    strcpy(node->word, word);
    node->left = left;
    node->right = right;
    return node;
}

void serializeTree(Node* root, FILE* out) {
    if (root == NULL) {
        fprintf(out, "%s\n", NULL_STRING);
        return;
    }

    fprintf(out, "%s\n", root->word);
    serializeTree(root->left, out);
    serializeTree(root->right, out);
}

Node* deserializeTree(FILE* in) {
    Node* node = malloc(sizeof(*node));
    if (node == NULL) abort();

    if (fgets(node->word, MAX_STRING_LENGTH, in) == NULL) return NULL;


    if (strcmp(node->word, NULL_STRING) == 0) {
        free(node);
        return NULL;
    }

    node->left = deserializeTree(in);
    node->right = deserializeTree(in);

    return node;
}

void freeTree(Node** node) {
    if (*node == NULL) return;

    freeTree(&(*node)->left);
    freeTree(&(*node)->right);

    free(*node);
}