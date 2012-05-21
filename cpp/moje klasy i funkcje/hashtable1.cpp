#include"hashtable1.h"
#include<iostream>

void hashtable1::write()
{
	htEl * pom;
	for(int i = 0; i < this->size; ++i)
	{
		pom = this->tab[i];
		while(pom)
		{
			std::cout << pom->val << " ";
			pom = pom->next;
		}
		std::cout << std::endl;
	}
}

int hashtable1::hash(int a)
{
	return a % this->size;
}

htEl * hashtable1::insert(int a)
{
	int indeks = hash(a);
	htEl * p = this->tab[indeks];
	htEl * q = 0;
	if(p && p->val < a)
	{
		do
		{
		q = p;
		p = p->next;
		} while(p && p->val < a);
		if(p && p->val == a)
			return p;
		q->next = new htEl(a);
		q->next->next = p;
		return q->next;
	}
	else if(p && p->val == a)
		return p;
	else
	{
		q = new htEl(a);
		this->tab[indeks] = q;
		q->next = p;
		return q;
	}
}

htEl * hashtable1::search(int a)
{
	int indeks = hash(a);
	htEl * p = this->tab[indeks];
	if(p && p->val < a)
	{
		do
		{
		p = p->next;
		} while(p && p->val < a);
		if(p && p->val == a)
			return p;
		else return 0;
	}
	else if(p && p->val == a)
		return p;
	else return 0;
}

void hashtable1::del(int a)
{
	int indeks = hash(a);
	htEl * p = this->tab[indeks];
	htEl * q = 0;
	if(p && p->val < a)
	{
		do
		{
		q = p;
		p = p->next;
		} while(p && p->val < a);
		if(p && p->val == a)
		{
			q->next = p->next;
			delete p;
		}
		else return;
	}
	else if(p && p->val == a)
	{
		this->tab[indeks] = p->next;
		delete p;
	}
	else return;
}
