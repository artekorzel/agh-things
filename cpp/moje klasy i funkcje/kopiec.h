#ifndef _KOPIEC__H_
#define _KOPIEC__H_

#include"graf_adj.h"

struct kopiec
{
	struct el
	{
		int ind;
		int key;

		el(int i = 0, int k = 0): ind(i), key(k) {}
	};

	int tab_size;
	int size;
	el * tab;

	kopiec(int a = 5): tab_size(a), size(0) {tab = new el [tab_size];}
	~kopiec() {delete [] tab;}

	int parent(int i) {return (i - 1)/2;}
	int left(int i) {return 2 * i + 1;}
	int right(int i) {return 2 * i + 2;}

	void kopcuj(int i)
	{
		int l = left(i);
		int r = right(i);
		el tmp;
		int maxi;
	
		if ((l < size) && ((tab[l]).key > (tab[i]).key))
			maxi = l;
		else maxi = i;
		if ((r < size) && ((tab[r]).key > (tab[maxi]).key))
			maxi = r;

		if (maxi != i)
		{
			tmp = tab[i];
			tab[i] = tab[maxi];
			tab[maxi] = tmp;
			kopcuj(maxi);
		}
	}

	void buduj()
	{
		int i;
		for(i = size/2 - 1; i >= 0; --i)
			kopcuj(i);
	}

	void dodaj(int x, int y)
	{
		tab[size++].ind = x;
		tab[size++].key = y;
		this->buduj();
	}

	void usun_pierwszy()
	{
		el tmp = tab[0];
		tab[0] = tab[--size];
		tab[size] = tmp;
		kopcuj(0);
	}
};

#endif