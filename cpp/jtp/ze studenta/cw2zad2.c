#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
	if(argc == 2)
	{
		FILE *plik = fopen(argv[1], "r");
		int N, i, j;
		fscanf(plik, "%d\n", &N);
		float **tab;
		tab = (float **)malloc(N * sizeof(float *));
		for(i = 0; i < N; ++i)
			tab[i] = (float *)malloc(3 * sizeof(float));
		for(i = 0; i < N; ++i)
			fscanf(plik, "%f %f %f\n", &tab[i][0], &tab[i][1], &tab[i][2]);
		fclose(plik);
		//wyznaczenie
		for(i = 0; i < N; ++i)
		{
			for(j = 0; j < 3; ++j)
				printf("%f ", tab[i][j]);
			printf("\n");
		}
		free(tab);
	}
}	

