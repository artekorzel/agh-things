#include<cstdio>

int main()
{
	int licznik = 15000;
	int ile, n;
	scanf("%d", &ile);
	bool tab[15000];
	for(int i = 0; i < 15000; ++i)
		tab[i] = true;
	while(ile)
	{
		scanf("%d", &n);
		if(tab[n])
		{
			licznik -= 1;
			tab[n] = false;
		}
		ile -= 1;
	}
	printf("%d", licznik);
	return 0;
}