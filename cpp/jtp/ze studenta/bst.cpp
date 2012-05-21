#include"bst.h"
#include<iostream>

bstEl * bst::insert(int a)
{
	if(this->root)
	{
		bstEl *p = this->root;
		bstEl *q = 0;
		while(p)
		{
			q = p;
			if(p->val < a)
				p = p->right;
			else if(p->val > a)
				p = p->left;
			else return p;
		}
		p = new bstEl(a, q);
		if(a < q->val)
			q->left = p;
		else q->right = p;
		return p;
	}
	else this->root = new bstEl(a);
	return this->root;
}

void bst::write(bstEl * p)
{
	if(p)
	{
		write(p->left);
		std::cout << p->val << " ";
		write(p->right);
	}
}

bstEl * bst::min()
{
	if(this->root)
	{
		bstEl * p = this->root;
		while(p->left)
			p = p->left;
		return p;
	}
	else return 0;
}

bstEl * bst::max()
{
	if(this->root)
	{
		bstEl * p = this->root;
		while(p->right)
			p = p->right;
		return p;
	}
	else return 0;
}

bstEl * bst::search(int a)
{
	if(this->root)
	{
		bstEl *p = this->root;
		while(p)
		{
			if(p->val < a)
				p = p->right;
			else if(p->val > a)
				p = p->left;
			else return p;
		}
	}
	return 0;
}

bstEl * successor(bstEl * p)
{
	if(p)
	{
		if(p->right)
		{
			p = p->right;
			while(p->left)
				p = p->left;
			return p;
		}
		else
		{
			while(p->parent)
			{
				if(p->parent->left = p)
					return p->parent;
				else p = p->parent;
			}
		}
	}
	return 0;
}

bstEl * predeccessor(bstEl * p)
{
	if(p)
	{
		if(p->left)
		{
			p = p->left;
			while(p->right)
				p = p->right;
			return p;
		}
		else
		{
			while(p->parent)
			{
				if(p->parent->right = p)
					return p->parent;
				else p = p->parent;
			}
		}
	}
	return 0;
}

void del(bstEl * p)
{
	if(p)
	{
		if(p->left)
		{
			if(p->right)
			{
				
				bstEl * q = successor(p);
				if(q->parent->left = q)
				{
					q->parent->left = q->right;
					q->right->parent = q->parent;
				}
				else
				{
					q->parent->right = q->right;
					q->right = q->parent;
				}
				q->parent = p->parent;
				if(p->parent->left = p)
					p->parent->left = q;
				else p->parent->right = q;
				q->left = p->left;
				q->right = p->right;
				p->left = 0;
				p->right = 0;
			}
			else
			{
				p->left->parent = p->parent;
				if(p->parent->left = p)
					p->parent->left = p->left;
				else p->parent->right = p->left;
				p->left = 0;
			}
		}
		else if(p->right)
		{
			p->right->parent = p->parent;
			if(p->parent->left = p)
				p->parent->left = p->right;
			else p->parent->right = p->right;
			p->right = 0;
		}
		p->parent = 0;
		delete p;
	}
}
		
 