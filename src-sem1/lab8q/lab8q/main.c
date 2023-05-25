#include "Header.h"

int main(int argc, char** argv) {
	int* max;
	int* max_ind;
	max_ind = (int*)calloc(argc, sizeof(int));
	max = (int*)calloc(argc, sizeof(int));
	for (int i = 0; i < argc; i++) {
		max_ind[i] = i;
	}
	check(argc);
	char** string = NULL;
	string = (char**)calloc(argc - 1, sizeof(char*));
	memory(string, argc, argv);
	copy(string, argc, argv);
	longest_words(string, len_string, argc, max);
	output(string, argc - 1);
	merge(max_ind, max, 0, argc - 1);
	output(string, argc - 1);
	free(string, argc - 1);
}