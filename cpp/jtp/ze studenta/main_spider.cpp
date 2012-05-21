#include <iostream>
#include <string>
#include <cstdio>
#include "spider.h"
#include "doc_svg.h"
using namespace std;



int main()
{//spider(Xpose, Ypose, webDensity, spiderSize)
spider s(-50, -40, 5, 1);
//doc_svg(wnetrze pliku svg, nazwa pliku
doc_svg d(s.get_code(), "spider.svg");
d.make_file();
}
