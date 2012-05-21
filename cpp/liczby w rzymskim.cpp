#include<stdio.h>
#include<conio.h>

int main()
{
	int n, k = 0;
	scanf("%d", &n);

	while (n - 1000 >= 0)
	{
		printf("M");
		n -=1000;
	}

	while (n - 100 >= 0)
	{
		n -= 100;
		++k;
	}

	if (k > 0)
	{
		if (k <= 3) for (k; k > 0; k--) printf("C");
		else if (k == 4) printf("CD");
		else if (k <= 8)
		{
			printf("D");
			for(k -=5; k > 0; k--) printf("C");
		}
		else printf("CM");
	}
	k = 0;

	while (n - 10 >= 0)
	{
		n -= 10;
		++k;
	}

	if (k > 0)
	{
		if (k <= 3) for (k; k > 0; k--) printf("X");
		else if (k == 4) printf("XL");
		else if (k <= 8)
		{
			printf("L");
			for(k -=5; k > 0; k--) printf("X");
		}
		else printf("XC");
	}
	k = 0;

	while (n - 1 >= 0)
	{
		n -= 1;
		++k;
	}

	if (k > 0)
	{
		if (k <= 3) for (k; k > 0; k--) printf("I");
		else if (k == 4) printf("IV");
		else if (k <= 8)
		{
			printf("V");
			for(k -=5; k > 0; k--) printf("I");
		}
		else printf("IX");
	}
	getch();
}
