#include<iostream>

int main()
{
	int n = 10;
	int * tab = new int [n];
	int i;
	for(i = 0; i < n; ++i)
		std::cin >> tab[i];
	int wyn = 0, aktwyn = 0;
	int poc, pocz, kon;
	for(i = 0; i < n; ++i)
	{
		if(aktwyn > 0)
			aktwyn += tab[i];
		else
		{
			poc = i;
			aktwyn = tab[i];
		}
		if(aktwyn > wyn)
		{
			pocz = poc;
			kon = i;
			wyn = aktwyn;
		}
	}
	std::cout << wyn << std::endl;
	for(i = pocz; i <= kon; ++i)
		std::cout << tab[i] << " ";
	getchar();
	getchar();
	return 0;
}