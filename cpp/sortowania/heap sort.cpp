#include<stdio.h>
#include<time.h>
#include<stdlib.h>

void kopcuj(int *tab, int i, int n)
{
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	int tmp, maxi;

	if ((l < n) && (tab[l] > tab[i]))
		maxi = l;
	else maxi = i;
	if ((r < n) && (tab[r] > tab[maxi]))
		maxi = r;

	if (maxi != i)
	{
		tmp = tab[i];
		tab[i] = tab[maxi];
		tab[maxi] = tmp;
		kopcuj(tab, maxi, n);
	}
}

void buduj(int *tab, int n)
{
	int i;
	for(i = n/2 - 1; i >= 0; --i)
		kopcuj(tab, i, n);
}

int main()
{
	int i, tmp;
	const int n = 100;
	int tab[n];
	srand((int)(time(NULL)));
	for(i = 0; i < n; ++i) tab[i] = rand() % 100;

	buduj(tab, n);
	for(i = n - 1; i > 0; --i)
	{
		tmp = tab[0];
		tab[0] = tab[i];
		tab[i] = tmp;
		kopcuj(tab, 0, i);
	}

	for(i = 0; i < n; ++i) printf("%d ", tab[i]);
	getchar();
}