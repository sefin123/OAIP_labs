#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int main()
{
	srand((unsigned int)time(NULL));
	int pathNumber,i, size = 0,arrFirst[100] = { 0 },arrSecond[100] = { 0 } , toggle = 0;
	bool boolean = 0;
	while (size > 100 || size < 1 || size % 1 != 0) {
		rewind(stdin);
		printf("Enter size\n");
		scanf_s("%d", &size);
	}
	printf("Select the path to fill the array (1 by yourself,2 random)\n");
	scanf_s("%d", &pathNumber);
	switch (pathNumber)
	{
	case 1:
		printf("Enter arrayFirst\n");
		for (int i = 0; i < size; i++) {
			boolean = scanf_s("%d", &arrFirst[i]);
			while (boolean != 1) {
				printf("enter array again\n");
				rewind(stdin);
				boolean = scanf_s("%d", &arrFirst[i]);
			}
		}
		printf("Enter arraySecond\n");
		for (int i = 0; i < size; i++) {
			boolean = scanf_s("%d", &arrSecond[i]);
			while (boolean != 1) {
				printf("enter array again \n");
				rewind(stdin);
				boolean = scanf_s("%d", &arrSecond[i]);
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