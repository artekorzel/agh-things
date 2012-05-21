#include<iostream>
#include<conio.h>
using namespace std;

int main()
{
    int a = 1,b = 1;
    cout << a;
    while (b < 1000)
    {
          cout << endl << b;
          b = a + b;
          a = b - a;
    }
    getch();
}
    
    
