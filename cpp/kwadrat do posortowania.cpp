#include<iostream>
#include<cstdlib>
#include<ctime>
#include<iomanip>

const int MAXINT = 100;

void swap(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;	
}

void sort(int **tab, int n, int & m, bool plus, bool czyi)
{
	int i, j, akti, aktj, min, mini, minj;
	akti = aktj = (n - 1) / 2;
	int licz2 = 0;

	int kont1 = 0, kont2;

	while(kont1 < (n - 2) * (n - 2))
	{
		int k = m;
		i = akti, j = aktj;
		int licz = licz2;
		kont2 = 0;
		bool plus2 = plus, czyi2 = czyi;
		min = MAXINT;
		
		while(kont2 < n * n - kont1)
		{
			if(tab[i][j] < min)
			{
				min = tab[i][j];
				mini = i;
				minj = j;
			}
			if(plus2)
			{
				if(czyi2) ++i;
				else ++j;
				++licz;
			}
			else
			{
				if(czyi2) --i;
				else --j;
				++licz;
			}
			if(licz % k == 0)
			{
				czyi2 = !czyi2;
				if(licz == 2*k)
				{
					plus2 = !plus2;
					++k;
					licz = 0;
				}
			}
			++kont2;
		}

		swap(tab[mini][minj], tab[akti][aktj]);

		if(plus)
		{
			if(czyi) ++akti;
			else ++aktj;
		}
		else
		{
			if(czyi) --akti;
			else --aktj;
		}
		++licz2;
		if(licz2 % m == 0)
		{
			czyi = !czyi;
			if(licz2 == 2*m)
			{
				plus = !plus;
				++m;
				licz2 = 0;
			}
		}

		++kont1;
	}
}

int main()
{
	const int n = 10;
	srand((int)time(0));
	int ** tab = new int * [n];
	for(int i = 0; i < n; ++i) tab[i] = new int [n];
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			tab[i][j] = rand() % 50;
	int m = 1;
	//int tab [n][n] = {4, 13, 5, 11, 2, 8, 12, 1, 7, 16, 9, 18, 14, 3, 15, 6};

	sort(tab, n, m, true, false);

	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < n; ++j)
			std::cout << std::setw(4) << tab[i][j] << " ";
		std::cout << std::endl;
	}
	getchar();
	return 0;
}