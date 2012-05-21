#include<stdio.h>
#include<time.h>
#include<stdlib.h>

const int size = 100000;
int tab[size]; // tablica z danymi, linijka poni¿ej to na razie tylko deklaracja funkcji

void przetworz(int p, int r, int q);      // parametry: pocz¹tek tablicy, koniec tablicy, pocz¹tek obszaru posortowanego

void swap(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

void scal(int l1,int r1, int l2, int r2)  // scala 2 tablice: l1-r1 i l2-r2, za³: l2-r1 >= r1-l1
{
  int pocz = l2 - r1 - 1 + l1;            // indeks pierwszego wolnego miejsca, gdzie mo¿emy wstawiæ element
  while(l2-pocz > 0)                        // oznacza, ¿e nie wykorzystaliœmy wszystkich elementów z l1-r1
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
  if((l2 > r2) && (l2-pocz>0))                // musimy przepisaæ koñcówkê
    for(;pocz <= r2;++pocz, ++l1)
		swap(tab[l1],tab[pocz]);
}

void merge(int p, int r)                  // parametry to indeks pocz¹tku i koñca tablicy do sortowania
{
  if(p < r)
  {
    int q = (p+r)/2;
    merge(q+1,r);                         //  sortujê drug¹ po³owê
    przetworz(p,r,q+1);                   // sortujê ju¿ wszystkie elementy, z wyj¹tkiem pierwszego w tablicy
    while((p < r) && (tab[p] > tab[p+1]))
	{
		swap(tab[p],tab[p+1]);
		++p;
	}// i jeszcze przesuniecie w odp miejsce pierwszego elementu
  }
}

void przetworz(int p, int r, int q)          
{
  if(p+1 < q)                             // czyli je¿eli czêœæ nieposortowana sk³ada siê z wiêcej ni¿ jednego elementu
  {
    int s = (p+q-2)/2;
    merge(p,s);                           // sortujê pierwsz¹ po³owê nieposortowanej czêœci
    scal(p,s,q,r);         // scalam obie czêœci, nieposortowana czêœæ przesuwa siê do obszaru od p do q-s-2, nowe q wynosi wiêc q-s-1
    przetworz(p,r,q-s-1+p);               // przetwarzam z coraz wiêksz¹ czêœci¹ posortowan¹
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