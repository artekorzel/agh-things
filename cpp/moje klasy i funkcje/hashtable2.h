#ifndef _hashtable2_h_
#define _hashtable2_h_

#include<iostream>
#include<cstring>

struct htEl
{
	char * val;

	bool deleted;
	htEl(char * a = "")
	{
		this->val = new char[strlen(a) + 1];
		strcpy(this->val, a);
		this->deleted = false;
	}
	~htEl()
	{
		delete [] this->val;
	}
};

struct hashtable2
{
	htEl ** tab;

	const int size; 

	hashtable2(int n = 10): size(n)
	{		
		this->tab = new htEl * [n];
		for(int i = 0; i < this->size; ++i)
			this->tab[i] = 0;
	}

	~hashtable2()
	{
		for(int i = 0; i < this->size; ++i)
			if(this->tab[i]) delete this->tab[i];
		delete [] this->tab;
	}

	int hash(char *);
	htEl * insert(char *);
	void write();
	htEl * search(char *);
	void del(char *);
};

#endif