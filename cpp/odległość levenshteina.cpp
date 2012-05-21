#include<iostream>

int main()
{
	int r1 = 4, r2 = 5;
	char * w1 = new char [r1];
	char * w2 = new char [r2];
	
	std::cin >> w1;
	std::cin >> w2;

	int ** tab = new int * [r1+1];

	int i, j, k, tmp;
	for(i = 0; i <= r1; ++i)
	{
		tab[i] = new int [r2+1];
		tab[i][0] = 0;
	}
	for(i = 0; i <= r2; ++i)
		tab[0][i] = 0;

	for(j = 1; j <= r2; ++j)
	{
		for(i = 1; i <= r1; ++i)
		{
			if(w1[i-1] == w2[i-1]) k = 0;
			else k = 1;
			if(tab[i-1][j] < tab[i][j-1]) tmp = tab[i-1][j] + 1;
			else tmp = tab[i][j-1] + 1;
			if(tmp < tab[i-1][j-1] + k) tab[i][j] = tmp;
			else tab[i][j] = tab[i-1][j-1] + k;
		}
	}

	std::cout << tab[r1][r2];
	getchar();
	getchar();
	return 0;
}