#ifndef _skiplist_h_
#define _skiplist_h_

#include<cstdlib>
#include<iostream>

struct slEl
{
	int val;
	int height;	
	static const int maxheight = 5;
	slEl **wsk;

	slEl()
	{
		this->val = 0;
		this->height = this->maxheight;
		this->wsk = new slEl * [this->height];
		for(int i = 0; i < this->height; ++i)
			this->wsk[i] = 0;
	}

	slEl(int a)
	{
		this->val = a;
		this->height = rand() % this->maxheight + 1;
		this->wsk = new slEl * [this->height];
		for(int i = 0; i < this->height; ++i)
			this->wsk[i] = 0;
	}

	~slEl()
	{
		delete [] this->wsk;
	}
};

struct skiplist
{
	slEl * head;

	skiplist()
	{
		this->head = new slEl;
	}

	~skiplist()
	{
		slEl * tmp;
		while(this->head)
		{
			tmp = this->head;
			this->head = this->head->wsk[0];
			delete tmp;
		}
	}

	slEl * insert(int);
	slEl * search(int);
	void del(int);
	void write();
};

#endif