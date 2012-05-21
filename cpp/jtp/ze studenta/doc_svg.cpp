
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

doc_svg:: doc_svg(string a, string b)
{
    inside= a;
    name= b;
    end="</svg>";
    headline="<?xml version='1.0' standalone='no'?> <!DOCTYPE svg PUBLIC '-//W3C//DTD SVG 1.1//EN' 'http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd'> <svg width='100%' height='100%' version='1.1' xmlns='http://www.w3.org/2000/svg'> ";

}

void doc_svg:: make_file()
{
    ofstream osrodek;                                                              //tworzenie pliku
    osrodek.open("spider.svg");
    osrodek<< headline+ inside+ end;
    osrodek.close();
}
