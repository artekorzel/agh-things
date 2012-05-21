#ifndef _TROJKAT__H_
#define _TROJKAT__H_

#include<iostream>
#include<string>
#include"punkt.h"
#include"figura.h"

namespace figury
{
/** Klasa @b trojkat jest klasa dziedziczaca z klasy @b funkcja.
* Jej skladnikami sa:
* - trzy skladowe chronione typu punkt: @b p1, @b p2, @b p3
* - skladowe chronione dziedziczone z klasy @b figura: @bsrodek typu punkt oraz @b etykieta typu std::string
* - metody wlasne oraz metody dziedziczone: @b setEtykieta oraz @b opis
*/
	class trojkat: public figura
	{
	protected:
		punkt p1, p2, p3;

	public:
/** Konstruktor domyslny przyjmujacy argumenty domniemane:
* - szesc liczb typu float stanowiacych kolejne wspolrzedne punktow @b p1, @b p2, @b p3
* - argument typu std::string stanowiacy etykiete figury
* - wspolrzedne srodka figury
*/
		trojkat(float = 0.0, float = 0.0, float = 0.0, float = 0.0, float = 0.0, float = 0.0, std::string = "trojkat", float = 0.0, float = 0.0);

/** Destruktor domyslny
*/
		~trojkat(){}

/** @return wartosc float pola powierzchni trojkata wyliczona z wyznacznika wektorow wychodzacych z jednego wierzcholka 
*/
		float pole();

/** @param os strumien wyjsciowy z biblioteki std::ostream,
* wypisuje do niego wartosci skladowych elementu klasy w nastepujacy sposob:
* - wspolrzedne skladowej @b srodek [znak nowej linii]
* - wspolrzedne skladowych @b p1, @b p2, @b p3 w kolejnych nowych liniach
* - zawartosc skladowej @b etykieta.
*
* @return typ bool mowiacy o stanie w jakim zostal pozostawiony strumien.
*/
		bool zapisz(std::ostream & os);

/** @param is strumien wejsciowy z biblioteki std::istream,
* wczytuje z niego wartosci skladowych do elementu klasy w kolejnosci:
* - wspolrzedne skladowej @b srodek
* - wspolrzedne skladowych @b p1, @b p2, @b p3
* - wartosc skladowej @b etykieta.
* Dane zostana pobrane ze strumienia prawidlowo takze w przypadku wczytywania ze strumienia,
* do ktorego wypisane zostaly za pomoca metody @b zapisz. 
*
* @return typ bool mowiacy o stanie w jakim zostal pozostawiony strumien.
*/
		bool wczytaj(std::istream & is);
	};

}

#endif