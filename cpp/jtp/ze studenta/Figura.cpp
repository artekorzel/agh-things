#include <iostream>
#include <cmath>
#include <string>

using namespace std;

class Figura_geometryczna
{public:
 	virtual float miara()
 	{}
 	virtual string rodzaj_miary()
 	{}

};
/************************************************************************/

class Figura_plaska: public Figura_geometryczna
{
virtual float miara()
{}
virtual string rodzaj_miary()
{}
};

/************************************************************************/

class Figura_przestrzenna: public Figura_geometryczna
{virtual float miara()
 	{}
 	virtual string rodzaj_miary()
 	{}

};

/************************************************************************/

class Elipsa: public Figura_plaska
{
 float a;
 float b;
public:
 float miara()
{return M_PI*a*b;}
 string rodzaj_miary()
 { return "Pole powierzchni elipsy";}
 Elipsa(float x=1, float y=1): a(x), b(y)
 {}

};

/************************************************************************/

class Kolo: public Elipsa
{
 float r;
public:
 float miara()
 {return M_PI*r*r;}
 string rodzaj_miary()
 {return "Pole powierzchni kola";}
 Kolo(float x=1): r(x)
 {}

};


/************************************************************************/

class Elipsoida: public Figura_przestrzenna
{	float a;
 float b;
 float c;
public:
 float miara()
 {return M_PI*a*b*c*4/3;}

 string rodzaj_miary()
 {return "Objetosc elipsoidy";}

 Elipsoida(float x=1, float y=1, float z=1): a(x), b(y), c(z)
 {}
};

/************************************************************************/

class Kula: public Elipsoida
{	float r;
public:
 float miara()
 {return M_PI*r*r*r*4/3;}

 string rodzaj_miary()
 {return "Objetosc kuli";}

 Kula(float x=1): r(x)
 {}
};
/************************************************************************/
int main()
{   int i;
    Figura_geometryczna* pojemnik_na_figury[4];

    pojemnik_na_figury[0]= new Elipsa(1, 3);
    pojemnik_na_figury[1]= new Kolo(2);
    pojemnik_na_figury[2]= new Elipsoida(2, 3, 4);
    pojemnik_na_figury[3]= new Kula(1);

    for(i=0; i<4; i++)
    {
             cout<<pojemnik_na_figury[i]->rodzaj_miary()<<"= "<<pojemnik_na_figury[i]->miara()<<endl;
             }

    getchar();
    return 0;
}
