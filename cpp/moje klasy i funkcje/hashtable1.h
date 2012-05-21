#ifndef _hashtable1_h_
#define _hashtable1_h_

#include<iostream>

struct htEl
{
	int val;

	htEl * next;
	htEl(int a = 0)
	{
		this->val = a;
		this->next = 0;
	}
};

struct hashtable1
{
	htEl ** tab;

	const int size; 

	hashtable1(int n = 5): size(n)
	{		
		this->tab = new htEl * [n];
		for(int i = 0; i < n; ++i)
			this->tab[i] = 0;
	}

	~hashtable1()
	{
		htEl * pom;
		for(int i = 0; i < this->size; ++i)
		{
			pom = this->tab[i];
			while(pom)
			{
				this->tab[i] = this->tab[i]->next;
				delete pom;
				pom = this->tab[i];
			}
		}
		delete [] this->tab;
	}

	int hash(int);
	htEl * insert(int);
	void write();
	htEl * search(int);
	void del(int);
};

#endif