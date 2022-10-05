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
	int pathNumber, z, i, size, arr[100] = { 0 };
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
				arr[i] = rand() % 10 - 3;
			}
			break;
		default:
			printf("Error unknown number.\n");
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


