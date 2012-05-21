#ifndef _PIERSCIEN__H_
#define _PIERSCIEN__H_

#include<iostream>
#include<string>
#include"figura.h"
#include"kolo.h"

namespace figury
{
/** Klasa pierscien dziedziczaca z klasy kolo zawiera nastepujace elementy:
* - skladowa @b promien_wewn typu float
* - odziedziczona skladowa @b promien typu float
* - odziedziczona skladowa @b srodek typu punkt
* - odziedziczona stala typu float @b PI = 3.14
* - odpowiednie metody
*/
	class pierscien: public kolo
	{
	protected:
/** skladowa chroniona dostepna w ramach dziedziczenia
*/
		float promien_wewn;

	public:
/** Konstruktor domyslny
* @param prom wartosc float skladowej @b promien
* @param prom2 wartosc float skladowej @b promien_wewn
* @param et wartosc std::string skladowej @b etykieta
* @param a pierwsza wspolrzedna typu float skladowej @b srodek
* @param b druga wspolrzedna typu float skladowej @b srodek
*/
		pierscien(float prom = 2.0, float prom2 = 1.0, std::string et = "pierscien", float a = 0.0, float b = 0.0);

/** Destruktor domyslny
*/
		~pierscien() {}

/** @return wartosc float pola powierzchni wyliczona z odpowiedniego wzoru
*/
		float pole();

/** @param os strumien wyjsciowy z biblioteki std::ostream,
* wypisuje do niego wartosci skladowych elementu klasy w nastepujacy sposob:
* - wspolrzedne skladowej @b srodek [znak nowej linii]
* - wartosc skladowej @b promien [znak nowej linii]
* - wartosc skladowej @b promien_wewn [znak nowej linii]
* - zawartosc skladowej @b etykieta.
*
* @return typ bool mowiacy o stanie w jakim zostal pozostawiony strumien.
*/
		bool zapisz(std::ostream & os);

/** @param is strumien wejsciowy z biblioteki std::istream,
* wczytuje z niego wartosci skladowych do elementu klasy w kolejnosci:
* - wspolrzedne skladowej @b srodek
* - wartosc skladowej @b promien
* - wartosc skladowej @b promien_wewn
* - wartosc skladowej @b etykieta.
* Dane zostana pobrane ze strumienia prawidlowo takze w przypadku wczytywania ze strumienia,
* do ktorego wypisane zostaly za pomoca metody @b zapisz. 
*
* @return typ bool mowiacy o stanie w jakim zostal pozostawiony strumien.
*/
		bool wczytaj(std::istream & is);

		void promienie(float, float);
	};

}
#endif
