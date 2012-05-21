#ifndef _splay_h_
#define _splay_h_

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
};

struct splay
{
	bstEl * root;
	
	splay()
	{
		root = 0;
	}
	
	~splay();

	bstEl * insert(int);
	void del(int);
	bstEl * splayMe(int);
	int successor(bstEl *);
	int predeccessor(bstEl *);
	void write(bstEl *);
	void left_rot(bstEl *);
	void right_rot(bstEl *);
};
#endif