#include<stdio.h>
#include<conio.h>


int main()
{
	int i, j, klucz;
	const int n = 10;
	int tab[n];
	for (i = 0; i < n; i++) scanf("%d", &tab[i]);

	for (i = 1; i < n; i++)
	{
		j = i;
		klucz = tab[j];
		while ((j > 0) && (klucz < tab[j-1]))
		{
			tab[j] = tab[j-1];
			j--;
		}
		tab[j] = klucz;
	}

	for (i = 0; i < n; i++) printf("%d ", tab[i]);
	getch();
}