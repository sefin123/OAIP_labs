#include <stdio.h>
#include <math.h>
int main()
{
	double d_ab, x1 , y1 , x2 , y2 , x3 , y3 , a , b , A , B , C;
	printf("enter A \n");
		scanf_s("%lf" , &x1);
		scanf_s("%lf", &y1);
		printf("enter B \n");
		scanf_s("%lf", &x2);
		scanf_s("%lf", &y2);
		printf("enter C \n");
		scanf_s("%lf", &x3);
		scanf_s("%lf", &y3);
		printf("enter M \n");
		scanf_s("%lf", &a);
		scanf_s("%lf", &b);
		A = (x1 - a) * (y2 - y1) - (x2 - x1) * (y1 - b);
		B = (x2 - a) * (y3 - y2) - (x3 - x2) * (y2 - b);
		C = (x3 - a) * (y1 - y3) - (x1 - x3) * (y3 - b);
		if (A >= 0 && B >= 0 && C >= 0 || A <= 0 && B <= 0 && C <= 0)
			printf("in");
		else
			printf("out");
		return 0;
}