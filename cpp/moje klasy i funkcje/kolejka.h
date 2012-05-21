#ifndef _KOLEJKA__H_
#define _KOLEJKA__H_

template<class T>
class kolejka
{
	struct el
	{
		T war;
		el * next;
		el * prev;

		el(T a = 0, el * n = 0, el * p = 0): war(a), next(n), prev(p) {}
	};

public:	
	el * top;
	el * back;

	kolejka(): top(0), back(0) {}
	~kolejka()
	{
		el * tmp = top;
		while(tmp)
		{
			top = top->next;
			delete tmp;
			tmp = top;
		}
	}

	void push(T a)
	{
		if(top)
			back->next = new el(a, 0, back);
		else top = back = new el(a);
	}

	T pop()
	{
		el * tmp = top;
		top = top->next;
		if(!top) back = 0;
		else top->prev = 0;
		tmp->next = 0;
		T k = tmp->war;
		delete tmp;
		return k;
	}

	bool empty()
	{
		return (top == 0);
	}
};

#endif