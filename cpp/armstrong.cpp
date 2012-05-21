#include<iostream>
using namespace std;

int main()
{
    
    int wyn[60], rez[60], licznik = 0;
    int potegi[10][60];
    bool b;
    int i,lic = 1;
	int x,tmp,p,j,k,m = 0;
	for (i = 0; i < 10; i++) for (j = 0; j < 60; j++) potegi[i][j] = 0;
    for (i = 1; i <= 9; i++) potegi[i][0] = 1;
	for (i = 0; i < 60; i++) wyn[i] = 0;
    wyn[0] = 1;
    
    do
    {
        i = lic - 1;
        for (k = 2; k <= 9; ++k)
        {
            x = 0;
            tmp = 0;
            b = false;
            do 
            {
                  potegi[k][x] = potegi[k][x] * k + tmp;
                  tmp = potegi[k][x] / 10;
                  potegi[k][x] = potegi[k][x] % 10;                  
                  if ((x=i) && (tmp != 0)) b = true;
                  ++x;
            } while(tmp != 0);
        };
        
    do
    {
        //for (i = lic-1; i >= 0; --i) cout << wyn[i];
        //cout << endl;
        
        i = lic - 1;

		++m;
        for (j = 0; j < 60; j++) rez[j] = 0;
        
        if (!b) for (k = 0; k <= i; k++) 
        {
            j = 0;
            p = 0;
			tmp = wyn[k];
            while ((potegi[tmp][j] != 0) || (p != 0))
            {
                  rez[j] = p + rez[j] + potegi[tmp][j];
                  p = rez[j] / 10;
                  rez[j] = rez[j] % 10;
                  if (j > i) b = true;
                  if (b) break;
                  ++j;                  
            };
            if (b) break;	
        };
		--j;
        
        if (j == i) 
        {
              j = 0;
              while (j <= i) 
              {
                    if (wyn[j] != rez[j]) b = true;
                    if (b) break;
                    ++j;
              }
          
          if (!b) 
          {
                  cout << "liczba nr: " << ++licznik << endl;
                  for (i; i >= 0; i--) cout << wyn[i];
                  cout << endl;
          }        
        }  
        
        wyn[0] = wyn[0] + 1;
        //cout << wyn[1] << wyn[0] << endl;
        tmp = 0;
        i = 0;
        do
        {
            wyn[i] = wyn[i] + tmp;
            tmp = wyn[i] / 10;
            wyn[i] = wyn[i] % 10;
            ++i;
        } while (tmp != 0); 
        //cout << wyn[1] << wyn[0] << endl;
         
        b = false; 
        
    } while (m < 10^lic);
	++lic;
        
    } while (i < 60);
}
    
    
