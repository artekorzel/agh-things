#include<iostream>

int main()
{
	int i, j, k, n = 6;
	int **tab = new int * [n];
	for(i = 0; i < n; ++i)
	{
		tab[i] = new int [n];
		tab[i][i] = 0;
	}

	int * mac = new int [n+1];
	for(i = 0; i < n + 1; ++i)
		std::cin >> mac[i];

	for(i = 1; i < n; ++i)
	{
		for(j = i-1; j >= 0; --j)
		{
			int min = 9999999, akt = 0;
			for(k = j; k < i; ++k)
			{
				akt = tab[j][k] + tab[k+1][i] + mac[j] * mac[k+1] * mac[i+1];
				if(akt < min) min = akt;
			}
			tab[j][i] = min;
		}
	}
	std::cout << tab[0][n-1];
	getchar();
	getchar();
	return 0;
}
