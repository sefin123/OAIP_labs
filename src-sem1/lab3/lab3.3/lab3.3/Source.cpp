#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int main()
{
	srand((unsigned int)time(NULL));
	int pathNumber,i, size = 0,arrFirst[100] = { 0 },arrSecond[100] = { 0 } , toggle = 0;
	bool boolean = 0;
	printf("Enter size\n");
	while (scanf_s("%d", &size) != 1 || size > 100 || size < 1 || size % 1 != 0 || getchar() != '\n') {
		rewind(stdin);
		printf("Enter size\n");
	}
	printf("Select the path to fill the array (1 by yourself,2 random)\n");
	while (scanf_s("%d", &pathNumber) == 0 || pathNumber < 1 || pathNumber > 2 || getchar() != '\n')
	{
		rewind(stdin);
		printf("Error unknown number\n");
	}
	switch (pathNumber)
	{
	case 1:
		printf("Enter arrayFirst\n");
		for (int i = 0; i < size; i++) {
			while (scanf_s("%d", &arrFirst[i]) != 1 || getchar() != '\n') {
				rewind(stdin);
				printf("Enter first array again\n");
			}
		}
		printf("Enter arraySecond\n");
		for (int i = 0; i < size; i++) {
			while (scanf_s("%d", &arrSecond[i]) != 1 || getchar() != '\n') {
				rewind(stdin);
				printf("Enter second array again\n");
			}
		}
		break;
	case 2:
		for (int i = 0; i < size; i++) {
			arrFirst[i] = rand() % 10;
		}
		for (int i = 0; i < size; i++) {
			arrSecond[i] = rand() % 10;
		}
		break;
	default:
		printf("Error unknown number\n");
		while (scanf_s("%d", &pathNumber) == 0 || pathNumber < 0) {
			printf("Error unknown number\n");
			rewind(stdin);
		}
	}

	printf("\narrayFirst\n");
	for (int i = 0; i < size; i++) {
		printf("%d ", arrFirst[i]);
	}
	printf("\narraySecond\n");
	for (int i = 0; i < size; i++) {
		printf("%d ", arrSecond[i]);
	}
	i = 0;
	while (toggle != 1) {	
		if (arrFirst[i] != arrSecond[i]) {
			break;
		}
		i++;
	}
	if (arrFirst[i] > arrSecond[i]){
		for (i = size - 1; i >= 0; i--){
		arrFirst[i] = arrFirst[i] - arrSecond[i];
			if (arrFirst[i] < 0) {
				arrFirst[i] += 10;
				arrFirst[i - 1] -= 1;
			}
		}
	}
	printf("\nThe resulting array\n");
	for (int i = 0; i < size; i++) {
		printf("%d ", arrFirst[i]);
	}
	
	return 0;
}