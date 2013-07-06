#include<stdio.h>
#include<stdlib.h>

void wypelnij(int **tab, int ppion, int kpion, int ppoz, int kpoz, int i, int *max)
{
		int j;
		for(j = ppion; j < kpion && i <= (*max); ++j)
			tab[j][ppoz] = i++;
		for(j = ppoz; j < kpoz && i <= (*max); ++j)
			tab[kpion][j] = i++;
		for(j = kpion; j >= ppion && i <= (*max); --j)
			tab[j][kpoz] = i++;
		if(i <= (*max)) wypelnij(tab, ppion, kpion-1, ppoz+1, kpoz-1, i, max);
}

int main()
{
	int i, j, N, M;
	printf("Podaj N: ");
	scanf("%d", &N);
	printf("Podaj M: ");
	scanf("%d", &M);

	int **tab;
	tab = (int **)malloc(N * sizeof(int *));
	for(i = 0; i < N; ++i)
		tab[i] = (int *)malloc(M * sizeof(int));

	int max = M * N;

	wypelnij(tab, 0, N-1, 0, M-1, 1, &max);

	for(i = 0; i < N; ++i)
	{
		for(j = 0; j < M; ++j)
			printf("%2d ", tab[i][j]);
		printf("\n");
	}
	free(tab);
	getchar();
	getchar();
}
