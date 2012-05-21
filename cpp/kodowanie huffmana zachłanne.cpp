#include<iostream>
#include<queue>

using namespace std;

struct tree
{
	tree *left;
	tree *right;
	char ch;
	int val;

	tree() {};
	tree(char c, int a, tree *l = NULL, tree *r = NULL): ch(c), val(a), left(l), right(r) {};
	~tree()
	{
		if(this->left) delete this->left;
		if(this->right) delete this->right;
	}
};

struct comp
{
	bool operator() (const tree * l, const tree * r)
	{
		return l->val < r->val;
	}
};

tree * fun(int * tab, int n)
{
	tree * l, *p, *c;
	priority_queue<tree *, vector<tree *>, comp> q;
	for(int i = 0; i < n; ++i)
		q.push(new tree(i + 'a', tab[i]));
	while(1)
	{
		l = q.top();
		q.pop();
		p = q.top();
		q.pop();
		c = new tree('*', l->val + p->val, l, p);
		if(q.empty()) return c;
		q.push(c);
	}
}

void wypisz(tree * head)
{
	if(head)
	{
		cout << head->ch;
		wypisz(head->left);
		wypisz(head->right);
	}
}

int main()
{
	int n = 5;
	int * tab = new int [n];
	for(int i = 0; i < n; ++i)
		cin >> tab[i];
	tree * head = fun(tab, n);
	wypisz(head);
	getchar();
	getchar();
	return 0;
}