#include"trie.h"
#include<iostream>
#include<cstring>

void writ(trieEl * p)
{
	trieEl * pom = p;
	while(pom)
	{
		if(pom->val != 0)
			std::cout << pom->val;
		else std::cout << ".";
		std::cout << "	";
		pom = pom->right;
	}
	pom = p;
	std::cout << std::endl;
	while(pom)
	{
		writ(pom->down);
		pom = pom->right;
	}
}

void trie::write()
{
	writ(this->head);
}

void trie::insert(char * a)
{
	int ileLiter = strlen(a);
	int i = 0;
	trieEl * pom = this->head;
	trieEl * q = 0;
	if(pom)
	{
		while(pom && i <= ileLiter)
		{
			if(pom->val == a[i])
			{
				q = 0;
				pom = pom->down;
				++i;
			}
			else 
			{
				q = pom;
				pom = pom->right;
			}
		}

		if(i > ileLiter)
			return;

		if(q)
		{
			q->right = new trieEl(a[i]);
			q = q->right;
			++i;
		}
	}
	else
	{
		this->head = new trieEl(a[i]);
		q = this->head;
		++i;
	}

	while(i <= ileLiter)
	{
		q->down = new trieEl(a[i]);
		q = q->down;
		++i;
	}
}

bool trie::isIn(char * a)
{
	int ileLiter = strlen(a);
	int i = 0;
	trieEl * pom = this->head;
	if(pom)
	{
		while(pom && i <= ileLiter)
		{
			if(pom->val == a[i])
			{
				pom = pom->down;
				++i;
			}
			else 
				pom = pom->right;
		}

		if(i > ileLiter)
			return true;
	}
	return false;
}

void trie::del(char * a)
{
	if(isIn(a))
		this->usun(this->head, a, 0, strlen(a));
}

bool trie::usun(trieEl * p, char * a, int ile, int max)
{
	if(ile == max)
	{
		trieEl * q = 0;
		while(p && p->val != 0)
		{
			q = p;
			p = p->right;
		}
		if(!q && !p->right)
		{
			delete p;
			return true;
		}
		else
		{
			if(q) q->right = p->right;
			else
			{
				q = p;
				p = p->right;
				q->val = p->val;
				q->down = p->down;
				q->right = p->right;
			}
			delete p;
			return false;
		}		
	}
	else
	{
		trieEl * q = 0;
		while(p && p->val != a[ile])
		{
			q = p;
			p = p->right;
		}
		bool b = usun(p->down, a, ile + 1, max); 
		if(!q && !p->right && b)
		{
			delete p;
			if(ile == 0)
				this->head = 0;
			return true;
		}
		else if(b)
		{
			if(q) q->right = p->right;
			else
			{
				q = p;
				p = p->right;
				if(p)
				{
					q->val = p->val;
					q->down = p->down;
					q->right = p->right;
				}
			}
			if(p) delete p;
		}		
		return false;
	}
}