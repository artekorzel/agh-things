#ifndef _ZBIORY__H_
#define _ZBIORY__H_

template<class T>
class zbior
{
public:
	void make_set(T * t)
	{
		t->set_root = t;
		t->rank = 0;
	}

	void link(T * t1, T * t2)
	{
		if(t1->rank > t2->rank)
			t2->set_root = t1;
		else
		{
			t1->set_root = t2;
			if(t1->rank == t2->rank)
				t2->rank = ++(t2->rank);
		}
	}

	void mix(T * t1, T * t2)
	{
		link(findset(t1), findset(t2));
	}

	T * findset(T * t1)
	{
		if(t1 != t1->set_root)
			t1->set_root = findset(t1->set_root);
		return t1->set_root;
	}
};

#endif