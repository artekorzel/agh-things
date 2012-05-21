#ifndef _PUNKT__H_
#define _PUNKT__H_

#include<iostream>

namespace figury
{
/** @par Punkt
* Klasa punkt zawiera dwa elementy typu float bedace kolejnymi 
* wspolrzednymi oraz metody ulatwiajace prace na jej przedstawicielach.
*/

	class punkt
	{
/** Skladowa @b x jest skladowa prywatna, wiec jej zmiana na
* zewnatrz klasy moze nastapic tylko za pomoca odpowiedniej metody.
*/
		float x;

/** Skladowa @b y jest skladowa prywatna, wiec jej zmiana na
* zewnatrz klasy moze nastapic tylko za pomoca odpowiedniej metody.
*/
		float y;

	public:
/** Konstruktor punkt jest konstruktorem domyslnym.
* @param nx argument domyslny typu float, ktorego wartosc ma przyjac nowo tworzony element klasy w skladowej x
* @param ny argument domyslny typu float, ktorego wartosc ma przyjac nowo tworzony element klasy w skladowej y
*/
		punkt(float nx = 0.0, float ny = 0.0): x(nx), y(ny) {}

/** @param nx wartosc typu float, na ktora metoda zmienia aktualna wartosc skladowej x
*/
		void setX(float nx) {x = nx;}

/** @return wartosc typu float rowna wartosci skladowej @b x
*/
		float getX() {return x;}

/** @param ny wartosc typu float, na ktora metoda zmienia aktualna wartosc skladowej y
*/
		void setY(float ny) {y = ny;}

/** @return wartosc typu float rowna wartosci skladowej @b y
*/
		float getY() {return y;}

/** @param os strumien wyjsciowy z biblioteki std::ostream,
* wypisuje do niego wartosci skladowych elementu klasy w nastepujacy sposob:
* x [spacja] y [znak nowej linii]
*
* @return typ bool mowiacy o stanie w jakim zostal pozostawiony strumien.
*/
		bool zapisz(std::ostream & os);

/** @param is strumien wejsciowy z biblioteki std::istream,
* wczytuje z niego wartosci skladowych do elementu klasy w kolejnosci:
* - wartosc x
* - wartosc y.
* Dane zostana pobrane ze strumienia prawidlowo takze w przypadku wczytywania ze strumienia,
* do ktorego wypisane zostaly za pomoca metody @b zapisz. 
*
* @return typ bool mowiacy o stanie w jakim zostal pozostawiony strumien.
*/
		bool wczytaj(std::istream & is);
	};

}

#endif 