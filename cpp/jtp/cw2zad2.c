#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Zle argumenty, program zostanie zamkniety");
		return 1;
	}
	
	FILE *plik = fopen(argv[1], "r");
	if(plik == 0)
	{
		printf("Blad otwierania pliku, program zostanie zamkniety");
		return 2;
	}
	
	int N, i, j;
	if(fscanf(plik, "%d\n", &N) == EOF)
	{
		printf("Niew³aœciwe dane, program zostanie zamkniety");
		return 3;
	}
	
	float **tab;
	tab = (float **)malloc(N * sizeof(float *));
	for(i = 0; i < N; ++i)
		tab[i] = (float *)malloc(3 * sizeof(float));
	for(i = 0; i < N; ++i)
		if(fscanf(plik, "%f %f %f\n", &tab[i][0], &tab[i][1], &tab[i][2]) == EOF)
		{
			printf("Niew³aœciwe dane, program zostanie zamkniety");
			return 3;
		}
		
	fclose(plik);
	//wyznaczenie
	for(i = 0; i < N; ++i)
	{
		for(j = 0; j < 3; ++j)
			printf("%f ", tab[i][j]);
		printf("\n");
	}
	free(tab);
	return 0;
}	

