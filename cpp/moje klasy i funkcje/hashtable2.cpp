#include"hashtable2.h"
#include<iostream>

void hashtable2::write()
{
	for(int i = 0; i < this->size; ++i)
	{
		if(this->tab[i] && !this->tab[i]->deleted)
			std::cout << this->tab[i]->val << std::endl;
	}
	std::cout << std::endl;
}

int hashtable2::hash(char * a)
{
	int hashyk = 0;
	int size = 0;
	bool stop = false;
	while(!stop)
	{
		size = 0;
		for(int i = 0; i < 4; ++i)
		{
			if(a[i])
				size++;
			else
			{
				stop = true;
				break;
			}
		}
		if(size == 4)
		{
			int x = *((int *)a);
			hashyk ^= x;
		}
		else
		{
			int x = 0;
			for(int i = 0; i < size; ++i)
				x = (x << 8) | a[i];
			hashyk ^= x;
		}
		a += 4;
	}
	return hashyk % this->size;
}

htEl * hashtable2::insert(char * a)
{
	int ahash = hash(a);
	if(!this->tab[ahash])
	{
		this->tab[ahash] = new htEl(a);
		return this->tab[ahash];
	}
	else
	{
		htEl * pom = 0;
		int i = this->size;
		while(i && this->tab[ahash])
		{
			if(!this->tab[ahash]->deleted && !strcmp(this->tab[ahash]->val, a))
				return this->tab[ahash];
			if(!pom && this->tab[ahash]->deleted)
				pom = this->tab[ahash];
			--i;
			(++ahash) %= this->size;
		}
		if(!i && this->tab[ahash] && !pom)
			return 0;
		if(pom)
		{
			delete pom;
			pom = new htEl(a);
			return pom;
		}
		else
		{
			this->tab[ahash] = new htEl(a);
			return this->tab[ahash];
		}
	}
}

htEl * hashtable2::search(char * a)
{
	int ahash = hash(a);
	if(this->tab[ahash])
	{
		int i = this->size;
		while(i && this->tab[ahash])
		{
			if(!this->tab[ahash]->deleted && !strcmp(this->tab[ahash]->val, a))
				return this->tab[ahash];
			--i;
			(++ahash) %= this->size;
		}
	}
	return 0;
}

void hashtable2::del(char * a)
{
	htEl * pom = 0;
	int i = this->size;
	while(i && this->tab[ahash])
	{
		if(!this->tab[ahash]->deleted && !strcmp(this->tab[ahash]->val, a))
		{
			this->tab[ahash]->deleted = true;
			break;
		}
		if(!pom && this->tab[ahash]->deleted)
			pom = this->tab[ahash];
		--i;
		(++ahash) %= this->size;
	}
}
