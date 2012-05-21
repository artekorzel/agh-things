#include"bst.h"

#include<iostream>

using namespace std;

int main()
{
	bst nowe;
	nowe.insert(5);
	nowe.insert(10);
	nowe.insert(15);
	nowe.insert(1);
	nowe.insert(2);
	nowe.write(nowe.root);
	cout << endl;
	cout << (nowe.min())->val << endl;
	cout << (nowe.max())->val << endl;
	cout << (nowe.search(5))->val << endl;
	bstEl * p = nowe.root;
	nowe.del(p);
	cout << (nowe.successor(nowe.root))->val << endl;
	cout << (nowe.predeccessor(nowe.root))->val << endl;
	
}
