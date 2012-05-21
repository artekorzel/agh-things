#include<iostream>
#include<cstdio>

using namespace std;

bool sprawdz(int ** tab)//sprawdza czy tablica spelnia warunki zadania i zwraca wartosc logiczna
{
	int * pom = new int[9], * pom2 = new int[9];//tablice pomocnicze ze zliczonymi wystapieniami w danym wierszu, kolumnie lub podkwadracie
	int i, j, k, licznik1, licznik2;

	for(i = 0; i < 9; ++i)//zlicza wystapienia liczb i sprawdza czy nie jest ich za duzo w danej czesci tablicy
	{
		for(k = 0; k < 9; ++k)
			pom[k] = 0;
		for(k = 0; k < 9; ++k)
			pom2[k] = 0;
		licznik1 = 0, licznik2 = 0;
		for(j = 0; j < 9; ++j)
		{
			if(++pom[tab[i][j]-1] > 2 || ++pom2[tab[j][i]-1] > 2)//czy za duzo
				return false;
			else 
			{
				if(pom[tab[i][j]-1] == 2)//zliczanie podwojen liczb
					++licznik1;
				if(pom2[tab[j][i]-1] == 2)
					++licznik2;
			}
		}
		if(licznik1 > 1 || licznik2 > 1)//sprawdzenie podwojen
			return false; 
	}
	
	for(i = 0; i < 9; i += 3)//zlicza wystapienia liczb i sprawdza czy nie jest ich za duzo w danym kwadracie
	{
		for(j = 0; j < 9; j += 3)
		{
			for(k = 0; k < 9; ++k)
				pom[k] = 0;
			licznik1 = 0;
			for(k = 0; k < 9; ++k)
			{
				if(++pom[tab[i + k/3][j + k % 3]-1] > 2)
					return false;
				else if(pom[tab[i + k/3][j + k % 3]-1] == 2)//zliczanie podwojen liczb
					++licznik1;
			}
			if(licznik1 > 1)//sprawdzenie podwojen
				return false;
		}
	}
	delete [] pom;
	delete [] pom2;
	return true;
}

void wypelnij(int **tab, int **zera, bool &wynik, int i, int ile_zer, bool &czy_ok)//wypelnia tablice w podany sposob, jesli to mozliwe
{
	if(czy_ok)//czy_ok - mowi czy znaleziono lub czy niemozliwe jest juz znalezienie rozwiazania
		if(i < ile_zer)//czy aktualnie badany element zerowy istnieje
		{
			int *pom1 = new int[9], *pom2 = new int[9], *pom3 = new int[9];
			int k, licznik1 = 0, licznik2 = 0, licznik3 = 0;
			for(k = 0; k < 9; k++)
			{
				pom1[k] = 0;
				pom2[k] = 0;
				pom3[k] = 0;
			}

			for(k = 0; k < 9; ++k)//sprawdzanie wystapien pozostalych cyfr w jednym wymiarze i ewentualne przerwanie dzialania
				if(tab[zera[i][0]][k] != 0)//ignoruje zera
					if(++pom1[tab[zera[i][0]][k]-1] > 2)
					{
						wynik = false;
						czy_ok = false;
						delete [] pom1;
						delete [] pom2;
						delete [] pom3;
						return;
					}
					else if(pom1[tab[zera[i][0]][k]-1] == 2)
						++licznik1;
			if(licznik1 > 1)
			{
				wynik = false;
				czy_ok = false;
				delete [] pom1;
				delete [] pom2;
				delete [] pom3;
				return;
			}
			for(k = 0; k < 9; ++k)//sprawdzanie wystapien pozostalych cyfr w drugim wymiarze i ewentualne przerwanie dzialania
				if(tab[k][zera[i][1]] != 0)
					if(++pom2[tab[k][zera[i][1]]-1] > 2)
					{
						wynik = false;
						czy_ok = false;
						delete [] pom1;
						delete [] pom2;
						delete [] pom3;
						return;
					}
					else if(pom2[tab[k][zera[i][1]]-1] == 2)
						++licznik2;
			if(licznik2 > 1)
			{
				wynik = false;
				czy_ok = false;
				delete [] pom1;
				delete [] pom2;
				delete [] pom3;
				return;
			}

			int pion = (zera[i][0] / 3) * 3; //zmienne pomocnicze do analizy zawartosci podkwadratu z dana komorka do zapelnienia
			int poz = (zera[i][1] / 3) * 3;
			for(k = 0; k < 9; ++k)//sprawdzenie zawartosci tego podkwadratu i odpowiednie przerwania w razie czego
				if(tab[pion + k / 3][poz + k % 3] != 0)
					if(++pom3[tab[pion + k / 3][poz + k % 3]-1] > 2)
					{
						wynik = false;
						czy_ok = false;
						delete [] pom1;
						delete [] pom2;
						delete [] pom3;
						return;
					}
					else if(pom3[tab[pion + k / 3][poz + k % 3]-1] == 2)
							++licznik3;
			if(licznik3 > 1)
			{
				wynik = false;
				czy_ok = false;
				delete [] pom1;
				delete [] pom2;
				delete [] pom3;
				return;
			}
			k = 0;
			while(k < 9)//proby wstawiania jesli mozliwe
			{
				if((pom1[k] == 0 || (licznik1 == 0 && pom1[k] == 1)) && (pom2[k] == 0 
						|| (licznik2 == 0 && pom2[k] == 1)) && (pom3[k] == 0 || (licznik3 == 0 && pom3[k] == 1)))
				{			//sprawdzanie warunkow dla danej cyfry czy moze byc wstawiona nie zaburzajac warunkow zadania
					tab[zera[i][0]][zera[i][1]] = k + 1;//wstawienie
					wypelnij(tab, zera, wynik, i + 1, ile_zer, czy_ok);//wywolanie rekurencyjne dla kolejnych elementow zerowych
					if(wynik)//jesli znaleziono wynik to pozwala cofnac rekurencje
					{
						czy_ok = false;
						delete [] pom1;
						delete [] pom2;
						delete [] pom3;
						return;
					}
				}
				++k;
			}
		}
		else
		{//gdy dojdzie do osatniego wywolania to znaczy ze jest rozwiazanie
			czy_ok = false;
			wynik = true;
		}
}	

