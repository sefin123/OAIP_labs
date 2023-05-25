#include <stdio.h>
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "Rus");
	int a,i =0;
	printf("введите возраст\n");
	scanf_s("%d", &a);
	if (a == 1) {
	printf("мне %d год", a);
	i++;
}
	else if (a < 5) {
		printf("мне %d года", a);
		i++;
	}
	else if(a < 10) {
		printf("мне %d лет", a);
	}
	return 0;
	
}