#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct el_listy
{
	el_listy * wsk;
	int war;
};

struct el_listy ** make(int i)
{
	struct el_listy **head, *p, *q;
	head = (struct el_listy **)malloc(sizeof(struct el_listy *));
	*head = (struct el_listy *)malloc(sizeof(struct el_listy));
	p = *head;
	(*p).war = rand() % 99;
	i--;
	while(i > 0)
	{		
		q = (struct el_listy *)malloc(sizeof(struct el_listy));
		(*q).war = rand() % 99;
		(*p).wsk = q;
		p = q;
		i--;
	}
	(*q).wsk = 0;
	return head;
}

void write(struct el_listy * head)
{
	while(head != 0)
	{		
		printf("%d ", (*head).war);
		head = (*head).wsk;
	}
	printf("\n");
}		

struct el_listy * scal(struct el_listy *pom, struct el_listy *s1, struct el_listy *s2) //pom pokazuje na ostatni element w lancuchu docelowym, zwraca 
{																						// poczatek tego samego lancucha
	struct el_listy *p = pom;
	while((s1 != 0) && (s2 != 0))
	{
		if((s1->war) <= (s2->war))
		{
			pom->wsk = s1;
			s1 = s1->wsk;
		} else
		{
			pom->wsk = s2;
			s2 = s2->wsk;
		}
		pom = pom->wsk;
	}
	while(s1 != 0) 
	{
		pom->wsk = s1;
		s1 = s1->wsk;
		pom = pom->wsk;
	}
	while(s2 != 0)
	{
		pom->wsk = s2;
		s2 = s2->wsk;
		pom = pom->wsk;
	}
	pom->wsk = 0;
	return p->wsk;
}

void sort(struct el_listy ** head, int n)
{
	struct el_listy *tmp2 = (struct el_listy *)malloc(sizeof(struct el_listy));
	int i, j;

	struct el_listy ** serie = (struct el_listy **)malloc((n+1) * sizeof(struct el_listy *));
	for(i = 0; i < n+1; ++i)
		serie[i] = 0;

	int lserii = 1;
	serie[0] = *head;
	serie[n] = 0;
	struct el_listy * pom = *head;
	struct el_listy * pom2;
	while(pom != 0)
	{
		pom2 = pom;
		pom = pom->wsk;
		if(pom != 0 && ((pom2->war) > (pom->war)))
		{
			serie[lserii++] = pom;
			pom2->wsk = 0;
		}
	}

	for(i = 1; i < lserii; i *= 2)
	{		
		j = 0;
		while(j < lserii)
		{						
			if(j + i < lserii)
				serie[j] = scal(tmp2, serie[j], serie[j+i]);
			else
				serie[j] = scal(tmp2, serie[j], serie[n]);	
			j += 2*i;
		}
	}
	*head = serie[0];
	free(serie);
	free(tmp2);
}

int main()
{
	srand((int)time(NULL));
	int n = 10000000;
	struct el_listy ** head = make(n);
	//write(*head);
	printf("%d\n", time(0));
	sort(head, n);
	printf("%d\n", time(0));
	//write(*head);
	getchar();
}