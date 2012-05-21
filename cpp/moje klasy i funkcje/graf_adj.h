#ifndef _GRAF_INC__H_
#define _GRAF_INC__H_

#include"kolejka.h"
#include"stos.h"
#include"zbiory.h"
#include"kolejka_p.h"

struct vertex
{
	int rank;
	vertex * bfs_par;
	vertex * dfs_par;
	vertex * set_root;
	vertex * prim_par;
	int dist;
	int start;
	int end;
	int key;
	enum {bialy, szary, czarny} color;
	static const int MAXINT = 2147483647;
	vertex * d_par;
	int d_dist;
	
	vertex(): bfs_par(0), dfs_par(0), dist(MAXINT), start(MAXINT), end(MAXINT), color(bialy), key(MAXINT), prim_par(0) {}
};

struct edge
{
	int weight;
	int v1;
	int v2;

	edge():weight(0), v1(0), v2(0) {}
};

struct krusk
{
	struct el
	{
		edge * e;
		el * next;
		el(edge * a = 0, el * n = 0): e(a), next(n) {}
	};

	el * Top;
	el * Back;

	krusk(): Top(0), Back(0) {}
	~krusk()
	{
		el * tmp = Top;
		while(tmp)
		{
			Top = Top->next;
			delete tmp;
			tmp = Top;
		}
	}

	void add(edge * x)
	{
		if(Top)
		{
			Back->next = new el(x);
			Back = Back->next;
		}
		else
		{
			Top = new el(x);
			Back = Top;
		}
	}
};

/***************************************************************************************/

struct graf_adj;

struct kolejka_p
{
	int tab_size;
	int size;
	int tab;

	int parent(int i) {return (i - 1)/2;}
	int left(int i) {return 2 * i + 1;}
	int right(int i) {return 2 * i + 2;}

	void kopcuj(int i)
	{
		int l = left(i);
		int r = right(i);
		int tmp;
		int mini;
	
		if ((l < size) && ((G.vert[tab[l]])->key < (G.vert[tab[i]])->key))
			mini = l;
		else mini = i;
		if ((r < size) && ((G.vert[tab[r]])->key < (G.vert[tab[mini]])->key))
			mini = r;

		if (mini != i)
		{
			tmp = tab[i];
			tab[i] = tab[mini];
			tab[mini] = tmp;
			kopcuj(mini);
		}
	}

	void buduj()
	{
		int i;
		for(i = size/2 - 1; i >= 0; --i)
			kopcuj(i);
	}

	void dodaj(int x)
	{
		tab[size++] = x;
		this->buduj();
	}

	void usun_pierwszy()
	{
		int tmp = tab[0];
		tab[0] = tab[--size];
		tab[size] = tmp;
		kopcuj(0);
	}

	kolejka_p(int a = 5): tab_size(a), size(0) {tab = new int [tab_size];}
	~kolejka_p() {delete [] tab;}

	int top() {return tab[0];}
	void pop() {this->usun_pierwszy();}
	void push(int x) {this->dodaj(x);}
	int isIn(int a)
	{
		for(int i = 0; i < size; ++i)
			if(tab[i] == a)
				return i;
		return -1;
	}
	bool empty() {return (size == 0);}
};

/********************************************************************************/

struct graf_adj
{
	vertex ** vert;
	int n;
	int m;
	int time;
	int ** tab;
	edge ** E;

	graf_adj(int x = 5, int y = 3): n(x), m(y), time(0)
	{
		vert = new vertex * [n];
		tab = new int * [n];
		E = new edge * [m];
		for(int i = 0; i < n; ++i)
			tab[i] = new int [n];
		for(int i = 0; i < n; ++i)
			for(int j = 0 ; j < n; ++j)
				tab[i][j] = 0;
	}
	~graf_adj()
	{
		delete [] vert;
		delete [] E;
		for(int i = 0; i < n; ++i) delete [] tab[i];
		delete [] tab;
	}
	void wypelnij()
	{
		for(int i = 0; i < m; ++i)
			tab[(E[i])->v1][(E[i])->v2] = (E[i])->weight;
	}
};

