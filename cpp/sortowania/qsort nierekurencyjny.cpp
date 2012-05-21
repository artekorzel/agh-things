#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct el
{
	int war;
	struct el *wsk;
};

class stos
{
public:	
	struct el *Top;

	void dodaj(int);

	void usun(int &);
};

	void stos::dodaj(int x)
	{
		struct el *nowy = new struct el;
		nowy->wsk = Top;
		nowy->war = x;
		Top = nowy;
	}

	void stos::usun(int &k)
	{
		k = Top->war;
		struct el *tmp = Top;
		Top = Top->wsk;
		delete tmp;
	}

void swap(int & a, int & b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

void qsort(int *t, int l, int p)
{	
	stos moj;
	moj.Top = 0;
	
	moj.dodaj(p);
	moj.dodaj(l);

	while(moj.Top != 0)
	{
		moj.usun(l);
		moj.usun(p);

		while(l < p)
		{
			int x = t[(l+p)/2];
			int i = l, j = p;
			do
			{
				while(x > t[i]) ++i;
				while(x < t[j]) --j;
				if(i <= j)
				{
					swap(t[i], t[j]);
					++i;
					--j;
				}
			}while(i < j);
			if(l < j) { moj.dodaj(j); moj.dodaj(l); }
			//if(i < p) { moj.dodaj(p); moj.dodaj(i); } //ponad dwa razy wolniej
			l = i;
		}
	}
}


int main()
{
	const int n = 1000000;
	int *t = new int [n];
	int i;
	srand((int)(time(NULL)));
	for (i = 0; i < n; ++i) t[i] = rand() % 999;
	printf("%d ",time(0));
	qsort(t, 0, n-1);
	printf("%d ",time(0));
	//for (i = 0; i < n; ++i) printf("%d ", t[i]);
	getchar();
}