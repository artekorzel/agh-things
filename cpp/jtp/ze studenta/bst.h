#ifndef _bst_h_
#define _bst_h_

struct bstEl
{
	int val;
	bstEl *parent;
	bstEl *left;
	bstEl *right;
	
	bstEl(int a = 0, bstEl *par = 0)
	{
		this->val = a;
		this->parent = par;
		this->left = 0;
		this->right = 0;
	}
	
	~bstEl()
	{
		delete this;
	}
};

struct bst
{
	bstEl * root;
	
	bst()
	{
		root = 0;
	}
	
	//~bst();

	bstEl * insert(int);
	void del(bstEl *);//
	bstEl * search(int);
	bstEl * successor(bstEl *);
	bstEl * predeccessor(bstEl *);
	bstEl * min();
	bstEl * max();
	void write(bstEl *);
	void left_rot(bstEl *);//
	void right_rot(bstEl*);//
};
#endif