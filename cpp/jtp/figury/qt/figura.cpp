#include<iostream>
#include<string>
#include"figura.h"
#include"punkt.h"

void figury::figura::setEtykieta(std::string et)
{
    this->etykieta = et;
}

std::string figury::figura::opis()
{
    return this->etykieta;
}