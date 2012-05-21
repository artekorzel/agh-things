#include<stdio.h>
#include<conio.h>

int main()
{
    double suma = 0;
    int n;
    scanf("%d", &n);
    for (n; n >= 0; n--)
    {
        double a = 1/(2*(double)n+1); 
		if (n % 2 == 0) suma += a;
        else suma -= a;
    }
	suma *= 4;
    printf("%f", suma);
    getch();
}
        
     
