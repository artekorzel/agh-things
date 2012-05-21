#ifndef _KOLO__H_
#define _KOLO__H_

#include<iostream>
#include<string>
#include"figura.h"

namespace figury
{
/** Klasa kolo dziedziczaca z klasy figura zawiera nastepujace elementy:
* - skladowa @b promien typu float
* - odziedziczona skladowa @b srodek typu punkt
* - stala typu float @b PI = 3.14
* - odpowiednie metody
*/
	class kolo: public figura
	{
	protected:
/** Skladowa chroniona dostepna w ramach dziedziczenia
*/
		float promien;

	public:
/** Stala publiczna potrzebna do obliczania pola figury
*/
		const float PI;

/** Konstruktor domyslny
* @param prom wartosc skladowej @b promien
* @param et wartosc skladowej @b etykieta
* @param a pierwsza wspolrzedna skladowej @b srodek
* @param b druga wspolrzedna skladowej @b srodek
*/
		kolo(float prom = 2.0, std::string et = "kolo", float a = 0.0, float b = 0.0);

/** Destruktor domyslny
*/
		~kolo() {}

/** @return wartosc float pola powierzchni wyliczona z odpowiedniego wzoru
*/
		float pole();

/** @param os strumien wyjsciowy z biblioteki std::ostream,
* wypisuje do niego wartosci skladowych elementu klasy w nastepujacy sposob:
* - wspolrzedne skladowej @b srodek [znak nowej linii]
* - wartosc skladowej @b promien [znak nowej linii]
* - zawartosc skladowej @b etykieta.
*
* @return typ bool mowiacy o stanie w jakim zostal pozostawiony strumien.
*/
		bool zapisz(std::ostream & os);

/** @param is strumien wejsciowy z biblioteki std::istream,
* wczytuje z niego wartosci skladowych do elementu klasy w kolejnosci:
* - wspolrzedne skladowej @b srodek
* - wartosc skladowej @b promien
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