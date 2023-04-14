#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"

binaryTree* createNode(int data) {
    binaryTree* newNode = malloc(sizeof(newNode));
    if (newNode == NULL) abort();

    newNode->data = data;
    //newNode->word = malloc(256);
    newNode->left = NULL;
    newNode->right = NULL;
    
    return newNode;
}

binaryTree* insert(binaryTree* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }

    if (data <= root->data) {
        root->left = insert(root->left, data);
    }

    else if (data >= root->data) {
        root->right = insert(root->right, data);
    }

    return root;
}


void Print(binaryTree* tree) {
    if (tree != NULL) { //���� �� ���������� ������ ����
        printf("%d ", tree->data); //���������� ������ ������
        Print(tree->left); //����������� ������� ��� ������ ���������
        Print(tree->right); //����������� ������� ��� ������� ���������
    }
}