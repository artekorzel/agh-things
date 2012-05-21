#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

void counting(int * tab, int n, int j)
{
	int i, pom[10], *wyn;
	wyn = (int *)malloc(n * sizeof(int));

	for(i = 0; i < 10; ++i) pom[i] = 0;

	int dzieln = (int)pow((double)10, j);

	for(i = 0; i < n; ++i)
		++pom[((tab[i]) / dzieln) % 10];

	for(i = 1; i < 10; ++i)
		pom[i] += pom[i-1];

	for(i = n - 1; i >= 0; --i)
	{
		wyn[pom[((tab[i]) / dzieln) % 10] - 1] = tab[i];
		--pom[((tab[i]) / dzieln) % 10];
	}

	for(i = 0; i < n; ++i)
		tab[i] = wyn[i];
	free(wyn);
}

void radix(int **tab, int n, int k)
{
	int j;
	for(j = 0; j < k; ++j)
		counting(*tab, n, j);
}

int main()
{
	const int n = 100000000;
	const int k = 3;
	int i, *tab, l = k;
	int zakr = (int)pow((double)10, l);
	tab = (int *)malloc(n * sizeof(int));
	srand((int)time(NULL));
	for(i = 0; i < n; ++i) tab[i] = rand() % zakr;
	clock_t start, end;
	start = clock();
	
	radix(&tab, n, k);

	end = clock();
	printf ("%f s\n",
		(double)( end - start ) / (double)CLOCKS_PER_SEC);
	
	
	free(tab);

	getchar();
}
