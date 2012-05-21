#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct el_listy
{
	el_listy * wsk;
	int war;
};

void write(struct el_listy ** head)
{
	struct el_listy * h = *head;
	while(h != 0)
	{		
		printf("%d ", (*h).war);
		h = (*h).wsk;
	}
	printf("\n");
}		

void quicksort(struct el_listy ** h)
{
	struct el_listy * head = *h;
	if (head != 0)
	{
		struct el_listy * h1, * h2, *lom = head, *p1, *p2;		
		h1 = (struct el_listy *)malloc(sizeof(struct el_listy));		
		h2 = (struct el_listy *)malloc(sizeof(struct el_listy));
		p1 = h1;
		p2 = h2;
		head = (*head).wsk;
		while(head != 0)
		{
			if((*head).war < (*lom).war)
			{
				(*p1).wsk = head;
				p1 = (*p1).wsk;
			}
			else
			{
				(*p2).wsk = head;
				p2 = (*p2).wsk;
			}
			head = (*head).wsk;
			(*lom).wsk = head;			
		}
		(*p1).wsk = 0;
		(*p2).wsk = 0;
		
		struct el_listy *tmp = h1;
		h1 = (*h1).wsk;		
		free(tmp);
		tmp = h2;
		h2 = (*h2).wsk;
		free(tmp);

		quicksort(&h1);
		quicksort(&h2);
		
		if(h1 == 0) head = lom;
		else
		{
			head = h1;
			while(h1 != 0)
			{
				p1 = h1;
				h1 = (*h1).wsk;
			}
			(*p1).wsk = lom;
		}
		(*lom).wsk = h2;
	}
	*h = head;
}
			
struct el_listy * make(int i)
{
	struct el_listy *head, *p, *q;
	head = (struct el_listy *)malloc(sizeof(struct el_listy));
	p = head;
	(*p).war = rand() % 999;
	i--;
	while(i > 0)
	{		
		q = (struct el_listy *)malloc(sizeof(struct el_listy));
		(*q).war = rand() % 999;
		(*p).wsk = q;
		p = q;
		i--;
	}
	(*q).wsk = 0;
	return head;
}

int main()
{
	srand((int)time(NULL));
	struct el_listy * head = make(1000000);
	
	clock_t start, end;
	start = clock();
	
	quicksort(&head);

	end = clock();
	printf ("%f s\n",
		(double)( end - start ) / (double)CLOCKS_PER_SEC);

	getchar();
}
