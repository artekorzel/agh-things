#include<stdio.h>
#include<iostream>
#include<conio.h>
#include<ctime>

int main()
{
	int i, j, klucz, tmp;
	const int n = 100;
	int tab[n];
	srand (static_cast<int>(time(NULL)));
	for (i = 0; i < n; i++) tab[i] = rand() % 100; //scanf("%d", &tab[i]);

	for (i = 0; i < n; i++)
	{
		klucz = i;
		j = i+1;
		while (j < n)
		{
			if (tab[klucz] > tab[j]) klucz = j;
			++j;
		}
		tmp = tab[i];
		tab[i] = tab[klucz];
		tab[klucz] = tmp;
	}

	for (i = 0; i < n; i++) printf("%d ", tab[i]);
	getch();
}