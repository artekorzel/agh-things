#ifndef _trie_h_
#define _trie_h_

struct trieEl
{
	char val;
	trieEl * down;
	trieEl * right;

	trieEl(char a = 0)
	{
		this->val = a;
		this->down = 0;
		this->right = 0;
	}
};

struct trie
{
	trieEl * head;

	trie()
	{
		this->head = 0;
	}

	void insert(char *);
	bool isIn(char *);
	void del(char *);
	void write();
	bool usun(trieEl *, char *, int, int);
};

#endif

