#include <stdio.h>
#include <locale.h>

int main()
{
	setlocale(LC_ALL, "Rus");
	int a,i =0;
	printf("������� �������\n");
	scanf_s("%d", &a);
	if (a == 1) {
	printf("��� %d ���", a);
	i++;
}
	else if (a < 5) {
		printf("��� %d ����", a);
		i++;
	}
	else if(a < 10) {
		printf("��� %d ���", a);
	}
	return 0;
	
}