#include"splay.h"
#include<iostream>

void delBst(bstEl * p)
{
	if(p)
	{
		delBst(p->left);
		delBst(p->right);
		delete p;
	}
}

splay::~splay()
{
	delBst(this->root);
}

void splay::write(bstEl * p)
{
	if(p)
	{
		write(p->left);
		std::cout << p->val << " ";
		write(p->right);
	}
}

void splay::left_rot(bstEl * p)
{
	if(p && p->right)
	{
		if(p->parent)
		{
			if(p->parent->right == p)
				p->parent->right = p->right;
			else p->parent->left = p->right;
		}
		else this->root = p->right;
		bstEl * q = p->right->left;
		p->right->left = p;
		p->right->parent = p->parent;
		p->parent = p->right;
		p->right = q;
		if(q) q->parent = p;
	}
}

void splay::right_rot(bstEl * p)
{
	if(p && p->left)
	{
		if(p->parent)
		{
			if(p->parent->right == p)
				p->parent->right = p->left;
			else p->parent->left = p->left;
		}
		else this->root = p->left;
		bstEl * q = p->left->right;
		p->left->right = p;
		p->left->parent = p->parent;
		p->parent = p->left;
		p->left = q;
		if(q) q->parent = p;
	}
}

bstEl * splay::splayMe(int a)
{
	bstEl * p = this->root;
	bstEl * q = 0;
	while(p && p->val != a)
	{
		q = p;
		if(p->val < a)
			p = p->right;
		else p = p->left;
	}
	if(!p) p = q;
	while(p->parent)
	{
		if(p->parent->parent)
		{
			if(p->parent->left == p)
			{
				if(p->parent->parent->left == p->parent)
				{
					this->right_rot(p->parent->parent);
					this->right_rot(p->parent);
				}
				else
				{
					this->right_rot(p->parent);
					this->left_rot(p->parent);
				}
			}
			else 
			{
				if(p->parent->parent->right == p->parent)
				{
					this->left_rot(p->parent->parent);
					this->left_rot(p->parent);
				}
				else
				{
					this->left_rot(p->parent);
					this->right_rot(p->parent);
				}
			}
		}
		else
		{
			if(p->parent->left == p)
				this->right_rot(p->parent);
			else
				this->left_rot(p->parent);
		}
	}
	return this->root;
}

bstEl * splay::insert(int a)
{
	if(this->root)
	{
		if(this->splayMe(a)->val == a)
			return this->root;
		bstEl * pom = new bstEl(a);
		this->root->parent = pom;
		if(this->root->val < a)
		{
			pom->left = this->root;
			pom->right = this->root->right;
			if(pom->right) pom->right->parent = pom;
			this->root->right = 0;
		}
		else
		{
			pom->right = this->root;
			pom->left = this->root->left;
			if(pom->left) pom->left->parent = pom;
			this->root->left = 0;
		}
		this->root = pom;
	}
	else
		this->root = new bstEl(a);
	return this->root;
}

bstEl * splay::successor(bstEl * p)
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
				if(p->parent->left == p)
					return p->parent;
				else p = p->parent;
			}
		}
	}
	return 0;
}

bstEl * splay::predeccessor(bstEl * p)
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
				if(p->parent->right == p)
					return p->parent;
				else p = p->parent;
			}
		}
	}
	return 0;
}

void splay::del(int a)
{
	if(this->root && this->splayMe(a)->val == a)
	{
		bstEl * pom = this->root->right;
		if(pom)
		{
			pom->parent = 0;
			this->root->right = 0;
		}
		bstEl * pred = this->predeccessor(this->root);
		bstEl * tmp;
		if(pred)
		{
			tmp = this->root;

			if(pred->parent->right == pred)
				pred->parent->right = pred->left;
			else
				pred->parent->left = pred->left;
			if(pred->left) pred->left->parent = pred->parent;
			pred->parent = 0;
			pred->left = 0;
			
			this->root = pred;

			pred->right = pom;
			if(pom) pom->parent = this->root;
		}
		else
		{
			tmp = this->root;
			this->root = pom;
		}
		delete tmp;
	}
}
