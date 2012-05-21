#include<stdio.h>
#include<time.h>
#include<stdlib.h>

struct el_listy
{
	el_listy * wsk;
	int war;
};

void insertion_sort(struct el_listy ** head)
{
	if(*head != 0)
	{
		struct el_listy * akt = (**head).wsk, * prev = *head;
		while(akt != 0)
		{
			struct el_listy * p = akt;
			akt = (*akt).wsk;
			(*prev).wsk = akt;
			
			struct el_listy * q = 0, * r = *head; 
			while(((r != akt) && (*r).war <= (*p).war))
			{
				q = r;
				r = (*r).wsk;
			}
			if(r != *head) (*q).wsk = p;
			else *head = p;
			(*p).wsk = r;
			if(r == akt) prev = (*prev).wsk;
		}
	}
}

struct el_listy ** make(int i)
{
	struct el_listy **head, *p, *q;
	head = (struct el_listy **)malloc(sizeof(struct el_listy *));
	*head = (struct el_listy *)malloc(sizeof(struct el_listy));
	p = *head;
	(*p).war = rand() % 10000;
	i--;
	while(i > 0)
	{		
		q = (struct el_listy *)malloc(sizeof(struct el_listy));
		(*q).war = rand() % 10000;
		(*p).wsk = q;
		p = q;
		i--;
	}
	(*q).wsk = 0;
	return head;
}

void write(struct el_listy ** head)
{
	while(*head != 0)
	{		
		printf("%d ", (**head).war);
		*head = (**head).wsk;
	}
}

		

int main()
{
	srand((int)time(NULL));
	struct el_listy ** head = make(20000);
	insertion_sort(head);
	write(head);
	getchar();
}
