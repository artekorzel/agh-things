#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct el_listy
{
	el_listy * wsk;
	int war;
};

void insertion(struct el_listy **head)
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

void write(struct el_listy ** head)
{
	while(*head != 0)
	{		
		printf("%d ", (**head).war);
		*head = (**head).wsk;
	}
	printf("\n");
}

void bucket(int *tab, int n, int max)
{
	int i, j, k = (n-1) / 10 + 1;
	struct el_listy **pom = (struct el_listy **)malloc(k * sizeof(struct el_listy*));
	for(i = 0; i < k; ++i) pom[i] = 0;
	double szer = max / k;
	struct el_listy *x;
	for(i = 0; i < n; ++i)
	{
		x = (struct el_listy *)malloc(sizeof(struct el_listy));
		double a = tab[i]/szer;
		(*x).wsk = pom[(int)a];
		pom[(int)a] = x;
		(*x).war = tab[i];
	}
	j = 0;
	for(i = 0; i < k; ++i)
	{
		insertion(&pom[i]);
		//write(pom + i);
		
		while(pom[i] != 0)
		{
			tab[j] = (**(pom + i)).war;
			x = pom[i];
			pom[i] = (**(pom + i)).wsk;
			free(x);
			j++;
		}

	}
		
}

/*struct el_listy ** make(int *tab, int i)
{
	struct el_listy **head, *p, *q;
	head = (struct el_listy **)malloc(sizeof(struct el_listy *));
	*head = (struct el_listy *)malloc(sizeof(struct el_listy));
	p = *head;
	int j = 0;
	(*p).war = &tab[j++];
	i--;
	while(i > 0)
	{		
		q = (struct el_listy *)malloc(sizeof(struct el_listy));
		(*q).war = &tab[j++];
		(*p).wsk = q;
		p = q;
		i--;
	}
	(*q).wsk = 0;
	return head;
}*/

int main()
{
	srand((int)time(NULL));
	int n = 100000;
	int max = 100000;
	int i, *tab = (int *) malloc(n * sizeof(int));
	for(i = 0; i < n; ++i) tab[i] = rand() % max;

	/*struct el_listy **head = make(tab, n);
	insertion(head);
	write(head);*/
	printf("%d ", time(0));
	bucket(tab, n, max);
	printf("%d ", time(0));
	//for(i = 0; i < n; ++i) printf("%d ", tab[i]);
	getchar();
}


