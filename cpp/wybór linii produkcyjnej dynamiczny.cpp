#include<iostream>

int main()
{
	int i, j, k, n = 6;
	int ** tab  = new int * [n];
	int ** lacz  = new int * [n];

	for(i = 0; i < n; ++i)
	{
		tab[i] = new int [n];
		tab[i][i] = 0;
	}

	std::cin >> tab[0][1];
	std::cin >> tab[0][2];
	std::cin >> tab[1][3];
	std::cin >> tab[2][3];
	std::cin >> tab[3][5];
	std::cin >> tab[4][5];
	std::cin >> tab[1][4];
	std::cin >> tab[2][4];

	for(i = 0; i < n-1; ++i)
		lacz[i] = new int [2];

	for(i = 0; i < n-1; ++i)
		for(j = 0; j < 2; ++j)
			std::cin >> lacz[i][j];

	for(i = 3; i < n; ++i)
	{
		int a = tab[0][lacz[n-i-1][0]] + tab[lacz[n-i-1][0]][i];
		int b = tab[0][lacz[n-i-1][1]] + tab[lacz[n-i-1][1]][i];
		tab[0][i] = a < b ? a : b;
	}

	std::cout << tab[0][n-1];

	getchar();
	getchar();
	return 0;
}

