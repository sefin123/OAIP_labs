#include "Header.h"

int checkIPWithValidation(char* ip) {
    if (ip == NULL) {
        return 0;
    }
    int partsIP[4];
    int nums = sscanf(ip, "%d.%d.%d.%d", &partsIP[0], &partsIP[1], &partsIP[2], &partsIP[3]);
    if (nums != 4) {
        return 0;
    }
    for (int i = 0; i < 4; i++) {
        if (partsIP[i] < 0 || partsIP[i] > 255) {
            return 0;
        }
    }
    return 1;
}

unsigned int convertHash(const char* str) {
    unsigned int hash = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        hash = hash * 31 + str[i];
    }
    return hash;
}

void addDomainToFile(char* search) {
    printf("There are no element.Add your ");

    char ip[MAX_STRING_LENGTH];
    do {
        printf("IP: ");
        (void)scanf("%s", ip);
    } while (!checkIPWithValidation(ip));
    FILE* file = fopen("database.txt", "a");
    if (file == NULL) abort();

    fprintf(file, "%s IN A %s\n", search, ip);

    fclose(file);

}

void push(HashTable* hash, char* domain, char* ip) {
    int index = convertHash(domain) % hash->size;

    while (hash->table[index] != NULL && index < hash->size)
        index++;

    if (index >= hash->size) {
        for (int i = 0; i < hash->size - 1; i++) {
            hash->table[i] = hash->table[i + 1];
        }

        hash->table[index - 1] = NULL;
        index--;
    }

    Hash* h = malloc(sizeof(Hash));
    if (h == NULL) abort();

    strcpy(h->key, domain);
    strcpy(h->value, ip);

    h->prev = NULL;
    h->next = NULL;
    hash->table[index] = h;
}

void CNAMECheck(char* newDomain) {
    FILE* file = fopen("database.txt", "r");
    if (file == NULL) abort();

    char str[MAX_STRING_LENGTH]; char domain[MAX_STRING_LENGTH]; char cname[MAX_STRING_LENGTH];

    while (fgets(str, MAX_STRING_LENGTH, file) != NULL) {
        if (sscanf(str, "%s IN CNAМЕ %s", domain, cname) == 2) {
            domain[strlen(domain)] = '\0';
            if (strcmp(domain, newDomain) == 0) {
                cname[strlen(cname)] = '\0';

                strcpy(newDomain, cname);
            }
        }
    }
    fclose(file);
}

void findInFile(HashTable* hash, char* search) {
    CNAMECheck(search);
    bool isThere = false;
    char str[MAX_STRING_LENGTH]; char domain[MAX_STRING_LENGTH]; char ip[MAX_STRING_LENGTH];

    FILE* file = fopen("database.txt", "r");

    while (fgets(str, MAX_STRING_LENGTH, file) != NULL) {
        if (sscanf(str, "%s IN A %s", domain, ip) == 2) {
            domain[strlen(domain)] = '\0';

            if (strcmp(domain, search) == 0) {
                push(hash, search, ip);

                isThere = true;
            }
        }
    }

    if (!isThere)
        addDomainToFile(search);

    fclose(file);
}

char* hashtable_search(HashTable* table, char* key) {   //осуществляет поиск значения по ключу в хэш-таблице 
    int index = hash_function(key);
    Queue* current_object = table->table[index];
    HashTable* head = table->table[index]->head;
    while (current_object != NULL) {
        if (!strcmp(current_object->, key))
            return current_object->node->value;
        if (head == NULL)
            return NULL;
        current_object = head->object;
        head = head->next;
    }
    return NULL;
}

void findIPByDomain(HashTable* hash, char* search) {

    bool HIT = false;
    for (int i = convertHash(search) % hash->size; i < hash->size; i++) {
        Queue* h = hash->table[i];
        while (h != NULL) {
            if (strcmp(h->head->key, search) == 0) {
                if (!HIT) printf("\n%s\n\n", h->head->value);
                HIT = true;
                for (int j = i; j < hash->size - 1; j++) {
                    hash->table[j] = hash->table[j + 1];
                }
                hash->table[hash->size - 1] = h;
            }
            h = h->head->next;
        }
    }
    if (!HIT) {
        findInFile(hash, search);
        findIPByDomain(hash, search);
    }
}

void printTable(HashTable* hash) {
    if (hash == NULL) return;
    for (int i = 0; i < hash->size; i++) {
        Hash* h = hash->table[i];
        if (h != NULL) {
            printf("%s IN A %s\n", h->key, h->value);
            h = h->next;
        }
    }
    printf("\n");
}

void findDomainByIP() {
    char search[MAX_STRING_LENGTH];
    printf("Enter IP: ");
    (void)scanf("%s", search);

    FILE* file = fopen("database.txt", "r");
    if (file == NULL) abort();

    char str[MAX_STRING_LENGTH]; char domain[MAX_STRING_LENGTH]; char ip[MAX_STRING_LENGTH];
    bool isThere = false;

    while (fgets(str, MAX_STRING_LENGTH, file) != NULL) {
        if (sscanf(str, "%255s IN A %255s", domain, ip) == 2 && !isThere) {

            domain[strlen(domain)] = '\0';
            search[strlen(search)] = '\0';
            ip[strlen(ip)] = '\0';

            if (strcmp(search, ip) == 0) {

                printf("\n%s\n\n", domain);
                isThere = true;
                strcpy(search, domain);
            }
        }
        if (sscanf(str, "%255s IN CNAМЕ %255s", domain, ip) == 2 && isThere) {
            if (strcmp(search, ip) == 0)
                printf("%s\n\n", domain);
        }
    }
    if (!isThere) {
        int choice;
        printf("There are no IP.Try again?\n1.Yes\n2.NO\n");
        (void)scanf("%d", &choice);
        if (choice == 1)
            findDomainByIP();
        if (choice == 2)
            return;
    }
}

void freeNode(Hash* node) {
    if (node == NULL) return;
        free(node->key);
        free(node->value);
        free(node);
}

void freeHashTable(HashTable* hash) {
    if (hash == NULL) return;

    for (int i = 0; i < hash->size; i++) {
        Hash* buf = hash->table[i];
        if (buf != NULL) {
            freeNode(buf);
        }
    }
    free(hash->table);
}