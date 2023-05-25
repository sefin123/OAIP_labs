#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int findIndexNegativeElement(int startIndex,int endIndex,int arr[])
{
	for (int i = startIndex; i < endIndex; i++)
	{
		if (arr[i] < 0) {
			return i;
		}
	}
	return 0;
}

int main()
{
	srand((unsigned int)time(NULL));
	int pathNumber, z, i, size = 0, arr[100] = { 0 };
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

	for (i = 0; i < size; i++)
		printf("%3d", arr[i]);

	int min = arr[0];
	int indexOfMin = 0;
	for (i = 1; i < size; i++)
	{
		if (min > arr[i])
		{
			min = arr[i];
			indexOfMin = i;
		}
	}
	printf("\n Position of min element %d\n", indexOfMin);
	int firstIndexNegativeNumber = findIndexNegativeElement(0, size - 1, arr);
	int secondIndexNegativeNumber = findIndexNegativeElement(firstIndexNegativeNumber + 1, size, arr);
	int sum = 0;
	for (int i = firstIndexNegativeNumber + 1; i < secondIndexNegativeNumber; i++)
	{
		sum += arr[i];
	}
	printf("Sum: %d", sum);

	return 0;
}