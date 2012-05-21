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
	(*p).war = rand() % 10;
	i--;
	while(i > 0)
	{		
		q = (struct el_listy *)malloc(sizeof(struct el_listy));
		(*q).war = rand() % 10;
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
	return pom;
}

void sort(struct el_listy ** head, int n)
{
	struct el_listy * pocz = (struct el_listy *)malloc(sizeof(struct el_listy));
	pocz->wsk = *head;
	*head = pocz;
	struct el_listy * kon, *p1, *k1, *p2, *k2;
	struct el_listy *tmp2;
	int i;
	for(i = 1; i < n; i *= 2)
	{
		pocz = *head;
		int licznik = n;
		while(licznik > 0)
		{
			int j = i;
			p1 = pocz->wsk;
			k1 = p1;
			--licznik;
			while(k1 && (j > 1))
			{				
				k1 = k1->wsk;
				--j;
				--licznik;
			}
			if(k1) 
			{
				kon = k1->wsk;
				k1->wsk = 0;
			
				int j = i;
				p2 = kon;
				k2 = p2;
				--licznik;
				while(k2 && (j > 1))
				{				
					k2 = k2->wsk;
					--j;
					--licznik;
				}
				if(k2) 
				{
					kon = k2->wsk;
					k2->wsk = 0;
				} else
					kon = 0;					
			
				struct el_listy *pom = (struct el_listy *)malloc(sizeof(struct el_listy));
				struct el_listy *tmp = scal(pom, p1, p2);
				tmp->wsk = kon;
				tmp2 = pom;
				pom = pom->wsk;
				free(tmp2);
				pocz->wsk = pom;

				pocz = tmp;
			}
		}
	}
	tmp2 = *head;
	*head = (*head)->wsk;
	free(tmp2);
}

int main()
{
	srand((int)time(NULL));
	int n = 1000;
	struct el_listy ** head = make(n);
	//write(*head);

	sort(head, n);
	
	write(*head);
	getchar();
}
