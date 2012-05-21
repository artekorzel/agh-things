#ifndef _STOS__H_
#define _STOS__H_

template<class T>
struct stos
{
	struct el
	{
		T war;
		el * wsk;
	};

public:	
	el *Top;

	stos() {Top = 0;}
	~stos()
	{
		stos::el * tmp = Top;
		while(tmp)
		{
			Top = Top->wsk;
			delete tmp;
			tmp = Top;
		}
	}
	void push(T x)
	{
		el *nowy = new el;
		nowy->wsk = Top;
		nowy->war = x;
		Top = nowy;
	}
	T pop()
	{
		T k = Top->war;
		stos::el *tmp = Top;
		Top = Top->wsk;
		delete tmp;
		return k;
	}
	bool empty()
	{
		return (Top == 0);
	}
};

#endif