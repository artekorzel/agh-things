#include<iostream>
#include<conio.h>
using namespace std;

int main()
{
    int a;
    cin >> a;
    int b = a;
    int c = 0;
    while (b!=0)
    {
        c = c*10 + b % 10;
        b = b / 10;
    }
    if (a == c) cout << "tak";
    else cout << "nie";
    getch();
}  
