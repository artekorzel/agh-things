#include<iostream>
#include<conio.h>
using namespace std;
const int maks = 5;

void jedynki(int tab[])
{
    for (int i = 0; i < maks; i++)
    {
        int k = 0;
        while (tab[i] != 0)
        {
              if (tab[i] % 2) ++k;
              tab[i] = tab[i] / 2;
        };
        tab[i] = k;
    }
};

bool sprawdz(int tab[], int s1, int s2, int s3, int k)
{
     if ((k == maks))
     {
		 if ((s1 == s2) && (s2 == s3)) return true;
     } else
     {
          return ((sprawdz(tab, s1+tab[k], s2, s3, k+1)) || 
                  (sprawdz(tab, s1, s2+tab[k], s3, k+1)) ||
                  (sprawdz(tab, s1, s2, s3+tab[k], k+1)));
     };
}

int main()
{
    int t[maks];
    for (int j = 0; j < maks; j++) cin >> t[j];
    jedynki(t);
    for (int j = 0; j < maks; j++) cout << t[j] << " ";
    if (sprawdz(t, 0, 0, 0, 0)) cout << "TAK";
    else cout << "NIE";
    getch();
}        
