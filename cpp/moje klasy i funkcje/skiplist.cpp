#include"skiplist.h"
#include<iostream>

void skiplist::write()
{
	slEl * tmp = this->head;
	while(tmp)
	{
		std::cout << tmp->val << " ";
		tmp = tmp->wsk[0];
	}
	std::cout << std::endl;
}

slEl * skiplist::insert(int a)
{
	if(a > 0)
	{
		int i, j = this->head->maxheight - 1;
		slEl ** pom = new slEl * [j + 1];
		for(i = 0; i < j + 1; ++i)
			pom[i] = 0;
		slEl * p = this->head;
		while(j >= 0)
		{
			while(p->wsk[j] && p->wsk[j]->val < a)
				p = p->wsk[j];
			if(p->wsk[j] && p->wsk[j]->val == a)
				return p->wsk[j];
			pom[j] = p;
			--j;
		}
		p = 0;
		p = new slEl(a);
		for(i = 0; i < p->height; ++i)
		{
			p->wsk[i] = pom[i]->wsk[i];
			pom[i]->wsk[i] = p;
		}
		delete [] pom;
		return p;
	}
	return 0;
}

slEl * skiplist::search(int a)
{
	int j = this->head->maxheight - 1;
	slEl * p = this->head;
	while(j >= 0)
	{
		while(p->wsk[j] && p->wsk[j]->val < a)
			p = p->wsk[j];
		if(p->wsk[j] && p->wsk[j]->val == a)
			return p->wsk[j];
		--j;
	}
	return 0;
}

void skiplist::del(int a)
{
	if(a > 0)
	{
		int i, j = this->head->maxheight - 1;
		slEl ** pom = new slEl * [j + 1];
		for(i = 0; i < j + 1; ++i)
			pom[i] = 0;
		slEl * p = this->head;
		slEl * q = 0; 
		while(j >= 0)
		{
			while(p->wsk[j] && p->wsk[j]->val < a)
				p = p->wsk[j];
			if(p->wsk[j] && p->wsk[j]->val == a)
				q = p->wsk[j];
			pom[j] = p;
			--j;
		}
		if(q)
		{
			for(i = 0; i < q->height; ++i)
				pom[i]->wsk[i] = q->wsk[i];
			delete q;
		}
		delete [] pom;
	}
}
