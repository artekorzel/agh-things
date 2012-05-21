#include<iostream>

int fun(int ** tab, int n, int akti, bool * wolne)
{
	if(akti < n)
	{
		int j, max = 0, maxj;
		for(j = 0; j < n; ++j)
			if(wolne[j] && tab[akti][j] > max)
			{
				max = tab[akti][j];
				maxj = j;
			}
		wolne[maxj] = false;
		return max + fun(tab, n, akti + 1, wolne);
	}
	else return 0;
}

int main()
{
	int n = 5, i, j;
	int ** tab = new int * [n];
	for(i = 0; i < n; ++i)
		tab[i] = new int [n];

	for(i = 0; i < n; ++i)
		for(j = 0; j < n; ++j)
			std::cin >> tab[i][j];

	bool * wolne = new bool [n];
	for(i = 0; i < n; ++i) wolne[i] = true;
	std::cout << fun(tab, n, 0, wolne);
	getchar();
	return 0;
}
