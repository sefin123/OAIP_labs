#include "Header.h"

int main(int argc, char** argv) {
	check(argc);
	char** string = NULL;
	string = (char**)calloc(argc - 1, sizeof(char*));

	memory(string, argc, argv);
	copy(string, argc, argv);
	output(string, argc - 1);
	
	merge_sort(string, 0, (argc - 1 - 1));
	output(string, argc - 1);
	
	free(string, argc - 1);
}