void bfs(graf_adj & G, int s)
{
	kolejka<int> Q;
	(G.vert[s])->color = vertex::szary;
	(G.vert[s])->dist = 0;
	Q.push(s);
	while(!Q.empty())
	{
		int tmp = Q.pop();
		for(int i = 0; i < G.n; ++i)
			if(G.tab[tmp][i])
				if((G.vert[i])->color == vertex::bialy)
				{
					(G.vert[i])->color = vertex::szary;
					(G.vert[i])->dist = (G.vert[tmp])->dist + 1;
					(G.vert[i])->bfs_par = G.vert[tmp];
					Q.push(i);
				}
		(G.vert[tmp])->color = vertex::czarny;
	}
}

void dfs_rek(graf_adj & G, int s)
{
	(G.vert[s])->color = vertex::szary;
	(G.vert[s])->start = ++(G.time);
	for(int i = 0; i < G.n; ++i)
		if(G.tab[s][i])
			if((G.vert[i])->color == vertex::bialy)
			{
				(G.vert[i])->dfs_par = G.vert[s];
				dfs_rek(G, i);
			}
	(G.vert[s])->color = vertex::czarny;
	(G.vert[s])->end = ++(G.time);
}

void dfs1(graf_adj & G, int s)
{
	G.time = 0;
	dfs_rek(G, s);
}

void dfs2(graf_adj & G, int s)
{
	G.time = 0;
	stos<int> S;
	S.push(s);
	while(!S.empty())
	{
		int tmp = S.pop();
		(G.vert[tmp])->color = vertex::szary;
		(G.vert[tmp])->start = ++(G.time);
		S.push(tmp);
		for(int i = 0; i < G.n; ++i)
			if(G.tab[tmp][i])
				if((G.vert[i])->color == vertex::bialy)
				{
					(G.vert[i])->dfs_par = G.vert[tmp];
					(G.vert[i])->color = vertex::szary;
					(G.vert[i])->start = ++(G.time);
					S.push(i);
					break;
				}
		if(i == G.n)
		{
			tmp = S.pop();
			(G.vert[tmp])->color = vertex::czarny;
			(G.vert[tmp])->end = ++(G.time);
		}
	}
}

template<class T>
void swap(T *a, T *b)
{
	T * tmp = a;
	a = b;
	b = tmp;	
}

void qsort(graf_adj & G, int p, int k)
{
	if(p < k)
	{
		int x = (G.E[p])->weight, i = p, j = k;
		do
		{
			while((G.E[i])->weight < x) ++i;
			while((G.E[j])->weight > x) --j;
			if(i <= j) swap(G.E[i++], G.E[j--]);
		}while(i < j);

		if(p < j) qsort(G, p, j);
		if(i < k) qsort(G, i, k);
	}
}

void Kruskal(graf_adj & G, krusk & A)
{
	zbior<vertex> z;
	for(int i = 0; i < G.m; ++i)
		z.make_set(G.vert[i]);
	qsort(G, 0, G.m - 1);

	for(int i = 0; i < G.m; ++i)
		if(z.findset(G.vert[(G.E[i])->v1]) != z.findset(G.vert[(G.E[i])->v2]))
		{
			A.add(G.E[i]);
			z.mix(G.vert[(G.E[i])->v1], G.vert[(G.E[i])->v2]);
		}
}

void prim(graf_adj & G, int s)
{
	kolejka_p Q(G.n);
	(G.vert[s])->key = 0;
	for(int i = 0; i < G.n; ++i)
		Q.push(i);
	while(!Q.empty())
	{
		int tmp = Q.top();
		Q.pop();
		for(int i = 0; i < G.n; ++i)
			if(G.tab[tmp][i])
				if(Q.isIn(i) && G.tab[tmp][i] < (G.vert[i])->key)
				{
					(G.vert[i])->prim_par = G.vert[tmp];
					(G.vert[i])->key = G.tab[tmp][i];
					Q.heap(Q.isIn(i));
				}
	}
}

