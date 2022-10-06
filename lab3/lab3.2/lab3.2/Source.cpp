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
	int pathNumber, z, i, size, b, arr[100] = { 0 };
	printf("Enter size\n");
	scanf_s("%d", &size);
	printf("Select the path to fill the array (1 by yourself,2 random)\n");
	scanf_s("%d", &pathNumber);
	switch (pathNumber)
	{
	case 1:
		for (i = 0; i < size; i++)
		{
			scanf_s("%d", &z);
			arr[i] = z;
		}
		break;
	case 2:
		for (i = 0; i < size; i++)
		{
			arr[i] = rand() % 10;
		}
		for (i = 0; i < size; ++i)
			printf("%3d ", arr[i]);  // 4 1 7 9 3
		break;
	default:
		printf("Error unknown number.\n");
	}
	printf("\n");
	printf("\n");
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