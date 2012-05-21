#ifndef _FIGURA__H_
#define _FIGURA__H_

#include<iostream>
#include<string>
#include"punkt.h"

namespace figury
{
/** Klasa @b figura jest klasa czysto wirtualna. Jej skladnikami sa:
* - element typu punkt o nazwie @b srodek
* - element typu std::string o nazwie @b etykieta
* - metody pracujace na tych elementach
*/
	class figura
	{
	protected:
/** Skladowa @b srodek jest skladowa chroniona, dostepna tylko dla klas potomnych.
*/
		punkt srodek;

/** Skladowa @b etykieta jest skladowa chroniona, dostepna tylko dla klas potomnych.
*/
		std::string etykieta;

	public:
/** Konstruktor i destruktor wirtualny sa pustymi metodami, bowiem ze wzgledu na wirtualnosc klasy nie mozna stworzyc obiektow typu figura.
*/
		figura() {}
		virtual ~figura() {}

/**@param et wartosc typu std::string ktora zostaje przypisana do elementu @b etykieta
*/
		void setEtykieta(std::string et);

/**@return wartosc typu std::string bedaca wartoscia elementu chronionego @b etykieta
*/
		std::string opis();

/** Metoda @b pole metoda czysto wirtuala, dzieki czemu nie mozna stworzyc obiektu typu figura.
* @return wartosc typu float
*/
		virtual float pole() = 0;

/** Metoda @b zapisz jest metoda czysto wirtuala, dzieki czemu nie mozna stworzyc obiektu typu figura.
* @return wartosc typu bool
*/
		virtual bool zapisz(std::ostream & os) = 0;

/** Metoda @b wczytaj jest metoda czysto wirtuala, dzieki czemu nie mozna stworzyc obiektu typu figura.
* @return wartosc typu bool
*/
		virtual bool wczytaj(std::istream & is) = 0;
	};

}

#endif 