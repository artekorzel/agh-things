#include<stdio.h>
#include<stdlib.h>

int main()
{
	int i, N, M;
	printf("Podaj N: ");
	scanf("%d", &N);
	printf("Podaj M: ");
	scanf("%d", &M);
	int **tab;
	tab = malloc(N * sizeof(int *));
	for(i = 0; i < N; ++i)
		tab[i] = malloc(M * sizeof(int));
	//wypelnienie
	free(tab);
}
