#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int newgap(int oldgap)
{
	oldgap = oldgap * 10 / 13;
	if ((oldgap == 9) || (oldgap == 10)) oldgap = 11;
	if (oldgap) return oldgap;
	else return 1;
}

void comb(int *tab, int n)
{	
	int i, j, gap, tmp;

	gap = n;
	j = 1;

	while((gap > 1) || (j))
	{
		j = 0;
		gap = newgap(gap);

		for(i = 0; i < n - gap; ++i)
			if (tab[i] > tab[i + gap])
			{
				tmp = tab[i];
				tab[i] = tab[i + gap];
				tab[i + gap] = tmp;
				j = 1;
			}
	}
}

int main()
{
	int i;
	int n = 100000000;
	int *tab = (int *)malloc(n*sizeof(int));
	srand ((int)time(NULL));
	for (i = 0; i < n; i++) tab[i] = rand() % 999;
		
	clock_t start, end;
	start = clock();
	
	comb(tab, n);

	end = clock();
	printf ("%f s\n",
		(double)( end - start ) / (double)CLOCKS_PER_SEC);
	getchar();
}