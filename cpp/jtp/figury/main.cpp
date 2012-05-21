/** @mainpage
* Zbior klas @b Figury
* @author Artur Orzel
* @date 2011-06-11
* @version 1.0
* 
* Zbior ten zawiera klasy:
*	- punkt
*	- figura - klasa czysto wirtualna
*	- trojkat
*	- kolo
*	- pierscien
*/

#include<iostream>
#include"figura.h"
#include"kolo.h"
#include"pierscien.h"
#include"punkt.h"
#include"trojkat.h"

using namespace figury;

int main()
{
	punkt p(1.0, 2.0);
    p.zapisz(std::cout);
    std::cout << p.getX() << std::endl;
    std::cout << p.getY() << std::endl;
    p.setX(5.0);
    p.setY(3.0);
    p.zapisz(std::cout);
    p.wczytaj(std::cin);
    p.zapisz(std::cout);

	trojkat t(2, 4, 3, 5, 1, 6, "troj");
	t.zapisz(std::cout);
	t.wczytaj(std::cin);
	t.zapisz(std::cout);
	std::cout << t.pole() << std::endl;

	kolo k(3.0, "kolko");
	k.zapisz(std::cout);
	k.wczytaj(std::cin);
	k.zapisz(std::cout);
	std::cout << k.pole() << std::endl;

	pierscien p2(3.0, 1.5, "piersc");
	p2.zapisz(std::cout);
	p2.wczytaj(std::cin);
	p2.zapisz(std::cout);
	std::cout << p2.pole() << std::endl;
    return 0;
}
