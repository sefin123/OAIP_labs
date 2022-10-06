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
	int pathNumber, i, size = 0, b, arr[100] = { 0 };
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
		printf("Enter array\n");
		for (int i = 0; i < size; i++) {
			boolean = scanf_s("%d", &arr[i]);
			while (boolean != 1) {
				printf("enter array again\n");
				rewind(stdin);
				boolean = scanf_s("%d", &arr[i]);
			}
		}
		break;
	case 2:
		for (int i = 0; i < size; i++) {
			arr[i] = rand() % 10;
		}
		break;
	default:
		printf("Error unknown number\n");
	}

	int max = arr[0];
	int indexOfMax = 0;
	for (int i = 0; i < size; i++)
	{
		if (arr[i] >= max)
		{
			max = arr[i];
			indexOfMax = i;
		}
	}

	int min = arr[0];
	int indexOfMin = 0;
	for (int i = 0; i < size; i++)
	{
		if (arr[i] < min)
		{
			min = arr[i];
			indexOfMin = i;
		}
	}

	int distance = module(indexOfMin - indexOfMax);
	indexOfMax < indexOfMin 
		? moveArray(indexOfMax + 1, indexOfMin, distance, arr)
		: moveArray(indexOfMin + 1, indexOfMax, distance, arr);

	for (int i = 0; i <= size - distance; i++) {
		printf("%3d ", arr[i]);
	}

	return 0;
}