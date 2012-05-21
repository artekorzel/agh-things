#include<stdio.h>
#include<time.h>
#include<stdlib.h>

const int n = 100;
int tab[n];

void swap(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

void merge(int, int);

void scal(int l1, int r1, int r2)
{
	if(r2 == r1 + 1)
	{
		while((r2 > l1) && (tab[r2] < tab[r2 - 1]))
	    {
			swap(tab[r2], tab[r2-1]);
			--r2;
	    }
	}
	else if(n - r2 > r2 - r1)
	{
		int l2 = r1 + 1, szer = r2 - r1;
		int i, j = r2 - l2;
		while(j >= 0)
		{
			i = 2*r2 - l2;
			while(i >= l1)
			{
				swap(tab[i], tab[i+1]);
				--i;
			}
			--j;
		}
		
		int pocz = l1;
		l1 +=szer; l2 += szer; r1 += szer; r2 += szer;

		while((l1 <= r1) && (l1 - pocz > 0))
		{
			if(tab[l1] < tab[l2])
			{
				swap(tab[pocz], tab[l1]);
				++l1;
			}
			else
			{
				swap(tab[pocz], tab[l2]);
				++l2;
			}
			++pocz;
		}
		if((l1 > r1) && (l2 <= r2))
			for(l2; l2 <= r2; ++l2, ++pocz) swap(tab[pocz], tab[l2]);
	}
}

void merge(int p, int k)
{
	if (p < k)
	{
		int s = (p + k)/2;
		merge(p, s);

		if (n - k > k - s)
		{
			merge(s+1, k);
			scal(p, s, k);
		}
		else while((n - s) > 2)
		{
			int x = (s + k)/2;
			merge(s+1, x);
			scal(p, s, x);
			s = x;
		}
	}
}

void mergesort()
{
	merge(0, n-1);
	scal(0, n-2, n-1);
}

int main()
{
	int i;
	srand((int)(time(NULL)));
	for (i = 0; i < n; ++i) tab[i] = rand() % 100;

	mergesort();

	for (i = 0; i <n; ++i) printf("%d ", tab[i]);
	getchar();
}