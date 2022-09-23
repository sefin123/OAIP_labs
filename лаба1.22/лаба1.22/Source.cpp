#include <stdio.h>
int main()
{
	int n, p, m, k = 0;
	printf("enter m\n", &m);
	scanf_s("%d", &m);
	printf("enter n\n ", &n);
	scanf_s("%d", &n);
	printf("enter p\n ", &p);
	scanf_s("%d", &p);
	if (m < 0) {
		 k++;
	}
	if (n < 0) {
		k++;
	}
	if (p < 0) {
		k++;
	}
	printf(" number of negative numbers %d\n" , k);




	return 0;
}