struct element {
	int key;
	char value;
};

int main()
{
	int i;
	int j = 1;
	int a;
	int n = 10;
	struct element tab[n];
	for (i = 0; i < n; i = i + 2)
	{
		struct element tmp;
		tmp.key = i;
		tmp.value = 97 + i;
		tab[i] = tmp;

		struct element tmp2;
		tmp2.key = i + 3;
		tmp2.value = 110 + 2 * i;
		tab[i + 1] = tmp2;
	}

	for (i = 0; i < n; ++i)
	{
		printf(tab[i].key);
		printf(":");
		printf(tab[i].value);
		printf(" ");
	}
	printf("\n");

	while (j != 0)
	{
		j = 0;
		i = 1;
		while(i < n)
		{
			a = i-1;
			if (tab[i].key < tab[a].key)
			{
				struct element tmp = tab[i];
				tab[i] = tab[a];
				tab[a] = tmp;
				j = 1;
			}
			++i;
		}
	}

	for (i = 0; i < n; ++i)
	{
		printf(tab[i].key);
		printf(":");
		printf(tab[i].value);
		printf(" ");
	}
	printf("\n");
}
