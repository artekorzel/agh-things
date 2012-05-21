#ifndef _KOLEJKA_P__H_
#define _KOLEJKA_P__H_

#include"graf_adj.h"

struct kolejka_p
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

	int parent(int i) {return (i - 1)/2;}
	int left(int i) {return 2 * i + 1;}
	int right(int i) {return 2 * i + 2;}

	void kopcuj(int i)
	{
		int l = left(i);
		int r = right(i);
		el tmp;
		int mini;
	
		if ((l < size) && ((tab[l]).key < (tab[i]).key))
			mini = l;
		else mini = i;
		if ((r < size) && ((tab[r]).key < (tab[mini]).key))
			mini = r;

		if (mini != i)
		{
			tmp = tab[i];
			tab[i] = tab[mini];
			tab[mini] = tmp;
			kopcuj(mini);
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

	kolejka_p(int a = 5): tab_size(a), size(0) {tab = new el [tab_size];}
	~kolejka_p() {delete [] tab;}

	int top() {return (tab[0]).ind;}
	void pop() {this->usun_pierwszy();}
	void push(int x, int y) {this->dodaj(x, y);}
	bool isIn(int a)
	{
		for(int i = 0; i < size; ++i)
			if((tab[i]).ind == a)
				return true;
		return false;
	}
	bool empty() {return (size == 0);}
};

#endif
