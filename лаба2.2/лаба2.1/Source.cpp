#include <stdio.h>
int main()
{
	int n , sum2 = 0 , b =1, a=1 , sum3 = 0 ;
	printf("enter n =\n");
	scanf_s("%d", &n);
	while (a <= n)
	{
		if (a % 2 == 0) {
			sum2 = sum2 + a * a;
		}
			a++;
	}
	printf("sum2 =%d\n" , sum2);
	while (b <= n)
	{
		if (b % 2 == 0) {
			sum3 = sum3 + b * b * b;
		}
		b++;
	}
	printf("sum3 =%d\n", sum3);
	return 0;
}