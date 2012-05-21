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

void sort(int * t, int n)
{
	int * serie = new int[n + 2];
	int *tmp = new int[n], *wt = t;
	int lserii = 1;
	serie[0] = 0;
	int i;
	for(i = 1; i < n; ++i)
		if(t[i] < t[i-1])
			serie[lserii++] = i;
	serie[lserii] = serie[lserii + 1] = n;
	while(lserii > 1)
	{
		int m = 0;
		for(i = 0; i < lserii; i += 2)
		{
			merge(tmp + serie[i], t + serie[i], t + serie[i+1], t + serie[i+2]);
			serie[m++] = serie[i];
		}
		serie[m] = serie[m+1] = n;
		lserii = m;
		int * tmp2;
		tmp2 = t;
		t = tmp;
		tmp = tmp2;
	}
	if(wt != t) merge(wt, t, t + n, t + n);
	if(tmp != wt) delete [] tmp;
	else delete [] t;
	delete [] serie;
}

int main()
{
	const int n = 10000000;
	int t[n];
	int i;
	srand((int)(time(NULL)));
	for (i = 0; i < n; ++i) t[i] = rand() % 100000;
	clock_t start, end;
	start = clock();
	
	sort(t, n);

	end = clock();
	printf ("%f s\n",
		(double)( end - start ) / (double)CLOCKS_PER_SEC);
	

	for (i = 0; i <n; ++i) printf("%d ", t[i]);
	getchar();
}