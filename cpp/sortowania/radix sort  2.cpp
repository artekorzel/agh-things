#include<iostream>
#include<cstdlib>
#include<ctime>

void sort(int * tab, int * tab2, int n, int m)
{
	int t[2];
	t[0] = t[1] = 0;

	for(int i = 0; i < n; ++i)
		++(t[(tab[i] & m) > 0]);

	t[1] += t[0];

	for(int i = n - 1; i >= 0; --i)
		tab2[t[(tab[i] & m) > 0]--] = tab[i];
}

void radix(int *tab, int *tab2, int n, int k)
{
	int m = 1;
	while(m < k)
	{
		sort(tab, tab2, n, m);
		m <<= 1;
		sort(tab2, tab, n, m);
		m <<= 1;
	}
}

int main()
{
	int n = 1000000;
	int k = 1000;
	int i;
	int * tab = new int [n];
	int * tab2 = new int [n];
	srand((int)time(NULL));

	for(i = 0; i < n; ++i) tab[i] = rand() % k;

	clock_t start, end;
	start = clock();
	
	radix(tab, tab2, n, k);
	
	end = clock();
	printf ("%f s\n",
		(double)( end - start ) / (double)CLOCKS_PER_SEC);	
	//delete [] tab;
	//delete [] tab2;
}
