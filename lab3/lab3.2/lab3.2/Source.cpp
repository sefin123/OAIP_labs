#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int module(int number) {
	return number < 0 ? number * -1 : number;
}

void moveArray(int startIndex, int endIndex,int distance,int arr[]) {
	for (int i = startIndex; i < endIndex; i++) {
		arr[i] = arr[i + distance - 1];
	}
}

int main()
{
	srand((unsigned int)time(NULL));
	int pathNumber, i, size = 0, arr[100] = { 0 };
	bool boolean = 0;
	printf("Enter size\n");
		while (scanf_s("%d",&size) !=1 || size > 100 || size < 1 || size % 1 != 0 || getchar()!='\n') {
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
		printf("Enter array\n");
		for (int i = 0; i < size; i++) {
			while (scanf_s("%d", &arr[i]) != 1 || getchar() != '\n') {
				rewind(stdin);
				printf("enter array again\n");
			}
		}
		break;
	case 2:
		for (int i = 0; i < size; i++) {
			arr[i] = rand() % 100 - 50;
		}
		break;
	default:
		printf("Error unknown number\n");
		while (scanf_s("%d", &pathNumber) == 0 || pathNumber < 0) {
			printf("Error unknown number\n");
			rewind(stdin);
		}
	}
	for (int i = 0; i < size; i++) {
		printf("%3d ", arr[i]);
	}
	printf("\n");
	int max = arr[0];
	int indexOfMax = 0;
	for (int i = 0; i < size; i++){
		if (arr[i] >= max){
			max = arr[i];
			indexOfMax = i;
		}
	}

	int min = arr[0];
	int indexOfMin = 0;
	for (int i = 0; i < size; i++){
		if (arr[i] < min){
			min = arr[i];
			indexOfMin = i;
		}
	}

	int distance = module(indexOfMin - indexOfMax);
	indexOfMax < indexOfMin // -2(0) 3 4 4(3) -2 
		? moveArray(indexOfMax + 1, indexOfMin, distance, arr)
		: moveArray(indexOfMin + 1, indexOfMax, distance, arr);
	/*void moveArray(int startIndex, int endIndex, int distance, int arr[]) {
		for (int i = startIndex(1); i < endIndex(3); i++) {
			arr[i] = arr[i + distance - 1];
		}
	}*/

	for (int i = 0; i <= size - distance; i++) {
		printf("%3d ", arr[i]);
	}

	return 0;
}