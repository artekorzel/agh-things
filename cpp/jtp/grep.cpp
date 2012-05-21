#include<iostream>
#include<string>
#include<cctype>
#include<fstream>
#include<cstring>

using namespace std;

string male(string s)//zamienia litery w stringu s na male i zwraca go
{
	unsigned int i;
	for(i = 0; i < s.length(); ++i)
		s[i] = tolower(s[i]);
	return s;
}

int main(int argc, char *argv[]) //bez opcji z jednym plikiem
{
	if(argc < 3)//sprawdza czy nie za malo argumentow
	{
		cout << "Za malo argumentow, program zostanie zamkniety";
		return 1;
	}

	int i = 1; // ew opcje, wzorzec i dalej pliki
	bool i_opcja = false;
	bool n_opcja = false;

	while((argv[i][0] == '-') && (argv[i][2] == '\0'))//sprawdza czy wybrano opcje dodatkowe
	{
		if(argv[i][1] == 'i')
			i_opcja = true;
		else if(argv[i][1] == 'n')
			n_opcja = true;
		++i;
	}

	int arg_wzorzec = i;
	++i;

	if(i_opcja && n_opcja)//jesli -i oraz -n 
	{
		string tmp(argv[arg_wzorzec]); 
		tmp = male(tmp); //zmienia wzorzec na zapisany malymi literami
		strcpy(argv[arg_wzorzec], tmp.c_str());//zamienia wzorzec na zapisany malymi literami
	
		while(i < argc)//dopoki sa pliki do sprawdzenia to szuka
		{
			ifstream plik;
			plik.open(argv[i]);
	
			if(plik.fail())//jesli blad otwierania pliku to go pomija
			{
				cout << "Blad otwierania pliku " << argv[i] << ", zostanie on pominiety" << endl;
				plik.clear();//usuwa flage bledu
				++i;
				continue;//rozpoczyna nowy przebieg petli z pominieciem blednego pliku
			}

			string linia, linia2;
			int n = 0;

			while(!plik.eof())
			{
				getline(plik, linia);//pobierz linie
				++n;
				linia2 = male(linia);

				if(linia2.find(argv[arg_wzorzec]) != -1)//jesli znajdzie w kopii to wypisz ale w wersji oryginalnej
					cout << argv[i] << ": " << n << ": " << linia << endl;
			}
			++i;
			plik.close();
		}	
	}
	else if(i_opcja)
	{
		string tmp(argv[arg_wzorzec]); 
		tmp = male(tmp); //zmienia wzorzec na zapisany malymi literami
		strcpy(argv[arg_wzorzec], tmp.c_str());//zamienia wzorzec na zapisany malymi literami

		while(i < argc)//dopoki sa pliki do sprawdzenia to szuka
		{
			ifstream plik;
			plik.open(argv[i]);

			if(plik.fail())//jesli blad otwierania pliku to go pomija
			{
				cout << "Blad otwierania pliku " << argv[i] << ", zostanie on pominiety" << endl;
				plik.clear();//usuwa flage bledu
				++i;
				continue;//rozpoczyna nowy przebieg petli
			}

			string linia, linia2;

			while(!plik.eof())
			{
				getline(plik, linia);//pobierz linie
				linia2 = male(linia);

				if(linia2.find(argv[arg_wzorzec]) != -1)//jesli znajdzie w kopii to wypisz ale w wersji oryginalnej
					cout << argv[i] << ": " << linia << endl;
			}
			++i;
			plik.close();
		}
	}
	else if(n_opcja)
	{
		while(i < argc)//dopoki sa pliki do sprawdzenia to szuka
		{
			ifstream plik;
			plik.open(argv[i]);

			if(plik.fail())//jesli blad otwierania pliku to go pomija
			{
				cout << "Blad otwierania pliku " << argv[i] << ", zostanie on pominiety" << endl;
				plik.clear();//usuwa flage bledu
				++i;
				continue;//rozpoczyna nowy przebieg petli
			}

			string linia;
			int n = 0;

			while(!plik.eof())
			{
				getline(plik, linia);//pobierz linie
				++n;

				if(linia.find(argv[arg_wzorzec]) != -1)//jesli znajdzie w kopii to wypisz
					cout << argv[i] << ": " << n << ": " << linia << endl;
			}
			++i;
			plik.close();
		}
	}
	else
	{
		while(i < argc)//dopoki sa pliki do sprawdzenia to szuka
		{
			ifstream plik;
			plik.open(argv[i]);

			if(plik.fail())//jesli blad otwierania pliku to go pomija
			{
				cout << "Blad otwierania pliku " << argv[i] << ", zostanie on pominiety" << endl;
				plik.clear();//usuwa flage bledu
				++i;
				continue;//rozpoczyna nowy przebieg petli
			}

			string linia;

			while(!plik.eof())
			{
				getline(plik, linia);

				if(linia.find(argv[arg_wzorzec]) != -1)//jesli znajdzie w kopii to wypisz
					cout << argv[i] << ": " << linia << endl;
			}
			++i;
			plik.close();
		}
	}

	return 0;
}