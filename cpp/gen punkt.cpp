#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#define frand() ((double)rand() / (RAND_MAX + 1.0))

int aaa(char *tekst, int n)
{	
	struct punkt
	{
		double x,y;
	};

	FILE *plik;
	plik = fopen(tekst, "a");

	fprintf(plik, "%d\n", n);

	struct punkt a;
	int i;
	srand((int)(time(NULL)));
	for (i = 0; i < n; i++)
	{
		a.x = ((rand() % 40) - 20) + frand();
		a.y = ((rand() % 40) - 20) + frand();

		fprintf(plik, "%f %f\n", a.x, a.y);
	}
	fclose(plik);
	return 0;
}

int main(int argc, char *argv[])
{
	if (argc == 3) aaa(argv[1], atoi(argv[2]));
	else printf("nic");
}


