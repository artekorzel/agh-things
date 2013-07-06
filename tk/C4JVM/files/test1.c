int n = 20;

int podziel(int t[n], int a, int b)
{
	int x;
	x = t[a];
	int tmp;
	--a;
	++b;
	while(1 > 0)
	{
		++a;
		while (t[a] < x) 
		{
			++a;
		}
		--b;
		while (t[b] > x)
		{
			--b;
		}
		if (a < b)
		{
			tmp = t[a];
			t[a] = t[b];
			t[b] = tmp;
		}
		else 
			return b;
	}
	return 0;
}

void quicksort(int t[n], int a, int b);

void quicksort(int t[n], int a, int b)
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
	int i;
	int t[n];
	for(i = 0; i < n; i = i + 2)
	{	
		t[i] = i;
		t[i+1] = -i + 3;	
	}
	for(i = 0; i < n; ++i)
	{
		printf(t[i]);
		printf(" ");
	}
	printf("\n");

	quicksort(t, 0, n-1);
	
	for(i = 0; i < n; ++i)
	{
		printf(t[i]);
		printf(" ");
	}
	printf("\n");

	return 0;
}
