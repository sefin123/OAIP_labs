#include <stdio.h>
int main()
{
	int a = 2 , s , i, x = 1 ;
	printf("enter s=\n");
	scanf_s("%d", &s);

	i = s / 5;
	while (x < i)
	{ 
		if ((s - x * 5) % 3 == 0) {
			a++;
		}
		x++;
	}
	printf("number of pairs %d", a);
	return 0;
}