void initialize(graf_adj & G, vertex * s)
{
	for(int i = 0; i < G.n; ++i)
	{
		(G.vert[i])->d_dist = vertex::MAXINT;
		(G.vert[i])->d_par = 0;
	}
	s->d_dist = 0;
	s->d_dist = 0;
}

void relax(graf_adj & G, int u, int v)
{
	if((G.vert[v])->d_dist > (G.vert[u])->d_dist + G.tab[u][v])
	{
		(G.vert[v])->d_dist = (G.vert[u])->d_dist + G.tab[u][v];
		(G.vert[v])->d_par = G.vert[u];
	}
}

bool bellman_ford(graf_adj & G, vertex * s)
{
	initialize(G, s);
	for(int i = 1; i < G.n - 1; ++i)
		for(int j = 0; j < G.m; ++j)
			relax(G, (G.E[j])->v1, (G.E[j])->v2);
	for(int j = 0; j < G.m; ++j)
		if((G.vert[(G.E[j])->v2])->d_dist > (G.vert[(G.E[j])->v1])->d_dist + G.tab[(G.E[j])->v1][(G.E[j])->v2])
			return false;
	return true;
}

void topological_sort(graf_adj & G, int * &t)
{
	int x = G.n-1;
	G.time = 0;
	stos<int> S;
	for(int s = 0; s < G.n; ++s)  if((G.vert[s])->color == vertex::bialy)	 
	{
		S.push(s);
		while(!S.empty())
		{
			int tmp = S.pop();
			(G.vert[tmp])->color = vertex::szary;
			(G.vert[tmp])->start = ++(G.time);
			S.push(tmp);
			for(int i = 0; i < G.n; ++i)
				if(G.tab[tmp][i])
					if((G.vert[i])->color == vertex::bialy)
					{
						(G.vert[i])->dfs_par = G.vert[tmp];
						S.push(i);
						break;
					}
			if(i == G.n)
			{
				tmp = S.pop();
				(G.vert[tmp])->color = vertex::czarny;
				(G.vert[tmp])->end = ++(G.time);
				t[x--] = tmp;
			}
		}
	}
}

void dag_s_p(graf_adj & G, vertex * s)
{
	int * t = new int [G.n];
	topological_sort(G, t);
	initialize(G, s);
	for(int i = 0; i < G.n; ++i)
		for(int j = 0; j < G.n; ++j)	
			if(G.tab[t[i]][j])
				relax(G, t[i], j);
}

struct dijks
{
	struct el
	{
		vertex * e;
		el * next;
		el(vertex * a = 0, el * n = 0): e(a), next(n) {}
	};

	el * Top;
	el * Back;

	dijks(): Top(0), Back(0) {}
	~dijks()
	{
		el * tmp = Top;
		while(tmp)
		{
			Top = Top->next;
			delete tmp;
			tmp = Top;
		}
	}

	void add(vertex * x)
	{
		if(Top)
		{
			Back->next = new el(x);
			Back = Back->next;
		}
		else
		{
			Top = new el(x);
			Back = Top;
		}
	}
};

void dijkstra(graf_adj & G, vertex * s, dijks & A)
{
	initialize(G, s);
	kolejka_p Q(G.n);
	for(int i = 0; i < G.n; ++i)
		Q.push(i);
	while(!Q.empty())
	{
		int tmp = Q.top();
		Q.pop();
		A.add(G.vert[tmp]);
		for(int i = 0; i < G.n; ++i)
			if(G.tab[tmp][i])
			{
				relax(G, tmp, i);
				Q.heap(Q.isIn(i));
			}
	}
}

#endif