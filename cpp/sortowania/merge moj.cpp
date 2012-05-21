#include<stdio.h>
#include<time.h>
#include<stdlib.h>

const int n = 100000;
int tab[n];

void scal(int l1, int r1, int r2)
{
	int szer = r2 - l1 + 1;
	int l2 = r1 + 1;
	int * tab2;
	tab2 = (int *)malloc(szer * sizeof(int));

	int i = 0, k = l1;
	while((l1 <= r1) && (l2 <= r2))
	{
		if(tab[l2] < tab[l1])
		{
			tab2[i] = tab[l2];
			++l2;
		}
		else
		{
			tab2[i] = tab[l1];
			++l1;
		}
		++i;
	}
	if(l1 > r1) for(i; i < szer; ++i)
	{
		tab2[i] = tab[l2];
		++l2;
	}
	else for(i; i < szer; ++i)
	{
		tab2[i] = tab[l1];
		++l1;
	}

	for(i = 0; i < szer; ++i)
		tab[k + i] = tab2[i];

	free(tab2);
}

void merge(int p, int k)
{
	if (p < k)
	{
		int s = (p + k)/2;
		merge(p, s);
		merge(s+1, k);
		scal(p, s, k);
	}
}

int main()
{
	srand((int)time(NULL));
	int i;
	for(i = 0; i < n; ++i) tab[i] = rand() % 100000;

	merge(0, n-1);

	for(i = 0; i < n; ++i) printf("%d ", tab[i]);
	getchar();
}