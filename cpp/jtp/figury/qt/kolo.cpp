#include<iostream>
#include<cmath>
#include"kolo.h"

figury::kolo::kolo(float prom, std::string et, float a, float b): PI(3.14)
{
	this->promien = prom;
	this->setEtykieta(et);
	srodek.setX(a);
	srodek.setY(b);
}

float figury::kolo::pole()
{
	return PI*(this->promien)*(this->promien);
}

bool figury::kolo::zapisz(std::ostream & os)
{
	(this->srodek).zapisz(os);
	os << this->promien << std::endl;
	os << this->etykieta << std::endl;
	return os.good();
}

bool figury::kolo::wczytaj(std::istream & is)
{
	(this->srodek).wczytaj(is);
	is >> this->promien;
	is >> std::ws;
	std::getline(is, this->etykieta);
	return is.good();
}
