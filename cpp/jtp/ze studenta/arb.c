#include<stdio.h>
#include<stdlib.h>

void merge(int * tab2, int * tab, int l1, int l2, int r2, int * licznik)
{
	int szer = r2 - l1;
	int r1 = l2;

	int i = l1, k = l1;
	while((l1 < r1) && (l2 < r2))
	{
		if(tab[l2] > tab[l1])
		{
			tab2[i++] = tab[l2];
			*licznik += r1-l1;
			++l2;
		}
		else tab2[i++] = tab[l1++];
	}
	while(l1 < r1)
		tab2[i++] = tab[l1++];
	while(l2 < r2)
		tab2[i++] = tab[l2++];
}

void sort(int *t, int n, int * licznik)
{
	int * serie = (int *)malloc((n+2)*sizeof(int));
	int lserii = 1;
	serie[0] = 0;
	int i;
	for(i = 1; i < n; ++i)
		if(t[i] > t[i-1])
			serie[lserii++] = i;
	serie[lserii] = serie[lserii + 1] = n;

	int * tab2;
	tab2 = (int *)malloc(n * sizeof(int));

	int *wt = t, *tmp;

	while(lserii > 1)
	{
		int m = 0;
		for(i = 0; i < lserii; i += 2)
		{
			merge(tab2, t, serie[i], serie[i+1], serie[i+2], licznik);
			serie[m++] = serie[i];
		}
		serie[m] = serie[m+1] = n;
		lserii = m;
		tmp = t;
		t = tab2;
		tab2 = tmp;
	}
	free(serie);
	
	if(wt != tab2) free(tab2);
	else free(t);
}


int main()
{	
	int zestawy, elementy, i;
  scanf("%d", &zestawy);
  int * tab;

  int licznik = 0;
  while(zestawy)
  {
	 scanf("%d", &elementy);
     
     tab = (int *)malloc(elementy * sizeof(int));
     
     i = 0;
     
     while(i < elementy)
     {
       scanf("%d", &tab[i]);
       ++i;
     }
     
     sort(tab, elementy, &licznik);     
     free(tab);     
     --zestawy;
  }

	printf("%d\n", licznik);
  return 0;
}