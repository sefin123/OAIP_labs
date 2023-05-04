#include "Header.h"

char *enterIPwithValidation(char *a) {
    while (scanf("%s", a) != 1 || a[3] != '.' || a[7] != '.' ||  a[11] != '.') {
        printf("Wrong IP\nPlease check that the IP is entered correctly\n");
        rewind(stdin);
    }
    return a;
}

Data* readingString(char* str, Data* data) {
    int begin;
    for (int i = 0; i != ' '; i++) {
        data->domain[i] = str[i];

        if (str[i] == ' ') {
            data->domain[i] = '\0';
            begin = i;
        }
    }
    for (int i = 0, j = begin + 1; str[j] != '\n'; i++, j++) {
        data->IP[i] = str[j];

        if (str[j + 1] == '\n') data->IP[i + 1] = '\0';
    }
    hash(data->domain);
    return data;
}

List* createList() {
    List* tmp = malloc(sizeof(*tmp));
    if (tmp == NULL) abort();
        tmp->head = NULL;
        tmp->tail = NULL;
    return tmp;
}

void freeList(List** list) {
    Node* tmp = (*list)->head;
    Node* next = NULL;
    while (tmp) {
        next = tmp->next;
        free(tmp);
        tmp = next;
    }
    free(*list);
    (*list) = NULL;
}

void push(List* list, Data* data) {
    Node* tmp = malloc(sizeof(*tmp));
    if (tmp == NULL) abort();
    strcpy(tmp->key, data->domain);
    strcpy(tmp->value, data->IP);
    tmp->next = list->head;
    tmp->prev = NULL;
    if (list->head) {
        list->head->prev = tmp;
    }
    list->head = tmp;

    if (list->tail == NULL) {
        list->tail = tmp;
    }
}

void* popBack(List* list) {
    Node* next;
    void* tmp;
    if (list->tail == NULL) {
        exit(4);
    }

    next = list->tail;
    list->tail = list->tail->prev;
    if (list->tail) {
        list->tail->next = NULL;
    }
    if (next == list->head) {
        list->head = NULL;
    }
    tmp = next->value;
    free(next);

    return tmp;
}

List* deserializeList() {
    FILE* file = fopen("map.txt", "r");
    Data* data = malloc(sizeof(*data));
    if (data == NULL) abort();
    List** list = NULL;
    for (int i = 0; i < 5; i++)
        list = createList();
    char str[MAX_STRING_LENGTH];

    while (fgets(str, MAX_STRING_LENGTH, file) != NULL) {
        data = readingString(str, data);
        push(list, data);
    }
    fclose(file);

    return list;
}

int hash(char* str) {
    int hash = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        hash = hash * 31 + str[i];
    }
    return hash % 5;
}

void serializeList(List* list) {
    FILE* file = fopen("map.txt", "w");
    for (Node* it = list->head; it != list->tail->next; it = it->next) {
        fprintf(file, "%s ",it->key);
        fprintf(file, "%s\n", it->value);
    }
    fclose(file);
}

void findIPInFile(List* list, char* search,bool hit) {
    FILE* file = fopen("database.txt", "r");
    Data* data = malloc(sizeof(*data));
    if (data == NULL) abort();
    char str[MAX_STRING_LENGTH];
    while (fgets(str, MAX_STRING_LENGTH, file) != NULL) {
        readingString(str, data);

        if (strcmp(search, data->domain) == 0) {
            hit = true;
            printf("Found in File:%s\n", data->IP);
            push(list, data);
            popBack(list);
            serializeList(list);
        }
    }
    if (!hit)
        printf("Not found in File\n");
}

bool findIPInhash(List* list, char* search, bool hit) {

    for (Node* it = list->head; it != list->tail->next; it = it->next) {
        if (strcmp(it->key, search) == 0) {
            printf("Found in hash:%s\n", it->value);
            hit = true;
        }
    }
    if (!hit)
        printf("Not found in hash\n");
    return hit;
}

void printList(List* list) {
    for (Node* it = list->head; it != list->tail->next; it = it->next) {
        printf("domain:%s\n", it->key);
        printf("IP:%s\n", it->value);
    }
}



int main() {
    bool exit = true;
    while (exit) {
        printf("1.Find IP\n2.Print hash\n0.Exit\n");
        int valueMenu;
        (void)scanf("%d", &valueMenu);

        List* list = deserializeList();

        if (valueMenu == 1) {
            bool hit = false;
            printf("Enter domain:");
            char search[MAX_STRING_LENGTH];
            (void)scanf("%s", search);
            hit = findIPInhash(list, search, hit);
            if (!hit) {
                findIPInFile(list, search, hit);
            }
        }
        if (valueMenu == 2)
            printList(list);
        if (valueMenu == 0) {
            freeList(&list);
            exit = false;
        }
    }
    return 0;
}