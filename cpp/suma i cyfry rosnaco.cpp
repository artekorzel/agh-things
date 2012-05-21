#include<iostream>
#include<conio.h>
using namespace std;

int main()
{
    int a,b;
    cin >> a >> b;
    bool test = true;
    a = a + b;
    b = a % 10;
    a = a / 10;
    while ((a!=0) && (test))
    {
          int c = a % 10;
          if (b <= c) test = false;
          else 
          {
               a = a / 10;
               b = c;
          }
    }
    if (test) cout << "tak";
    else cout << "nie";
    getch();
}
