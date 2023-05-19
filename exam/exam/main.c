#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "hashtable.h"
#include "function.h"

int main() {
	lru_cache* cache = create_cache(SIZE_OF_CACHE);
	int choice = 0;
	do {
		menu_info();
		choice = choice_menu();
		switch (choice) {
		case 1:
			search_ip(cache);
			break;
		case 2:
			print_cache(cache);
		case 3:
			domain_search_by_ip();
		case 4:
			break;
		default:
			exit(PROGRAMM_ERROR);
		}
	} while (choice != EXIT);
	free_cache(cache);
	return 0;
}