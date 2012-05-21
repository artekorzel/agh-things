#include<stdio.h>
#include<conio.h>
#include<math.h> 

int pierwsza(int a)
{
        int k = 0;
        if (a % 2 == 0) 
        {
                k = 1;
        }
        else
        {
                for (int j = 3; j <= (pow(a, 0.5)); j += 2)
                {
                        if (a % j == 0) k = 1;
                }
        }
        return k;
} 
 
int main()
{
        int n;
        scanf("%d",&n);
        int i = 2;
        while (i <= n)
        {
                if (n % i == 0)
                {
                        printf("%d ",i);
                        n = n / i;
                } 
                else
                {
                        ++i;
                        while (pierwsza(i) != 0) ++i;
                }
        }
        getch();
        return 0;
}       
