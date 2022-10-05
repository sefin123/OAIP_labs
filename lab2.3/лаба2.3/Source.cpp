#include <stdio.h>
int main()
{
	int i, precision;
double x, a , b = 1, power;
printf("enter x=\n");
scanf_s("%lf", &x);
printf("enter precision=\n");
scanf_s("%d", &precision);
a = x;
for (i = 2;i < precision;i = i + 2)
{
	power = x * x;
	a = a *  (-1) * power;
	b = b * (i + 1) * i;
	x = x + a / b;
}
printf("sinx =%lf", x);
return 0;
}