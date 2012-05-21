#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void counting(int * tab, int n)
{
	int i, pom[100], *wyn;
	wyn = (int *)malloc(n * sizeof(int));
	for(i = 0; i < 100; ++i) pom[i] = 0;

	for(i = 0; i < n; ++i)
		++pom[tab[i]];

	for(i = 1; i < 100; ++i)
		pom[i] += pom[i-1];

	for(i = n-1; i>= 0; --i)
	{
		wyn[pom[tab[i]]-1] = tab[i];
		pom[tab[i]]--;
	}

	for(i = 0; i < n; ++i)
		tab[i] = wyn[i];
}

int main()
{
	const int n = 10000000;
	int i, tab[n];
	srand((int)time(NULL));
	for(i = 0; i < n; ++i)
		tab[i] = rand() % 100;

	clock_t start, end;
	start = clock();
	
	counting(tab, n);

	end = clock();
	printf ("%f s\n",
		(double)( end - start ) / (double)CLOCKS_PER_SEC);
	for(i = 0; i < n; ++i) printf("%d ", tab[i]);
	getchar();
}