int main(int argc, char* argv[])
{
	if(argc != 2)//sprawdzenie argumentow
	{
		cout << "Zle argumenty! Program zostanie zamkniety";
		return 1;
	}
	
	FILE *plik;
	plik = fopen(argv[1], "r");

	if(!plik)//czy dobry plik
	{
		cout << "Zly plik! Program zostanie zamkniety";
		return 2;
	}

	int **tab;
	tab = new int* [9];
	for(int i = 0; i < 9; ++i)
		tab[i] = new int[9];

	bool bez_bledu = true;//czy prawidlowo bedzie pobrany dany znak
	int i = 0, j, ile_zer = 0;
	while(plik && bez_bledu && i < 9)
	{
		j = 0;
		while(plik && bez_bledu && j < 9)
		{
			tab[i][j] = getc(plik) - 48;
			if((j < 8 && getc(plik) != ' ') || (j == 8 && getc(plik) != '\n'))//sprawdzanie czy prawidlowo spacje i koniec linii
				bez_bledu = false;
			if(tab[i][j] < 0 || tab[i][j] > 9)//sprawdzanie czy odpowiednie cyfry
				bez_bledu = false;
			if(tab[i][j] == 0)//zliczanie zer
				++ile_zer; 
			++j;
		}
		++i;
	}

	if(i < 9 || j < 9)//jesli koniec pliku wczesniej to blad
		bez_bledu = false;

	fclose(plik);
	
	if (!bez_bledu)
	{
		cout << "BLAD";
		return 3;
	}
	
	if(ile_zer == 0)//jesli bez zer to sprawdzam po prostu czy odpowiednia zawartosc tablicy
	{
		if(sprawdz(tab))
			cout << "TAK";
		else cout << "NIE";
	}		
	else
	{
		bool wynik = false;
		bool czy_ok = true;
		int **zera = new int* [ile_zer];//tablica ze wspolczednymi komorek z zerami
		for(i = 0; i < ile_zer; ++i)
			zera[i] = new int[2];
		int k = 0;
		for(i = 0; i < 9; ++i) //wypelnienie tablicy zera wspolrzednymi
			for(j = 0; j < 9; ++j)
				if(tab[i][j] == 0)
				{
					zera[k][0] = i;
					zera[k][1] = j;
					++k;
				}		
		wypelnij(tab, zera, wynik, 0, ile_zer, czy_ok);//zastapienie zer cyframi zgodnie z warunkami zadania

		if(wynik && sprawdz(tab))//jesli otrzymano wynik i reszta tablicy byla ok, to wypis rozw, inaczej nie
		{
			cout << "MOZE" << endl;
			for(i = 0; i < 9; ++i)
			{
				for(j = 0; j < 9; ++j)
					cout << tab[i][j] << "  ";
				cout << endl;
			}
		}
		else cout << "NIE";	

		for(i = 0; i < ile_zer; ++i) //zwalnianie pamieci i zakonczenie
			delete [] zera[i];
		delete [] zera;			
	}	
	
	for(i = 0; i < 9; ++i)
		delete [] tab[i];
	delete [] tab;

	return 0;
}