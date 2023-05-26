#include "Header.h"
#include "list.h"

int enterWithValidationForIndex(int value) {
    int a;

    while (scanf_s("%d", &a) != 1 || a < 1 || a > value || getchar() != '\n') {
        printf("Error\n");
        rewind(stdin);
    }

    return a;
}

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

void hashTableDelete(HashTable* hashTable, const char* key) {
    int index = convertHash(key) % HASH_SIZE;
    Node* currentNode = hashTable->buckets[index].head;
    Node* previousNode = NULL;

    while (currentNode != NULL) {
        if (strcmp(currentNode->data.key, key) == 0) {
            if (previousNode == NULL) {
            
                hashTable->buckets[index].head = currentNode->next;
            }
            else {
                previousNode->next = currentNode->next;
            }
            
            if (currentNode == hashTable->buckets[index].tail) {
                hashTable->buckets[index].tail = previousNode;
            }

            free(currentNode);
            hashTable->count--;
            return;
        }
        previousNode = currentNode;
        currentNode = currentNode->next;
    }
}

void deleteTail(Node** head, Node** tail) {
    Node* temp = (*head);
    if ((*tail) != (*head)) {
        while (temp->next != (*tail))
            temp = temp->next;
        (*tail) = temp;
        (*tail)->next = NULL;
    }
    else {
        (*tail) = NULL;
        (*head) = NULL;
    }
}

void ToHead(Node** head, Node** tail, const char* key, const char* value) {

    Data data = { 0 };
    strcpy(data.key, key);
    strcpy(data.value, value);
    Node* temp = initNode(malloc(sizeof(*temp)), data);


    if ((*head) == NULL) {
        (*head) = temp;
        (*tail) = temp;
    }
    else {
        temp->next = (*head);
        (*head)->prev = temp;
        (*head) = temp;
    }
}

void preoritet(Node* node, HashTable* cashe) {
    if (node == NULL) return;
    if (cashe->head == node)
        return;

    Node* temp = cashe->head;

    cashe->head = node;
    
    node->prev->next = node->next;

    if (node->next != NULL)
        node->next->prev = node->prev;

    if (cashe->tail == node)
        cashe->tail = node->prev;

    node->next = temp;
    node->prev = NULL;

    temp->prev = node;
}

void insertHashtable(HashTable* table, char* key, char* value) {
    Data data = { 0 };
    strcpy(data.key, key);
    strcpy(data.value, value);

    List* bucket = mapBucket(table, key);
    Node* currentNode = bucket->head;
    while (currentNode != NULL) {
        if (strcmp(currentNode->data.key, key) == 0) {
            strcpy(currentNode->data.value, value);
            return;
        }
        currentNode = currentNode->next;
    }
    Node* newNode = malloc(sizeof(*newNode));
    if (newNode == NULL) abort();
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;

    if (bucket->head == NULL) {
        bucket->head = newNode;
        bucket->tail = newNode;
    }
    else {
        bucket->tail->next = newNode;
        newNode->prev = bucket->tail;
        bucket->tail = newNode;
    }
    table->count++;
}

