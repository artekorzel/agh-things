#include"graf odsy³aczowy.h"
#include"stos.h"
#include<iostream>

int main()
{
	graf G;
	stos<int> L;
	G.fleury(1, L);
	stos<int>::el * tmp = L.Top;
	while(tmp)
	{
		std::cout << tmp->war << " ";
		tmp = tmp->wsk;
	}
	return 0;
}