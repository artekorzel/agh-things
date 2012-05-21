#include<stdio.h>
#include<time.h>
#include<stdlib.h>

void swap(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;	
}

void quicksort(int *t, int p, int k)
{
	if(p < k)
	{
		int x = t[p], i = p, j = k;
		do
		{
			while(t[i] < x) ++i;
			while(t[j] > x) --j;
			if(i <= j) swap(t[i++], t[j--]);
		}while(i < j);

		if(p < j) quicksort(t, p, j);
		if(i < k) quicksort(t, i, k);
	}
}

int main()
{		
	int n = 1000000;
	int *tab = (int *)malloc(n * sizeof(int));
	int l = 0, p = n - 1, i;
	srand ((int)time(NULL));
	for (i = 0; i < n; i++) tab[i] = rand() % 999; 
	

	clock_t start, end;
	start = clock();
	
	quicksort(tab, l, p);

	end = clock();
	printf ("%f s\n",
		(double)( end - start ) / (double)CLOCKS_PER_SEC);
	free(tab);
	getchar();
}
	