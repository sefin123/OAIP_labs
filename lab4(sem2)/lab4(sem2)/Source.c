#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"
#include "Tree.h"
#include "log.h"

#define MAX_STRING_LENGTH 256
#define NULL_STRING "NULL"

int enterWithValidation() {
    int a;
    while (scanf_s("%d", &a) != 1 || a > 1 || a < 0 || getchar() != '\n') {
        printf("error\n");
        rewind(stdin);
    }
    return a;
}

void correctAnswersTree(Node* node) {
    printf("\nWhat was that?\nName: ");
    char answer[MAX_STRING_LENGTH];
    while (getchar() != '\n');
    fgets(answer, MAX_STRING_LENGTH, stdin);
    answer[strlen(answer) - 1] = '\0';
    messageLog("New entity: %s", answer);

    printf("\nWhat question is better to ask?\nQuestion: ");
    char question[MAX_STRING_LENGTH];
    fgets(question, MAX_STRING_LENGTH, stdin);
    question[strlen(question) - 1] = '\0';

    messageLog("New question: %s", question);

    node->left = createNode(node->word, NULL, NULL);
    node->right = createNode(answer, NULL, NULL);

    strcpy(node->word, question);
}

void gameAkinator(Node* root) {
    messageLog("Question: %s", root->word);
    
    printf("%s?\n1.yes//0.no\nchoose: ", root->word);
    int choice;
    (void)scanf("%d", &choice);
    messageLog("Choice: %d", choice);

    if (!(root->right == NULL || root->left == NULL)) {
        if (choice == 0)gameAkinator(root->left);
        if (choice == 1)gameAkinator(root->right);
    }

    if (root->right == NULL && root->left == NULL) {
        if (choice == 0) correctAnswersTree(root);
        if (choice == 1) printf("\nEnd of the game\n");
    }
}