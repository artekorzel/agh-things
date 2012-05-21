#include<stdio.h>
#include<conio.h>

int main()
{
	int i, j = 1, tmp, a;
	const int n = 10;
	int tab[n];
	for (i = 0; i < n; i++) scanf("%d", &tab[i]);

	while (j)
	{
		j = 0;
		for (i = 1; i < n; i++)
		{
			a = i-1;
			if (tab[i] < tab[a])
			{
				tmp = tab[i];
				tab[i] = tab[a];
				tab[a] = tmp;
				j = 1;
			}
		}
	}

	for (i = 0; i < n; i++) printf("%d ", tab[i]);
	getch();
}

