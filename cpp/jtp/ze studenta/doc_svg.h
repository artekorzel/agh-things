#ifndef DOC_SVG_H_
#define DOC_SVG_H_
//******
//plik doc_svg.h
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>


using namespace std;


class doc_svg
{

    string end;             //stopka
    string headline;        //naglowek
    string inside;          //wnetrze, istotna czesc kodu
    string name;            //nazwa pliku

public:
doc_svg(string a, string b);

void make_file();

/***********************************************METODY**************************************************************/


};

#endif
#include "doc_svg.cpp"
