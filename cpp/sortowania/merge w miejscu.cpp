#include<stdio.h>
#include<time.h>
#include<stdlib.h>

const int size = 100000;
int tab[size]; // tablica z danymi, linijka poni�ej to na razie tylko deklaracja funkcji

void przetworz(int p, int r, int q);      // parametry: pocz�tek tablicy, koniec tablicy, pocz�tek obszaru posortowanego

void swap(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

void scal(int l1,int r1, int l2, int r2)  // scala 2 tablice: l1-r1 i l2-r2, za�: l2-r1 >= r1-l1
{
  int pocz = l2 - r1 - 1 + l1;            // indeks pierwszego wolnego miejsca, gdzie mo�emy wstawi� element
  while(l2-pocz > 0)                        // oznacza, �e nie wykorzystali�my wszystkich element�w z l1-r1
  {
    if(tab[l1] > tab[l2]) 
	{ 
		swap(tab[l2],tab[pocz]);
		++l2; 
	}
    else                  
	{ 
		swap(tab[l1],tab[pocz]); 
		++l1; 
	}
    ++pocz;
    if(l2 > r2)
		break;
  }
  if((l2 > r2) && (l2-pocz>0))                // musimy przepisa� ko�c�wk�
    for(;pocz <= r2;++pocz, ++l1)
		swap(tab[l1],tab[pocz]);
}

void merge(int p, int r)                  // parametry to indeks pocz�tku i ko�ca tablicy do sortowania
{
  if(p < r)
  {
    int q = (p+r)/2;
    merge(q+1,r);                         //  sortuj� drug� po�ow�
    przetworz(p,r,q+1);                   // sortuj� ju� wszystkie elementy, z wyj�tkiem pierwszego w tablicy
    while((p < r) && (tab[p] > tab[p+1]))
	{
		swap(tab[p],tab[p+1]);
		++p;
	}// i jeszcze przesuniecie w odp miejsce pierwszego elementu
  }
}

void przetworz(int p, int r, int q)          
{
  if(p+1 < q)                             // czyli je�eli cz�� nieposortowana sk�ada si� z wi�cej ni� jednego elementu
  {
    int s = (p+q-2)/2;
    merge(p,s);                           // sortuj� pierwsz� po�ow� nieposortowanej cz�ci
    scal(p,s,q,r);         // scalam obie cz�ci, nieposortowana cz�� przesuwa si� do obszaru od p do q-s-2, nowe q wynosi wi�c q-s-1
    przetworz(p,r,q-s-1+p);               // przetwarzam z coraz wi�ksz� cz�ci� posortowan�
  }
}

int main()
{
	int i;
	srand((int)(time(NULL)));
	for (i = 0; i < size; ++i) tab[i] = rand() % 100000;

	merge(0, size -1);

	for (i = 0; i < size; ++i) printf("%d ", tab[i]);
	getchar();
}