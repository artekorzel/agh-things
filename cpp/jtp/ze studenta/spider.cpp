
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

//******************************************************************

const float spider::middle = 300;   
const float spider::length = 200;   
const float spider::webLength = 225;

spider:: spider(float x, float y, float d, float s)
        {   Xpose=x;
            Ypose= y;
            webDensity= d;
            spiderSize= s;
            transform_begin="<g transform= 'translate (";
            scale=") scale(";
            comma=",";
            space=" ";
            transform_end=")'> ";}

//----------------float- string--------------/

   string spider:: conversionF(float a)
{
    char b[9];
                sprintf(b, "%f", a);
                string s(b);
                return s;
}
//----------------int- string--------------/
    string spider:: conversionI(int a)
{
    char b[9];
                sprintf(b, "%d", a);
                string s(b);
                return s;
}
//--------------------szkielet pajeczyny----------/
string spider:: set_webSkeleton()
{

    //odcinki- osie symetrii sieci, szkielet
    //Pierwsza kreska: ukosna
    string webSkeleton("<polyline points='" + conversionF(middle+webLength*0.5)+ comma+  conversionF(middle- webLength*sqrt(3.0)/2)+space);
    webSkeleton= webSkeleton+  conversionF(middle- webLength*0.5)+comma+ conversionF(middle+ webLength*sqrt(3.0)/2)+ space;
    webSkeleton= webSkeleton+ " ' style='fill:white;stroke:silver;stroke-width:2'/> <polyline points=' ";
    //Druga kreska: ukosna
    webSkeleton= webSkeleton+ conversionF(middle - webLength/2)+comma+conversionF(middle- webLength*sqrt(3.0)/2)+space;
    webSkeleton= webSkeleton+ conversionF(middle+webLength*0.5)+ comma+ conversionF(middle+ webLength*sqrt(3.0)/2)+space;
    webSkeleton= webSkeleton+ " ' style='fill:white;stroke:silver;stroke-width:2'/> <polyline points=' "+space;
    //Trzecia kreska: pozioma
    webSkeleton= webSkeleton+ conversionF(middle- webLength) + comma+ conversionF(middle)+space+ conversionF(middle+ webLength)+comma+ conversionF(middle);
    webSkeleton= webSkeleton+ "' style='fill:white;stroke:silver;stroke-width:2'/>";
cout<<webSkeleton;
    float i;
   return webSkeleton;
}

string spider:: set_webHexagons()            //rysowanie szesciokatow
{   //rysowanie jednego szesciokata(najmniejszego)
    string hexagon("<polyline points='" + conversionF(middle- length/webDensity)+ comma+ conversionF(middle)+ space+ conversionF(middle- length/(2*webDensity))+ comma+ conversionF(middle-length*sqrt(3.0)/(2*webDensity))+ space+ conversionF(middle+ length/(2*webDensity)));
    hexagon= hexagon+ comma+ conversionF(middle-length* sqrt(3.0)/(2*webDensity))+ space + conversionF(middle+ length/webDensity)+ comma+ conversionF(middle)+ space+ conversionF(middle+ length/(2*webDensity))+comma+ conversionF(middle+length* sqrt(3.0)/(2*webDensity))+space;
    hexagon= hexagon+ conversionF(middle- length/(2*webDensity))+comma+conversionF(middle+length* sqrt(3.0)/(2*webDensity))+ space;
    hexagon= hexagon+ conversionF(middle- length/webDensity)+ comma+ conversionF(middle)+"' style='fill:#ffffff; stroke:silver; ";

    //rysowanie reszty szesciokatow
string web;
float i;

    for (i= 1; i<=webDensity; i++)
{ //(1-i)*middle - przesuniêcie(translacja) wspolrzednej tak, aby po przeksztalceniu nie obiekt nie zmienil swojego polozenia
// i(w kodzie)- skala powiekszenia szesciokata(w kierunku x i y taka sama- jednokladnosc)
//2/i- szerokosc linii szesciokata

web= "<g transform='translate (" + conversionF((1-i)*middle)+ comma+ conversionF((1-i)*middle)+ ") scale("+ conversionF(i)+comma+conversionF(i)+")'>"+ hexagon+ " stroke-width: "+ conversionF(2/i) + "'/>"+"</g>"+ web;
}
return web;
}

string spider:: set_spider()
{   // wzorcowy pajak:
    string spider(" <ellipse cx='300' cy='280' rx='6' ry='9' fill='black'/> <ellipse cx='300' cy='300' rx='12' ry='18' fill='black'/> <polyline points='300,289 311,270 322,260 311,270 300,289' style='stroke:black;stroke-width:1.3'/>");
    spider= spider+  "<polyline points='300,283 317,279 332,268 317,279 300,283' style='stroke:black;stroke-width:1.3'/> <polyline points='300,283 319,284 336,291 319,284 300,283' style='stroke:black;stroke-width:1.3'/>";
    spider= spider+ "<polyline points='300,285 320,290 334,304 320,290 300,285' style='stroke:black;stroke-width:1.3'/> <g transform= 'translate (600,0) scale(-1,1)'> <ellipse cx='300' cy='280' rx='6' ry='9' fill='black'/>";
    spider= spider+ "<ellipse cx='300' cy='300' rx='12' ry='18' fill='black'/> <polyline points='300,289 311,270 322,260 311,270 300,289' style='stroke:black;stroke-width:1.3'/> ";
    spider= spider+ "<polyline points='300,283 317,279 332,268 317,279 300,283' style='stroke:black;stroke-width:1.3'/> <polyline points='300,283 319,284 336,291 319,284 300,283' style='stroke:black;stroke-width:1.3'/> <polyline points='300,285 320,290 334,304 320,290 300,285' style='stroke:black;stroke-width:1.3'/> </g>";

                //  przesuniecie o Xpose,Ypose                                            //zmiana rozmiaru pajaka w skali spiderSize; przesuniecie (1-spiderSize)*middle, by polozenie pajaka wrocilo do poprzedniego
return transform_begin+ conversionF(Xpose)+ comma+ conversionF(Ypose)+ ") scale(1,1) '>"+transform_begin+ conversionF((1-spiderSize)*middle)+ comma+ conversionF((1-spiderSize)*middle)+ scale+ conversionF(spiderSize)+ comma+ conversionF(spiderSize) +transform_end+ spider+ "</g>"+"</g>";
}
                        //---------------metody get-----------------/
string spider:: get_code()
{
    return set_webHexagons()+ set_webSkeleton()+ set_spider();
}
