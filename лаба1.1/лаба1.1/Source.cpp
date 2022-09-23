#include <stdio.h>


int main()
{
	double radius, height, square , totalsquare , volume;
	const double pi = 3.1415926535897932384626433832795;

	printf("enter radius\n", &radius);
	scanf_s("%lg" , &radius);
	printf("enter height\n", &height);
	scanf_s("%lg", &height);

	square = 2 * pi * radius * height;
	totalsquare = 2 * pi * radius * height + 2 * pi * radius * radius;
	volume = pi * radius * radius * height;

	printf("square is %0.2f\n", square);
	printf("total square is %0.2f\n", totalsquare);
	printf("volume is %0.2f\n", volume);
	return 0;
}