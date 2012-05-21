#include<iostream>

using namespace std;

void wypelnij(int * tab, bool * byly, int &rozmiar, int licznik, int akti, bool &b)
{
	if(licznik == 0)
	{
		b = true;
	}
	else
	{
		int i;
		for(i = akti; i < rozmiar; ++i)
			if(tab[i] == rozmiar) break;
		akti = i;
		for(i = 0; i < rozmiar && !b; ++i)
		{
			if(!byly[i])
			{
				tab[akti] = i;
				byly[i] = true;
				wypelnij(tab, byly, rozmiar, licznik - 1, akti + 1, b);
				if(!b)
				{
					byly[i] = false;
					tab[akti] = rozmiar;
				}
			}
		}
	}
}

int main()
{
	int rozmiar, i, j;
	cin >> rozmiar;
	cin.ignore(1,'\n');
	int * tab = new int [rozmiar];

	for(i = 0; i < rozmiar; ++i)
	{
		char c;
		j = -1;
		do
		{
			cin.get(c);
			++j;
		}while((c == '.') && (j < rozmiar));
		tab[i] = j;
		if(rozmiar > j) cin.ignore(rozmiar, '\n');
	}

	int licznik = rozmiar;

	bool * byly = new bool [rozmiar];
	for(i = 0; i < rozmiar; ++i)
		byly[i] = false;

	for(i = 0; i < rozmiar; ++i)
		if(tab[i] != rozmiar)
		{
			byly[tab[i]] = true;
			--licznik;
		}

	bool b = false;
	wypelnij(tab, byly, rozmiar, licznik, 0, b);

	for(i = 0; i < rozmiar; ++i)
	{
		licznik = tab[i];
		while(licznik > 0)
		{
			cout << '.';
			--licznik;
		}
		cout << 'W';
		licznik = rozmiar - tab[i] - 1;
		while(licznik > 0)
		{
			cout << '.';
			--licznik;
		}
		cout << endl;
	}

	return 0;
}

