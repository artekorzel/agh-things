#ifndef SPIDER_H_
#define SPIDER_H_
//*********************
//plik: spider.h
//********************
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

/*****************************deklaracja klasy spider***********************************************/
class spider{
      //atrybuty:
        static const float middle;     //wspolrzedna x i y srodka symetrii pajeczyny
        static const float length;     //odleglosc od srodka symetrii najbardziej odleglego punktu najwiekszego szesciokata pajeczyny
        static const float webLength;  //odleglosc od srodka symetrii najbardziej odleglego punktu pajeczyny
        static int id;
        string transform_begin;
        string comma;
        string space;
        string scale;
        string transform_end;

        float Xpose;                        //wspólrzedna x pajaka(wzgledem srodka symetrii pajeczyny)
        float Ypose;                        //wspólrzedna y pajaka
        float webDensity;                   //dla naturalnych: ile szesciokatow zmiesci sie w sieci; dla reszty- zmiesci sie sufit z webDensity szeciokatow; odleglosc miedzy nimi length/webDensity
        float spiderSize;                   //skala powiekszenia pajaka wzgledem rozmiaru wzorcowego
public:
//------------------------------------konstruktor----------------------------------------/
spider(float x, float y, float d, float s);
//---------------------------------------metody-------------------------------------------/

private:

//----------------float- string--------------/
   string conversionF(float a);
//----------------int- string--------------/
    string conversionI(int a);
//--------------------------metody set---------------------/
string set_webSkeleton();
string set_webHexagons();

string set_spider();
public:
string get_code();
};

#endif
#include "spider.cpp"
