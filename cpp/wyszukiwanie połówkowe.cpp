#include<stdio.h>
#include<conio.h>


int main()
{	
	const int n = 10;
	int l = 0, p = n-1, s, klucz, i;
	int tab[n];
	for (i = 0; i < n; i++) scanf("%d", &tab[i]);

	scanf("%d", &klucz);

	while (l <= p)
	{
		s = (p + l) / 2;
		if (tab[s] == klucz) l = p + n;
		else if (tab[s] > klucz) p = s - 1;
		else l = s + 1;
	}
	if (l == p + n) printf("znaleziono");
	else printf("nie znaleziono");
	getch();
}