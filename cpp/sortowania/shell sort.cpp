#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

void shell(int *tab, int n, int gap)
{
	int i, j, x;
	
	for(i = gap; i < n; ++i)
	{
		x = tab[i];
		for(j = i - gap; j >= 0 && tab[j] > x; j -= gap)
			tab[j + gap] = tab[j];
		tab[j + gap] = x;
	}
}

void sort(int *tab, int n)
{
	int i, k = (int)(log((double)n-2)/log(3.0));
	int * gapy = (int *)malloc(k * sizeof(int));
	gapy[0] = 1;
	for(i = 1; i < k; ++i)
		gapy[i] = 3*gapy[i-1] + 1;

	for(i = k-1; i >= 0; --i)
		shell(tab, n, gapy[i]);
	free(gapy);
}

int main()
{
	int i, n = 100000000;
	int *tab = (int *)malloc(n * sizeof(int));
	srand((int)time(NULL));
	for(i = 0; i < n; ++i) tab[i] = rand() % 999;
	printf("%d\n",time(0));
	sort(tab, n);
	printf("%d",time(0));
	//for(i = 0; i < n; ++i) printf("%d ", tab[i]);
	free(tab);
	getchar();
}