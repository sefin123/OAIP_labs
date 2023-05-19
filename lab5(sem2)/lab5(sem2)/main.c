#include "Header.h"

int main()
{
    HashTable hash = { HASH_SIZE, calloc(HASH_SIZE, sizeof(Queue)) };
    int choice;
    bool menu = true;
    while (menu) {
        printf("1.Find IP\n2.Find domain\n3.Print Hash\n0.Exit\nChoice: ");
        (void)scanf("%d", &choice);
        if (choice == 1) {
            char search[MAX_STRING_LENGTH];
            printf("\nEnter domain: ");
            (void)scanf("%s", search);
            findIPByDomain(&hash, search);
        }
        if (choice == 2)
            findDomainByIP();
        if (choice == 3)
            printTable(&hash);
        if (choice == 0) {
            menu = false;
        }
    }
    return 0;
}