void insertCache(HashTable* cache, const char* key, const char* value) {
    if (cache->count > HASH_SIZE) {
        hashTableDelete(cache->buckets, cache->tail->data.key);

        deleteTail(&cache->head, &cache->tail);
    }
    ToHead(&cache->head, &cache->tail, key, value);
    insertHashtable(cache->buckets, key, value);
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

List* mapBucket(HashTable* self, const char* key) {
    return &self->buckets[convertHash(key) % HASH_SIZE];
}

Node* findNode(HashTable* self, const char* key) {
    List* bucket = mapBucket(self, key);
    for (Node* it = bucket->head; it; it = it->next) {
        if (!strcmp(it->data.key, key)) {
            insertCache(self, key, it->data.value);
            
            return it;
        }
    }
    return NULL;
}

char* findIPPushToBucket(HashTable* hash, const char* key) {
    Node* node = findNode(hash, key);
    preoritet(node, hash);

    List* bucket = mapBucket(hash, key);
    detachFromList(bucket, node);
    pushNodeFront(bucket, node);

}

char* findIpInFile(HashTable* hash, char* search) {
    search = findCNAMEDomain(search);
    bool isThere = false;
    char str[MAX_STRING_LENGTH]; char domain[MAX_STRING_LENGTH]; char ip[MAX_STRING_LENGTH];

    FILE* file = fopen("database.txt", "r");

    while (fgets(str, MAX_STRING_LENGTH, file) != NULL) {
        if (sscanf(str, "%s IN A %s", domain, ip) == 2) {
            domain[strlen(domain)] = '\0';
            ip[strlen(ip)] = '\0';

            if (strcmp(domain, search) == 0) {
                printf("%s\n", ip);
                return _strdup(ip);
                isThere = true;
            }
        }
    }

    if (!isThere)
        addDomainToFile(search);
    
    return NULL;

    fclose(file);
}

void setInHash(HashTable* self, const char* key, const char* value) {
    Node* node = findNode(self, key);
    if (node != NULL) {
        List* bucket = mapBucket(self, key);
        detachFromList(bucket, node);
        pushNodeFront(bucket, node);

        strcpy(node->data.value, value);
        return;
    }

    Data data = { 0 };
    strcpy(data.key, key);
    strcpy(data.value, value);
    pushFront(mapBucket(self, key), data);
    node = findNode(self, key);
}

void findIP(const char* domain, FILE* source, HashTable* cache) {
    char* ip = findIPPushToBucket(cache, domain);
    if (ip != NULL) return ;

    ip = findIpInFile(cache, domain);
    if (ip == NULL) return ;

    setInHash(cache, domain, ip);
    return ip;
}

char* findCNAMEDomain(char* newDomain) {
    FILE* file = fopen("database.txt", "r");
    if (file == NULL) abort();

    char str[MAX_STRING_LENGTH];
    while (fgets(str, MAX_STRING_LENGTH, file) != NULL) {
        char domain[MAX_STRING_LENGTH];
        char cname[MAX_STRING_LENGTH];
        if (sscanf(str, "%s IN CNAÃ≈ %s", domain, cname) == 2) {
            domain[strlen(domain)] = '\0';
            if (strcmp(domain, newDomain) == 0) {

                cname[strlen(cname)] = '\0';

                fclose(file);
                return _strdup(cname);
            }
        }
    }

    fclose(file);
    return newDomain;
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

            if (strcmp(search, ip) == 0) {//123 123

                printf("\n%s\n\n", domain);
                isThere = true;
                strcpy(search, domain); // 123 <- lms
            }
        }
        if (sscanf(str, "%255s IN CNAME %255s", domain, ip) == 2 && isThere) {
            if (strcmp(search, ip) == 0) {
                strcpy(search, domain);
            }// lms lms
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

HashTable* initHashTable(HashTable* self) {
    self->count = 0;
    self->head = NULL;
    self->tail = NULL;
    for (int i = 0; i < HASH_SIZE; i++) {
        initList(&self->buckets[i]);
    }
    return self;
}

void printCache(HashTable* cache) {
    Node* node = cache->head;
    while (node != NULL) {
        printf("%s - %s\n", node->data.key, node->data.value);
        node = node->next;
    }
}

void freeHash(HashTable* hash) {
    if (hash == NULL) return;
    for (int i = 0; i < HASH_SIZE; i++) {
        Node* current = &hash->buckets[i];
        Node* next;
        while (current != NULL) {
            next = current->next;
            free(current);
            current = next;
        }
    }
}

void printTable(HashTable* hash) {
    if (hash == NULL) return;

    for (int i = 0; i < HASH_SIZE; i++) {
        printf("--- Bucket %d ---\n", i);
        printList(hash->buckets[i]);
    }
    printf("\n");
}