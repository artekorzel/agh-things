#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void merge(int *pom, int *s1, int *s2, int *e2)
{
	int *e1 = s2;
	while((s1 != e1) && (s2 != e2))
		*pom++ = *s1 < *s2 ? *s1++ : *s2++;
	while(s1 != e1) *pom++ = *s1++;
	while(s2 != e2) *pom++ = *s2++;
}

void sort(int *t, int n)
{
	int * pom, * wt, i;
	pom = new int[n];
	wt = t;
	
	int p,s,k;
	for(i = 1; i < n; i *= 2)
	{
		p = 0;
		s = i;
		k = s + i;
		while(p < n)
		{
			if (s > n) s = n;
			if (k > n) k = n;
			merge(pom + p, t + p, t + s, t + k);
			p = k;
			s = p + i;
			k = s + i;
		}
		int *tmp;
		tmp = t;
		t = pom;
		pom = tmp;
	}
	if(wt != t)
	{
		merge(wt, t, t + n, t + n);
		delete [] t;
	}
	else delete [] pom;
}

int main()
{
	const int n = 10000000;
	int *t = new int[n];
	int i;
	srand((int)(time(NULL)));
	for (i = 0; i < n; ++i) t[i] = rand() % 100;
	
	clock_t start, end;
	start = clock();
	
	sort(t, n);

	end = clock();
	printf("%f", (double)(end-start)/double(CLOCKS_PER_SEC));
	//for (i = 0; i <n; ++i) printf("%d ", t[i]);
	delete [] t;
	getchar();
}