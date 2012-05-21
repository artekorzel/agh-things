#include<stdio.h>
#include<iostream>
#include<conio.h>
#include<ctime>

int podziel(int *t, int a, int b)
{
	int x = t[a], tmp;
	a--;
	b++;
	while(1)
	{
		do a++; while (t[a] < x);
		do b--; while (t[b] > x);
		if (a < b)
		{
			tmp = t[a];
			t[a] = t[b];
			t[b] = tmp;
		}
		else return b;
	}
}

void quicksort(int *t, int a, int b)
{
	int dzielnik;
	if (a < b)
	{
		dzielnik = podziel(t, a, b);
		quicksort(t, a, dzielnik);
		quicksort(t, dzielnik + 1, b);
	}
}

int main()
{	
	const int n = 200000;
	int l = 0, p = n-1, s, klucz, i;
	int tab[n];
	srand (static_cast<int>(time(NULL)));
	for (i = 0; i < n; i++) tab[i] = rand() % 1000000; 

	scanf("%d", &klucz);
	
	quicksort(tab, l, p);

	while (l <= p)
	{
		s = (p + l) / 2;
		if (tab[s] == klucz) l = p + n;
		else if (tab[s] > klucz) p = s - 1;
		else l = s + 1;
	}
	if (l == p + n) printf("\nindeks: %d", s);
	else printf("\nnie znaleziono");
	getch();
}