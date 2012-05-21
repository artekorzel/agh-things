#include<stdio.h>
#include<time.h>
#include<stdlib.h>

float losuj()
{
	
	return (float)((rand() % 19)) - 10 + ((float)rand())/RAND_MAX;
	//return 20*(float)rand()/RAND_MAX - 10;
}

int main()
{
	srand((int)(time(NULL)));
	int i;
        float tab[10];
	for(i = 0; i < 10; i++) tab[i] = losuj();
	
	for(i = 0; i < 10; i++) printf("%f ", tab[i]);
	printf("%d", RAND_MAX);
}

