#include<iostream>

using namespace std;

bool sumy(int **tab, int n, int suma)
{
	int i = 0, j, s1, s2;
	while(i < n)
	{
		j = 0;
		s1 = 0;
		while(j < n)
			s1 += tab[i][j++];
		if(s1 != suma) return false;
		++i;
	}

	s1 = 0; s2 = 0;
	for(i = 0; i < n; ++i)
	{
		s1 += tab[i][i];
		s2 += tab[i][n-i-1];
	}
	if(s1 != suma || s2 != suma) return false;
	return true;
}

void wpisz(int **tab, int n, int suma, bool *bools, int n_kw, int i, int j, int wpisano, bool &koniec)
{
  if(!koniec)
	if(wpisano == n_kw)
	{
		if(sumy(tab, n, suma)) koniec = true;
	}
	else
	{
		int k = 0;
		while(k < n_kw && !koniec)
		{
			while(bools[k] && k < n_kw) ++k;
			if(k < n_kw)
			{
				tab[i][j] = k + 1;
				bools[k] = true;
				if(i < n-1)
					wpisz(tab, n, suma, bools, n_kw, i + 1, j, wpisano + 1, koniec);
				else
				{
					int c, s = 0;
					for(c = 0; c < n; ++c)
						s += tab[c][j];
					if(s == suma) wpisz(tab, n, suma, bools, n_kw, 0, j + 1, wpisano + 1, koniec);
				}
				bools[k] = false;
			}
			++k;
		}
	}
}

int main()
{
	int n = 6;
	int **tab = new int*[n];
	int i, j;
	for(i = 0; i < n; ++i)
		tab[i] = new int[n];
	for(i = 0; i < n; ++i)
		for(j = 0; j < n; ++j)
			tab[i][j] = 0;
	int n_kw = n*n;
	int suma = (n_kw+1)*n/2;
	bool *bools = new bool[n_kw];
	for(i = 0; i < n_kw; ++i) bools[i] = false;
	bool koniec = false;
	wpisz(tab, n, suma, bools, n_kw, 0, 0, 0, koniec);
	if(koniec)
		for(i = 0; i < n; ++i)
		{
			for(j = 0; j < n; ++j)
				cout << tab[i][j] << " ";
			cout << endl;
		}
	else cout << "brak";
	getchar();
}