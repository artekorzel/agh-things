#ifndef _graf_odsylaczowy_h_
#define _graf_odsylaczowy_h_

#include<iostream>
#include<queue>
#include"stos.h"

struct graf
{
	static const int MAXINT = 2147483647;
	
	struct node
	{
		int ind;
		node * next;

		node(int a = 0)
		{
			ind = a;
			next = 0;
		}
		/*~node()
		{
			if(this)
			{
				node * tmp = this->next, *tmp2;
				while(tmp)
				{
					tmp2 = tmp;
					tmp = tmp->next;
					delete tmp2;
				}
			}
		}*/
	};

	struct elem
	{
		enum colors {bialy, szary, czarny};
		colors color;
		elem * prev;
		int dist;
		node * head;
		node * end;
		int to_grey;
		int to_black;

		elem()
		{
			color = bialy;
			prev = 0;
			dist = MAXINT;
			head = 0;
			end = 0;
			to_grey = 0;
			to_black = 0;
		}
		~elem() {delete head;}	
	};

	elem * tab;
	int ile;

	void write_lists()
	{
		for(int i = 0; i < ile; ++i)
		{
			node * tmp = tab[i].head;
			while(tmp)
			{
				std::cout << tmp->ind << " ";
				tmp = tmp->next;
			}
			std::cout << std::endl;
		}
	}

	void write_dist()
	{
		for(int i = 0; i < ile; ++i)
			std::cout << tab[i].dist << " ";
		std::cout << std::endl;
	}

	void write_to_g_b()
	{
		for(int i = 0; i < ile; ++i)
			std::cout << tab[i].to_grey << " " << tab[i].to_black << std::endl;;
	}

	void wstaw(int i, int c)
	{
		if(tab[i].head == 0)
		{
			tab[i].head = new node(c);
			tab[i].end = tab[i].head;
		}		
		else
		{
			tab[i].end->next = new node(c);
			tab[i].end = tab[i].end->next;
		}
	}

	graf(int a = 5)
	{
		ile = a;
		tab = new elem [a];
		for(int i = 0; i < a; ++i)
		{
			std::cout << "ile dla: " << i << std::endl;
			int b, c;
			std::cin >> b;
			if(b > 0)
			{
				std::cout << "jakie dla: " << i << std::endl;
				do
				{				
					std::cin >> c;
					wstaw(i, c);
					wstaw(c, i);//dla nieskierowanego
					--b;
				} while(b > 0);
			}
		}
		tab[0].dist = 0;
	}

	~graf()
	{
		delete [] tab;
	}

	void bfs()
	{
		std::queue<int> q;
		q.push(0);
		int i, j;
		while(!q.empty())
		{
			i = q.front();
			q.pop();
			node * tmp = tab[i].head;
			while(tmp)
			{
				j = tmp->ind;
				if(tab[j].color == elem::bialy)
				{
					tab[j].color = elem::szary;
					tab[j].dist = tab[i].dist + 1;
					tab[j].prev = &tab[i];
					q.push(j);
				}
				tmp = tmp->next;
			}
			tab[i].color = elem::czarny;
		}
	}

	void dfs()
	{
		int i, count = 0;
		for(i = 0; i < ile; ++i)
			if(tab[i].color == elem::bialy) dfs_visit(i, count);
	}

	void dfs_visit(int i, int & count)
	{
		tab[i].color = elem::szary;
		++count;
		tab[i].to_grey = count;
		node * tmp = tab[i].head;
		int j;
		while(tmp)
		{
			j = tmp->ind;
			if(tab[j].color == elem::bialy)
			{
				tab[j].prev = &tab[i];
				dfs_visit(j, count);
			}
			tmp = tmp->next;
		}
		tab[i].color = elem::czarny;
		tab[i].to_black = ++count;
	}

	void fleury(int s, stos<int> & L)
	{
		while(tab[s].head != 0)
		{
			node * tmp = tab[s].head;
			int x = tmp->ind;
			tab[s].head = tmp->next;
			delete tmp;
			node * pom = 0, *tmp2;
			tmp2 = tab[x].head;
			while(tmp2 != 0)
				if(tmp2->ind == s)
				{
					if(pom)
						pom->next = tmp2->next;
					else tab[x].head = tmp2->next;
					delete tmp2;
					break;
				}
			fleury(x, L);
		}
		L.push(s);
	}
};

#endif