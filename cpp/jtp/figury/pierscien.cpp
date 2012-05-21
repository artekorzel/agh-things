#include<iostream>
#include<cmath>
#include"pierscien.h"

figury::pierscien::pierscien(float prom, float prom2, std::string et, float a, float b)
{
	this->promien = prom;
	this->promien_wewn = prom2;
	this->setEtykieta(et);
	srodek.setX(a);
	srodek.setY(b);
}

float figury::pierscien::pole()
{
	return PI*(this->promien - this->promien_wewn)*(this->promien + this->promien_wewn);
}

bool figury::pierscien::zapisz(std::ostream & os)
{
	(this->srodek).zapisz(os);
	os << this->promien << std::endl;
	os << this->promien_wewn << std::endl;
	os << this->etykieta << std::endl;
	return os.good();
}

bool figury::pierscien::wczytaj(std::istream & is)
{
	(this->srodek).wczytaj(is);
	is >> this->promien;
	is >> this->promien_wewn;
	is >> std::ws;
	std::getline(is, this->etykieta);
	return is.good();
}