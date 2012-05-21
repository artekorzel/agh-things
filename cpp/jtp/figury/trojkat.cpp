#include<iostream>
#include<cmath>
#include"trojkat.h"

figury::trojkat::trojkat(float a, float b, float c, float d, float e, float f, std::string et, float g, float h)
{
	p1.setX(a);
	p1.setY(b);
	p2.setX(c);
	p2.setY(d);
	p3.setX(e);
	p3.setY(f);
	this->setEtykieta(et);
	srodek.setX(g);
	srodek.setY(h);
}

float figury::trojkat::pole()
{
	float a, b , c, d, e, f;
	a = p1.getX();
	b = p1.getY();
	c = p2.getX();
	d = p2.getY();
	e = p3.getX();
	f = p3.getY();
	float p = 0.5 * (c*f + a*d + b*e - d*e - b*c - a*f);
	if(p < 0) p = -p;
	return p;
}

bool figury::trojkat::zapisz(std::ostream & os)
{
	(this->srodek).zapisz(os);
	(this->p1).zapisz(os);
	(this->p2).zapisz(os);
	(this->p3).zapisz(os);
	os << this->etykieta << std::endl;
	return os.good();
}

bool figury::trojkat::wczytaj(std::istream & is)
{
	(this->srodek).wczytaj(is);
	(this->p1).wczytaj(is);
	(this->p2).wczytaj(is);
	(this->p3).wczytaj(is);
	is >> std::ws;
	std::getline(is, this->etykieta);
	return is.good();
}