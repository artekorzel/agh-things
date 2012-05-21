#include<iostream>

int main()
{
	int n = 6, i, j, k;

	int * liczby = new int [n];
	for(i = 0; i < n; ++i)
		std::cin >> liczby[i];

	int ** sumy = new int * [n];
	for(i = 0; i < n; ++i)
	{
		sumy[i] = new int [n];
		sumy[i][i] = liczby[i];
	}

	for(j = 0; j < n - 1; ++j)
		for(i = j + 1; i < n; ++i)		
			sumy[i][j] = sumy[i-1][j] + liczby[i];

	int ** tab = new int * [n];
	for(i = 0; i < n; ++i)
	{
		tab[i] = new int [n];
		tab[i][i] = 0;
	}

	for(i = n-2; i >=0; --i)
	{
		for(j = i+1; j < n; ++j)
		{			//ogolniej min = MAXINT
			int min = 1000000, akt = 0;
			for(k = i; k < j; ++k)
			{
				akt = tab[i][k] + tab[k+1][j];
				if(akt < min) min = akt;
			}
			tab[i][j] = min + sumy[j][i];
		}
	}
	std::cout << tab[0][n-1];
	getchar();
	getchar();
	return 0;
}

