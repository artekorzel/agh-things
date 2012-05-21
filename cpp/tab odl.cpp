#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
  if (argc == 2)
  {
	int i = 0, j = 0, n;	 

	FILE *pl;
	pl = fopen(argv[1], "r");

	fscanf(pl, "%d\n", &n);

	float **tab;
	tab = (float **)malloc(n * sizeof(float *));
	for (i = 0; i < n; i++) 
		*(tab + i) = (float *)malloc(2 * sizeof(float));
	
	i = 0;

	while(!feof(pl))
	{
		fscanf(pl, "%f %f\n", &tab[i][0], &tab[i][1]);
		
		++i;			
	}
	fclose(pl);

	float **tabl;
	tabl = (float **)malloc(n * sizeof(float *));
	for (i = 0; i < n; i++) tabl[i] = (float *)malloc(n * sizeof(float));

	for (i = 0; i < n; i++)
	{
		tabl[i][i] = 0;
		for (j = 0; j < i; j++)
		{
			tabl[i][j] = sqrt((float)(pow((tab[i][0] - tab[j][0]),2)
						 + pow((tab[i][1] - tab[j][1]),2)));
			tabl[j][i] = tabl[i][j];
		}
	}

	float aktsuma, suma = 0;
	int najmn;
	for (i = 0; i < n; i++)
	{
		aktsuma = 0;
		for (j = 0; j < n; j++)
			aktsuma += tabl[i][j];

		if ((aktsuma < suma) || (suma == 0))
		{
			suma = aktsuma;
			najmn = i;
		}
	}

	printf("{%f, %f}", tab[najmn][0], tab[najmn][1]);
  } else printf("nic");
}
