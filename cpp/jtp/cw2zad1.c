#include<stdio.h>
#include<time.h>
#include<stdlib.h>

float losuj()
{
	return (float)(rand() % RAND_MAX)/RAND_MAX * 10 - 5; //przedzial
}

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		printf("Zle argumenty, program zostanie zamkniety");
		return 1;
	}
	
	srand(time(NULL));
	int i, N = atoi(argv[2]);
	FILE *plik = fopen(argv[1], "w");
	if(plik == 0)
	{
		printf("Blad otwierania pliku, program zostanie zamkniety");
		return 2;
	}

	fprintf(plik, "%d\n", N);
	for (i = 0; i < N; ++i)
		fprintf(plik, "%f %f %f\n", losuj(), losuj(), losuj());
	fclose(plik);
	return 0;
}

