int main()
{
	int i;
	int j;
	int klucz;
	int n = 10;
	int tab[n];
	for (i = 0; i < n; i = i + 2)
	{
		tab[i] = i;
		tab[i+1] = -i + 2;
	} 
		
	for (i = 0; i < n; ++i)
	{ 
		printf(tab[i]);
		printf(" ");
	}
	printf("\n");

	for (i = 1; i < n; ++i)
	{
		j = i;
		klucz = tab[j];
		while ((j > 0) && (klucz < tab[j-1]))
		{
			tab[j] = tab[j-1];
			--j;
		}
		tab[j] = klucz;
	}

	for (i = 0; i < n; ++i)
	{ 
		printf(tab[i]);
		printf(" ");
	}
	printf("\n");
}