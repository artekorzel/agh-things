#include<iostream>
#include"punkt.h"

bool figury::punkt::zapisz(std::ostream & os)
{
    os << this->x << " " << this->y << std::endl;
    return os.good();
}

bool figury::punkt::wczytaj(std::istream & is)
{
    is >> this->x >> this->y;
    return is.good();
}
