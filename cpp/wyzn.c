#include<stdio.h>
#include<math.h>
#include<stdlib.h>

float wyznacznik(float **tab, int roz)
{
	if (roz == 1) return tab[0][0];
	else
	{
		float a = 0.0;

		int i, j = roz - 1, k, l;
		
		float **tab2;
		*tab2 = (float *)malloc(j * sizeof(float *));
		for (i = 0; i < j; ++i)
			tab2[i] = (float *)malloc(j * sizeof(float));

		for (i = 0; i < roz; ++i)
		{
			for (k = 0; k < j; ++k)
			{
				for (l = 0; l < i; ++l) tab2[l][k] = tab[l][k];
				for (l = i + 1; l < roz; ++l) tab2[l-1][k] = tab[l][k];
			}

			a = a + pow((float)(-1), (i + j)) * wyznacznik(tab2, j) * tab[i][j];
		}		
		return a;
	}
}

int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		FILE *plik = fopen(argv[1], "r");

		int rozmiar, i, j;
		fscanf(plik, "%d ", &rozmiar);

		float **tab;
		*tab = (float *)malloc(rozmiar * sizeof(float *));
		for (i = 0; i < rozmiar; ++i)
			tab[i] = (float *)malloc(rozmiar * sizeof(float));

		int n = 0;
		float x;

		while (!feof(plik))
		{
			fscanf(plik, "%f ", &x);
			tab[(n % rozmiar)][(n / rozmiar)] = x;	
			++n;
		}

		fclose(plik);

		for (i = 0; i < rozmiar; ++i)
		{
		    for (j = 0; j < rozmiar; ++j) printf("%f ", tab[j][i]);
			printf("\n");
		}

		float wyzn = 0.0;
		printf("%f\n", wyznacznik(tab, rozmiar));
	} else printf("nic");
}