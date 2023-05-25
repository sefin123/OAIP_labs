#include "Header.h"

int main()
{
    HashTable *hash = initHashTable(malloc(sizeof(*hash)));
    int choice;
    bool menu = true;
    while (menu) {
        printf("1.Find IP\n2.Find domain\n3.Print cache\n4.Exit\nChoice: ");
        choice = enterWithValidationForIndex(4);
        if (choice == 1) {
            char search[MAX_STRING_LENGTH];
            printf("\nEnter domain: ");
            (void)scanf("%s", search);
            FILE* file = fopen("database.txt", "r");
            findIP(search, file, hash);
        }
        if (choice == 2) {
            findDomainByIP();
        }
        if (choice == 3) {
            printCache(hash);
        }
        if (choice == 4) {
            menu = false;
        }
    }
    return 0;
}